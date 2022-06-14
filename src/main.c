#include <math.h>
#include <pthread.h>
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

#define THREAD_COUNT 40

struct RenderingThreadInput {
	unsigned int thread_count;
	unsigned int thread_num;
	Scene* scene;
	Camera* camera;
	Color255* pixels;
};

typedef struct RenderingThreadInput RenderingThreadInput;

void* scene_thread_calculate_colors(void* params) {
	unsigned int x, y;
	RenderingThreadInput* input = (RenderingThreadInput*) params;

	for (x = input->thread_num; x < input->camera->width; x+=input->thread_count) {
		for (y = 0; y < input->camera->height; ++y) {
			input->pixels[x + y * input->camera->width] = color_to_color255(render_color(input->scene, camera_get_ray(input->camera, x, y), 5));
		}
	}

	return params;
}

void scene_calculate_colors(Scene* scene, Camera* camera, Color255* pixels) {
	unsigned int i;
	pthread_t threads[THREAD_COUNT];
	RenderingThreadInput inputs[THREAD_COUNT];

    for (i = 0; i < THREAD_COUNT; ++i) {
		inputs[i] = (RenderingThreadInput) {THREAD_COUNT, i, scene, camera, pixels};
        pthread_create(&threads[i], NULL, scene_thread_calculate_colors, (void*)&(inputs[i]));
	}
    for (i = 0; i < THREAD_COUNT; ++i)
        pthread_join(threads[i], NULL);
	
}

void scene_render(SDL_Renderer* renderer, Camera* camera, Color255* pixels) {
	unsigned int x, y;

	for (x = 0; x < camera->width; ++x) {
		for (y = 0; y < camera->height; ++y) {
			SDL_SetRenderDrawColor(renderer, pixels[x + y * camera->width].r, pixels[x + y * camera->width].g, pixels[x + y * camera->width].b, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}

void move_forward(Camera *camera) {
	Vector forward = matrix_multiply_vector(&(camera->orientation), &VECTOR_Z);

	camera->position = vector_add(&(camera->position), &forward);
}

void move_backward(Camera *camera) {
	Vector forward = matrix_multiply_vector(&(camera->orientation), &VECTOR_Z);

	camera->position = vector_subtract(&(camera->position), &forward);
}

void rotate_left(Camera *camera) {
	Matrix left = matrix_rotate_y(-0.1);
	camera->orientation = matrix_multiply_matrix(&(camera->orientation), &left);
}

void rotate_right(Camera *camera) {
	Matrix right = matrix_rotate_y(0.1);
	camera->orientation = matrix_multiply_matrix(&(camera->orientation), &right);
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	Camera* camera = camera_make(WIDTH, HEIGHT, M_PI_4);
	Scene scene = scene_make();
	Color255* pixel_buffer = (Color255*) malloc(sizeof(Color255) * camera->height * camera->width);

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
					move_forward(camera);
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					move_backward(camera);
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					rotate_left(camera);
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					rotate_right(camera);
				}
			}
		}

		SDL_RenderClear(renderer);
		scene_calculate_colors(&scene, camera, pixel_buffer);
		scene_render(renderer, camera, pixel_buffer);

		SDL_RenderPresent(renderer);
	}

	camera_destroy(camera);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}