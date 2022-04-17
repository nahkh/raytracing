#ifndef _camera_h_
#define _camera_h_

#include "vector.h"
#include "matrix.h"
#include "ray.h"


struct Camera {
    unsigned int width, height;
    Vector *rays;
    Vector position;
    Matrix orientation;
};

typedef struct Camera Camera;

Camera camera_make(unsigned int, unsigned int, double);

Ray camera_get_ray(Camera, unsigned int, unsigned int);

#endif