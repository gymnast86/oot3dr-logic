#pragma once

#include "oot3d_world_graph.hpp"
#include "../item.hpp"
#include "../logic.hpp"
#include "../world.hpp"
#include "../../patch_code/oot3d/src/settings.h"

struct Oot3dLogicItems {
    uint16_t kokiriSword;
    uint16_t masterSword;
    uint16_t giantsKnife;
    uint16_t biggoronsSword;
    uint16_t dekuShield;
    uint16_t hylianShield;
    uint16_t mirrorShield;
    uint16_t goronTunic;
    uint16_t zoraTunic;
    uint16_t ironBoots;
    uint16_t hoverBoots;
    uint16_t boomerang;
    uint16_t lensOfTruth;
    uint16_t megatonHammer;
    uint16_t shardOfAgony;
    uint16_t dinsFire;
    uint16_t faroresWind;
    uint16_t nayrusLove;
    uint16_t fireArrows;
    uint16_t iceArrows;
    uint16_t lightArrows;
    uint16_t gerudoToken;
    uint16_t magicBean;
    uint16_t magicBeanPack;
    uint16_t doubleDefense;
    uint16_t weirdEgg;
    uint16_t cucco;
    uint16_t zeldasLetter;
    uint16_t keatonMask;
    uint16_t skullMask;
    uint16_t spookyMask;
    uint16_t bunnyHood;
    uint16_t goronMask;
    uint16_t zoraMask;
    uint16_t gerudoMask;
    uint16_t maskOfTruth;
    uint16_t pocketEgg;
    uint16_t pocketCucco;
    uint16_t cojiro;
    uint16_t oddMushroom;
    uint16_t oddPoultice;
    uint16_t poachersSaw;
    uint16_t brokenGoronsSword;
    uint16_t prescription;
    uint16_t eyeballFrog;
    uint16_t eyedrops;
    uint16_t claimCheck;
    uint16_t goldSkulltulaToken;
    uint16_t progressiveHookshot;
    uint16_t progressiveStrengthUpgrade;
    uint16_t progressiveBombBag;
    uint16_t progressiveBow;
    uint16_t progressiveSlingshot;
    uint16_t progressiveWallet;
    uint16_t progressiveScale;
    uint16_t progressiveNutCapacity;
    uint16_t progressiveStickCapacity;
    uint16_t progressiveBombchus;
    uint16_t progressiveMagicMeter;
    uint16_t progressiveOcarina;
    uint16_t progressiveGoronSword;
    uint16_t emptyBottle;
    uint16_t bottleWithMilk;
    uint16_t bottleWithRedPotion;
    uint16_t bottleWithGreenPotion;
    uint16_t bottleWithBluePotion;
    uint16_t bottleWithFairy;
    uint16_t bottleWithFish;
    uint16_t bottleWithBlueFire;
    uint16_t bottleWithBugs;
    uint16_t bottleWithPoe;
    uint16_t rutosLetter;
    uint16_t bottleWithBigPoe;
    uint16_t zeldasLullaby;
    uint16_t eponasSong;
    uint16_t sariasSong;
    uint16_t sunsSong;
    uint16_t songOfTime;
    uint16_t songOfStorms;
    uint16_t minuetOfForest;
    uint16_t boleroOfFire;
    uint16_t serenadeOfWater;
    uint16_t requiemOfSpirit;
    uint16_t nocturneOfShadow;
    uint16_t preludeOfLight;
    uint16_t dekuTreeMap;
    uint16_t dodongosCavernMap;
    uint16_t jabuJabusBellyMap;
    uint16_t forestTempleMap;
    uint16_t fireTempleMap;
    uint16_t waterTempleMap;
    uint16_t spiritTempleMap;
    uint16_t shadowTempleMap;
    uint16_t bottomOfTheWellMap;
    uint16_t iceCavernMap;
    uint16_t dekuTreeCompass;
    uint16_t dodongosCavernCompass;
    uint16_t jabuJabusBellyCompass;
    uint16_t forestTempleCompass;
    uint16_t fireTempleCompass;
    uint16_t waterTempleCompass;
    uint16_t spiritTempleCompass;
    uint16_t shadowTempleCompass;
    uint16_t bottomOfTheWellCompass;
    uint16_t iceCavernCompass;
    uint16_t forestTempleBossKey;
    uint16_t fireTempleBossKey;
    uint16_t waterTempleBossKey;
    uint16_t spiritTempleBossKey;
    uint16_t shadowTempleBossKey;
    uint16_t ganonsCastleBossKey;
    uint16_t forestTempleSmallKey;
    uint16_t fireTempleSmallKey;
    uint16_t waterTempleSmallKey;
    uint16_t spiritTempleSmallKey;
    uint16_t shadowTempleSmallKey;
    uint16_t bottomOfTheWellSmallKey;
    uint16_t gerudoTrainingGroundSmallKey;
    uint16_t thievesHideoutSmallKey;
    uint16_t ganonsCastleSmallKey;
    uint16_t chestGameSmallKey;
    uint16_t kokiriEmerald;
    uint16_t goronRuby;
    uint16_t zoraSapphire;
    uint16_t forestMedallion;
    uint16_t fireMedallion;
    uint16_t waterMedallion;
    uint16_t spiritMedallion;
    uint16_t shadowMedallion;
    uint16_t lightMedallion;
    uint16_t recoveryHeart;
    uint16_t greenRupee;
    uint16_t blueRupee;
    uint16_t redRupee;
    uint16_t purpleRupee;
    uint16_t hugeRupee;
    uint16_t pieceOfHeart;
    uint16_t heartContainer;
    uint16_t iceTrap;
    uint16_t milk;
    uint16_t bombs5;
    uint16_t bombs10;
    uint16_t bombs20;
    uint16_t bombchus5;
    uint16_t bombchus10;
    uint16_t bombchus20;
    uint16_t bombchuDrop;
    uint16_t arrows5;
    uint16_t arrows10;
    uint16_t arrows30;
    uint16_t dekuNuts5;
    uint16_t dekuNuts10;
    uint16_t dekuSeeds30;
    uint16_t dekuStick1;
    uint16_t redPotionRefill;
    uint16_t greenPotionRefill;
    uint16_t bluePotionRefill;
    uint16_t treasureGameHeart;
    uint16_t treasureGameGreenRupee;
    uint16_t buyDekuNut5;
    uint16_t buyArrows30;
    uint16_t buyArrows50;
    uint16_t buyBombs525;
    uint16_t buyDekuNut10;
    uint16_t buyDekuStick1;
    uint16_t buyBombs10;
    uint16_t buyFish;
    uint16_t buyRedPotion30;
    uint16_t buyGreenPotion;
    uint16_t buyBluePotion;
    uint16_t buyHylianShield;
    uint16_t buyDekuShield;
    uint16_t buyGoronTunic;
    uint16_t buyZoraTunic;
    uint16_t buyHeart;
    uint16_t buyBombchu10;
    uint16_t buyBombchu20;
    uint16_t buyBombchu5;
    uint16_t buyDekuSeeds30;
    uint16_t soldOut;
    uint16_t buyBlueFire;
    uint16_t buyBottleBug;
    uint16_t buyPoe;
    uint16_t buyFairysSpirit;
    uint16_t buyArrows10;
    uint16_t buyBombs20;
    uint16_t buyBombs30;
    uint16_t buyBombs535;
    uint16_t buyRedPotion40;
    uint16_t buyRedPotion50;
    // Events
    uint16_t epona;
    uint16_t linksCow;
    uint16_t bonooru;
    uint16_t triforcePiece;
    uint16_t timeTravel;
    uint16_t scarecrowSong;
    uint16_t triforce;
    uint16_t forestTrialClear;
    uint16_t fireTrialClear;
    uint16_t waterTrialClear;
    uint16_t shadowTrialClear;
    uint16_t spiritTrialClear;
    uint16_t lightTrialClear;
    uint16_t dekuStickDrop;
    uint16_t dekuNutDrop;
    uint16_t blueFire;
    uint16_t fairy;
    uint16_t fish;
    uint16_t bugs;
    uint16_t bigPoe;
    uint16_t dekuTreeClear;
    uint16_t dodongosCavernClear;
    uint16_t jabuJabusBellyClear;
    uint16_t forestTempleClear;
    uint16_t fireTempleClear;
    uint16_t waterTempleClear;
    uint16_t spiritTempleClear;
    uint16_t shadowTempleClear;
    uint16_t showedMidoSwordAndShield;
    uint16_t drainWell;
    uint16_t dampesWindmillAccess;
    uint16_t gcDaruniasDoorOpenChild;
    uint16_t goronCityChildFire;
    uint16_t gcWoodsWarpOpen;
    uint16_t stopGCRollingGoronAsAdult;
    uint16_t deliverLetter;
    uint16_t kingZoraThawed;
    uint16_t carpenterRescue;
    uint16_t gfGateOpen;
    uint16_t gtgGateOpen;
    uint16_t sellBigPoe;
    uint16_t kakarikoVillageGateOpen;
    uint16_t wakeUpAdultTalon;
    uint16_t hint;
};

