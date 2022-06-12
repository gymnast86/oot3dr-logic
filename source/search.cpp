
#include "search.hpp"
#include "pool_functions.hpp"
#include "file_system_defs.hpp"
#include "debug.hpp"
#include "oot3d/oot3d_world.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

Search::Search()
{

}

Search::Search(const SearchMode& searchMode_, WorldPool* worlds_, const ItemPool& items, const int worldToSearch_ /*= -1*/)
{
    searchMode = searchMode_;
    worlds = worlds_;
    worldToSearch = worldToSearch_;

    // Add starting inventory items to the pool of items
    for (auto& world : *worlds)
    {
        if (worldToSearch == -1 || worldToSearch == world->GetWorldID())
        {
            // AddElementsToPool(items, world->GetStartingItems())
        }
    }

    ownedItems = ItemMultiSet(items.begin(), items.end());
    // DebugLog("Owned items:");
    // for (const auto& item : ownedItems)
    // {
    //     DebugLog("\t" + item.GetName());
    // }
    for (auto& world : *worlds)
    {
        if (worldToSearch == -1 || worldToSearch == world->GetWorldID())
        {
            visitedAreas.insert(world->GetRootArea());
            SetStartingProperties(world.get());
            for (auto& exit : world->GetRootArea()->exits)
            {
                exitsToTry.push_back(exit.get());
            }
            for (auto& locAccess : world->GetRootArea()->locations)
            {
                locationsToTry.push_back(&locAccess);
            }
        }
    }
}

Search::~Search()
{

}

// Begin the starting phase of propogating world specific area properties
//
// Oot3d: Propogate age and time of day combinations
void Search::SetStartingProperties(World* world)
{
    // Start day/night propogation for oot3d worlds
    if (world->GetType() == WorldType::Oot3d)
    {
        auto root = world->GetRootArea();
        if (world->settings["starting_age"] == "child")
        {
            if (world->settings["had_night_start"] == "Off")
            {
                areaTime[root] = OOT3D_CHILD_DAY;
            }
            else
            {
                areaTime[root] = OOT3D_CHILD_NIGHT;
            }
        }
        else
        {
            if (world->settings["had_night_start"] == "Off")
            {
                areaTime[root] = OOT3D_ADULT_DAY;
            }
            else
            {
                areaTime[root] = OOT3D_ADULT_NIGHT;
            }
        }
    }
}

