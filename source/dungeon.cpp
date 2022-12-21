#include "dungeon.hpp"

Dungeon::Dungeon() { }

Dungeon::~Dungeon() = default;

void   Dungeon::SetBossKeyItemID(const ItemID& itemId) { bossKey = itemId; }
ItemID Dungeon::GetBossKeyItemID() const { return bossKey; }
void   Dungeon::SetSmallKeyItemID(const ItemID& itemId) { smallKey = itemId; }
ItemID Dungeon::GetSmallKeyItemID() const { return smallKey; }
void   Dungeon::SetSmallKeyCount(const int& keyCount_) { keyCount = keyCount_; }
int    Dungeon::GetSmallKeyCount() const { return keyCount; }
void   Dungeon::SetMapItemID(const ItemID& itemId) { map = itemId; }
ItemID Dungeon::GetMapItemID() const { return map; }
void   Dungeon::SetCompassItemID(const ItemID& itemId) { compass = itemId; }
ItemID Dungeon::GetCompassItemID() const { return compass; }

void Dungeon::AddLocation(Location* loc)
{
    locations.push_back(loc);
}
