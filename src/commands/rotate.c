/*
 * FILE:     rotate.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the rotate command.
 * LAST MOD: 2018-10-18
 */

#include "rotate.h"
#include "../config.h"
#include "../error.h"
#include "../state.h"
#include "helpers.h"
#include <math.h>
#include <stdlib.h>

int rotateParser(size_t nArgs, const size_t *argLens, const char *const *args,
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
        retval = doubleParser(argLens[1], args[1], &out->data.doubleData,
                              -TURTLE_DBL_MAX, TURTLE_DBL_MAX);
        if (retval != 0)
        {
            (*printers->error)(printers,
                               "Could not parse the argument on line %lu, "
                               "please enter a number between %e and %e.\n",
                               (unsigned long)out->lineNumber, -TURTLE_DBL_MAX,
                               TURTLE_DBL_MAX);
        }
    }

    return retval;
}

int rotateHandler(Command *command, DrawingState *state,
                  const ErrorPrinters *printers)
{
    (void)printers;

    /* Subtract the angle since the coordinate system is upside down. */
    state->angle -= command->data.doubleData;
    if (state->angle >= 360.0 || state->angle <= -360.0)
    {
        state->angle = fmod(state->angle, 360);
    }

    return 0;
}

int rotateDestructor(Command *command, const ErrorPrinters *printers)
{
    (void)command;
    (void)printers;

    return 0;
}
