#pragma once

#include "area_id.hpp"
#include "location.hpp"
#include "item.hpp"
#include "entrance.hpp"

#include <string>
#include <list>
#include <memory>

struct Event {
    ItemID item;
    RequirementFn requirement;
    Area* area;
};

struct LocationAccess {
    Location* location;
    RequirementFn requirement;
    Area* area;
};

class World;
class Area {
public:

    Area();
    virtual ~Area();

    bool operator==(const Area& rhs) const;
    bool operator<(const Area& rhs) const;

    Event* GetEvent(const ItemID& itemId);
    LocationAccess* GetLocationAccess(const LocationID& locationId);
    Entrance* GetExit(const AreaID& areaId);

    AreaID id = AreaID::INVALID;
    std::string name = "";
    std::list<Event> events;
    std::list<LocationAccess> locations;
    std::list<std::unique_ptr<Entrance>> exits;
    std::list<Entrance*> entrances;
    World* world = nullptr;

};
