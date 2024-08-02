#include "vector.h"

#include <math.h>
#include <stdio.h>

const Vector VECTOR_X = {1.0, 0.0, 0.0};
const Vector VECTOR_Y = {0.0, 1.0, 0.0};
const Vector VECTOR_Z = {0.0, 0.0, 1.0};
const Vector VECTOR_ZERO = {0.0, 0.0, 0.0};

inline Vector vector_make(double x, double y, double z) {
  return (Vector){x, y, z};
}

double vector_dot_product(const Vector* a, const Vector* b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

double vector_length2(const Vector* vector) {
  return vector_dot_product(vector, vector);
}

double vector_length(const Vector* vector) {
  return sqrt(vector_length2(vector));
}

void vector_add(const Vector* a, const Vector* b, Vector* restrict out) {
  out->x = a->x + b->x;
  out->y = a->y + b->y;
  out->z = a->z + b->z;
}

void vector_add_to(Vector* a, const Vector* b) {
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
}

void vector_subtract(const Vector* a, const Vector* b, Vector* restrict out) {
  out->x = a->x - b->x;
  out->y = a->y - b->y;
  out->z = a->z - b->z;
}

void vector_subtract_from(Vector* a, const Vector* b) {
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
}

void vector_scale(const Vector* a, double scalar, Vector* restrict out) {
  out->x = a->x * scalar;
  out->y = a->y * scalar;
  out->z = a->z * scalar;
}

void vector_cross_product(const Vector* a, const Vector* b,
                          Vector* restrict out) {
  out->x = a->y * b->z - a->z * b->y;
  out->y = a->z * b->x - a->x * b->z;
  out->z = a->x * b->y - a->y * b->x;
}

void vector_normalize(Vector* v) {
  double length = vector_length(v);
  if (length == 0.0) {
    return;
  }
  double inverse_length = 1.0 / length;
  v->x *= inverse_length;
  v->y *= inverse_length;
  v->z *= inverse_length;
}

void vector_print(const Vector* v) {
  printf("Vector(%1.3f, %1.3f, %1.3f)\n", v->x, v->y, v->z);
}