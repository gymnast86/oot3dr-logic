#include "oot3d_location.hpp"

#include <unordered_map>

Oot3dLocation::Oot3dLocation() {}

Oot3dLocation::Oot3dLocation(const LocationID& id_, std::string name_, LocationType type_, uint8_t scene_, uint8_t flag_, const ItemID& vanillaItem_, SpoilerCollectionCheck collectionCheck_, SpoilerCollectionCheckGroup collectionCheckGroup_, World* world_)
{
    id = id_;
    name = std::move(name_);
    type = type_;
    scene = scene_;
    flag = flag_;
    vanillaItem = vanillaItem_;
    collectionCheck = collectionCheck_;
    collectionCheckGroup = collectionCheckGroup_;
    world = world_;
}

Oot3dLocation::~Oot3dLocation() = default;

std::string Oot3dLocation::TypeString() const
{
    return "Oot3d Location";
}

LocationType NameToOot3dLocationType(const std::string& name)
{
    std::unordered_map<std::string, LocationType> nameLocationTypeMap = {
        {"Base", LocationType::Base},
        {"Chest", LocationType::Chest},
        {"Collectable", LocationType::Collectable},
        {"GS Token", LocationType::GSToken},
        {"Grotto Scrub", LocationType::GrottoScrub},
        {"Delayed", LocationType::Delayed},
        {"Temple Reward", LocationType::TempleReward},
        {"Hint Stone", LocationType::HintStone},
        {"Other Hint", LocationType::OtherHint},
        {"Event", LocationType::Event},
        {"Drop", LocationType::Drop},
    };

    if (nameLocationTypeMap.count(name) == 0)
    {
        return LocationType::INVALID;
    }
    return nameLocationTypeMap.at(name);
}

LocationCategory NameToOot3dLocationCategory(const std::string& name)
{
    std::unordered_map<std::string, LocationCategory> nameLocationCategoryMap = {
        {"Kokiri Forest", LocationCategory::KokiriForest},
        {"Forest", LocationCategory::Forest},
        {"Grotto", LocationCategory::Grotto},
        {"Minigame", LocationCategory::Minigame},
        {"Chest Minigame", LocationCategory::ChestMinigame},
        {"Lost Woods", LocationCategory::LostWoods},
        {"Deku Scrub", LocationCategory::DekuScrub},
        {"Deku Scrub Upgrades", LocationCategory::DekuScrubUpgrades},
        {"Need Spiritual Stones", LocationCategory::NeedSpiritualStones},
        {"Sacred Forest Meadow", LocationCategory::SacredForestMeadow},
        {"Hyrule Field", LocationCategory::HyruleField},
        {"Lake Hylia", LocationCategory::LakeHylia},
        {"Gerudo", LocationCategory::Gerudo},
        {"Gerudo Valley", LocationCategory::GerudoValley},
        {"Gerudo Fortress", LocationCategory::GerudoFortress},
        {"Haunted Wasteland", LocationCategory::HauntedWasteland},
        {"Desert Colossus", LocationCategory::DesertColossus},
        {"Inner Market", LocationCategory::InnerMarket},
        {"Market", LocationCategory::Market},
        {"Hyrule Castle", LocationCategory::HyruleCastle},
        {"Kakariko Village", LocationCategory::KakarikoVillage},
        {"Kakariko", LocationCategory::Kakariko},
        {"Skulltula House", LocationCategory::SkulltulaHouse},
        {"Graveyard", LocationCategory::Graveyard},
        {"Death Mountain Trail", LocationCategory::DeathMountainTrail},
        {"Death Mountain", LocationCategory::DeathMountain},
        {"Goron City", LocationCategory::GoronCity},
        {"Death Mountain Crater", LocationCategory::DeathMountainCrater},
        {"Zoras River", LocationCategory::ZorasRiver},
        {"Zoras Domain", LocationCategory::ZorasDomain},
        {"Zoras Fountain", LocationCategory::ZorasFountain},
        {"Lon Lon Ranch", LocationCategory::LonLonRanch},
        {"Deku Tree", LocationCategory::DekuTree},
        {"Dodongos Cavern", LocationCategory::DodongosCavern},
        {"Jabu Jabus Belly", LocationCategory::JabuJabusBelly},
        {"Forest Temple", LocationCategory::ForestTemple},
        {"Fire Temple", LocationCategory::FireTemple},
        {"Water Temple", LocationCategory::WaterTemple},
        {"Spirit Temple", LocationCategory::SpiritTemple},
        {"Shadow Temple", LocationCategory::ShadowTemple},
        {"Bottom of the Well", LocationCategory::BottomOfTheWell},
        {"Ice Cavern", LocationCategory::IceCavern},
        {"Gerudo Training Ground", LocationCategory::GerudoTrainingGround},
        {"Ganons Castle", LocationCategory::GanonsCastle},
        {"Skulltula", LocationCategory::Skulltula},
        {"Boss Heart", LocationCategory::BossHeart},
        {"Temple of Time", LocationCategory::TempleOfTime},
        {"Fairies", LocationCategory::Fairies},
        {"Outside Ganons Castle", LocationCategory::OutsideGanonsCastle},
        {"Song", LocationCategory::Song},
        {"Song Dungeon Reward", LocationCategory::SongDungeonReward},
        {"Cow", LocationCategory::Cow},
        {"Shop", LocationCategory::Shop},
        {"Merchant", LocationCategory::Merchant},
        {"Vanilla Small Key", LocationCategory::VanillaSmallKey},
        {"Vanilla TH Small Key", LocationCategory::VanillaTHSmallKey},
        {"Vanilla Boss Key", LocationCategory::VanillaBossKey},
        {"Vanilla Map", LocationCategory::VanillaMap},
        {"Vanilla Compass", LocationCategory::VanillaCompass},
        {"Adult Trade", LocationCategory::AdultTrade},
    };
    if (nameLocationCategoryMap.count(name) == 0)
    {
        return LocationCategory::INVALID;
    }
    return nameLocationCategoryMap.at(name);
}

