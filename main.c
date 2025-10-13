/*
 * Graphical chess game built with Raylib Framework
 * 
 * Made by: André Norberg
 *
 * */

#include "utils.h"
#include "moves.h"
#include "gui.h"
#include "types.h"

// ----------------------------------------------------------------------------
// Local function declarations 
// ----------------------------------------------------------------------------
void InitGame(void);                                                   // Initializes game state
void ExitGame(void);                                                   // Context clean up for exiting
void UpdateState(void);                                                // Update game state
void RenderFrame(void);                                                // Draw every frame
void RenderWinnerFrame(void);                                          // Draw menu when game is won
void initialize_board(ChessBoard board[8][8], ChessPiece pieces[64]);  // Initialize chess board context
void initialize_pieces(ChessPiece pieces[64], Texture2D Textures[13]); // Initialize chess pieces
void initialize_captured_pieces(ChessPiece captured[30]);              // Initialize captured pieces array

void detect_winner(ChessPiece *p);                                              
int get_array_index_by_coords(ChessPiece pieces[64], int x, int y);
void scan_capture_matrix(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece pieces[64]);
void zero_capture_matrix(void);

Vector2_Int get_index_by_coords(float x, float y);

ChessPiece pieces[64];
ChessPiece captured_pieces[30];

ChessBoard board[8][8];
Rectangle Background[8][8];

Image Icons[13];
Texture2D Textures[13];

int ColorState[8][8];
int capture_matrix[8][8];

// ----------------------------------------------------------------------------
// GUI shapes (including for mouse interaction)
// ----------------------------------------------------------------------------
Vector2 mousePoint  = { 0.0f, 0.0f };
Vector2 touchPoint  = { 0.0f, 0.0f };

Rectangle touchArea       = { 0.0f, 0.0f, 5.0f, 5.0f };
Rectangle pieceArea       = { 0.0f, 0.0f, 100.0f, 100.0f };
Rectangle CapturedPieces  = { 800.0f, 0.0f, 110.0f, 800.0f };
Rectangle winner_display  = { 115.0f, 240.0f, 570.0f, 200.0f };
Rectangle button_exit     = { 420.0f, 360.0f, 160.f, 50.f };
Rectangle button_restart  = { 220.0f, 360.0f, 160.f, 50.f };

int turn            =  1;
int quit            =  0;
int b_winner        =  0;
int w_winner        =  0;
int heldPieceIndex  = -1;
int captured_index  =  0;

// ----------------------------------------------------------------------------
// Sound effects
// ----------------------------------------------------------------------------
Sound fxGrab;
Sound fxPlace;

