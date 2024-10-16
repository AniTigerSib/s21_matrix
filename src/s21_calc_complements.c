#include <math.h>

#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  res_code_e ret = OK;

  ret = (A == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = (A->rows != A->columns) * CALC_ERROR;
  if (ret == OK) ret = s21_create_matrix(A->rows, A->columns, result);
  if (ret == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double minor = get_minor(A, i, j);
        minor *= pow(-1, i + j);
        result->matrix[i][j] = minor;
      }
    }
  }

  return ret;
}