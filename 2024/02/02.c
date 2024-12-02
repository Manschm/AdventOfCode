/* Advent of Code - Day 01
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// in total there are 1000 lines (line 1001 is empty)
// a line has at max. 8 numbers
// numbers are either one or two digits long
// there seem to be no numbers with leading zeros and no negative numbers
#define NLINES 1000
#define LINELEN 30

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }

    char input_line[LINELEN];
    int ans = 0;

    for (int i = 0; i < NLINES; i++) {
        fgets(input_line, LINELEN, fptr);
        printf("%3d: %s", i, input_line);
        
        /* #### Part One #### */
        int j = 0;
        int k = 0;
        int prev_num = 100;
        int new_num;
        int diff;
        int old_diff = 0;
        int dir;

        //printf("%3d: ", i);
        while (j < LINELEN) {
            char c = input_line[j];
            j++;
            switch (c)
            {
            case '\n':
            case '\0':
            case ' ':   // space
                k = 0;
                if (prev_num == 100) {
                    prev_num = new_num;
                    //printf(" ");
                    continue;
                }
                //printf(" |%2d-%2d=", prev_num, new_num);

                prev_num -= new_num;
                if (prev_num < 0 && prev_num >= -3) {
                    //printf("%d|", prev_num);
                    diff = -1;
                } else if (prev_num > 0 && prev_num <= 3) {
                    //printf("+%d|", prev_num);
                    diff = 1;
                } else {
                    break; // quit loop
                }
                prev_num = new_num;

                if (old_diff != 0 && old_diff != diff) {
                    break; // quit loop
                }
                old_diff = diff;

                if (c == '\n' || c == '\0') {
                    ans++;
                    break;
                }
                //printf(" ");
                continue;

            default:
                //printf("%c", c);
                if (k == 0) {
                    new_num = 0;
                }
                new_num = (c - 0x30) + new_num * 10;
                k++;
                continue;
            }
            break;
        }
        //printf("\n");
    }
    fclose(fptr);

    printf("Answer 1: %d\n", ans);

    return 0;
}
