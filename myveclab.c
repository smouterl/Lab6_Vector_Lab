#include "myveclab.h"
#include "myvect.h"
#include "myvectarray.h"
#include "myvectop.h"

#include <stdio.h>

void veclab(void)
{
    puts("The interactive vector calculator is not implemented yet.");
}

void printhelp(const char *program_name)
{
    printf("Usage: %s [-h]\n", program_name);
    puts("  -h  Display this help message and exit.");
    puts("Run without options to start the interactive vector calculator.");
    puts("The interactive command handler is still under development.");
}
