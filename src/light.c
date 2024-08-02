#include "light.h"

LightSource light_source_make_global(Color color) {
  return (LightSource){LIGHT_SOURCE_GLOBAL, 0, color, {{}}};
}

LightSource light_source_make_directional(Color color, Vector direction) {
  Vector temp;

  vector_scale(&direction, -1, &temp);
  vector_normalize(&temp);
  return (LightSource){LIGHT_SOURCE_DIRECTIONAL, 1, color, {{temp}}};
}

LightSource light_source_make_point(Color color, Vector point) {
  return (LightSource){LIGHT_SOURCE_POINT, 1, color, {{point}}};
}

Vector get_direction_to(LightSource light_source, Vector point) {
  Vector temp;

  switch (light_source.type) {
    case LIGHT_SOURCE_DIRECTIONAL:
      return light_source.as_directional.direction;
    case LIGHT_SOURCE_POINT:
      vector_subtract(&(light_source.as_point.position), &point, &temp);
      vector_normalize(&temp);
      return temp;
    default:
      return VECTOR_Y;
  }
}