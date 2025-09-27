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

void DrawChessboard(Rectangle ChessBoard[8][8], Color color1, Color color2);
void DrawChesspieces(BoardCell board[8][8], Rectangle RenderChessboard[8][8],
                ChessIconTexture IconTextures[12], Vector2 mousePoint,
                int square_width, int square_height);
void DrawMouseHoverAction(Rectangle ChessBoard[8][8], int ColorState[8][8]);

Texture2D InjectIcon(BoardCell board[8][8],
                ChessIconTexture IconTextures[12], int row, int col);
void LoadIcons(ChessIcon Icons[12]);
void LoadIconsAsTextures(ChessIcon Icons[12],
                ChessIconTexture IconTextures[12]);
void UnloadIcons(ChessIcon Icons[12]);
void InitChessboard(Rectangle ChessBoard[8][8], int square_width, int square_height);
#endif
