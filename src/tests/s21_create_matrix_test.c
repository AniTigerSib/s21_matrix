#include "matrix_test.h"

#include "../s21_matrix.h"
#include "../allocator_wrapper/allocator_wrapper.h"

/*----------------OK----------------*/

START_TEST(create_matrix_1to1)
{
  int rows = 1;
  int columns = 1;
  res_code_e expected_result = OK;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_ne(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0f);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_1to3)
{
  int rows = 1;
  int columns = 3;
  res_code_e expected_result = OK;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_ne(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[0][1], 0.0f);
  ck_assert_double_eq(matrix.matrix[0][2], 0.0f);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_3to1)
{
  int rows = 3;
  int columns = 1;
  res_code_e expected_result = OK;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_ne(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[1][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[2][0], 0.0f);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_3to3)
{
  int rows = 3;
  int columns = 3;
  res_code_e expected_result = OK;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_ne(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[0][1], 0.0f);
  ck_assert_double_eq(matrix.matrix[0][2], 0.0f);
  ck_assert_double_eq(matrix.matrix[1][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[1][1], 0.0f);
  ck_assert_double_eq(matrix.matrix[1][2], 0.0f);
  ck_assert_double_eq(matrix.matrix[2][0], 0.0f);
  ck_assert_double_eq(matrix.matrix[2][1], 0.0f);
  ck_assert_double_eq(matrix.matrix[2][2], 0.0f);
  s21_remove_matrix(&matrix);
}
END_TEST

/*---------------FAIL---------------*/

START_TEST(create_matrix_zero_to_positive)
{
  int rows = 0;
  int columns = 3;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_positive_to_zero)
{
  int rows = 3;
  int columns = 0;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  res_code_e return_value = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(return_value, expected_result);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_zero_to_zero)
{
  int rows = 0;
  int columns = 0;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_negative_to_zero)
{
  int rows = -1;
  int columns = 0;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_zero_to_negative)
{
  int rows = 0;
  int columns = -1;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_negative_to_negative)
{
  int rows = -1;
  int columns = -1;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_negative_to_positive)
{
  int rows = -1;
  int columns = 1;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_positive_to_negative)
{
  int rows = 1;
  int columns = -1;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_not_null_pointer)
{
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  s21_create_matrix(1, 1, &matrix);
  ck_assert_int_eq(s21_create_matrix(3, 3, &matrix), expected_result);

  ck_assert_int_eq(matrix.rows, 1);
  ck_assert_int_eq(matrix.columns, 1);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0f);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_null_pointer)
{
  int rows = 3;
  int columns = 3;
  res_code_e expected_result = ERROR;

  matrix_t *matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(rows, columns, matrix), expected_result);
}
END_TEST

#ifndef WITHOUT_MEMORY_LOCKING

START_TEST(create_matrix_mem_allocating_blocked_p_double)
{
  int rows = 3;
  int columns = 3;
  res_code_e expected_result = ERROR;

  matrix_t matrix = {0};
  memory_locked(sizeof(double *), 1);
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  memory_locked(0, -1);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_mem_allocating_blocked_double)
{
  int rows = 3;
  int columns = 3;
  res_code_e expected_result = ERROR;
  
  matrix_t matrix = {0};
  memory_locked(sizeof(double), 1);
  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), expected_result);
  memory_locked(0, -1);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
  s21_remove_matrix(&matrix);
}
END_TEST

#endif

Suite *s21_create_matrix_suite(void) {
  Suite *s = suite_create("s21_create_matrix_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, create_matrix_1to1);
  tcase_add_test(tc_core, create_matrix_1to3);
  tcase_add_test(tc_core, create_matrix_3to1);
  tcase_add_test(tc_core, create_matrix_3to3);
  tcase_add_test(tc_core, create_matrix_zero_to_positive);
  tcase_add_test(tc_core, create_matrix_positive_to_zero);
  tcase_add_test(tc_core, create_matrix_zero_to_zero);
  tcase_add_test(tc_core, create_matrix_negative_to_zero);
  tcase_add_test(tc_core, create_matrix_zero_to_negative);
  tcase_add_test(tc_core, create_matrix_negative_to_negative);
  tcase_add_test(tc_core, create_matrix_negative_to_positive);
  tcase_add_test(tc_core, create_matrix_positive_to_negative);
  tcase_add_test(tc_core, create_matrix_not_null_pointer);
  tcase_add_test(tc_core, create_matrix_null_pointer);
#ifndef WITHOUT_MEMORY_LOCKING
  tcase_add_test(tc_core, create_matrix_mem_allocating_blocked_p_double);
  tcase_add_test(tc_core, create_matrix_mem_allocating_blocked_double);
#endif
  suite_add_tcase(s, tc_core);
  return s;
}