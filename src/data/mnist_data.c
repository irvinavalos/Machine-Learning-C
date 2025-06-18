#include "mnist_data.h"

static uint32_t read_be32(FILE *fp) {
  uint8_t arr[4];
  if (fread(arr, 1, 4, fp) != 4) {
    perror("fread");
    exit(EXIT_FAILURE);
  }
  return (arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3];
}

matrix mnist_load_image(const char *img_file, size_t idx, int normalize) {
  FILE *fp = fopen(img_file, "rb");
  if (!fp) {
    perror(img_file);
    exit(EXIT_FAILURE);
  }
  uint32_t magic = read_be32(fp);
  if (magic != 0x00000803) {
    fprintf(stderr, "Not an IDX-3 file: %s\n", img_file);
    exit(EXIT_FAILURE);
  }
  uint32_t n_imgs = read_be32(fp);
  uint32_t n_rows = read_be32(fp);
  uint32_t n_cols = read_be32(fp);
  if (idx >= n_imgs) {
    fprintf(stderr, "Image index %zu out of range (0-%u)\n", idx, n_imgs - 1);
    exit(EXIT_FAILURE);
  }
  size_t img_size = (size_t)n_rows * n_cols;
  size_t offset = 16 + idx * img_size;
  if (fseek(fp, (long)offset, SEEK_SET) != 0) {
    perror("fseek");
    exit(EXIT_FAILURE);
  }
  matrix img = mat_alloc(n_rows, n_cols);
  uint8_t *buf = malloc(img_size);
  if (!buf) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  if (fread(buf, 1, img_size, fp) != img_size) {
    fprintf(stderr, "Unexpected EOF in %s\n", img_file);
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  for (size_t i = 0; i < n_rows; i++) {
    for (size_t j = 0; j < n_cols; j++) {
      uint8_t px = buf[i * n_cols + j];
      float val = normalize ? (float)px / 255.0f : (float)px;
      MAT_SET_AT(img, i, j, val);
    }
  }
  free(buf);
  return img;
}

int mnist_load_label(const char *path, mnist_label *out);

void mnist_free_image(mnist_image *image);

void mnist_free_label(mnist_label *label);
