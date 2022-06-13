#include "oot3d_world.hpp"
#include "oot3d_entrance.hpp"
#include "../search.hpp"
#include "../debug.hpp"
#include "../timing.hpp"

#include <iostream>
#include <algorithm>

static std::list<uint8_t> allAgeTimes = {OOT3D_CHILD_DAY, OOT3D_CHILD_NIGHT, OOT3D_ADULT_DAY, OOT3D_ADULT_NIGHT};

bool Oot3dWorld::EvaluateRequirement(const RequirementFn& req, Search* search, void* object, EvaluateType evalType /*= EvaluateType::NONE*/)
{
    //DebugLog("EvalulateRequirement");
    const int EXIT_PARTIAL_SUCCESS = 1;
    const int EXIT_COMPLETE_SUCCESS = 2;
    Oot3dArea* parentArea = nullptr;
    Oot3dArea* connectedArea = nullptr;
    Event* event = nullptr;
    LocationAccess* locAccess = nullptr;
    Oot3dEntrance* exit = nullptr;
    uint8_t parentAreaAgeTime = 0;
    uint8_t connectedAreaAgeTime = 0;
    uint8_t exitsAgeTimes = 0;
    uint8_t exitsAgeTimesToTest = 0;
    int exitSuccess = false;

    // Set the current search and world for the logic to refer to
    logic->search = search;
    logic->world = this;
    // Evaluate Events and Locations directly with their ageTime
    switch (evalType)
    {
        case EvaluateType::Event:
            event = (Event*) object;
            logic->area = (Oot3dArea*) event->area;
            logic->ageTime = search->areaTime[logic->area];
            numEvals++;
            //DebugLog("Eval Event " + logic->AgeTimeStr());
            return req();
        case EvaluateType::Location:
            locAccess = (LocationAccess*) object;
            //location = (Oot3dLocation*) locAccess->location;
            logic->area = (Oot3dArea*) locAccess->area;
            logic->ageTime = search->areaTime[logic->area];
            //std::cout << "ageTime at " << location->name << ": " << std::to_string(parentAreaAgeTime) << std::endl;
            numEvals++;
            //DebugLog("Eval " + logic->AgeTimeStr());
            return req();
        case EvaluateType::Exit:
            exit = (Oot3dEntrance*) object;
            parentArea = (Oot3dArea*) exit->GetParentArea();
            connectedArea = (Oot3dArea*) exit->GetConnectedArea();
            parentAreaAgeTime = search->areaTime[parentArea];
            connectedAreaAgeTime = search->areaTime[connectedArea];
            exitsAgeTimes = allowedExitAgeTimes[exit];
            logic->area = (Oot3dArea*) parentArea;
            //std::cout << "Eval [W" << std::to_string(worldId) << "] exit " << exit->GetOriginalName() << std::endl;
            // Handle exits which don't have any age/time requirements
            if (exitsAgeTimes == OOT3D_NO_AGE_TIME)
            {
                logic->ageTime = 0;
                numEvals++;
                //DebugLog("Eval " + exit->GetOriginalName() + " with no age time: " + logic->AgeTimeStr() + " &logic->ageTime.adultNight=" + std::to_string((uint64_t)&logic->ageTime.adultNight));
                if (req())
                {
                    // std::cout << "Spreading ageTime " << std::to_string(ageTime) << " to " << connectedArea->name << std::endl;
                    // If the connected area gets new agetimes
                    if (~connectedAreaAgeTime & parentAreaAgeTime)
                    {
                        search->areaTime[connectedArea] |= parentAreaAgeTime;
                    }
                    // If the parent area does not have all the agetimes that can pass
                    // through this exit, it's only a partial success
                    if (~search->areaTime[connectedArea] & exitsAgeTimes)
                    {
                        exitSuccess = EXIT_PARTIAL_SUCCESS;
                    }
                    else
                    {
                        exitSuccess = EXIT_COMPLETE_SUCCESS;
                    }
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
                        logic->ageTime = ageTime;
                        numEvals++;
                        //DebugLog("Eval Exit With Age Time" + logic->AgeTimeStr());
                        if (req())
                        {
                            search->areaTime[connectedArea] |= ageTime;
                        }
                    }
                }
                // If the connected area does not have all the agetimes
                // provided by the exit, then it's only a partial success
                if (~search->areaTime[connectedArea] & exitsAgeTimes)
                {
                    exitSuccess = EXIT_PARTIAL_SUCCESS;
                }
                else
                {
                    exitSuccess = EXIT_COMPLETE_SUCCESS;
                }
            }
            if (exitSuccess)
            {
                //std::cout << "Passed" << std::endl;
                if (exitSuccess == EXIT_PARTIAL_SUCCESS)
                {
                    // If the exit is only partially successful keep it in exitsTotry
                    // until it's completely successful or it's not needed anymore
                    search->partiallySuccessfulExits.insert(exit);
                    search->exitsToTry.push_front(exit);
                }
                else
                {
                    search->partiallySuccessfulExits.erase(exit);
                    search->successfulExits.insert(exit);
                }

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
    logic->ageTime = ageTimeToExpand;
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
        if (search->visitedAreas.count(connectedArea) > 0 && searchedAreas.count(connectedArea) == 0 && (exitsAgeTimes & ageTimeToExpand || !exitsAgeTimes) && ~search->areaTime[connectedArea] & ageTimeToExpand)
        {
            logic->area = exit->GetParentArea();
            auto& req = exit->GetRequirement();
            numEvals++;

            //DebugLog("Eval " + logic->AgeTimeStr());
            if (req())
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
    DebugLog("ExpandToDMasterSword");
    logic->search = search;
    auto worldRoot = GetRootArea();
    auto area = locAccess->area;
    auto ageTime = search->areaTime[area];
    if (!(ageTime & OOT3D_IS_ADULT))
    {
        search->visitedAreas.insert(areas[AreaID::AdultSpawn].get());
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
        search->visitedAreas.insert(areas[AreaID::ChildSpawn].get());
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
    std::cout << "Caching Age/Time requirements..." << std::endl;
    Search searchWithItems = Search();
    Search searchWithNoItems = Search();
    for (auto& [id, areaPtr] : areas)
    {
        auto area = areaPtr.get();
        searchWithItems.areaTime[area] = OOT3D_ALL_TIMES;
        searchWithNoItems.areaTime[area] = OOT3D_ALL_TIMES;
    }
    for (uint32_t itemIdint = static_cast<uint32_t>(ItemID::KokiriSword); itemIdint < static_cast<uint32_t>(ItemID::Hint); itemIdint++)
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
            auto& req = exit->GetRequirement();
            allowedExitAgeTimes[exit] = 0;
            // First evaluate with items and no agetime to see which exits *require*
            // any specific agetimes
            logic->ageTime = 0;
            logic->area = exit->GetParentArea();
            logic->search = &searchWithItems;
            DebugLog("Eval " + exit->GetOriginalName() + " with no age time: " + logic->AgeTimeStr());
            if (!req())
            {
                DebugLog("Not Passed");
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    logic->ageTime = ageTime;
                    DebugLog("Eval " + exit->GetOriginalName() + " with age time: " + logic->AgeTimeStr());
                    if (req())
                    {
                        DebugLog("Passed");
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
                DebugLog("Passed");
                logic->search = &searchWithNoItems;
                for (const uint8_t& ageTime : allAgeTimes)
                {
                    logic->ageTime = ageTime;
                    DebugLog("Eval " + exit->GetOriginalName() + " with age time but no items: " + logic->AgeTimeStr());
                    if (req())
                    {
                        DebugLog("Passed");
                        // std::cout << Oot3dAgeTimeToString(ageTime) << std::endl;
                        allowedExitAgeTimes[exit] |= OOT3D_ALL_TIMES;
                        break;
                    }
                    else
                    {
                        DebugLog("Failed");
                    }
                }
            }
            DebugLog("Next Exit...");
        }
    }
    // Print out decided allowed age/times (for debugging)
    for (const auto& [exit, ageTime] : allowedExitAgeTimes)
    {
        std::cout << "Allowed agetimes for " << exit->GetOriginalName() << ": " << Oot3dAgeTimeToString(ageTime) << std::endl;
    }
    return WorldBuildingError::NONE;
}

void Oot3dWorld::ExpandAreaVariables()
{

}
