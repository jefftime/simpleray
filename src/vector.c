#include "vector.h"
#include <math.h>

float vector_magnitude(vector v) {
  return (float) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vector_normalize(vector v) {
  float magnitude = vector_magnitude(v);
  v[0] = v[0] / magnitude;
  v[1] = v[1] / magnitude;
  v[2] = v[2] / magnitude;
}

float vector_dot(vector v1, vector v2) {
  return (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]);
}

void vector_add(vector result, vector v1, vector v2) {
  result[0] = v1[0] + v2[0];
  result[1] = v1[1] + v2[1];
  result[2] = v1[2] + v2[2];
}

void vector_sub(vector result, vector v1, vector v2) {
  result[0] = v1[0] - v2[0];
  result[1] = v1[1] - v2[1];
  result[2] = v1[2] - v2[2];
}
