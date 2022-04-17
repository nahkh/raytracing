#include <math.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "renderable.h"
#include "collision.h"

#define WIDTH 800
#define HEIGHT 600

#define MAX_SCENE_SIZE 100

struct Scene {
	Renderable renderables[MAX_SCENE_SIZE];
	int renderable_count;
};

typedef struct Scene Scene;

Scene scene_make() {
	Scene scene;
	
	scene.renderables[0] = renderable_make_plane(vector_make(0, 1, 0), -10);
	renderable_set_checkered_scale(&(scene.renderables[0]), 20.0);
	scene.renderables[1] = renderable_make_sphere(vector_make(0, 0, 100), 50);
	renderable_set_solid_color(&(scene.renderables[1]), 255, 255, 255);

	scene.renderable_count = 2;

	return scene;
}

void scene_render(Scene* scene, SDL_Renderer* renderer, Camera camera) {
	Renderable best_hit;
	Collision best_collision;
	Collision collision;
	Ray ray;
	unsigned int x, y, i;

	for (x = 0; x < camera.width; ++x) {
		for (y = 0; y < camera.height; ++y) {
			best_collision = COLLISION_MISS;
			ray = camera_get_ray(camera, x, y);

			for (i = 0; i < scene->renderable_count; ++i) {
				collision = calculate_collision(scene->renderables[i], ray);
				if (collision.hit && (!best_collision.hit || collision.distance < best_collision.distance)) {
					best_collision = collision;
					best_hit = scene->renderables[i];
				}
			}

			if (best_collision.hit) {
				Color color = renderable_get_color_at(best_hit, best_collision.pos);
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			} else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 40, 255);
			}

			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	Camera camera = camera_make(WIDTH, HEIGHT, M_PI_4);
	Scene scene = scene_make();

	int isRunning = 1;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = 0;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = 1;
				}
			}
		}

		SDL_RenderClear(renderer);
		scene_render(&scene, renderer, camera);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}