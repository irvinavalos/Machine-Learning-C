#include "matrix.h"

const char *mat_strerror(mat_status stat) {
  switch (stat) {
  case MAT_OK:
    return "success";
  case MAT_ERR_OOB:
    return "index out of bounds";
  case MAT_ERR_SHAPE:
    return "shape mismatch";
  case MAT_ERR_ALLOC:
    return "memory allocation failed";
  case MAT_ERR_NULL:
    return "NULL pointer argument";
  case MAT_ERR_SINGULAR:
    return "matrix is singular / not invertible";
  default:
    return "unknown matrix error";
  }
}

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
        printf("%.2f|\n", MAT_GET_AT(mat, i, j));
      } else {
        printf("%.2f ", MAT_GET_AT(mat, i, j));
      }
    }
  }
}

matrix mat_copy(matrix mat) {
  if (mat.ele == NULL) {
    printf("Input matrix cannot be empty\n");
    exit(1);
  }
  matrix ret = mat_alloc(mat.row, mat.row);
  for (size_t i = 0; i < mat.row; i++) {
    for (size_t j = 0; j < mat.col; j++) {
      MAT_SET_AT(ret, i, j, MAT_GET_AT(mat, i, j));
    }
  }
  return ret;
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

int mat_are_equal(matrix mat1, matrix mat2) {
  if (mat1.col > mat2.col) {
    printf("Number of columns in matrix 1 is greater than matrix 2\n");
    exit(1);
  } else if (mat1.col < mat2.col) {
    printf("Number of columns in matrix 2 is greater than matrix 1\n");
    exit(1);
  } else if (mat1.row > mat2.row) {
    printf("Number of rows in matrix 1 is greater than matrix 2\n");
    exit(1);
  } else if (mat1.row < mat2.row) {
    printf("Number of rows in matrix 2 is greater than matrix 1\n");
    exit(1);
  } else if (mat1.ele == NULL) {
    printf("Matrix 1 cannot be empty\n");
    exit(1);
  } else if (mat2.ele == NULL) {
    printf("Matrix 1 cannot be empty\n");
    exit(1);
  }
  int ret = 0;
  for (size_t i = 0; i < mat1.row; i++) {
    for (size_t j = 0; j < mat1.col; j++) {
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
  if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  int ret = 0;
  if (mat.dim == 4) {
    float res = mat.ele[0] * mat.ele[3] - mat.ele[1] * mat.ele[2];
    if (res > 0) {
      ret = 1;
    }
  }
  // TODO: mat.dim > 4
  return ret;
}

matrix mat_get_inverse(matrix mat) {
  if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  matrix ret = mat_alloc(mat.row, mat.col);
  if (mat.dim == 4) {
    float det = mat.ele[0] * mat.ele[3] - mat.ele[1] * mat.ele[2];
    ret.ele[0] = mat.ele[3];
    ret.ele[1] = -1.0 * mat.ele[1];
    ret.ele[2] = -1.0 * mat.ele[2];
    ret.ele[0] = mat.ele[0];
    for (size_t i = 0; i < ret.row; i++) {
      for (size_t j = 0; j < ret.col; j++) {
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
  if (row >= mat.row) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  vector ret = vec_alloc(mat.col);
  for (size_t i = 0; i < mat.col; i++) {
    float val = MAT_GET_AT(mat, row, i);
    VEC_SET_AT(ret, i, val);
  }
  return ret;
}

vector mat_get_col(matrix mat, size_t col) {
  if (col >= mat.col) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  }
  vector ret = vec_alloc(mat.row);
  for (size_t i = 0; i < mat.row; i++) {
    float val = MAT_GET_AT(mat, i, col);
    VEC_SET_AT(ret, i, val);
  }
  return ret;
}

void mat_set_row(matrix mat, vector src, size_t row) {
  if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Vector cannot be empty\n");
    exit(1);
  } else if (row >= mat.row) {
    printf("Out of bounds row index\n");
    exit(1);
  } else if (mat.col != src.dim) {
    printf("Number of column entries in matrix does not match dimension of the "
           "row vector\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.col; i++) {
    float val = VEC_GET_AT(src, i);
    MAT_SET_AT(mat, row, i, val);
  }
}

void mat_set_col(matrix mat, vector src, size_t col) {
  if (mat.ele == NULL) {
    printf("Matrix cannot be empty\n");
    exit(1);
  } else if (src.ele == NULL) {
    printf("Vector cannot be empty\n");
    exit(1);
  } else if (col >= mat.col) {
    printf("Out of bounds column index\n");
    exit(1);
  } else if (mat.row != src.dim) {
    printf("Number of row entries in matrix does not match dimension of the "
           "column vector\n");
    exit(1);
  }
  for (size_t i = 0; i < mat.row; i++) {
    float val = VEC_GET_AT(src, i);
    MAT_SET_AT(mat, i, col, val);
  }
}
