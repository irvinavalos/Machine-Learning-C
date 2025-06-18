#include "mnist_data.h"

int mnist_load_image(const char *path, mnist_image *out);

int mnist_load_label(const char *path, mnist_label *out);

void mnist_free_image(mnist_image *image);

void mnist_free_label(mnist_label *label);
