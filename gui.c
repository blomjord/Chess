#include "gui.h"

/*
 * Purpose:
 * Notes:
 * */
void DrawChessboard(int square_width, int square_height, Color color)
{
        Color brown = { 196, 133, 94, 255 };
        ClearBackground(brown);
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

/*
 * Purpose:
 * Notes:
 * */
void DrawChesspieces(ChessPiece *board[8][8], Image Icons[12], int square_width, int square_height)
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (board[row][col] != NULL) {
                                int IconPosX = ( (row+1) * square_width) - (0.5 * square_width);
                                int IconPosY = ( (col+1) * square_height) - (0.5 * square_height);
                                // Func: Select icon for board[col][row]
                                Texture2D Icon = LoadTextureFromImage();
                        }
                }
        }
}

/*
 * Purpose: Selects correct chess icon to display
 * Notes:
 * */
Texture2D select_icon(ChessPiece board[8][8], int posX, int posY)
{
        // TODO: Continue from here
        // Add array of Icons to func parameters
        // and inject them and return to function DrawChessPieces
        Texture2D IconToDisplay;
        
        return IconToDisplay;
}

/*
 * Purpose: Loads all icons into RAM
 * Notes:
 * */
void LoadIcons(Image Icons[12])
{
        Image tmp[12] = {
                LoadImage("Images/B_King"),
                LoadImage("Images/B_Queen"),
                LoadImage("Images/B_Rook.png"),
                LoadImage("Images/B_Bishop.png"),
                LoadImage("Images/B_Knight.png"),
                LoadImage("Images/B_Pawn.png"),
                LoadImage("Images/W_King"),
                LoadImage("Images/W_Queen"),
                LoadImage("Images/W_Rook.png"),
                LoadImage("Images/W_Bishop.png"),
                LoadImage("Images/W_Knight.png"),
                LoadImage("Images/W_Pawn.png")
        };
        for (int i = 0; i < 12; ++i)
                Icons[i] = tmp[i]; 
}
