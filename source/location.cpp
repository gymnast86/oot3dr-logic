#include "location.hpp"

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

std::string Location::GetName() const
{
    return name;
}

World* Location::GetWorld() const
{
    return world;
}

Item Location::GetCurrentItem() const
{
    return currentItem;
}

std::string Location::TypeString() const
{
    return "Generic Location";
}
