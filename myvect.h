/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Define the vector type used by the calculator.
 */

#ifndef MYVECT_H
#define MYVECT_H

#define VECT_NAME_SIZE 16

/* Store a vector's name and three components. */
typedef struct
{
    char name[VECT_NAME_SIZE];
    double values[3];
} vect;

#endif
