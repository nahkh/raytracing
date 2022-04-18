#include "matrix.h"
#include <math.h>

const Matrix MATRIX_IDENTITY = {1.0, 0, 0, 0, 1.0, 0, 0, 0, 1.0};

Vector matrix_column_1(Matrix m) {
    return vector_make(m.a1, m.b1, m.c1);
}

Vector matrix_column_2(Matrix m) {
    return vector_make(m.a2, m.b2, m.c2);
}

Vector matrix_column_3(Matrix m) {
    return vector_make(m.a3, m.b3, m.c3);
}

Vector matrix_row_1(Matrix m) {
    return vector_make(m.a1, m.a2, m.a3);
}

Vector matrix_row_2(Matrix m) {
    return vector_make(m.b1, m.b2, m.b3);
}

Vector matrix_row_3(Matrix m) {
    return vector_make(m.c1, m.c2, m.c3);
}

Matrix matrix_multiply_matrix(Matrix m, Matrix n) {
    Vector r1 = matrix_row_1(m);
    Vector r2 = matrix_row_2(m);
    Vector r3 = matrix_row_3(m);
    Vector c1 = matrix_column_1(n);
    Vector c2 = matrix_column_2(n);
    Vector c3 = matrix_column_3(n);
    return (Matrix) {   vector_dot_product(r1, c1), vector_dot_product(r1, c2), vector_dot_product(r1, c3), 
                        vector_dot_product(r2, c1), vector_dot_product(r2, c2), vector_dot_product(r2, c3), 
                        vector_dot_product(r3, c1), vector_dot_product(r3, c2), vector_dot_product(r3, c3)};
}

Vector matrix_multiply_vector(Matrix m, Vector v) {
    Vector r1 = matrix_row_1(m);
    Vector r2 = matrix_row_2(m);
    Vector r3 = matrix_row_3(m);
    return (Vector) {vector_dot_product(v, r1), vector_dot_product(v, r2), vector_dot_product(v, r3)};
}

Matrix matrix_multiply_scalar(Matrix m, double a) {
    return (Matrix) {m.a1 * a, m.a2 * a, m.a3 * a, m.b1 * a, m.b2 * a, m.b3 * a, m.c1 * a, m.c2 * a, m.c3 * a};
}


Matrix matrix_inverse(Matrix a) {
    double det = matrix_determinant(a);
    if (det == 0.0) {
        return a;
    }

    double A = (a.b2 * a.c3 - a.b3 * a.c2) / det;
    double B = (a.b3 * a.c1 - a.b1 * a.c3) / det;
    double C = (a.b1 * a.c2 - a.b2 * a.c1) / det;
    double D = (a.c2 * a.a3 - a.c3 * a.a2) / det;
    double E = (a.c3 * a.a1 - a.c1 * a.a3) / det;
    double F = (a.c1 * a.a2 - a.c2 * a.a1) / det;
    double G = (a.a2 * a.b3 - a.a3 * a.b2) / det;
    double H = (a.a3 * a.b1 - a.a1 * a.b3) / det;
    double I = (a.a1 * a.b2 - a.a2 * a.b1) / det;
    return (Matrix) {A, D, G, B, E, H, C, F, I};
}

double matrix_determinant(Matrix m) {
    return m.a1 * (m.b2 * m.c3 - m.b3 * m.c2) + m.a2 * (m.b3 * m.c1 - m.b1 * m.c3) + m.a3 * (m.b1 * m.c2 - m.b2 * m.c1);
}

Matrix matrix_make(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3) {
    return (Matrix) {a1, a2, a3, b1, b2, b3, c1, c2, c3};
}


Matrix matrix_rotate_x(double radians){
    double cosine = cos(radians);
    double sine = sin(radians);
    return matrix_make(1, 0, 0, 0, cosine, -sine, 0, sine, cosine);
}

Matrix matrix_rotate_y(double radians) {
    double cosine = cos(radians);
    double sine = sin(radians);
    return matrix_make(cosine, 0, sine, 0, 1, 0, -sine, 0, cosine);
}

Matrix matrix_rotate_z(double radians) {
    double cosine = cos(radians);
    double sine = sin(radians);
    return matrix_make(cosine, -sine, 0, sine, cosine, 0, 0, 0, 1);
}
