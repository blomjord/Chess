#include "utils.h"
#include "moves.h"

int num_moves_within_board(int count, int pos_X, int pos_Y, int moves_X[], int moves_Y[]);

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
Point *moves_knight(ChessPiece *board[8][8], ChessPiece *piece, int *num_moves)
{
        int pos_X = piece->x;
        int pos_Y = piece->y;
        int moves_X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int moves_Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
        int count = num_moves_within_board(8, pos_X, pos_Y, moves_X, moves_Y);
        
        *num_moves = count;
        Point *moves = malloc(count * sizeof(Point));

        int moves_idx = 0;
        for (int i = 0; i < 8; ++i) {
                int tar_X = pos_X + moves_X[i];
                int tar_Y = pos_Y + moves_Y[i];
                if (tar_X >= 0 && tar_Y >= 0 && tar_X <= 7 && tar_Y <= 7) {
                        if ( (piece->type) * ( board[tar_X][tar_Y]->type ) < 0
                                        || board[tar_X][tar_Y] == NULL) {
                                moves[i].x = tar_X;
                                moves[i].y = tar_Y;
                                moves_idx++;
                        }
                }
        }
#if 0
        int new_count = 0;
        if (piece->type == W_KNIGHT) {
                // Moves for white
                for (int i = 0; i < moves_idx; ++i) {
                        printf("board[%d][%d]\n", moves[i].x, moves[i].y);
                        if (&board[moves[i].x][moves[i].y]->type > 0) {
                                printf("Same color. Illegal move!\n");
                        } else {
                                new_count++;      
                        }
                }
                printf("New num moves: %d\n", new_count);
        } else {
                // Moves for black
        }
#endif
        for (int i = 0; i < moves_idx; ++i) {
                printf("(%d,%d)\n", moves[i].x, moves[i].y);
        }
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

}*/
void show_legal_moves(BoardCell board[8][8], int x, int y)
{

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
