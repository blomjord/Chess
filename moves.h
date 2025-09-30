#ifndef MOVES_H
#define MOVES_H

#include "utils.h"
#include "types.h"

int swap_allowd(ChessBoard board[8][8], ChessPiece piece, int tarX, int tarY);

void show_moves(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_pawn(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_rook(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_knight(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_bishop(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_queen(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);
void show_moves_king(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece);

#endif
