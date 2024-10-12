#include "s21_matrix.h"

#include <math.h>

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-10
#define is_equal(a, b) (fabs(a - b) < EPSILON)

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = 0;

  result = !(A == NULL || B == NULL) * SUCCESS;

  if (result) {
    result = A->rows == B->rows * SUCCESS;
    result *= (A->columns == B->columns * SUCCESS);
  }

  if (result) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result *= is_equal(A->matrix[i][j], B->matrix[i][j]) * SUCCESS;
      }
    }
  }

  return result;
}