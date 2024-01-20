#include "../headers/s21_common.h"

int handleMemoryAllocationError(double **matrix, int allocatedSize) {
  int errorCode = 0;
  if (!(matrix)[allocatedSize]) {
    errorCode = 1;
    for (int rowIndex = 0; rowIndex < allocatedSize; ++rowIndex)
      free(matrix[rowIndex]);
    free(matrix);
  }
  return errorCode;
}

int matrixMemoryAllocation(int rows, int columns, double **matrix) {
  int rowIndex;
  int errorCode = errorCode_noError;
  if (matrix == NULL) errorCode = errorCode_errorCreatingResultMatrix;
  for (rowIndex = 0; rowIndex < rows && !errorCode; ++rowIndex) {
    (matrix)[rowIndex] = (double *)calloc(columns, sizeof(double));
    errorCode = handleMemoryAllocationError(matrix, rowIndex);
  }

  return errorCode;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int errorCode = handleReturnValueInputCreateMatrix(rows, columns, result);
  if (errorCode) return errorCode;
  double **matrix = NULL;

  matrix = (double **)calloc(rows, sizeof(double *));

  if (!matrix) {
    errorCode = errorCode_invalidInputMatrices;
  } else {
    errorCode = matrixMemoryAllocation(rows, columns, matrix);
    if (!errorCode) {
      result->matrix = matrix;
      result->rows = rows;
      result->columns = columns;
    } else {
      free(matrix);
    }
  }

  int returnValue = returnValue_Ok;
  if (errorCode) returnValue = returnValue_IncorrectMatrixError;
  return returnValue;
}
