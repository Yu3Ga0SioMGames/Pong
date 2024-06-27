#include <stdbool.h>

#include "collision.h"

Segment get_rect_proj_x(RectangleCollider r)
{
    Segment proj;
    proj.start = r.p.x;
    proj.end = r.p.x + r.w;

    return proj;
}

Segment get_rect_proj_y(RectangleCollider r)
{
    Segment proj;
    proj.start = r.p.y;
    proj.end = r.p.y + r.h;

    return proj;
}

bool point_cross_segment(int p, Segment proj)
{
    return p >= proj.start && p <= proj.end;
}

bool rect_cross_point(RectangleCollider r, Point p)
{
    Segment r_x = get_rect_proj_x(r);
    Segment r_y = get_rect_proj_y(r);

    return point_cross_segment(p.x, r_x) &&
           point_cross_segment(p.y, r_y);
}

bool segment_cross_segment(Segment a, Segment b)
{
    return point_cross_segment(a.start, b) ||
           point_cross_segment(a.end, b) ||
           point_cross_segment(b.start, a);
}

bool rect_cross_rect(RectangleCollider a, RectangleCollider b)
{
    return segment_cross_segment(get_rect_proj_x(a),
                                 get_rect_proj_x(b)) &&
           segment_cross_segment(get_rect_proj_y(a),
                                 get_rect_proj_y(b));
}
