#pragma once

#include "item.hpp"

#include <string>

enum class LocationID : uint32_t
{
    NONE,
    LinksPocket,
    QueenGohma,
    KingDodongo,
    Barinade,
    PhantomGanon,
    Volvagia,
    Morpha,
    BongoBongo,
    Twinrova,
    Ganon,
    GiftfromSages,
    SongfromImpa,
    SongfromMalon,
    SongfromSaria,
    SongfromRoyalFamilysTomb,
    SongfromOcarinaofTime,
    SongfromWindmill,
    SheikInForest,
    SheikInCrater,
    SheikInIceCavern,
    SheikAtColossus,
    SheikInKakariko,
    SheikAtTemple,
    KFMidosTopLeftChest,
    KFMidosTopRightChest,
    KFMidosBottomLeftChest,
    KFMidosBottomRightChest,
    KFKokiriSwordChest,
    KFStormsGrottoChest,
    KFLinksHouseCow,
    KFGSKnowItAllHouse,
    KFGSBeanPatch,
    KFGSHouseofTwins,
    KFShopItem1,
    KFShopItem2,
    KFShopItem3,
    KFShopItem4,
    KFShopItem5,
    KFShopItem6,
    KFShopItem7,
    KFShopItem8,
    LWGiftfromSaria,
    LWOcarinaMemoryGame,
    LWTargetInWoods,
    LWNearShortcutsGrottoChest,
    DekuTheaterSkullMask,
    DekuTheaterMaskofTruth,
    LWSkullKid,
    LWTradeCojiro,
    LWTradeOddPoultice,
    LWDekuScrubNearBridge,
    LWDekuScrubNearDekuTheaterLeft,
    LWDekuScrubNearDekuTheaterRight,
    LWDekuScrubGrottoFront,
    LWDekuScrubGrottoRear,
    LWGSBeanPatchNearBridge,
    LWGSBeanPatchNearTheater,
    LWGSAboveTheater,
    SFMWolfosGrottoChest,
    SFMDekuScrubGrottoFront,
    SFMDekuScrubGrottoRear,
    SFMGS,
    HFOcarinaofTimeItem,
    HFNearMarketGrottoChest,
    HFTektiteGrottoFreestandingPoH,
    HFSoutheastGrottoChest,
    HFOpenGrottoChest,
    HFDekuScrubGrotto,
    HFCowGrottoCow,
    HFGSCowGrotto,
    HFGSNearKakGrotto,
    MarketShootingGalleryReward,
    MarketBombchuBowlingFirstPrize,
    MarketBombchuBowlingSecondPrize,
    MarketBombchuBowlingBombchus,
    MarketLostDog,
    MarketChestGameFirstRoomChest,
    MarketChestGameSecondRoomChest,
    MarketChestGameThirdRoomChest,
    MarketChestGameFourthRoomChest,
    MarketChestGameFifthRoomChest,
    MarketTreasureChestGameReward,
    Market10BigPoes,
    MarketGSGuardHouse,
    MarketBazaarItem1,
    MarketBazaarItem2,
    MarketBazaarItem3,
    MarketBazaarItem4,
    MarketBazaarItem5,
    MarketBazaarItem6,
    MarketBazaarItem7,
    MarketBazaarItem8,
    MarketPotionShopItem1,
    MarketPotionShopItem2,
    MarketPotionShopItem3,
    MarketPotionShopItem4,
    MarketPotionShopItem5,
    MarketPotionShopItem6,
    MarketPotionShopItem7,
    MarketPotionShopItem8,
    MarketBombchuShopItem1,
    MarketBombchuShopItem2,
    MarketBombchuShopItem3,
    MarketBombchuShopItem4,
    MarketBombchuShopItem5,
    MarketBombchuShopItem6,
    MarketBombchuShopItem7,
    MarketBombchuShopItem8,
    ToTLightArrowsCutscene,
    HCMalonEgg,
    HCZeldasLetter,
    HCGreatFairyReward,
    HCGSTree,
    HCGSStormsGrotto,
    LLRTalonsChickens,
    LLRFreestandingPoH,
    LLRDekuScrubGrottoLeft,
    LLRDekuScrubGrottoCenter,
    LLRDekuScrubGrottoRight,
    LLRStablesLeftCow,
    LLRStablesRightCow,
    LLRTowerLeftCow,
    LLRTowerRightCow,
    LLRGSHouseWindow,
    LLRGSTree,
    LLRGSRainShed,
    LLRGSBackWall,
    KakAnjuasChild,
    KakAnjuasAdult,
    KakTradePocketCucco,
    KakImpasHouseFreestandingPoH,
    KakWindmillFreestandingPoH,
    KakManonRoof,
    KakOpenGrottoChest,
    KakRedeadGrottoChest,
    KakShootingGalleryReward,
    KakTradeOddMushroom,
    Kak10GoldSkulltulaReward,
    Kak20GoldSkulltulaReward,
    Kak30GoldSkulltulaReward,
    Kak40GoldSkulltulaReward,
    Kak50GoldSkulltulaReward,
    KakImpasHouseCow,
    KakGSTree,
    KakGSGuardsHouse,
    KakGSWatchtower,
    KakGSSkulltulaHouse,
    KakGSHouseUnderConstruction,
    KakGSAboveImpasHouse,
    KakBazaarItem1,
    KakBazaarItem2,
    KakBazaarItem3,
    KakBazaarItem4,
    KakBazaarItem5,
    KakBazaarItem6,
    KakBazaarItem7,
    KakBazaarItem8,
    KakPotionShopItem1,
    KakPotionShopItem2,
    KakPotionShopItem3,
    KakPotionShopItem4,
    KakPotionShopItem5,
    KakPotionShopItem6,
    KakPotionShopItem7,
    KakPotionShopItem8,
    GraveyardShieldGraveChest,
    GraveyardHeartPieceGraveChest,
    GraveyardRoyalFamilysTombChest,
    GraveyardFreestandingPoH,
    GraveyardDampeGravediggingTour,
    GraveyardHookshotChest,
    GraveyardDampeRaceFreestandingPoH,
    GraveyardGSBeanPatch,
    GraveyardGSWall,
    DMTFreestandingPoH,
    DMTChest,
    DMTStormsGrottoChest,
    DMTGreatFairyReward,
    DMTTradeBrokenSword,
    DMTTradeEyedrops,
    DMTTradeClaimCheck,
    DMTCowGrottoCow,
    DMTGSNearKak,
    DMTGSBeanPatch,
    DMTGSAboveDodongosCavern,
    DMTGSFallingRocksPath,
    GCDaruniasJoy,
    GCPotFreestandingPoH,
    GCRollingGoronasChild,
    GCRollingGoronasAdult,
    GCMedigoron,
    GCMazeLeftChest,
    GCMazeRightChest,
    GCMazeCenterChest,
    GCDekuScrubGrottoLeft,
    GCDekuScrubGrottoCenter,
    GCDekuScrubGrottoRight,
    GCGSCenterPlatform,
    GCGSBoulderMaze,
    GCShopItem1,
    GCShopItem2,
    GCShopItem3,
    GCShopItem4,
    GCShopItem5,
    GCShopItem6,
    GCShopItem7,
    GCShopItem8,
    DMCVolcanoFreestandingPoH,
    DMCWallFreestandingPoH,
    DMCUpperGrottoChest,
    DMCGreatFairyReward,
    DMCDekuScrub,
    DMCDekuScrubGrottoLeft,
    DMCDekuScrubGrottoCenter,
    DMCDekuScrubGrottoRight,
    DMCGSCrate,
    DMCGSBeanPatch,
    ZRMagicBeanSalesman,
    ZROpenGrottoChest,
    ZRFrogsintheRain,
    ZRFrogsOcarinaGame,
    ZRNearOpenGrottoFreestandingPoH,
    ZRNearDomainFreestandingPoH,
    ZRDekuScrubGrottoFront,
    ZRDekuScrubGrottoRear,
    ZRGSTree,
    ZRGSLadder,
    ZRGSNearRaisedGrottos,
    ZRGSAboveBridge,
    ZDDivingMinigame,
    ZDChest,
    ZDKingZoraThawed,
    ZDTradePrescription,
    ZDGSFrozenWaterfall,
    ZDShopItem1,
    ZDShopItem2,
    ZDShopItem3,
    ZDShopItem4,
    ZDShopItem5,
    ZDShopItem6,
    ZDShopItem7,
    ZDShopItem8,
    ZFGreatFairyReward,
    ZFIcebergFreestandingPoH,
    ZFBottomFreestandingPoH,
    ZFGSAbovetheLog,
    ZFGSTree,
    ZFGSHiddenCave,
    LHUnderwaterItem,
    LHChildFishing,
    LHAdultFishing,
    LHLabDive,
    LHLabTradeEyeballFrog,
    LHFreestandingPoH,
    LHSun,
    LHDekuScrubGrottoLeft,
    LHDekuScrubGrottoCenter,
    LHDekuScrubGrottoRight,
    LHGSBeanPatch,
    LHGSLabWall,
    LHGSSmallIsland,
    LHGSLabCrate,
    LHGSTree,
    GVCrateFreestandingPoH,
    GVWaterfallFreestandingPoH,
    GVChest,
    GVTradeSaw,
    GVDekuScrubGrottoFront,
    GVDekuScrubGrottoRear,
    GVCow,
    GVGSSmallBridge,
    GVGSBeanPatch,
    GVGSBehindTent,
    GVGSPillar,
    GFChest,
    GFHBA1000Points,
    GFHBA1500Points,
    GFGSTopFloor,
    GFGSArcheryRange,
    HideoutJailGuard1Torch,
    HideoutJailGuard2Torches,
    HideoutJailGuard3Torches,
    HideoutJailGuard4Torches,
    HideoutGerudoToken,
    WastelandBombchuSalesman,
    WastelandChest,
    WastelandGS,
    ColossusGreatFairyReward,
    ColossusFreestandingPoH,
    ColossusDekuScrubGrottoFront,
    ColossusDekuScrubGrottoRear,
    ColossusGSBeanPatch,
    ColossusGSTree,
    ColossusGSHill,
    OGCGreatFairyReward,
    OGCGS,

