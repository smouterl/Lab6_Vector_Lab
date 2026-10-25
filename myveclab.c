/*
 * Author: Logan Smouter
 * Date: 10/16/2026
 * Description: Read vector calculator commands and display results or errors.
 * Compilation: $ make
 */

#include "myveclab.h"
#include "myvect.h"
#include "myvectarray.h"
#include "myvectop.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 128

/**
 * Remove leading and trailing whitespace from a string.
 *
 * @param text Writable string to trim.
 * @return Pointer to the first non-whitespace character, or the ending null.
 */
static char *trim(char *text)
{
    char *end;

    while (isspace((unsigned char)*text))
        text++;

    end = text + strlen(text);
    while (end > text && isspace((unsigned char)end[-1]))
        end--;
    *end = '\0';
    return text;
}

/**
 * Check a vector name's length, characters, and use of reserved commands.
 *
 * @param name Name to check.
 * @return 1 for a valid name, or 0 otherwise.
 */
static int validname(const char *name)
{
    size_t index;

    if (strlen(name) == 0 || strlen(name) >= VECT_NAME_SIZE)
        return 0;
    if (!isalpha((unsigned char)name[0]) && name[0] != '_')
        return 0;

    for (index = 1; name[index] != '\0'; index++)
    {
        if (!isalnum((unsigned char)name[index]) && name[index] != '_')
            return 0;
    }

    /* Reserve these names for commands. */
    return strcmp(name, "quit") != 0 && strcmp(name, "clear") != 0
        && strcmp(name, "list") != 0;
}

/**
 * Convert a complete string to a finite double.
 *
 * @param text String containing the number.
 * @param value Location in which to store the converted value.
 * @return 1 on success, or 0 for invalid or out-of-range input.
 */
static int parsenumber(const char *text, double *value)
{
    char *end;

    errno = 0;
    *value = strtod(text, &end);
    return end != text && *end == '\0' && errno != ERANGE
        && isfinite(*value);
}

/**
 * Print a vector's name and three components.
 *
 * @param value Vector to display.
 */
static void printvect(const vect *value)
{
    printf("%s = %.6g  %.6g  %.6g\n", value->name,
           value->values[0], value->values[1], value->values[2]);
}

/**
 * Print every stored vector, or a message when storage is empty.
 */
static void listvects(void)
{
    int index;
    vect value;

    if (vectcount() == 0)
        puts("No vectors stored.");

    for (index = 0; index < vectcount(); index++)
    {
        if (getvect(index, &value))
            printvect(&value);
    }
}

/**
 * Read exactly three components separated by whitespace or commas.
 *
 * @param text String containing the vector components.
 * @param result Vector in which to store the components.
 * @return 1 on success, or 0 for an invalid component or separator.
 */
static int parseliteral(const char *text, vect *result)
{
    int index;
    char *end;

    for (index = 0; index < 3; index++)
    {
        while (isspace((unsigned char)*text))
            text++;

        errno = 0;
        result->values[index] = strtod(text, &end);
        if (end == text || errno == ERANGE || !isfinite(result->values[index]))
            return 0;

        text = end;
        if (index < 2)
        {
            int had_space = isspace((unsigned char)*text);

            while (isspace((unsigned char)*text))
                text++;
            if (*text == ',')
                text++;
            else if (!had_space)
                return 0;
        }
    }

    while (isspace((unsigned char)*text))
        text++;
    return *text == '\0';
}

/**
 * Retrieve a named vector and report invalid or missing names.
 *
 * @param name Name of the vector to retrieve.
 * @param result Location in which to store the retrieved vector.
 * @return 1 on success, or 0 on failure.
 */
static int lookup(const char *name, vect *result)
{
    if (!validname(name))
    {
        printf("Invalid vector name: %s\n", name);
        return 0;
    }
    if (!findvect(name, result))
    {
        printf("Vector '%s' does not exist.\n", name);
        return 0;
    }
    return 1;
}

/**
 * Evaluate a vector name, a single operation, or allowed component values.
 *
 * @param expression Writable expression split into tokens during parsing.
 * @param result Location in which to store the evaluated vector.
 * @param allow_literal Nonzero to accept three numeric components.
 * @return 1 on success, or 0 after reporting an error.
 */
