#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "collision.h"

typedef Point Vector;

Vector vector_summ(Vector, Vector);

Vector vector_multi(Vector, float); // vector_multiplication

Vector vector_module(Vector);

Vector vector_normal(Vector); // vector_normalization

#endif
