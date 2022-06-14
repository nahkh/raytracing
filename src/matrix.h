#ifndef _matrix_h_
#define _matrix_h_

#include "vector.h"

struct Matrix {
    double a1, a2, a3, b1, b2, b3, c1, c2, c3;
};

typedef struct Matrix Matrix;

extern const Matrix MATRIX_IDENTITY;

Matrix matrix_multiply_matrix(const Matrix*, const Matrix*);

Vector matrix_multiply_vector(const Matrix*, const Vector*);

Matrix matrix_multiply_scalar(const Matrix*, double);

Matrix matrix_inverse(const Matrix*);

double matrix_determinant(const Matrix*);

Vector matrix_column_1(const Matrix*);
Vector matrix_column_2(const Matrix*);
Vector matrix_column_3(const Matrix*);
Vector matrix_row_1(const Matrix*);
Vector matrix_row_2(const Matrix*);
Vector matrix_row_3(const Matrix*);

Matrix matrix_make(double, double, double, double, double, double, double, double, double);
Matrix matrix_rotate_x(double);
Matrix matrix_rotate_y(double);
Matrix matrix_rotate_z(double);

#endif
