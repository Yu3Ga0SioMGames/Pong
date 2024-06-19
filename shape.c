#include <stdlib.h>

#include "shape.h"

/* ShapeMTable circle_table = {
    circle_draw,
    circle_rotate,
    circle_scale
};

ShapeMTable square_table = {
    square_draw,
    square_rotate,
    square_scale
}; */

ShapeMTable polygon_table = {
    polygon_draw,
    /* polygon_rotate,
    polygon_scale */
};

/* void shape_draw(Shape, int, int)
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

} */

/* void square_draw(Square, int, int)
{
    ;
}

Square square_rotate(Square, float)
{
    ;
}

Square square_scale(Square, float)
{
    ;
} */

/* void circle_draw(Circle, int, int)
{
    ;
}

Circle circle_rotate(Circle, float)
{
    ;
}

Circle circle_scale(Circle, float)
{
    ;
} */

void polygon_draw(SDL_Renderer *renderer, Polygon *polygon, int x, int y)
{
    for(int i = 0; i < polygon->point_count - 1; ++i) {
        SDL_RenderDrawLine(renderer, polygon->points[i].x + x, polygon->points[i].y + y,
                           polygon->points[i + 1].x + x, polygon->points[i + 1].y + y);
    }

    SDL_RenderDrawLine(renderer, polygon->points[polygon->point_count - 1].x + x, polygon->points[polygon->point_count - 1].y + y,
                       polygon->points[0].x + x, polygon->points[0].y + y);
}

void polygon_rotate(Polygon *polygon, Polygon *result, float angle)
{
    for(int i = 0; i < polygon->point_count; ++i) {
        result->points[i] = vector_rotate(polygon->points[i], angle);
    }
}

void polygon_scale(Polygon *polygon, Polygon *result, float factor)
{
    for(int i = 0; i < polygon->point_count; ++i) {
        result->points[i] = vector_multiplication(polygon->points[i], factor);
    }
}

/* Circle shape_create_circle()
{
    Circle *ptr = malloc(sizeof(Circle));
    ptr->header.m_table = &circle_table;
}

void shape_free_circle(Circle *circle)
{
    free(circle);
}

Square shape_create_square()
{
    Square *ptr = malloc(sizeof(Square));
    ptr->header.m_table = &square_table;
}

void shape_free_square(Square *square)
{
    free(square);
} */

Polygon *shape_create_polygon(int point_count, Vector points[])
{
    Polygon *ptr = (Polygon *)malloc(sizeof(Polygon) + sizeof(Vector) * point_count);

    ptr->header.m_table = &polygon_table;
    ptr->point_count = point_count;

    for(int i = 0; i < point_count; ++i) {
        ptr->points[i] = points[i];
    }

    return ptr;
}

void shape_free_polygon(Polygon *polygon)
{
    free(polygon);
}
