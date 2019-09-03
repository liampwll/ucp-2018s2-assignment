/*
 * FILE:     draw.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the draw command.
 * LAST MOD: 2018-10-18
 */

#include "draw.h"
#include "../config.h"
#include "../effectswrapper.h"
#include "../error.h"
#include "../state.h"
#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Prints the pattern stored in state->pattern.
 *
 * @return Always returns zero.
 */
static DrawFunc patternDrawFunc;

int drawParser(size_t nArgs, const size_t *argLens, const char *const *args,
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

int drawHandler(Command *command, DrawingState *state,
                const ErrorPrinters *printers)
{
    int retval = 0;
    double newX;
    double newY;
    double distance;
    (void)printers;

    distance = command->data.doubleData;

    if (retval == 0)
    {
        retval = safeDoubleAdd(state->pos.x,
                               distance * cos(degToRad(state->angle)), &newX);
        if (retval != 0)
        {
            (*printers->error)(printers,
                               "The x coordinate went outside of the range "
                               "%e to %e on line %lu, this is not allowed.\n",
                               -TURTLE_DBL_MAX, TURTLE_DBL_MAX,
                               (unsigned long)command->lineNumber);
        }
    }

    if (retval == 0)
    {
        retval = safeDoubleAdd(state->pos.y,
                               distance * sin(degToRad(state->angle)), &newY);
        if (retval != 0)
        {
            (*printers->error)(printers,
                               "The y coordinate went outside of the range "
                               "%e to %e on line %lu, this is not allowed.\n",
                               -TURTLE_DBL_MAX, TURTLE_DBL_MAX,
                               (unsigned long)command->lineNumber);
        }
    }

    if (retval == 0)
    {
        (*printers->log)(printers, "DRAW (%7.3f, %7.3f)-(%7.3f, %7.3f)\n",
                         state->pos.x, state->pos.y, newX, newY);
#ifdef TURTLE_DEBUG
        (*printers->debug)(printers, "DRAW (%7.3f, %7.3f)-(%7.3f, %7.3f)\n",
                           state->pos.x, state->pos.y, newX, newY);
#endif
        retval = lineWrapper(state, state->pos.x, state->pos.y, newX, newY,
                             &patternDrawFunc, command->lineNumber, printers);
    }

    return retval;
}

int drawDestructor(Command *command, const ErrorPrinters *printers)
{
    (void)command;
    (void)printers;

    return 0;
}

static int patternDrawFunc(DrawingState *state, const ErrorPrinters *printers)
{
    (void)printers;

    printf("%c", state->pattern);

    return 0;
}
