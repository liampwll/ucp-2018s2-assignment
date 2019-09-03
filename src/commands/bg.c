/*
 * FILE:     bg.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the bg command.
 * LAST MOD: 2018-10-18
 */

#include "bg.h"
#include "../config.h"
#include "../effectswrapper.h"
#include "../error.h"
#include "../state.h"
#include "helpers.h"
#include <stdlib.h>

int bgParser(size_t nArgs, const size_t *argLens, const char *const *args,
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
        retval = intParser(argLens[1], args[1], &out->data.intData, MIN_BG_ARG,
                           MAX_BG_ARG);
        if (retval != 0)
        {
            (*printers->error)(printers,
                               "Could not parse the argument on line %lu, "
                               "please enter a number between %d and %d.\n",
                               (unsigned long)out->lineNumber, MIN_BG_ARG,
                               MAX_BG_ARG);
        }
    }

    return retval;
}

int bgHandler(Command *command, DrawingState *state,
              const ErrorPrinters *printers)
{
#ifndef TURTLE_SIMPLE
    return setBgColourWrapper(state, command->data.intData, printers);
#else
    (void)command;
    (void)state;
    (void)printers;

    return 0;
#endif
}

int bgDestructor(struct Command *command, const ErrorPrinters *printers)
{
    (void)command;
    (void)printers;

    return 0;
}
