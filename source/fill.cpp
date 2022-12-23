#include "fill.hpp"
#include "search.hpp"
#include "utility/timing.hpp"
#include "utility/random.hpp"
#include "utility/pool_functions.hpp"

#include <iostream>

#define FILL_ERROR_CHECK(func) err = func; if (err != FillError::NONE) {return err;}
#define ENOUGH_SPACE_CHECK(items, locations) if (items.size() > locations.size()) {return FillError::MORE_ITEMS_THAN_LOCATIONS;}

FillError AssumedFill(WorldPool& worlds, ItemPool& itemsToPlaceVector, const ItemPool& itemsNotYetPlaced, LocationPool& allowedLocations, int worldToFill /*= -1*/)
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
                if (locationSet.count(locAccess.location) > 0 && locAccess.location->GetCurrentItem().GetID() == NONE)
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
            LOG_TO_DEBUG("Ran out of assumed fill retries");
            return FillError::RAN_OUT_OF_RETRIES;
        }
        retries--;
        unsuccessfulPlacement = false;
        ShufflePool(itemsToPlaceVector);

        std::list<Item> itemsToPlace;
        itemsToPlace.assign(itemsToPlaceVector.begin(), itemsToPlaceVector.end());
        LocationPool rollbacks;

        while (!itemsToPlace.empty())
        {
            // Get a random item to place
            auto item = itemsToPlace.back();
            itemsToPlace.pop_back();

            ShufflePool(validLocations);

            // Get the list of accessible locations
            // Assume we have all the items which haven't been placed yet
            // (except for this one we're about to place)
            ItemPool assumedItems = itemsNotYetPlaced;
            MergePools(assumedItems, itemsToPlace);
            auto search = Search(SearchMode::AccessibleLocations, &worlds, assumedItems, worldToFill);
            search.SearchWorlds();
            Location* spotToFill = nullptr;

            for (auto locAccess : validLocations)
            {
                if (locAccess->location->GetCurrentItem().GetID() != NONE || search.visitedAreas.count(locAccess->area) == 0)
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
                    location->RemoveCurrentItem();
                }
                // Also add back the randomly selected item
                itemsToPlace.push_back(item);
                rollbacks.clear();
                // Break out of the item placement loop and flag an unsuccessful
                // placement attempt to try again.
                unsuccessfulPlacement = true;
                break;
            }

            spotToFill->SetCurrentItem(item);
            rollbacks.push_back(spotToFill);
        }
    }
    while (unsuccessfulPlacement);

    return FillError::NONE;
}

FillError FastFill(ItemPool& itemsToPlace, LocationPool& allowedLocations)
{
    auto emptyAllowedLocations = FilterFromPool(allowedLocations, [](Location* loc){return loc->GetCurrentItem().GetID() == NONE;});
    ENOUGH_SPACE_CHECK(itemsToPlace, emptyAllowedLocations);
    ShufflePool(emptyAllowedLocations);
    for (auto location : emptyAllowedLocations)
    {
        if (itemsToPlace.empty())
        {
            break;
        }
        location->SetCurrentItem(PopRandomElement(itemsToPlace));
    }

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
        auto worldItemLocations = world->GetAllItemLocations();
        MergePools(allLocations, worldItemLocations);
        itemPool.insert(itemPool.end(), world->itemPool.begin(), world->itemPool.end());
    }

    // Get Major items
    auto majorItems = FilterAndEraseFromPool(itemPool, [](const Item& item){return item.IsMajorItem();});

    // Fill major items into any available locations
    FILL_ERROR_CHECK(AssumedFill(worlds, majorItems, itemPool, allLocations));
    // Fill the rest with the known junk from the rest of the pool
    FILL_ERROR_CHECK(FastFill(itemPool, allLocations));

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
