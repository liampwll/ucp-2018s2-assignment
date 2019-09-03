/*
 * FILE:     config.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Compile time configuration.
 * LAST MOD: 2018-10-18
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * Maximum length of a line in the input file.
 */
#define MAX_LINE_LEN 100

/**
 * Minimum value of fg command argument. Must be in the range of an int.
 */
#define MIN_FG_ARG 0

/**
 * Maximum value of fg command argument. Must be in the range of an int.
 */
#define MAX_FG_ARG 15

/**
 * Minimum value of bg command argument. Must be in the range of an int.
 */
#define MIN_BG_ARG 0

/**
 * Maximum value of bg command argument. Must be in the range of an int.
 */
#define MAX_BG_ARG 7

/**
 * Used instead of DBL_MAX throughout this program to guarantee consistency
 * consistency on different C implementations. 1e37 was chosen because it is
 * guaranteed to be in the range of a double by
 * the C89 spec.
 */
#define TURTLE_DBL_MAX 1e37

/**
 * Used instead of INT_MIN throughout this program to guarantee consistency
 * consistency on different C implementations. -32767 was chosen because it is
 * guaranteed to be in the range of an int by the C89 spec.
 */
#define TURTLE_INT_MIN -32767

/**
 * Used instead of INT_MAX throughout this program to guarantee consistency
 * consistency on different C implementations. 32767 was chosen because it is
 * guaranteed to be in the range of an int by the C89 spec.
 */
#define TURTLE_INT_MAX 32767

/**
 * Controls whether or not to draw the last point of a line, if this is true
 * then the command "DRAW 0" will draw 1 character and "DRAW 1" will draw 2
 * characters.
 */
#define DRAW_LAST_POINT 0

/**
 * The minimum x/y coordinate that can be drawn by the provided effects
 * library.
 */
#define EFFECTS_LINE_MIN 0

/**
 * The maximum x/y coordinate that can be drawn by the provided effects
 * library.
 */
#define EFFECTS_LINE_MAX TURTLE_INT_MAX

/**
 * If true lineWrapper will fail when an attempt is made to draw a line
 * outside the bounds defined by EFFECTS_LINE_MIN and EFFECTS_LINE_MAX.
 *
 * If false lineWrapper will only draw the segment of the line that's within
 * the bounds defined by EFFECTS_LINE_MIN and EFFECTS_LINE_MAX. (Note: This
 * has not been implemented.)
 */
#define FAIL_ON_OUT_OF_BOUNDS_LINE 1

#endif /* CONFIG_H */
