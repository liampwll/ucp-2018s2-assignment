/*
 * FILE:     state.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Drawing state tracker.
 * LAST MOD: 2018-10-20
 */

#include "state.h"
#include "effectswrapper.h"
#include "error.h"
#include <stdlib.h>

int createState(DrawingState *state, const ErrorPrinters *printers)
{
    int retval = 0;

    state->angle = 0;
    state->fg = 7;
    state->bg = 0;
    state->pos.x = 0;
    state->pos.y = 0;
    state->pattern = '+';

    if (retval == 0)
    {
        retval = setFgColourWrapper(state, state->fg, printers);
    }

    if (retval == 0)
    {
        retval = setBgColourWrapper(state, state->bg, printers);
    }

    if (retval == 0)
    {
        retval = clearScreenWrapper(state, printers);
    }

    return retval;
}

int destroyState(DrawingState *state, const ErrorPrinters *printers)
{
    return penDownWrapper(state, printers);
}
