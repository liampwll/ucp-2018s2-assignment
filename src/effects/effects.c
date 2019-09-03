/*
 * This file contains functions for drawing on the terminal.
 *
 * Use this in your UCP assignment *as is*. You *do not* need to modify these
 * functions, or even (necessarily) understand how they work.
 *
 * Author: David Cooper
 */

#include "effects.h"
#include <stdio.h>

typedef void (*MoveFunc)(int* x, int* y);

/* These are utility functions used by line(). */
static void moveRight(int* x, int* y) { (*x)++; }
static void moveLeft(int* x, int* y)  { (*x)--; }
static void moveDown(int* x, int* y)  { (*y)++; }
static void moveUp(int* x, int* y)    { (*y)--; }

/**
 * Draw a line from (x1,y1) to (x2,y2) using the *plotter function to actually
 * plot each "pixel" (character).
 */
void line(int x1, int y1, int x2, int y2, PlotFunc plotter, void *plotData)
{
    MoveFunc majorMove, minorMove;
    int x = x1, y = y1, minorDelta, majorDelta, decision, i;

    majorDelta = x2 - x1;
    majorMove = &moveRight;
    if(majorDelta < 0)
    {
        majorDelta = -majorDelta;
        majorMove = &moveLeft;
    }

    minorDelta = y2 - y1;
    minorMove = &moveDown;
    if(minorDelta < 0)
    {
        minorDelta = -minorDelta;
        minorMove = &moveUp;
    }

    if(minorDelta > majorDelta)
    {
        MoveFunc tempMove = majorMove;
        int tempDelta     = majorDelta;
        majorMove  = minorMove;
        majorDelta = minorDelta;
        minorMove  = tempMove;
        minorDelta = tempDelta;
    }

    /* Bresenham's line algorithm */
    decision = majorDelta / 2;
    for(i = 0; i <= majorDelta; i++)
    {
        /* Move to row y + 1, column x + 1 and plot a point. */
        printf("\033[%d;%dH", y + 1, x + 1);
        (*plotter)(plotData);

        /* Move along one "pixel" and (possibly) across one as well. */
        (*majorMove)(&x, &y);
        decision += minorDelta;
        if(decision >= majorDelta)
        {
            decision -= majorDelta;
            (*minorMove)(&x, &y);
        }
    }
}


/**
 * Blanks the terminal.
 */
void clearScreen()
{
    printf("\033[2J");
}


/**
 * Moves the cursor to the bottom of the screen, so that the shell's prompt
 * doesn't overwrite our beautiful drawings.
 */
void penDown()
{
    printf("\033[10000;1H");
}


/**
 * Changes the foreground colour to a code from 0-15.
 */
void setFgColour(int code)
{
    printf("\033[22;%dm", (code % 8) + 30);
    if((code % 16) >= 8)
        printf("\033[1m");
}


/**
 * Changes the background colour to a code from 0-7.
 */
void setBgColour(int code)
{
    printf("\033[%dm", (code % 8) + 40);
}
