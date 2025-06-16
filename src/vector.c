#include "vector.h"

vector vec_alloc(size_t dim) {
  if (dim <= 0) {
    printf("Invalid dimension, %zu must be greater than or equal to 0", dim);
    exit(EXIT_FAILURE);
  }
  vector vec;
  vec.dim = dim;
  vec.ele = malloc(dim * sizeof(*vec.ele));
  return vec;
}

void vec_free(vector vec) {
  if (vec.ele == NULL) {
    printf("Input vector must not be empty");
    exit(EXIT_FAILURE);
  }
  vec.dim = 0;
  free(vec.ele);
  vec.ele = NULL;
}

float vec_get(vector vec, size_t idx) {
  if (idx >= vec.dim) {
    printf("Index out of bounds");
    exit(EXIT_FAILURE);
  }
  return vec.ele[idx];
}

void vec_print(vector vec) {
  if (vec.ele == NULL) {
    printf("Input vector must not be empty");
    exit(EXIT_FAILURE);
  }
  printf("(");
  for (size_t i = 0; i < vec.dim; i++) {
    float val = VEC_GET_AT(vec, i);
    if (i == vec.dim - 1) {
      printf("%f)\n", val);
    } else {
      printf("%f, ", val);
    }
  }
}

void vec_set(vector vec, size_t idx, float val) {
  if (idx >= vec.dim) {
    printf("Index out of bounds");
    exit(EXIT_FAILURE);
  } else if (vec.ele == NULL) {
    printf("Input vector must not be empty");
    exit(EXIT_FAILURE);
  }
  VEC_SET_AT(vec, idx, val);
}

vector vec_ones(size_t dim) {
  if (dim <= 0) {
    printf("Invalid dimension, %zu must be greater than or equal to 0", dim);
    exit(EXIT_FAILURE);
  }
  vector vec = vec_alloc(dim);
  for (size_t i = 0; i < dim; i++) {
    VEC_SET_AT(vec, i, 1.0);
  }
  return vec;
}

void vec_scale(vector vec, float val) {
  if (vec.ele == NULL) {
    printf("Input vector must not be empty");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < vec.dim; i++) {
    VEC_SET_AT(vec, i, VEC_GET_AT(vec, i) * val);
  }
}

void vec_add(vector dst, vector src) {
  if (dst.ele == NULL) {
    printf("Destination vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (src.ele == NULL) {
    printf("Source vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (dst.dim != src.dim) {
    printf("Both vectors must have the same dimension");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < dst.dim; i++) {
    VEC_SET_AT(dst, i, VEC_GET_AT(dst, i) + VEC_GET_AT(src, i));
  }
}

void vec_sub(vector dst, vector src) {
  if (dst.ele == NULL) {
    printf("Destination vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (src.ele == NULL) {
    printf("Source vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (dst.dim != src.dim) {
    printf("Both vectors must have the same dimension");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < dst.dim; i++) {
    VEC_SET_AT(dst, i, VEC_GET_AT(dst, i) - VEC_GET_AT(src, i));
  }
}

vector vec_dot(vector vec1, vector vec2) {
  if (vec1.ele == NULL) {
    printf("Destination vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (vec2.ele == NULL) {
    printf("Source vector must not be empty");
    exit(EXIT_FAILURE);
  } else if (vec1.dim != vec2.dim) {
    printf("Both vectors must have the same dimension");
    exit(EXIT_FAILURE);
  }
  vector ret = vec_alloc(vec1.dim);
  for(size_t i = 0; i < ret.dim; i++) {
    VEC_SET_AT(ret, i, VEC_GET_AT(vec1, i) * VEC_GET_AT(vec2, i));
  }
  return ret;
}
