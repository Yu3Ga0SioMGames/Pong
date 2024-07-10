#include <stdbool.h>
#include <sys/param.h>

#include "object.h"

static inline int sign(int x)
{
    return (x < 0) ? -1 : 1;
}

bool check_collision(const GameObject *first, const GameObject *second)
{
    if(first->collider_type == 1) {
        return circle_cross_rect(*((CircleCollider *)(first->collider)),
                                 *((RectangleCollider *)(second->collider)));
    }

    return circle_cross_rect(*((CircleCollider *)(second->collider)),
                               *((RectangleCollider *)(first->collider)));
}

void collision_resolution(GameObject *first, GameObject *second)
{
    do {
        move_gameobject(first, -sign(first->velocity.x), 0);
    } while(check_collision(first, second));

    first->velocity.x = -(first->velocity.x);
}

void draw_gameobject(SDL_Renderer *renderer, GameObject *object, int x, int y)
{
    shape_draw(renderer, object->shape, x, y);
}

void move_gameobject(GameObject *obj, int x, int y)
{
    obj->scene_position.x += x;
    obj->scene_position.y += y;

    void *collider = obj->collider;
    switch(obj->collider_type) {
    case COLLIDER_TYPE_CIRCLE:
        ((CircleCollider *)collider)->center.x = obj->scene_position.x;
        ((CircleCollider *)collider)->center.y = obj->scene_position.y;
        break;
    case COLLIDER_TYPE_RECTANGLE:
        ((RectangleCollider *)collider)->p.x = obj->scene_position.x;
        ((RectangleCollider *)collider)->p.y = obj->scene_position.y;
        break;
    default:
        break;
    }
}

void move_gameobject_bounded(GameObject *obj,
                             int x, int y,
                             int x_min, int x_max,
                             int y_min, int y_max)
{
    obj->scene_position.x += x;
    obj->scene_position.x = MIN(obj->scene_position.x, x_max);
    obj->scene_position.x = MAX(obj->scene_position.x, x_min);
    obj->scene_position.y += y;
    obj->scene_position.y = MIN(obj->scene_position.y, y_max);
    obj->scene_position.y = MAX(obj->scene_position.y, y_min);

    void *collider = obj->collider;
    switch(obj->collider_type) {
    case COLLIDER_TYPE_CIRCLE:
        ((CircleCollider *)collider)->center.x = obj->scene_position.x;
        ((CircleCollider *)collider)->center.y = obj->scene_position.y;
        break;
    case COLLIDER_TYPE_RECTANGLE:
        ((RectangleCollider *)collider)->p.x = obj->scene_position.x + obj->collider_displacement.x;
        ((RectangleCollider *)collider)->p.y = obj->scene_position.y + obj->collider_displacement.y;
        break;
    default:
        break;
    }
}
