#include "utils.h"
#include "moves.h"

#ifdef USE_GRAPHICS
#include "gui.h"
#else
#include "tui.h"
#endif




void initialize_pieces(ChessPiece pieces[32]) 
{
        ChessPiece tmp[32] = {
        
                // Black
                { B_ROOK,   0, 7, 0, 'r' },
                { B_ROOK,   7, 7, 0, 'r' },
                { B_KNIGHT, 1, 7, 0, 'k' },
                { B_KNIGHT, 6, 7, 0, 'k' },
                { B_BISHOP, 2, 7, 0, 'b' },
                { B_BISHOP, 5, 7, 0, 'b' },
                { B_QUEEN,  3, 7, 0, 'q' },
                { B_KING,   4, 7, 0, 'w' },
                { B_PAWN,   0, 6, 0, 'p' },
                { B_PAWN,   1, 6, 0, 'p' },
                { B_PAWN,   2, 6, 0, 'p' },
                { B_PAWN,   3, 6, 0, 'p' },
                { B_PAWN,   4, 6, 0, 'p' },
                { B_PAWN,   5, 6, 0, 'p' },
                { B_PAWN,   6, 6, 0, 'p' },
                { B_PAWN,   7, 6, 0, 'p' },
                
                // White
                { W_ROOK,   0, 0, 0, 'R' },
                { W_ROOK,   7, 0, 0, 'R' },
                { W_KNIGHT, 1, 0, 0, 'K' },
                { W_KNIGHT, 6, 0, 0, 'K' },
                { W_BISHOP, 2, 0, 0, 'B' },
                { W_BISHOP, 5, 0, 0, 'B' },
                { W_QUEEN,  3, 0, 0, 'Q' },
                { W_KING,   4, 0, 0, 'W' },
                { W_PAWN,   0, 1, 0, 'P' },
                { W_PAWN,   1, 1, 0, 'P' },
                { W_PAWN,   2, 1, 0, 'P' },
                { W_PAWN,   3, 1, 0, 'P' },
                { W_PAWN,   4, 1, 0, 'P' },
                { W_PAWN,   5, 1, 0, 'P' },
                { W_PAWN,   6, 1, 0, 'P' },
                { W_PAWN,   7, 1, 0, 'P' }
        };
    // Assignt the chess pieces
        for (int i = 0; i < 32; ++i) {
                pieces[i] = tmp[i];
        }
}


/*
 *  Returns a pointer to chosen chess piece, or NULL
 * */
ChessPiece *get_piece_by_coords(ChessPiece pieces[32], int x, int y)
{
        for (int i = 0; i < 32; ++i) {
                if (pieces[i].x == x && pieces[i].y == y)
                        return &pieces[i];
        }
        return NULL;
}

void initialize_board(ChessPiece *board[8][8], ChessPiece pieces[32])
{
        ChessPiece *piece;
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 2; ++j) {
                        piece = get_piece_by_coords(pieces, i, j);
                        printf("i: %d j: %d\n", i, j);
                        if (i == piece->x && j == piece->y)
                                board[i][j] = piece;
                }
                
                for (int j = 2; j < 6; ++j)
                        board[i][j] = NULL;

                for (int j = 6; j < 8; ++j) {
                        if (i == piece->x && j == piece->y)
                                board[i][j] = piece;
                } 
        }
}

void get_user_input(char *buf)
{
        fgets(buf, 3, stdin);
        int c;
        while ( (c = getchar()) != '\n' && c != EOF); // Flushes stdin
}

// Maybe don't use this (remove?)
char *get_sized_line(char *buf)
{
    while (fgets(buf, 3, stdin)) {
        size_t len = strlen(buf);
        if (len > 2 && buf[--len] == '\n')
            return buf;
        
        int ch = fgetc(stdin);
        
        if (ch == '\n' || feof(stdin))
            return buf;
        
        while (ch != '\n' && ch != EOF) {
            ch = fgetc(stdin);
        }
        if (ch == EOF)
            return NULL;
    }
    return NULL;
}

// The following functions generate the possible and legal moves for each piece.
void show_available_moves(ChessPiece *board[8][8], int type, int x, int y, Point *available_moves)
{
        switch (type) {
                case B_PAWN:
                case W_PAWN:
                        moves_pawn(board, type, x, y, available_moves);
                        break;
                case B_ROOK:
                case W_ROOK:
                        moves_rook(board, type, x, y, available_moves);
                        break;
                case B_KNIGHT:
                case W_KNIGHT:
                        moves_knight(type, x, y, available_moves);
                        break;
                case B_BISHOP:
                case W_BISHOP:
                        moves_bishop(type, x, y, available_moves);
                        break;
                case B_QUEEN:
                case W_QUEEN:
                        moves_queen(type, x, y, available_moves);
                        break;
                case B_KING:
                case W_KING:
                        moves_king(type, x, y, available_moves);
                        break;
        }
}

// Performs move if legal.
void move(ChessPiece *board[8][8], ChessPiece pieces[32], Point *available_moves)
{
        int posX, posY, tarX, tarY;
        char pos[3];
        char tar[3];
        
        while (1) {

                printf("Choose pos: \n");
                get_user_input(pos);

                posX = pos[0] - 97;
                posY = pos[1] - 49;

                if (board[posX][posY] == EMPTY)
                        continue;
                
                ChessPiece *piece_to_move = get_piece_by_coords(pieces, posX, posY);
                show_available_moves(board, piece_to_move->type, posX, posY, available_moves);
                printf("Choose target: \n");
                get_user_input(tar);
                tarX = tar[0] - 97;
                tarY = tar[1] - 49;
                
                if ( board[posX][posY] != EMPTY && piece_to_move != NULL ) {
                            piece_to_move->x = tarX;
                            piece_to_move->y = tarY;
                            board[tarX][tarY] = piece_to_move->type;
                            board[posX][posY] = EMPTY;
                            break;
                } else {
                            printf("Empty cell. Please try again.\n");
                            continue;
                }
        }
}


// Continously prints the board after each move.
void print_board(ChessPiece *board[8][8])
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
        for (int i = 7; i > -1; --i) {
                printf("%d [ ", i + 1);
                for (int j = 0; j < 8; ++j) {
                        printf("type: %d\n", board[i][j]->type);
                        switch (board[j][i]->type) {
                                case W_PAWN:
                                        printf("P ");
                                        break;
                                case W_ROOK:
                                        printf("R ");
                                        break;
                                case W_KNIGHT:
                                        printf("K ");
                                        break;
                                case W_BISHOP:
                                        printf("B ");
                                        break;
                                case W_QUEEN:
                                        printf("Q ");
                                        break;
                                case W_KING:
                                        printf("K ");
                                        break;
                                case B_PAWN:
                                        printf("p ");
                                        break;
                                case B_ROOK:
                                        printf("r ");
                                        break;
                                case B_KNIGHT:
                                        printf("k ");
                                        break;
                                case B_BISHOP:
                                        printf("b ");
                                        break;
                                case B_QUEEN:
                                        printf("q ");
                                        break;
                                case B_KING:
                                        printf("k ");
                                        break;
                                default:
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

int main()
{
        ChessPiece pieces[32];
        ChessPiece *board[8][8];
        Point *available_moves = malloc(2 * sizeof(int));

        initialize_pieces(pieces);
        initialize_board(board, pieces);
        print_board(board);
        printf("d6");
        while(1) {
                move(board, pieces, available_moves);
                print_board(board);
        }
    
        free(pieces);

        return 0;
}
