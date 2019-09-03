/*
 * FILE:     fgetslength.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Line reading function similar to fgets.
 * LAST MOD: 2018-10-20
 */

#ifndef FGETSLENGTH_H
#define FGETSLENGTH_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Line reading function similar to fgets.
 *
 * Similar to fgets except the size parameter has been changed to size_t and
 * the return value is the number of characters that were read. This allows us
 * to handle lines that contain '\0'.
 *
 * @param s Pointer to buffer.
 * @param size Size of buffer.
 * @param stream Stream to read from.
 *
 * @pre @a s points to a buffer which is at least @a size chars.
 *
 * @post @a s contains the characters read from @a stream unless an error
 *       occurs in which case the content is undefined.
 *
 * @return Number of characters read, 0 if an error occurs. Use ferror or feof
 * to differentiate an error from an empty line at the end of the file.
 */
size_t fgetsLength(char *s, size_t size, FILE *stream);

#endif /* FGETSLENGTH_H */
