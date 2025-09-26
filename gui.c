#include "gui.h"

void DrawChessboard(int square_width, int square_height, Color color)
{
        ClearBackground(BEIGE);
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if ( (row % 2) == 0 && (col % 2) == 0 ) {
                                DrawRectangle(row * square_width,
                                                col * square_height,
                                                square_width,
                                                square_height,
                                                color);
                        } else if ( (row % 2) != 0 && (col % 2) != 0 ) {
                                DrawRectangle(row * square_width,
                                                col * square_height,
                                                square_width,
                                                square_height,
                                                color);
                        }
                }
        }
}

void DrawChesspieces(ChessPiece *board)
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (board[row][col] != NULL) {
                                DrawText("A");
                        }
                }
        }
}
