#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <stdbool.h>

#define COLLIDER_TYPE_NONE 0
#define COLLIDER_TYPE_CIRCLE (COLLIDER_TYPE_NONE + 1)
#define COLLIDER_TYPE_RECTANGLE (COLLIDER_TYPE_CIRCLE + 1)

typedef
struct
{
    int x;
    int y;
} Point;

typedef
struct
{
    Point p;
    int h;
    int w;
} RectangleCollider;

typedef
struct
{
    int start;
    int end;
} Segment;

typedef
struct
{
    Point center;
    int r;
} CircleCollider;

bool circle_cross_rect(CircleCollider, RectangleCollider);

bool circle_cross_circle(CircleCollider, CircleCollider);

bool circle_cross_point(CircleCollider, Point);

bool point_cross_segment(int, Segment);

bool segment_cross_segment(Segment, Segment);

bool rect_cross_point(RectangleCollider, Point);

bool rect_cross_rect(RectangleCollider, RectangleCollider);

#endif
