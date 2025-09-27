#include "utils.h"
#include "moves.h"
#include "gui.h"
#include "types.h"

Vector2 square_coords(int file, int rank)
{
        Vector2 pos;
        pos.x = file * SQUARE_WIDTH;
        pos.y = rank * SQUARE_HEIGHT;
        return pos;
}

/*
 * Purpose: God-awful init func..
 * Notes:
 * */
void initialize_pieces(ChessPiece pieces[32], ChessIcon Icons[12]) 
{
        // TODO: Fix Texture init.
        pieces[0]  = (ChessPiece) { B_ROOK,   0, 0, 0, 0};//, LoadTextureFromImage(Icons[2].icon), square_coords(0, 0) };
        pieces[1]  = (ChessPiece) { B_ROOK,   7, 0, 0, 0};//, LoadTextureFromImage(Icons[2].icon), square_coords(7, 0) };
        pieces[2]  = (ChessPiece) { B_KNIGHT, 1, 0, 0, 0};//, LoadTextureFromImage(Icons[4].icon), square_coords(1, 0) };
        pieces[3]  = (ChessPiece) { B_KNIGHT, 6, 0, 0, 0};//, LoadTextureFromImage(Icons[4].icon), square_coords(6, 0) };
        pieces[4]  = (ChessPiece) { B_BISHOP, 2, 0, 0, 0};//, LoadTextureFromImage(Icons[3].icon), square_coords(2, 0) };
        pieces[5]  = (ChessPiece) { B_BISHOP, 5, 0, 0, 0};//, LoadTextureFromImage(Icons[3].icon), square_coords(5, 0) };
        pieces[6]  = (ChessPiece) { B_QUEEN,  3, 0, 0, 0};//, LoadTextureFromImage(Icons[1].icon), square_coords(3, 0) };
        pieces[7]  = (ChessPiece) { B_KING,   4, 0, 0, 0};//, LoadTextureFromImage(Icons[0].icon), square_coords(4, 0) };
        pieces[8]  = (ChessPiece) { B_PAWN,   0, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(0, 1) };
        pieces[9]  = (ChessPiece) { B_PAWN,   1, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(1, 1) };
        pieces[10] = (ChessPiece) { B_PAWN,   2, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(2, 1) };
        pieces[11] = (ChessPiece) { B_PAWN,   3, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(3, 1) };
        pieces[12] = (ChessPiece) { B_PAWN,   4, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(4, 1) };
        pieces[13] = (ChessPiece) { B_PAWN,   5, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(5, 1) };
        pieces[14] = (ChessPiece) { B_PAWN,   6, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(6, 1) };
        pieces[15] = (ChessPiece) { B_PAWN,   7, 1, 0, 0};//, LoadTextureFromImage(Icons[5].icon), square_coords(7, 1) };

        pieces[16] = (ChessPiece) { W_ROOK,   0, 7, 0, 0};//, LoadTextureFromImage(Icons[8].icon), square_coords(0, 7) };
        pieces[17] = (ChessPiece) { W_ROOK,   7, 7, 0, 0};//, LoadTextureFromImage(Icons[8].icon), square_coords(7, 7) };
        pieces[18] = (ChessPiece) { W_KNIGHT, 1, 7, 0, 0};//, LoadTextureFromImage(Icons[10].icon), square_coords(1, 7) };
        pieces[19] = (ChessPiece) { W_KNIGHT, 6, 7, 0, 0};//, LoadTextureFromImage(Icons[10].icon), square_coords(6, 7) };
        pieces[20] = (ChessPiece) { W_BISHOP, 2, 7, 0, 0};//, LoadTextureFromImage(Icons[9].icon), square_coords(2, 7) };
        pieces[21] = (ChessPiece) { W_BISHOP, 5, 7, 0, 0};//, LoadTextureFromImage(Icons[9].icon), square_coords(5, 7) };
        pieces[22] = (ChessPiece) { W_QUEEN,  3, 7, 0, 0};//, LoadTextureFromImage(Icons[7].icon), square_coords(3, 7) };
        pieces[23] = (ChessPiece) { W_KING,   4, 7, 0, 0};//, LoadTextureFromImage(Icons[6].icon), square_coords(4, 7) };
        pieces[24] = (ChessPiece) { W_PAWN,   0, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(0, 6) };
        pieces[25] = (ChessPiece) { W_PAWN,   1, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(1, 6) };
        pieces[26] = (ChessPiece) { W_PAWN,   2, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(2, 6) };
        pieces[27] = (ChessPiece) { W_PAWN,   3, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(3, 6) };
        pieces[28] = (ChessPiece) { W_PAWN,   4, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(4, 6) };
        pieces[29] = (ChessPiece) { W_PAWN,   5, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(5, 6) };
        pieces[30] = (ChessPiece) { W_PAWN,   6, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(6, 6) };
        pieces[31] = (ChessPiece) { W_PAWN,   7, 6, 0, 0};//, LoadTextureFromImage(Icons[11].icon), square_coords(7, 6) };
}

