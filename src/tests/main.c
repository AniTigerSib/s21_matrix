#include "matrix_test.h"

static const char *names[] = {
  "create_matrix_suite",
  "remove_matrix_suite",
  "eq_matrix_suite",
  "sum_matrix_suite",
  "sub_matrix_suite",
  "mult_number_suite",
  "transpose_suite",
  "calc_complements_suite",
  "determinant_suite",
  "inverse_matrix_suite",
};

int main() {
  Suite *suites[] = {
    s21_create_matrix_suite(),
    s21_remove_matrix_suite(),
    s21_eq_matrix_suite(),
    s21_sum_matrix_suite(),
    /*s21_sub_matrix_suite(),
    s21_mult_number_suite(),
    s21_transpose_suite(),
    s21_calc_complements_suite(),
    s21_determinant_suite(),
    s21_inverse_matrix_suite(),*/
  };
  /*-----------------------------------------------------*/
  // int number_failed = 0;
  int n_suites = sizeof(suites) / sizeof(suites[0]);

  for (int i = 0; i < n_suites; i++) {
    char logfile_name[150] = "./logs/";
    strcat(logfile_name, names[i]);
    strcat(logfile_name, ".log");

    SRunner *sr = srunner_create(suites[i]);
    srunner_set_log(sr, logfile_name);
    srunner_run_all(sr, CK_NORMAL);
    // number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  // return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  return 0;
}

// SRunner *sr = srunner_create(NULL);
//   srunner_set_log(sr, "../logs/matrix_test.log");

//   sr = srunner_create(s21_create_matrix_suite());
//   srunner_set_log(sr, "../logs/create_matrix_test.log");
//   srunner_run_all(sr, CK_NORMAL);
//   number_failed += srunner_ntests_failed(sr);
//   srunner_free(sr);

//   srunner_add_suite(sr, s21_create_matrix_suite());
//   srunner_add_suite(sr, s21_remove_matrix_suite());
//   srunner_add_suite(sr, s21_eq_matrix_suite());
//   srunner_add_suite(sr, s21_sum_matrix_suite());
//   srunner_add_suite(sr, s21_sub_matrix_suite());
//   srunner_add_suite(sr, s21_mult_number_suite());
//   srunner_add_suite(sr, s21_mult_matrix_suite());
//   srunner_add_suite(sr, s21_transpose_suite());
//   srunner_add_suite(sr, s21_calc_complements_suite());
//   srunner_add_suite(sr, s21_determinant_suite());
//   srunner_add_suite(sr, s21_inverse_matrix_suite());

//   srunner_run_all(sr, CK_NORMAL);
//   number_failed = srunner_ntests_failed(sr);
//   srunner_free(sr);