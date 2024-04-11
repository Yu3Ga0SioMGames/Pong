#include <stdbool.h>

#include "collision.h"

bool circle_cross_point(Circle circle, Point point)
{
    int y_diff = circle.center.y - point.y;
    int x_diff = circle.center.x - point.x;

    int l_2 = x_diff * x_diff + y_diff * y_diff;

    return circle.r * circle.r <= l_2;
}
