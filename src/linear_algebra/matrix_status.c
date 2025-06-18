#include "matrix_status.h"

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
