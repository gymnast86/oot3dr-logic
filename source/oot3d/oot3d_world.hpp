#pragma once

#include "../world.hpp"
#include "../requirement.hpp"
#include "oot3d_item.hpp"

#include <unordered_map>

class Oot3dWorld : public World {
public:

    Oot3dWorld();
    Oot3dWorld(const SettingsMap& settings_);
    ~Oot3dWorld();

    WorldBuildingError Build() override;

    static std::unordered_map<ItemID, Oot3dItem> itemTable;

private:

    WorldBuildingError BuildItemTable();
    WorldBuildingError BuildLocationTable();
    WorldBuildingError LoadLogicHelpers();
    WorldBuildingError LoadWorldGraph();

};
