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

    /* State:
     * 0: X
     * 1: M
     * 2: A
     * 3: S
    */
    int state = 0;

    // horizontal, forward
    int ans1 = 0;
    while ((input_char = fgetc(fptr)) != EOF) {
        switch (input_char)
        {
        case 'X':
            state = 1;
            break;
            
        case 'M':
            if (state == 1)
                state++;
            else
                state = 0;
            break;
            
        case 'A':
            if (state == 2)
                state++;
            else
                state = 0;
            break;
            
        case 'S':
            if (state == 3) {
                ans1++;
            }
            state = 0;
            break;
        
        default:
            state = 0;
            break;
        }
    }
    rewind(fptr);
    printf("Horizontal forward: %d\n", ans1);

    // horizontal, backward
    int ans2 = 0;
    while ((input_char = fgetc(fptr)) != EOF) {
        switch (input_char)
        {
        case 'S':
            state = 1;
            break;
            
        case 'A':
            if (state == 1)
                state++;
            else
                state = 0;
            break;
            
        case 'M':
            if (state == 2)
                state++;
            else
                state = 0;
            break;
            
        case 'X':
            if (state == 3) {
                ans2++;
            }
            state = 0;
            break;
        
        default:
            state = 0;
            break;
        }
    }
    rewind(fptr);
    printf("Horizontal backward: %d\n", ans2);

    char input_line[LINELEN];
    for (int row = 0; fgets(input_line, LINELEN, fptr) != NULL; row++) {
        for (int col = 0; input_line[col] != '\n' && input_line[col] != '\0'; col++) {
            char_matrix[row][col] = input_line[col];
        }
    }
    fclose(fptr);

    // vertical, forward
    int ans3 = 0;
    for (int col = 0; col < FILELEN; col++) {
        for (int row = 0; row < FILELEN; row++) {
            switch (char_matrix[row][col])
            {
            case 'X':
                state = 1;
                break;
                
            case 'M':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'A':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'S':
                if (state == 3) {
                    ans3++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }
        }
    }
    printf("Vertical forward: %d\n", ans3);

    // vertical, backward
    int ans4 = 0;
    for (int col = 0; col < FILELEN; col++) {
        for (int row = 0; row < FILELEN; row++) {
            switch (char_matrix[row][col])
            {
            case 'S':
                state = 1;
                break;
                
            case 'A':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'M':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'X':
                if (state == 3) {
                    ans4++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }
        }
    }
    printf("Vertical backward: %d\n", ans4);

    // diagonal left-right, forward
    int ans5 = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 0;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);
        
        state = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'X':
                state = 1;
                break;
                
            case 'M':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'A':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'S':
                if (state == 3) {
                    ans5++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }

            row++;
            col++;
        } while (col < 140 && row < 140);
    }
    printf("Diagonal left-right forward: %d\n", ans5);

    // diagonal left-right, backward
    int ans6 = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 0;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);
        
        state = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'S':
                state = 1;
                break;
                
            case 'A':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'M':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'X':
                if (state == 3) {
                    ans6++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }

            row++;
            col++;
        } while (col < 140 && row < 140);
    }
    printf("Diagonal left-right backward: %d\n", ans6);

    // diagonal right-left, forward
    int ans7 = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 139;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);
        
        state = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'X':
                state = 1;
                break;
                
            case 'M':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'A':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'S':
                if (state == 3) {
                    ans7++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }

            row++;
            col--;
        } while (col >= 0 && row < 140);
    }
    printf("Diagonal left-right forward: %d\n", ans7);

    // diagonal left-right, backward
    int ans8 = 0;
    for (int start = 139; abs(start) < 140; start--) {
        int row = 0;
        int col = 139;
        if (start > 0)
            col = start;
        else if (start < 0);
            row = abs(start);
        
        state = 0;
        do {
            switch (char_matrix[row][col])
            {
            case 'S':
                state = 1;
                break;
                
            case 'A':
                if (state == 1)
                    state++;
                else
                    state = 0;
                break;
                
            case 'M':
                if (state == 2)
                    state++;
                else
                    state = 0;
                break;
                
            case 'X':
                if (state == 3) {
                    ans8++;
                }
                state = 0;
                break;
            
            default:
                state = 0;
                break;
            }

            row++;
            col--;
        } while (col >= 0 && row < 140);
    }
    printf("Diagonal right-left backward: %d\n", ans8);
    

    printf("\n\nAnswers: %d\n", ans1+ans2+ans3+ans4+ans5+ans6+ans7+ans8);

    return 0;
}
