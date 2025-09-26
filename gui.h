#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "raylib.h"

void DrawChessboard(int square_width, int square_height, Color color);
void DrawChesspieces(ChessPiece *board[8][8], int square_width, int square_height);

void LoadIcons(Image Icons[12]);
#endif
