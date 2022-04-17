#ifndef _ray_h_
#define _ray_h_

#include "vector.h"

struct Ray {
    Vector pos;
    Vector dir;
};

typedef struct Ray Ray;


Ray ray_make(Vector pos, Vector dir);

#endif