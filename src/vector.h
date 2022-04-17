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

double vector_dot_product(Vector, Vector);

double vector_length(Vector);

double vector_length2(Vector);

Vector vector_add(Vector, Vector);

Vector vector_subtract(Vector, Vector);

Vector vector_scale(Vector, double);

Vector vector_cross_product(Vector, Vector);

Vector vector_normalize(Vector);

void vector_print(Vector);

#endif