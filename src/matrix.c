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
  mat.row = 0;
  mat.col = 0;
  mat.dim = 0;
  mat.ele = NULL;
  free(mat.ele);
}
