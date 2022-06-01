#include "generate.hpp"
#include "timing.hpp"
#include "fill.hpp"
#include "random.hpp"
#include "oot3d/oot3d_world.hpp"

#include <unordered_map>
#include <array>
#include <vector>
#include <unordered_set>

void GenerateRandomizer()
{


    Random_Init(1); // This eventually has to go where deciding random settings

    SettingsMap settings1 = {
        {"world_type", "oot3d"},
        {"starting_age", "child"},
        {"player_num", "1"},
        {"bombchus_in_logic", "On"},
        {"logic_rules", "glitchless"},
        {"open_forest", "open"},
        {"gerudo_fortress", "normal"},
        {"damage_multiplier", "1x"},
        {"hints", "none"},
        {"plant_beans", "Off"},
        {"bridge", "open"},
        {"lacs_condition", "vanilla"},
        {"shuffle_ganon_bosskey", "medallions"},
        {"bridge_tokens", "10"},
        {"bridge_stones", "3"},
        {"bridge_medallions", "6"},
        {"bridge_rewards", "9"},
        {"lacs_tokens", "10"},
        {"lacs_stones", "3"},
        {"lacs_medallions", "6"},
        {"lacs_rewards", "9"},
        {"ganon_bosskey_stones", "3"},
        {"ganon_bosskey_tokens", "10"},
        {"ganon_bosskey_rewards", "9"},
        {"ganon_bosskey_medallions", "6"},
        {"had_night_start", "Off"},
        {"complete_mask_quest", "Off"},
        {"entrance_shuffle", "On"},
        {"shuffle_scrubs", "off"},
        {"shuffle_weird_egg", "Off"},
        {"shuffle_gerudo_token", "Off"},
        {"shuffle_chest_game", "off"},
        {"shuffle_dungeon_entrances", "On"},
        {"shuffle_overworld_entrances", "On"},
        {"free_scarecrow", "Off"},
        {"big_poe_count", "2"},
        {"zora_fountain", "normal"},
        {"open_kakariko", "open"},
        {"open_door_of_time", "open"},
        {"skip_child_zelda", "Off"},
        {"night_gs_expect_suns", "Off"},

        {"logic_grottos_without_agony", "Off"},
        {"logic_gerudo_kitchen", "Off"},
        {"logic_adult_kokiri_gs", "On"},
        {"logic_lost_woods_gs_bean", "Off"},
        {"logic_lost_woods_bridge", "Off"},
        {"logic_lab_wall_gs", "On"},
        {"logic_lab_diving", "Off"},
        {"logic_wasteland_crossing", "Off"},
        {"logic_lens_wasteland", "Off"},
        {"logic_reverse_wasteland", "Off"},
        {"logic_colossus_gs", "Off"},
        {"logic_kakariko_tower_gs", "On"},
        {"logic_kakariko_rooftop_gs", "On"},
        {"logic_man_on_roof", "On"},
        {"logic_windmill_poh", "On"},
        {"logic_graveyard_poh", "On"},
        {"logic_child_dampe_race_poh", "On"},
        {"logic_shadow_fire_arrow_entry", "Off"},
        {"logic_visible_collisions", "Off"},
        {"logic_dmt_bombable", "On"},
        {"logic_dmt_soil_gs", "Off"},
        {"logic_dmt_climb_hovers", "Off"},
        {"logic_link_goron_dins", "On"},
        {"logic_goron_city_leftmost", "Off"},
        {"logic_goron_city_pot_with_strength", "On"},
        {"logic_goron_city_pot", "On"},
        {"logic_child_rolling_with_strength", "On"},
        {"logic_goron_grotto", "Off"},
        {"logic_crater_upper_to_lower", "On"},
        {"logic_fewer_tunic_requirements", "On"},
        {"logic_crater_bean_poh_with_hovers", "On"},
        {"logic_zora_river_lower", "Off"},
        {"logic_zora_river_upper", "On"},
        {"logic_domain_gs", "On"},
        {"logic_king_zora_skip", "On"},
        {"logic_castle_storms_gs", "On"},
    };
    std::vector<SettingsMap> settingsVector = {settings1, settings1, settings1, settings1};
    WorldPool worlds;
    worlds.resize(settingsVector.size());

    std::cout << "Building Worlds..." << std::endl;
    for (size_t i = 0; i < settingsVector.size(); i++)
    {
        auto& settings = settingsVector[i];
        if (settings["world_type"] == "oot3d")
        {
            //std::cout << "Building oot3d world..." << std::endl;
            auto world = std::make_unique<Oot3dWorld>(settings);
            worlds[i] = std::move(world);
        }
        else if (settings["world_type"] == "mm3d")
        {
            // Make MM3D world
        }
        else
        {
            std::cout << "ERROR: No world type defined in settings for world " << std::to_string(i) << std::endl;
            return;
        }
        worlds[i]->worldId = i;
        if (worlds[i]->Build() != WorldBuildingError::NONE)
        {
            std::cout << " when building world " << std::to_string(i) << " of type " << settings["world_type"] << std::endl;
            return;
        }
        // std::cout << "Done building world " << std::to_string(i) << std::endl;
    }

    StartTiming();
    std::cout << "Filling Worlds..." << std::endl;
    FillError err = FillWorlds(worlds);


    EndTiming();
    PrintTiming();
    DebugLog("Total Evals: " + std::to_string(TotalWorldEvals(worlds)));
}

