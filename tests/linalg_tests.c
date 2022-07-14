#include <check.h>
#include <stdlib.h>

#include "../src/matrix.h"
#include "../src/vector.h"

#define DELTA 0.0001

void assert_vector_eq_tol(Vector a, Vector b, double tol) {
  ck_assert_double_eq_tol(a.x, b.x, tol);
  ck_assert_double_eq_tol(a.y, b.y, tol);
  ck_assert_double_eq_tol(a.z, b.z, tol);
}

void assert_matrix_eq_tol(Matrix a, Matrix b, double tol) {
  ck_assert_double_eq_tol(a.a1, b.a1, tol);
  ck_assert_double_eq_tol(a.a2, b.a2, tol);
  ck_assert_double_eq_tol(a.a3, b.a3, tol);
  ck_assert_double_eq_tol(a.b1, b.b1, tol);
  ck_assert_double_eq_tol(a.b2, b.b2, tol);
  ck_assert_double_eq_tol(a.b3, b.b3, tol);
  ck_assert_double_eq_tol(a.c1, b.c1, tol);
  ck_assert_double_eq_tol(a.c2, b.c2, tol);
  ck_assert_double_eq_tol(a.c3, b.c3, tol);
}

START_TEST(vector_length_correct) {
  Vector vector = {4.0, 3.0, 0.0};

  ck_assert_double_eq_tol(5, vector_length(&vector), DELTA);

  vector.x = 0.0;
  vector.z = -4.0;
  ck_assert_double_eq_tol(5, vector_length(&vector), DELTA);

  vector.y = 0;
  vector.x = -3.0;
  ck_assert_double_eq_tol(5, vector_length(&vector), DELTA);
}
END_TEST

START_TEST(vector_add_correct) {
  Vector vector_a = {4.0, 3.0, 0.0};

  Vector vector_b = {-2.0, 5.0, 1.0};

  Vector expected = {2.0, 8.0, 1.0};

  assert_vector_eq_tol(expected, vector_add(&vector_a, &vector_b), DELTA);
}
END_TEST

START_TEST(vector_scale_correct) {
  Vector vector = {4.0, 3.0, 0.0};

  Vector expected = {8.0, 6.0, 0.0};

  assert_vector_eq_tol(expected, vector_scale(&vector, 2.0), DELTA);

  vector = (Vector){1.0, 1.0, 1.0};
  expected = (Vector){0.0, 0.0, 0.0};
  assert_vector_eq_tol(expected, vector_scale(&vector, 0.0), DELTA);
}
END_TEST

START_TEST(vector_dot_product_correct) {
  Vector vector_a = {4.0, 3.0, 0.0};
  Vector vector_b = {1.0, 0.0, 1.0};

  double expected = 4.0;
  ck_assert_double_eq_tol(expected, vector_dot_product(&vector_a, &vector_b),
                          DELTA);
}
END_TEST

START_TEST(vector_cross_product_perpendicular) {
  Vector vector_a = {4.0, 3.0, 0.0};
  Vector vector_b = {1.0, 0.0, 1.0};
  Vector cross = vector_cross_product(&vector_a, &vector_b);

  ck_assert_double_eq_tol(0, vector_dot_product(&cross, &vector_a), DELTA);
  ck_assert_double_eq_tol(0, vector_dot_product(&cross, &vector_b), DELTA);
}
END_TEST

START_TEST(vector_normalize_length_one) {
  Vector vector = {4.0, 3.0, 0.0};
  Vector normalized = vector_normalize(&vector);

  ck_assert_double_eq_tol(1.0, vector_length(&normalized), DELTA);
}
END_TEST

START_TEST(vector_normalize_in_same_direction) {
  Vector vector = {4.0, 3.0, 0.0};
  Vector normalized = vector_normalize(&vector);

  ck_assert_double_eq_tol(5.0, vector_dot_product(&vector, &normalized), DELTA);
}
END_TEST

