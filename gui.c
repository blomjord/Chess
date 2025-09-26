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
void DrawChesspieces(ChessPiece *board[8][8], ChessIcon Icons[12],
                int square_width, int square_height)
{
        Texture2D Icon;

        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (board[row][col] != NULL) {
                                int x = ( (row+1) * square_width) - (0.7 * square_width);
                                int y = ( (col+1) * square_height) - (0.7 * square_height);
                                //TODO: Change name of variable: tmp_name
                                Image tmp_name = InjectIcon(board, Icons, row, col); 
                                Texture2D Icon = LoadTextureFromImage(tmp_name);
                                DrawTexture(Icon, x, y, WHITE);
                        }
                }
        }
}

/*
 * Purpose: Selects correct chess icon to display
 * Notes:
 * */
Image InjectIcon(ChessPiece *board[8][8], ChessIcon Icons[12], int row, int col)
{
        // TODO: Continue from here
        // Add array of Icons to func parameters
        // and inject them and return to function DrawChessPieces
        Image IconToDisplay;
        if (board[row][col] != NULL) {
                int type = board[row][col]->type;
                for (int i = 0; i < 12; ++i) {
                        if (type == Icons[i].type)
                                IconToDisplay = Icons[i].Icon;
                }
        } 
        return IconToDisplay;
}

/*
 * Purpose: Loads all icons into RAM
 * Notes:
 * */
void LoadIcons(ChessIcon Icons[12])
{
        ChessIcon tmp[12] = {
                { B_KING,   LoadImage("Images/B_King.png") },
                { B_QUEEN,  LoadImage("Images/B_Queen.png") },
                { B_ROOK,   LoadImage("Images/B_Rook.png") },
                { B_BISHOP, LoadImage("Images/B_Bishop.png") },
                { B_KNIGHT, LoadImage("Images/B_Knight.png") },
                { B_PAWN,   LoadImage("Images/B_Pawn.png") },
                { W_KING,   LoadImage("Images/W_King.png") },
                { W_QUEEN,  LoadImage("Images/W_Queen.png") },
                { W_ROOK,   LoadImage("Images/W_Rook.png") },
                { W_BISHOP, LoadImage("Images/W_Bishop.png") },
                { W_KNIGHT, LoadImage("Images/W_Knight.png") },
                { W_PAWN,   LoadImage("Images/W_Pawn.png") }
        };
        for (int i = 0; i < 12; ++i)
                Icons[i] = tmp[i];
}

void UnloadIcons(ChessIcon Icons[12])
{
        for (int i = 0; i < 12; ++i)
                UnloadImage(Icons[i].Icon);
}
