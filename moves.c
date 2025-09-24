#include "utils.h"
#include "moves.h"

void moves_pawn(int type, int x, int y, Point *available_moves)
{

}

void moves_rook(int type, int x, int y, Point *available_moves)
{
        printf("X: %d Y: %d\n", x, y);
        int offset = 0;
        int up    = 7 - y;
        int down  = y;
        int left  = x;
        int right = 7 - x;
        printf("up: %d\ndown: %d\nleft: %d\nright: %d\n", up, down, left, right);
        int total_moves = up + down + left + right;
        available_moves = (Point *) realloc(available_moves, total_moves * sizeof(Point));
        if (type == W_ROOK) {

                // Direction: UP
                for (int i = 0; i < up; ++i) {
                        available_moves[i + offset].x = x;
                        available_moves[i + offset].y = i + y;
                }

                offset += up;
                
                // Direction: DOWN
                for (int i = 0; i < down; ++i) {
                        available_moves[i + offset].x = x;
                        available_moves[i + offset].y = i - y;
                }

                offset += down;

                // Direction LEFT
                for (int i = 0; i < left; ++i) {
                        available_moves[i + offset].x = x - i;
                        available_moves[i + offset].y = y;
                }

                offset += down;

                // Direction RIGHT
                for (int i = 0; i < right; ++i) {
                        available_moves[i + offset].x = x + i;
                        available_moves[i + offset].y = y;
                }
                
                offset += left;

        } else {
                // else type == B_ROOK
        }
        for (int i = 0; i < total_moves; ++i)
                printf("(%d,%d)\n", available_moves[i].x, available_moves[i].y);

        f(total_moves, available_moves);
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
void f(int num_moves, Point *available_moves)
{

}
