#ifndef _scene_h_
#define _scene_h_

#include "vector.h"
#include "renderable.h"
#include "light.h"

#define MAX_SCENE_SIZE 100
#define MAX_LIGHT_SOURCES 10

struct Scene {
	LightSource light_sources[MAX_LIGHT_SOURCES];
	Renderable renderables[MAX_SCENE_SIZE];
	unsigned int light_source_count;
	unsigned int renderable_count;
};

typedef struct Scene Scene;

Scene scene_make();

#endif