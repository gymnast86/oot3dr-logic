#pragma once

#include "Yaml.hpp"
#include "string_util.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// shorthand for getting yaml field
#define YAML_FIELD(ref) Utility::Str::RemoveUnicodeReplacements(ref.As<std::string>());

// Short function for getting the string data from a file
int GetFileContents(const std::string& filename, std::string& fileContents)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "unable to open file \"" << filename << "\"" << std::endl;
        return 1;
    }

    // Read and load file contents
    auto ss = std::ostringstream{};
    ss << file.rdbuf();
    fileContents = ss.str();

    return 0;
}

void PrintYAML(const Yaml::Node& node, int nestingLevel = 1)
{
    std::string spaces (nestingLevel * 2, ' ');
    auto fieldIt = node.End();
    do
    {
        fieldIt--;
        auto field = *fieldIt;
        if (field.second.IsScalar())
        {
            std::cout << spaces << field.first << ": " << field.second.As<std::string>() << std::endl;
        }
        else if (field.second.IsSequence())
        {
            std::cout << spaces << field.first << ": " << std::endl;
            for (auto it = field.second.Begin(); it != field.second.End(); it++)
            {
                std::cout << spaces << "  - " << (*it).second.As<std::string>() << std::endl;
            }
        }
        else if (field.second.IsMap())
        {
            std::cout << spaces << field.first << ": " << std::endl;
            PrintYAML(field.second, nestingLevel + 1);
        }
    }
    while (fieldIt != node.Begin());
}
