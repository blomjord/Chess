#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 0: White
// 1: Black

#define EMPTY 0

#define W_PAWN 1
#define W_ROOK 2
#define W_KNIGHT 3
#define W_BISHOP 4
#define W_QUEEN 5
#define W_KING 6

#define B_PAWN -1
#define B_ROOK -2
#define B_KNIGHT -3
#define B_BISHOP -4
#define B_QUEEN -5
#define B_KING -6

typedef struct {
    int type, x, y;
    char symbol;
} ChessPiece;

typedef struct {
    int x, y;
} Point;

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
                    printf("Placing %d at %d,%d.\n", pieces[k].type, i, j);
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
ChessPiece *get_piece_by_coords(ChessPiece *pieces, int x, int y) {
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
void move(int **chessboard, ChessPiece *pieces)
{
    int posX, posY, tarX, tarY;
    char pos[3];
    char tar[3];
    
    while (1) {

        printf("Choose pos: \n");
        get_user_input(pos);
        printf("Choose target: \n");
        get_user_input(tar);

        posX = pos[0] - 97;
        posY = pos[1] - 49;
        tarX = tar[0] - 97;
        tarY = tar[1] - 49;
        
        ChessPiece *piece_to_move = get_piece_by_coords(pieces, posX, posY);

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
void available_moves(ChessPiece *pieces, char *pos, int type)
{
    switch (type) {
        case B_PAWN || W_PAWN:
            moves_pawn(type);
            break;
        case B_ROOK || W_ROOK:
            moves_rook(type);
            break;
        case B_KNIGHT || W_KNIGHT:
            moves_knight(type);
            break;
        case B_BISHOP || W_BISHOP:
            moves_bishop(type);
            break;
        case B_QUEEN || W_QUEEN:
            moves_queen(type);
            break;
        case B_KING || W_KING:
            moves_king(type);
            break;
    }
}

// TODO
void moves_pawn(int type, int x, int y)
{
    Point *moves = calloc(8, sizeof(Point);
    if (type < 0) {
        for (int i = 0; i < 8; ++i) {
            moves[i] = Point {x, i};
        }
    } else {
        for (int i = 0; i < 8; ++i) {

        }
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
    
    initialize_chesspieces(pieces);
    initialize_chessboard(chessboard, pieces);
    
    print_board(chessboard);
    while(1) {
        move(chessboard, pieces);
        print_board(chessboard);
    }
    
    dealloc_board(chessboard);
    free(chessboard);
    free(pieces);

    return 0;
}
