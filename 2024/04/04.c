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

    // horizontal, forward
    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);


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
