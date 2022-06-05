#pragma once

#include "../requirement.hpp"

#include <memory>
#include <list>
#include <string>

class Oot3dWorld;

#define TIMEPASS true
#define NO_TIMEPASS false

struct ConditionsStruct {
    RequirementFn glitchless = []{return false;};
    RequirementFn glitched = []{return false;};
};

struct EventStruct {
    std::string name;
    ConditionsStruct requirement;
};

struct LocationStruct {
    std::string name;
    ConditionsStruct requirement;
};

struct EntranceStruct {
    std::string connectedAreaName;
    ConditionsStruct requirement;
};

struct AreaStruct {
    std::string areaName;
    std::string sceneName;
    bool timePass;
    std::list<EventStruct> events;
    std::list<LocationStruct> locations;
    std::list<EntranceStruct> entrances;
};
