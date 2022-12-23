#include "config.hpp"

#include "utility/log.hpp"
#include "utility/random.hpp"
#include "utility/Yaml.hpp"
#include "item_id.hpp"

#include <fstream>
#include <unordered_set>
#include <filesystem>

#define GET_FIELD(yaml, name, out) {                                        \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        out = yaml[#name].As<std::string>();                                \
    }

#define SET_CONFIG_FIELD(yaml, config, name) {                              \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        config.name = yaml[#name].As<std::string>();                        \
    }

#define SET_CONFIG_BOOL_FIELD(yaml, config, name) {                         \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        config.name = yaml[#name].As<bool>();                               \
    }

#define SET_FIELD_EMPTY_STR_IF_FAIL(yaml, config, name) {                   \
        if(yaml[#name].IsNone())                                            \
            config.name = "";                                               \
        config.name = yaml[#name].As<std::string>();                        \
    }

#define SET_BOOL_FIELD(yaml, config, name) {                                \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        config.settings.name = yaml[#name].As<bool>();                      \
    }

#define SET_INT_FIELD(yaml, config, name) {                                 \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        config.settings.name = yaml[#name].As<int>();                       \
    }

#define SET_STR_FIELD(yaml, config, name) {                                 \
        if(yaml[#name].IsNone()) {                                          \
            LOG_TO_ERROR("\""#name"\" not found in config.yaml\n"); \
            if (!ignoreErrors) return ConfigError::MISSING_KEY;}            \
        config.settings.name = yaml[#name].As<std::string>();               \
    }

#define SET_STR_FIELD_EMPTY_STR_IF_FAIL(yaml, config, name) {               \
        if(yaml[#name].IsNone())                                            \
            config.settings.name = "";                                      \
        config.settings.name = yaml[#name].As<std::string>();               \
    }

ConfigError CreateDefaultConfig(const std::string& filePath) {
    Config conf;

    conf.outputDir = "";
    conf.seed = "";

    conf.settingsVector = {{
      {"world_type", "oot3d"},
      {"starting_age", "child"},
      {"player_num", "1"},
      {"bombchus_in_logic", "on"},
      {"logic_rules", "glitchless"},
      {"open_forest", "open"},
      {"gerudo_fortress", "normal"},
      {"damage_multiplier", "1x"},
      {"shopsanity", "off"},
      {"hints", "none"},
      {"plant_beans", "off"},
      {"bridge", "medallions"},
      {"lacs_condition", "vanilla"},
      {"shuffle_ganon_bosskey", "medallions"},
      {"bridge_tokens", "50"},
      {"bridge_stones", "3"},
      {"bridge_medallions", "6"},
      {"bridge_rewards", "9"},
      {"lacs_tokens", "50"},
      {"lacs_stones", "3"},
      {"lacs_medallions", "6"},
      {"lacs_rewards", "9"},
      {"ganon_bosskey_stones", "3"},
      {"ganon_bosskey_tokens", "10"},
      {"ganon_bosskey_rewards", "9"},
      {"ganon_bosskey_medallions", "6"},
      {"had_night_start", "off"},
      {"complete_mask_quest", "off"},
      {"entrance_shuffle", "on"},
      {"shuffle_scrubs", "off"},
      {"shuffle_weird_egg", "off"},
      {"shuffle_gerudo_token", "off"},
      {"shuffle_chest_game", "off"},
      {"shuffle_dungeon_entrances", "off"},
      {"shuffle_overworld_entrances", "off"},
      {"small_keys", "vanilla"},
      {"free_scarecrow", "off"},
      {"big_poe_count", "2"},
      {"zora_fountain", "normal"},
      {"open_kakariko", "open"},
      {"open_door_of_time", "open"},
      {"skip_child_zelda", "off"},
      {"night_gs_expect_suns", "off"},
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

      {"logic_grottos_without_agony", "off"},
      {"logic_gv_hammer_chest", "off"},
      {"logic_gerudo_kitchen", "off"},
      {"logic_adult_kokiri_gs", "on"},
      {"logic_lost_woods_gs_bean", "off"},
      {"logic_lost_woods_bridge", "off"},
      {"logic_lab_wall_gs", "on"},
      {"logic_lab_diving", "off"},
      {"logic_wasteland_crossing", "off"},
      {"logic_lens_wasteland", "off"},
      {"logic_reverse_wasteland", "off"},
      {"logic_colossus_gs", "off"},
      {"logic_windmill_poh_hookshot", "off"},
      {"logic_kakariko_tower_gs", "on"},
      {"logic_kakariko_rooftop_gs", "on"},
      {"logic_man_on_roof", "on"},
      {"logic_graveyard_poh", "on"},
      {"logic_child_dampe_race_poh", "on"},
      {"logic_shadow_fire_arrow_entry", "off"},
      {"logic_visible_collisions", "off"},
      {"logic_dmt_bombable", "on"},
      {"logic_dmt_soil_gs", "off"},
      {"logic_dmt_climb_hovers", "off"},
      {"logic_link_goron_dins", "on"},
      {"logic_goron_city_leftmost", "off"},
      {"logic_goron_city_pot_with_strength", "on"},
      {"logic_goron_city_pot", "on"},
      {"logic_child_rolling_with_strength", "on"},
      {"logic_goron_grotto", "off"},
      {"logic_crater_upper_to_lower", "on"},
      {"logic_fewer_tunic_requirements", "on"},
      {"logic_crater_bean_poh_with_hovers", "on"},
      {"logic_zora_river_lower", "off"},
      {"logic_zora_river_upper", "on"},
      {"logic_domain_gs", "on"},
      {"logic_king_zora_skip", "on"},
      {"logic_zf_great_fairy", "off"},
      {"logic_castle_storms_gs", "on"},
      {"logic_deku_basement_gs", "off"},
      {"logic_deku_b1_skip", "off"},
      {"logic_deku_b1_webs_with_bow", "off"},
      {"logic_deku_mq_compass_gs", "off"},
      {"logic_deku_mq_log", "off"},
      {"logic_dc_scarecrow_gs", "off"},
      {"logic_dc_staircase", "off"},
      {"logic_dc_jump", "off"},
      {"logic_dc_slingshot_skip", "off"},
      {"logic_dc_mq_child_bombs", "off"},
      {"logic_dc_mq_eyes", "off"},
      {"logic_dc_mq_child_back", "off"},
      {"logic_jabu_boss_gs_adult", "off"},
      {"logic_jabu_scrub_jump_dive", "off"},
      {"logic_jabu_mq_sot_gs", "off"},
      {"logic_lens_jabu_mq", "off"},
      {"logic_forest_outdoor_east_gs", "off"},
      {"logic_forest_door_frame", "off"},
      {"logic_forest_outside_backdoor", "off"},
      {"logic_forest_mq_block_puzzle", "off"},
      {"logic_forest_mq_hallway_switch_jumpslash", "off"},
      {"logic_forest_mq_hallway_switch_hookshot", "off"},
      {"logic_forest_mq_well_swim", "off"},
      {"logic_forest_outdoors_ledge", "off"},
      {"logic_fire_boss_door_jump", "off"},
      {"logic_fire_song_of_time", "off"},
      {"logic_fire_strength", "off"},
      {"logic_fire_scarecrow", "off"},
      {"logic_fire_flame_maze", "off"},
      {"logic_fire_mq_near_boss", "off"},
      {"logic_fire_boss_door_jump", "off"},
      {"logic_fire_mq_bk_chest", "off"},
      {"logic_fire_mq_blocked_chest", "off"},
      {"logic_fire_mq_climb", "off"},
      {"logic_fire_mq_maze_side_room", "off"},
      {"logic_fire_mq_maze_hovers", "off"},
      {"logic_fire_mq_maze_jump", "off"},
      {"logic_fire_mq_flame_maze", "off"},
      {"logic_fire_mq_above_maze_gs", "off"},
      {"logic_water_temple_torch_longshot", "off"},
      {"logic_water_temple_upper_boost", "off"},
      {"logic_water_central_bow", "off"},
      {"logic_water_cracked_wall_hovers", "off"},
      {"logic_water_cracked_wall_nothing", "off"},
      {"logic_water_boss_key_region", "off"},
      {"logic_water_north_basement_ledge_jump", "off"},
      {"logic_water_bk_jump_dive", "off"},
      {"logic_water_dragon_adult", "off"},
      {"logic_water_dragon_jump_dive", "off"},
      {"logic_water_central_gs_fw", "off"},
      {"logic_water_falling_platform_gs", "off"},
      {"logic_water_river_gs", "off"},
      {"logic_water_mq_central_pillar", "off"},
      {"logic_water_dragon_jump_dive", "off"},
      {"logic_water_north_basement_ledge_jump", "off"},
      {"logic_water_mq_locked_gs", "off"},
      {"logic_spirit_child_bombchu", "off"},
      {"logic_spirit_lower_adult_switch", "off"},
      {"logic_spirit_map_chest", "off"},
      {"logic_spirit_sun_chest", "off"},
      {"logic_spirit_lobby_gs", "off"},
      {"logic_lens_spirit", "off"},
      {"logic_spirit_wall", "off"},
      {"logic_flaming_chests", "off"},
      {"logic_spirit_mq_frozen_eye", "off"},
      {"logic_lens_spirit_mq", "off"},
      {"logic_spirit_mq_lower_adult", "off"},
      {"logic_spirit_mq_sun_block_sot", "off"},
      {"logic_spirit_mq_sun_block_gs", "off"},
      {"logic_lens_spirit_mq", "off"},
      {"logic_lens_shadow", "off"},
      {"logic_lens_shadow_mq", "off"},
      {"logic_shadow_umbrella", "off"},
      {"logic_lens_shadow_back", "off"},
      {"logic_shadow_freestanding_key", "off"},
      {"logic_lens_shadow_back", "off"},
      {"logic_shadow_statue", "off"},
      {"logic_shadow_mq_gap", "off"},
      {"logic_shadow_mq_invisible_blades", "off"},
      {"logic_shadow_mq_huge_pit", "off"},
      {"logic_shadow_umbrella", "off"},
      {"logic_lens_shadow_mq_back", "off"},
      {"logic_shadow_statue", "off"},
      {"logic_lens_botw", "off"},
      {"logic_child_deadhand", "off"},
      {"logic_lens_botw", "off"},
      {"logic_child_deadhand", "off"},
      {"logic_bot_w_mq_dead_hand_key", "off"},
      {"logic_bot_w_mq_pits", "off"},
      {"logic_ice_mq_scarecrow", "off"},
      {"logic_ice_mq_red_ice_gs", "off"},
      {"logic_gtg_without_hookshot", "off"},
      {"logic_lens_gtg", "off"},
      {"logic_flaming_chests", "off"},
      {"logic_gtg_fake_wall", "off"},
      {"logic_lens_gtg_mq", "off"},
      {"logic_gtg_mq_without_hookshot", "off"},
      {"logic_gtg_mq_with_hookshot", "off"},
      {"logic_lens_gtg_mq", "off"},
      {"logic_gtg_fake_wall", "off"},
      {"logic_lens_castle", "off"},
      {"logic_spirit_trial_hookshot", "off"},
      {"logic_lens_castle_mq", "off"},
      {"logic_fire_trial_mq", "off"},
      {"logic_shadow_trial_mq", "off"},
      {"logic_shadow_trial_mq", "off"},
      {"logic_light_trial_mq", "off"},
    }};

    LOG_AND_RETURN_IF_ERR(WriteConfigToFile(filePath, conf))

    return ConfigError::NONE;
}

ConfigError LoadConfigFromFile(const std::string& filePath, Config& out, bool ignoreErrors /*= false*/) {
    //Check if we can open the file before parsing because exceptions won't work on console
    std::ifstream file(filePath);
    if(!file.is_open()) LOG_ERR_AND_RETURN(ConfigError::COULD_NOT_OPEN);
    file.close();

    Yaml::Node root;
    Yaml::Parse(root, filePath.c_str());

    //hardcode paths for console, otherwise use config
    #ifdef __3DS__
        out.outputDir = "/luma/titles/0004000000033500/";
        // out.settings.plandomizerFile = APP_SAVE_PATH "plandomizer.yaml";
    #else
        SET_FIELD_EMPTY_STR_IF_FAIL(root, out, outputDir)
    #endif

    SET_FIELD_EMPTY_STR_IF_FAIL(root, out, seed)

    int worldNum = 1;
    std::string worldNumStr = "World " + std::to_string(worldNum);
    while (root[worldNumStr].IsMap())
    {
        out.settingsVector.push_back({});
        auto fieldIt = root[worldNumStr].End();
        do
        {
            fieldIt--;
            auto settingMap = *fieldIt;
            auto setting = settingMap.first;
            auto value = settingMap.second.As<std::string>();
            out.settingsVector[worldNum - 1][setting] = value;
        }
        while (fieldIt != root[worldNumStr].Begin());

        worldNum++;
        worldNumStr = "World " + std::to_string(worldNum);
    }

    return ConfigError::NONE;
}



#define WRITE_CONFIG_FIELD(yaml, config, name) {   \
        yaml[#name] = config.name;                 \
    }

#define WRITE_CONFIG_BOOL_FIELD(yaml, config, name) {   \
        yaml[#name] = config.name ? "true" : "false";   \
    }


#define WRITE_SETTING_BOOL_FIELD(yaml, config, name) {           \
        yaml[#name] = config.settings.name ? "true" : "false";   \
    }


#define WRITE_NUM_FIELD(yaml, config, name) {                 \
        yaml[#name] = std::to_string(config.settings.name);   \
    }

#define WRITE_STR_FIELD(yaml, config, name) {          \
        yaml[name] = settings[name];            \
    }

ConfigError WriteConfigToFile(const std::string& filePath, Config& config) {
    //Check if we can open the file before parsing because exceptions won't work on console
    std::ofstream file(filePath);
    if(!file.is_open()) return ConfigError::COULD_NOT_OPEN;
    file.close();

    Yaml::Node root;

    root["program_version"] = RANDOMIZER_VERSION; //Keep track of rando version to give warning (different versions will have different item placements)

    WRITE_CONFIG_FIELD(root, config, outputDir)
    WRITE_CONFIG_FIELD(root, config, seed)

    for (auto& settings : config.settingsVector)
    {
        auto worldNum = "World " + settings["player_num"];
        for (auto& [setting, value] : settings)
        {
            root[worldNum][setting] = value;
        }
    }

    Yaml::Serialize(root, filePath.c_str());

    return ConfigError::NONE;
}

std::string ErrorToName(ConfigError err) {
    switch (err)
    {
        case ConfigError::NONE:
            return "NONE";
        case ConfigError::COULD_NOT_OPEN:
            return "COULD_NOT_OPEN";
        case ConfigError::MISSING_KEY:
            return "MISSING_KEY";
        case ConfigError::DIFFERENT_FILE_VERSION:
            return "DIFFERENT_FILE_VERSION";
        case ConfigError::DIFFERENT_RANDO_VERSION:
            return "DIFFERENT_RANDO_VERSION";
        case ConfigError::INVALID_VALUE:
            return "INVALID_VALUE";
        case ConfigError::TOO_MANY_OF_ITEM:
            return "TOO_MANY_OF_ITEM";
        default:
            return "UNKNOWN";
    }
}
