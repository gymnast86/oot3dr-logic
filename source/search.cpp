
#include "search.hpp"
#include "pool_functions.hpp"
#include "file_system_defs.hpp"
#include "debug.hpp"
#include "timing.hpp"
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
    // // DebugLog("Owned items:");
    // for (const auto& item : ownedItems)
    // {
    //     // DebugLog("\t" + item.GetName());
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
    newThingsFound = false;

    // If any previous locations which didn't have anything now do have something
    // then add them back to locationsToTry
    for (auto locItr = locationsToTryAtEnd.begin(); locItr != locationsToTryAtEnd.end(); )
    {
        auto locAccess = *locItr;
        auto location = locAccess->location;

        if (location->currentItem.GetID() != ItemID::NONE && (worldToSearch == -1 || location->world->GetWorldID() == worldToSearch))
        {
            // std::cout << "\t" + location->GetName() + " in world " + std::to_string(location->GetWorld()->GetWorldID()));
            locationsToTry.push_back(locAccess);
            // Delete locations which now have an item
            locItr = locationsToTryAtEnd.erase(locItr);
        }
        else
        {
            locItr++; // Only increment if we don't erase
        }
    }

    // Main searching loop
    do
    {
        // DebugLog("Begin Search Loop");
        // push_back an empty sphere if we're generating the playthrough
        if (searchMode == SearchMode::GeneratePlaythrough)
        {
            playthroughSpheres.push_back({});
            entranceSpheres.push_back({});
        }

        // Variable to keep track of making logical progress. We want to keep
        // looping as long as we're finding new things on each iteration
        newThingsFound = false;

        ProcessExits();
        ProcessEvents();
        ProcessLocations();

        sphere++;
        // DebugLog(std::string("End Search Loop: ") + (newThingsFound ? "continuing" : "not continuing"));
    }
    while (newThingsFound);
    if (searchMode == SearchMode::AccessibleLocations)
    {
        // DebugLog("Processing End Locations");
        for (auto locItr = locationsToTryAtEnd.begin(); locItr != locationsToTryAtEnd.end(); )
        {
            auto locAccess = *locItr;
            auto location = locAccess->location;
            auto world = location->GetWorld();
            // DebugLog("\t\tTesting location " + location->GetName());
            if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
            {
                // DebugLog("\t\t\tNot part of current world");
                locItr++;
                continue;
            }
            if (world->EvaluateLocationRequirement(this, locAccess) == EvalSuccess::Complete)
            {
                // DebugLog("\t\t\tSuccess");
                // std::cout << "\t" + location->GetName() + " in world " + std::to_string(location->GetWorld()->GetWorldID()));
                visitedLocations.insert(location);
                // Delete newly accessible locations from locationsToTryAtEnd
                accessibleLocations.insert(location);
                locItr = locationsToTryAtEnd.erase(locItr);
            }
            else
            {
                // DebugLog("\t\t\tFailure");
                locItr++; // Only increment if we don't erase
            }
        }
        // DebugLog("End Locations Done");
    }
    worldToSearch = oldWorldToSearch;
}

// Explore the given area, and recursively explore the area's connected to it as
// well if they haven't been visited yet.
void Search::Explore(Area* area)
{
    auto world = area->world;
    for (auto& event : area->events)
    {
        // DebugLog("\t\tFound Event " + ItemIDToName(event.item));
        eventsToTry.push_back(&event);
    }
    for (auto& locAccess : area->locations)
    {
        // Add new locations we come across to try them and potentially account
        // for any items on the next iteration.
        // DebugLog("\t\tFound Location " + locAccess.location->GetName());
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
            //
            // if (!reverseInPlaythrough && world->EvaluateRequirement(exit->GetRequirement(), this, exit, EvaluateType::Exit))
            // {
            //     entranceSpheres.back().push_back(exit);
            // }
        }

        auto connectedArea = exit->GetConnectedArea();

        StartTiming("Exit");
        auto evalSuccess = world->EvaluateExitRequirement(this, exit);
        auto timing = GetTiming("Exit");
        DebugLog("\t\tTesting exploration exit " + exit->GetOriginalName() + " " + std::to_string(timing) + " seconds");
        switch (evalSuccess)
        {
            case EvalSuccess::Partial:
                exitsToTry.push_front(exit);
                [[fallthrough]];
            case EvalSuccess::Complete:
                // DebugLog("\t\t\tSuccess");
                if (visitedAreas.count(connectedArea) == 0)
                {
                    // DebugLog("\t\t\tConnected Area is new, exploring");
                    visitedAreas.insert(connectedArea);
                    Explore(connectedArea);
                }
                break;
            case EvalSuccess::Unnecessary:
                // DebugLog("\t\t\tUnnecessary");
                break;
            case EvalSuccess::NONE:
                // DebugLog("\t\t\tFailure");
                exitsToTry.push_front(exit);
            default:
                break;
        }
    }
}

