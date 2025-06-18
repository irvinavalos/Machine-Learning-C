#include "mnist_data.h"

int main(void) {
  // vector v = vec_alloc(5);
  // vec_print(v);
  // vec_set(v, 2, 1.0);
  // vec_print(v);
  // vector u = vec_ones(5);
  // vec_print(u);
  // vec_add(u, v);
  // vec_print(u);
  // vec_scale(u, 5.0);
  // vec_print(u);
  // vec_sub(u, v);
  // vec_print(u);
  // float val = vec_dot(u, v);
  // printf("Value: %f\n", val);

  // matrix m = mat_ident(2, 2);
  // printf("Identity matrix\n");
  // mat_print(m);
  // printf("Testing mat_set\n");
  // mat_set(m, 0, 1, 2.0);
  // mat_set(m, 1, 0, 3.0);
  // mat_set(m, 1, 1, 4.0);
  // mat_print(m);
  // printf("Testing mat_copy\n");
  // matrix n = mat_copy(m);
  // mat_print(n);
  // printf("Testing mat_scale\n");
  // mat_scale(n, 2.0);
  // mat_print(n);

  matrix img = mnist_load_image("tests/mnist/train-images-idx3-ubyte/train-images-idx3-ubyte", 0, 1);
  mat_print(img);
  mat_free(img);

  return 0;
}
