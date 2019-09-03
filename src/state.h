/*
 * FILE:     state.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Drawing state tracker.
 * LAST MOD: 2018-10-18
 */

#ifndef STATE_H
#define STATE_H

#include "error.h"

typedef struct
{
    /** Current angle in degrees. */
    double angle;
    /** Current position. */
    struct
    {
        /** Current x coordinate. */
        double x;
        /** Current y coordinate. */
        double y;
    } pos;
    /** Current foreground colour. */
    int fg;
    /** Current background colour. */
    int bg;
    /** Current pattern. */
    char pattern;
} DrawingState;

/**
 * @brief Initialise a DrawingState.
 *
 * @param state The state to setup.
 * @param printers Printers to use for error and log messages.
 *
 * @return Zero unless an error occurs.
 */
int createState(DrawingState *state, const ErrorPrinters *printers);

/**
 * @brief Destroy a DrawingState.
 *
 * @param state The state to destroy.
 * @param printers Printers to use for error and log messages.
 *
 * @return Zero unless an error occurs.
 */
int destroyState(DrawingState *state, const ErrorPrinters *printers);

#endif /* STATE_H */