/*
 *  Returns a pointer to chosen chess piece, or NULL
 * */
ChessPiece *get_piece_by_coords(ChessPiece pieces[32], int x, int y)
{
        for (int i = 0; i < 32; ++i)
                if (pieces[i].file == x && pieces[i].rank == y)
                        return &pieces[i];
        return NULL;
}

void initialize_board(ChessPiece board[8][8], ChessPiece pieces[32])
{
        ChessPiece *piece;
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 2; ++j) {
                        piece = get_piece_by_coords(pieces, i, j);
                        if (i == piece->file && j == piece->rank) {
                                board[i][j] = *piece;
                        }
                } 
                for (int j = 2; j < 6; ++j) {
                        board[i][j].type = EMPTY;
                }

                for (int j = 6; j < 8; ++j) {
                        piece = get_piece_by_coords(pieces, i, j);
                        if (i == piece->file && j == piece->rank) {
                                board[i][j] = *piece;
                        }
                } 
        }
}

/*
 * Purpose:
 * Notes:
 * */

int main(void)
{
        ChessPiece pieces[32];
        ChessPiece board[8][8];
        Rectangle Background[8][8];
        
        ChessIcon Icons[12];
        LoadIcons(Icons);
        
        Vector2 mousePoint = { 0.0f, 0.0f };
        
        int ColorState[8][8];

        
        initialize_pieces(pieces, Icons);
        
        UnloadIcons(Icons);
#if 0 
        initialize_board(board, pieces);
#endif
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
        SetTargetFPS(60);
        SetExitKey(KEY_Q);

        ChessIconTexture IconTextures[12];
        
        Rectangle tmp_name_RECTANGLE = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        InitChessboard(Background);

        LoadIconsAsTextures(Icons, IconTextures);
        
        while (!WindowShouldClose()) {
                // Events
                mousePoint = GetMousePosition();

                for (int row = 0; row < 8; ++row) {
                        for (int col = 0; col < 8; ++col) {
                                if (CheckCollisionPointRec(mousePoint, Background[row][col])
                                                && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                                        ColorState[row][col] = 2;
                                        
                                } else if (CheckCollisionPointRec(mousePoint, Background[row][col])) {
                                        ColorState[row][col] = 1;
                                } else {
                                        ColorState[row][col] = 0;
                                }
                        }
                }
                // Game state update

                // Graphics drawing
                BeginDrawing();
                DrawChessboard(Background, LIGHTBEIGE, LIGHTBROWN);
                DrawMouseHoverAction(Background, ColorState);
#if 0          
#
                DrawChesspiecePotentialMoves(board);
                DrawChesspieces(LogicalChessboard, RenderChessboard,
                                tmp_name_RECTANGLE,
                                IconTextures, mousePoint);
#endif           
                EndDrawing();
        }
        CloseWindow();
        return 0;
}
