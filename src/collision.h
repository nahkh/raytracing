#ifndef _collision_h_
#define _collision_h_

#include "vector.h"
#include "ray.h"
#include "renderable.h"

struct Collision {
    int hit;
    double distance;
    Vector pos;
};

typedef struct Collision Collision;

Collision calculate_collision(Renderable, Ray);

extern const Collision COLLISION_MISS;

#endif