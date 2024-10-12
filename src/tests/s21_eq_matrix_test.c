#include "matrix_test.h"

#include "../s21_matrix.h"

START_TEST(test_eq_matrix_null) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(NULL, &A);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}

START_TEST(test_eq_matrix_identical) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_different_dimensions) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 5.0;
  B.matrix[1][2] = 6.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_same_dimensions_different_elements) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 5.0;  // Different from A

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_1x1) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5.0;
  B.matrix[0][0] = 5.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  B.matrix[0][0] = 5.1;
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_large) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1000, 1000, &A);
  s21_create_matrix(1000, 1000, &B);

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      A.matrix[i][j] = (double)(i * 1000 + j);
      B.matrix[i][j] = (double)(i * 1000 + j);
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  B.matrix[999][999] += 1e-7;
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_empty) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_empty_vs_nonempty) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(1, 1, &B);

  B.matrix[0][0] = 1.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(&B, &A);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_small_float_diff) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0000001;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0000002;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  B.matrix[0][0] = 1.0000001;
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_eq_matrix_same_elements_different_order) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 2.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 3.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *s21_eq_matrix_suite(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_eq_matrix_null);
  tcase_add_test(tc_core, test_eq_matrix_identical);
  tcase_add_test(tc_core, test_eq_matrix_different_dimensions);
  tcase_add_test(tc_core, test_eq_matrix_same_dimensions_different_elements);
  tcase_add_test(tc_core, test_eq_matrix_1x1);
  tcase_add_test(tc_core, test_eq_matrix_large);
  tcase_add_test(tc_core, test_eq_matrix_empty);
  tcase_add_test(tc_core, test_eq_matrix_empty_vs_nonempty);
  tcase_add_test(tc_core, test_eq_matrix_small_float_diff);
  tcase_add_test(tc_core, test_eq_matrix_same_elements_different_order);

  suite_add_tcase(s, tc_core);
  return s;
}