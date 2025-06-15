#ifndef VECTOR_H

#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t dim;
  float *ele;
} vector;

#define VEC_GET_AT(vec, idx) (vec.ele[idx]);
#define VEC_SET_AT(vec, idx, val) (vec.ele[idx] = val);

vector vec_alloc(size_t dim);

void vec_free(vector vec);

float vec_get(vector vec, size_t idx);

void vec_set(vector vec, size_t idx, float val);

void vec_print(vector vec);

#endif // !VECTOR_H
