#include "item.hpp"
#include "world.hpp"

Item::Item() {}

Item::Item(const ItemID& id_, World* world_) : id(id_), world(world_) {
    worldId = world->GetWorldID();
    name = ItemIDToName(id_);
}

Item::~Item() = default;

ItemID Item::GetID() const
{
    return id;
}

std::string Item::GetName()
{
    return (world != nullptr && world->GetNumWorldTypes() == 1 ? name.substr(world->GetTypeString().length() + 1) : name) +
           (world != nullptr && world->GetNumWorlds() > 1 ? " [W" + std::to_string(world->GetWorldID() + 1) + "]" : "");
}

World* Item::GetWorld() const
{
    return world;
}

int Item::GetWorldID() const
{
    return worldId;
}

void Item::SetAsMajorItem()
{
    isMajorItem = true;
}

bool Item::IsMajorItem() const
{
    return isMajorItem;
}

bool Item::operator==(const Item& rhs) const
{
		return id == rhs.id && worldId == rhs.worldId;
}

bool Item::operator<(const Item& rhs) const
{
		return (worldId == rhs.worldId) ? id < rhs.id : worldId < rhs.worldId;
}
