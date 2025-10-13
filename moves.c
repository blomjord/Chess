/* ****************************************************************************
 *
 * Moving and capturing logic functions
 *
 * ***************************************************************************/

#include "utils.h"
#include "moves.h"
#include "gui.h"

/*
 * Purpose:
 *
 * Notes:
 *
 * */

/*
 * Purpose: Special move, castle king with rook.
 *
 * Notes: Only usable once
 *
 * */
void castle(ChessPiece *king, ChessPiece *rook, ChessBoard board[8][8])
{
        int k_file = king->file;
        int k_rank = king->rank;
        int r_file = rook->file;
        int r_rank = rook->rank;
        if (r_file == 0) { // Queenside
                king->file = r_file + 2;
                king->pos.x = ((r_file + 2) * SQUARE_SIZE) + PIXEL_OFFSET;
                king->pos.y = ((r_rank + 2) * SQUARE_SIZE) + PIXEL_OFFSET;
                rook->file = k_file - 1;
                rook->pos.x = ((k_file - 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                rook->pos.y = ((k_rank - 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                board[r_file + 2][r_rank].piece = king;
                board[k_file - 1][k_rank].piece = rook;
                board[r_file][r_rank].piece = NULL;
                board[k_file][k_rank].piece = NULL;
        }
        if (r_file ==  7) { // Kingside
                king->file = r_file - 1;
                king->pos.x = ((r_file - 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                king->pos.y = ((r_rank - 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                rook->file = k_file + 1;
                rook->pos.x = ((k_file + 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                rook->pos.y = ((k_rank + 1) * SQUARE_SIZE) + PIXEL_OFFSET;
                board[r_file - 1][r_rank].piece = king;
                board[k_file + 1][k_rank].piece = rook;
                board[r_file][r_rank].piece = NULL;
                board[k_file][k_rank].piece = NULL;
        }
}

/*
 * Purpose:
 *
 * Notes:
 *
 * */
int swap_allowed(ChessBoard board[8][8], int capture_matrix[8][8], ChessPiece piece, int tarX, int tarY)
{
        int type = piece.type;
        if (capture_matrix[tarX][tarY] == 1) {
                if (board[tarX][tarY].piece == NULL) {
                        return 1;
                } else {
                        if (board[tarX][tarY].piece->type * type < 0
                            || type == W_KING   // Castle
                            || type == B_KING)  // Castle
                                return 1;
                }
        }
        return 0;
}

/*
 * Purpose: Selects correct chesspiece and shows legal moves
 *
 * Notes:
 *
 * */
void show_moves(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        switch (piece.type) {
        case  1:
        case -1:
               show_moves_pawn(board, ColorState, capture_matrix, piece);
               break;
        case  2:
        case -2:
               show_moves_rook(board, ColorState, capture_matrix, piece);
                break;
        case  3:
        case -3:
                show_moves_knight(board, ColorState, capture_matrix, piece);
                break;
        case  4:
        case -4:
                show_moves_bishop(board, ColorState, capture_matrix, piece);
                break;
        case  5:
        case -5:
                show_moves_queen(board, ColorState, capture_matrix, piece);
                break;
        case  6:
        case -6:
                show_moves_king(board, ColorState, capture_matrix, piece);
                break;
        default:        // Empty cell
                break;
        }
}

// Pawn moves
void show_moves_pawn(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int leap = piece.special_move;

        if (piece.type == B_PAWN) {
                tarX = file;
                tarY = rank + 1;
                if (board[tarX][tarY].piece != NULL) {
                        if (board[tarX][tarY].piece->type == EMPTY) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        }

                } else {
                        ColorState[tarX][tarY] = 3;
                        capture_matrix[tarX][tarY] = 1;
                }
                if (board[tarX + 1][tarY].piece != NULL) {
                        if (tarX + 1 < 8 && board[tarX + 1][tarY].piece->type * type < 0) {
                                ColorState[tarX + 1][tarY] = 3;
                                capture_matrix[tarX + 1][tarY] = 1;
                        }
                }
                if (board[tarX - 1][tarY].piece != NULL) {
                        if (tarX - 1 > -1 && board[tarX - 1][tarY].piece->type * type < 0) {
                                ColorState[tarX - 1][tarY] = 3;
                                capture_matrix[tarX - 1][tarY] = 1;
                        }
                }
                if (leap) {
                        if (board[file][rank + 1].piece != NULL) {
                                if (board[file][rank + 1].piece->type * type < 0) {
                                        ColorState[file][rank + 1] = 3;
                                        capture_matrix[file][rank + 1] = 1;
                                }
                        } else {
                                ColorState[file][rank + 1] = 3;
                                capture_matrix[file][rank + 1] = 1;
                                if (board[file][rank + 2].piece != NULL) {
                                        if (board[file][rank + 2].piece->type * type < 0) {
                                                ColorState[file][rank + 2] = 3;
                                                capture_matrix[file][rank + 2] = 1;
                                        }
                                } else {
                                        ColorState[file][rank + 2] = 3;
                                        capture_matrix[file][rank + 2] = 1;
                                }
                        }
                }
        } else if (piece.type == W_PAWN) {
                tarX = file;
                tarY = rank - 1;

                if (board[tarX][tarY].piece != NULL) {
                        if (board[tarX][tarY].piece->type == EMPTY) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        }

                } else {
                        ColorState[tarX][tarY] = 3;
                        capture_matrix[tarX][tarY] = 1;
                }
                if (board[tarX + 1][tarY].piece != NULL) {
                        if (tarX + 1 < 8 && board[tarX + 1][tarY].piece->type * type < 0) {
                                ColorState[tarX + 1][tarY] = 3;
                                capture_matrix[tarX + 1][tarY] = 1;
                        }
                }
                if (board[tarX - 1][tarY].piece != NULL) {
                        if (tarX - 1 > -1 && board[tarX - 1][tarY].piece->type * type < 0) {
                                ColorState[tarX - 1][tarY] = 3;
                                capture_matrix[tarX - 1][tarY] = 1;
                        }
                }
                if (leap) {
                        if (board[file][rank - 1].piece != NULL) {
                                if (board[file][rank - 1].piece->type * type < 0) {
                                        ColorState[file][rank - 1] = 3;
                                        capture_matrix[file][rank - 1] = 1;
                                }
                        } else {
                                ColorState[file][rank - 1] = 3;
                                capture_matrix[file][rank - 1] = 1;
                                if (board[file][rank - 2].piece != NULL) {
                                        if (board[file][rank - 2].piece->type * type < 0) {
                                                ColorState[file][rank - 2] = 3;
                                                capture_matrix[file][rank - 2] = 1;
                                        }
                                } else {
                                        ColorState[file][rank - 2] = 3;
                                        capture_matrix[file][rank - 2] = 1;
                                }
                        }
                }
        }
}

// Rook moves
void show_moves_rook(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int dirX[4] = { -1, 0, 1, 0 };
        int dirY[4] = { 0, 1, 0, -1 };
        
        for (int dir = 0; dir < 4; ++dir) {
                tarX = file;
                tarY = rank;

                while (1) {
                        tarX += dirX[dir];
                        tarY += dirY[dir];
                        
                        if (tarX < 0 || tarY < 0 || tarX > 7 || tarY > 7)
                                break;

                        if (board[tarX][tarY].piece == NULL) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;

                        } else {
                                if (board[tarX][tarY].piece->type * type < 0) {
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                }
                                break;
                        }
                }
        }
}

// Knight moves
void show_moves_knight(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int rangeX[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
        int rangeY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

        for (int i = 0; i < 8; ++i) {
                tarX = file + rangeX[i];
                tarY = rank + rangeY[i];
              
                if (tarX >= 0 && tarY >= 0
                 && tarX <= 7 && tarY <= 7) {
                        if (board[tarX][tarY].piece == NULL) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;

                        } else if (board[tarX][tarY].piece->type * type < 0) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;

                        }
                }
        }
}

// Bishop moves
void show_moves_bishop(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int dirX[4] = { -1, 1, 1, -1 };
        int dirY[4] = { 1, 1, -1, -1 };

        for (int dir = 0; dir < 4; ++dir) {
                tarX = file;
                tarY = rank;
                while (1) {
                        tarX += dirX[dir];
                        tarY += dirY[dir];
               
                        if (tarX < 0 || tarY < 0 || tarX > 7 || tarY > 7)
                                break;

                        if (board[tarX][tarY].piece == NULL) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        
                        } else {
                                if (board[tarX][tarY].piece->type * type < 0) {
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                }
                                break;
                        }
                }
        }        
}

// Queen moves
void show_moves_queen(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int dirX[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
        int dirY[8] = { 0, 1, 0, -1,  1, 1, -1, -1};
        
        for (int dir = 0; dir < 8;  ++dir) {
                tarX = file;
                tarY = rank;
                
                while (1) {
                        tarX += dirX[dir];
                        tarY += dirY[dir];

                        if (tarX < 0 || tarY < 0 || tarX > 7 || tarY > 7)
                                break;

                        if (board[tarX][tarY].piece == NULL) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        } else {

                                if (board[tarX][tarY].piece->type * type < 0) {
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                }
                                break;
                        }
                }
        }
}

// King moves
void show_moves_king(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        int castle = piece.special_move;
        int rangeX[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
        int rangeY[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };

        for (int i = 0; i < 8; ++i) {
                tarX = file + rangeX[i];
                tarY = rank + rangeY[i];
                
                if (tarX >= 0 && tarY >= 0
                 && tarX <= 7 && tarY <= 7) {
                        if (board[tarX][tarY].piece == NULL) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                
                        } else if (board[tarX][tarY].piece->type * type < 0) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        }
                }
        }
        if (castle) {
                // Queenside castling
                if (board[file - 4][rank].piece != NULL
                 && board[file - 4][rank].piece->special_move
                 && board[file - 3][rank].piece == NULL
                 && board[file - 2][rank].piece == NULL
                 && board[file - 1][rank].piece == NULL) {
                        ColorState[file - 4][rank] = 3;
                        capture_matrix[file - 4][rank] = 1;
                }
                // Kingside castling
                if (board[file + 3][rank].piece != NULL
                 && board[file + 3][rank].piece->special_move
                 && board[file + 2][rank].piece == NULL
                 && board[file + 1][rank].piece == NULL) {
                        ColorState[file + 3][rank]  = 3;
                        capture_matrix[file + 3][rank] = 1;
                }
        }
}
