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
        {"shuffle_dungeon_entrances", "off"},
        {"shuffle_overworld_entrances", "Off"},
        {"small_keys", "vanilla"},
        {"free_scarecrow", "Off"},
        {"big_poe_count", "2"},
        {"zora_fountain", "normal"},
        {"open_kakariko", "open"},
        {"open_door_of_time", "open"},
        {"skip_child_zelda", "Off"},
        {"night_gs_expect_suns", "Off"},
        {"deku_tree_dungeon_mode", "vanilla"},
        {"dodongos_cavern_dungeon_mode", "vanilla"},
        {"jabu_jabus_belly_dungeon_mode", "vanilla"},
        {"forest_temple_dungeon_mode", "vanilla"},
        {"fire_temple_dungeon_mode", "vanilla"},
        {"water_temple_dungeon_mode", "vanilla"},
        {"spirit_temple_dungeon_mode", "vanilla"},
        {"shadow_temple_dungeon_mode", "vanilla"},
        {"bottom_of_the_well_dungeon_mode", "vanilla"},
        {"ice_cavern_dungeon_mode", "vanilla"},
        {"gerudo_training_ground_dungeon_mode", "vanilla"},
        {"ganons_castle_dungeon_mode", "vanilla"},
        {"forest_trial_mode", "not_skipped"},
        {"fire_trial_mode", "not_skipped"},
        {"water_trial_mode", "not_skipped"},
        {"shadow_trial_mode", "not_skipped"},
        {"spirit_trial_mode", "not_skipped"},
        {"light_trial_mode", "not_skipped"},

        {"logic_grottos_without_agony", "Off"},
        {"logic_gv_hammer_chest", "Off"},
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
        {"logic_windmill_poh_hookshot", "Off"},
        {"logic_kakariko_tower_gs", "On"},
        {"logic_kakariko_rooftop_gs", "On"},
        {"logic_man_on_roof", "On"},
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
        {"logic_zf_great_fairy", "Off"},
        {"logic_castle_storms_gs", "On"},
        {"logic_deku_basement_gs", "Off"},
        {"logic_deku_b1_skip", "Off"},
        {"logic_deku_b1_webs_with_bow", "Off"},
        {"logic_deku_mq_compass_gs", "Off"},
        {"logic_deku_mq_log", "Off"},
        {"logic_dc_scarecrow_gs", "Off"},
        {"logic_dc_staircase", "Off"},
        {"logic_dc_jump", "Off"},
        {"logic_dc_slingshot_skip", "Off"},
        {"logic_dc_mq_child_bombs", "Off"},
        {"logic_dc_mq_eyes", "Off"},
        {"logic_dc_mq_child_back", "Off"},
        {"logic_jabu_boss_gs_adult", "Off"},
        {"logic_jabu_scrub_jump_dive", "Off"},
        {"logic_jabu_mq_sot_gs", "Off"},
        {"logic_lens_jabu_mq", "Off"},
        {"logic_forest_outdoor_east_gs", "Off"},
        {"logic_forest_door_frame", "Off"},
        {"logic_forest_outside_backdoor", "Off"},
        {"logic_forest_mq_block_puzzle", "Off"},
        {"logic_forest_mq_hallway_switch_jumpslash", "Off"},
        {"logic_forest_mq_hallway_switch_hookshot", "Off"},
        {"logic_forest_mq_well_swim", "Off"},
        {"logic_forest_outdoors_ledge", "Off"},
        {"logic_fire_boss_door_jump", "Off"},
        {"logic_fire_song_of_time", "Off"},
        {"logic_fire_strength", "Off"},
        {"logic_fire_scarecrow", "Off"},
        {"logic_fire_flame_maze", "Off"},
        {"logic_fire_mq_near_boss", "Off"},
        {"logic_fire_boss_door_jump", "Off"},
        {"logic_fire_mq_bk_chest", "Off"},
        {"logic_fire_mq_blocked_chest", "Off"},
        {"logic_fire_mq_climb", "Off"},
        {"logic_fire_mq_maze_side_room", "Off"},
        {"logic_fire_mq_maze_hovers", "Off"},
        {"logic_fire_mq_maze_jump", "Off"},
        {"logic_fire_mq_flame_maze", "Off"},
        {"logic_fire_mq_above_maze_gs", "Off"},
        {"logic_water_temple_torch_longshot", "Off"},
        {"logic_water_temple_upper_boost", "Off"},
        {"logic_water_central_bow", "Off"},
        {"logic_water_cracked_wall_hovers", "Off"},
        {"logic_water_cracked_wall_nothing", "Off"},
        {"logic_water_boss_key_region", "Off"},
        {"logic_water_north_basement_ledge_jump", "Off"},
        {"logic_water_bk_jump_dive", "Off"},
        {"logic_water_dragon_adult", "Off"},
        {"logic_water_dragon_jump_dive", "Off"},
        {"logic_water_central_gs_fw", "Off"},
        {"logic_water_falling_platform_gs", "Off"},
        {"logic_water_river_gs", "Off"},
        {"logic_water_mq_central_pillar", "Off"},
        {"logic_water_dragon_jump_dive", "Off"},
        {"logic_water_north_basement_ledge_jump", "Off"},
        {"logic_water_mq_locked_gs", "Off"},
        {"logic_spirit_child_bombchu", "Off"},
        {"logic_spirit_lower_adult_switch", "Off"},
        {"logic_spirit_map_chest", "Off"},
        {"logic_spirit_sun_chest", "Off"},
        {"logic_spirit_lobby_gs", "Off"},
        {"logic_lens_spirit", "Off"},
        {"logic_spirit_wall", "Off"},
        {"logic_flaming_chests", "Off"},
        {"logic_spirit_mq_frozen_eye", "Off"},
        {"logic_lens_spirit_mq", "Off"},
        {"logic_spirit_mq_lower_adult", "Off"},
        {"logic_spirit_mq_sun_block_sot", "Off"},
        {"logic_spirit_mq_sun_block_gs", "Off"},
        {"logic_lens_spirit_mq", "Off"},
        {"logic_lens_shadow", "Off"},
        {"logic_lens_shadow_mq", "Off"},
        {"logic_shadow_umbrella", "Off"},
        {"logic_lens_shadow_back", "Off"},
        {"logic_shadow_freestanding_key", "Off"},
        {"logic_lens_shadow_back", "Off"},
        {"logic_shadow_statue", "Off"},
        {"logic_shadow_mq_gap", "Off"},
        {"logic_shadow_mq_invisible_blades", "Off"},
        {"logic_shadow_mq_huge_pit", "Off"},
        {"logic_shadow_umbrella", "Off"},
        {"logic_lens_shadow_mq_back", "Off"},
        {"logic_shadow_statue", "Off"},
        {"logic_lens_botw", "Off"},
        {"logic_child_deadhand", "Off"},
        {"logic_lens_botw", "Off"},
        {"logic_child_deadhand", "Off"},
        {"logic_bot_w_mq_dead_hand_key", "Off"},
        {"logic_bot_w_mq_pits", "Off"},
        {"logic_ice_mq_scarecrow", "Off"},
        {"logic_ice_mq_red_ice_gs", "Off"},
        {"logic_gtg_without_hookshot", "Off"},
        {"logic_lens_gtg", "Off"},
        {"logic_flaming_chests", "Off"},
        {"logic_gtg_fake_wall", "Off"},
        {"logic_lens_gtg_mq", "Off"},
        {"logic_gtg_mq_without_hookshot", "Off"},
        {"logic_gtg_mq_with_hookshot", "Off"},
        {"logic_lens_gtg_mq", "Off"},
        {"logic_gtg_fake_wall", "Off"},
        {"logic_lens_castle", "Off"},
        {"logic_spirit_trial_hookshot", "Off"},
        {"logic_lens_castle_mq", "Off"},
        {"logic_fire_trial_mq", "Off"},
        {"logic_shadow_trial_mq", "Off"},
        {"logic_shadow_trial_mq", "Off"},
        {"logic_light_trial_mq", "Off"},
    };
    std::vector<SettingsMap> settingsVector = {settings1};
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

    StartTiming("Fill");
    std::cout << "Filling Worlds..." << std::endl;
    FillError err = FillWorlds(worlds);


    EndTiming("Fill");
    PrintTiming("Fill");
    DebugLog("Total Evals: " + std::to_string(TotalWorldEvals(worlds)));
    std::cout << "Eval Timing took " << std::to_string(worlds[0]->evalTime) << std::endl;
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
