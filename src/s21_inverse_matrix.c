#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  res_code_e ret = OK;
  double det = 0;

  ret = (A == NULL || result == NULL) * ERROR;

  if (ret == OK) ret = (A->rows != A->columns) * CALC_ERROR;
  if (ret == OK) {
    det = get_determinant(A);
    if (det == 0)
      ret = CALC_ERROR;
    else
      det = 1 / det;
  }
  if (ret == OK) {
    if (A->columns == 1) {
      ret = s21_create_matrix(1, 1, result);
      if (ret == OK) result->matrix[0][0] = det;
    } else {
      matrix_t algebraic = {0};
      if (ret == OK) ret = s21_calc_complements(A, &algebraic);
      matrix_t transposed = {0};
      if (ret == OK) ret = s21_transpose(&algebraic, &transposed);
      if (ret == OK) ret = s21_mult_number(&transposed, det, result);

      s21_remove_matrix(&algebraic);
      s21_remove_matrix(&transposed);
    }
  }
  return ret;
}

// int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
//   res_code_e ret = OK;
//   double det = 0;

//   ret = (A == NULL || result == NULL) * ERROR;

//   if (ret == OK) ret = (A->rows != A->columns) * CALC_ERROR;
//   if (ret == OK) {
//     det = get_determinant(A);
//     if (det == 0)
//       ret = CALC_ERROR;
//     else
//       det = 1 / det;
//   }
//   if (A->columns > 1) {
//     matrix_t algebraic = {0};
//     if (ret == OK) ret = s21_calc_complements(A, &algebraic);
//     matrix_t transposed = {0};
//     if (ret == OK) ret = s21_transpose(&algebraic, &transposed);
//     if (ret == OK) ret = s21_mult_number(&transposed, det, result);
//     s21_remove_matrix(&algebraic);
//     s21_remove_matrix(&transposed);
//   } else {
//     ret = s21_create_matrix(1, 1, result);
//     if (ret == OK) result->matrix[0][0] = det;
//   }

//   return ret;
// }