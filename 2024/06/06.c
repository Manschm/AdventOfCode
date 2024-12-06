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
#define MATDIM MAPDIM+2

int check_map(char* input);

char map[MATDIM][MATDIM];

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }
    
    char input_line[MATDIM];
    int start_row = 0;
    int start_col = 0;
    
    // create matrix
    int row, col;
    for (row = 0;  row < MATDIM; row++) {
        fgets(input_line, MATDIM, fptr);
        for (col = 0; col < MATDIM; col++) {
            if (row == 0 || row == MATDIM-1 || col == 0 || col == MATDIM-1) {
                map[row][col] = '0';
            } else {
                map[row][col] = input_line[col];
            }
            if (map[row][col] == '^') {
                start_row = row;
                start_col = col;
            }
        }
    }
    fclose(fptr);

    /* #### Part One #### */
    int ans = 1;
    int dir = 0; // 0: up, 1: right, 2: down, 3: left
    row = start_row;
    col = start_col;
    do {
        switch (dir)
        {
        case 0:
            if (map[row-1][col] != '#')
                row--;
            else
                dir = (dir+1) % 4;
            break;

        case 1:
            if (map[row][col+1] != '#')
                col++;
            else
                dir = (dir+1) % 4;
            break;

        case 2:
            if (map[row+1][col] != '#')
                row++;
            else
                dir = (dir+1) % 4;
            break;

        case 3:
            if (map[row][col-1] != '#')
                col--;
            else
                dir = (dir+1) % 4;
            break;
        
        default:
            break;
        }
        ans += check_map(&map[row][col]);
    } while (map[row][col] != '0');
    
    printf("\n\nAnswer 1: %d\n", ans); // correct one

    return 0;
}

int check_map(char* input) {
    switch (*input)
    {
    case '^':
    case '.':
        *input = 'X';
        return 1;

    case '#':
    case 'X':
    case '0':
    default:
        return 0;
    }
}