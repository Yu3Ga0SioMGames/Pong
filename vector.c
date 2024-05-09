#include <math.h>

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

// vector_multiplication
Vector vector_multi(Vector v0, float n)
{
    Vector v1 = {
        v0.x * n;
        v0.y * n;
    };

    return v1;
}

Vector vector_module(Vector v0)
{
    return sqrt(v0.x * v0.x + v0.y * v0.y); // after... remake sqrt
}

// vector_normalization
Vector vector_normal(Vector v0)
{
    Vector vabs = vector_module(v0);
    Vector vN = {
        v0.x / vabs;
        v0.y / vabs;
    };

    return vN;
}
