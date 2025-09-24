#include "utils.h"
#include "moves.h"

#ifdef USE_GRAPHICS
#include "gui.h"
#else
#include "tui.h"
#endif


typedef struct {
        int type, x, y;
        char symbol;
} ChessPiece;


void initialize_chesspieces(ChessPiece *pieces) 
{
        ChessPiece tmp[] = {
        
                // Black
                { B_ROOK,   0, 7, 'r' },
                { B_ROOK,   7, 7, 'r' },
                { B_KNIGHT, 1, 7, 'k' },
                { B_KNIGHT, 6, 7, 'k' },
                { B_BISHOP, 2, 7, 'b' },
                { B_BISHOP, 5, 7, 'b' },
                { B_QUEEN,  3, 7, 'q' },
                { B_KING,   4, 7, 'k' },
                { B_PAWN,   0, 6, 'p' },
                { B_PAWN,   1, 6, 'p' },
                { B_PAWN,   2, 6, 'p' },
                { B_PAWN,   3, 6, 'p' },
                { B_PAWN,   4, 6, 'p' },
                { B_PAWN,   5, 6, 'p' },
                { B_PAWN,   6, 6, 'p' },
                { B_PAWN,   7, 6, 'p' },
                
                // White
                { W_ROOK,   0, 0, 'R' },
                { W_ROOK,   7, 0, 'R' },
                { W_KNIGHT, 1, 0, 'K' },
                { W_KNIGHT, 6, 0, 'K' },
                { W_BISHOP, 2, 0, 'B' },
                { W_BISHOP, 5, 0, 'B' },
                { W_QUEEN,  3, 0, 'Q' },
                { W_KING,   4, 0, 'K' },
                { W_PAWN,   0, 1, 'P' },
                { W_PAWN,   1, 1, 'P' },
                { W_PAWN,   2, 1, 'P' },
                { W_PAWN,   3, 1, 'P' },
                { W_PAWN,   4, 1, 'P' },
                { W_PAWN,   5, 1, 'P' },
                { W_PAWN,   6, 1, 'P' },
                { W_PAWN,   7, 1, 'P' }
        };
    // Assignt the chess pieces
        for (int i = 0; i < 32; ++i) {
                pieces[i] = tmp[i];
        }
}

// Initializes chessboard.
// Integers 0-31 represents individual chess pieces.
// Integer -1 represents an empty cell.
// INPUT: Empty chessboard
// RETURNS: Initialized chessboard
void initialize_chessboard(int **chessboard, ChessPiece *pieces)
{
        for (int i = 0; i < 8; ++i) {
                chessboard[i] = (int *) malloc(8 * sizeof(int));
        }
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                        for (int k = 0; k < 32; ++k) {
                                if (pieces[k].x == i && pieces[k].y == j) {
                                        chessboard[i][j] = pieces[k].type;
                                }
                        }
                } 
        }
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                        if (j > 1 && j < 6) {
                                chessboard[i][j] = EMPTY;
                        }
                }
        }
}

/*
 *  Returns a pointer to chosen chess piece
 * */
ChessPiece *get_piece_by_coords(ChessPiece *pieces, int x, int y)
{
        for (int i = 0; i < 32; ++i) {
                if (pieces[i].x == x && pieces[i].y == y)
                        return &pieces[i];
        }
        return NULL;
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
// Performs move if legal.
void move(int **chessboard, ChessPiece *pieces, Point *available_moves)
{
        int posX, posY, tarX, tarY;
        char pos[3];
        char tar[3];
        
        while (1) {

                printf("Choose pos: \n");
                get_user_input(pos);

                posX = pos[0] - 97;
                posY = pos[1] - 49;

                if (chessboard[posX][posY] == EMPTY)
                        continue;
                
                ChessPiece *piece_to_move = get_piece_by_coords(pieces, posX, posY);
                show_available_moves(piece_to_move, posX, posY, available_moves);
                printf("Choose target: \n");
                get_user_input(tar);
                tarX = tar[0] - 97;
                tarY = tar[1] - 49;
                
                if ( chessboard[posX][posY] != EMPTY && piece_to_move != NULL ) {
                            piece_to_move->x = tarX;
                            piece_to_move->y = tarY;
                            chessboard[tarX][tarY] = piece_to_move->type;
                            chessboard[posX][posY] = EMPTY;
                            break;
                } else {
                            printf("Empty cell. Please try again.\n");
                            continue;
                }
        }
}

// The following functions generate the possible and legal moves for each piece.
void show_available_moves(ChessPiece *piece, int x, int y, Point *available_moves)
{
        Point *placeholder = malloc(sizeof(int));
        int type = piece->type;
        switch (type) {
                case B_PAWN:
                case W_PAWN:
                        moves_pawn(type, 1, 1, available_moves);
                        break;
                case B_ROOK:
                case W_ROOK:
                        moves_rook(type, x, y, placeholder);
                        break;
                case B_KNIGHT:
                case W_KNIGHT:
                        moves_knight(type, 1, 1, placeholder);
                        break;
                case B_BISHOP:
                case W_BISHOP:
                        moves_bishop(type, 1, 1, placeholder);
                        break;
                case B_QUEEN:
                case W_QUEEN:
                        moves_queen(type, 1, 1, placeholder);
                        break;
                case B_KING:
                case W_KING:
                        moves_king(type, 1, 1, placeholder);
                        break;
        }
}

// Continously prints the board after each move.
void print_board(int **chessboard)
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
                        if (chessboard[j][i] == EMPTY)
                                printf("  ");
                        else {
                                switch (chessboard[j][i]) {
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
                                }
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

void dealloc_board(int **chessboard)
{
        for (int i = 0; i < 8; ++i) {
                free(chessboard[i]);
        }
}

int main()
{
        ChessPiece *pieces = calloc(32, sizeof(ChessPiece));
        int **chessboard = (int **) malloc(8 * sizeof(int *));
        Point *available_moves = malloc(2 * sizeof(int));

        initialize_chesspieces(pieces);
        initialize_chessboard(chessboard, pieces);
    
        print_board(chessboard);
        while(1) {
                move(chessboard, pieces, available_moves);
                print_board(chessboard);
        }
    
        dealloc_board(chessboard);
        free(chessboard);
        free(pieces);

        return 0;
}
