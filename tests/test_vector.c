#include "vector.h"

int main(void) {
  vector v = vec_alloc(5);
  vec_print(v);
  vec_set(v, 2, 1.0);
  vec_print(v);
  return 0;
}
