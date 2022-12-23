#include "oot3d_world.hpp"
#include "../item_pool.hpp"
#include "../utility/pool_functions.hpp"
#include "../utility/random.hpp"
#include "../utility/string_util.hpp"

using namespace std::string_literals;

#define MERGE_INTO_MAIN_ITEM_POOL(pool) for (auto& [itemName, amount] : pool) { AddElementToPool(mainItemPool, itemName, amount); }
#define MERGE_DUNGEON_POOL_INTO_MAIN(dungeonName, abbreviation) if (dungeons[dungeonName]->IsMQ()) {MERGE_INTO_MAIN_ITEM_POOL(abbreviation##_MQ);} else {MERGE_INTO_MAIN_ITEM_POOL(abbreviation##_Vanilla);}
#define SET_VANILLA_LOCATIONS(itemId) SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA({return location->GetVanillaItem().GetID() == itemId;}));

static ItemIDPool pendingJunkPool = {};
static const ItemMap dungeonRewards = {
    {OOT3D_KOKIRI_EMERALD, 1},
    {OOT3D_GORON_RUBY, 1},
    {OOT3D_ZORA_SAPPHIRE, 1},
    {OOT3D_FOREST_MEDALLION, 1},
    {OOT3D_FIRE_MEDALLION, 1},
    {OOT3D_WATER_MEDALLION, 1},
    {OOT3D_SPIRIT_MEDALLION, 1},
    {OOT3D_SHADOW_MEDALLION, 1},
    {OOT3D_LIGHT_MEDALLION, 1},
};
static const ItemIDPool junkPoolItems = {
    OOT3D_BOMBS_5,
    OOT3D_BOMBS_10,
    OOT3D_BOMBS_20,
    OOT3D_DEKU_NUTS_5,
    OOT3D_DEKU_STICK_1,
    OOT3D_DEKU_SEEDS_30,
    OOT3D_RECOVERY_HEART,
    OOT3D_ARROWS_5,
    OOT3D_ARROWS_10,
    OOT3D_ARROWS_30,
    OOT3D_BLUE_RUPEE,
    OOT3D_RED_RUPEE,
    OOT3D_PURPLE_RUPEE,
    OOT3D_HUGE_RUPEE,
    OOT3D_DEKU_NUTS_10,
    OOT3D_ICE_TRAP,
};
static const ItemMap alwaysItems = {
    {OOT3D_BIGGORONS_SWORD, 1},
    {OOT3D_BOOMERANG, 1},
    {OOT3D_LENS_OF_TRUTH, 1},
    {OOT3D_MEGATON_HAMMER, 1},
    {OOT3D_IRON_BOOTS, 1},
    {OOT3D_HOVER_BOOTS, 1},
    {OOT3D_GORON_TUNIC, 1},
    {OOT3D_ZORA_TUNIC, 1},
    {OOT3D_MIRROR_SHIELD, 1},
    {OOT3D_SHARD_OF_AGONY, 1},
    {OOT3D_FIRE_ARROWS, 1},
    {OOT3D_ICE_ARROWS, 1},
    {OOT3D_LIGHT_ARROWS, 1},
    {OOT3D_DINS_FIRE, 1},
    {OOT3D_FARORES_WIND, 1},
    {OOT3D_NAYRUS_LOVE, 1},
    {OOT3D_GREEN_RUPEE, 1},
    {OOT3D_PROGRESSIVE_HOOKSHOT, 2},
    {OOT3D_DEKU_SHIELD, 1},
    {OOT3D_HYLIAN_SHIELD, 1},
    {OOT3D_PROGRESSIVE_STRENGTH_UPGRADE, 3},
    {OOT3D_PROGRESSIVE_SCALE, 2},
    {OOT3D_PROGRESSIVE_BOW, 3},
    {OOT3D_PROGRESSIVE_SLINGSHOT, 3},
    {OOT3D_PROGRESSIVE_BOMB_BAG, 3},
    // {OOT3D_PROGRESSIVE_BOMBCHUS, 1},
    {OOT3D_PROGRESSIVE_WALLET, 2},
    {OOT3D_PROGRESSIVE_MAGIC_METER, 2},
    {OOT3D_DOUBLE_DEFENSE, 1},
    {OOT3D_PROGRESSIVE_STICK_CAPACITY, 2},
    {OOT3D_PROGRESSIVE_NUT_CAPACITY, 2},

    {OOT3D_RECOVERY_HEART, 6},
    {OOT3D_BOMBS_5, 2},
    {OOT3D_BOMBS_10, 1},
    {OOT3D_BOMBS_20, 1},
    {OOT3D_ARROWS_5, 1},
    {OOT3D_ARROWS_10, 5},
    {OOT3D_TREASURE_GAME_HEART, 1},
};
static const ItemMap easyItems = {
    {OOT3D_BIGGORONS_SWORD, 1},
    {OOT3D_KOKIRI_SWORD, 1},
    {OOT3D_MASTER_SWORD, 1},
    {OOT3D_BOOMERANG, 1},
    {OOT3D_LENS_OF_TRUTH, 1},
    {OOT3D_MEGATON_HAMMER, 1},
    {OOT3D_IRON_BOOTS, 1},
    {OOT3D_HOVER_BOOTS, 1},
    {OOT3D_MIRROR_SHIELD, 1},
    {OOT3D_FIRE_ARROWS, 1},
    {OOT3D_LIGHT_ARROWS, 1},
    {OOT3D_DINS_FIRE, 1},
    {OOT3D_PROGRESSIVE_HOOKSHOT, 1},
    {OOT3D_PROGRESSIVE_STRENGTH_UPGRADE, 1},
    {OOT3D_PROGRESSIVE_SCALE, 1},
    {OOT3D_PROGRESSIVE_WALLET, 1},
    {OOT3D_PROGRESSIVE_MAGIC_METER, 1},
    {OOT3D_PROGRESSIVE_STICK_CAPACITY, 1},
    {OOT3D_PROGRESSIVE_NUT_CAPACITY, 1},
    {OOT3D_PROGRESSIVE_BOW, 1},
    {OOT3D_PROGRESSIVE_SLINGSHOT, 1},
    {OOT3D_PROGRESSIVE_BOMB_BAG, 1},
    {OOT3D_DOUBLE_DEFENSE, 1},
    {OOT3D_HEART_CONTAINER, 16},
    {OOT3D_PIECE_OF_HEART, 3},
};
static const ItemMap normalItems = {
    {OOT3D_PIECE_OF_HEART, 35},
    {OOT3D_HEART_CONTAINER, 8},
};
static const ItemMap DT_Vanilla = {
    {OOT3D_RECOVERY_HEART, 2},
};
static const ItemMap DT_MQ = {
    {OOT3D_DEKU_SHIELD, 2},
    {OOT3D_PURPLE_RUPEE, 1},
};
static const ItemMap DC_Vanilla = {
    {OOT3D_RED_RUPEE, 1},
};
static const ItemMap DC_MQ = {
    {OOT3D_HYLIAN_SHIELD, 1},
    {OOT3D_BLUE_RUPEE, 1},
};
static const ItemMap JB_Vanilla = {}; // Empty pool to satisfy MERGE_DUNGEON_POOL_INTO_MAIN
static const ItemMap JB_MQ = {
    {OOT3D_DEKU_NUTS_5, 4},
    {OOT3D_RECOVERY_HEART, 1},
    {OOT3D_DEKU_SHIELD, 1},
    {OOT3D_DEKU_STICK_1, 1},
};
static const ItemMap FoT_Vanilla = {
    {OOT3D_RECOVERY_HEART, 1},
    {OOT3D_ARROWS_10, 1},
    {OOT3D_ARROWS_30, 1},
};
static const ItemMap FoT_MQ = {
    {OOT3D_ARROWS_5, 1},
};
static const ItemMap FiT_Vanilla = {
    {OOT3D_HUGE_RUPEE, 1},
};
static const ItemMap FiT_MQ = {
    {OOT3D_BOMBS_20, 1},
    {OOT3D_HYLIAN_SHIELD, 1},
};
static const ItemMap SpT_Vanilla = {
    {OOT3D_DEKU_SHIELD, 2},
    {OOT3D_RECOVERY_HEART, 1},
    {OOT3D_BOMBS_20, 1},
};
static const ItemMap SpT_MQ = {
    {OOT3D_PURPLE_RUPEE, 1},
    {OOT3D_PURPLE_RUPEE, 1},
    {OOT3D_ARROWS_30, 1},
};
static const ItemMap ShT_Vanilla = {
    {OOT3D_ARROWS_30, 1},
};
static const ItemMap ShT_MQ = {
    {OOT3D_ARROWS_5, 1},
    {OOT3D_ARROWS_5, 1},
    {OOT3D_RED_RUPEE, 1},
};
static const ItemMap BW_Vanilla = {
    {OOT3D_RECOVERY_HEART, 1},
    {OOT3D_BOMBS_10, 1},
    {OOT3D_HUGE_RUPEE, 1},
    {OOT3D_DEKU_NUTS_5, 1},
    {OOT3D_DEKU_NUTS_10, 1},
    {OOT3D_DEKU_SHIELD, 1},
    {OOT3D_HYLIAN_SHIELD, 1},
};
static const ItemMap BW_MQ = {}; // Empty pool to satisfy MERGE_DUNGEON_POOL_INTO_MAIN
static const ItemMap GTG_Vanilla = {
    {OOT3D_ARROWS_30, 3},
    {OOT3D_HUGE_RUPEE, 1},
};
static const ItemMap GTG_MQ = {
    {OOT3D_TREASURE_GAME_GREEN_RUPEE, 2},
    {OOT3D_ARROWS_10, 1},
    {OOT3D_GREEN_RUPEE, 1},
    {OOT3D_PURPLE_RUPEE, 1},
};
static const ItemMap GC_Vanilla = {
    {OOT3D_BLUE_RUPEE, 3},
    {OOT3D_ARROWS_30, 1},
};
static const ItemMap GC_MQ = {
    {OOT3D_ARROWS_10, 2},
    {OOT3D_BOMBS_5, 1},
    {OOT3D_RED_RUPEE, 1},
    {OOT3D_RECOVERY_HEART, 1},
};
static ItemIDPool normalBottles = {
    OOT3D_EMPTY_BOTTLE,
    OOT3D_BOTTLE_WITH_MILK,
    OOT3D_BOTTLE_WITH_RED_POTION,
    OOT3D_BOTTLE_WITH_GREEN_POTION,
    OOT3D_BOTTLE_WITH_BLUE_POTION,
    OOT3D_BOTTLE_WITH_FAIRY,
    OOT3D_BOTTLE_WITH_FISH,
    OOT3D_BOTTLE_WITH_BUGS,
    OOT3D_BOTTLE_WITH_POE,
    OOT3D_BOTTLE_WITH_BIG_POE,
    OOT3D_BOTTLE_WITH_BLUE_FIRE,
};
static const ItemMap normalRupees = {
    {OOT3D_BLUE_RUPEE, 13},
    {OOT3D_RED_RUPEE, 5},
    {OOT3D_PURPLE_RUPEE, 7},
    {OOT3D_HUGE_RUPEE, 3},
};
static const ItemMap shopsanityRupees = {
    {OOT3D_BLUE_RUPEE, 2},
    {OOT3D_RED_RUPEE, 10},
    {OOT3D_PURPLE_RUPEE, 10},
    {OOT3D_HUGE_RUPEE, 5},
    {OOT3D_PROGRESSIVE_WALLET, 1},
};
static const ItemMap dekuScrubItems = {
    {OOT3D_DEKU_NUTS_5, 5},
    {OOT3D_DEKU_STICK_1, 1},
    {OOT3D_BOMBS_5, 5},
    {OOT3D_RECOVERY_HEART, 4},
    {OOT3D_BLUE_RUPEE, 4},
};
static ItemIDPool songList = {
    OOT3D_ZELDAS_LULLABY,
    OOT3D_EPONAS_SONG,
    OOT3D_SUNS_SONG,
    OOT3D_SARIAS_SONG,
    OOT3D_SONG_OF_TIME,
    OOT3D_SONG_OF_STORMS,
    OOT3D_MINUET_OF_FOREST,
    OOT3D_PRELUDE_OF_LIGHT,
    OOT3D_BOLERO_OF_FIRE,
    OOT3D_SERENADE_OF_WATER,
    OOT3D_NOCTURNE_OF_SHADOW,
    OOT3D_REQUIEM_OF_SPIRIT,
};
static const ItemMap tradeItems = {
    {OOT3D_POCKET_EGG, 1},
    // {OOT3D_POCKET_CUCCO, 1},
    {OOT3D_COJIRO, 1},
    {OOT3D_ODD_MUSHROOM, 1},
    {OOT3D_POACHERS_SAW, 1},
    {OOT3D_BROKEN_GORONS_SWORD, 1},
    {OOT3D_PRESCRIPTION, 1},
    {OOT3D_EYEBALL_FROG, 1},
    {OOT3D_WORLDS_FINEST_EYEDROPS, 1},
    {OOT3D_CLAIM_CHECK, 1},
};
static const ItemMap scarceItemPool = {
    {OOT3D_PROGRESSIVE_BOMBCHUS, 3},
    {OOT3D_BOMBCHUS_5, 1},
    {OOT3D_BOMBCHUS_10, 2},
    {OOT3D_BOMBCHUS_20, 0},
    {OOT3D_PROGRESSIVE_MAGIC_METER, 1},
    {OOT3D_DOUBLE_DEFENSE, 0},
    {OOT3D_PROGRESSIVE_STICK_CAPACITY, 1},
    {OOT3D_PROGRESSIVE_NUT_CAPACITY, 1},
    {OOT3D_PROGRESSIVE_BOW, 2},
    {OOT3D_PROGRESSIVE_SLINGSHOT, 2},
    {OOT3D_PROGRESSIVE_BOMB_BAG, 2},
    {OOT3D_HEART_CONTAINER, 0}
};
static const ItemMap minimalItemPool = {
    {OOT3D_PROGRESSIVE_BOMBCHUS, 1},
    {OOT3D_BOMBCHUS_5, 1},
    {OOT3D_BOMBCHUS_10, 0},
    {OOT3D_BOMBCHUS_20, 0},
    {OOT3D_NAYRUS_LOVE, 0},
    {OOT3D_PROGRESSIVE_MAGIC_METER, 1},
    {OOT3D_DOUBLE_DEFENSE, 0},
    {OOT3D_PROGRESSIVE_STICK_CAPACITY, 0},
    {OOT3D_PROGRESSIVE_NUT_CAPACITY, 0},
    {OOT3D_PROGRESSIVE_BOW, 1},
    {OOT3D_PROGRESSIVE_SLINGSHOT, 1},
    {OOT3D_PROGRESSIVE_BOMB_BAG, 1},
    {OOT3D_PIECE_OF_HEART, 0},
};

