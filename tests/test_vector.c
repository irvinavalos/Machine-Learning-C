#include "vector.h"

int main(void) {
  vector v = vec_alloc(5);
  vec_print(v);
  vec_set(v, 2, 1.0);
  vec_print(v);
  vector u = vec_ones(5);
  vec_print(u);
  vec_add(u, v);
  vec_print(u);
  vec_scale(u, 5.0);
  vec_print(u);
  vec_sub(u, v);
  vec_print(u);
  float val = vec_dot(u, v);
  printf("Value: %f\n", val);
  return 0;
}
