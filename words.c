// Author: Susie Chac
// FQ 2015
// 
// Checks if a word is alphanumberical based off of the user's input.
// Used fgets to get the word.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros.
#define MAX_INPUT_LEN 100

// Function prototypes
int isAlphanumerical(int letter);

int main(void) {
  char words[MAX_INPUT_LEN];
  int line = 0;
  // Ctrl + D is EOF
  while(fgets(words, MAX_INPUT_LEN, stdin)!=NULL) {
    int i;
    int marker = 0;
    line++;
    for(i=0; i<strlen(words); i++) {
      if(!(isAlphanumerical(words[i]))) {
        int j;
        if(i-marker!=0) {
          printf("%d\t", line);
          for(j= marker; j<i; j++) {
             printf("%c", words[j]);
          }
          printf("\n");
        }
        marker = i+1;
      } 
    }
  }
}

int isAlphanumerical(int letter) {
  if((letter>='A' && letter<='Z') || (letter>='a' && letter<='z') || (letter>='0' && letter<='9')) {
    return 1;
  } 
  return 0;
}
