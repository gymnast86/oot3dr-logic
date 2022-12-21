
#include "search.hpp"
#include "oot3d/oot3d_world.hpp"
#include "utility/pool_functions.hpp"
#include "utility/log.hpp"
#include "utility/timing.hpp"

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

void Search::SearchWorlds(int tempWorldToSearch /*= -1*/, bool oneIteration /*= false*/)
{
    int oldWorldToSearch = worldToSearch;
    worldToSearch = tempWorldToSearch;

    // Get all locations which currently have items to test on each iteration
    std::set<LocationAccess*, LocationAccessComparator> itemLocations = {};
    for (auto& world : *worlds)
    {
        for (auto& [id, area] : world->areas)
        {
            for (auto& locAccess : area->locations)
            {
                if (locAccess.location->GetCurrentItem().GetID() != ItemID::NONE && visitedLocations.count(locAccess.location) == 0)
                {
                    itemLocations.insert(&locAccess);
                }
            }
        }
    }

    // Main searching loop
    do
    {
        // Variable to keep track of making logical progress. We want to keep
        // looping as long as we're finding new things on each iteration
        newThingsFound = false;

        // push_back an empty sphere if we're generating the playthrough
        if (searchMode == SearchMode::GeneratePlaythrough)
        {
            playthroughSpheres.push_back({});
            entranceSpheres.push_back({});
        }

        ProcessExits();
        ProcessEvents();
        ProcessLocations(itemLocations);

        sphereNum++;
    }
    while (newThingsFound && !((searchMode == SearchMode::GeneratePlaythrough || searchMode == SearchMode::GameBeatable) && isBeatable));
    worldToSearch = oldWorldToSearch;
}

// Explore the given area, and recursively explore the area's connected to it as
// well if they haven't been visited yet.
void Search::Explore(Area* area)
{
    auto world = area->world;
    for (auto& event : area->events)
    {
        // LOG_TO_DEBUG("\t\tFound Event " + ItemIDToName(event.item));
        eventsToTry.push_back(&event);
    }
    for (auto& exitPtr : area->exits)
    {
        auto exit = exitPtr.get();
        // std::cout << "Found [W" << std::to_string(world->GetWorldID()) << "] exit " << exit->GetOriginalName() << std::endl;
        // If we're generating the playthrough, evaluate the entrance requirement
        // if it's shuffled to potentially add it to the entrance spheres
        // if (searchMode == SearchMode::GeneratePlaythrough && exit->IsShuffled())
        // {
        //     // If entrances are not decoupled we only want to add the first entrance
        //     // of a bound two way entrance to the entrance playthrough for
        //     // spoiler log simplicity
        //     bool reverseInPlaythrough = false;
        //     if (!worlds[exit.getWorldId()].getSettings().decouple_entrances && exit.getReplaces()->getReverse() != nullptr)
        //     {
        //         for (auto& sphere : worlds[0].entranceSpheres)
        //         {
        //             if (std::find(sphere.begin(), sphere.end(), exit.getReplaces()->getReverse()) != sphere.end())
        //             {
        //                 reverseInPlaythrough = true;
        //                 break;
        //             }
        //         }
        //     }
        //
        //     if (!reverseInPlaythrough && world->EvaluateRequirement(exit->GetRequirement(), this, exit, EvaluateType::Exit))
        //     {
        //         entranceSpheres.back().push_back(exit);
        //     }
        // }

        auto connectedArea = exit->GetConnectedArea();

        auto evalSuccess = world->EvaluateExitRequirement(this, exit);
        switch (evalSuccess)
        {
            case EvalSuccess::Partial:
                exitsToTry.push_back(exit);
                [[fallthrough]];
            case EvalSuccess::Complete:
                if (evalSuccess == EvalSuccess::Complete)
                {
                    successfulExits.insert(exit);
                }
                if (visitedAreas.count(connectedArea) == 0)
                {
                    visitedAreas.insert(connectedArea);
                    Explore(connectedArea);
                }
                break;
            case EvalSuccess::Unnecessary:
                break;
            case EvalSuccess::NONE:
                exitsToTry.push_back(exit);
            default:
                break;
        }
    }
}

