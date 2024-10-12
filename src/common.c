#include "s21_matrix.h"
#include <math.h>

void create_sub_matrix(const matrix_t *src, matrix_t *dst, const int base_row, const int base_col) {
  s21_create_matrix(src->rows - 1, src->columns - 1, dst);
  int dst_row = 0;

  for (int i = 0; i < src->rows; i++) {
    if (i == base_row) continue;
    int dst_col = 0;
    for (int j = 0; j < src->columns; j++) {
      if (j == base_col) continue;
      dst->matrix[dst_row][dst_col] = src->matrix[i][j];
      dst_col++;
    }
    dst_row++;
  }

  return;
}

double get_minor(const matrix_t *src, const int row, const int col) {
  matrix_t sub_matrix = {0};

  create_sub_matrix(src, &sub_matrix, row, col);
  double minor = get_determinant(&sub_matrix);
  s21_remove_matrix(&sub_matrix);

  return minor;
}

double get_determinant(const matrix_t *src) {
  double res = 0.0;

  if (src->columns == 1) {
    res = src->matrix[0][0];
  } else if (src->columns == 2) {
    res = src->matrix[0][0] * src->matrix[1][1] - src->matrix[0][1] * src->matrix[1][0];
  } else {
    for (int i = 0; i < src->columns; i++) {
      matrix_t sub_matrix = {0};
      create_sub_matrix(src, &sub_matrix, 0, i);
      double minor = get_determinant(&sub_matrix);
      minor *= pow(-1, i);
      res += minor * src->matrix[0][i];
      s21_remove_matrix(&sub_matrix);
    }
  }

  return res;
}