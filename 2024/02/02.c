/* Advent of Code - Day 01
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NFALSE 58
int false_lut[] = {5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 94, 104, 119, 130, 137, 138, 142, 143, 149, 159, 228, 248, 250, 270, 292, 313};
int true_lut[] = {0, 1, 2, 3, 4, 9, 20, 49, 74, 79, 99, 124, 125, 126, 127, 128, 133, 198, 223, 249, 252, 256, 259, 262, 278, 284, 326};

// in total there are 1000 lines (line 1001 is empty)
// a line has at max. 8 numbers
// numbers are either one or two digits long
// there seem to be no numbers with leading zeros and no negative numbers
#define NLINES 1000
#define LINELEN 30

int check_series(int* series, int length, int* err_series, char print);
int check_series2(int* series, int length, unsigned char* flags, int* flag_count);

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

        //int errs = check_series(nums, num_idx, err_list, 0);
        unsigned char og_flags[8];
        int og_nerrs = 0;
        int og_check = check_series2(nums, num_idx, og_flags, &og_nerrs);
        if (og_nerrs == 0 && og_check != 0) {
            ans1++;
            for (int lut_idx = 0; lut_idx < NFALSE; lut_idx++) {
                if (i == false_lut[lut_idx]) {
                    printf("\nT1 ERROR: %d is a false positive!\n", i);
                    return 1;
                }
            }
            continue;
        }

        /* printf("\n%d,", i);
        for (j=0; j<num_idx; j++) {
            printf("%d,", err_list[j]);
        }
        */
        
        /* int new_j = 0;
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
        */

        // deduping
        int new_j = 0;
        for (j = 0; j < num_idx; j++) {
            if (og_flags[j] & 0x01 != 0) {
                j++;    // skip dupe
                list_a[new_j] = nums[j];
            } else {
                list_a[new_j] = nums[j];
            }
            new_j++;
        }

        unsigned char flags[8];
        int nerrs = 0;
        int check = check_series2(list_a, new_j, flags, &nerrs);
        if (nerrs == 0 && check != 0) {
            ans2++;
            printf("\n%3da: %s", i, input_line);
            for (int lut_idx = 0; lut_idx < NFALSE; lut_idx++) {
                if (i == false_lut[lut_idx]) {
                    printf("\nT2a ERROR: %d is a false positive!\n", i);
                    return 1;
                }
            }
            continue;
        }

        // edges
        new_j = 0;
        for (j = 0; j < num_idx; j++) {
            if ((og_flags[j] & 0x02 != 0) || (og_flags[j] & 0x04 != 0)) {
                list_a[new_j] = nums[j];
                j++;
                list_b[new_j] = nums[j];
            } else {
                list_a[new_j] = nums[j];
                list_b[new_j] = nums[j];
            }
            new_j++;
        }

        check = check_series2(list_a, new_j, flags, &nerrs);
        if (nerrs == 0 && check != 0) {
            ans2++;
            printf("\n%3db: %s", i, input_line);
            for (int lut_idx = 0; lut_idx < NFALSE; lut_idx++) {
                if (i == false_lut[lut_idx]) {
                    printf("\nT2b ERROR: %d is a false positive!\n", i);
                    return 1;
                }
            }
            continue;
        }
        check = check_series2(list_b, new_j, flags, &nerrs);
        if (nerrs == 0 && check != 0) {
            ans2++;
            printf("\n%3db: %s", i, input_line);
            for (int lut_idx = 0; lut_idx < NFALSE; lut_idx++) {
                if (i == false_lut[lut_idx]) {
                    printf("\nT2b ERROR: %d is a false positive!\n", i);
                    return 1;
                }
            }
            continue;
        }

        // direction
        new_j = 0;
        int diffdir;
        for (j = 0; j < num_idx; j++) {
            if (j+1 < num_idx) {
                diffdir = nums[j] - nums[j+1];
                if ((diffdir < 0 && og_check == 1) || (diffdir > 0 && og_check == -1)) {
                    list_a[new_j] = nums[j];
                    new_j++;
                    j += 2;
                    if (j >= num_idx) {
                        break;
                    }
                    list_a[new_j] = nums[j];
                } else {
                    list_a[new_j] = nums[j];
                }
            } else {
                list_a[new_j] = nums[j];
            }
            new_j++;
        }

        check = check_series2(list_a, new_j, flags, &nerrs);
        if (nerrs == 0 && check != 0) {
            ans2++;
            printf("\n%3dc: %s", i, input_line);
            for (int lut_idx = 0; lut_idx < NFALSE; lut_idx++) {
                if (i == false_lut[lut_idx]) {
                    printf("\nT2c ERROR: %d is a false positive!\n", i);
                    return 1;
                }
            }
            continue;
        }

        //printf("\n%3d: ", i);
        /* if (check_series(list_a, num_idx-1, err_list, 0) == 0 || check_series(list_b, num_idx-1, err_list, 0) == 0) {
            ans2++;
            printf("\n%d,", i);
            for (j=0; j<num_idx; j++) {
                printf("%d,", err_list[j]);
            }
        } else {
            printf("\n%d,", i);
            for (j=0; j<num_idx; j++) {
                printf("%d,", err_list[j]);
            }
            printf("\033[1;0m");
        } */
    }
    fclose(fptr);

    printf("\n\nAnswers: T1 = %d, T2 = %d, sum = %d\n", ans1, ans2, ans1+ans2);

    return 0;
}

// 79: 27 31 29 32 33 36 49 40
// 49: 30 30 31 32 35 38 41
int check_series2(int* series, int length, unsigned char* flags, int* flag_count) {
    int diffsum = 0;
    char dupes = 0;
    flags[0] = 0;   // 0: dupe, 1: rising, 2: falling
    int rise_count = 0;
    int fall_count = 0;
    int flag_count_int = 0;

    for (int i=1; i<length; i++) {
        flags[i] = 0;
        int diff = series[i-1] - series[i];
        diffsum += (diff > 0) - (diff < 0);

        if (diff == 0) {
            dupes++;
            if (dupes > 1) {
                return 0;   // too many dupes
            }
            flags[i]    |= 0x01;    // dupe
            flag_count_int++;

        } else if (diff > 3) {
            flags[i-1]  |= 0x02;
            flags[i]    |= 0x02;
            flag_count_int++;

            if (dupes > 1) {
                return 0;   // too many dupes
            }

            rise_count++;
            fall_count = 0;
            if (rise_count > 1) {
                return 0;   // too many faults
            }

        } else if (diff < -3) {
            flags[i-1]  |= 0x04;
            flags[i]    |= 0x04;
            flag_count_int++;

            if (dupes > 1) {
                return 0;   // too many dupes
            }

            rise_count = 0;
            fall_count++;
            if (fall_count > 1) {
                return 0; // too many faults
            }
        }
    }
    *flag_count = flag_count_int;

    if (length - abs(diffsum) == 1) {   // all values rise in the same direction
        if ((diffsum > 0) - (diffsum < 0)) {
            return 2;
        }
        return -2;
    } else if (length - abs(diffsum) > 2) {
        return 0;   // too many up and downs
    } else if ((diffsum > 0) - (diffsum < 0)) {
        return 1;   // values tend to grow
    } else{
        return -1; // values tend to fall
    }
}

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
        old_diff = diffdir;
    }
    if (print) {
        printf("%d\t", series[length-1]);
    }
    return nerr;
}