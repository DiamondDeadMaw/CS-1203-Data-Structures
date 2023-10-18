#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void draw(int arr[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Use Unicode block characters to create the chessboard
            if ((i + j) % 2 == 0) {
                printf("▓▓▓▓▓");  // Light block character (U+2593)
            } else {
                printf("░░░░░");  // Dark block character (U+2591)
            }
        }
        printf("\n");

        // Print each row 5 times to create 5x5 squares
        for (int k = 0; k < 2; k++) {
            for (int j = 0; j < 8; j++) {

                if (arr[i][j]==1 && k == 0) {
                    if ((i+j) % 2== 0) {
                        printf("▓▓Q▓▓");
                    } else {
                        printf("░░Q░░");
                    } 
                } else {
                    if ((i + j) % 2 == 0) {
                    printf("▓▓▓▓▓");
                } else {
                    printf("░░░░░");
                }
                }
                
            }
            printf("\n");
        }
    }
}

bool isSafe(int board[8][8], int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (i = row, j = col; i < 8 && j >= 0; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solve(int board[8][8], int col) {
    if (col >= 8) {
        return true; // All queens are placed successfully
    }

    for (int i = 0; i < 8; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solve(board, col + 1)) {
                return true;
            }

            board[i][col] = 0; // Backtrack
        }
    }

    return false; // No safe position found, need to backtrack
}

int main() {
    
    int board[8][8] = {0};
    solve(board, 0);
    draw(board);



    return 0;
}