void Search::ProcessEvents()
{
    // Loop through and see if there are any events that we are now accessible.
    // Add them to the ownedItems list if they are.
    // DebugLog("\tProcessing Events");
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
        // DebugLog("\t\tTesting event " + ItemIDToName(event->item) + " in area " + area->name);
        if (world->EvaluateEventRequirement(this, event) == EvalSuccess::Complete)
        {
            // DebugLog("\t\t\tSuccess");
            newThingsFound = true;
            eventItr = eventsToTry.erase(eventItr);
            ownedItems.emplace(event->item, world);
            sphereItems.emplace(event->item, world);
        }
        else
        {
            // DebugLog("\t\t\tFailure");
            eventItr++; // Only increment if we don't erase
        }
    }
    // DebugLog("\tEvents Done");
}

void Search::ProcessExits()
{
    // Search each exit in the exitsToTry list and explore any new areas found as well.
    // For any exits which we try and don't meet the requirements for, put them
    // into exitsToTry for the next iteration. Any locations we come across will
    // be added to locationsToTry.
    // DebugLog("\tProcessing Exits");
    for (auto exitItr = exitsToTry.begin(); exitItr != exitsToTry.end(); )
    {
        auto exit = *exitItr;
        auto world = exit->GetWorld();
        // DebugLog("\t\tTesting exit " + exit->GetOriginalName());
        if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
        {
            // Ignore the exit if it isn't part of the world we're searching
            // DebugLog("\t\t\tNot part of current world");
            exitItr++;
            continue;
        }

        // If the requirement has a set of fulfillment items, then test to see
        // if any of those items were found last iteration. If none of them were
        // then don't test the requirement.
        auto& requirement = exit->GetRequirement();
        if (requirement.fulfillmentItems.size() > 0 && sphereItems.size() > 0 && areaTimeSpread.count(exit->GetParentArea()) == 0)
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
                // DebugLog("\t\t\tNo potential fulfillment items, ignoring");
                exitItr++;
                continue;
            }
        }
        // std::cout << "Now exploring [W" << std::to_string(world->GetWorldID()) << "] exit " << exit->GetOriginalName() << std::endl;

        EvalSuccess evalSuccess = world->EvaluateExitRequirement(this, exit);
        if (evalSuccess == EvalSuccess::Unnecessary) {
            // DebugLog("\t\t\tUnnecessary");
            exitItr = exitsToTry.erase(exitItr);
        }
        else if (evalSuccess == EvalSuccess::Complete || evalSuccess == EvalSuccess::Partial)
        {
            if (evalSuccess == EvalSuccess::Complete)
            {
                // DebugLog("\t\t\tComplete Success");
                exitItr = exitsToTry.erase(exitItr);
            }
            else
            {
                // DebugLog("\t\t\tPartial Success");
                exitItr++;
            }

            newThingsFound = true;
            // If we're generating the playthrough, add it to the entranceSpheres if it's randomized
            if (searchMode == SearchMode::GeneratePlaythrough && exit->IsShuffled())
            {
                entranceSpheres.back().push_back(exit);
            }
            // Erase the exit from the list of exits if we've met its requirement
            // exitItr = exitsToTry.erase(exitItr);
            // If this exit's connected region has not been explored yet, then explore it
            auto connectedArea = exit->GetConnectedArea();
            if (visitedAreas.count(connectedArea) == 0)
            {
                visitedAreas.insert(connectedArea);
                // DebugLog("\t\t\tConnected Area is new, now exploring");
                Explore(connectedArea);
            }
        }
        else
        {
            // DebugLog("\t\t\tFailure");
            exitItr++; // Only increment if we don't erase
        }
    }
    // DebugLog("\tExits Done");
}

void Search::ProcessLocations()
{
    // Note which locations are now accessible on this iteration
    std::list<LocationAccess*> accessibleThisIteration = {};
    // std::cout << "New Locations Accessible:" << std::endl;
    // DebugLog("\tProcessing Locations");
    for (auto locItr = locationsToTry.begin(); locItr != locationsToTry.end(); )
    {
        auto locAccess = *locItr;
        auto location = locAccess->location;
        auto world = location->GetWorld();
        // DebugLog("\t\tTesting location " + location->GetName());
        // Ignore the location if it isn't part of the world we're searching
        if (worldToSearch != -1 && world->GetWorldID() != worldToSearch)
        {
            // DebugLog("\t\t\tNot part of current world");
            locItr++;
            continue;
        }
        // Erase locations which have already been found. Some item locations
        // can be accessed from multiple areas, so this check is necessary
        // in those circumstances
        if (visitedLocations.count(location) > 0)
        {
            // DebugLog("\t\t\tLocation already found");
            locItr = locationsToTry.erase(locItr);
            continue;
        }

        // If this location does not contain an item, then there's no reason to
        // evaluate it now. Evaluate it after the searching loop is over
        if (location->currentItem.GetID() == ItemID::NONE)
        {
            // DebugLog("\t\t\tNo Item at location, evaluating later");
            locationsToTryAtEnd.insert(locAccess);
            locItr = locationsToTry.erase(locItr);
            continue;
        }

        // If the requirement has a set of fulfillment items, then test to see
        // if any of those items were found last iteration. If none of them were
        // then don't test the requirement.
        auto& requirement = locAccess->requirement;
        if (requirement.fulfillmentItems.size() > 0 && sphereItems.size() > 0 && areaTimeSpread.count(locAccess->area) == 0)
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
                // DebugLog("\t\t\tNo fulfillment items");
                locItr++;
                continue;
            }
        }
        if (world->EvaluateLocationRequirement(this, locAccess) == EvalSuccess::Complete)
        {
            // DebugLog("\t\t\tSuccess");
            // std::cout << "\t" + location->GetName() + " in world " + std::to_string(location->GetWorld()->GetWorldID()));
            newThingsFound = true;
            visitedLocations.insert(location);
            // Delete newly accessible locations from locationsToTry
            accessibleThisIteration.push_back(locAccess);
            locItr = locationsToTry.erase(locItr);
        }
        else
        {
            // DebugLog("\t\t\tFailure");
            locItr++; // Only increment if we don't erase
        }
    }

    // Clear the sphere items and spread age times for the next iteration
    sphereItems.clear();
    areaTimeSpread.clear();
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
    // DebugLog("\tLocations Done");
}

