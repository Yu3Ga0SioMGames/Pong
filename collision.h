#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <stdbool.h>

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
} Rect;

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
} Circle;

bool circle_cross_rect(Circle, Rect);

bool circle_cross_circle(Circle, Circle);

bool circle_cross_point(Circle, Point);

bool point_cross_segment(int, Segment);

bool segment_cross_segment(Segment, Segment);

bool rect_cross_point(Rect, Point);

bool rect_cross_rect(Rect, Rect);

#endif