    DekuTreeMapChest,
    DekuTreeSlingshotRoomSideChest,
    DekuTreeSlingshotChest,
    DekuTreeCompassChest,
    DekuTreeCompassRoomSideChest,
    DekuTreeBasementChest,
    DekuTreeGSCompassRoom,
    DekuTreeGSBasementVines,
    DekuTreeGSBasementGate,
    DekuTreeGSBasementBackRoom,
    DekuTreeMQMapChest,
    DekuTreeMQSlingshotChest,
    DekuTreeMQSlingshotRoomBackChest,
    DekuTreeMQCompassChest,
    DekuTreeMQBasementChest,
    DekuTreeMQBeforeSpinningLogChest,
    DekuTreeMQAfterSpinningLogChest,
    DekuTreeMQDekuScrub,
    DekuTreeMQGSLobby,
    DekuTreeMQGSCompassRoom,
    DekuTreeMQGSBasementGravesRoom,
    DekuTreeMQGSBasementBackRoom,
    DekuTreeQueenGohmaHeart,
    DodongosCavernMapChest,
    DodongosCavernCompassChest,
    DodongosCavernBombFlowerPlatformChest,
    DodongosCavernBombBagChest,
    DodongosCavernEndofBridgeChest,
    DodongosCavernDekuScrubSideRoomNearDodongos,
    DodongosCavernDekuScrubLobby,
    DodongosCavernDekuScrubNearBombBagLeft,
    DodongosCavernDekuScrubNearBombBagRight,
    DodongosCavernGSSideRoomNearLowerLizalfos,
    DodongosCavernGSScarecrow,
    DodongosCavernGSAlcoveAboveStairs,
    DodongosCavernGSVinesAboveStairs,
    DodongosCavernGSBackRoom,
    DodongosCavernMQMapChest,
    DodongosCavernMQBombBagChest,
    DodongosCavernMQTorchPuzzleRoomChest,
    DodongosCavernMQLarvaeRoomChest,
    DodongosCavernMQCompassChest,
    DodongosCavernMQUnderGraveChest,
    DodongosCavernMQDekuScrubLobbyFront,
    DodongosCavernMQDekuScrubLobbyRear,
    DodongosCavernMQDekuScrubSideRoomNearLowerLizalfos,
    DodongosCavernMQDekuScrubStaircase,
    DodongosCavernMQGSScrubRoom,
    DodongosCavernMQGSLarvaeRoom,
    DodongosCavernMQGSLizalfosRoom,
    DodongosCavernMQGSSongofTimeBlockRoom,
    DodongosCavernMQGSBackArea,
    DodongosCavernBossRoomChest,
    DodongosCavernKingDodongoHeart,
    JabuJabusBellyBoomerangChest,
    JabuJabusBellyMapChest,
    JabuJabusBellyCompassChest,
    JabuJabusBellyDekuScrub,
    JabuJabusBellyGSWaterSwitchRoom,
    JabuJabusBellyGSLobbyBasementLower,
    JabuJabusBellyGSLobbyBasementUpper,
    JabuJabusBellyGSNearBoss,
    JabuJabusBellyMQMapChest,
    JabuJabusBellyMQFirstRoomSideChest,
    JabuJabusBellyMQSecondRoomLowerChest,
    JabuJabusBellyMQCompassChest,
    JabuJabusBellyMQBasementNearSwitchesChest,
    JabuJabusBellyMQBasementNearVinesChest,
    JabuJabusBellyMQBoomerangRoomSmallChest,
    JabuJabusBellyMQBoomerangChest,
    JabuJabusBellyMQFallingLikeLikeRoomChest,
    JabuJabusBellyMQSecondRoomUpperChest,
    JabuJabusBellyMQNearBossChest,
    JabuJabusBellyMQCow,
    JabuJabusBellyMQGSBoomerangChestRoom,
    JabuJabusBellyMQGSTailpasaranRoom,
    JabuJabusBellyMQGSInvisibleEnemiesRoom,
    JabuJabusBellyMQGSNearBoss,
    JabuJabusBellyBarinadeHeart,
    BottomoftheWellFrontLeftFakeWallChest,
    BottomoftheWellFrontCenterBombableChest,
    BottomoftheWellBackLeftBombableChest,
    BottomoftheWellUnderwaterLeftChest,
    BottomoftheWellFreestandingKey,
    BottomoftheWellCompassChest,
    BottomoftheWellCenterSkulltulaChest,
    BottomoftheWellRightBottomFakeWallChest,
    BottomoftheWellFireKeeseChest,
    BottomoftheWellLikeLikeChest,
    BottomoftheWellMapChest,
    BottomoftheWellUnderwaterFrontChest,
    BottomoftheWellInvisibleChest,
    BottomoftheWellLensofTruthChest,
    BottomoftheWellGSWestInnerRoom,
    BottomoftheWellGSEastInnerRoom,
    BottomoftheWellGSLikeLikeCage,
    BottomoftheWellMQMapChest,
    BottomoftheWellMQEastInnerRoomFreestandingKey,
    BottomoftheWellMQCompassChest,
    BottomoftheWellMQDeadHandFreestandingKey,
    BottomoftheWellMQLensofTruthChest,
    BottomoftheWellMQGSCoffinRoom,
    BottomoftheWellMQGSWestInnerRoom,
    BottomoftheWellMQGSBasement,
    ForestTempleFirstRoomChest,
    ForestTempleFirstStalfosChest,
    ForestTempleRaisedIslandCourtyardChest,
    ForestTempleMapChest,
    ForestTempleWellChest,
    ForestTempleEyeSwitchChest,
    ForestTempleBossKeyChest,
    ForestTempleFloormasterChest,
    ForestTempleRedPoeChest,
    ForestTempleBowChest,
    ForestTempleBluePoeChest,
    ForestTempleFallingCeilingRoomChest,
    ForestTempleBasementChest,
    ForestTempleGSFirstRoom,
    ForestTempleGSLobby,
    ForestTempleGSRaisedIslandCourtyard,
    ForestTempleGSLevelIslandCourtyard,
    ForestTempleGSBasement,
    ForestTempleMQFirstRoomChest,
    ForestTempleMQWolfosChest,
    ForestTempleMQWellChest,
    ForestTempleMQRaisedIslandCourtyardLowerChest,
    ForestTempleMQRaisedIslandCourtyardUpperChest,
    ForestTempleMQBossKeyChest,
    ForestTempleMQRedeadChest,
    ForestTempleMQMapChest,
    ForestTempleMQBowChest,
    ForestTempleMQCompassChest,
    ForestTempleMQFallingCeilingRoomChest,
    ForestTempleMQBasementChest,
    ForestTempleMQGSFirstHallway,
    ForestTempleMQGSRaisedIslandCourtyard,
    ForestTempleMQGSLevelIslandCourtyard,
    ForestTempleMQGSWell,
    ForestTempleMQGSBlockPushRoom,
    ForestTemplePhantomGanonHeart,
    FireTempleNearBossChest,
    FireTempleFlareDancerChest,
    FireTempleBossKeyChest,
    FireTempleBigLavaRoomLowerOpenDoorChest,
    FireTempleBigLavaRoomBlockedDoorChest,
    FireTempleBoulderMazeLowerChest,
    FireTempleBoulderMazeSideRoomChest,
    FireTempleMapChest,
    FireTempleBoulderMazeShortcutChest,
    FireTempleBoulderMazeUpperChest,
    FireTempleScarecrowChest,
    FireTempleCompassChest,
    FireTempleMegatonHammerChest,
    FireTempleHighestGoronChest,
    FireTempleGSBossKeyLoop,
    FireTempleGSSongofTimeRoom,
    FireTempleGSBoulderMaze,
    FireTempleGSScarecrowClimb,
    FireTempleGSScarecrowTop,
    FireTempleMQMapRoomSideChest,
    FireTempleMQMegatonHammerChest,
    FireTempleMQMapChest,
    FireTempleMQNearBossChest,
    FireTempleMQBigLavaRoomBlockedDoorChest,
    FireTempleMQBossKeyChest,
    FireTempleMQLizalfosMazeSideRoomChest,
    FireTempleMQCompassChest,
    FireTempleMQLizalfosMazeUpperChest,
    FireTempleMQLizalfosMazeLowerChest,
    FireTempleMQFreestandingKey,
    FireTempleMQChestOnFire,
    FireTempleMQGSBigLavaRoomOpenDoor,
    FireTempleMQGSSkullOnFire,
    FireTempleMQGSFireWallMazeCenter,
    FireTempleMQGSFireWallMazeSideRoom,
    FireTempleMQGSAboveFireWallMaze,
    FireTempleVolvagiaHeart,
    WaterTempleCompassChest,
    WaterTempleMapChest,
    WaterTempleCrackedWallChest,
    WaterTempleTorchesChest,
    WaterTempleBossKeyChest,
    WaterTempleCentralPillarChest,
    WaterTempleCentralBowTargetChest,
    WaterTempleLongshotChest,
    WaterTempleRiverChest,
    WaterTempleDragonChest,
    WaterTempleGSBehindGate,
    WaterTempleGSNearBossKeyChest,
    WaterTempleGSCentralPillar,
    WaterTempleGSFallingPlatformRoom,
    WaterTempleGSRiver,
    WaterTempleMQLongshotChest,
    WaterTempleMQMapChest,
    WaterTempleMQCompassChest,
    WaterTempleMQCentralPillarChest,
    WaterTempleMQBossKeyChest,
    WaterTempleMQFreestandingKey,
    WaterTempleMQGSLizalfosHallway,
    WaterTempleMQGSBeforeUpperWaterSwitch,
    WaterTempleMQGSRiver,
    WaterTempleMQGSFreestandingKeyArea,
    WaterTempleMQGSTripleWallTorch,
    WaterTempleMorphaHeart,
    ShadowTempleMapChest,
    ShadowTempleHoverBootsChest,
    ShadowTempleCompassChest,
    ShadowTempleEarlySilverRupeeChest,
    ShadowTempleInvisibleBladesVisibleChest,
    ShadowTempleInvisibleBladesInvisibleChest,
    ShadowTempleFallingSpikesLowerChest,
    ShadowTempleFallingSpikesUpperChest,
    ShadowTempleFallingSpikesSwitchChest,
    ShadowTempleInvisibleSpikesChest,
    ShadowTempleFreestandingKey,
    ShadowTempleWindHintChest,
    ShadowTempleAfterWindEnemyChest,
    ShadowTempleAfterWindHiddenChest,
    ShadowTempleSpikeWallsLeftChest,
    ShadowTempleBossKeyChest,
    ShadowTempleInvisibleFloormasterChest,
    ShadowTempleGSLikeLikeRoom,
    ShadowTempleGSFallingSpikesRoom,
    ShadowTempleGSSingleGiantPot,
    ShadowTempleGSNearShip,
    ShadowTempleGSTripleGiantPot,
    ShadowTempleMQEarlyGibdosChest,
    ShadowTempleMQMapChest,
    ShadowTempleMQNearShipInvisibleChest,
    ShadowTempleMQCompassChest,
    ShadowTempleMQHoverBootsChest,
    ShadowTempleMQInvisibleBladesInvisibleChest,
    ShadowTempleMQInvisibleBladesVisibleChest,
    ShadowTempleMQBeamosSilverRupeesChest,
    ShadowTempleMQFallingSpikesLowerChest,
    ShadowTempleMQFallingSpikesUpperChest,
    ShadowTempleMQFallingSpikesSwitchChest,
    ShadowTempleMQInvisibleSpikesChest,
    ShadowTempleMQStalfosRoomChest,
    ShadowTempleMQWindHintChest,
    ShadowTempleMQAfterWindHiddenChest,
    ShadowTempleMQAfterWindEnemyChest,
    ShadowTempleMQBossKeyChest,
    ShadowTempleMQSpikeWallsLeftChest,
    ShadowTempleMQFreestandingKey,
    ShadowTempleMQBombFlowerChest,
    ShadowTempleMQGSFallingSpikesRoom,
    ShadowTempleMQGSWindHintRoom,
    ShadowTempleMQGSAfterWind,
    ShadowTempleMQGSAfterShip,
    ShadowTempleMQGSNearBoss,
    ShadowTempleBongoBongoHeart,
    SpiritTempleChildBridgeChest,
    SpiritTempleChildEarlyTorchesChest,
    SpiritTempleChildClimbNorthChest,
    SpiritTempleChildClimbEastChest,
    SpiritTempleMapChest,
    SpiritTempleSunBlockRoomChest,
    SpiritTempleMQEntranceFrontLeftChest,
    SpiritTempleMQEntranceBackRightChest,
    SpiritTempleMQEntranceFrontRightChest,
    SpiritTempleMQEntranceBackLeftChest,
    SpiritTempleMQMapChest,
    SpiritTempleMQMapRoomEnemyChest,
    SpiritTempleMQChildClimbNorthChest,
    SpiritTempleMQChildClimbSouthChest,
    SpiritTempleMQCompassChest,
    SpiritTempleMQSilverBlockHallwayChest,
    SpiritTempleMQSunBlockRoomChest,
    SpiritTempleSilverGauntletsChest,
    SpiritTempleCompassChest,
    SpiritTempleEarlyAdultRightChest,
    SpiritTempleFirstMirrorLeftChest,
    SpiritTempleFirstMirrorRightChest,
    SpiritTempleStatueRoomNortheastChest,
    SpiritTempleStatueRoomHandChest,
    SpiritTempleNearFourArmosChest,
    SpiritTempleHallwayRightInvisibleChest,
    SpiritTempleHallwayLeftInvisibleChest,
    SpiritTempleMQChildHammerSwitchChest,
    SpiritTempleMQStatueRoomLullabyChest,
    SpiritTempleMQStatueRoomInvisibleChest,
    SpiritTempleMQLeeverRoomChest,
    SpiritTempleMQSymphonyRoomChest,
    SpiritTempleMQBeamosRoomChest,
    SpiritTempleMQChestSwitchChest,
    SpiritTempleMQBossKeyChest,
    SpiritTempleMirrorShieldChest,
    SpiritTempleBossKeyChest,
    SpiritTempleTopmostChest,
    SpiritTempleMQMirrorPuzzleInvisibleChest,
    SpiritTempleGSMetalFence,
    SpiritTempleGSSunonFloorRoom,
    SpiritTempleGSHallAfterSunBlockRoom,
    SpiritTempleGSLobby,
    SpiritTempleGSBoulderRoom,
    SpiritTempleMQGSSunBlockRoom,
    SpiritTempleMQGSLeeverRoom,
    SpiritTempleMQGSSymphonyRoom,
    SpiritTempleMQGSNineThronesRoomWest,
    SpiritTempleMQGSNineThronesRoomNorth,
    SpiritTempleTwinrovaHeart,
    IceCavernMapChest,
    IceCavernCompassChest,
    IceCavernFreestandingPoH,
    IceCavernIronBootsChest,
    IceCavernGSSpinningScytheRoom,
    IceCavernGSHeartPieceRoom,
    IceCavernGSPushBlockRoom,
    IceCavernMQMapChest,
    IceCavernMQCompassChest,
    IceCavernMQFreestandingPoH,
    IceCavernMQIronBootsChest,
    IceCavernMQGSRedIce,
    IceCavernMQGSIceBlock,
    IceCavernMQGSScarecrow,
    GerudoTrainingGroundLobbyLeftChest,
    GerudoTrainingGroundLobbyRightChest,
    GerudoTrainingGroundStalfosChest,
    GerudoTrainingGroundBeforeHeavyBlockChest,
    GerudoTrainingGroundHeavyBlockFirstChest,
    GerudoTrainingGroundHeavyBlockSecondChest,
    GerudoTrainingGroundHeavyBlockThirdChest,
    GerudoTrainingGroundHeavyBlockFourthChest,
    GerudoTrainingGroundEyeStatueChest,
    GerudoTrainingGroundNearScarecrowChest,
    GerudoTrainingGroundHammerRoomClearChest,
    GerudoTrainingGroundHammerRoomSwitchChest,
    GerudoTrainingGroundFreestandingKey,
    GerudoTrainingGroundMazeRightCentralChest,
    GerudoTrainingGroundMazeRightSideChest,
    GerudoTrainingGroundUnderwaterSilverRupeeChest,
    GerudoTrainingGroundBeamosChest,
    GerudoTrainingGroundHiddenCeilingChest,
    GerudoTrainingGroundMazePathFirstChest,
    GerudoTrainingGroundMazePathSecondChest,
    GerudoTrainingGroundMazePathThirdChest,
    GerudoTrainingGroundMazePathFinalChest,
    GerudoTrainingGroundMQLobbyLeftChest,
    GerudoTrainingGroundMQLobbyRightChest,
    GerudoTrainingGroundMQFirstIronKnuckleChest,
    GerudoTrainingGroundMQBeforeHeavyBlockChest,
    GerudoTrainingGroundMQHeavyBlockChest,
    GerudoTrainingGroundMQEyeStatueChest,
    GerudoTrainingGroundMQIceArrowsChest,
    GerudoTrainingGroundMQSecondIronKnuckleChest,
    GerudoTrainingGroundMQFlameCircleChest,
    GerudoTrainingGroundMQMazeRightCentralChest,
    GerudoTrainingGroundMQMazeRightSideChest,
    GerudoTrainingGroundMQUnderwaterSilverRupeeChest,
    GerudoTrainingGroundMQDinolfosChest,
    GerudoTrainingGroundMQHiddenCeilingChest,
    GerudoTrainingGroundMQMazePathFirstChest,
    GerudoTrainingGroundMQMazePathThirdChest,
    GerudoTrainingGroundMQMazePathSecondChest,
    GanonsCastleForestTrialChest,
    GanonsCastleWaterTrialLeftChest,
    GanonsCastleWaterTrialRightChest,
    GanonsCastleShadowTrialFrontChest,
    GanonsCastleShadowTrialGoldenGauntletsChest,
    GanonsCastleLightTrialFirstLeftChest,
    GanonsCastleLightTrialSecondLeftChest,
    GanonsCastleLightTrialThirdLeftChest,
    GanonsCastleLightTrialFirstRightChest,
    GanonsCastleLightTrialSecondRightChest,
    GanonsCastleLightTrialThirdRightChest,
    GanonsCastleLightTrialInvisibleEnemiesChest,
    GanonsCastleLightTrialLullabyChest,
    GanonsCastleSpiritTrialCrystalSwitchChest,
    GanonsCastleSpiritTrialInvisibleChest,
    GanonsCastleDekuScrubLeft,
    GanonsCastleDekuScrubCenterLeft,
    GanonsCastleDekuScrubCenterRight,
    GanonsCastleDekuScrubRight,
    GanonsCastleMQForestTrialFreestandingKey,
    GanonsCastleMQForestTrialEyeSwitchChest,
    GanonsCastleMQForestTrialFrozenEyeSwitchChest,
    GanonsCastleMQWaterTrialChest,
    GanonsCastleMQShadowTrialBombFlowerChest,
    GanonsCastleMQShadowTrialEyeSwitchChest,
    GanonsCastleMQLightTrialLullabyChest,
    GanonsCastleMQSpiritTrialFirstChest,
    GanonsCastleMQSpiritTrialInvisibleChest,
    GanonsCastleMQSpiritTrialSunFrontLeftChest,
    GanonsCastleMQSpiritTrialSunBackLeftChest,
    GanonsCastleMQSpiritTrialSunBackRightChest,
    GanonsCastleMQSpiritTrialGoldenGauntletsChest,
    GanonsCastleMQDekuScrubLeft,
    GanonsCastleMQDekuScrubCenterLeft,
    GanonsCastleMQDekuScrubCenter,
    GanonsCastleMQDekuScrubCenterRight,
    GanonsCastleMQDekuScrubRight,
    GanonsTowerBossKeyChest,

