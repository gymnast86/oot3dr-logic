#include "oot3d_item_pool.hpp"

static ItemIDPool alwaysItems = {
    ItemID::Oot3dBiggoronsSword,
    ItemID::Oot3dBoomerang,
    ItemID::Oot3dLensOfTruth,
    ItemID::Oot3dMegatonHammer,
    ItemID::Oot3dIronBoots,
    ItemID::Oot3dGoronTunic,
    ItemID::Oot3dZoraTunic,
    ItemID::Oot3dHoverBoots,
    ItemID::Oot3dMirrorShield,
    ItemID::Oot3dShardOfAgony,
    ItemID::Oot3dFireArrows,
    ItemID::Oot3dIceArrows,
    ItemID::Oot3dLightArrows,
    ItemID::Oot3dDinsFire,
    ItemID::Oot3dFaroresWind,
    ItemID::Oot3dNayrusLove,
    ItemID::Oot3dGreenRupee,
    ItemID::Oot3dProgressiveHookshot,
    ItemID::Oot3dProgressiveHookshot,
    ItemID::Oot3dProgressiveBombBag,
    ItemID::Oot3dProgressiveBombBag,
    ItemID::Oot3dDekuShield,
    ItemID::Oot3dHylianShield,
    ItemID::Oot3dProgressiveStrengthUpgrade,
    ItemID::Oot3dProgressiveStrengthUpgrade,
    ItemID::Oot3dProgressiveStrengthUpgrade,
    ItemID::Oot3dProgressiveScale,
    ItemID::Oot3dProgressiveScale,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dRecoveryHeart,
    ItemID::Oot3dProgressiveBow,
    ItemID::Oot3dProgressiveBow,
    ItemID::Oot3dProgressiveBow,
    ItemID::Oot3dProgressiveSlingshot,
    ItemID::Oot3dProgressiveSlingshot,
    ItemID::Oot3dProgressiveSlingshot,
    ItemID::Oot3dBombs5,
    ItemID::Oot3dBombs5,
    ItemID::Oot3dBombs10,
    ItemID::Oot3dBombs20,
    ItemID::Oot3dArrows5,
    ItemID::Oot3dArrows10,
    ItemID::Oot3dArrows10,
    ItemID::Oot3dArrows10,
    ItemID::Oot3dArrows10,
    ItemID::Oot3dArrows10,
    ItemID::Oot3dProgressiveWallet,
    ItemID::Oot3dProgressiveWallet,
    ItemID::Oot3dProgressiveMagicMeter,
    ItemID::Oot3dProgressiveMagicMeter,
    ItemID::Oot3dDoubleDefense,
    ItemID::Oot3dProgressiveStickCapacity,
    ItemID::Oot3dProgressiveStickCapacity,
    ItemID::Oot3dProgressiveNutCapacity,
    ItemID::Oot3dProgressiveNutCapacity,
    ItemID::Oot3dTreasureGameHeart,

    ItemID::Oot3dZeldasLullaby,
    ItemID::Oot3dSariasSong,
    ItemID::Oot3dSunsSong,
    ItemID::Oot3dSongOfStorms,
    ItemID::Oot3dEponasSong,
    ItemID::Oot3dSongOfTime,
    ItemID::Oot3dMinuetOfForest,
    ItemID::Oot3dBoleroOfFire,
    ItemID::Oot3dSerenadeOfWater,
    ItemID::Oot3dRequiemOfSpirit,
    ItemID::Oot3dNocturneOfShadow,
    ItemID::Oot3dPreludeOfLight,

    ItemID::Oot3dRutosLetter,
    ItemID::Oot3dEmptyBottle,

    ItemID::Oot3dProgressiveOcarina,
    ItemID::Oot3dProgressiveOcarina,
    ItemID::Oot3dGerudoToken,
    ItemID::Oot3dWeirdEgg,
    ItemID::Oot3dZeldasLetter,
    ItemID::Oot3dMagicBeanPack,

    ItemID::Oot3dLightMedallion,
    ItemID::Oot3dForestMedallion,
    ItemID::Oot3dFireMedallion,
    ItemID::Oot3dWaterMedallion,
    ItemID::Oot3dSpiritMedallion,
    ItemID::Oot3dShadowMedallion,
    ItemID::Oot3dKokiriEmerald,
    ItemID::Oot3dGoronRuby,
    ItemID::Oot3dZoraSapphire,

    ItemID::Oot3dGanonsCastleBossKey,
    ItemID::Oot3dThievesHideoutSmallKey,
    ItemID::Oot3dThievesHideoutSmallKey,
    ItemID::Oot3dThievesHideoutSmallKey,
    ItemID::Oot3dThievesHideoutSmallKey,
};

ItemIDPool GenerateOot3dItemPool(SettingsMap& settings)
{
    ItemIDPool itemPool = {};

    if (settings["shuffle_kokiri_sword"] == "On")
    {
        itemPool.push_back(ItemID::Oot3dKokiriSword);
    }

    itemPool.insert(itemPool.end(), alwaysItems.begin(), alwaysItems.end());

    for (int i = 0; i < 50; i++)
    {
        itemPool.push_back(ItemID::Oot3dGoldSkulltulaToken);
    }

    return itemPool;
}
