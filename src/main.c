/*
 * FILE:     main.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Main file.
 * LAST MOD: 2018-10-18
 */

#include "commands/command.h"
#include "config.h"
#include "effectswrapper.h"
#include "error.h"
#include "fgetslength/fgetslength.h"
#include "linkedlist/linkedlist.h"
#include "parser.h"
#include "tokeniser.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Read a single line from the input file.
 *
 * Fails if the line is longer than maxLen.
 *
 * @param stream The file to read from.
 * @param maxLen The maximum line length.
 * @param line Buffer to output the line to.
 * @param lineLen Pointer to output the length of the line.
 * @param lineNumber Line number to use in log and error messages.
 * @param printers Printers to use for log and error messages.
 *
 * @return Zero unless an error occurs.
 */
static int readLine(FILE *stream, size_t maxLen, char *line, size_t *lineLen,
                    size_t lineNumber, ErrorPrinters *printers);

/**
 * @brief Process a file of commands.
 *
 * @param stream The file to read from.
 * @param list The list to read in to.
 * @param printers Printers to use for log and error messages.
 *
 * @return Zero unless an error occurs.
 */
static int processFile(FILE *stream, LinkedList **list,
                       ErrorPrinters *printers);

/**
 * @brief Process a line containing a command.
 *
 * @param lineLen The length of the line.
 * @param line The line.
 * @param out Pointer to output a malloced command to.
 * @param lineNumber Line number to use in log and error messages.
 * @param printers Printers to use for log and error messages.
 *
 * @return Zero unless an error occurs.
 */
static int processLine(size_t lineLen, char *line, Command **out,
                       size_t lineNumber, ErrorPrinters *printers);

/**
 * @brief Run the commands in a list.
 *
 * Stops if a command fails. Consumes list elements.
 *
 * @param list The list to pop commands from.
 * @param printers Printers to use for log and error messages.
 *
 * @return Zero unless an error occurs.
 */
static int runCommands(LinkedList *list, ErrorPrinters *printers);

/**
 * @brief Run the destructors for the commands in a list.
 *
 * Consumes list elements.
 *
 * @param list The list to pop commands from.
 * @param printers Printers to use for log and error messages.
 *
 * @return Zero unless an error occurs.
 */
static int destroyCommands(LinkedList *list, ErrorPrinters *printers);

int main(int argc, char **argv)
{
    int retval = 0;
    const char *logFilePath = "graphics.log";
    FILE *inputFile = NULL;
    FILE *logFile = NULL;
    LinkedList *list = NULL;
    ErrorPrinters printers = {0};

    if (argc != 2)
    {
        fprintf(stderr, "Provide exactly one command line argument.\n");
        retval = -1;
    }

    if (retval == 0)
    {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL)
        {
            fprintf(stderr, "Could not open input file (%s).\n", argv[1]);
            retval = -1;
        }
    }

    if (retval == 0)
    {
        logFile = fopen(logFilePath, "a");
        if (logFile == NULL)
        {
            fprintf(stderr, "Could not open log file (%s).\n", logFilePath);
            retval = -1;
        }
    }

    if (retval == 0)
    {
        retval = createErrorPrinters(&printers, logFile, stderr, stderr);
    }

    if (retval == 0)
    {
        retval = processFile(inputFile, &list, &printers);
        fclose(inputFile);
        inputFile = NULL;
    }

    if (retval == 0)
    {
        retval = errorPrintersChangeState(&printers,
                                          ERROR_PRINTERS_STATE_DRAWING);
    }

    if (retval == 0)
    {
        retval = runCommands(list, &printers);
    }

    if (retval == 0)
    {
        /* Not being able to print an error isn't fatal, so we leave this
         * check until the end of the program. */
        retval = errorPrintersCheckError(&printers);
    }

    if (inputFile != NULL)
    {
        fclose(inputFile);
    }
    if (logFile != NULL)
    {
        fclose(logFile);
    }
    if (list != NULL)
    {
        if (retval == 0)
        {
            retval = destroyCommands(list, &printers);
        }
        else
        {
            destroyCommands(list, &printers);
        }
    }
    destroyErrorPrinters(&printers);

    return retval;
}

