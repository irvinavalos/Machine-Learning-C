#ifndef MATRIX_H
#define MATRIX_H

#include "matrix_status.h"
#include "vector.h"
#include <stdint.h>
#include <string.h>

typedef struct {
  size_t rows;
  size_t cols;
  float *data;
} matrix;

#define MAT_INDEX(m, r, c) (r) * (m)->cols + (c)

mat_status mat_alloc(matrix *mat, size_t ro, size_t co);

void mat_free(matrix *mat);

matrix mat_zeros(size_t ro, size_t co);

mat_status mat_copy(matrix *dst, const matrix *src);

static float mat_get(const matrix *mat, size_t ro, size_t co);

static void mat_set(matrix *mat, size_t ro, size_t co, float val);

void mat_print(matrix mat);

// matrix mat_ident(size_t row, size_t col);

mat_status mat_scale(matrix *mat, float sca);

mat_status mat_apply(matrix *mat, float (*f)(float));

mat_status mat_eq_shape(matrix *mat1, matrix *mat2);

mat_status mat_add(matrix *dst, matrix *src);

mat_status mat_sub(matrix *dst, matrix *src);

mat_status mat_mult(matrix *out, const matrix *mat1, const matrix *mat2);

int mat_are_equal(matrix mat1, matrix mat2);

int mat_is_invertible(matrix mat);

matrix mat_get_inverse(matrix mat);

matrix mat_transpose(matrix mat);

int mat_is_symmetric(matrix mat);

vector mat_get_row(matrix mat, size_t row);

vector mat_get_col(matrix mat, size_t col);

void mat_set_row(matrix mat, vector src, size_t row);

void mat_set_col(matrix mat, vector src, size_t col);

#endif // !MATRIX_H
