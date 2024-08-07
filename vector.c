#define _GNU_SOURCE
#include <math.h>
#undef _GNU_SOURCE

#include "vector.h"
#include "collision.h"

Vector vector_summ(Vector first, Vector second)
{
    Vector result = {
        first.x + second.x,
        first.y + second.y
    };

    return result;
}

Vector vector_multiplication(Vector v0, float n)
{
    Vector v1 = {
        v0.x * n,
        v0.y *n
    };

    return v1;
}

int vector_module(Vector v0)
{
    return sqrt(v0.x * v0.x + v0.y * v0.y);
}

Vector vector_normalization(Vector v0)
{
    int vabs = vector_module(v0);
    Vector vN = {
        v0.x / vabs,
        v0.y / vabs
    };

    return vN;
}

Vector vector_rotate(Vector v, float angle)
{
    float rad = angle * M_PIf / 180;

    Vector v0 = {
        v.x * cos(rad) - v.y * sin(rad),
        v.x * sin(rad) + v.y * cos(rad)
    };

    return v0;
}
