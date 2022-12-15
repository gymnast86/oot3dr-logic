#pragma once

#include <ios>
#include <string>
#include <type_traits>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Utility::Str {

    template<typename T>
    std::vector<T> split(const T& string, const typename T::value_type delim) {
    	std::vector<T> ret;
    	T tail = string;
    	auto index = tail.find_first_of(delim);

    	while (index != T::npos) {
    		ret.push_back(tail.substr(0, index));
    		tail = tail.substr(index + 1);
    		index = tail.find_first_of(delim);
    	}
    	ret.push_back(tail); //add anything after last line break

    	return ret;
    }

    template<typename T>
    T merge(const std::vector<T>& lines, const typename T::value_type separator) {
    	T ret;
    	for (const T& segment : lines) {
    		ret += segment + separator;
    	}

    	return ret;
    }

    template<typename T>
    std::string intToHex(const T& i, const bool& base = true)
    {
      static_assert(std::is_integral_v<T>, "intToHex<T> must be integral type!");

      std::stringstream stream;
      stream << std::hex << (base ? std::showbase : std::noshowbase) << i;
      return stream.str();
    }

    template<typename T>
    std::string intToHex(const T& i, const std::streamsize& width, const bool& base = true)
    {
      static_assert(std::is_integral_v<T>, "intToHex<T> must be integral type!");

      std::stringstream stream;
      stream << std::hex << (base ? std::showbase : std::noshowbase) << std::setfill('0') << std::setw(width) << i;
      return stream.str();
    }

    // This map is for characters that the YAML parsing library seems to not like.
    // These characters will be translated into the literal string of their unicode
    // mapping and then translated back after YAML parsing.
    // TODO: Try to generalize this at some point
    std::map<std::string, std::string> unicodeMappings = {
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
}
