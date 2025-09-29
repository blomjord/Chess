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
                printf("Case 2.\n");
                break;
        case  3:
        case -3:
                printf("Case 3.\n");
                break;
        case  4:
        case -4:
                printf("Case 4.\n");
                break;
        case  5:
        case -5:
                printf("Case 5.\n");
                break;
        case  6:
        case -6:
                printf("Case 6.\n");
                break;
        default:
                // Empty
                printf("Empty.\n");
                break;
        }

}

void show_moves_pawn(ChessBoard board[8][8], int ColorState[8][8], ChessPiece piece)
{
        int file = piece.file;
        int rank = piece.rank;
        int rangeX[4]   = { -1, 0, 0, 1   };
        int B_rangeY[4] = { 1, 1, 2, 1    };
        int W_rangeY[4] = { -1, -1, -2, -1 };

        if (piece.type == B_PAWN) {
                for (int i = 0; i < 4; ++i) {
                        if ( file + rangeX[i] >= 0 && rank + B_rangeY[i] >= 0 
                            && file + rangeX[i] <= 7 && rank + B_rangeY[i] <= 7 ) {
                                ColorState[file + rangeX[i]][rank + B_rangeY[i]] = 3;
                        }
                }

        } else if (piece.type == W_PAWN) {
                for (int i = 0; i < 4; ++i) {
                        if ( file + rangeX[i] >= 0 && rank + W_rangeY[i] >= 0 
                            && file + rangeX[i] <= 7 && rank + W_rangeY[i] <= 7 ) {
                                ColorState[file + rangeX[i]][rank + W_rangeY[i]] = 3;
                        }
                }

        }                
        
}

#if 0
void moves_rook(ChessPiece *board[8][8], int type, int x, int y, Point moves[14])
{
        int offset = 0;
        int up    = 7 - y;
        int down  = y;
        int left  = x;
        int right = 7 - x;
        int total_moves = up + down + left + right;

        // Direction: UP
        for (int i = 0; i < up; ++i) {
                moves[i + offset].x = x;
                moves[i + offset].y = i + y + 1;
        }
        offset += up;
        
        // Direction: DOWN
        for (int i = 0; i < down; ++i) {
                moves[i + offset].x = x;
                moves[i + offset].y = y - i - 1;
        }
        offset += down;

        // Direction LEFT
        for (int i = 0; i < left; ++i) {
                moves[i + offset].x = x - i -1;
                moves[i + offset].y = y;
        }
        offset += left;

        // Direction RIGHT
        for (int i = 0; i < right; ++i) {
                moves[i + offset].x = x + i + 1;
                moves[i + offset].y = y;
        }
}
#endif
void moves_knight(ChessPiece board[8][8], ChessPiece piece)
{
        int targetX, targetY;
        int posX = piece.file;
        int posY = piece.rank;
        int rangeX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int rangeY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
        int count = 0;

        for (int i = 0; i < 8; ++i) {
                targetX = posX + rangeX[i];
                targetY = posY + rangeY[i];
                if (is_move_legal(board, posX, posY, targetX, targetY)) {
                        count++;
                }
        }
}

/*
void moves_bishop(int type, int x, int y, Point moves)
{

}

void moves_queen(int type, int x, int y, Point moves)
{

}

void moves_king(int type, int x, int y, Point moves)
{

}*/

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
