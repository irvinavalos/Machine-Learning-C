#include "matrix.h"

matrix mat_alloc(size_t row, size_t col) {
  matrix mat;
  mat.row = row;
  mat.col = col;
  mat.dim = row * col;
  mat.ele = malloc(row * col * sizeof(*mat.ele));
  return mat;
}

void mat_free(matrix mat) {
  if (mat.ele == NULL) {
    printf("Input matrix cannot be empty");
    exit(1);
  }
  mat.row = 0;
  mat.col = 0;
  mat.dim = 0;
  mat.ele = NULL;
  free(mat.ele);
}

float mat_get(matrix mat, size_t row, size_t col) {
  if (row >= mat.row) {
    printf("Row index out of bounds");
    exit(1);
  } else if (col >= mat.col) {
    printf("Column index out of bounds");
    exit(1);
  }
  return MAT_GET_AT(mat, row, col);
}

void mat_set(matrix mat, size_t row, size_t col, float val) {
  if (row >= mat.row) {
    printf("Row index out of bounds");
    exit(1);
  } else if (col >= mat.col) {
    printf("Column index out of bounds");
    exit(1);
  }
  MAT_SET_AT(mat, row, col, val);
}

void mat_print(matrix mat) {
  if (mat.ele == NULL) {
    printf("Input matrix cannot be empty");
    exit(1);
  }
  for (size_t i = 0; i < mat.row; i++) {
    printf("|");
    for (size_t j = 0; j < mat.col; j++) {
      if (j == mat.col - 1) {
        printf("%f|\n", MAT_GET_AT(mat, i, j));
      } else {
        printf("%f, ", MAT_GET_AT(mat, i, j));
      }
    }
  }
}

matrix mat_ident(size_t row, size_t col);

void mat_scale(matrix mat, float val);

void mat_add(matrix dst, matrix src);

void mat_sub(matrix dst, matrix src);

void mat_mult(matrix dst, matrix src);
