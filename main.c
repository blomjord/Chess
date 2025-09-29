#include "utils.h"
#include "moves.h"
#include "gui.h"
#include "types.h"

Vector2 square_coords(int file, int rank)
{
        Vector2 pos;
        pos.x = file * SQUARE_WIDTH + 50;
        pos.y = rank * SQUARE_HEIGHT + 50;
        return pos;
}

/*
 * Purpose: God-awful init func..
 * Notes:
 * */
void initialize_pieces(ChessPiece pieces[64], Texture2D IconTextures[13]) 
{
        pieces[0]  = (ChessPiece) { B_ROOK,   0, 0, 0, 0, IconTextures[2],  square_coords(0, 0) };
        pieces[1]  = (ChessPiece) { B_ROOK,   7, 0, 0, 0, IconTextures[2],  square_coords(7, 0) };
        pieces[2]  = (ChessPiece) { B_KNIGHT, 1, 0, 0, 0, IconTextures[4],  square_coords(1, 0) };
        pieces[3]  = (ChessPiece) { B_KNIGHT, 6, 0, 0, 0, IconTextures[4],  square_coords(6, 0) };
        pieces[4]  = (ChessPiece) { B_BISHOP, 2, 0, 0, 0, IconTextures[3],  square_coords(2, 0) };
        pieces[5]  = (ChessPiece) { B_BISHOP, 5, 0, 0, 0, IconTextures[3],  square_coords(5, 0) };
        pieces[6]  = (ChessPiece) { B_QUEEN,  3, 0, 0, 0, IconTextures[1],  square_coords(3, 0) };
        pieces[7]  = (ChessPiece) { B_KING,   4, 0, 0, 0, IconTextures[0],  square_coords(4, 0) };
        pieces[8]  = (ChessPiece) { W_ROOK,   0, 7, 0, 0, IconTextures[8],  square_coords(0, 7) },
        pieces[9]  = (ChessPiece) { W_ROOK,   7, 7, 0, 0, IconTextures[8],  square_coords(7, 7) },
        pieces[10] = (ChessPiece) { W_KNIGHT, 1, 7, 0, 0, IconTextures[10], square_coords(1, 7) },
        pieces[11] = (ChessPiece) { W_KNIGHT, 6, 7, 0, 0, IconTextures[10], square_coords(6, 7) },
        pieces[12] = (ChessPiece) { W_BISHOP, 2, 7, 0, 0, IconTextures[9],  square_coords(2, 7) },
        pieces[13] = (ChessPiece) { W_BISHOP, 5, 7, 0, 0, IconTextures[9],  square_coords(5, 7) },
        pieces[14] = (ChessPiece) { W_QUEEN,  3, 7, 0, 0, IconTextures[7],  square_coords(3, 7) },
        pieces[15] = (ChessPiece) { W_KING,   4, 7, 0, 0, IconTextures[6],  square_coords(4, 7) };

        // Init of pawns and empty cells
        int index = 16;
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { B_PAWN, file, 1, 0, 0, IconTextures[5], square_coords(file, 1) };
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { W_PAWN, file, 6, 0, 0, IconTextures[11], square_coords(file, 6) };
        for (int file = 0; file < 8; ++file) {
                for (int rank = 2; rank < 6; ++rank)
                        pieces[index++] = (ChessPiece) { EMPTY, file, rank, 0, 0, IconTextures[12], square_coords(file, rank) };
        }
}

/*
 *  Returns a pointer to chosen chess piece, or NULL
 * */
ChessPiece *get_piece_by_coords(ChessPiece pieces[64], int x, int y)
{
        for (int i = 0; i < 64; ++i)
                if (pieces[i].file == x && pieces[i].rank == y)
                        return &pieces[i];
        fprintf(stderr, "ERROR: No piece found at (%d, %d)\n", x, y);
        exit(1);
}

/*
 * Purpose:
 * Notes:
 * */
void initialize_board(ChessBoard board[8][8], ChessPiece pieces[64])
{
        ChessPiece *piece;
        for (int file = 0; file < 8; ++file) {
                for (int rank = 0; rank < 8; ++rank) {
                        piece = get_piece_by_coords(pieces, file, rank);
                        if (piece != NULL) {
                                board[file][rank].file = file;
                                board[file][rank].rank = rank;
                                board[file][rank].piece = piece;
                        }
                } 
        }
}

int main(void)
{
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
        SetTargetFPS(60);
        SetExitKey(KEY_Q);
        
        ChessPiece pieces[64];
        ChessBoard board[8][8];
        Rectangle Background[8][8];
        
        Image Icons[13];
        Texture2D IconTextures[13];
        LoadIcons(Icons);
        LoadIconsAsTextures(Icons, IconTextures);
        UnloadIcons(Icons);

        initialize_pieces(pieces, IconTextures);
        initialize_board(board, pieces);

        Vector2 mousePoint = { 0.0f, 0.0f };
        Vector2 touchPoint = { 0.0f, 0.0f };
        Rectangle touchArea = { 0.0f, 0.0f, 25.0f, 25.0f };
        Rectangle pieceArea = { 0.0f, 0.0f, 80.0f, 80.0f };
        
        int ColorState[8][8];
        InitChessboard(Background);
        
        while (!WindowShouldClose()) {
                // Events
                mousePoint = GetMousePosition();
                touchArea.x = mousePoint.x;
                touchArea.y = mousePoint.y;

                // void DetectActionMouseHover
                for (int file = 0; file < 8; ++file) {
                        for (int rank = 0; rank < 8; ++rank) {
                                if (CheckCollisionPointRec(mousePoint, Background[file][rank])
                                                && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                                        ColorState[file][rank] = 2;
                                        
                                } else if (CheckCollisionPointRec(mousePoint, Background[file][rank])) {
                                        ColorState[file][rank] = 1;
                                } else {
                                        ColorState[file][rank] = 0;
                                }
                        }
                }
                // void DetectActionMouseDragAndHold()
                for (int i = 0; i < 64; ++i) {
                        if (pieces[i].type == EMPTY)
                                continue;

                        pieceArea.x = pieces[i].pos.x;
                        pieceArea.y = pieces[i].pos.y;
                        if ( CheckCollisionRecs(touchArea, pieceArea) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) {
                                pieces[i].dragging = 1;
                                pieces[i].pos.x = mousePoint.x;
                                pieces[i].pos.y = mousePoint.y;
                        } else {
                                pieces[i].dragging = 0;
                                pieces[i].pos.x = (pieces[i].file * SQUARE_WIDTH) + PIXEL_OFFSET;
                                pieces[i].pos.y = (pieces[i].rank * SQUARE_HEIGHT) + PIXEL_OFFSET;
                        }
                }
                // void detect_action_mouse_release();
                // void DetectActionMouseRelease();

                // Game state update

                // Graphics drawing
                BeginDrawing();
                DrawChessboard(Background, LIGHTBEIGE, LIGHTBROWN);
                DrawMouseHoverAction(Background, ColorState);
                DrawChesspiecePotentialMoves(pieces);
                DrawChesspieces(pieces, mousePoint);
                EndDrawing();
        }
        CloseWindow();
        return 0;
}
