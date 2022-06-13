
#pragma once

#include "world.hpp"
#include <string>
#include <vector>
#include <list>
#include <memory>

enum class SearchMode
{
    INVALID = 0,
    AccessibleLocations,
    GameBeatable,
    AllLocationsReachable,
    GeneratePlaythrough,
};

class Search
{
public:
    Search();
    Search(const SearchMode& searchMode_, WorldPool* worlds_, const ItemPool& items, const int worldToSearch_ = -1);
    ~Search();

    void FindLocations(int worldToSearch = -1);
    void DumpSearchGraph(size_t worldId = 0, const std::string filename = "World0");
private:
    void SetStartingProperties(World* world);
    void Explore(Area* area);
public:

    SearchMode searchMode = SearchMode::AccessibleLocations;
    WorldPool* worlds = nullptr;
    int worldToSearch = -1;
    int sphere = 0;
    ItemMultiSet ownedItems = {};
    LocationSet accessibleLocations = {};
    std::list<Event*> eventsToTry = {};
    std::list<Entrance*> exitsToTry = {};
    std::list<LocationAccess*> locationsToTry = {};
    std::unordered_set<Location*> visitedLocations = {};
    std::unordered_set<Area*> visitedAreas = {};
    std::unordered_set<Entrance*> successfulExits = {};
    std::unordered_set<Entrance*> partiallySuccessfulExits = {};

    // Oot3D Specific Stuff
    // areaTime maps an Area Pointer to what times of day it has
    std::unordered_map<Area*, uint8_t> areaTime = {};

    // Playthrough spheres
    std::list<std::list<Location*>> playthroughSpheres = {};
    std::list<std::list<Entrance*>> entranceSpheres = {};

    //Search& operator=(const Search& rhs) {};
};

LocationPool GetAccessibleLocations(WorldPool& worlds, ItemPool& items, LocationPool& allowedLocations, int worldToSearch = -1);
