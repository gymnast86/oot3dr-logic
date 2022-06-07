#include "oot3d_world.hpp"
#include "oot3d_entrance.hpp"
#include "../search.hpp"
#include "../debug.hpp"

#include <iostream>
#include <algorithm>

static std::list<uint8_t> allAgeTimes = {OOT3D_CHILD_DAY, OOT3D_CHILD_NIGHT, OOT3D_ADULT_DAY, OOT3D_ADULT_NIGHT};

bool Oot3dWorld::EvaluateRequirement(const Requirement& req, Search* search, void* object, EvaluateType evalType /*= EvaluateType::NONE*/)
{
    Oot3dArea* parentArea = nullptr;
    Oot3dArea* connectedArea = nullptr;
    Event* event = nullptr;
    LocationAccess* locAccess = nullptr;
    //Oot3dLocation* location = nullptr;
    Oot3dEntrance* exit = nullptr;
    uint8_t parentAreaAgeTime = 0;
    uint8_t connectedAreaAgeTime = 0;
    uint8_t exitsAgeTimes = 0;
    bool exitSuccess = false;
    // Evaluate Events and Locations directly with their ageTime
    switch (evalType)
    {
        case EvaluateType::Event:
            event = (Event*) object;
            parentArea = (Oot3dArea*) event->area;
            parentAreaAgeTime = search->areaTime[parentArea];
            return EvaluateRequirementWithAgeTime(req, search, object, evalType, parentAreaAgeTime);
        case EvaluateType::Location:
            locAccess = (LocationAccess*) object;
            //location = (Oot3dLocation*) locAccess->location;
            parentArea = (Oot3dArea*) locAccess->area;
            parentAreaAgeTime = search->areaTime[parentArea];
            //std::cout << "ageTime at " << location->name << ": " << std::to_string(parentAreaAgeTime) << std::endl;
            return EvaluateRequirementWithAgeTime(req, search, object, evalType, parentAreaAgeTime);
        case EvaluateType::Exit:
            exit = (Oot3dEntrance*) object;
            parentArea = (Oot3dArea*) exit->GetParentArea();
            connectedArea = (Oot3dArea*) exit->GetConnectedArea();
            parentAreaAgeTime = search->areaTime[parentArea];
            exitsAgeTimes = allowedExitAgeTimes[exit];
            //std::cout << "Eval [W" << std::to_string(worldId) << "] exit " << exit->GetOriginalName() << std::endl;
            // Handle exits which don't have any age/time requirements
            if (exitsAgeTimes == OOT3D_NO_AGE_TIME)
            {
                if (EvaluateRequirementWithAgeTime(req, search, object, evalType, OOT3D_NO_AGE_TIME))
                {
                    // std::cout << "Spreading ageTime " << std::to_string(ageTime) << " to " << connectedArea->name << std::endl;
                    search->areaTime[connectedArea] |= parentAreaAgeTime;
                    exitSuccess = true;
                }
                else
                {
                    return false;
                }
            }
            // If the exit requires specific agetimes, then test the ones that can work
            else
            {
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    if (exitsAgeTimes & ageTime && parentAreaAgeTime & ageTime)
                    {
                        if (EvaluateRequirementWithAgeTime(req, search, object, evalType, ageTime))
                        {
                            exitSuccess = true;
                            search->areaTime[connectedArea] |= ageTime;
                        }
                    }
                }
            }
            if (exitSuccess)
            {
                //std::cout << "Passed" << std::endl;
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
                        DebugLog("newRootAgeTimes: " + Oot3dAgeTimeToString(newRootAgeTimes));
                        for (const uint8_t& ageTime : allAgeTimes)
                        {
                            if (newRootAgeTimes & ageTime)
                            {
                                ExpandToDAreas(search, ageTime);
                            }
                        }
                    }
                }
            }
            return exitSuccess;
        default:
            std::cout << "default EvaluateType hit. A dev forgot to specify it somewhere." << std::endl;
            return false;
    }
}

bool Oot3dWorld::EvaluateRequirementWithAgeTime(const Requirement& req, Search* search, void* object, EvaluateType evalType, uint8_t ageTime)
{
    numEvals++;
    uint32_t expectedCount = 0;
    ItemID itemId;
    Item item;
    AreaID areaId;
    Requirement newReq;
    uint8_t newAgeTime;
    switch(req.type)
    {
        case RequirementType::TRUE:
            return true;
        case RequirementType::FALSE:
            return false;
        case RequirementType::OR:
            return std::any_of(req.args.begin(), req.args.end(), [&](const Requirement::Argument& arg){return EvaluateRequirementWithAgeTime(std::get<Requirement>(arg), search, object, evalType, ageTime);});
        case RequirementType::AND:
            return std::all_of(req.args.begin(), req.args.end(), [&](const Requirement::Argument& arg){return EvaluateRequirementWithAgeTime(std::get<Requirement>(arg), search, object, evalType, ageTime);});
        case RequirementType::NOT:
            return !EvaluateRequirementWithAgeTime(std::get<Requirement>(req.args[0]), search, object, evalType, ageTime);
        case RequirementType::ITEM:
            itemId = std::get<ItemID>(req.args[0]);
            item = Item(itemId, this);
            return search->ownedItems.count(item) > 0;
        case RequirementType::COUNT:
            expectedCount = std::get<int>(req.args[0]);
            itemId = std::get<ItemID>(req.args[1]);
            item = Item(itemId, this);
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
            return EvaluateRequirementWithAgeTime(newReq, search, object, evalType, newAgeTime);
        case RequirementType::HAS_STONES:
            expectedCount = std::get<int>(req.args[0]);
            return search->ownedItems.count(Item(ItemID::Oot3dKokiriEmerald, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dGoronRuby, this))     +
                   search->ownedItems.count(Item(ItemID::Oot3dZoraSapphire, this))  > expectedCount;
        case RequirementType::HAS_MEDALLIONS:
            expectedCount = std::get<int>(req.args[0]);
            return search->ownedItems.count(Item(ItemID::Oot3dForestMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dFireMedallion, this))   +
                   search->ownedItems.count(Item(ItemID::Oot3dWaterMedallion, this))  +
                   search->ownedItems.count(Item(ItemID::Oot3dSpiritMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dShadowMedallion, this)) +
                   search->ownedItems.count(Item(ItemID::Oot3dLightMedallion, this))  > expectedCount;
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
                   search->ownedItems.count(Item(ItemID::Oot3dLightMedallion, this))  > expectedCount;
        default:
            std::cout << "Default hit when evaluating requirement. Something probably went wrong." << std::endl;
            std::cout << "Type: " << RequirementToName(req.type) << std::endl;
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
            for (auto exitItr = search->exitsToTry.begin(); exitItr != search->exitsToTry.end(); )
            {
                auto exitToTry = *exitItr;
                // We don't need to continue once we've reached the current exit
                if (exit == exitToTry || pushedBackExits.count(exitToTry) > 0)
                {
                    break;
                }
                // Only push back ones from this world if they have agetime requirements
                if (exitToTry->world == this && allowedExitAgeTimes[exitToTry] != OOT3D_NO_AGE_TIME)
                {
                    exitItr = search->exitsToTry.erase(exitItr);
                    search->exitsToTry.push_back(exitToTry);
                    pushedBackExits.insert(exitToTry);
                }
                // Only iterate if we aren't erasing
                else
                {
                    exitItr++;
                }
            }
        }
    }
}

