#pragma once

#include "item.hpp"
#include "area_id.hpp"

#include <vector>
#include <variant>
#include <unordered_map>

struct Requirement;
using LogicHelperMap = std::unordered_map<std::string, Requirement>;
using SettingsMap = std::unordered_map<std::string, std::string>;

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
    CAN_USE,
    IS_CHILD,
    IS_ADULT,
    HAS_STONES,
    HAS_MEDALLIONS,
    HAS_REWARDS,
    HAS_BOTTLE,

    INVALID
};

enum struct RequirementError
{
    NONE,
    EXTRA_OR_MISSING_PARENTHESIS,
    LOGIC_SYMBOL_DOES_NOT_EXIST,
    SAME_NESTING_LEVEL,
    COULD_NOT_DETERMINE_TYPE,
};

struct Requirement
{
    using Argument = std::variant<int, bool, std::string, Requirement, ItemID, AreaID>;
    RequirementType type = RequirementType::INVALID;
    std::vector<Argument> args;
};

// std::string printRequirement(Requirement& req, int nestingLevel = 0);

RequirementError ParseRequirementString(const std::string& str, Requirement& req, LogicHelperMap& logicMap, SettingsMap& settings);

std::string errorToName(RequirementError err);
