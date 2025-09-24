#include "utils.h"
#include "moves.h"

void moves_pawn(int type, int x, int y, Point *available_moves)
{

}

void moves_rook(int type, int x, int y, Point *available_moves)
{
        int offset = 0;
        int up    = 8 - x;
        int down  = x - 1;
        int left  = x - 1;
        int right = 8 - x;
        int total_moves = up + down + left + right;
        available_moves = (Point *) realloc(available_moves, total_moves * sizeof(Point));
        if (type == W_ROOK) {
                for (int i = 0; i < up; ++i) {
                        available_moves[i + offset].x = x;
                        available_moves[i + offset].y = i + y;
                }

                offset += up;
                
                for (int i = 0; i < down; ++i) {
                        available_moves[i + offset].x = x;
                        available_moves[i + offset].y = i - y;
                }

                offset += down;

                for (int i = 0; i < left; ++i) {
                        available_moves[i + offset].x = x - i;
                        available_moves[i + offset].y = y;
                }

                offset += down;

                for (int i = 0; i < right; ++i) {
                        available_moves[i + offset].x = x + i;
                        available_moves[i + offset].y = y;
                }
                
                offset += left;

        } else {
                // else type == B_ROOK
        }
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
void f()
{

}
