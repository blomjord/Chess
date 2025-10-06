#include "utils.h"
#include "moves.h"
#include "gui.h"
#include "types.h"

void UpdateState(void);
void RenderFrame(void);
void RenderWinnerFrame(void);
void initialize_pieces(ChessPiece pieces[64], Texture2D IconTextures[13]);
void initialize_board(ChessBoard board[8][8], ChessPiece pieces[64]);
void InitGame(void);
void ExitGame(void);
void zero_capture_matrix(void);
void detect_winner(ChessPiece *p);
int get_array_index_by_coords(ChessPiece pieces[64], int x, int y);
Point get_index_by_coords(float x, float y);

Image Icons[13];
ChessPiece pieces[64];
ChessBoard board[8][8];
Rectangle Background[8][8];
Texture2D IconTextures[13];

int ColorState[8][8];
int capture_matrix[8][8];

Vector2 mousePoint  = { 0.0f, 0.0f };
Vector2 touchPoint  = { 0.0f, 0.0f };

Rectangle touchArea       = { 0.0f, 0.0f, 5.0f, 5.0f };
Rectangle pieceArea       = { 0.0f, 0.0f, 100.0f, 100.0f };
Rectangle captured_pieces = { 800.0f, 0.0f, 200.0f, 800.0f };
Rectangle winner_display  = { 115.0f, 240.0f, 570.0f, 200.0f };
Rectangle button_exit     = { 420.0f, 360.0f, 160.f, 50.f };
Rectangle button_restart  = { 220.0f, 360.0f, 160.f, 50.f };

int quit = 0;
int b_winner = 0;
int w_winner = 0;
int heldPieceIndex  = -1;

Sound fxMoving;

int main(void)
{
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
        InitGame();
        while (!WindowShouldClose()) {
                UpdateState();
                RenderFrame();
                if (quit)
                        break;           
        }
        ExitGame();
        CloseWindow();
        return 0;
}

Point get_index_by_coords(float x, float y)
{
        Point point;
        point.x = (int) x;
        point.y = (int) y;
        point.x /= 100;
        point.y /= 100;
        return point;
}

Vector2 square_coords(int file, int rank)
{
        Vector2 pos;
        pos.x = file * SQUARE_SIZE + 50;
        pos.y = rank * SQUARE_SIZE + 50;
        return pos;
}

void InitGame(void)
{
        SetTargetFPS(60);
        SetExitKey(KEY_Q);
        LoadIcons(Icons);
        LoadIconsAsTextures(Icons, IconTextures);
        UnloadIcons(Icons);
        initialize_pieces(pieces, IconTextures);
        initialize_board(board, pieces);
        zero_capture_matrix();
        InitChessboard(Background);
        b_winner = 0;
        w_winner = 0;
        InitAudioDevice();
        fxMoving = LoadSound("Sounds/moving.wav");
}

void ExitGame(void)
{
        UnloadTextures(IconTextures);
        UnloadSound(fxMoving);
        //UnloadSoundFiles();
}

/*
 * Purpose: God-awful init func..
 * Notes:
 * */
void initialize_pieces(ChessPiece pieces[64], Texture2D IconTextures[13]) 
{
        // Order of struct members: type, file, rank, special_move, holding, texture, pos
        pieces[0]  = (ChessPiece) { B_ROOK,   0, 0, 1, 0, IconTextures[2],  square_coords(0, 0) };
        pieces[1]  = (ChessPiece) { B_ROOK,   7, 0, 1, 0, IconTextures[2],  square_coords(7, 0) };
        pieces[2]  = (ChessPiece) { B_KNIGHT, 1, 0, 0, 0, IconTextures[4],  square_coords(1, 0) };
        pieces[3]  = (ChessPiece) { B_KNIGHT, 6, 0, 0, 0, IconTextures[4],  square_coords(6, 0) };
        pieces[4]  = (ChessPiece) { B_BISHOP, 2, 0, 0, 0, IconTextures[3],  square_coords(2, 0) };
        pieces[5]  = (ChessPiece) { B_BISHOP, 5, 0, 0, 0, IconTextures[3],  square_coords(5, 0) };
        pieces[6]  = (ChessPiece) { B_QUEEN,  3, 0, 0, 0, IconTextures[1],  square_coords(3, 0) };
        pieces[7]  = (ChessPiece) { B_KING,   4, 0, 1, 0, IconTextures[0],  square_coords(4, 0) };
        pieces[8]  = (ChessPiece) { W_ROOK,   0, 7, 1, 0, IconTextures[8],  square_coords(0, 7) },
        pieces[9]  = (ChessPiece) { W_ROOK,   7, 7, 1, 0, IconTextures[8],  square_coords(7, 7) },
        pieces[10] = (ChessPiece) { W_KNIGHT, 1, 7, 0, 0, IconTextures[10], square_coords(1, 7) },
        pieces[11] = (ChessPiece) { W_KNIGHT, 6, 7, 0, 0, IconTextures[10], square_coords(6, 7) },
        pieces[12] = (ChessPiece) { W_BISHOP, 2, 7, 0, 0, IconTextures[9],  square_coords(2, 7) },
        pieces[13] = (ChessPiece) { W_BISHOP, 5, 7, 0, 0, IconTextures[9],  square_coords(5, 7) },
        pieces[14] = (ChessPiece) { W_QUEEN,  3, 7, 0, 0, IconTextures[7],  square_coords(3, 7) },
        pieces[15] = (ChessPiece) { W_KING,   4, 7, 1, 0, IconTextures[6],  square_coords(4, 7) };

        // Init of pawns and empty cells
        int index = 16;
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { B_PAWN, file, 1, 1, 0, IconTextures[5], square_coords(file, 1) };
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { W_PAWN, file, 6, 1, 0, IconTextures[11], square_coords(file, 6) };
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
                if (pieces[i].file == x && pieces[i].rank == y && pieces[i].type != EMPTY)
                        return &pieces[i];
        return NULL;
}

