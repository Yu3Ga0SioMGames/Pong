#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <SDL2/SDL.h>

#include "vector.h"

typedef void *ShapePtr;
typedef void (*shape_draw_ptr)(SDL_Renderer *, ShapePtr, int, int);
typedef void (*shape_rotate_ptr)(ShapePtr, float);
typedef void (*shape_scale_ptr)(ShapePtr, float);

typedef
struct
{
    shape_draw_ptr draw;
    shape_rotate_ptr rotate;
    shape_scale_ptr scale;
} ShapeMTable;

typedef
struct
{
    ShapeMTable *m_table;
} Shape;

/* typedef
struct
{
    Shape header;
    int radius;
} Circle; */

typedef
struct
{
    Shape header;
    Vector points[4];
} Square;

typedef
struct
{
    Shape header;
    Point points[3];
} Triangle;

void shape_draw(SDL_Renderer *, Shape *, int, int);

Shape shape_rotate(Shape *, float);

Shape shape_scale(Shape *, float);

// Shape shape_rotate_around(Shape, Angle, RotationCenter);

void square_draw(SDL_Renderer *, Square *, int, int);

Square square_rotate(Square *, float);

Square square_scale(Square *, float);

/* void circle_draw(SDL_Renderer *, Circle *, int, int);

Circle circle_scale(Circle *, float); */

void triangle_draw(SDL_Renderer *, Triangle *, int, int);

Triangle triangle_rotate(Triangle *, float);

Triangle triangle_scale(Triangle *, float);

/* void circle_init(Circle *);

Circle shape_create_circle(); */

void shape_free_circle(Circle *);

void square_init(Square *, int, int);

Square *shape_create_square(Square *, int, int);

void shape_free_square(Square *);

void triangle_init(Triangle *);

Triangle *shape_create_triangle(Vector[3]);

void shape_free_triangle(Triangle *);

#endif
