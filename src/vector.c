#include "vector.h"
#include <math.h>
#include <stdio.h>

const Vector VECTOR_X = {1.0, 0.0, 0.0};
const Vector VECTOR_Y = {0.0, 1.0, 0.0};
const Vector VECTOR_Z = {0.0, 0.0, 1.0};
const Vector VECTOR_ZERO = {0.0, 0.0, 0.0};

Vector vector_make(double x, double y, double z) {
    return (Vector) {x, y, z};
}

double vector_dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vector_length2(Vector vector) {
    return vector_dot_product(vector, vector);
}

double vector_length(Vector vector) {
    return sqrt(vector_length2(vector));
}

Vector vector_add(Vector a, Vector b) {
    Vector result = {a.x+b.x, a.y + b.y, a.z + b.z};
    return result;
}

Vector vector_subtract(Vector a, Vector b) {
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Vector vector_scale(Vector a, double scalar) {
    Vector result = {a.x*scalar, a.y * scalar, a.z * scalar};
    return result;
}

Vector vector_cross_product(Vector a, Vector b) {
    return (Vector) {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

Vector vector_normalize(Vector v) {
    double length = vector_length(v);
    if (length == 0.0) {
        return v;
    }
    return vector_scale(v, 1/length);
}

void vector_print(Vector v) {
    printf("Vector(%1.3f, %1.3f, %1.3f)\n", v.x, v.y, v.z);
}