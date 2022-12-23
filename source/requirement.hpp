#pragma once

#include "item.hpp"
#include "area_id.hpp"
#include "settings.hpp"

#include <vector>
#include <variant>
#include <unordered_map>
#include <unordered_set>

#define EVENT_CHECK(eventName, world) auto& events = world->eventMap; if (events.count(eventName) == 0) {events[eventName] = events.size(); world->reverseEventMap[events[eventName]] = eventName;}

struct Requirement;
using LogicHelperMap = std::unordered_map<std::string, Requirement>;
using EventID = size_t;

enum struct RequirementType
{
    NONE = 0,
    TRUE,
    FALSE,
    OR,
    AND,
    NOT,
    ITEM,
    EVENT,
    COUNT,
    // OoT3D Specific types
    CHILD_DAY,
    CHILD_NIGHT,
    ADULT_DAY,
    ADULT_NIGHT,
    AT,
    HEARTS,
    EFFECTIVE_HEALTH,
    FIRE_TIMER,
    WATER_TIMER,
    HAS_STONES,
    HAS_MEDALLIONS,
    HAS_REWARDS,

    INVALID
};

enum struct RequirementError
{
    NONE,
    EXTRA_OR_MISSING_PARENTHESIS,
    LOGIC_SYMBOL_DOES_NOT_EXIST,
    SAME_NESTING_LEVEL,
    COULD_NOT_DETERMINE_TYPE,
    UNKNOWN_AREA_NAME,
    UNKNOWN_ITEM_NAME,
    COULD_NOT_PARSE_NUMBER,
    SETTING_NOT_FOUND,
};

struct Requirement
{
    using Argument = std::variant<int, bool, std::string, Requirement,  EventID, ItemID, AreaID, Item>;
    RequirementType type = RequirementType::INVALID;
    std::vector<Argument> args = {};
};

class World;
RequirementError ParseRequirementString(const std::string& str, Requirement& req, LogicHelperMap& logicMap, SettingsMap& settings, AreaID areaId, const std::string& game_prefix, World* world);

std::string RequirementStr(const Requirement& req, int nestingLevel = 0);

std::string ErrorToName(RequirementError err);

std::string RequirementToName(RequirementType type);
