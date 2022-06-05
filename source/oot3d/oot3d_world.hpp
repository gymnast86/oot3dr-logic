#pragma once

#include "oot3d_item.hpp"
#include "oot3d_location.hpp"
#include "oot3d_area.hpp"
#include "oot3d_logic.hpp"
#include "oot3d_world_graph.hpp"

#include "../world.hpp"
#include "../requirement.hpp"

#include <unordered_map>

class Search;
class Oot3dWorld : public World {
public:

    Oot3dWorld();
    Oot3dWorld(const SettingsMap& settings_);
    ~Oot3dWorld();

    WorldBuildingError Build() override;
    bool EvaluateRequirement(const RequirementFn& req, Search* search, void* object, EvaluateType evalType = EvaluateType::NONE) override;
    void ExpandAreaVariables() override;
    std::string GetTypeString() const override;

    void ExpandToDMasterSword(Search* search, LocationAccess* locAccess);

    std::unordered_map<ItemID, Oot3dItem> itemTable;
    std::unordered_map<Entrance*, uint8_t> allowedExitAgeTimes;

    Oot3dLogic* logic;

private:

    WorldBuildingError BuildItemTable();
    WorldBuildingError BuildLocationTable();
    WorldBuildingError LoadLogicHelpers();
    WorldBuildingError LoadWorldGraph();
    WorldBuildingError BuildItemPools();
    WorldBuildingError ProcessArea(AreaStruct areaStruct);
    WorldBuildingError InitWorldGraph();
    WorldBuildingError CacheAgeTimeRequirements();

    void ExpandTimePassToD(uint8_t connectedAreaAgeTime, uint8_t day, uint8_t night, Search* search, Entrance* exit);
    void ExpandToDAreas(Search* search, uint8_t ageTimeToExpand);

};
