#include "matrix_test.h"
#include "../s21_matrix.h"

START_TEST(test_calc_complements_null_matrix) {
  matrix_t result;
  int ret = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(ret, ERROR);
}
END_TEST

START_TEST(test_calc_complements_null_result) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  int ret = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(ret, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_non_square_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 2, &A);
  int ret = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_2x2_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_3x3_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 0; A.matrix[1][1] = 4; A.matrix[1][2] = 2;
  A.matrix[2][0] = 5; A.matrix[2][1] = 2; A.matrix[2][2] = 1;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -20, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -14, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 4, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_1x1_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 5, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_large_matrix) { // not working
  matrix_t A;
  matrix_t result;
  s21_create_matrix(5, 5, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3; A.matrix[0][3] = 4; A.matrix[0][4] = 5;
  A.matrix[1][0] = 6; A.matrix[1][1] = 7; A.matrix[1][2] = 8; A.matrix[1][3] = 9; A.matrix[1][4] = 10;
  A.matrix[2][0] = 11; A.matrix[2][1] = 12; A.matrix[2][2] = 13; A.matrix[2][3] = 14; A.matrix[2][4] = 15;
  A.matrix[3][0] = 16; A.matrix[3][1] = 17; A.matrix[3][2] = 18; A.matrix[3][3] = 19; A.matrix[3][4] = 20;
  A.matrix[4][0] = 21; A.matrix[4][1] = 22; A.matrix[4][2] = 23; A.matrix[4][3] = 24; A.matrix[4][4] = 25;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[3][3], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[4][4], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][4], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[4][0], 0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_decimal_values) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.5; A.matrix[0][1] = 2.3; A.matrix[0][2] = 3.7;
  A.matrix[1][0] = 0.8; A.matrix[1][1] = 4.2; A.matrix[1][2] = 2.1;
  A.matrix[2][0] = 5.6; A.matrix[2][1] = 2.9; A.matrix[2][2] = 1.4;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -0.21, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 10.64, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -21.2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.51, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -18.62, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 8.53, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -10.71, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -0.19, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 4.46, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_negative_values) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = -1; A.matrix[0][1] = 2; A.matrix[0][2] = -3;
  A.matrix[1][0] = 4; A.matrix[1][1] = -5; A.matrix[1][2] = 6;
  A.matrix[2][0] = -7; A.matrix[2][1] = 8; A.matrix[2][2] = -9;

  int ret = s21_calc_complements(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -12, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], -6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], -3, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_calc_complements_null_matrix);
  tcase_add_test(tc_core, test_calc_complements_null_result);
  tcase_add_test(tc_core, test_calc_complements_non_square_matrix);
  tcase_add_test(tc_core, test_calc_complements_2x2_matrix);
  tcase_add_test(tc_core, test_calc_complements_3x3_matrix);
  tcase_add_test(tc_core, test_calc_complements_1x1_matrix);
  tcase_add_test(tc_core, test_calc_complements_large_matrix);
  tcase_add_test(tc_core, test_calc_complements_decimal_values);
  tcase_add_test(tc_core, test_calc_complements_negative_values);

  suite_add_tcase(s, tc_core);
  return s;
}