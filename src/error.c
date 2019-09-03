/*
 * FILE:     error.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Error printers functions used throughout the program.
 * LAST MOD: 2018-10-18
 */

#include "error.h"
#include "effects/effects.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    FILE *file;
    int fprintfError;
} FileData;

struct ErrorPrinterData
{
    FileData log;
    FileData debug;
    FileData error;
    ErrorPrintersState state;
};

/**
 * @brief Wrapper around vfprintf.
 */
static ErrorPrinter vfprintfLogWrapper;

/**
 * @brief Wrapper around vfprintf.
 */
static ErrorPrinter vfprintfDebugWrapper;

/**
 * @brief Wrapper around vfprintf.
 */
static ErrorPrinter vfprintfErrorWrapper;

int createErrorPrinters(ErrorPrinters *printers, FILE *log, FILE *debug,
                       FILE *error)
{
    int retval = 0;

    printers->private = (ErrorPrinterData *)malloc(sizeof(ErrorPrinterData));
    if (printers->private == NULL)
    {
        fprintf(error, "Out of memory.\n");
        retval = -1;
    }

    if (retval == 0)
    {
        printers->log = &vfprintfLogWrapper;
        printers->debug = &vfprintfDebugWrapper;
        printers->error = &vfprintfErrorWrapper;
        printers->private->log.file = log;
        printers->private->log.fprintfError = 0;
        printers->private->debug.file = debug;
        printers->private->debug.fprintfError = 0;
        printers->private->error.file = error;
        printers->private->error.fprintfError = 0;
        printers->private->state = ERROR_PRINTERS_STATE_NORMAL;
    }

    if (retval == 0)
    {
        if (fprintf(log, "---\n") < 0)
        {
            fprintf(error, "Failed to write to log file.\n");
            retval = -1;
        }
    }

    if (retval != 0)
    {
        free(printers->private);
    }

    return retval;
}

static void vfprintfLogWrapper(const ErrorPrinters *printers,
                               const char *format, ...)
{
    va_list ap;

    if (printers->private->log.fprintfError == 0)
    {
        va_start(ap, format);
        printers->private->log.fprintfError =
            vfprintf(printers->private->log.file, format, ap) < 0;
        va_end(ap);
    }
}

static void vfprintfDebugWrapper(const ErrorPrinters *printers,
                                 const char *format, ...)
{
    va_list ap;

    if (printers->private->debug.fprintfError == 0)
    {
        va_start(ap, format);
        printers->private->debug.fprintfError =
            vfprintf(printers->private->debug.file, format, ap) < 0;
        va_end(ap);
    }
}

static void vfprintfErrorWrapper(const ErrorPrinters *printers,
                                 const char *format, ...)
{
    va_list ap;

    if (printers->private->error.fprintfError == 0)
    {
        if (printers->private->state == ERROR_PRINTERS_STATE_DRAWING)
        {
            /* Printing a \n to stdout moves stderr to the same position.
             * If we don't do this then stderr won't be visible. */
            penDown();
            printf("\n");
        }

        va_start(ap, format);
        printers->private->error.fprintfError =
            vfprintf(printers->private->error.file, format, ap) < 0;
        va_end(ap);
    }
}

int errorPrintersChangeState(ErrorPrinters *printers, ErrorPrintersState state)
{
    printers->private->state = state;

    return 0;
}

int errorPrintersCheckError(ErrorPrinters *printers)
{
    return (printers->private->log.fprintfError != 0)
        || (printers->private->debug.fprintfError != 0)
        || (printers->private->error.fprintfError != 0);
}

int destroyErrorPrinters(ErrorPrinters *printers)
{
    free(printers->private);

    return 0;
}
