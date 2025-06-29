#ifndef VECTOR_H

#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  size_t dim;
  float *ele;
} vector;

#define VEC_GET_AT(vec, idx) vec.ele[idx]
#define VEC_SET_AT(vec, idx, val) vec.ele[idx] = val

vector vec_alloc(size_t dim);

void vec_free(vector vec);

float vec_get(vector vec, size_t idx);

void vec_set(vector vec, size_t idx, float val);

void vec_print(vector vec);

vector vec_ones(size_t dim);

void vec_scale(vector vec, float val);

void vec_add(vector dst, vector src);

void vec_sub(vector dst, vector src);

float vec_dot(vector vec1, vector vec2);

float vec_l1_norm(vector vec);

float vec_l2_norm(vector vec);

float vec_angle_btw(vector dst, vector src);

int vec_are_orthogonal(vector dst, vector src);

int vec_are_orthonormal(vector dst, vector src);

#endif // !VECTOR_H
