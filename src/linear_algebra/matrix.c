#include "matrix.h"

mat_status mat_alloc(matrix *mat, size_t ro, size_t co) {
  if (!mat) {
    return MAT_ERR_NULL;
  }
  if (!(ro && co)) {
    return MAT_ERR_SHAPE;
  }
  if (ro > SIZE_MAX / co) {
    return MAT_ERR_ALLOC;
  }
  mat->data = malloc(ro * co * sizeof(*mat->data));
  if (!mat->data) {
    return MAT_ERR_ALLOC;
  }
  mat->rows = ro;
  mat->cols = co;
  return MAT_OK;
}

void mat_free(matrix *mat) {
  if (!mat || !mat->data) {
    return;
  }
  free(mat->data);
  mat->rows = 0;
  mat->cols = 0;
  mat->data = NULL;
}

matrix mat_zeros(size_t ro, size_t co) {
  matrix m;
  if (mat_alloc(&m, ro, co) == MAT_OK) {
    memset(m.data, 0, ro * co * sizeof(*m.data));
  }
  return m;
}

matrix mat_ident(size_t ro, size_t co) {
  matrix m;
  if (mat_alloc(&m, ro, co) == MAT_OK) {
    memset(m.data, 0, ro * co * sizeof(*m.data));
  }
  for (size_t i = 0; i < m.rows; i++) {
    for (size_t j = 0; j < m.cols; j++) {
      if (i == j) {
        mat_set(&m, i, j, 1.0);
      }
    }
  }
  return m;
}

mat_status mat_copy(matrix *dst, const matrix *src) {
  if (!(dst && src)) {
    return MAT_ERR_NULL;
  }
  if (!(src->data)) {
    return MAT_ERR_NULL;
  }
  if (dst == src) {
    return MAT_OK;
  }
  if (dst->rows != src->rows || dst->cols != src->cols) {
    mat_free(dst);
    if (!(mat_alloc(dst, src->rows, src->cols) == MAT_OK)) {
      return MAT_ERR_ALLOC;
    }
  }
  memcpy(dst->data, src->data, src->rows * src->cols * sizeof(*dst->data));
  return MAT_OK;
}

