#include <stdio.h>
#include <stdlib.h>




// 0: White
// 1: Black
typedef struct {
    int team_color, id, x, y;
    char *type;
    char symbol;
} ChessPiece;


void initialize_chesspieces(ChessPiece *pieces) {

    ChessPiece tmp[] = {
    
        // Team White
        { 0, 0,  0, 0, "rook", 'R' },
        { 0, 1,  7, 0, "rook", 'R' },
        { 0, 2,  1, 0, "knight", 'K' },
        { 0, 3,  6, 0, "knight", 'K' },
        { 0, 4,  2, 0, "bishop", 'B' },
        { 0, 5,  5, 0, "bishop", 'B' },
        { 0, 6,  3, 0, "queen", 'Q' },
        { 0, 7,  4, 0, "king", 'K' },
        { 0, 8,  0, 1, "pawn", 'P' },
        { 0, 9,  1, 1, "pawn", 'P' },
        { 0, 10, 2, 1, "pawn", 'P' },
        { 0, 11, 3, 1, "pawn", 'P' },
        { 0, 12, 4, 1, "pawn", 'P' },
        { 0, 13, 5, 1, "pawn", 'P' },
        { 0, 14, 6, 1, "pawn", 'P' },
        { 0, 15, 7, 1, "pawn", 'P' },
        
        // Team Black
        { 1, 16, 0, 7, "rook", 'r' },
        { 1, 17, 7, 7, "rook", 'r' },
        { 1, 18, 1, 7, "knight", 'k' },
        { 1, 19, 6, 7, "knight", 'k' },
        { 1, 20, 2, 7, "bishop", 'b' },
        { 1, 21, 5, 7, "bishop", 'b' },
        { 1, 22, 3, 7, "queen", 'q' },
        { 1, 23, 4, 7, "king", 'k' },
        { 1, 24, 0, 6, "pawn", 'p' },
        { 1, 25, 1, 6, "pawn", 'p' },
        { 1, 26, 2, 6, "pawn", 'p' },
        { 1, 27, 3, 6, "pawn", 'p' },
        { 1, 28, 4, 6, "pawn", 'p' },
        { 1, 29, 5, 6, "pawn", 'p' },
        { 1, 30, 6, 6, "pawn", 'p' },
        { 1, 31, 7, 6, "pawn", 'p' }
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
void initialize_chessboard(char **chessboard, ChessPiece *pieces) {
    for (int i = 0; i < 8; ++i) {
        chessboard[i] = (char *) malloc(8 * sizeof(char));
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 32; ++k) {
                if (pieces[k].x == i && pieces[k].y == j) {
                    chessboard[i][j] = pieces[k].symbol;
                }
            }
        } 
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j > 1 && j < 6) {
                chessboard[i][j] = ' ';
            }
        }
    }
}

void move(char *current_pos, char *target) {
    
    int posX = current_pos[0] - 96;
    int posY = current_pos[1] - 45;
    int tarX = target[0] - 96;
    int tarY = target[1] - 45;

    if (check_move_legal(current_pos, target)) {
        printf("Moving %c%c to %c%c.\n", current_pos[0], current_pos[1], target[0], target[1]);
    } else {
        printf("Illegal move.\n");
    }
}

int check_move_legal(char *current_pos, char *target) {
    return 1;
}

void print_board(char **chessboard) {
    printf("    ");
        for (int i = 97; i < 105; ++i) {
        printf("%c ", i);
    }
    printf("\n");
    for (int i = 0; i < 8; ++i) {
        printf("%d [ ", 8-i);
        for (int j = 0; j < 8; ++j) {
            printf("%c ", chessboard[j][i]);
        }
        printf("] %d\n", 8-i);
    }
    printf("    ");
        for (int i = 97; i < 105; ++i) {
        printf("%c ", i);
    }
    printf("\n");
}

void dealloc_board(char **chessboard) {
    for (int i = 0; i < 8; ++i) {
        free(chessboard[i]);
    }
}
int main() {
    // For ASCII values: Subtract 96 from char letters, and 48 from char
    // numbers.
    printf("ASCII values: Subtract 97 from letter, and 47 from number.\n");
    char *tmp_string = "e4";
    int posX = tmp_string[0] - 96;
    int posY = tmp_string[1] - 48;
    printf("Pos: (%d, %d)\n", posX, posY);
    
    tmp_string = "a1";
    posX = tmp_string[0] - 96;
    posY = tmp_string[1] - 48;
    printf("Pos: (%d, %d)\n", posX, posY);
     
    ChessPiece pieces[32];
    char **chessboard = (char **) malloc(8 * sizeof(char *));
    
    initialize_chesspieces(pieces);
    initialize_chessboard(chessboard, pieces);
    
    print_board(chessboard);
    
    // Function test
    move("e4", "a1");
    
    dealloc_board(chessboard);
    free(chessboard);
    return 0;

}
