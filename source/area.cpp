#include "area.hpp"
#include "world.hpp"

#include <iostream>

Area::Area() {}

Area::~Area() = default;

Event* Area::GetEvent(const ItemID& itemId)
{
		for (auto& event : events)
		{
				if (event.item == itemId)
				{
						return &event;
				}
		}
		std::cout << ItemIDToName(itemId) << " Is not an event in " << AreaIDToName(id) << std::endl;
		return nullptr;
}

LocationAccess* Area::GetLocationAccess(const LocationID& locationId)
{
		for (auto& locAccess : locations)
		{
				if (locAccess.location->id == locationId)
				{
						return &locAccess;
				}
		}
		std::cout << LocationIDToName(locationId) << " Is not a location in " << AreaIDToName(id) << std::endl;
		return nullptr;
}

Entrance* Area::GetExit(const AreaID& areaId)
{
		for (auto& exit : exits)
		{
				if (exit->GetConnectedAreaID() == areaId)
				{
						return exit.get();
				}
		}
		std::cout << AreaIDToName(areaId) << " Is not an exit area in " << AreaIDToName(id) << std::endl;
		return nullptr;
}

bool Area::operator==(const Area& rhs) const
{
		return id == rhs.id && world->GetWorldID() == rhs.world->GetWorldID();
}

bool Area::operator<(const Area& rhs) const
{
		return (world->GetWorldID() == rhs.world->GetWorldID()) ? id < rhs.id : world->GetWorldID() < rhs.world->GetWorldID();
}
