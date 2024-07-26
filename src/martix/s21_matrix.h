#ifndef S21_MATRIX_H
#define S21_MATRIX_H

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum return_codes {
  OK = 0,
  INVALID_MATRIX = 1,
  INVALID_CALCULATIONS
} res_code_e;

#endif