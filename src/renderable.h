#ifndef _renderable_h_
#define _renderable_h_

#include "vector.h"
#include "ray.h"
#include "color.h"

enum RenderableType {
    RENDERABLE_PLANE,
    RENDERABLE_SPHERE
};

typedef enum RenderableType RenderableType;

struct RenderablePlane {
    Vector normal;
    double distance_to_origin;
};

typedef struct RenderablePlane RenderablePlane;

struct RenderableSphere {
    Vector position;
    double radius;
};

typedef struct RenderableSphere RenderableSphere;

enum TextureType {
    TEXTURE_SOLID,
    TEXTURE_CHECKERED
};

typedef enum TextureType TextureType;

typedef Color SolidTexture;

struct CheckeredTexture {
    double scale;
};

typedef struct CheckeredTexture CheckeredTexture;

struct Renderable {
    RenderableType type;
    union {
        RenderablePlane as_plane;
        RenderableSphere as_sphere;
    };
    TextureType texture_type;
    double reflectivity;
    union {
        SolidTexture as_solid_texture;
        CheckeredTexture as_checkered_texture;
    };
};

typedef struct Renderable Renderable;

Renderable renderable_make_plane(Vector, double);

Renderable renderable_make_sphere(Vector, double);

void renderable_set_solid_color(Renderable*, int, int, int);
void renderable_set_checkered_scale(Renderable*, double);
void renderable_set_reflectivity(Renderable*, double);

Color renderable_get_color_at(Renderable, Vector);

#endif