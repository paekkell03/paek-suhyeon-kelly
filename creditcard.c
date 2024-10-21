    /***********************************************************************
     * Name(s)  Kelly Paek                                                 *
     * Assignment name (Homework 2 Calculating Credit Card Interest)       *
     * Help obtained: Seunghyeon Kim                                       *
     * King, K. N. (2008). C Programming: A Modern Approach . W.W. Norton  *
     * & Company.                                                          *
     * https://eikmeier.sites.grinnell.edu/csc-161-fall-2023/homework/fall-*
     * 2023-homework2.html                                                 *
     * Due Date 9/22                                                       *
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
     *   Signature:  Kelly Paek                                            *                                                                               *
     ***********************************************************************/

# include <stdio.h>
# include <math.h>

//day30: Returns true if the number given is either 4, 6, 9, or 11 (months that have 30 days)
//Precondition: month must be an integer
//Postcondition: returns a boolean (#t or #f)
int day30 (int month){
    return ((month = 4) || (month = 6) || (month = 9) || (month = 11));
}

//daysCalc: Returns 30 if day3(month) is true, 28 if month is 2, and 31 if day30(month) is not true.
//Precondition: month must be an integer
//Postcondition: returns an integer (days in the given month)
int daysCalc(int month){
    int days = 0;
    if (day30(month)) {
        days = 30;
    } else if(month == 2){
        days = 28;
    } else if (!day30(month)) {
        days = 31;
    }
    return days;
}

//dpr: Calculates the dpr (daily percent rate) based on the given apr (annual percent rate)
//Precondition: apr is a double
//Postcondition: returns a double, dpr
double dpr (double apr) {
    return apr / 365.0;
}

int main(void) {
//Defines and initializes values needed for further procedures.
    int i = 0, days = 0, month;
    double initial_balance, APR, monthly_minimum, balance = 0.0, interest = 0.0, total = 0.0;

//Prompt for user to enter their initial balance, percentage rate, monthly minimum payment, and starting month.
    printf ("Please enter your initial balance, annual percentage rate (in decimal from 0 to 1), monthly minimum payment, and your starting month (in number) in order. \n");
    scanf ("%lf %lf %lf %d", &initial_balance, &APR, &monthly_minimum, &month);

//Error messages for when initial balance is less than 0, APR is not a number between 0 and 1, monthly minimum is less than 0, and the starting month is not a number between 1 to 12.
    if (initial_balance <= 0) {
        printf ("Your initial balance cannot be less than or equal to zero. \n");
        return 1;
    }

    if ((APR <= 0) || (APR >= 1)) {
        printf ("Please enter your annual percentage rate as a decimal number (from 0 to 1). \n");
        return 1;
    }

    if (monthly_minimum <= 0) {
        printf ("Your monthly minimum payment cannot be less than or equal to zero. \n");
        return 1;
    }

    if ((month <= 1) || (month > 12)) {
        printf ("Your starting month has to be between 1 to 12 (January to December). \n");
        return 1;
    }

//Initializes balance as initial balance (will be updated later after each month).
    balance = initial_balance;

    printf ("Cycle	Month	Interest	Payment    Balance\n");

/*
  As long as the balance is more than or equal to the monthly minimumL
    - Uses modulo to renew the month after each cycle, ensuring that the month does not go over 12
    - Calculate the days in the month and use it to calculate the interest based on APR and current balance
    - Updates balance by adding interest and subtracting monthly minimum
    - Increments month every cycle
    - Adds up the total payment
    - Prints a line of Cycle Month Interest	Payment Balance to add on to the table
*/
    for (i = 0; balance >= monthly_minimum; i++) {
        days = daysCalc(month);
        interest = dpr(APR) * days * balance;
        balance += (interest - monthly_minimum);
        printf ("%3d%8d%11.2lf%16.2lf%11.2lf \n", i, month, interest, monthly_minimum, balance);
        month++;
        total += monthly_minimum;
        month = (month - 1) % 12 + 1;
    }

/*
  Once the balance is less than the monthly minimum:
    - Update the month and calculate the interesnt once again
    - This time, the balance is the current balance + interest - monthly minimum
    - Print the last line of the table
*/
    month = (month - 1) % 12 + 1;
    days = daysCalc(month);
    interest = dpr(APR) * days * balance;
    total += (interest + balance);
    printf ("%3d%8d%11.2lf%16.2lf%11.2lf \n", i, month, interest, balance, 0.00);

//Prints final statement that summarizes the total months passed and total amount paid for the initial balance to run out on the credit card.
    printf ("After %d months, you paid $%.2lf on an initial balance of $%.2lf.\n", i+1, total, initial_balance);
    return 0;
}