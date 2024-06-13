#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

typedef void *Shape;
typedef void (*shape_draw_ptr)(Shape, int, int);
typedef void (*shape_rotate_ptr)(Shape, float);
typedef void (*shape_scale_ptr)(Shape, float);

typedef
struct
{
    shape_draw_ptr draw;
    shape_rotate_ptr rotate;
    shape_scale_ptr scale;
} ShapeMTable;

ShapeMTable circle_table = {
    circle_draw();
    circle_rotate();
    circle_scale();
};

ShapeMTable square_table = {
    square_draw();
    square_rotate();
    square_scale();
};

ShapeMTable polygon_table = {
    polygon_draw();
    polygon_rotate();
    polygon_scale();
};

typedef
struct
{
    ShapeMTable *m_table;
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
} Square;

typedef
struct
{
    Shape header;
} Polygon;

void shape_draw(Shape, int, int);

Shape shape_rotate(Shape, float);

Shape shape_scale(Shape, float);

// Shape shape_rotate_around(Shape, Angle, RotationCenter);

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

Polygon shape_create_square()
{
    Polygon *ptr = malloc(sizeof(Polygon));
    ptr->header.m_table = &polygon_table;
}

#endif
