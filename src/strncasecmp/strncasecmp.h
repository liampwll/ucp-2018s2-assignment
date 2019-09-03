/*
 * FILE:      strncasecmp.h
 * AUTHOR:    Liam Powell (19236221)
 * UNIT:      UCP (COMP1000)
 * PURPOSE:   My own implementation of the strncasecmp function from POSIX.
 * REFERENCE: http://pubs.opengroup.org/onlinepubs/9699919799/functions/strncasecmp.html
 * LAST MOD:  2018-10-21
 */

#ifndef STRNCASECMP_H
#define STRNCASECMP_H

#include <stddef.h>

/*
 * This is my own implementation of strncasecmp from POSIX.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/
 */
int strncasecmp(const char *s1, const char *s2, size_t n);

#endif /* STRNCASECMP_H */
