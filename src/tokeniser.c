/*
 * FILE:     tokeniser.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Line tokeniser.
 * LAST MOD: 2018-10-18
 */

#include "tokeniser.h"
#include "error.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Count the number of arguments in a line.
 *
 * @param lineLen The length of the line.
 * @param line The line.
 *
 * @pre @p line points to a sequence of characters @p lineLen chars long.
 *
 * @return The number of arguments in the line.
 */
static size_t countArgs(size_t lineLen, char *line);

/**
 * @brief Put the arguments from a line in to arrays unless @p args is NULL.
 *
 * Will add null-terminators to the arguments of @p line if @p args is not
 * NULL.
 *
 * @param lineLen The length of the line.
 * @param line The line.
 * @param argLens Array of arguments lengths (excluding the null-terinator) or
 *        NULL.
 * @param args Array of arguments or NULL.
 *
 * @pre @p line points to a sequence of characters @p lineLen chars long. If
 *      @p args is not NULL then @p args points to an array large enough to
 *      hold all the arguments in @p line and @p argLens points to an array
 *      large enough to hold the lengths of all arguments in @p line.
 *
 * @post If @p args is not NULL then @p args contains pointers to the
 *       arguments in @p line which have had null-terminators added to them
 *       and @p argLens contains the lengths of all the arguments.
 *
 * @return The number of arguments in the line.
 */
static size_t setArgs(size_t lineLen, char *line, size_t *argLens,
                      char **args);

int tokeniseLine(size_t lineLen, char *line, size_t *nArgs, size_t **argLens,
                 char ***args, size_t lineNumber,
                 const ErrorPrinters *printers)
{
    int retval = 0;

    *args = NULL;
    *argLens = NULL;

    *nArgs = countArgs(lineLen, line);

    if (*nArgs == 0)
    {
        retval = -1;
        (*printers->error)(printers, "No command/arguments on line %lu.\n",
                           (unsigned long)lineNumber);
    }

    if (retval == 0)
    {
        *args = malloc(sizeof(char *) * *nArgs);
        if (*args == NULL)
        {
            retval = -1;
            (*printers->error)(printers, "Out of memory.\n");
        }
    }

    if (retval == 0)
    {
        *argLens = malloc(sizeof(size_t) * *nArgs);
        if (*argLens == NULL)
        {
            retval = -1;
            (*printers->error)(printers, "Out of memory.\n");
        }
    }

    if (retval == 0)
    {
        setArgs(lineLen, line, *argLens, *args);
    }

    if (retval != 0)
    {
        free(*args);
        free(*argLens);
        *args = NULL;
        *argLens = NULL;
    }

    return retval;
}

static size_t countArgs(size_t lineLen, char *line)
{
    return setArgs(lineLen, line, NULL, NULL) + 1;
}

static size_t setArgs(size_t lineLen, char *line, size_t *argLens,
                      char **args)
{
    size_t i;
    size_t count = 0;
    size_t len = 0;
    int inArg = 0;

    for (i = 0; i < lineLen; ++i)
    {
        if ((line[i] == ' ') && inArg)
        {
            inArg = 0;
            if (args != NULL)
            {
                line[i] = '\0';
                argLens[count] = len;
            }
            ++count;
        }
        else if ((line[i] != ' ') && !inArg)
        {
            inArg = 1;
            len = 1;
            if (args != NULL)
            {
                args[count] = line + i;
            }
        }
        else
        {
            len += 1;
        }
    }

    if (args != NULL && inArg)
    {
        line[i] = '\0';
        argLens[count] = len;
    }

    return count;
}
