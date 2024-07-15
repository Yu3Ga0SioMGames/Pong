#include <stdbool.h>

#include "collision.h"

bool circle_cross_rect(CircleCollider circle, RectangleCollider rect)
{
    int left = rect.p.x;
    int right = rect.p.x + rect.w;

    int up = rect.p.y;
    int down = rect.p.y + rect.h;

    bool cross_v = circle.center.y >= up && circle.center.y <= down;
    bool cross_h = circle.center.x >= left && circle.center.x <= right;

    if(cross_v && cross_h) {
        return true;
    }

    if(cross_v || cross_h) {
        RectangleCollider bbox;
        bbox.h = circle.r * 2;
        bbox.w = bbox.h;
        bbox.p.x = circle.center.x - circle.r;
        bbox.p.y = circle.center.y - circle.r;

        int b_left = bbox.p.x;
        int b_right = bbox.p.x + bbox.w;

        int b_up = bbox.p.y;
        int b_down = bbox.p.y + bbox.h;

        bool cross_x = (b_left <= right && b_left >= left) ||
                       (b_right <= right && b_right >= left) ||
                       (right <= b_right && right >= b_left);
        bool cross_y = (b_up <= down && b_down >= up) ||
                       (b_down <= down && b_down >= up) ||
                       (down <= b_down && down >= b_up);

        return cross_x && cross_y;
    }

    Point corner;
    bool below = circle.center.y > rect.p.y;
    bool rightof = circle.center.x > rect.p.x;
    corner.x = rect.p.x;
    corner.y = rect.p.y;
    if(below) {
        corner.y += rect.h;
    }
    if(rightof) {
        corner.x += rect.w;
    }

    return circle_cross_point(circle, corner);
}

bool circle_cross_circle(CircleCollider c1, CircleCollider c2)
{
    int y_diff = c1.center.y - c2.center.y;
    int x_diff = c1.center.x - c2.center.x;

    int l_2 = x_diff * x_diff + y_diff * y_diff;

    return l_2 <= c1.r * c1.r + 2 * c1.r * c2.r + c2.r * c2.r;
}

bool circle_cross_point(CircleCollider circle, Point point)
{
    int y_diff = circle.center.y - point.y;
    int x_diff = circle.center.x - point.x;

    int l_2 = x_diff * x_diff + y_diff * y_diff;

    return circle.r * circle.r >= l_2;
}
