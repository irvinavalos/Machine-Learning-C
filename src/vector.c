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
