#ifndef MOVES_H
#define MOVES_H

#include "utils.h"

void moves_pawn  (ChessPiece *board[8][8], int type, int x, int y, Point *available_moves);
void moves_rook  (ChessPiece *board[8][8], int type, int x, int y, Point *available_moves);
void moves_knight(int type, int x, int y, Point *available_moves);
void moves_bishop(int type, int x, int y, Point *available_moves);
void moves_queen (int type, int x, int y, Point *available_moves);
void moves_king  (int type, int x, int y, Point *available_moves);
void filter_illegal_moves(ChessPiece *board[8][8], int type, int num_moves, Point *available_moves);
#endif
