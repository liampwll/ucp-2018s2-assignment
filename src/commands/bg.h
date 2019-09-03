/*
 * FILE:     bg.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Parser, handler, and destructor for the bg command.
 * LAST MOD: 2018-10-20
 */

#ifndef BG_H
#define BG_H

#include "command.h"

/**
 * @brief Parses the arguments of a bg command.
 *
 * The argument should be a single integer between BG_MIN and BG_MAX inclusive.
 */
CommandParser bgParser;
/* This is a function declaration, not a global variable. */

/**
 * @brief Handle a bg command.
 */
CommandHandler bgHandler;
/* This is a function declaration, not a global variable. */

/**
 * @brief Frees resources associated with a bg command.
 */
CommandDestructor bgDestructor;
/* This is a function declaration, not a global variable. */

#endif /* BG_H */
