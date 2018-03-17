#include "image.h"
#include <stdio.h>
#include <stdlib.h>

void image_init(struct image *image, unsigned int width, unsigned int height) {
  if (!image) return;
  image->width = width;
  image->height = height;
  image->data = malloc(sizeof(unsigned char) * width * height * 3);
}

void image_deinit(struct image *image) {
  if (!image) return;
  free(image->data);
}

void image_set(struct image *image,
               unsigned int x,
               unsigned int y,
               unsigned char r,
               unsigned char g,
               unsigned char b) {
  unsigned int index;

  if (x > image->width) return;
  if (y > image->height) return;
  index = (y * image->width + x) * 3;
  if (!image) return;
  image->data[index + 0] = r;
  image->data[index + 1] = g;
  image->data[index + 2] = b;
}

void image_write_ppm(struct image *image, char *filename) {
  FILE *out = fopen(filename, "wb");
  if (!out) {
    puts("could not open file for writing");
    return;
  }
  fprintf(out, "P6 %u %u 255 ", image->width, image->height);
  fwrite(image->data,
         sizeof(unsigned char),
         image->width * image->height * 3,
         out);
  fclose(out);
}