static int evaluate(char *expression, vect *result, int allow_literal)
{
    char *tokens[4];
    char *token;
    char *end;
    int count = 0;
    vect left;
    vect right;
    double scalar;

    if (allow_literal)
    {
        (void)strtod(expression, &end);
        if (end != expression)
        {
            if (parseliteral(expression, result))
                return 1;
            /* If this is not three components, try scalar multiplication below. */
        }
    }

    token = strtok(expression, " \t\r\n");
    while (token != NULL && count < 4)
    {
        tokens[count++] = token;
        token = strtok(NULL, " \t\r\n");
    }

    if (count == 1)
        return lookup(tokens[0], result);

    if (count != 3)
    {
        puts("Invalid expression. Use three values or spaces around operators.");
        return 0;
    }

    if (strcmp(tokens[1], "+") == 0 || strcmp(tokens[1], "-") == 0)
    {
        if (!lookup(tokens[0], &left) || !lookup(tokens[2], &right))
            return 0;
        if (strcmp(tokens[1], "+") == 0)
            *result = addvect(left, right);
        else
            *result = subtractvect(left, right);
        return 1;
    }

    if (strcmp(tokens[1], "*") == 0)
    {
        if (parsenumber(tokens[0], &scalar))
        {
            if (!lookup(tokens[2], &right))
                return 0;
            *result = scalevect(right, scalar);
            return 1;
        }
        if (parsenumber(tokens[2], &scalar))
        {
            if (!lookup(tokens[0], &left))
                return 0;
            *result = scalevect(left, scalar);
            return 1;
        }
        puts("Multiplication requires one vector and one number.");
        return 0;
    }

    puts("Invalid expression. Supported operators are +, -, and *.");
    return 0;
}

/**
 * Parse an assignment, store its result, and display the calculated vector.
 *
 * @param command Writable command containing an equals sign.
 */
static void assignment(char *command)
{
    char *equals = strchr(command, '=');
    char *name;
    char *expression;
    vect result = {0};

    *equals = '\0';
    name = trim(command);
    expression = trim(equals + 1);

    if (!validname(name))
    {
        printf("Use a name of 1 to %d letters, digits, or underscores, starting\n"
               "with a letter or underscore. Command names are reserved.\n",
               VECT_NAME_SIZE - 1);
        return;
    }

    if (!evaluate(expression, &result, 1))
        return;

    strcpy(result.name, name);
    if (storevect(result) != 0)
        printf("Memory full: cannot store '%s'. Use clear to free storage.\n", name);

    /* Display the result even if there was no room to store it. */
    printvect(&result);
}

/**
 * Read and process commands until quit or the end of input.
 */
void veclab(void)
{
    char input[INPUT_SIZE];

    while (1)
    {
        char *command;
        vect result = {0};

        printf("minimat> ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            putchar('\n');
            return;
        }

        /* Discard the rest of a long line before reading another command. */
        if (strchr(input, '\n') == NULL)
        {
            int next = getchar();

            if (next != '\n' && next != EOF)
            {
                while (next != '\n' && next != EOF)
                    next = getchar();
                puts("Input too long. Please enter a shorter command.");
                continue;
            }
        }

        command = trim(input);
        if (*command == '\0')
            continue;
        if (strcmp(command, "quit") == 0)
            return;
        if (strcmp(command, "clear") == 0)
        {
            clearvects();
            puts("All vectors cleared.");
        }
        else if (strcmp(command, "list") == 0)
            listvects();
        else if (strchr(command, '=') != NULL)
            assignment(command);
        else if (evaluate(command, &result, 0))
        {
            /* Use ans for calculations that were not assigned a name. */
            if (result.name[0] == '\0')
                strcpy(result.name, "ans");
            printvect(&result);
        }
    }
}

/**
 * Display command-line usage, calculator commands, and input restrictions.
 *
 * @param program_name Name of the executable to show in the usage line.
 */
void printhelp(const char *program_name)
{
    printf("Usage: %s [-h]\n", program_name);
    puts("\nCommands:\n"
         "  name = x y z        Create or replace a vector\n"
         "  name = x,y,z        Commas may also separate values\n"
         "  name                Display a vector\n"
         "  vector + vector     Add vectors\n"
         "  vector - vector     Subtract vectors\n"
         "  vector * number     Scale a vector\n"
         "  number * vector     Scale a vector\n"
         "  result = expression Store and display an operation result\n"
         "  list                Display all stored vectors\n"
         "  clear               Remove all stored vectors\n"
         "  quit                Exit\n"
         "\nUse spaces around math operators. Names are case-sensitive,\n"
         "start with a letter or underscore, and contain at most 15 characters.\n"
         "Up to 10 vectors can be stored. Values may be decimal or scientific\n"
         "notation. Dot and cross products are not implemented.");
}
