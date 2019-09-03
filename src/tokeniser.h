/*
 * FILE:     tokeniser.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Line tokeniser.
 * LAST MOD: 2018-10-18
 */

#ifndef TOKENISER_H
#define TOKENISER_H

#include "error.h"
#include <stddef.h>

/**
 * @brief Tokenises a line.
 *
 * The arguments outputted by this function are not null-terminated.
 *
 * @param lineLen The length of the line.
 * @param line The line to be tokenised.
 * @param nArgs Number of arguments outputted to args.
 * @param argLens Pointer to store a malloced array of argument lengths at.
 * @param args Pointer to store a malloced array of arguments at. These will
 *        be pointers to the original line.
 * @param lineNumber Line number to use in log and error messages.
 * @param printers Printers to use for log and error messages.
 *
 * @pre @a line points to a null-terminated sequence of chars which is @a
 *      lineLen long excluding the null terminator.
 *
 * @post @a args points to a malloced array of pointers to null-terminated
 *       arguments from @a line unless the function returned non-zero. No
 *       memory is allocated if the function returns non-zero. @a line will
 *       be modified to null-terminate the arguments.
 *
 * @return Zero unless an error occurs.
 */
int tokeniseLine(size_t lineLen, char *line, size_t *nArgs, size_t **argLens,
                 char ***args, size_t lineNumber,
                 const ErrorPrinters *printers);

#endif /* TOKENISER_H */
