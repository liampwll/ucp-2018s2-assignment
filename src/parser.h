/*
 * FILE:     parser.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Command parser.
 * LAST MOD: 2018-10-18
 */

#ifndef PARSER_H
#define PARSER_H

#include "commands/command.h"
#include "error.h"
#include <stddef.h>

/**
 * @brief Lookup and parse a command.
 *
 * @param nArgs The number of arguments including the command. must be at
 *        least one.
 * @param argLens Array of lengths of arguments not including
 *        null-terminators.
 * @param args Array of null-terminated arguments.
 * @param out The command struct to output to.
 * @param lineNumber The line number to use in error and log messages.
 * @param printers Printers to use for error and log messages.
 *
 * @return Zero unless an error occurs.
 */
int parseCommand(size_t nArgs, const size_t *argLens, const char *const *args,
                 Command *out, size_t lineNumber,
                 const ErrorPrinters *printers);

#endif /* PARSER_H */
