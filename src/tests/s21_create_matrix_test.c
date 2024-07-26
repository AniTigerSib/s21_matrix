#include "matrix_test.h"

#include "../martix/s21_matrix.h"

START_TEST(create_matrix_1to1)
{
  matrix_t* matrix = NULL;
  ck_assert_int_eq(s21_create_matrix(1, 1, matrix), OK);
  ck_assert_ptr_nonnull(matrix);
  ck_assert_int_eq(matrix->rows, 1);
  ck_assert_int_eq(matrix->columns, 1);
  ck_assert_int_eq(matrix->matrix[0][0], 0);
  s21_remove_matrix(matrix);
}
END_TEST



Suite *s21_create_matrix_suite(void) {
  Suite *s = suite_create("s21_create_matrix_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, create_matrix_1to1);

  suite_add_tcase(s, tc_core);
  return s;
}