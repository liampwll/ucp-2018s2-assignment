/*
 * FILE:     commands.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Functions related to command lookup/manipulation.
 * LAST MOD: 2018-10-20
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "commands/command.h"

/**
 * @brief Lookup a command by its name.
 *
 * @param[in] commandLen Length of the command.
 * @param[in] command The command to lookup.
 * @param[in] parser Pointer to store the command's parser.
 * @param[out] handler Pointer to store the command's handler.
 * @param[out] dtor Pointer to store the command's destructor.
 * @param[out] lineNumber The line number to be used in error messages.
 * @param[in] printers Printers to use for errors and logging.
 *
 * @return Non-zero if an error occurs or the command can not be found.
 */
int lookupCommand(size_t commandLen, const char *command,
                  CommandParser **parser, CommandHandler **handler,
                  CommandDestructor **dtor, size_t lineNumber,
                  const ErrorPrinters *printers);

#endif /* COMMANDS_H */
