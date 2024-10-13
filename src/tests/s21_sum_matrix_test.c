#include "matrix_test.h"

#include "../s21_matrix.h"

START_TEST(test_sum_matrix_null_input) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int ret = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(ret, ERROR);

  ret = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(ret, ERROR);

  ret = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(ret, ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_different_rows) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_different_columns) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1x1) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  
  A.matrix[0][0] = 2.5;
  B.matrix[0][0] = 3.7;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 6.2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_3x3_positive_integers) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Initialize matrix A
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
  A.matrix[2][0] = 7; A.matrix[2][1] = 8; A.matrix[2][2] = 9;

  // Initialize matrix B
  B.matrix[0][0] = 9; B.matrix[0][1] = 8; B.matrix[0][2] = 7;
  B.matrix[1][0] = 6; B.matrix[1][1] = 5; B.matrix[1][2] = 4;
  B.matrix[2][0] = 3; B.matrix[2][1] = 2; B.matrix[2][2] = 1;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);

  // Check the result matrix
  ck_assert_double_eq_tol(result.matrix[0][0], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 10, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_2x4_negative_numbers) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(2, 4, &B);

  // Initialize matrix A
  A.matrix[0][0] = -1.5; A.matrix[0][1] = -2.7; A.matrix[0][2] = -3.1; A.matrix[0][3] = -4.9;
  A.matrix[1][0] = -5.2; A.matrix[1][1] = -6.8; A.matrix[1][2] = -7.3; A.matrix[1][3] = -8.0;

  // Initialize matrix B
  B.matrix[0][0] = -0.5; B.matrix[0][1] = -1.3; B.matrix[0][2] = -2.9; B.matrix[0][3] = -3.1;
  B.matrix[1][0] = -4.8; B.matrix[1][1] = -5.2; B.matrix[1][2] = -6.7; B.matrix[1][3] = -7.0;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);

  // Check the result matrix
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][3], -8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -12.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], -14.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][3], -15.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_floating_point) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  // Initialize matrix A
  A.matrix[0][0] = 1.5; A.matrix[0][1] = -2.7; A.matrix[0][2] = 3.14;
  A.matrix[1][0] = 4.2; A.matrix[1][1] = -5.8; A.matrix[1][2] = 6.01;

  // Initialize matrix B
  B.matrix[0][0] = 0.5; B.matrix[0][1] = 1.3; B.matrix[0][2] = -2.14;
  B.matrix[1][0] = -3.2; B.matrix[1][1] = 4.2; B.matrix[1][2] = -5.01;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);

  // Check the result matrix
  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -1.6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_large_values) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Initialize matrix A with large values
  A.matrix[0][0] = 1e15;
  A.matrix[0][1] = 2e15;
  A.matrix[1][0] = 3e15;
  A.matrix[1][1] = 4e15;

  // Initialize matrix B with large values
  B.matrix[0][0] = 5e15;
  B.matrix[0][1] = 6e15;
  B.matrix[1][0] = 7e15;
  B.matrix[1][1] = 8e15;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);

  // Check the result matrix
  ck_assert_double_eq_tol(result.matrix[0][0], 6e15, 1e8);
  ck_assert_double_eq_tol(result.matrix[0][1], 8e15, 1e8);
  ck_assert_double_eq_tol(result.matrix[1][0], 1e16, 1e8);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.2e16, 1e8);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_small_values) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Initialize matrix A with very small values
  A.matrix[0][0] = 1e-15;
  A.matrix[0][1] = 2e-15;
  A.matrix[1][0] = 3e-15;
  A.matrix[1][1] = 4e-15;

  // Initialize matrix B with very small values
  B.matrix[0][0] = 5e-15;
  B.matrix[0][1] = 6e-15;
  B.matrix[1][0] = 7e-15;
  B.matrix[1][1] = 8e-15;

  int ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, OK);

  // Check the result matrix
  ck_assert_double_eq_tol(result.matrix[0][0], 6e-15, 1e-20);
  ck_assert_double_eq_tol(result.matrix[0][1], 8e-15, 1e-20);
  ck_assert_double_eq_tol(result.matrix[1][0], 1e-14, 1e-20);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.2e-14, 1e-20);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_sum_matrix_suite(void) {
  Suite *s = suite_create("s21_sum_matrix");
  TCase *tc_core  = tcase_create("Core");

  tcase_add_test(tc_core, test_sum_matrix_null_input);
  tcase_add_test(tc_core, test_sum_matrix_different_rows);
  tcase_add_test(tc_core, test_sum_matrix_different_columns);
  tcase_add_test(tc_core, test_sum_matrix_1x1);
  tcase_add_test(tc_core, test_sum_matrix_3x3_positive_integers);
  tcase_add_test(tc_core, test_sum_matrix_2x4_negative_numbers);
  tcase_add_test(tc_core, test_sum_matrix_floating_point);
  tcase_add_test(tc_core, test_sum_matrix_large_values);
  tcase_add_test(tc_core, test_sum_matrix_small_values);

  suite_add_tcase(s, tc_core);
  return s;
}