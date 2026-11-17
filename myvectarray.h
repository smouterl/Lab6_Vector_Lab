/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Declare functions for dynamically storing and retrieving vectors.
 */

#ifndef MYVECTARRAY_H
#define MYVECTARRAY_H

#include "myvect.h"
#include <stddef.h>

/* Add or replace a vector. Return 0 on success, or -1 on empty name/allocation failure. */
int storevect(vect newvect);

/* Copy the named vector into result. Return 1 if found, or 0 on failure. */
int findvect(const char *name, vect *result);

/* Remove every stored vector. */
void clearvects(void);

/* Return the number of vectors currently stored. */
size_t vectcount(void);

/* Copy the vector at index into result. Return 1 on success, or 0 on failure. */
int getvect(size_t index, vect *result);

#endif
