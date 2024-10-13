#include "matrix_test.h"
#include "../s21_matrix.h"

START_TEST(test_determinant_null_matrix) {
  matrix_t *A = NULL;
  double result;
  int status = s21_determinant(A, &result);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(test_determinant_null_result_pointer) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  int status = s21_determinant(&A, NULL);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_non_square_matrix) {
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_1x1_matrix) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 5.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2_matrix) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;  A.matrix[0][1] = 2;  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;  A.matrix[1][1] = 5;  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;  A.matrix[2][1] = 8;  A.matrix[2][2] = 9;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4x4_matrix) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1;  A.matrix[0][1] = 2;  A.matrix[0][2] = 3;  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;  A.matrix[1][1] = 6;  A.matrix[1][2] = 7;  A.matrix[1][3] = 8;
  A.matrix[2][0] = 9;  A.matrix[2][1] = 10; A.matrix[2][2] = 11; A.matrix[2][3] = 12;
  A.matrix[3][0] = 13; A.matrix[3][1] = 14; A.matrix[3][2] = 15; A.matrix[3][3] = 16;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_floating_point_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.5;  A.matrix[0][1] = 2.7;  A.matrix[0][2] = 3.1;
  A.matrix[1][0] = 4.2;  A.matrix[1][1] = 5.8;  A.matrix[1][2] = 6.3;
  A.matrix[2][0] = 7.4;  A.matrix[2][1] = 8.9;  A.matrix[2][2] = 9.6;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -0.749, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_singular_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;  A.matrix[0][1] = 2;  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;  A.matrix[1][1] = 5;  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;  A.matrix[2][1] = 8;  A.matrix[2][2] = 9;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_large_and_small_values) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1e-15; A.matrix[0][1] = 2e15;  A.matrix[0][2] = 3e-15;
  A.matrix[1][0] = 4e15;  A.matrix[1][1] = 5e-15; A.matrix[1][2] = 6e15;
  A.matrix[2][0] = 7e-15; A.matrix[2][1] = 8e15;  A.matrix[2][2] = 9e-15;
  double result;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 6e+16, 1e23);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_determinant_null_matrix);
  tcase_add_test(tc_core, test_determinant_null_result_pointer);
  tcase_add_test(tc_core, test_determinant_non_square_matrix);
  tcase_add_test(tc_core, test_determinant_1x1_matrix);
  tcase_add_test(tc_core, test_determinant_2x2_matrix);
  tcase_add_test(tc_core, test_determinant_3x3_matrix);
  tcase_add_test(tc_core, test_determinant_4x4_matrix);
  tcase_add_test(tc_core, test_determinant_floating_point_matrix);
  tcase_add_test(tc_core, test_determinant_singular_matrix);
  tcase_add_test(tc_core, test_determinant_large_and_small_values);

  suite_add_tcase(s, tc_core);
  return s;
}