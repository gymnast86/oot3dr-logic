#pragma once

#include <string>

enum class ItemID : uint32_t
{
    NONE,
    KokiriSword,
    MasterSword,
    GiantsKnife,
    BiggoronsSword,
    DekuShield,
    HylianShield,
    MirrorShield,
    GoronTunic,
    ZoraTunic,
    IronBoots,
    HoverBoots,
    Boomerang,
    LensOfTruth,
    MegatonHammer,
    ShardOfAgony,
    DinsFire,
    FaroresWind,
    NayrusLove,
    FireArrows,
    IceArrows,
    LightArrows,
    GerudoToken,
    MagicBean,
    MagicBeanPack,
    DoubleDefense,
    WeirdEgg,
    Cucco,
    ZeldasLetter,
    KeatonMask,
    SkullMask,
    SpookyMask,
    BunnyHood,
    GoronMask,
    ZoraMask,
    GerudoMask,
    MaskOfTruth,
    PocketEgg,
    PocketCucco,
    Cojiro,
    OddMushroom,
    OddPoultice,
    PoachersSaw,
    BrokenGoronsSword,
    Prescription,
    EyeballFrog,
    Eyedrops,
    ClaimCheck,
    GoldSkulltulaToken,
    ProgressiveHookshot,
    ProgressiveStrengthUpgrade,
    ProgressiveBombBag,
    ProgressiveBow,
    ProgressiveSlingshot,
    ProgressiveWallet,
    ProgressiveScale,
    ProgressiveNutCapacity,
    ProgressiveStickCapacity,
    ProgressiveBombchus,
    ProgressiveMagicMeter,
    ProgressiveOcarina,
    ProgressiveGoronSword,
    EmptyBottle,
    BottleWithMilk,
    BottleWithRedPotion,
    BottleWithGreenPotion,
    BottleWithBluePotion,
    BottleWithFairy,
    BottleWithFish,
    BottleWithBlueFire,
    BottleWithBugs,
    BottleWithPoe,
    RutosLetter,
    BottleWithBigPoe,
    ZeldasLullaby,
    EponasSong,
    SariasSong,
    SunsSong,
    SongOfTime,
    SongOfStorms,
    MinuetOfForest,
    BoleroOfFire,
    SerenadeOfWater,
    RequiemOfSpirit,
    NocturneOfShadow,
    PreludeOfLight,
    DekuTreeMap,
    DodongosCavernMap,
    JabuJabusBellyMap,
    ForesTempleMap,
    FireTempleMap,
    WaterTempleMap,
    SpiritTempleMap,
    ShadowTempleMap,
    BottomOfTheWellMap,
    IceCavernMap,
    DekuTreeCompass,
    DodongosCavernCompass,
    JabuJabusBellyCompass,
    ForesTempleCompass,
    FireTempleCompass,
    WaterTempleCompass,
    SpiritTempleCompass,
    ShadowTempleCompass,
    BottomOfTheWellCompass,
    IceCavernCompass,
    ForestTempleBossKey,
    FireTempleBossKey,
    WaterTempleBossKey,
    SpiritTempleBossKey,
    ShadowTempleBossKey,
    GanonsCastleBossKey,
    ForestTempleSmallKey,
    FireTempleSmallKey,
    WaterTempleSmallKey,
    SpiritTempleSmallKey,
    ShadowTempleSmallKey,
    BottomOfTheWellSmallKey,
    GerudoTrainingGroundSmallKey,
    GerudoFortressSmallKey,
    GanonsCastleSmallKey,
    ChestGameSmallKey,
    KokiriEmerald,
    GoronRuby,
    ZoraSapphire,
    ForestMedallion,
    FireMedallion,
    WaterMedallion,
    SpiritMedallion,
    ShadowMedallion,
    LightMedallion,
    RecoveryHeart,
    GreenRupee,
    BlueRupee,
    RedRupee,
    PurpleRupee,
    HugeRupee,
    PieceOfHeart,
    HeartContainer,
    IceTrap,
    Milk,
    Bombs5,
    Bombs10,
    Bombs20,
    Bombchus5,
    Bombchus10,
    Bombchus20,
    BombchuDrop,
    Arrows5,
    Arrows10,
    Arrows30,
    DekuNuts5,
    DekuNuts10,
    DekuSeeds30,
    DekuStick1,
    RedPotionRefill,
    GreenPotionRefill,
    BluePotionRefill,
    TreasureGameHeart,
    TreasureGameGreenRupee,
    BuyDekuNut5,
    BuyArrows30,
    BuyArrows50,
    BuyBombs525,
    BuyDekuNut10,
    BuyDekuStick1,
    BuyBombs10,
    BuyFish,
    BuyRedPotion30,
    BuyGreenPotion,
    BuyBluePotion,
    BuyHylianShield,
    BuyDekuShield,
    BuyGoronTunic,
    BuyZoraTunic,
    BuyHeart,
    BuyBombchu10,
    BuyBombchu20,
    BuyBombchu5,
    BuyDekuSeeds30,
    SoldOut,
    BuyBlueFire,
    BuyBottleBug,
    BuyPoe,
    BuyFairysSpirit,
    BuyArrows10,
    BuyBombs20,
    BuyBombs30,
    BuyBombs535,
    BuyRedPotion40,
    BuyRedPotion50,
    // Events
    Epona,
    LinksCow,
    Bonooru,
    TriforcePiece,
    TimeTravel,
    ScarecrowSong,
    Triforce,
    ForestTrialClear,
    FireTrialClear,
    WaterTrialClear,
    ShadowTrialClear,
    SpiritTrialClear,
    LightTrialClear,
    DekuStickDrop,
    DekuNutDrop,
    BlueFire,
    Fairy,
    Fish,
    Bugs,
    BigPoe,
    DekuTreeClear,
    WaterTempleClear,
    ShowedMidoSwordAndShield,
    DrainWell,
    DampesWindmillAccess,
    GoronCityChildFire,
    GCWoodsWarpOpen,
    StopGCRollingGoronAsAdult,
    KingZoraThawed,
    Hint,
    INVALID,
};

ItemID NameToItemID(const std::string& name);

class World;
class Item {
public:

    Item();
    Item(const ItemID& id_, World* world_);
    Item(const ItemID& id_, std::string name_, World* world_);
    ~Item();

    ItemID GetID() const;
    std::string GetName() const;
    World* GetWorld() const;
    int GetWorldID() const;

    bool operator==(const Item& rhs) const;
    bool operator<(const Item& rhs) const;

    ItemID id = ItemID::INVALID;
    std::string name = "";
    World* world = nullptr;
    int worldId = -1;
};

// inject specialization of std::hash<Item> into the std namespace
// taken from: https://en.cppreference.com/w/cpp/utility/hash
template<>
struct std::hash<Item>
{
    size_t operator()(Item const& i) const noexcept
    {
        size_t h1 = std::hash<ItemID>{}(i.GetID());
        size_t h2 = std::hash<int>{}(i.GetWorldID());
        return h1 ^ (h2 << 16);
    }
};