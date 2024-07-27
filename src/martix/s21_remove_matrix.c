#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  int code = (A == NULL);
  if (!code) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    A->columns = 0;
    A->rows = 0;
  }
}