void Search::FindLocations(int tempWorldToSearch /*= -1*/)
{
    int oldWorldToSearch = worldToSearch;
    worldToSearch = tempWorldToSearch;
    bool newThingsFound = false;

    do
    {
        // push_back an empty sphere if we're generating the playthrough
        if (searchMode == SearchMode::GeneratePlaythrough)
        {
            playthroughSpheres.push_back({});
            entranceSpheres.push_back({});
        }

        // Variable to keep track of making logical progress. We want to keep
        // looping as long as we're finding new things on each iteration
        newThingsFound = false;
        // Loop through and see if there are any events that we are now accessible.
        // Add them to the ownedItems list if they are.
        for (auto eventItr = eventsToTry.begin(); eventItr != eventsToTry.end(); )
        {
            auto event = *eventItr;
            auto area = event->area;
            auto world = area->world;
            // Ignore the event if it isn't part of the world we're searching
            if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
            {
                eventItr++;
                continue;
            }
            auto& requirement = event->requirement;
            if (world->EvaluateRequirement(requirement, this, event, EvaluateType::Event))
            {
                newThingsFound = true;
                eventItr = eventsToTry.erase(eventItr);
                ownedItems.emplace(event->item, world);
                sphereItems.emplace(event->item, world);
            }
            else
            {
                eventItr++; // Only increment if we don't erase
            }
        }

        // Search each exit in the exitsToTry list and explore any new areas found as well.
        // For any exits which we try and don't meet the requirements for, put them
        // into exitsToTry for the next iteration. Any locations we come across will
        // be added to locationsToTry.
        for (auto exitItr = exitsToTry.begin(); exitItr != exitsToTry.end(); )
        {
            auto exit = *exitItr;
            auto world = exit->GetWorld();
            if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
            {
                // Ignore the exit if it isn't part of the world we're searching
                exitItr++;
                continue;
            }
            auto& requirement = exit->GetRequirement();

            // If the requirement has a set of fulfillment items, then test to see
            // if any of those items were found last iteration. If none of them were
            // then don't test the requirement.
            if (requirement.fulfillmentItems.size() > 0 && !ageTimeSpread[world])
            {
                bool potentialfulfillment = false;
                for (const auto& item : sphereItems)
                {
                    if (requirement.fulfillmentItems.count(item) > 0)
                    {
                        potentialfulfillment = true;
                        break;
                    }
                }
                if (!potentialfulfillment)
                {
                    exitItr++;
                    continue;
                }
            }
            // std::cout << "Now exploring [W" << std::to_string(world->GetWorldID()) << "] exit " << exit->GetOriginalName() << std::endl;
            if (world->EvaluateRequirement(requirement, this, exit, EvaluateType::Exit)) {
                // If we're generating the playthrough, add it to the entranceSpheres if it's randomized
                if (searchMode == SearchMode::GeneratePlaythrough && exit->IsShuffled())
                {
                    entranceSpheres.back().push_back(exit);
                }
                // Erase the exit from the list of exits if we've met its requirement
                exitItr = exitsToTry.erase(exitItr);
                // If this exit's connected region has not been explored yet, then explore it
                auto connectedArea = exit->GetConnectedArea();
                if (visitedAreas.count(connectedArea) == 0)
                {
                    newThingsFound = true;
                    visitedAreas.insert(connectedArea);
                    Explore(connectedArea);
                }
            }
            else
            {
                exitItr++; // Only increment if we don't erase
            }
        }

        // Note which locations are now accessible on this iteration
        std::list<LocationAccess*> accessibleThisIteration = {};
        // std::cout << "New Locations Accessible:" << std::endl;
        for (auto locItr = locationsToTry.begin(); locItr != locationsToTry.end(); )
        {
            auto locAccess = *locItr;
            auto location = locAccess->location;
            auto world = location->GetWorld();
            // Ignore the location if it isn't part of the world we're searching
            if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
            {
                locItr++;
                continue;
            }
            // Erase locations which have already been found. Some item locations
            // can be accessed from multiple areas, so this check is necessary
            // in those circumstances
            if (visitedLocations.count(location) > 0)
            {
                locItr = locationsToTry.erase(locItr);
                continue;
            }

            auto& requirement = locAccess->requirement;
            // If the requirement has a set of fulfillment items, then test to see
            // if any of those items were found last iteration. If none of them were
            // then don't test the requirement.
            //
            // NOTE: This is a good idea, but needs to properly account for
            // agetimes as well. May go back to implement later
            if (requirement.fulfillmentItems.size() > 0 && sphereItems.size() > 0 && !ageTimeSpread[world])
            {
                bool potentialfulfillment = false;
                for (const auto& item : sphereItems)
                {
                    if (requirement.fulfillmentItems.count(item) > 0)
                    {
                        potentialfulfillment = true;
                        break;
                    }
                }
                if (!potentialfulfillment)
                {
                    locItr++;
                    continue;
                }
            }
            if (world->EvaluateRequirement(requirement, this, locAccess, EvaluateType::Location))
            {
                // std::cout << "\t" + location->GetName() + " in world " + std::to_string(location->GetWorld()->GetWorldID()));
                newThingsFound = true;
                visitedLocations.insert(location);
                // Delete newly accessible locations from locationsToTry
                accessibleThisIteration.push_back(locAccess);
                locItr = locationsToTry.erase(locItr);
            }
            else
            {
                locItr++; // Only increment if we don't erase
            }
        }

        // Clear the sphere items and spread age times for the next iteration
        sphereItems.clear();
        ageTimeSpread.clear();
        // Now apply any effects of newly accessible locations for the next iteration.
        // This lets us properly keep track of spheres for playthrough generation
        for (auto locAccess : accessibleThisIteration)
        {
            auto location = locAccess->location;
            accessibleLocations.insert(location);
            Item currentItem = location->GetCurrentItem();
            if (currentItem.GetID() != ItemID::NONE)
            {
                ownedItems.insert(currentItem);
                sphereItems.insert(currentItem);
                if (searchMode == SearchMode::GeneratePlaythrough /*&& location has major item*/)
                {
                    playthroughSpheres.back().push_back(location);
                }
                // If we found the Master Sword for an Oot3D world, handle the new agetime
                if (currentItem.GetID() == ItemID::Oot3dMasterSword && currentItem.GetWorld()->GetType() == WorldType::Oot3d)
                {
                    auto world = currentItem.GetWorld();
                    Oot3dWorld* oot3dWorld = (Oot3dWorld*) world;
                    oot3dWorld->ExpandToDMasterSword(this, locAccess);
                }
            }
        }
        sphere++;
    }
    while (newThingsFound);
    worldToSearch = oldWorldToSearch;
}

