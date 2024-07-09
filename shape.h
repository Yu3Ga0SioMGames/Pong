#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <SDL2/SDL.h>

#include "vector.h"

typedef
struct
{
    void *m_table;
} Shape;

typedef
struct
{
    Shape header;
    int radius;
} Circle;

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

typedef
union {
    Shape header;
    Circle circle;
    Triangle triangle;
    Square square;
} AnyShape;

typedef void *ShapePtr;
typedef void (*shape_draw_ptr)(SDL_Renderer *, ShapePtr, int, int);
typedef AnyShape (*shape_rotate_ptr)(ShapePtr, float);
typedef AnyShape (*shape_scale_ptr)(ShapePtr, float);

typedef
struct
{
    shape_draw_ptr draw;
    shape_rotate_ptr rotate;
    shape_scale_ptr scale;
} ShapeMTable;

void shape_draw(SDL_Renderer *, Shape *, int, int);

AnyShape shape_rotate(Shape *, float);

AnyShape shape_scale(Shape *, float);

void square_draw(SDL_Renderer *, Square *, int, int);

AnyShape square_rotate(Square *, float);

AnyShape square_scale(Square *, float);

void circle_draw(SDL_Renderer *, Circle *, int, int);

AnyShape circle_scale(Circle *, float);

void triangle_draw(SDL_Renderer *, Triangle *, int, int);

AnyShape triangle_rotate(Triangle *, float);

AnyShape triangle_scale(Triangle *, float);

void circle_init(Circle *, int);

Circle *shape_create_circle(int);

void shape_free_circle(CircleCollider *);

void square_init(Square *, int, int);

Square *shape_create_square(int, int);

void shape_free_square(Square *);

void triangle_init(Triangle *);

Triangle *shape_create_triangle(Vector[3]);

void shape_free_triangle(Triangle *);

#endif
