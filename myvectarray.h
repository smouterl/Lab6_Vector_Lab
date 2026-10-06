#ifndef MYVECTARRAY_H
#define MYVECTARRAY_H

#include "myvect.h"

#define MAX_VECTORS 10


int storevect(vect newvect);


int findvect(const char *name, vect *result);

/* Remove every stored vector. */
void clearvects(void);

/* Return the number of vectors currently stored. */
int vectcount(void);

/*
 * Copy the vector at index into result. 
 * Returns 1 for a valid index and 0 otherwise.
 */
int getvect(int index, vect *result);

#endif
