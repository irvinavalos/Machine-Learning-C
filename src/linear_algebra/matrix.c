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
  matrix m = {0};
  if (mat_alloc(&m, ro, co) == MAT_OK) {
    memset(m.data, 0, ro * co * sizeof(float));
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

static float mat_get(const matrix *mat, size_t ro, size_t co) {
  return mat->data[MAT_INDEX(mat, ro, co)];
}

static void mat_set(matrix *mat, size_t ro, size_t co, float val) {
  mat->data[MAT_INDEX(mat, ro, co)] = val;
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
        printf("%.2f|\n", MAT_GET_AT(mat, i, j));
      } else {
        printf("%.2f ", MAT_GET_AT(mat, i, j));
      }
    }
  }
}

// matrix mat_ident(size_t row, size_t col) {
//   matrix mat = mat_alloc(row, col);
//   for (size_t i = 0; i < row; i++) {
//     for (size_t j = 0; j < col; j++) {
//       if (i == j) {
//         MAT_SET_AT(mat, i, j, 1.0);
//       } else {
//         MAT_SET_AT(mat, i, j, 0.0);
//       }
//     }
//   }
//   return mat;
// }

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

int mat_are_equal(matrix mat1, matrix mat2) {
  if (mat1.cols > mat2.cols) {
    printf("Number of columns in matrix 1 is greater than matrix 2\n");
    exit(1);
  } else if (mat1.cols < mat2.cols) {
    printf("Number of columns in matrix 2 is greater than matrix 1\n");
    exit(1);
  } else if (mat1.rows > mat2.rows) {
    printf("Number of rows in matrix 1 is greater than matrix 2\n");
    exit(1);
  } else if (mat1.rows < mat2.rows) {
    printf("Number of rows in matrix 2 is greater than matrix 1\n");
    exit(1);
  } else if (mat1.data == NULL) {
    printf("Matrix 1 cannot be empty\n");
    exit(1);
  } else if (mat2.data == NULL) {
    printf("Matrix 1 cannot be empty\n");
    exit(1);
  }
  int ret = 0;
  for (size_t i = 0; i < mat1.rows; i++) {
    for (size_t j = 0; j < mat1.cols; j++) {
      float val1 = MAT_GET_AT(mat1, i, j);
      float val2 = MAT_GET_AT(mat2, i, j);
      if (val1 != val2) {
        ret = 1;
        return ret;
      }
    }
  }
  return ret;
}

int mat_is_invertible(matrix mat) {
  if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  int ret = 0;
  if (mat.dim == 4) {
    float res = mat.data[0] * mat.data[3] - mat.data[1] * mat.data[2];
    if (res > 0) {
      ret = 1;
    }
  }
  // TODO: mat.dim > 4
  return ret;
}

matrix mat_get_inverse(matrix mat) {
  if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  matrix ret = mat_alloc(mat.rows, mat.cols);
  if (mat.dim == 4) {
    float det = mat.data[0] * mat.data[3] - mat.data[1] * mat.data[2];
    ret.data[0] = mat.data[3];
    ret.data[1] = -1.0 * mat.data[1];
    ret.data[2] = -1.0 * mat.data[2];
    ret.data[0] = mat.data[0];
    for (size_t i = 0; i < ret.rows; i++) {
      for (size_t j = 0; j < ret.cols; j++) {
        float val = MAT_GET_AT(ret, i, j);
        MAT_SET_AT(mat, i, j, 1.0 / det * val);
      }
    }
  }
  // TODO: mat.dim > 4
  return ret;
}

matrix mat_transpose(matrix mat);

int mat_is_symmetric(matrix mat);

vector mat_get_row(matrix mat, size_t row) {
  if (row >= mat.rows) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  vector ret = vec_alloc(mat.cols);
  for (size_t i = 0; i < mat.cols; i++) {
    float val = MAT_GET_AT(mat, row, i);
    VEC_SET_AT(ret, i, val);
  }
  return ret;
}

vector mat_get_col(matrix mat, size_t col) {
  if (col >= mat.cols) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  vector ret = vec_alloc(mat.rows);
  for (size_t i = 0; i < mat.rows; i++) {
    float val = MAT_GET_AT(mat, i, col);
    VEC_SET_AT(ret, i, val);
  }
  return ret;
}

void mat_set_row(matrix mat, vector src, size_t row) {
  if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Vector cannot be empty\n");
    exit(1);
  } else if (row >= mat.rows) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.cols != src.dim) {
    printf("Number of column entries in matrix does not match dimension of the "
           "row vector\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.cols; i++) {
    float val = VEC_GET_AT(src, i);
    MAT_SET_AT(mat, row, i, val);
  }
}

void mat_set_col(matrix mat, vector src, size_t col) {
  if (mat.data == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Vector cannot be empty\n");
    exit(1);
  } else if (col >= mat.cols) {
    printf("Out of bounds column index\n");
    exit(1);
  } else if (mat.rows != src.dim) {
    printf("Number of row entries in matrix does not match dimension of the "
           "column vector\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.rows; i++) {
    float val = VEC_GET_AT(src, i);
    MAT_SET_AT(mat, i, col, val);
  }
}
