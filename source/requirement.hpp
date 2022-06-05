#pragma once

#include "item.hpp"
#include "area_id.hpp"
#include "settings.hpp"

#include <vector>
#include <variant>
#include <unordered_map>
#include <functional>


struct Requirement;
using LogicHelperMap = std::unordered_map<std::string, Requirement>;
using RequirementFn = std::function<bool()>;

enum struct RequirementType
{
    NONE = 0,
    OR,
    AND,
    NOT,
    ITEM,
    COUNT,
    AT,
    TRUE,
    FALSE,
    // OoT3D Specific types
    CHILD_DAY,
    CHILD_NIGHT,
    ADULT_DAY,
    ADULT_NIGHT,
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
};

struct Requirement
{
    using Argument = std::variant<int, bool, std::string, Requirement, ItemID, AreaID>;
    RequirementType type = RequirementType::INVALID;
    std::vector<Argument> args;
};

// std::string printRequirement(Requirement& req, int nestingLevel = 0);

RequirementError ParseRequirementString(const std::string& str, Requirement& req, LogicHelperMap& logicMap, SettingsMap& settings, AreaID areaId);

std::string RequirementStr(Requirement& req, int nestingLevel = 0);

std::string errorToName(RequirementError err);

std::string RequirementToName(RequirementType type);
