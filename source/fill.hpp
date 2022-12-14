#pragma once

#include "world.hpp"

enum class FillError {
    NONE = 0,
    RAN_OUT_OF_RETRIES,
    MORE_ITEMS_THAN_LOCATIONS,
    NO_REACHABLE_LOCATIONS,
    GAME_NOT_BEATABLE,
};

FillError FillWorlds(WorldPool& worlds);
std::string ErrorToName(FillError err);
