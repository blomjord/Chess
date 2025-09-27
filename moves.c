#include "utils.h"
#include "moves.h"
#include "gui.h"

int num_moves_within_board(int count, int pos_X, int pos_Y, int moves_X[], int moves_Y[]);

#if 0
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
