#ifndef SIMPLERAY_SCENE_H
#define SIMPLERAY_SCENE_H

#include "sphere.h"

struct scene {
  struct sphere *spheres;
  struct ray *lights;
};

void scene_init(struct scene *scene);
void scene_deinit(struct scene *scene);

#endif
