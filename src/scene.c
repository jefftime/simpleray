#include "scene.h"
#include "sphere.h"
#include "vector.h"
#include <stdlib.h>

void scene_init(struct scene *scene) {
  scene->n_spheres = 0;
  scene->n_lights = 1;
  vector_set(scene->lights[0].pos, 0, 0, 0);
  vector_set(scene->lights[0].dir, -1, -1, -1);
  vector_normalize(scene->lights[0].dir);
}

void scene_add(struct scene *scene, struct sphere *in_sphere) {
  scene->spheres[scene->n_spheres++] = *in_sphere;
}
