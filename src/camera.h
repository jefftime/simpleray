#ifndef SIMPLERAY_CAMERA_H
#define SIMPLERAY_CAMERA_H

#include "ray.h"

struct camera {
  struct ray eye;
  float fovx;
  float fovy;
};

void camera_init(struct camera *camera,
                 struct ray *eye,
                 float fovx,
                 float fovy);
#define camera_deinit(camera)

#endif
