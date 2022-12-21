#include "string_util.hpp"

#include <map>

// This map is for characters that the YAML parsing library doesn't like.
// These characters will be translated into the literal string of their unicode
// mapping and then translated back after YAML parsing.
// TODO: Try to generalize this at some point
static std::map<std::string, std::string> unicodeMappings = {
    {"À", "\\u00C0"},
    {"Á", "\\u00C1"},
    {"Â", "\\u00C2"},
    {"É", "\\u00C9"},
    {"à", "\\u00E0"},
    {"á", "\\u00E1"},
    {"â", "\\u00E2"},
    {"ç", "\\u00E7"},
    {"è", "\\u00E8"},
    {"é", "\\u00E9"},
    {"ê", "\\u00EA"},
    {"í", "\\u00ED"},
    {"î", "\\u00EE"},
    {"ï", "\\u00EF"},
    {"ñ", "\\u00F1"},
    {"ó", "\\u00F3"},
    {"ô", "\\u00F4"},
    {"ú", "\\u00FA"},
    {"Œ", "\\u0152"},
    {"œ", "\\u0153"},
};

namespace Utility::Str {

    std::string InsertUnicodeReplacements(std::string text)
    {
        for (auto& [c, unicode] : unicodeMappings)
        {
            auto pos = text.find(c);
            while (pos != std::string::npos)
            {
                text.erase(pos, c.length());
                text.insert(pos, unicode);
                pos = text.find(c);
            }
        }

        return text;
    }

    std::string RemoveUnicodeReplacements(std::string text)
    {
        for (auto& [c, unicode] : unicodeMappings)
        {
            auto pos = text.find(unicode);
            while (pos != std::string::npos)
            {
                text.erase(pos, unicode.length());
                text.insert(pos, c);
                pos = text.find(unicode);
            }
        }

        return text;
    }

    std::string ToLower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return std::tolower(c);});
        return str;
    }

    bool StartsWith(const std::string& str, const std::string& prefix)
    {
        return str.rfind(prefix, 0) == 0;
    }

    bool EndsWith(const std::string& str, const std::string& suffix)
    {
        if (suffix.length() > str.length() || suffix == "")
        {
            return false;
        }
        return str.find(suffix, str.length() - suffix.length());
    }
}