int get_array_index_by_coords(ChessPiece pieces[64], int x, int y)
{
        for (int i = 0; i < 64; ++i)
                if (pieces[i].file == x && pieces[i].rank == y)
                        return i;
        fprintf(stderr, "No chess piece found. Exiting.");
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
                                board[file][rank].file  = file;
                                board[file][rank].rank  = rank;
                                board[file][rank].piece = piece;
                        } else {
                                board[file][rank].file  = file;
                                board[file][rank].rank  = rank;
                                board[file][rank].piece = NULL;
                        }
                } 
        }
}

/*
 * Purpose: Zeroes capture matrix.
 * Used in show_moves to determine legal moves
 *
 * Notes:
 * */
void zero_capture_matrix(void)
{
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j)
                        capture_matrix[i][j] = 0;
        }
}

void UpdateState(void)
{
        mousePoint = GetMousePosition();
        touchArea.x = mousePoint.x;
        touchArea.y = mousePoint.y;

        DetectActionMouseHover(mousePoint, Background, ColorState);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
                                && heldPieceIndex == -1) {
                mousePoint = GetMousePosition();
                for (int i = 0; i < 64; ++i) {
                        pieceArea.x = (float) pieces[i].file * SQUARE_SIZE;
                        pieceArea.y = (float) pieces[i].rank * SQUARE_SIZE;
                        touchArea.x = mousePoint.x;
                        touchArea.y = mousePoint.y;
                        
                        if (pieces[i].type != EMPTY
                               && CheckCollisionPointRec(mousePoint, pieceArea)) {
                                heldPieceIndex = i;
                                pieces[i].holding = 1;
                                break;
                        }         
                }
        }

        // If a piece is being held
        if (heldPieceIndex != -1) {
                mousePoint = GetMousePosition();
                
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        pieces[heldPieceIndex].pos.x = mousePoint.x;
                        pieces[heldPieceIndex].pos.y = mousePoint.y;
                        show_moves(board, ColorState, capture_matrix, pieces[heldPieceIndex]);
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                        mousePoint = GetMousePosition();
                        Point target = get_index_by_coords(mousePoint.x, mousePoint.y);
                        if (swap_allowed(board, capture_matrix, pieces[heldPieceIndex], target.x, target.y)) {
                                Point source;
                                source.x = pieces[heldPieceIndex].file;
                                source.y = pieces[heldPieceIndex].rank;

                                ChessPiece *moving = board[source.x][source.y].piece;
                                ChessPiece *capture = board[target.x][target.y].piece;

                                if (capture != NULL && capture->type != EMPTY) {
                                        detect_winner(capture);
                                        capture->type = EMPTY;
                                        board[target.x][target.y].piece = NULL;
                                }
                                board[source.x][source.y].piece = NULL;
                                board[target.x][target.y].piece = moving;
                                
                                moving->file = target.x;
                                moving->rank = target.y;
                                moving->pos.x = (target.x * SQUARE_SIZE) + PIXEL_OFFSET;
                                moving->pos.y = (target.y * SQUARE_SIZE) + PIXEL_OFFSET;

                                if (pieces[heldPieceIndex].type == W_PAWN
                                 || pieces[heldPieceIndex].type == B_PAWN)
                                        pieces[heldPieceIndex].special_move = 0;

                                pieces[heldPieceIndex].holding = 0;
                                heldPieceIndex = -1;
                                zero_capture_matrix();
                                PlaySound(fxMoving);
                        } else { 
                                pieces[heldPieceIndex].pos.x = (pieces[heldPieceIndex].file * SQUARE_SIZE) + PIXEL_OFFSET;
                                pieces[heldPieceIndex].pos.y = (pieces[heldPieceIndex].rank * SQUARE_SIZE) + PIXEL_OFFSET;
                                pieces[heldPieceIndex].holding = 0;
                                heldPieceIndex = -1;
                                zero_capture_matrix();
                        }
                }
        }
}

void RenderFrame(void)
{
        BeginDrawing();
        
        ClearBackground(LIGHTBEIGE);
        DrawChessboard(Background, LIGHTBEIGE, LIGHTBROWN);
        DrawChesspieceLegalMoves(ColorState);
        DrawMouseHoverAction(Background, ColorState);
        DrawChesspieces(pieces, mousePoint);
        DrawCapturedChesspieces(captured_pieces);
        if (b_winner || w_winner) {
                DrawWinner(winner_display, b_winner, w_winner);
                if (RestartButtonClicked(button_restart))
                        InitGame();
                if (QuitButtonClicked(button_exit))
                        quit = 1;
        }
        
        EndDrawing();
}

/*
 * Purpose: Cheks if captured piece is king
 * Notes:
 * */
void detect_winner(ChessPiece *p)
{
        if (p && p->type == W_KING)
                b_winner = 1;
        if (p && p->type == B_KING)
                w_winner = 1;
}
