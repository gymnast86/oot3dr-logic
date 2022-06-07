#include "oot3d_world.hpp"
#include "oot3d_item_pool.hpp"
#include "oot3d_entrance.hpp"
#include "../file_functions.hpp"
#include "../file_system_defs.hpp"
#include "../debug.hpp"

#include <iostream>

#define BUILD_ERROR_CHECK(err) if (err != WorldBuildingError::NONE) {return err;}
#define FILE_READ_CHECK(retVal) if (retVal != 0) {return WorldBuildingError::COULD_NOT_LOAD_FILE;}
#define VALID_REQUIREMENT(err, reqStr) if (err != RequirementError::NONE) {std::cout << errorToName(err) << " encountered during \n\"" << reqStr << "\"" << std::endl; return WorldBuildingError::BAD_REQUIREMENT;}
#define YAML_FIELD_CHECK(ref, field, err) if(!ref.has_child(field)) {std::cout << "ERROR: Unable to find field \"" << field << "\" in YAML object" << std::endl; PrintYAML(ref); return err;}
#define VALID_ITEM_CHECK(ref, itemName) if (NameToItemID(itemName) == ItemID::INVALID) {std::replace(itemName.begin(), itemName.end(), '_', ' '); std::cout << "ERROR: Unknown item name \"" << itemName << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_ITEM_TYPE(ref, typeStr) if (NameToOot3dItemType(typeStr) == ItemType::INVALID) {std::cout << "ERROR: Unknown item type \"" << typeStr << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_UINT8_T(ref, getItemIdStr, valueName) if (std::strtoul(getItemIdStr.c_str(), nullptr, 0) > 0xFF) {std::cout << "ERROR: " << valueName << " value is greater than 0xFF in YAML object: " << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_ADVANCEMENT(ref, advancementStr) if (advancementStr != "true" && advancementStr != "false") {std::cout << "ERROR: Unknown advancement value \"" << advancementStr << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_LOCATION_CHECK(ref, locName) if (NameToLocationID(locName) == LocationID::INVALID) {std::cout << "ERROR: Unknown location name \"" << locName << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_LOCATION_VALUE;}
#define VALID_LOCATION_TYPE(ref, typeStr) if (NameToOot3dLocationType(typeStr) == LocationType::INVALID) {std::cout << "ERROR: Unknown location type \"" << typeStr << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_LOCATION_VALUE;}
#define VALID_CHECK_TYPE(ref, checkTypeStr) if (NameToOot3dSpoilerCheckType(checkTypeStr) == SpoilerCollectionCheckType::SPOILER_CHK_INVALID) {std::cout << "Unknown location check_type \"" << checkTypeStr << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_LOCATION_VALUE;}
#define VALID_CHECK_GROUP(ref, checkGroupStr) if (NameToOot3dSpoilerCheckGroup(checkGroupStr) == SpoilerCollectionCheckGroup::GROUP_INVALID) {std::cout << "Unknown location check_group \"" << checkGroupStr << "\" in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_LOCATION_VALUE;}
#define VALID_AREA_CHECK(ref, areaName) if (NameToAreaID(areaName) == AreaID::INVALID) {std::cout << "ERROR: Unknown area name " << areaName << " in YAML object:" << std::endl; PrintYAML(ref); return WorldBuildingError::BAD_AREA_VALUE;}
#define VALID_LOCATION_DEFINITION(ref, locId, locations, name) if (locations.count(locId) == 0) {std::cout << "ERROR: location \"" << name << "\" not defined"; return WorldBuildingError::LOCATION_NOT_DEFINED;}

Oot3dWorld::Oot3dWorld()
{
    worldType = WorldType::Oot3d;
}

Oot3dWorld::Oot3dWorld(const SettingsMap& settings_)
{
    settings = std::move(settings_);
    worldType = WorldType::Oot3d;
}

Oot3dWorld::~Oot3dWorld() = default;

