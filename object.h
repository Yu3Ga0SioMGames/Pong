#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "shape.h"
#include "vector.h"
#include "collision.h"

typedef
struct
{
    Vector screen_position;
    float direction;
    Shape *shape;
} GameObject;

#endif
