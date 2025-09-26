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
void DrawChesspieces(ChessPiece *board[8][8], ChessIconTexture IconTextures[12],
                int square_width, int square_height)
{
        Texture2D Icon;
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if (board[row][col] != NULL) {
                                int x = ( (row+1) * square_width) - (0.7 * square_width);
                                int y = ( (col+1) * square_height) - (0.7 * square_height);
                                // TODO: Textures are NOT valid. Examine this!
                                Icon = InjectIcon(board, IconTextures, row, col); 
                                DrawTexture(Icon, x, y, WHITE);
                                if (IsTextureValid(Icon)){
                                        printf("Texture is valid");     
                                        while(1){}
                                }
                                else 
                                        printf("Texutre NOT valid!\n");
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
        // TODO: Continue from here
        // Add array of Icons to func parameters
        // and inject them and return to function DrawChessPieces
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

void LoadIconsAsTextures(ChessIcon Icons[12], ChessIconTexture IconTextures[12])
{
        for (int i = 0; i < 12; ++i) {
                IconTextures[i].type = Icons[12].type;
                IconTextures[i].texture = LoadTextureFromImage(Icons[i].icon);
        }
}

void UnloadIcons(ChessIcon Icons[12])
{
        for (int i = 0; i < 12; ++i)
                UnloadImage(Icons[i].icon);
}
