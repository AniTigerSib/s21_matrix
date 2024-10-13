#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  res_code_e ret = OK;
  double det = 0;

  ret = (A == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = (A->rows != A->columns) * CALC_ERROR;
  if (ret == OK) {
    det = get_determinant(A);
    if (det == 0) ret = CALC_ERROR;
    else det = 1 / det;
  }
  matrix_t algebraic = {0};
  if (ret == OK) ret = s21_calc_complements(A, &algebraic);
  matrix_t transposed = {0};
  if (ret == OK) ret = s21_transpose(&algebraic, &transposed);
  if (ret == OK) ret = s21_mult_number(&transposed, det, result);

  s21_remove_matrix(&algebraic);
  s21_remove_matrix(&transposed);
  return ret;
}