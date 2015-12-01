// Susie Chac
// FALL Quarter 2015.

#include <stdio.h>
#include <stdlib.h>

// Learned how to write prototypes and print out numbers between a range. 
// Had to determine whether or not if it needed to be incremented or
// decremented.

// Function prototypes
void printNumbers(int a, int b, int c);

int main(void) {
  int start_pt, end_pt, inc;
  printf("Starting point: ");
  scanf("%d", &start_pt);
  printf("Ending point: ");
  scanf("%d", &end_pt);
  printf("Increment: ");
  scanf("%d", &inc);
  printNumbers(start_pt, end_pt, inc);
  exit(0);
}

void printNumbers(int start, int end, int increment) {
  int count;
  if(start < end && increment <= 0) {
    fprintf(stderr, "Increment must be > 0 if begin < end\n");
    exit(1);
  } else if(start > end && increment >= 0) {
    fprintf(stderr, "Increment must be < 0 if begin > end\n");
    exit(1);
  } else {
    if(increment > 0) {
      for(count = start; count <= end; count+=increment) {
        printf("%d", count);
        if (count + increment <= end) { 
          printf(" ");
        }
      }
    } else if(increment < 0) {
      for(count = start; count >= end; count+=increment) {
        printf("%d", count);
        if (count + increment >= end) { 
          printf(" ");
        }
      }
    } else {
      // if starting point = ending point & increment = 0
      printf("%d", start);
    }
    printf("\n");
  }
}