static int readLine(FILE *stream, size_t maxLen, char *line, size_t *lineLen,
                    size_t lineNumber, ErrorPrinters *printers)
{
    int retval;

    *lineLen = fgetsLength(line, maxLen, stream);

    if (*lineLen == 0)
    {
        if (!feof(stream))
        {
            retval = -1;
            (*printers->error)(printers, "Error while reading file.");
        }
        else
        {
            /* End of file. */
            retval = 0;
        }
    }
    else if (line[*lineLen - 1] != '\n' && !feof(stream))
    {
        retval = -1;
        /* Line too long, get rid of the rest of the line. */
        while (*lineLen != 0 && line[*lineLen] != '\n' && !feof(stream))
        {
            *lineLen = fgetsLength(line, maxLen, stream);
        }

        if (*lineLen == 0 && !feof(stream))
        {
            /* A read error takes precedence over a long line error. */
            (*printers->error)(printers, "Error while reading file.");
        }
        else
        {
            (*printers->error)(printers, "Line %lu too long, max length %d",
                               lineNumber, MAX_LINE_LEN);
        }
    }
    else
    {
        retval = 0;
    }

    /* Remove trailing \n. */
    if (retval == 0)
    {
        if (*lineLen != 0 && line[*lineLen - 1] == '\n')
        {
            line[--*lineLen] = '\0';
        }
    }

    return retval;
}

static int processFile(FILE *stream, LinkedList **list, ErrorPrinters *printers)
{
    int retval = 0;
    char *line;
    size_t lineLen;
    size_t lineNumber;
    Command *command = NULL;

    line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    if (line == NULL)
    {
        (*printers->error)(printers, "Out of memory.\n");
        retval = -1;
    }

    if (retval == 0)
    {
        *list = linkedListCreate();
        if (*list == NULL)
        {
            (*printers->error)(printers, "Out of memory.\n");
            retval = -1;
        }
    }

    if (retval == 0)
    {
        lineNumber = 1;
        retval = readLine(stream, MAX_LINE_LEN, line, &lineLen, lineNumber,
                          printers);
    }

    while (retval == 0 && lineLen != 0)
    {
        retval = processLine(lineLen, line, &command, lineNumber, printers);

        if (retval == 0)
        {
            if (linkedListInsert(*list, linkedListLength(*list), command) != 0)
            {
                retval = -1;
                (*printers->error)(printers, "Out of memory.\n");
                command->destructor(command, printers);
            }
        }

        if (retval == 0)
        {
            retval = readLine(stream, MAX_LINE_LEN, line, &lineLen, lineNumber,
                              printers);
            ++lineNumber;
        }
    }

    if (retval != 0)
    {
        free(command);
    }

    free(line);

    return retval;
}

static int processLine(size_t lineLen, char *line, Command **out,
                       size_t lineNumber, ErrorPrinters *printers)
{
    int retval = 0;
    size_t nArgs;
    size_t *argLens = NULL;
    char **args = NULL;

    *out = (Command *)malloc(sizeof(Command));
    if (*out == NULL)
    {
        retval = -1;
        (*printers->error)(printers, "Out of memory.\n");
    }

    if (retval == 0)
    {
        retval = tokeniseLine(lineLen, line, &nArgs, &argLens, &args,
                              lineNumber, printers);
    }

    if (retval == 0)
    {
        retval = parseCommand(nArgs, argLens, (const char *const *)args, *out,
                              lineNumber, printers);
    }

    free(argLens);
    free(args);

    return retval;
}

static int runCommands(LinkedList *list, ErrorPrinters *printers)
{
    int retval = 0;
    DrawingState state;
    Command *command;

    retval = createState(&state, printers);

    while (linkedListLength(list) != 0 && retval == 0)
    {
        command = linkedListPop(list, 0);
        retval = command->handler(command, &state, printers);
        if (retval == 0)
        {
            retval = command->destructor(command, printers);
        }
        else
        {
            command->destructor(command, printers);
        }
        free(command);
    }

    if (retval == 0)
    {
        retval = destroyState(&state, printers);
    }
    else
    {
        destroyState(&state, printers);
    }

    return retval;
}

static int destroyCommands(LinkedList *list, ErrorPrinters *printers)
{
    int tmp;
    int retval = 0;
    Command *command;

    while (linkedListLength(list) != 0)
    {
        command = linkedListPop(list, 0);
        tmp = command->destructor(command, printers);
        retval = tmp ? tmp : retval;
        free(command);
    }

    linkedListDestroy(list);

    return retval;
}
