#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "raylib.h"
#include "types.h"

void DrawChessboard(Rectangle ChessBoard[8][8], Color color1, Color color2);
void DrawMouseHoverAction(Rectangle ChessBoard[8][8], int ColorState[8][8]);
void DrawChesspieces(ChessPiece pieces[64], Vector2 mousePoint);
void DrawChesspieceLegalMoves(int ColorState[8][8]);
void DrawCapturedChesspieces(Rectangle rect, ChessPiece captured[30]);
void DetectActionMouseHover(Vector2 mousePoint, Rectangle Background[8][8], int ColorState[8][8]);
void DrawWinner(Rectangle Rect, int b, int w);
void LoadIcons(Image Icons[13]);
void LoadIconsAsTextures(Image Icons[13], Texture2D IconTextures[13]);
void UnloadIcons(Image Icons[13]);
void UnloadTextures(Texture2D tex[13]);
void InitChessboard(Rectangle ChessBoard[8][8]);

int DetectRestartButtonClicked(Rectangle btn);
int DetectQuitButtonClicked(Rectangle btn);
#endif
