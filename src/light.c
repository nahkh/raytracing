#include "light.h"


LightSource light_source_make_global(Color color) {
    return (LightSource) {LIGHT_SOURCE_GLOBAL, 0, color, {{}}};
}

LightSource light_source_make_directional(Color color, Vector direction) {
    Vector temp = vector_scale(&direction, -1);
    return (LightSource) {LIGHT_SOURCE_DIRECTIONAL, 1, color, {{vector_normalize(&temp)}}};
}

LightSource light_source_make_point(Color color, Vector point) {
    return (LightSource) {LIGHT_SOURCE_POINT, 1, color, {{point}}};
}

Vector get_direction_to(LightSource light_source, Vector point) {
    Vector temp;

    switch(light_source.type) {
        case LIGHT_SOURCE_DIRECTIONAL:
            return light_source.as_directional.direction;
        case LIGHT_SOURCE_POINT:
            temp = vector_subtract(&(light_source.as_point.position), &point);
            return vector_normalize(&temp);
        default:
            return VECTOR_Y;
    }
}