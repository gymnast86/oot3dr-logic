#pragma once

#include "../item.hpp"

union ItemOverride_Value;

enum class ItemType {
    NONE,
    Item,
    Map,
    Compass,
    BossKey,
    SmallKey,
    Token,
    FortressSmallKey,
    Event,
    Drop,
    Refill,
    Song,
    Shop,
    DungeonReward,
    INVALID,
};

class Oot3dItem : public Item {
public:
    Oot3dItem();
    Oot3dItem(const ItemID& id_, ItemType type_, uint8_t getItemId_, bool advancement_, World* world_);
    ~Oot3dItem();

    ItemType GetType() const;
    uint16_t GetPrice() const;
    void SetPrice(const uint16_t& newPrice);

    ItemOverride_Value Value() const;

    ItemType type = ItemType::NONE;
    uint8_t getItemId = 0;
    bool advancement = false;
    uint16_t price = 0;
    bool playthrough = false;
};

ItemType NameToOot3dItemType(const std::string& name);
