#include "oot3d_world.hpp"
#include "../file_functions.hpp"
#include "../file_system_defs.hpp"
#include "../debug.hpp"

#include <iostream>

#define BUILD_ERROR_CHECK(err) if (err != WorldBuildingError::NONE) {return err;}
#define FILE_READ_CHECK(retVal) if (retVal != 0) {return WorldBuildingError::COULD_NOT_LOAD_FILE;}
#define YAML_FIELD_CHECK(ref, field, err) if(!ref.has_child(field)) {std::cout << "ERROR: Unable to find field \"" << field << "\" in YAML object" << std::endl; PrintObjectFields(ref); return err;}
#define VALID_ITEM_CHECK(ref, itemName) if (NameToItemID(itemName) == ItemID::INVALID) {std::replace(itemName.begin(), itemName.end(), '_', ' '); std::cout << "ERROR: Unknown item name \"" << itemName << "\" in YAML object:" << std::endl; PrintObjectFields(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_ITEM_TYPE(ref, typeStr) if (NameToOot3dItemType(typeStr) == ItemType::INVALID) {std::cout << "ERROR: Unknown item type \"" << typeStr << "\" in YAML object:" << std::endl; PrintObjectFields(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_GET_ITEM_ID(ref, getItemIdStr) if (std::strtoul(getItemIdStr.c_str(), nullptr, 0) > 0xFF) {std::cout << "ERROR: Get Item ID value is greater than 0xFF in YAML object: " << std::endl; PrintObjectFields(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_ADVANCEMENT(ref, advancementStr) if (advancementStr != "true" && advancementStr != "false") {std::cout << "ERROR: Unknown advancement value \"" << advancementStr << "\" in YAML object:" << std::endl; PrintObjectFields(ref); return WorldBuildingError::BAD_ITEM_VALUE;}
#define VALID_LOCATION_CHECK(ref, locName) if (NameToLocationID(locName) == LocationID::INVALID) {std::cout << "ERROR: Unknown location name \"" << locName << "\" in YAML object:" << std::endl; PrintObjectFields(ref); return WorldBuildingError::BAD_LOCATION_VALUE;}

std::unordered_map<ItemID, Oot3dItem> Oot3dWorld::itemTable;

Oot3dWorld::Oot3dWorld() {}

