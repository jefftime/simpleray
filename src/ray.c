#include "ray.h"
#include "vector.h"

void ray_init(struct ray *ray, vector pos, vector dir) {
  if (!ray) return;
  vector_set(ray->pos, pos[0], pos[1], pos[2]);
  vector_set(ray->dir, dir[0], dir[1], dir[2]);
}
