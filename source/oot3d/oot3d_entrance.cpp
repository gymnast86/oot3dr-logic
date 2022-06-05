#include "oot3d_entrance.hpp"

Oot3dEntrance::Oot3dEntrance()
{

}

Oot3dEntrance::Oot3dEntrance(const AreaID& parentArea_, const AreaID& connectedArea_, RequirementFn& requirement_, World* world_)
{
    parentArea = parentArea_;
    connectedArea = connectedArea_;
    requirement = requirement_;
    world = world_;
    originalName = AreaIDToName(parentArea) + " -> " + AreaIDToName(connectedArea);
}

Oot3dEntrance::~Oot3dEntrance()
{

}
