#include "renderable.h"

#include <math.h>
#include <stdlib.h>

Renderable renderable_make_plane(Vector normal, double distance) {
  return (Renderable){
      RENDERABLE_PLANE, {{normal, distance}}, TEXTURE_NONE, {{0}}, NULL};
}

Renderable renderable_make_sphere(Vector position, double radius) {
  return (Renderable){
      RENDERABLE_SPHERE, {{position, radius}}, TEXTURE_NONE, {{0}}, NULL};
}

void renderable_set_checkered_scale(Renderable* renderable, double scale) {
  renderable->texture_type = TEXTURE_CHECKERED;
  renderable->as_checkered_texture.scale = scale;
}

Color renderable_get_color_at(Renderable* renderable, Vector position) {
  switch (renderable->texture_type) {
    case TEXTURE_NONE:
      if (renderable->material != NULL) {
        return renderable->material->color;
      }
      return color_make(0, 0, 0);
    case TEXTURE_CHECKERED:
      return ((int)floor(position.x / renderable->as_checkered_texture.scale) +
              (int)floor(position.y / renderable->as_checkered_texture.scale) +
              (int)floor(position.z / renderable->as_checkered_texture.scale)) %
                     2
                 ? (Color){0, 0, 0}
                 : (Color){1, 1, 1};
    default:
      return (Color){0, 0, 0};
  }
}

int renderable_is_reflective(Renderable* renderable) {
  return renderable->material != NULL &&
         renderable->material->reflectivity > 0.0;
}

double renderable_get_reflectivity(Renderable* renderable) {
  if (renderable->material != NULL) {
    return renderable->material->reflectivity;
  } else {
    return 0.0;
  }
}

void renderable_set_material(Renderable* renderable, Material* material) {
  renderable->material = material;
};
