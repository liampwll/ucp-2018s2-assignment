/*
 * FILE:      strncasecmp.c
 * AUTHOR:    Liam Powell (19236221)
 * UNIT:      UCP (COMP1000)
 * PURPOSE:   My own implementation of the strncasecmp function from POSIX.
 * REFERENCE: http://pubs.opengroup.org/onlinepubs/9699919799/functions/strncasecmp.html
 * LAST MOD:  2018-10-21
 */

#include "strncasecmp.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>

/*
 * This is my own implementation of strncasecmp from POSIX.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/
 */
int strncasecmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    while ((i < n - 1) && (s1[i] != '\0') && (s2[i] != '\0')
           && (tolower(s1[i]) == tolower(s2[i])))
    {
        ++i;
    }

    return tolower(s1[i]) - tolower(s2[i]);
}
