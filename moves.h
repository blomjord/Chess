#ifndef MOVES_H
#define MOVES_H

#include "utils.h"

Point *moves_pawn  (ChessPiece *board[8][8], ChessPiece *piece, int *num_moves);
//void moves_rook  (ChessPiece *board[8][8], ChessPiece *piece, Point moves[14]);
Point *moves_knight(ChessPiece *board[8][8], ChessPiece *piece, int *num_moves);

/*void moves_bishop(ChessPiece *board[8][8], ChessPiece *piece, Point *moves);
void moves_queen (ChessPiece *board[8][8], ChessPiece *piece, Point *moves);
void moves_king  (ChessPiece *board[8][8], ChessPiece *piece, Point *moves);
void filter_illegal_moves(ChessPiece *board[8][8], int type, int num_moves, Point *available_moves);*/
#endif
