/*
 * FILE:     rotate.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the rotate command.
 * LAST MOD: 2018-10-20
 */

#ifndef ROTATE_H
#define ROTATE_H

#include "command.h"

/**
 * @brief Parses the arguments of a rotate command.
 *
 * The argument is a single real number between TURTLE_DBL_MIN and
 * TURTLE_DBL_MAX.
 */
CommandParser rotateParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a rotate command.
 */
CommandHandler rotateHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a rotate command.
 */
CommandDestructor rotateDestructor;
/* This is a function declaration, not a global variable. */

#endif /* ROTATE_H */
