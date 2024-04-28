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