// Properly apply settings later
struct Oot3dLogicSettings {
    uint16_t bombchusInLogic = ON;
    uint16_t logicRules = LOGIC_GLITCHLESS;
    uint16_t openForest = OPENFOREST_OPEN;
    uint16_t gerudoFortress = GERUDOFORTRESS_NORMAL;
    uint16_t damageMultiplier = DAMAGEMULTIPLIER_DEFAULT;
    uint16_t hints = HINTS_NEED_NOTHING;
    uint16_t plantBeans = OFF;
    uint16_t bridge = RAINBOWBRIDGE_MEDALLIONS;
    uint16_t lacsCondition = LACSCONDITION_VANILLA;
    uint16_t shuffleGanonBosskey = GANONSBOSSKEY_ANYWHERE;
    uint16_t bridgeTokens = 10;
    uint16_t bridgeStones = 3;
    uint16_t bridgeMedallions = 6;
    uint16_t bridgeRewards = 9;
    uint16_t lacsTokens = 10;
    uint16_t lacsStones = 3;
    uint16_t lacsMedallions = 6;
    uint16_t lacsRewards = 9;
    uint16_t ganonBosskeyStones = 3;
    uint16_t ganonBosskeyTokens = 10;
    uint16_t ganonBosskeyRewards = 9;
    uint16_t ganonBosskeyMedallions = 6;
    uint16_t hadNightStart = OFF;
    uint16_t completeMaskQuest = OFF;
    uint16_t entranceShuffle = OFF;
    uint16_t shuffleScrubs = SCRUBSANITY_OFF;
    uint16_t shuffleWeirdEgg = OFF;
    uint16_t shuffleGerudoToken = OFF;
    uint16_t shuffleChestGame = OFF;
    uint16_t shuffleDungeonEntrances = OFF;
    uint16_t shuffleOverworldEntrances = OFF;
    uint16_t freeScarecrow = OFF;
    uint16_t bigPoeCount = 1;
    uint16_t zoraFountain = ZORASFOUNTAIN_NORMAL;
    uint16_t openKakariko = OPENKAKARIKO_OPEN;
    uint16_t openDoorOfTime = OPENDOOROFTIME_OPEN;
    uint16_t skipChildZelda = OFF;
    uint16_t nightGsExpectSuns = ON;
    uint16_t ammoDrops = AMMODROPS_VANILLA;
    uint16_t baseHearts = 3;
};

