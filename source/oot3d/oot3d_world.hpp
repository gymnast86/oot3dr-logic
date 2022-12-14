#pragma once

#include "oot3d_item.hpp"
#include "oot3d_location.hpp"
#include "oot3d_area.hpp"

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
    EvalSuccess EvaluateEventRequirement(Search* search, Event* event) override;
    EvalSuccess EvaluateLocationRequirement(Search* search, LocationAccess* locAccess) override;
    EvalSuccess EvaluateExitRequirement(Search* search, Entrance* exit) override;
    std::string GetTypeString() const override;

    void ExpandToDMasterSword(Search* search);

    std::unordered_map<ItemID, Oot3dItem> itemTable;
    std::unordered_map<Entrance*, uint8_t> possibleExitAgeTimes;

private:

    WorldBuildingError BuildItemTable();
    WorldBuildingError BuildLocationTable();
    WorldBuildingError LoadLogicHelpers();
    WorldBuildingError LoadWorldGraph();
    WorldBuildingError BuildItemPools();
    WorldBuildingError CacheAgeTimeRequirements();
    WorldBuildingError PlaceVanillaItems();

    bool EvaluateRequirementWithAgeTime(const Requirement& req, Search* search, uint8_t ageTime);
    void ExpandTimePassToD(uint8_t connectedAreaAgeTime, uint8_t day, uint8_t night, Search* search, Entrance* exit);
    void ExpandToDAreas(Search* search, uint8_t ageTimeToExpand, const AreaID& startingArea = AreaID::Root);

};
