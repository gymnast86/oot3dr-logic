#include "item.hpp"
#include "world.hpp"

#include <unordered_map>

ItemID NameToItemID(const std::string& name)
{
  	static std::unordered_map<std::string, ItemID> nameItemMap = {
        {"NONE", ItemID::NONE},
        {"Kokiri_Sword", ItemID::KokiriSword},
        {"Master_Sword", ItemID::MasterSword},
        {"Giants_Knife", ItemID::GiantsKnife},
        {"Biggorons_Sword", ItemID::BiggoronsSword},
        {"Deku_Shield", ItemID::DekuShield},
        {"Hylian_Shield", ItemID::HylianShield},
        {"Mirror_Shield", ItemID::MirrorShield},
        {"Goron_Tunic", ItemID::GoronTunic},
        {"Zora_Tunic", ItemID::ZoraTunic},
        {"Iron_Boots", ItemID::IronBoots},
        {"Hover_Boots", ItemID::HoverBoots},
        {"Boomerang", ItemID::Boomerang},
        {"Lens_of_Truth", ItemID::LensOfTruth},
        {"Megaton_Hammer", ItemID::MegatonHammer},
        {"Shard_of_Agony", ItemID::ShardOfAgony},
        {"Dins_Fire", ItemID::DinsFire},
        {"Farores_Wind", ItemID::FaroresWind},
        {"Nayrus_Love", ItemID::NayrusLove},
        {"Fire_Arrows", ItemID::FireArrows},
        {"Ice_Arrows", ItemID::IceArrows},
        {"Light_Arrows", ItemID::LightArrows},
        {"Gerudo_Token", ItemID::GerudoToken},
        {"Magic_Bean", ItemID::MagicBean},
        {"Magic_Bean_Pack", ItemID::MagicBeanPack},
        {"Double_Defense", ItemID::DoubleDefense},
        {"Weird_Egg", ItemID::WeirdEgg},
        {"Cucco", ItemID::Cucco},
        {"Zeldas_Letter", ItemID::ZeldasLetter},
        {"Keaton_Mask", ItemID::KeatonMask},
        {"Skull_Mask", ItemID::SkullMask},
        {"Spooky_Mask", ItemID::SpookyMask},
        {"Bunny_Hood", ItemID::BunnyHood},
        {"Goron_Mask", ItemID::GoronMask},
        {"Zora_Mask", ItemID::ZoraMask},
        {"Gerudo_Mask", ItemID::GerudoMask},
        {"Mask_of_Truth", ItemID::MaskOfTruth},
        {"Pocket_Egg", ItemID::PocketEgg},
        {"Pocket_Cucco", ItemID::PocketCucco},
        {"Cojiro", ItemID::Cojiro},
        {"Odd_Mushroom", ItemID::OddMushroom},
        {"Odd_Poultice", ItemID::OddPoultice},
        {"Poachers_Saw", ItemID::PoachersSaw},
        {"Broken_Gorons_Sword", ItemID::BrokenGoronsSword},
        {"Prescription", ItemID::Prescription},
        {"Eyeball_Frog", ItemID::EyeballFrog},
        {"Eyedrops", ItemID::Eyedrops},
        {"Worlds_Finest_Eyedrops", ItemID::Eyedrops},
        {"Claim_Check", ItemID::ClaimCheck},
        {"Gold_Skulltula_Token", ItemID::GoldSkulltulaToken},
        {"Progressive_Hookshot", ItemID::ProgressiveHookshot},
        {"Progressive_Strength_Upgrade", ItemID::ProgressiveStrengthUpgrade},
        {"Progressive_Bomb_Bag", ItemID::ProgressiveBombBag},
        {"Bomb_Bag", ItemID::ProgressiveBombBag},
        {"Progressive_Bow", ItemID::ProgressiveBow},
        {"Bow", ItemID::ProgressiveBow},
        {"Progressive_Slingshot", ItemID::ProgressiveSlingshot},
        {"Slingshot", ItemID::ProgressiveSlingshot},
        {"Progressive_Wallet", ItemID::ProgressiveWallet},
        {"Progressive_Scale", ItemID::ProgressiveScale},
        {"Progressive_Nut_Capacity", ItemID::ProgressiveNutCapacity},
        {"Progressive_Stick_Capacity", ItemID::ProgressiveStickCapacity},
        {"Progressive_Bombchus", ItemID::ProgressiveBombchus},
        {"Bombchus", ItemID::ProgressiveBombchus},
        {"Progressive_Magic_Meter", ItemID::ProgressiveMagicMeter},
        {"Magic_Meter", ItemID::ProgressiveMagicMeter},
        {"Progressive_Ocarina", ItemID::ProgressiveOcarina},
        {"Ocarina", ItemID::ProgressiveOcarina},
        {"Progressive_Goron_Sword", ItemID::ProgressiveGoronSword},
        {"Empty_Bottle", ItemID::EmptyBottle},
        {"Bottle_with_Milk", ItemID::BottleWithMilk},
        {"Bottle_with_Red_Potion", ItemID::BottleWithRedPotion},
        {"Bottle_with_Green_Potion", ItemID::BottleWithGreenPotion},
        {"Bottle_with_Blue_Potion", ItemID::BottleWithBluePotion},
        {"Bottle_with_Fairy", ItemID::BottleWithFairy},
        {"Bottle_with_Fish", ItemID::BottleWithFish},
        {"Bottle_with_Blue_Fire", ItemID::BottleWithBlueFire},
        {"Bottle_with_Bugs", ItemID::BottleWithBugs},
        {"Bottle_with_Poe", ItemID::BottleWithPoe},
        {"Rutos_Letter", ItemID::RutosLetter},
        {"Bottle_with_Big_Poe", ItemID::BottleWithBigPoe},
        {"Zeldas_Lullaby", ItemID::ZeldasLullaby},
        {"Eponas_Song", ItemID::EponasSong},
        {"Sarias_Song", ItemID::SariasSong},
        {"Suns_Song", ItemID::SunsSong},
        {"Song_of_Time", ItemID::SongOfTime},
        {"Song_of_Storms", ItemID::SongOfStorms},
        {"Minuet_of_Forest", ItemID::MinuetOfForest},
        {"Bolero_of_Fire", ItemID::BoleroOfFire},
        {"Serenade_of_Water", ItemID::SerenadeOfWater},
        {"Requiem_of_Spirit", ItemID::RequiemOfSpirit},
        {"Nocturne_of_Shadow", ItemID::NocturneOfShadow},
        {"Prelude_of_Light", ItemID::PreludeOfLight},
        {"Deku_Tree_Map", ItemID::DekuTreeMap},
        {"Dodongos_Cavern_Map", ItemID::DodongosCavernMap},
        {"Jabu_Jabus_Belly_Map", ItemID::JabuJabusBellyMap},
        {"Forest_Temple_Map", ItemID::ForesTempleMap},
        {"Fire_Temple_Map", ItemID::FireTempleMap},
        {"Water_Temple_Map", ItemID::WaterTempleMap},
        {"Spirit_Temple_Map", ItemID::SpiritTempleMap},
        {"Shadow_Temple_Map", ItemID::ShadowTempleMap},
        {"Bottom_of_the_Well_Map", ItemID::BottomOfTheWellMap},
        {"Ice_Cavern_Map", ItemID::IceCavernMap},
        {"Deku_Tree_Compass", ItemID::DekuTreeCompass},
        {"Dodongos_Cavern_Compass", ItemID::DodongosCavernCompass},
        {"Jabu_Jabus_Belly_Compass", ItemID::JabuJabusBellyCompass},
        {"Forest_Temple_Compass", ItemID::ForesTempleCompass},
        {"Fire_Temple_Compass", ItemID::FireTempleCompass},
        {"Water_Temple_Compass", ItemID::WaterTempleCompass},
        {"Spirit_Temple_Compass", ItemID::SpiritTempleCompass},
        {"Shadow_Temple_Compass", ItemID::ShadowTempleCompass},
        {"Bottom_of_the_Well_Compass", ItemID::BottomOfTheWellCompass},
        {"Ice_Cavern_Compass", ItemID::IceCavernCompass},
        {"Forest_Temple_Boss_Key", ItemID::ForestTempleBossKey},
        {"Fire_Temple_Boss_Key", ItemID::FireTempleBossKey},
        {"Water_Temple_Boss_Key", ItemID::WaterTempleBossKey},
        {"Spirit_Temple_Boss_Key", ItemID::SpiritTempleBossKey},
        {"Shadow_Temple_Boss_Key", ItemID::ShadowTempleBossKey},
        {"Ganons_Castle_Boss_Key", ItemID::GanonsCastleBossKey},
        {"Forest_Temple_Small_Key", ItemID::ForestTempleSmallKey},
        {"Fire_Temple_Small_Key", ItemID::FireTempleSmallKey},
        {"Water_Temple_Small_Key", ItemID::WaterTempleSmallKey},
        {"Spirit_Temple_Small_Key", ItemID::SpiritTempleSmallKey},
        {"Shadow_Temple_Small_Key", ItemID::ShadowTempleSmallKey},
        {"Bottom_of_the_Well_Small_Key", ItemID::BottomOfTheWellSmallKey},
        {"Gerudo_Training_Ground_Small_Key", ItemID::GerudoTrainingGroundSmallKey},
        {"Thieves_Hideout_Small_Key", ItemID::GerudoFortressSmallKey},
        {"Ganons_Castle_Small_Key", ItemID::GanonsCastleSmallKey},
        {"Chest_Game_Small_Key", ItemID::ChestGameSmallKey},
        {"Kokiri_Emerald", ItemID::KokiriEmerald},
        {"Goron_Ruby", ItemID::GoronRuby},
        {"Zora_Sapphire", ItemID::ZoraSapphire},
        {"Forest_Medallion", ItemID::ForestMedallion},
        {"Fire_Medallion", ItemID::FireMedallion},
        {"Water_Medallion", ItemID::WaterMedallion},
        {"Spirit_Medallion", ItemID::SpiritMedallion},
        {"Shadow_Medallion", ItemID::ShadowMedallion},
        {"Light_Medallion", ItemID::LightMedallion},
        {"Recovery_Heart", ItemID::RecoveryHeart},
        {"Green_Rupee", ItemID::GreenRupee},
        {"Blue_Rupee", ItemID::BlueRupee},
        {"Red_Rupee", ItemID::RedRupee},
        {"Purple_Rupee", ItemID::PurpleRupee},
        {"Huge_Rupee", ItemID::HugeRupee},
        {"Piece_of_Heart", ItemID::PieceOfHeart},
        {"Heart_Container", ItemID::HeartContainer},
        {"Ice_Trap", ItemID::IceTrap},
        {"Milk", ItemID::Milk},
        {"Bombs_5", ItemID::Bombs5},
        {"Bombs_10", ItemID::Bombs10},
        {"Bombs_20", ItemID::Bombs20},
        {"Bombchus_5", ItemID::Bombchus5},
        {"Bombchus_10", ItemID::Bombchus10},
        {"Bombchus_20", ItemID::Bombchus20},
        {"Bombchu_Drop", ItemID::BombchuDrop},
        {"Arrows_5", ItemID::Arrows5},
        {"Arrows_10", ItemID::Arrows10},
        {"Arrows_30", ItemID::Arrows30},
        {"Deku_Nuts_5", ItemID::DekuNuts5},
        {"Deku_Nuts_10", ItemID::DekuNuts10},
        {"Deku_Seeds_30", ItemID::DekuSeeds30},
        {"Deku_Stick_1", ItemID::DekuStick1},
        {"Red_Potion_Refill", ItemID::RedPotionRefill},
        {"Green_Potion_Refill", ItemID::GreenPotionRefill},
        {"Blue_Potion_Refill", ItemID::BluePotionRefill},
        {"Treasure_Game_Heart", ItemID::TreasureGameHeart},
        {"Treasure_Game_Green_Rupee", ItemID::TreasureGameGreenRupee},
        {"Buy_Deku_Nut_5", ItemID::BuyDekuNut5},
        {"Buy_Arrows_30", ItemID::BuyArrows30},
        {"Buy_Arrows_50", ItemID::BuyArrows50},
        {"Buy_Bombs_5_25", ItemID::BuyBombs525},
        {"Buy_Deku_Nut_10", ItemID::BuyDekuNut10},
        {"Buy_Deku_Stick_1", ItemID::BuyDekuStick1},
        {"Buy_Bombs_10", ItemID::BuyBombs10},
        {"Buy_Fish", ItemID::BuyFish},
        {"Buy_Red_Potion_30", ItemID::BuyRedPotion30},
        {"Buy_Green_Potion", ItemID::BuyGreenPotion},
        {"Buy_Blue_Potion", ItemID::BuyBluePotion},
        {"Buy_Hylian_Shield", ItemID::BuyHylianShield},
        {"Buy_Deku_Shield", ItemID::BuyDekuShield},
        {"Buy_Goron_Tunic", ItemID::BuyGoronTunic},
        {"Buy_Zora_Tunic", ItemID::BuyZoraTunic},
        {"Buy_Heart", ItemID::BuyHeart},
        {"Buy_Bombchu_10", ItemID::BuyBombchu10},
        {"Buy_Bombchu_20", ItemID::BuyBombchu20},
        {"Buy_Bombchu_5", ItemID::BuyBombchu5},
        {"Buy_Deku_Seeds_30", ItemID::BuyDekuSeeds30},
        {"Sold_Out", ItemID::SoldOut},
        {"Buy_Blue_Fire", ItemID::BuyBlueFire},
        {"Buy_Bottle_Bug", ItemID::BuyBottleBug},
        {"Buy_Poe", ItemID::BuyPoe},
        {"Buy_Fairys_Spirit", ItemID::BuyFairysSpirit},
        {"Buy_Arrows_10", ItemID::BuyArrows10},
        {"Buy_Bombs_20", ItemID::BuyBombs20},
        {"Buy_Bombs_30", ItemID::BuyBombs30},
        {"Buy_Bombs_5_35", ItemID::BuyBombs535},
        {"Buy_Red_Potion_40", ItemID::BuyRedPotion40},
        {"Buy_Red_Potion_50", ItemID::BuyRedPotion50},
        {"Epona", ItemID::Epona},
        {"Links_Cow", ItemID::LinksCow},
        {"Bonooru", ItemID::Bonooru},
        {"Triforce_Piece", ItemID::TriforcePiece},
        {"Time_Travel", ItemID::TimeTravel},
        {"Scarecrow_Song", ItemID::ScarecrowSong},
        {"Triforce", ItemID::Triforce},
        {"Water_Temple_Clear", ItemID::WaterTempleClear},
        {"Forest_Trial_Clear", ItemID::ForestTrialClear},
        {"Fire_Trial_Clear", ItemID::FireTrialClear},
        {"Water_Trial_Clear", ItemID::WaterTrialClear},
        {"Shadow_Trial_Clear", ItemID::ShadowTrialClear},
        {"Spirit_Trial_Clear", ItemID::SpiritTrialClear},
        {"Light_Trial_Clear", ItemID::LightTrialClear},
        {"Deku_Stick_Drop", ItemID::DekuStickDrop},
        {"Deku_Nut_Drop", ItemID::DekuNutDrop},
        {"Blue_Fire", ItemID::BlueFire},
        {"Fairy", ItemID::Fairy},
        {"Fish", ItemID::Fish},
        {"Bugs", ItemID::Bugs},
        {"Big_Poe", ItemID::BigPoe},
        {"Deku_Tree_Clear", ItemID::DekuTreeClear},
        {"Water_Temple_Clear", ItemID::WaterTempleClear},
        {"Drain_Well", ItemID::DrainWell},
        {"Showed_Mido_Sword_And_Shield", ItemID::ShowedMidoSwordAndShield},
        {"Dampes_Windmill_Access", ItemID::DampesWindmillAccess},
        {"Goron_City_Child_Fire", ItemID::GoronCityChildFire},
        {"GC_Woods_Warp_Open", ItemID::GCWoodsWarpOpen},
        {"Stop_GC_Rolling_Goron_as_Adult", ItemID::StopGCRollingGoronAsAdult},
        {"Deliver_Letter", ItemID::DeliverLetter},
        {"King_Zora_Thawed", ItemID::KingZoraThawed},
        {"Carpenter_Rescue", ItemID::CarpenterRescue},
        {"GF_Gate_Open", ItemID::GFGateOpen},
        {"Sell_Big_Poe", ItemID::SellBigPoe},
        {"Kakariko_Village_Gate_Open", ItemID::KakarikoVillageGateOpen},
        {"Wake_Up_Adult_Talon", ItemID::WakeUpAdultTalon},
        {"Hint", ItemID::Hint},
  	};

  	if (nameItemMap.count(name) == 0)
  	{
  		  return ItemID::INVALID;
  	}
  	return nameItemMap.at(name);
}

Item::Item() {}

Item::Item(const ItemID& id_, World* world_) : id(id_), world(world_) {
    worldId = world->GetWorldID();
}

Item::Item(const ItemID& id_, std::string name, World* world_) : id(id_), name(std::move(name)), world(world_) {
    worldId = world->GetWorldID();
}

Item::~Item() = default;

ItemID Item::GetID() const
{
    return id;
}

std::string Item::GetName() const
{
    return name;
}

World* Item::GetWorld() const
{
    return world;
}

int Item::GetWorldID() const
{
    return worldId;
}

bool Item::operator==(const Item& rhs) const
{
		return id == rhs.id && worldId == rhs.worldId;
}

bool Item::operator<(const Item& rhs) const
{
		return (worldId == rhs.worldId) ? id < rhs.id : worldId < rhs.worldId;
}