LocationPool GetAccessibleLocations(WorldPool& worlds, ItemPool& items, LocationPool& allowedLocations, int worldToSearch /*= -1*/)
{
    int oldNum = worlds[0]->numEvals;
    auto search = Search(SearchMode::AccessibleLocations, &worlds, items, worldToSearch);
    search.FindLocations();
    // DebugLog(std::to_string(worlds[0]->numEvals - oldNum));
    // search.DumpSearchGraph(0, "World0");
    // Filter to only those locations which are allowed
    return FilterFromPool(allowedLocations, [search](Location* loc){return search.accessibleLocations.count(loc) > 0 && loc->GetCurrentItem().GetID() == ItemID::NONE;});
}

bool GameBeatable(WorldPool& worlds)
{
    ItemPool noItemsToPlace = {};
    auto search = Search(SearchMode::AccessibleLocations, &worlds, noItemsToPlace, -1);
    search.FindLocations();
    auto worldsBeatable = std::count_if(search.accessibleLocations.begin(), search.accessibleLocations.end(), [](Location* loc){return loc->currentItem.GetID() == ItemID::Oot3dTriforce /* || ItemID::Mm3dMajoraBeatable*/;});
    return worldsBeatable == (int) worlds.size();
}

void GeneratePlaythrough(WorldPool& worlds)
{
    ItemPool noItemsToPlace = {};
    auto search = Search(SearchMode::GeneratePlaythrough, &worlds, noItemsToPlace, -1);
    search.FindLocations();

    // Pare down playthrough
    auto& playthroughSpheres = search.playthroughSpheres;
    auto& entranceSpheres = search.entranceSpheres;

    // Keep track of all locations we temporarily take items away from to give them back
    // after the playthrough calculation
    std::unordered_map<Location*, Item> nonRequiredLocations = {};

    for (auto sphereItr = playthroughSpheres.rbegin(); sphereItr != playthroughSpheres.rend(); sphereItr++)
    {
        auto& sphere = *sphereItr;
        for (auto loc = sphere.begin(); loc != sphere.end(); )
        {
            // Remove the item at the current location and check if the game is still beatable
            auto location = *loc;
            auto itemAtLocation = location->currentItem;
            location->currentItem = Item(ItemID::NONE, worlds[0].get());
            if (GameBeatable(worlds))
            {
                // If the game is still beatable, then this item is not required
                // and we can erase it from the playthrough
                loc = sphere.erase(loc);
                nonRequiredLocations.insert({location, itemAtLocation});
            }
            else
            {
                location->currentItem = itemAtLocation;
                loc++; // Only increment if we don't erase
            }
        }
    }

    // Now regenerate the playthrough with only the required locations incase
    // some spheres were flattened by non-required locations having progress items
    search = Search(SearchMode::GeneratePlaythrough, &worlds, noItemsToPlace, -1);
    search.FindLocations();

    // Give back nonrequired items
    for (auto& [location, item] : nonRequiredLocations)
    {
        location->currentItem = item;
    }

    int sphere = 0;
    std::cout << "Printing Playthrough..." << std::endl;
    for (auto sphereItr = playthroughSpheres.begin(); sphereItr != playthroughSpheres.end(); sphereItr++)
    {
        // DebugLog("Sphere " + std::to_string(sphere++) + ": ");
        for (auto location : *sphereItr)
        {
            // DebugLog("\t" + location->GetName() + ": " + location->currentItem.GetName());
        }
    }
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

        // Make edge connections defined by events
        for (const auto& event : area->events) {
            color = ownedItems.count(Item(event.item, world)) > 0 ? "\"blue\"" : "\"red\"";
            std::string connectedName = ItemIDToName(event.item);
            if (parentName != "INVALID"){
                worldGraph << "\t\"" << parentName << "\" -> \"" << connectedName << "\"" << "[dir=forward color=" << color << "]" << std::endl;
            }
        }

        // Make edge connections defined by exits
        for (const auto& exitPtr : area->exits) {

            auto exit = exitPtr.get();
            // Only dump shuffled exits if set
            if (!exit->IsShuffled() && onlyRandomizedExits)
            {
                continue;
            }
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
