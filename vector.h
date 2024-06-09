#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "collision.h"

typedef Point Vector;

Vector vector_summ(Vector, Vector);

Vector vector_multiplication(Vector, double);

int vector_module(Vector);

Vector vector_normalization(Vector);

Vector vector_rotate(Vector, double);

#endif
