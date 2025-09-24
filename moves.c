#include "utils.h"
#include "moves.h"

void moves_pawn(int **chessboard, int type, int x, int y, Point *available_moves)
{

}

void moves_rook(int **chessboard, int type, int x, int y, Point *available_moves)
{
        int offset = 0;
        int up    = 7 - y;
        int down  = y;
        int left  = x;
        int right = 7 - x;
        int total_moves = up + down + left + right;
        available_moves = (Point *) realloc(available_moves, total_moves * sizeof(Point));

        // Direction: UP
        for (int i = 0; i < up; ++i) {
                available_moves[i + offset].x = x;
                available_moves[i + offset].y = i + y + 1;
        }
        offset += up;
        
        // Direction: DOWN
        for (int i = 0; i < down; ++i) {
                available_moves[i + offset].x = x;
                available_moves[i + offset].y = y - i - 1;
        }
        offset += down;

        // Direction LEFT
        for (int i = 0; i < left; ++i) {
                available_moves[i + offset].x = x - i -1;
                available_moves[i + offset].y = y;
        }
        offset += left;

        // Direction RIGHT
        for (int i = 0; i < right; ++i) {
                available_moves[i + offset].x = x + i + 1;
                available_moves[i + offset].y = y;
        }

        filter_illegal_moves(chessboard, type, total_moves, available_moves);
}

void moves_knight(int type, int x, int y, Point *available_moves)
{

}

void moves_bishop(int type, int x, int y, Point *available_moves)
{

}

void moves_queen(int type, int x, int y, Point *available_moves)
{

}

void moves_king(int type, int x, int y, Point *available_moves)
{

}

// This function removes all occupied cells from
// the available_moves array.
// ( UNFINISHED )
void filter_illegal_moves(int **chessboard, int type, int num_moves, Point *available_moves)
{
        int num_legals = 0;
        if (type > 0) {
                for (int i = 0; i < num_moves; ++i) {
                        if (chessboard[available_moves[i].x][] > 0)
                                num_legals++;
                }
        } else {
                for (int i = 0; i < num_moves; ++i) {
                
                }
        }
}