// Explore the given area, and recursively explore the area's connected to it as
// well if they haven't been visited yet.
void Search::Explore(Area* area)
{
    auto world = area->world;
    for (auto& event : area->events)
    {
        eventsToTry.push_back(&event);
    }
    for (auto& locAccess : area->locations)
    {
        // Add new locations we come across to try them and potentially account
        // for any items on the next iteration
        locationsToTry.push_back(&locAccess);
    }
    for (auto& exitPtr : area->exits)
    {
        auto exit = exitPtr.get();
        // std::cout << "Found [W" << std::to_string(world->GetWorldID()) << "] exit " << exit->GetOriginalName() << std::endl;
        // If we're generating the playthrough, evaluate the entrance requirement
        // if it's shuffled to potentially add it to the entrance spheres
        if (searchMode == SearchMode::GeneratePlaythrough && exit->IsShuffled())
        {
            // If entrances are not decoupled we only want to add the first entrance
            // of a bound two way entrance to the entrance playthrough for
            // spoiler log simplicity
            bool reverseInPlaythrough = false;
            // if (!worlds[exit.getWorldId()].getSettings().decouple_entrances && exit.getReplaces()->getReverse() != nullptr)
            // {
            //     for (auto& sphere : worlds[0].entranceSpheres)
            //     {
            //         if (std::find(sphere.begin(), sphere.end(), exit.getReplaces()->getReverse()) != sphere.end())
            //         {
            //             reverseInPlaythrough = true;
            //             break;
            //         }
            //     }
            // }

            if (!reverseInPlaythrough && world->EvaluateRequirement(exit->GetRequirement(), this, exit, EvaluateType::Exit))
            {
                entranceSpheres.back().push_back(exit);
            }
        }

        auto connectedArea = exit->GetConnectedArea();
        // If the connected area is already reachable, then the current exit
        // is ignored since it won't matter for logical access (but might
        // check for day/night later, depending on the game)
        if (visitedAreas.count(connectedArea) == 0)
        {
            if (world->EvaluateRequirement(exit->GetRequirement(), this, exit, EvaluateType::Exit))
            {
                visitedAreas.insert(connectedArea);
                Explore(connectedArea);
            }
            else
            {
                // Push failed exits to the front so the searching loop doesn't
                // consider them until the next sphere of iteration
                exitsToTry.push_front(exit);
            }
        }
    }
}

LocationPool GetAccessibleLocations(WorldPool& worlds, ItemPool& items, LocationPool& allowedLocations, int worldToSearch /*= -1*/)
{
    int oldNum = worlds[0]->numEvals;
    auto search = Search(SearchMode::AccessibleLocations, &worlds, items, worldToSearch);
    search.FindLocations();
    DebugLog(std::to_string(worlds[0]->numEvals - oldNum));
    // search.DumpSearchGraph(0, "World0");
    // Filter to only those locations which are allowed
    return FilterFromPool(allowedLocations, [search](Location* loc){return search.accessibleLocations.count(loc) > 0 && loc->GetCurrentItem().GetID() == ItemID::NONE;});
}

