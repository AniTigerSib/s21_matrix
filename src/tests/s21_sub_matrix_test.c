#include "../s21_matrix.h"
#include "matrix_test.h"

START_TEST(test_s21_sub_matrix_null_input) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int ret = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(ret, ERROR);

  ret = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(ret, ERROR);

  ret = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(ret, ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_different_rows) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_different_columns) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_1x1) {
  matrix_t A, B, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5.0;
  B.matrix[0][0] = 3.0;

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_large) {
  matrix_t A, B, result = {0};
  s21_create_matrix(100, 100, &A);
  s21_create_matrix(100, 100, &B);

  // Fill matrices A and B with values
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      A.matrix[i][j] = i * 100 + j * 1;
      B.matrix[i][j] = (i * 100 + j * 1) * 0.5;
    }
  }

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 100);
  ck_assert_int_eq(result.columns, 100);

  // Check a few random elements
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[50][50], 2525.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[99][99], 4999.5, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_negative_values) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = -6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = -8.0;

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 12.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_correct_dimensions) {
  matrix_t A, B, result = {0};
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &B);

  // Fill matrices A and B with some values
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
      B.matrix[i][j] = (i * 4 + j + 1) * 0.5;
    }
  }

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 4);

  // Check a few elements to ensure correct subtraction
  ck_assert_double_eq_tol(result.matrix[0][0], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 3.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][3], 6.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_decimal_values) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 1.2;
  B.matrix[1][0] = 2.1;
  B.matrix[1][1] = 3.3;

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.1, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.6, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_from_itself) {
  matrix_t A, result = {0};
  s21_create_matrix(3, 3, &A);

  // Fill matrix A with some values
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  int ret = s21_sub_matrix(&A, &A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  // Check that all elements of the result matrix are zero
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_large_values) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  double large_value = 1e307;
  A.matrix[0][0] = large_value;
  A.matrix[0][1] = -large_value;
  A.matrix[1][0] = large_value / 2;
  A.matrix[1][1] = -large_value / 2;

  B.matrix[0][0] = large_value / 2;
  B.matrix[0][1] = -large_value / 2;
  B.matrix[1][0] = large_value / 4;
  B.matrix[1][1] = -large_value / 4;

  int ret = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], large_value / 2,
                          1e-7 * large_value);
  ck_assert_double_eq_tol(result.matrix[0][1], -large_value / 2,
                          1e-7 * large_value);
  ck_assert_double_eq_tol(result.matrix[1][0], large_value / 4,
                          1e-7 * large_value);
  ck_assert_double_eq_tol(result.matrix[1][1], -large_value / 4,
                          1e-7 * large_value);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *s = suite_create("s21_sub_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sub_matrix_null_input);
  tcase_add_test(tc_core, test_sub_matrix_different_rows);
  tcase_add_test(tc_core, test_sub_matrix_different_columns);
  tcase_add_test(tc_core, test_sub_matrix_1x1);
  tcase_add_test(tc_core, test_sub_matrix_large);
  tcase_add_test(tc_core, test_sub_matrix_negative_values);
  tcase_add_test(tc_core, test_sub_matrix_correct_dimensions);
  tcase_add_test(tc_core, test_sub_matrix_decimal_values);
  tcase_add_test(tc_core, test_sub_matrix_from_itself);
  tcase_add_test(tc_core, test_sub_matrix_large_values);

  suite_add_tcase(s, tc_core);
  return s;
}