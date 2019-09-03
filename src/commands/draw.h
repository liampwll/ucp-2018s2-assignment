/*
 * FILE:     draw.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the draw command.
 * LAST MOD: 2018-10-20
 */

#ifndef DRAW_H
#define DRAW_H

#include "command.h"

/**
 * @brief Parses the arguments of a draw command.
 *
 * The argument is a single real number between TURTLE_DBL_MIN and
 * TURTLE_DBL_MAX The argument represents the number of units to move.
 */
CommandParser drawParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a draw command.
 */
CommandHandler drawHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a draw command.
 */
CommandDestructor drawDestructor;
/* This is a function declaration, not a global variable. */

#endif /* DRAW_H */