// ----------------------------------------------------------------------------
// Program main entry point
// ----------------------------------------------------------------------------
int main(void)
{
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
        InitAudioDevice();
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

// ----------------------------------------------------------------------------
// Local function definitions 
// ----------------------------------------------------------------------------

/*
 * Purpose: Gives chess board file and rank according to pixel coordinates.
 *
 * Notes
 *
 * */
Vector2_Int get_index_by_coords(float x, float y)
{
        Vector2_Int point;
        point.x = (int) x;
        point.y = (int) y;
        point.x /= 100;
        point.y /= 100;
        return point;
}

/*
 * Purpose: Gives pixel coordinates for chosen chess board cell.
 *
 * Notes: Offset needed because origin is in top-left corner.
 *
 * */
Vector2 square_coords(int file, int rank)
{
        Vector2 pos;
        pos.x = file * SQUARE_SIZE + 50;
        pos.y = rank * SQUARE_SIZE + 50;
        return pos;
}

/*
 * Purpose: Initializes the game state.
 *
 * Notes: This is also called when "Restart" is chosen.
 *
 * */
void InitGame(void)
{
        SetTargetFPS(60);
        SetExitKey(KEY_Q);
        LoadIcons(Icons);
        LoadIconsAsTextures(Icons, Textures);
        UnloadIcons(Icons);
        initialize_pieces(pieces, Textures);
        initialize_board(board, pieces);
        initialize_captured_pieces(captured_pieces);
        zero_capture_matrix();
        InitChessboard(Background);
        turn = 1;
        b_winner = 0;
        w_winner = 0;
        fxGrab = LoadSound("Sounds/grab.wav");
        fxPlace = LoadSound("Sounds/place.wav");
}

/*
 * Purpose: Context clean up for successful exit.
 *
 * Notes:
 *
 * */
void ExitGame(void)
{
        UnloadTextures(Textures);
        UnloadSound(fxGrab);
        UnloadSound(fxPlace);
        CloseAudioDevice();
        //UnloadSoundFiles();
}

/*
 * Purpose: Initializes each chess piece on the board,
 * as well as empty cells.
 * 
 * Notes:
 *
 * */
void initialize_pieces(ChessPiece pieces[64], Texture2D Textures[13]) 
{
        // Order of struct members: type, file, rank, special_move, holding, texture, pos
        pieces[0]  = (ChessPiece) { 0, B_ROOK,   0, 0, 1, 0, Textures[2],  square_coords(0, 0) };
        pieces[1]  = (ChessPiece) { 0, B_ROOK,   7, 0, 1, 0, Textures[2],  square_coords(7, 0) };
        pieces[2]  = (ChessPiece) { 0, B_KNIGHT, 1, 0, 0, 0, Textures[4],  square_coords(1, 0) };
        pieces[3]  = (ChessPiece) { 0, B_KNIGHT, 6, 0, 0, 0, Textures[4],  square_coords(6, 0) };
        pieces[4]  = (ChessPiece) { 0, B_BISHOP, 2, 0, 0, 0, Textures[3],  square_coords(2, 0) };
        pieces[5]  = (ChessPiece) { 0, B_BISHOP, 5, 0, 0, 0, Textures[3],  square_coords(5, 0) };
        pieces[6]  = (ChessPiece) { 0, B_QUEEN,  3, 0, 0, 0, Textures[1],  square_coords(3, 0) };
        pieces[7]  = (ChessPiece) { 0, B_KING,   4, 0, 1, 0, Textures[0],  square_coords(4, 0) };
        pieces[8]  = (ChessPiece) { 1, W_ROOK,   0, 7, 1, 0, Textures[8],  square_coords(0, 7) },
        pieces[9]  = (ChessPiece) { 1, W_ROOK,   7, 7, 1, 0, Textures[8],  square_coords(7, 7) },
        pieces[10] = (ChessPiece) { 1, W_KNIGHT, 1, 7, 0, 0, Textures[10], square_coords(1, 7) },
        pieces[11] = (ChessPiece) { 1, W_KNIGHT, 6, 7, 0, 0, Textures[10], square_coords(6, 7) },
        pieces[12] = (ChessPiece) { 1, W_BISHOP, 2, 7, 0, 0, Textures[9],  square_coords(2, 7) },
        pieces[13] = (ChessPiece) { 1, W_BISHOP, 5, 7, 0, 0, Textures[9],  square_coords(5, 7) },
        pieces[14] = (ChessPiece) { 1, W_QUEEN,  3, 7, 0, 0, Textures[7],  square_coords(3, 7) },
        pieces[15] = (ChessPiece) { 1, W_KING,   4, 7, 1, 0, Textures[6],  square_coords(4, 7) };

        // Init of pawns and empty cells
        int index = 16;
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { 0, B_PAWN, file, 1, 1, 0, Textures[5], square_coords(file, 1) };
        for (int file = 0; file < 8; ++file)
                pieces[index++] = (ChessPiece) { 1, W_PAWN, file, 6, 1, 0, Textures[11], square_coords(file, 6) };
        for (int file = 0; file < 8; ++file) {
                for (int rank = 2; rank < 6; ++rank)
                        pieces[index++] = (ChessPiece) { -1, EMPTY, file, rank, 0, 0, Textures[12], square_coords(file, rank) };
        }
}

/*
 *  Purpose: Returns a pointer to chosen chess piece, or NULL
 *
 *  Notes:
 *
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
 * Purpose: Inits chess board with all the pieces.
 *
 * Notes: Empty cells are also inited but as "EMPTY"
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
 * Purpose: Inits array captured pieces for use when
 * drawing the GUI.
 *
 * Notes:
 *
 * */
void initialize_captured_pieces(ChessPiece captured[30])
{
        for (int i = 0; i < 30; ++i)
                captured[i].type = EMPTY;
}

/*
 * Purpose:
 *
 * Notes:
 *
 * */
void scan_capture_matrix(ChessBoard board[8][8], int ColorState[8][8], int capture_matrix[8][8], ChessPiece pieces[64])
{
        for (int i = 0; i < 32; ++i) { // Only 32 pieces are non-empty
                show_moves(board, ColorState, capture_matrix, pieces[i]);
                for (int file = 0; file < 8; ++file) {
                        for (int rank = 0; rank < 8; ++rank) {
                                if (board[file][rank].piece != NULL) {
                                        if (capture_matrix[file][rank] && board[file][rank].piece->type == W_KING) {
                                                ColorState[file][rank] = 4;

                                        }
                                        if (capture_matrix[file][rank] && board[file][rank].piece->type == B_KING) {
                                                ColorState[file][rank] = 4;
                                        }
                                }
                        }
                }
                zero_capture_matrix();
        }
}

/*
 * Purpose: Zeroes capture matrix.
 * Used in show_moves to determine legal moves
 *
 * Notes:
 *
 * */
void zero_capture_matrix(void)
{
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j)
                        capture_matrix[i][j] = 0;
        }
}

/*
 * Updates game state. Includes moving pieces,
 * capturing, detecting potential winner
 *
 * Notes:
 * */
