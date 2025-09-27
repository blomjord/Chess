#include "raylib.h"

#ifndef TYPES_H
#define TYPES_H
typedef struct {
        int type, file, rank, special_move;
        bool dragging;
//        Texture2D texture;
//        Vector2 pos;
} ChessPiece;

typedef struct {
        int type;
        Image icon;
} ChessIcon;

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
