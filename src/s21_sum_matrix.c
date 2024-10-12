#include "s21_matrix.h"
#include <stdio.h>

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  res_code_e ret = OK;

  ret = (A == NULL || B == NULL || result == NULL) * ERROR;

  if (!ret) ret = (A->rows != B->rows) * CALC_ERROR;
  if (!ret) ret = (A->columns != B->columns) * CALC_ERROR;

  if (!ret) ret = s21_create_matrix(A->rows, A->columns, result);

  if (!ret) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return ret;
}