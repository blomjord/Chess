#include "gui.h"

/*
 * Purpose:
 * Notes:
 * */
void DrawChessboard(Rectangle ChessBoard[8][8], Color color1, Color color2)
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if ( ((row % 2) == 0 && (col % 2) == 0)
                                || ((row % 2) != 0 && (col % 2) != 0) )
                                DrawRectangleRec(ChessBoard[row][col], color1);

                        else if ( ((row % 2) == 0 && (col % 2) != 0)
                                        || ((row % 2) != 0 && (col % 2) == 0 ) )
                                DrawRectangleRec(ChessBoard[row][col], color2);
                }
        } 
}

/*
 * Purpose:
 * Notes:
 * */
void InitChessboard(Rectangle ChessBoard[8][8], int square_width, int square_height)
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        ChessBoard[row][col].x = row * square_width;;
                        ChessBoard[row][col].y = col * square_height;
                        ChessBoard[row][col].width  = square_width;
                        ChessBoard[row][col].height = square_height;
                }
        }
}

/*
 * Purpose:
 * Notes:
 * */
void DrawMouseHoverAction(Rectangle ChessBoard[8][8], int ColorState[8][8])
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (ColorState[row][col] == 1)
                                DrawRectangleLinesEx(ChessBoard[row][col], 4.0f, BLUE);
                        else if (ColorState[row][col] == 2)
                                DrawRectangleRec(ChessBoard[row][col],  BLUE);
                }
        }
}

/*
 * Purpose:
 * Notes:
 * */
void DrawChesspieces(ChessPiece *board[8][8], ChessIconTexture IconTextures[12],
                int square_width, int square_height)
{
        Texture2D Icon;
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (board[row][col] != NULL) {
                                int x = (row * square_width) + (55 / 2);
                                int y = (col * square_height) + (55 / 2);
                                // TODO: Textures are NOT valid. Examine this!
                                Icon = InjectIcon(board, IconTextures, row, col);
                                DrawTexture(Icon, x, y, WHITE);
                        }
                }
        }
}

/*
 * Purpose: Selects correct chess icon to display
 * Notes:
 * */
Texture2D InjectIcon(ChessPiece *board[8][8],
                ChessIconTexture IconTextures[12], int row, int col)
{
        Texture2D IconToDisplay;
        if (board[row][col] != NULL) {
                int type = board[row][col]->type;
                for (int i = 0; i < 12; ++i) {
                        if (type == IconTextures[i].type)
                                IconToDisplay = IconTextures[i].texture;
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
        ChessIcon Images[12] = {
                { B_KING,   LoadImage("Images/B_King.png")   },
                { B_QUEEN,  LoadImage("Images/B_Queen.png")  },
                { B_ROOK,   LoadImage("Images/B_Rook.png")   },
                { B_BISHOP, LoadImage("Images/B_Bishop.png") },
                { B_KNIGHT, LoadImage("Images/B_Knight.png") },
                { B_PAWN,   LoadImage("Images/B_Pawn.png")   },
                { W_KING,   LoadImage("Images/W_King.png")   },
                { W_QUEEN,  LoadImage("Images/W_Queen.png")  },
                { W_ROOK,   LoadImage("Images/W_Rook.png")   },
                { W_BISHOP, LoadImage("Images/W_Bishop.png") },
                { W_KNIGHT, LoadImage("Images/W_Knight.png") },
                { W_PAWN,   LoadImage("Images/W_Pawn.png")   }
        };
        for (int i = 0; i < 12; ++i) {
                Icons[i] = Images[i];
        }
}

/*
 * Purpose: Loads the images into texture to be drawn
 * Notes:
 * */
void LoadIconsAsTextures(ChessIcon Icons[12], ChessIconTexture IconTextures[12])
{
        for (int i = 0; i < 12; ++i) {
                IconTextures[i].type = Icons[i].type;
                IconTextures[i].texture = LoadTextureFromImage(Icons[i].icon);
        }
}

/*
 * Purpose: Unload images from RAM
 * Notes:
 */
void UnloadIcons(ChessIcon Icons[12])
{
        for (int i = 0; i < 12; ++i)
                UnloadImage(Icons[i].icon);
}
