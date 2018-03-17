#ifndef SIMPLERAY_SCENE_H
#define SIMPLERAY_SCENE_H

#ifndef MAX_SPHERES
#define MAX_SPHERES 64
#endif

#ifndef MAX_LIGHTS
#define MAX_LIGHTS 64
#endif

#include "sphere.h"

struct scene {
  unsigned int n_spheres;
  struct sphere spheres[MAX_SPHERES];
  unsigned int n_lights;
  struct ray lights[MAX_LIGHTS];
};

void scene_init(struct scene *scene);
#define scene_deinit(scene)
void scene_add(struct scene *scene, struct sphere *in_sphere);

#endif
