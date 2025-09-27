#include "utils.h"
#include "moves.h"
#include "gui.h"

void initialize_pieces(ChessPiece pieces[32]) 
{
        ChessPiece tmp[32] = {
                { B_ROOK,   0, 0, 0, 'r' },
                { B_ROOK,   7, 0, 0, 'r' },
                { B_KNIGHT, 1, 0, 0, 'k' },
                { B_KNIGHT, 6, 0, 0, 'k' },
                { B_BISHOP, 2, 0, 0, 'b' },
                { B_BISHOP, 5, 0, 0, 'b' },
                { B_QUEEN,  3, 0, 0, 'q' },
                { B_KING,   4, 0, 0, 'w' },
                { B_PAWN,   0, 1, 0, 'p' },
                { B_PAWN,   1, 1, 0, 'p' },
                { B_PAWN,   2, 1, 0, 'p' },
                { B_PAWN,   3, 1, 0, 'p' },
                { B_PAWN,   4, 1, 0, 'p' },
                { B_PAWN,   5, 1, 0, 'p' },
                { B_PAWN,   6, 1, 0, 'p' },
                { B_PAWN,   7, 1, 0, 'p' },

                { W_ROOK,   0, 7, 0, 'R' },
                { W_ROOK,   7, 7, 0, 'R' },
                { W_KNIGHT, 1, 7, 0, 'K' },
                { W_KNIGHT, 6, 7, 0, 'K' },
                { W_BISHOP, 2, 7, 0, 'B' },
                { W_BISHOP, 5, 7, 0, 'B' },
                { W_QUEEN,  3, 7, 0, 'Q' },
                { W_KING,   4, 7, 0, 'W' },
                { W_PAWN,   0, 6, 0, 'P' },
                { W_PAWN,   1, 6, 0, 'P' },
                { W_PAWN,   2, 6, 0, 'P' },
                { W_PAWN,   3, 6, 0, 'P' },
                { W_PAWN,   4, 6, 0, 'P' },
                { W_PAWN,   5, 6, 0, 'P' },
                { W_PAWN,   6, 6, 0, 'P' },
                { W_PAWN,   7, 6, 0, 'P' }
        };
    // Assign the chess pieces
        for (int i = 0; i < 32; ++i)
                pieces[i] = tmp[i];
}

/*
 *  Returns a pointer to chosen chess piece, or NULL
 * */
ChessPiece *get_piece_by_coords(ChessPiece pieces[32], int x, int y)
{
        for (int i = 0; i < 32; ++i)
                if (pieces[i].x == x && pieces[i].y == y)
                        return &pieces[i];
        return NULL;
}

void initialize_board(BoardCell board[8][8], ChessPiece pieces[32])
{
        ChessPiece *piece;
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 2; ++j) {
                        piece = get_piece_by_coords(pieces, i, j);
                        if (i == piece->x && j == piece->y) {
                                board[i][j].is_selected = 0;
                                board[i][j].piece = piece;
                        }
                } 
                for (int j = 2; j < 6; ++j) {
                        board[i][j].is_selected = 0;
                        board[i][j].piece = NULL;
                }

                for (int j = 6; j < 8; ++j) {
                        piece = get_piece_by_coords(pieces, i, j);
                        if (i == piece->x && j == piece->y) {
                                board[i][j].is_selected = 0;
                                board[i][j].piece = piece;
                        }
                } 
        }
}

/*
 * Purpose:
 * Notes:
 * */
void move(BoardCell board[8][8], ChessPiece pieces[32])
{
        return NULL; 
}

#if 0
int is_legal_move(ChessPiece *board[0][0], ChessPiece *piece)
{
        return 0;
}
void show_legal_moves(ChessPiece *board[8][8], ChessPiece *piece, Point *moves)
{
        printf("    ");
                for (int i = 97; i < 105; ++i) {
                printf("%c ", i);
                }
        printf("\n");
        /*
        * For development purposes, this is reverse.
        * For final build, change loop index i to:
        * for (int i = 7; i > -1; --i)
        * */
        ChessPiece *piece;
        for (int i = 7; i > -1; --i) {
                printf("%d [ ", i + 1);
                for (int j = 0; j < 8; ++j) {
                        piece = get_piece_by_coords(pieces, j, i);
                        if (piece != NULL) {
                                if (is_legal_move(board, piece))
                                        printf(". ");
                                else
                                        printf("%c ", board[j][i]->symbol);
                         } else {
                                printf("  ");
                         }
        }
        printf("] %d\n", i + 1);
}
        printf("    ");
        for (int i = 97; i < 105; ++i) {
                printf("%c ", i);
        }
        printf("\n");
}
#endif
int main(void)
{
        ChessPiece pieces[32];
        BoardCell LogicalChessboard[8][8];
        
        int ColorState[8][8];
        int ChessIconCoordinateOffset = 55 / 2;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 800;
        const int SQUARE_WIDTH = SCREEN_WIDTH / 8;
        const int SQUARE_HEIGHT = SCREEN_HEIGHT / 8;
        
        Color LIGHTBEIGE = { 230, 215, 215, 255 };
        Color LIGHTBROWN = { 196, 133, 94, 255 };

        initialize_pieces(pieces);
        initialize_board(LogicalChessboard, pieces);

        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
        SetTargetFPS(60);
        SetExitKey(KEY_Q);

        ChessIcon Icons[12];
        ChessIconTexture IconTextures[12];
        
        Rectangle RenderChessboard[8][8];
        InitChessboard(RenderChessboard, SQUARE_WIDTH, SQUARE_HEIGHT);
        Vector2 mousePoint = { 0.0f, 0.0f };

        LoadIcons(Icons);
        LoadIconsAsTextures(Icons, IconTextures);
        UnloadIcons(Icons);
        
        while (!WindowShouldClose()) {

                // Events
                mousePoint = GetMousePosition();

                for (int row = 0; row < 8; ++row) {
                        for (int col = 0; col < 8; ++col) {
                                if (CheckCollisionPointRec(mousePoint, RenderChessboard[row][col])
                                                && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                                        ColorState[row][col] = 2;
                                        
                                } else if (CheckCollisionPointRec(mousePoint, RenderChessboard[row][col])) {
                                        ColorState[row][col] = 1;
                                } else {
                                        ColorState[row][col] = 0;
                                }
                        }
                }

                for (int i = 0; i < 32; ++i) {
                        
                }

                // Game state update

                // Graphics drawing
                BeginDrawing();
                
                DrawChessboard(RenderChessboard, LIGHTBEIGE, LIGHTBROWN);
                DrawMouseHoverAction(RenderChessboard, ColorState);
                DrawChesspiecePotentialMoves(LogicalChessboard);
                DrawChesspieces(LogicalChessboard, RenderChessboard,
                                IconTextures, mousePoint,
                                SQUARE_WIDTH, SQUARE_HEIGHT);
                
                EndDrawing();
        }
        CloseWindow();
        return 0;
}
