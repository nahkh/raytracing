#ifndef _light_h_
#define _light_h_

#include "color.h"
#include "vector.h"

enum LightSourceType {
    LIGHT_SOURCE_GLOBAL,
    LIGHT_SOURCE_DIRECTIONAL,
    LIGHT_SOURCE_POINT
};

typedef enum LightSourceType LightSourceType;

struct LightSourceDirectional {
    Vector direction;
};

typedef struct LightSourceDirectional LightSourceDirectional;

struct LightSourcePoint {
    Vector position;
};

typedef struct LightSourcePoint LightSourcePoint;

struct LightSource {
    LightSourceType type;
    int has_direction;
    Color color;
    union {
        LightSourceDirectional as_directional;
        LightSourcePoint as_point;
    };
};

typedef struct LightSource LightSource;

LightSource light_source_make_global(Color);
LightSource light_source_make_directional(Color, Vector);
LightSource light_source_make_point(Color, Vector);
Vector get_direction_to(LightSource, Vector);

#endif