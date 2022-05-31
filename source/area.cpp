#include "area.hpp"
#include "world.hpp"

Area::Area() {}

Area::~Area() = default;

bool Area::operator==(const Area& rhs) const
{
		return id == rhs.id && world->GetWorldID() == rhs.world->GetWorldID();
}

bool Area::operator<(const Area& rhs) const
{
		return (world->GetWorldID() == rhs.world->GetWorldID()) ? id < rhs.id : world->GetWorldID() < rhs.world->GetWorldID();
}
