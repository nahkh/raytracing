#ifndef _renderable_h_
#define _renderable_h_

#include "color.h"
#include "material.h"
#include "ray.h"
#include "vector.h"

enum RenderableType { RENDERABLE_PLANE, RENDERABLE_SPHERE };

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

enum TextureType { TEXTURE_NONE, TEXTURE_CHECKERED };

typedef enum TextureType TextureType;

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
  union {
    CheckeredTexture as_checkered_texture;
  };
  Material* material;
};

typedef struct Renderable Renderable;

Renderable renderable_make_plane(Vector, double);

Renderable renderable_make_sphere(Vector, double);

void renderable_set_checkered_scale(Renderable*, double);
void renderable_set_material(Renderable*, Material*);

Color renderable_get_color_at(Renderable*, Vector);
int renderable_is_reflective(Renderable*);

double renderable_get_reflectivity(Renderable*);

#endif