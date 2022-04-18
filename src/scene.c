#include "scene.h"



Scene scene_make(){
	Scene scene;

	scene.light_direction = vector_normalize(vector_make(1, -5, 1));
	
	scene.renderables[0] = renderable_make_plane(vector_make(0, 1, 0), -50);
	renderable_set_checkered_scale(&(scene.renderables[0]), 20.0);
	scene.renderables[1] = renderable_make_sphere(vector_make(50, 5, 100), 50);
	renderable_set_solid_color(&(scene.renderables[1]), 127, 125, 255);
	renderable_set_reflectivity(&(scene.renderables[1]), 0.5);
	scene.renderables[2] = renderable_make_sphere(vector_make(-50, -5, 120), 45);
	renderable_set_solid_color(&(scene.renderables[2]), 25, 156, 45);
	renderable_set_reflectivity(&(scene.renderables[2]), 0.5);

	scene.renderable_count = 3;

	return scene;
}