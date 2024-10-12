#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  res_code_e ret = OK;

  ret = (A == NULL || B == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = (A->rows != B->columns) * CALC_ERROR;
  if (ret == OK) ret = (A->columns != B->rows) * CALC_ERROR;
  if (ret == OK) ret = s21_create_matrix(A->rows, B->columns, result);
  if (ret == OK) {
    for (int i = 0; i < result->rows; i++) {
      int k = 0;
      for (int j = 0; j < result->columns; j++, k++) {
        result->matrix[i][j] = A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return ret;
}