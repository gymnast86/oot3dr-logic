#include "oot3d_item.hpp"
#include "../world.hpp"

#include <unordered_map>

Oot3dItem::Oot3dItem() {}

Oot3dItem::Oot3dItem(const ItemID& id_, ItemType type_, uint8_t getItemId_, bool advancement_, World* world_)
{
    id = id_;
    name = ItemIDToName(id_);
    type = type_;
    getItemId = getItemId_;
    advancement = advancement_;
    world = world_;
    worldId = world->GetWorldID();
}

Oot3dItem::~Oot3dItem() = default;

ItemType NameToOot3dItemType(const std::string& name)
{
    std::unordered_map<std::string, ItemType> nameTypeMap = {
        {"None", ItemType::NONE},
        {"Item", ItemType::Item},
        {"Map", ItemType::Map},
        {"Compass", ItemType::Compass},
        {"Boss Key", ItemType::BossKey},
        {"Small Key", ItemType::SmallKey},
        {"Token", ItemType::Token},
        {"Fortress Small Key", ItemType::FortressSmallKey},
        {"Event", ItemType::Event},
        {"Drop", ItemType::Drop},
        {"Refill", ItemType::Refill},
        {"Song", ItemType::Song},
        {"Shop", ItemType::Shop},
        {"Dungeon Reward", ItemType::DungeonReward},
    };

    if (nameTypeMap.count(name) == 0)
    {
        return ItemType::INVALID;
    }
    return nameTypeMap.at(name);
}
