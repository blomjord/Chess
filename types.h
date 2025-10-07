#include "raylib.h"

#ifndef TYPES_H
#define TYPES_H
typedef struct {
        int type, file, rank, special_move, holding;
        Texture2D texture;
        Vector2 pos;
} ChessPiece;

typedef struct {
        int file, rank;
        ChessPiece *piece;
} ChessBoard;

/*
 * Purpose:
 * Notes:
 * */
typedef struct {
        int x, y;
} Vector2_Int;
#endif

