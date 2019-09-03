/*
 * FILE:     fg.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the fg command.
 * LAST MOD: 2018-10-18
 */

#include "fg.h"
#include "../config.h"
#include "../effectswrapper.h"
#include "../error.h"
#include "../state.h"
#include "helpers.h"
#include <stdlib.h>

int fgParser(size_t nArgs, const size_t *argLens, const char *const *args,
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
        retval = intParser(argLens[1], args[1], &out->data.intData, MIN_FG_ARG,
                           MAX_FG_ARG);
        if (retval != 0)
        {
            (*printers->error)(printers,
                               "Could not parse the argument on line %lu, "
                               "please enter a number between %d and %d.\n",
                               (unsigned long)out->lineNumber, MIN_FG_ARG,
                               MAX_FG_ARG);
        }
    }

    return retval;
}

int fgHandler(Command *command, DrawingState *state,
              const ErrorPrinters *printers)
{
#ifndef TURTLE_SIMPLE
    return setFgColourWrapper(state, command->data.intData, printers);
#else
    (void)command;
    (void)state;
    (void)printers;

    return 0;
#endif
}

int fgDestructor(Command *command, const ErrorPrinters *printers)
{
    (void)command;
    (void)printers;

    return 0;
}
