/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Declare functions for storing and retrieving up to ten vectors.
 */

#ifndef MYVECTARRAY_H
#define MYVECTARRAY_H

#include "myvect.h"

#define MAX_VECTORS 10
/* Add or replace a vector. Return 0 on success, or -1 for an empty name or full storage. */
int storevect(vect newvect);

/* Copy the named vector into result. Return 1 if found, or 0 on failure. */
int findvect(const char *name, vect *result);

/* Remove every stored vector. */
void clearvects(void);

/* Return the number of vectors currently stored. */
int vectcount(void);

/* Copy the vector at index into result. Return 1 on success, or 0 on failure. */
int getvect(int index, vect *result);

#endif