// Will dump a file which can be turned into a visual graph using graphviz
// https://graphviz.org/download/
// Use this command to generate the graph: dot -Tsvg <filename> -o world.svg
// Then, open world.svg in a browser and CTRL + F to find the area of interest
void Search::DumpSearchGraph(size_t worldId /*= 0*/, const std::string filename /*= "World0"*/)
{

    std::cout << "Now dumping search graph" << std::endl;
    bool onlyRandomizedExits = false;
    std::ofstream worldGraph;
    std::string fullFilename = WORLD_GRAPHS"/" + filename + ".gv";
    worldGraph.open (fullFilename);
    worldGraph << "digraph {\n\tcenter=true;\n";

    auto world = worlds->at(worldId).get();
    for (const auto& [areaId, areaPtr] : world->areas) {

        auto area = areaPtr.get();
        std::string color = visitedAreas.count(area) > 0 ? "\"black\"" : "\"red\"";

        std::string parentName = AreaIDToName(area->id);
        std::string timeOfDayStr = "";
        if (world->GetType() == WorldType::Oot3d)
        {
            timeOfDayStr = ":<br/>";
            auto tod = areaTime[area];
            if (tod & OOT3D_CHILD_DAY)   timeOfDayStr += " CD";
            if (tod & OOT3D_CHILD_NIGHT) timeOfDayStr += " CN";
            if (tod & OOT3D_ADULT_DAY)   timeOfDayStr += " AD";
            if (tod & OOT3D_ADULT_NIGHT) timeOfDayStr += " AN";
        }

        worldGraph << "\t\"" << parentName << "\"[label=<" << parentName << timeOfDayStr << "> shape=\"plain\" fontcolor=" << color << "];" << std::endl;
        // Make edge connections defined by exits
        for (const auto& exitPtr : area->exits) {

            auto exit = exitPtr.get();
            // Only dump shuffled exits if set
            if (!exit->IsShuffled() && onlyRandomizedExits)
            {
                continue;
            }
            // Evaluate the exit requirement one more time to ensure if it really isn't accessible
            world->EvaluateRequirement(exit->GetRequirement(), this, exit, EvaluateType::Exit);
            std::string connectedName = AreaIDToName(exit->GetConnectedAreaID());
            if (parentName != "INVALID" && connectedName != "INVALID"){
                color = successfulExits.count(exit) > 0 ? "\"black\"" : "\"red\"";
                worldGraph << "\t\"" << parentName << "\" -> \"" << connectedName << "\"" << "[dir=forward color=" << color << "]" << std::endl;
            }
        }

        // Make edge connections between areas and their locations
        for (const auto& [location, req, locArea] : area->locations) {
            std::string connectedLocation = location->GetName();
            std::string itemAtLocation = "No Item";
            if (location->GetCurrentItem().GetID() != ItemID::NONE)
            {
                itemAtLocation = location->GetCurrentItem().GetName() + " [W" + std::to_string(location->GetCurrentItem().GetWorldID() + 1) + "]";
            }
            color = visitedLocations.count(location) > 0 ? "\"black\"" : "\"red\"";
            if (parentName != "INVALID" && connectedLocation != "INVALID"){
                worldGraph << "\t\"" << connectedLocation << "\"[label=<" << connectedLocation << ":<br/>" << itemAtLocation << "> shape=\"plain\" fontcolor=" << color << "];" << std::endl;
                worldGraph << "\t\"" << parentName << "\" -> \"" << connectedLocation << "\"" << "[dir=forward color=" << color << "]" << std::endl;
            }
        }
    }

    worldGraph << "}";
    worldGraph.close();
    std::cout << "Dumped world graph at " << fullFilename << std::endl;
}
