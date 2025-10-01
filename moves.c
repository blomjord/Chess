#include "utils.h"
#include "moves.h"
#include "gui.h"

/*
 * Purpose:
 * Notes:
 * */
int swap_allowed(ChessBoard board[8][8], int capture_matrix[8][8], ChessPiece piece, int tarX, int tarY)
{
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
        if (capture_matrix[tarX][tarY] == 1) {
                if (board[tarX][tarY].piece == NULL) {
                        return 1;
                } else {
                        if (board[tarX][tarY].piece->type * type < 0)
                                return 1;
                }
        }
        return 0;
}

/*
 * Purpose:
 * Notes:
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

                printf("---------------\n");
                for (int row=0;row<8;++row){
                        for (int col=0;col<8;++col){
                                printf("%d ",capture_matrix[col][row]);
                        }
                        printf("\n");
                }
                printf("---------------\n");
}

void show_moves_pawn(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
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
                                capture_matrix[tarX][tarY] = 1;
                        }
                }

        } else if (piece.type == W_PAWN) {
                for (int i = 0; i < 4; ++i) {
                        tarX = file + rangeX[i];
                        tarY = rank + W_rangeY[i];

                        if ( tarX >= 0 && tarY >= 0 
                          && tarX <= 7 && tarY <= 7 ) {
                                ColorState[tarX][tarY] = 3;
                                capture_matrix[tarX][tarY] = 1;
                        }
                }

        }                
        
}

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
                                if (board[tarX][tarY].piece->type * type < 0)
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                break;
                        }
                }
        }
}

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
                                if (board[tarX][tarY].piece->type * type < 0)
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                break;
                        }
                }
        }        
}

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

                                if (board[tarX][tarY].piece->type * type < 0)
                                        ColorState[tarX][tarY] = 3;
                                        capture_matrix[tarX][tarY] = 1;
                                break;
                        }
                }
        }
}
void show_moves_king(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece piece)
{
        int tarX, tarY;
        int file = piece.file;
        int rank = piece.rank;
        int type = piece.type;
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
}
