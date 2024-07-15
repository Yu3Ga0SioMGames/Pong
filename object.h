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
    Vector collider_displacement;
} GameObject;

bool check_collision(const GameObject *, const GameObject *);

void collision_resolution(GameObject *, GameObject *);

void draw_gameobject(SDL_Renderer *, GameObject *, int, int);

void place_gameobject(GameObject *obj, int x, int y);

void move_gameobject(GameObject *obj, int x, int y);

void move_gameobject_bounded(GameObject *obj,
                             int x, int y,
                             int x_min, int x_max,
                             int y_min, int y_max);

#endif
