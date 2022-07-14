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

Vector vector_add(const Vector*, const Vector*);

Vector vector_subtract(const Vector*, const Vector*);

Vector vector_scale(const Vector*, double);

Vector vector_cross_product(const Vector*, const Vector*);

Vector vector_normalize(const Vector*);

void vector_print(const Vector*);

#endif