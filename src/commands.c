/*
 * FILE:     commands.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Functions related to command lookup/manipulation.
 * LAST MOD: 2018-10-18
 */

#include "commands.h"
#include "strncasecmp/strncasecmp.h"
#include "commands/bg.h"
#include "commands/draw.h"
#include "commands/fg.h"
#include "commands/move.h"
#include "commands/pattern.h"
#include "commands/rotate.h"
#include <stddef.h>
#include <string.h>

int lookupCommand(size_t commandLen, const char *command,
                  CommandParser **parser, CommandHandler **handler,
                  CommandDestructor **dtor, size_t lineNumber,
                  const ErrorPrinters *printers)
{
    static const struct
    {
        /** Name of the command. */
        const char *command;
        /** Parser for the command. */
        CommandParser *parser;
        /** Handler for the command. */
        CommandHandler *handler;
        /** Destructor for the command, or NULL if no destructor is required. */
        CommandDestructor *dtor;
    } table[] =
    {
        {"bg",      &bgParser,      &bgHandler,      &bgDestructor     },
        {"draw",    &drawParser,    &drawHandler,    &drawDestructor   },
        {"fg",      &fgParser,      &fgHandler,      &fgDestructor     },
        {"move",    &moveParser,    &moveHandler,    &moveDestructor   },
        {"pattern", &patternParser, &patternHandler, &patternDestructor},
        {"rotate",  &rotateParser,  &rotateHandler,  &rotateDestructor }
    };

    int retval;
    size_t i;
    int found;

    found = 0;
    i = 0;
    *parser = NULL;
    while (!found && i < sizeof(table) / sizeof(table[0]))
    {
        if ((commandLen == strlen(table[i].command))
            && (strncasecmp(table[i].command, command, commandLen) == 0))
        {
            *parser = table[i].parser;
            *handler = table[i].handler;
            *dtor = table[i].dtor;
            found = 1;
        }
        ++i;
    }

    if (!found)
    {
        (*printers->error)(printers, "Unrecognised command on line %lu.\n",
                           (unsigned long)lineNumber);
        retval = -1;
    }
    else
    {
        retval = 0;
    }

    return retval;
}
