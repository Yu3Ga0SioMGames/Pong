#include <stdlib.h>

#include "shape.h"

/*

void shape_draw(Shape, int, int)
{

}

Shape shape_rotate(Shape, float)
{

}

Shape shape_scale(Shape, float)
{

}

Shape shape_rotate_around(Shape, Angle, RotationCenter)
{

}

Circle shape_create_circle()
{
    Circle *ptr = malloc(sizeof(Circle));
    ptr->header.m_table = &circle_table;
}

Square shape_create_square()
{
    Square *ptr = malloc(sizeof(Square));
    ptr->header.m_table = &square_table;
}

*/

Polygon *shape_create_polygon(int point_count, Point points[])
{
    Polygon *ptr = (Polygon*)malloc(sizeof(Polygon) + sizeof(Point) * point_count);

    ptr->header.m_table = &polygon_table;
    ptr->point_count = point_count;

    for(int i = 0; i < point_count; ++i) {
        ptr->points[i] = points[i];
    }

    return ptr;
}
