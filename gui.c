#include "gui.h"

/*
 * Purpose:
 * Notes:
 * */
void DrawChessboard(Rectangle board[8][8], Color color1, Color color2)
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        if ( ((row % 2) == 0 && (col % 2) == 0)
                                || ((row % 2) != 0 && (col % 2) != 0) )
                                DrawRectangleRec(board[row][col], color1);

                        else if ( ((row % 2) == 0 && (col % 2) != 0)
                                        || ((row % 2) != 0 && (col % 2) == 0 ) )
                                DrawRectangleRec(board[row][col], color2);
                }
        } 
}

/*
 * Purpose:
 * Notes:
 * */
void InitChessboard(Rectangle ChessBoard[8][8])
{
        for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                        ChessBoard[row][col].x = row * SQUARE_WIDTH;
                        ChessBoard[row][col].y = col * SQUARE_HEIGHT;
                        ChessBoard[row][col].width   = SQUARE_WIDTH;
                        ChessBoard[row][col].height  = SQUARE_HEIGHT;
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
#if 0
void DrawChesspieces(ChessBoard board[8][8], Vector2 mousePoint)
{
        int textureX, textureY;
        for (int file = 0; file < 8; ++file) {
                for (int rank = 0; rank < 8; ++rank) {
                        
                        if (board[file][rank].piece->type == EMPTY)
                                continue;
                        if (board[file][rank].piece->dragging) {
                                textureX = mousePoint.x - PIXEL_OFFSET;
                                textureY = mousePoint.y - PIXEL_OFFSET;
                                DrawTexture(board[file][rank].piece->texture, textureX, textureY, WHITE);
                        } else if (!board[file][rank].piece->dragging) {
                                textureX = (file * SQUARE_WIDTH)  + PIXEL_OFFSET;
                                textureY = (rank * SQUARE_HEIGHT) + PIXEL_OFFSET;
                                DrawTexture(board[file][rank].piece->texture, textureX, textureY, WHITE);
                        }
                }
        }
}
#endif

void DrawChesspieces(ChessPiece pieces[64], Vector2 mousePoint)
{
        int textureX, textureY;
        for (int i = 0; i < 64; ++i) {
                if (pieces[i].type == EMPTY)
                        continue;
                if (pieces[i].dragging) {
                        textureX = mousePoint.x - PIXEL_OFFSET;
                        textureY = mousePoint.y - PIXEL_OFFSET;
                        DrawTexture(pieces[i].texture, textureX, textureY, WHITE);

                } else {
                        textureX = (pieces[i].file * SQUARE_WIDTH) + PIXEL_OFFSET;
                        textureY = (pieces[i].rank * SQUARE_HEIGHT) + PIXEL_OFFSET;
                        DrawTexture(pieces[i].texture, textureX, textureY, WHITE);
                }
        }
}
void DrawChesspiecePotentialMoves(ChessPiece pieces[64])
{
        for (int i = 0; i < 64; ++i) {
                if (pieces[i].type == EMPTY)
                        continue;
        }
}

/*
 * Purpose: Loads all icons into RAM
 * Notes:
 * */
void LoadIcons(Image Icons[13])
{
        Icons[0]  = LoadImage("Images/B_King.png")   ;
        Icons[1]  = LoadImage("Images/B_Queen.png")  ;
        Icons[2]  = LoadImage("Images/B_Rook.png")   ;
        Icons[3]  = LoadImage("Images/B_Bishop.png") ;
        Icons[4]  = LoadImage("Images/B_Knight.png") ;
        Icons[5]  = LoadImage("Images/B_Pawn.png")   ;
        Icons[6]  = LoadImage("Images/W_King.png")   ;
        Icons[7]  = LoadImage("Images/W_Queen.png")  ;
        Icons[8]  = LoadImage("Images/W_Rook.png")   ;
        Icons[9]  = LoadImage("Images/W_Bishop.png") ;
        Icons[10] = LoadImage("Images/W_Knight.png") ;
        Icons[11] = LoadImage("Images/W_Pawn.png")   ;
        Icons[12] = LoadImage("Images/W_Pawn.png")   ;

}

/*
 * Purpose: Loads the images into texture to be drawn
 * Notes:
 * */
void LoadIconsAsTextures(Image Icons[13], Texture2D IconTextures[13])
{
        for (int i = 0; i < 13; ++i) {
                printf("Trying to load Icon %d\n", i);
                IconTextures[i] = LoadTextureFromImage(Icons[i]); 
        }
}

/*
 * Purpose: Unload icons from RAM, 
 * 
 * Notes: Useonly after they have
 * been converted into type Texture2D.
 */
void UnloadIcons(Image Icons[13])
{
        for (int i = 0; i < 13; ++i)
                UnloadImage(Icons[i]);
}
