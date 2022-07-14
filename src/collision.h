#ifndef _collision_h_
#define _collision_h_

#include "ray.h"
#include "renderable.h"
#include "vector.h"

#define MIN_COLLISION_DISTANCE 0.5

struct Collision {
  int hit;
  double distance;
  Vector pos;
  Vector normal;
};

typedef struct Collision Collision;

Collision calculate_collision(Renderable, Ray);

extern const Collision COLLISION_MISS;

#endif