// This file holds functions for specific item filling operations to OoT3D. The
// general fill functionality can be found in source/fill.cpp

#include "oot3d_world.hpp"

#include "../utility/string_util.hpp"
#include "../utility/pool_functions.hpp"

#include <iostream>

#define VALID_REQUIREMENT(err, reqStr) if (err != RequirementError::NONE) {std::cout << errorToName(err) << " encountered during \n\"" << reqStr << "\"" << std::endl; return WorldBuildingError::BAD_REQUIREMENT;}

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
    if (settings["shopsanity"] == "off")
    {
        SetTheseLocationsAsVanilla(OOT3D_LOCATIONS_LAMDA({return location->categories.count(Oot3dLocationCategory::Shop);}));
    }

    // Set prices for locations with placed items
    for (auto& [locationId, location] : locations)
    {
        auto& currentItem = itemTable[location->GetCurrentItem().GetID()];
        if (currentItem.GetType() == ItemType::Shop)
        {
            ((Oot3dLocation*)location.get())->SetPrice(currentItem.GetPrice());
        }
    }

    // Modify requirements for shop locations based on what item is there and what
    // the price is
    for (auto& [areaId, area] : areas)
    {
        for (auto &locAccess : area->locations)
        {
            auto location = (Oot3dLocation*) locAccess.location;
            if (location->categories.count(Oot3dLocationCategory::Shop))
            {
                std::vector<std::string> reqStrs;
                auto price = location->GetPrice();
                if (price > 500)
                {
                    reqStrs.push_back("Tycoons_Wallet");
                }
                else if (price > 200)
                {
                    reqStrs.push_back("Giants_Wallet");
                }
                else if (price > 99)
                {
                    reqStrs.push_back("Adults_Wallet");
                }

                auto item = location->GetCurrentItem().GetID();
                // Need a bottle to buy logically relevant bottle items
                if (IsAnyOf(item, OOT3D_BUY_BLUE_FIRE, OOT3D_BUY_BOTTLE_BUG, OOT3D_BUY_FISH, OOT3D_BUY_FAIRYS_SPIRIT))
                {
                    reqStrs.push_back("has_bottle");
                }
                // If bombchus in logic, need to have found chus to buy; if not just need bomb bag
                else if (IsAnyOf(item, OOT3D_BUY_BOMBCHU_5, OOT3D_BUY_BOMBCHU_10, OOT3D_BUY_BOMBCHU_20))
                {
                    std::string reqStr = "(not bombchus_in_logic and Bombs) or (bombchus_in_logic and found_bombchus)";
                    if (!reqStrs.empty())
                    {
                        reqStr = '(' + reqStr + ')';
                    }
                    reqStrs.push_back(reqStr);
                }

                std::string totalReqStr = Utility::Str::merge(reqStrs, std::string(" and "));
                if (totalReqStr != "")
                {
                    // Add the new requirements to the location access' requirements object
                    Requirement currentReq = locAccess.requirement;
                    Requirement newReq;
                    RequirementError err = ParseRequirementString(totalReqStr, newReq, logicHelpers, settings, locAccess.area->GetID(), GetTypeString(), this);
                    VALID_REQUIREMENT(err, totalReqStr);
                    locAccess.requirement = {RequirementType::AND, {currentReq, newReq}};
                }
            }
        }
    }

    return WorldBuildingError::NONE;
}
