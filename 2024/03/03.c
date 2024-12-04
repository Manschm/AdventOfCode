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

    /* MUL States:
        0: M
        1: U
        2: L
        3: (
        4: n1
        5: ,
        6: n2
        7: )
    */
    int mul_state = 0;

    /* DO States:
        0: D
        1: O
        2: (
        3: )
        4: N
        5: '
        6: t
        7: (
        8: )
    */
    int do_state = 0;

    int n1, n2;
    int digit_count;
    int do_mul = 1;

    while ((input_char = fgetc(fptr)) != EOF) {
        //putchar(input_char);

        switch (input_char)
        {
        case 'd':
            if (do_state == 0)
                do_state++;
            else
                do_state = 0;
            break;
            
        case 'o':
            if (do_state == 1)
                do_state++;
            else
                do_state = 0;
            break;
            
        case 'n':
            if (do_state == 2)
                do_state = 5;
            else
                do_state = 0;
            break;
            
        case '\'':
            if (do_state == 5)
                do_state++;
            else
                do_state = 0;
            break;
            
        case 't':
            if (do_state == 6)
                do_state++;
            else
                do_state = 0;
            break;
            
        case '(':
            if (do_state == 2 || do_state == 7)
                do_state++;
            else
                do_state = 0;
            break;
            
        case ')':
            if (do_state == 3)
                do_mul = 1;
            else if (do_state == 8)
                do_mul = 0;
            
            do_state = 0;
            break;
        
        default:
            do_state = 0;
            break;
        }

        if (mul_state == 0) {
            n1 = -1;
            n2 = -1;
            digit_count = 0;
        }

        switch (input_char)
        {
        case 'm':
            if (mul_state == 0)
                mul_state++;
            else
                mul_state = 0;
            break;

        case 'u':
            if (mul_state == 1)
                mul_state++;
            else
                mul_state = 0;
            break;

        case 'l':
            if (mul_state == 2)
                mul_state++;
            else
                mul_state = 0;
            break;

        case '(':
            if (mul_state == 3)
                mul_state++;
            else
                mul_state = 0;
            break;

        case ',':
            if (mul_state == 5 || mul_state == 4)
                mul_state = 6;
            else
                mul_state = 0;
            break;

        case ')':
            if (mul_state == 7 || mul_state == 6) {
                if (n1 < 0 || n2 < 0) {
                    mul_state = 0;
                    break;
                }
                if (do_mul)
                    ans += n1 * n2;
                //printf("%d,%d\n", n1, n2);
            }
            mul_state = 0;
            break;

        default:
            if ((mul_state == 4 || mul_state == 6) && (input_char >= 0x30) && (input_char <= 0x39)) {
                if (mul_state == 4) {
                    if (n1 < 0) {
                        n1 = 0;
                        digit_count = 0;
                    }

                    n1 = (input_char - 0x30) + n1*10;
                    digit_count++;
                    if (digit_count >= 3) {
                        mul_state++;
                        digit_count = 0;
                    }
                } else if (mul_state == 6) {
                    if (n2 < 0) {
                        n2 = 0;
                        digit_count = 0;
                    }

                    n2 = (input_char - 0x30) + n2*10;
                    digit_count++;
                    if (digit_count >= 3) {
                        mul_state++;
                        digit_count = 0;
                    }
                }
            } else {
                mul_state = 0;
            }
            break;
        }
    }
    fclose(fptr);

    printf("\n\nAnswers: %d\n", ans);

    return 0;
}
