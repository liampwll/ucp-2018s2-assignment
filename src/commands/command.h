/*
 * FILE:     command.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Function typedefs and structs used to defining commands.
 * LAST MOD: 2018-10-20
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "../error.h"
#include "../state.h"
#include "../tokeniser.h"
#include <stddef.h>

/* Forward declaration so we can declare some functions that use this. */
typedef struct Command Command;

/**
 * @brief Parses the arguments of a command.
 *
 * This function will be called exactly once for for a given Command struct.
 * This function is free to change any field in the @a out, the default values
 * are provided for convenience.
 *
 * @param nArgs The number of arguments pointed to by args, including the
 *        command itself.
 * @param argLens Pointer to array containing the length of each arg.
 * @param args Pointer to array of arguments, including the command itself.
 * @param out The Command struct to parse the arguments in to.
 * @param printers Print functions to use for logging and error messages.
 *
 * @pre @a out->lineNumber points to the line number of the command in the
 *      input file. @a out->handler points to the handler associated with the
 *      command. @a out->destructor points to the destructor associated with
 *      this command.
 *
 * @post @a out->lineNumber is set to the line number of the command in the
 *       input file. @a out->handler points to a handler that can act on @a
 *       out. @a out->destructor points to a destructor that can act on @a
 *       out.
 *
 * @return Zero unless an error occurs.
 */
typedef int CommandParser(size_t nArgs, const size_t *argLens,
                          const char *const *args, Command *out,
                          const ErrorPrinters *printers);
/* This is a typedef of a function type rather than a typedef of a function
 * pointer type. This means we can declare functions using this type. */

/**
 * @brief Handles a command.
 *
 * This function will be called zero or more times with a Command struct that
 * was previously passed to the associated CommandParser exactly once and
 * passed to a CommandHandler zero or more times. This function is free to
 * change any value in the Command struct. If the parser returned non-zero
 * this function will never be called.
 *
 * @param command The Command struct that was previously passed to the
 *        associated CommandParser.
 * @param state The current drawing state.
 * @param printers Print functions to use for logging and error messages.
 *
 * @pre @a command was previously passed to a CommandParser exactly once. @a
 *      command has not been passed to a CommandDestructor. @a command has
 *      been passed to a CommandHandler zero or more times. @p
 *      command->lineNumber is set to the line number of the command in the
 *      input file. @a command->handler points to a handler that can act on
 *      this the Command struct. @a command->destructor points to a destructor
 *      that can act on the @a command. The CommandParser called with @p
 *      command returned zero.
 *
 * @post @a command->lineNumber is set to the line number of the command in
 *       the input file. @a command->handler points to a handler that can act
 *       on @a command. @a command->destructor points to a destructor that can
 *       act on @a command.
 *
 * @return Zero unless an error occurs.
 */
typedef int CommandHandler(Command *command, DrawingState *state,
                           const ErrorPrinters *printers);
/* This is a typedef of a function type rather than a typedef of a function
 * pointer type. This means we can declare functions using this type. */

/**
 * @brief Frees any resources in a Command struct.
 *
 * This function will be called exactly once with a Command struct that was
 * previously passed to a CommandParser exactly once and passed to a
 * CommandHandler zero or more times. This function is free to change any
 * value in the Command struct.
 *
 * @param command The Command struct that was previously passed to the
 *        associated CommandParser and possibly the associated CommandHandler.
 * @param printers Print functions to use for logging and error messages.
 *
 * @pre @a command->destructor points to this function. @a command->handler
 *      points to a CommandHandler that can act on @a command. A CommandParser
 *      has been called with @a command exactly once and returned zero. A
 *      CommandHandler has been called with @a data zero or more times.
 *
 * @return Zero unless an error occurs.
 */
typedef int CommandDestructor(Command *command, const ErrorPrinters *printers);
/* This is a typedef of a function type rather than a typedef of a function
 * pointer type. This means we can declare functions using this type. */

/**
 * @brief Used to keep track of a commands data and functions.
 */
struct Command
{
    /** The line number that the command was on to be used in error
     * messages. */
    size_t lineNumber;
    /** The handler to be called to execute the command. */
    CommandHandler *handler;
    /** The destructor to be called to clean up this commands resources. */
    CommandDestructor *destructor;
    /** The data to be used by this command. A union is used since all the
     * commands in the assignment only require a single int/double/char.
     * An array of 4 chars is provided so unicode character support can be
     * added without requiring extra memory allocation. */
    union
    {
        int intData;
        double doubleData;
        char charData[4];
        void *ptrData;
    } data;
};

#endif /* COMMAND_H */
