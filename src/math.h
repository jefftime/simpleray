#ifndef SIMPLERAY_MATH_H
#define SIMPLERAY_MATH_H

#define PI 3.14159265f

#define to_rads(degrees) ((degrees / 180.0f) * PI)

int flt_eq(float f1, float f2);
int quad_eqn(float a, float b, float c, float *out_first, float *out_second);

#endif
