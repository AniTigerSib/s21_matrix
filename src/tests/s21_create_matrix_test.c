#include "matrix_test.h"

#include "../martix/s21_matrix.h"

START_TEST(create_matrix_1to1)
{
  int rows = 1;
  int columns = 1;
  res_code_e expected_result = OK;

  matrix_t* matrix = NULL;
  res_code_e return_value = s21_create_matrix(rows, columns, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix != NULL, "Expected matrix to be created, got NULL");
  ck_assert_msg(matrix->columns == columns, "Expected %d columns, got %d", columns, matrix->columns);
  ck_assert_msg(matrix->rows == rows, "Expected %d rows, got %d", rows, matrix->rows);
  ck_assert_msg(matrix->matrix[0][0] == 0, "Expected zero matrix in [0][0] position");
  s21_remove_matrix(matrix);
}
END_TEST

START_TEST(create_matrix_1to3)
{
  int rows = 1;
  int columns = 3;
  res_code_e expected_result = OK;

  matrix_t* matrix = NULL;
  res_code_e return_value = s21_create_matrix(rows, columns, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix != NULL, "Expected matrix to be created, got NULL");
  ck_assert_msg(matrix->columns == columns, "Expected %d columns, got %d", columns, matrix->columns);
  ck_assert_msg(matrix->rows == rows, "Expected %d rows, got %d", rows, matrix->rows);
  ck_assert_msg(matrix->matrix[0][0] == 0, "Expected zero matrix in [0][0] position");
  ck_assert_msg(matrix->matrix[0][1] == 0, "Expected zero matrix in [0][1] position");
  ck_assert_msg(matrix->matrix[0][2] == 0, "Expected zero matrix in [0][2] position");
  s21_remove_matrix(matrix);
}
END_TEST

START_TEST(create_matrix_3to1)
{
  int rows = 3;
  int columns = 1;
  res_code_e expected_result = OK;

  matrix_t* matrix = NULL;
  res_code_e return_value = s21_create_matrix(rows, columns, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix != NULL, "Expected matrix to be created, got NULL");
  ck_assert_msg(matrix->columns == columns, "Expected %d columns, got %d", columns, matrix->columns);
  ck_assert_msg(matrix->rows == rows, "Expected %d rows, got %d", rows, matrix->rows);
  ck_assert_msg(matrix->matrix[0][0] == 0, "Expected zero matrix in [0][0] position");
  ck_assert_msg(matrix->matrix[1][0] == 0, "Expected zero matrix in [1][0] position");
  ck_assert_msg(matrix->matrix[2][0] == 0, "Expected zero matrix in [2][0] position");
  s21_remove_matrix(matrix);
}
END_TEST

START_TEST(create_matrix_3to3)
{
  int rows = 3;
  int columns = 3;
  res_code_e expected_result = OK;

  matrix_t* matrix = NULL;
  res_code_e return_value = s21_create_matrix(rows, columns, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix != NULL, "Expected matrix to be created, got NULL");
  ck_assert_msg(matrix->columns == columns, "Expected %d columns, got %d", columns, matrix->columns);
  ck_assert_msg(matrix->rows == rows, "Expected %d rows, got %d", rows, matrix->rows);
  ck_assert_msg(matrix->matrix[0][0] == 0, "Expected zero matrix in [0][0] position");
  ck_assert_msg(matrix->matrix[0][1] == 0, "Expected zero matrix in [0][1] position");
  ck_assert_msg(matrix->matrix[0][2] == 0, "Expected zero matrix in [0][2] position");
  ck_assert_msg(matrix->matrix[1][0] == 0, "Expected zero matrix in [1][0] position");
  ck_assert_msg(matrix->matrix[1][1] == 0, "Expected zero matrix in [1][1] position");
  ck_assert_msg(matrix->matrix[1][2] == 0, "Expected zero matrix in [1][2] position");
  ck_assert_msg(matrix->matrix[2][0] == 0, "Expected zero matrix in [2][0] position");
  ck_assert_msg(matrix->matrix[2][1] == 0, "Expected zero matrix in [2][1] position");
  ck_assert_msg(matrix->matrix[2][2] == 0, "Expected zero matrix in [2][2] position");
  s21_remove_matrix(matrix);
}
END_TEST

START_TEST(create_matrix_zero_to_positive)
{
  int a = 0;
  int b = 3;
  res_code_e expected_result = INVALID_MATRIX;

  matrix_t* matrix = NULL;
  res_code_e return_value = s21_create_matrix(a, b, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix == NULL, "Expected matrix NOT to be created, got %p", matrix);
  return_value = s21_create_matrix(b, a, matrix);
  ck_assert_msg(return_value == expected_result, "Expected %d return code, got %d", expected_result, return_value);
  ck_assert_msg(matrix == NULL, "Expected matrix NOT to be created, got %p", matrix);
}
END_TEST

START_TEST(create_matrix_zero_to_zero)
{
  matrix_t* matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(0, 0, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
}

START_TEST(create_matrix_negative_to_zero)
{
  matrix_t* matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(-1, 0, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
  ck_assert_int_eq(s21_create_matrix(0, -1, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
}

START_TEST(create_matrix_negative_to_negative)
{
  matrix_t* matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(-1, -1, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
}
END_TEST

START_TEST(create_matrix_negative_to_positive)
{
  matrix_t* matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(-1, 1, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
  ck_assert_int_eq(s21_create_matrix(1, -1, matrix), INVALID_MATRIX);
  ck_assert_ptr_eq(matrix, NULL);
}
END_TEST

START_TEST(create_matrix_not_null_pointer)
{
  matrix_t* matrix = NULL;
  s21_create_matrix(1, 1, matrix);
  ck_assert_int_eq(s21_create_matrix(1, 1, matrix), INVALID_MATRIX);
  ck_assert_ptr_ne(matrix, NULL);
  s21_remove_matrix(matrix);
}
END_TEST

// TODO: Запилить тесты на проверку работы с динамической памятью (ссылка открыта в фаерфоксе)

Suite *s21_create_matrix_suite(void) {
  Suite *s = suite_create("s21_create_matrix_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, create_matrix_1to1);
  tcase_add_test(tc_core, create_matrix_1to3);
  tcase_add_test(tc_core, create_matrix_3to1);
  tcase_add_test(tc_core, create_matrix_3to3);
  tcase_add_test(tc_core, create_matrix_zero_to_positive);
  tcase_add_test(tc_core, create_matrix_zero_to_zero);
  tcase_add_test(tc_core, create_matrix_negative_to_zero);
  tcase_add_test(tc_core, create_matrix_negative_to_negative);
  tcase_add_test(tc_core, create_matrix_negative_to_positive);
  tcase_add_test(tc_core, create_matrix_not_null_pointer);

  suite_add_tcase(s, tc_core);
  return s;
}