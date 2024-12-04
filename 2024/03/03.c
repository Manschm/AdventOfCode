/* Advent of Code - Day 03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// minput is a massive string
// look for "mul(aaa,bbb)" strings
// a and b are one to three digit numbers
// any partial results are to be discarded
// for every string a and b must be multiplied
// the results are summed and that is the puzzle's answer

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }
    
    int input_char;
    int ans;

    while ((input_char = fgetc(fptr)) != EOF) {
        putchar(input_char);
    }
    fclose(fptr);

    printf("\n\nAnswers: %d\n", ans);

    return 0;
}
