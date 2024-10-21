    /***********************************************************************
     * Name(s)  Kelly Paek                                                 *
     * Assignment name (Homework 4 Calculating Maximum Hourglass)          *
     * Help obtained: Seunghyeon Kim                                       *
     * King, K. N. (2008). C Programming: A Modern Approach . W.W. Norton  *
     * & Company.                                                          *
     * https://eikmeier.sites.grinnell.edu/csc-161-fall-2023/homework/fall-*
     * 2023-homework4.html                                                 *
     * Due Date 11/01                                                      *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     [include textbook(s), CSC 161 labs or readings;                 *
     *       complete citations for Web or other written sources           *
     *      write "none" if no sources used]                               *
     *   Help obtained                                                     *
     *     [indicate names of instructor, class mentors                    *
     *      or evening tutors, consulted according to class policy;        *
     *      write "none" if none of these sources used]                    *
     *     ["none" required for Homework Problems                          *
     *   My/our typed name(s) below confirms that the above list of sources*
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students, tutors) about the solutions              *
     *                                                                     *
     *   Signature:  Kelly Paek                                            *
     ***********************************************************************/
#include <stdio.h>
#include <ctype.h>
#define LEN 6

/*
Function: void hourglass(int * max_sum, int input[LEN][LEN])
          Takes in the address for the variable ('max_sum') that would store the maximum hourglass sum,
          and the input array input[LEN][LEN]
          Calculates and stores the maximum hourglass sum to 'max_sum' based on the input[LEN][LEN]
Precondition: 'max_sum' an address to a variable and 'input' is a double array with height and width LEN.
Postcondition: 'max_sum' is assigned with the maximum hourglass sum value
*/
void hourglass(int * max_sum, int input[LEN][LEN]) {
    int cur_sum;
    for (int i = 0; i < (LEN-2); i++) {
        for (int j = 0; j < (LEN-2); j++) {
            cur_sum = input[i][j] + input[i][j+1] + input[i][j+2] + input[i+1][j+1] + input[i+2][j] + input[i+2][j+1] + input[i+2][j+2];
            if (cur_sum > (* max_sum)) {
                (* max_sum) = cur_sum;
            }
        }
    }
}

int main(void) {
    //Explains the program to the user.
    printf("This program will find the largest hourglass sum of your input.\n");
    printf("Please enter 36 integers in the form of a 6x6 grid, separating each integer with a space and each row with a new line.\n");
    printf("The integers can range from -9 to 9, including 0.\n");
    printf("Example: \n       0 0 0 0 0 0\n       0 0 0 0 0 0\n       0 0 0 0 0 0\n       0 0 0 0 0 0\n       0 0 0 0 0 0\n       0 0 0 0 0 0\n");

    //Scans for user input and stores it in array input_hg
    int input_hg[LEN][LEN];
    //initialize cur_sum to -100, which is impossible to get if inputs are limited from -9 to 9
    int maxhg = -100;
    int inpCount = 0;
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            //Keeps track of the number inputs that are stored correctly
            inpCount += scanf("%d", &input_hg[i][j]);
            //Checks whether each element is within the range
            if (!((input_hg[i][j] >= -9) && (input_hg[i][j] <= 9))) {
                printf("All of the numbers in your input array has to be integers between -9 and 9.\n");
                return 1;
            }
        }
    }
    //Checks whether all of the inputs are stored correctly
    if (inpCount != LEN*LEN) {
        printf("Error: Some of the arguments were either not an integer or was not able to be passed on correctly.\n");
        return 1;
    }
    //Calls function to calculate he maximum hourglass sum.
    hourglass(&maxhg, input_hg);

    //Returns the maximum hourglass sum.
    printf("The largest hourglass sum is: %d\n", maxhg);
}