// Explore the world graph and spread ToD to regions we've already visited
void Oot3dWorld::ExpandToDAreas(Search* search, uint8_t ageTimeToExpand)
{
    DebugLog("Expanding " + Oot3dAgeTimeToString(ageTimeToExpand));
    std::unordered_set<Area*> searchedAreas = {};
    std::list<Entrance*> exitQueue = {};
    for (auto& exit : GetRootArea()->exits)
    {
        exitQueue.push_back(exit.get());
    }
    for (auto exit : exitQueue)
    {

        auto connectedArea = exit->GetConnectedArea();
        uint8_t exitsAgeTimes = allowedExitAgeTimes[exit];
        if (search->visitedAreas.count(connectedArea) > 0 && searchedAreas.count(connectedArea) == 0 && (exitsAgeTimes & ageTimeToExpand || !exitsAgeTimes) && !(search->areaTime[connectedArea] & ageTimeToExpand))
        {
            auto& req = exit->GetRequirement();
            if (EvaluateRequirementWithAgeTime(req, search, exit, EvaluateType::Exit, ageTimeToExpand))
            {
                // std::cout << "Spreading ageTime " << std::to_string(ageTime) << " to " << connectedArea->name << std::endl;
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
void Oot3dWorld::ExpandToDMasterSword(Search* search, LocationAccess* locAccess)
{
    auto worldRoot = GetRootArea();
    auto area = locAccess->area;
    auto ageTime = search->areaTime[area];
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

WorldBuildingError Oot3dWorld::CacheAgeTimeRequirements()
{
    DebugLog("Caching Age/Time requirements...");
    Search searchWithItems = Search();
    Search searchWithNoItems = Search();
    for (uint32_t itemIdint = static_cast<uint32_t>(ItemID::Oot3dKokiriSword); itemIdint < static_cast<uint32_t>(ItemID::Oot3dHint); itemIdint++)
    {
        // Insert 10 of each item to account for small keys
        Item item = Item(static_cast<ItemID>(itemIdint), this);
        searchWithItems.ownedItems.insert({item, item, item, item, item, item, item, item, item, item});
    }
    for (const auto& [areaId, areaPtr] : areas)
    {
        auto area = areaPtr.get();
        for (const auto& exitPtr : area->exits)
        {
            Entrance* exit = exitPtr.get();
            auto req = exit->GetRequirement();
            allowedExitAgeTimes[exit] = 0;
            // First evaluate with items and no agetime to see which exits *require*
            // any specific agetimes
            if (!EvaluateRequirementWithAgeTime(req, &searchWithItems, exit, EvaluateType::Exit, OOT3D_NO_AGE_TIME))
            {
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    if (EvaluateRequirementWithAgeTime(req, &searchWithItems, exit, EvaluateType::Exit, ageTime))
                    {
                        // std::cout << Oot3dAgeTimeToString(ageTime) << std::endl;
                        allowedExitAgeTimes[exit] |= ageTime;
                    }
                }
            }
            // If the exit doesn't require any specific agetime with items, then see if
            // it requires any *without* items. If an agetime alone can satisfy
            // the requirement, but it also can be satisfied with items, it allows
            // all agetimes through, but each one has to be tested individually still
            // since it'll be different depending on what items are owned
            else
            {
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    if (EvaluateRequirementWithAgeTime(req, &searchWithNoItems, exit, EvaluateType::Exit, ageTime))
                    {
                        // std::cout << Oot3dAgeTimeToString(ageTime) << std::endl;
                        allowedExitAgeTimes[exit] |= OOT3D_ALL_TIMES;
                        break;
                    }
                }
            }
        }
    }
    // Print out decided allowed age/times (for debugging)
    // for (const auto& [exit, ageTime] : allowedExitAgeTimes)
    // {
    //     std::cout << "Allowed agetimes for " << exit->GetOriginalName() << ": " << Oot3dAgeTimeToString(ageTime) << std::endl;
    // }
    return WorldBuildingError::NONE;
}

void Oot3dWorld::ExpandAreaVariables()
{

}
