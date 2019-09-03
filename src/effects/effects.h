/**
 * Defines the plotter functions required by line().
 */
typedef void (*PlotFunc)(void *plotData);

/**
 * Draw a line from (x1,y1) to (x2,y2) using the *plotter function to actually
 * plot each "pixel" (character).
 */
void line(int x1, int y1, int x2, int y2, PlotFunc plotter, void *plotData);

/**
 * Blanks the terminal.
 */
void clearScreen();

/**
 * Moves the cursor to the bottom of the screen, so that the shell's prompt
 * doesn't overwrite our beautiful drawings.
 */
void penDown();

/**
 * Changes the foreground colour to a code from 0-15.
 */
void setFgColour(int code);

/**
 * Changes the background colour to a code from 0-7.
 */
void setBgColour(int code);
