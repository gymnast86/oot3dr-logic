
#include "oot3d_area.hpp"

Oot3dArea::Oot3dArea() {}

Oot3dArea::~Oot3dArea() {}

std::string Oot3dAgeTimeToString(uint8_t ageTime)
{
    std::string ageTimeStr = "";
    if (ageTime & OOT3D_CHILD_DAY)   ageTimeStr += "CD ";
    if (ageTime & OOT3D_CHILD_NIGHT) ageTimeStr += "CN ";
    if (ageTime & OOT3D_ADULT_DAY)   ageTimeStr += "AD ";
    if (ageTime & OOT3D_ADULT_NIGHT) ageTimeStr += "AN ";
    if (ageTimeStr == "") return "None";
    return ageTimeStr;
}
