/* Advent of Code - Day 05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// two input parts
// part 1: xx|yy
// x and y are two digit numbers
// part 2: cc,dd,ee,...
// a bunch of 2 digit numbers seperated by commas
// both parts are seperated by a newline
// x must be printed before y
// part 2 has multiple lines, each line lists the pages to be printed
// check which lines of part two are correct according to the ordering rules from part 1
// get the middle number of each correct line and sum them
#define LINELEN 150
#define NRULES 1176
#define NXS 72

int main() {
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if (fptr == NULL) {
        fclose(fptr);
        return 1; // file doesn't exist
    }

    int ans = 0;
    char input_line[LINELEN];

    // input exploration
    int rule_count;
    int num_count = 0;
    int prev_num = 0;
    for (rule_count = 0; fgets(input_line, LINELEN, fptr) != NULL && input_line[0] != '\n'; rule_count++) {
        int num = (input_line[0] - 0x30) * 10 + (input_line[1] - 0x30);
        if (prev_num != num) {
            prev_num = num;
            num_count++;
        }
    }
    rewind(fptr);
    printf("%d rules in total and %d different X's\n", rule_count, num_count);

    // rule LUT
    unsigned char rules[99-10][99-10] = {0};
    for (int i = 0; i < NRULES; i++) {  // every rule is assumed to be unique
        fgets(input_line, LINELEN, fptr);
        int x = (input_line[0] - 0x30) * 10 + (input_line[1] - 0x30);
        int y = (input_line[3] - 0x30) * 10 + (input_line[4] - 0x30);
        rules[x-10][y-10] = 1;
    }

    // line check
    fgets(input_line, LINELEN, fptr);   // read empty line

    int nums[22];
    int valid;
    for (int i = 0; fgets(input_line, LINELEN, fptr) != NULL; i++) {
        // every line has at max. 68 characters (measured using notepad++)
        // 68/3 = 22.67 --> 23 numbers separated by ',''s max.
        num_count = 0;
        valid = 1;
        for (int j = 0; input_line[j+2] != '\n'; j+=3) {
            int num = (input_line[j] - 0x30) * 10 + (input_line[j+1] - 0x30);
            nums[j/3] = num;

            for (int k = num_count-1; k >= 0; k--) {
                if (rules[num-10][nums[k]-10]) {
                    //printf("line %d is invalid because of rule %d|%d\n", i+2+NRULES, num, nums[k]);
                    valid = 0;
                }
            }
            num_count++;
        }
        if (valid) {
            printf("%d numbers on line %d, middle number is %d\n", num_count, i+2+NRULES, nums[num_count/2]);
            ans += nums[num_count/2];
        }
        
    }

    fclose(fptr);

    
    printf("\n\nAnswer: %d\n", ans);

    return 0;
}
