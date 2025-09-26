#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "raylib.h"

typedef struct {
        int type;
        Image Icon;
} ChessIcon;

void DrawChessboard(int square_width, int square_height, Color color);
void DrawChesspieces(ChessPiece *board[8][8], ChessIcon Icons[12],
                int square_width, int square_height);

Image InjectIcon(ChessPiece *board[8][8], ChessIcon Icons[12], int row, int col);
void LoadIcons(ChessIcon Icons[12]);
void UnloadIcons(ChessIcon Icons[12]);
#endif
