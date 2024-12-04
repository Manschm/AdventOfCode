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
    unsigned long ans = 0;

    /* States:
        0: M
        1: U
        2: L
        3: (
        4: n1
        5: ,
        6: n2
        7: )
    */
    int state = 0;

    int n1, n2;
    int digit_count;

    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);

        if (state == 0) {
            n1 = -1;
            n2 = -1;
            digit_count = 0;
        }

        switch (input_char)
        {
        case 'm':
            if (state == 0)
                state++;
            else
                state = 0;
            break;

        case 'u':
            if (state == 1)
                state++;
            else
                state = 0;
            break;

        case 'l':
            if (state == 2)
                state++;
            else
                state = 0;
            break;

        case '(':
            if (state == 3)
                state++;
            else
                state = 0;
            break;

        case ',':
            if (state == 5 || state == 4)
                state = 6;
            else
                state = 0;
            break;

        case ')':
            if (state == 7 || state == 6) {
                if (n1 < 0 || n2 < 0) {
                    state = 0;
                    break;
                }
                ans += n1 * n2;
                printf("%d,%d\n", n1, n2);
            }
            state = 0;
            break;

        default:
            if ((state == 4 || state == 6) && (input_char >= 0x30) && (input_char <= 0x39)) {
                if (state == 4) {
                    if (n1 < 0) {
                        n1 = 0;
                        digit_count = 0;
                    }

                    n1 = (input_char - 0x30) + n1*10;
                    digit_count++;
                    if (digit_count >= 3) {
                        state++;
                        digit_count = 0;
                    }
                } else if (state == 6) {
                    if (n2 < 0) {
                        n2 = 0;
                        digit_count = 0;
                    }

                    n2 = (input_char - 0x30) + n2*10;
                    digit_count++;
                    if (digit_count >= 3) {
                        state++;
                        digit_count = 0;
                    }
                }
            } else {
                state = 0;
            }
            break;
        }
    }
    fclose(fptr);

    printf("\n\nAnswers: %d\n", ans);

    return 0;
}