    Pierre,
    DeliverRutosLetter,
    MasterSwordPedestal,
    DekuBabaSticks,
    DekuBabaNuts,
    StickPot,
    NutPot,
    NutCrate,
    BlueFire,
    LoneFish,
    FishGroup,
    BugRock,
    BugShrub,
    WanderingBugs,
    FairyPot,
    FreeFairies,
    WallFairy,
    ButterflyFairy,
    GossipStoneFairy,
    BeanPlantFairy,
    FairyPond,
    BigPoeKill,

    DMCGossipStone,
    DMTGossipStone,
    ColossusGossipStone,
    DodongosCavernGossipStone,
    GVGossipStone,
    GCMazeGossipStone,
    GCMedigoronGossipStone,
    GraveyardGossipStone,
    HCMalonGossipStone,
    HCRockWallGossipStone,
    HCStormsGrottoGossipStone,
    HFCowGrottoGossipStone,
    KFDekuTreeGossipStoneLeft,
    KFDekuTreeGossipStoneRight,
    KFGossipStone,
    LHLabGossipStone,
    LHGossipStoneSoutheast,
    LHGossipStoneSouthwest,
    LWGossipStone,
    SFMMazeGossipStoneLower,
    SFMMazeGossipStoneUpper,
    SFMSariaGossipStone,
    ToTGossipStoneLeft,
    ToTGossipStoneLeftCenter,
    ToTGossipStoneRight,
    ToTGossipStoneRightCenter,
    ZDGossipStone,
    ZFFairyGossipStone,
    ZFJabuGossipStone,
    ZRNearGrottosGossipStone,
    ZRNearDomainGossipStone,
    HFNearMarketGrottoGossipStone,
    HFSoutheastGrottoGossipStone,
    HFOpenGrottoGossipStone,
    KakOpenGrottoGossipStone,
    ZROpenGrottoGossipStone,
    KFStormsGrottoGossipStone,
    LWNearShortcutsGrottoGossipStone,
    DMTStormsGrottoGossipStone,
    DMCUpperGrottoGossipStone,
    GanondorfHint,
    INVALID,
};

LocationID NameToLocationID(const std::string& name);

class World;
class Area;
class Location {
public:

    Location();
    Location(const LocationID& id_, std::string name_, World* world_, Area* area_);
    ~Location();

    LocationID GetID() const;
    std::string GetName() const;
    World* GetWorld() const;
    Area* GetArea() const;
    Item GetCurrentItem() const;

    LocationID id = LocationID::INVALID;
    std::string name = "";
    World* world = nullptr;
    Area* area = nullptr;
    Item currentItem;

};

// inject specialization of std::hash<LocationID> into the std namespace
// taken from: https://en.cppreference.com/w/cpp/utility/hash
template<>
struct std::hash<LocationID>
{
    std::size_t operator()(LocationID const& locationId) const noexcept
    {
        return static_cast<std::underlying_type<LocationID>::type>(locationId);
    }
};
