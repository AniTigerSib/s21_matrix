#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  int rows = 0;
  int code = (A == NULL);

  if (!code) {
    rows = A->rows;
    A->columns = 0;
    A->rows = 0;
    code = (A->matrix == NULL);
  }

  if (!code) {
    for (int i = 0; i < rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}