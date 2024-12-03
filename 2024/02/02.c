/* Advent of Code - Day 01
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// in total there are 1000 lines (line 1001 is empty)
// a line has at max. 8 numbers
// numbers are either one or two digits long
// there seem to be no numbers with leading zeros and no negative numbers
#define NLINES 1000
#define LINELEN 30

int check_series(int* series, int length);

int err_list[8];
int list_a[8];
int list_b[8];

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }

    char input_line[LINELEN];
    int ans1 = 0;
    int ans2 = 0;

    for (int i = 0; i < NLINES; i++) {
        fgets(input_line, LINELEN, fptr);
        
        int digit_count = 0;
        int num_count = 0;
        int num;
        int nums[8] = {0};

        int j = 0;
        while (j < LINELEN) {
            char c = input_line[j++];
            switch (c)
            {
            case '\n':
            case '\0':
            case ' ': // end of number
                digit_count = 0;
                nums[num_count++] = num;

                if (c == '\n' || c == '\0') {
                    break;
                }
                continue;

            default:
                if (digit_count == 0) {
                    num = 0;
                }
                num = (c - 0x30) + num * 10;
                digit_count++;
                continue;
            }
            break;
        }

        /* #### Part One #### */
        if (check_series(nums, num_count)) {
            ans1++;
            continue;
        }

        /* #### Part Two #### */
    }
    fclose(fptr);

    printf("\n\nAnswers: T1 = %d, T2 = %d, sum = %d\n", ans1, ans2, ans1+ans2);

    return 0;
}

int check_series(int* series, int length) {
    int diff;
    int dir = 0;

    for (int i = 0; i < (length-1); i++) {
        diff = series[i] - series[i+1];
        if (diff == 0 || abs(diff) > 3) {
            return 0;
        }
        diff = (diff > 0) - (diff < 0);
        if (dir != 0 && dir != diff) {
            return 0;
        }
        dir = diff;
    }
    return 1;
}