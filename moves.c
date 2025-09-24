#include "utils.h"
#include "moves.h"

void moves_pawn(int type, int x, int y, int *available_moves)
{
        if (type == W_PAWN) {
                if (y == 1) { // Starting row white pawns
                        available_moves[0] = 2;
                        available_moves[1] = 3;
                } else
                        available_moves[0] = ++y;
        } else {
                if (y == 7) { // Starting row black pawns
                        available_moves[0] = 6;
                        available_moves[1] = 5;
                } else
                        available_moves[0] = --y;
        }
}

void moves_rook(int type)
{

}

void moves_knight(int type)
{

}

void moves_bishop(int type)
{

}

void moves_queen(int type)
{

}

void moves_king(int type)
{

}
