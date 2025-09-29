#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "raylib.h"
#include "types.h"


void DrawChessboard(Rectangle ChessBoard[8][8], Color color1, Color color2);
//void DrawChesspieces(BoardCell board[8][8], Rectangle RenderChessboard[8][8],
//                Rectangle tmp_name_RECTANGLE,
//                ChessIconTexture IconTextures[12], Vector2 mousePoint);
void DrawMouseHoverAction(Rectangle ChessBoard[8][8], int ColorState[8][8]);

void DrawChesspieces(ChessPiece pieces[64], Vector2 mousePoint);
void DrawChesspieceLegalMoves(int ColorState[8][8]);
void LoadIcons(Image Icons[13]);
void LoadIconsAsTextures(Image Icons[13], Texture2D IconTextures[13]);
void UnloadIcons(Image Icons[13]);
void InitChessboard(Rectangle ChessBoard[8][8]);
#endif
