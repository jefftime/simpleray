#ifndef SIMPLERAY_VECTOR_H
#define SIMPLERAY_VECTOR_H

typedef float vector[3];
#define vector_set(v, i, j, k) { (v)[0] = i; (v)[1] = j; (v)[2] = k; }

float vector_magnitude(vector v);
void vector_normalize(vector v);
float vector_dot(vector v1, vector v2);
void vector_add(vector result, vector v1, vector v2);
void vector_sub(vector result, vector v1, vector v2);

#endif
