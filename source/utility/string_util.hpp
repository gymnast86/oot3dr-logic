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
    std::vector<T> split(const T& string, const typename T::value_type delim)
    {
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

    template<typename T, typename U>
    T merge(const std::vector<T>& lines, const U& separator)
    {
      	T ret;
      	for (size_t i = 0; i < lines.size(); i++) {
      		  ret += lines[i];
            if (i < lines.size() - 1)
            {
                ret += separator;
            }
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

    std::string InsertUnicodeReplacements(std::string text);
    std::string RemoveUnicodeReplacements(std::string text);
    std::string ToLower(std::string str);
    bool StartsWith(const std::string& str, const std::string& prefix);
    bool EndsWith(const std::string& str, const std::string& suffix);
}
