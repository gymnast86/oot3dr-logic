#pragma once

#include "../location.hpp"

#include "../../patch_code/oot3d/src/spoiler_data.h"

enum class Oot3dLocationType {
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

enum class Oot3dLocationCategory {
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
    ThievesHideout,
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
    FrogRupees,
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
    Oot3dLocation(const LocationID& id_, std::string name, Oot3dLocationType type_, uint8_t scene_, uint8_t flag_, std::unordered_set<Oot3dLocationCategory> categories_,
                  const Item& vanillaItem_, SpoilerCollectionCheck collectionCheck_, SpoilerCollectionCheckGroup collectionCheckGroup_, std::string dungeon_, World* world_);
    ~Oot3dLocation();

    uint16_t GetPrice() const;
    void SetPrice(uint16_t newPrice);
    std::string TypeString() const override;

    Oot3dLocationType type;
    uint8_t scene = 0;
    uint8_t flag = 0;
    uint16_t priceForPlacedItem = 0;
    std::unordered_set<Oot3dLocationCategory> categories = {};
    SpoilerCollectionCheck collectionCheck;
    SpoilerCollectionCheckGroup collectionCheckGroup;
    std::string dungeon = "None";
};

Oot3dLocationType NameToOot3dLocationType(const std::string& name);

Oot3dLocationCategory NameToOot3dLocationCategory(const std::string& name);

SpoilerCollectionCheckType NameToOot3dSpoilerCheckType(const std::string& name);

SpoilerCollectionCheckGroup NameToOot3dSpoilerCheckGroup(const std::string& name);
