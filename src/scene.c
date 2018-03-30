#include "scene.h"
#include "sphere.h"
#include "vector.h"
#include <darray/darray.h>
#include <stdlib.h>


void scene_init(struct scene *scene) {
#define initial_spheres 16
#define initial_lights 16

  scene->spheres = danew(struct sphere, initial_spheres);
  scene->lights = danew(struct ray, initial_lights);

#undef initial_spheres
#undef initial_lights
}

void scene_deinit(struct scene *scene) {
  if (!scene) return;
  dafree(scene->spheres);
  dafree(scene->lights);
}
