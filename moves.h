#ifndef MOVES_H
#define MOVES_H

void moves_pawn(int type, int x, int y, int *available_moves);
void moves_rook(int type);
void moves_knight(int type);
void moves_bishop(int type);
void moves_queen(int type);
void moves_king(int type);

#endif
