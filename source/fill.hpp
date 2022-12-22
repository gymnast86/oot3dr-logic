#pragma once

#include "world.hpp"

enum class FillError {
    NONE = 0,
    RAN_OUT_OF_RETRIES,
    MORE_ITEMS_THAN_LOCATIONS,
    NO_REACHABLE_LOCATIONS,
    GAME_NOT_BEATABLE,
};

FillError AssumedFill(WorldPool& worlds, ItemPool& itemsToPlaceVector, const ItemPool& itemsNotYetPlaced, LocationPool& allowedLocations, int worldToFill = -1);
FillError FastFill(ItemPool& itemsToPlace, LocationPool& allowedLocations);
FillError FillWorlds(WorldPool& worlds);
std::string ErrorToName(FillError err);
