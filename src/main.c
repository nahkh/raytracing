#include <math.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "renderable.h"
#include "collision.h"
#include "scene.h"
#include "renderer.h"

#define WIDTH 1000
#define HEIGHT 800


void scene_render(Scene* scene, SDL_Renderer* renderer, Camera camera) {
	Color color;
	unsigned int x, y;

	for (x = 0; x < camera.width; ++x) {
		for (y = 0; y < camera.height; ++y) {
			color = render_color(scene, camera_get_ray(camera, x, y), 5);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}

int main()
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