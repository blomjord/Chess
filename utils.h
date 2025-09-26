#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define EMPTY NULL

#define W_PAWN 1
#define W_ROOK 2
#define W_KNIGHT 3
#define W_BISHOP 4
#define W_QUEEN 5
#define W_KING 6

#define B_PAWN -1
#define B_ROOK -2
#define B_KNIGHT -3
#define B_BISHOP -4
#define B_QUEEN -5
#define B_KING -6

/*
 * Purpose: Main data structure for chess pieces.
 *
 * Variables:
 * type: Type of chess piece
 * x, y: Coordinates
 * special_move: Flag if king has castled or pawn has used en passant
 *
 * Notes:
 * */
typedef struct {
        int type, x, y, special_move;
        char symbol;
} ChessPiece;

/*
 * Purpose:
 * Notes:
 * */
typedef struct {
        int x, y;
} Point;

#endif
