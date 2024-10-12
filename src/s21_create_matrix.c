#include "s21_matrix.h"
#include <string.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) {
    return ERROR;
  }
  memset(result, 0, sizeof(*result));

  res_code_e code = OK;

  result->rows = rows;
  result->columns = columns;

  double **temp_matrix = (double **)calloc(rows, sizeof(double *));
  code = (temp_matrix == NULL) * ERROR;
  if (code == OK) result->matrix = temp_matrix;

  if (code == OK) {
    double *temp = NULL;
    for (int row = 0; !code && row < rows; row++) {
      temp = (double *)calloc(columns, sizeof(double));
      code = (temp == NULL) * ERROR;
      if (code == OK) result->matrix[row] = temp;
    }
  }

  if (code != OK) {
    s21_remove_matrix(result);
  }

  return code;
}