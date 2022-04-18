#include <math.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "renderable.h"
#include "collision.h"
#include "scene.h"
#include "renderer.h"

#define WIDTH 600
#define HEIGHT 400


void scene_render(Scene* scene, SDL_Renderer* renderer, Camera* camera) {
	Color255 color;
	unsigned int x, y;

	for (x = 0; x < camera->width; ++x) {
		for (y = 0; y < camera->height; ++y) {
			color = color_to_color255(render_color(scene, camera_get_ray(camera, x, y), 5));
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}

void move_forward(Camera *camera) {
	camera->position = vector_add(camera->position, matrix_multiply_vector(camera->orientation, VECTOR_Z));
}

void move_backward(Camera *camera) {
	camera->position = vector_subtract(camera->position, matrix_multiply_vector(camera->orientation, VECTOR_Z));
}

void rotate_left(Camera *camera) {
	Matrix left = matrix_rotate_y(-0.1);
	camera->orientation = matrix_multiply_matrix(camera->orientation, left);
}

void rotate_right(Camera *camera) {
	Matrix right = matrix_rotate_y(0.1);
	camera->orientation = matrix_multiply_matrix(camera->orientation, right);
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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

				if (event.key.keysym.sym == SDLK_UP) {
					move_forward(&camera);
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					move_backward(&camera);
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					rotate_left(&camera);
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					rotate_right(&camera);
				}
			}
		}

		SDL_RenderClear(renderer);
		scene_render(&scene, renderer, &camera);

		SDL_RenderPresent(renderer);
	}

	camera_destroy(&camera);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}