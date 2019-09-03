/*
 * FILE:     fg.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the fg command.
 * LAST MOD: 2018-10-20
 */

#ifndef FG_H
#define FG_H

#include "command.h"

/**
 * @brief Parses the arguments of a fg command.
 *
 * The argument should be a single integer between FG_MIN and FG_MAX inclusive.
 */
CommandParser fgParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a fg command.
 */
CommandHandler fgHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a fg command.
 */
CommandDestructor fgDestructor;
/* This is a function declaration, not a global variable. */

#endif /* FG_H */
