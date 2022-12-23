#include "generate.hpp"

#include "config.hpp"
#include "fill.hpp"
#include "search.hpp"
#include "spoiler_log.hpp"
#include "oot3d/oot3d_world.hpp"
#include "utility/random.hpp"
#include "utility/timing.hpp"

#include <unordered_map>
#include <array>
#include <vector>
#include <unordered_set>

int GenerateRandomizer()
{
    StartTiming("General");



    Config config;
    // Create default config if it doesn't exist
    std::ifstream conf(LOGS_PATH "config.yaml");
    if (!conf.is_open())
    {
        std::cout << "Creating default config" << std::endl;
        ConfigError err = createDefaultConfig(LOGS_PATH "config.yaml");
        if (err != ConfigError::NONE)
        {
            LOG_TO_ERROR("Failed to create config, ERROR: " + errorToName(err));
            return 1;
        }
    }
    conf.close();

    // Read saved config
    std::cout << "Reading config" << std::endl;
    ConfigError err = loadFromFile(LOGS_PATH "config.yaml", config);
    if (err != ConfigError::NONE)
    {
        LOG_TO_ERROR("Failed to read config, ERROR: " + errorToName(err));
        return 1;
    }

    auto settingsVector = config.settingsVector;
    WorldPool worlds;
    worlds.resize(settingsVector.size());

    std::set<std::string> worldTypes;
    for (auto& settings : settingsVector)
    {
        worldTypes.insert(settings["world_type"]);
    }

    Random_Init(0); // This eventually has to go where deciding random settings

    std::cout << "Building Worlds..." << std::endl;
    for (size_t i = 0; i < settingsVector.size(); i++)
    {
        auto& settings = settingsVector[i];
        if (settings["world_type"] == "oot3d")
        {
            LOG_TO_DEBUG("Building oot3d world...")
            auto world = std::make_unique<Oot3dWorld>(settings, settingsVector.size());
            worlds[i] = std::move(world);
        }
        else if (settings["world_type"] == "mm3d")
        {
            // Make MM3D world
        }
        else
        {
            LOG_TO_ERROR("ERROR: No world type defined in settings for world " + std::to_string(i));
            return 1;
        }
        worlds[i]->worldId = i;
        worlds[i]->numWorlds = worlds.size();
        worlds[i]->numWorldTypes = worldTypes.size();
        if (worlds[i]->Build() != WorldBuildingError::NONE)
        {
            LOG_TO_ERROR("when building world " + std::to_string(i) + " of type " + settings["world_type"]);
            return 1;
        }
    }

    StartTiming("Fill");
    std::cout << "Filling Worlds..." << std::endl;
    FillError fillErr = FillWorlds(worlds);
    if (fillErr != FillError::NONE)
    {
        LOG_TO_ERROR("ERROR: " + ErrorToName(fillErr) + " when attempting to fill worlds");
        return 1;
    }

    EndTiming("Fill");
    PrintTiming("Fill");
    std::cout << "Generating Playthrough..." << std::endl;
    GeneratePlaythrough(worlds);

    GenerateSpoilerLog(worlds);

    EndTiming("General");
    PrintTiming("General");

    return 0;
}
