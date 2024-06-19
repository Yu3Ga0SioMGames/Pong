#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <SDL2/SDL.h>

#include "vector.h"

typedef void *ShapePtr;
typedef void (*shape_draw_ptr)(ShapePtr, int, int);
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

/* typedef
struct
{
    Shape header;
} Square; */

typedef
struct
{
    Shape header;
    int point_count;
    Point points[];
} Polygon;

/* void shape_draw(Shape, int, int);

Shape shape_rotate(Shape, float);

Shape shape_scale(Shape, float);

Shape shape_rotate_around(Shape, Angle, RotationCenter); */

/* void square_draw(Square, int, int);

Square square_rotate(Square, float);

Square square_scale(Square, float); */

/* void circle_draw(Circle, int, int);

Circle circle_rotate(Circle, float);

Circle circle_scale(Circle, float); */

void polygon_draw(SDL_Renderer *, Polygon *, int, int);

void polygon_rotate(Polygon *, Polygon *, float);

void polygon_scale(Polygon *, Polygon *, float);

/* Circle shape_create_circle();

void shape_free_circle(Circle *);

Square shape_create_square();

void shape_free_square(Square *); */

Polygon *shape_create_polygon(int, Vector[]);

void shape_free_polygon(Polygon *);

#endif
