#include "fill.hpp"
#include "random.hpp"
#include "search.hpp"
#include "timing.hpp"
#include "pool_functions.hpp"

#include <iostream>

#define FILL_ERROR_CHECK(func) err = func; if (err != FillError::NONE) {return err;}
#define ENOUGH_SPACE_CHECK(items, locations) if (items.size() > locations.size()) {return FillError::MORE_ITEMS_THAN_LOCATIONS;}

static FillError AssumedFill(WorldPool& worlds, ItemPool& itemsToPlaceVector, const ItemPool& itemsNotYetPlaced, LocationPool& allowedLocations, int worldToFill = -1)
{
    ENOUGH_SPACE_CHECK(itemsToPlaceVector, allowedLocations);

    LocationSet locationSet = LocationSet(allowedLocations.begin(), allowedLocations.end());
    std::vector<LocationAccess*> validLocations = {};
    for (auto& world : worlds)
    {
        for (auto& [id, area] : world->areas)
        {
            for (auto& locAccess : area->locations)
            {
                if (locationSet.count(locAccess.location) > 0 && locAccess.location->GetCurrentItem().GetID() == ItemID::NONE)
                {
                    validLocations.push_back(&locAccess);
                }
            }
        }
    }

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

        // Create a list of searches
        // This optimization is too memory intensive for the 3DS and typically
        // causes it to crash.
        #ifdef NON_3DS
        std::list<Search> searches = {};
        auto baseSearch = Search(SearchMode::AccessibleLocations, &worlds, itemsNotYetPlaced, worldToFill);
        baseSearch.SearchWorlds();

        for (const auto& item: itemsToPlace)
        {
            searches.push_back(baseSearch);
            baseSearch.ownedItems.insert(item);
            baseSearch.SearchWorlds(item.GetWorld()->GetWorldID());
        }
        #endif

        while (!itemsToPlace.empty())
        {
            // Get a random item to place
            auto& item = itemsToPlace.back();
            #ifdef NON_3DS
            auto& search = searches.back();
            #endif

            ShufflePool(validLocations);

            // Assume we have all the items which haven't been placed yet
            // (except for this one we're about to place)

            // Get the list of accessible locations
            #ifndef NON_3DS
            auto search = Search(SearchMode::AccessibleLocations, &worlds, itemsNotYetPlaced, worldToFill);
            #endif
            search.SearchWorlds();
            Location* spotToFill = nullptr;

            for (auto locAccess : validLocations)
            {
                if (locAccess->location->GetCurrentItem().GetID() != ItemID::NONE || search.visitedAreas.count(locAccess->area) == 0)
                {
                    continue;
                }
                if (locAccess->location->GetWorld()->EvaluateLocationRequirement(&search, locAccess) == EvalSuccess::Complete)
                {
                    spotToFill = locAccess->location;
                    break;
                }
            }

            if (spotToFill == nullptr)
            {
                LOG_TO_DEBUG("No Accessible Locations to place " + item.GetName() + ". Retrying " + std::to_string(retries) + " more times.");
                for (auto location : rollbacks)
                {
                    itemsToPlace.push_back(location->GetCurrentItem());
                    location->currentItem = Item(ItemID::NONE, worlds[0].get());
                }
                // Also add back the randomly selected item
                rollbacks.clear();
                // Break out of the item placement loop and flag an unsuccessful
                // placement attempt to try again.
                unsuccessfulPlacement = true;
                break;
            }

            spotToFill->currentItem = std::move(item);
            rollbacks.push_back(spotToFill);
            // If this location is accessible in previous searches, then add it to those searches owned items
            // Search through the searches backwards and when we hit a search where the location isn't accessible
            // we can break out since none of the previous ones will have it either
            #ifdef NON_3DS
            for (auto pastSearch = searches.rbegin(); pastSearch != searches.rend(); pastSearch++)
            {
                if (pastSearch->visitedLocations.count(spotToFill) == 0)
                {
                    break;
                }
                pastSearch->ownedItems.insert(item);
                pastSearch->sphereItems.insert(item);
            }
            #endif
            LOG_TO_DEBUG("Placed " + item.GetName() + " at " + spotToFill->GetName());
            itemsToPlace.pop_back();
            #ifdef NON_3DS
            searches.pop_back();
            #endif
        }
    }
    while (unsuccessfulPlacement);

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

    FILL_ERROR_CHECK(AssumedFill(worlds, itemPool, otherItems, allLocations));

    if (!GameBeatable(worlds))
    {
        return FillError::GAME_NOT_BEATABLE;
    }

    return err;
}

std::string ErrorToName(FillError err)
{
    switch(err)
    {
        case FillError::NONE:
            return "NONE";
        case FillError::RAN_OUT_OF_RETRIES:
            return "RAN_OUT_OF_RETRIES";
        case FillError::MORE_ITEMS_THAN_LOCATIONS:
            return "MORE_ITEMS_THAN_LOCATIONS";
        case FillError::NO_REACHABLE_LOCATIONS:
            return "NO_REACHABLE_LOCATIONS";
        case FillError::GAME_NOT_BEATABLE:
            return "GAME_NOT_BEATABLE";
        default:
            return "UNKNOWN";
    }
}
