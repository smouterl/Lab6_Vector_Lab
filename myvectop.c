/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Implement vector addition, subtraction, and scalar multiplication.
 * Compilation: $ make
 */

#include "myvectop.h"
#include <stdio.h>
#include "myvect.h"

/**
 * Add the corresponding components of two vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return The sum, with an empty name for the caller to set.
 */
vect addvect(vect a, vect b)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = a.values[i] + b.values[i];

    return result;
}

/**
 * Subtract the corresponding components of b from a.
 *
 * @param a Vector to subtract from.
 * @param b Vector to subtract.
 * @return The difference, with an empty name for the caller to set.
 */
vect subtractvect(vect a, vect b)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = a.values[i] - b.values[i];

    return result;
}

/**
 * Multiply each component of a vector by a scalar.
 *
 * @param v Vector to scale.
 * @param scalar Number by which to multiply each component.
 * @return The scaled vector, with an empty name for the caller to set.
 */
vect scalevect(vect v, double scalar)
{
    vect result = {0};

    for (int i = 0; i < 3; i++)
        result.values[i] = v.values[i] * scalar;

    return result;
}