Oot3dWorld::Oot3dWorld(const SettingsMap& settings_)
{
    settings = std::move(settings_);
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
    std::cout << "Building Item Table..." << std::endl;
    std::string itemStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/item_data.yaml", itemStr))

    const ryml::Tree itemsTree = ryml::parse_in_place(ryml::to_substr(itemStr));
    for (const ryml::NodeRef& item : itemsTree.rootref().children())
    {
        // Check that all the appropriate fields exist
        WorldBuildingError err = CheckValidItemFields(item);
        BUILD_ERROR_CHECK(err);

              std::string name = SubstrToString(item["name"].val());
        const std::string typeStr = SubstrToString(item["type"].val());
        const std::string getItemIdStr = SubstrToString(item["get_item_id"].val());
        const std::string advancementStr = SubstrToString(item["advancement"].val());

        // Replace spaces in the item name with underscores to get proper ItemIDs
        std::replace(name.begin(), name.end(), ' ', '_');

        // Check each field for proper values
        VALID_ITEM_CHECK(item, name);
        VALID_ITEM_TYPE(item, typeStr);
        VALID_GET_ITEM_ID(item, getItemIdStr);
        VALID_ADVANCEMENT(item, advancementStr);

        auto itemId = NameToItemID(name);
        ItemType type = NameToOot3dItemType(name);
        uint8_t getItemId = std::strtoul(getItemIdStr.c_str(), nullptr, 0);
        bool advancement = advancementStr == "true";

        itemTable.try_emplace(itemId, name, type, getItemId, advancement, this);
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::BuildLocationTable()
{
    std::cout << "Building Location Table..." << std::endl;
    std::string locationStr;
    FILE_READ_CHECK(GetFileContents(ROMFS"/oot3d/location_data.yaml", locationStr))

    const ryml::Tree itemsTree = ryml::parse_in_place(ryml::to_substr(locationStr));
    for (const ryml::NodeRef& location : itemsTree.rootref().children())
    {
        // Check that all the appropriate fields exist
        WorldBuildingError err = CheckValidLocationFields(location);
        BUILD_ERROR_CHECK(err);

        const std::string name = SubstrToString(location["name"].val());
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

        // Check each field for proper values
        VALID_LOCATION_CHECK(location, name);
        VALID_ITEM_CHECK(location, vanillaItemStr);

        //
        // auto itemId = NameToItemID(name);
        // ItemType type = NameToOot3dItemType(name);
        // uint8_t getItemId = std::strtoul(getItemIdStr.c_str(), nullptr, 0);
        // bool advancement = advancementStr == "true";
        //
        // itemTable.try_emplace(itemId, name, type, getItemId, advancement, this);
    }
    return WorldBuildingError::NONE;
}


WorldBuildingError Oot3dWorld::LoadLogicHelpers()
{
    std::cout << "Loading Logic Helpers..." << std::endl;
    std::string logicHelpersStr;
    if (GetFileContents(ROMFS"/oot3d/logic_helpers.yaml", logicHelpersStr))
    {
        std::cout << "Error loading file" << std::endl;
        return WorldBuildingError::COULD_NOT_LOAD_FILE;
    }
    else
    {
        const ryml::Tree logicHelpersTree = ryml::parse_in_place(ryml::to_substr(logicHelpersStr));
        for (const ryml::NodeRef& logicHelper : logicHelpersTree.rootref().children())
        {
            const std::string helperName = SubstrToString(logicHelper.key());
            const std::string helperStr = SubstrToString(logicHelper.val());
            Requirement helperReq;
            RequirementError err = ParseRequirementString(helperStr, helperReq, logicHelpers, settings);
            if (err != RequirementError::NONE)
            {
                std::cout << errorToName(err) << " encountered during \n\"" << helperStr << "\"" << std::endl;
                return WorldBuildingError::BAD_REQUIREMENT;
            }
            logicHelpers.emplace(helperName, helperReq);
        }
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::LoadWorldGraph()
{
    std::cout << "Building World Graph..." << std::endl;
    std::string overworldStr;
    if (GetFileContents(ROMFS"/oot3d/overworld.yaml", overworldStr))
    {
        std::cout << "Error loading file" << std::endl;
    }
    else
    {
        const ryml::Tree overworldTree = ryml::parse_in_place(ryml::to_substr(overworldStr));
        for (const ryml::NodeRef& object : overworldTree.rootref().children())
        {
            const std::string name = SubstrToString(object["region_name"].val());
            Area newArea;
            newArea.name = name;
            newArea.id = NameToAreaID(name);
            if (object.has_child("font_color"))
            {
                const std::string font_color = SubstrToString(object["font_color"].val());
            }
            if (object.has_child("scene"))
            {
                const std::string scene = SubstrToString(object["scene"].val());
            }
            if (object.has_child("hint"))
            {
                const std::string hint = SubstrToString(object["hint"].val());
            }
            if (object.has_child("events"))
            {
                for (const ryml::NodeRef& event : object["events"].children())
                {
                    const std::string eventName = SubstrToString(event.key());
                    const std::string reqStr = SubstrToString(event.val());
                }
            }
            if (object.has_child("locations"))
            {
                for (const ryml::NodeRef& location : object["locations"].children())
                {
                    const std::string locationName = SubstrToString(location.key());
                    const std::string reqStr = SubstrToString(location.val());

                    // location name access
                    // auto locationId = NameToLocationID(locationName);

                    //world.locations.emplace_back(locationId, Location());


                    Requirement req;
                    RequirementError err = ParseRequirementString(reqStr, req, logicHelpers, settings);
                    if (err != RequirementError::NONE)
                    {
                        std::cout << errorToName(err) << " encountered during \n\"" << reqStr << "\"" << std::endl;
                        return WorldBuildingError::BAD_REQUIREMENT;
                    }
                }
            }
            if (object.has_child("exits"))
            {
                for (const ryml::NodeRef& exit : object["exits"].children())
                {
                    const std::string exitName = SubstrToString(exit.key());
                    const std::string requirement = SubstrToString(exit.val());
                }
            }
        }
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
    return WorldBuildingError::NONE;
}
