#pragma once

#include "item.hpp"
#include "settings.hpp"

#include <vector>
#include <set>
#include <unordered_map>

using ItemPool     = std::vector<Item>;
using ItemIDPool   = std::vector<ItemID>;
using ItemMultiSet = std::multiset<Item>;
using ItemMap      = std::unordered_map<std::string, int>;

namespace PresetPools {
    extern ItemPool NoItems;
};
