#include "location.hpp"
#include "utility/log.hpp"
#include "world.hpp"

Location::Location() {}

Location::Location(const LocationID& id_, std::string name_, World* world_) :
                      id(id_), name(std::move(name_)), world(world_)
{
    currentItem = Item(ItemID::NONE, world);
}

Location::~Location() = default;

LocationID Location::GetID() const
{
    return id;
}

std::string Location::GetName()
{
    // Include [W#] if more than 1 world
    return name + (world->GetNumWorlds() > 1 ? " [W" + std::to_string(world->GetWorldID() + 1) + "]" : "");
}

World* Location::GetWorld() const
{
    return world;
}

Item Location::GetCurrentItem() const
{
    return currentItem;
}

void Location::SetCurrentItem(Item item)
{
    currentItem = item;
    LOG_TO_DEBUG("Placed " + currentItem.GetName() + " at " + this->GetName());
}

void Location::SetCurrentItemAsVanilla()
{
    SetCurrentItem(Item(vanillaItemId, world));
}

void Location::RemoveCurrentItem()
{
    LOG_TO_DEBUG("Removed " + currentItem.GetName() + " from " + this->GetName());
    currentItem = Item(ItemID::NONE, world);
}

ItemID Location::GetVanillaItemID() const
{
    return vanillaItemId;
}

std::string Location::TypeString() const
{
    return "Generic Location";
}

bool Location::operator==(const Location& rhs) const
{
		return id == rhs.id && world == rhs.world;
}

bool Location::operator<(const Location& rhs) const
{
		return (world == rhs.world) ? id < rhs.id : world < rhs.world;
}
