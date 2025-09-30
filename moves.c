#include "utils.h"
#include "moves.h"
#include "gui.h"

int num_moves_within_board(int count, int pos_X, int pos_Y, int moves_X[], int moves_Y[]);

void show_moves(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        switch (piece.type) {
        case  1:
        case -1:
               show_moves_pawn(board, ColorState, piece);
               break;
        case  2:
        case -2:
               show_moves_rook(board, ColorState, piece);
                break;
        case  3:
        case -3:
                show_moves_knight(board, ColorState, piece);
                break;
        case  4:
        case -4:
                show_moves_bishop(board, ColorState, piece);
                break;
        case  5:
        case -5:
                printf("Queen.\n");
                break;
        case  6:
        case -6:
                show_moves_king(board, ColorState, piece);
                break;
        default:
                // Empty
                printf("Empty.\n");
                break;
        }

}

void show_moves_pawn(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int rangeX[4]   = { -1, 0, 0, 1   };
        int B_rangeY[4] = { 1, 1, 2, 1    };
        int W_rangeY[4] = { -1, -1, -2, -1 };

        if (piece.type == B_PAWN) {
                for (int i = 0; i < 4; ++i) {
                        tarX = file + rangeX[i];
                        tarY = rank + B_rangeY[i];
                        if ( tarX >= 0 && tarY >= 0 
                          && tarX <= 7 && tarY <= 7 ) {
                                ColorState[tarX][tarY] = 3;
                        }
                }

        } else if (piece.type == W_PAWN) {
                for (int i = 0; i < 4; ++i) {
                        tarX = file + rangeX[i];
                        tarY = rank + W_rangeY[i];
                        if ( tarX >= 0 && tarY >= 0 
                          && tarX <= 7 && tarY <= 7 ) {
                                ColorState[tarX][tarY] = 3;
                        }
                }

        }                
        
}

void show_moves_rook(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int dirX[4] = { -1, 0, 1, 0 };
        int dirY[4] = { 0, 1, 0, -1 };
         // TODO: This wont work as of now. Fix next time.
        for (int i = 0; i < 14; ++i) {
                tarX = file + range[i];
                if (tarX >= 0  && tarX <= 7) {
                        ColorState[tarX][rank] = 3;
                }
        }

        for (int i = 0; i < 14; ++i) {
                tarY = rank + range[i];
                if (tarY >= 0  && tarY <= 7) {
                        ColorState[file][tarY] = 3;
                }
        }
}

void show_moves_knight(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int rangeX[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
        int rangeY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

        for (int i = 0; i < 8; ++i) {
                tarX = file + rangeX[i];
                tarY = rank + rangeY[i];
                if (tarX >= 0 && tarY >= 0
                 && tarX <= 7 && tarY <= 7) {
                        ColorState[tarX][tarY] = 3;
                }
        }
}

void show_moves_bishop(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int dirX[4] = { -1, 1, 1, -1 };
        int dirY[4] = { 1, 1, -1, -1 };

        for (int i = 0; i < 4; ++i) {
                tarX = file;
                tarY = rank;
                while (1) {
                        tarX += dirX[i];
                        tarY += dirY[i];

                        if (tarX < 0 || tarY < 0 || tarX > 7 || tarY > 7)
                                break;
                        // TODO: Fix this segfault 
                        if (board[tarX][tarY].piece->type == EMPTY) {
                                ColorState[tarX][tarY] = 3;
                        
                        } else {
                                if (board[tarX][tarY].piece->type * piece.type < 0)
                                        ColorState[tarX][tarY] = 3;
                                break;
                        }
                }
        }        
}

#if 0
void moves_queen(int type, int x, int y, Point moves)
{

}
#endif
void show_moves_king(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int rangeX[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
        int rangeY[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };

        for (int i = 0; i < 8; ++i) {
                tarX = file + rangeX[i];
                tarY = rank + rangeY[i];
                if (tarX >= 0 && tarY >= 0
                 && tarX <= 7 && tarY <= 7) {
                        ColorState[tarX][tarY] = 3;
                }
        }
}

int is_move_legal(ChessPiece board[8][8], int posX, int posY, int targetX, int targetY)
{
        if (targetX >= 0 && targetY >= 0 && targetX <= 7 && targetY <= 7
                        && (board[targetX][targetY].type == EMPTY
                                || board[targetX][targetY].type * board[posX][posY].type < 0))
                return 1;
        return 0;
}
/*
 * Purpose: Returns the number of possible moves that
 * are within the borders of the chess board.
 * */
int num_moves_within_board(int count, int pos_X, int pos_Y, int moves_X[], int moves_Y[])
{
        int num_moves = 0;
        for (int i = 0; i < count; ++i) {
                int tar_X = pos_X + moves_X[i];
                int tar_Y = pos_Y + moves_Y[i];
                if (tar_X >= 0 && tar_Y >= 0 && tar_X <= 7 && tar_Y <= 7)
                        num_moves++;
        }
        return num_moves;
}
