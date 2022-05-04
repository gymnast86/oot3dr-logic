#pragma once

#include "area_id.hpp"
#include "location.hpp"
#include "item.hpp"
#include "entrance.hpp"

#include <string>
#include <list>

struct Event {
    ItemID item;
    Requirement requirement;
};

struct LocationAccess {
    Location* location;
    Requirement requirement;
};

class World;
class Area {
public:

    Area();
    ~Area();

    AreaID id = AreaID::INVALID;
    std::string name = "";
    std::list<Event> events;
    std::list<LocationAccess> locations;
    std::list<Entrance> exits;
    std::list<Entrance*> entrances;
    World* world = nullptr;

};
