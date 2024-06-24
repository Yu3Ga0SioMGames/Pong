#include <stdlib.h>

#include "shape.h"

/* ShapeMTable circle_table = {
    circle_draw,
    NULL,
    circle_scale
}; */

ShapeMTable square_table = {
    square_draw,
    square_rotate,
    square_scale
};

ShapeMTable triangle_table = {
    triangle_draw,
    triangle_rotate,
    triangle_scale
};

void shape_draw(SDL_Renderer *renderer, Shape *shape, int x, int y)
{
    shape->m_table->draw(renderer, shape, x, y);
}

/* Shape shape_rotate(Shape *shape, float angle)
{
    shape_rotate_ptr ptr = shape->m_table->rotate;
    if(ptr != NULL) {
        ptr(shape, angle);
    }

    return ;
}

Shape shape_scale(Shape *shape, float factor)
{
    return shape->m_table->scale(shape, factor);
} */

/* Shape shape_rotate_around(Shape, Angle, RotationCenter)
{

} */

void square_draw(SDL_Renderer *renderer, Square *polygon, int x, int y)
{
    for(int i = 0; i < 3; ++i) {
        SDL_RenderDrawLine(renderer, polygon->points[i].x + x, polygon->points[i].y + y,
                           polygon->points[i + 1].x + x, polygon->points[i + 1].y + y);
    }

    SDL_RenderDrawLine(renderer, polygon->points[3].x + x, polygon->points[3].y + y,
                       polygon->points[0].x + x, polygon->points[0].y + y);
}

Square square_rotate(Square *polygon, float angle)
{
    Square result;
    result.header = polygon->header;

    for(int i = 0; i < 4; ++i) {
        result.points[i] = vector_rotate(polygon->points[i], angle);
    }

    return result;
}

Square square_scale(Square *polygon, float factor)
{
    Square result;
    result.header = polygon->header;

    for(int i = 0; i < 4; ++i) {
        result.points[i] = vector_multiplication(polygon->points[i], factor);
    }

    return result;
}

/* void circle_draw(SDL_Renderer *renderer, Circle *circle, int x, int y)
{
    ;
}

Circle circle_scale(Circle *circle, float factor)
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

} */

void shape_free_circle(Circle *circle)
{
    free(circle);
}

void square_init(Square *ptr, int h, int w)
{
    ptr->header.m_table = &square_table;

    ptr->points[0].x = -(w / 2 + w % 2);
    ptr->points[0].y = -(h / 2 + h % 2);

    ptr->points[1].x = w / 2;
    ptr->points[1].y = -(h / 2 + h % 2);

    ptr->points[2].x = w / 2;
    ptr->points[2].y = h / 2;

    ptr->points[3].x = -(w / 2 + w % 2);
    ptr->points[3].y = h / 2;
}

Square *shape_create_square(Square *square, int h, int w)
{
    Square *ptr = (Square *)malloc(sizeof(Square) + sizeof(Vector) + 4);
    square_init(ptr, h, w);

    return ptr;
}

void shape_free_square(Square *square)
{
    free(square);
}

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
