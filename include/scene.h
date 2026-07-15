#ifndef SCENE_H
#define SCENE_H

#include <string>

#include "hittable_list.h"
#include "camera.h"

struct scene {
    hittable_list world;
    camera cam;
    std::string name;
};

#endif