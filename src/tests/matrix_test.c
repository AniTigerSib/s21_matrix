#include "matrix_test.h"

#include <stdlib.h>

int main() {
  int number_failed = 0;
  SRunner *sr = srunner_create(NULL);
  srunner_set_log(sr, "../logs/matrix_test.log");

  srunner_add_suite(sr, s21_create_matrix_suite());
  srunner_add_suite(sr, s21_remove_matrix_suite());
  srunner_add_suite(sr, s21_eq_matrix_suite());
  srunner_add_suite(sr, s21_sum_matrix_suite());
  srunner_add_suite(sr, s21_sub_matrix_suite());
  srunner_add_suite(sr, s21_mult_number_suite());
  srunner_add_suite(sr, s21_mult_matrix_suite());
  srunner_add_suite(sr, s21_transpose_suite());
  srunner_add_suite(sr, s21_calc_complements_suite());
  srunner_add_suite(sr, s21_determinant_suite());
  srunner_add_suite(sr, s21_inverse_matrix_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}