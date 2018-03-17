#include "math.h"
#include <math.h>
#include <float.h>

int flt_eq(float f1, float f2) {
  return ((float) fabs((double) f1 - (double) f2) < FLT_EPSILON);
}

int quad_eqn(float a, float b, float c, float *out_first, float *out_second) {
  float d;

  if (a < 0.0f) return 0;
  d = (b * b) - (4.0f * a * c);
  if (d < 0.0f) return 0;
  *out_first  = (float) (-b + sqrt(d)) / (2.0f * a);
  *out_second = (float) (-b - sqrt(d)) / (2.0f * a);
  return 1;
}
