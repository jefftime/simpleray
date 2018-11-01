#ifndef SIMPLERAY_SPHERE_H
#define SIMPLERAY_SPHERE_H

#include "ray.h"
#include "vector.h"

struct sphere {
  vector pos;
  float radius;
  unsigned char color[3];
};

int sphere_ray_intersect(struct sphere *sphere, struct ray *r, float *out_hit);

#endif
