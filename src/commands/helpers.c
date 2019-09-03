/*
 * FILE:     helpers.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Various helper functions used by commands.
 * LAST MOD: 2018-10-18
 */

#include "helpers.h"
#include "../config.h"
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

int doubleParser(size_t inSize, const char *in, double *out, double min,
                 double max)
{
    int retval;
    double result;
    char *end;

    errno = 0;
    result = strtod(in, &end);
    if ((size_t)(end - in) != inSize)
    {
        retval = -1;
    }
    else if (errno == ERANGE)
    {
        retval = -1;
    }
    else if (result != result)
    {
        /* Check for NAN, c89 doesn't have isnan(). */
        retval = -1;
    }
    else if (result < min || result > max)
    {
        retval = -1;
    }
    else
    {
        *out = result;
        retval = 0;
    }

    return retval;
}

int intParser(size_t inSize, const char *in, int *out, int min, int max)
{
    int retval;
    long result;
    char *end;

    errno = 0;
    result = strtol(in, &end, 10);
    if ((size_t)(end - in) != inSize)
    {
        retval = -1;
    }
    else if (errno == ERANGE)
    {
        retval = -1;
    }
    else if (result < min || result > max)
    {
        retval = -1;
    }
    else
    {
        *out = (int)result;
        retval = 0;
    }

    return retval;
}

int safeDoubleAdd(double x, double y, double *result)
{
    int retval;

    if (((x < 0.0) == (y < 0.0)) && (fabs(x) > (TURTLE_DBL_MAX - fabs(y))))
    {
        retval = -1;
    }
    else
    {
        retval = 0;
        *result = x + y;
    }

    return retval;
}

double degToRad(double deg)
{
    const double factor = 3.141592653589793238462643383279502884197 / 180.0;
    return deg * factor;
}
