#include "mnist_data.h"

static uint32_t read_be32(FILE *fp) {
  uint8_t arr[4];
  if (fread(arr, 1, 4, fp) != 4) {
    perror("fread");
    exit(EXIT_FAILURE);
  }
  return (arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3];
}

int mnist_load_image(const char *path, mnist_image *out);

int mnist_load_label(const char *path, mnist_label *out);

void mnist_free_image(mnist_image *image);

void mnist_free_label(mnist_label *label);
