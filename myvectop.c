#include "myvectop.h"
#include <stdio.h>
#include "myvect.h"

vect addvect(vect a, vect b)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = a.values[i] + b.values[i];

    return result;
}

vect subtractvect(vect a, vect b)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = a.values[i] - b.values[i];

    return result;
}

vect scalevect(vect v, double scalar)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = v.values[i] * scalar;

    return result;
}