#include "fill.hpp"
#include "random.hpp"
#include "search.hpp"
#include "pool_functions.hpp"

#include <iostream>

#define FILL_ERROR_CHECK(err) if (err != FillError::NONE) {return err;}
#define ENOUGH_SPACE_CHECK(items, locations) if (items.size() > locations.size()) {return FillError::MORE_ITEMS_THAN_LOCATIONS;}

static FillError AssumedFill(WorldPool& worlds, ItemPool& itemsToPlaceVector, const ItemPool& itemsNotYetPlaced, LocationPool& allowedLocations, int worldToFill = -1)
{
    ENOUGH_SPACE_CHECK(itemsToPlaceVector, allowedLocations);

    int retries = 10;
    bool unsuccessfulPlacement = false;
    do
    {
        if (retries <= 0)
        {
            std::cout << "Ran out of assumed fill retries" << std::endl;
            return FillError::RAN_OUT_OF_RETRIES;
        }
        retries--;
        unsuccessfulPlacement = false;
        ShufflePool(itemsToPlaceVector);
        std::list<Item> itemsToPlace;
        itemsToPlace.assign(itemsToPlaceVector.begin(), itemsToPlaceVector.end());
        LocationPool rollbacks;

        std::list<Search> searches = {};
        int oldNum = TotalWorldEvals(worlds);
        auto baseSearch = Search(SearchMode::AccessibleLocations, &worlds, itemsNotYetPlaced, worldToFill);
        baseSearch.FindLocations();
        // baseSearch.DumpSearchGraph();
        // DebugLog("\nAdded item: None");
        // DebugLog("Actual base search iteration: " + std::to_string(TotalWorldEvals(worlds) - oldNum));
        // DebugLog("available Locations: " + std::to_string(baseSearch.visitedLocations.size()));
        // DebugLog("exitsToTry: " + std::to_string(baseSearch.exitsToTry.size()) + " locationsToTry: " + std::to_string(baseSearch.locationsToTry.size()));
        for (const auto& item: itemsToPlace)
        {
            searches.push_back(baseSearch);
            baseSearch.ownedItems.insert(item);
            baseSearch.sphereItems.insert(item);
            int oldNum = TotalWorldEvals(worlds);
            baseSearch.FindLocations(item.GetWorld()->GetWorldID());
            // DebugLog("\nAdded item: " + item.GetName());
            // DebugLog("base search iteration: " + std::to_string(TotalWorldEvals(worlds) - oldNum));
            // DebugLog("available Locations: " + std::to_string(baseSearch.visitedLocations.size()));
            // DebugLog("exitsToTry: " + std::to_string(baseSearch.exitsToTry.size()) + " locationsToTry: " + std::to_string(baseSearch.locationsToTry.size()));
        }

        while (!itemsToPlace.empty())
        {
            // Get a random item to place
            auto item = itemsToPlace.back();
            itemsToPlace.pop_back();
            auto search = searches.back();
            searches.pop_back();

            // Assume we have all the items which haven't been placed yet
            // (except for this one we're about to place)

            // Get the list of accessible locations
            int oldNum = TotalWorldEvals(worlds);
            search.FindLocations();
            DebugLog(std::to_string(TotalWorldEvals(worlds) - oldNum));
            auto accessibleLocations = FilterFromPool(allowedLocations, [search](Location* loc){return search.accessibleLocations.count(loc) > 0 && loc->GetCurrentItem().GetID() == ItemID::NONE;});

            if (accessibleLocations.empty())
            {
                DebugLog("No Accessible Locations to place " + item.GetName() + ". Retrying " + std::to_string(retries) + " more times.");
                for (auto location : rollbacks)
                {
                    itemsToPlace.push_back(location->GetCurrentItem());
                    location->currentItem = Item(ItemID::NONE, worlds[0].get());
                }
                // Also add back the randomly selected item
                itemsToPlace.push_back(item);
                rollbacks.clear();
                // Break out of the item placement loop and flag an unsuccessful
                // placement attempt to try again.
                unsuccessfulPlacement = true;
                break;
            }
            // for (auto loc : accessibleLocations)
            // {
            //     auto message = "[W" + std::to_string(loc->GetWorld()->GetWorldID()) + "] " + loc->TypeString() + " " + loc->GetName();
            //     DebugLog(message);
            // }
            auto location = RandomElement(accessibleLocations);
            location->currentItem = std::move(item);
            rollbacks.push_back(location);
            // If this location is accessible in previous searches, then add it to those searches owned items
            // Search through the searches backwards and when we hit a search where the location isn't accessible
            // we can break out since none of the previous ones will have it either
            for (auto pastSearch = searches.rbegin(); pastSearch != searches.rend(); pastSearch++)
            {
                if (pastSearch->accessibleLocations.count(location) == 0)
                {
                    break;
                }
                pastSearch->ownedItems.insert(item);
                pastSearch->sphereItems.insert(item);
            }
            DebugLog("Placed " + item.GetName() + " at " + location->GetName());
        }
    }
    while (unsuccessfulPlacement);

    // Search newSearch = Search(SearchMode::AccessibleLocations, &worlds, itemsNotYetPlaced, worldToFill);
    // newSearch.FindLocations();
    // newSearch.DumpSearchGraph();

    return FillError::NONE;
}

FillError FillWorlds(WorldPool& worlds)
{
    FillError err;
    ItemPool itemPool;
    LocationPool allLocations;

    // Combine all worlds' item pools and location pools
    for (auto& world : worlds)
    {
        for (auto& [name, location] : world->locations)
        {
            allLocations.push_back(location.get());
        }
        itemPool.insert(itemPool.end(), world->itemPool.begin(), world->itemPool.end());
    }

    // Get Major items
    ItemPool otherItems = {};
    // Get Progression Locations

    err = AssumedFill(worlds, itemPool, otherItems, allLocations);
    FILL_ERROR_CHECK(err);

    return err;
}
