#ifndef MATRIX_H
#define MATRIX_H

#include "matrix_status.h"
#include "vector.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  size_t rows;
  size_t cols;
  float *data;
} matrix;

#define MAT_INDEX(m, r, c) (r) * (m)->cols + (c)

/*
 * Allocation/Destruction functionality
 */

mat_status mat_alloc(matrix *mat, size_t ro, size_t co);

void mat_free(matrix *mat);

/*
 * Element helper functions
 */

static inline float mat_get(const matrix *mat, size_t ro, size_t co) {
  return mat->data[MAT_INDEX(mat, ro, co)];
}

static inline void mat_set(matrix *mat, size_t ro, size_t co, float val) {
  mat->data[MAT_INDEX(mat, ro, co)] = val;
}

/*
 * Matrix creation
 */

matrix mat_zeros(size_t ro, size_t co);

matrix mat_ident(size_t ro, size_t co);

/*
 * Utility
 */

mat_status mat_copy(matrix *dst, const matrix *src);

void mat_print(matrix mat);

/*
 * Matrix operations
 */

mat_status mat_scale(matrix *mat, float sca);

mat_status mat_apply(matrix *mat, float (*f)(float));

mat_status mat_eq_shape(matrix *mat1, matrix *mat2);

mat_status mat_add(matrix *dst, matrix *src);

mat_status mat_sub(matrix *dst, matrix *src);

mat_status mat_mult(matrix *out, const matrix *mat1, const matrix *mat2);

bool mat_equal(const matrix *mat1, const matrix *mat2, float eps);

bool mat_is_invertible(const matrix *mat);

mat_status mat_inverse_2x2(matrix *out, const matrix *src);

matrix mat_transpose(matrix mat);

int mat_is_symmetric(matrix mat);

vector mat_get_row(matrix mat, size_t row);

vector mat_get_col(matrix mat, size_t col);

void mat_set_row(matrix mat, vector src, size_t row);

void mat_set_col(matrix mat, vector src, size_t col);

#endif // !MATRIX_H
