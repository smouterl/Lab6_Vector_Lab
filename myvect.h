#ifndef MYVECT_H
#define MYVECT_H

#define VECT_NAME_SIZE 16

typedef struct
{
    char name[VECT_NAME_SIZE];
    double values[3];
} vect;

#endif