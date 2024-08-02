#ifndef _vector_h_
#define _vector_h_

struct Vector {
  double x;
  double y;
  double z;
};

typedef struct Vector Vector;

extern const Vector VECTOR_X;
extern const Vector VECTOR_Y;
extern const Vector VECTOR_Z;
extern const Vector VECTOR_ZERO;

Vector vector_make(double, double, double);

double vector_dot_product(const Vector*, const Vector*);

double vector_length(const Vector*);

double vector_length2(const Vector*);

void vector_add(const Vector*, const Vector*, Vector*);

void vector_add_to(Vector*, const Vector*);

void vector_subtract(const Vector*, const Vector*, Vector*);

void vector_subtract_from(Vector*, const Vector*);

void vector_scale(const Vector*, double, Vector*);

void vector_cross_product(const Vector*, const Vector*, Vector*);

void vector_normalize(Vector*);

void vector_print(const Vector*);

#endif