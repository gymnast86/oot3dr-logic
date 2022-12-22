// This file holds functions for specific item filling operations to OoT3D. The
// general fill functionality can be found in source/fill.cpp

#include "oot3d_world.hpp"

WorldBuildingError Oot3dWorld::PlaceHardcodedItems()
{
    // Hardcoded vanilla locations
    std::list<LocationID> vanillaLocations = {
        LocationID::Oot3dGanon,
        LocationID::Oot3dHCZeldasLetter,
        LocationID::Oot3dDeliverRutosLetter,
        LocationID::Oot3dBigPoeKill,
        LocationID::Oot3dPierre,
        LocationID::Oot3dBugRock,
        LocationID::Oot3dBugShrub,
        LocationID::Oot3dWanderingBugs,
        LocationID::Oot3dMarketBombchuBowlingBombchus,
        LocationID::Oot3dBlueFire,
        LocationID::Oot3dLoneFish,
        LocationID::Oot3dFishGroup,
        LocationID::Oot3dNutPot,
        LocationID::Oot3dNutCrate,
        LocationID::Oot3dStickPot,
        LocationID::Oot3dDekuBabaSticks,
        LocationID::Oot3dDekuBabaNuts,
        LocationID::Oot3dButterflyFairy,
        LocationID::Oot3dFreeFairies,
        LocationID::Oot3dWallFairy,
        LocationID::Oot3dFairyPot,
        LocationID::Oot3dBeanPlantFairy,
        LocationID::Oot3dGossipStoneFairy,
    };

    for (auto& locationId : vanillaLocations)
    {
        locations[locationId]->SetVanillaItemAsCurrentItem();
    }

    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::FillOwnDungeonItems()
{
    

    return WorldBuildingError::NONE;
}

WorldBuildingError Oot3dWorld::FillShopItems()
{
    return WorldBuildingError::NONE;
}
