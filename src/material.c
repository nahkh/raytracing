#include "material.h"

#include <stdlib.h>

Material* material_make(Color color, double reflectivity, double transparency,
                        double refractive_index) {
  Material* material = (Material*)malloc(sizeof(Material));
  material->color = color;
  material->reflectivity = reflectivity;
  material->transparency = transparency;
  material->refractive_index = refractive_index;
  return material;
}

void material_destroy(Material* material) { free(material); }