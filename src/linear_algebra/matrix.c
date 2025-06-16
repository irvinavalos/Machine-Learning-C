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
    printf("Input matrix cannot be empty\n");
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
    printf("Row index out of bounds\n");
    exit(1);
  } else if (col >= mat.col) {
    printf("Column index out of bounds\n");
    exit(1);
  }
  return MAT_GET_AT(mat, row, col);
}

void mat_set(matrix mat, size_t row, size_t col, float val) {
  if (row >= mat.row) {
    printf("Row index out of bounds\n");
    exit(1);
  } else if (col >= mat.col) {
    printf("Column index out of bounds\n");
    exit(1);
  }
  MAT_SET_AT(mat, row, col, val);
}

void mat_print(matrix mat) {
  if (mat.ele == NULL) {
    printf("Input matrix cannot be empty\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.row; i++) {
    printf("|");
    for (size_t j = 0; j < mat.col; j++) {
      if (j == mat.col - 1) {
        printf("%f|\n", MAT_GET_AT(mat, i, j));
      } else {
        printf("%f ", MAT_GET_AT(mat, i, j));
      }
    }
  }
}

matrix mat_ident(size_t row, size_t col) {
  matrix mat = mat_alloc(row, col);
  for (size_t i = 0; i < row; i++) {
    for (size_t j = 0; j < col; j++) {
      if (i == j) {
        MAT_SET_AT(mat, i, j, 1.0);
      } else {
        MAT_SET_AT(mat, i, j, 0.0);
      }
    }
  }
  return mat;
}

void mat_scale(matrix mat, float val) {
  if (mat.ele == NULL) {
    printf("Input matrix cannot be empty\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.row; i++) {
    for (size_t j = 0; j < mat.col; j++) {
      MAT_SET_AT(mat, i, j, MAT_GET_AT(mat, i, j) * val);
    }
  }
}

void mat_add(matrix dst, matrix src) {
  if (dst.ele == NULL) {
    printf("Destination matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Source matrix cannot be empty\n");
    exit(1);
  } else if (dst.dim != src.dim) {
    printf("Both matrices must have the same dimension\n");
    exit(1);
  }
  for (size_t i = 0; i < dst.row; i++) {
    for (size_t j = 0; j < dst.col; j++) {
      MAT_SET_AT(dst, i, j, MAT_GET_AT(dst, i, j) + MAT_GET_AT(src, i, j));
    }
  }
}

void mat_sub(matrix dst, matrix src) {
  if (dst.ele == NULL) {
    printf("Destination matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Source matrix cannot be empty\n");
    exit(1);
  } else if (dst.dim != src.dim) {
    printf("Both matrices must have the same dimension\n");
    exit(1);
  }
  for (size_t i = 0; i < dst.row; i++) {
    for (size_t j = 0; j < dst.col; j++) {
      MAT_SET_AT(dst, i, j, MAT_GET_AT(dst, i, j) - MAT_GET_AT(src, i, j));
    }
  }
}

matrix mat_mult(matrix dst, matrix src) {
  if (dst.col != src.row) {
    printf("Row dimension of destintation matrix does not match the column "
           "dimension of the source matrix\n");
    exit(1);
  } else if (dst.ele == NULL) {
    printf("Destination matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Source matrix cannot be empty\n");
    exit(1);
  }
  matrix ret = mat_alloc(dst.row, src.col);
  for (size_t i = 0; i < ret.col; i++) {
    for (size_t j = 0; j < ret.row; j++) {
      for (size_t k = 0; k < src.row; k++) {
        MAT_SET_AT(ret, i, j, MAT_GET_AT(dst, i, k) * MAT_GET_AT(src, k, j));
      }
    }
  }
  return ret;
}

int mat_are_equal(matrix mat1, matrix mat2);

int mat_is_invertible(matrix mat);

matrix mat_get_inverse(matrix mat);

matrix mat_transpose(matrix mat);

int mat_is_symmetric(matrix mat);

vector mat_get_row(matrix mat, size_t row);

vector mat_get_col(matrix mat, size_t col);

void mat_set_row(matrix mat, vector src, size_t row);

void mat_set_col(matrix mat, vector src, size_t row);
