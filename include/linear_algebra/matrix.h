#ifndef MATRIX_H

#define MATRIX_H

#include "vector.h"

typedef struct {
  float *ele;
  size_t row;
  size_t col;
  size_t dim;
} matrix;

#define MAT_GET_AT(m, r, c) (m.ele[r * m.col + c])
#define MAT_SET_AT(m, r, c, val) m.ele[r * m.col + c] = val

matrix mat_alloc(size_t row, size_t col);

void mat_free(matrix mat);

float mat_get(matrix mat, size_t row, size_t col);

void mat_set(matrix mat, size_t row, size_t col, float val);

void mat_print(matrix mat);

matrix mat_ident(size_t row, size_t col);

void mat_scale(matrix mat, float val);

void mat_add(matrix dst, matrix src);

void mat_sub(matrix dst, matrix src);

matrix mat_mult(matrix dst, matrix src);

int mat_is_invertible(matrix mat);

matrix mat_get_inverse(matrix mat);

matrix mat_transpose(matrix mat);

int mat_is_symmetric(matrix mat);

vector mat_get_row(matrix mat, size_t row);

vector mat_get_col(matrix mat, size_t col);

void mat_set_row(matrix mat, vector src, size_t row);

void mat_set_col(matrix mat, vector src, size_t row);


#endif // !MATRIX_H
