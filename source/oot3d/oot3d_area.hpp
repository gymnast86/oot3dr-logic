#pragma once

#include "../area.hpp"

#define OOT3D_NO_AGE_TIME 0b0000
#define OOT3D_CHILD_DAY   0b0001
#define OOT3D_CHILD_NIGHT 0b0010
#define OOT3D_ADULT_DAY   0b0100
#define OOT3D_ADULT_NIGHT 0b1000
#define OOT3D_IS_CHILD    0b0011
#define OOT3D_IS_ADULT    0b1100
#define OOT3D_ALL_TIMES   0b1111

class Oot3dArea : public Area {
public:

    Oot3dArea();
    // Oot3dArea(const AreaID& id_, const bool& timePasses_, World* world_, std::unordered_set<Event> events_, std::unordered_set<LocationAccess> locations_, std::unordered_set<std::unique_ptr<Entrance>> exits_);
    ~Oot3dArea();

    bool timePasses = false;

};

std::string Oot3dAgeTimeToString(uint8_t ageTime);
