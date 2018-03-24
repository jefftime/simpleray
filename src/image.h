#ifndef SIMPLERAY_IMAGE_H
#define SIMPLERAY_IMAGE_H

struct image {
  unsigned int width;
  unsigned int height;
  unsigned char *data;
};

void image_init(struct image *image, unsigned int width, unsigned int height);
void image_deinit(struct image *image);
void image_set(struct image *image,
               unsigned int x,
               unsigned int y,
               unsigned char r,
               unsigned char g,
               unsigned char b);
void image_write_ppm(struct image *image, char *filepath);
void image_write_bmp(struct image *image, char *filepath);

#endif
