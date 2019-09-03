/*
 * FILE:     pattern.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the pattern command.
 * LAST MOD: 2018-10-20
 */

#ifndef PATTERN_H
#define PATTERN_H

#include "command.h"

/**
 * @brief Parses the arguments of a pattern command.
 *
 * The argument is a single character.
 */
CommandParser patternParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a pattern command.
 */
CommandHandler patternHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a pattern command.
 */
CommandDestructor patternDestructor;
/* This is a function declaration, not a global variable. */

#endif /* PATTERN_H */
