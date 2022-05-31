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
    bool EvaluateRequirement(const Requirement& req, Search* search, void* object, EvaluateType evalType = EvaluateType::NONE) override;
    void ExpandAreaVariables() override;
    std::string GetTypeString() const override;

    void ExpandToDMasterSword(Search* search, LocationAccess* locAccess);

    std::unordered_map<ItemID, Oot3dItem> itemTable;
    std::unordered_map<Entrance*, uint8_t> allowedExitAgeTimes;

private:

    WorldBuildingError BuildItemTable();
    WorldBuildingError BuildLocationTable();
    WorldBuildingError LoadLogicHelpers();
    WorldBuildingError LoadWorldGraph();
    WorldBuildingError BuildItemPools();
    WorldBuildingError CacheAgeTimeRequirements();

    // Logic Helper functions
    bool IsMagicArrow(const ItemID& itemId);
    bool IsMagicItem(const ItemID& itemId);
    bool IsChildItem(const ItemID& itemId);
    bool IsAdultItem(const ItemID& itemId);
    bool CanUse(const ItemID& itemId, const Requirement& req, Search* search, void* object, EvaluateType evalType, uint8_t ageTime);

    bool EvaluateRequirementWithAgeTime(const Requirement& req, Search* search, void* object, EvaluateType evalType, uint8_t ageTime);
    void ExpandTimePassToD(uint8_t connectedAreaAgeTime, uint8_t day, uint8_t night, Search* search, Entrance* exit);
    void ExpandToDAreas(Search* search, uint8_t ageTimeToExpand);

};
