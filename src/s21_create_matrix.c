#include "s21_matrix.h"
#include <string.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) {
    return ERROR;
  }
  memset(result, 0, sizeof(*result));

  int code = 0;

  result->rows = rows;
  result->columns = columns;

  double **temp_matrix = (double **)calloc(rows, sizeof(double *));
  code = (temp_matrix == NULL) * ERROR;
  if (!code) result->matrix = temp_matrix;

  if (!code) {
    double *temp = NULL;
    for (int row = 0; !code && row < rows; row++) {
      temp = (double *)calloc(columns, sizeof(double));
      code = (temp == NULL) * ERROR;
      if (!code) result->matrix[row] = temp;
    }
  }

  if (code) {
    s21_remove_matrix(result);
  }

  return code;
}