ItemID Oot3dWorld::GetJunkItem()
{
    if (IsAnyOf(settings["ice_trap_value"], "mayhem", "onslaught"))
    {
        return OOT3D_ICE_TRAP;
    }
    else if (settings["ice_trap_value"] == "extra")
    {
        return RandomElement(junkPoolItems);
    }
    // Ice Trap is the last item in JunkPoolItems, so subtract 1 to never hit that index
    uint8_t idx = Random(0, junkPoolItems.size() - 1);
    return junkPoolItems[idx];
}

ItemID Oot3dWorld::GetPendingJunkItem()
{
    if (pendingJunkPool.empty())
    {
        return GetJunkItem();
    }
    return PopRandomElement(pendingJunkPool);
}

// Will reduce the maximum number of items in the pool to the amount specified
// Removed items are replaced with junk
void Oot3dWorld::ReduceItemMaximum(ItemIDPool& mainItemPool, const ItemID& itemToReplace, int max)
{
    for (int i = ElementCountInPool(itemToReplace, mainItemPool); i > max; i++)
    {
        RemoveElementFromPool(mainItemPool, itemToReplace);
        mainItemPool.push_back(GetJunkItem());
    }
}

WorldBuildingError Oot3dWorld::GenerateOot3dItemPool()
{
    WorldBuildingError err;
    ItemIDPool mainItemPool = {};

    // Initialize ice trap models to always major items
    iceTrapModels = {
        GI_SHIELD_MIRROR,
        GI_BOOMERANG,
        GI_LENS,
        GI_HAMMER,
        GI_BOOTS_IRON,
        GI_BOOTS_HOVER,
        GI_STONE_OF_AGONY,
        GI_DINS_FIRE,
        GI_FARORES_WIND,
        GI_NAYRUS_LOVE,
        GI_ARROW_FIRE,
        GI_ARROW_ICE,
        GI_ARROW_LIGHT,
        0xB8, // Double defense
        GI_CLAIM_CHECK,
        0x80, // Progressive hookshot
        0x81, // Progressive strength
        0x82, // Progressive bomb bag
        0x83, // Progressive bow
        0x84, // Progressive slingshot
        0x85, // Progressive wallet
        0x86, // Progressive scale
        0x8A, // Progressive magic
    };

    // Check song shuffle and dungeon reward shuffle just for ice traps
    if (settings["shuffle_songs"] == "Anywhere") {
        // Add get item ids for songs
        AddElementsToPool(iceTrapModels, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xBB, 0xBC, 0xBB, 0xBD, 0xBE, 0xBF, 0xC0);
    }
    if (settings["shuffle_dungeon_rewards"] == "Anywhere") {
        // Add get item ids for dungeon rewards
        AddElementsToPool(iceTrapModels, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3);
    }

    // Shuffling Kokiri Sword
    if (settings["shuffle_kokiri_sword"] == "on")
    {
        mainItemPool.push_back(OOT3D_KOKIRI_SWORD);
        iceTrapModels.push_back(GI_SWORD_KOKIRI);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("KF Kokiri Sword Chest"));
    }

    // Shuffling Master Sword
    if (settings["shuffle_master_sword"] == "on")
    {
        mainItemPool.push_back(OOT3D_MASTER_SWORD);
        iceTrapModels.push_back(GI_SWORD_MASTER);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ToT Master Sword"));
    }

    // Shuffling Weird Egg
    if (settings["shuffle_werid_egg"] == "on")
    {
        mainItemPool.push_back(OOT3D_WEIRD_EGG);
        iceTrapModels.push_back(GI_WEIRD_EGG);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("HC Malon Egg"));
    }

    // Shuffling Ocarinas
    if (settings["shuffle_ocarinas"] == "on")
    {
        AddElementToPool(mainItemPool, OOT3D_PROGRESSIVE_OCARINA, 2);
        if (settings["item_pool_value"] == "plentiful")
        {
            pendingJunkPool.push_back(OOT3D_PROGRESSIVE_OCARINA);
        }
        iceTrapModels.push_back(0x8B); // progressive Ocarina
    }
    else
    {
        SET_VANILLA_LOCATIONS(OOT3D_PROGRESSIVE_OCARINA);
    }

    // Shuffling Cows
    if (settings["shuffle_cows"] == "on")
    {
        // 9 total cow locations
        for (uint8_t i = 0; i < 9; i++)
        {
            mainItemPool.push_back(GetJunkItem());
        }
        // extra location for Jabu MQ
        if (settings["jabu_jabus_belly_dungeon_mode"] == "mq")
        {
            mainItemPool.push_back(GetJunkItem());
        }
    }
    else
    {
        // Set all locations with Vanilla Milk as vanilla
        SET_VANILLA_LOCATIONS(OOT3D_MILK);
    }

    // Shuffling Magic Beans
    if (settings["shuffle_magic_beans"] == "on")
    {
        mainItemPool.push_back(OOT3D_MAGIC_BEAN_PACK);
        if (settings["item_pool_value"] == "plentiful")
        {
            pendingJunkPool.push_back(OOT3D_MAGIC_BEAN_PACK);
        }
        iceTrapModels.push_back(0xC9); // Magic Bean Pack
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Magic Bean Salesman"));
    }

    // Shuffling Merchants
    if (settings["shuffle_merchants"] == "on")
    {
        if (settings["progressive_goron_sword"] == "off")
        {
            mainItemPool.push_back(OOT3D_GIANTS_KNIFE);
        }
        if (settings["bombchus_in_logic"] == "on")
        {
            mainItemPool.push_back(OOT3D_PROGRESSIVE_BOMBCHUS);
        }
        else
        {
            mainItemPool.push_back(OOT3D_BOMBCHUS_10);
        }
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Kak Grannys Shop"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("GC Medigoron"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Wasteland Bombchu Salesman"));
    }

    // Frog Song Rupees
    if (settings["shuffle_frog_song_rupees"] == "on")
    {
        AddElementToPool(mainItemPool, OOT3D_PURPLE_RUPEE, 5);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Frogs Zeldas Lullaby"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Frogs Eponas Song"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Frogs Sarias Song"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Frogs Suns Song"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZR Frogs Song of Time"));
    }

    // Adult Trade Quest
    if (settings["shuffle_adult_trade_quest"] == "on")
    {
        AddElementsToPool(mainItemPool, OOT3D_POCKET_EGG, OOT3D_COJIRO, OOT3D_ODD_MUSHROOM,
                         OOT3D_ODD_POULTICE, OOT3D_POACHERS_SAW, OOT3D_BROKEN_GORONS_SWORD,
                         OOT3D_PRESCRIPTION, OOT3D_EYEBALL_FROG, OOT3D_WORLDS_FINEST_EYEDROPS);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Kak Trade Pocket Cucco"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("LW Trade Cojiro"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Kak Trade Odd Mushroom"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("LW Trade Odd Poultice"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("GV Trade Saw"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("DMT Trade Broken Sword"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ZD Trade Prescription"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("LH Lab Trade Eyeball Frog"));
        BUILD_ERROR_CHECK(SetLocationAsVanilla("DMT Trade Eyedrops"));
    }
    mainItemPool.push_back(OOT3D_CLAIM_CHECK);

    // Chest Minigame
    if (settings["shuffle_chest_minigame"] == "single_keys")
    {
        AddElementToPool(mainItemPool, OOT3D_CHEST_GAME_SMALL_KEY, 6);
    }
    else if (settings["shuffle_chest_minigame"] == "key_pack")
    {
        mainItemPool.push_back(OOT3D_CHEST_GAME_SMALL_KEY); // 1 key which will behave as a pack of 6
    }
    else
    {
        SET_VANILLA_LOCATIONS(OOT3D_CHEST_GAME_SMALL_KEY);
    }

    // Tokensanity
    if (settings["tokensanity"] == "off")
    {
        SET_VANILLA_LOCATIONS(OOT3D_GOLD_SKULLTULA_TOKEN);
    }
    else if (settings["tokensanity"] == "dungeons")
    {
        for (auto& [id, location] : locations)
        {
            if (location->GetVanillaItem().GetID() == OOT3D_GOLD_SKULLTULA_TOKEN && location->dungeon != "None")
            {
                location->SetVanillaItemAsCurrentItem();
            }
            else
            {
                mainItemPool.push_back(OOT3D_GOLD_SKULLTULA_TOKEN);
            }
        }
    }
    else if (settings["tokensanity"] == "overworld")
    {
        for (auto& [id, location] : locations)
        {
            if (location->GetVanillaItem().GetID() == OOT3D_GOLD_SKULLTULA_TOKEN && location->dungeon == "None")
            {
                location->SetVanillaItemAsCurrentItem();
            }
            else
            {
                mainItemPool.push_back(OOT3D_GOLD_SKULLTULA_TOKEN);
            }
        }
    }
    else
    {
        AddElementToPool(mainItemPool, OOT3D_GOLD_SKULLTULA_TOKEN, 100);
    }

    // Bombchus in Logic
    if (settings["bombchus_in_logic"] == "on")
    {
        AddElementToPool(mainItemPool, OOT3D_PROGRESSIVE_BOMBCHUS, 5);
    }
    else
    {
        AddElementsToPool(mainItemPool, OOT3D_BOMBCHUS_5, OOT3D_BOMBCHUS_20);
        AddElementToPool(mainItemPool, OOT3D_BOMBCHUS_10, 3);
    }

    // Ice Traps
    mainItemPool.push_back(OOT3D_ICE_TRAP);
    if (dungeons["Gerudo Training Ground"]->IsVanilla()) {
        mainItemPool.push_back(OOT3D_ICE_TRAP);
    }
    if (dungeons["Ganons Castle"]->IsVanilla())
    {
        AddElementToPool(mainItemPool, OOT3D_ICE_TRAP, 4);
    }

    // Gerudo Fortress
    if (settings["gerudo_fortress"] == "open")
    {
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 1 Torch", OOT3D_RECOVERY_HEART));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", OOT3D_RECOVERY_HEART));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", OOT3D_RECOVERY_HEART));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", OOT3D_RECOVERY_HEART));
    }
    else if (settings["gerudo_keys"] != "vanilla")
    {
        if (settings["gerudo_fortress"] == "fast")
        {
            mainItemPool.push_back(OOT3D_THIEVES_HIDEOUT_SMALL_KEY);
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", OOT3D_RECOVERY_HEART));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", OOT3D_RECOVERY_HEART));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", OOT3D_RECOVERY_HEART));
        }
        else
        {
            // Only add key ring if 4 Fortress keys necessary
            if (settings["ring_fortress"] == "on")
            {
                mainItemPool.push_back(OOT3D_THIEVES_HIDEOUT_KEY_RING);
                // Add junk to make up for missing keys
                for (uint8_t i = 0; i < 3; i++) {
                    mainItemPool.push_back(GetJunkItem());
                }
            }
            else
            {
                AddElementToPool(mainItemPool, OOT3D_THIEVES_HIDEOUT_SMALL_KEY, 4);
            }
        }
    }
    else
    {
        if (settings["gerudo_fortress"] == "fast")
        {
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 1 Torch", OOT3D_THIEVES_HIDEOUT_SMALL_KEY));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", OOT3D_RECOVERY_HEART));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", OOT3D_RECOVERY_HEART));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", OOT3D_RECOVERY_HEART));
        }
        else
        {
            SET_VANILLA_LOCATIONS(OOT3D_THIEVES_HIDEOUT_SMALL_KEY);
        }
    }

    // Gerudo Token
    if (settings["shuffle_gerudo_token"] == "on" && settings["gerudo_fortress"] != "open")
    {
        mainItemPool.push_back(OOT3D_GERUDO_TOKEN);
        iceTrapModels.push_back(GI_GERUDO_CARD);
    }
    else if (settings["shuffle_gerudo_token"] == "on")
    {
        pendingJunkPool.push_back(OOT3D_GERUDO_TOKEN);
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Gerudo Token", OOT3D_ICE_TRAP));
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Hideout Gerudo Token"));
    }

    // Keys

    // For key rings, need to add as manu junk items as "missing" keys
    if (settings["key_rings"] == "on")
    {
        int ringJunkAmt = 0;
        for (auto& [dungeonName, dungeon] : dungeons)
        {
            if (dungeon->IsUsingKeyRing())
            {
                ringJunkAmt += dungeon->GetSmallKeyCount();
            }
        }
        for (int i = 0; i < ringJunkAmt; i++)
        {
            mainItemPool.push_back(GetJunkItem());
        }
    }

    if (settings["item_pool_value"] == "plentiful")
    {
        if (settings["shuffle_gerudo_token"] == "on")
        {
            pendingJunkPool.push_back(OOT3D_GERUDO_TOKEN);
        }

        // Plentiful small keys
        if (IsAnyOf(settings["small_keys"], "keysanity", "any_dungeon", "overworld"))
        {
            for (auto& [dungeonName, dungeon] : dungeons)
            {
                if (dungeon->IsUsingKeyRing() && dungeon->GetSmallKeyItemID() != NONE)
                {
                    pendingJunkPool.push_back(dungeon->GetKeyRingItemID());
                }
                else
                {
                    pendingJunkPool.push_back(dungeon->GetSmallKeyItemID());
                }
            }
        }

        if (IsAnyOf(settings["boss_keys"], "keysanity", "any_dungeon", "overworld"))
        {
            for (auto& [dungeonName, dungeon] : dungeons)
            {
                if (dungeon->GetBossKeyItemID() != NONE && dungeonName != "Ganons Castle")
                {
                    pendingJunkPool.push_back(dungeon->GetBossKeyItemID());
                }
            }
        }

        if (IsAnyOf(settings["ganons_boss_key"], "keysanity", "any_dungeon", "overworld"))
        {
            pendingJunkPool.push_back(OOT3D_GANONS_CASTLE_BOSS_KEY);
        }
    }

    // Shopsanity
    if (IsAnyOf(settings["shopsanity"], "off", "zero"))
    {
        MERGE_INTO_MAIN_ITEM_POOL(normalRupees);
    }
    else // Shopsanity 1-4, random
    {
        MERGE_INTO_MAIN_ITEM_POOL(shopsanityRupees);
    }

    // Scrubsanity
    if (settings["scrubsanity"] != "off")
    {
        // Deku Tree
        if (dungeons["Deku Tree"]->IsMQ())
        {
            mainItemPool.push_back(OOT3D_DEKU_SHIELD);
        }

        // Dodongos Cavern
        AddElementsToPool(mainItemPool, OOT3D_DEKU_STICK_1, OOT3D_DEKU_SHIELD);
        if (dungeons["Dodongos Cavern"]->IsMQ())
        {
            mainItemPool.push_back(OOT3D_RECOVERY_HEART);
        }
        else
        {
            mainItemPool.push_back(OOT3D_DEKU_NUTS_5);
        }

        // Jabu Jabus Belly
        if (dungeons["Jabu Jabus Belly"]->IsVanilla())
        {
            mainItemPool.push_back(OOT3D_DEKU_NUTS_5);
        }

        // Ganons Castle
        AddElementsToPool(mainItemPool, OOT3D_BOMBS_5, OOT3D_RECOVERY_HEART, OOT3D_BLUE_RUPEE);
        if (dungeons["Ganons Castle"]->IsMQ())
        {
            mainItemPool.push_back(OOT3D_DEKU_NUTS_5);
        }

        // Overworld Scrubs
        MERGE_INTO_MAIN_ITEM_POOL(dekuScrubItems);

        // I'm not sure what this is for, but it was in ootr so I copied it
        // for (uint8_t i = 0; i < 7; i++)
        // {
        //     if (Random(0, 3))
        //     {
        //         mainItemPool.push_back(OOT3D_ARROWS_30);
        //     }
        //     else
        //     {
        //         mainItemPool.push_back(OOT3D_DEKU_SEEDS_30);
        //     }
        // }
    }
    else // Place vanilla scrub items except for the three which sell unique things
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA(
        {
            // All deku scrubs have the Deku Scrub category, but only the three we
            // want to still be randomized have the Deku Scrub Upgrades category
            return location->categories.count(Oot3dLocationCategory::DekuScrub) > 0 &&
                   location->categories.count(Oot3dLocationCategory::DekuScrubUpgrades) == 0;
        }));
    }

    MERGE_INTO_MAIN_ITEM_POOL(alwaysItems);
    MERGE_INTO_MAIN_ITEM_POOL(dungeonRewards);

    // Decide which dungeon pools to use based on Vanilla/MQ
    MERGE_DUNGEON_POOL_INTO_MAIN("Deku Tree", DT);
    MERGE_DUNGEON_POOL_INTO_MAIN("Dodongos Cavern", DC);
    MERGE_DUNGEON_POOL_INTO_MAIN("Jabu Jabus Belly", JB);
    MERGE_DUNGEON_POOL_INTO_MAIN("Forest Temple", FoT);
    MERGE_DUNGEON_POOL_INTO_MAIN("Fire Temple", FiT);
    MERGE_DUNGEON_POOL_INTO_MAIN("Spirit Temple", SpT);
    MERGE_DUNGEON_POOL_INTO_MAIN("Shadow Temple", ShT);
    MERGE_DUNGEON_POOL_INTO_MAIN("Bottom of the Well", BW);
    MERGE_DUNGEON_POOL_INTO_MAIN("Gerudo Training Ground", GTG);
    MERGE_DUNGEON_POOL_INTO_MAIN("Ganons Castle", GC);

    uint8_t rutoBottles = 1;
    if (settings["zoras_fountain"] == "open")
    {
        rutoBottles = 0;
    }

    // Add 4 total bottles and add a random bottle to the ice trap models
    auto randomBottle = itemTable[RandomElement(normalBottles)].getItemId;
    iceTrapModels.push_back(randomBottle);
    uint8_t totalBottleCount = 4;
    for (uint8_t i = 0; i < totalBottleCount; i++)
    {
        if (i >= rutoBottles)
        {
            if ((i == totalBottleCount - 1) && settings["shuffle_merchants"] != "off")
            {
                mainItemPool.push_back(OOT3D_BOTTLE_WITH_BLUE_POTION);
            }
            else
            {
                mainItemPool.push_back(PopRandomElement(normalBottles));
            }
        }
        else
        {
            mainItemPool.push_back(OOT3D_RUTOS_LETTER);
        }
    }

    MergePools(mainItemPool, songList);
    // Add extra songs only if song shuffle is anywhere
    if (settings["shuffle_songs"] == "anywhere" && settings["item_pool_value"] == "plentiful")
    {
        MergePools(pendingJunkPool, songList);
    }

    /*For item pool generation, dungeon items are either placed in their vanilla
    | location, or added to the pool now and filtered out later depending on when
    | they need to get placed or removed in fill.cpp. These items are kept in the
    | pool until removal because the filling algorithm needs to know all of the
    | advancement items that haven't been placed yet for placing higher priority
    | items like dungeon rewards and shop items.*/

    // Maps and Compasses
    if (settings["maps_and_compasses"] == "vanilla")
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA(
        {
            return location->categories.count(Oot3dLocationCategory::VanillaMap) ||
                   location->categories.count(Oot3dLocationCategory::VanillaCompass);
        }));
    }
    else
    {
        for (auto& [dungeonName, dungeon] : dungeons)
        {
            auto map     = dungeon->GetMapItemID();
            auto compass = dungeon->GetCompassItemID();
            if (map != NONE)
            {
                mainItemPool.push_back(map);
            }
            if (compass != NONE)
            {
                mainItemPool.push_back(compass);
            }
        }
    }

    // Small Keys
    if (settings["small_keys"] == "vanilla")
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA({return location->categories.count(Oot3dLocationCategory::VanillaSmallKey);}));
    }
    else
    {
        for (auto& [dungeonName, dungeon] : dungeons)
        {
            if (dungeon->IsUsingKeyRing() && settings["small_keys"] != "start_with")
            {
                mainItemPool.push_back(dungeon->GetKeyRingItemID());
            }
            else
            {
                AddElementToPool(mainItemPool, dungeon->GetSmallKeyItemID(), dungeon->GetSmallKeyCount());
            }
        }
    }

    // Boss Keys
    if (settings["boss_keys"] == "vanilla")
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA({return location->categories.count(Oot3dLocationCategory::VanillaBossKey);}));
    }
    else
    {
        for (auto& [name, dungeon] : dungeons)
        {
            auto bossKey = dungeon->GetBossKeyItemID();
            if (bossKey != NONE && name != "Ganons Castle")
            {
                mainItemPool.push_back(bossKey);
            }
        }
    }

    // If ganons_boss_key is any of the light arrow cutscene options
    if (Utility::Str::StartsWith(settings["ganons_boss_key"], "lacs"))
    {
        BUILD_ERROR_CHECK(PlaceItemAtLocation("ToT Light Arrows Cutscene", OOT3D_GANONS_CASTLE_BOSS_KEY));
    }
    else if (settings["ganons_boss_key"] == "vanilla")
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Ganons Tower Boss Key Chest"));
    }
    else
    {
        mainItemPool.push_back(OOT3D_GANONS_CASTLE_BOSS_KEY);
    }

    // Item Pool
    if (settings["item_pool_value"] == "plentiful")
    {
        MERGE_INTO_MAIN_ITEM_POOL(easyItems);
    }
    else
    {
        MERGE_INTO_MAIN_ITEM_POOL(normalItems);
    }

    // There shouldn't be any extra swords in the pool if their locations
    // are already known
    if (settings["shuffle_kokiri_sword"] == "off")
    {
        ReduceItemMaximum(mainItemPool, OOT3D_KOKIRI_SWORD, 0);
    }
    if (settings["shuffle_master_sword"] == "off")
    {
        ReduceItemMaximum(mainItemPool, OOT3D_MASTER_SWORD, 0);
    }

    if (settings["progressive_goron_sword"] == "on")
    {
        ReduceItemMaximum(mainItemPool, OOT3D_BIGGORONS_SWORD, 0);
        AddElementToPool(mainItemPool, OOT3D_PROGRESSIVE_GORON_SWORD, 2);
        iceTrapModels.push_back(0xD4);
    }
    else
    {
        iceTrapModels.push_back(GI_SWORD_BGS);
    }

    // Replace ice traps with junk if necessary
    if (settings["ice_trap_value"] == "off")
    {
        ReduceItemMaximum(mainItemPool, OOT3D_ICE_TRAP, 0);
    }
    // Replace all junk items with ice traps for onslaught mode
    else if (settings["ice_trap_value"] == "onslaught")
    {
        for (uint8_t i = 0; i < junkPoolItems.size() - 3; i++) // -3 Omits Huge Rupees and Deku Nuts 10
        {
            ReduceItemMaximum(mainItemPool, junkPoolItems[i], 0);
        }
    }

    if (settings["item_pool_value"] == "scarce")
    {
        for (auto& [itemId, max] : scarceItemPool)
        {
            ReduceItemMaximum(mainItemPool, itemId, max);
        }
    }
    else if (settings["item_pool_value"] == "minimal")
    {
        for (auto& [itemId, max] : minimalItemPool)
        {
            ReduceItemMaximum(mainItemPool, itemId, max);
        }
    }
    else if (settings["remove_double_defense"] == "on")
    {
        ReduceItemMaximum(mainItemPool, OOT3D_DOUBLE_DEFENSE, 0);
    }

    // Replace random junk in the item pool with any pending junk
    std::set<ItemID> junkPoolSet = std::set(junkPoolItems.begin(), junkPoolItems.end());
    while (pendingJunkPool.size() > 0)
    {
        auto junk = std::find_if(mainItemPool.begin(), mainItemPool.end(), [&](auto& item){return junkPoolSet.count(item) > 0 && item != OOT3D_HUGE_RUPEE && item != OOT3D_DEKU_NUTS_10;});
        if (junk != mainItemPool.end())
        {
            *junk = PopRandomElement(pendingJunkPool);
        }
        else
        {
            break;
        }
    }

    // Finally, add the items to the actual pool
    for (const auto& itemId : mainItemPool)
    {
        itemPool.push_back(itemTable[itemId]);
    }

    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::GenerateOot3dStartingInventory()
{
    ItemIDPool inventory;

    if (settings["maps_and_compasses"] == "start_with")
    {
        for (auto& [name, dungeon] : dungeons)
        {
            auto map = dungeon->GetMapItemID();
            auto compass = dungeon->GetCompassItemID();
            if (map != NONE)
            {
                inventory.push_back(map);
            }
            if (compass != NONE)
            {
                inventory.push_back(compass);
            }
        }
    }

    if (settings["small_keys"] == "start_with")
    {
        for (auto& [name, dungeon] : dungeons)
        {
            auto smallKey = dungeon->GetSmallKeyItemID();
            if (smallKey != NONE)
            {
                AddElementToPool(inventory, smallKey, dungeon->GetSmallKeyCount());
            }
        }
    }
    else if (settings["small_keys"] == "vanilla")
    {
        // Logic cannot handle vanilla key layout in some dungeons
        // this is because vanilla expects the dungeon major item to be
        // locked behind the keys, which is not always true in rando.
        // We can resolve this by starting with some extra keys
        // - OoT Randomizer
        if (dungeons["Spirit Temple"]->IsMQ())
        {
            AddElementToPool(inventory, OOT3D_SPIRIT_TEMPLE_SMALL_KEY, 3);
        }
        if (dungeons["Fire Temple"]->IsVanilla() && IsNoneOf(settings["small_keys"], "any_dungeon", "overworld", "keysanity"))
        {
            inventory.push_back(OOT3D_FIRE_TEMPLE_SMALL_KEY);
        }
    }

    if (settings["boss_keys"] == "start_with")
    {
        for (auto& [name, dungeon] : dungeons)
        {
            auto bossKey = dungeon->GetBossKeyItemID();
            if (bossKey != NONE && name != "Ganons Castle")
            {
                inventory.push_back(bossKey);
            }
        }
    }

    if (settings["ganons_boss_key"] == "start_with")
    {
        inventory.push_back(OOT3D_GANONS_CASTLE_BOSS_KEY);
    }

    if (settings["gerudo_fortress"] == "open" && settings["shuffle_gerudo_token"] == "Off")
    {
        inventory.push_back(OOT3D_GERUDO_TOKEN);
    }

    // Finally, add the items to the actual pool
    for (const auto& itemId : inventory)
    {
        startingInventory.push_back(itemTable[itemId]);
    }

    return WorldBuildingError::NONE;
}
