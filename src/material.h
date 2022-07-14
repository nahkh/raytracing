#ifndef _material_h_
#define _material_h_

#include "color.h"

struct Material {
  Color color;
  double reflectivity;
  double transparency;
  double refractive_index;
};

typedef struct Material Material;

Material* material_make(Color, double, double, double);
void material_destroy(Material*);

#endif