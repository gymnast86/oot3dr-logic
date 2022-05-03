#pragma once

#define RYML_SINGLE_HDR_DEFINE_NOW
#include "../include/ryml.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

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

// Helper function for dealing with YAML library strings
std::string SubstrToString(const ryml::csubstr& substr)
{
    return std::string(substr.data(), substr.size());
}

void PrintObjectFields(const ryml::NodeRef& object, int nestingLevel = 1)
{
    std::string spaces (nestingLevel * 2, ' ');
    for (const auto& field : object.children())
    {
        if (!field.has_val())
        {
            std::cout << spaces << SubstrToString(field.key()) << ":" << std::endl;
            PrintObjectFields(field, nestingLevel + 1);
        }
        else if (!field.has_key())
        {
            std::cout << spaces << SubstrToString(field.val()) << std::endl;
        }
        else
        {
            std::cout << spaces << SubstrToString(field.key()) << ": " << SubstrToString(field.val()) << std::endl;
        }
    }
}
