/*
 * FILE:     patern.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the pattern command.
 * LAST MOD: 2018-10-21
 */

#include "pattern.h"
#include "../error.h"
#include "../state.h"
#include <stdlib.h>

int patternParser(size_t nArgs, const size_t *argLens, const char *const *args,
                  Command *out, const ErrorPrinters *printers)
{
    int retval = 0;

    if (nArgs != 2)
    {
        retval = -1;
        (*printers->error)(printers,
                           "Wrong number of arguments on line %lu, "
                           "expected 1 but got %lu.\n",
                           (unsigned long)out->lineNumber,
                           (unsigned long)nArgs - 1);
    }

    if (retval == 0)
    {
        if (argLens[1] != 1)
        {
            retval = -1;
            (*printers->error)(printers,
                               "Could not parse the argument on line %lu, "
                               "the argument of a pattern command must be a "
                               "single character.\n",
                               (unsigned long)out->lineNumber);
        }
    }

    if (retval == 0)
    {
        out->data.charData[0] = args[1][0];
    }

    return retval;
}

int patternHandler(Command *command, DrawingState *state,
                   const ErrorPrinters *printers)
{
    (void)printers;

    state->pattern = command->data.charData[0];

    return 0;
}

int patternDestructor(Command *command, const ErrorPrinters *printers)
{
    (void)command;
    (void)printers;

    return 0;
}
