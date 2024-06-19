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

ShapeMTable triangle_table = {
    triangle_draw,
    triangle_rotate,
    triangle_scale
};

void shape_draw(SDL_Renderer *renderer, Shape *shape, int x, int y)
{
    shape->m_table->draw(renderer, shape, x, y);
}

/* Shape shape_rotate(Shape, float)
{
    shape->m_table->draw(renderer, shape, x, y);
} */

/* Shape shape_scale(Shape, float)
{

} */

/* Shape shape_rotate_around(Shape, Angle, RotationCenter)
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

void triangle_draw(SDL_Renderer *renderer, Triangle *polygon, int x, int y)
{
    for(int i = 0; i < 2; ++i) {
        SDL_RenderDrawLine(renderer, polygon->points[i].x + x, polygon->points[i].y + y,
                           polygon->points[i + 1].x + x, polygon->points[i + 1].y + y);
    }

    SDL_RenderDrawLine(renderer, polygon->points[2].x + x, polygon->points[2].y + y,
                       polygon->points[0].x + x, polygon->points[0].y + y);
}

Triangle triangle_rotate(Triangle *polygon, float angle)
{
    Triangle result;
    result.header = polygon->header;

    for(int i = 0; i < 3; ++i) {
        result.points[i] = vector_rotate(polygon->points[i], angle);
    }

    return result;
}

Triangle triangle_scale(Triangle *polygon, float factor)
{
    Triangle result;
    result.header = polygon->header;

    for(int i = 0; i < 3; ++i) {
        result.points[i] = vector_multiplication(polygon->points[i], factor);
    }

    return result;
}

/* void circle_init()
{

}

Circle shape_create_circle()
{
    Circle *ptr = malloc(sizeof(Circle));
    ptr->header.m_table = &circle_table;
}

void shape_free_circle(Circle *circle)
{
    free(circle);
}

void square_init()
{

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

void triangle_init(Triangle *triangle)
{
    triangle->header.m_table = &triangle_table;
}

Triangle *shape_create_triangle(Vector points[3])
{
    Triangle *ptr = (Triangle *)malloc(sizeof(Triangle) + sizeof(Vector) * 3);
    triangle_init(ptr);
    for(int i = 0; i < 3; ++i) {
        ptr->points[i] = points[i];
    }

    return ptr;
}

void shape_free_triangle(Triangle *polygon)
{
    free(polygon);
}
