#include <SDL2/SDL.h>
#include <math.h>
#include <pthread.h>

#include "camera.h"
#include "collision.h"
#include "ray.h"
#include "renderable.h"
#include "renderer.h"
#include "scene.h"
#include "vector.h"

#define WIDTH 600
#define HEIGHT 400

#define THREAD_COUNT 20

void scene_render(SDL_Renderer *renderer, Camera *camera, Color255 *pixels) {
  unsigned int x, y;

  for (x = 0; x < camera->width; ++x) {
    for (y = 0; y < camera->height; ++y) {
      SDL_SetRenderDrawColor(renderer, pixels[x + y * camera->width].r,
                             pixels[x + y * camera->width].g,
                             pixels[x + y * camera->width].b, 255);
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

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window =
      SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  Camera *camera = camera_make(WIDTH, HEIGHT, M_PI_4);
  Scene scene = scene_make();
  Color255 *pixel_buffer =
      (Color255 *)malloc(sizeof(Color255) * camera->height * camera->width);
  RenderingThreadPool *rendering_thread_pool =
      start_rendering_threads(THREAD_COUNT, &scene, camera, pixel_buffer);

  int isRunning = 1;
  SDL_Event event;

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          isRunning = 0;
          break;

        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
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
    start_render(rendering_thread_pool);
    scene_render(renderer, camera, pixel_buffer);

    SDL_RenderPresent(renderer);
  }
  stop_rendering_threads(rendering_thread_pool);
  camera_destroy(camera);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}