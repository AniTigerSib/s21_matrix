#include "../s21_matrix.h"
#include "matrix_test.h"

START_TEST(test_transpose_null_matrix) {
  matrix_t *A = NULL;
  matrix_t result;
  int ret = s21_transpose(A, &result);
  ck_assert_int_eq(ret, ERROR);
}
END_TEST

START_TEST(test_s21_transpose_null_result) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  int ret = s21_transpose(&A, NULL);
  ck_assert_int_eq(ret, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_1x1_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 5.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_2x2_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 3.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 4.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_2x3_matrix) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 5.0);
  ck_assert_double_eq(result.matrix[2][0], 3.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_matrix_with_negative_values) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[0][2] = -3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = -5.0;
  A.matrix[1][2] = 6.0;

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], -1.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], -2.0);
  ck_assert_double_eq(result.matrix[1][1], -5.0);
  ck_assert_double_eq(result.matrix[2][0], -3.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_original_matrix_unchanged) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 2);
  ck_assert_double_eq(A.matrix[0][0], 1.0);
  ck_assert_double_eq(A.matrix[0][1], 2.0);
  ck_assert_double_eq(A.matrix[1][0], 3.0);
  ck_assert_double_eq(A.matrix[1][1], 4.0);
  ck_assert_double_eq(A.matrix[2][0], 5.0);
  ck_assert_double_eq(A.matrix[2][1], 6.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_large_matrix) {
  matrix_t A;
  matrix_t result;
  int size = 1000;
  s21_create_matrix(size, size, &A);

  // Fill the matrix with some values
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i * size + j;
    }
  }

  int ret = s21_transpose(&A, &result);

  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(result.rows, size);
  ck_assert_int_eq(result.columns, size);

  // Check a few random elements to ensure correct transposition
  ck_assert_double_eq(result.matrix[0][0], A.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][999], A.matrix[999][0]);
  ck_assert_double_eq(result.matrix[999][0], A.matrix[0][999]);
  ck_assert_double_eq(result.matrix[999][999], A.matrix[999][999]);
  ck_assert_double_eq(result.matrix[500][500], A.matrix[500][500]);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_transpose_null_matrix);
  tcase_add_test(tc_core, test_s21_transpose_null_result);
  tcase_add_test(tc_core, test_transpose_1x1_matrix);
  tcase_add_test(tc_core, test_transpose_2x2_matrix);
  tcase_add_test(tc_core, test_transpose_2x3_matrix);
  tcase_add_test(tc_core, test_transpose_matrix_with_negative_values);
  tcase_add_test(tc_core, test_transpose_original_matrix_unchanged);
  tcase_add_test(tc_core, test_transpose_large_matrix);

  suite_add_tcase(s, tc_core);
  return s;
}