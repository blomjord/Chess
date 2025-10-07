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
                        ChessBoard[row][col].x = row * SQUARE_SIZE;
                        ChessBoard[row][col].y = col * SQUARE_SIZE;
                        ChessBoard[row][col].width   = SQUARE_SIZE;
                        ChessBoard[row][col].height  = SQUARE_SIZE;
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
void DrawChesspieces(ChessPiece pieces[64], Vector2 mousePoint)
{
        int textureX, textureY;
        for (int i = 63; i > -1; --i) {
//        for (int i = 0; i < 64; ++i) {
                if (pieces[i].type == EMPTY)
                        continue;

                if (!pieces[i].holding) {
                        textureX = (pieces[i].file * SQUARE_SIZE) + PIXEL_OFFSET;
                        textureY = (pieces[i].rank * SQUARE_SIZE) + PIXEL_OFFSET;
                        DrawTexture(pieces[i].texture, textureX, textureY, WHITE);

                } else {
                        textureX = mousePoint.x - PIXEL_OFFSET;
                        textureY = mousePoint.y - PIXEL_OFFSET;
                        DrawTexture(pieces[i].texture, textureX, textureY, WHITE);
                }
        }
}

/*
 * Purpose:
 * Notes:
 * */
void DetectActionMouseHover(Vector2 mousePoint, Rectangle Background[8][8], int ColorState[8][8])
{
        for (int file = 0; file < 8; ++file) {
                for (int rank = 0; rank < 8; ++rank) {
                        if (CheckCollisionPointRec(mousePoint, Background[file][rank])
                        && IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) {
                                ColorState[file][rank] = 2;
                        } else if (CheckCollisionPointRec(mousePoint, Background[file][rank])) {
                                ColorState[file][rank] = 1;
                        } else {
                                ColorState[file][rank] = 0;
                        }
                }
        }
}

void DrawChesspieceLegalMoves(int ColorState[8][8])
{
        for (int file = 0; file < 8; ++file) {
                for (int rank = 0; rank < 8; ++rank) {
                        if (ColorState[file][rank] == 3) {
                                DrawCircle((file * SQUARE_SIZE) + 50,
                                           (rank * SQUARE_SIZE) + 50,
                                            20.0f, BLUE);
                        }
                }
        }
}

/*
 * Purpose
 * Notes:
 * */
void DrawCapturedChesspieces(Rectangle rect, ChessPiece captured[30])
{
        int B_textureX = 810;
        int B_textureY = 410;
        
        int W_textureY =  10;
        int W_textureX = 810;
        
        DrawRectangleLinesEx(rect, 5.0f, GOLD);
        for (int i = 0; i < 30; ++i) {
                if (captured[i].type == EMPTY)
                        break;

                if (captured[i].color == 0) { // BLACK
                        if (B_textureY > 750) {
                                B_textureX +=  45;
                                B_textureY  = 410;
                        }
                        DrawTexture(captured[i].texture, B_textureX, B_textureY, WHITE); 
                        B_textureY += 45;
                }
                if (captured[i].color == 1) { // WHITE
                        if (W_textureY > 360) {
                                W_textureX += 45;
                                W_textureY =  10;
                        }
                        DrawTexture(captured[i].texture, W_textureX, W_textureY, WHITE); 
                        W_textureY += 45;
                }
        }
}

void DrawWinner(Rectangle Rect, int b, int w)
{
        if (b) {
                DrawRectangleRec(Rect, LIGHTBEIGE);
                DrawRectangleLinesEx(Rect, 12.0f, GOLD);
                DrawText("Black has won!", 170.0f, 285.0f, 64.0f, BLACK);
        }
        if (w) {
                DrawRectangleRec(Rect, LIGHTBEIGE);
                DrawRectangleLinesEx(Rect, 12.0f, GOLD);
                DrawText("White has won!", 170.0f, 285.0f, 64.0f, BLACK);
        }
}

int RestartButtonClicked(Rectangle btn)
{
        DrawRectangleRec(btn, LIGHTBEIGE);
        DrawRectangleLinesEx(btn, 4.0f, GOLD);
        DrawText("Restart", 230.0f, 370.f, 36.0f, BLACK);
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return 1;
        return 0;
}

int QuitButtonClicked(Rectangle btn)
{
        DrawRectangleRec(btn, LIGHTBEIGE);
        DrawRectangleLinesEx(btn, 4.0f, GOLD);
        DrawText("Quit", 470.0f, 370.f, 36.0f, BLACK);
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return 1;
        return 0;
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

void UnloadTextures(Texture2D tex[13])
{
        for (int i = 0; i < 13; ++i)
                UnloadTexture(tex[i]);
}
