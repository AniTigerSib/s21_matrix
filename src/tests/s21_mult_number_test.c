#include "../s21_matrix.h"
#include "matrix_test.h"

START_TEST(test_s21_mult_number_null_matrix) {
  matrix_t result = {0};
  double number = 2.0;

  int ret = s21_mult_number(NULL, number, &result);

  ck_assert_int_eq(ret, ERROR);
}
END_TEST

START_TEST(test_s21_mult_number_null_result) {
  matrix_t A = {0};
  double number = 2.0;

  s21_create_matrix(3, 3, &A);

  int ret = s21_mult_number(&A, number, NULL);

  ck_assert_int_eq(ret, ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_mult_number_1x1_positive) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 5.0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 10.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_1x1_by_zero) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 0.0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_1x1_negative) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = -5.0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], -10.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_large_matrix) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 3.14;
  int size = 100;

  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (double)(i * size + j + 1);
    }
  }

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, size);
  ck_assert_int_eq(result.columns, size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j] * number,
                              1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_small_number) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 1e-15;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1000000.0;
  A.matrix[0][1] = 2000000.0;
  A.matrix[1][0] = 3000000.0;
  A.matrix[1][1] = 4000000.0;

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 1e-9, 1e-20);
  ck_assert_double_eq_tol(result.matrix[0][1], 2e-9, 1e-20);
  ck_assert_double_eq_tol(result.matrix[1][0], 3e-9, 1e-20);
  ck_assert_double_eq_tol(result.matrix[1][1], 4e-9, 1e-20);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_large_number) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 1e100;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1e-98;
  A.matrix[0][1] = 2e-98;
  A.matrix[1][0] = 3e-98;
  A.matrix[1][1] = 4e-98;

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 1e2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2e2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 3e2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4e2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_result_dimensions) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 2.5;

  s21_create_matrix(3, 4, &A);

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, A.rows);
  ck_assert_int_eq(result.columns, A.columns);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_valid_inputs) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 2.5;

  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  int ret = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j] * number,
                              1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_mult_number_null_matrix);
  tcase_add_test(tc_core, test_s21_mult_number_null_result);
  tcase_add_test(tc_core, test_s21_mult_number_1x1_positive);
  tcase_add_test(tc_core, test_s21_mult_number_1x1_by_zero);
  tcase_add_test(tc_core, test_s21_mult_number_1x1_negative);
  tcase_add_test(tc_core, test_s21_mult_number_large_matrix);
  tcase_add_test(tc_core, test_s21_mult_number_small_number);
  tcase_add_test(tc_core, test_s21_mult_number_large_number);
  tcase_add_test(tc_core, test_s21_mult_number_result_dimensions);
  tcase_add_test(tc_core, test_s21_mult_number_valid_inputs);

  suite_add_tcase(s, tc_core);

  return s;
}