#include "matrix_test.h"

#include "../s21_matrix.h"

#include <stdio.h>
#include <time.h>

START_TEST(remove_matrix_normal)
{
  matrix_t matrix = {0};
  s21_create_matrix(3, 3, &matrix);
  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(remove_matrix_null_pointer)
{
  matrix_t *matrix = NULL;
  s21_remove_matrix(matrix);
  ck_assert_ptr_eq(matrix, NULL);
}
END_TEST

START_TEST(remove_matrix_null_pointer_inside)
{
  matrix_t matrix = {0};
  s21_create_matrix(3, 3, &matrix);
  for (int i = 0; i < 3; i++) {
    free(matrix.matrix[i]);
    matrix.matrix[i] = NULL;
  }
  free(matrix.matrix);
  matrix.matrix = NULL;
  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(remove_matrix_null_pointer_inside_normal_pointer)
{
  matrix_t matrix = {0};
  s21_create_matrix(3, 3, &matrix);
  free(matrix.matrix[1]);
  matrix.matrix[1] = NULL;
  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, remove_matrix_normal);
  tcase_add_test(tc_core, remove_matrix_null_pointer);
  tcase_add_test(tc_core, remove_matrix_null_pointer_inside);
  tcase_add_test(tc_core, remove_matrix_null_pointer_inside_normal_pointer);

  suite_add_tcase(s, tc_core);
  return s;
}