#ifndef MNIST_DATA_H

#define MNIST_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
  uint32_t n;
  uint32_t row;
  uint32_t col;
  uint8_t *pixel;
} mnist_image;

typedef struct {
  uint32_t n;
  uint8_t *label;
} mnist_label;

int mnist_load_image(const char *path, mnist_image *out);

int mnist_load_label(const char *path, mnist_label *out);

void mnist_free_image(mnist_image *image);

void mnist_free_label(mnist_label *label);

#endif // !MNIST_DATA_H
