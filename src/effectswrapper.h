/*
 * FILE:     effectswrapper.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Wrapper around the library provided by for the assignment.
 * LAST MOD: 2018-10-20
 */

#ifndef EFFECTSWRAPPER_H
#define EFFECTSWRAPPER_H

#include "state.h"
#include "error.h"
#include <stddef.h>

/**
 * @brief Used to draw each pixel.
 *
 * @param[in] state The drawing state.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Zero unless drawing fails.
 */
typedef int DrawFunc(DrawingState *state, const ErrorPrinters *printers);

/**
 * @brief Wrapper around line() from effects.h.
 *
 * Takes doubles instead of ints and a DrawFunc* instead of a PlotFunc. This
 * makes command handlers a bit simpler. If plotter returns non-zero then this
 * function will terminate early and return the return value from plotter.
 * Before @a plotter is called the state is updated to the point which is
 * being plotted.
 *
 * @param[in] state Argument to be passed to plotter, will be modified
 *            before each call.
 * @param[in] x1 Start of line on x axis.
 * @param[in] y1 Start of line on y axis.
 * @param[in] x2 End of line on x axis.
 * @param[in] y2 End of line on y axis.
 * @param[in] plotter Function called for each point on the line.
 * @param[in] lineNumber Line number to print in error messages.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Zero unless plotter returns non-zero or another error occurs.
 */
int lineWrapper(DrawingState *state, double x1, double y1, double x2,
                double y2, DrawFunc *plotter, size_t lineNumber,
                const ErrorPrinters *printers);

/**
 * @brief Wrapper around clearScreen() from effects.h.
 *
 * Currently adds no additional functionality.
 *
 * @param[in] state The drawing state.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Currently always returns zero.
 */
int clearScreenWrapper(DrawingState *state, const ErrorPrinters *printers);

/**
 * @brief Wrapper around penDown() from effects.h.
 *
 * Changes @a state->pos.x to 0 and @a state->pos.y to 9999.
 *
 * @param[in] state The drawing state.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Currently always returns zero.
 */
int penDownWrapper(DrawingState *state, const ErrorPrinters *printers);

/**
 * @brief Wrapper around setFgColour() from effects.h.
 *
 * Changes @a state->fg to code.
 *
 * @param[in] state The drawing state.
 * @param[in] code The colour code to set the foreground colour too.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Currently always returns zero.
 */
int setFgColourWrapper(DrawingState *state, int code,
                       const ErrorPrinters *printers);

/**
 * @brief Wrapper around setBgColour() from effects.h.
 *
 * Changes @a state->bg to code.
 *
 * @param[in] state The drawing state.
 * @param[in] code The colour code to set the background colour too.
 * @param[in] printers Printers to use for error messages and logging.
 *
 * @return Currently always returns zero.
 */
int setBgColourWrapper(DrawingState *state, int code,
                       const ErrorPrinters *printers);

#endif /* EFFECTSWRAPPER_H */
