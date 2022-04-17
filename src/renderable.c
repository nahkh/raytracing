#include "renderable.h"


Renderable renderable_make_plane(Vector normal, double distance) {
    return (Renderable) {RENDERABLE_PLANE, {{normal, distance}}, TEXTURE_SOLID, 0, {{0,0,0}}};
}

Renderable renderable_make_sphere(Vector position, double radius) {
    return (Renderable) {RENDERABLE_SPHERE, {{position, radius}}, TEXTURE_SOLID, 0, {{0,0,0}}};
}


void renderable_set_solid_color(Renderable* renderable, int r, int g, int b) {
    renderable->texture_type = TEXTURE_SOLID;
    renderable->as_solid_texture.r = r;
    renderable->as_solid_texture.g = g;
    renderable->as_solid_texture.b = b;
}

void renderable_set_checkered_scale(Renderable* renderable, double scale) {
    renderable->texture_type = TEXTURE_CHECKERED;
    renderable->as_checkered_texture.scale = scale;
}

void renderable_set_reflectivity(Renderable* renderable, double reflectivity) {
    renderable->reflectivity = reflectivity;
}

Color renderable_get_color_at(Renderable renderable, Vector position) {
    switch(renderable.texture_type) {
        case TEXTURE_SOLID:
            return renderable.as_solid_texture;
        case TEXTURE_CHECKERED:
            return ((int) (position.x / renderable.as_checkered_texture.scale) +
                   (int) (position.y / renderable.as_checkered_texture.scale) +
                   (int) (position.z / renderable.as_checkered_texture.scale)) % 2 ? (Color) {0,0,0} : (Color) {255, 255, 255};
        default:
            return (Color) {0,0,0};
    }
}