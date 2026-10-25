/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Implement storage, lookup, and clearing for up to ten vectors.
 * Compilation: $ make
 */

#include "myvectarray.h"

#include <string.h>

/* Keep the array and count available only to functions in this file. */
static vect storage[MAX_VECTORS];
static int stored_count;

/**
 * Replace a vector with the same name, or add it to the next available slot.
 *
 * @param newvect Vector to store, including its name and three components.
 * @return 0 on success, or -1 for an empty name or full storage.
 */
int storevect(vect newvect)
{
    int index;

    if (newvect.name[0] == '\0')
        return -1;

    /* Check for an existing name before checking whether storage is full. */
    for (index = 0; index < stored_count; index++)
    {
        if (strcmp(storage[index].name, newvect.name) == 0)
        {
            storage[index] = newvect;
            return 0;
        }
    }

    if (stored_count >= MAX_VECTORS)
        return -1;

    storage[stored_count] = newvect;
    stored_count++;

    return 0;
}

/**
 * Find a stored vector by name and copy it into result.
 *
 * @param name Name of the vector to find.
 * @param result Location in which to store the copy.
 * @return 1 if found, or 0 if missing or given invalid arguments.
 */
int findvect(const char *name, vect *result)
{
    int index;

    if (name == NULL || result == NULL || name[0] == '\0')
        return 0;

    for (index = 0; index < stored_count; index++)
    {
        if (strcmp(storage[index].name, name) == 0)
        {
            *result = storage[index];
            return 1;
        }
    }

    return 0;
}

/**
 * Clear the storage array and reset the vector count to zero.
 */
void clearvects(void)
{
    memset(storage, 0, sizeof(storage));
    stored_count = 0;
}

/**
 * Return the number of vectors currently stored.
 *
 * @return Number of occupied slots in the storage array.
 */
int vectcount(void)
{
    return stored_count;
}

/**
 * Copy a stored vector by index so the interface can list all vectors.
 *
 * @param index Zero-based index of the vector to retrieve.
 * @param result Location in which to store the copy.
 * @return 1 on success, or 0 for an invalid index or null result pointer.
 */
int getvect(int index, vect *result)
{
    if (result == NULL || index < 0 || index >= stored_count)
        return 0;

    *result = storage[index];
    return 1;
}
