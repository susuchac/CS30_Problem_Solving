/*
 * GETINTDRIVER -- program to call an integer reading function
 *
 * Compiling: put the getint function in getint.c, then say:
 * 	gcc -ansi -pedantic -Wall -o getint getintdriver.c getint.c
 *
 * Usage: getint
 *
 * Inputs (from standard input)
 *      -- a line of text
 *      -- EOF to exit
 *      -- special handling of 2246, 2247, 2248, 2249
 * Outputs (to standard output)
 * 	-- a prompt when it expects input
 *	-- outputs indicating the success or failure of the getint call
 *	-- if input is integer 2246, also indicate whether getint() handles
 *		a NULL first argument correctly
 *	-- if input is integer 2247, also indicate whether getint() handles
 *		a NULL second argument correctly
 *	-- if input is integer 2248, also indicate whether getint() handles
 *		a NULL third argument correctly
 *	-- if input is integer 2249, also indicate whether getint() handles
 *		a NULL dereferencing of the third argument correctly
 * Errors (to standard error)
 * 	-- nothing printed
 *
 * Exit Code: 0
 *
 * written for ECS 030, Fall 2015
 * 
 * Matt Bishop, Oct. 28, 2015
 *      original program written
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
 * macros
 *
 * how to test for bogus arguments
 */
#define	BADARG1	2246		/* if read, test handling of NULL first arg */
#define	BADARG2	2247		/* if read, test handling of NULL second arg */
#define	BADARG3	2248		/* if read, test handling of NULL third arg */
#define	BADARG4	2249		/* if read, test handling of NULL dereference for third arg */

/*
 *  prototypes
 */
int getint(char *, int *, char **);	/* function to read an integer */

/*
 * this function calls getint with various illegal parameters
 *
 * Parameter:	int	number to trigger test (or not)
 * 			numbers that do not trigger tests are ignored
 * 			BADARG1		test NULL argument 1
 * 			BADARG2		test NULL argument 2
 * 			BADARG3		test NULL argument 3
 * 			BADARG4		test argument 3 pointing to NULL
 * Returns:	nothing
 * Exceptions:	none
 * Side Effects:	prints a 1-line message identifying the test run and
 * 			giving the success or failure of the test
 */

int getint(char *inputline, int *value, char **nextchar)
{
    /* 
     * checks if parameter values are null
     * returns -1 for invalid input 
     * */
    if (inputline == NULL || value == NULL || nextchar == NULL || *nextchar == NULL) {
        return(-1);
    }

    char* start = inputline; /* pointer to first character of inputline */
    char* plus = inputline; /* pointer index for current character of inputline */

    int before = 0; /* index of last character before reaching first integer */
    int middle = 0; /* index of current character in integer */
    int negative = 0; /* indicates if inputline is negative */

    int turn_second = 0; /* indicates if inputline has integers following a plus sign */

    int  second_num = 0; /* index of second number in inputline */ 
    double total = 0; /* stores *value as a double; doubles are larger than integers */
    *value = 0; /* sets value equal to 0 */

    /*
     * checks that current value of inputline is not a null byte 
     * loops until it reaches a null byte
     */
    while(*inputline != '\0') {  
        /* checks if has leading spaces before reaching the first number, and does nothing */
        if (!before && *inputline == ' ') {  
            
        } else if (!before && (*inputline == '+' || *inputline == '-')) {
            /* checks if inputline has a plus or a minus for the first character */

            /* checks if next character in inputline is not a number */
            if (*(inputline+1) < '0' || *(inputline+1) > '9') {
                /* resets inputline back to original line*/
                inputline = start;
            }
            /* next character in inputline is a number */
            before = 1;
            /* checks if inputline is a negative number */
            if (*inputline == '-') {
                /* variable negative becomes true */
                negative = 1;
            } 
        } else if (*inputline < '0' || *inputline > '9') {
            /* checks if inputline is not a number, and breaks if true */
            break;
        } else if (*inputline >= '0' || *inputline <= '9') {
            /* checks if inputline is a number */

            if (*(inputline+1) == '+' && ( *(inputline+2) >= '0'|| *(inputline+2) <= '9') ) {
                /* checks if next character in inputline is a plus
                 * and if next character after that is a number
                 */

                second_num = 1; /* index of second number */
                turn_second = 1; /* found a second number after plus. true! */
                plus = inputline + 1; /* increments plus to be next character in inputline */
            } else if (*(inputline+1) == '.' && (*(inputline+2) == ' ' || *(inputline +2) == '\0')) {
                /* checks if next character in inputline is a dot
                 * and if next character after that is either a space or a null byte
                 */

                *value = *value * 10 + (*inputline - '0'); /* converts inputline character into an integer and adds it to value */
                total = total * 10 + (*inputline - '0'); /* same as value, but is a double */
                inputline++; /* increments inputline */
                break;
            } else if ((*(inputline+1) < '0' || *(inputline+1) > '9') && *(inputline+1) != '\0' && *(inputline+1) != ' ') {
                /* checks if next character of inputline is not a number and is a null byte */

                middle = 0;
                break;
            } else if (plus != start && (*inputline == ' ' || *inputline == '\0')) {
                /* checks if plus was incremented and inputline is a space or a null byte */
                start = plus;
            }
            if (second_num == 0 || turn_second) {
                middle = 1;
                before = 1;
                *value = *value * 10 + (*inputline - '0');
                total = total * 10 + (*inputline - '0');
            } else {
            }
            if (turn_second == 1) {
                inputline++;
                turn_second = 0;
            }
       }   
       inputline++;
  }
  *nextchar = inputline;
  if (!middle) {
      *nextchar = start;
      *value = 0;
      return 0;
  }
  if (plus != start) {
      *nextchar = plus;
  }
  if (negative) {
      *value *= -1;
      total *= -1;
  }

  // Returns 1 if it's a proper integer.
  if (total > INT_MAX) {
      return 2;
  }
  if (total < INT_MIN) {
      return 3;
  }

  if (*value == BADARG1 || *value == BADARG2 || *value == BADARG3 ||
      *value == BADARG4) {
      return (1);
  }
  return(1);
}
