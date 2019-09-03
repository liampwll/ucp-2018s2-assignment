/*
 * FILE:     effectswrapper.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Wrapper around the library provided by for the assignment.
 * LAST MOD: 2018-10-20
 */

#include "effectswrapper.h"
#include "config.h"
#include "effects/effects.h"
#include "error.h"
#include <float.h>
#include <math.h>
#include <stddef.h>

/** Used for state tracking in drawFuncWrapper. */
typedef struct
{
    /** Starting x coordinate. */
    double startX;
    /** Starting y coordinate. */
    double startY;
    /** Delta to change @a state->x by each step. */
    double deltaX;
    /** Delta to change @a state->y by each step. */
    double deltaY;
    /** The drawing state. */
    DrawingState *state;
    /** DrawFunc provided by the caller. */
    DrawFunc *plotter;
    /** Printers to use for error and log messages. */
    const ErrorPrinters *printers;
    /** The number of points drawn. */
    unsigned int count;
    /** The total number of points to be drawn. */
    unsigned int totalPoints;
    /** Return value of last call to plotter. */
    int error;
} DrawFuncWrapperState;

/**
 * @brief Used to add extra functionality to the plotter callback in the
 * effects library.
 *
 * Changes the state to the point that is being plotted before calling the
 * DrawFunc provided via lineWrapper. Won't call a DrawFunc again if the
 * previous call returned non-zero.
 *
 * @param data DrawFuncWrapperState* cast to void*
 */
static void drawFuncWrapper(void *data);

/**
 * @brief Round real coordinates to integers.
 *
 * If FAIL_ON_OUT_OF_BOUNDS_LINE is false this function will return the
 * segment of the line inside the bounds described in config.h. If
 * FAIL_ON_OUT_OF_BOUNDS_LINE is true this function will fail and return
 * non-zero when the coordinates are out of bounds.
 *
 * @param[in] x1 Pointer to first x coordinate.
 * @param[in] y1 Pointer to first y coordinate.
 * @param[in] x2 Pointer to second x coordinate.
 * @param[in] y2 Pointer to second y coordinate.
 * @param[out] x1int Pointer to first x coordinate as int to be passed to
 *             line().
 * @param[out] y1int Pointer to first y coordinate as int to be passed to
 *             line().
 * @param[out] x2int Pointer to second x coordinate as int to be passed to
 *             line().
 * @param[out] y2int Pointer to second y coordinate as int to be passed to
 *             line().
 * @param[in] lineNumber Line number to use in error and log messages.
 * @param[in] printers Printers to use for error and log messages.
 *
 * @return Zero unless an error occurs.
 */
static int roundCoords(double *x1, double *y1, double *x2, double *y2,
                       int *x1int, int *y1int, int *x2int, int *y2int,
                       size_t lineNumber, const ErrorPrinters *printers);

int lineWrapper(DrawingState *state, double x1, double y1, double x2,
                double y2, DrawFunc *plotter, size_t lineNumber,
                const ErrorPrinters *printers)
{
    int retval;
    int x1int;
    int y1int;
    int x2int;
    int y2int;
    unsigned int distanceXint;
    unsigned int distanceYint;
    double distance;
    double distanceX;
    double distanceY;
    DrawFuncWrapperState wrapperState;

    retval = roundCoords(&x1, &x2, &y1, &y2, &x1int, &x2int, &y1int, &y2int,
                         lineNumber, printers);

    if (retval == 0)
    {
        distanceX = x2 - x1;
        distanceY = y2 - y1;
        distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        distanceXint =
            x1int > x2int ? (unsigned)x1int - x2int : (unsigned)x2int - x1int;
        distanceYint =
            y1int > y2int ? (unsigned)y1int - y2int : (unsigned)y2int - y1int;

        wrapperState.deltaX = distance == 0.0 ? 0.0 : distanceX / distance;
        wrapperState.deltaY = distance == 0.0 ? 0.0 : distanceY / distance;
        wrapperState.state = state;
        wrapperState.plotter = plotter;
        wrapperState.printers = printers;
        wrapperState.count = 0;
        wrapperState.totalPoints =
            distanceXint > distanceYint ? distanceXint : distanceYint;
        wrapperState.error = 0;
        wrapperState.startX = x1;
        wrapperState.startY = y1;

        line(x1int, y1int, x2int, y2int, &drawFuncWrapper, &wrapperState);

        state->pos.x = x2;
        state->pos.y = y2;

        retval = wrapperState.error;
    }

    return retval;
}