void BKey()
{
  // SettingsMap settings = {
  //     {"world_type", "oot3d"},
  //     {"bombchus_in_logic", "On"},
  //     {"logic_rules", "glitchless"},
  //     {"open_forest", "open"},
  //     {"gerudo_fortress", "normal"},
  //     {"damage_multiplier", "1x"},
  //     {"hints", "none"},
  //     {"plant_beans", "Off"},
  //     {"bridge", "open"},
  //     {"lacs_condition", "vanilla"},
  //     {"shuffle_ganon_bosskey", "medallions"},
  //     {"bridge_tokens", "10"},
  //     {"bridge_stones", "3"},
  //     {"bridge_medallions", "6"},
  //     {"bridge_rewards", "9"},
  //     {"lacs_tokens", "10"},
  //     {"lacs_stones", "3"},
  //     {"lacs_medallions", "6"},
  //     {"lacs_rewards", "9"},
  //     {"ganon_bosskey_stones", "3"},
  //     {"ganon_bosskey_tokens", "10"},
  //     {"ganon_bosskey_rewards", "9"},
  //     {"ganon_bosskey_medallions", "6"},
  //     {"had_night_start", "Off"},
  //     {"entrance_shuffle", "On"},
  //     {"shuffle_scrubs", "off"},
  //     {"shuffle_weird_egg", "Off"},
  //     {"shuffle_dungeon_entrances", "On"},
  //     {"shuffle_overworld_entrances", "On"},
  //     {"free_scarecrow", "Off"},
  //     {"big_poe_count", "2"},
  //     {"zora_fountain", "normal"},
  //
  //     {"logic_grottos_without_agony", "Off"},
  //     {"logic_gerudo_kitchen", "Off"},
  //     {"logic_adult_kokiri_gs", "On"},
  //     {"logic_lost_woods_gs_bean", "Off"},
  //     {"logic_lab_wall_gs", "On"},
  //     {"logic_lab_diving", "Off"},
  //     {"logic_colossus_gs", "Off"},
  //     {"logic_kakariko_tower_gs", "On"},
  //     {"logic_windmill_poh", "On"},
  //     {"logic_graveyard_poh", "On"},
  //     {"logic_child_dampe_race_poh", "On"},
  //     {"logic_shadow_fire_arrow_entry", "Off"},
  //     {"logic_visible_collisions", "Off"},
  //     {"logic_dmt_bombable", "On"},
  //     {"logic_dmt_soil_gs", "Off"},
  //     {"logic_dmt_climb_hovers", "Off"},
  //     {"logic_link_goron_dins", "On"},
  //     {"logic_goron_city_leftmost", "Off"},
  //     {"logic_goron_city_pot_with_strength", "On"},
  //     {"logic_goron_city_pot", "On"},
  //     {"logic_child_rolling_with_strength", "On"},
  //     {"logic_goron_grotto", "Off"},
  //     {"logic_crater_upper_to_lower", "On"},
  //     {"logic_fewer_tunic_requirements", "On"},
  //     {"logic_crater_bean_poh_with_hovers", "On"},
  //     {"logic_zora_river_lower", "Off"},
  //     {"logic_zora_river_upper", "On"},
  //     {"logic_domain_gs", "On"},
  //     {"logic_king_zora_skip", "On"},
  //     {"logic_castle_storms_gs", "On"},
  // };
  //
  // WorldPool worlds;
  //
  // if (settings["world_type"] == "oot3d")
  // {
  //     auto world = std::make_unique<Oot3dWorld>();
  //     worlds.push_back(std::move(world));
  // }
  // else
  // {
  //     std::cout << "ERROR: No world type defined in settings" << std::endl;
  //     return;
  // }
  //
  // worlds.back()->Build();
}
