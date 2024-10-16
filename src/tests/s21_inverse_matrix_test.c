#include "../s21_matrix.h"
#include "matrix_test.h"

START_TEST(test_inverse_matrix_null_input) {
  matrix_t *A = NULL;
  matrix_t result;
  int ret = s21_inverse_matrix(A, &result);
  ck_assert_int_eq(ret, ERROR);
}
END_TEST

START_TEST(test_inverse_matrix_null_result) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  int ret = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(ret, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_not_square) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  int ret = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_zero_determinant) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int ret = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_2x2) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  int ret = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 0;

  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = -24.0;
  expected.matrix[0][1] = 18.0;
  expected.matrix[0][2] = 5.0;
  expected.matrix[1][0] = 20.0;
  expected.matrix[1][1] = -15.0;
  expected.matrix[1][2] = -4.0;
  expected.matrix[2][0] = -5.0;
  expected.matrix[2][1] = 4.0;
  expected.matrix[2][2] = 1.0;

  int ret = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_matrix_1x1) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;

  int ret = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.5, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_identity) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int ret = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(ret, OK);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_product) {
  matrix_t A, inverse, product, identity;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 0;

  int ret = s21_inverse_matrix(&A, &inverse);
  ck_assert_int_eq(ret, OK);

  s21_mult_matrix(&A, &inverse, &product);

  s21_create_matrix(3, 3, &identity);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      identity.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(product.matrix[i][j], identity.matrix[i][j],
                              1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&inverse);
  s21_remove_matrix(&product);
  s21_remove_matrix(&identity);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inverse_matrix_null_input);
  tcase_add_test(tc_core, test_inverse_matrix_null_result);
  tcase_add_test(tc_core, test_inverse_matrix_not_square);
  tcase_add_test(tc_core, test_inverse_matrix_zero_determinant);
  tcase_add_test(tc_core, test_inverse_matrix_2x2);
  tcase_add_test(tc_core, test_inverse_matrix_3x3);
  tcase_add_test(tc_core, test_inverse_matrix_1x1);
  tcase_add_test(tc_core, test_inverse_matrix_identity);
  tcase_add_test(tc_core, test_inverse_matrix_product);

  suite_add_tcase(s, tc_core);
  return s;
}