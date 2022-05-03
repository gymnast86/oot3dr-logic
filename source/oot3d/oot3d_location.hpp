#pragma once

#include "../location.hpp"

enum class ItemLocationType {
    Base,
    Chest,
    Collectable,
    GSToken,
    GrottoScrub,
    Delayed,
    TempleReward,
    HintStone,
    OtherHint,
};

class SpoilerCollectionCheck {
public:
  SpoilerCollectionCheckType type = SpoilerCollectionCheckType::SPOILER_CHK_NONE;
  u8 scene = 0;
  u8 flag = 0;

  SpoilerCollectionCheck() {}
  SpoilerCollectionCheck(SpoilerCollectionCheckType type_, u8 scene_, u8 flag_) : type(type_), scene(scene_), flag(flag_) {}
};

class Oot3dLocation : public Location {
public:

    Oot3dLocation();



};
