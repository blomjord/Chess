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
        
        // Black
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
        { 1, 31, 7, 6, "pawn", 'p' },
        
        // White
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
        { 0, 15, 7, 1, "pawn", 'P' }
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

ChessPiece *get_piece_by_coords(ChessPiece *pieces, int x, int y) {
    for (int i = 0; i < 32; ++i) {
        if (pieces[i].x == x && pieces[i].y == y) {
            return &pieces[i];
        }
    }
    return NULL;
}

// Performs move if legal.
void move(char **chessboard, ChessPiece *pieces, char *current_pos, char *target) {
    
    int posX = current_pos[0] - 97;
    int posY = current_pos[1] - 49;
    int tarX = target[0] - 97;
    int tarY = target[1] - 49;
    ChessPiece *piece_to_move = get_piece_by_coords(pieces, posX, posY);

    piece_to_move->x = tarX;
    piece_to_move->y = tarY;

    printf("Attemting move: %c%c > %c%c\n", posX, posY, tarX, tarY);
    chessboard[tarX][tarY] = piece_to_move->symbol;
    chessboard[posX][posY] = ' ';
}

int check_move_legal() {
    return 1;
}

// Continously prints the board after each move.
void print_board(char **chessboard) {
    printf("    ");
        for (int i = 97; i < 105; ++i) {
        printf("%c ", i);
    }
    printf("\n");
    for (int i = 7; i > -1; --i) {
        printf("%d [ ", i + 1);
        for (int j = 0; j < 8; ++j) {
            printf("%c ", chessboard[j][i]);
        }
        printf("] %d\n", i + 1);
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
     
    ChessPiece pieces[32];
    char **chessboard = (char **) malloc(8 * sizeof(char *));
    
    initialize_chesspieces(pieces);
    initialize_chessboard(chessboard, pieces);
    
    print_board(chessboard);
    while(1) {
        char pos[3];
        char tar[3];
        printf("Choose pos: \n");
        scanf("%2s", pos);
        printf("Move to: \n");
        scanf("%2s", tar);
        move(chessboard, pieces, pos, tar);
        print_board(chessboard);

    }
    
    
    dealloc_board(chessboard);
    free(chessboard);
    return 0;

}
