#include "sphere.h"
#include "math.h"

int sphere_ray_intersect(struct sphere *sphere, struct ray *r, float *out_hit) {
  float a, b, c, first_root, second_root;
  vector delta_pos;

  a = vector_dot(r->dir, r->dir);
  vector_sub(delta_pos, r->pos, sphere->pos);
  b = 2.0f * vector_dot(r->dir, delta_pos);
  c = vector_dot(delta_pos, delta_pos) - (sphere->radius * sphere->radius);
  if (quad_eqn(a, b, c, &first_root, &second_root)) {
    if (first_root < 0.0f || second_root < 0.0f) {
      if (first_root >= 0.0f || second_root >= 0.0f) {
        *out_hit = 0.0;
        return 1;
      }
      return 0;
    }
    *out_hit = first_root < second_root ? first_root : second_root;
    return 1;
  }
  return 0;
}
