#pragma once

#include "../entrance.hpp"

class Oot3dEntrance : public Entrance {
public:

    Oot3dEntrance();
    Oot3dEntrance(const AreaID& parentArea_, const AreaID& connectedArea_, Requirement& requirement_, World* world_);
    ~Oot3dEntrance();

};
