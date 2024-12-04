/* Advent of Code - Day 03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input contains only letter X, M, A, and S
// every complete XMAS combination must be counted
// the combination can be horizontal, vertical, diagonal, and backwards

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
     * 0: X
     * 1: M
     * 2: A
     * 3: S
    */
    int state = 0;

    int i = 0;
    // horizontal, forward
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
                ans++;
                printf("%4d, i: %d\n", ans, i);
            }
            state = 0;
            break;
        
        default:
            state = 0;
            break;
        }
        i++;
    }
    rewind(fptr);

    // horizontal, backward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // vertical, forward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // vertical, backward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // diagonal left-right, forward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // diagonal left-right, backward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // diagonal right-left, forward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);

    // diagonal right-left, backward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


    }
    rewind(fptr);
    
    fclose(fptr);

    printf("\n\nAnswers: %d\n", ans);

    return 0;
}
