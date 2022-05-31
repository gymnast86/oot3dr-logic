#include "oot3d_item_pool.hpp"

static ItemIDPool alwaysItems = {
    ItemID::BiggoronsSword,
    ItemID::Boomerang,
    ItemID::LensOfTruth,
    ItemID::MegatonHammer,
    ItemID::IronBoots,
    ItemID::GoronTunic,
    ItemID::ZoraTunic,
    ItemID::HoverBoots,
    ItemID::MirrorShield,
    ItemID::ShardOfAgony,
    ItemID::FireArrows,
    ItemID::IceArrows,
    ItemID::LightArrows,
    ItemID::DinsFire,
    ItemID::FaroresWind,
    ItemID::NayrusLove,
    ItemID::GreenRupee,
    ItemID::ProgressiveHookshot,
    ItemID::ProgressiveHookshot,
    ItemID::ProgressiveBombBag,
    ItemID::ProgressiveBombBag,
    ItemID::DekuShield,
    ItemID::HylianShield,
    ItemID::ProgressiveStrengthUpgrade,
    ItemID::ProgressiveStrengthUpgrade,
    ItemID::ProgressiveStrengthUpgrade,
    ItemID::ProgressiveScale,
    ItemID::ProgressiveScale,
    ItemID::RecoveryHeart,
    ItemID::RecoveryHeart,
    ItemID::RecoveryHeart,
    ItemID::RecoveryHeart,
    ItemID::RecoveryHeart,
    ItemID::RecoveryHeart,
    ItemID::ProgressiveBow,
    ItemID::ProgressiveBow,
    ItemID::ProgressiveBow,
    ItemID::ProgressiveSlingshot,
    ItemID::ProgressiveSlingshot,
    ItemID::ProgressiveSlingshot,
    ItemID::Bombs5,
    ItemID::Bombs5,
    ItemID::Bombs10,
    ItemID::Bombs20,
    ItemID::Arrows5,
    ItemID::Arrows10,
    ItemID::Arrows10,
    ItemID::Arrows10,
    ItemID::Arrows10,
    ItemID::Arrows10,
    ItemID::ProgressiveWallet,
    ItemID::ProgressiveWallet,
    ItemID::ProgressiveMagicMeter,
    ItemID::ProgressiveMagicMeter,
    ItemID::DoubleDefense,
    ItemID::ProgressiveStickCapacity,
    ItemID::ProgressiveStickCapacity,
    ItemID::ProgressiveNutCapacity,
    ItemID::ProgressiveNutCapacity,
    ItemID::TreasureGameHeart,

    ItemID::ZeldasLullaby,
    ItemID::SariasSong,
    ItemID::SunsSong,
    ItemID::SongOfStorms,
    ItemID::EponasSong,
    ItemID::SongOfTime,
    ItemID::MinuetOfForest,
    ItemID::BoleroOfFire,
    ItemID::SerenadeOfWater,
    ItemID::RequiemOfSpirit,
    ItemID::NocturneOfShadow,
    ItemID::PreludeOfLight,

    ItemID::RutosLetter,
    ItemID::EmptyBottle,

    ItemID::ProgressiveOcarina,
    ItemID::ProgressiveOcarina,
    ItemID::GerudoToken,
    ItemID::WeirdEgg,
    ItemID::ZeldasLetter,
    ItemID::MagicBeanPack,

    ItemID::LightMedallion,
    ItemID::ForestMedallion,
    ItemID::FireMedallion,
    ItemID::WaterMedallion,
    ItemID::SpiritMedallion,
    ItemID::ShadowMedallion,
    ItemID::KokiriEmerald,
    ItemID::GoronRuby,
    ItemID::ZoraSapphire,

    ItemID::GanonsCastleBossKey,
    ItemID::ThievesHideoutSmallKey,
    ItemID::ThievesHideoutSmallKey,
    ItemID::ThievesHideoutSmallKey,
    ItemID::ThievesHideoutSmallKey,
};

ItemIDPool GenerateOot3dItemPool(SettingsMap& settings)
{
    ItemIDPool itemPool = {};

    if (settings["shuffle_kokiri_sword"] == "On")
    {
        itemPool.push_back(ItemID::KokiriSword);
    }

    itemPool.insert(itemPool.end(), alwaysItems.begin(), alwaysItems.end());

    for (int i = 0; i < 50; i++)
    {
        itemPool.push_back(ItemID::GoldSkulltulaToken);
    }

    return itemPool;
}
