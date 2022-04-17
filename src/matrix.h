#ifndef _matrix_h_
#define _matrix_h_

#include "vector.h"

struct Matrix {
    double a1, a2, a3, b1, b2, b3, c1, c2, c3;
};

typedef struct Matrix Matrix;

extern const Matrix MATRIX_IDENTITY;

Matrix matrix_multiply_matrix(Matrix, Matrix);

Vector matrix_multiply_vector(Matrix, Vector);

Matrix matrix_multiply_scalar(Matrix, double);

Matrix matrix_inverse(Matrix);

double matrix_determinant(Matrix);

Vector matrix_column_1(Matrix);
Vector matrix_column_2(Matrix);
Vector matrix_column_3(Matrix);
Vector matrix_row_1(Matrix);
Vector matrix_row_2(Matrix);
Vector matrix_row_3(Matrix);

#endif
