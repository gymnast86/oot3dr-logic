#pragma once

#include "oot3d_item.hpp"
#include "oot3d_location.hpp"
#include "oot3d_area.hpp"
#include "oot3d_dungeon.hpp"

#include "../world.hpp"
#include "../requirement.hpp"
#include "../fill.hpp"

#include <unordered_map>

#define OOT3D_LOCATIONS_LAMDA(func) [](Location* loc) {auto location = ((Oot3dLocation*)loc); func}

class Search;
class Oot3dWorld : public World {
public:

    Oot3dWorld();
    Oot3dWorld(const SettingsMap& settings_, int numWorlds);
    ~Oot3dWorld();

    WorldBuildingError Build() override;
    EvalSuccess EvaluateEventRequirement(Search* search, Event* event) override;
    EvalSuccess EvaluateLocationRequirement(Search* search, LocationAccess* locAccess) override;
    EvalSuccess EvaluateExitRequirement(Search* search, Entrance* exit) override;
    std::string GetTypeString() const override;

    void ExpandToDTimeTravel(Search* search);

    std::map<std::string, std::unique_ptr<Oot3dDungeon>> dungeons = {};
    std::unordered_map<ItemID, Oot3dItem> itemTable = {};
    std::unordered_map<Entrance*, uint8_t> possibleExitAgeTimes = {};
    std::vector<uint8_t> iceTrapModels = {};

private:

    // oot3d_world.cpp
    WorldBuildingError CreateDungeons();
    WorldBuildingError BuildItemTable();
    WorldBuildingError BuildLocationTable();
    WorldBuildingError LoadLogicHelpers();
    WorldBuildingError LoadWorldGraph();
    WorldBuildingError BuildItemPools();
    WorldBuildingError CacheAgeTimeRequirements();

    // oot3d_world_fill.cpp
    WorldBuildingError PlaceHardcodedItems();
    WorldBuildingError FillShopItems();
    WorldBuildingError FillOwnDungeonItems();


    // oot3d_world_logic.cpp
    bool EvaluateRequirementWithAgeTime(const Requirement& req, Search* search, uint8_t ageTime);
    void ExpandTimePassToD(uint8_t connectedAreaAgeTime, uint8_t day, uint8_t night, Search* search, Entrance* exit);
    void ExpandToDAreas(Search* search, uint8_t ageTimeToExpand, const AreaID& startingArea = AreaID::Root);

    // oot3d_world_item_pool.cpp
    ItemID GetJunkItem();
    ItemID GetPendingJunkItem();
    void ReduceItemMaximum(ItemIDPool& mainItemPool, const ItemID& itemToReplace, int max);
    WorldBuildingError GenerateOot3dItemPool();
    WorldBuildingError GenerateOot3dStartingInventory();
};