WorldBuildingError CheckValidItemFields(const ryml::NodeRef& item)
{
    YAML_FIELD_CHECK(item, "name", WorldBuildingError::MISSING_ITEM_FIELD);
    YAML_FIELD_CHECK(item, "type", WorldBuildingError::MISSING_ITEM_FIELD);
    YAML_FIELD_CHECK(item, "get_item_id", WorldBuildingError::MISSING_ITEM_FIELD);
    YAML_FIELD_CHECK(item, "advancement", WorldBuildingError::MISSING_ITEM_FIELD);
    return WorldBuildingError::NONE;
}

WorldBuildingError CheckValidLocationFields(const ryml::NodeRef& location)
{
    // Trying to get this to work with iteration was a pain, so we'll just define
    // them all for now
    YAML_FIELD_CHECK(location, "name", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "type", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "scene", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "flag", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "vanilla_item", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "categories", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "check_type", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "check_type_arg1", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "check_type_arg2", WorldBuildingError::MISSING_LOCATION_FIELD);
    YAML_FIELD_CHECK(location, "check_group", WorldBuildingError::MISSING_LOCATION_FIELD);
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::BuildItemTable()
{
    DebugLog("Building Item Table for world " + std::to_string(worldId) + "...");
    std::string itemStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/item_data.yaml", itemStr))

    const ryml::Tree itemsTree = ryml::parse_in_place(ryml::to_substr(itemStr));
    for (const ryml::NodeRef& item : itemsTree.rootref().children())
    {
        // Check that all the appropriate fields exist
        WorldBuildingError err = CheckValidItemFields(item);
        BUILD_ERROR_CHECK(err);

        // Get the field strings
              std::string name = "Oot3d " + SubstrToString(item["name"].val());
        const std::string typeStr = SubstrToString(item["type"].val());
        const std::string getItemIdStr = SubstrToString(item["get_item_id"].val());
        const std::string advancementStr = SubstrToString(item["advancement"].val());

        // Replace spaces in the item name with underscores to get proper ItemIDs
        std::replace(name.begin(), name.end(), ' ', '_');

        // Check each field for proper values
        VALID_ITEM_CHECK(item, name);
        VALID_ITEM_TYPE(item, typeStr);
        VALID_UINT8_T(item, getItemIdStr, "get_item_id");
        VALID_ADVANCEMENT(item, advancementStr);

        // Get the values
        auto itemId = NameToItemID(name);
        ItemType type = NameToOot3dItemType(name);
        uint8_t getItemId = std::strtoul(getItemIdStr.c_str(), nullptr, 0);
        bool advancement = advancementStr == "true";

        // Insert the values into the item table
        itemTable.try_emplace(itemId, itemId, type, getItemId, advancement, this);
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::BuildLocationTable()
{
    DebugLog("Building Location Table for world " + std::to_string(worldId) + "...");
    std::string locationDataStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/location_data.yaml", locationDataStr))

    const ryml::Tree itemsTree = ryml::parse_in_place(ryml::to_substr(locationDataStr));
    for (const ryml::NodeRef& location : itemsTree.rootref().children())
    {
        // Check that all the appropriate fields exist
        WorldBuildingError err = CheckValidLocationFields(location);
        BUILD_ERROR_CHECK(err);

        // Get the field strings
              std::string name = "Oot3d " + SubstrToString(location["name"].val());
        const std::string typeStr = SubstrToString(location["type"].val());
        const std::string sceneStr = SubstrToString(location["scene"].val());
        const std::string flagStr = SubstrToString(location["flag"].val());
              std::string vanillaItemStr = SubstrToString(location["vanilla_item"].val());
        const std::string checkTypeStr = SubstrToString(location["check_type"].val());
        const std::string arg1Str = SubstrToString(location["check_type_arg1"].val());
        const std::string arg2Str = SubstrToString(location["check_type_arg2"].val());
        const std::string checkGroupStr = SubstrToString(location["check_group"].val());

        // Replace spaces in the vanilla item name with underscores to get proper ItemIDs
        std::replace(vanillaItemStr.begin(), vanillaItemStr.end(), ' ', '_');
        // Properly set none value
        if (vanillaItemStr == "None")
        {
            vanillaItemStr = "NONE";
        }
        else
        {
            vanillaItemStr = "Oot3d_" + vanillaItemStr;
        }


        // Check each field for proper values
        VALID_LOCATION_CHECK(location, name);
        VALID_LOCATION_TYPE(location, typeStr);
        VALID_UINT8_T(location, sceneStr, "scene");
        VALID_UINT8_T(location, flagStr, "flag");
        VALID_ITEM_CHECK(location, vanillaItemStr);
        VALID_CHECK_TYPE(location, checkTypeStr);
        VALID_UINT8_T(location, arg1Str, "check_type_arg1");
        VALID_UINT8_T(location, arg2Str, "check_type_arg2");
        VALID_CHECK_GROUP(location, checkGroupStr);

        // Get the values
        auto locationId = NameToLocationID(name);
        auto type = NameToOot3dLocationType(typeStr);
        uint8_t scene = std::strtoul(sceneStr.c_str(), nullptr, 0);
        uint8_t flag = std::strtoul(flagStr.c_str(), nullptr, 0);
        auto vanillaItem = NameToItemID(vanillaItemStr);
        auto checkType = NameToOot3dSpoilerCheckType(checkTypeStr);
        uint8_t arg1 = std::strtoul(arg1Str.c_str(), nullptr, 0);
        uint8_t arg2 = std::strtoul(arg2Str.c_str(), nullptr, 0);
        auto checkGroup = NameToOot3dSpoilerCheckGroup(checkGroupStr);

        // Create the Spoiler Check object
        auto collectionCheck = SpoilerCollectionCheck(checkType, arg1, arg2);
        // Create the location
        auto loc = std::make_unique<Oot3dLocation>(locationId, name, type, scene, flag, vanillaItem, collectionCheck, checkGroup, this);
        // insert the Location into the locations map
        locations.emplace(locationId, std::move(loc));
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::LoadLogicHelpers()
{
    DebugLog("Loading Logic Helpers for world " + std::to_string(worldId) + "...");
    std::string logicHelpersStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/logic_helpers.yaml", logicHelpersStr))

    const ryml::Tree logicHelpersTree = ryml::parse_in_place(ryml::to_substr(logicHelpersStr));
    for (const ryml::NodeRef& logicHelper : logicHelpersTree.rootref().children())
    {
        const std::string helperName = SubstrToString(logicHelper.key());
        const std::string helperStr = SubstrToString(logicHelper.val());
        Requirement helperReq;
        RequirementError err = ParseRequirementString(helperStr, helperReq, logicHelpers, settings, AreaID::NONE, "Oot3d");
        VALID_REQUIREMENT(err, helperStr);
        logicHelpers.emplace(helperName, helperReq);
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::LoadWorldGraph()
{
    DebugLog("Building World Graph for world " + std::to_string(worldId) + "...");
    std::string overworldDataStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/world/overworld_world_graph.yaml", overworldDataStr))

    const ryml::Tree overworldTree = ryml::parse_in_place(ryml::to_substr(overworldDataStr));
    for (const ryml::NodeRef& area : overworldTree.rootref().children())
    {
        const std::string name = SubstrToString(area["region_name"].val());
        VALID_AREA_CHECK(area, name);
        const AreaID areaId = NameToAreaID(name);

        // Create area
        auto newArea = std::make_unique<Oot3dArea>();
        newArea->id = areaId;
        newArea->name = name;
        newArea->world = this;

        if (area.has_child("font_color"))
        {
            const std::string font_color = SubstrToString(area["font_color"].val());
        }
        if (area.has_child("scene"))
        {
            const std::string scene = SubstrToString(area["scene"].val());
        }
        if (area.has_child("hint"))
        {
            const std::string hint = SubstrToString(area["hint"].val());
        }
        if (area.has_child("time_passes"))
        {
            newArea->timePasses = true;
        }
        if (area.has_child("events"))
        {
            for (const ryml::NodeRef& event : area["events"].children())
            {
                // Get field strings
                std::string eventName = "Oot3d " + SubstrToString(event.key());
                const std::string reqStr = SubstrToString(event.val());

                // Check for valid values
                VALID_ITEM_CHECK(area, eventName); // Events are treated as items
                Requirement req;
                RequirementError err = ParseRequirementString(reqStr, req, logicHelpers, settings, areaId, "Oot3d");
                VALID_REQUIREMENT(err, reqStr);

                // Add event to list of events in this area
                auto itemId = NameToItemID(eventName);
                newArea->events.push_back({itemId, req, newArea.get()});
            }
        }
        if (area.has_child("locations"))
        {
            for (const ryml::NodeRef& location : area["locations"].children())
            {
                // Get field strings
                const std::string locationName = "Oot3d " + SubstrToString(location.key());
                const std::string reqStr = SubstrToString(location.val());

                // Check for valid values
                VALID_LOCATION_CHECK(area, locationName);
                Requirement req;
                RequirementError err = ParseRequirementString(reqStr, req, logicHelpers, settings, areaId, "Oot3d");
                VALID_REQUIREMENT(err, reqStr);

                auto locationId = NameToLocationID(locationName);
                VALID_LOCATION_DEFINITION(area, locationId, locations, locationName);
                // Add location to list of locations in area
                auto locPtr = locations[locationId].get();
                newArea->locations.push_back({locPtr, req, newArea.get()});
            }
        }
        if (area.has_child("exits"))
        {
            for (const ryml::NodeRef& exit : area["exits"].children())
            {
                // Get field strings
                const std::string exitName = "Oot3d " + SubstrToString(exit.key());
                const std::string reqStr = SubstrToString(exit.val());

                // Check for valid values
                VALID_AREA_CHECK(area, exitName);
                Requirement req;
                RequirementError err = ParseRequirementString(reqStr, req, logicHelpers, settings, areaId, "Oot3d");
                VALID_REQUIREMENT(err, reqStr);

                // Add the exit to the list of exits in area
                auto exitAreaId = NameToAreaID(exitName);
                auto newExit = std::make_unique<Oot3dEntrance>(newArea->id, exitAreaId, req, this);
                newArea->exits.push_back(std::move(newExit));
            }
        }

        areas.emplace(areaId, std::move(newArea));
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::BuildItemPools()
{
    auto itemIdPool = GenerateOot3dItemPool(settings);

    for (const auto& itemId : itemIdPool)
    {
        itemPool.push_back(itemTable[itemId]);
    }

    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::Build()
{
    WorldBuildingError err;
    err = BuildItemTable();
    BUILD_ERROR_CHECK(err);
    err = BuildLocationTable();
    BUILD_ERROR_CHECK(err);
    err = LoadLogicHelpers();
    BUILD_ERROR_CHECK(err);
    err = LoadWorldGraph();
    BUILD_ERROR_CHECK(err);
    err = BuildItemPools();
    BUILD_ERROR_CHECK(err);
    err = CacheAgeTimeRequirements();
    BUILD_ERROR_CHECK(err);

    locations[LocationID::Oot3dMasterSwordPedestal]->currentItem = Item(ItemID::Oot3dMasterSword, this);
    locations[LocationID::Oot3dBigPoeKill]->currentItem = Item(ItemID::Oot3dBigPoe, this);
    locations[LocationID::Oot3dPierre]->currentItem = Item(ItemID::Oot3dScarecrowSong, this);
    locations[LocationID::Oot3dBugRock]->currentItem = Item(ItemID::Oot3dBugs, this);
    locations[LocationID::Oot3dMarketBombchuBowlingBombchus]->currentItem = Item(ItemID::Oot3dBombchuDrop, this);

    return WorldBuildingError::NONE;
}

std::string Oot3dWorld::GetTypeString() const
{
    return "Oot3d";
}
