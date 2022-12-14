
#pragma once

#include "world.hpp"
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <set>
#include <queue>

enum class SearchMode
{
    INVALID = 0,
    AccessibleLocations,
    GameBeatable,
    AllLocationsReachable,
    GeneratePlaythrough,
};

const ItemPool emptyItemPool = {};

struct LocationAccessComparator
{
    bool operator()(const LocationAccess * lhs, const LocationAccess * rhs) const
    {
        return *(lhs->location) < *(rhs->location);
    }
};

class Search
{
public:
    Search();
    Search(const SearchMode& searchMode_, WorldPool* worlds_, const ItemPool& items = emptyItemPool, const int worldToSearch_ = -1);
    ~Search();

    void SearchWorlds(int tempWorldToSearch = -1, bool oneIteration = false);
    void RemoveEmptySpheres();
    void DumpSearchGraph(size_t worldId = 0, const std::string filename = "World0");

private:
    void SetStartingProperties(World* world);

    void ProcessEvents();
    void ProcessExits();
    void ProcessLocation(Location* location);
    void ProcessLocations(std::set<LocationAccess*, LocationAccessComparator>& itemLocations);
    void Explore(Area* area);
public:

    SearchMode searchMode = SearchMode::AccessibleLocations;
    WorldPool* worlds = nullptr;
    int worldToSearch = -1;
    int sphereNum = 0;
    bool newThingsFound = false;
    bool isBeatable = false;
    ItemMultiSet ownedItems = {};
    ItemMultiSet sphereItems = {};
    std::list<Event*> eventsToTry = {};
    std::list<Entrance*> exitsToTry = {};
    std::set<Location*, PointerComparator<Location>> visitedLocations = {};
    std::unordered_set<Area*> visitedAreas = {};
    std::unordered_set<Entrance*> successfulExits = {};
    std::unordered_set<Entrance*> partiallySuccessfulExits = {};

    // Oot3D Specific Stuff
    // areaTime maps an Area Pointer to what times of day it has
    std::unordered_map<Area*, uint8_t> areaTime = {};

    // Playthrough spheres
    std::list<std::set<Location*, PointerComparator<Location>>> playthroughSpheres = {};
    std::list<std::list<Entrance*>> entranceSpheres = {};

    //Search& operator=(const Search& rhs) {};
};

bool GameBeatable(WorldPool& worlds);
void GeneratePlaythrough(WorldPool& worlds);
