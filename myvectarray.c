#include "myvectarray.h"

#include <string.h>

/* This storage is shared by this module's functions but isn't needed for other files. */
static vect storage[MAX_VECTORS];
static int stored_count;

int storevect(vect newvect)
{
    int index;

    if (newvect.name[0] == '\0')
        return -1;

    /* Replace an existing vector without consuming another storage slot. */
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

void clearvects(void)
{
    memset(storage, 0, sizeof(storage));
    stored_count = 0;
}

int vectcount(void)
{
    return stored_count;
}

int getvect(int index, vect *result)
{
    if (result == NULL || index < 0 || index >= stored_count)
        return 0;

    *result = storage[index];
    return 1;
}
