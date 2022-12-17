#include "oot3d_world.hpp"
#include "oot3d_entrance.hpp"
#include "../search.hpp"
#include "../utility/log.hpp"
#include "../utility/timing.hpp"

#include <iostream>
#include <algorithm>

static std::list<uint8_t> allAgeTimes = {OOT3D_CHILD_DAY, OOT3D_CHILD_NIGHT, OOT3D_ADULT_DAY, OOT3D_ADULT_NIGHT};

EvalSuccess Oot3dWorld::EvaluateEventRequirement(Search* search, Event* event)
{
    uint8_t parentAreaAgeTime = search->areaTime[event->area];
    EvalSuccess retval = EvaluateRequirementWithAgeTime(event->requirement, search, parentAreaAgeTime) ? EvalSuccess::Complete : EvalSuccess::NONE;
    return retval;
}

EvalSuccess Oot3dWorld::EvaluateLocationRequirement(Search* search, LocationAccess* locAccess)
{
    auto parentArea = locAccess->area;
    uint8_t parentAreaAgeTime = search->areaTime[parentArea];
    EvalSuccess retval = EvaluateRequirementWithAgeTime(locAccess->requirement, search, parentAreaAgeTime) ? EvalSuccess::Complete : EvalSuccess::NONE;
    return retval;
}

EvalSuccess Oot3dWorld::EvaluateExitRequirement(Search* search, Entrance* exit)
{
    auto parentArea = (Oot3dArea*) exit->GetParentArea();
    auto connectedArea = (Oot3dArea*) exit->GetConnectedArea();
    uint8_t parentAreaAgeTime = search->areaTime[parentArea];
    uint8_t connectedAreaAgeTime = search->areaTime[connectedArea];
    uint8_t exitsAgeTimes = possibleExitAgeTimes[exit];
    uint8_t potentialAgeTimeSpread = ~connectedAreaAgeTime & (parentAreaAgeTime & exitsAgeTimes);
    EvalSuccess evalSuccess = EvalSuccess::NONE;

    // If the connected area already has all the agetimes that this exit can
    // provide, then this exit is unecessary
    if (!(~connectedAreaAgeTime & exitsAgeTimes))
    {
        return EvalSuccess::Unnecessary;
    }
    // If there aren't any potential agetimes to spread, then this exit
    // isn't going to be a success even if we evaluate it
    if (potentialAgeTimeSpread == OOT3D_NO_AGE_TIME)
    {
        return EvalSuccess::NONE;
    }

    for (const uint8_t& ageTime : allAgeTimes)
    {
        if (potentialAgeTimeSpread & ageTime)
        {
            bool evalTest = EvaluateRequirementWithAgeTime(exit->GetRequirement(), search, ageTime);
            if (evalTest)
            {
                search->areaTime[connectedArea] |= ageTime;
                evalSuccess = EvalSuccess::Partial;
            }
        }
    }
    if (evalSuccess != EvalSuccess::NONE)
    {

        search->successfulExits.insert(exit);

        // Handle finding new agetimes via timePass access
        if (connectedArea->timePasses)
        {
            connectedAreaAgeTime = search->areaTime[connectedArea];
            auto prevRootAgeTime = search->areaTime[GetRootArea()];
            // Spread new ageTimes to the root of the world graph
            ExpandTimePassToD(connectedAreaAgeTime, OOT3D_CHILD_DAY, OOT3D_CHILD_NIGHT, search, exit);
            ExpandTimePassToD(connectedAreaAgeTime, OOT3D_ADULT_DAY, OOT3D_ADULT_NIGHT, search, exit);
            // If we spread any new ones to the root, then spread them to
            // the rest of the world graph areas that have been visited.
            auto curRootAgeTime = search->areaTime[GetRootArea()];
            auto newRootAgeTimes = curRootAgeTime - prevRootAgeTime;
            if (newRootAgeTimes)
            {
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    if (newRootAgeTimes & ageTime)
                    {
                        ExpandToDAreas(search, ageTime);
                    }
                }
            }
        }
        if ((~search->areaTime[connectedArea] & exitsAgeTimes) == 0)
        {
            evalSuccess = EvalSuccess::Complete;
        }
    }
    return evalSuccess;
}

