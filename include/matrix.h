#ifndef MATRIX_H

#define MATRIX_H

#include "vector.h"

typedef struct {
  float *ele;
  size_t row;
  size_t col;
  size_t dim;
} matrix;

#define MAT_GET_AT(mat, row, col) mat.ele[row * mat.col + col]
#define MAT_SET_AT(mat, row, col, val) mat.ele[row * mat.col + col] = val

matrix mat_alloc(size_t row, size_t col);

void mat_free(matrix mat);

float mat_get(matrix mat, size_t row, size_t col);

void mat_set(matrix mat, size_t row, size_t col, float val);

void mat_print(matrix mat);

matrix mat_ident(size_t row, size_t col);

void mat_scale(matrix mat, float val);

void mat_add(matrix dst, matrix src);

void mat_sub(matrix dst, matrix src);

float vec_dot(vector vec1, vector vec2);

#endif // !MATRIX_H
