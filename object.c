#include <stdbool.h>

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

    return circle_cross_circle(*((CircleCollider *)(first->collider)),
                               *((CircleCollider *)(second->collider)));
}

void collision_resolution(GameObject *first, GameObject *second)
{
    do {
        first->scene_position.x -= sign(first->velocity.x);
    } while(!check_collision(first, second));

    first->velocity.x = -(first->velocity.x);
}

void draw_gameobject(SDL_Renderer *renderer, GameObject *object, int x, int y)
{
    shape_draw(renderer, object->shape, x, y);
}
