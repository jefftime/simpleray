#ifndef SIMPLERAY_VECTOR_H
#define SIMPLERAY_VECTOR_H

typedef float vector[3];
#define vector_set(v, i, j, k) (v[0] = i, v[1] = j, v[2] = k)
#define vector_setv(v, rhs) { v[0] = rhs[0]; v[1] = rhs[1]; v[2] = rhs[2]; }
#define vector_negate(r, v) { r[0] = -v[0]; r[1] = -v[1]; r[2] = -v[2]; }

float vector_magnitude(vector v);
void vector_normalize(vector result, vector v);
float vector_dot(vector v1, vector v2);
void vector_add(vector result, vector v1, vector v2);
void vector_sub(vector result, vector v1, vector v2);
void vector_mulf(vector result, float f, vector v);

#endif
