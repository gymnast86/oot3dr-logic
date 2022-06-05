#include "oot3d_logic.hpp"
#include "oot3d_area.hpp"
#include "../search.hpp"

#include <unordered_map>
#include <iostream>
#include <cstring>

Oot3dLogic::Oot3dLogic() {};

Oot3dLogic::~Oot3dLogic() {};

uint16_t* Oot3dLogic::GetLogicalAssignment(const ItemID& itemId)
{
    std::unordered_map<ItemID, uint16_t*> itemLogicMap = {
        {ItemID::KokiriSword, &items.kokiriSword},
        {ItemID::MasterSword, &items.masterSword},
        {ItemID::GiantsKnife, &items.giantsKnife},
        {ItemID::BiggoronsSword, &items.biggoronsSword},
        {ItemID::DekuShield, &items.dekuShield},
        {ItemID::HylianShield, &items.hylianShield},
        {ItemID::MirrorShield, &items.mirrorShield},
        {ItemID::GoronTunic, &items.goronTunic},
        {ItemID::ZoraTunic, &items.zoraTunic},
        {ItemID::IronBoots, &items.ironBoots},
        {ItemID::HoverBoots, &items.hoverBoots},
        {ItemID::Boomerang, &items.boomerang},
        {ItemID::LensOfTruth, &items.lensOfTruth},
        {ItemID::MegatonHammer, &items.megatonHammer},
        {ItemID::ShardOfAgony, &items.shardOfAgony},
        {ItemID::DinsFire, &items.dinsFire},
        {ItemID::FaroresWind, &items.faroresWind},
        {ItemID::NayrusLove, &items.nayrusLove},
        {ItemID::FireArrows, &items.fireArrows},
        {ItemID::IceArrows, &items.iceArrows},
        {ItemID::LightArrows, &items.lightArrows},
        {ItemID::GerudoToken, &items.gerudoToken},
        {ItemID::MagicBean, &items.magicBean},
        {ItemID::MagicBeanPack, &items.magicBeanPack},
        {ItemID::DoubleDefense, &items.doubleDefense},
        {ItemID::WeirdEgg, &items.weirdEgg},
        {ItemID::Cucco, &items.cucco},
        {ItemID::ZeldasLetter, &items.zeldasLetter},
        {ItemID::KeatonMask, &items.keatonMask},
        {ItemID::SkullMask, &items.skullMask},
        {ItemID::SpookyMask, &items.spookyMask},
        {ItemID::BunnyHood, &items.bunnyHood},
        {ItemID::GoronMask, &items.goronMask},
        {ItemID::ZoraMask, &items.zoraMask},
        {ItemID::GerudoMask, &items.gerudoMask},
        {ItemID::MaskOfTruth, &items.maskOfTruth},
        {ItemID::PocketEgg, &items.pocketEgg},
        {ItemID::PocketCucco, &items.pocketCucco},
        {ItemID::Cojiro, &items.cojiro},
        {ItemID::OddMushroom, &items.oddMushroom},
        {ItemID::OddPoultice, &items.oddPoultice},
        {ItemID::PoachersSaw, &items.poachersSaw},
        {ItemID::BrokenGoronsSword, &items.brokenGoronsSword},
        {ItemID::Prescription, &items.prescription},
        {ItemID::EyeballFrog, &items.eyeballFrog},
        {ItemID::Eyedrops, &items.eyedrops},
        {ItemID::ClaimCheck, &items.claimCheck},
        {ItemID::GoldSkulltulaToken, &items.goldSkulltulaToken},
        {ItemID::ProgressiveHookshot, &items.progressiveHookshot},
        {ItemID::ProgressiveStrengthUpgrade, &items.progressiveStrengthUpgrade},
        {ItemID::ProgressiveBombBag, &items.progressiveBombBag},
        {ItemID::ProgressiveBow, &items.progressiveBow},
        {ItemID::ProgressiveSlingshot, &items.progressiveSlingshot},
        {ItemID::ProgressiveWallet, &items.progressiveWallet},
        {ItemID::ProgressiveScale, &items.progressiveScale},
        {ItemID::ProgressiveNutCapacity, &items.progressiveNutCapacity},
        {ItemID::ProgressiveStickCapacity, &items.progressiveStickCapacity},
        {ItemID::ProgressiveBombchus, &items.progressiveBombchus},
        {ItemID::ProgressiveMagicMeter, &items.progressiveMagicMeter},
        {ItemID::ProgressiveOcarina, &items.progressiveOcarina},
        {ItemID::ProgressiveGoronSword, &items.progressiveGoronSword},
        {ItemID::EmptyBottle, &items.emptyBottle},
        {ItemID::BottleWithMilk, &items.emptyBottle},
        {ItemID::BottleWithRedPotion, &items.emptyBottle},
        {ItemID::BottleWithGreenPotion, &items.emptyBottle},
        {ItemID::BottleWithBluePotion, &items.emptyBottle},
        {ItemID::BottleWithFairy, &items.emptyBottle},
        {ItemID::BottleWithFish, &items.emptyBottle},
        {ItemID::BottleWithBlueFire, &items.emptyBottle},
        {ItemID::BottleWithBugs, &items.emptyBottle},
        {ItemID::BottleWithPoe, &items.emptyBottle},
        {ItemID::RutosLetter, &items.rutosLetter},
        {ItemID::BottleWithBigPoe, &items.bottleWithBigPoe},
        {ItemID::ZeldasLullaby, &items.zeldasLullaby},
        {ItemID::EponasSong, &items.eponasSong},
        {ItemID::SariasSong, &items.sariasSong},
        {ItemID::SunsSong, &items.sunsSong},
        {ItemID::SongOfTime, &items.songOfTime},
        {ItemID::SongOfStorms, &items.songOfStorms},
        {ItemID::MinuetOfForest, &items.minuetOfForest},
        {ItemID::BoleroOfFire, &items.boleroOfFire},
        {ItemID::SerenadeOfWater, &items.serenadeOfWater},
        {ItemID::RequiemOfSpirit, &items.requiemOfSpirit},
        {ItemID::NocturneOfShadow, &items.nocturneOfShadow},
        {ItemID::PreludeOfLight, &items.preludeOfLight},
        {ItemID::DekuTreeMap, &items.dekuTreeMap},
        {ItemID::DodongosCavernMap, &items.dodongosCavernMap},
        {ItemID::JabuJabusBellyMap, &items.jabuJabusBellyMap},
        {ItemID::ForestTempleMap, &items.forestTempleMap},
        {ItemID::FireTempleMap, &items.fireTempleMap},
        {ItemID::WaterTempleMap, &items.waterTempleMap},
        {ItemID::SpiritTempleMap, &items.spiritTempleMap},
        {ItemID::ShadowTempleMap, &items.shadowTempleMap},
        {ItemID::BottomOfTheWellMap, &items.bottomOfTheWellMap},
        {ItemID::IceCavernMap, &items.iceCavernMap},
        {ItemID::DekuTreeCompass, &items.dekuTreeCompass},
        {ItemID::DodongosCavernCompass, &items.dodongosCavernCompass},
        {ItemID::JabuJabusBellyCompass, &items.jabuJabusBellyCompass},
        {ItemID::ForestTempleCompass, &items.forestTempleCompass},
        {ItemID::FireTempleCompass, &items.fireTempleCompass},
        {ItemID::WaterTempleCompass, &items.waterTempleCompass},
        {ItemID::SpiritTempleCompass, &items.spiritTempleCompass},
        {ItemID::ShadowTempleCompass, &items.shadowTempleCompass},
        {ItemID::BottomOfTheWellCompass, &items.bottomOfTheWellCompass},
        {ItemID::IceCavernCompass, &items.iceCavernCompass},
        {ItemID::ForestTempleBossKey, &items.forestTempleBossKey},
        {ItemID::FireTempleBossKey, &items.fireTempleBossKey},
        {ItemID::WaterTempleBossKey, &items.waterTempleBossKey},
        {ItemID::SpiritTempleBossKey, &items.spiritTempleBossKey},
        {ItemID::ShadowTempleBossKey, &items.shadowTempleBossKey},
        {ItemID::GanonsCastleBossKey, &items.ganonsCastleBossKey},
        {ItemID::ForestTempleSmallKey, &items.forestTempleSmallKey},
        {ItemID::FireTempleSmallKey, &items.fireTempleSmallKey},
        {ItemID::WaterTempleSmallKey, &items.waterTempleSmallKey},
        {ItemID::SpiritTempleSmallKey, &items.spiritTempleSmallKey},
        {ItemID::ShadowTempleSmallKey, &items.shadowTempleSmallKey},
        {ItemID::BottomOfTheWellSmallKey, &items.bottomOfTheWellSmallKey},
        {ItemID::GerudoTrainingGroundSmallKey, &items.gerudoTrainingGroundSmallKey},
        {ItemID::ThievesHideoutSmallKey, &items.thievesHideoutSmallKey},
        {ItemID::GanonsCastleSmallKey, &items.ganonsCastleSmallKey},
        {ItemID::ChestGameSmallKey, &items.chestGameSmallKey},
        {ItemID::KokiriEmerald, &items.kokiriEmerald},
        {ItemID::GoronRuby, &items.goronRuby},
        {ItemID::ZoraSapphire, &items.zoraSapphire},
        {ItemID::ForestMedallion, &items.forestMedallion},
        {ItemID::FireMedallion, &items.fireMedallion},
        {ItemID::WaterMedallion, &items.waterMedallion},
        {ItemID::SpiritMedallion, &items.spiritMedallion},
        {ItemID::ShadowMedallion, &items.shadowMedallion},
        {ItemID::LightMedallion, &items.lightMedallion},
        {ItemID::RecoveryHeart, &items.recoveryHeart},
        {ItemID::GreenRupee, &items.greenRupee},
        {ItemID::BlueRupee, &items.blueRupee},
        {ItemID::RedRupee, &items.redRupee},
        {ItemID::PurpleRupee, &items.purpleRupee},
        {ItemID::HugeRupee, &items.hugeRupee},
        {ItemID::PieceOfHeart, &items.pieceOfHeart},
        {ItemID::HeartContainer, &items.heartContainer},
        {ItemID::IceTrap, &items.iceTrap},
        {ItemID::Milk, &items.milk},
        {ItemID::Bombs5, &items.bombs5},
        {ItemID::Bombs10, &items.bombs10},
        {ItemID::Bombs20, &items.bombs20},
        {ItemID::Bombchus5, &items.bombchus5},
        {ItemID::Bombchus10, &items.bombchus10},
        {ItemID::Bombchus20, &items.bombchus20},
        {ItemID::BombchuDrop, &items.bombchuDrop},
        {ItemID::Arrows5, &items.arrows5},
        {ItemID::Arrows10, &items.arrows10},
        {ItemID::Arrows30, &items.arrows30},
        {ItemID::DekuNuts5, &items.dekuNuts5},
        {ItemID::DekuNuts10, &items.dekuNuts10},
        {ItemID::DekuSeeds30, &items.dekuSeeds30},
        {ItemID::DekuStick1, &items.dekuStick1},
        {ItemID::RedPotionRefill, &items.redPotionRefill},
        {ItemID::GreenPotionRefill, &items.greenPotionRefill},
        {ItemID::BluePotionRefill, &items.bluePotionRefill},
        {ItemID::TreasureGameHeart, &items.treasureGameHeart},
        {ItemID::TreasureGameGreenRupee, &items.treasureGameGreenRupee},
        {ItemID::BuyDekuNut5, &items.buyDekuNut5},
        {ItemID::BuyArrows30, &items.buyArrows30},
        {ItemID::BuyArrows50, &items.buyArrows50},
        {ItemID::BuyBombs525, &items.buyBombs525},
        {ItemID::BuyDekuNut10, &items.buyDekuNut10},
        {ItemID::BuyDekuStick1, &items.buyDekuStick1},
        {ItemID::BuyBombs10, &items.buyBombs10},
        {ItemID::BuyFish, &items.buyFish},
        {ItemID::BuyRedPotion30, &items.buyRedPotion30},
        {ItemID::BuyGreenPotion, &items.buyGreenPotion},
        {ItemID::BuyBluePotion, &items.buyBluePotion},
        {ItemID::BuyHylianShield, &items.buyHylianShield},
        {ItemID::BuyDekuShield, &items.buyDekuShield},
        {ItemID::BuyGoronTunic, &items.buyGoronTunic},
        {ItemID::BuyZoraTunic, &items.buyZoraTunic},
        {ItemID::BuyHeart, &items.buyHeart},
        {ItemID::BuyBombchu10, &items.buyBombchu10},
        {ItemID::BuyBombchu20, &items.buyBombchu20},
        {ItemID::BuyBombchu5, &items.buyBombchu5},
        {ItemID::BuyDekuSeeds30, &items.buyDekuSeeds30},
        {ItemID::SoldOut, &items.soldOut},
        {ItemID::BuyBlueFire, &items.buyBlueFire},
        {ItemID::BuyBottleBug, &items.buyBottleBug},
        {ItemID::BuyPoe, &items.buyPoe},
        {ItemID::BuyFairysSpirit, &items.buyFairysSpirit},
        {ItemID::BuyArrows10, &items.buyArrows10},
        {ItemID::BuyBombs20, &items.buyBombs20},
        {ItemID::BuyBombs30, &items.buyBombs30},
        {ItemID::BuyBombs535, &items.buyBombs535},
        {ItemID::BuyRedPotion40, &items.buyRedPotion40},
        {ItemID::BuyRedPotion50, &items.buyRedPotion50},
        // Events
        {ItemID::Epona, &items.epona},
        {ItemID::LinksCow, &items.linksCow},
        {ItemID::Bonooru, &items.bonooru},
        {ItemID::TriforcePiece, &items.triforcePiece},
        {ItemID::TimeTravel, &items.timeTravel},
        {ItemID::ScarecrowSong, &items.scarecrowSong},
        {ItemID::Triforce, &items.triforce},
        {ItemID::ForestTrialClear, &items.forestTrialClear},
        {ItemID::FireTrialClear, &items.fireTrialClear},
        {ItemID::WaterTrialClear, &items.waterTrialClear},
        {ItemID::ShadowTrialClear, &items.shadowTrialClear},
        {ItemID::SpiritTrialClear, &items.spiritTrialClear},
        {ItemID::LightTrialClear, &items.lightTrialClear},
        {ItemID::DekuStickDrop, &items.dekuStickDrop},
        {ItemID::DekuNutDrop, &items.dekuNutDrop},
        {ItemID::BlueFire, &items.blueFire},
        {ItemID::Fairy, &items.fairy},
        {ItemID::Fish, &items.fish},
        {ItemID::Bugs, &items.bugs},
        {ItemID::BigPoe, &items.bigPoe},
        {ItemID::DekuTreeClear, &items.dekuTreeClear},
        {ItemID::DodongosCavernClear, &items.dodongosCavernClear},
        {ItemID::JabuJabusBellyClear, &items.jabuJabusBellyClear},
        {ItemID::ForestTempleClear, &items.forestTempleClear},
        {ItemID::FireTempleClear, &items.fireTempleClear},
        {ItemID::WaterTempleClear, &items.waterTempleClear},
        {ItemID::SpiritTempleClear, &items.spiritTempleClear},
        {ItemID::ShadowTempleClear, &items.shadowTempleClear},
        {ItemID::ShowedMidoSwordAndShield, &items.showedMidoSwordAndShield},
        {ItemID::DrainWell, &items.drainWell},
        {ItemID::DampesWindmillAccess, &items.dampesWindmillAccess},
        {ItemID::GCDaruniasDoorOpenChild, &items.gcDaruniasDoorOpenChild},
        {ItemID::GoronCityChildFire, &items.goronCityChildFire},
        {ItemID::GCWoodsWarpOpen, &items.gcWoodsWarpOpen},
        {ItemID::StopGCRollingGoronAsAdult, &items.stopGCRollingGoronAsAdult},
        {ItemID::DeliverLetter, &items.deliverLetter},
        {ItemID::KingZoraThawed, &items.kingZoraThawed},
        {ItemID::CarpenterRescue, &items.carpenterRescue},
        {ItemID::GFGateOpen, &items.gfGateOpen},
        {ItemID::GTGGateOpen, &items.gtgGateOpen},
        {ItemID::SellBigPoe, &items.sellBigPoe},
        {ItemID::KakarikoVillageGateOpen, &items.kakarikoVillageGateOpen},
        {ItemID::WakeUpAdultTalon, &items.wakeUpAdultTalon},
        {ItemID::Hint, &items.hint},
    };

    if (itemLogicMap.count(itemId) == 0)
    {
        std::cout << "WARNING: assigned nullptr in GetLogicalAssignment for " << ItemIDToName(itemId) << std::endl;
        return nullptr;
    }
    return itemLogicMap.at(itemId);
}

