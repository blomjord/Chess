#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "raylib.h"

typedef struct {
        int type;
        Image icon;
} ChessIcon;

typedef struct {
        int type;
        Texture2D texture;
} ChessIconTexture;

void DrawChessboard(int square_width, int square_height, Color color);
void DrawChesspieces(ChessPiece *board[8][8], ChessIconTexture IconTextures[12],
                int square_width, int square_height);

Texture2D InjectIcon(ChessPiece *board[8][8],
                ChessIconTexture IconTextures[12], int row, int col);
void LoadIcons(ChessIcon Icons[12]);
void LoadIconsAsTextures();
void UnloadIcons(ChessIcon Icons[12]);
#endif
