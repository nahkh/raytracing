#ifndef _renderer_h_
#define _renderer_h_

#include <pthread.h>
#include "renderable.h"
#include "scene.h"
#include "color.h"
#include "camera.h"


enum RenderingThreadState {
    RENDERING,
    IDLE,
    STOPPING,
};

typedef enum RenderingThreadState RenderingThreadState;

struct RenderingThreadInput {
    pthread_t thread_id;
	unsigned int thread_count;
	unsigned int thread_num;
    volatile RenderingThreadState state;
	Scene* scene;
	Camera* camera;
	volatile Color255* pixels;
};

typedef struct RenderingThreadInput RenderingThreadInput;

struct RenderingThreadPool {
    size_t thread_count;
    RenderingThreadInput* threads;
};

typedef struct RenderingThreadPool RenderingThreadPool;


RenderingThreadPool* start_rendering_threads(size_t, Scene*, Camera*, Color255*);

void start_render(RenderingThreadPool*);

void stop_rendering_threads(RenderingThreadPool*);

Color render_color(Scene* scene, Ray ray, int reflections);


#endif