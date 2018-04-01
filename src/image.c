#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void image_init(struct image *image, unsigned int width, unsigned int height) {
  if (!image) return;
  image->width = width;
  image->height = height;
  image->data = malloc(sizeof(unsigned char) * width * height * 3);
}

void image_deinit(struct image *image) {
  if (!image) return;
  if (image->data) free(image->data);
}

void image_set(struct image *image,
               unsigned int x,
               unsigned int y,
               unsigned char r,
               unsigned char g,
               unsigned char b) {
  unsigned long index;

  if (x >= image->width) return;
  if (y >= image->height) return;
  index = (y * image->width + x) * 3;
  if (!image) return;
  image->data[index + 0] = r;
  image->data[index + 1] = g;
  image->data[index + 2] = b;
}

void image_write_ppm(struct image *image, char *filepath) {
  FILE *out = fopen(filepath, "wb");
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

#define write4le(buf, n) { \
  (buf)[3] = (unsigned char) (((n) & 0xff000000) >> 24);	\
  (buf)[2] = (unsigned char) (((n) & 0x00ff0000) >> 16);	\
  (buf)[1] = (unsigned char) (((n) & 0x0000ff00) >> 8);	\
  (buf)[0] = (unsigned char) ((n) & 0x000000ff);		\
  }

#define write2le(buf, n) { \
  (buf)[1] = (unsigned char) (((n) & 0xff00) >> 8); \
  (buf)[0] = (unsigned char) ((n) & 0x00ff); \
  }

void image_write_bmp(struct image *image, char *filepath) {
#define header_size 14
#define dib_size 40

  unsigned char header[header_size], dib[dib_size], *data;
  unsigned int bpp;
  unsigned long y, row_size, image_size;
  FILE *out;

  if (!image) return;
  out = fopen(filepath, "wb");
  if (!out) {
    puts("could not open file for writing");
    return;
  }
  bpp = 24;
  row_size = ((bpp * image->width + 31) / 32) * 4;
  image_size = row_size * image->height * 3;
  data = malloc(image_size);
  if (!data) {
    puts("could not allocate memory for bmp");
    return;
  }
  for (y = 0; y < image_size; ++y) {
    data[y] = 0;
  }
  for (y = 0; y < image->height; ++y) {
    unsigned char *row = data + (y * row_size);

    memcpy(row,
           image->data + ((image->height - 1 - y) * image->width * 3),
           image->width * 3);
  }
  header[0] = 'B';
  header[1] = 'M';
  write4le(header + 2, header_size + dib_size + image_size);
  write4le(header + 6, 0);
  write4le(header + 10, header_size + dib_size);
  write4le(dib, dib_size);
  write4le(dib + 4, image->width);
  write4le(dib + 8, image->height);
  write2le(dib + 12, 1); /* number of color planes */
  write2le(dib + 14, bpp);
  write4le(dib + 16, 0); /* compression */
  write4le(dib + 20, 0); /* image size dummy value */
  write4le(dib + 24, 0); /* horizontal resolution */
  write4le(dib + 28, 0); /* vertical resolution */
  write4le(dib + 32, 0); /* number of colors in palette */
  write4le(dib + 36, 0); /* number of important colors */
  fwrite(header, header_size, 1, out);
  fwrite(dib, dib_size, 1, out);
  fwrite(data, image_size, 1, out);
  fclose(out);

#undef header_size
#undef dib_size
}
