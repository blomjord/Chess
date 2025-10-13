#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define SCREEN_WIDTH     910
#define SCREEN_HEIGHT    800
#define SQUARE_SIZE      100

#define LIGHTBEIGE (Color) { 230, 215, 215, 255 }
#define LIGHTBROWN (Color) { 196, 133, 94,  255 }
#define THREAT_RED (Color) { 255,   0,  0,  255 }

#define PIXEL_OFFSET 55 / 2

#define EMPTY            0

#define W_PAWN           1
#define W_ROOK           2
#define W_KNIGHT         3
#define W_BISHOP         4
#define W_QUEEN          5
#define W_KING           6

#define B_PAWN          -1
#define B_ROOK          -2
#define B_KNIGHT        -3
#define B_BISHOP        -4
#define B_QUEEN         -5
#define B_KING          -6

#endif
