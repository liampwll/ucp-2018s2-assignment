/*
 * FILE:     helpers.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Various helper functions used by commands.
 * LAST MOD: 2018-10-20
 */

#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

/**
 * @brief Parses a double within a range.
 *
 * @param inSize The size of the input string.
 * @param in The string to be parsed.
 * @param out Pointer to output double, will not be set if non-zero is
 *        returned.
 * @param min Minimum value.
 * @param max Maximum value.
 *
 * @pre @a in points to a null-terminated sequence of characters @a inSize
 *      chars long excluding the null terminator.
 *
 * @post @a *out is set to the parsed number if the function returns non-zero.
 *
 * @return Non-zero if the entire string could not be parsed or the parsed
 *         number was not in range.
 */
int doubleParser(size_t inSize, const char *in, double *out, double min,
                 double max);

/**
 * @brief Parses an int within a range.
 *
 * @param inSize The size of the input string.
 * @param in The string to be parsed.
 * @param out Pointer to output int, will not be set if non-zero is returned.
 * @param min Minimum value.
 * @param max Maximum value.
 *
 * @pre @a in points to a null-terminated sequence of characters @a inSize
 *      chars long excluding the null terminator.
 *
 * @post @a *out is set to the parsed number if the function returns non-zero.
 *
 * @return Non-zero if the entire string could not be parsed or the parsed
 *         number was not in range.
 */
int intParser(size_t inSize, const char *in, int *out, int min, int max);

/**
 * @brief Adds two doubles if the can be added without overflow.
 *
 * @param x One of two values to be added.
 * @param y One of two values to be added.
 * @param result Pointer to output double, will not be set if non-zero is
 *        returned.
 *
 * @return Non-zero if values can no be added without overflow.
 */
int safeDoubleAdd(double x, double y, double *result);

/**
 * @brief Converts an angle in degrees to an angle in radians.
 *
 * @param deg Angle to convert.
 *
 * @return Non-zero if values can not be added without overflow.
 */
double degToRad(double deg);

#endif /* HELPERS_H */
