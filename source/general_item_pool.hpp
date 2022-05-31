#pragma once

#include "item.hpp"
#include "settings.hpp"

#include <vector>
#include <unordered_set>

using ItemPool = std::vector<Item>;
using ItemIDPool = std::vector<ItemID>;
using ItemMultiSet = std::unordered_multiset<Item>;
