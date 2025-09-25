#include "utils.h"
#include "moves.h"

Point *moves_pawn(ChessPiece *board[8][8], ChessPiece *piece, int *num_moves)
{
        int pos_X = piece->x;
        int pos_Y = piece->y;
        int moves_X[4] = { 1, 0, 0, -1};
        int moves_Y[4] = { 1, 2, 1, 1 };
        int count = 0;
        
        if (piece->type < 0)
                for (int i = 0; i < 4; ++i)
                        moves_Y[i] *= -1;

        for (int i = 0; i < 4; ++i) {
                int tar_X = pos_X + moves_X[i];
                int tar_Y = pos_Y + moves_Y[i];
                if (tar_X >= 0 && tar_Y >= 0 && tar_X <= 7 && tar_Y <= 7)
                        count++;
        }

        Point *moves = malloc(count * sizeof(Point));
        *num_moves = count;
        printf("Pawn nMoves: %d\n", count);
        return moves;
}
/*
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
*/
Point *moves_knight(ChessPiece *board[8][8], ChessPiece *piece, int *num_moves)
{
        int pos_X = piece->x;
        int pos_Y = piece->y;
        int moves_X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int moves_Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
        int count = 0;

        for (int i = 0; i < 8; ++i) {
                int tar_X = pos_X + moves_X[i];
                int tar_Y = pos_Y + moves_Y[i];

                if (tar_X >= 0 && tar_Y >= 0 && tar_X <= 7 && tar_Y <= 7)
                        count++;
        }
        printf("Knight nMoves: %d\n", count);
        Point *moves = malloc(count * sizeof(Point));
        *num_moves = count;
        return moves;
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

}

// This function removes all occupied cells from
// the available_moves array.
// ( UNFINISHED )
void filter_illegal_moves(ChessPiece *board[8][8], int type, int num_moves, Point *moves)
{
        int num_legals = 0;
        if (type > 0) {
                for (int i = 0; i < num_moves; ++i) {
                }
        } else {
                for (int i = 0; i < num_moves; ++i) {
                
                }
        }
}*/
