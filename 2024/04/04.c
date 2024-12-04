/* Advent of Code - Day 03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input contains only letter X, M, A, and S
// every complete XMAS combination must be counted
// the combination can be horizontal, vertical, diagonal, and backwards
#define LINELEN 150
#define FILELEN 140

char char_matrix[140][140];

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }
    
    int input_char;
    int ans = 0;

    /* #### Part One #### */
    for (int row = 0; row < FILELEN; row++) {
        for (int col = 0; col < FILELEN; col++) {
            if (char_matrix[row][col] == 'X') {
                // forward
                if (char_matrix[row][col+1] == 'M' &&
                    char_matrix[row][col+2] == 'A' &&
                    char_matrix[row][col+3] == 'S' &&
                    col < FILELEN-3)
                    ans++;
                
                // back
                if (char_matrix[row][col-1] == 'M' &&
                    char_matrix[row][col-2] == 'A' &&
                    char_matrix[row][col-3] == 'S' &&
                    col >= 3)
                    ans++;

                // up
                if (char_matrix[row+1][col] == 'M' &&
                    char_matrix[row+2][col] == 'A' &&
                    char_matrix[row+3][col] == 'S' &&
                    row < FILELEN-3)
                    ans++;
                
                // down
                if (char_matrix[row-1][col] == 'M' &&
                    char_matrix[row-2][col] == 'A' &&
                    char_matrix[row-3][col] == 'S' &&
                    row >= 3)
                    ans++;

                // north east
                if (char_matrix[row-1][col+1] == 'M' &&
                    char_matrix[row-2][col+2] == 'A' &&
                    char_matrix[row-3][col+3] == 'S' &&
                    row >= 3 &&
                    col < FILELEN-3)
                    ans++;

                // south east
                if (char_matrix[row+1][col+1] == 'M' &&
                    char_matrix[row+2][col+2] == 'A' &&
                    char_matrix[row+3][col+3] == 'S' &&
                    row < FILELEN-3 &&
                    col < FILELEN-3)
                    ans++;

                // south west
                if (char_matrix[row+1][col-1] == 'M' &&
                    char_matrix[row+2][col-2] == 'A' &&
                    char_matrix[row+3][col-3] == 'S' &&
                    row < FILELEN-3 &&
                    col >= 3)
                    ans++;

                // north west
                if (char_matrix[row-1][col-1] == 'M' &&
                    char_matrix[row-2][col-2] == 'A' &&
                    char_matrix[row-3][col-3] == 'S' &&
                    row >= 3 &&
                    col >= 3)
                    ans++;
            }
        }
    }
    
    printf("\n\nAnswer: %d\n", ans); // correct one

    return 0;
}