int clearScreenWrapper(DrawingState *state, const ErrorPrinters *printers)
{
    (void)state;
    (void)printers;

    clearScreen();

    return 0;
}

int penDownWrapper(DrawingState *state, const ErrorPrinters *printers)
{
    (void)printers;

    penDown();
    state->pos.x = 0;
    state->pos.y = 9999;

    return 0;
}

int setFgColourWrapper(DrawingState *state, int code,
                       const ErrorPrinters *printers)
{
    (void)printers;

    setFgColour(code);
    state->fg = code;

    return 0;
}

int setBgColourWrapper(DrawingState *state, int code,
                       const ErrorPrinters *printers)
{
    (void)printers;

    setBgColour(code);
    state->bg = code;

    return 0;
}

static void drawFuncWrapper(void *data)
{
    DrawFuncWrapperState *state = data;

    if (state->error == 0)
    {
        state->state->pos.x = state->startX + state->deltaX * state->count;
        state->state->pos.y = state->startY + state->deltaY * state->count;

        if (DRAW_LAST_POINT || state->count != state->totalPoints)
        {
            state->error = (*state->plotter)(state->state, state->printers);
        }

        ++state->count;
    }
}

#if FAIL_ON_OUT_OF_BOUNDS_LINE
static int roundCoords(double *x1, double *y1, double *x2, double *y2,
                       int *x1int, int *y1int, int *x2int, int *y2int,
                       size_t lineNumber, const ErrorPrinters *printers)
{
    int retval = 0;

    if ((floor(*x1 + 0.5) < EFFECTS_LINE_MIN)
        || (floor(*x1 + 0.5) > EFFECTS_LINE_MAX)
        || (floor(*x2 + 0.5) < EFFECTS_LINE_MIN)
        || (floor(*x2 + 0.5) > EFFECTS_LINE_MAX)
        || (floor(*y1 + 0.5) < EFFECTS_LINE_MIN)
        || (floor(*y1 + 0.5) > EFFECTS_LINE_MAX)
        || (floor(*y2 + 0.5) < EFFECTS_LINE_MIN)
        || (floor(*y2 + 0.5) > EFFECTS_LINE_MAX))
    {
        retval = -1;
        (*printers->error)(printers,
                           "Tried to draw a line out of bounds on line %lu, "
                           "lines can only be drawn between (%d, %d) and "
                           "(%d, %d).\n",
                           (unsigned long)lineNumber, EFFECTS_LINE_MIN,
                           EFFECTS_LINE_MIN, EFFECTS_LINE_MAX,
                           EFFECTS_LINE_MAX);
#if !DRAW_LAST_POINT
        (*printers->error)(printers,
                           "The compile time variable DRAW_LAST_POINT is "
                           "false, which means the line you tried to draw "
                           "might be in bounds but the end of the line is "
                           "out of bounds. This behaviour is intentional "
                           "as it ensures that DRAW_LAST_POINT will not "
                           "affect whether or not an input file is valid.\n");
#endif
    }

    if (retval == 0)
    {
        *x1int = (int)floor(*x1 + 0.5);
        *x2int = (int)floor(*x2 + 0.5);
        *y1int = (int)floor(*y1 + 0.5);
        *y2int = (int)floor(*y2 + 0.5);
    }

    return retval;
}
#else
/* Algorithm to use for line truncation. */
/* https://en.wikipedia.org/wiki/Line-line_intersection */
#error "Line truncation is not implemented yet."
#endif