void UpdateState(void)
{
        // CHECK IF KING IS CHECK/CHECKMATE
        scan_capture_matrix(board, ColorState, capture_matrix, pieces);
        mousePoint = GetMousePosition();
        touchArea.x = mousePoint.x;
        touchArea.y = mousePoint.y;

        DetectActionMouseHover(mousePoint, Background, ColorState); // Blue effect when mouse is over cell
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
                                && heldPieceIndex == -1) {
                mousePoint = GetMousePosition();
                for (int i = 0; i < 64; ++i) {
                        pieceArea.x = (float) pieces[i].file * SQUARE_SIZE;
                        pieceArea.y = (float) pieces[i].rank * SQUARE_SIZE;
                        touchArea.x = mousePoint.x;
                        touchArea.y = mousePoint.y;
                        //TODO: Continue here
                        if (pieces[i].type != EMPTY
                               && CheckCollisionPointRec(mousePoint, pieceArea)
                               && turn == pieces[i].color) {
                                heldPieceIndex = i;
                                pieces[i].holding = 1;
                                PlaySound(fxGrab);
                                break;
                        }         
                }
        }

        // If a piece is being grabbed and held
        if (heldPieceIndex != -1) {
                mousePoint = GetMousePosition();
                
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        pieces[heldPieceIndex].pos.x = mousePoint.x;
                        pieces[heldPieceIndex].pos.y = mousePoint.y;
                        show_moves(board, ColorState, capture_matrix, pieces[heldPieceIndex]);
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                        mousePoint = GetMousePosition();
                        Vector2_Int target = get_index_by_coords(mousePoint.x, mousePoint.y);
                        show_moves(board, ColorState, capture_matrix, pieces[heldPieceIndex]);

                        // Check if swapped piece is actually on other team
                        if (swap_allowed(board, capture_matrix, pieces[heldPieceIndex], target.x, target.y)) {
                                Vector2_Int source;
                                source.x = pieces[heldPieceIndex].file;
                                source.y = pieces[heldPieceIndex].rank;

                                ChessPiece *moving = board[source.x][source.y].piece;
                                ChessPiece *capturing = board[target.x][target.y].piece;
                                
                                if (capturing != NULL && capturing->type != EMPTY) {
                                        if (moving->type == W_KING && capturing->type == W_ROOK) { // Check white castle
                                                castle(moving, capturing, board);
                                                goto out_castled;
                                        }
                                        if (moving->type == B_KING && capturing->type == B_ROOK) { // Check black castle
                                                castle(moving, capturing, board);
                                                goto out_castled;
                                        }

                                        detect_winner(capturing);
                                        captured_pieces[captured_index++] = *capturing;
                                        capturing->type = EMPTY;
                                        board[target.x][target.y].piece = NULL;
                                }
                                board[source.x][source.y].piece = NULL;
                                board[target.x][target.y].piece = moving;
                                
                                moving->file = target.x;
                                moving->rank = target.y;
                                moving->pos.x = (target.x * SQUARE_SIZE) + PIXEL_OFFSET;
                                moving->pos.y = (target.y * SQUARE_SIZE) + PIXEL_OFFSET;

                                // Pawn initial potential double move
                                //if (pieces[heldPieceIndex].type == W_PAWN
                                 //|| pieces[heldPieceIndex].type == B_PAWN)
out_castled:
                                pieces[heldPieceIndex].special_move = 0;
                                pieces[heldPieceIndex].holding = 0;
                                heldPieceIndex = -1;
                                zero_capture_matrix();
                                PlaySound(fxPlace);
                                turn = turn ^ 1; // XOR, Change turns between each move
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

/*
 * Purpose: Renders each frame according to current game state.
 *
 * Notes:
 *
 * */
void RenderFrame(void)
{
        BeginDrawing();
        
        ClearBackground(LIGHTBEIGE);
        DrawChessboard(Background, LIGHTBEIGE, LIGHTBROWN);
        DrawChesspieceLegalMoves(ColorState);
        DrawMouseHoverAction(Background, ColorState);
        DrawKingInCheck(Background, ColorState);
        DrawChesspieces(pieces, mousePoint);
        DrawCapturedChesspieces(CapturedPieces, captured_pieces);
        if (b_winner || w_winner) {
                DrawWinner(winner_display, b_winner, w_winner);
                if (DetectRestartButtonClicked(button_restart))
                        InitGame();
                if (DetectQuitButtonClicked(button_exit))
                        quit = 1;
        }
        
        EndDrawing();
}

/*
 * Purpose: Cheks if captured piece is king
 *
 * Notes:
 *
 * */
void detect_winner(ChessPiece *p)
{
        if (p && p->type == W_KING)
                b_winner = 1;
        if (p && p->type == B_KING)
                w_winner = 1;
}
