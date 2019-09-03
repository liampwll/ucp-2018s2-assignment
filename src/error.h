/*
 * FILE:     error.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Error printers functions used throughout the program.
 * LAST MOD: 2018-10-18
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

typedef struct ErrorPrinters ErrorPrinters;

typedef struct ErrorPrinterData ErrorPrinterData;

/* If we're compiling using gcc we can use function attributes to add checking
 * to format strings for printf-like functions. */
#if defined(__GNUC__)
/**
 * @brief printf wrapper used to print messages throughout the program.
 *
 * @param printers An ErrorPrinters struct that errorPrintersSetup() has been
 * called on.
 * @param format The format string.
 */
typedef void ErrorPrinter(const ErrorPrinters *printers, const char *format,
                          ...) __attribute__ ((__format__ (__printf__, 2, 3)));
#else
typedef void ErrorPrinter(const ErrorPrinters *printers, const char *format,
                          ...);
#endif

struct ErrorPrinters
{
    ErrorPrinter *log;
    ErrorPrinter *debug;
    ErrorPrinter *error;
    ErrorPrinterData *private;
};

typedef enum
{
    ERROR_PRINTERS_STATE_NORMAL,
    ERROR_PRINTERS_STATE_DRAWING
} ErrorPrintersState;

/**
 * @brief Setup error printers.
 *
 * @param printers The ErrorPrinters struct to setup.
 * @param log The log message file.
 * @param debug The debug message file.
 * @param error The error message file.
 *
 * @return Zero unless an error occurs.
 */
int createErrorPrinters(ErrorPrinters *printers, FILE *log, FILE *debug,
                       FILE *error);

/**
 * @brief Change the state of the error printers.
 *
 * @param printers The ErrorPrinters struct to change.
 * @param state The state to change to.
 *
 * @return Zero unless an error occurs.
 */
int errorPrintersChangeState(ErrorPrinters *printers, ErrorPrintersState state);

/**
 * @brief Check if an error occurred during printing.
 *
 * @param printers The ErrorPrinters struct to check.
 *
 * @return Zero unless an error occurred during a previous call to a printer.
 */
int errorPrintersCheckError(ErrorPrinters *printers);

/**
 * @brief Free resources used by errorPrintersSetup().
 *
 * @param printers The ErrorPrinters struct to destroy.
 *
 * @return Zero unless an error occurs.
 */
int destroyErrorPrinters(ErrorPrinters *printers);

#endif /* ERROR_H */
