#include "camera.h"

void camera_init(struct camera *camera,
                 struct ray *eye,
                 float fovx,
                 float fovy) {
  if (!camera) return;
  camera->eye = *eye;
  camera->fovx = fovx;
  camera->fovy = fovy;
}
