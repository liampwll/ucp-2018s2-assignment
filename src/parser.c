/*
 * FILE:     parser.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Command parser.
 * LAST MOD: 2018-10-18
 */

#include "parser.h"
#include "commands.h"
#include "commands/command.h"
#include "config.h"
#include "error.h"
#include <assert.h>
#include <float.h>
#include <stddef.h>

int parseCommand(size_t nArgs, const size_t *argLens, const char *const *args,
                 Command *out, size_t lineNumber,
                 const ErrorPrinters *printers)
{
    int retval = 0;
    CommandParser *parser;

    assert(nArgs != 0);

    out->lineNumber = lineNumber;

    retval = lookupCommand(argLens[0], args[0], &parser, &out->handler,
                           &out->destructor, lineNumber, printers);

    if (retval == 0)
    {
        retval = (*parser)(nArgs, argLens, args, out, printers);
    }

    return retval;
}
