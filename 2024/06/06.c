/* Advent of Code - Day 05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// start at "arrow character"
// walk in the direction which the arrow is pointing in
// stop before any # characters
// turn 90°
// repeat until the edge of the map is reached
// count every unique tile that has been visited
#define MAPDIM 130

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
    
    // create matrix
    char input_line[LINELEN];
    int row, col;
    for (row = 0; fgets(input_line, LINELEN, fptr) != NULL; row++) {
        for (col = 0; input_line[col] != '\n' && input_line[col] != '\0'; col++) {
            char_matrix[row][col] = input_line[col];
        }
    }
    fclose(fptr);

    /* #### Part One #### */
    for (int row = 0; row < FILELEN; row++) {
        for (int col = 0; col < FILELEN; col++) {
            if (char_matrix[row][col] == 'X') {

            }
        }
    }
    
    printf("\n\nAnswer 1: %d\n", ans); // correct one

    /* #### Part Two #### */
    ans = 0;
    for (int row = 0; row < FILELEN; row++) {
        for (int col = 0; col < FILELEN; col++) {
            if (char_matrix[row][col] == 'A') {
                // north west -> south east
                if (((char_matrix[row-1][col-1] == 'M' && char_matrix[row+1][col+1] == 'S') ||
                    (char_matrix[row-1][col-1] == 'S' && char_matrix[row+1][col+1] == 'M')) &&
                    row >= 1 && row < FILELEN-1 && col >= 1 && col < FILELEN-1)
                    
                    // south west -> north east
                    if (((char_matrix[row+1][col-1] == 'M' && char_matrix[row-1][col+1] == 'S') ||
                        (char_matrix[row+1][col-1] == 'S' && char_matrix[row-1][col+1] == 'M')) &&
                        row >= 1 && row < FILELEN-1 && col >= 1 && col < FILELEN-1)
                        ans++;
            }
        }
    }
    
    printf("\n\nAnswer 2: %d\n", ans); // correct one

    return 0;
}
