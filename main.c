#include "myveclab.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        veclab();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        printhelp(argv[0]);
        return 0;
    }

    fprintf(stderr, "Usage: %s [-h]\n", argv[0]);
    return 1;
}
