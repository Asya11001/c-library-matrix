#include "../headers/s21_common.h"

void s21_remove_matrix(matrix_t *matrix) {
  if (matrix) {
    if (matrix->matrix) {
      for (int rowIndex = 0; rowIndex < matrix->rows; ++rowIndex) {
        free(matrix->matrix[rowIndex]);
        matrix->matrix[rowIndex] = NULL;
      }
      free(matrix->matrix);
      matrix->matrix = NULL;
    }
    matrix->rows = 0;
    matrix->columns = 0;
  }
}