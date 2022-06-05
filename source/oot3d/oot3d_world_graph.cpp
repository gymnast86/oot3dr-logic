#include "oot3d_world_graph.hpp"
#include "oot3d_world.hpp"
#include "oot3d_world_graph_defs.hpp"
#include "../debug.hpp"

#include <algorithm>
#include <iostream>

#define GLITCHLESS(logic) [this]{return logic;}
#define GLITCHED(logic) [this]{return logic;}

WorldBuildingError Oot3dWorld::ProcessArea(AreaStruct areaStruct)
{
    auto parentAreaId = NameToAreaID(areaStruct.areaName);
    if (parentAreaId == AreaID::INVALID)
    {
        std::cout << "Unknown area name " << areaStruct.areaName;
        return WorldBuildingError::BAD_AREA_VALUE;
    }
    auto area = areas[parentAreaId].get();
    for (EventStruct& event : areaStruct.events)
    {
        std::replace(event.name.begin(), event.name.end(), ' ', '_');
        auto itemId = NameToItemID(event.name);
        if (itemId == ItemID::INVALID)
        {
            std::cout << "Unknown event name " << event.name;
            return WorldBuildingError::BAD_AREA_VALUE;
        }
        area->GetEvent(itemId)->requirement = event.requirement.glitchless;
    }
    for (LocationStruct& location : areaStruct.locations)
    {
        auto locationId = NameToLocationID(location.name);
        if (locationId == LocationID::INVALID)
        {
            std::cout << "Unknown location name " << location.name;
            return WorldBuildingError::BAD_AREA_VALUE;
        }
        area->GetLocationAccess(locationId)->requirement = location.requirement.glitchless;
    }
    for (EntranceStruct& exit : areaStruct.entrances)
    {
        auto connectedAreaId = NameToAreaID(exit.connectedAreaName);
        if (connectedAreaId == AreaID::INVALID)
        {
            std::cout << "Unknown connected area name " << exit.connectedAreaName;
            return WorldBuildingError::BAD_AREA_VALUE;
        }
        area->GetExit(connectedAreaId)->requirement = exit.requirement.glitchless;
    }
    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::InitWorldGraph() {
    std::cout << "Initing World Graph for " << std::to_string(worldId) << "..." << std::endl;
    WorldBuildingError err = WorldBuildingError::NONE;

    //static std::list<AreaStruct> areaStructs = {
/*===============================================
|                 WORLD GRAPH                   |
================================================*/
err = ProcessArea(
{"Root", "", NO_TIMEPASS, {}, {
    //Locations
        {"Links Pocket", {GLITCHLESS(true)}},
        // Gift from Sages: can_Receive_Ganon_Bosskey
    }, {
    //Exits
        {"Root Exits", {GLITCHLESS(true)}},
        // HC Garden Locations: skip_Child_Zelda
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Root Exits", "", NO_TIMEPASS, {}, {}, {
    //Exits
        {"Child Spawn",             {GLITCHLESS(IS_CHILD)}},
        {"Adult Spawn",             {GLITCHLESS(IS_ADULT)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && PRELUDE_OF_LIGHT   && CAN_LEAVE_FOREST;}}},
        {"Minuet of Forest Warp",   {GLITCHLESS(CAN_PLAY_MINUET_OF_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && MINUET_OF_FOREST;}}},
        {"Bolero of Fire Warp",     {GLITCHLESS(CAN_PLAY_BOLERO_OF_FIRE     && CAN_LEAVE_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && BOLERO_OF_FIRE     && CAN_LEAVE_FOREST;}}},
        {"Serenade of Water Warp",  {GLITCHLESS(CAN_PLAY_SERENADE_OF_WATER  && CAN_LEAVE_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && SERENADE_OF_WATER  && CAN_LEAVE_FOREST;}}},
        {"Nocturne of Shadow Warp", {GLITCHLESS(CAN_PLAY_NOCTURNE_OF_SHADOW && CAN_LEAVE_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && NOCTURNE_OF_SHADOW && CAN_LEAVE_FOREST;}}},
        {"Requiem of Spirit Warp",  {GLITCHLESS(CAN_PLAY_REQUIEM_OF_SPIRIT  && CAN_LEAVE_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && REQUIEM_OF_SPIRIT  && CAN_LEAVE_FOREST;}}},
        {"Prelude of Light Warp",   {GLITCHLESS(CAN_PLAY_PRELUDE_OF_LIGHT  && CAN_LEAVE_FOREST)}},
                                         // /*Glitched*/[]{return (((IS_CHILD /*&& (ChildCanAccess(KOKIRI_FOREST) || ChildCanAccess(HYRULE_FIELD) || ChildCanAccess(LAKE_HYLIA)*/)) || (IS_ADULT /*&& (AdultCanAccess(KOKIRI_FOREST) || AdultCanAccess(HYRULE_FIELD) || AdultCanAccess(LAKE_HYLIA)*/))) && (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/
                                         //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (IS_ADULT || KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) && REQUIEM_OF_SPIRIT  && CAN_LEAVE_FOREST;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Child Spawn", "", NO_TIMEPASS, {}, {}, {
    //Exits
        {"KF Links House", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Adult Spawn", "", NO_TIMEPASS, {}, {}, {
    //Exits
        {"Temple of Time", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Minuet of Forest Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"Sacred Forest Meadow", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Bolero of Fire Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"DMC Central Local", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Serenade of Water Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"Lake Hylia", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Nocturne of Shadow Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"Graveyard Warp Pad Region", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Requiem of Spirit Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"Desert Colossus", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Prelude of Light Warp","", NO_TIMEPASS,  {}, {}, {
    //Exits
        {"Temple of Time", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"Kokiri Forest", "Kokiri Forest", NO_TIMEPASS, {
   //Events
       {"Showed Mido Sword And Shield", {GLITCHLESS(IS_CHILD && KOKIRI_SWORD && DEKU_SHIELD)}},
   }, {
   //Locations
       {"KF Kokiri Sword Chest",   {GLITCHLESS(IS_CHILD)}},
       {"KF GS Know It All House", {GLITCHLESS(CHILD_NIGHT && CAN_CHILD_ATTACK && (logic->settings.hadNightStart || CAN_LEAVE_FOREST || CAN_PLAY_SUNS_SONG) && CAN_GET_NIGHT_TIME_GS)}},
       {"KF GS Bean Patch",        {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"KF GS House of Twins",    {GLITCHLESS(ADULT_NIGHT && (HOOKSHOT || BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                            // /*Glitched*/[]{return ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS && (CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE));}}},
       {"KF Gossip Stone",         {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",      {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
       {"Bean Plant Fairy",        {GLITCHLESS(CAN_PLANT_BEAN && CAN_PLAY_SONG_OF_STORMS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"KF Links House",        {GLITCHLESS(true)}},
       {"KF Midos House",        {GLITCHLESS(true)}},
       {"KF Sarias House",       {GLITCHLESS(true)}},
       {"KF House of Twins",     {GLITCHLESS(true)}},
       {"KF Know It All House",  {GLITCHLESS(true)}},
       {"KF Kokiri Shop",        {GLITCHLESS(true)}},
       {"KF Outside Deku Tree",  {GLITCHLESS(IS_ADULT || logic->settings.openForest == OPENFOREST_OPEN || logic->items.showedMidoSwordAndShield)}},
                                  //   /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"Lost Woods",            {GLITCHLESS(true)}},
       {"LW Bridge From Forest", {GLITCHLESS(IS_ADULT || logic->settings.openForest != OPENFOREST_CLOSED || DEKU_TREE_CLEAR)}},
                                  //   /*Glitched*/[]{return CAN_LEAVE_FOREST && (CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || GlitchWWTEscape);}}},
       {"KF Storms Grotto",      {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
                                  //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Outside Deku Tree", "Kokiri Forest", NO_TIMEPASS, {
   //Events
       {"Showed Mido Sword And Shield", {GLITCHLESS(IS_CHILD && KOKIRI_SWORD && DEKU_SHIELD)}},
   }, {
   //Locations
       {"Deku Baba Sticks",                {GLITCHLESS((IS_ADULT && !logic->settings.entranceShuffle) || CAN_USE_KOKIRI_SWORD || CAN_USE_BOOMERANG)}},
       {"Deku Baba Nuts",                  {GLITCHLESS((IS_ADULT && !logic->settings.entranceShuffle) || CAN_USE_KOKIRI_SWORD || CAN_USE_SLINGSHOT || CAN_USE_STICKS || CAN_USE_DINS_FIRE || HAS_EXPLOSIVES)}},
       {"KF Deku Tree Gossip Stone Left",  {GLITCHLESS(true)}},
       {"KF Deku Tree Gossip Stone Right", {GLITCHLESS(true)}},
   }, {
   //Exits
       //{"Deku Tree Entryway", {GLITCHLESS(IS_CHILD || (logic->settings.shuffleDungeonEntrances != SHUFFLEDUNGEONS_OFF && (logic->settings.openForest == OPENFOREST_OPEN || logic->items.showedMidoSwordAndShield)))}},
                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE);}}},
       {"Kokiri Forest",      {GLITCHLESS(IS_ADULT || logic->settings.openForest == OPENFOREST_OPEN || logic->items.showedMidoSwordAndShield)}},
                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Links House", "", NO_TIMEPASS, {}, {
   //Locations
       {"KF Links House Cow", {GLITCHLESS(IS_ADULT && CAN_PLAY_EPONAS_SONG && LINKS_COW)}},
                                      //  /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (NumBottles >= 2 && Fairy)) && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT))) && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && BOMBS && IS_ADULT && EponasSong && LINKS_COW;}}},
   }, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}}
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Midos House", "", NO_TIMEPASS, {}, {
   //Locations
       {"KF Midos Top Left Chest",     {GLITCHLESS(true)}},
       {"KF Midos Top Right Chest",    {GLITCHLESS(true)}},
       {"KF Midos Bottom Left Chest",  {GLITCHLESS(true)}},
       {"KF Midos Bottom Right Chest", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Sarias House", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF House of Twins", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Know It All House", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Kokiri Shop", "", NO_TIMEPASS, {}, {
   //Locations
       {"KF Shop Item 1", {GLITCHLESS(true)}},
       {"KF Shop Item 2", {GLITCHLESS(true)}},
       {"KF Shop Item 3", {GLITCHLESS(true)}},
       {"KF Shop Item 4", {GLITCHLESS(true)}},
       {"KF Shop Item 5", {GLITCHLESS(true)}},
       {"KF Shop Item 6", {GLITCHLESS(true)}},
       {"KF Shop Item 7", {GLITCHLESS(true)}},
       {"KF Shop Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);


err = ProcessArea(
{"KF Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"KF Storms Grotto Chest",        {GLITCHLESS(true)}},
       {"KF Storms Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",               {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                     {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                     {GLITCHLESS(HAS_BOTTLE)}}, // without "&& true", it fails to compile
   }, {
   //Exits
       {"Kokiri Forest", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);
//
// {"LW Forest Exit", "Lost Woods", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Kokiri Forest", {GLITCHLESS(true)}}
// }},

err = ProcessArea(
{"Lost Woods", "Lost Woods", NO_TIMEPASS, {}, {
   //Locations
       {"LW Skull Kid",                 {GLITCHLESS(IS_CHILD && CAN_PLAY_SARIAS_SONG)}},
                                                //  /*Glitched*/[]{return IS_CHILD && (FISH || BUGS) && SariasSong && CAN_SHIELD && (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));}}},
       {"LW Trade Cojiro",              {GLITCHLESS(IS_ADULT && COJIRO)}},
       {"LW Trade Odd Poultice",        {GLITCHLESS(IS_ADULT && ODD_POULTICE && COJIRO)}},
       {"LW Ocarina Memory Game",       {GLITCHLESS(IS_CHILD && OCARINA)}},
                                                //  /*Glitched*/[]{return IS_CHILD && (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((FISH || BUGS) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));}}},
       {"LW Target in Woods",           {GLITCHLESS(IS_CHILD && CAN_USE_SLINGSHOT)}},
       {"LW Deku Scrub Near Bridge",    {GLITCHLESS(IS_CHILD && CAN_STUN_DEKU)}},
       {"LW GS Bean Patch Near Bridge", {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"LW Gossip Stone",              {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",           {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
       {"Bean Plant Fairy",             {GLITCHLESS(CAN_PLANT_BEAN && CAN_PLAY_SONG_OF_STORMS && HAS_BOTTLE)}},
       {"Bug Shrub",                    {GLITCHLESS(IS_CHILD && CAN_CUT_SHRUBS && HAS_BOTTLE)}},
                                                //  /*Glitched*/[]{return IS_CHILD && STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
   }, {
   //Exits
       {"LW Forest Exit",           {GLITCHLESS(true)}},
       {"GC Woods Warp",            {GLITCHLESS(true)}},
       {"LW Bridge",                {GLITCHLESS(IS_ADULT && (HERE(CAN_PLANT_BEAN) || CAN_USE_HOVER_BOOTS || CAN_USE_LONGSHOT))}},
                                      //  /*Glitched*/[]{return CAN_LEAVE_FOREST && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && HAS_BOMBCHUS) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE));}}},
       {"Zora River",               {GLITCHLESS(CAN_LEAVE_FOREST && (SILVER_SCALE || CAN_USE_IRON_BOOTS))}},
                                        // /*Glitched*/[]{return CAN_LEAVE_FOREST && (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::NaviDive_Stick, GlitchDifficulty::ADVANCED) ||
                                        //                       ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) || (CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || (IS_ADULT && (HasBoots || CLAIM_CHECK)) || (IS_CHILD && WEIRD_EGG)))) &&
                                        //                       ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED)))));}}},
       {"LW Beyond Mido",           {GLITCHLESS(IS_CHILD || CAN_PLAY_SARIAS_SONG)}},
                                      //  /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) ||
                                                              // CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) || (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::ADVANCED) && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) || HOVER_BOOTS)) ||
                                                              // ((CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SariasSong);}}},
       {"LW Near Shortcuts Grotto", {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                      //  /*Glitched*/[]{return HERE(THE_LOST_WOODS, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LW Beyond Mido", "Lost Woods", NO_TIMEPASS, {}, {
   //Locations
       {"LW Deku Scrub Near Deku Theater Right", {GLITCHLESS(IS_CHILD && CAN_STUN_DEKU)}},
       {"LW Deku Scrub Near Deku Theater Left",  {GLITCHLESS(IS_CHILD && CAN_STUN_DEKU)}},
       {"LW GS Above Theater",                   {GLITCHLESS(ADULT_NIGHT &&
                                                            (HERE(CAN_PLANT_BEAN) ||
                                                                (logic->tricks.lostWoodsGsBean && CAN_USE_HOOKSHOT &&
                                                                (CAN_USE_LONGSHOT || CAN_USE_BOW || CAN_USE_SLINGSHOT || HAS_BOMBCHUS || CAN_USE_DINS_FIRE))) &&
                                                                CAN_GET_NIGHT_TIME_GS)}},
                                                          // /*Glitched*/[]{return ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"LW GS Bean Patch Near Theater",         {GLITCHLESS(CAN_PLANT_BUGS && (CAN_CHILD_ATTACK || (logic->settings.shuffleScrubs == SCRUBSANITY_OFF && DEKU_SHIELD)))}},
       {"Butterfly Fairy",                       {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"LW Forest Exit",   {GLITCHLESS(true)}},
       {"Lost Woods",       {GLITCHLESS(IS_CHILD || CAN_PLAY_SARIAS_SONG)}},
                                // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || ((CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                //                       ((BUGS || FISH) && CAN_SHIELD && BOMBS && (CanSurviveDamage || (NumBottles >= 2 && Fairy)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SariasSong);}}},
       {"SFM Entryway",     {GLITCHLESS(true)}},
       {"Deku Theater",     {GLITCHLESS(true)}},
       {"LW Scrubs Grotto", {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                              //  /*Glitched*/[]{return HERE(LW_BEYOND_MIDO, []{return IS_CHILD && CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LW Near Shortcuts Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"LW Near Shortcuts Grotto Chest",        {GLITCHLESS(true)}},
       {"LW Near Shortcuts Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",                       {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                             {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                             {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Lost Woods", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Lost Woods Mushroom Timeout", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Lost Woods", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Deku Theater", "", NO_TIMEPASS, {}, {
   //Locations
       {"Deku Theater Skull Mask",    {GLITCHLESS(IS_CHILD && SKULL_MASK)}},
       {"Deku Theater Mask of Truth", {GLITCHLESS(IS_CHILD && MASK_OF_TRUTH)}},
   }, {
   //Exits
       {"LW Beyond Mido", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LW Scrubs Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"LW Deku Scrub Grotto Rear",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"LW Deku Scrub Grotto Front", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"LW Beyond Mido", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"SFM Entryway", "Sacred Forest Meadow", NO_TIMEPASS, {}, {}, {
   //Exits
       {"LW Beyond Mido",       {GLITCHLESS(true)}},
       {"Sacred Forest Meadow", {GLITCHLESS(IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || CAN_USE_DINS_FIRE)}},
       {"SFM Wolfos Grotto",    {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Sacred Forest Meadow", "Sacred Forest Meadow", NO_TIMEPASS, {}, {
   //Locations
       {"Song from Saria",             {GLITCHLESS(IS_CHILD && ZELDAS_LETTER)}},
       {"Sheik in Forest",             {GLITCHLESS(IS_ADULT)}},
       {"SFM GS",                      {GLITCHLESS(ADULT_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
       {"SFM Maze Gossip Stone Lower", {GLITCHLESS(true)}},
       {"SFM Maze Gossip Stone Upper", {GLITCHLESS(true)}},
       {"SFM Saria Gossip Stone",      {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",          {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"SFM Entryway",           {GLITCHLESS(true)}},
       //{"Forest Temple Entryway", {GLITCHLESS(CAN_USE_HOOKSHOT)}},
                                    //  /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"SFM Fairy Grotto",       {GLITCHLESS(true)}},
       {"SFM Storms Grotto",      {GLITCHLESS(CAN_OPEN_STORM_GROTTO)}},
                                    //  /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"SFM Fairy Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Sacred Forest Meadow", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"SFM Wolfos Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"SFM Wolfos Grotto Chest", {GLITCHLESS(IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || CAN_USE_DINS_FIRE || CAN_USE_MEGATON_HAMMER || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
   }, {
   //Exits
       {"SFM Entryway", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"SFM Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"SFM Deku Scrub Grotto Rear",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"SFM Deku Scrub Grotto Front", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Sacred Forest Meadow", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LW Bridge From Forest", "Lost Woods", NO_TIMEPASS, {}, {
   //Locations
       {"LW Gift from Saria", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"LW Bridge", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LW Bridge", "Lost Woods", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kokiri Forest",  {GLITCHLESS(true)}},
       {"Hyrule Field",   {GLITCHLESS(true)}},
       {"Lost Woods", {GLITCHLESS(CAN_USE_LONGSHOT)}},
                            //  /*Glitched*/[]{return (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && BOMBS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::NOVICE);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Hyrule Field", "Hyrule Field", TIMEPASS, {}, {
   //Locations
       {"HF Ocarina of Time Item",   {GLITCHLESS(IS_CHILD && HAS_ALL_STONES)}},
       {"Song from Ocarina of Time", {GLITCHLESS(IS_CHILD && HAS_ALL_STONES)}},
       {"Big Poe Kill",              {GLITCHLESS(CAN_USE_BOW && CAN_RIDE_EPONA && HAS_BOTTLE)}},
   }, {
   //Exits
       {"LW Bridge",              {GLITCHLESS(true)}},
       {"Lake Hylia",             {GLITCHLESS(true)}},
       {"Gerudo Valley",          {GLITCHLESS(true)}},
       {"Market Entrance",        {GLITCHLESS(true)}},
       {"Kakariko Village",       {GLITCHLESS(true)}},
       {"ZR Front",               {GLITCHLESS(true)}},
       {"Lon Lon Ranch",          {GLITCHLESS(true)}},
       {"HF Southeast Grotto",    {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                  //    /*Glitched*/[]{return HERE(HYRULE_FIELD, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
       {"HF Open Grotto",         {GLITCHLESS(true)}},
       {"HF Inside Fence Grotto", {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
                                  //    /*Glitched*/[]{return STICKS && IS_CHILD && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"HF Cow Grotto",          {GLITCHLESS((CAN_USE_MEGATON_HAMMER || IS_CHILD) && CAN_OPEN_BOMB_GROTTO)}},
                                  //    /*Glitched*/[]{return (CAN_USE_STICKS && (ShardOfAgony || logic->tricks.grottosWithoutAgony) && (IS_CHILD || (CAN_OPEN_BOMB_GROTTO && (CAN_TAKE_DAMAGETwice || CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)))) && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE));}}},
       {"HF Near Market Grotto",  {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                  //    /*Glitched*/[]{return HERE(HYRULE_FIELD, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
       {"HF Fairy Grotto",        {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                  //    /*Glitched*/[]{return HERE(HYRULE_FIELD, []{return CAN_USE_STICKS && ((IS_CHILD && CAN_TAKE_DAMAGE && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT)) || (IS_ADULT /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/));});}}},
       {"HF Near Kak Grotto",     {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
                                  //    /*Glitched*/[]{return STICKS && IS_CHILD && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"HF Tektite Grotto",      {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
                                  //    /*Glitched*/[]{return STICKS && IS_CHILD && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Southeast Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF Southeast Grotto Chest",        {GLITCHLESS(true)}},
       {"HF Southeast Grotto Gossip Stone", {GLITCHLESS(true)}},
      {"Butterfly Fairy",                   {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
      {"Bug Shrub",                         {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
      {"Lone Fish",                         {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Open Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF Open Grotto Chest",        {GLITCHLESS(true)}},
       {"HF Open Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",             {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                   {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                   {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Inside Fence Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF Deku Scrub Grotto", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Cow Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF GS Cow Grotto",           {GLITCHLESS(HAS_FIRE_SOURCE && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                            //    /*Glitched*/[]{return (CAN_USE_STICKS && BOMBS && CanSurviveDamage && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG);}}},
       {"HF Cow Grotto Cow",          {GLITCHLESS(HAS_FIRE_SOURCE && CAN_PLAY_EPONAS_SONG)}},
                                            //    /*Glitched*/[]{return ((CAN_USE_STICKS && BOMBS && CanSurviveDamage && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) || HAS_FIRE_SOURCE) &&
                                            //                          (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && BOMBS && (CanSurviveDamage || (NumBottles >= 2 && Fairy)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)) || OCARINA) && EponasSong;}}},
       {"HF Cow Grotto Gossip Stone", {GLITCHLESS(HAS_FIRE_SOURCE)}},
                                            //    /*Glitched*/[]{return CAN_USE_STICKS && BOMBS && CanSurviveDamage && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE);}}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Near Market Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF Near Market Grotto Chest",        {GLITCHLESS(true)}},
       {"HF Near Market Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",                    {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                          {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                          {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Fairy Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Near Kak Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF GS Near Kak Grotto", {GLITCHLESS(CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HF Tektite Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HF Tektite Grotto Freestanding PoH", {GLITCHLESS(GOLD_SCALE || CAN_USE_IRON_BOOTS)}},
   }, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Lake Hylia", "Lake Hylia", TIMEPASS, {
   //Events
       {"Bonooru",   {GLITCHLESS(IS_CHILD && OCARINA)}},
                                  //  /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && (KOKIRI_SWORD || STICKS || BOMBS || HAS_BOMBCHUS || BOOMERANG || SLINGSHOT || CAN_USE_MEGATON_HAMMER) /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/)) && IS_CHILD;}}},
   }, {
   //Locations
       {"Pierre",                    {GLITCHLESS(IS_ADULT && logic->items.bonooru && !logic->settings.freeScarecrow)}},
       {"LH Underwater Item",        {GLITCHLESS(IS_CHILD && SILVER_SCALE)}},
       {"LH Sun",                    {GLITCHLESS(IS_ADULT && WATER_TEMPLE_CLEAR && CAN_USE_BOW)}},
       {"LH Freestanding PoH",       {GLITCHLESS(IS_ADULT && (CAN_USE_SCARECROW || HERE(CAN_PLANT_BEAN)))}},
                                              // /*Glitched*/[]{return (IS_ADULT && CAN_USE_HOOKSHOT && ScarecrowSong && (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"LH GS Bean Patch",          {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"LH GS Lab Wall",            {GLITCHLESS(CHILD_NIGHT && ((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || (logic->tricks.labWallGS && (STICKS || KOKIRI_SWORD || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD))) && CAN_GET_NIGHT_TIME_GS)}},
       {"LH GS Small Island",        {GLITCHLESS(CHILD_NIGHT && CAN_CHILD_ATTACK && CAN_GET_NIGHT_TIME_GS)}},
       {"LH GS Tree",                {GLITCHLESS(ADULT_NIGHT && CAN_USE_LONGSHOT && CAN_GET_NIGHT_TIME_GS)}},
                                              // /*Glitched*/[]{return (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE)) && AT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"LH Lab Gossip Stone",       {GLITCHLESS(true)}},
       {"LH Gossip Stone Southeast", {GLITCHLESS(true)}},
       {"LH Gossip Stone Southwest", {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",        {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Bean Plant Fairy",          {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS && HAS_BOTTLE)}},
       {"Butterfly Fairy",           {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                 {GLITCHLESS(IS_CHILD && CAN_CUT_SHRUBS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field",          {GLITCHLESS(true)}},
       {"Zoras Domain",          {GLITCHLESS(IS_CHILD && (SILVER_SCALE || CAN_USE_IRON_BOOTS))}},
                                  //   /*Glitched*/[]{return IS_CHILD && (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::NaviDive_Stick, GlitchDifficulty::INTERMEDIATE) ||
                                  //                         (BUGS && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) || (CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || (IS_ADULT && (HasBoots || CLAIM_CHECK)) || (IS_CHILD && WEIRD_EGG)))) &&
                                  //                         ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED)))));}}},
       {"LH Owl Flight",         {GLITCHLESS(IS_CHILD)}},
       {"LH Fishing Island",     {GLITCHLESS(IS_CHILD || CAN_USE_SCARECROW || HERE(CAN_PLANT_BEAN) || WATER_TEMPLE_CLEAR)}},
                                  //   /*Glitched*/[]{return (CAN_USE_HOOKSHOT && ScarecrowSong && (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) /*&& CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::NOVICE)*/))) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
       {"LH Lab",                {GLITCHLESS(true)}},
       //{"Water Temple Entryway", {GLITCHLESS(CAN_USE_HOOKSHOT && (CAN_USE_IRON_BOOTS || (IS_ADULT && CAN_USE_LONGSHOT && GOLD_SCALE)))}},
                                  //   /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::ADVANCED);}}},
       {"LH Grotto",             {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LH Fishing Island", "Lake Hylia", TIMEPASS, {}, {}, {
   //Exits
       {"Lake Hylia",      {GLITCHLESS(true)}},
       {"LH Fishing Hole", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LH Owl Flight", "Lake Hylia", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LH Lab", "", NO_TIMEPASS, {}, {
   //Locations
       {"LH Lab Dive",     {GLITCHLESS(GOLD_SCALE || (logic->tricks.labDiving && CAN_USE_IRON_BOOTS && CAN_USE_HOOKSHOT))}},
                                  //   /*Glitched*/[]{return CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) ||
                                  //                         (CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || (IS_ADULT && (HasBoots || CLAIM_CHECK)) || (IS_CHILD && WEIRD_EGG)))) && CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE));}}},
       {"LH Lab Trade Eyeball Frog", {GLITCHLESS(IS_ADULT && EYEBALL_FROG)}},
       {"LH GS Lab Crate",           {GLITCHLESS(CAN_USE_IRON_BOOTS && CAN_USE_HOOKSHOT)}},
                                     // /*Glitched*/[]{return (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && HAS_BOMBCHUS && (HAS_BOTTLE || (IS_ADULT && (HasBoots || CLAIM_CHECK)) || (IS_CHILD && WEIRD_EGG)) &&
                                     //                       (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::ADVANCED) || ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) ||
                                     //                       (CAN_USE_FARORES_WIND && CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || GOLD_SCALE || CAN_USE_IRON_BOOTS)) ||
                                     //                       (CAN_USE_IRON_BOOTS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE));}}},
   }, {
   //Exits
       {"Lake Hylia", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LH Fishing Hole", "", TIMEPASS, {}, {
   //Locations
       {"LH Child Fishing", {GLITCHLESS(IS_CHILD)}},
       {"LH Adult Fishing", {GLITCHLESS(IS_ADULT)}},
   }, {
   //Exits
       {"LH Fishing Island", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LH Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"LH Deku Scrub Grotto Left",   {GLITCHLESS(CAN_STUN_DEKU)}},
       {"LH Deku Scrub Grotto Right",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"LH Deku Scrub Grotto Center", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Lake Hylia", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Gerudo Valley", "Gerudo Valley", TIMEPASS, {
   //Events

   }, {
   //Locations
       {"GV GS Small Bridge", {GLITCHLESS(CHILD_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                  //      /*Glitched*/[]{return IS_CHILD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && AT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"Bug Rock",           {GLITCHLESS(IS_CHILD && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field",      {GLITCHLESS(true)}},
       {"GV Upper Stream",   {GLITCHLESS(true)}},
       {"GV Crate Ledge",    {GLITCHLESS(IS_CHILD || CAN_USE_LONGSHOT)}},
       {"GV Grotto Ledge",   {GLITCHLESS(true)}},
       {"GV Fortress Side",  {GLITCHLESS((IS_ADULT && (CAN_RIDE_EPONA || CAN_USE_LONGSHOT || logic->settings.gerudoFortress == GERUDOFORTRESS_OPEN || logic->items.carpenterRescue)) || (IS_CHILD && CAN_USE_HOOKSHOT))}},
                              //   /*Glitched*/[]{return (HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) || (IS_CHILD && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::HERO)) || (IS_ADULT && (CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED) ||
                              //                         (CAN_USE_HOVER_BOOTS && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) || (CanSurviveDamage && (BOMBS || HAS_BOMBCHUS) && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) || (BOMBS && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED))))));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Upper Stream", "Gerudo Valley", TIMEPASS, {}, {
   //Locations
       {"GV Waterfall Freestanding PoH", {GLITCHLESS(true)}},
       {"GV GS Bean Patch",              {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"GV Cow",                        {GLITCHLESS(IS_CHILD && CAN_PLAY_EPONAS_SONG)}},
                                              //     /*Glitched*/[]{return IS_CHILD && EponasSong && (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));}}},
       {"GV Gossip Stone",               {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",            {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Bean Plant Fairy",              {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"GV Lower Stream", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Lower Stream", "Gerudo Valley", TIMEPASS, {}, {}, {
   //Exits
       {"Lake Hylia", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Grotto Ledge", "Gerudo Valley", TIMEPASS, {}, {}, {
   //Exits
       {"GV Lower Stream",   {GLITCHLESS(true)}},
       {"GV Octorok Grotto", {GLITCHLESS(CAN_USE_SILVER_GAUNTLETS)}},
       {"GV Crate Ledge",    {GLITCHLESS(CAN_USE_LONGSHOT)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Crate Ledge", "Gerudo Valley", TIMEPASS, {}, {
   //Locations
       {"GV Crate Freestanding PoH", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"GV Lower Stream", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Fortress Side", "Gerudo Valley", TIMEPASS, {}, {
   //Locations
       {"GV Chest",          {GLITCHLESS(IS_ADULT && (CAN_USE_MEGATON_HAMMER || logic->tricks.gvHammerChest))}},
                                    //   /*Glitched*/[]{return IS_ADULT && (CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) && (CAN_TAKE_DAMAGETwice || CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED))));}}},
       {"GV Trade Saw",      {GLITCHLESS(IS_ADULT && POACHERS_SAW)}},
       {"GV GS Behind Tent", {GLITCHLESS(ADULT_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                    //   /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"GV GS Pillar",      {GLITCHLESS(ADULT_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
   }, {
   //Exits
       {"Gerudo Fortress",   {GLITCHLESS(true)}},
       {"GV Upper Stream",   {GLITCHLESS(true)}},
       {"Gerudo Valley",     {GLITCHLESS(IS_CHILD || CAN_RIDE_EPONA || CAN_USE_LONGSHOT || logic->settings.gerudoFortress == GERUDOFORTRESS_OPEN || logic->items.carpenterRescue)}},
                                // /*Glitched*/[]{return (HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED) ||
                                //                       (CAN_USE_HOVER_BOOTS && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) || (CanSurviveDamage && (BOMBS || HAS_BOMBCHUS) && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) || (BOMBS && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED))));}}},
       {"GV Carpenter Tent", {GLITCHLESS(IS_ADULT)}},
                                // /*Glitched*/[]{return GlitchGVTentAsChild.Value<bool>();}}},
       {"GV Storms Grotto",  {GLITCHLESS(IS_ADULT && CAN_OPEN_STORM_GROTTO)}},
                              //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_ADULT && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Carpenter Tent", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"GV Fortress Side", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Octorok Grotto", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"GV Grotto Ledge", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GV Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"GV Deku Scrub Grotto Rear",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"GV Deku Scrub Grotto Front", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"GV Fortress Side", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Gerudo Fortress", "Gerudo Fortress", NO_TIMEPASS, {
   //Events
       {"Carpenter Rescue", {GLITCHLESS(CAN_FINISH_GERUDOFORTRESS)}},
       {"GF Gate Open",     {GLITCHLESS(IS_ADULT && GERUDO_TOKEN)}},
       {"GTG Gate Open",    {GLITCHLESS(logic->items.gtgGateOpen || (IS_ADULT && GERUDO_TOKEN))}},
   }, {
   //Locations
       {"GF Chest",                     {GLITCHLESS(CAN_USE_HOVER_BOOTS || CAN_USE_SCARECROW || CAN_USE_LONGSHOT)}},
                                      //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE))) && (GERUDO_TOKEN || CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS || logic->tricks.gerudoKitchen);}}},
       {"GF HBA 1000 Points",           {GLITCHLESS(ADULT_DAY && GERUDO_TOKEN && CAN_RIDE_EPONA && BOW)}},
       {"GF HBA 1500 Points",           {GLITCHLESS(ADULT_DAY && GERUDO_TOKEN && CAN_RIDE_EPONA && BOW)}},
       {"Hideout Jail Guard 1 Torch",   {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
                                      //  /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
       {"Hideout Jail Guard 2 Torches", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
     //         /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
       {"Hideout Jail Guard 3 Torches", {GLITCHLESS((IS_ADULT || KOKIRI_SWORD || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD) && (GERUDO_TOKEN || CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS || logic->tricks.gerudoKitchen))}},
                                      //      /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) && (GERUDO_TOKEN || CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS || logic->tricks.gerudoKitchen);}}},
       {"Hideout Jail Guard 4 Torches", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
                                        //   /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
       {"Hideout Gerudo Token",         {GLITCHLESS(CAN_FINISH_GERUDOFORTRESS)}},
       {"GF GS Archery Range",          {GLITCHLESS(ADULT_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && GERUDO_TOKEN && CAN_GET_NIGHT_TIME_GS)}},
                                        //   /*Glitched*/[]{return IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && GlitchGFGuardSneak && AT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"GF GS Top Floor",              {GLITCHLESS(ADULT_NIGHT && (GERUDO_TOKEN || CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS || logic->tricks.gerudoKitchen) && CAN_GET_NIGHT_TIME_GS)}},
   }, {
   //Exits
       {"GV Fortress Side",                 {GLITCHLESS(true)}},
       {"GF Outside Gate",                  {GLITCHLESS(logic->items.gfGateOpen && true)}},
                                            //    /*Glitched*/[]{return (IS_CHILD && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::ADVANCED)) || ((IS_CHILD || ((CAN_USE_HOOKSHOT || CAN_USE_BOW || CAN_USE_BOOMERANG) && GlitchGFGuardSneak)) && ((CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE)) ||
                                            //                          CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)) && (CAN_USE_STICKS || (BiggoronSword && IS_ADULT) || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)));}}},
       //{"Gerudo Training Grounds Entryway", {GLITCHLESS(logic->items.gtgGateOpen && (IS_ADULT || logic->settings.shuffleDungeonEntrances))}},
                                            //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE) && (HOVER_BOOTS || CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::ADVANCED))) || ((IS_CHILD || ((CAN_USE_HOOKSHOT || CAN_USE_BOW || CAN_USE_BOOMERANG) && GlitchGFGuardSneak)) && ((CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                                            //                          CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)) && (CAN_USE_STICKS || (BiggoronSword && IS_ADULT) || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)));}}},
       {"GF Storms Grotto",                 {GLITCHLESS(IS_ADULT && CAN_OPEN_STORM_GROTTO)}},
                                            //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_ADULT && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GF Outside Gate", "Gerudo Fortress", NO_TIMEPASS, {
   //Events
       {"GF Gate Open", {[this]{return IS_ADULT && GERUDO_TOKEN && (logic->settings.shuffleGerudoToken || logic->settings.shuffleOverworldEntrances /*|| ShuffleSpecialIndoorEntrances*/);}}},
   }, {}, {
   //Exits
       {"Gerudo Fortress",         {GLITCHLESS((IS_ADULT && (HOOKSHOT || !logic->settings.shuffleOverworldEntrances)) || logic->items.gfGateOpen)}},
       {"Wasteland Near Fortress", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GF Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Gerudo Fortress", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Wasteland Near Fortress", "Haunted Wasteland", NO_TIMEPASS, {}, {}, {
   //Exits
       {"GF Outside Gate",   {GLITCHLESS(true)}},
       {"Haunted Wasteland", {GLITCHLESS(CAN_USE_HOVER_BOOTS || CAN_USE_LONGSHOT)}},
                              //   /*Glitched*/[]{return ((BOMBS || HAS_BOMBCHUS) && CanSurviveDamage && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) || (CAN_USE_MEGATON_HAMMER && CAN_SHIELD && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::INTERMEDIATE)) ||
                              //                         (BOMBS && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED)) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) || GlitchItemlessWasteland;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Haunted Wasteland", "Haunted Wasteland", NO_TIMEPASS, {}, {
   //Locations
       {"Wasteland Chest",            {GLITCHLESS(HAS_FIRE_SOURCE)}},
                                            //    /*Glitched*/[]{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE);}}},
       {"Wasteland Bombchu Salesman", {GLITCHLESS(ADULTS_WALLET && (IS_ADULT || STICKS || KOKIRI_SWORD))}},
                                            //    /*Glitched*/[]{return ADULTS_WALLET && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}},
       {"Wasteland GS",               {GLITCHLESS(CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)}},
                                            //    /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"Fairy Pot",                  {GLITCHLESS(HAS_BOTTLE)}},
       {"Nut Pot",                    {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Wasteland Near Colossus", {GLITCHLESS(logic->tricks.lensWasteland || CAN_USE_LENS_OF_TRUTH)}},
       {"Wasteland Near Fortress", {GLITCHLESS(CAN_USE_HOVER_BOOTS || CAN_USE_LONGSHOT)}},
                                    //   /*Glitched*/[]{return ((BOMBS || HAS_BOMBCHUS) && CanSurviveDamage && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) || (CAN_USE_MEGATON_HAMMER && CAN_SHIELD && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::INTERMEDIATE)) ||
                                    //                         (BOMBS && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED)) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) || GlitchItemlessWasteland;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Wasteland Near Colossus", "Haunted Wasteland", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Desert Colossus",   {GLITCHLESS(true)}},
       {"Haunted Wasteland", {GLITCHLESS(logic->tricks.reverseWasteland && true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Desert Colossus", "Desert Colossus", TIMEPASS, {}, {
   //Locations
       {"Colossus Freestanding PoH", {GLITCHLESS(IS_ADULT && HERE(CAN_PLANT_BEAN))}},
                                          //     /*Glitched*/[]{return (HOVER_BOOTS && CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED)) || (((IS_CHILD && (ChildCanAccess(SPIRIT_TEMPLE_OUTDOOR_HANDS) || ChildCanAccess(SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND) || ChildCanAccess(SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND))) ||
                                          //                           (IS_ADULT && (AdultCanAccess(SPIRIT_TEMPLE_OUTDOOR_HANDS) || AdultCanAccess(SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND) || AdultCanAccess(SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND)))) && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::ADVANCED) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE)));}}},
       {"Colossus GS Bean Patch",    {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"Colossus GS Tree",          {GLITCHLESS(ADULT_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
       {"Colossus GS Hill",          {GLITCHLESS(ADULT_NIGHT && (HERE(CAN_PLANT_BEAN) || CAN_USE_LONGSHOT || (logic->tricks.colossusGS && CAN_USE_HOOKSHOT)) && CAN_GET_NIGHT_TIME_GS)}},
                                            //   /*Glitched*/[]{return CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::EXPERT) && CAN_SHIELD && ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"Colossus Gossip Stone",     {GLITCHLESS(true)}},
       {"Fairy Pond",                {GLITCHLESS(CAN_PLAY_SONG_OF_STORMS && HAS_BOTTLE)}},
                          //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && BOMBS && CAN_TAKE_DAMAGE /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms;}}},
       {"Bug Rock",                  {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Colossus Great Fairy Fountain", {GLITCHLESS(HAS_EXPLOSIVES)}},
       //{"Spirit Temple Entryway",        {GLITCHLESS(true)}},
       {"Wasteland Near Colossus",       {GLITCHLESS(true)}},
       {"Colossus Grotto",               {GLITCHLESS(CAN_USE_SILVER_GAUNTLETS)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Desert Colossus From Spirit Lobby", "Desert Colossus", NO_TIMEPASS, {}, {
   //Locations
       {"Sheik at Colossus",  {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Desert Colossus",   {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Colossus Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"Colossus Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                            //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && BOMBS && CAN_TAKE_DAMAGE /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"Desert Colossus", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Colossus Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Colossus Deku Scrub Grotto Rear",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"Colossus Deku Scrub Grotto Front", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Desert Colossus", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Entrance", "Market Entrance", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Hyrule Field",       {GLITCHLESS(IS_ADULT || AT_DAY)}},
       {"Market",         {GLITCHLESS(true)}},
       {"Market Guard House", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market", "Market", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Market Entrance",            {GLITCHLESS(true)}},
       {"ToT Entrance",               {GLITCHLESS(true)}},
       {"Castle Grounds",             {GLITCHLESS(true)}},
       {"Market Bazaar",              {GLITCHLESS(CHILD_DAY)}},
       {"Market Mask Shop",           {GLITCHLESS(CHILD_DAY)}},
       {"Market Shooting Gallery",    {GLITCHLESS(CHILD_DAY)}},
       {"Market Bombchu Bowling",     {GLITCHLESS(IS_CHILD)}},
       {"Market Treasure Chest Game", {GLITCHLESS(CHILD_NIGHT)}},
       {"Market Potion Shop",         {GLITCHLESS(CHILD_DAY)}},
       {"Market Back Alley",          {GLITCHLESS(IS_CHILD)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Back Alley", "Market", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Market",                 {GLITCHLESS(true)}},
       {"Market Bombchu Shop",        {GLITCHLESS(AT_NIGHT)}},
       {"Market Dog Lady House",      {GLITCHLESS(true)}},
       {"Market Man in Green House",  {GLITCHLESS(AT_NIGHT)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ToT Entrance", "ToT Entrance", NO_TIMEPASS, {
   //Events

   }, {
   //Locations
       {"ToT Gossip Stone Left",         {GLITCHLESS(true)}},
       {"ToT Gossip Stone Left Center",  {GLITCHLESS(true)}},
       {"ToT Gossip Stone Right Center", {GLITCHLESS(true)}},
       {"ToT Gossip Stone Right",        {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",            {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Market",     {GLITCHLESS(true)}},
       {"Temple of Time", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Temple of Time", "", NO_TIMEPASS, {}, {
   //Locations
       {"ToT Light Arrows Cutscene", {GLITCHLESS(IS_ADULT && CAN_TRIGGER_LACS)}},
   }, {
   //Exits
       {"ToT Entrance",        {GLITCHLESS(true)}},
       {"Beyond Door of Time", {GLITCHLESS(logic->settings.openDoorOfTime == OPENDOOROFTIME_OPEN || (CAN_PLAY_SONG_OF_TIME && (logic->settings.openDoorOfTime == OPENDOOROFTIME_CLOSED || (HAS_ALL_STONES && OCARINA_OF_TIME))))}},
                                    //   /*Glitched*/[]{return SongOfTime && OpenDoorOfTime.Is(OPENDOOROFTIME_CLOSED) && (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::ADVANCED) ||
                                    //                         ((BUGS || FISH) && BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2)) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/ && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE)));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Beyond Door of Time", "", NO_TIMEPASS, {}, {
   //Locations
       {"Master Sword Pedestal", {GLITCHLESS(true)}},
       {"Sheik at Temple",       {GLITCHLESS(FOREST_MEDALLION && IS_ADULT)}},
   }, {
   //Exits
       {"Temple of Time", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Castle Grounds", "Castle Grounds", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Market",                {GLITCHLESS(true)}},
       {"Hyrule Castle Grounds", {GLITCHLESS(IS_CHILD)}},
       {"Ganons Castle Grounds", {GLITCHLESS(IS_ADULT)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Hyrule Castle Grounds", "Castle Grounds", TIMEPASS, {}, {
   //Locations
       {"HC Malon Egg",              {GLITCHLESS(true)}},
       {"HC GS Tree",                {GLITCHLESS(CAN_CHILD_ATTACK)}},
       {"HC Malon Gossip Stone",     {GLITCHLESS(true)}},
       {"HC Rock Wall Gossip Stone", {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",        {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Butterfly Fairy",           {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Rock",                  {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Castle Grounds",          {GLITCHLESS(true)}},
       {"HC Garden",               {GLITCHLESS(WEIRD_EGG || !logic->settings.shuffleWeirdEgg)}},
       {"HC Great Fairy Fountain", {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
                                    //   /*Glitched*/[]{return STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"HC Storms Grotto",        {GLITCHLESS(CAN_OPEN_STORM_GROTTO)}},
                                    //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HC Garden", "Castle Grounds", NO_TIMEPASS, {}, {}, {
   //Exits
       {"HC Garden Locations",   {GLITCHLESS(true)}},
       {"Hyrule Castle Grounds", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HC Garden Locations", "Castle Grounds", NO_TIMEPASS, {}, {
   //Locations
       {"HC Zeldas Letter", {GLITCHLESS(true)}},
       {"Song from Impa",   {GLITCHLESS(true)}},
   }, {
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HC Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"HC Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                      //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"Castle Grounds", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"HC Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"HC GS Storms Grotto",           {GLITCHLESS(CAN_BLAST_OR_SMASH && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                              //     /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"HC Storms Grotto Gossip Stone", {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
       {"Nut Pot",                       {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
       {"Gossip Stone Fairy",            {GLITCHLESS(CAN_BLAST_OR_SMASH && CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Wandering Bugs",                {GLITCHLESS(CAN_BLAST_OR_SMASH && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Castle Grounds", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Ganons Castle Grounds", "Castle Grounds", NO_TIMEPASS, {}, {
   //Locations                                   //the terrain was lowered such that you can't get this GS with a simple sword slash
       {"OGC GS", {GLITCHLESS(HAS_EXPLOSIVES || (IS_ADULT && (logic->tricks.outsideGanonsGS || BOW || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_USE_DINS_FIRE)))}},
   }, {
   //Exits
       {"Castle Grounds",           {GLITCHLESS(true)}},
       {"OGC Great Fairy Fountain", {GLITCHLESS(CAN_USE_GOLDEN_GAUNTLETS)}},
       //{"Ganons Castle Entryway",   {GLITCHLESS(CAN_BUILD_RAINBOW_BRIDGE)}},
                                    //    /*Glitched*/[]{return (HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::ADVANCED) || (HOVER_BOOTS && CAN_SHIELD && BOMBS && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::EXPERT)) || (HOVER_BOOTS && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::ADVANCED));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"OGC Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"OGC Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                        //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"Castle Grounds", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Guard House", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market 10 Big Poes",    {GLITCHLESS(IS_ADULT && logic->items.bigPoe)}},
       {"Market GS Guard House", {GLITCHLESS(IS_CHILD)}},
   }, {
   //Exits
       {"Market Entrance", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Bazaar", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Bazaar Item 1", {GLITCHLESS(true)}},
       {"Market Bazaar Item 2", {GLITCHLESS(true)}},
       {"Market Bazaar Item 3", {GLITCHLESS(true)}},
       {"Market Bazaar Item 4", {GLITCHLESS(true)}},
       {"Market Bazaar Item 5", {GLITCHLESS(true)}},
       {"Market Bazaar Item 6", {GLITCHLESS(true)}},
       {"Market Bazaar Item 7", {GLITCHLESS(true)}},
       {"Market Bazaar Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Mask Shop", "", NO_TIMEPASS, {
   //Events
       {"Skull Mask",    {[this]{return ZELDAS_LETTER && (logic->settings.completeMaskQuest || AT(AreaID::KakarikoVillage, IS_CHILD));}}},
       {"Mask of Truth", {[this]{return SKULL_MASK && (logic->settings.completeMaskQuest || (AT(AreaID::LostWoods, IS_CHILD && CAN_PLAY_SARIAS_SONG) &&
                                                                                            AT(AreaID::Graveyard, CHILD_DAY) &&
                                                                                            AT(AreaID::HyruleField, IS_CHILD && HAS_ALL_STONES)));}}},
   }, {}, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Shooting Gallery", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Shooting Gallery Reward", {GLITCHLESS(IS_CHILD)}},
   }, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Bombchu Bowling", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Bombchu Bowling First Prize",  {GLITCHLESS(FOUND_BOMBCHUS)}},
       {"Market Bombchu Bowling Second Prize", {GLITCHLESS(FOUND_BOMBCHUS)}},
       {"Market Bombchu Bowling Bombchus",     {GLITCHLESS(FOUND_BOMBCHUS)}},
   }, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Potion Shop", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Potion Shop Item 1", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 2", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 3", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 4", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 5", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 6", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 7", {GLITCHLESS(true)}},
       {"Market Potion Shop Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Treasure Chest Game", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Treasure Chest Game Reward",   {[this]{return (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 6) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1);}}},
                                                    //   /*Glitched*/[]{return logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF && (CAN_USE_FARORES_WIND && (HAS_BOTTLE || WEIRD_EGG) && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE));}}},
       {"Market Chest Game First Room Chest",  {[this]{return (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF);}}},
       {"Market Chest Game Second Room Chest", {[this]{return (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 2) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF);}}},
       {"Market Chest Game Third Room Chest",  {[this]{return (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 3) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF);}}},
       {"Market Chest Game Fourth Room Chest", {[this]{return (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 4) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF);}}},
       {"Market Chest Game Fifth Room Chest",  {[this]{return (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_SINGLE_KEYS && CHEST_GAME_SMALL_KEYS >= 5) ||
                                                          (logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_PACK && CHEST_GAME_SMALL_KEYS >= 1) ||
                                                          (CAN_USE_LENS_OF_TRUTH && logic->settings.shuffleChestGame == SHUFFLECHESTMINIGAME_OFF);}}},
   }, {
   //Exits
       {"Market", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Bombchu Shop", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Bombchu Shop Item 1", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 2", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 3", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 4", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 5", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 6", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 7", {GLITCHLESS(true)}},
       {"Market Bombchu Shop Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Market Back Alley", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Dog Lady House", "", NO_TIMEPASS, {}, {
   //Locations
       {"Market Lost Dog", {GLITCHLESS(CHILD_NIGHT)}},
   }, {
   //Exits
       {"Market Back Alley", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Market Man in Green House", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Market Back Alley", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kakariko Village", "Kakariko Village", NO_TIMEPASS, {
   //Events
       {"Kakariko Village Gate Open", {GLITCHLESS(IS_CHILD && (ZELDAS_LETTER || logic->settings.openKakariko == OPENKAKARIKO_OPEN))}},
   }, {
   //Locations
       {"Sheik in Kakariko",               {GLITCHLESS(IS_ADULT && FOREST_MEDALLION && FIRE_MEDALLION && WATER_MEDALLION)}},
       {"Kak Anju as Child",               {GLITCHLESS(CHILD_DAY)}},
       {"Kak Anju as Adult",               {GLITCHLESS(ADULT_DAY)}},
       {"Kak Trade Pocket Cucco",          {GLITCHLESS(ADULT_DAY && POCKET_EGG && logic->items.wakeUpAdultTalon)}},
       {"Kak GS House Under Construction", {GLITCHLESS(CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
       {"Kak GS Skulltula House",          {GLITCHLESS(CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
       {"Kak GS Guards House",             {GLITCHLESS(CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
       {"Kak GS Tree",                     {GLITCHLESS(CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
       {"Kak GS Watchtower",               {GLITCHLESS(CHILD_NIGHT && (SLINGSHOT || HAS_BOMBCHUS || CAN_USE_BOW || CAN_USE_LONGSHOT) && CAN_GET_NIGHT_TIME_GS)}},
                                                //     /*Glitched*/[]{return CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS && (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) || (STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE)));}}},
                                                //     /*Glitched*/[]{return ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS && ((HOVER_BOOTS && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE));}}},
       {"Bug Rock",                        {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Hyrule Field",                {GLITCHLESS(true)}},
       {"Kak Carpenter Boss House",    {GLITCHLESS(true)}},
       {"Kak House of Skulltula",      {GLITCHLESS(true)}},
       {"Kak Impas House",             {GLITCHLESS(true)}},
       {"Kak Windmill",                {GLITCHLESS(true)}},
       {"Kak Bazaar",                  {GLITCHLESS(ADULT_DAY)}},
                                        //   /*Glitched*/[]{return CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE);}}},
       {"Kak Shooting Gallery",        {GLITCHLESS(ADULT_DAY)}},
       //{"Bottom of the Well Entryway", {GLITCHLESS(logic->items.drainWell && (IS_CHILD || logic->settings.shuffleDungeonEntrances != SHUFFLEDUNGEONS_OFF))}},
                                        //   /*Glitched*/[]{return (IS_CHILD && (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) || (AT_NIGHT && (CanDoGlitch(GlitchType::NaviDive_Stick, GlitchDifficulty::NOVICE) || ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) ||
                                        //                         (CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || WEIRD_EGG))) && ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) ||
                                        //                         (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED)))))))) || (IS_ADULT && CAN_USE_LONGSHOT && AT_DAY && CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE));}}},
       {"Kak Potion Shop Front",       {GLITCHLESS(AT_DAY || IS_CHILD)}},
       {"Kak Redead Grotto",           {GLITCHLESS(CAN_OPEN_BOMB_GROTTO)}},
       {"Kak Impas Ledge",             {GLITCHLESS(CHILD_DAY)}},
                                        //   /*Glitched*/[]{return IS_ADULT && ((HOVER_BOOTS && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE));}}},
       {"Kak Impas Rooftop",           {GLITCHLESS(CAN_USE_HOOKSHOT)}},
       {"Kak Odd Medicine Rooftop",    {GLITCHLESS(CAN_USE_HOOKSHOT || (logic->tricks.manOnRoof && (IS_ADULT || AT_DAY || SLINGSHOT || HAS_BOMBCHUS || CAN_USE_BOW || CAN_USE_LONGSHOT)))}},
                                        //   /*Glitched*/[]{return logic->tricks.manOnRoof && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
       {"Graveyard",               {GLITCHLESS(true)}},
       {"Kak Behind Gate",             {GLITCHLESS(IS_ADULT || logic->items.kakarikoVillageGateOpen)}},
                                        //   /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Impas Ledge", "Kakariko Village", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kak Impas House Back", {GLITCHLESS(true)}},
       {"Kakariko Village",     {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Impas Rooftop", "Kakariko Village", NO_TIMEPASS, {}, {
   //Locations
       {"Kak GS Above Impas House", {GLITCHLESS(ADULT_NIGHT)}},
}, {
   //Exits
       {"Kak Impas Ledge",  {GLITCHLESS(true)}},
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Odd Medicine Rooftop", "Kakariko Village", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Man on Roof", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
       {"Kak Backyard",     {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Backyard", "Kakariko Village", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kakariko Village",          {GLITCHLESS(true)}},
       {"Kak Open Grotto",           {GLITCHLESS(true)}},
       {"Kak Odd Medicine Building", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Back",      {GLITCHLESS(ADULT_DAY)}},
                                      //   /*Glitched*/[]{return CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Carpenter Boss House", "", NO_TIMEPASS, {
   //Events
       {"Wake Up Adult Talon", {GLITCHLESS(IS_ADULT && POCKET_EGG)}},
   }, {}, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak House of Skulltula", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak 10 Gold Skulltula Reward", {[this]{return GOLD_SKULLTULA_TOKENS >= 10;}}},
       {"Kak 20 Gold Skulltula Reward", {[this]{return GOLD_SKULLTULA_TOKENS >= 20;}}},
       {"Kak 30 Gold Skulltula Reward", {[this]{return GOLD_SKULLTULA_TOKENS >= 30;}}},
       {"Kak 40 Gold Skulltula Reward", {[this]{return GOLD_SKULLTULA_TOKENS >= 40;}}},
       {"Kak 50 Gold Skulltula Reward", {[this]{return GOLD_SKULLTULA_TOKENS >= 50;}}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Impas House", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kak Impas House Near Cow", {GLITCHLESS(true)}},
       {"Kakariko Village",         {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Impas House Back", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Impas House Freestanding PoH", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Kak Impas Ledge",          {GLITCHLESS(true)}},
       {"Kak Impas House Near Cow", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Impas House Near Cow", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Impas House Cow", {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                      //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::ADVANCED) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/)) && EponasSong;}}},
}, {}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Windmill", "", NO_TIMEPASS, {
   //Events
       {"Drain Well", {GLITCHLESS(IS_CHILD && CAN_PLAY_SONG_OF_STORMS)}},
                          //   /*Glitched*/[]{return IS_CHILD && SongOfStorms && (CanDoGlitch(GlitchType::WindmillBombOI, GlitchDifficulty::ADVANCED) || ((FISH || BUGS) && CAN_SHIELD && ((BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2))) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) &&
                          //                         CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) || ((FISH || BUGS) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));}}},
   }, {
   //Locations
       {"Kak Windmill Freestanding PoH", {GLITCHLESS(CAN_USE_BOOMERANG || logic->items.dampesWindmillAccess || (IS_ADULT && CAN_USE_HOOKSHOT && logic->tricks.windmillPohHookshot))}},
                                                //   /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"Song from Windmill",            {GLITCHLESS(IS_ADULT && OCARINA)}},
                                                //   /*Glitched*/[]{return IS_ADULT && (CanDoGlitch(GlitchType::WindmillBombOI, GlitchDifficulty::EXPERT) || ((FISH || BUGS) && CAN_SHIELD && ((BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2))) || (DampesWindmillAccess || (IS_ADULT && CAN_USE_HOOKSHOT && logic->tricks.windmillPoHHookshot) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE))) &&
                                                //                         CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) || ((FISH || BUGS) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));}}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Bazaar", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Bazaar Item 1", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 2", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 3", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 4", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 5", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 6", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 7", {GLITCHLESS(true)}},
       {"Kak Bazaar Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Shooting Gallery", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Shooting Gallery Reward", {GLITCHLESS(IS_ADULT && BOW)}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Potion Shop Front", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Potion Shop Item 1", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 2", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 3", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 4", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 5", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 6", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 7", {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Item 8", {GLITCHLESS(IS_ADULT)}},
   }, {
   //Exits
       {"Kakariko Village",     {GLITCHLESS(true)}},
       {"Kak Potion Shop Back", {GLITCHLESS(IS_ADULT)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Potion Shop Back", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kak Backyard",          {GLITCHLESS(IS_ADULT)}},
       {"Kak Potion Shop Front", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Odd Medicine Building", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Trade Odd Mushroom", {GLITCHLESS(IS_ADULT && ODD_MUSHROOM)}},
   }, {
   //Exits
       {"Kak Backyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Redead Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Redead Grotto Chest", {GLITCHLESS(IS_ADULT || (STICKS || KOKIRI_SWORD || CAN_USE_DINS_FIRE || CAN_USE_MEGATON_HAMMER || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD))}},
   }, {
   //Exits
       {"Kakariko Village", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Open Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Kak Open Grotto Chest",         {GLITCHLESS(true)}},
       {"Kak Open Grotto Gossip Stone",  {GLITCHLESS(true)}},
       {"Butterfly Fairy",               {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                     {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                     {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Kak Backyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard", "Graveyard", NO_TIMEPASS, {}, {
   //Locations
       {"Graveyard Freestanding PoH",        {GLITCHLESS((IS_ADULT && HERE(CAN_PLANT_BEAN)) || CAN_USE_LONGSHOT || (logic->tricks.graveyardPoh && CAN_USE_BOOMERANG))}},
                                              //         /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::NOVICE);}}},
       {"Graveyard Dampe Gravedigging Tour", {GLITCHLESS(CHILD_NIGHT)}},
       {"Graveyard GS Wall",                 {GLITCHLESS(CHILD_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                              //         /*Glitched*/[]{return CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"Graveyard GS Bean Patch",           {GLITCHLESS(CAN_PLANT_BUGS && CAN_CHILD_ATTACK)}},
       {"Butterfly Fairy",                   {GLITCHLESS(CAN_USE_STICKS && CHILD_DAY)}},
       {"Bean Plant Fairy",                  {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS)}},
       {"Bug Rock",                          {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Graveyard Shield Grave",       {GLITCHLESS(IS_ADULT || CHILD_NIGHT)}},
       {"Graveyard Royal Familys Tomb",    {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                      //      /*Glitched*/[]{return (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/ ((BUGS || FISH) && CAN_SHIELD && (IS_CHILD || AdultCanAccess(GRAVEYARD_WARP_PAD_REGION) || (IS_ADULT && (HERE(CAN_PLANT_BEAN) || CAN_USE_LONGSHOT)) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2)))) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                      //                            ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
       {"Graveyard Heart Piece Grave",  {GLITCHLESS(IS_ADULT || CHILD_NIGHT)}},
       {"Graveyard Dampes Grave",       {GLITCHLESS(IS_ADULT)}},
       {"Graveyard Dampes House",       {GLITCHLESS(IS_ADULT || CHILD_NIGHT)}}, //TODO: This needs to be handled
       {"Kakariko Village",             {GLITCHLESS(true)}},
       {"Graveyard Warp Pad Region",    {GLITCHLESS(false)}},
                                    //        /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Shield Grave", "", NO_TIMEPASS, {}, {
   //Locations
       {"Graveyard Shield Grave Chest", {GLITCHLESS(true)}},
       {"Free Fairies",                 {GLITCHLESS(CAN_BLAST_OR_SMASH && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Graveyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Heart Piece Grave", "", NO_TIMEPASS, {}, {
   //Locations
       {"Graveyard Heart Piece Grave Chest", {GLITCHLESS(CAN_PLAY_SUNS_SONG)}},
                                                //       /*Glitched*/[]{return (/*CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::NOVICE) ||*/ ((BUGS || FISH) && CAN_SHIELD && (BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2))) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SunsSong;}}},
   }, {
   //Exits
       {"Graveyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Royal Familys Tomb", "", NO_TIMEPASS, {}, {
   //Locations
       {"Graveyard Royal Familys Tomb Chest", {GLITCHLESS(HAS_FIRE_SOURCE)}},
                                                //     /*Glitched*/[]{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE);}}},
       {"Song from Royal Familys Tomb",       {GLITCHLESS(IS_ADULT || (SLINGSHOT || BOOMERANG || STICKS || HAS_EXPLOSIVES || KOKIRI_SWORD || CAN_USE_MEGATON_HAMMER || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD || CAN_USE_BOW || CAN_USE_HOOKSHOT))}},
   }, {
   //Exits
       {"Graveyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Dampes Grave", "", NO_TIMEPASS, {
   //Events
       {"Dampes Windmill Access",                {GLITCHLESS(IS_ADULT && CAN_PLAY_SONG_OF_TIME)}},
                                               //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::WindmillBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                               //                          ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_ADULT && SongOfTime;}}},
   }, {
   //Locations
       {"Graveyard Hookshot Chest",              {GLITCHLESS(true)}},
       {"Graveyard Dampe Race Freestanding PoH", {GLITCHLESS(IS_ADULT || logic->tricks.childDampeRacePoh)}},
       {"Nut Pot",                               {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Graveyard", {GLITCHLESS(true)}},
       {"Kak Windmill",  {GLITCHLESS(IS_ADULT && CAN_PLAY_SONG_OF_TIME)}},
                          //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::WindmillBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                          //                         ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_ADULT && SongOfTime;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Dampes House", "", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Graveyard", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Graveyard Warp Pad Region", "Graveyard", NO_TIMEPASS, {}, {
   //Locations
       {"Graveyard Gossip Stone", {GLITCHLESS(true)}},
       {"Gossip Stone Fairy", {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Graveyard",               {GLITCHLESS(true)}},
       //{"Shadow Temple Entryway",  {GLITCHLESS(CAN_USE_DINS_FIRE || (logic->tricks.shadowFireArrowEntry && IS_ADULT && CAN_USE_FIRE_ARROWS))}},
                                  //       /*Glitched*/[]{return (CAN_USE_STICKS && (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE) || CAN_USE_FIRE_ARROWS)) || (CAN_TAKE_DAMAGE && (
                                  //                             CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE)));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Kak Behind Gate", "Kakariko Village", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kakariko Village",     {GLITCHLESS(IS_ADULT || logic->tricks.visibleCollisions || logic->items.kakarikoVillageGateOpen || logic->settings.openKakariko == OPENKAKARIKO_OPEN)}},
       {"Death Mountain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Death Mountain", "Death Mountain", TIMEPASS, {}, {
   //Locations
       {"DMT Chest",                    {GLITCHLESS(CAN_BLAST_OR_SMASH || (logic->tricks.dmtBombable && IS_CHILD && GORON_BRACELET))}},
                                              //    /*Glitched*/[]{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"DMT Freestanding PoH",         {GLITCHLESS(CAN_TAKE_DAMAGE || CAN_USE_HOVER_BOOTS || (IS_ADULT && HERE(CAN_PLANT_BEAN) && (HAS_EXPLOSIVES || GORON_BRACELET)))}},
       {"DMT GS Bean Patch",            {GLITCHLESS(CAN_PLANT_BUGS && (HAS_EXPLOSIVES || GORON_BRACELET || (logic->tricks.dmtSoilGS && (CAN_TAKE_DAMAGE || CAN_USE_HOVER_BOOTS) && CAN_USE_BOOMERANG)))}},
       {"DMT GS Near Kak",              {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
                                              //    /*Glitched*/[]{return (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);}}},
       {"DMT GS Above Dodongos Cavern", {GLITCHLESS(ADULT_NIGHT && MEGATON_HAMMER && CAN_GET_NIGHT_TIME_GS)}},
                                              //    /*Glitched*/[]{return ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS && CAN_USE_STICKS && ((CAN_TAKE_DAMAGETwice && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED));}}},
       {"Bean Plant Fairy", {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS && (HAS_EXPLOSIVES || GORON_BRACELET))}},
   }, {
   //Exits
       {"Kak Behind Gate",          {GLITCHLESS(true)}},
       {"Goron City",               {GLITCHLESS(true)}},
       {"Death Mountain Summit",    {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH) || (IS_ADULT && ((HERE(CAN_PLANT_BEAN) && GORON_BRACELET) || (HOVER_BOOTS && logic->tricks.dmtClimbHovers))))}},
                                    //    /*Glitched*/[]{return IS_ADULT && HERE(DEATH_MOUNTAIN_TRAIL, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
       //{"Dodongos Cavern Entryway", {GLITCHLESS(HAS_EXPLOSIVES || GORON_BRACELET || IS_ADULT)}},
       {"DMT Storms Grotto",        {GLITCHLESS(CAN_OPEN_STORM_GROTTO)}},
                                    //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Death Mountain Summit", "Death Mountain", TIMEPASS, {}, {
   //Locations
       {"DMT Trade Broken Sword",    {GLITCHLESS(IS_ADULT && BROKEN_GORONS_SWORD)}},
       {"DMT Trade Eyedrops",        {GLITCHLESS(IS_ADULT && EYEDROPS)}},
       {"DMT Trade Claim Check",     {GLITCHLESS(IS_ADULT && CLAIM_CHECK)}},
       {"DMT GS Falling Rocks Path", {GLITCHLESS(ADULT_NIGHT && MEGATON_HAMMER && CAN_GET_NIGHT_TIME_GS)}},
       {"DMT Gossip Stone",          {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",        {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Bug Rock",                  {GLITCHLESS(IS_CHILD && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Death Mountain",     {GLITCHLESS(true)}},
       {"DMC Upper Local",          {GLITCHLESS(true)}},
       {"DMT Owl Flight",           {GLITCHLESS(IS_CHILD)}},
       {"DMT Cow Grotto",           {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                  //      /*Glitched*/[]{return HERE(DEATH_MOUNTAIN_SUMMIT, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
       {"DMT Great Fairy Fountain", {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                                //        /*Glitched*/[]{return ((KOKIRI_SWORD || STICKS || IS_ADULT) && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::ADVANCED)) || (IS_CHILD && CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::EXPERT));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMT Owl Flight", "Death Mountain", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Kak Impas Rooftop", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMT Cow Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMT Cow Grotto Cow", {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                    //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                    //                          ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && EponasSong;}}},
   }, {
   //Exits
       {"Death Mountain Summit", {GLITCHLESS(true)}},

}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMT Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMT Storms Grotto Chest",        {GLITCHLESS(true)}},
       {"DMT Storms Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",                {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                      {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                      {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Death Mountain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMT Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMT Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                        //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                        //                          ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"Death Mountain Summit", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Goron City", "Goron City", NO_TIMEPASS, {
   //Events
       {"Goron City Child Fire",          {GLITCHLESS(IS_CHILD && CAN_USE_DINS_FIRE)}},
                                    //         /*Glitched*/[]{return IS_CHILD && CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE);}}},
       {"GC Woods Warp Open",             {GLITCHLESS(CAN_BLAST_OR_SMASH || CAN_USE_DINS_FIRE || CAN_USE_BOW || GORON_BRACELET || logic->items.goronCityChildFire)}},
                                    //         /*Glitched*/[]{return (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);}}},
       {"GC Darunias Door Open Child",    {GLITCHLESS(IS_CHILD && CAN_PLAY_ZELDAS_LULLABY)}},
                                    //         /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                    //                               ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_CHILD && ZeldasLullaby;}}},
       {"Stop GC Rolling Goron as Adult", {GLITCHLESS(IS_ADULT && (GORON_BRACELET || HAS_EXPLOSIVES || BOW || (logic->tricks.linkGoronDins && CAN_USE_DINS_FIRE)))}},
   }, {
   //Locations
       {"GC Maze Left Chest",        {GLITCHLESS(CAN_USE_MEGATON_HAMMER || CAN_USE_SILVER_GAUNTLETS || (logic->tricks.goronCityLeftmost && HAS_EXPLOSIVES && CAN_USE_HOVER_BOOTS))}},
                                      //         /*Glitched*/[]{return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
       {"GC Maze Center Chest",      {GLITCHLESS(CAN_BLAST_OR_SMASH  || CAN_USE_SILVER_GAUNTLETS)}},
       {"GC Maze Right Chest",       {GLITCHLESS(CAN_BLAST_OR_SMASH  || CAN_USE_SILVER_GAUNTLETS)}},
       {"GC Pot Freestanding PoH",   {GLITCHLESS(IS_CHILD && logic->items.goronCityChildFire && (BOMBS || (GORON_BRACELET && logic->tricks.goronCityPotWithStrength) || (HAS_BOMBCHUS && logic->tricks.goronCityPot)))}},
       {"GC Rolling Goron as Child", {GLITCHLESS(IS_CHILD && (HAS_EXPLOSIVES || (GORON_BRACELET && logic->tricks.childRollingWithStrength)))}},
       {"GC Rolling Goron as Adult", {GLITCHLESS(logic->items.stopGCRollingGoronAsAdult && true)}},
       {"GC GS Boulder Maze",        {GLITCHLESS(IS_CHILD && CAN_BLAST_OR_SMASH)}},
       {"GC GS Center Platform",     {GLITCHLESS(IS_ADULT)}},
       {"GC Medigoron",              {GLITCHLESS(IS_ADULT && ADULTS_WALLET && (CAN_BLAST_OR_SMASH || GORON_BRACELET))}},
       {"GC Maze Gossip Stone",      {GLITCHLESS(CAN_BLAST_OR_SMASH || CAN_USE_SILVER_GAUNTLETS)}},
       {"GC Medigoron Gossip Stone", {GLITCHLESS(CAN_BLAST_OR_SMASH || GORON_BRACELET)}},
       {"Gossip Stone Fairy",        {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE && (CAN_BLAST_OR_SMASH || CAN_USE_SILVER_GAUNTLETS))}},
       {"Stick Pot",                 {GLITCHLESS(IS_CHILD)}},
       {"Bug Rock",                  {GLITCHLESS((CAN_BLAST_OR_SMASH || CAN_USE_SILVER_GAUNTLETS) && HAS_BOTTLE)}},
   }, {
   //Exits
       {"Death Mountain",       {GLITCHLESS(true)}},
       {"GC Woods Warp",        {GLITCHLESS(logic->items.gcWoodsWarpOpen && true)}},
       {"GC Shop",              {GLITCHLESS((IS_ADULT && logic->items.stopGCRollingGoronAsAdult) || (IS_CHILD && (CAN_BLAST_OR_SMASH || GORON_BRACELET || logic->items.goronCityChildFire || CAN_USE_BOW)))}},
                                  //  /*Glitched*/[]{return IS_CHILD && STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"GC Darunias Chamber",  {GLITCHLESS((IS_ADULT && logic->items.stopGCRollingGoronAsAdult) || logic->items.gcDaruniasDoorOpenChild)}},
       {"GC Grotto Platform",   {[this]{return IS_ADULT && ((CAN_PLAY_SONG_OF_TIME && ((EFFECTIVE_HEALTH > 2) || CAN_USE_GORON_TUNIC || CAN_USE_LONGSHOT || CAN_USE_NAYRUS_LOVE)) || (EFFECTIVE_HEALTH > 1 && CAN_USE_GORON_TUNIC && CAN_USE_HOOKSHOT) || (CAN_USE_NAYRUS_LOVE && CAN_USE_HOOKSHOT));}}},
                                //    /*Glitched*/[]{return (HAS_BOMBCHUS && ((IS_CHILD && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE))) || (IS_CHILD && CAN_USE_LONGSHOT);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GC Woods Warp", "Goron City", NO_TIMEPASS, {
   //Events
       {"GC Woods Warp Open", {GLITCHLESS(CAN_BLAST_OR_SMASH || CAN_USE_DINS_FIRE)}},
   }, {}, {
   //Exits
       {"Goron City", {GLITCHLESS(CAN_LEAVE_FOREST && logic->items.gcWoodsWarpOpen)}},
       {"Lost Woods", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GC Darunias Chamber", "Goron City", NO_TIMEPASS, {
   //Events
       {"Goron City Child Fire", {GLITCHLESS(IS_CHILD && CAN_USE_STICKS)}},
   }, {
   //Locations
       {"GC Darunias Joy", {GLITCHLESS(IS_CHILD && CAN_PLAY_SARIAS_SONG)}},
                                  //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && ((BOMBS && (CanSurviveDamage || (Fairy && NumBottles >= 2))) || logic->items.gcDaruniasDoorOpenChild) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                  //                         ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_CHILD && SariasSong;}}},
   }, {
   //Exits
       {"Goron City",      {GLITCHLESS(true)}},
       {"DMC Lower Local", {GLITCHLESS(IS_ADULT)}},
                            //   /*Glitched*/[]{return IS_CHILD && logic->items.gcDaruniasDoorOpenChild && (KOKIRI_SWORD || STICKS) && GlitchOccamsStatue;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GC Grotto Platform", "Goron City", NO_TIMEPASS, {}, {}, {
   //Exits
       {"GC Grotto",  {GLITCHLESS(true)}},
       {"Goron City", {[this]{return EFFECTIVE_HEALTH > 2 || CAN_USE_GORON_TUNIC || CAN_USE_NAYRUS_LOVE || ((IS_CHILD || CAN_PLAY_SONG_OF_TIME) && CAN_USE_LONGSHOT);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GC Shop", "", NO_TIMEPASS, {}, {
   //Locations
       {"GC Shop Item 1", {GLITCHLESS(true)}},
       {"GC Shop Item 2", {GLITCHLESS(true)}},
       {"GC Shop Item 3", {GLITCHLESS(true)}},
       {"GC Shop Item 4", {GLITCHLESS(true)}},
       {"GC Shop Item 5", {GLITCHLESS(true)}},
       {"GC Shop Item 6", {GLITCHLESS(true)}},
       {"GC Shop Item 7", {GLITCHLESS(true)}},
       {"GC Shop Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Goron City", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"GC Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"GC Deku Scrub Grotto Left",   {GLITCHLESS(CAN_STUN_DEKU)}},
       {"GC Deku Scrub Grotto Right",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"GC Deku Scrub Grotto Center", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"GC Grotto Platform", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Upper Nearby", "Death Mountain Crater", NO_TIMEPASS, {}, {}, {
   //Exits
       {"DMC Upper Local",       {[this]{return FIRE_TIMER >= 48;}}},
       {"Death Mountain Summit", {GLITCHLESS(true)}},
       {"DMC Upper Grotto",      {[this]{return HERE(CAN_BLAST_OR_SMASH && (FIRE_TIMER >= 8 || HEARTS >= 3));}}},
                                  //   /*Glitched*/[]{return HERE(DMC_UPPER_NEARBY, []{return CAN_USE_STICKS && FIRE_TIMER >= 48 && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}}
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Upper Local", "Death Mountain Crater", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Wall Freestanding PoH", {[this]{return FIRE_TIMER >= 16 || HEARTS >= 3;}}},
       {"DMC GS Crate",              {[this]{return (FIRE_TIMER >= 8 || HEARTS >= 3) && IS_CHILD && CAN_CHILD_ATTACK;}}},
       {"DMC Gossip Stone",          {[this]{return HAS_EXPLOSIVES && (FIRE_TIMER >= 16 || HEARTS >= 3);}}},
       {"Gossip Stone Fairy",        {[this]{return HAS_EXPLOSIVES && CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && (FIRE_TIMER >= 16 || HEARTS >= 3) && HAS_BOTTLE;}}},
   }, {
   //Exits
       {"DMC Upper Nearby",         {GLITCHLESS(true)}},
       {"DMC Ladder Area Nearby",   {[this]{return FIRE_TIMER >= 16 || HEARTS >= 3;}}},
       {"DMC Central Nearby",       {[this]{return IS_ADULT && CAN_USE_GORON_TUNIC && CAN_USE_DISTANT_SCARECROW && ((EFFECTIVE_HEALTH > 2) || (FAIRY && logic->settings.shuffleDungeonEntrances != SHUFFLEDUNGEONS_OFF) || CAN_USE_NAYRUS_LOVE);}}},
                                  //      /*Glitched*/[]{return FIRE_TIMER >= 24 && CAN_TAKE_DAMAGE && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}},
       {"DMC Lower Nearby",         {GLITCHLESS(false)}},
                                  //      /*Glitched*/[]{return FIRE_TIMER >= 24 && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Ladder Area Nearby", "Death Mountain Crater", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Deku Scrub", {GLITCHLESS(IS_CHILD && CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"DMC Upper Nearby", {[this]{return HEARTS >= 3;}}},
       {"DMC Lower Nearby", {[this]{return HEARTS >= 3 && (CAN_USE_HOVER_BOOTS || (logic->tricks.craterUpperToLower && IS_ADULT && CAN_USE_MEGATON_HAMMER));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Lower Nearby", "Death Mountain Crater", NO_TIMEPASS, {}, {}, {
   //Exits
       {"DMC Lower Local",          {[this]{return FIRE_TIMER >= 48;}}},
       {"GC Darunias Chamber",      {GLITCHLESS(true)}},
       {"DMC Great Fairy Fountain", {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
                                  //      /*Glitched*/[]{return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) || (FIRE_TIMER >= 48 && CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) && (CAN_TAKE_DAMAGETwice || CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED))) ||
                                  //                            (BOMBS && CAN_SHIELD && FIRE_TIMER >= 48 && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::EXPERT)) || HERE(DMC_UPPER_LOCAL, []{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::ADVANCED);});}}},
       {"DMC Hammer Grotto",        {GLITCHLESS(IS_ADULT && CAN_USE_MEGATON_HAMMER)}},
                                  //      /*Glitched*/[]{return IS_ADULT && FIRE_TIMER >= 48 && CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) && (CAN_TAKE_DAMAGETwice || CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Lower Local", "Death Mountain Crater", NO_TIMEPASS, {}, {}, {
   //Exits
       {"DMC Lower Nearby",       {GLITCHLESS(true)}},
       {"DMC Ladder Area Nearby", {GLITCHLESS(true)}},
       {"DMC Central Nearby",     {[this]{return (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT) && (FIRE_TIMER >= 8 || HEARTS >= 3);}}},
                                //      /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) && (FIRE_TIMER >= 8 || HEARTS >= 3);}}},
       {"DMC Fire Temple Entrance", {[this]{return (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT) && FIRE_TIMER >= 24;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Central Nearby", "Death Mountain Crater", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Volcano Freestanding PoH", {[this]{return IS_ADULT && HEARTS >= 3 && (HERE(CAN_PLANT_BEAN) || (logic->tricks.craterBeanPohWithHovers && HOVER_BOOTS));}}},
                                        //          /*Glitched*/[]{return HERE(DMC_LOWER_LOCAL, []{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) && FIRE_TIMER >= 24;});}}},
       {"Sheik in Crater",              {[this]{return IS_ADULT && (FIRE_TIMER >= 8 || HEARTS >= 3);}}},
   }, {
   //Exits
       {"DMC Central Local", {[this]{return FIRE_TIMER >= 48;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Central Local", "Death Mountain Crater", NO_TIMEPASS, {}, {
   //Locations
       {"DMC GS Bean Patch", {[this]{return (FIRE_TIMER >= 8 || HEARTS >= 3) && CAN_PLANT_BUGS && CAN_CHILD_ATTACK;}}},
       {"Bean Plant Fairy", {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS)}},
   }, {
   //Exits
       {"DMC Central Nearby",   {GLITCHLESS(true)}},
       {"DMC Lower Nearby",     {GLITCHLESS((IS_ADULT && HERE(CAN_PLANT_BEAN)) || CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT)}},
                                  //  /*Glitched*/[]{return IS_CHILD && HEARTS >= 3 && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
       {"DMC Upper Nearby",     {GLITCHLESS(IS_ADULT && HERE(CAN_PLANT_BEAN))}},
       {"DMC Fire Temple Entrance", {[this]{return (IS_CHILD && HEARTS >= 3 && logic->settings.shuffleDungeonEntrances != SHUFFLEDUNGEONS_OFF) || (IS_ADULT && FIRE_TIMER >= 24);}}},
                                //    /*Glitched*/[]{return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) && FIRE_TIMER >= 48;}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Fire Temple Entrance", "Death Mountain Crater", NO_TIMEPASS, {}, {}, {
   //Exits
       {"DMC Central Nearby", {GLITCHLESS(CAN_USE_GORON_TUNIC)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                        //    /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CAN_TAKE_DAMAGE || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                        //                          ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"DMC Lower Local", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Upper Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Upper Grotto Chest",        {GLITCHLESS(true)}},
       {"DMC Upper Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",               {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                     {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                     {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"DMC Upper Local", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"DMC Hammer Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"DMC Deku Scrub Grotto Left",   {GLITCHLESS(CAN_STUN_DEKU)}},
       {"DMC Deku Scrub Grotto Right",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"DMC Deku Scrub Grotto Center", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"DMC Lower Local", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZR Front", "Zora River", TIMEPASS, {}, {
   //Locations
       {"ZR GS Tree", {GLITCHLESS(IS_CHILD && CAN_CHILD_ATTACK)}},
   }, {
   //Exits
       {"Zora River",   {GLITCHLESS(IS_ADULT || CAN_BLAST_OR_SMASH)}},
                      //      /*Glitched*/[]{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);}}},
       {"Hyrule Field", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Zora River", "Zora River", TIMEPASS, {}, {
   //Locations
       {"ZR Magic Bean Salesman",               {GLITCHLESS(IS_CHILD)}},
       {"ZR Frogs Ocarina Game",                {GLITCHLESS(IS_CHILD && CAN_PLAY_ZELDAS_LULLABY && CAN_PLAY_SARIAS_SONG && CAN_PLAY_SUNS_SONG && CAN_PLAY_EPONAS_SONG && CAN_PLAY_SONG_OF_TIME && CAN_PLAY_SONG_OF_STORMS)}},
                                                    //      /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::ADVANCED) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                                    //                            ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_CHILD && ZeldasLullaby && SariasSong && SunsSong && EponasSong && SongOfTime && SongOfStorms;}}},
       {"ZR Frogs in the Rain",                 {GLITCHLESS(IS_CHILD && CAN_PLAY_SONG_OF_STORMS)}},
                                                    //      /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::ADVANCED) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                                    //                            ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_CHILD && SongOfStorms;}}},
       {"ZR Near Open Grotto Freestanding PoH", {GLITCHLESS(IS_CHILD || CAN_USE_HOVER_BOOTS || (IS_ADULT && logic->tricks.zoraRiverLower))}},
       {"ZR Near Domain Freestanding PoH",      {GLITCHLESS(IS_CHILD || CAN_USE_HOVER_BOOTS || (IS_ADULT && logic->tricks.zoraRiverUpper))}},
       {"ZR GS Ladder",                         {GLITCHLESS(CHILD_NIGHT && CAN_CHILD_ATTACK && CAN_GET_NIGHT_TIME_GS)}},
       {"ZR GS Near Raised Grottos",            {GLITCHLESS(ADULT_NIGHT && (HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
       {"ZR GS Above Bridge",                   {GLITCHLESS(ADULT_NIGHT && HOOKSHOT && CAN_GET_NIGHT_TIME_GS)}},
       {"ZR Near Grottos Gossip Stone",         {GLITCHLESS(true)}},
       {"ZR Near Domain Gossip Stone",          {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",                   {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
       {"Bean Plant Fairy",                     {GLITCHLESS(HERE(CAN_PLANT_BEAN) && CAN_PLAY_SONG_OF_STORMS)}},
       {"Butterfly Fairy",                      {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                            {GLITCHLESS(CAN_CUT_SHRUBS)}},
   }, {
   //Exits
       {"ZR Front",            {GLITCHLESS(true)}},
       {"ZR Open Grotto",      {GLITCHLESS(true)}},
       {"ZR Fairy Grotto",     {GLITCHLESS(HERE(CAN_BLAST_OR_SMASH))}},
                              //     /*Glitched*/[]{return HERE(ZORAS_RIVER, []{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);});}}},
       {"Lost Woods",          {GLITCHLESS(SILVER_SCALE || CAN_USE_IRON_BOOTS)}},
                              //     /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) || (CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || (IS_ADULT && (HasBoots || CLAIM_CHECK)) || (IS_CHILD && WEIRD_EGG)))) &&
                              //                           ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED))));}}},
       {"ZR Storms Grotto",    {GLITCHLESS(CAN_OPEN_STORM_GROTTO)}},
                              //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                              //                           ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
       {"ZR Behind Waterfall", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                              //     /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED) || ((CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                              //                           ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZR Behind Waterfall", "Zora River", TIMEPASS, {}, {}, {
   //Exits
       {"Zora River",   {GLITCHLESS(true)}},
       {"Zoras Domain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZR Open Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"ZR Open Grotto Chest",        {GLITCHLESS(true)}},
       {"ZR Open Grotto Gossip Stone", {GLITCHLESS(true)}},
       {"Butterfly Fairy",             {GLITCHLESS(CAN_USE_STICKS && HAS_BOTTLE)}},
       {"Bug Shrub",                   {GLITCHLESS(CAN_CUT_SHRUBS && HAS_BOTTLE)}},
       {"Lone Fish",                   {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Zora River", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZR Fairy Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Zora River", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZR Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"ZR Deku Scrub Grotto Rear",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"ZR Deku Scrub Grotto Front", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Zora River", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Zoras Domain", "Zoras Domain", NO_TIMEPASS, {
   //Events
       {"Deliver Letter",   {GLITCHLESS(RUTOS_LETTER && IS_CHILD && logic->settings.zoraFountain != ZORASFOUNTAIN_OPEN)}},
       {"King Zora Thawed", {GLITCHLESS(IS_ADULT && BLUE_FIRE)}},
   }, {
   //Locations
       {"ZD Diving Minigame",     {GLITCHLESS(IS_CHILD)}},
       {"ZD Chest",               {GLITCHLESS(IS_CHILD && CAN_USE_STICKS)}},
       {"ZD King Zora Thawed",    {GLITCHLESS(logic->items.kingZoraThawed && true)}},
       {"ZD Trade Prescription",  {GLITCHLESS(logic->items.kingZoraThawed && PRESCRIPTION)}},
       {"ZD GS Frozen Waterfall", {GLITCHLESS(ADULT_NIGHT && ((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_USE_SLINGSHOT || BOW || MAGIC_METER || logic->tricks.domainGS) && CAN_GET_NIGHT_TIME_GS)}},
       {"ZD Gossip Stone",        {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",     {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
       {"Nut Pot",                {GLITCHLESS(true)}},
       {"Stick Pot",              {GLITCHLESS(IS_CHILD)}},
       {"Fish Group",             {GLITCHLESS(IS_CHILD && HAS_BOTTLE)}},
   }, {
   //Exits
       {"ZR Behind Waterfall", {GLITCHLESS(true)}},
       {"Lake Hylia",          {GLITCHLESS(IS_CHILD && (SILVER_SCALE || CAN_USE_IRON_BOOTS))}},
                                //   /*Glitched*/[]{return (IS_ADULT && GlitchZDOoBJumpSlash) || (IS_CHILD && CAN_USE_FARORES_WIND && (FaroresWindAnywhere || (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && (HAS_BOTTLE || WEIRD_EGG))) &&
                                //                         ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED))));}}},
       {"ZD Behind King Zora", {GLITCHLESS(logic->items.deliverLetter || logic->settings.zoraFountain == ZORASFOUNTAIN_OPEN || (logic->settings.zoraFountain == ZORASFOUNTAIN_ADULT && IS_ADULT))}},
                                //   /*Glitched*/[]{return ((IS_CHILD || CAN_USE_IRON_BOOTS) && CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::NOVICE) ||
                                //                         CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}},
       {"ZD Shop",             {GLITCHLESS(IS_CHILD || BLUE_FIRE)}},
                                //   /*Glitched*/[]{return GlitchZDOoBJumpSlash.Value<bool>();}}},
       {"ZD Storms Grotto",    {GLITCHLESS(CAN_OPEN_STORM_GROTTO)}},
                                //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                //                         ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && SongOfStorms && (ShardOfAgony || logic->tricks.grottosWithoutAgony);}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZD Behind King Zora", "Zoras Domain", NO_TIMEPASS, {}, {}, {
   //Exits
       {"Zoras Domain",   {GLITCHLESS(logic->items.deliverLetter || logic->settings.zoraFountain == ZORASFOUNTAIN_OPEN || (logic->settings.zoraFountain == ZORASFOUNTAIN_ADULT && IS_ADULT))}},
                            //  /*Glitched*/[]{return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::NOVICE) || (CAN_USE_LONGSHOT && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE)) || (BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
       {"Zoras Fountain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZD Shop", "", NO_TIMEPASS, {}, {
   //Locations
       {"ZD Shop Item 1", {GLITCHLESS(true)}},
       {"ZD Shop Item 2", {GLITCHLESS(true)}},
       {"ZD Shop Item 3", {GLITCHLESS(true)}},
       {"ZD Shop Item 4", {GLITCHLESS(true)}},
       {"ZD Shop Item 5", {GLITCHLESS(true)}},
       {"ZD Shop Item 6", {GLITCHLESS(true)}},
       {"ZD Shop Item 7", {GLITCHLESS(true)}},
       {"ZD Shop Item 8", {GLITCHLESS(true)}},
   }, {
   //Exits
       {"Zoras Domain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZD Storms Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
   }, {
   //Exits
       {"Zoras Domain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Zoras Fountain", "Zoras Fountain", NO_TIMEPASS, {}, {
   //Locations
       {"ZF Iceberg Freestanding PoH", {GLITCHLESS(IS_ADULT)}},
       {"ZF Bottom Freestanding PoH",  {[this]{return IS_ADULT && IRON_BOOTS && WATER_TIMER >= 24;}}},
       {"ZF GS Tree",                  {GLITCHLESS(IS_CHILD)}},
       {"ZF GS Above the Log",         {GLITCHLESS(CHILD_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                      //           /*Glitched*/[]{return CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
       {"ZF GS Hidden Cave",           {GLITCHLESS(CAN_USE_SILVER_GAUNTLETS && CAN_BLAST_OR_SMASH && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && ADULT_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
                                      //           /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::INTERMEDIATE) && IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && AT_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
       {"ZF Fairy Gossip Stone",       {GLITCHLESS(true)}},
       {"ZF Jabu Gossip Stone",        {GLITCHLESS(true)}},
       {"Gossip Stone Fairy",          {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS && HAS_BOTTLE)}},
       {"Butterfly Fairy",             {GLITCHLESS(CAN_USE_STICKS && CHILD_DAY && HAS_BOTTLE)}},
   }, {
   //Exits
       {"ZD Behind King Zora",       {GLITCHLESS(true)}},
       //{"Jabu Jabus Belly Entryway", {GLITCHLESS(IS_CHILD && FISH)}},
                                      //   /*Glitched*/[]{return (IS_CHILD && CAN_USE_STICKS && GlitchJabuStickRecoil) || (IS_ADULT && GlitchJabuAdult);}}},
       //{"Ice Cavern Entryway",       {GLITCHLESS(IS_ADULT)}},
                                      //   /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);}}},
       {"ZF Great Fairy Fountain",   {GLITCHLESS(HAS_EXPLOSIVES || (CAN_USE_SILVER_GAUNTLETS && MEGATON_HAMMER && logic->tricks.zfGreatFairy))}},
                                      //   /*Glitched*/[]{return IS_CHILD && (KOKIRI_SWORD || STICKS) && CAN_SHIELD && (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::ADVANCED) || (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)));}}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"ZF Great Fairy Fountain", "", NO_TIMEPASS, {}, {
   //Locations
       {"ZF Great Fairy Reward", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
                                        //   /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                        //                         ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && ZeldasLullaby;}}},
   }, {
   //Exits
       {"Zoras Fountain", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"Lon Lon Ranch", "Lon Lon Ranch", NO_TIMEPASS, {
   //Events
       {"Epona",     {GLITCHLESS(CAN_PLAY_EPONAS_SONG && ADULT_DAY)}},
       {"Links Cow", {GLITCHLESS(CAN_PLAY_EPONAS_SONG && ADULT_DAY)}},
   }, {
   //Locations
       {"Song from Malon",     {GLITCHLESS(CHILD_DAY && ZELDAS_LETTER && OCARINA)}},
                                    //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
                                    //                           ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) && IS_CHILD && ZELDAS_LETTER && AT_DAY;}}},
       {"LLR GS Tree",         {GLITCHLESS(IS_CHILD)}},
       {"LLR GS Rain Shed",    {GLITCHLESS(CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS)}},
       {"LLR GS House Window", {GLITCHLESS(CHILD_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
       {"LLR GS Back Wall",    {GLITCHLESS(CHILD_NIGHT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) && CAN_GET_NIGHT_TIME_GS)}},
                                    //     /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CHILD_NIGHT && CAN_GET_NIGHT_TIME_GS;}}},
   }, {
   //Exits
       {"Hyrule Field",     {GLITCHLESS(true)}},
       {"LLR Talons House", {GLITCHLESS(true)}},
       {"LLR Stables",      {GLITCHLESS(true)}},
       {"LLR Tower",        {GLITCHLESS(true)}},
       {"LLR Grotto",       {GLITCHLESS(IS_CHILD)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LLR Talons House", "", NO_TIMEPASS, {}, {
   //Locations
       {"LLR Talons Chickens", {GLITCHLESS(CHILD_DAY && ZELDAS_LETTER)}},
   }, {
   //Exits
       {"Lon Lon Ranch", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LLR Stables", "", NO_TIMEPASS, {}, {
   //Locations
       {"LLR Stables Left Cow",  {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                      //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/ && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE))) && EponasSong;}}},
       {"LLR Stables Right Cow", {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                      //     /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) || ((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (Fairy && NumBottles >= 2)) /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/ && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE))) && EponasSong;}}},
   }, {
   //Exits
       {"Lon Lon Ranch", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LLR Tower", "", NO_TIMEPASS, {}, {
   //Locations
       {"LLR Freestanding PoH", {GLITCHLESS(IS_CHILD)}},
       {"LLR Tower Left Cow",   {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                    //      /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/ && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE))) && EponasSong;}}},
       {"LLR Tower Right Cow",  {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
                                    //      /*Glitched*/[]{return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) || ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/ && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE))) && EponasSong;}}},
   }, {
   //Exits
       {"Lon Lon Ranch", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);

err = ProcessArea(
{"LLR Grotto", "", NO_TIMEPASS, {}, {
   //Locations
       {"LLR Deku Scrub Grotto Left",   {GLITCHLESS(CAN_STUN_DEKU)}},
       {"LLR Deku Scrub Grotto Right",  {GLITCHLESS(CAN_STUN_DEKU)}},
       {"LLR Deku Scrub Grotto Center", {GLITCHLESS(CAN_STUN_DEKU)}},
   }, {
   //Exits
       {"Lon Lon Ranch", {GLITCHLESS(true)}},
}});
BUILD_ERROR_CHECK(err);
//
// /*--------------------------
// |    VANILLA/MQ DECIDERS   |
// ---------------------------*/
// {"Deku Tree Entryway", "Deku Tree", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Deku Tree Lobby",      {[this]{return Dungeon::DekuTree.IsVanilla();}}},
//        {"Deku Tree MQ Lobby",   {[this]{return Dungeon::DekuTree.IsMQ();}}},
//        {"KF Outside Deku Tree", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Entryway", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Beginning",    {[this]{return Dungeon::DodongosCavern.IsVanilla();}}},
//        {"Dodongos Cavern MQ Beginning", {[this]{return Dungeon::DodongosCavern.IsMQ();}}},
//        {"Death Mountain",         {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Entryway", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Beginning",    {[this]{return Dungeon::JabuJabusBelly.IsVanilla();}}},
//        {"Jabu Jabus Belly MQ Beginning", {[this]{return Dungeon::JabuJabusBelly.IsMQ();}}},
//        {"Zoras Fountain",                {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Entryway", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple First Room", {[this]{return Dungeon::ForestTemple.IsVanilla();}}},
//        {"Forest Temple MQ Lobby",   {[this]{return Dungeon::ForestTemple.IsMQ();}}},
//        {"Sacred Forest Meadow",     {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Entryway", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple First Room", {[this]{return Dungeon::FireTemple.IsVanilla();}}},
//        {"Fire Temple MQ Lower",   {[this]{return Dungeon::FireTemple.IsMQ();}}},
//        {"DMC Central Local",      {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Entryway", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Lobby",    {[this]{return Dungeon::WaterTemple.IsVanilla();}}},
//        {"Water Temple MQ Lobby", {[this]{return Dungeon::WaterTemple.IsMQ();}}},
//        {"Lake Hylia",            {GLITCHLESS(true)}},
// }},
//
// {"Spirit Temple Entryway", "Spirit Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Spirit Temple Lobby",    {[this]{return Dungeon::SpiritTemple.IsVanilla();}}},
//        {"Spirit Temple MQ Lobby", {[this]{return Dungeon::SpiritTemple.IsMQ();}}},
//        {"Desert Colossus",        {GLITCHLESS(true)}},
// }},
//
// {"Shadow Temple Entryway", "Shadow Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Shadow Temple Beginning",    {[this]{return Dungeon::ShadowTemple.IsVanilla() && (logic->tricks.lensShadow || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT);}}},
//                                           /*Glitched*/[]{return Dungeon::ShadowTemple.IsVanilla() && (logic->tricks.lensShadow || CAN_USE_LENS_OF_TRUTH) && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Shadow Temple MQ Beginning", {[this]{return Dungeon::ShadowTemple.IsMQ()    && (logic->tricks.lensShadowMQ || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT);}}},
//                                           /*Glitched*/[]{return Dungeon::ShadowTemple.IsMQ()    && (logic->tricks.lensShadowMQ || CAN_USE_LENS_OF_TRUTH) && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Graveyard Warp Pad Region",  {GLITCHLESS(true)}},
// }},
//
// {"Bottom of the Well Entryway", "Bottom of the Well", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Bottom Of the Well Main Area",    {[this]{return Dungeon::BottomOfTheWell.IsVanilla() && IS_CHILD && (CAN_CHILD_ATTACK || Nuts);}}},
//                                                /*Glitched*/[]{return Dungeon::BottomOfTheWell.IsVanilla() && IS_CHILD && CAN_USE_MEGATON_HAMMER;}}},
//        {"Bottom Of the Well MQ Perimeter", {[this]{return Dungeon::BottomOfTheWell.IsMQ()      && IS_CHILD;}}},
//                                                /*Glitched*/[]{return Dungeon::BottomOfTheWell.IsMQ()      && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE) && Longshot;}}},
//        {"Kakariko Village",                {GLITCHLESS(true)}},
// }},
//
// {"Ice Cavern Entryway", "Ice Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Ice Cavern Beginning",    {[this]{return Dungeon::IceCavern.IsVanilla();}}},
//        {"Ice Cavern MQ Beginning", {[this]{return Dungeon::IceCavern.IsMQ();}}},
//        {"Zoras Fountain",          {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Entryway", "Gerudo Training Grounds", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Gerudo Training Grounds Lobby",    {[this]{return Dungeon::GerudoTrainingGrounds.IsVanilla();}}},
//        {"Gerudo Training Grounds MQ Lobby", {[this]{return Dungeon::GerudoTrainingGrounds.IsMQ();}}},
//        {"Gerudo Fortress",                  {GLITCHLESS(true)}},
// }},
//
// {"Ganon's Castle Entryway", "Ganon's Castle", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Ganons Castle Lobby",    {[this]{return Dungeon::GanonsCastle.IsVanilla();}}},
//        {"Ganons Castle MQ Lobby", {[this]{return Dungeon::GanonsCastle.IsMQ();}}},
//        {"Ganons Castle Grounds",  {GLITCHLESS(true)}},
// }},
//
// /*--------------------------
// |    VANILLA DUNGEONS      |
// ---------------------------*/
// if (Dungeon::DekuTree.IsVanilla()) {
// {"Deku Tree Lobby", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Locations
//        {"Deku Tree Map Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Deku Tree Entryway",          {GLITCHLESS(true)}},
//        {"Deku Tree 2f Middle Room",    {GLITCHLESS(true)}},
//        {"Deku Tree Compass Room",      {GLITCHLESS(true)}},
//        {"Deku Tree Basement Lower",    {[this]{return HERE(DEKU_TREE_LOBBY, []{return IS_ADULT || CAN_CHILD_ATTACK || Nuts;});}}},
                                           // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Deku Tree Outside Boss Room", {GLITCHLESS(false)}},
                                           // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}},
//        {"Deku Tree Boss Room",         {GLITCHLESS(false)}},
                                           // /*Glitched*/[]{return IS_CHILD && CanUse(KOKIRI_SWORD) && Nuts && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::EXPERT);}}},
// }},
//
// areaTable[DEKU_TREE_2F_MIDDLE_ROOM] = Area("Deku Tree 2F Middle Room", "Deku Tree", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Deku Tree Lobby",         {[this]{return HERE(DEKU_TREE_2F_MIDDLE_ROOM, []{return HasShield || CAN_USE_MEGATON_HAMMER;});}}},
//        {"Deku Tree SLINGSHOT Room",{[this]{return HERE(DEKU_TREE_2F_MIDDLE_ROOM, []{return HasShield || CAN_USE_MEGATON_HAMMER;});}}},
// }},
//
// {"Deku Tree SLINGSHOT Room", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree SLINGSHOT Chest",           {GLITCHLESS(true)}},
//        {"Deku Tree SLINGSHOT Room Side Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Deku Tree 2f Middle Room", {GLITCHLESS(CAN_USE_SLINGSHOT || CAN_USE_HOVER_BOOTS)}},
                                        // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Deku Tree Compass Room", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Locations
//        {"Deku Tree Compass Chest",           {GLITCHLESS(true)}},
//        {"Deku Tree Compass Room Side Chest", {GLITCHLESS(true)}},
//        {"Deku Tree GS Compass Room",         {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
                                                       // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Deku Tree Lobby",     {GLITCHLESS(HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW)}},
//        {"Deku Tree Boss Room", {GLITCHLESS(false)}},
                                   // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED);}}},
// }},
//
// {"Deku Tree Basement Lower", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Locations
//        {"Deku Tree Basement Chest",    {GLITCHLESS(true)}},
//        {"Deku Tree GS Basement Gate",  {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
                                                 // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Deku Tree GS Basement Vines", {GLITCHLESS(CanUseProjectile || CAN_USE_DINS_FIRE || (logic->tricks.dekuBasementGS && (IS_ADULT || STICKS || KOKIRI_SWORD)))}},
                                                 // /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Deku Tree Lobby",               {GLITCHLESS(true)}},
//        {"Deku Tree Basement Scrub Room", {[this]{return HERE(DEKU_TREE_BASEMENT_LOWER, []{return HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW;});}}},
//        {"Deku Tree Basement Upper",      {[this]{return IS_ADULT || logic->tricks.dekuB1Skip || HasAccessTo(DEKU_TREE_BASEMENT_UPPER);}}},
                                             // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
//        {"Deku Tree Outside Boss Room",   {GLITCHLESS(false)}},
                                             // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Deku Tree Basement Scrub Room", "Deku Tree", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Deku Tree Basement Lower",      {GLITCHLESS(true)}},
//        {"Deku Tree Basement Water Room", {[this]{return HERE(DEKU_TREE_BASEMENT_SCRUB_ROOM, []{return CAN_USE_SLINGSHOT || CAN_USE_BOW;});}}},
// }},
//
// {"Deku Tree Basement Water Room", "Deku Tree", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Deku Tree Basement Scrub Room", {GLITCHLESS(true)}},
//        {"Deku Tree Basement Torch Room", {GLITCHLESS(true)}},
// }},
//
// {"Deku Tree Basement Torch Room", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {}, {
//    //Exits
//        {"Deku Tree Basement Water Room", {GLITCHLESS(true)}},
//        {"Deku Tree Basement Back Lobby", {[this]{return HERE(DEKU_TREE_BASEMENT_TORCH_ROOM, []{return HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW;});}}},
// }},
//
// {"Deku Tree Basement Back Lobby", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {[this]{return DekuBabaNuts   || (HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW;}) &&
//                                                                           (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE));}}},
//                                   /*Glitched*/[]{return HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW;}) && CAN_USE_MEGATON_HAMMER;}}},
//    }, {}, {
//    //Exits
//        {"Deku Tree Basement Torch Room", {GLITCHLESS(true)}},
//        {"Deku Tree Basement Back Room",  {[this]{return HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || CanUse(BOW);}) &&
//                                                                    HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return CAN_BLAST_OR_SMASH;});}}},
//                                              /*Glitched*/[]{return HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || CanUse(BOW);}) &&
//                                                                    HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS && CAN_TAKE_DAMAGE && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT));});}}},
//        {"Deku Tree Basement Upper",      {[this]{return HERE(DEKU_TREE_BASEMENT_BACK_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || CanUse(BOW);}) && IS_CHILD;}}},
// }},
//
// {"Deku Tree Basement Back Room", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree GS Basement Back Room", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                                     // /*Glitched*/[]{return BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {
//    //Exits
//        {"Deku Tree Basement Back Lobby", {GLITCHLESS(true)}},
// }},
//
// {"Deku Tree Basement Upper", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {}, {
//    //Exits
//        {"Deku Tree Basement Lower",      {GLITCHLESS(true)}},
//        {"Deku Tree Basement Back Lobby", {GLITCHLESS(IS_CHILD)}},
//        {"Deku Tree Outside Boss Room",   {[this]{return HERE(DEKU_TREE_BASEMENT_UPPER, []{return HAS_FIRE_SOURCEWithTorch || (logic->tricks.dekuB1WebsWithBOW && IS_ADULT && CAN_USE_BOW);});}}},
// }},
//
// {"Deku Tree Outside Boss Room", "Deku Tree", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Deku Tree Basement Upper", {GLITCHLESS(true)}},
//        {"Deku Tree Boss Room",      {[this]{return HERE(DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return HasShield;});}}},
// }},
//
// {"Deku Tree Boss Room", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuTreeClear, {GLITCHLESS(DekuTreeClear || ((IS_ADULT || KOKIRI_SWORD || STICKS) && (Nuts || CAN_USE_SLINGSHOT || CAN_USE_BOW || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))))}},
                                 // /*Glitched*/[]{return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Locations
//        {"Queen Gohma",                 {GLITCHLESS(DekuTreeClear)}},
//        {"Deku Tree Queen Gohma Heart", {GLITCHLESS(DekuTreeClear)}},
//    }, {
//    //Exits
//        {"Deku Tree Outside Boss Room", {GLITCHLESS(true)}},
//        {"Deku Tree Entryway",          {GLITCHLESS(DekuTreeClear)}},
// }},
// }
//
// if (Dungeon::DodongosCavern.IsVanilla()) {
// {"Dodongos Cavern Beginning", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Entryway", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Lobby",    {[this]{return HERE(DODONGOS_CAVERN_BEGINNING, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                         /*Glitched*/[]{return HERE(DODONGOS_CAVERN_BEGINNING, []{return GlitchBLUE_FIREWall && BLUE_FIRE;});}}},
// }},
//
// {"Dodongos Cavern Lobby", "Dodongos Cavern", NO_TIMEPASS, {
//    //Events
//        {"Gossip Stone Fairy", {[this]{return "Gossip Stone Fairy" || (CAN_SUMMON_GOSSIP_FAIRY && HERE(DODONGOS_CAVERN_LOBBY, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;}));}}},
//                                     /*Glitched*/[]{return CAN_SUMMON_GOSSIP_FAIRY && HERE(DODONGOS_CAVERN_LOBBY, []{return GlitchBLUE_FIREWall && BLUE_FIRE;});}}},
//    }, {
//    //Locations
//        {"Dodongos Cavern Map Chest",        {[this]{return HERE(DODONGOS_CAVERN_LOBBY, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                                       /*Glitched*/[]{return HERE(DODONGOS_CAVERN_LOBBY, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);}) || CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//        {"Dodongos Cavern Deku Scrub Lobby", {GLITCHLESS(CAN_STUN_DEKU || GORON_BRACELET)}},
//        {"Dodongos Cavern Gossip Stone",     {[this]{return HERE(DODONGOS_CAVERN_LOBBY, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                                       /*Glitched*/[]{return HERE(DODONGOS_CAVERN_LOBBY, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);});}}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Beginning",    {GLITCHLESS(true)}},
//        {"Dodongos Cavern Lobby Switch", {GLITCHLESS(IS_ADULT)}},
                                            // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) || (HAS_EXPLOSIVES && (CAN_USE_SLINGSHOT || CAN_USE_HOOKSHOT || CAN_USE_BOW) && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)) || (CAN_SHIELD && GORON_BRACELET && GlitchModernHalfie) || ((KOKIRI_SWORD || STICKS || CAN_USE_MEGATON_HAMMER) && (BOMBS || GORON_BRACELET) && Fairy && GlitchClassicHalfie);}}},
//        {"Dodongos Cavern Se Corridor",  {[this]{return HERE(DODONGOS_CAVERN_LOBBY, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                             /*Glitched*/[]{return HERE(DODONGOS_CAVERN_LOBBY, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);});}}},
//        {"Dodongos Cavern Stairs Lower", {GLITCHLESS(HasAccessTo(DODONGOS_CAVERN_LOBBY_SWITCH))}},
//        {"Dodongos Cavern Far Bridge",   {GLITCHLESS(HasAccessTo(DODONGOS_CAVERN_FAR_BRIDGE))}},
                                            // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Dodongos Cavern Boss Area",    {[this]{return HERE(DODONGOS_CAVERN_FAR_BRIDGE, []{return HAS_EXPLOSIVES;});}}},
//        {"Dodongos Cavern Boss Room",    {GLITCHLESS(false)}},
                                            // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED);}}},
// }},
//
// {"Dodongos Cavern Lobby Switch", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Lobby",        {GLITCHLESS(true)}},
//        {"Dodongos Cavern Dodongo Room", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern SE Corridor", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern GS Scarecrow", {GLITCHLESS(CAN_USE_SCARECROW || (IS_ADULT && CAN_USE_LONGSHOT) || (logic->tricks.dCScarecrowGS && (IS_ADULT || CAN_CHILD_ATTACK)))}},
                                                  // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (CAN_USE_LONGSHOT && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Lobby",               {GLITCHLESS(true)}},
//        {"Dodongos Cavern Se Room",             {[this]{return HERE(DODONGOS_CAVERN_SE_CORRIDOR, []{return CAN_BLAST_OR_SMASH || IS_ADULT || CAN_CHILD_ATTACK || (CAN_TAKE_DAMAGE && CAN_SHIELD);});}}},
//                                                    /*Glitched*/[]{return HERE(DODONGOS_CAVERN_SE_CORRIDOR, []{return (GlitchBLUE_FIREWall && BLUE_FIRE);});}}},
//        {"Dodongos Cavern Near Lower Lizalfos", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern SE Room", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern GS Side Room Near Lower Lizalfos", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
                                                                      // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Se Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Near Lower Lizalfos", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Se Corridor",    {GLITCHLESS(true)}},
//        {"Dodongos Cavern Lower Lizalfos", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Lower Lizalfos", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Near Lower Lizalfos", {[this]{return HERE(DODONGOS_CAVERN_LOWER_LIZALFOS, []{return IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES;});}}},
                                                   // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Dodongos Cavern Dodongo Room",        {[this]{return HERE(DODONGOS_CAVERN_LOWER_LIZALFOS, []{return IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES;});}}},
                                                   // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Dodongos Cavern Dodongo Room", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Lobby Switch",      {GLITCHLESS(HAS_FIRE_SOURCEWithTorch)}},
//        {"Dodongos Cavern Lower Lizalfos",    {GLITCHLESS(true)}},
//        {"Dodongos Cavern Near Dodongo Room", {[this]{return HERE(DODONGOS_CAVERN_DODONGO_ROOM, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                                  /*Glitched*/[]{return HERE(DODONGOS_CAVERN_DODONGO_ROOM, []{return GlitchBLUE_FIREWall && BLUE_FIRE;});}}},
// }},
//
// {"Dodongos Cavern Near Dodongo Room", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern Deku Scrub Side Room Near Dodongos", {GLITCHLESS(CAN_STUN_DEKU)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Dodongo Room", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Stairs Lower", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Lobby",        {GLITCHLESS(true)}},
//        {"Dodongos Cavern Stairs Upper", {GLITCHLESS(HAS_EXPLOSIVES || GORON_BRACELET || CAN_USE_DINS_FIRE || (logic->tricks.dCStaircase && CAN_USE_BOW))}},
//        {"Dodongos Cavern Compass Room", {[this]{return HERE(DODONGOS_CAVERN_STAIRS_LOWER, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                             /*Glitched*/[]{return HERE(DODONGOS_CAVERN_STAIRS_LOWER, []{return GlitchBLUE_FIREWall && BLUE_FIRE;});}}},
// }},
//
// {"Dodongos Cavern Stairs Upper", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern GS Alcove Above Stairs", {[this]{return HERE(DODONGOS_CAVERN_FAR_BRIDGE, []{return (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG);}) || CAN_USE_LONGSHOT;}}},
                                                            // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG));}}},
//        {"Dodongos Cavern GS Vines Above Stairs",  {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Stairs Lower", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Armos Room",   {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Compass Room", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern Compass Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Stairs Lower", {GLITCHLESS(IS_ADULT || HAS_EXPLOSIVES || GORON_BRACELET)}},
                                            // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Dodongos Cavern Armos Room", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Stairs Upper",    {GLITCHLESS(true)}},
//        {"Dodongos Cavern Bomb Room Lower", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Bomb Room Lower", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern Bomb Flower Platform Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern 2f Side Room",         {[this]{return HERE(DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return CAN_BLAST_OR_SMASH;});}}},
//                                                     /*Glitched*/[]{return HERE(DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);});}}},
//        {"Dodongos Cavern First SLINGSHOT Room", {[this]{return HERE(DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
//                                                     /*Glitched*/[]{return HERE(DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);});}}},
//        {"Dodongos Cavern Bomb Room Upper",      {GLITCHLESS((IS_ADULT && logic->tricks.dCJump) || CAN_USE_HOVER_BOOTS || (IS_ADULT && CAN_USE_LONGSHOT))}},
                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) ||
                                                    //                       (IS_ADULT && (CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_SLINGSHOT) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED));}}},
// }},
//
// areaTable[DODONGOS_CAVERN_2F_SIDE_ROOM] = Area("Dodongos Cavern 2F Side Room", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern Deku Scrub Near Bomb Bag Left",  {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Dodongos Cavern Deku Scrub Near Bomb Bag Right", {GLITCHLESS(CAN_STUN_DEKU)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Bomb Room Lower", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern First SLINGSHOT Room", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Bomb Room Lower", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Upper Lizalfos",  {GLITCHLESS(CAN_USE_SLINGSHOT || CAN_USE_BOW || logic->tricks.dCSLINGSHOTSkip)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (IS_ADULT && CAN_USE_HOOKSHOT && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED));}}},
// }},
//
// {"Dodongos Cavern Upper Lizalfos", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Lower Lizalfos",        {GLITCHLESS(true)}},
//        {"Dodongos Cavern First SLINGSHOT Room",  {[this]{return HERE(DODONGOS_CAVERN_LOWER_LIZALFOS, []{return IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES;});}}},
                                                     // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Dodongos Cavern Second SLINGSHOT Room", {[this]{return HERE(DODONGOS_CAVERN_LOWER_LIZALFOS, []{return IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES;});}}},
                                                     // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Dodongos Cavern Second SLINGSHOT Room", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Upper Lizalfos",  {GLITCHLESS(true)}},
//        {"Dodongos Cavern Bomb Room Upper", {GLITCHLESS(CAN_USE_SLINGSHOT || CAN_USE_BOW || logic->tricks.dCSLINGSHOTSkip)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) || (IS_ADULT && CAN_USE_HOOKSHOT && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED));}}},
// }},
//
// {"Dodongos Cavern Bomb Room Upper", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern Bomb Bag Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Bomb Room Lower",       {GLITCHLESS(true)}},
//        {"Dodongos Cavern Second SLINGSHOT Room", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Far Bridge",            {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Far Bridge", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern End Of Bridge Chest", {[this]{return HERE(DODONGOS_CAVERN_FAR_BRIDGE, []{return CAN_BLAST_OR_SMASH;});}}},
//                                                          /*Glitched*/[]{return HERE(DODONGOS_CAVERN_FAR_BRIDGE, []{return (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);}) ||
//                                                                                CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Lobby",           {GLITCHLESS(true)}},
//        {"Dodongos Cavern Bomb Room Upper", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Boss Area", "Dodongos Cavern", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {}, {
//    //Exits
//        {"Dodongos Cavern Lobby", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Back Room", {[this]{return HERE(DODONGOS_CAVERN_BOSS_AREA, []{return CAN_BLAST_OR_SMASH;});}}},
//                                          /*Glitched*/[]{return HERE(DODONGOS_CAVERN_BOSS_AREA, []{return (GlitchBLUE_FIREWall && BLUE_FIRE) || (CAN_USE_STICKS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/);});}}},
//        {"Dodongos Cavern Boss Room", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Back Room", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern GS Back Room", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
                                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Boss Area", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern Boss Room", "Dodongos Cavern", NO_TIMEPASS, {
//    //Events
//        {DodongosCavernClear, {[this]{return DodongosCavernClear || (HERE(DODONGOS_CAVERN_BOSS_ROOM, []{return HAS_EXPLOSIVES || (CAN_USE_MEGATON_HAMMER && CAN_SHIELD);}) && (BOMBS || GORON_BRACELET) && (IS_ADULT || STICKS || KOKIRI_SWORD));}}},
//                                        /*Glitched*/[]{return HERE(DODONGOS_CAVERN_BOSS_ROOM, []{return HAS_EXPLOSIVES || (CAN_USE_MEGATON_HAMMER && CAN_SHIELD) || (GlitchBLUE_FIREWall && BLUE_FIRE);}) && (HAS_EXPLOSIVES || GORON_BRACELET) && (IS_ADULT || STICKS || KOKIRI_SWORD || CAN_USE_MEGATON_HAMMER);}}},
//    }, {
//    //Locations
//        {"Dodongos Cavern Boss Room Chest",    {GLITCHLESS(true)}},
//        {"Dodongos Cavern King Dodongo Heart", {GLITCHLESS(DodongosCavernClear)}},
//        {"King Dodongo",                       {GLITCHLESS(DodongosCavernClear)}},
//    }, {
//    //Exits
//        {"Dodongos Cavern Boss Area", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Entryway",  {GLITCHLESS(DodongosCavernClear)}},
// }},
// }
//
// if (Dungeon::JabuJabusBelly.IsVanilla()) {
// {"Jabu Jabus Belly Beginning", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Entryway",    {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lift Middle", {GLITCHLESS(CanUseProjectile)}},
                                            // /*Glitched*/[]{return CAN_USE_BOOMERANG || CAN_USE_BOW || CAN_USE_HOOKSHOT || (CAN_USE_STICKS && CAN_TAKE_DAMAGE && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT)) || CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Jabu Jabus Belly Lift Middle", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Beginning",      {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Main Upper",     {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lift Lower",     {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Near Boss Room", {GLITCHLESS(HasAccessTo(JABU_JABUS_BELLY_LIFT_UPPER) || (logic->tricks.jabuBossGSAdult && IS_ADULT && CAN_USE_HOVER_BOOTS))}},
                                               // /*Glitched*/[]{return (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)) &&
                                               //                       GlitchJabuSwitch && (FISH || BUGS || CAN_USE_FARORES_WIND || (IS_ADULT && CLAIM_CHECK));}}},
// }},
//
// {"Jabu Jabus Belly Main Upper", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Lift Middle",     {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Main Lower",      {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Forked Corridor", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Bigocto Room",    {[this]{return HERE(JABU_JABUS_BELLY_GREEN_TENTACLE, []{return CAN_USE_BOOMERANG;});}}},
// }},
//
// {"Jabu Jabus Belly Main Lower", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly GS Lobby Basement Lower", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                                              // /*Glitched*/[]{return BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Jabu Jabus Belly GS Lobby Basement Upper", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                                              // /*Glitched*/[]{return BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Main Upper",       {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Shabomb Corridor", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lower Side Room",  {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Shabomb Corridor", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {
//    //Locations
//        {"Jabu Jabus Belly GS Water Switch Room", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Main Lower", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lift Lower", {GLITCHLESS(CanUseProjectile)}},
                                           // /*Glitched*/[]{return CAN_USE_BOOMERANG || CAN_USE_BOW || CAN_USE_HOOKSHOT || (CAN_USE_STICKS && CAN_TAKE_DAMAGE && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT));}}},
// }},
//
// {"Jabu Jabus Belly Lower Side Room", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {[this]{return "Fairy Pot" || (CAN_USE_BOOMERANG || CAN_USE_HOVER_BOOTS);}}},
                            // /*Glitched*/[]{return (BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {}, {
//    //Exits
//        {"Jabu Jabus Belly Main Lower", {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Lift Lower", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly Deku Scrub", {GLITCHLESS((IS_CHILD || SILVER_SCALE || logic->tricks.jabuScrubJumpDive || CAN_USE_IRON_BOOTS) && CAN_STUN_DEKU)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Shabomb Corridor", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lift Middle",      {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Forked Corridor", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Main Upper",     {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly BOOMERANG Room", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Map Room",       {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Compass Room",   {[this]{return HERE(JABU_JABUS_BELLY_MAP_ROOM,      []{return CAN_USE_BOOMERANG;});}}},
//        {"Jabu Jabus Belly Blue Tentacle",  {[this]{return HERE(JABU_JABUS_BELLY_MAP_ROOM,      []{return CAN_USE_BOOMERANG;});}}},
//        {"Jabu Jabus Belly Green Tentacle", {[this]{return HERE(JABU_JABUS_BELLY_BLUE_TENTACLE, []{return CAN_USE_BOOMERANG;});}}},
// }},
//
// {"Jabu Jabus Belly BOOMERANG Room", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly BOOMERANG Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Forked Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Map Room", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly Map Chest", {GLITCHLESS(CAN_USE_BOOMERANG)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Forked Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Compass Room", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly Compass Chest", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Forked Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Blue Tentacle", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Forked Corridor", {[this]{return HERE(JABU_JABUS_BELLY_BLUE_TENTACLE, []{return CAN_USE_BOOMERANG;});}}},
// }},
//
// {"Jabu Jabus Belly Green Tentacle", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Forked Corridor", {[this]{return HERE(JABU_JABUS_BELLY_GREEN_TENTACLE, []{return CAN_USE_BOOMERANG;});}}},
// }},
//
// {"Jabu Jabus Belly Bigocto Room", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Main Lower",    {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Above Bigocto", {[this]{return HERE(JABU_JABUS_BELLY_BIGOCTO_ROOM, []{return (CAN_USE_BOOMERANG || Nuts) && (CanUse(KOKIRI_SWORD) || CAN_USE_STICKS);});}}},
// }},
//
// {"Jabu Jabus Belly Above Bigocto", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//        {"Nut Pot",   {GLITCHLESS(true)}},
//    }, {}, {
//    //Exits
//        {"Jabu Jabus Belly Lift Upper", {GLITCHLESS(CAN_USE_BOOMERANG)}},
                                           // /*Glitched*/[]{return HAS_BOMBCHUS && CAN_SHIELD && IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOW || CAN_USE_SLINGSHOT) && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED);}}},
// }},
//
// {"Jabu Jabus Belly Lift Upper", "Jabu Jabus Belly", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Jabu Jabus Belly Lift Middle", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Lift Lower",  {GLITCHLESS(true)}},
// }},
//
// {"Jabu Jabus Belly Near Boss Room", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly GS Near Boss", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Lift Middle", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Boss Room",   {GLITCHLESS(CAN_USE_BOOMERANG)}},
                                            // /*Glitched*/[]{return (CAN_USE_HOVER_BOOTS && (CAN_USE_BOW || CAN_USE_SLINGSHOT)) || CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) ||
                                            //                       (CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) || (BOMBS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Jabu Jabus Belly Boss Room", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {JabuJabusBellyClear, {GLITCHLESS(JabuJabusBellyClear || CAN_USE_BOOMERANG)}},
//    }, {
//    //Locations
//        {"Jabu Jabus Belly Barinade Heart", {GLITCHLESS(JabuJabusBellyClear)}},
//        {"Barinade",                        {GLITCHLESS(JabuJabusBellyClear)}},
//    }, {
//    //Exits
//        {"Jabu Jabus Belly Near Boss Room", {GLITCHLESS(JabuJabusBellyClear)}},
//        {"Jabu Jabus Belly Entryway",       {GLITCHLESS(JabuJabusBellyClear)}},
// }},
// }
//
// if (Dungeon::ForestTemple.IsVanilla()) {
// {"Forest Temple First Room", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple First Room Chest", {GLITCHLESS(true)}},
//        {"Forest Temple GS First Room",    {GLITCHLESS((IS_ADULT && BOMBS) || CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG || CAN_USE_SLINGSHOT || HAS_BOMBCHUS || CAN_USE_DINS_FIRE)}},
                                                    // /*Glitched*/[]{return (BOMBS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE)) || CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Forest Temple Entryway",       {GLITCHLESS(true)}},
//        {"Forest Temple South Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple South Corridor", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple First Room", {GLITCHLESS(true)}},
//        {"Forest Temple Lobby",      {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK || Nuts)}},
                                        // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Forest Temple Lobby", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleMeg, {GLITCHLESS(ForestTempleMeg || (ForestTempleJoelle && ForestTempleBeth && ForestTempleAmy && CAN_USE_BOW))}},
//    }, {
//    //Locations
//        {"Forest Temple GS Lobby", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                            // /*Glitched*/[]{return IS_ADULT && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Forest Temple South Corridor",    {GLITCHLESS(true)}},
//        {"Forest Temple North Corridor",    {GLITCHLESS(true)}},
//        {"Forest Temple Nw Outdoors Lower", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME || IS_CHILD)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::NOVICE) || (SongOfTime && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                               //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))));}}},
//        {"Forest Temple Ne Outdoors Lower", {GLITCHLESS(CAN_USE_BOW || CAN_USE_SLINGSHOT)}},
//        {"Forest Temple West Corridor",     {[this]{return SmallKeys(FOREST_TEMPLE, 1, 5);}}},
//        {"Forest Temple East Corridor",     {GLITCHLESS(false)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE);}}},
//        {"Forest Temple Boss Region",       {GLITCHLESS(ForestTempleMeg)}},
//        {"Forest Temple Boss Room",         {GLITCHLESS(false)}},
                                               // /*Glitched*/[]{return IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOW || CAN_USE_SLINGSHOT) && GlitchForestBKSkip;}}},
// }},
//
// {"Forest Temple North Corridor", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Lobby",         {GLITCHLESS(true)}},
//        {"Forest Temple Lower Stalfos", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Lower Stalfos", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {
//    //Locations
//        {"Forest Temple First Stalfos Chest", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
                                                       // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Forest Temple North Corridor", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple NW Outdoors Lower", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Locations
//        {"Forest Temple GS Level Island Courtyard", {[this]{return CAN_USE_LONGSHOT || HERE(FOREST_TEMPLE_NW_OUTDOORS_UPPER, []{return (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG);});}}},
//    }, {
//    //Exits
//        {"Forest Temple Lobby",             {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::NOVICE) || (SongOfTime && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                               //                       ((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || ((BUGS || FISH) && CAN_SHIELD && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))));}}},
//        {"Forest Temple Nw Outdoors Upper", {GLITCHLESS(false)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) || (IS_ADULT && CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::NOVICE)) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//        {"Forest Temple Map Room",          {GLITCHLESS(true)}},
//        {"Forest Temple Sewer",             {GLITCHLESS(GoldScale || CAN_USE_IRON_BOOTS || HasAccessTo(FOREST_TEMPLE_NE_OUTDOORS_UPPER))}},
//        {"Forest Temple Boss Room",         {GLITCHLESS(false)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Forest Temple NW Outdoors Upper", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {}, {
//    //Exits
//        {"Forest Temple Nw Outdoors Lower",    {GLITCHLESS(true)}},
//        {"Forest Temple Below Boss Key Chest", {GLITCHLESS(true)}},
//        {"Forest Temple Floormaster Room",     {GLITCHLESS(true)}},
//        {"Forest Temple Block Push Room",      {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple NE Outdoors Lower", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Locations
//        {"Forest Temple Raised Island Courtyard Chest", {GLITCHLESS(CAN_USE_HOOKSHOT || HasAccessTo(FOREST_TEMPLE_FALLING_ROOM))}},
//        {"Forest Temple GS Raised Island Courtyard",    {[this]{return CAN_USE_HOOKSHOT || (logic->tricks.forestOutdoorEastGS && CAN_USE_BOOMERANG) || HERE(FOREST_TEMPLE_FALLING_ROOM, []{return CAN_USE_BOW || CAN_USE_SLINGSHOT || CAN_USE_DINS_FIRE || HAS_EXPLOSIVES;});}}},
//    }, {
//    //Exits
//        {"Forest Temple Lobby",             {GLITCHLESS(true)}},
//        {"Forest Temple Ne Outdoors Upper", {GLITCHLESS(CAN_USE_LONGSHOT)}},
//        {"Forest Temple Sewer",             {GLITCHLESS(GoldScale || CAN_USE_IRON_BOOTS || HasAccessTo(FOREST_TEMPLE_NE_OUTDOORS_UPPER))}},
//        {"Forest Temple Falling Room",      {GLITCHLESS(false)}},
                                               // /*Glitched*/[]{return BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Forest Temple NE Outdoors Upper", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {}, {
//    //Exits
//        {"Forest Temple Ne Outdoors Lower", {GLITCHLESS(true)}},
//        {"Forest Temple Map Room",          {GLITCHLESS(true)}},
//        {"Forest Temple Falling Room",      {GLITCHLESS(logic->tricks.forestDoorFrame && CAN_USE_HOVER_BOOTS && CAN_USE_SCARECROW)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::EXPERT);}}},
// }},
//
// {"Forest Temple Map Room", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Map Chest", {[this]{return HERE(FOREST_TEMPLE_MAP_ROOM, []{return HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_BOW || ((IS_ADULT || STICKS || KOKIRI_SWORD || SLINGSHOT) && (Nuts || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_SHIELD));});}}},
//    }, {
//    //Exits
//        {"Forest Temple Nw Outdoors Lower", {[this]{return HERE(FOREST_TEMPLE_MAP_ROOM, []{return HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_BOW || ((IS_ADULT || STICKS || KOKIRI_SWORD || SLINGSHOT) && (Nuts || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_SHIELD));});}}},
//        {"Forest Temple Ne Outdoors Upper", {[this]{return HERE(FOREST_TEMPLE_MAP_ROOM, []{return HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_BOW || ((IS_ADULT || STICKS || KOKIRI_SWORD || SLINGSHOT) && (Nuts || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_SHIELD));});}}},
// }},
//
// {"Forest Temple Sewer", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Well Chest", {GLITCHLESS(HasAccessTo(FOREST_TEMPLE_NE_OUTDOORS_UPPER))}},
//    }, {
//    //Exits
//        {"Forest Temple Nw Outdoors Lower", {GLITCHLESS(true)}},
//        {"Forest Temple Ne Outdoors Lower", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Below Boss Key Chest", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Nw Outdoors Upper", {[this]{return HERE(FOREST_TEMPLE_BELOW_BOSS_KEY_CHEST, []{return HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_BOW || ((IS_ADULT || STICKS || KOKIRI_SWORD || SLINGSHOT) && (Nuts || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || CAN_SHIELD));});}}},
// }},
//
// {"Forest Temple Floormaster Room", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Floormaster Chest", {GLITCHLESS(IS_ADULT || CanChildDamage)}},
                                                     // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Forest Temple Nw Outdoors Upper", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple West Corridor", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Lobby",           {[this]{return SmallKeys(FOREST_TEMPLE, 1, 5);}}},
//        {"Forest Temple Block Push Room", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK || Nuts)}},
                                             // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Forest Temple Block Push Room", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Eye Switch Chest", {GLITCHLESS(GORON_BRACELET && (CAN_USE_BOW || CAN_USE_SLINGSHOT))}},
                                                    // /*Glitched*/[]{return IS_ADULT && (CAN_USE_BOW || CAN_USE_SLINGSHOT) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED);}}},
//    }, {
//    //Exits
//        {"Forest Temple West Corridor",            {GLITCHLESS(true)}},
//        {"Forest Temple Nw Outdoors Upper",        {GLITCHLESS(CAN_USE_HOVER_BOOTS || (logic->tricks.forestOutsideBackdoor && IS_ADULT && GORON_BRACELET))}},
                                                      // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || (BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//        {"Forest Temple Nw Corridor Twisted",      {[this]{return IS_ADULT && GORON_BRACELET && FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
//                                                       /*Glitched*/[]{return ((IS_ADULT && (BOW || Hookshot || CAN_USE_SLINGSHOT) && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)) ||
//                                                                              (BOMBS && GORON_BRACELET && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE))) && FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
//        {"Forest Temple Nw Corridor Straightened", {[this]{return CAN_USE_BOW && GORON_BRACELET && FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
//                                                       /*Glitched*/[]{return ((IS_ADULT && HAS_BOMBCHUS && CAN_SHIELD && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)) ||
//                                                                              (IS_CHILD && BOMBS && GORON_BRACELET && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE))) && (CAN_USE_BOW || CAN_USE_SLINGSHOT) && FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
// }},
//
// {"Forest Temple NW Corridor Twisted", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Block Push Room", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
//        {"Forest Temple Red Poe Room",    {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 3;}}},
// }},
//
// {"Forest Temple NW Corridor Straightened", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Boss Key Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Forest Temple Below Boss Key Chest", {GLITCHLESS(true)}},
//        {"Forest Temple Block Push Room",      {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
// }},
//
// {"Forest Temple Red Poe Room", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleJoelle, {GLITCHLESS(ForestTempleJoelle || CAN_USE_BOW)}},
//    }, {
//    //Locations
//        {"Forest Temple Red Poe Chest", {GLITCHLESS(ForestTempleJoelle)}},
//    }, {
//    //Exits
//        {"Forest Temple Nw Corridor Twisted", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 3;}}},
//        {"Forest Temple Upper Stalfos",       {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Upper Stalfos", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple BOW Chest", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
                                             // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Forest Temple Red Poe Room",  {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
                                           // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Forest Temple Blue Poe Room", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
                                           // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Forest Temple Blue Poe Room", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleBeth, {GLITCHLESS(ForestTempleBeth || CAN_USE_BOW)}},
//    }, {
//    //Locations
//        {"Forest Temple Blue Poe Chest", {GLITCHLESS(ForestTempleBeth)}},
//    }, {
//    //Exits
//        {"Forest Temple Upper Stalfos",            {GLITCHLESS(true)}},
//        {"Forest Temple Ne Corridor Straightened", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 4;}}},
// }},
//
// {"Forest Temple NE Corridor Straightened", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Blue Poe Room",   {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 4;}}},
//        {"Forest Temple Frozen Eye Room", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 5;}}},
// }},
//
// {"Forest Temple NE Corridor Twisted", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Frozen Eye Room", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Forest Temple Falling Room",    {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Frozen Eye Room", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Ne Corridor Straightened", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Forest Temple Ne Corridor Twisted",      {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 5 && (CAN_USE_BOW || CAN_USE_DINS_FIRE);}}},
// }},
//
// {"Forest Temple Falling Room", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Falling Ceiling Room Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Forest Temple Ne Outdoors Lower", {GLITCHLESS(true)}},
//        {"Forest Temple Green Poe Room",    {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple Green Poe Room", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleAmy, {GLITCHLESS(ForestTempleAmy || CAN_USE_BOW)}},
//    }, {}, {
//    //Exits
//        {"Forest Temple Falling Room",  {GLITCHLESS(true)}},
//        {"Forest Temple East Corridor", {GLITCHLESS(ForestTempleAmy)}},
// }},
//
// {"Forest Temple East Corridor", "Forest Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Forest Temple Lobby",          {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK || Nuts)}},
                                            // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//        {"Forest Temple Green Poe Room", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK || Nuts)}},
                                            // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Forest Temple Boss Region", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple Basement Chest", {GLITCHLESS(true)}},
//        {"Forest Temple GS Basement",    {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
                                                  // /*Glitched*/[]{return BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {
//    //Exits
//        {"Forest Temple Lobby",     {GLITCHLESS(true)}},
//        {"Forest Temple Boss Room", {GLITCHLESS(BossKeyForestTemple)}},
// }},
//
// {"Forest Temple Boss Room", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleClear, {GLITCHLESS(ForestTempleClear || ((IS_ADULT || KOKIRI_SWORD) && (CAN_USE_HOOKSHOT || CAN_USE_BOW || CAN_USE_SLINGSHOT)))}},
//    }, {
//    //Locations
//        {"Forest Temple Phantom Ganon Heart", {GLITCHLESS(ForestTempleClear)}},
//        {"Phantom Ganon",                     {GLITCHLESS(ForestTempleClear)}},
//    }, {
//    //Exits
//        {"Forest Temple Entryway", {GLITCHLESS(ForestTempleClear)}},
// }},
// }
//
// if (Dungeon::FireTemple.IsVanilla()) {
// {"Fire Temple First Room", "Fire Temple", NO_TIMEPASS, {}, {
//    }, {
//    //Exits
//        {"Fire Temple Entryway",       {GLITCHLESS(true)}},
//        {"Fire Temple Near Boss Room", {[this]{return FIRE_TIMER >= 24;}}},
//        {"Fire Temple Loop Enemies",   {[this]{return HERE(FIRE_TEMPLE_FIRST_ROOM, []{return CAN_USE_MEGATON_HAMMER;}) && (FIRE_TEMPLE_SMALL_KEYS >= 8 || !IsKeysanity);}}},
//                                           /*Glitched*/[]{return ((IS_ADULT && CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::EXPERT)) ||
//                                                                 (GlitchFireGrunzClip && BOMBS && IS_ADULT && CAN_USE_HOVER_BOOTS && CanSurviveDamage)) && (FIRE_TEMPLE_SMALL_KEYS >= 8 || !IsKeysanity);}}},
//        {"Fire Temple Loop Exit",      {GLITCHLESS(true)}},
//        {"Fire Temple Big Lava Room",  {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 2 && FIRE_TIMER >= 24;}}},
// }},
//
// {"Fire Temple Near Boss Room", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {[this]{return "Fairy Pot" || (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT);}}},
//    }, {
//    //Locations
//        {"Fire Temple Near Boss Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple First Room", {GLITCHLESS(true)}},
//        {"Fire Temple Boss Room",  {[this]{return BossKeyFireTemple && ((IS_ADULT && logic->tricks.fireBossDoorJump) || CAN_USE_HOVER_BOOTS || HERE(FIRE_TEMPLE_FIRE_MAZE_UPPER, []{return CAN_USE_MEGATON_HAMMER;}));}}},
                                      // /*Glitched*/[]{return BossKeyFireTemple && (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) ||
                                      //                       (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)));}}},
// }},
//
// {"Fire Temple Boss Room", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {FireTempleClear, {[this]{return FireTempleClear || (FIRE_TIMER >= 64 && CAN_USE_MEGATON_HAMMER);}}},
//                                    /*Glitched*/[]{return FIRE_TIMER >= 48 && ((CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) ||
//                                                          CAN_USE_MEGATON_HAMMER) && BOMBS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {
//    //Locations
//        {"Fire Temple Volvagia Heart", {GLITCHLESS(FireTempleClear)}},
//        {"Volvagia",                   {GLITCHLESS(FireTempleClear)}},
//    }, {
//    //Exits
//        {"Fire Temple Entryway", {GLITCHLESS(FireTempleClear)}},
// }},
//
// {"Fire Temple Loop Enemies", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple First Room", {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 8 || !IsKeysanity;}}},
//        {"Fire Temple Loop Tiles", {[this]{return HERE(FIRE_TEMPLE_LOOP_ENEMIES, []{return IS_ADULT || KOKIRI_SWORD;});}}},
                                      // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Fire Temple Loop Tiles", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple GS Boss Key Loop", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
                                                  // /*Glitched*/[]{return CAN_USE_MEGATON_HAMMER;}}},
//    }, {
//    //Exits
//        {"Fire Temple Loop Enemies",      {GLITCHLESS(true)}},
//        {"Fire Temple Loop Flare Dancer", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Loop Flare Dancer", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Flare Dancer Chest", {GLITCHLESS((HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER) && IS_ADULT)}},
                                                    // /*Glitched*/[]{return (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                                                    //                       (CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED) && HAS_BOMBCHUS && CAN_SHIELD && (SLINGSHOT || CAN_USE_BOW || CAN_USE_HOOKSHOT));}}},
//    }, {
//    //Exits
//        {"Fire Temple Loop Tiles",         {GLITCHLESS(true)}},
//        {"Fire Temple Loop Hammer Switch", {[this]{return HERE(FIRE_TEMPLE_LOOP_FLARE_DANCER, []{return (HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_HOOKSHOT) && (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || BOOMERANG);});}}},
// }},
//
// {"Fire Temple Loop Hammer Switch", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {FireLoopSwitch, {GLITCHLESS(FireLoopSwitch || CAN_USE_MEGATON_HAMMER)}},
                                  // /*Glitched*/[]{return CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) && BOMBS && CAN_TAKE_DAMAGE && CAN_USE_STICKS;}}},
//    }, {}, {
//    //Exits
//        {"Fire Temple Loop Flare Dancer", {GLITCHLESS(true)}},
//        {"Fire Temple Loop Goron Room",   {GLITCHLESS(FireLoopSwitch)}},
                                             // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Fire Temple Loop Goron Room", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Boss Key Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Loop Hammer Switch", {GLITCHLESS(FireLoopSwitch)}},
//        {"Fire Temple Loop Exit",          {GLITCHLESS(FireLoopSwitch)}},
// }},
//
// {"Fire Temple Loop Exit", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple First Room",      {GLITCHLESS(true)}},
//        {"Fire Temple Loop Goron Room", {GLITCHLESS(FireLoopSwitch)}},
                                           // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Fire Temple Big Lava Room", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple First Room",                {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 2;}}},
//        {"Fire Temple Big Lava Room North Goron", {GLITCHLESS(true)}},
//        {"Fire Temple Big Lava Room North Tiles", {GLITCHLESS(IS_ADULT && (CAN_PLAY_SONG_OF_TIME || logic->tricks.fireSongOfTime))}},
//                                                      /*Glitched*/[]{return FIRE_TIMER >= 48 && ((CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
//                                                                            (IS_ADULT && (SongOfTime && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) || (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) && (BUGS || FISH) && CAN_SHIELD)))));}}},
//        {"Fire Temple Big Lava Room South Goron", {GLITCHLESS(IS_ADULT && HAS_EXPLOSIVES)}},
//                                                      /*Glitched*/[]{return FIRE_TIMER >= 48 && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Fire Temple Fire Pillar Room",          {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 3;}}},
// }},
//
// {"Fire Temple Big Lava Room North Goron", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Big Lava Room Lower Open Door Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Big Lava Room", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Big Lava Room North Tiles", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple GS Song Of Time Room", {GLITCHLESS(IS_ADULT)}},
//    }, {
//    //Exits
//        {"Fire Temple Big Lava Room", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Big Lava Room South Goron", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Big Lava Room Blocked Door Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Big Lava Room", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Fire Pillar Room", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Big Lava Room", {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 3;}}},
//        {"Fire Temple Shortcut Room", {[this]{return FIRE_TIMER >= 56 && FIRE_TEMPLE_SMALL_KEYS >= 4;}}},
// }},
//
// {"Fire Temple Shortcut Room", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Boulder Maze Shortcut Chest", {[this]{return HERE(FIRE_TEMPLE_SHORTCUT_CLIMB, []{return true;});}}},
                                                             // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE);}}},
//    }, {
//    //Exits
//        {"Fire Temple Fire Pillar Room",   {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 4;}}},
//        {"Fire Temple Shortcut Climb",     {[this]{return HERE(FIRE_TEMPLE_SHORTCUT_CLIMB, []{return true;});}}},
                                              // /*Glitched*/[]{return (GORON_BRACELET || logic->tricks.fireStrength) && BOMBS && CanSurviveDamage && CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Fire Temple Boulder Maze Lower", {GLITCHLESS((GORON_BRACELET || (IS_ADULT && logic->tricks.fireStrength)) && (HAS_EXPLOSIVES || (IS_ADULT && (CAN_USE_BOW || CAN_USE_HOOKSHOT || CAN_USE_SLINGSHOT))))}},
                                              // /*Glitched*/[]{return (GORON_BRACELET || (IS_ADULT && logic->tricks.fireStrength)) && (CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                                              //                       (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) && CAN_USE_STICKS));}}},
// }},
//
// {"Fire Temple Shortcut Climb", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Shortcut Room",      {GLITCHLESS(true)}},
//        {"Fire Temple Boulder Maze Upper", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Boulder Maze Lower", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Boulder Maze Lower Chest", {GLITCHLESS(true)}},
//        {"Fire Temple GS Boulder Maze",          {GLITCHLESS(HAS_EXPLOSIVES && (IS_ADULT || BOOMERANG || CAN_USE_HOOKSHOT))}},
//                                                           /*Glitched*/[]{return (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) && BOMBS) ||
//                                                                                 HERE(FIRE_TEMPLE_BOULDER_MAZE_UPPER, []{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);});}}},
//    }, {
//    //Exits
//        {"Fire Temple Shortcut Room",                {GLITCHLESS(true)}},
//        {"Fire Temple Boulder Maze Lower Side Room", {GLITCHLESS(true)}},
//        {"Fire Temple East Central Room",            {[this]{return SmallKeys(FIRE_TEMPLE, 5, 7);}}},
//        {"Fire Temple Boulder Maze Upper",           {GLITCHLESS(false)}},
                                                        // /*Glitched*/[]{return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) && BOMBS;}}},
// }},
//
// {"Fire Temple Boulder Maze Lower Side Room", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Boulder Maze Side Room Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Boulder Maze Lower", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple East Central Room", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Big Lava Room",      {GLITCHLESS(CAN_TAKE_DAMAGE)}},
//        {"Fire Temple Boulder Maze Lower", {[this]{return SmallKeys(FIRE_TEMPLE, 5, 8);}}},
//        {"Fire Temple Fire Wall Chase",    {[this]{return SmallKeys(FIRE_TEMPLE, 6, 8);}}},
//        {"Fire Temple Map Area",           {GLITCHLESS(CAN_USE_SLINGSHOT || CAN_USE_BOW)}},
// }},
//
// {"Fire Temple Fire Wall Chase", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple East Central Room",  {[this]{return FIRE_TIMER >= 24 && SmallKeys(FIRE_TEMPLE, 6, 8);}}},
//        {"Fire Temple Map Area",           {GLITCHLESS(IS_ADULT)}},
//        {"Fire Temple Boulder Maze Upper", {[this]{return FIRE_TIMER >= 24 && IS_ADULT;}}},
//                                               /*Glitched*/[]{return FIRE_TIMER >= 32 && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Fire Temple Corridor",           {[this]{return FIRE_TIMER >= 24 && IS_ADULT && FIRE_TEMPLE_SMALL_KEYS >= 7;}}},
//                                               /*Glitched*/[]{return FIRE_TIMER >= 32 && FIRE_TEMPLE_SMALL_KEYS >= 7 && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Fire Temple Map Area", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Map Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple East Central Room", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Boulder Maze Upper", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Boulder Maze Upper Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Shortcut Climb",     {GLITCHLESS(HAS_EXPLOSIVES)}},
//        {"Fire Temple Boulder Maze Lower", {GLITCHLESS(true)}},
//        {"Fire Temple Fire Wall Chase",    {GLITCHLESS(true)}},
//        {"Fire Temple Scarecrow Room",     {GLITCHLESS(CAN_USE_SCARECROW || (logic->tricks.fireScarecrow && IS_ADULT && CAN_USE_LONGSHOT))}},
// }},
//
// {"Fire Temple Scarecrow Room", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple GS Scarecrow Climb", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
//    }, {
//    //Exits
//        {"Fire Temple Boulder Maze Upper", {GLITCHLESS(true)}},
//        {"Fire Temple East Peak",          {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple East Peak", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Scarecrow Chest",  {GLITCHLESS(true)}},
//        {"Fire Temple GS Scarecrow Top", {GLITCHLESS(CanUseProjectile)}},
//    }, {
//    //Exits
//        {"Fire Temple Scarecrow Room",    {GLITCHLESS(true)}},
//        {"Fire Temple East Central Room", {GLITCHLESS(CAN_TAKE_DAMAGE)}},
// }},
//
// {"Fire Temple Corridor", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Fire Wall Chase", {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 7;}}},
//        {"Fire Temple Fire Maze Room",  {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Fire Maze Room", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Corridor",            {GLITCHLESS(true)}},
//        {"Fire Temple Fire Maze Upper",     {GLITCHLESS(CAN_USE_HOVER_BOOTS)}},
                                               // /*Glitched*/[]{return BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Fire Temple Fire Maze Side Room", {GLITCHLESS(true)}},
//        {"Fire Temple West Central Lower",  {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 8;}}},
//        {"Fire Temple Late Fire Maze",      {GLITCHLESS(logic->tricks.fireFlameMaze || false)}},
                                               // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) || (CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED) && BOMBS && CAN_SHIELD);}}},
// }},
//
// {"Fire Temple Fire Maze Upper", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Near Boss Room",     {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
//        {"Fire Temple Fire Maze Room",     {GLITCHLESS(true)}},
//        {"Fire Temple West Central Upper", {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
                                              // /*Glitched*/[]{return CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Fire Temple Fire Maze Side Room", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Compass Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple Fire Maze Room", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple West Central Lower", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Highest Goron Chest", {[this]{return HERE(FIRE_TEMPLE_WEST_CENTRAL_UPPER, []{return CAN_PLAY_SONG_OF_TIME && CAN_USE_MEGATON_HAMMER;});}}},
//                                                      /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE) || HERE(FIRE_TEMPLE_WEST_CENTRAL_UPPER, []{return (IS_ADULT || CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) ||
//                                                                            (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE))) &&
//                                                                            (((SongOfTime && (((BUGS || FISH) && CAN_SHIELD /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::NOVICE))) ||
//                                                                            CAN_PLAY_SONG_OF_TIME) && ((CAN_USE_STICKS && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE)) || CAN_USE_MEGATON_HAMMER));});}}},
//    }, {
//    //Exits
//        {"Fire Temple Fire Maze Room",     {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 8;}}},
//        {"Fire Temple West Central Upper", {GLITCHLESS(IS_ADULT && CAN_PLAY_SONG_OF_TIME)}},
//                                               /*Glitched*/[]{return (IS_ADULT && SongOfTime && (((BUGS || FISH) && CAN_SHIELD && (CanSurviveDamage || (CAN_TAKE_DAMAGE && NumBottles >= 2)) && BOMBS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) ||
//                                                                     (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::NOVICE)))) || (BOMBS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//        {"Fire Temple Late Fire Maze",     {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple West Central Upper", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Boss Room",          {GLITCHLESS(false)}},
                                              // /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Fire Temple Fire Maze Upper",    {GLITCHLESS(true)}},
//        {"Fire Temple West Central Lower", {GLITCHLESS(true)}},
// }},
//
// {"Fire Temple Late Fire Maze", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Fire Maze Room",     {GLITCHLESS(false)}},
                                              // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) || (BOMBS && CAN_SHIELD && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED));}}},
//        {"Fire Temple West Central Lower", {GLITCHLESS(true)}},
//        {"Fire Temple Upper Flare Dancer", {GLITCHLESS(HAS_EXPLOSIVES)}},
// }},
//
// {"Fire Temple Upper Flare Dancer", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Late Fire Maze", {[this]{return HERE(FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return (HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_HOOKSHOT) && (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || BOOMERANG);});}}},
//        {"Fire Temple West Climb",     {[this]{return HERE(FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return (HAS_EXPLOSIVES || CAN_USE_MEGATON_HAMMER || CAN_USE_HOOKSHOT) && (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || BOOMERANG);});}}},
// }},
//
// {"Fire Temple West Climb", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Upper Flare Dancer", {GLITCHLESS(true)}},
//        {"Fire Temple West Peak",          {GLITCHLESS(CanUseProjectile)}},
                                              // /*Glitched*/[]{return CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Fire Temple West Peak", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple Megaton Hammer Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Fire Temple West Central Upper", {GLITCHLESS(CAN_TAKE_DAMAGE)}},
//        {"Fire Temple West Climb",         {GLITCHLESS(true)}},
//        {"Fire Temple Hammer Return Path", {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
// }},
//
// {"Fire Temple Hammer Return Path", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Above Fire Maze", {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
// }},
//
// {"Fire Temple Above Fire Maze", "Fire Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Fire Temple Hammer Return Path", {GLITCHLESS(true)}},
//        {"Fire Temple Fire Maze Upper",    {GLITCHLESS(CAN_USE_MEGATON_HAMMER)}},
// }},
// }
//
// if (Dungeon::WaterTemple.IsVanilla()) {
// //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
// {"Water Temple Lobby", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Entryway",              {GLITCHLESS(true)}},
//        {"Water Temple East Lower",            {GLITCHLESS(WaterTempleLow || ((logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)) && (CAN_USE_IRON_BOOTS || (CAN_USE_LONGSHOT && logic->tricks.waterTempleTorchLongshot))))}},
                                                  // /*Glitched*/[]{return ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) || (CAN_USE_FARORES_WIND &&
                                                  //                       ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED))));}}},
//        {"Water Temple North Lower",           {GLITCHLESS(WaterTempleLow || ((logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)) && CAN_USE_IRON_BOOTS))}},
//        {"Water Temple South Lower",           {GLITCHLESS(WaterTempleLow && HAS_EXPLOSIVES && (SILVER_SCALE || CAN_USE_IRON_BOOTS) && (logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)))}},
                                                  // /*Glitched*/[]{return CAN_USE_IRON_BOOTS && (WaterTempleMiddle || WaterTempleHigh) && (logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)) && AdultCanAccess(WATER_TEMPLE_WEST_LOWER) && CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Water Temple West Lower",            {GLITCHLESS(WaterTempleLow && GORON_BRACELET && (IS_CHILD || SILVER_SCALE || CAN_USE_IRON_BOOTS) && (logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)))}},
//        {"Water Temple Central Pillar Lower",  {[this]{return WaterTempleLow && WATER_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Water Temple Central Pillar Upper",  {GLITCHLESS((WaterTempleLow || WaterTempleMiddle) && (HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW))}},
//        {"Water Temple East Middle",           {[this]{return (WaterTempleLow || WaterTempleMiddle || (CAN_USE_IRON_BOOTS && WATER_TIMER >= 16)) && CAN_USE_HOOKSHOT;}}},
//        {"Water Temple West Middle",           {GLITCHLESS(WaterTempleMiddle)}},
                                                  // /*Glitched*/[]{return WaterTempleLow && (CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) || CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE));}}},
//        {"Water Temple High Water",            {GLITCHLESS(IS_ADULT && (CAN_USE_HOVER_BOOTS || (logic->tricks.waterTempleUpperBoost && BOMBS && CAN_TAKE_DAMAGE)))}},
                                                  // /*Glitched*/[]{return CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE) || (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//        {"Water Temple Block Corridor",        {GLITCHLESS((WaterTempleLow || WaterTempleMiddle) && (CAN_USE_SLINGSHOT || CAN_USE_BOW) && (CAN_USE_LONGSHOT || CAN_USE_HOVER_BOOTS || (logic->tricks.waterCentralBOW && (IS_ADULT || WaterTempleMiddle))))}},
                                                  // /*Glitched*/[]{return (WaterTempleLow || WaterTempleMiddle) && IS_ADULT && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Water Temple Falling Platform Room", {[this]{return WaterTempleHigh && WATER_TEMPLE_SMALL_KEYS >= 4;}}},
//                                                   /*Glitched*/[]{return WATER_TEMPLE_SMALL_KEYS >= 4 && (CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE));}}},
//        {"Water Temple Pre Boss Room",         {GLITCHLESS(WaterTempleHigh && CAN_USE_LONGSHOT)}},
                                                  // /*Glitched*/[]{return CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE) || CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) ||
                                                  //                       (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
// }},
//
// {"Water Temple East Lower", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {WaterTempleLow, {GLITCHLESS(WaterTempleLow || CAN_PLAY_ZELDAS_LULLABY)}},
                                  // /*Glitched*/[]{return ZeldasLullaby && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD &&
                                  //                       ((BOMBS /*&& CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)*/) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)))));}}},
//    }, {}, {
//    //Exits
//        {"Water Temple Lobby",        {GLITCHLESS(WaterTempleLow || ((logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)) && CAN_USE_IRON_BOOTS))}},
                                         // /*Glitched*/[]{return ((BUGS || FISH) && CAN_USE_HOVER_BOOTS && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) || (CAN_USE_FARORES_WIND &&
                                         //                       ((CAN_USE_NAYRUS_LOVE && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) || (CanUseMagicArrow && CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED))));}}},
//        {"Water Temple Map Room",     {GLITCHLESS(WaterTempleHigh)}},
//        {"Water Temple Cracked Wall", {GLITCHLESS(WaterTempleMiddle || (WaterTempleHigh && WaterTempleLow && ((CAN_USE_HOVER_BOOTS && logic->tricks.waterCrackedWallHovers) || logic->tricks.waterCrackedWallNothing)))}},
                                         // /*Glitched*/[]{return WaterTempleHigh && WaterTempleLow && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//        {"Water Temple Torch Room",   {GLITCHLESS(WaterTempleLow && (HAS_FIRE_SOURCEWithTorch || CAN_USE_BOW))}},
// }},
//
// {"Water Temple Map Room", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Map Chest", {GLITCHLESS((MAGIC_METER && CanUse(KOKIRI_SWORD)) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD || CAN_USE_HOOKSHOT)}},
//    }, {
//    //Exits
//        {"Water Temple East Lower", {GLITCHLESS((MAGIC_METER && CanUse(KOKIRI_SWORD)) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD || CAN_USE_HOOKSHOT)}},
// }},
//
// {"Water Temple Cracked Wall", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Cracked Wall Chest", {GLITCHLESS(HAS_EXPLOSIVES)}},
                                                     // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Water Temple East Lower", {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Torch Room", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Torches Chest", {GLITCHLESS((MAGIC_METER && CanUse(KOKIRI_SWORD)) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD || CAN_USE_HOOKSHOT)}},
//    }, {
//    //Exits
//        {"Water Temple East Lower", {GLITCHLESS((MAGIC_METER && CanUse(KOKIRI_SWORD)) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD || CAN_USE_HOOKSHOT)}},
// }},
//
// {"Water Temple North Lower", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Lobby",          {GLITCHLESS(true)}},
//        {"Water Temple Boulders Lower", {[this]{return (CAN_USE_LONGSHOT || (logic->tricks.waterBossKeyRegion && CAN_USE_HOVER_BOOTS)) && WATER_TEMPLE_SMALL_KEYS >= 4;}}},
//                                            /*Glitched*/[]{return ((BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
//                                                                  CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE)) && WATER_TEMPLE_SMALL_KEYS >= 4;}}},
// }},
//
// {"Water Temple Boulders Lower", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple GS Near Boss Key Chest", {[this]{return CAN_USE_LONGSHOT || HERE(WATER_TEMPLE_BOULDERS_UPPER, []{return (IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)) || (CAN_USE_IRON_BOOTS && CAN_USE_HOOKSHOT);});}}},
//    }, {
//    //Exits
//        {"Water Temple North Lower",    {[this]{return WATER_TEMPLE_SMALL_KEYS >= 4;}}},
//        {"Water Temple Block Room",     {GLITCHLESS(true)}},
//        {"Water Temple Boulders Upper", {GLITCHLESS((IS_ADULT && (CAN_USE_HOVER_BOOTS || logic->tricks.waterNorthBasementLedgeJump)) || (CAN_USE_HOVER_BOOTS && CAN_USE_IRON_BOOTS))}},
// }},
//
// {"Water Temple Block Room", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Boulders Lower", {GLITCHLESS((GORON_BRACELET && HAS_EXPLOSIVES) || CAN_USE_HOOKSHOT)}},
//        {"Water Temple Jets Room",      {GLITCHLESS((GORON_BRACELET && HAS_EXPLOSIVES) || (CAN_USE_HOOKSHOT && CAN_USE_HOVER_BOOTS))}},
                                           // /*Glitched*/[]{return CAN_USE_HOOKSHOT && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);}}},
// }},
//
// {"Water Temple Jets Room", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Block Room",     {GLITCHLESS(CAN_USE_HOOKSHOT)}},
//        {"Water Temple Boulders Upper", {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Boulders Upper", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Boulders Lower", {GLITCHLESS(true)}},
//        {"Water Temple Jets Room",      {GLITCHLESS(IS_ADULT)}},
//        {"Water Temple Boss Key Room",  {[this]{return (CAN_USE_IRON_BOOTS || (IS_ADULT && logic->tricks.waterBKJumpDive)) && WATER_TEMPLE_SMALL_KEYS >= 5;}}},
// }},
//
// {"Water Temple Boss Key Room", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {
//    //Locations
//        {"Water Temple Boss Key Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Water Temple Boulders Upper", {[this]{return (CAN_USE_IRON_BOOTS || (IS_ADULT && logic->tricks.waterBKJumpDive) || IS_CHILD || SILVER_SCALE) && WATER_TEMPLE_SMALL_KEYS >= 5;}}},
// }},
//
// {"Water Temple South Lower", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple GS Behind Gate", {GLITCHLESS(CAN_USE_HOOKSHOT || (IS_ADULT && CAN_USE_HOVER_BOOTS))}},
                                                 // /*Glitched*/[]{return (CAN_USE_BOOMERANG && CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE)) ||
                                                 //                       (BOMBS && HAS_BOMBCHUS && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));}}},
//    }, {
//    //Exits
//        {"Water Temple Lobby", {GLITCHLESS(CAN_USE_IRON_BOOTS)}},
// }},
//
// {"Water Temple West Lower", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Lobby",       {GLITCHLESS(CAN_USE_HOOKSHOT && CAN_USE_IRON_BOOTS && GORON_BRACELET)}},
                                        // /*Glitched*/[]{return CAN_USE_IRON_BOOTS && (logic->tricks.fewerTunicRequirements || CanUse(ZORA_TUNIC)) && CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE);}}},
//        {"Water Temple Dragon Room", {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
// }},
//
// {"Water Temple Dragon Room", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Dragon Chest", {[this]{return (CAN_USE_HOOKSHOT && CAN_USE_IRON_BOOTS) || (IS_ADULT && logic->tricks.waterDragonAdult && HAS_BOMBCHUS && (SILVER_SCALE || CAN_USE_IRON_BOOTS)) ||
//                                                                      HERE(WATER_TEMPLE_RIVER, []{return IS_ADULT && CAN_USE_BOW && ((logic->tricks.waterDragonAdult && (SILVER_SCALE || CAN_USE_IRON_BOOTS)) || logic->tricks.waterDragonJumpDive);});}}},
                                               // /*Glitched*/[]{return BOMBS && ((IS_ADULT && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::ADVANCED)) || (CAN_USE_IRON_BOOTS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)));}}},
//    }, {
//    //Exits
//        {"Water Temple West Lower", {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Central Pillar Lower", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Lobby",                   {[this]{return WATER_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Water Temple Central Pillar Upper",    {GLITCHLESS(CAN_USE_HOOKSHOT)}},
//        {"Water Temple Central Pillar Basement", {[this]{return WaterTempleMiddle && CAN_USE_IRON_BOOTS && WATER_TIMER >= 40;}}},
//                                                     /*Glitched*/[]{return CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::NOVICE) && CAN_USE_IRON_BOOTS && WATER_TIMER >= 40;}}},
// }},
//
// {"Water Temple Central Pillar Upper", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {WaterTempleMiddle, {GLITCHLESS(WaterTempleMiddle || CAN_PLAY_ZELDAS_LULLABY)}},
                                     // /*Glitched*/[]{return ZeldasLullaby && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD &&
                                     //                       (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)))));}}},
//    }, {
//    //Locations
//        {"Water Temple GS Central Pillar", {GLITCHLESS(CAN_USE_LONGSHOT || (logic->tricks.waterCentralGSFW && WaterTempleHigh && CAN_USE_FARORES_WIND && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)))}},
//    }, {
//    //Exits
//        {"Water Temple Lobby",                {GLITCHLESS(true)}},
//        {"Water Temple Central Pillar Lower", {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Central Pillar Basement", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Central Pillar Chest", {[this]{return CAN_USE_HOOKSHOT && CAN_USE_IRON_BOOTS && WATER_TIMER >= 40;}}},
//    }, {
//    //Exits
//        {"Water Temple Central Pillar Lower", {[this]{return CAN_USE_IRON_BOOTS && WATER_TIMER >= 16;}}},
// }},
//
// {"Water Temple East Middle", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Compass Chest", {GLITCHLESS(CanUseProjectile)}},
//    }, {
//    //Exits
//        {"Water Temple Lobby", {GLITCHLESS(CAN_USE_IRON_BOOTS)}},
// }},
//
// {"Water Temple West Middle", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Lobby",      {GLITCHLESS(true)}},
//        {"Water Temple High Water", {GLITCHLESS(CanUseProjectile)}},
// }},
//
// {"Water Temple High Water", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {WaterTempleHigh, {GLITCHLESS(WaterTempleHigh || CAN_PLAY_ZELDAS_LULLABY)}},
                                   // /*Glitched*/[]{return ZeldasLullaby && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD &&
                                   //                       (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)))));}}},
//    }, {}, {
//    //Exits
//        {"Water Temple Lobby", {GLITCHLESS(true)}},
// }},
//
// {"Water Temple Block Corridor", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Central BOW Target Chest", {GLITCHLESS(GORON_BRACELET && (WaterTempleLow || WaterTempleMiddle))}},
                                                           // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::INTERMEDIATE) && (WaterTempleLow || WaterTempleMiddle);}}},
//    }, {
//    //Exits
//        {"Water Temple Lobby", {GLITCHLESS(CAN_USE_HOOKSHOT)}},
// }},
//
// {"Water Temple Falling Platform Room", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple GS Falling Platform Room", {GLITCHLESS(CAN_USE_LONGSHOT || (logic->tricks.waterFallingPlatformGS && IS_ADULT && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)))}},
//    }, {
//    //Exits
//        {"Water Temple Lobby",               {[this]{return CAN_USE_HOOKSHOT && WATER_TEMPLE_SMALL_KEYS >= 4;}}},
//        {"Water Temple Dragon Pillars Room", {[this]{return CAN_USE_HOOKSHOT && WATER_TEMPLE_SMALL_KEYS >= 5;}}},
// }},
//
// {"Water Temple Dragon Pillars Room", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Falling Platform Room", {GLITCHLESS(CanUseProjectile)}},
//        {"Water Temple Dark Link Room",        {GLITCHLESS(CAN_USE_HOOKSHOT)}},
// }},
//
// {"Water Temple Dark Link Room", "Water Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Water Temple Dragon Pillars Room", {GLITCHLESS(CanUse(KOKIRI_SWORD) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
//        {"Water Temple Longshot Room",       {GLITCHLESS(CanUse(KOKIRI_SWORD) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)}},
// }},
//
// {"Water Temple Longshot Room", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple Longshot Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Water Temple Dark Link Room", {GLITCHLESS(true)}},
//        {"Water Temple River",          {GLITCHLESS(IS_CHILD || CAN_PLAY_SONG_OF_TIME)}},
                                           // /*Glitched*/[]{return SongOfTime && (CanDoGlitch(GlitchType::DungeonBombOI, GlitchDifficulty::INTERMEDIATE) || ((BUGS || FISH) && CAN_SHIELD &&
                                           //                       (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) || (HAS_BOMBCHUS && CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)))));}}},
// }},
//
// {"Water Temple River", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple River Chest", {GLITCHLESS((CAN_USE_SLINGSHOT || CAN_USE_BOW) && (IS_ADULT || CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT))}},
//        {"Water Temple GS River",    {GLITCHLESS((CAN_USE_IRON_BOOTS && CAN_USE_HOOKSHOT) || (logic->tricks.waterRiverGS && CAN_USE_LONGSHOT))}},
//    }, {
//    //Exits
//        {"Water Temple Dragon Room", {GLITCHLESS((CAN_USE_SLINGSHOT || CAN_USE_BOW) && (IS_ADULT || CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT))}},
// }},
//
// {"Water Temple Pre Boss Room", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {}, {
//    //Exits
//        {"Water Temple Lobby",     {GLITCHLESS(true)}},
//        {"Water Temple Boss Room", {GLITCHLESS(BossKeyWaterTemple)}},
// }},
//
// {"Water Temple Boss Room", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {"Water Temple Clear", {GLITCHLESS(WATER_TEMPLE_CLEAR || (CAN_USE_HOOKSHOT && (CanUse(KOKIRI_SWORD) || CAN_USE_MASTER_SWORD || CAN_USE_BIGGORON_SWORD)))}},
//    }, {
//    //Locations
//        {"Water Temple Morpha Heart", {GLITCHLESS(WATER_TEMPLE_CLEAR)}},
//        {"Morpha",                    {GLITCHLESS(WATER_TEMPLE_CLEAR)}},
//    }, {
//    //Exits
//        {"Water Temple Entryway", {GLITCHLESS(WATER_TEMPLE_CLEAR)}},
// }},
// }
//
// if (Dungeon::SpiritTemple.IsVanilla()) {
// {"Spirit Temple Lobby", "Spirit Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Spirit Temple Entryway",    {GLITCHLESS(true)}},
//        {"Spirit Temple Child",       {GLITCHLESS(IS_CHILD)}},
//        {"Spirit Temple Early Adult", {GLITCHLESS(CAN_USE_SILVER_GAUNTLETS)}},
// }},
//
// {"Child Spirit Temple", "Spirit Temple", NO_TIMEPASS, {
//    //Events
//        {NutCrate, {GLITCHLESS(true)}},
//    }, {
//    //Locations
//        {"Spirit Temple Child Bridge Chest",        {GLITCHLESS((BOOMERANG || SLINGSHOT || (HAS_EXPLOSIVES && logic->tricks.spiritChildBombchu)) && (HAS_EXPLOSIVES || ((Nuts || BOOMERANG) && (STICKS || KOKIRI_SWORD || SLINGSHOT))))}},
//        {"Spirit Temple Child Early Torches Chest", {GLITCHLESS((BOOMERANG || SLINGSHOT || (HAS_EXPLOSIVES && logic->tricks.spiritChildBombchu)) && (HAS_EXPLOSIVES || ((Nuts || BOOMERANG) && (STICKS || KOKIRI_SWORD || SLINGSHOT))) && (STICKS || CAN_USE_DINS_FIRE))}},
//        {"Spirit Temple GS Metal Fence",            {GLITCHLESS((BOOMERANG || SLINGSHOT || (HAS_EXPLOSIVES && logic->tricks.spiritChildBombchu)) && (HAS_EXPLOSIVES || ((Nuts || BOOMERANG) && (STICKS || KOKIRI_SWORD || SLINGSHOT))))}},
//    }, {
//    //Exits
//        {"Spirit Temple Child Climb", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 1;}}},
// }},
//
// {"Child Spirit Temple Climb", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Child Climb North Chest", {[this]{return HasProjectile(HasProjectileAge::Both) || ((SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) && CAN_USE_SILVER_GAUNTLETS && HasProjectile(HasProjectileAge::Adult)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 5 && IS_CHILD && HasProjectile(HasProjectileAge::Child));}}},
//        {"Spirit Temple Child Climb East Chest",  {[this]{return HasProjectile(HasProjectileAge::Both) || ((SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) && CAN_USE_SILVER_GAUNTLETS && HasProjectile(HasProjectileAge::Adult)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 5 && IS_CHILD && HasProjectile(HasProjectileAge::Child));}}},
//        {"Spirit Temple GS Sun on Floor Room",    {[this]{return HasProjectile(HasProjectileAge::Both) || CAN_USE_DINS_FIRE ||
//                                                                                     (CAN_TAKE_DAMAGE && (STICKS || KOKIRI_SWORD || HasProjectile(HasProjectileAge::Child))) ||
//                                                                                       (IS_CHILD && SPIRIT_TEMPLE_SMALL_KEYS >= 5 && HasProjectile(HasProjectileAge::Child)) ||
//                                                                                         ((SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) && CAN_USE_SILVER_GAUNTLETS && (HasProjectile(HasProjectileAge::Adult) || CAN_TAKE_DAMAGE));}}},
//    }, {
//    //Exits
//        {"Spirit Temple Central Chamber", {GLITCHLESS(HAS_EXPLOSIVES)}},
// }},
//
// {"Early Adult Spirit Temple", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Compass Chest",            {GLITCHLESS(CAN_USE_HOOKSHOT && CAN_PLAY_ZELDAS_LULLABY)}},
//        {"Spirit Temple Early Adult Right Chest",  {GLITCHLESS(BOW || Hookshot || HAS_BOMBCHUS || (BOMBS && logic->tricks.spiritLowerAdultSwitch))}},
//        {"Spirit Temple First Mirror Left Chest",  {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 3;}}},
//        {"Spirit Temple First Mirror Right Chest", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 3;}}},
//        {"Spirit Temple GS Boulder Room",          {GLITCHLESS(CAN_PLAY_SONG_OF_TIME && (BOW || Hookshot || HAS_BOMBCHUS || (BOMBS && logic->tricks.spiritLowerAdultSwitch)))}},
//    }, {
//    //Exits
//        {"Spirit Temple Central Chamber", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 1;}}},
// }},
//
// {"Spirit Temple Central Chamber", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Map Chest",                    {[this]{return ((HAS_EXPLOSIVES || SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) &&
//
//                                                                                               (CAN_USE_DINS_FIRE ||
//                                                                                                   (((MAGIC_METER && FireArrows) || logic->tricks.spiritMapChest) && BOW && STICKS))) ||
//                                                                                           (SPIRIT_TEMPLE_SMALL_KEYS >= 5 && HAS_EXPLOSIVES &&
//                                                                                               CAN_USE_STICKS) ||
//                                                                                           (SPIRIT_TEMPLE_SMALL_KEYS >= 3 &&
//                                                                                               (CAN_USE_FIRE_ARROWS || (logic->tricks.spiritMapChest && BOW)) &&
//                                                                                               CAN_USE_SILVER_GAUNTLETS);}}},
//        {"Spirit Temple Sun Block Room Chest",         {[this]{return ((HAS_EXPLOSIVES || SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) &&
//                                                                                               (CAN_USE_DINS_FIRE ||
//                                                                                                   (((MAGIC_METER && FireArrows) || logic->tricks.spiritSunChest) && BOW && STICKS))) ||
//                                                                                           (SPIRIT_TEMPLE_SMALL_KEYS >= 5 && HAS_EXPLOSIVES &&
//                                                                                               CAN_USE_STICKS) ||
//                                                                                           (SPIRIT_TEMPLE_SMALL_KEYS >= 3 &&
//                                                                                               (CAN_USE_FIRE_ARROWS || (logic->tricks.spiritSunChest && BOW)) &&
//                                                                                               CAN_USE_SILVER_GAUNTLETS);}}},
//        {"Spirit Temple Statue Room Hand Chest",       {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 3 && CAN_USE_SILVER_GAUNTLETS && CAN_PLAY_ZELDAS_LULLABY;}}},
//        {"Spirit Temple Statue Room Northeast Chest",  {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 3 && CAN_USE_SILVER_GAUNTLETS && CAN_PLAY_ZELDAS_LULLABY && (Hookshot || HOVER_BOOTS);}}},
//        {"Spirit Temple GS Hall After Sun Block Room", {[this]{return (HAS_EXPLOSIVES && BOOMERANG && Hookshot) ||
//                                                                                           (CAN_USE_BOOMERANG && SPIRIT_TEMPLE_SMALL_KEYS >= 5 && HAS_EXPLOSIVES) ||
//                                                                                           (Hookshot && CAN_USE_SILVER_GAUNTLETS &&
//                                                                                               (SPIRIT_TEMPLE_SMALL_KEYS >= 3 ||
//                                                                                                   (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BOOMERANG && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)));}}},
//        {"Spirit Temple GS Lobby",                     {[this]{return ((HAS_EXPLOSIVES || SPIRIT_TEMPLE_SMALL_KEYS >= 3 || (SPIRIT_TEMPLE_SMALL_KEYS >= 2 && BombchusInlogic->tricks. && logic->settings.shuffleDungeonEntrances == SHUFFLEDUNGEONS_OFF)) &&
//                                                                                               logic->tricks.spiritLobbyGS && BOOMERANG && (Hookshot || HOVER_BOOTS)) ||
//                                                                                           (logic->tricks.spiritLobbyGS && SPIRIT_TEMPLE_SMALL_KEYS >= 5 && HAS_EXPLOSIVES && CAN_USE_BOOMERANG) ||
//                                                                                           (SPIRIT_TEMPLE_SMALL_KEYS >= 3 && CAN_USE_SILVER_GAUNTLETS && (Hookshot || HOVER_BOOTS));}}},
//    }, {
//    //Exits
//        {"Spirit Temple Outdoor Hands",              {GLITCHLESS(true)}},
//        {"Spirit Temple Beyond Central Locked Door", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_USE_SILVER_GAUNTLETS;}}},
//        {"Spirit Temple Child Climb",                {GLITCHLESS(true)}},
// }},
//
// {"Spirit Temple Outdoor Hands", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Silver Gauntlets Chest", {[this]{return (SPIRIT_TEMPLE_SMALL_KEYS >= 3 && Longshot && HAS_EXPLOSIVES) || SPIRIT_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Spirit Temple Mirror Shield Chest",    {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_USE_SILVER_GAUNTLETS && HAS_EXPLOSIVES;}}},
//    }, {
//    //Exits
//        {"Desert Colossus", {[this]{return (IS_CHILD && SPIRIT_TEMPLE_SMALL_KEYS >= 5) || (CAN_USE_SILVER_GAUNTLETS && ((SPIRIT_TEMPLE_SMALL_KEYS >= 3 && HAS_EXPLOSIVES) || SPIRIT_TEMPLE_SMALL_KEYS >= 5));}}},
// }},
//
// {"Spirit Temple Beyond Central Locked Door", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Near Four Armos Chest",         {GLITCHLESS(MirrorShield && HAS_EXPLOSIVES)}},
//        {"Spirit Temple Hallway Left Invisible Chest",  {GLITCHLESS((logic->tricks.lensSpirit || CAN_USE_LENS_OF_TRUTH) && HAS_EXPLOSIVES)}},
//        {"Spirit Temple Hallway Right Invisible Chest", {GLITCHLESS((logic->tricks.lensSpirit || CAN_USE_LENS_OF_TRUTH) && HAS_EXPLOSIVES)}},
//    }, {
//    //Exits
//        {"Spirit Temple Beyond Final Locked Door", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 5 && (logic->tricks.spiritWall || CAN_USE_LONGSHOT || HAS_BOMBCHUS || ((BOMBS || Nuts || CAN_USE_DINS_FIRE) && (BOW || CAN_USE_HOOKSHOT || MEGATON_HAMMER )));}}},
// }},
//
// {"Spirit Temple Beyond Final Locked Door", "Spirit Temple", NO_TIMEPASS, {
//    //Events
//        {SpiritTempleClear, {GLITCHLESS(SpiritTempleClear || (MirrorShield && HAS_EXPLOSIVES && Hookshot && BossKeySpiritTemple))}},
// }, {
//    //Locations
//        {"Spirit Temple Boss Key Chest", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY && ((CAN_TAKE_DAMAGE && logic->tricks.flamingChests) || (BOW && Hookshot)))}},
//        {"Spirit Temple Topmost Chest",  {GLITCHLESS(MirrorShield)}},
//        {"Spirit Temple Twinrova Heart", {GLITCHLESS(MirrorShield && HAS_EXPLOSIVES && Hookshot && BossKeySpiritTemple)}},
//        {"Twinrova",                     {GLITCHLESS(MirrorShield && HAS_EXPLOSIVES && Hookshot && BossKeySpiritTemple)}},
// }, {}},
// }
//
// if (Dungeon::ShadowTemple.IsVanilla()) {
// {"Shadow Temple Beginning", "Shadow Temple", NO_TIMEPASS, {
//    //Events
//        {"Nut Pot", {GLITCHLESS(true)}},
//    }, {
//    //Locations
//        {"Shadow Temple Map Chest",         {GLITCHLESS(true)}},
//        {"Shadow Temple Hover Boots Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Shadow Temple Entryway",     {GLITCHLESS(true)}},
//        {"Shadow Temple First Beamos", {GLITCHLESS(HOVER_BOOTS)}},
                                          // /*Glitched*/[]{return CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Shadow Temple First Beamos", "Shadow Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}}, //This fairy pot is only on 3DS
//    }, {
//    //Locations
//        {"Shadow Temple Compass Chest",            {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || STICKS)}},
//        {"Shadow Temple Early Silver Rupee Chest", {GLITCHLESS(CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT)}},
//        {"Shadow Temple GS Near Ship",             {GLITCHLESS(false)}},
                                                            // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && Longshot;}}},
//    }, {
//    //Exits
//        {"Shadow Temple Huge Pit",    {[this]{return HAS_EXPLOSIVES && IS_ADULT && SmallKeys(SHADOW_TEMPLE, 1, 2);}}},
//        {"Shadow Temple Beyond Boat", {GLITCHLESS(false)}},
                                         // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && Longshot && CAN_PLAY_ZELDAS_LULLABY;}}},
// }},
//
// {"Shadow Temple Huge Pit", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple Invisible Blades Visible Chest",   {GLITCHLESS(true)}},
//        {"Shadow Temple Invisible Blades Invisible Chest", {GLITCHLESS(true)}},
//        {"Shadow Temple Falling Spikes Lower Chest",       {GLITCHLESS(true)}},
//        {"Shadow Temple Falling Spikes Upper Chest",       {GLITCHLESS(logic->tricks.shadowUmbrella || GORON_BRACELET)}},
//        {"Shadow Temple Falling Spikes Switch Chest",      {GLITCHLESS(logic->tricks.shadowUmbrella || GORON_BRACELET)}},
//        {"Shadow Temple Invisible Spikes Chest",           {[this]{return SmallKeys(SHADOW_TEMPLE, 2, 3) && (logic->tricks.lensShadowBack || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Shadow Temple Freestanding Key",                 {[this]{return SmallKeys(SHADOW_TEMPLE, 2, 3) && (logic->tricks.lensShadowBack || CAN_USE_LENS_OF_TRUTH) && Hookshot && (BOMBS || GORON_BRACELET || (logic->tricks.shadowFreestandingKey && HAS_BOMBCHUS));}}},
//        {"Shadow Temple GS Like Like Room",                {GLITCHLESS(true)}},
//        {"Shadow Temple GS Falling Spikes Room",           {GLITCHLESS(Hookshot)}},
//        {"Shadow Temple GS Single Giant Pot",              {[this]{return SmallKeys(SHADOW_TEMPLE, 2, 3) && (logic->tricks.lensShadowBack || CAN_USE_LENS_OF_TRUTH) && Hookshot;}}},
//    }, {
//    //Exits
//        {"Shadow Temple Wind Tunnel", {[this]{return (logic->tricks.lensShadowBack || CAN_USE_LENS_OF_TRUTH) && Hookshot && SmallKeys(SHADOW_TEMPLE, 3, 4);}}},
// }},
//
// {"Shadow Temple Wind Tunnel", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple Wind Hint Chest",         {GLITCHLESS(true)}},
//        {"Shadow Temple After Wind Enemy Chest",  {GLITCHLESS(true)}},
//        {"Shadow Temple After Wind Hidden Chest", {GLITCHLESS(true)}},
//        {"Shadow Temple GS Near Ship",            {[this]{return CAN_USE_LONGSHOT && SmallKeys(SHADOW_TEMPLE, 4, 5);}}},
//    }, {
//    //Exits
//        {"Shadow Temple Beyond Boat", {[this]{return CAN_PLAY_ZELDAS_LULLABY && SmallKeys(SHADOW_TEMPLE, 4, 5);}}},
// }},
//
// {"Shadow Temple Beyond Boat", "Shadow Temple", NO_TIMEPASS, {
//    //Events
//        {ShadowTempleClear, {[this]{return ShadowTempleClear || (SHADOW_TEMPLE_SMALL_KEYS >= 5 && BossKeyShadowTemple && (BOW || CAN_USE_DISTANT_SCARECROW || (logic->tricks.shadowStatue && HAS_BOMBCHUS)));}}},
// }, {
//    //Locations
//        {"Shadow Temple Spike Walls Left Chest",      {GLITCHLESS(CAN_USE_DINS_FIRE)}},
//        {"Shadow Temple Boss Key Chest",              {GLITCHLESS(CAN_USE_DINS_FIRE)}},
//        {"Shadow Temple Invisible Floormaster Chest", {GLITCHLESS(true)}},
//        {"Shadow Temple Bongo Bongo Heart",           {[this]{return SHADOW_TEMPLE_SMALL_KEYS >= 5 && BossKeyShadowTemple && (BOW || CAN_USE_DISTANT_SCARECROW || (logic->tricks.shadowStatue && HAS_BOMBCHUS));}}},
//        {"Bongo Bongo",                               {[this]{return SHADOW_TEMPLE_SMALL_KEYS >= 5 && BossKeyShadowTemple && (BOW || CAN_USE_DISTANT_SCARECROW || (logic->tricks.shadowStatue && HAS_BOMBCHUS));}}},
//        {"Shadow Temple GS Triple Giant Pot",         {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::BottomOfTheWell.IsVanilla()) {
// {"Bottom of the Well Main Area", "Bottom of the Well", NO_TIMEPASS, {
//    //Events
//        {StickPot, {GLITCHLESS(true)}},
//        {"Nut Pot",   {GLITCHLESS(true)}},
//    }, {
//    //Locations
//        {"Bottom Of the Well Front Left Fake Wall Chest",   {GLITCHLESS(logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH)}},
//        {"Bottom Of the Well Front Center Bombable Chest",  {GLITCHLESS(HAS_EXPLOSIVES)}},
//        {"Bottom Of the Well Right Bottom Fake Wall Chest", {GLITCHLESS(logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH)}},
//        {"Bottom Of the Well Compass Chest",                {GLITCHLESS(logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH)}},
//        {"Bottom Of the Well Center Skulltula Chest",       {GLITCHLESS(logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH)}},
//        {"Bottom Of the Well Back Left Bombable Chest",     {GLITCHLESS((logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH) && HAS_EXPLOSIVES)}},
//        {"Bottom Of the Well Freestanding Key",             {GLITCHLESS(STICKS || CAN_USE_DINS_FIRE)}},
//        {"Bottom Of the Well Lens Of Truth Chest",          {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY && (KOKIRI_SWORD || (STICKS && logic->tricks.childDeadhand)))}},
//        {"Bottom Of the Well Invisible Chest",              {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH))}},
//        {"Bottom Of the Well Underwater Front Chest",       {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
//        {"Bottom Of the Well Underwater Left Chest",        {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
//        {"Bottom Of the Well Map Chest",                    {[this]{return HAS_EXPLOSIVES || (((BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3 && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH)) || CAN_USE_DINS_FIRE) && GORON_BRACELET);}}},
//        {"Bottom Of the Well Fire Keese Chest",             {[this]{return BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3 && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Bottom Of the Well Like Like Chest",              {[this]{return BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3 && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Bottom Of the Well GS West Inner Room",           {[this]{return BOOMERANG && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH) && BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3;}}},
//        {"Bottom Of the Well GS East Inner Room",           {[this]{return BOOMERANG && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH) && BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3;}}},
//        {"Bottom Of the Well GS Like Like Cage",            {[this]{return BOTTOM_OF_THE_WELL_SMALL_KEYS >= 3 && (logic->tricks.lensBotw || CAN_USE_LENS_OF_TRUTH) && BOOMERANG;}}},
//    }, {
//    //Exits
//        {"Bottom Of the Well Entryway", {GLITCHLESS(true)}},
// }},
// }
//
// if (Dungeon::IceCavern.IsVanilla()) {
// {"Ice Cavern Beginning", "Ice Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Ice Cavern Entryway", {GLITCHLESS(true)}},
//        {"Ice Cavern Main",     {[this]{return HERE(ICE_CAVERN_BEGINNING, []{return IS_ADULT || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE;});}}},
// }},
//
// {"Ice Cavern", "Ice Cavern", NO_TIMEPASS, {
//    //Events
//        {BLUE_FIREAccess, {GLITCHLESS(BLUE_FIREAccess || (IS_ADULT && HAS_BOTTLE))}},
//    }, {
//    //Locations
//        {"Ice Cavern Map Chest",               {GLITCHLESS(BLUE_FIRE && IS_ADULT)}},
//        {"Ice Cavern Compass Chest",           {GLITCHLESS(BLUE_FIRE)}},
//        {"Ice Cavern Iron Boots Chest",        {GLITCHLESS(BLUE_FIRE && (IS_ADULT || SLINGSHOT || STICKS || KOKIRI_SWORD || CAN_USE_DINS_FIRE))}},
//        {"Sheik in Ice Cavern",                {GLITCHLESS(BLUE_FIRE && IS_ADULT)}},
//        {"Ice Cavern Freestanding PoH",        {GLITCHLESS(BLUE_FIRE)}},
//        {"Ice Cavern GS Spinning Scythe Room", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
//        {"Ice Cavern GS Heart Piece Room",     {GLITCHLESS(BLUE_FIRE && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
//        {"Ice Cavern GS Push Block Room",      {GLITCHLESS(BLUE_FIRE && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
// }, {}},
// }
//
// if (Dungeon::GerudoTrainingGrounds.IsVanilla()) {
// {"Gerudo Training Grounds Lobby", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Lobby Left Chest",  {GLITCHLESS(CAN_USE_BOW || CAN_USE_SLINGSHOT)}},
//        {"Gerudo Training Grounds Lobby Right Chest", {GLITCHLESS(CAN_USE_BOW || CAN_USE_SLINGSHOT)}},
//        {"Gerudo Training Grounds Stalfos Chest",     {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
//        {"Gerudo Training Grounds Beamos Chest",      {GLITCHLESS(HAS_EXPLOSIVES && (IS_ADULT || KOKIRI_SWORD))}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Entryway",         {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Heavy Block Room", {GLITCHLESS((IS_ADULT || KOKIRI_SWORD) && (CAN_USE_HOOKSHOT || logic->tricks.gtgWithoutHookshot))}},
//        {"Gerudo Training Grounds Lava Room",        {[this]{return HERE(GERUDO_TRAINING_GROUNDS_LOBBY, []{return (IS_ADULT || KOKIRI_SWORD) && HAS_EXPLOSIVES;});}}},
//        {"Gerudo Training Grounds Central Maze",     {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Hidden Ceiling Chest",   {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 3 && (logic->tricks.lensGtg || CAN_USE_LENS_OF_TRUTH);}}},
                                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE) && (logic->tricks.lensGtg || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Gerudo Training Grounds Maze Path First Chest",  {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 4;}}},
                                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//        {"Gerudo Training Grounds Maze Path Second Chest", {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 6;}}},
                                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//        {"Gerudo Training Grounds Maze Path Third Chest",  {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 7;}}},
                                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//        {"Gerudo Training Grounds Maze Path Final Chest",  {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 9;}}},
                                                                    // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Central Maze Right", {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 9;}}},
                                                          // /*Glitched*/[]{return CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);}}},
// }},
//
// {"Gerudo Training Grounds Central Maze Right", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Maze Right Central Chest", {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Maze Right Side Chest",    {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Freestanding Key",         {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Hammer Room", {GLITCHLESS(CAN_USE_HOOKSHOT)}},
//        {"Gerudo Training Grounds Lava Room",   {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Underwater Silver Rupee Chest", {[this]{return CAN_USE_HOOKSHOT && CAN_PLAY_SONG_OF_TIME && IRON_BOOTS && WATER_TIMER >= 24;}}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Central Maze Right", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME || IS_CHILD)}},
//        {"Gerudo Training Grounds Hammer Room",        {GLITCHLESS(CAN_USE_LONGSHOT  || (CAN_USE_HOVER_BOOTS && CAN_USE_HOOKSHOT))}},
// }},
//
// {"Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Hammer Room Clear Chest",  {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Hammer Room Switch Chest", {GLITCHLESS(CAN_USE_MEGATON_HAMMER || (CAN_TAKE_DAMAGE && logic->tricks.flamingChests))}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Eye Statue Lower", {GLITCHLESS(CAN_USE_MEGATON_HAMMER && BOW)}},
//        {"Gerudo Training Grounds Lava Room",        {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Eye Statue Chest", {GLITCHLESS(CAN_USE_BOW)}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Hammer Room", {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Near Scarecrow Chest", {GLITCHLESS(CAN_USE_BOW)}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Eye Statue Lower", {GLITCHLESS(true)}},
// }},
//
// {"Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Before Heavy Block Chest", {GLITCHLESS(true)}},
//    }, {
//    //Exits
//        {"Gerudo Training Grounds Eye Statue Upper", {GLITCHLESS((logic->tricks.lensGtg || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOOKSHOT || (logic->tricks.gtgFakeWall && CAN_USE_HOVER_BOOTS)))}},
//        {"Gerudo Training Grounds Like Like Room",   {GLITCHLESS((logic->tricks.lensGtg || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOOKSHOT || (logic->tricks.gtgFakeWall && CAN_USE_HOVER_BOOTS)) && CAN_USE_SILVER_GAUNTLETS)}},
// }},
//
// {"Gerudo Training Grounds Like Like Room", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds Heavy Block First Chest",  {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Heavy Block Second Chest", {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Heavy Block Third Chest",  {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds Heavy Block Fourth Chest", {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::GanonsCastle.IsVanilla()) {
// {"Ganon's Castle Lobby", "Ganon's Castle", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Ganons Castle Entryway",     {GLITCHLESS(true)}},
//        {"Ganons Castle Forest Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle Fire Trial",   {GLITCHLESS(true)}},
//        {"Ganons Castle Water Trial",  {GLITCHLESS(true)}},
//        {"Ganons Castle Shadow Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle Spirit Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial",  {GLITCHLESS(CanUse(GOLDEN_GAUNTLETS))}},
//        {"Ganons Castle Tower",        {[this]{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
//                                                                        (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
//                                                                        (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
//                                                                        (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
//                                                                        (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
//                                                                        (LightTrialClear  || Trial::LightTrial.IsSkipped());}}},
//        {"Ganons Castle Deku Scrubs",  {GLITCHLESS(logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH)}},
// }},
//
// {"Ganon's Castle Deku Scrubs", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
//    }, {
//    //Locations
//        {"Ganons Castle Deku Scrub Center Left",  {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle Deku Scrub Center Right", {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle Deku Scrub Right",        {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle Deku Scrub Left",         {GLITCHLESS(CAN_STUN_DEKU)}},
// }, {}},
//
// {"Ganon's Castle Forest Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {ForestTrialClear, {GLITCHLESS(CanUse(LIGHT_ARROWS) && (FireArrows || DinsFire))}},
//    }, {
//    //Locations
//        {"Ganons Castle Forest Trial Chest", {GLITCHLESS(IS_ADULT || CanChildDamage)}},
// }, {}},
//
// {"Ganon's Castle Fire Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {FireTrialClear, {GLITCHLESS(CAN_USE_GORON_TUNIC && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && CAN_USE_LONGSHOT)}},
// }, {}, {}},
//
// {"Ganon's Castle Water Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {BLUE_FIREAccess,  {GLITCHLESS(BLUE_FIREAccess || HAS_BOTTLE)}},
//        {"Fairy Pot",        {[this]{return "Fairy Pot" || BLUE_FIRE;}}},
//        {WaterTrialClear, {GLITCHLESS(BLUE_FIRE && Hammer && CanUse(LIGHT_ARROWS))}},
//    }, {
//    //Locations
//        {"Ganons Castle Water Trial Left Chest",  {GLITCHLESS(true)}},
//        {"Ganons Castle Water Trial Right Chest", {GLITCHLESS(true)}},
// }, {}},
//
// {"Ganon's Castle Shadow Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {ShadowTrialClear, {GLITCHLESS(CanUse(LIGHT_ARROWS) && MEGATON_HAMMER  && ((FireArrows && (logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH)) || (CAN_USE_LONGSHOT && (CAN_USE_HOVER_BOOTS || (DinsFire && (logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH))))))}},
//    }, {
//    //Locations
//        {"Ganons Castle Shadow Trial Front Chest",            {GLITCHLESS(CAN_USE_FIRE_ARROWS || CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS || CAN_PLAY_SONG_OF_TIME || IS_CHILD)}},
//        {"Ganons Castle Shadow Trial Golden Gauntlets Chest", {GLITCHLESS(CAN_USE_FIRE_ARROWS || (CAN_USE_LONGSHOT && (CAN_USE_HOVER_BOOTS || CAN_USE_DINS_FIRE)))}},
// }, {}},
//
// {"Ganon's Castle Spirit Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {"Nut Pot",           {[this]{return "Nut Pot" || ((logic->tricks.spiritTrialHookshot || CAN_USE_HOOKSHOT) && HAS_BOMBCHUS && BOW && MirrorShield && IS_ADULT);}}},
//        {SpiritTrialClear, {GLITCHLESS(CanUse(LIGHT_ARROWS)  && MirrorShield && HAS_BOMBCHUS && (logic->tricks.spiritTrialHookshot || CAN_USE_HOOKSHOT))}},
//    }, {
//    //Locations
//        {"Ganons Castle Spirit Trial Crystal Switch Chest", {GLITCHLESS(logic->tricks.spiritTrialHookshot || CAN_USE_HOOKSHOT)}},
//        {"Ganons Castle Spirit Trial Invisible Chest",      {GLITCHLESS((logic->tricks.spiritTrialHookshot || CAN_USE_HOOKSHOT) && HAS_BOMBCHUS && (logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH))}},
// }, {}},
//
// {"Ganon's Castle Light Trial", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {LightTrialClear, {[this]{return CanUse(LIGHT_ARROWS) && CAN_USE_HOOKSHOT && GANONS_CASTLE_SMALL_KEYS >= 2 && (logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH);}}},
//    }, {
//    //Locations
//        {"Ganons Castle Light Trial First Left Chest",        {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial Second Left Chest",       {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial Third Left Chest",        {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial First Right Chest",       {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial Second Right Chest",      {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial Third Right Chest",       {GLITCHLESS(true)}},
//        {"Ganons Castle Light Trial Invisible Enemies Chest", {GLITCHLESS(logic->tricks.lensCastle || CAN_USE_LENS_OF_TRUTH)}},
//        {"Ganons Castle Light Trial Lullaby Chest",           {[this]{return CAN_PLAY_ZELDAS_LULLABY && GANONS_CASTLE_SMALL_KEYS >= 1;}}},
// }, {}},
// }
//
// {"Ganon's Castle Tower", "Ganons Castle", NO_TIMEPASS, {}, {
//    //Locations
//        {"Ganons Tower Boss Key Chest", {GLITCHLESS(true)}},
//        {"Ganondorf Hint",              {GLITCHLESS(BossKeyGanonsCastle)}},
//        {"Ganon",                       {GLITCHLESS(BossKeyGanonsCastle && CanUse(LIGHT_ARROWS))}},
// }, {}},
//
// /*---------------------------
// |   MASTER QUEST DUNGEONS   |
// ---------------------------*/
// if (Dungeon::DekuTree.IsMQ()) {
// {"Deku Tree MQ Lobby", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
// }, {
//    //Locations
//        {"Deku Tree MQ Map Chest",                 {GLITCHLESS(true)}},
//        {"Deku Tree MQ SLINGSHOT Chest",           {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
//        {"Deku Tree MQ SLINGSHOT Room Back Chest", {GLITCHLESS(HAS_FIRE_SOURCEWithTorch || (IS_ADULT && CAN_USE_BOW))}},
//        {"Deku Tree MQ Basement Chest",            {GLITCHLESS(HAS_FIRE_SOURCEWithTorch || (IS_ADULT && CAN_USE_BOW))}},
//        {"Deku Tree MQ GS Lobby",                  {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK)}},
// }, {
//    //Exits
//        {"Deku Tree Entryway",                     {GLITCHLESS(true)}},
//        {"Deku Tree MQ Compass Room",              {[this]{return HERE(DEKU_TREE_MQ_LOBBY, []{return (IS_CHILD && CAN_USE_SLINGSHOT) || (IS_ADULT && CAN_USE_BOW);}) &&
//                                                                              HERE(DEKU_TREE_MQ_LOBBY, []{return HAS_FIRE_SOURCEWithTorch || (IS_ADULT && CAN_USE_BOW);});}}},
//        {"Deku Tree MQ Basement Water Room Front", {[this]{return HERE(DEKU_TREE_MQ_LOBBY, []{return (IS_CHILD && CAN_USE_SLINGSHOT) || (IS_ADULT && CAN_USE_BOW);}) &&
//                                                                              HERE(DEKU_TREE_MQ_LOBBY, []{return HAS_FIRE_SOURCEWithTorch;});}}},
//        {"Deku Tree MQ Basement Ledge",            {[this]{return logic->tricks.dekuB1Skip || HERE(DEKU_TREE_MQ_LOBBY, []{return IS_ADULT;});}}},
// }},
//
// {"Deku Tree MQ Compass Room", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree MQ Compass Chest",   {GLITCHLESS(true)}},
//        {"Deku Tree MQ GS Compass Room", {[this]{return (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) &&
//                                                                              HERE(DEKU_TREE_MQ_COMPASS_ROOM, []{return HAS_BOMBCHUS ||
//                                                                              (BOMBS && (CAN_PLAY_SONG_OF_TIME || IS_ADULT)) ||
//                                                                              (IS_ADULT && CAN_USE_MEGATON_HAMMER && (CAN_PLAY_SONG_OF_TIME /*|| logic->tricks.dekuMQCompassGS*/));});}}},
// }, {
//    //Exits
//        {"Deku Tree MQ Lobby", {GLITCHLESS(true)}},
// }},
//
// {"Deku Tree MQ Basement Water Room Front", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree MQ Before Spinning Log Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Deku Tree MQ Basement Water Room Back", {[this]{return /*logic->tricks.dekuMQLog || */ (IS_CHILD && (DEKU_SHIELD || HylianShield)) ||
//                                                                            (IS_ADULT && (CAN_USE_LONGSHOT || (CAN_USE_HOOKSHOT && CAN_USE_IRON_BOOTS)));}}},
//        {"Deku Tree MQ Lobby",                    {GLITCHLESS(true)}},
// }},
//
// {"Deku Tree MQ Basement Water Room Front", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree MQ After Spinning Log Chest", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
// }, {
//    //Exits
//        {"Deku Tree MQ Basement Back Room",        {[this]{return HERE(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return (IS_CHILD && CAN_USE_STICKS) || CAN_USE_DINS_FIRE ||
//                                                                              HERE(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, []{return IS_ADULT && CAN_USE_FIRE_ARROWS;});}) &&
//                                                                                HERE(DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return IS_ADULT || KOKIRI_SWORD || CanUseProjectile || (Nuts && STICKS);});}}},
//        {"Deku Tree MQ Basement Water Room Front", {GLITCHLESS(true)}},
// }},
//
// {"Deku Tree MQ Basement Back Room", "Deku Tree", NO_TIMEPASS, {}, {
//    //Locations
//        {"Deku Tree MQ GS Basement Graves Room", {GLITCHLESS((IS_ADULT && CAN_USE_LONGSHOT) || (CAN_PLAY_SONG_OF_TIME && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)))}},
//        {"Deku Tree MQ GS Basement Back Room",   {GLITCHLESS(HAS_FIRE_SOURCEWithTorch && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
// }, {
//    //Exits
//        {"Deku Tree MQ Basement Ledge",           {GLITCHLESS(IS_CHILD)}},
//        {"Deku Tree MQ Basement Water Room Back", {GLITCHLESS((IS_CHILD && CanUse(KOKIRI_SWORD)) || CanUseProjectile || (Nuts && (IS_CHILD && CAN_USE_STICKS)))}},
// }},
//
// {"Deku Tree MQ Basement Ledge", "Deku Tree", NO_TIMEPASS, {
//    //Events
//        {DekuTreeClear, {[this]{return DekuTreeClear || (HERE(DEKU_TREE_MQ_BASEMENT_LEDGE, []{return HAS_FIRE_SOURCEWithTorch;}) &&
//                                                                          HERE(DEKU_TREE_MQ_BASEMENT_LEDGE, []{return HasShield;})  &&
//                                                                          (IS_ADULT || KOKIRI_SWORD || STICKS) && (Nuts || CAN_USE_SLINGSHOT || CAN_USE_BOW || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)));}}},
// }, {
//    //Locations
//        {"Deku Tree MQ Deku Scrub",     {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Deku Tree Queen Gohma Heart", {GLITCHLESS(HAS_FIRE_SOURCEWithTorch && HasShield && (IS_ADULT || KOKIRI_SWORD || STICKS) && (Nuts || CAN_USE_SLINGSHOT || CAN_USE_BOW || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)))}},
//        {"Queen Gohma",                 {GLITCHLESS(HAS_FIRE_SOURCEWithTorch && HasShield && (IS_ADULT || KOKIRI_SWORD || STICKS) && (Nuts || CAN_USE_SLINGSHOT || CAN_USE_BOW || (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG)))}},
// }, {
//    //Exits
//        {"Deku Tree MQ Basement Back Room", {GLITCHLESS(IS_CHILD)}},
//        {"Deku Tree MQ Lobby",              {GLITCHLESS(true)}},
// }},
// }
//
// if (Dungeon::DodongosCavern.IsMQ()) {
// {"Dodongos Cavern MQ Beginning", "Dodongos Cavern", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Dodongos Cavern Entryway", {GLITCHLESS(true)}},
//        {"Dodongos Cavern MQ Lobby", {[this]{return HERE(DODONGOS_CAVERN_MQ_BEGINNING, []{return CAN_BLAST_OR_SMASH || GORON_BRACELET;});}}},
// }},
//
// {"Dodongos Cavern MQ Lobby", "Dodongos Cavern", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS,   {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {"Gossip Stone Fairy", {GLITCHLESS(CAN_SUMMON_GOSSIP_FAIRY && HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Dodongos Cavern MQ Map Chest",                  {GLITCHLESS(true)}},
//        {"Dodongos Cavern MQ Compass Chest",              {GLITCHLESS(IS_ADULT || CAN_CHILD_ATTACK || Nuts)}},
//        {"Dodongos Cavern MQ Larvae Room Chest",          {GLITCHLESS((IS_CHILD && CAN_USE_STICKS) || HAS_FIRE_SOURCE)}},
//        {"Dodongos Cavern MQ Torch Puzzle Room Chest",    {GLITCHLESS(CAN_BLAST_OR_SMASH || (IS_CHILD && CAN_USE_STICKS) || CAN_USE_DINS_FIRE || (IS_ADULT && (logic->tricks.dCJump || HOVER_BOOTS || Hookshot)))}},
//        {"Dodongos Cavern MQ GS Song Of Time Block Room", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME && (CAN_CHILD_ATTACK || IS_ADULT))}},
//        {"Dodongos Cavern MQ GS Larvae Room",             {GLITCHLESS((IS_CHILD && CAN_USE_STICKS) || HAS_FIRE_SOURCE)}},
//        {"Dodongos Cavern MQ GS Lizalfos Room",           {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
//        {"Dodongos Cavern MQ Deku Scrub Lobby Rear",      {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Dodongos Cavern MQ Deku Scrub Lobby Front",     {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Dodongos Cavern MQ Deku Scrub Staircase",       {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Dodongos Cavern Gossip Stone",                  {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Dodongos Cavern MQ Lower Right Side",  {[this]{return HERE(DODONGOS_CAVERN_MQ_LOBBY, []{return CAN_BLAST_OR_SMASH || (((IS_CHILD && CAN_USE_STICKS) || CAN_USE_DINS_FIRE) && CAN_TAKE_DAMAGE);});}}},
//        {"Dodongos Cavern MQ Bomb Bag Area",     {[this]{return IS_ADULT || (HERE(DODONGOS_CAVERN_MQ_LOBBY, []{return IS_ADULT;}) && HAS_EXPLOSIVES);}}},
//                   //Trick: IS_ADULT || HAS_EXPLOSIVES || (logic->tricks.dCMQChildBOMBS && (KOKIRI_SWORD || STICKS) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
//        {"Dodongos Cavern MQ Boss Area",         {GLITCHLESS(HAS_EXPLOSIVES)}},
//                   //Trick: HAS_EXPLOSIVES || (logic->tricks.dCMQEyes && GORON_BRACELET && (IS_ADULT || logic->tricks.dCMQChildBack) && ((IS_CHILD && CAN_USE_STICKS) || CAN_USE_DINS_FIRE || (IS_ADULT && (logic->tricks.dCJump || MEGATON_HAMMER  || HOVER_BOOTS || Hookshot))))
// }},
//
// {"Dodongos Cavern MQ Lower Right Side", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern MQ Deku Scrub Side Room Near Lower Lizalfos", {GLITCHLESS(CAN_STUN_DEKU)}},
// }, {
//    //Exits
//        {"Dodongos Cavern MQ Bomb Bag Area", {[this]{return (HERE(DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, []{return IS_ADULT && CAN_USE_BOW;}) || GORON_BRACELET ||
//                                                                               CAN_USE_DINS_FIRE || HAS_EXPLOSIVES) &&
//                                                                               IS_CHILD && CAN_USE_SLINGSHOT;}}},
// }},
//
// {"Dodongos Cavern MQ Bomb Bag Area", "Dodongos Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Dodongos Cavern MQ Bomb Bag Chest", {GLITCHLESS(true)}},
//        {"Dodongos Cavern MQ GS Scrub Room",  {[this]{return (HERE(DODONGOS_CAVERN_MQ_BOMB_BAG_AREA, []{return IS_ADULT && CAN_USE_BOW;}) ||  GORON_BRACELET || CAN_USE_DINS_FIRE || HAS_EXPLOSIVES) && (CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG);}}},
// }, {
//    //Exits
//        {"Dodongos Cavern MQ Lower Right Side", {GLITCHLESS(true)}},
// }},
//
// {"Dodongos Cavern MQ BossArea", "Dodongos Cavern", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot",            {GLITCHLESS(true)}},
//        {DodongosCavernClear, {GLITCHLESS(DodongosCavernClear || (CAN_BLAST_OR_SMASH && (BOMBS || GORON_BRACELET) && (IS_ADULT || STICKS || KOKIRI_SWORD)))}},
// }, {
//    //Locations
//        {"Dodongos Cavern MQ Under Grave Chest", {GLITCHLESS(true)}},
//        {"Dodongos Cavern Boss Room Chest",      {GLITCHLESS(true)}},
//        {"Dodongos Cavern King Dodongo Heart",   {GLITCHLESS(CAN_BLAST_OR_SMASH && (BOMBS || GORON_BRACELET) && (IS_ADULT || STICKS || KOKIRI_SWORD))}},
//        {"King Dodongo",                         {GLITCHLESS(CAN_BLAST_OR_SMASH && (BOMBS || GORON_BRACELET) && (IS_ADULT || STICKS || KOKIRI_SWORD))}},
//        {"Dodongos Cavern MQ GS Back Area",      {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::JabuJabusBelly.IsMQ()) {
// {"Jabu Jabus Belly MQ Beginning", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {"Nut Pot", {GLITCHLESS(true)}},
// }, {
//    //Locations
//        {"Jabu Jabus Belly MQ Map Chest",             {GLITCHLESS(CAN_BLAST_OR_SMASH)}},
//        {"Jabu Jabus Belly MQ First Room Side Chest", {GLITCHLESS(IS_CHILD && CAN_USE_SLINGSHOT)}},
// }, {
//    //Exits
//        {"Jabu Jabus Belly Entryway", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Main",  {[this]{return HERE(JABU_JABUS_BELLY_MQ_BEGINNING, []{return IS_CHILD && CAN_USE_SLINGSHOT;});}}},
// }},
//
// {"Jabu Jabus Belly MQ Main", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly MQ Second Room Lower Chest",      {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Second Room Upper Chest",      {GLITCHLESS((IS_ADULT && (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT)) || ChildCanAccess(JABU_JABUS_BELLY_MQ_BOSS_AREA))}},
//        {"Jabu Jabus Belly MQ Compass Chest",                {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Basement Near Vines Chest",    {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Basement Near Switches Chest", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ BOOMERANG Room Small Chest",   {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ BOOMERANG Chest",              {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ GS BOOMERANG Chest Room",      {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || (logic->tricks.jabuMQSoTGS && IS_CHILD && CAN_USE_BOOMERANG)
// }, {
//    //Exits
//        {"Jabu Jabus Belly MQ Beginning", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Depths",    {GLITCHLESS(HAS_EXPLOSIVES && IS_CHILD && CAN_USE_BOOMERANG)}},
// }},
//
// {"Jabu Jabus Belly MQ Depths", "Jabu Jabus Belly", NO_TIMEPASS, {}, {
//    //Locations
//        {"Jabu Jabus Belly MQ Falling Like Like Room Chest", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ GS Tailpasaran Room",          {GLITCHLESS(STICKS || CAN_USE_DINS_FIRE)}},
//        {"Jabu Jabus Belly MQ GS Invisible Enemies Room",    {[this]{return (logic->tricks.lensJabuMQ || CAN_USE_LENS_OF_TRUTH) || HERE(JABU_JABUS_BELLY_MQ_MAIN, []{return IS_ADULT && CAN_USE_HOVER_BOOTS && CAN_USE_HOOKSHOT;});}}},
// }, {
//    //Exits
//        {"Jabu Jabus Belly MQ Main",      {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ Boss Area", {GLITCHLESS(STICKS || (CAN_USE_DINS_FIRE && KOKIRI_SWORD))}},
// }},
//
// {"Jabu Jabus Belly MQ Boss Area", "Jabu Jabus Belly", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot",            {GLITCHLESS(true)}},
//        {JabuJabusBellyClear, {GLITCHLESS(true)}},
// }, {
//    //Locations
//        {"Jabu Jabus Belly MQ Cow",             {GLITCHLESS(CAN_PLAY_EPONAS_SONG)}},
//        {"Jabu Jabus Belly MQ Near Boss Chest", {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly Barinade Heart",     {GLITCHLESS(true)}},
//        {"Barinade",                            {GLITCHLESS(true)}},
//        {"Jabu Jabus Belly MQ GS Near Boss",    {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Jabu Jabus Belly MQ Main", {GLITCHLESS(true)}},
// }},
// }
//
// if (Dungeon::ForestTemple.IsMQ()) {
// {"Forest Temple MQ Lobby", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ First Room Chest", {GLITCHLESS(IS_ADULT || BOMBS || CAN_USE_STICKS || Nuts || CAN_USE_BOOMERANG || CAN_USE_DINS_FIRE || KOKIRI_SWORD || CAN_USE_SLINGSHOT)}},
//        {"Forest Temple MQ GS First Hallway", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
// }, {
//    //Exits
//        {"Forest Temple Entryway",        {GLITCHLESS(true)}},
//        {"Forest Temple MQ Central Area", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 1 && (IS_ADULT || CAN_CHILD_ATTACK || Nuts);}}},
// }},
//
// {"Forest Temple MQ Central Area", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Forest Temple MQ Wolfos Chest",       {GLITCHLESS((CAN_PLAY_SONG_OF_TIME || IS_CHILD) && (IS_ADULT || CAN_USE_DINS_FIRE || CAN_USE_STICKS || CAN_USE_SLINGSHOT || KOKIRI_SWORD))}},
//        {"Forest Temple MQ GS Block Push Room", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Nw Outdoors",        {GLITCHLESS((IS_ADULT && CAN_USE_BOW) || (IS_CHILD && CAN_USE_SLINGSHOT))}},
//        {"Forest Temple MQ Ne Outdoors",        {GLITCHLESS((IS_ADULT && CAN_USE_BOW) || (IS_CHILD && CAN_USE_SLINGSHOT))}}, //This is as far as child can get
//        {"Forest Temple MQ After Block Puzzle", {GLITCHLESS(IS_ADULT && GORON_BRACELET)}},
//                   //Trick: IS_ADULT && (GORON_BRACELET || (logic->tricks.forestMQBlockPuzzle && HAS_BOMBCHUS && IS_ADULT && CAN_USE_HOOKSHOT))
//        {"Forest Temple MQ Outdoor Ledge",      {GLITCHLESS(false)}},
//                   //Trick: (logic->tricks.forestMQHallwaySwitchJumpslash && IS_ADULT && CAN_USE_HOVER_BOOTS) || (logic->tricks.forestMQHallwaySwitchHookshot && IS_ADULT && CAN_USE_HOOKSHOT)
//        {"Forest Temple MQ Boss Region",        {GLITCHLESS(ForestTempleJoAndBeth && ForestTempleAmyAndMeg)}},
// }},
//
// {"Forest Temple MQ After Block Puzzle", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ Boss Key Chest", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 3;}}},
// }, {
//    //Exits
//        {"Forest Temple MQ BOW Region",    {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 4;}}},
//        {"Forest Temple MQ Outdoor Ledge", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 3;}}},
//                   //Trick: FOREST_TEMPLE_SMALL_KEYS >= 3 || (logic->tricks.forestMQHallwaySwitchJumpslash && ((IS_ADULT && CAN_USE_HOOKSHOT) || logic->tricks.forestOutsideBackdoor))
//        {"Forest Temple MQ Nw Outdoors",   {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 2;}}},
// }},
//
// {"Forest Temple MQ Outdoor Ledge", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ Redead Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Nw Outdoors", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple MQ NW Outdoors", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ GS Level Island Courtyard", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Ne Outdoors",         {GLITCHLESS((IS_ADULT && (CAN_USE_IRON_BOOTS || CAN_USE_LONGSHOT)) || GOLD_SCALE)}},
//                   //Trick: (IS_ADULT && (CAN_USE_IRON_BOOTS || CAN_USE_LONGSHOT || (logic->tricks.forestMQWellSwim && CAN_USE_HOOKSHOT))) || GOLD_SCALE
//        {"Forest Temple MQ Outdoors Top Ledges", {GLITCHLESS(IS_ADULT && CAN_USE_FIRE_ARROWS)}},
// }},
//
// {"Forest Temple MQ NE Outdoors", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {DekuBabaSTICKS, {GLITCHLESS(DekuBabaSTICKS || (IS_ADULT || KOKIRI_SWORD || BOOMERANG))}},
//        {DekuBabaNuts,   {GLITCHLESS(DekuBabaNuts   || (IS_ADULT || KOKIRI_SWORD || SLINGSHOT || STICKS || HAS_EXPLOSIVES || CAN_USE_DINS_FIRE))}},
// }, {
//    //Locations
//        {"Forest Temple MQ Well Chest",                 {GLITCHLESS((IS_ADULT && CAN_USE_BOW) || (IS_CHILD && CAN_USE_SLINGSHOT))}},
//        {"Forest Temple MQ GS Raised Island Courtyard", {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG) || (IS_ADULT && CAN_USE_FIRE_ARROWS && (CAN_PLAY_SONG_OF_TIME || (CAN_USE_HOVER_BOOTS && logic->tricks.forestDoorFrame))))}},
//        {"Forest Temple MQ GS Well",                    {GLITCHLESS((IS_ADULT && ((CAN_USE_IRON_BOOTS && CAN_USE_HOOKSHOT) || CAN_USE_BOW)) || (IS_CHILD && CAN_USE_SLINGSHOT))}},
// }, {
//    //Exits
//        {"Forest Temple MQ Outdoors Top Ledges", {GLITCHLESS(IS_ADULT && CAN_USE_HOOKSHOT && (CAN_USE_LONGSHOT || CAN_USE_HOVER_BOOTS || CAN_PLAY_SONG_OF_TIME))}},
//        {"Forest Temple MQ Ne Outdoors Ledge",   {GLITCHLESS(IS_ADULT && CAN_USE_LONGSHOT)}},
// }},
//
// {"Forest Temple MQ Outdoors Top Ledges", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ Raised Island Courtyard Upper Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Ne Outdoors",       {GLITCHLESS(true)}},
//        {"Forest Temple MQ Ne Outdoors Ledge", {GLITCHLESS(false)}},
//                   //Trick: logic->tricks.forestOutdoorsLedge && IS_ADULT && CAN_USE_HOVER_BOOTS
// }},
//
// {"Forest Temple MQ NE Outdoors Ledge", "Forest Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Forest Temple MQ Raised Island Courtyard Lower Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Ne Outdoors",  {GLITCHLESS(true)}},
//        {"Forest Temple MQ Falling Room", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
// }},
//
// {"Forest Temple MQ BOW Region", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleJoAndBeth, {GLITCHLESS(ForestTempleJoAndBeth || (IS_ADULT && CAN_USE_BOW))}},
// }, {
//    //Locations
//        {"Forest Temple MQ BOW Chest",     {GLITCHLESS(true)}},
//        {"Forest Temple MQ Map Chest",     {GLITCHLESS(IS_ADULT && CAN_USE_BOW)}},
//        {"Forest Temple MQ Compass Chest", {GLITCHLESS(IS_ADULT && CAN_USE_BOW)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Falling Room", {[this]{return FOREST_TEMPLE_SMALL_KEYS >= 5 && ((IS_ADULT && CAN_USE_BOW) || CAN_USE_DINS_FIRE);}}},
// }},
//
// {"Forest Temple MQ Falling Room", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleAmyAndMeg, {[this]{return ForestTempleAmyAndMeg || (IS_ADULT && CAN_USE_BOW && FOREST_TEMPLE_SMALL_KEYS >= 6);}}},
// }, {
//    //Locations
//        {"Forest Temple MQ Falling Ceiling Room Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Forest Temple MQ Ne Outdoors Ledge", {GLITCHLESS(true)}},
// }},
//
// {"Forest Temple MQ Boss Region", "Forest Temple", NO_TIMEPASS, {
//    //Events
//        {ForestTempleClear, {GLITCHLESS(ForestTempleClear || BossKeyForestTemple)}},
// }, {
//    //Locations
//        {"Forest Temple MQ Basement Chest",   {GLITCHLESS(true)}},
//        {"Forest Temple Phantom Ganon Heart", {GLITCHLESS(BossKeyForestTemple)}},
//        {"Phantom Ganon",                     {GLITCHLESS(BossKeyForestTemple)}},
// }, {}},
// }
//
// if (Dungeon::FireTemple.IsMQ()) {
// {"Fire Temple MQ Lower", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple MQ Map Room Side Chest", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || STICKS || SLINGSHOT || BOMBS || CAN_USE_DINS_FIRE)}},
//        {"Fire Temple MQ Near Boss Chest",     {[this]{return IS_ADULT && FIRE_TIMER >= 24
//                                                                            && (CAN_USE_HOVER_BOOTS || CAN_USE_HOOKSHOT)
//                                                                            && (CAN_USE_FIRE_ARROWS || (CAN_USE_DINS_FIRE &&
//                                                                                                           ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE))
//                                                                                                          || CAN_USE_GORON_TUNIC
//                                                                                                          || CAN_USE_BOW
//                                                                                                          || CAN_USE_LONGSHOT)));}}},
//                   //Trick: IS_ADULT && (logic->tricks.fewerTunicRequirements || CAN_USE_GORON_TUNIC) && (((CAN_USE_HOVER_BOOTS || (logic->tricks.fireMQNearBoss && CAN_USE_BOW)) && HAS_FIRE_SOURCE) || (CAN_USE_HOOKSHOT && CAN_USE_FIRE_ARROWS || (CAN_USE_DINS_FIRE && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE)) || CAN_USE_GORON_TUNIC || CAN_USE_BOW || CAN_USE_LONGSHOT))))
// }, {
//    //Exits
//        {"Fire Temple Entryway",             {GLITCHLESS(true)}},
//        {"Fire Temple MQ Boss Room",         {GLITCHLESS(IS_ADULT && CAN_USE_GORON_TUNIC && CAN_USE_MEGATON_HAMMER && BossKeyFireTemple && ((HAS_FIRE_SOURCE && (logic->tricks.fireBossDoorJump || HOVER_BOOTS)) || HasAccessTo(FIRE_TEMPLE_MQ_UPPER)))}},
//        {"Fire Temple MQ Lower Locked Door", {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 5 && (IS_ADULT || KOKIRI_SWORD);}}},
//        {"Fire Temple MQ Big Lava Room",     {[this]{return IS_ADULT && FIRE_TIMER >= 24 && CAN_USE_MEGATON_HAMMER;}}},
// }},
//
// {"Fire Temple MQ Lower Locked Door", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Fire Temple MQ Megaton Hammer Chest", {GLITCHLESS(IS_ADULT && (HAS_EXPLOSIVES || MEGATON_HAMMER  || Hookshot))}},
//        {"Fire Temple MQ Map Chest",            {GLITCHLESS(IS_ADULT && CAN_USE_MEGATON_HAMMER)}},
// }, {}},
//
// {"Fire Temple MQ Big Lava Room", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {[this]{return "Fairy Pot" || (HAS_FIRE_SOURCE && BOW && IS_ADULT && (CAN_USE_HOOKSHOT || logic->tricks.fireSongOfTime));}}},
//                   //Trick: HAS_FIRE_SOURCE && (BOW || logic->tricks.fireMQBKChest) && IS_ADULT && (CAN_USE_HOOKSHOT || logic->tricks.fireSongOfTime)
// }, {
//    //Locations
//        {"Fire Temple MQ Boss Key Chest",                   {GLITCHLESS(HAS_FIRE_SOURCE && BOW && IS_ADULT && CAN_USE_HOOKSHOT)}},
//                   //Trick: HAS_FIRE_SOURCE && (BOW || logic->tricks.fireMQBKChest) && IS_ADULT && CAN_USE_HOOKSHOT
//        {"Fire Temple MQ Big Lava Room Blocked Door Chest", {GLITCHLESS(HAS_FIRE_SOURCE && HAS_EXPLOSIVES && IS_ADULT && CAN_USE_HOOKSHOT)}},
//                   //Trick: HAS_FIRE_SOURCE && HAS_EXPLOSIVES && IS_ADULT && (CAN_USE_HOOKSHOT || logic->tricks.fireMQBlockedChest)
//        {"Fire Temple MQ GS Big Lava Room Open Door",       {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Fire Temple MQ Lower Maze", {[this]{return IS_ADULT && CAN_USE_GORON_TUNIC && FIRE_TEMPLE_SMALL_KEYS >= 2 && HAS_FIRE_SOURCE;}}},
//                   //Trick: IS_ADULT && CAN_USE_GORON_TUNIC && FIRE_TEMPLE_SMALL_KEYS >= 2 && (HAS_FIRE_SOURCE || (logic->tricks.fireMQClimb && HOVER_BOOTS))
// }},
//
// {"Fire Temple MQ Lower Maze", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple MQ Lizalfos Maze Lower Chest",     {GLITCHLESS(true)}},
//        {"Fire Temple MQ Lizalfos Maze Side Room Chest", {GLITCHLESS(HAS_EXPLOSIVES && HasAccessTo(FIRE_TEMPLE_MQ_UPPER_MAZE))}},
//                   //Trick: HAS_EXPLOSIVES && (logic->tricks.fireMQMazeSideRoom || FIRE_TEMPLE_MQ_UPPER_MAZE.Adult())
//  }, {
//    //Exits
//        {"Fire Temple MQ Upper Maze", {GLITCHLESS(HAS_EXPLOSIVES && IS_ADULT && CAN_USE_HOOKSHOT)}},
//                   //Trick: (IS_ADULT && ((HAS_EXPLOSIVES && CAN_USE_HOOKSHOT) || (logic->tricks.fireMQMazeHovers && CAN_USE_HOVER_BOOTS))) || logic->tricks.fireMQMazeJump
// }},
//
// {"Fire Temple MQ Upper Maze", "Fire Temple", NO_TIMEPASS, {
//    //Events
//                 //        {WallFairy, {GLITCHLESS(WallFairy || (IS_ADULT && (((CAN_PLAY_SONG_OF_TIME && CAN_USE_HOOKSHOT && HAS_EXPLOSIVES) || CAN_USE_LONGSHOT))))}},
//        {"Fairy Pot",  {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 3;}}},
// }, {
//    //Locations
//        {"Fire Temple MQ Lizalfos Maze Upper Chest", {GLITCHLESS(true)}},
//        {"Fire Temple MQ Compass Chest",             {GLITCHLESS(HAS_EXPLOSIVES)}},
//        {"Fire Temple MQ GS Skull on Fire",          {GLITCHLESS(IS_ADULT && ((CAN_PLAY_SONG_OF_TIME && CAN_USE_HOOKSHOT && HAS_EXPLOSIVES) || CAN_USE_LONGSHOT))}},
// }, {
//    //Exits
//        {"Fire Temple MQ Upper", {[this]{return FIRE_TEMPLE_SMALL_KEYS >= 3 && IS_ADULT && ((CAN_USE_BOW && CAN_USE_HOOKSHOT) || CAN_USE_FIRE_ARROWS);}}},
// }},
//
// {"Fire Temple MQ Upper", "Fire Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Fire Temple MQ Freestanding Key",            {GLITCHLESS(IS_ADULT && CAN_USE_HOOKSHOT)}},
//                   //Trick: (IS_ADULT && CAN_USE_HOOKSHOT) || logic->tricks.fireMQFlameMaze
//        {"Fire Temple MQ Chest on Fire",               {[this]{return IS_ADULT && CAN_USE_HOOKSHOT && FIRE_TEMPLE_SMALL_KEYS >= 4;}}},
//                   //Trick: ((IS_ADULT && CAN_USE_HOOKSHOT) || logic->tricks.fireMQFlameMaze) && FIRE_TEMPLE_SMALL_KEYS >= 4
//        {"Fire Temple MQ GS Fire Wall Maze Side Room", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME || HOVER_BOOTS)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || HOVER_BOOTS || logic->tricks.fireMQFlameMaze
//        {"Fire Temple MQ GS Fire Wall Maze Center",    {GLITCHLESS(HAS_EXPLOSIVES)}},
//        {"Fire Temple MQ GS Above Fire Wall Maze",     {[this]{return IS_ADULT && CAN_USE_HOOKSHOT && FIRE_TEMPLE_SMALL_KEYS >= 5;}}},
//                   //Trick: (IS_ADULT && CAN_USE_HOOKSHOT && FIRE_TEMPLE_SMALL_KEYS >= 5) || (logic->tricks.fireMQAboveMazeGS && IS_ADULT && CAN_USE_LONGSHOT)
// }, {}},
//
// {"Fire Temple MQ Boss Room", "Fire Temple", NO_TIMEPASS, {
//    //Events
//        {FireTempleClear, {GLITCHLESS(true)}},
// }, {
//    //Locations
//        {"Fire Temple Volvagia Heart", {GLITCHLESS(true)}},
//        {"Volvagia",                   {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::WaterTemple.IsMQ()) {
// {"Water Temple MQ Lobby", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {"Water Temple Clear", {GLITCHLESS(BossKeyWaterTemple && IS_ADULT && CAN_USE_LONGSHOT)}},
// }, {
//    //Locations
//        {"Water Temple Morpha Heart", {GLITCHLESS(BossKeyWaterTemple && IS_ADULT && CAN_USE_LONGSHOT)}},
//        {"Morpha",                    {GLITCHLESS(BossKeyWaterTemple && IS_ADULT && CAN_USE_LONGSHOT)}},
// }, {
//    //Exits
//        {"Water Temple Entryway",            {GLITCHLESS(true)}},
//        {"Water Temple MQ Dive",             {[this]{return IS_ADULT && WATER_TIMER >= 24 && CAN_USE_IRON_BOOTS;}}},
//        {"Water Temple MQ Dark Link Region", {[this]{return WATER_TEMPLE_SMALL_KEYS >= 1 && IS_ADULT && CAN_USE_LONGSHOT;}}},
// }},
//
// {"Water Temple MQ Dive", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple MQ Map Chest",            {GLITCHLESS(HAS_FIRE_SOURCE && IS_ADULT && CAN_USE_HOOKSHOT)}},
//        {"Water Temple MQ Central Pillar Chest", {GLITCHLESS(IS_ADULT && CanUse(ZORA_TUNIC) && CAN_USE_HOOKSHOT && (CAN_USE_DINS_FIRE && CAN_PLAY_SONG_OF_TIME))}},
//                   //Trick: IS_ADULT && CanUse(ZORA_TUNIC) && CAN_USE_HOOKSHOT && ((logic->tricks.waterMQCentralPillar && CAN_USE_FIRE_ARROWS) || (CAN_USE_DINS_FIRE && CAN_PLAY_SONG_OF_TIME))
// }, {
//    //Exits
//        {"Water Temple MQ Lowered Water Levels", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
// }},
//
// {"Water Temple MQ Lowered Water Levels", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple MQ Compass Chest",                {[this]{return (IS_ADULT && CAN_USE_BOW) || CAN_USE_DINS_FIRE || HERE(WATER_TEMPLE_MQ_LOBBY, []{return IS_CHILD && CAN_USE_STICKS && HAS_EXPLOSIVES;});}}},
//        {"Water Temple MQ Longshot Chest",               {GLITCHLESS(IS_ADULT && CAN_USE_HOOKSHOT)}},
//        {"Water Temple MQ GS Lizalfos Hallway",          {GLITCHLESS(CAN_USE_DINS_FIRE)}},
//        {"Water Temple MQ GS Before Upper Water Switch", {GLITCHLESS(IS_ADULT && CAN_USE_LONGSHOT)}},
// }, {}},
//
// {"Water Temple MQ Dark Link Region", "Water Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
//        {"Nut Pot",   {GLITCHLESS(true)}},
// }, {
//    //Locations
//        {"Water Temple MQ Boss Key Chest", {[this]{return IS_ADULT && WATER_TIMER >= 24 && CAN_USE_DINS_FIRE && (logic->tricks.waterDragonJumpDive || SILVER_SCALE || CAN_USE_IRON_BOOTS);}}},
//        {"Water Temple MQ GS River",       {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Water Temple MQ Basement Gated Areas", {[this]{return IS_ADULT && WATER_TIMER >= 24 && CAN_USE_DINS_FIRE && CAN_USE_IRON_BOOTS;}}},
// }},
//
// {"Water Temple MQ Basement Gated Areas", "Water Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Water Temple MQ Freestanding Key",         {GLITCHLESS(HOVER_BOOTS || CAN_USE_SCARECROW || logic->tricks.waterNorthBasementLedgeJump)}},
//        {"Water Temple MQ GS Triple Wall Torch",     {GLITCHLESS(CAN_USE_FIRE_ARROWS && (HOVER_BOOTS || CAN_USE_SCARECROW))}},
//        {"Water Temple MQ GS Freestanding Key Area", {[this]{return WATER_TEMPLE_SMALL_KEYS >= 2 && (HOVER_BOOTS || CAN_USE_SCARECROW || logic->tricks.waterNorthBasementLedgeJump);}}},
//                   //Trick: logic->tricks.waterMQLockedGS || (WATER_TEMPLE_SMALL_KEYS >= 2 && (HOVER_BOOTS || CAN_USE_SCARECROW || logic->tricks.waterNorthBasementLedgeJump))
// }, {}},
// }
//
// if (Dungeon::SpiritTemple.IsMQ()) {
// {"Spirit Temple MQ Lobby", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple MQ Entrance Front Left Chest", {GLITCHLESS(true)}},
//        {"Spirit Temple MQ Entrance Back Left Chest",  {[this]{return HERE(SPIRIT_TEMPLE_MQ_LOBBY, []{return CAN_BLAST_OR_SMASH;}) && ((IS_CHILD && CAN_USE_SLINGSHOT) || (IS_ADULT && CAN_USE_BOW));}}},
//        {"Spirit Temple MQ Entrance Back Right Chest", {GLITCHLESS(HAS_BOMBCHUS || (IS_ADULT && (CAN_USE_BOW || CAN_USE_HOOKSHOT)) || (IS_CHILD && (CAN_USE_SLINGSHOT || CAN_USE_BOOMERANG)))}},
// }, {
//    //Exits
//        {"Spirit Temple Entryway", {GLITCHLESS(true)}},
//        {"Spirit Temple MQ Child", {GLITCHLESS(IS_CHILD)}},
//        {"Spirit Temple MQ Adult", {GLITCHLESS(HAS_BOMBCHUS && IS_ADULT && CAN_USE_LONGSHOT && CAN_USE_SILVER_GAUNTLETS)}},
// }},
//
// {"Spirit Temple MQ Child", "Spirit Temple", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {[this]{return "Fairy Pot" || (KOKIRI_SWORD && HAS_BOMBCHUS && SLINGSHOT);}}},
// }, {
//    //Locations
//        {"Spirit Temple MQ Child Hammer Switch Chest",  {[this]{return HERE(SPIRIT_TEMPLE_MQ_ADULT, []{return SPIRIT_TEMPLE_SMALL_KEYS >= 7 && MEGATON_HAMMER ;});}}},
//        {"Spirit Temple MQ Map Room Enemy Chest",       {GLITCHLESS(KOKIRI_SWORD && HAS_BOMBCHUS && SLINGSHOT && CAN_USE_DINS_FIRE)}},
//        {"Spirit Temple MQ Map Chest",                  {GLITCHLESS(KOKIRI_SWORD || BOMBS)}},
//        {"Spirit Temple MQ Silver Block Hallway Chest", {[this]{return HAS_BOMBCHUS && SPIRIT_TEMPLE_SMALL_KEYS >= 7 && SLINGSHOT && (CAN_USE_DINS_FIRE || (HERE(SPIRIT_TEMPLE_MQ_ADULT, []{return IS_ADULT && CAN_USE_FIRE_ARROWS;})));}}},
//                   //Trick: HAS_BOMBCHUS && SPIRIT_TEMPLE_SMALL_KEYS >= 7 && SLINGSHOT && (CAN_USE_DINS_FIRE || (SPIRIT_TEMPLE_MQ_ADULT.Adult() && IS_ADULT && (CAN_USE_FIRE_ARROWS || (logic->tricks.spiritMQFrozenEye && CAN_USE_BOW && CAN_PLAY_SONG_OF_TIME))))
// }, {
//    //Exits
//        {"Spirit Temple MQ Shared", {[this]{return HAS_BOMBCHUS && SPIRIT_TEMPLE_SMALL_KEYS >= 2;}}},
// }},
//
// {"Spirit Temple MQ Adult", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple MQ Child Climb South Chest",     {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 7;}}},
//        {"Spirit Temple MQ Statue Room Lullaby Chest",   {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
//        {"Spirit Temple MQ Statue Room Invisible Chest", {GLITCHLESS((logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH))}},
//        {"Spirit Temple MQ Beamos Room Chest",           {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 5;}}},
//        {"Spirit Temple MQ Chest Switch Chest",          {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 5 && CAN_PLAY_SONG_OF_TIME;}}},
//        {"Spirit Temple MQ Boss Key Chest",              {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 5 && CAN_PLAY_SONG_OF_TIME && MirrorShield;}}},
//        {"Spirit Temple MQ GS Nine Thrones Room West",   {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 7;}}},
//        {"Spirit Temple MQ GS Nine Thrones Room North",  {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 7;}}},
// }, {
//    //Exits
//        {"Spirit Temple MQ Lower Adult",        {GLITCHLESS(MirrorShield && IS_ADULT && CAN_USE_FIRE_ARROWS)}},
//                   //Trick: MirrorShield && IS_ADULT && (CAN_USE_FIRE_ARROWS || (logic->tricks.spiritMQLowerAdult && CAN_USE_DINS_FIRE && BOW))
//        {"Spirit Temple MQ Shared",             {GLITCHLESS(true)}},
//        {"Spirit Temple MQ Boss Area",          {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 6 && CAN_PLAY_ZELDAS_LULLABY && MEGATON_HAMMER ;}}},
//        {"Spirit Temple MQ Mirror Shield Hand", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 5 && CAN_PLAY_SONG_OF_TIME && (logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH);}}},
// }},
//
// {"Spirit Temple MQ Shared", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple MQ Child Climb North Chest", {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 6;}}},
//        {"Spirit Temple MQ Compass Chest",           {[this]{return (IS_CHILD && CAN_USE_SLINGSHOT && SPIRIT_TEMPLE_SMALL_KEYS >= 7) || (IS_ADULT && CAN_USE_BOW) || (BOW && SLINGSHOT);}}},
//        {"Spirit Temple MQ Sun Block Room Chest",    {GLITCHLESS(CAN_PLAY_SONG_OF_TIME || IS_ADULT)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || logic->tricks.spiritMQSunBlockSoT || IS_ADULT
//        {"Spirit Temple MQ GS Sun Block Room",       {GLITCHLESS(IS_ADULT)}},
//                   //Trick: (logic->tricks.spiritMQSunBlockGS && BOOMERANGe && (CAN_PLAY_SONG_OF_TIME || logic->tricks.spiritMQSunBlockSoT)) || IS_ADULT
//  }, {
//    //Exits
//        {"Spirit Temple MQ Silver Gauntlets Hand", {[this]{return (SPIRIT_TEMPLE_SMALL_KEYS >= 7 && (CAN_PLAY_SONG_OF_TIME || IS_ADULT)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_PLAY_SONG_OF_TIME && (logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH));}}},
//                   //Trick: (SPIRIT_TEMPLE_SMALL_KEYS >= 7 && (CAN_PLAY_SONG_OF_TIME || logic->tricks.spiritMQSunBlockSoT || IS_ADULT)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_PLAY_SONG_OF_TIME && (logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH))
//        {"Desert Colossus",                        {[this]{return (SPIRIT_TEMPLE_SMALL_KEYS >= 7 && (CAN_PLAY_SONG_OF_TIME || IS_ADULT)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_PLAY_SONG_OF_TIME && (logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH) && IS_ADULT);}}},
//                   //Trick: (SPIRIT_TEMPLE_SMALL_KEYS >= 7 && (CAN_PLAY_SONG_OF_TIME || logic->tricks.spiritMQSunBlockSoT || IS_ADULT)) || (SPIRIT_TEMPLE_SMALL_KEYS >= 4 && CAN_PLAY_SONG_OF_TIME && (logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH) && IS_ADULT)
// }},
//
// {"Spirit Temple MQ Lower Adult", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple MQ Leever Room Chest",          {GLITCHLESS(true)}},
//        {"Spirit Temple MQ Symphony Room Chest",        {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 7 && MEGATON_HAMMER  && OCARINA && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}}},
//        {"Spirit Temple MQ Entrance Front Right Chest", {GLITCHLESS(MEGATON_HAMMER )}},
//        {"Spirit Temple MQ GS Leever Room",             {GLITCHLESS(true)}},
//        {"Spirit Temple MQ GS Symphony Room",           {[this]{return SPIRIT_TEMPLE_SMALL_KEYS >= 7 && MEGATON_HAMMER  && OCARINA && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}}},
// }, {}},
//
// {"Spirit Temple MQ Boss Area", "Spirit Temple", NO_TIMEPASS, {
//    //Events
//        {SpiritTempleClear, {GLITCHLESS(SpiritTempleClear || (MirrorShield && BossKeySpiritTemple))}},
// }, {
//    //Locations
//        {"Spirit Temple MQ Mirror Puzzle Invisible Chest", {GLITCHLESS(logic->tricks.lensSpiritMQ || CAN_USE_LENS_OF_TRUTH)}},
//        {"Spirit Temple Twinrova Heart",                   {GLITCHLESS(MirrorShield && BossKeySpiritTemple)}},
//        {"Twinrova",                                       {GLITCHLESS(MirrorShield && BossKeySpiritTemple)}},
// }, {}},
//
// {"Spirit Temple MQ Mirror Shield Hand", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Mirror Shield Chest", {GLITCHLESS(true)}},
// }, {}},
//
// {"Spirit Temple MQ Silver Gauntlets Hand", "Spirit Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Spirit Temple Silver Gauntlets Chest", {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::ShadowTemple.IsMQ()) {
// {"Shadow Temple MQ Beginning", "Shadow Temple", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Shadow Temple Entryway",          {GLITCHLESS(true)}},
//        {"Shadow Temple MQ First Beamos",   {GLITCHLESS(IS_ADULT && (CAN_USE_FIRE_ARROWS || CAN_USE_HOVER_BOOTS))}},
//                   //Trick: IS_ADULT && (CAN_USE_FIRE_ARROWS || HOVER_BOOTS || (logic->tricks.shadowMQGap && CAN_USE_LONGSHOT))
//        {"Shadow Temple MQ Dead Hand Area", {[this]{return HAS_EXPLOSIVES && SHADOW_TEMPLE_SMALL_KEYS >= 6;}}},
// }},
//
// {"Shadow Temple MQ Dead Hand Area", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple MQ Compass Chest",     {GLITCHLESS(true)}},
//        {"Shadow Temple MQ Hover Boots Chest", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME && IS_ADULT && CAN_USE_BOW)}},
// }, {}},
//
// {"Shadow Temple MQ First Beamos", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple MQ Map Chest",                 {GLITCHLESS(true)}},
//        {"Shadow Temple MQ Early Gibdos Chest",        {GLITCHLESS(true)}},
//        {"Shadow Temple MQ Near Ship Invisible Chest", {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Shadow Temple MQ Upper Huge Pit", {[this]{return HAS_EXPLOSIVES && SHADOW_TEMPLE_SMALL_KEYS >= 2;}}},
// }},
//
// {"Shadow Temple MQ Upper Huge Pit", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple MQ Invisible Blades Visible Chest",   {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || (logic->tricks.shadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
//        {"Shadow Temple MQ Invisible Blades Invisible Chest", {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || (logic->tricks.shadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
// }, {
//    //Exits
//        {"Shadow Temple MQ Lower Huge Pit", {GLITCHLESS(HAS_FIRE_SOURCE)}},
//                   //Trick: HAS_FIRE_SOURCE || logic->tricks.shadowMQHugePit
// }},
//
// {"Shadow Temple MQ Lower Huge Pit", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple MQ Beamos Silver Rupees Chest",  {GLITCHLESS(IS_ADULT && CAN_USE_LONGSHOT)}},
//        {"Shadow Temple MQ Falling Spikes Lower Chest",  {GLITCHLESS(true)}},
//        {"Shadow Temple MQ Falling Spikes Upper Chest",  {GLITCHLESS((logic->tricks.shadowUmbrella && HOVER_BOOTS) || GORON_BRACELET)}},
//        {"Shadow Temple MQ Falling Spikes Switch Chest", {GLITCHLESS((logic->tricks.shadowUmbrella && HOVER_BOOTS) || GORON_BRACELET)}},
//        {"Shadow Temple MQ Invisible Spikes Chest",      {[this]{return HOVER_BOOTS && SHADOW_TEMPLE_SMALL_KEYS >= 3 && (logic->tricks.lensShadowMQBack || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Shadow Temple MQ Stalfos Room Chest",          {[this]{return HOVER_BOOTS && SHADOW_TEMPLE_SMALL_KEYS >= 3 && Hookshot && (logic->tricks.lensShadowMQBack || CAN_USE_LENS_OF_TRUTH);}}},
//        {"Shadow Temple MQ GS Falling Spikes Room",      {GLITCHLESS(Hookshot)}},
// }, {
//    //Exits
//        {"Shadow Temple MQ Wind Tunnel", {[this]{return HOVER_BOOTS && (logic->tricks.lensShadowMQBack || CAN_USE_LENS_OF_TRUTH) && Hookshot && SHADOW_TEMPLE_SMALL_KEYS >= 4;}}},
// }},
//
// {"Shadow Temple MQ Wind Tunnel", "Shadow Temple", NO_TIMEPASS, {
//    //Events
//        {"Nut Pot", {GLITCHLESS(true)}},
// }, {
//    //Locations
//        {"Shadow Temple MQ Wind Hint Chest",         {GLITCHLESS(true)}},
//        {"Shadow Temple MQ After Wind Enemy Chest",  {GLITCHLESS(true)}},
//        {"Shadow Temple MQ After Wind Hidden Chest", {GLITCHLESS(true)}},
//        {"Shadow Temple MQ GS Wind Hint Room",       {GLITCHLESS(true)}},
//        {"Shadow Temple MQ GS After Wind",           {GLITCHLESS(true)}},
// }, {
//    //Exits
//        {"Shadow Temple MQ Beyond Boat", {[this]{return CAN_PLAY_ZELDAS_LULLABY && SHADOW_TEMPLE_SMALL_KEYS >= 5;}}},
// }},
//
// {"Shadow Temple MQ Beyond Boat", "Shadow Temple", NO_TIMEPASS, {
//    //Events
//        {ShadowTempleClear, {GLITCHLESS(ShadowTempleClear || ((BOW || (logic->tricks.shadowStatue && HAS_BOMBCHUS)) && BossKeyShadowTemple))}},
// }, {
//    //Locations
//        {"Shadow Temple Bongo Bongo Heart", {GLITCHLESS((BOW || (logic->tricks.shadowStatue && HAS_BOMBCHUS)) && BossKeyShadowTemple)}},
//        {"Bongo Bongo",                     {GLITCHLESS((BOW || (logic->tricks.shadowStatue && HAS_BOMBCHUS)) && BossKeyShadowTemple)}},
//        {"Shadow Temple MQ GS After Ship",  {GLITCHLESS(true)}},
//        {"Shadow Temple MQ GS Near Boss",   {GLITCHLESS(BOW || (logic->tricks.shadowStatue && HAS_BOMBCHUS))}},
// }, {
//    //Exits
//        {"Shadow Temple MQ Invisible Maze", {GLITCHLESS(BOW && CAN_PLAY_SONG_OF_TIME && IS_ADULT && CAN_USE_LONGSHOT)}},
// }},
//
// {"Shadow Temple MQ Invisible Maze", "Shadow Temple", NO_TIMEPASS, {}, {
//    //Locations
//        {"Shadow Temple MQ Spike Walls Left Chest", {[this]{return CAN_USE_DINS_FIRE && SHADOW_TEMPLE_SMALL_KEYS >= 6;}}},
//        {"Shadow Temple MQ Boss Key Chest",         {[this]{return CAN_USE_DINS_FIRE && SHADOW_TEMPLE_SMALL_KEYS >= 6;}}},
//        {"Shadow Temple MQ Bomb Flower Chest",      {GLITCHLESS(true)}},
//        {"Shadow Temple MQ Freestanding Key",       {GLITCHLESS(true)}},
// }, {}},
// }
//
// if (Dungeon::BottomOfTheWell.IsMQ()) {
// {"Bottom of the Well MQ Perimeter", "Bottom of the Well", NO_TIMEPASS, {
//    //Events
//                 //        {WallFairy, {GLITCHLESS(WallFairy || SLINGSHOT)}},
// }, {
//    //Locations
//        {"Bottom Of the Well MQ Compass Chest",              {GLITCHLESS(KOKIRI_SWORD || (STICKS && logic->tricks.childDeadhand))}},
//        {"Bottom Of the Well MQ Dead Hand Freestanding Key", {GLITCHLESS(HAS_EXPLOSIVES)}},
//                   //Trick: HAS_EXPLOSIVES || (logic->tricks.botWMQDeadHandKey && BOOMERANG)
//        {"Bottom Of the Well MQ GS Basement",                {GLITCHLESS(CAN_CHILD_ATTACK)}},
//        {"Bottom Of the Well MQ GS Coffin Room",             {[this]{return CAN_CHILD_ATTACK && BOTTOM_OF_THE_WELL_SMALL_KEYS >= 2;}}},
// }, {
//    //Exits
//        {"Bottom Of the Well Entryway",  {GLITCHLESS(true)}},
//        {"Bottom Of the Well MQ Middle", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
//                   //Trick: CAN_PLAY_ZELDAS_LULLABY || (logic->tricks.botWMQPits && HAS_EXPLOSIVES)
// }},
//
// {"Bottom of the Well MQ Middle", "Bottom of the Well", NO_TIMEPASS, {}, {
//    //Locations
//        {"Bottom Of the Well MQ Map Chest",                        {GLITCHLESS(true)}},
//        {"Bottom Of the Well MQ Lens Of Truth Chest",              {[this]{return HAS_EXPLOSIVES && BOTTOM_OF_THE_WELL_SMALL_KEYS >= 2;}}},
//        {"Bottom Of the Well MQ East Inner Room Freestanding Key", {GLITCHLESS(true)}},
//        {"Bottom Of the Well MQ GS West Inner Room",               {GLITCHLESS(CAN_CHILD_ATTACK && HAS_EXPLOSIVES)}},
//                   //Trick: CAN_CHILD_ATTACK && (logic->tricks.botWMQPits || HAS_EXPLOSIVES)
// }, {
//    //Exits
//        {"Bottom Of the Well MQ Perimeter", {GLITCHLESS(true)}},
// }},
// }
//
// if (Dungeon::IceCavern.IsMQ()) {
// {"Ice Cavern MQ Beginning", "Ice Cavern", NO_TIMEPASS, {
//    //Events
//        {"Fairy Pot", {GLITCHLESS(HAS_BOTTLE)}},
// }, {}, {
//    //Exits
//        {"Ice Cavern Entryway",             {GLITCHLESS(true)}},
//        {"Ice Cavern MQ Map Room",          {GLITCHLESS(IS_ADULT || CAN_USE_DINS_FIRE || (HAS_EXPLOSIVES && (CAN_USE_STICKS || CAN_USE_SLINGSHOT || KOKIRI_SWORD)))}},
//        {"Ice Cavern MQ Compass Room",      {GLITCHLESS(IS_ADULT && BLUE_FIRE)}},
//        {"Ice Cavern MQ Iron Boots Region", {GLITCHLESS(BLUE_FIRE)}},
// }},
//
// {"Ice Cavern MQ Map Room", "Ice Cavern", NO_TIMEPASS, {
//    //Events
//        {BLUE_FIREAccess,  {GLITCHLESS(BLUE_FIREAccess || HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Ice Cavern MQ Map Chest", {GLITCHLESS(BLUE_FIRE && (IS_ADULT || CAN_USE_STICKS || KOKIRI_SWORD || CanUseProjectile))}},
// }, {}},
//
// {"Ice Cavern MQ Iron Boots Region", "Ice Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Ice Cavern MQ Iron Boots Chest", {GLITCHLESS(IS_ADULT)}},
//        {"Sheik in Ice Cavern",            {GLITCHLESS(IS_ADULT)}},
//        {"Ice Cavern MQ GS Ice Block",     {GLITCHLESS(IS_ADULT || CanUseProjectile)}},
//        {"Ice Cavern MQ GS Scarecrow",     {GLITCHLESS(IS_ADULT && (CAN_USE_SCARECROW || (CAN_USE_HOVER_BOOTS && CAN_USE_LONGSHOT)))}},
//                   //Tricks: (CAN_USE_SCARECROW || (HOVER_BOOTS && CAN_USE_LONGSHOT) || logic->tricks.iceMQScarecrow) && IS_ADULT
// }, {}},
//
// {"Ice Cavern MQ Compass Room", "Ice Cavern", NO_TIMEPASS, {}, {
//    //Locations
//        {"Ice Cavern MQ Compass Chest",    {GLITCHLESS(true)}},
//        {"Ice Cavern MQ Freestanding PoH", {GLITCHLESS(HAS_EXPLOSIVES)}},
//        {"Ice Cavern MQ GS Red Ice",       {GLITCHLESS(CAN_PLAY_SONG_OF_TIME)}},
//                   //Trick: CAN_PLAY_SONG_OF_TIME || logic->tricks.iceMQRedIceGS
// }, {}},
// }
//
// if (Dungeon::GerudoTrainingGrounds.IsMQ()) {
// {"Gerudo Training Grounds MQ Lobby", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds MQ Lobby Left Chest",       {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Lobby Right Chest",      {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Hidden Ceiling Chest",   {GLITCHLESS(logic->tricks.lensGtgMQ || CAN_USE_LENS_OF_TRUTH)}},
//        {"Gerudo Training Grounds MQ Maze Path First Chest",  {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Maze Path Second Chest", {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Maze Path Third Chest",  {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 1;}}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds Entryway",      {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Left Side",  {[this]{return HERE(GERUDO_TRAINING_GROUNDS_MQ_LOBBY, []{return HAS_FIRE_SOURCE;});}}},
//        {"Gerudo Training Grounds MQ Right Side", {[this]{return HERE(GERUDO_TRAINING_GROUNDS_MQ_LOBBY, []{return (IS_ADULT && CAN_USE_BOW) || (IS_CHILD && CAN_USE_SLINGSHOT);});}}},
// }},
//
// {"Gerudo Training Grounds MQ Right Side", "Gerudo Training Grounds", NO_TIMEPASS, {
//    //Events
//                 //        {WallFairy, {GLITCHLESS(WallFairy || (IS_ADULT && CAN_USE_BOW))}},
// }, {
//    //Locations
//        {"Gerudo Training Grounds MQ Dinolfos Chest", {GLITCHLESS(IS_ADULT)}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds MQ Underwater", {GLITCHLESS((BOW || CAN_USE_LONGSHOT) && CAN_USE_HOVER_BOOTS && IS_ADULT)}},
// }},
//
// {"Gerudo Training Grounds MQ Underwater", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds MQ Underwater Silver Rupee Chest", {[this]{return HAS_FIRE_SOURCE && IS_ADULT && CAN_USE_IRON_BOOTS && WATER_TIMER >= 24 && CAN_TAKE_DAMAGE;}}},
// }, {}},
//
// {"Gerudo Training Grounds MQ Left Side", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds MQ First Iron Knuckle Chest", {GLITCHLESS(IS_ADULT || KOKIRI_SWORD || HAS_EXPLOSIVES)}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds MQ Stalfos Room", {GLITCHLESS(IS_ADULT && CAN_USE_LONGSHOT)}},
//                   //Trick: (IS_ADULT && CAN_USE_LONGSHOT) || logic->tricks.gtgMQWithoutHookshot || (logic->tricks.gtgMQWithHookshot && IS_ADULT && CAN_USE_HOOKSHOT)
// }},
//
// {"Gerudo Training Grounds MQ Stalfos Room", "Gerudo Training Grounds", NO_TIMEPASS, {
//    //Events
//        {BLUE_FIREAccess,  {GLITCHLESS(BLUE_FIREAccess || HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Gerudo Training Grounds MQ Before Heavy Block Chest", {GLITCHLESS(IS_ADULT)}},
//        {"Gerudo Training Grounds MQ Heavy Block Chest",        {GLITCHLESS(CAN_USE_SILVER_GAUNTLETS)}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds MQ Back Areas", {GLITCHLESS(IS_ADULT && (logic->tricks.lensGtgMQ || CAN_USE_LENS_OF_TRUTH) && BLUE_FIRE && CAN_PLAY_SONG_OF_TIME)}},
//                   //Trick: IS_ADULT && (logic->tricks.lensGtgMQ || CAN_USE_LENS_OF_TRUTH) && BLUE_FIRE && (CAN_PLAY_SONG_OF_TIME || (logic->tricks.gtgFakeWall && IS_ADULT && CAN_USE_HOVER_BOOTS))
// }},
//
// {"Gerudo Training Grounds MQ Back Areas", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds MQ Eye Statue Chest",          {GLITCHLESS(BOW)}},
//        {"Gerudo Training Grounds MQ Second Iron Knuckle Chest", {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Flame Circle Chest",        {GLITCHLESS(CAN_USE_HOOKSHOT || BOW || HAS_EXPLOSIVES)}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds MQ Central Maze Right", {GLITCHLESS(MEGATON_HAMMER )}},
//        {"Gerudo Training Grounds MQ Right Side",         {GLITCHLESS(CAN_USE_LONGSHOT)}},
// }},
//
// {"Gerudo Training Grounds MQ Central Maze Right", "Gerudo Training Grounds", NO_TIMEPASS, {}, {
//    //Locations
//        {"Gerudo Training Grounds MQ Maze Right Central Chest", {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Maze Right Side Chest",    {GLITCHLESS(true)}},
//        {"Gerudo Training Grounds MQ Ice Arrows Chest",         {[this]{return GERUDO_TRAINING_GROUNDS_SMALL_KEYS >= 3;}}},
// }, {
//    //Exits
//        {"Gerudo Training Grounds MQ Underwater",  {GLITCHLESS(IS_ADULT && (CAN_USE_LONGSHOT || (CAN_USE_HOOKSHOT && BOW)))}},
//        {"Gerudo Training Grounds MQ Right Side",  {GLITCHLESS(IS_ADULT && CAN_USE_HOOKSHOT)}},
// }},
// }
//
// if (Dungeon::GanonsCastle.IsMQ()) {
// {"Ganon's Castle MQ Lobby", "Ganons Castle", NO_TIMEPASS, {}, {}, {
//    //Exits
//        {"Ganons Castle Entryway",        {GLITCHLESS((IS_ADULT || (HAS_EXPLOSIVES || ((Nuts || BOOMERANG) && (STICKS || KOKIRI_SWORD)))))}},
//        {"Ganons Castle MQ Forest Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle MQ Fire Trial",   {GLITCHLESS(true)}},
//        {"Ganons Castle MQ Water Trial",  {GLITCHLESS(true)}},
//        {"Ganons Castle MQ Shadow Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle MQ Spirit Trial", {GLITCHLESS(true)}},
//        {"Ganons Castle MQ Light Trial",  {GLITCHLESS(CanUse(GOLDEN_GAUNTLETS))}},
//        {"Ganons Castle Tower",           {[this]{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
//                                                                           (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
//                                                                           (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
//                                                                           (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
//                                                                           (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
//                                                                           (LightTrialClear  || Trial::LightTrial.IsSkipped());}}},
//        {"Ganons Castle MQ Deku Scrubs",  {GLITCHLESS(logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH)}},
// }},
//
// {"Ganon's Castle MQ Deku Scrubs", "Ganon's Castle", NO_TIMEPASS, {
//    //Events
//        {"Free Fairies", {GLITCHLESS(HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Ganons Castle MQ Deku Scrub Center Left",  {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle MQ Deku Scrub Center",       {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle MQ Deku Scrub Center Right", {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle MQ Deku Scrub Left",         {GLITCHLESS(CAN_STUN_DEKU)}},
//        {"Ganons Castle MQ Deku Scrub Right",        {GLITCHLESS(CAN_STUN_DEKU)}},
// }, {}},
//
// {"Ganon's Castle MQ Forest Trial", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {ForestTrialClear, {GLITCHLESS(IS_ADULT && CanUse(LIGHT_ARROWS) && CAN_PLAY_SONG_OF_TIME)}},
// }, {
//    //Locations
//        {"Ganons Castle MQ Forest Trial Eye Switch Chest",        {GLITCHLESS((IS_ADULT && CAN_USE_BOW) || (IS_CHILD && CAN_USE_SLINGSHOT))}},
//        {"Ganons Castle MQ Forest Trial Frozen Eye Switch Chest", {GLITCHLESS(HAS_FIRE_SOURCE)}},
//        {"Ganons Castle MQ Forest Trial Freestanding Key",        {GLITCHLESS((CAN_USE_HOOKSHOT || CAN_USE_BOOMERANG))}},
// }, {}},
//
// {"Ganon's Castle MQ Fire Trial", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {FireTrialClear, {GLITCHLESS(CAN_USE_GORON_TUNIC && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && (CAN_USE_LONGSHOT || CAN_USE_HOVER_BOOTS))}},
//                   //Trick: CAN_USE_GORON_TUNIC && CanUse(GOLDEN_GAUNTLETS) && CanUse(LIGHT_ARROWS) && (CAN_USE_LONGSHOT || HOVER_BOOTS || (logic->tricks.fireTrialMQ && CAN_USE_HOOKSHOT))
// }, {}, {}},
//
// {"Ganon's Castle MQ Water Trial", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {WaterTrialClear, {[this]{return BLUE_FIRE && IS_ADULT && CanUse(LIGHT_ARROWS) && GANONS_CASTLE_SMALL_KEYS >= 3;}}},
//        {BLUE_FIREAccess,  {GLITCHLESS(BLUE_FIREAccess || HAS_BOTTLE)}},
// }, {
//    //Locations
//        {"Ganons Castle MQ Water Trial Chest", {GLITCHLESS(BLUE_FIRE && (IS_ADULT || CAN_USE_STICKS || KOKIRI_SWORD || CanUseProjectile))}},
// }, {}},
//
// {"Ganon's Castle MQ Shadow Trial", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {ShadowTrialClear, {GLITCHLESS(IS_ADULT && CanUse(LIGHT_ARROWS) && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOVER_BOOTS || (CAN_USE_HOOKSHOT && HAS_FIRE_SOURCE)))}},
//                   //Trick: IS_ADULT && CanUse(LIGHT_ARROWS) && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (HOVER_BOOTS || (Hookshot && (HAS_FIRE_SOURCE || logic->tricks.shadowTrialMQ)))
// }, {
//    //Locations
//        {"Ganons Castle MQ Shadow Trial Bomb Flower Chest", {GLITCHLESS(IS_ADULT && ((BOW && (CAN_USE_HOOKSHOT || CAN_USE_HOVER_BOOTS)) || (CAN_USE_HOVER_BOOTS && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (HAS_EXPLOSIVES || GORON_BRACELET || CAN_USE_DINS_FIRE))))}},
//        {"Ganons Castle MQ Shadow Trial Eye Switch Chest",  {GLITCHLESS(IS_ADULT && BOW && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (CAN_USE_HOVER_BOOTS || (CAN_USE_HOOKSHOT && HAS_FIRE_SOURCE)))}},
//                   //Trick: IS_ADULT && BOW && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (HOVER_BOOTS || (Hookshot && (HAS_FIRE_SOURCE || logic->tricks.shadowTrialMQ)))
// }, {}},
//
// {"Ganon's Castle MQ Spirit Castle", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {SpiritTrialClear, {GLITCHLESS(IS_ADULT && CanUse(LIGHT_ARROWS) && MEGATON_HAMMER  && HAS_BOMBCHUS && FireArrows && MirrorShield)}},
//        {"Nut Pot",           {[this]{return "Nut Pot" || (MEGATON_HAMMER  && HAS_BOMBCHUS && IS_ADULT && CAN_USE_FIRE_ARROWS && MirrorShield);}}},
// }, {
//    //Locations
//        {"Ganons Castle MQ Spirit Trial First Chest",             {GLITCHLESS(IS_ADULT && BOW && MEGATON_HAMMER )}},
//        {"Ganons Castle MQ Spirit Trial Invisible Chest",         {GLITCHLESS(IS_ADULT && BOW && MEGATON_HAMMER  && HAS_BOMBCHUS && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH))}},
//        {"Ganons Castle MQ Spirit Trial Sun Front Left Chest",    {GLITCHLESS(IS_ADULT && MEGATON_HAMMER  && HAS_BOMBCHUS && CAN_USE_FIRE_ARROWS && CanUse(MIRROR_SHIELD))}},
//        {"Ganons Castle MQ Spirit Trial Sun Back Left Chest",     {GLITCHLESS(IS_ADULT && MEGATON_HAMMER  && HAS_BOMBCHUS && CAN_USE_FIRE_ARROWS && CanUse(MIRROR_SHIELD))}},
//        {"Ganons Castle MQ Spirit Trial Golden Gauntlets Chest",  {GLITCHLESS(IS_ADULT && MEGATON_HAMMER  && HAS_BOMBCHUS && CAN_USE_FIRE_ARROWS && CanUse(MIRROR_SHIELD))}},
//        {"Ganons Castle MQ Spirit Trial Sun Back Right Chest",    {GLITCHLESS(IS_ADULT && MEGATON_HAMMER  && HAS_BOMBCHUS && CAN_USE_FIRE_ARROWS && CanUse(MIRROR_SHIELD))}},
// }, {}},
//
// {"Ganon's Castle MQ Light Trial", "Ganons Castle", NO_TIMEPASS, {
//    //Events
//        {LightTrialClear, {[this]{return IS_ADULT && CanUse(LIGHT_ARROWS) && GANONS_CASTLE_SMALL_KEYS >= 3 && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && CAN_USE_HOOKSHOT;}}},
//                   //Trick: IS_ADULT && CanUse(LIGHT_ARROWS) && GANONS_CASTLE_SMALL_KEYS >= 3 && (logic->tricks.lensCastleMQ || CAN_USE_LENS_OF_TRUTH) && (Hookshot || logic->tricks.lightTrialMQ)
// }, {
//    //Locations
//        {"Ganons Castle MQ Light Trial Lullaby Chest", {GLITCHLESS(CAN_PLAY_ZELDAS_LULLABY)}},
// }, {}},
// }
    return WorldBuildingError::NONE;
}
