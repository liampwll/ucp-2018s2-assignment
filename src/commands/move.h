/*
 * FILE:     move.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the move command.
 * LAST MOD: 2018-10-20
 */

#ifndef MOVE_H
#define MOVE_H

#include "command.h"

/**
 * @brief Parses the arguments of a move command.
 *
 * The argument is a single real number between TURTLE_DBL_MIN and
 * TURTLE_DBL_MAX.
 */
CommandParser moveParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a move command.
 */
CommandHandler moveHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a brief command.
 */
CommandDestructor moveDestructor;
/* This is a function declaration, not a global variable. */

#endif /* MOVE_H */
