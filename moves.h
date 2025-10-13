#ifndef MOVES_H
#define MOVES_H

#include "utils.h"
#include "types.h"

void scan_capture_matrix(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece pieces[64]);
void castle(ChessPiece *king, ChessPiece *rook, ChessBoard board[8][8]);
int swap_allowed(ChessBoard board[8][8], int capture_matrix[8][8], ChessPiece piece, int tarX, int tarY);

void show_moves       (ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_pawn  (ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_rook  (ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_knight(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_bishop(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_queen (ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);
void show_moves_king  (ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8],ChessPiece piece);

#endif
