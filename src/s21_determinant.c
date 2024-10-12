#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  res_code_e ret = OK;

  ret = (A == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = (A->rows != A->columns) * CALC_ERROR;
  if (ret == OK) {
    *result = get_determinant(A);
  }

  return ret;
}