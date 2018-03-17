#ifndef SIMPLERAY_RAY_H
#define SIMPLERAY_RAY_H

#include "vector.h"

struct ray {
  vector pos;
  vector dir;
};

void ray_init(struct ray *ray, vector pos, vector dir);
#define ray_deinit(ray)

#endif
