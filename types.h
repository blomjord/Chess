#include "raylib.h"

#ifndef TYPES_H
#define TYPES_H
typedef struct {
        int type, file, rank, special_move, dragging;
        Texture2D texture;
        Vector2 pos;
//        Rectangle grabArea;
} ChessPiece;

typedef struct {
        int type;
        Image icon;
} ChessIcon;

typedef struct {
        int file, rank;
        ChessPiece *piece;
} ChessBoard;

typedef struct {
        int type;
        Texture2D texture;
} ChessIconTexture;

/*
 * Purpose:
 * Notes:
 * */
typedef struct {
        int x, y;
} Point;
#endif