Suite *vector_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Vector");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, vector_length_correct);
  tcase_add_test(tc_core, vector_add_correct);
  tcase_add_test(tc_core, vector_scale_correct);
  tcase_add_test(tc_core, vector_dot_product_correct);
  tcase_add_test(tc_core, vector_cross_product_perpendicular);
  tcase_add_test(tc_core, vector_normalize_length_one);
  tcase_add_test(tc_core, vector_normalize_in_same_direction);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(matrix_multiply_matrix_correct) {
  Matrix matrix_a = (Matrix){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix matrix_b =
      (Matrix){11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0};
  Matrix expected = (Matrix){90, 96, 102, 216, 231, 246, 342, 366, 390};

  assert_matrix_eq_tol(expected, matrix_multiply_matrix(&matrix_a, &matrix_b),
                       DELTA);
}
END_TEST

START_TEST(matrix_multiply_vector_correct) {
  Matrix matrix = (Matrix){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Vector vector = (Vector){11.0, 14.0, 17.0};
  Vector expected = (Vector){90, 216, 342};

  assert_vector_eq_tol(expected, matrix_multiply_vector(&matrix, &vector),
                       DELTA);
}
END_TEST

START_TEST(matrix_multiply_scalar_correct) {
  Matrix matrix = (Matrix){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double scalar = 3.0;
  Matrix expected = (Matrix){3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 24.0, 27.0};

  assert_matrix_eq_tol(expected, matrix_multiply_scalar(&matrix, scalar),
                       DELTA);
}
END_TEST

START_TEST(matrix_inverse_multiplication_results_in_identity) {
  Matrix matrix = (Matrix){7.0, 12.0, -1.0, 8.0, 9.5, 3.0, 2.0, 0, -1.0};

  ck_assert_double_eq(120.5, matrix_determinant(&matrix));

  Matrix inverse = matrix_inverse(&matrix);
  Matrix actual = matrix_multiply_matrix(&matrix, &inverse);
  Matrix expected = MATRIX_IDENTITY;

  assert_matrix_eq_tol(expected, actual, DELTA);
}
END_TEST

START_TEST(matrix_rotation_x_maintains_x_vector) {
  Matrix matrix = matrix_rotate_x(1.0);

  assert_vector_eq_tol(VECTOR_X, matrix_multiply_vector(&matrix, &VECTOR_X),
                       DELTA);
}
END_TEST

START_TEST(matrix_rotation_y_maintains_y_vector) {
  Matrix matrix = matrix_rotate_y(1.0);

  assert_vector_eq_tol(VECTOR_Y, matrix_multiply_vector(&matrix, &VECTOR_Y),
                       DELTA);
}
END_TEST

START_TEST(matrix_rotation_z_maintains_z_vector) {
  Matrix matrix = matrix_rotate_z(1.0);

  assert_vector_eq_tol(VECTOR_Z, matrix_multiply_vector(&matrix, &VECTOR_Z),
                       DELTA);
}
END_TEST

START_TEST(matrix_rotation_x_inverses_itself) {
  Matrix matrix = matrix_rotate_x(1.0);
  Matrix inverse = matrix_rotate_x(-1.0);

  assert_matrix_eq_tol(MATRIX_IDENTITY,
                       matrix_multiply_matrix(&matrix, &inverse), DELTA);
}
END_TEST

START_TEST(matrix_rotation_y_inverses_itself) {
  Matrix matrix = matrix_rotate_y(1.0);
  Matrix inverse = matrix_rotate_y(-1.0);

  assert_matrix_eq_tol(MATRIX_IDENTITY,
                       matrix_multiply_matrix(&matrix, &inverse), DELTA);
}
END_TEST

START_TEST(matrix_rotation_z_inverses_itself) {
  Matrix matrix = matrix_rotate_z(1.0);
  Matrix inverse = matrix_rotate_z(-1.0);

  assert_matrix_eq_tol(MATRIX_IDENTITY,
                       matrix_multiply_matrix(&matrix, &inverse), DELTA);
}
END_TEST

START_TEST(matrix_rotation_x_2_pi_is_identity) {
  Matrix matrix = matrix_rotate_x(2.0 * M_PI);

  assert_matrix_eq_tol(MATRIX_IDENTITY, matrix, DELTA);
}
END_TEST

START_TEST(matrix_rotation_y_2_pi_is_identity) {
  Matrix matrix = matrix_rotate_y(2.0 * M_PI);

  assert_matrix_eq_tol(MATRIX_IDENTITY, matrix, DELTA);
}
END_TEST

START_TEST(matrix_rotation_z_2_pi_is_identity) {
  Matrix matrix = matrix_rotate_z(2.0 * M_PI);

  assert_matrix_eq_tol(MATRIX_IDENTITY, matrix, DELTA);
}
END_TEST

START_TEST(matrix_rotation_x_y_becomes_z) {
  Matrix matrix = matrix_rotate_x(M_PI_2);

  assert_vector_eq_tol(VECTOR_Z, matrix_multiply_vector(&matrix, &VECTOR_Y),
                       DELTA);
}
END_TEST

START_TEST(matrix_rotation_y_x_becomes_minus_z) {
  Matrix matrix = matrix_rotate_y(M_PI_2);

  assert_vector_eq_tol(vector_scale(&VECTOR_Z, -1),
                       matrix_multiply_vector(&matrix, &VECTOR_X), DELTA);
}
END_TEST

START_TEST(matrix_rotation_z_y_becomes_minus_x) {
  Matrix matrix = matrix_rotate_z(M_PI_2);

  assert_vector_eq_tol(vector_scale(&VECTOR_X, -1),
                       matrix_multiply_vector(&matrix, &VECTOR_Y), DELTA);
}
END_TEST

Suite *matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, matrix_multiply_matrix_correct);
  tcase_add_test(tc_core, matrix_multiply_vector_correct);
  tcase_add_test(tc_core, matrix_multiply_scalar_correct);
  tcase_add_test(tc_core, matrix_inverse_multiplication_results_in_identity);
  tcase_add_test(tc_core, matrix_rotation_x_maintains_x_vector);
  tcase_add_test(tc_core, matrix_rotation_y_maintains_y_vector);
  tcase_add_test(tc_core, matrix_rotation_z_maintains_z_vector);
  tcase_add_test(tc_core, matrix_rotation_x_inverses_itself);
  tcase_add_test(tc_core, matrix_rotation_y_inverses_itself);
  tcase_add_test(tc_core, matrix_rotation_z_inverses_itself);
  tcase_add_test(tc_core, matrix_rotation_z_2_pi_is_identity);
  tcase_add_test(tc_core, matrix_rotation_y_2_pi_is_identity);
  tcase_add_test(tc_core, matrix_rotation_z_2_pi_is_identity);
  tcase_add_test(tc_core, matrix_rotation_x_y_becomes_z);
  tcase_add_test(tc_core, matrix_rotation_y_x_becomes_minus_z);
  tcase_add_test(tc_core, matrix_rotation_z_y_becomes_minus_x);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  number_failed = 0;

  s = vector_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : -1;
}