/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Declare the vector addition, subtraction, and scaling functions.
 */

#ifndef MYVECT_TOP
#define MYVECT_TOP

#include "myvect.h"

/* Return the component-by-component sum of two vectors. */
vect addvect(vect a, vect b);

/* Return the component-by-component difference a - b. */
vect subtractvect(vect a, vect b);

/* Return a vector with each component multiplied by scalar. */
vect scalevect(vect v, double scalar);

#endif
