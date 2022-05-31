#pragma once

#include "../location.hpp"

#include "../../patch_code/oot3d/src/spoiler_data.h"

enum class LocationType {
    Base,
    Chest,
    Collectable,
    GSToken,
    GrottoScrub,
    Delayed,
    TempleReward,
    HintStone,
    OtherHint,
    Event,
    Drop,
    INVALID,
};

enum class LocationCategory {
    INVALID,
    KokiriForest,
    Forest,
    Grotto,
    Minigame,
    ChestMinigame,
    LostWoods,
    DekuScrub,
    DekuScrubUpgrades,
    NeedSpiritualStones,
    SacredForestMeadow,
    HyruleField,
    LakeHylia,
    Gerudo,
    GerudoValley,
    GerudoFortress,
    HauntedWasteland,
    DesertColossus,
    InnerMarket,
    Market,
    HyruleCastle,
    KakarikoVillage,
    Kakariko,
    SkulltulaHouse,
    Graveyard,
    DeathMountainTrail,
    DeathMountain,
    GoronCity,
    DeathMountainCrater,
    ZorasRiver,
    ZorasDomain,
    ZorasFountain,
    LonLonRanch,
    DekuTree,
    DodongosCavern,
    JabuJabusBelly,
    ForestTemple,
    FireTemple,
    WaterTemple,
    SpiritTemple,
    ShadowTemple,
    BottomOfTheWell,
    IceCavern,
    GerudoTrainingGround,
    GanonsCastle,
    Skulltula,
    BossHeart,
    TempleOfTime,
    Fairies,
    OutsideGanonsCastle,
    Song,
    SongDungeonReward,
    Cow,
    Shop,
    Merchant,
    VanillaSmallKey,
    VanillaTHSmallKey,
    VanillaBossKey,
    VanillaMap,
    VanillaCompass,
    AdultTrade,
};

class SpoilerCollectionCheck {
public:
    SpoilerCollectionCheckType type = SpoilerCollectionCheckType::SPOILER_CHK_NONE;
    uint8_t scene = 0;
    uint8_t flag = 0;

    SpoilerCollectionCheck() {}
    SpoilerCollectionCheck(SpoilerCollectionCheckType type_, uint8_t scene_, uint8_t flag_) : type(type_), scene(scene_), flag(flag_) {}
};

class Oot3dLocation : public Location {
public:

    Oot3dLocation();
    Oot3dLocation(const LocationID& id_, std::string name, LocationType type_, uint8_t scene_, uint8_t flag_, const ItemID& vanillaItem, SpoilerCollectionCheck collectionCheck_, SpoilerCollectionCheckGroup collectionCheckGroup_, World* world_);
    ~Oot3dLocation();

    std::string TypeString() const override;

    LocationType type;
    uint8_t scene = 0;
    uint8_t flag = 0;
    ItemID vanillaItem = ItemID::NONE;
    SpoilerCollectionCheck collectionCheck;
    SpoilerCollectionCheckGroup collectionCheckGroup;
};

LocationType NameToOot3dLocationType(const std::string& name);

LocationCategory NameToOot3dLocationCategory(const std::string& name);

SpoilerCollectionCheckType NameToOot3dSpoilerCheckType(const std::string& name);

SpoilerCollectionCheckGroup NameToOot3dSpoilerCheckGroup(const std::string& name);
