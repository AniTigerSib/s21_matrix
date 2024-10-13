#include "matrix_test.h"
#include "../s21_matrix.h"

START_TEST(test_s21_mult_matrix_null_input) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &result), ERROR);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &result), ERROR);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_calc_error_rows_columns) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(4, 2, &B);

  int ret = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_incompatible_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_1x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5.0;
  B.matrix[0][0] = 3.0;
  expected.matrix[0][0] = 15.0;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], expected.matrix[0][0], 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_1xN_Nx1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;

  B.matrix[0][0] = 4.0;
  B.matrix[1][0] = 5.0;
  B.matrix[2][0] = 6.0;

  expected.matrix[0][0] = 32.0;

  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], expected.matrix[0][0], 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_NxN) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &expected);

  // Initialize matrix A
  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0; A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0; A.matrix[1][1] = 5.0; A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0; A.matrix[2][1] = 8.0; A.matrix[2][2] = 9.0;

  // Initialize matrix B
  B.matrix[0][0] = 9.0; B.matrix[0][1] = 8.0; B.matrix[0][2] = 7.0;
  B.matrix[1][0] = 6.0; B.matrix[1][1] = 5.0; B.matrix[1][2] = 4.0;
  B.matrix[2][0] = 3.0; B.matrix[2][1] = 2.0; B.matrix[2][2] = 1.0;

  // Expected result
  expected.matrix[0][0] = 30.0; expected.matrix[0][1] = 24.0; expected.matrix[0][2] = 18.0;
  expected.matrix[1][0] = 84.0; expected.matrix[1][1] = 69.0; expected.matrix[1][2] = 54.0;
  expected.matrix[2][0] = 138.0; expected.matrix[2][1] = 114.0; expected.matrix[2][2] = 90.0;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_decimal_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;  A.matrix[0][1] = 2.3;
  A.matrix[1][0] = 3.7;  A.matrix[1][1] = 4.1;

  B.matrix[0][0] = 0.5;  B.matrix[0][1] = 1.2;
  B.matrix[1][0] = 2.4;  B.matrix[1][1] = 3.6;

  expected.matrix[0][0] = 6.27;  expected.matrix[0][1] = 10.08;
  expected.matrix[1][0] = 11.69; expected.matrix[1][1] = 19.2;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_negative_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = -1.0;  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = -3.0;  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = -5.0;  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = -7.0;  B.matrix[1][1] = 8.0;

  expected.matrix[0][0] = -9.0;  expected.matrix[0][1] = 10.0;
  expected.matrix[1][0] = -13.0; expected.matrix[1][1] = 14.0;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_large_matrices) {
  matrix_t A, B, result, expected;
  int size = 100;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);
  s21_create_matrix(size, size, &expected);

  // Initialize matrices A and B with values
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i + j) * 0.1;
      B.matrix[i][j] = (i - j) * 0.1;
    }
  }

  // Calculate expected result
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      expected.matrix[i][j] = 0;
      for (int k = 0; k < size; k++) {
        expected.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, size);
  ck_assert_int_eq(result.columns, size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix_valid_inputs) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  // Initialize matrix A
  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0; A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0; A.matrix[1][1] = 5.0; A.matrix[1][2] = 6.0;

  // Initialize matrix B
  B.matrix[0][0] = 7.0; B.matrix[0][1] = 8.0;
  B.matrix[1][0] = 9.0; B.matrix[1][1] = 10.0;
  B.matrix[2][0] = 11.0; B.matrix[2][1] = 12.0;

  // Expected result
  expected.matrix[0][0] = 58.0; expected.matrix[0][1] = 64.0;
  expected.matrix[1][0] = 139.0; expected.matrix[1][1] = 154.0;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_mult_matrix_null_input);
  tcase_add_test(tc_core, test_s21_mult_matrix_calc_error_rows_columns);
  tcase_add_test(tc_core, test_s21_mult_matrix_incompatible_sizes);
  tcase_add_test(tc_core, test_s21_mult_matrix_1x1);
  tcase_add_test(tc_core, test_s21_mult_matrix_1xN_Nx1);
  tcase_add_test(tc_core, test_s21_mult_matrix_NxN);
  tcase_add_test(tc_core, test_s21_mult_matrix_decimal_values);
  tcase_add_test(tc_core, test_s21_mult_matrix_negative_values);
  tcase_add_test(tc_core, test_s21_mult_matrix_large_matrices);
  tcase_add_test(tc_core, test_s21_mult_matrix_valid_inputs);

  suite_add_tcase(s, tc_core);

  return s;
}