bool Oot3dWorld::EvaluateRequirementWithAgeTime(const Requirement& req, Search* search, uint8_t ageTime)
{
    uint32_t expectedCount = 0;
    Item item;
    AreaID areaId;
    Requirement newReq;
    uint8_t newAgeTime;
    int reqHearts;
    int curHearts;
    bool doubleDefense;
    int multiplier;
    int reqEffectiveHealth;
    int curEffectiveHealth;
    int reqSeconds;
    int curMaxSeconds;
    bool fewerTunicRequirements;
    bool canUseTunic;
    switch(req.type)
    {
        case RequirementType::TRUE:
            return true;

        case RequirementType::FALSE:
            return false;

        case RequirementType::OR:
            return std::any_of(req.args.begin(), req.args.end(), [&](const Requirement::Argument& arg){return EvaluateRequirementWithAgeTime(std::get<Requirement>(arg), search, ageTime);});

        case RequirementType::AND:
            return std::all_of(req.args.begin(), req.args.end(), [&](const Requirement::Argument& arg){return EvaluateRequirementWithAgeTime(std::get<Requirement>(arg), search, ageTime);});

        case RequirementType::NOT:
            return !EvaluateRequirementWithAgeTime(std::get<Requirement>(req.args[0]), search, ageTime);

        case RequirementType::ITEM:
            item = std::get<Item>(req.args[0]);
            return search->ownedItems.count(item) > 0;

        case RequirementType::COUNT:
            expectedCount = std::get<int>(req.args[0]);
            item = std::get<Item>(req.args[1]);
            return search->ownedItems.count(item) >= expectedCount;

        case RequirementType::CHILD_DAY:
            return ageTime & OOT3D_CHILD_DAY;

        case RequirementType::CHILD_NIGHT:
            return ageTime & OOT3D_CHILD_NIGHT;

        case RequirementType::ADULT_DAY:
            return ageTime & OOT3D_ADULT_DAY;

        case RequirementType::ADULT_NIGHT:
            return ageTime & OOT3D_ADULT_NIGHT;

        case RequirementType::AT:
            areaId = std::get<AreaID>(req.args[0]);
            newReq = std::get<Requirement>(req.args[1]);
            newAgeTime = search->areaTime[areas[areaId].get()];
            return EvaluateRequirementWithAgeTime(newReq, search, newAgeTime);

        case RequirementType::HEARTS:
            reqHearts = std::get<int>(req.args[0]);
            curHearts = search->ownedItems.count(Item(ItemID::Oot3dHeartContainer, this)) + (search->ownedItems.count(Item(ItemID::Oot3dPieceOfHeart, this)) >> 2); // Heart Containers + (Pieces of Heart / 4)
            return curHearts >= reqHearts;

        case RequirementType::EFFECTIVE_HEALTH:
            reqEffectiveHealth = std::get<int>(req.args[0]);
            multiplier = std::get<int>(req.args[1]);
            curHearts = search->ownedItems.count(Item(ItemID::Oot3dHeartContainer, this)) + (search->ownedItems.count(Item(ItemID::Oot3dPieceOfHeart, this)) >> 2); // Heart Containers + (Pieces of Heart / 4)
            doubleDefense = search->ownedItems.count(Item(ItemID::Oot3dDoubleDefense, this)) > 0;
            //Number of half heart hits to die, ranges from 1 to 160
            curEffectiveHealth = ((curHearts << (2 + doubleDefense)) >> multiplier) + ((curHearts << (2 + doubleDefense)) % (1 << multiplier) > 0);
            return curEffectiveHealth >= reqEffectiveHealth;

        case RequirementType::FIRE_TIMER:
            [[fallthrough]];
        case RequirementType::WATER_TIMER:
            if (req.type == RequirementType::FIRE_TIMER)
            {
                canUseTunic = ageTime & OOT3D_IS_ADULT && (search->ownedItems.count(Item(ItemID::Oot3dGoronTunic, this)) || search->ownedItems.count(Item(ItemID::Oot3dBuyGoronTunic, this)));
            }
            else
            {
                canUseTunic = ageTime & OOT3D_IS_ADULT && (search->ownedItems.count(Item(ItemID::Oot3dZoraTunic, this)) || search->ownedItems.count(Item(ItemID::Oot3dBuyZoraTunic, this)));
            }
            reqSeconds = std::get<int>(req.args[0]);
            fewerTunicRequirements = std::get<bool>(req.args[1]);
            curHearts = search->ownedItems.count(Item(ItemID::Oot3dHeartContainer, this)) + (search->ownedItems.count(Item(ItemID::Oot3dPieceOfHeart, this)) >> 2);
            curMaxSeconds = canUseTunic ? 255 : (fewerTunicRequirements) ? (curHearts * 8) : 0;
            return curMaxSeconds >= reqSeconds;

        case RequirementType::HAS_STONES:
            expectedCount = std::get<int>(req.args[0]);
            return search->ownedItems.count(Item(ItemID::Oot3dKokiriEmerald, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dGoronRuby, this))     +
                   search->ownedItems.count(Item(ItemID::Oot3dZoraSapphire, this))  >= expectedCount;

        case RequirementType::HAS_MEDALLIONS:
            expectedCount = std::get<int>(req.args[0]);
            return search->ownedItems.count(Item(ItemID::Oot3dForestMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dFireMedallion, this))   +
                   search->ownedItems.count(Item(ItemID::Oot3dWaterMedallion, this))  +
                   search->ownedItems.count(Item(ItemID::Oot3dSpiritMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dShadowMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dLightMedallion, this))  >= expectedCount;

        case RequirementType::HAS_REWARDS:
            expectedCount = std::get<int>(req.args[0]);
            return search->ownedItems.count(Item(ItemID::Oot3dKokiriEmerald, this))   +
                   search->ownedItems.count(Item(ItemID::Oot3dGoronRuby, this))       +
                   search->ownedItems.count(Item(ItemID::Oot3dZoraSapphire, this))    +
                   search->ownedItems.count(Item(ItemID::Oot3dForestMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dFireMedallion, this))   +
                   search->ownedItems.count(Item(ItemID::Oot3dWaterMedallion, this))  +
                   search->ownedItems.count(Item(ItemID::Oot3dSpiritMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dShadowMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dLightMedallion, this))  >= expectedCount;

        default:
            LOG_TO_ERROR("Default case hit when evaluating requirement. Something probably went wrong.");
            LOG_TO_ERROR("Type: " + RequirementToName(req.type) + " Value: " + std::to_string(static_cast<int>(req.type)));
            LOG_TO_ERROR("Requirement: " + std::endl + RequirementStr(req));
            return false;
    }
}
// Expands new ageTime access to the root of the world and pushes any exits which
// failed in the current search iteration to the back of the exitsToTry list to
// be tried again once the new ageTime has been propogated.
void Oot3dWorld::ExpandTimePassToD(uint8_t connectedAreaAgeTime, uint8_t day, uint8_t night, Search* search, Entrance* exit)
{
    if (!(connectedAreaAgeTime & day) != !(connectedAreaAgeTime & night))
    {
        auto connectedArea = exit->GetConnectedArea();
        search->areaTime[connectedArea] |= day | night;
        uint8_t rootAgeTime = search->areaTime[GetRootArea()];
        // If the root doesn't have this time, then spread it to the root
        // and spread time of day to all visited areas.
        if (!(rootAgeTime & day) != !(rootAgeTime & night))
        {
            search->areaTime[GetRootArea()] |= day | night;
            std::unordered_set<Entrance*> pushedBackExits = {};
            // Push exits in exitsToTry back to the end so they get tried again on this iteration
            for (auto exitItr = search->exitsToTry.begin(); exitItr != search->exitsToTry.end(); exitItr++)
            {
                auto exitToTry = *exitItr;
                // We don't need to continue once we've reached the current exit
                if (exit == exitToTry || pushedBackExits.count(exitToTry) > 0)
                {
                    break;
                }
                // Only push back ones from this world if they have agetime requirements
                if (exitToTry->world == this)
                {
                    search->exitsToTry.push_back(exitToTry);
                    pushedBackExits.insert(exitToTry);
                }
            }
        }
    }
}

