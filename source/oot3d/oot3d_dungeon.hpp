#pragma once

#include "../dungeon.hpp"
#include "oot3d_item.hpp"
#include "oot3d_location.hpp"

class Oot3dDungeon : public Dungeon {
public:

    Oot3dDungeon();
    ~Oot3dDungeon();

    void   SetKeyRingItemID(const ItemID& itemId);
    ItemID GetKeyRingItemID() const;
    void   SetUsingKeyRing(bool value);
    bool   IsUsingKeyRing() const;
    void   SetMQSmallKeyCount(const int& keyCount_);
    int    GetMQSmallKeyCount() const;
    void   SetAsMQ();
    bool   IsMQ() const;
    void   SetAsVanilla();
    bool   IsVanilla() const;

    int    GetSmallKeyCount() const override;

    ItemID keyRing = ItemID::NONE;
    bool usingKeyRing = false;
    int mqKeyCount = -1;
    bool isMq;

};
