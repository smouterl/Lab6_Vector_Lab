/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Handle command-line arguments and start the vector calculator.
 * Compilation: $ make
 */

#include "myveclab.h"

#include <stdio.h>
#include <string.h>

/**
 * Start the calculator or display help for the -h option.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on success, or 1 for invalid arguments.
 */
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
