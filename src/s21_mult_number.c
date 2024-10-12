#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  res_code_e ret = OK;

  ret = (A == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = s21_create_matrix(A->rows, A->columns, result);
  if (ret == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return ret;
}