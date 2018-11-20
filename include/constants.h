#pragma once

/*
 * In this file we define some global constants.
 *
 * Please note that the problem with global variables
 * is that anyone can change them whenever which makes
 * it extremely hard to reason about your code. But for
 * constants, this is not a problem since we cannot
 * change them, and therefore they stay the same during
 * the entire execution of the program.
 */

/*
 * define the size of the window.
 */
int const screen_width  { 800 };
int const screen_height { 600 };

/*
 * define how many fps we want our program to run in.
 */
double const fps { 60.0 };

/*
 * Tiles
 */
int const xTilesMax {18};
int const yTilesMax {18};
float const tileWidth {32};

int const mapBorderOffset {(screen_height % (int)tileWidth) / 2};

/*
 * Map data characters
 */
char const startChar {'S'};
char const endChar {'E'};
char const pathChar {'0'};
char const fieldChar {'1'};
char const placeableChar {'2'};