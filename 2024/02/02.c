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

int check_series(int* series, int length);


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
        
        /* #### Part One/Two #### */
        
        int digit_count = 0;
        int num_idx = 0;
        int num;
        int nums[8] = {0};

        //printf("%3d: ", i);
        int j = 0;
        nums[0] = 100;
        while (j < LINELEN) {
            char c = input_line[j];
            j++;
            switch (c)
            {
            case '\n':
            case '\0':
            case ' ': // end of number
                digit_count = 0;

                if (nums[0] == 100) {  // save first number
                    nums[0] = num;
                    num_idx++;
                    continue;
                }

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

        int errs = check_series(nums, num_idx);
        if (errs == 0) {
            ans++;
            continue;
        } else if (errs > 1) {
            continue;
        }

        int old_diff = 0;
        for (int i=1; i<num_idx; i++) {
            int diff = nums[i-1] - nums[i];
            int diffdir = (diff > 0) - (diff < 0);
 
            if (i == 1) {
                old_diff = diffdir;
            }

            if (diff == 0 || diff < -3 || diff > 3 || old_diff != diffdir) {
                nerr++;
                if (err_idx > 0 && i - err_idx == 1) {
                    nerr--;
                } else {
                    err_idx = i;
                }
            }
        }
        
    }
    fclose(fptr);

    printf("Answer 1: %d\n", ans);

    return 0;
}

int check_series(int* series, int length) {
    int old_diff = 0;
    int nerr = 0;
    int err_idx = -1;
    for (int i=1; i<length; i++) {
        int diff = series[i-1] - series[i];
        int diffdir = (diff > 0) - (diff < 0);

        if (i == 1) {
            old_diff = diffdir;
        }

        if (diff == 0 || diff < -3 || diff > 3 || old_diff != diffdir) {
            nerr++;
            if (err_idx > 0 && i - err_idx == 1) {
                nerr--;
            } else {
                err_idx = i;
            }
        }
    }
    return nerr;
}