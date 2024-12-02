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

int check_series(int* series, int length, int* err_series, char print);

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
        
        /* #### Part One/Two #### */
        
        int digit_count = 0;
        int num_idx = 0;
        int num;
        int nums[8] = {0};

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

                nums[num_idx] = num;
                num_idx++;

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

        int errs = check_series(nums, num_idx, err_list, 0);
        if (errs == 0) {
            ans1++;
            continue;

        } else if (errs > 1) {
            printf("\n%3d: ", i);
            check_series(nums, num_idx, err_list, 1);
            continue;
        }

        /* printf("\n%d,", i);
        for (j=0; j<num_idx; j++) {
            printf("%d,", err_list[j]);
        } */

        
        int new_j = 0;
        for (j=0; j<num_idx; j++) {
            if (err_list[j] == 1) {
                if (err_list[j+1] == 1) {
                    list_a[new_j] = nums[j];
                    j++;
                    list_b[new_j] = nums[j];
                } else if (err_list[j+1] == 2) {
                    list_a[new_j] = nums[j];
                    list_b[new_j] = nums[j];
                    new_j++;
                    j += 2;
                    list_a[new_j] = nums[j];
                    list_b[new_j] = nums[j];
                }
            } else {
                list_a[new_j] = nums[j];
                list_b[new_j] = nums[j];
            }
            new_j++;
        }

        //printf("\n%3d: ", i);
        if (check_series(list_a, num_idx-1, err_list, 0) == 0 || check_series(list_b, num_idx-1, err_list, 0) == 0) {
            ans2++;
            /* printf("\n%d,", i);
            for (j=0; j<num_idx; j++) {
                printf("%d,", err_list[j]);
            } */
        } else {
            /* printf("\n%d,", i);
            for (j=0; j<num_idx; j++) {
                printf("%d,", err_list[j]);
            }
            printf("\033[1;0m"); */
        }
    }
    fclose(fptr);

    printf("\n\nAnswers: T1 = %d, T2 = %d, sum = %d\n", ans1, ans2, ans1+ans2);

    return 0;
}

// 49: 30 30 31 32 35 38 41
int check_series(int* series, int length, int* err_series, char print) {
    int old_diff = 0;
    int nerr = 0;
    int err_idx = -1;
    err_series[0] = 0;
    for (int i=1; i<length; i++) {
        int diff = series[i-1] - series[i];
        int diffdir = (diff > 0) - (diff < 0);
        err_series[i] = 0;

        if (i == 1) {
            old_diff = diffdir;
        }

        if (diff == 0 || diff < -3 || diff > 3 || old_diff != diffdir) {
            err_series[i-1]++;
            err_series[i]++;

            if (print) {
                printf("\033[1;31m"); // red
                printf("%d ", series[i-1]);
                printf("\033[1;0m");
            }

            nerr++;
            if (err_idx > 0 && i - err_idx == 1) {
                nerr--;
            } else {
                err_idx = i;
            }
        } else {
            if (print) {
                printf("%d ", series[i-1]);
            }
        }
    }
    if (print) {
        printf("%d\t", series[length-1]);
    }
    return nerr;
}