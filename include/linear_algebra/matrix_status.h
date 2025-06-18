#ifndef MATRIX_STATUS_H
#define MATRIX_STATUS_H

typedef enum {
  MAT_OK = 0,
  MAT_ERR_OOB,
  MAT_ERR_SHAPE,
  MAT_ERR_ALLOC,
  MAT_ERR_NULL,
  MAT_ERR_SINGULAR
} mat_status;

const char *mat_strerror(mat_status status);

#endif // !MATRIX_STATUS_H
