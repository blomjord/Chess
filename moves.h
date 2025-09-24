#ifndef MOVES_H
#define MOVES_H

#include "utils.h"

void moves_pawn  (int type, int x, int y, Point *available_moves);
void moves_rook  (int type, int x, int y, Point *available_moves);
void moves_knight(int type, int x, int y, Point *available_moves);
void moves_bishop(int type, int x, int y, Point *available_moves);
void moves_queen (int type, int x, int y, Point *available_moves);
void moves_king  (int type, int x, int y, Point *available_moves);

#endif
