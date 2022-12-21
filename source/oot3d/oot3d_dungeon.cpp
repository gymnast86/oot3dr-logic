#include "oot3d_dungeon.hpp"

Oot3dDungeon::Oot3dDungeon() {}

Oot3dDungeon::~Oot3dDungeon() {}

void   Oot3dDungeon::SetKeyRingItemID(const ItemID& itemId) { keyRing = itemId; }
ItemID Oot3dDungeon::GetKeyRingItemID() const { return keyRing; }
void   Oot3dDungeon::SetUsingKeyRing(bool value) { usingKeyRing = value; }
bool   Oot3dDungeon::IsUsingKeyRing() const { return usingKeyRing; }
void   Oot3dDungeon::SetMQSmallKeyCount(const int& keyCount_) { mqKeyCount = keyCount_; }
void   Oot3dDungeon::SetAsMQ() { isMq = true; }
bool   Oot3dDungeon::IsMQ() const { return isMq; }
void   Oot3dDungeon::SetAsVanilla() { isMq = false; }
bool   Oot3dDungeon::IsVanilla() const { return !isMq; }

int Oot3dDungeon::GetSmallKeyCount() const
{
    if (IsMQ())
    {
        return mqKeyCount;
    }
    else
    {
        return keyCount;
    }
}
