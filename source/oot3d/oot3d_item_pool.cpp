#include "oot3d_world.hpp"
#include "../general_item_pool.hpp"
#include "../utility/pool_functions.hpp"
#include "../utility/random.hpp"
#include "../utility/string_util.hpp"

#define MERGE_INTO_MAIN_ITEM_POOL(pool) for (auto& [itemName, amount] : pool) { AddElementToPool(mainItemPool, itemName, amount); }
#define MERGE_DUNGEON_POOL_INTO_MAIN(dungeonName, abbreviation) if (dungeons[dungeonName]->IsMQ()) {MERGE_INTO_MAIN_ITEM_POOL(abbreviation##_MQ);} else {MERGE_INTO_MAIN_ITEM_POOL(abbreviation##_Vanilla);}

static std::vector<std::string> pendingJunkPool = {};
static const ItemMap dungeonRewards = {
    {"Kokiri Emerald", 1},
    {"Goron Ruby", 1},
    {"Zora Sapphire", 1},
    {"Forest Medallion", 1},
    {"Fire Medallion", 1},
    {"Water Medallion", 1},
    {"Spirit Medallion", 1},
    {"Shadow Medallion", 1},
    {"Light Medallion", 1},
};
static const std::vector<std::string> junkPoolItems = {
    "Bombs 5",
    "Bombs 10",
    "Bombs 20",
    "Deku Nuts 5",
    "Deku Stick 1",
    "Deku Seeds 30",
    "Recovery Heart",
    "Arrows 5",
    "Arrows 10",
    "Arrows 30",
    "Blue Rupee",
    "Red Rupee",
    "Purple Rupee",
    "Huge Rupee",
    "Deku Nuts 10",
    "Ice Trap",
};
static const ItemMap alwaysItems = {
    {"Biggorons Sword", 1},
    {"Boomerang", 1},
    {"Lens of Truth", 1},
    {"Megaton Hammer", 1},
    {"Iron Boots", 1},
    {"Hover Boots", 1},
    {"Goron Tunic", 1},
    {"Zora Tunic", 1},
    {"Mirror Shield", 1},
    {"Shard of Agony", 1},
    {"Fire Arrows", 1},
    {"Ice Arrows", 1},
    {"Light Arrows", 1},
    {"Dins Fire", 1},
    {"Farores Wind", 1},
    {"Nayrus Love", 1},
    {"Green Rupee", 1},
    {"Progressive Hookshot", 2},
    {"Deku Shield", 1},
    {"Hylian Shield", 1},
    {"Progressive Strength Upgrade", 3},
    {"Progressive Scale", 2},
    {"Progressive Bow", 3},
    {"Progressive Slingshot", 3},
    {"Progressive Bomb Bag", 3},
    // {"Progressive Bombchus", 1},
    {"Progressive Wallet", 2},
    {"Progressive Magic Meter", 2},
    {"Double Defense", 1},
    {"Progressive Stick Capacity", 2},
    {"Progressive Nut Capacity", 2},

    {"Recovery Heart", 6},
    {"Bombs 5", 2},
    {"Bombs 10", 1},
    {"Bombs 20", 1},
    {"Arrows 5", 1},
    {"Arrows 10", 5},
    {"Treasure Game Heart", 1},

    // {"Zeldas Lullaby", 1},
    // {"Sarias Song", 1},
    // {"Suns Song", 1},
    // {"Song of Storms", 1},
    // {"Eponas Song", 1},
    // {"Song of Time", 1},
    // {"Minuet of Forest", 1},
    // {"Bolero of Fire", 1},
    // {"Serenade of Water", 1},
    // {"Requiem of Spirit", 1},
    // {"Nocturne of Shadow", 1},
    // {"Prelude of Light", 1},
    //
    // {"Rutos Letter", 1},
    // {"Empty Bottle", 1},
    //
    // {"Progressive Ocarina", 2},
    // {"Gerudo Token", 1},
    // {"Weird Egg", 1},
    // {"Magic Bean Pack", 1},
    //
    // {"Pocket Egg", 1},
    // {"Pocket Cucco", 1},
    // {"Cojiro", 1},
    // {"Odd Mushroom", 1},
    // {"Odd Poultice", 1},
    // {"Poachers Saw", 1},
    // {"Broken Gorons Sword", 1},
    // {"Prescription", 1},
    // {"Eyeball Frog", 1},
    // {"Worlds Finest Eyedrops", 1},
    // {"Claim Check", 1},
    //
    // {"Light Medallion", 1},
    // {"Forest Medallion", 1},
    // {"Fire Medallion", 1},
    // {"Water Medallion", 1},
    // {"Spirit Medallion", 1},
    // {"Shadow Medallion", 1},
    // {"Kokiri Emerald", 1},
    // {"Goron Ruby", 1},
    // {"Zora Sapphire", 1},
    //
    // {"Forest Temple Boss Key", 1},
    // {"Fire Temple Boss Key", 1},
    // {"Water Temple Boss Key", 1},
    // {"Spirit Temple Boss Key", 1},
    // {"Shadow Temple Boss Key", 1},
    // {"Ganons Castle Boss Key", 1},
    //
    // {"Thieves Hideout Small Key", 4},
    // {"Forest Temple Small Key", 5},
    // {"Fire Temple Small Key", 8},
    // {"Water Temple Small Key", 6},
    // {"Shadow Temple Small Key", 5},
    // {"Spirit Temple Small Key", 5},
    // {"Bottom of the Well Small Key", 3},
    // {"Gerudo Training Ground Small Key", 9},
    // {"Ganons Castle Small Key", 2},
    //
    // {"Heart Container", 8},

    {"Buy Deku Shield", 1},
    {"Buy Hylian Shield", 1},
    {"Rutos Letter", 1},
};
static const ItemMap easyItems = {
    {"Biggorons Sword", 1},
    {"Kokiri Sword", 1},
    {"Master Sword", 1},
    {"Boomerang", 1},
    {"Lens of Truth", 1},
    {"Megaton Hammer", 1},
    {"Iron Boots", 1},
    {"Hover Boots", 1},
    {"Mirror Shield", 1},
    {"Fire Arrows", 1},
    {"Light Arrows", 1},
    {"Dins Fire", 1},
    {"Progressive Hookshot", 1},
    {"Progressive Strength Upgrade", 1},
    {"Progressive Scale", 1},
    {"Progressive Wallet", 1},
    {"Progressive Magic Meter", 1},
    {"Progressive Stick Capacity", 1},
    {"Progressive Nut Capacity", 1},
    {"Progressive Bow", 1},
    {"Progressive Slingshot", 1},
    {"Progressive Bomb Bag", 1},
    {"Double Defense", 1},
    {"Heart Container", 16},
    {"Piece of Heart", 3},
};
static const ItemMap normalItems = {
    {"Piece of Heart", 35},
    {"Heart Container", 8},
};
static const ItemMap DT_Vanilla = {
    {"Recovery Heart", 2},
};
static const ItemMap DT_MQ = {
    {"Deku Shield", 2},
    {"Purple Rupee", 1},
};
static const ItemMap DC_Vanilla = {
    {"Red Rupee", 1},
};
static const ItemMap DC_MQ = {
    {"Hylian Shield", 1},
    {"Blue Rupee", 1},
};
static const ItemMap JB_Vanilla = {};
static const ItemMap JB_MQ = {
    {"Deku Nuts 5", 4},
    {"Recovery Heart", 1},
    {"Deku Shield", 1},
    {"Deku Stick 1", 1},
};
static const ItemMap FoT_Vanilla = {
    {"Recovery Heart", 1},
    {"Arrows 10", 1},
    {"Arrows 30", 1},
};
static const ItemMap FoT_MQ = {
    {"Arrows 5", 1},
};
static const ItemMap FiT_Vanilla = {
    {"Huge Rupee", 1},
};
static const ItemMap FiT_MQ = {
    {"Bombs 20", 1},
    {"Hylian Shield", 1},
};
static const ItemMap SpT_Vanilla = {
    {"Deku Shield", 2},
    {"Recovery Heart", 1},
    {"Bombs 20", 1},
};
static const ItemMap SpT_MQ = {
    {"Purple Rupee", 1},
    {"Purple Rupee", 1},
    {"Arrows 30", 1},
};
static const ItemMap ShT_Vanilla = {
    {"Arrows 30", 1},
};
static const ItemMap ShT_MQ = {
    {"Arrows 5", 1},
    {"Arrows 5", 1},
    {"Red Rupee", 1},
};
static const ItemMap BW_Vanilla = {
    {"Recovery Heart", 1},
    {"Bombs 10", 1},
    {"Huge Rupee", 1},
    {"Deku Nuts 5", 1},
    {"Deku Nuts 10", 1},
    {"Deku Shield", 1},
    {"Hylian Shield", 1},
};
static const ItemMap BW_MQ = {};
static const ItemMap GTG_Vanilla = {
    {"Arrows 30", 3},
    {"Huge Rupee", 1},
};
static const ItemMap GTG_MQ = {
    {"Treasure Game Green Rupee", 2},
    {"Arrows 10", 1},
    {"Green Rupee", 1},
    {"Purple Rupee", 1},
};
static const ItemMap GC_Vanilla = {
    {"Blue Rupee", 3},
    {"Arrows 30", 1},
};
static const ItemMap GC_MQ = {
    {"Arrows 10", 2},
    {"Bombs 5", 1},
    {"Red Rupee", 1},
    {"Recovery Heart", 1},
};
static std::vector<std::string> normalBottles = {
    "Empty Bottle",
    "Bottle with Milk",
    "Bottle with Red Potion",
    "Bottle with Green Potion",
    "Bottle with Blue Potion",
    "Bottle with Fairy",
    "Bottle with Fish",
    "Bottle with Bugs",
    "Bottle with Poe",
    "Bottle with Big Poe",
    "Bottle with Blue Fire",
};
static const ItemMap normalRupees = {
    {"Blue Rupee", 13},
    {"Red Rupee", 5},
    {"Purple Rupee", 7},
    {"Huge Rupee", 3},
};
static const ItemMap shopsanityRupees = {
    {"Blue Rupee", 2},
    {"Red Rupee", 10},
    {"Purple Rupee", 10},
    {"Huge Rupee", 5},
    {"Progressive Wallet", 1},
};
static const ItemMap dekuScrubItems = {
    {"Deku Nuts 5", 5},
    {"Deku Stick 1", 1},
    {"Bombs 5", 5},
    {"Recovery Heart", 4},
    {"Blue Rupee", 4},
};
static std::vector<std::string> songList = {
    "Zeldas Lullaby",
    "Eponas Song",
    "Suns Song",
    "Sarias Song",
    "Song of Time",
    "Song of Storms",
    "Minuet of Forest",
    "Prelude of Light",
    "Bolero of Fire",
    "Serenade of Water",
    "Nocturne of Shadow",
    "Requiem of Spirit",
};
static const ItemMap tradeItems = {
    {"Pocket Egg", 1},
    // {"Pocket Cucco", 1},
    {"Cojiro", 1},
    {"Odd Mushroom", 1},
    {"Poachers Saw", 1},
    {"Broken Gorons Sword", 1},
    {"Prescription", 1},
    {"Eyeball Frog", 1},
    {"Worlds Finest Eyedrops", 1},
    {"Claim Check", 1},
};
static const ItemMap scarceItemPool = {
    {"Progressive Bombchus", 3},
    {"Bombchu 5", 1},
    {"Bombchu 10", 2},
    {"Bombchu 20", 0},
    {"Progressive Magic Meter", 1},
    {"Double Defense", 0},
    {"Progressive Stick Capacity", 1},
    {"Progressive Nut Capacity", 1},
    {"Progressive Bow", 2},
    {"Progressive Slingshot", 2},
    {"Progressive Bomb Bag", 2},
    {"Heart Container", 0}
};
static const ItemMap minimalItemPool = {
    {"Progressive Bombchus", 1},
    {"Bombchu 5", 1},
    {"Bombchu 10", 0},
    {"Bombchu 20", 0},
    {"Nayrus Love", 0},
    {"Progressive Magic Meter", 1},
    {"Double Defense", 0},
    {"Progressive Stick Capacity", 0},
    {"Progressive Nut Capacity", 0},
    {"Progressive Bow", 1},
    {"Progressive Slingshot", 1},
    {"Progressive Bomb Bag", 1},
    {"Piece of Heart", 0},
};

