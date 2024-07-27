#include "matrix_test.h"

#include "../martix/s21_matrix.h"

START_TEST(remove_matrix_normal)
{
  matrix_t *matrix = NULL;
  s21_create_matrix(3, 3, matrix);
  s21_remove_matrix(matrix);
  ck_assert_ptr_null(matrix);
}

START_TEST(remove_matrix_null_pointer)
{
  matrix_t *matrix = NULL;
  s21_remove_matrix(matrix);
  ck_assert_ptr_null(matrix);
}

Suite *s21_remove_matrix_suite(void) {
  Suite *s = suite_create("s21_remove_matrix_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, remove_matrix_normal);
  tcase_add_test(tc_core, remove_matrix_null_pointer);

  suite_add_tcase(s, tc_core);
  return s;
}