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
    int ans1 = 0;
    int ans2 = 0;
    int diff_list[7];
    int new_nums[8];
    int new_nums_alt[8];
    int err_list[8];

    for (int i = 0; i < NLINES; i++) {
        fgets(input_line, LINELEN, fptr);
        
        int digit_count = 0;
        int num_count = 0;
        int num;
        int nums[8];

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
        int dir = 0;
        for (int i = 0; i < num_count-1; i++) { // calculate diffs
            diff_list[i] = nums[i] - nums[i+1];
            dir += (diff_list[i] > 0) - (diff_list[i] < 0);
        }
        dir = (dir > 0) - (dir < 0);

        // dedupe
        int dupes = 0;
        int new_num_count = 1;
        new_nums[0] = nums[0];
        for (int n = 1; n < num_count; n++) {
            if (diff_list[n-1] == 0) {
                dupes++;
            } else {
                new_nums[new_num_count++] = nums[n];
            }
        }
        if (dupes > 1) {
            continue;
        }
        
        if (check_series(new_nums, new_num_count)) {
            ans2++;
            continue;
        } else if (dupes != 0) {
            continue;
        }

        // The Flattener™
        int jump_count = 0;
        int prev_dir = 0;

        for (int n = 0; n < num_count-1; n++) {
            if (diff_list[n] > 0) {
                if (diff_list[n] > 3) {
                    if (prev_dir != -1) {
                        jump_count++;
                    }
                }

            } else if (diff_list[n] < 0) {
                if (diff_list[n] < -3) {
                    if (prev_dir != 1) {
                        jump_count++;
                    }
                }
            }

            prev_dir = (diff_list[n] > 0) - (diff_list[n] < 0);
        }

        if (jump_count > 1) {
            //printf("%3d: %s", i, input_line);
            continue;
        }

        // The Enforcer™
        int dir_count = 0;

        for (int n = 0; n < num_count-1; n++) {
            if (dir != (diff_list[n] > 0) - (diff_list[n] < 0)) {
                dir_count++;
            }
        }

        if (dir_count > 1) {
            //printf("%3d: %s", i, input_line);
            continue;
        }

        // The Rehibilitator™
        for (int n = 0; n < num_count; n++) {
            err_list[n] = 0;
        }
        for (int n = 0; n < num_count-1; n++) {
            if (abs(diff_list[n]) > 3 || dir != (diff_list[n] > 0) - (diff_list[n] < 0)) {
                err_list[n]++;
                err_list[n+1]++;
            }
        }
        
        int one_count = 0;
        for (int n = 0; n < num_count; n++) {
            if (err_list[n] == 1) {
                one_count++;
            }
        }

        if (one_count > 2) {
            continue;
        }

        new_num_count = 0;
        for (int n = 0; n < num_count; n++) {
            if (n == 0 && err_list[0] && err_list[1] != 2) {    // skip first one
                continue;
            } else if (err_list[n] == 2) {  // skip any 2's
                continue;
            } else if (n == num_count-1 && err_list[n-1] == 2) {   // skip last one if prev. one was a 2
                continue;
            } else if (err_list[n] == 1 && err_list[n-1] == 0) {
                new_nums[new_num_count] = nums[n];
                new_nums_alt[new_num_count] = nums[++n];
            } else {
                new_nums[new_num_count] = nums[n];
                new_nums_alt[new_num_count] = nums[n];
            }
            new_num_count++;
        }

        if (check_series(new_nums, new_num_count) || check_series(new_nums_alt, new_num_count)) {
            //printf("%3d: %s", i, input_line);
            /* printf("%3d, %d: ", i, num_count);
            for (int n = 0; n < num_count; n++) {
                printf("%d ", err_list[n]);
            }
            printf("\t%s", input_line); */
            ans2++;
            continue;
        }

        printf("%3d, %d: ", i, num_count);
        for (int n = 0; n < num_count; n++) {
            printf("%d ", err_list[n]);
        }
        printf("\t%s", input_line);

        
       

        //printf("%3d: %s", i, input_line);

        
        /* printf("%3d: ", i);
        for (int n = 0; n < new_num_count; n++) {
            printf("%d ", new_nums[n]);
        }
        printf("\t%s", input_line); */
        

    }
    fclose(fptr);

    printf("\n\nAnswers: T1 = %d, T2 = %d, sum = %d\n", ans1, ans2, ans1+ans2);

    return 0;
}


int check_series(int* series, int length) {
    int diff;
    int dir = 0;

    for (int i = 0; i < length-1; i++) {
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