void Oot3dLogic::ResetLogicVariables()
{
    memset(&items, 0, sizeof items);
}

bool Oot3dLogic::Here(const RequirementFn& condition)
{
    Oot3dLogicAgeTime oldAgeTime = ageTime;
    ageTime.childDay   = search->areaTime[area] & OOT3D_CHILD_DAY   ? 1 : 0;
    ageTime.childNight = search->areaTime[area] & OOT3D_CHILD_NIGHT ? 1 : 0;
    ageTime.adultDay   = search->areaTime[area] & OOT3D_ADULT_DAY   ? 1 : 0;
    ageTime.adultNight = search->areaTime[area] & OOT3D_CHILD_NIGHT ? 1 : 0;
    bool retVal = condition();
    ageTime = oldAgeTime;
    return retVal;
}

bool Oot3dLogic::At(const AreaID& areaId, const RequirementFn& condition)
{
    auto oldArea = area;
    area = world->areas[areaId].get();
    // return false if we haven't accessed the area yet
    if (search->areaTime[area] == OOT3D_NO_AGE_TIME)
    {
        area = oldArea;
        return false;
    }
    bool retVal = Here(condition);
    area = oldArea;
    return retVal;
}

std::string Oot3dLogic::AgeTimeStr()
{
    std::string message = "Logic.ageTime: ";
    message += ((ageTime.childDay) ? "CD " : "");
    message += ((ageTime.childNight) ? "CN " : "");
    message += ((ageTime.adultDay) ? "AD " : "");
    message += ((ageTime.adultNight) ? "AN" : "");
    return message;
}