// Explore the world graph and spread ToD to regions we've already visited if necessary
void Oot3dWorld::ExpandToDAreas(Search* search, uint8_t ageTimeToExpand, const AreaID& startingArea /*= AreaID::Root*/)
{
    std::unordered_set<Area*> searchedAreas = {};
    std::list<Entrance*> exitQueue = {};
    for (auto& exit : areas[startingArea]->exits)
    {
        exitQueue.push_back(exit.get());
    }
    for (auto exit : exitQueue)
    {
        auto connectedArea = exit->GetConnectedArea();
        if (search->visitedAreas.count(connectedArea) > 0 && searchedAreas.count(connectedArea) == 0 && ~search->areaTime[connectedArea] & ageTimeToExpand)
        {
            auto& req = exit->GetRequirement();
            bool evalTest = EvaluateRequirementWithAgeTime(req, search, ageTimeToExpand);
            if (evalTest)
            {
                search->areaTime[connectedArea] |= ageTimeToExpand;
                searchedAreas.insert(connectedArea);
                for (const auto& exitPtr : connectedArea->exits)
                {
                    exitQueue.push_back(exitPtr.get());
                }
            }
        }
    }
}

// Expand agetime specifically when obtaining the Master Sword
void Oot3dWorld::ExpandToDMasterSword(Search* search)
{
    auto worldRoot = GetRootArea();
    auto ageTime = search->areaTime[worldRoot];
    if (!(ageTime & OOT3D_IS_ADULT))
    {
        search->visitedAreas.insert(areas[AreaID::Oot3dAdultSpawn].get());
        if (ageTime & OOT3D_CHILD_DAY) {
            search->areaTime[worldRoot] |= OOT3D_ADULT_DAY;
            ExpandToDAreas(search, OOT3D_ADULT_DAY);
        }
        if (ageTime & OOT3D_CHILD_NIGHT) {
            search->areaTime[worldRoot] |= OOT3D_ADULT_NIGHT;
            ExpandToDAreas(search, OOT3D_ADULT_NIGHT);
        }
    }
    else if (!(ageTime & OOT3D_IS_CHILD))
    {
        search->visitedAreas.insert(areas[AreaID::Oot3dChildSpawn].get());
        if (ageTime & OOT3D_ADULT_DAY) {
            search->areaTime[worldRoot] |= OOT3D_CHILD_DAY;
            ExpandToDAreas(search, OOT3D_CHILD_DAY);
        }
        if (ageTime & OOT3D_ADULT_NIGHT) {
            search->areaTime[worldRoot] |= OOT3D_CHILD_NIGHT;
            ExpandToDAreas(search, OOT3D_CHILD_NIGHT);
        }
    }

}