struct Oot3dLogicTricks {
    uint16_t grottosWithoutAgony = OFF;
    uint16_t gerudoKitchen = OFF;
    uint16_t adultKokiriGs = ON;
    uint16_t lostWoodsGsBean = OFF;
    uint16_t lostWoodsBridge = OFF;
    uint16_t labWallGS = ON;
    uint16_t labDiving = OFF;
    uint16_t gvHammerChest = OFF;
    uint16_t wastelandCrossing = OFF;
    uint16_t lensWasteland = OFF;
    uint16_t reverseWasteland = ON;
    uint16_t colossusGS = OFF;
    uint16_t outsideGanonsGS = OFF;
    uint16_t kakarikoTowerGS = OFF;
    uint16_t kakarikoRooftopGS = ON;
    uint16_t manOnRoof = ON;
    uint16_t windmillPohHookshot = ON;
    uint16_t graveyardPoh = ON;
    uint16_t childDampeRacePoh = ON;
    uint16_t shadowFireArrowEntry = OFF;
    uint16_t visibleCollisions = ON;
    uint16_t dmtBombable = ON;
    uint16_t dmtSoilGS = OFF;
    uint16_t dmtClimbHovers = OFF;
    uint16_t linkGoronDins = ON;
    uint16_t goronCityLeftmost = ON;
    uint16_t goronCityPotWithStrength = OFF;
    uint16_t goronCityPot = OFF;
    uint16_t childRollingWithStrength = ON;
    uint16_t goronGrotto = OFF;
    uint16_t craterUpperToLower = OFF;
    uint16_t fewerTunicRequirements = ON;
    uint16_t craterBeanPohWithHovers = ON;
    uint16_t zoraRiverLower = OFF;
    uint16_t zoraRiverUpper = OFF;
    uint16_t domainGS = ON;
    uint16_t zfGreatFairy = OFF;
    uint16_t kingZoraSkip = OFF;
    uint16_t castleStormsGS = OFF;
};

class Search;
class Area;
class Oot3dLogic : public Logic {
public:

    Oot3dLogic();
    ~Oot3dLogic();

    uint16_t* GetLogicalAssignment(const ItemID& itemId);
    void ResetLogicVariables() override;
    bool Here(const RequirementFn& condition);
    bool At(const AreaID& areaId, const RequirementFn& condition);
    std::string AgeTimeStr();

    Oot3dLogicItems items;
    Oot3dLogicSettings settings;
    Oot3dLogicTricks tricks;
    uint8_t ageTime;

    Search* search;
    Area* area;
    World* world;
};
