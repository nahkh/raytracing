#include "camera.h"

#include <math.h>
#include <stdlib.h>

Camera *camera_make(unsigned int w, unsigned int h, double fov) {
  unsigned int x, y, depth;
  Vector origin_to_screen;
  Camera *camera = (Camera *)malloc(sizeof(Camera));

  camera->width = w;
  camera->height = h;
  camera->orientation = MATRIX_IDENTITY;
  camera->position = vector_make(0, 0, 0);
  camera->rays = (Vector *)malloc(sizeof(Vector) * w * h);

  depth = 0.5 * (int)w / tan(fov);
  for (y = 0; y < h; ++y) {
    for (x = 0; x < w; ++x) {
      origin_to_screen =
          vector_make((int)x - (int)w / 2, (int)h / 2 - (int)y, depth);
      camera->rays[x + y * w] = vector_normalize(&origin_to_screen);
    }
  }

  return camera;
}

void camera_destroy(Camera *camera) {
  free(camera->rays);
  free(camera);
}

Ray camera_get_ray(Camera *camera, unsigned int x, unsigned int y) {
  Vector direction = matrix_multiply_vector(
      &(camera->orientation), &(camera->rays[x + camera->width * y]));

  return ray_make(&(camera->position), &direction);
}