std::string Oot3dWorld::GetJunkItem()
{
    if (IsAnyOf(settings["ice_trap_value"], "mayhem", "onslaught"))
    {
        return "Ice Trap";
    }
    else if (settings["ice_trap_value"] == "extra")
    {
        return RandomElement(junkPoolItems);
    }
    // Ice Trap is the last item in JunkPoolItems, so subtract 1 to never hit that index
    uint8_t idx = Random(0, junkPoolItems.size() - 1);
    return junkPoolItems[idx];
}

std::string Oot3dWorld::GetPendingJunkItem()
{
    if (pendingJunkPool.empty())
    {
        return GetJunkItem();
    }
    return PopRandomElement(pendingJunkPool);
}

// Will reduce the maximum number of items in the pool to the amount specified
// Removed items are replaced with junk
void Oot3dWorld::ReduceItemMaximum(std::vector<std::string> mainItemPool, const std::string& itemToReplace, int max)
{
    for (int i = ElementCountInPool(itemToReplace, mainItemPool); i > max; i++)
    {
        RemoveElementFromPool(mainItemPool, itemToReplace);
        mainItemPool.push_back(GetJunkItem());
    }
}

WorldBuildingError Oot3dWorld::GenerateOot3dItemPool()
{
    using namespace std::string_literals;
    WorldBuildingError err;
    std::vector<std::string> mainItemPool = {};

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
        mainItemPool.push_back("Kokiri Sword");
        iceTrapModels.push_back(GI_SWORD_KOKIRI);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("KF Kokiri Sword Chest"));
    }

    // Shuffling Master Sword
    if (settings["shuffle_master_sword"] == "on")
    {
        mainItemPool.push_back("Master Sword");
        iceTrapModels.push_back(GI_SWORD_MASTER);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("ToT Master Sword"));
    }

    // Shuffling Weird Egg
    if (settings["shuffle_werid_egg"] == "on")
    {
        mainItemPool.push_back("Weird Egg");
        iceTrapModels.push_back(GI_WEIRD_EGG);
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("HC Malon Egg"));
    }

    // Shuffling Ocarinas
    if (settings["shuffle_ocarinas"] == "on")
    {
        AddElementToPool(mainItemPool, "Progressive Ocarina"s, 2);
        if (settings["item_pool_value"] == "plentiful")
        {
            pendingJunkPool.push_back("Progressive Ocarina");
        }
        iceTrapModels.push_back(0x8B); // progressive Ocarina
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationsWithVanillaItem("Progressive Ocarina"));
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
        BUILD_ERROR_CHECK(SetLocationsWithVanillaItem("Milk"));
    }

    // Shuffling Magic Beans
    if (settings["shuffle_magic_beans"] == "on")
    {
        mainItemPool.push_back("Magic Bean Pack");
        if (settings["item_pool_value"] == "plentiful")
        {
            pendingJunkPool.push_back("Magic Bean Pack");
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
            mainItemPool.push_back("Giants Knife");
        }
        if (settings["bombchus_in_logic"] == "on")
        {
            mainItemPool.push_back("Progressive Bombchus");
        }
        else
        {
            mainItemPool.push_back("Bombchus 10");
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
        AddElementToPool(mainItemPool, "Purple Rupee"s, 5);
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
        AddElementsToPool(mainItemPool,  "Pocket Egg"s, "Cojiro"s, "Odd Mushroom"s,
                                         "Odd Poultice"s, "Poachers Saw"s,
                                         "Broken Gorons Sword"s, "Prescription"s,
                                         "Eyeball Frog"s, "Worlds Finest Eyedrops"s);
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
    mainItemPool.push_back("Claim Check");

    // Chest Minigame
    if (settings["shuffle_chest_minigame"] == "single_keys")
    {
        AddElementToPool(mainItemPool, "Chest Game Small Key"s, 6);
    }
    else if (settings["shuffle_chest_minigame"] == "key_pack")
    {
        mainItemPool.push_back("Chest Game Small Key"); // 1 key which will behave as a pack of 6
    }
    else
    {
        BUILD_ERROR_CHECK(SetLocationsWithVanillaItem("Chest Game Small Key"));
    }

    // Tokensanity
    if (settings["tokensanity"] == "off")
    {
        BUILD_ERROR_CHECK(SetLocationsWithVanillaItem("Gold Skulltula Token"));
    }
    else if (settings["tokensanity"] == "dungeons")
    {
        for (auto& [id, location] : locations)
        {
            if (location->GetVanillaItemID() == ItemID::Oot3dGoldSkulltulaToken && location->dungeon != "None")
            {
                location->SetVanillaItemAsCurrentItem();
            }
            else
            {
                mainItemPool.push_back("Gold Skulltula Token");
            }
        }
    }
    else if (settings["tokensanity"] == "overworld")
    {
        for (auto& [id, location] : locations)
        {
            if (location->GetVanillaItemID() == ItemID::Oot3dGoldSkulltulaToken && location->dungeon == "None")
            {
                location->SetVanillaItemAsCurrentItem();
            }
            else
            {
                mainItemPool.push_back("Gold Skulltula Token");
            }
        }
    }
    else
    {
        AddElementToPool(mainItemPool, "Gold Skulltula Token"s, 100);
    }

    // Bombchus in Logic
    if (settings["bombchus_in_logic"] == "on")
    {
        AddElementToPool(mainItemPool, "Progressive Bombchus"s, 5);
    }
    else
    {
        AddElementsToPool(mainItemPool, "Bombchu 5"s, "Bombchu 20"s);
        AddElementToPool(mainItemPool, "Bombchu 10"s, 3);
    }

    // Ice Traps
    mainItemPool.push_back("Ice Trap");
    if (dungeons["Gerudo Training Ground"]->IsVanilla()) {
        mainItemPool.push_back("Ice Trap");
    }
    if (dungeons["Ganons Castle"]->IsVanilla())
    {
        AddElementToPool(mainItemPool, "Ice Trap"s, 4);
    }

    // Gerudo Fortress
    if (settings["gerudo_fortress"] == "open")
    {
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 1 Torch", "Recovery Heart"));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", "Recovery Heart"));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", "Recovery Heart"));
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", "Recovery Heart"));
    }
    else if (settings["gerudo_keys"] != "vanilla")
    {
        if (settings["gerudo_fortress"] == "fast")
        {
            mainItemPool.push_back("Thieves Hideout Small Key");
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", "Recovery Heart"));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", "Recovery Heart"));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", "Recovery Heart"));
        }
        else
        {
            // Only add key ring if 4 Fortress keys necessary
            if (settings["ring_fortress"] == "on")
            {
                mainItemPool.push_back("Gerudo Fortress Key Ring");
                // Add junk to make up for missing keys
                for (uint8_t i = 0; i < 3; i++) {
                    mainItemPool.push_back(GetJunkItem());
                }
            }
            else
            {
                AddElementToPool(mainItemPool, "Thieves Hideout Small Key"s, 4);
            }
        }
    }
    else
    {
        if (settings["gerudo_fortress"] == "fast")
        {
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 1 Torch", "Thieves Hideout Small Key"));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 2 Torches", "Recovery Heart"));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 3 Torches", "Recovery Heart"));
            BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Jail Guard 4 Torches", "Recovery Heart"));
        }
        else
        {
            BUILD_ERROR_CHECK(SetLocationsWithVanillaItem("Thieves Hideout Small Key"));
        }
    }

    // Gerudo Token
    if (settings["shuffle_gerudo_token"] == "on" && settings["gerudo_fortress"] != "open")
    {
        mainItemPool.push_back("Gerudo Token");
        iceTrapModels.push_back(GI_GERUDO_CARD);
    }
    else if (settings["shuffle_gerudo_token"] == "on")
    {
        pendingJunkPool.push_back("Gerudo Token");
        BUILD_ERROR_CHECK(PlaceItemAtLocation("Hideout Gerudo Token", "Ice Trap"));
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
            pendingJunkPool.push_back("Gerudo Token");
        }

        // Plentiful small keys
        if (IsAnyOf(settings["small_keys"], "keysanity", "any_dungeon", "overworld"))
        {
            for (auto& [dungeonName, dungeon] : dungeons)
            {
                if (dungeon->IsUsingKeyRing() && dungeon->GetSmallKeyItemID() != ItemID::NONE)
                {
                    pendingJunkPool.push_back(ItemIDToName(dungeon->GetKeyRingItemID()));
                }
                else
                {
                    pendingJunkPool.push_back(ItemIDToName(dungeon->GetSmallKeyItemID()));
                }
            }
        }

        if (IsAnyOf(settings["boss_keys"], "keysanity", "any_dungeon", "overworld"))
        {
            for (auto& [dungeonName, dungeon] : dungeons)
            {
                if (dungeon->GetBossKeyItemID() != ItemID::NONE && dungeonName != "Ganons Castle")
                {
                    pendingJunkPool.push_back(ItemIDToName(dungeon->GetBossKeyItemID()));
                }
            }
        }

        if (IsAnyOf(settings["ganons_boss_key"], "keysanity", "any_dungeon", "overworld"))
        {
            pendingJunkPool.push_back("Ganons Castle Boss Key");
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
            mainItemPool.push_back("Deku Shield");
        }

        // Dodongos Cavern
        AddElementsToPool(mainItemPool, "Deku Stick 1", "Deku Shield");
        if (dungeons["Dodongos Cavern"]->IsMQ())
        {
            mainItemPool.push_back("Recovery Heart");
        }
        else
        {
            mainItemPool.push_back("Deku Nuts 5");
        }

        // Jabu Jabus Belly
        if (dungeons["Jabu Jabus Belly"]->IsVanilla())
        {
            mainItemPool.push_back("Deku Nuts 5");
        }

        // Ganons Castle
        AddElementsToPool(mainItemPool, "Bombs 5", "Recovery Heart", "Blue Rupee");
        if (dungeons["Ganons Castle"]->IsMQ())
        {
            mainItemPool.push_back("Deku Nuts 5");
        }

        // Overworld Scrubs
        MERGE_INTO_MAIN_ITEM_POOL(dekuScrubItems);

        // Not sure what this is for, but it was in ootr so it's here too
        for (uint8_t i = 0; i < 7; i++)
        {
            if (Random(0, 3))
            {
                mainItemPool.push_back("Arrows 30");
            } else
            {
                mainItemPool.push_back("Deku Seeds 30");
            }
        }
    }
    else // Place vanilla scrub items except for the three which sell unique things
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA(
        {
            // All deku scrubs have the Deku Scrub category, but only the three we
            // want to exclude have the Deku Scrub Upgrades category
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
    auto randomBottle = itemTable[NameToItemID(RandomElement(normalBottles))].getItemId;
    iceTrapModels.push_back(randomBottle);
    uint8_t totalBottleCount = 4;
    for (uint8_t i = 0; i < totalBottleCount; i++)
    {
        if (i >= rutoBottles)
        {
            if ((i == totalBottleCount - 1) && settings["shuffle_merchants"] != "off")
            {
                mainItemPool.push_back("Bottle with Blue Potion");
            }
            else
            {
                mainItemPool.push_back(PopRandomElement(normalBottles));
            }
        }
        else
        {
            mainItemPool.push_back("Rutos Letter");
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
            if (map != ItemID::NONE)
            {
                mainItemPool.push_back(ItemIDToName(map));
            }
            if (compass != ItemID::NONE)
            {
                mainItemPool.push_back(ItemIDToName(compass));
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
                mainItemPool.push_back(ItemIDToName(dungeon->GetKeyRingItemID()));
            }
            else
            {
                AddElementToPool(mainItemPool, ItemIDToName(dungeon->GetSmallKeyItemID()), dungeon->GetSmallKeyCount());
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
        AddElementsToPool(mainItemPool, "Forest Temple Boss Key", "Fire Temple Boss Key", "Water Temple Boss Key", "Spirit Temple Boss Key", "Shadow Temple Boss Key");
    }

    // If ganons_boss_key is any of the light arrow cutscene options
    if (Utility::Str::StartsWith(settings["ganons_boss_key"], "lacs"))
    {
        BUILD_ERROR_CHECK(PlaceItemAtLocation("ToT Light Arrows Cutscene", "Ganons Castle Boss Key"));
    }
    else if (settings["ganons_boss_key"] == "vanilla")
    {
        BUILD_ERROR_CHECK(SetLocationAsVanilla("Ganons Tower Boss Key Chest"));
    }
    else
    {
        mainItemPool.push_back("Ganons Castle Boss Key");
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
        ReduceItemMaximum(mainItemPool, "Kokiri Sword", 0);
    }
    if (settings["shuffle_master_sword"] == "off")
    {
        ReduceItemMaximum(mainItemPool, "Master Sword", 0);
    }

    if (settings["progressive_goron_sword"] == "on")
    {
        ReduceItemMaximum(mainItemPool, "Biggoron Sword", 0);
        AddElementToPool(mainItemPool, "Progressive Goron Sword"s, 2);
        iceTrapModels.push_back(0xD4);
    }
    else
    {
        iceTrapModels.push_back(GI_SWORD_BGS);
    }

    // Replace ice traps with junk if necessary
    if (settings["ice_trap_value"] == "off")
    {
        ReduceItemMaximum(mainItemPool, "Ice Trap", 0);
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
        for (auto& [itemName, max] : scarceItemPool)
        {
            ReduceItemMaximum(mainItemPool, itemName, max);
        }
    }
    else if (settings["item_pool_value"] == "minimal")
    {
        for (auto& [itemName, max] : minimalItemPool)
        {
            ReduceItemMaximum(mainItemPool, itemName, max);
        }
    }
    else if (settings["remove_double_defense"] == "on")
    {
        ReduceItemMaximum(mainItemPool, "Double Defense", 0);
    }

    // Replace random junk in the item pool with any pending junk
    std::set<std::string> junkPoolSet = std::set(junkPoolItems.begin(), junkPoolItems.end());
    while (pendingJunkPool.size() > 0)
    {
        auto junk = std::find_if(mainItemPool.begin(), mainItemPool.end(), [&](auto& item){return junkPoolSet.count(item) > 0 && item != "Huge Rupee" && item != "Deku Nuts 10";});
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
    LOG_TO_DEBUG("Item Pool for Oot3d World " + std::to_string(worldId + 1) + ":");
    for (const auto& itemName : mainItemPool)
    {
        ItemID itemId;
        // Don't preppend "Oot3d" if the string already starts with it
        if (Utility::Str::StartsWith(itemName, "Oot3d"))
        {
            itemId = NameToItemID(itemName);
        }
        else
        {
            itemId = NameToItemID("Oot3d " + itemName);
        }

        if (itemId == ItemID::INVALID)
        {
            LOG_TO_ERROR("ERROR: Unknown item name \"" + itemName + "\"");
            return WorldBuildingError::BAD_ITEM_NAME;
        }
        itemPool.push_back(itemTable[itemId]);
        LOG_TO_DEBUG("- " + itemName);
    }

    return WorldBuildingError::NONE;
}