void Search::ProcessEvents()
{
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
            eventItr++; // Only increment if we don't erase
            continue;
        }
        if (world->EvaluateEventRequirement(this, event) == EvalSuccess::Complete)
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
}

void Search::ProcessExits()
{
    // Search each exit in the exitsToTry list and explore any new areas found as well.
    // For any exits which we try and don't meet the requirements for, put them
    // into exitsToTry for the next iteration.
    for (auto exitItr = exitsToTry.begin(); exitItr != exitsToTry.end(); exitItr++)
    {
        auto exit = *exitItr;
        if (successfulExits.count(exit) > 0 || (worldToSearch != -1 && exit->GetWorld()->GetWorldID() != worldToSearch))
        {
            // Ignore the exit if it we've already completed it, or we're not searching
            // its world at the moment
            continue;
        }

        auto world = exit->GetWorld();
        EvalSuccess evalSuccess = world->EvaluateExitRequirement(this, exit);
        if (evalSuccess == EvalSuccess::Unnecessary) {
            successfulExits.insert(exit);
        }
        else if (evalSuccess == EvalSuccess::Complete || evalSuccess == EvalSuccess::Partial)
        {
            if (evalSuccess == EvalSuccess::Complete)
            {
                successfulExits.insert(exit);
            }

            newThingsFound = true;
            // If we're generating the playthrough, add it to the entranceSpheres if it's randomized
            if (searchMode == SearchMode::GeneratePlaythrough && exit->IsShuffled())
            {
                entranceSpheres.back().push_back(exit);
            }

            // If this exit's connected region has not been explored yet, then explore it
            auto connectedArea = exit->GetConnectedArea();
            if (visitedAreas.count(connectedArea) == 0)
            {
                visitedAreas.insert(connectedArea);
                Explore(connectedArea);
            }
        }
    }

    // if (searchMode == SearchMode::GameBeatable)
    // {
    //     LOG_TO_DEBUG("]");
    // }
}

void Search::ProcessLocation(Location* location)
{
    ownedItems.insert(location->GetCurrentItem());
    // Set appropriate new ageTimes if we found the master sword in oot3d
    if (location->GetCurrentItem().GetID() == ItemID::Oot3dMasterSword && location->GetWorld()->GetType() == WorldType::Oot3d)
    {
        Oot3dWorld* oot3dWorld = (Oot3dWorld*) location->GetWorld();
        oot3dWorld->ExpandToDMasterSword(this);
    }
    if (searchMode == SearchMode::GeneratePlaythrough)
    {
        playthroughSpheres.back().insert(location);
    }
    // If we're generating a playthrough or just checking for beatability then we can
    // stop searching early by checking if we've found all game beating items for each
    // world
    if (searchMode == SearchMode::GeneratePlaythrough || searchMode == SearchMode::GameBeatable)
    {
        // If we've found the item at the final boss for all worlds, then return early
        if (location->GetCurrentItem().GetID() == ItemID::Oot3dTriforce /*or ItemID::Mm3dMajoraBeatable*/)
        {
            if (std::count_if(ownedItems.begin(), ownedItems.end(), [](const Item& item){return item.GetID() == ItemID::Oot3dTriforce /* || ItemID::Mm3dMajoraBeatable*/;}) == (int) worlds->size())
            {
                // If this is the playthrough, then disregard any items found in the current sphere
                // and just put the final boss item there.
                if (searchMode == SearchMode::GeneratePlaythrough)
                {
                    playthroughSpheres.back().clear();
                    playthroughSpheres.back().insert(location);
                }
                isBeatable = true;
            }
        }
    }
}

