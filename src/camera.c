#include <math.h>
#include <stdlib.h>
#include "camera.h"

Camera camera_make(unsigned int w, unsigned int h, double fov) {
    unsigned int x, y, depth;
    Camera camera;

    camera.width = w;
    camera.height = h;
    camera.orientation = MATRIX_IDENTITY;
    camera.position = vector_make(0, 0, 0);
    camera.rays = (Vector*) malloc(sizeof(Vector) * w * h);

    depth = 0.5 * (int)w / tan(fov);
    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            camera.rays[x + y * w] = vector_normalize(vector_make((int)x - (int)w/2, (int)h/2 - (int)y, depth));
        }
    }
    
    return camera;
}

Ray camera_get_ray(Camera camera, unsigned int x, unsigned int y) {
    return ray_make(camera.position, matrix_multiply_vector(camera.orientation, camera.rays[x + camera.width * y]));
}