// Cache the agetime requirements for each exit so that we don't waste time
// evaluating each exit with all agetimes during searches
WorldBuildingError Oot3dWorld::CacheAgeTimeRequirements()
{
    LOG_TO_DEBUG("Caching Age/Time requirements...");
    Search searchWithItems = Search();
    for (uint32_t itemIdint = static_cast<uint32_t>(ItemID::Oot3dKokiriSword); itemIdint < static_cast<uint32_t>(ItemID::Oot3dHint); itemIdint++)
    {
        // Insert 10 of each item to account for small keys
        Item item = Item(static_cast<ItemID>(itemIdint), this);
        searchWithItems.ownedItems.insert({item, item, item, item, item, item, item, item, item, item});
    }
    for (auto& [areaId, areaPtr] : areas)
    {
        searchWithItems.visitedAreas.insert(areaPtr.get());
    }
    searchWithItems.areaTime[areas[AreaID::Root].get()] = OOT3D_ALL_TIMES;
    for (const auto& ageTime : allAgeTimes)
    {
        ExpandToDAreas(&searchWithItems, ageTime);
    }


    for (const auto& [areaId, areaPtr] : areas)
    {
        auto area = areaPtr.get();
        uint8_t areaAgeTimes = searchWithItems.areaTime[area];
        for (const auto& exitPtr : area->exits)
        {

            Entrance* exit = exitPtr.get();
            auto req = exit->GetRequirement();
            possibleExitAgeTimes[exit] = OOT3D_NO_AGE_TIME;
            // First evaluate with items and no agetime to see which exits *require*
            // any specific agetimes
            for (const uint8_t& ageTime : allAgeTimes)
            {
                if (areaAgeTimes & ageTime && EvaluateRequirementWithAgeTime(req, &searchWithItems, ageTime))
                {
                    possibleExitAgeTimes[exit] |= ageTime;
                }
            }
        }
    }
    // Uncomment to log decided allowed age/times (for debugging)
    // for (const auto& [exit, ageTime] : possibleExitAgeTimes)
    // {
    //     LOG_TO_DEBUG("Allowed agetimes for " +  + ": " + );
    // }
    return WorldBuildingError::NONE;
}