SpoilerCollectionCheckType NameToOot3dSpoilerCheckType(const std::string& name)
{
    std::unordered_map<std::string, SpoilerCollectionCheckType> nameCheckTypeMap = {
        {"None", SpoilerCollectionCheckType::SPOILER_CHK_NONE},
        {"Always Collected", SpoilerCollectionCheckType::SPOILER_CHK_ALWAYS_COLLECTED},
        {"Chest", SpoilerCollectionCheckType::SPOILER_CHK_CHEST},
        {"Collectable", SpoilerCollectionCheckType::SPOILER_CHK_COLLECTABLE},
        {"Gold Skulltula", SpoilerCollectionCheckType::SPOILER_CHK_GOLD_SKULLTULA},
        {"Item Get Inf", SpoilerCollectionCheckType::SPOILER_CHK_ITEM_GET_INF},
        {"Event Check Inf", SpoilerCollectionCheckType::SPOILER_CHK_EVENT_CHK_INF},
        {"Inf Table", SpoilerCollectionCheckType::SPOILER_CHK_INF_TABLE},
        {"Cow", SpoilerCollectionCheckType::SPOILER_CHK_COW},
        {"Minigame", SpoilerCollectionCheckType::SPOILER_CHK_MINIGAME},
        {"Scrub", SpoilerCollectionCheckType::SPOILER_CHK_SCRUB},
        {"Biggoron", SpoilerCollectionCheckType::SPOILER_CHK_BIGGORON},
        {"Gerudo Token", SpoilerCollectionCheckType::SPOILER_CHK_GERUDO_TOKEN},
        {"Poe Points", SpoilerCollectionCheckType::SPOILER_CHK_POE_POINTS},
        {"Shop Item", SpoilerCollectionCheckType::SPOILER_CHK_SHOP_ITEM},
        {"Magic Beans", SpoilerCollectionCheckType::SPOILER_CHK_MAGIC_BEANS},
    };

    if (nameCheckTypeMap.count(name) == 0)
    {
        return SpoilerCollectionCheckType::SPOILER_CHK_INVALID;
    }
    return nameCheckTypeMap.at(name);
}

SpoilerCollectionCheckGroup NameToOot3dSpoilerCheckGroup(const std::string& name)
{
    std::unordered_map<std::string, SpoilerCollectionCheckGroup> nameCheckGroupMap = {
        {"None", SpoilerCollectionCheckGroup::GROUP_NO_GROUP},
        {"Kokiri Forest", SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST},
        {"Lost Woods", SpoilerCollectionCheckGroup::GROUP_LOST_WOODS},
        {"Deku Tree", SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE},
        {"Forest Temple", SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE},
        {"Kakariko", SpoilerCollectionCheckGroup::GROUP_KAKARIKO},
        {"Bottom of the Well", SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL},
        {"Shadow Temple", SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE},
        {"Death Mountain", SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN},
        {"Goron City", SpoilerCollectionCheckGroup::GROUP_GORON_CITY},
        {"Dodongos Cavern", SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN},
        {"Fire Temple", SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE},
        {"Zoras River", SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER},
        {"Zoras Domain", SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN},
        {"Jabu Jabus Belly", SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY},
        {"Ice Cavern", SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN},
        {"Hyrule Field", SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD},
        {"Lon Lon Ranch", SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH},
        {"Lake Hylia", SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA},
        {"Water Temple", SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE},
        {"Gerudo Valley", SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY},
        {"Gerudo Training Ground", SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND},
        {"Spirit Temple", SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE},
        {"Hyrule Castle", SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE},
        {"Ganons Castle", SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE},
    };

    if (nameCheckGroupMap.count(name) == 0)
    {
        return SpoilerCollectionCheckGroup::GROUP_INVALID;
    }
    return nameCheckGroupMap.at(name);
}
