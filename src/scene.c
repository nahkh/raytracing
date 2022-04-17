#include "scene.h"

Scene scene_make(){
	Scene scene;

	scene.light_direction = vector_normalize(vector_make(1, -5, 1));
	
	scene.renderables[0] = renderable_make_plane(vector_make(0, 1, 0), -50);
	renderable_set_checkered_scale(&(scene.renderables[0]), 20.0);
	scene.renderables[1] = renderable_make_sphere(vector_make(0, 0, 100), 50);
	renderable_set_solid_color(&(scene.renderables[1]), 255, 255, 255);

	scene.renderable_count = 2;

	return scene;
}