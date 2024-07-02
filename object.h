#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <stdbool.h>

#include "shape.h"
#include "vector.h"
#include "collision.h"

typedef
struct
{
    Vector scene_position;
    Vector direction;
    Shape *shape;
    Vector velocity;
    int collider_type;
    void *collider;
} GameObject;

bool check_collision(const GameObject *, const GameObject *);

void collision_resolution(GameObject *, GameObject *);

// void draw_gameobject();

#endif
