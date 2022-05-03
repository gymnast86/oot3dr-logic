#pragma once

#include <string>

enum class AreaID : uint32_t
{
    NONE,
    Root,
    RootExits,
    ChildSpawn,
    AdultSpawn,
    PreludeOfLightWarp,
    MinuetOfForestWarp,
    BoleroOfFireWarp,
    SerenadeOfWaterWarp,
    RequiemOfSpiritWarp,
    NocturneOfShadowWarp,
    KokiriForest,
    KFOutsideDekuTree,
    KFLinksHouse,
    KFMidosHouse,
    KFSariasHouse,
    KFHouseOfTwins,
    KFKnowItAllHouse,
    KFKokiriShop,
    LWForestExit,
    LostWoods,
    LWBeyondMido,
    LostWoodsMushroomTimeout,
    SFMEntryway,
    SacredForestMeadow,
    SFMForestTempleEntranceLedge,
    LWBridgeFromForest,
    LWBridge,
    HyruleField,
    LakeHylia,
    LHFishingIsland,
    LHOwlFlight,
    LHLab,
    LHFishingHole,
    GerudoValley,
    GVUpperStream,
    GVLowerStream,
    GVGrottoLedge,
    GVCrateLedge,
    GVFortressSide,
    GVCarpenterTent,
    GerudoFortress,
    GFOutsideGate,
    WastelandNearFortress,
    HauntedWasteland,
    WastelandNearColossus,
    DesertColossus,
    DesertColossusFromSpiritLobby,
    ColossusGreatFairyFountain,
    MarketEntrance,
    Market,
    MarketBackAlley,
    ToTEntrance,
    TempleOfTime,
    BeyondDoorOfTime,
    CastleGrounds,
    HyruleCastleGrounds,
    HCGarden,
    HCGardenLocations,
    HCGreatFairyFountain,
    GanonsCastleGrounds,
    OGCGreatFairyFountain,
    MarketGuardHouse,
    MarketBazaar,
    MarketMaskShop,
    MarketShootingGallery,
    MarketBombchuBowling,
    MarketPotionShop,
    MarketTreasureChestGame,
    MarketBombchuShop,
    MarketDogLadyHouse,
    MarketManInGreenHouse,
    KakarikoVillage,
    KakImpasLedge,
    KakImpasRooftop,
    KakOddMedicineRooftop,
    KakBackyard,
    KakCarpenterBossHouse,
    KakHouseOfSkulltula,
    KakImpasHouse,
    KakImpasHouseBack,
    KakImpasHouseNearCow,
    KakWindmill,
    KakBazaar,
    KakShootingGallery,
    KakPotionShopBack,
    KakOddMedicineBuilding,
    Graveyard,
    GraveyardShieldGrave,
    GraveyardHeartPieceGrave,
    GraveyardRoyalFamilysTomb,
    GraveyardDampesGrave,
    GraveyardDampesHouse,
    GraveyardWarpPadRegion,
    KakBehindGate,
    DeathMountain,
    DeathMountainSummit,
    DMTOwlFlight,
    GoronCity,
    GCWoodsWarp,
    GCDaruniasChamber,
    GCGrottoPlatform,
    DMCUpperNearby,
    DMCUpperLocal,
    DMCLadderAreaNearby,
    DMCLowerNearby,
    DMCLowerLocal,
    DMCCentralNearby,
    DMCCentralLocal,
    DMCFireTempleEntrance,
    DMCGreatFairyFountain,
    DMTGreatFairyFountain,
    ZRFront,
    ZoraRiver,
    ZRBehindWaterfall,
    ZRTopOfWaterfall,
    ZorasDomain,
    ZDBehindKingZora,
    ZDEyeballFrogTimeout,
    ZorasFountain,
    ZFIceLedge,
    ZDShop,
    ZFGreatFairyFountain,
    LonLonRanch,
    LLRTalonsHouse,
    LLRStables,
    LLRTower,
    GanonsCastleTower,
    GFStormsGrotto,
    ZDStormsGrotto,
    KFStormsGrotto,
    LWNearShortcutsGrotto,
    DekuTheater,
    LWScrubsGrotto,
    SFMFairyGrotto,
    SFMStormsGrotto,
    SFMWolfosGrotto,
    LLRGrotto,
    HFSoutheastGrotto,
    HFOpenGrotto,
    HFInsideFenceGrotto,
    HFCowGrotto,
    HFNearMarketGrotto,
    HFFairyGrotto,
    HFNearKakGrotto,
    HFTektiteGrotto,
    HCStormsGrotto,
    KakRedeadGrotto,
    KakOpenGrotto,
    DMTCowGrotto,
    DMTStormsGrotto,
    GCGrotto,
    DMCUpperGrotto,
    DMCHammerGrotto,
    ZROpenGrotto,
    ZRFairyGrotto,
    ZRStormsGrotto,
    LHGrotto,
    ColossusGrotto,
    GVOctorokGrotto,
    GVStormsGrotto,
    DekuTreeLobby,
    DodongosCavernBeginning,
    JabuJabusBellyBeginning,
    ForestTempleLobby,
    FireTempleLower,
    WaterTempleLobby,
    SpiritTempleLobby,
    ShadowTempleEntryway,
    IceCavernBeginning,
    BottomOfTheWell,
    GerudoTrainingGroundLobby,

    INVALID
};

AreaID NameToAreaID(const std::string& name);

std::string AreaIDToName(const AreaID& areaId);

// inject specialization of std::hash<AreaID> into the std namespace
// taken from: https://en.cppreference.com/w/cpp/utility/hash
template<>
struct std::hash<AreaID>
{
    std::size_t operator()(AreaID const& areaId) const noexcept
    {
        return static_cast<std::underlying_type<AreaID>::type>(areaId);
    }
};
