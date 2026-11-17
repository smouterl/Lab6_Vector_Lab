/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Implement dynamically growing vector storage, lookup, and cleanup.
 * Compilation: $ make
 */

#include "myvectarray.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static vect *storage;
static size_t stored_count;
static size_t capacity;

/**
 * Replace a vector with the same name, or add it to the next available slot.
 *
 * @param newvect Vector to store, including its name and three components.
 * @return 0 on success, or -1 for an empty name or allocation failure.
 */
int storevect(vect newvect)
{
    size_t index;

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

    if (stored_count == capacity)
    {
        size_t new_capacity = capacity == 0 ? 10 : capacity * 2;
        vect *new_storage;

        if (new_capacity < capacity || new_capacity > SIZE_MAX / sizeof(*storage))
            return -1;
        new_storage = realloc(storage, new_capacity * sizeof(*storage));
        if (new_storage == NULL)
            return -1;
        storage = new_storage;
        capacity = new_capacity;
    }

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
    size_t index;

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
 * Release the storage array and reset its count and capacity to zero.
 */
void clearvects(void)
{
    free(storage);
    storage = NULL;
    stored_count = 0;
    capacity = 0;
}

/**
 * Return the number of vectors currently stored.
 *
 * @return Number of occupied slots in the storage array.
 */
size_t vectcount(void)
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
int getvect(size_t index, vect *result)
{
    if (result == NULL || index >= stored_count)
        return 0;

    *result = storage[index];
    return 1;
}
