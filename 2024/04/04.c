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

    /* State:
     * V  F  B
     * 0  X  S
     * 1  M  A
     * 2  A  M
     * 3  S  X
    */
    int state_f = 0;
    int state_b = 0;

    int state = 0; //TODO: remove

    // create matrix
    char input_line[LINELEN];
    int row, col;
    for (row = 0; fgets(input_line, LINELEN, fptr) != NULL; row++) {
        for (col = 0; input_line[col] != '\n' && input_line[col] != '\0'; col++) {
            char_matrix[row][col] = input_line[col];
        }
    }
    fclose(fptr);

    // horizontal (notepad++: 194 backwards, 213 forwards)
    int ans_h = 0;
    for (int row = 0; row < FILELEN; row++) {
        state_f = 0;
        state_b = 0;
        for (int col = 0; col < FILELEN; col++) {
            switch (char_matrix[row][col])
            {
            case 'X':
                state_f = 1;

                if (state_b == 3)
                    ans_h++;
                state_b = 0;

                break;
                
            case 'M':
                if (state_f == 1)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 2)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'A':
                if (state_f == 2)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 1)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'S':
                if (state_f == 3)
                    ans_h++;
                state_f = 0;

                state_b = 1;

                break;
            
            default:
                state_f = 0;
                state_b = 0;
                break;
            }
        }
    }
    printf("Horizontal: %d\n", ans_h);

    // vertical
    int ans_v = 0;
    for (int col = 0; col < FILELEN; col++) {
        state_f = 0;
        state_b = 0;
        for (int row = 0; row < FILELEN; row++) {
            switch (char_matrix[row][col])
            {
            case 'X':
                state_f = 1;

                if (state_b == 3)
                    ans_v++;
                state_b = 0;

                break;
                
            case 'M':
                if (state_f == 1)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 2)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'A':
                if (state_f == 2)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 1)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'S':
                if (state_f == 3)
                    ans_v++;
                state_f = 0;

                state_b = 1;

                break;
            
            default:
                state_f = 0;
                state_b = 0;
                break;
            }
        }
    }
    printf("Vertical: %d\n", ans_v);

    // diagonal left-right
    int ans_dlr = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 0;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);

        state_f = 0;
        state_b = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'X':
                state_f = 1;

                if (state_b == 3)
                    ans_dlr++;
                state_b = 0;

                break;
                
            case 'M':
                if (state_f == 1)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 2)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'A':
                if (state_f == 2)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 1)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'S':
                if (state_f == 3)
                    ans_dlr++;
                state_f = 0;

                state_b = 1;

                break;
            
            default:
                state_f = 0;
                state_b = 0;
                break;
            }

            row++;
            col++;
        } while (col < 140 && row < 140);
    }
    printf("Diagonal left-right: %d\n", ans_dlr);

    // diagonal right-left
    int ans_drl = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 139;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);
        
        state_f = 0;
        state_b = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'X':
                state_f = 1;

                if (state_b == 3)
                    ans_drl++;
                state_b = 0;

                break;
                
            case 'M':
                if (state_f == 1)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 2)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'A':
                if (state_f == 2)
                    state_f++;
                else
                    state_f = 0;

                if (state_b == 1)
                    state_b++;
                else
                    state_b = 0;

                break;
                
            case 'S':
                if (state_f == 3)
                    ans_drl++;
                state_f = 0;

                state_b = 1;

                break;
            
            default:
                state_f = 0;
                state_b = 0;
                break;
            }

            row++;
            col--;
        } while (col >= 0 && row < 140);
    }
    printf("Diagonal left-right: %d\n", ans_drl);
    

    printf("\n\nAnswers: %d\n", ans_h+ans_v+ans_dlr+ans_drl);

    return 0;
}
