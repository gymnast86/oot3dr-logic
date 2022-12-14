#include "spoiler_log.hpp"

#include "file_system_defs.hpp"

#include <fstream>

static std::string GetSpoilerFormatLocation(Location* location, const size_t& longestNameLength, const WorldPool& worlds)
{
    // Print the world number if more than 1 world
    std::string locWorldNumber = worlds.size() > 1 ? " [W" + std::to_string(location->GetWorld()->GetWorldID() + 1) + "]" : "";
                                                                 // Don't add an extra space if the world id is two digits long
    size_t numSpaces = (longestNameLength - location->GetName().length()) + ((location->GetWorld()->GetWorldID() >= 9) ? 0 : 1);
    std::string spaces (numSpaces, ' ');

    // Don't say which player the item is for if there's only 1 world
    std::string itemWorldNumber = worlds.size() > 1 ? " [W" + std::to_string(location->currentItem.GetWorld()->GetWorldID() + 1) + "]" : "";
    std::string itemName = location->currentItem.GetName() + (worlds.size() > 1 ? itemWorldNumber : "");

    return location->GetName() + locWorldNumber + ":" + spaces + itemName;
}

void GenerateSpoilerLog(WorldPool& worlds)
{
    std::ofstream log(LOGS_PATH "/Spoiler-Log.txt");

    // Playthroughs are stored in world 1 for the time being, regardless of how
    // many worlds there are.
    auto& playthroughSpheres = worlds[0]->playthroughSpheres;
    auto& entranceSpheres = worlds[0]->entranceSpheres;

    // Find the longest location/entrances names for formatting the file
    size_t longestNameLength = 0;
    size_t longestEntranceLength = 0;
    LOG_TO_DEBUG("Getting Name Lengths");
    for (auto sphereItr = playthroughSpheres.begin(); sphereItr != playthroughSpheres.end(); sphereItr++)
    {
        for (auto location : *sphereItr)
        {
            longestNameLength = std::max(longestNameLength, location->GetName().length());
        }
    }
    // for (auto& world : worlds)
    // {
    //     auto entrances = world.getShuffledEntrances(EntranceType::ALL, false);
    //     for (auto entrance : entrances)
    //     {
    //         longestEntranceLength = std::max(longestEntranceLength, entrance->getOriginalName().length());
    //     }
    // }

    // Print the playthrough
    LOG_TO_DEBUG("Printing Playthrough");
    log << "Playthrough:" << std::endl;
    int sphere = 0;
    for (auto sphereItr = playthroughSpheres.begin(); sphereItr != playthroughSpheres.end(); sphereItr++, sphere++)
    {
        log << "\tSphere " << std::to_string(sphere) << ":" << std::endl;
        auto& sphereLocations = *sphereItr;
        for (auto location : sphereLocations)
        {
            log << "\t\t" << GetSpoilerFormatLocation(location, longestNameLength, worlds) << std::endl;
        }
    }
    log << std::endl;

    // List all locations
    log << std::endl << "All Locations:" << std::endl;
    LOG_TO_DEBUG("All Locations");
    // Update the longest location name considering all locations
    for (auto& world : worlds)
    {
        for (auto& [id, location] : world->locations)
        {
            longestNameLength = std::max(longestNameLength, location->GetName().length());
        }
    }
    for (auto& world : worlds)
    {
        for (auto& [id, location] : world->locations)
        {
            log << "\t" << GetSpoilerFormatLocation(location.get(), longestNameLength, worlds) << std::endl;
        }
    }
    log << std::endl;

    log.close();
}
