#include "scene.h"

#include "material.h"

void scene_add_renderable(Scene* scene, Renderable renderable) {
  scene->renderables[scene->renderable_count++] = renderable;
}

void scene_add_light_source(Scene* scene, LightSource light_source) {
  scene->light_sources[scene->light_source_count++] = light_source;
}

Scene scene_make() {
  Scene scene;

  scene_add_light_source(
      &scene, light_source_make_point(color_make_from_rgb(255, 255, 255),
                                      vector_make(0, 100, 0)));

  scene_add_light_source(
      &scene, light_source_make_global(color_make_from_rgb(10, 10, 10)));

  Renderable plane = renderable_make_plane(vector_make(0, 1, 0), -50);
  renderable_set_checkered_scale(&plane, 20.0);
  renderable_set_material(
      &plane, material_make(color_make_from_rgb(0, 0, 0), 0.005, 0, 0));
  scene_add_renderable(&scene, plane);
  Renderable sphere1 = renderable_make_sphere(vector_make(50, 5, 100), 50);
  renderable_set_material(
      &sphere1, material_make(color_make_from_rgb(127, 125, 255), 0.1, 0, 0));
  scene_add_renderable(&scene, sphere1);
  Renderable sphere2 = renderable_make_sphere(vector_make(-50, -5, 120), 45);
  renderable_set_material(
      &sphere2, material_make(color_make_from_rgb(25, 156, 45), 0.2, 0, 0));
  scene_add_renderable(&scene, sphere2);

  return scene;
}