void Search::ProcessLocations(std::set<LocationAccess*, LocationAccessComparator>& itemLocations)
{

    LocationPool accessibleThisIteration = {};

    for (auto locAccess : itemLocations)
    {
        auto location = locAccess->location;
        auto world = location->GetWorld();
        // if (searchMode == SearchMode::GameBeatable)
        // {
        //    LOG_TO_DEBUG("Evaluating location " + locAccess->location->GetName());
        // }
        if (visitedLocations.count(location) > 0 || visitedAreas.count(locAccess->area) == 0 || (worldToSearch != -1 && world->GetWorldID() != worldToSearch))
        {
            // if (searchMode == SearchMode::GameBeatable)
            // {
            //    LOG_TO_DEBUG("Continued " + std::to_string(visitedLocations.count(location) > 0) + " " + std::to_string(visitedAreas.count(locAccess->area) == 0) + " " + std::to_string((worldToSearch != -1 && world->GetWorldID() != worldToSearch)));
            // }
            continue;
        }

        if (world->EvaluateLocationRequirement(this, locAccess) == EvalSuccess::Complete)
        {
            // if (searchMode == SearchMode::GameBeatable)
            // {
            //    LOG_TO_DEBUG("\t\tSuccess");
            // }
            visitedLocations.insert(location);
            newThingsFound = true;
            if (searchMode == SearchMode::GeneratePlaythrough)
            {
                accessibleThisIteration.push_back(location);
            }
            else
            {
                ProcessLocation(location);
            }
        }
    }

    // If we're generating the playthrough, then process locations after we've
    // found all that are available this iteration
    for (auto location : accessibleThisIteration)
    {
        ProcessLocation(location);
        if (isBeatable)
        {
            return;
        }
    }

}

void Search::RemoveEmptySpheres()
{
    // Get rid of any empty spheres in both the item playthrough and entrance playthrough
    // based only on if the item playthrough has empty spheres. Both the playthroughs
    // will have the same number of spheres, so we only need to conditionally
    // check one of them.
    auto itemItr = playthroughSpheres.begin();
    auto entranceItr = entranceSpheres.begin();
    while (itemItr != playthroughSpheres.end())
    {
        if (itemItr->empty() && entranceItr->empty())
        {
            itemItr = playthroughSpheres.erase(itemItr);
            entranceItr = entranceSpheres.erase(entranceItr);
        }
        else
        {
            itemItr++;     // Only incremement if we don't erase
            entranceItr++;
        }
    }
}

bool GameBeatable(WorldPool& worlds)
{
    auto search = Search(SearchMode::GameBeatable, &worlds);
    search.SearchWorlds();
    return search.isBeatable;
}

void GeneratePlaythrough(WorldPool& worlds)
{
    // Generate initial Playthrough
    auto playthroughSearch = Search(SearchMode::GeneratePlaythrough, &worlds);
    playthroughSearch.SearchWorlds();
    std::list<Search> playthroughSearches = {};

    // Pare down playthrough
    auto& playthroughSpheres = playthroughSearch.playthroughSpheres;
    auto& entranceSpheres = playthroughSearch.entranceSpheres;

    // Keep track of all locations we temporarily take items away from to give them back
    // after the playthrough calculation
    std::unordered_map<Location*, Item> tempEmptyLocations = {};

    for (auto sphereItr = playthroughSpheres.rbegin(); sphereItr != playthroughSpheres.rend(); sphereItr++)
    {
        auto& sphere = *sphereItr;
        for (auto location : sphere)
        {
            // Remove the item at the current location and check if the game is still beatable
            auto itemAtLocation = location->currentItem;
            location->currentItem = Item(ItemID::NONE, worlds[0].get());
            auto search = Search(SearchMode::GameBeatable, &worlds);
            search.SearchWorlds();

            // Check if the game is beatable
            if (search.isBeatable)
            {
                // If the game is still beatable, then this item is not required
                tempEmptyLocations.insert({location, itemAtLocation});
            }
            else
            {
                location->currentItem = itemAtLocation;
            }
        }
    }

    // Now regenerate the playthrough with only the required locations incase
    // some spheres were flattened by non-required locations having progress items
    auto newSearch = Search(SearchMode::GeneratePlaythrough, &worlds);
    newSearch.SearchWorlds();
    newSearch.RemoveEmptySpheres();

    worlds[0]->playthroughSpheres = newSearch.playthroughSpheres;
    worlds[0]->entranceSpheres = newSearch.entranceSpheres;

    // Give items back to empty locations
    for (auto& [location, item] : tempEmptyLocations)
    {
        location->currentItem = item;
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
    std::string fullFilename = LOGS_PATH + filename + ".gv";
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
                itemAtLocation = location->GetCurrentItem().GetName();
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