void mat_print(matrix mat) {
  if (mat.data == NULL) {
    printf("Input matrix cannot be empty\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.rows; i++) {
    printf("|");
    for (size_t j = 0; j < mat.cols; j++) {
      if (j == mat.cols - 1) {
        printf("%.2f|\n", mat_get(&mat, i, j));
      } else {
        printf("%.2f ", mat_get(&mat, i, j));
      }
    }
  }
}

mat_status mat_scale(matrix *mat, float sca) {
  if (!(mat && mat->data)) {
    return MAT_ERR_NULL;
  }
  size_t dim = mat->rows * mat->cols;
  for (size_t i = 0; i < dim; i++) {
    mat->data[i] *= sca;
  }
  return MAT_OK;
}

mat_status mat_apply(matrix *mat, float (*f)(float)) {
  if (!(mat && mat->data && f)) {
    return MAT_ERR_NULL;
  }
  size_t dim = mat->rows * mat->cols;
  for (size_t i = 0; i < dim; i++) {
    mat->data[i] = f(mat->data[i]);
  }
  return MAT_OK;
}

mat_status mat_eq_shape(matrix *mat1, matrix *mat2) {
  if (mat1->rows == mat2->rows && mat1->cols == mat2->cols) {
    return MAT_OK;
  }
  return MAT_ERR_SHAPE;
}

mat_status mat_add(matrix *dst, matrix *src) {
  if (!(dst && src)) {
    return MAT_ERR_NULL;
  }
  if (!(dst->data && src->data)) {
    return MAT_ERR_NULL;
  }
  if (!(mat_eq_shape(dst, src) == MAT_OK)) {
    return MAT_ERR_SHAPE;
  }
  size_t dim = dst->rows * dst->cols;
  for (size_t i = 0; i < dim; i++) {
    dst->data[i] += src->data[i];
  }
  return MAT_OK;
}

mat_status mat_sub(matrix *dst, matrix *src) {
  if (!(dst && src)) {
    return MAT_ERR_NULL;
  }
  if (!(dst->data && src->data)) {
    return MAT_ERR_NULL;
  }
  if (!(mat_eq_shape(dst, src) == MAT_OK)) {
    return MAT_ERR_SHAPE;
  }
  size_t dim = dst->rows * dst->cols;
  for (size_t i = 0; i < dim; i++) {
    dst->data[i] -= src->data[i];
  }
  return MAT_OK;
}

mat_status mat_mult(matrix *out, const matrix *mat1, const matrix *mat2) {
  if (!(out && mat1 && mat2)) {
    return MAT_ERR_NULL;
  }
  if (!(mat1->data && mat2->data)) {
    return MAT_ERR_NULL;
  }
  if (!(mat1->cols == mat2->rows)) {
    return MAT_ERR_SHAPE;
  }
  if (out->rows != mat1->rows || out->cols != mat2->cols) {
    mat_free(out);
    if (!(mat_alloc(out, mat1->rows, mat2->cols) == MAT_OK)) {
      return MAT_ERR_ALLOC;
    }
  }
  for (size_t i = 0; i < out->rows; i++) {
    for (size_t j = 0; j < out->cols; j++) {
      float sum = 0.0;
      for (size_t k = 0; k < mat1->cols; i++) {
        sum += mat_get(mat1, i, k) * mat_get(mat2, k, j);
      }
      mat_set(out, i, j, sum);
    }
  }
  return MAT_OK;
}

bool mat_equal(const matrix *mat1, const matrix *mat2, float eps) {
  if (!mat1 || !mat2 || !mat1->data || !mat2->data) {
    return false;
  }
  if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
    return false;
  }
  size_t dim = mat1->rows * mat1->cols;
  for (size_t i = 0; i < dim; i++) {
    if (fabs(mat1->data[i] - mat2->data[i]) > eps) {
      return false;
    }
  }
  return true;
}

bool mat_is_invertible(const matrix *mat) {
  if (!mat || !mat->data) {
    return false;
  }
  if (mat->rows != mat->cols) {
    return false;
  }
  if (mat->rows == 2) {
    float det = mat->data[0] * mat->data[3] - mat->data[1] * mat->data[2];
    return (fabsf(det) > 1e-6f);
  }
  // TODO: determinant for matrices larger than 2x2
  return false;
}

mat_status mat_inverse_2x2(matrix *out, const matrix *src) {
  if (!(out && src)) {
    return MAT_ERR_NULL;
  }
  if (!(src->data)) {
    return MAT_ERR_NULL;
  }
  if (!(src->rows == 2 && src->cols == 2)) {
    return MAT_ERR_SHAPE;
  }
  float det = src->data[0] * src->data[3] - src->data[1] * src->data[2];
  if (!(fabsf(det) > 1e-6f)) {
    return MAT_ERR_SINGULAR;
  }
  if (out->rows != 2 || out->cols != 2) {
    mat_free(out);
    if (!(mat_alloc(out, 2, 2) == MAT_OK)) {
      return MAT_ERR_ALLOC;
    }
  }
  out->data[0] = src->data[3] / det;
  out->data[1] = -src->data[1] / det;
  out->data[2] = -src->data[2] / det;
  out->data[3] = src->data[0] / det;
  return MAT_OK;
}

mat_status mat_inverse(matrix *out, const matrix *src);

mat_status mat_transpose(matrix *out, const matrix *src) {
  if (!(out && src)) {
    return MAT_ERR_NULL;
  }
  if (!(src->data)) {
    return MAT_ERR_NULL;
  }
  if (out->rows != src->cols || out->cols != src->rows) {
    return MAT_ERR_SHAPE;
  }
  for (size_t i = 0; i < out->rows; i++) {
    for (size_t j = 0; j < out->cols; j++) {
      mat_set(out, j, i, mat_get(src, i, j));
    }
  }
  return MAT_OK;
}

int mat_is_symmetric(matrix mat);
