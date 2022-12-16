#include "oot3d_location.hpp"

#include <unordered_map>

Oot3dLocation::Oot3dLocation() {}

Oot3dLocation::Oot3dLocation(const LocationID& id_, std::string name_, Oot3dLocationType type_, uint8_t scene_, uint8_t flag_, std::unordered_set<Oot3dLocationCategory> categories_,
                             const ItemID& vanillaItemId_, SpoilerCollectionCheck collectionCheck_, SpoilerCollectionCheckGroup collectionCheckGroup_, World* world_)
{
    id = id_;
    name = std::move(name_);
    type = type_;
    scene = scene_;
    flag = flag_;
    vanillaItemId = vanillaItemId_;
    categories = categories_;
    collectionCheck = collectionCheck_;
    collectionCheckGroup = collectionCheckGroup_;
    world = world_;
}

Oot3dLocation::~Oot3dLocation() = default;

std::string Oot3dLocation::TypeString() const
{
    return "Oot3d Location";
}

Oot3dLocationType NameToOot3dLocationType(const std::string& name)
{
    std::unordered_map<std::string, Oot3dLocationType> nameLocationTypeMap = {
        {"Base", Oot3dLocationType::Base},
        {"Chest", Oot3dLocationType::Chest},
        {"Collectable", Oot3dLocationType::Collectable},
        {"GS Token", Oot3dLocationType::GSToken},
        {"Grotto Scrub", Oot3dLocationType::GrottoScrub},
        {"Delayed", Oot3dLocationType::Delayed},
        {"Temple Reward", Oot3dLocationType::TempleReward},
        {"Hint Stone", Oot3dLocationType::HintStone},
        {"Other Hint", Oot3dLocationType::OtherHint},
        {"Event", Oot3dLocationType::Event},
        {"Drop", Oot3dLocationType::Drop},
    };

    if (nameLocationTypeMap.count(name) == 0)
    {
        return Oot3dLocationType::INVALID;
    }
    return nameLocationTypeMap.at(name);
}

Oot3dLocationCategory NameToOot3dLocationCategory(const std::string& name)
{
    std::unordered_map<std::string, Oot3dLocationCategory> nameLocationCategoryMap = {
        {"Kokiri Forest", Oot3dLocationCategory::KokiriForest},
        {"Forest", Oot3dLocationCategory::Forest},
        {"Grotto", Oot3dLocationCategory::Grotto},
        {"Minigame", Oot3dLocationCategory::Minigame},
        {"Chest Minigame", Oot3dLocationCategory::ChestMinigame},
        {"Lost Woods", Oot3dLocationCategory::LostWoods},
        {"Deku Scrub", Oot3dLocationCategory::DekuScrub},
        {"Deku Scrub Upgrades", Oot3dLocationCategory::DekuScrubUpgrades},
        {"Need Spiritual Stones", Oot3dLocationCategory::NeedSpiritualStones},
        {"Sacred Forest Meadow", Oot3dLocationCategory::SacredForestMeadow},
        {"Hyrule Field", Oot3dLocationCategory::HyruleField},
        {"Lake Hylia", Oot3dLocationCategory::LakeHylia},
        {"Gerudo", Oot3dLocationCategory::Gerudo},
        {"Gerudo Valley", Oot3dLocationCategory::GerudoValley},
        {"Gerudo Fortress", Oot3dLocationCategory::GerudoFortress},
        {"Thieves Hideout", Oot3dLocationCategory::ThievesHideout},
        {"Haunted Wasteland", Oot3dLocationCategory::HauntedWasteland},
        {"Desert Colossus", Oot3dLocationCategory::DesertColossus},
        {"Inner Market", Oot3dLocationCategory::InnerMarket},
        {"Market", Oot3dLocationCategory::Market},
        {"Hyrule Castle", Oot3dLocationCategory::HyruleCastle},
        {"Kakariko Village", Oot3dLocationCategory::KakarikoVillage},
        {"Kakariko", Oot3dLocationCategory::Kakariko},
        {"Skulltula House", Oot3dLocationCategory::SkulltulaHouse},
        {"Graveyard", Oot3dLocationCategory::Graveyard},
        {"Death Mountain Trail", Oot3dLocationCategory::DeathMountainTrail},
        {"Death Mountain", Oot3dLocationCategory::DeathMountain},
        {"Goron City", Oot3dLocationCategory::GoronCity},
        {"Death Mountain Crater", Oot3dLocationCategory::DeathMountainCrater},
        {"Zoras River", Oot3dLocationCategory::ZorasRiver},
        {"Zoras Domain", Oot3dLocationCategory::ZorasDomain},
        {"Zoras Fountain", Oot3dLocationCategory::ZorasFountain},
        {"Lon Lon Ranch", Oot3dLocationCategory::LonLonRanch},
        {"Deku Tree", Oot3dLocationCategory::DekuTree},
        {"Dodongos Cavern", Oot3dLocationCategory::DodongosCavern},
        {"Jabu Jabus Belly", Oot3dLocationCategory::JabuJabusBelly},
        {"Forest Temple", Oot3dLocationCategory::ForestTemple},
        {"Fire Temple", Oot3dLocationCategory::FireTemple},
        {"Water Temple", Oot3dLocationCategory::WaterTemple},
        {"Spirit Temple", Oot3dLocationCategory::SpiritTemple},
        {"Shadow Temple", Oot3dLocationCategory::ShadowTemple},
        {"Bottom of the Well", Oot3dLocationCategory::BottomOfTheWell},
        {"Ice Cavern", Oot3dLocationCategory::IceCavern},
        {"Gerudo Training Ground", Oot3dLocationCategory::GerudoTrainingGround},
        {"Ganons Castle", Oot3dLocationCategory::GanonsCastle},
        {"Skulltula", Oot3dLocationCategory::Skulltula},
        {"Boss Heart", Oot3dLocationCategory::BossHeart},
        {"Temple of Time", Oot3dLocationCategory::TempleOfTime},
        {"Fairies", Oot3dLocationCategory::Fairies},
        {"Outside Ganons Castle", Oot3dLocationCategory::OutsideGanonsCastle},
        {"Song", Oot3dLocationCategory::Song},
        {"Song Dungeon Reward", Oot3dLocationCategory::SongDungeonReward},
        {"Cow", Oot3dLocationCategory::Cow},
        {"Shop", Oot3dLocationCategory::Shop},
        {"Merchant", Oot3dLocationCategory::Merchant},
        {"Vanilla Small Key", Oot3dLocationCategory::VanillaSmallKey},
        {"Vanilla TH Small Key", Oot3dLocationCategory::VanillaTHSmallKey},
        {"Vanilla Boss Key", Oot3dLocationCategory::VanillaBossKey},
        {"Vanilla Map", Oot3dLocationCategory::VanillaMap},
        {"Vanilla Compass", Oot3dLocationCategory::VanillaCompass},
        {"Adult Trade", Oot3dLocationCategory::AdultTrade},
    };
    if (nameLocationCategoryMap.count(name) == 0)
    {
        return Oot3dLocationCategory::INVALID;
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
