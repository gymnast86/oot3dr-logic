#include "requirement.hpp"
#include "pool_functions.hpp"

#include <iostream>

#define STR_HAS(str, substr) str.find(substr) != std::string::npos
#define AREA_VALID_CHECK(name, reqStr) if (NameToAreaID(name) == AreaID::INVALID) {std::cout << "ERROR: Unknown area name " << name << " in requirement string: \"" << reqStr << "\"" << std::endl; return RequirementError::UNKNOWN_AREA_NAME;}
#define REQ_ERROR_CHECK(err) if (err != RequirementError::NONE) {return err;}

// Takes a logic expression string and stores it as a requirement within the passed in Requirement
// object. This means we only have to parse the string once and then evaluating it many times
// later is a lot faster. An example of a logic expression string is: "Hookshot and (Bow or Bombs)"
RequirementError ParseRequirementString(const std::string& str, Requirement& req, LogicHelperMap& logicMap, SettingsMap& settings, AreaID areaId, const std::string& gamePrefix)
{

    RequirementError err = RequirementError::NONE;
    std::string logicStr (str);

    // First, we make sure that the expression has no missing or extra parenthesis
    // and that the nesting level at the beginning is the same at the end.
    //
    // Logic expressions are split up via spaces, but we only want to evaluate the parts of
    // the expression at the highest nesting level for the string that was passed in.
    // (We'll recursively call the function later to evaluate deeper levels.) So we replace
    // all the spaces on the highest nesting level with an arbitrarily chosen delimeter
    // that should never be used in logic statements.
    // (in this case: '+').
    int nestingLevel = 1;
    const char delimeter = '+';
    for (auto& ch : logicStr)
    {
        if (ch == '(')
        {
            nestingLevel++;
        }
        else if (ch == ')')
        {
            nestingLevel--;
        }

        if (nestingLevel == 1 && ch == ' ')
        {
            ch = delimeter;
        }
    }

    // If the nesting level isn't the same as what we started with, then the logic
    // expression is invalid.
    if (nestingLevel != 1)
    {
        return RequirementError::EXTRA_OR_MISSING_PARENTHESIS;
    }

    // Next we split up the expression by the delimeter in the previous step.
    size_t pos = 0;
    std::vector<std::string> splitLogicStr = {};
    while ((pos = logicStr.find(delimeter)) != std::string::npos)
    {
        // When parsing setting checks, take the entire expression
        // and the three components individually
        auto& chBefore = logicStr[pos-1];
        auto& chAfter = logicStr[pos+1];
        if (chBefore != '!' && chAfter != '!' && chBefore != '=' && chAfter != '=')
        {
            splitLogicStr.push_back(logicStr.substr(0, pos));
            logicStr.erase(0, pos + 1);
        }
        else
        {
            logicStr.erase(logicStr.begin() + pos);
        }

    }
    splitLogicStr.push_back(logicStr);



    // Once we have the different parts of our expression, we can use the number
    // of parts we have to determine what kind of expression it is.

    // If we only have one part, then we have either a logic helper, an item,
    // an at check, a setting, or a count
    if (splitLogicStr.size() == 1)
    {
        const std::string& argStr = splitLogicStr[0];

        // First check if there are no requirements
        if (STR_HAS(argStr, "True"))
        {
            req.type = RequirementType::TRUE;
            return RequirementError::NONE;
        }
        // Then for a logic helper...
        if (logicMap.count(argStr) > 0)
        {
            // replace string
            req = logicMap[argStr];
            return RequirementError::NONE;
        }
        // Then an item...
        else if (NameToItemID(gamePrefix + " " + argStr) != ItemID::INVALID)
        {
            req.type = RequirementType::ITEM;
            req.args.push_back(NameToItemID(argStr));
            return RequirementError::NONE;
        }
        // Then the time/age checks...
        else if (STR_HAS(argStr, "child_day"))
        {
            req.type = RequirementType::CHILD_DAY;
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "child_night"))
        {
            req.type = RequirementType::CHILD_NIGHT;
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "adult_day"))
        {
            req.type = RequirementType::ADULT_DAY;
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "adult_night"))
        {
            req.type = RequirementType::ADULT_NIGHT;
            return RequirementError::NONE;
        }

        // Then an at/here check...
        else if (STR_HAS(argStr, "at(") || STR_HAS(argStr, "here("))
        {
            req.type = RequirementType::AT;
            AreaID argArea;
            Requirement areaReq;
            std::string areaReqStr;
            if (STR_HAS(argStr, "here"))
            {
                argArea = areaId;
                // Get rid of parenthesis
                areaReqStr = std::string (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            }
            else // if argStr has "at"
            {
                // Get rid of parenthesis
                std::string countArgs (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
                // Erase any quotation marks
                countArgs.erase(std::remove(countArgs.begin(), countArgs.end(), '\''), countArgs.end());

                // Split up the arguments
                pos = 0;
                splitLogicStr = {};
                while ((pos = countArgs.find(",")) != std::string::npos)
                {
                    splitLogicStr.push_back(countArgs.substr(0, pos));
                    countArgs.erase(0, pos + 1);
                }
                splitLogicStr.push_back(countArgs);
                // Get the arguments
                std::string areaName = splitLogicStr[0];
                // Get rid of the leading space if it exists
                areaReqStr = splitLogicStr[1][0] == ' ' ? splitLogicStr[1].substr(1, splitLogicStr[1].length() - 1) : splitLogicStr[1];
                argArea = NameToAreaID(areaName);
            }
            std::string areaName = AreaIDToName(argArea);
            AREA_VALID_CHECK(areaName, argStr);
            err = ParseRequirementString(areaReqStr, areaReq, logicMap, settings, argArea, gamePrefix);
            REQ_ERROR_CHECK(err);
            req.args.push_back(argArea);
            req.args.push_back(areaReq);
            return RequirementError::NONE;
        }
        // Then a count...
        else if (STR_HAS(argStr, "count"))
        {
            req.type = RequirementType::COUNT;
            // Since a count has two arguments (a number and an item), we have
            // to split up the string in the parenthesis into those arguments.

            // Get rid of parenthesis
            std::string countArgs (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            // Erase any spaces
            countArgs.erase(std::remove(countArgs.begin(), countArgs.end(), ' '), countArgs.end());

            // Split up the arguments
            pos = 0;
            splitLogicStr = {};
            while ((pos = countArgs.find(",")) != std::string::npos)
            {
                splitLogicStr.push_back(countArgs.substr(0, pos));
                countArgs.erase(0, pos + 1);
            }
            splitLogicStr.push_back(countArgs);

            // Get the arguments
            int count;
            if (settings.count(splitLogicStr[1]) > 0)
            {
                // If the count depends on a setting
                count = std::stoi(settings.at(splitLogicStr[1]));
            }
            else
            {
                // If the count is hardcoded
                count = std::stoi(splitLogicStr[1]);
            }
            std::string itemName = splitLogicStr[0];
            auto argItem = NameToItemID(itemName);
            //ITEM_VALID_CHECK(argItem, "Game Item of name \"" << itemName << " Does Not Exist");
            req.args.push_back(count);
            req.args.push_back(argItem);
            return RequirementError::NONE;
        }
        // Then a can_play check...
        else if (STR_HAS(argStr, "can_play"))
        {
            // Turn the argument into type AND with the song and Ocarina as arguments
            req.type = RequirementType::AND;
            std::string songStr (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            auto song = NameToItemID(songStr);
            Requirement ocarinaReq = {RequirementType::ITEM, {ItemID::Oot3dProgressiveOcarina}};
            Requirement songReq = {RequirementType::ITEM, {song}};
            req.args.push_back(ocarinaReq);
            req.args.push_back(songReq);

            return RequirementError::NONE;
        }
        // Then a settings check...
        // Since settings don't change during seed generation, we can resolve them
        // to a true or false value now
        else if (STR_HAS(argStr, "!=") || STR_HAS(argStr, "=="))
        {
            bool equalComparison = STR_HAS(argStr, "==");

            // Split up the comparison using the second comparison character (which will always be '=')
            auto compPos = argStr.rfind('=');
            std::string comparedOption (argStr.begin() + (compPos + 1), argStr.end());
            std::string settingName (argStr.begin(), argStr.begin() + (compPos - 1));

            std::string& actualOption = settings.at(settingName);

            // If the comparison is true
            if ((equalComparison && actualOption == comparedOption) || (!equalComparison && actualOption != comparedOption))
            {
                req.type = RequirementType::TRUE;
            }
            else
            {
                req.type = RequirementType::FALSE;
            }
            return RequirementError::NONE;
        }
        // Case for boolean setting checks
        else if (settings.count(argStr) > 0)
        {
            if (settings.at(argStr) == "On")
            {
                req.type = RequirementType::TRUE;
            }
            else
            {
                req.type = RequirementType::FALSE;
            }
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "has_stones"))
        {
            req.type = RequirementType::HAS_STONES;
            std::string countStr (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            int count = std::stoi(settings.at(countStr));
            req.args.push_back(count);
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "has_medallions"))
        {
            req.type = RequirementType::HAS_MEDALLIONS;
            std::string countStr (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            int count = std::stoi(settings.at(countStr));
            req.args.push_back(count);
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "has_dungeon_rewards"))
        {
            req.type = RequirementType::HAS_REWARDS;
            std::string countStr (argStr.begin() + argStr.find('(') + 1, argStr.end() - 1);
            int count = std::stoi(settings.at(countStr));
            req.args.push_back(count);
            return RequirementError::NONE;
        }
        else if (STR_HAS(argStr, "False"))
        {
            req.type = RequirementType::FALSE;
            return RequirementError::NONE;
        }
        std::cout << "Unrecognized logic symbol: \"" << argStr << "\"" << std::endl;
        return RequirementError::LOGIC_SYMBOL_DOES_NOT_EXIST;
    }

    // If our expression has two parts, then the only type of requirement
    // that can currently be is a "not" requirement
    if (splitLogicStr.size() == 2)
    {
        if (splitLogicStr[0] == "not")
        {
            req.type = RequirementType::NOT;
            req.args.emplace_back(Requirement());
            // The second part of the not expression is another expression
            // so we have to evaluate that one as well.
            auto reqStr = splitLogicStr[1];
            // Get rid of parenthesis around the expression if it has them
            if (reqStr[0] == '(')
            {
                reqStr = reqStr.substr(1, reqStr.length() - 2);
            }
            // Evaluate the deeper expression and add it to the requirement object if it's valid
            if ((err = ParseRequirementString(reqStr, std::get<Requirement>(req.args.back()), logicMap, settings, areaId, gamePrefix)) != RequirementError::NONE) return err;
        }
        else
        {
            std::cout << "Unrecognized 2 part expression: \"" << str << "\"" << std::endl;
            return RequirementError::LOGIC_SYMBOL_DOES_NOT_EXIST;
        }
    }

    // If we have more than two parts to our expression, then we have either "and"
    // or "or".
    bool andType = ElementInPool("and", splitLogicStr);
    bool orType = ElementInPool("or", splitLogicStr);

    // If we have both of them, there's a problem with the logic expression
    if (andType && orType)
    {
        std::cout << "\"and\" & \"or\" in same nesting level when parsing \"" << str << "\"" << std::endl;
        return RequirementError::SAME_NESTING_LEVEL;
    }

    if (andType || orType)
    {
        // Set the appropriate type
        if (andType)
        {
            req.type = RequirementType::AND;
        }
        else if (orType)
        {
            req.type = RequirementType::OR;
        }

        // Once we know the type, we can erase the "and"s or "or"s and are left with just the deeper
        // expressions to be logically operated on.
        FilterAndEraseFromPool(splitLogicStr, [](const std::string& arg){return arg == "and" || arg == "or";});

        // If we have any deeper "not" expressions, we have to recombine them here since they got separated
        // by the delimeter earlier
        for (auto itr = splitLogicStr.begin(); itr != splitLogicStr.end(); itr++)
        {
            if (*itr == "not")
            {
                *itr = *itr + " " + *(itr + 1);
                splitLogicStr.erase(itr + 1);
            }
        }

        // For each deeper expression, parse it and add it as an argument to the
        // Requirement
        for (auto& reqStr : splitLogicStr)
        {
            req.args.emplace_back(Requirement());
            // Get rid of parenthesis surrounding each deeper expression
            if (reqStr[0] == '(')
            {
                reqStr = reqStr.substr(1, reqStr.length() - 2);
            }
            if ((err = ParseRequirementString(reqStr, std::get<Requirement>(req.args.back()), logicMap, settings, areaId, gamePrefix)) != RequirementError::NONE) return err;
        }
    }


    if (req.type != RequirementType::NONE)
    {
        return RequirementError::NONE;
    }
    else
    // If we've reached this point, we weren't able to determine a logical operator within the expression
    {
        std::cout << "Could not determine logical operator type from expression: \"" << str << "\"" << std::endl;
        return RequirementError::COULD_NOT_DETERMINE_TYPE;
    }
}

// Helper function for printing requirements
static std::string tabs(int numTabs)
{
    std::string returnStr = "";
    for (int i = 0; i < numTabs; i++)
    {
        returnStr += "\t";
    }
    return returnStr;
}

std::string RequirementStr(Requirement& req, int nestingLevel /*= 0*/)
{
    std::string returnStr = "";
    uint32_t expectedCount = 0;
    ItemID itemId;
    Requirement nestedReq;
    returnStr += tabs(nestingLevel);
    switch(req.type)
    {
        case RequirementType::TRUE:
            returnStr += "True\n";
            return returnStr;
        case RequirementType::FALSE:
            returnStr += "False\n";
            return returnStr;
        case RequirementType::OR:
            returnStr += "or\n";
            for (Requirement::Argument& arg : req.args)
            {
                nestedReq = std::get<Requirement>(arg);
                returnStr += RequirementStr(nestedReq, nestingLevel + 1);
            }
            return returnStr;
        case RequirementType::AND:
            returnStr += "and\n";
            for (Requirement::Argument& arg : req.args)
            {
                nestedReq = std::get<Requirement>(arg);
                returnStr += RequirementStr(nestedReq, nestingLevel + 1);
            }
            return returnStr;
        case RequirementType::NOT:
            returnStr += "not\n";
            returnStr += RequirementStr(std::get<Requirement>(req.args[0]), nestingLevel + 1);
            return returnStr;
        case RequirementType::ITEM:
            itemId = std::get<ItemID>(req.args[0]);
            returnStr += ItemIDToName(itemId) + "\n";
            return returnStr;
        case RequirementType::COUNT:
            returnStr += "count: ";
            expectedCount = std::get<int>(req.args[0]);
            itemId = std::get<ItemID>(req.args[1]);
            returnStr += std::to_string(expectedCount) + " " + ItemIDToName(itemId) + "\n";
            return returnStr;
        case RequirementType::CHILD_DAY:
            returnStr += "child_day";
            return returnStr;
        case RequirementType::CHILD_NIGHT:
            returnStr += "child_night";
            return returnStr;
        case RequirementType::ADULT_DAY:
            returnStr += "adult_day";
            return returnStr;
        case RequirementType::ADULT_NIGHT:
            returnStr += "adult_night";
            return returnStr;
        // Add other types later
        default:
            return returnStr;
    }
}

std::string errorToName(RequirementError err)
{
    switch (err)
    {
        case RequirementError::NONE:
            return "NONE";
        case RequirementError::EXTRA_OR_MISSING_PARENTHESIS:
            return "EXTRA_OR_MISSING_PARENTHESIS";
        case RequirementError::LOGIC_SYMBOL_DOES_NOT_EXIST:
            return "LOGIC_SYMBOL_DOES_NOT_EXIST";
        case RequirementError::SAME_NESTING_LEVEL:
            return "SAME_NESTING_LEVEL";
        case RequirementError::COULD_NOT_DETERMINE_TYPE:
            return "COULD_NOT_DETERMINE_TYPE";
        case RequirementError::UNKNOWN_AREA_NAME:
            return "UNKNOWN_AREA_NAME";
        default:
            return "UNKNOWN";
    }
}

std::string RequirementToName(RequirementType type)
{
    switch(type)
    {
        case RequirementType::TRUE:
            return "True";
        case RequirementType::FALSE:
            return "False";
        case RequirementType::OR:
            return "Or";
        case RequirementType::AND:
            return "And";
        case RequirementType::NOT:
            return "Not";
        case RequirementType::ITEM:
            return "Item";
        case RequirementType::COUNT:
            return "Count";
        case RequirementType::CHILD_DAY:
            return "Child_Day";
        case RequirementType::CHILD_NIGHT:
            return "Child_Night";
        case RequirementType::ADULT_DAY:
            return "Adult_Day";
        case RequirementType::ADULT_NIGHT:
            return "Adult_Night";
        case RequirementType::AT:
            return "At";
        case RequirementType::HAS_STONES:
            return "Has_Stones";
        case RequirementType::HAS_MEDALLIONS:
            return "HAS_MEDALLIONS";
        case RequirementType::HAS_REWARDS:
            return "HAS_REWARDS";
        default:
            return "Unknown Type";
    }
    return "Unknown Type";
}
