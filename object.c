#include <stdbool.h>

#include "object.h"

inline int sign(int x)
{
    return (x < 0) ? -1 : 1;
}

bool check_collision(const GameObject *first, const GameObject *second)
{
    if(first->collider_type == 1) {
        return circle_cross_rect(&first, &second);
    }

    return circle_cross_circle(&second, &first);
}

void collision_resolution(GameObject *first, GameObject *second)
{
    do {
        first->scene_position.x -= sign(first->velocity.x);
    } while(!check_collision(first, second));

    first->velocity.x = -(first->velocity.x);
}
