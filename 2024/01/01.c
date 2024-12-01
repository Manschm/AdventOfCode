/* Advent of Code - Day 01
 * Input: two lists of numbers
 * Process: take n-th largest number of both lists and calculate difference between them
 * Output: sum of differences
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// each line is 13 characters long (not including \r)
// in total there are 1000 lines (line 1001 is empty)
// a line has two numbers each 5 numbers long
// both numbers are separated by 3 spaces
// there seem to be no numbers with leading zeros and no negative numbers
#define NLINES 1000
#define LINELEN 20

void swap(int *x, int *y);

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }

    char input_line[LINELEN];
    int *list_a = malloc(sizeof(int)*NLINES);
    int *list_b = malloc(sizeof(int)*NLINES);

    /* #### Part One #### */
    for (int i = 0; i < NLINES; i++) {
        fgets(input_line, LINELEN, fptr);
        /* 0 1 2 3 4 5 6 7 8 9 10 11 12 13
         * A A A A A S S S B B B  B  B  \r
        */
        list_a[i] = 0;
        list_b[i] = 0;
        for (int j = 0; j <= 4; j++) {
            list_a[i] = (input_line[j]   - 0x30) + list_a[i] * 10;
            list_b[i] = (input_line[j+8] - 0x30) + list_b[i] * 10;
        }
        //printf("%3d: %d   %d\n", i, list_a[i], list_b[i]);

        if (i > 0) {
            int j = 0;
            do {
                if (list_a[i-j] > list_a[i-(j+1)]) {
                    swap(&list_a[i-j], &list_a[i-(j+1)]);
                } else {
                    break;
                }
                j++;
            } while (i-j > 0);

            j = 0;
            do {
                if (list_b[i-j] > list_b[i-(j+1)]) {
                    swap(&list_b[i-j], &list_b[i-(j+1)]);
                } else {
                    break;
                }
                j++;
            } while (i-j > 0);
        }
    }
    fclose(fptr);

    int ans = 0;
    for (int i = 0; i < NLINES; i++) {
        //printf("%3d: %d   %d\n", i, list_a[i], list_b[i]);
        ans += abs(list_a[i] - list_b[i]);
    }
    printf("Answer 1: %d\n", ans);

    /* #### Part Two #### */
    ans = 0;
    for (int i = 0; i < NLINES; i++) {
        int count = 0;
        for (int j = 0; j < NLINES; j++) {
            if (list_a[i] == list_b[j]) {
                count++;
            } else if (count > 0) {
                break;
            }
        }
        ans += list_a[i] * count;
    }
    printf("Answer 2: %d\n", ans);
    
    free(list_a);
    free(list_b);
    return 0;
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}