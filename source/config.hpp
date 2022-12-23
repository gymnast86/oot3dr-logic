#pragma once

#include "settings.hpp"

#include <string>
#include <vector>

enum struct ConfigError {
    NONE = 0,
    COULD_NOT_OPEN,
    MISSING_KEY,
    DIFFERENT_FILE_VERSION,
    DIFFERENT_RANDO_VERSION,
    INVALID_VALUE,
    TOO_MANY_OF_ITEM,
    UNKNOWN,
    COUNT
};

struct Config {

    std::string outputDir = "";
    std::string seed = "";

    std::vector<SettingsMap> settingsVector = {};
};


ConfigError CreateDefaultConfig(const std::string& filePath);

ConfigError LoadConfigFromFile(const std::string& filePath, Config& out, bool ignoreErrors = false);

ConfigError WriteConfigToFile(const std::string& filePath, Config& config);

std::string ErrorToName(ConfigError err);
