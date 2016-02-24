/*
*   WORDS -- creates a linked list of words in 1 or more files,
*   and counts the number of occurences of each word
*
*   Usage: to print all the words in files with their number of occurences
*
*   Inputs: User inputs the executable followed by file names
*   Outputs: A list of all the words in the files, in ASCII order;
*            Each word is preceded by its number of occurences in the files
*   Exit Code: exit(0) if no errors resulted from program execution
*              exit(1) otherwise
*
*   written for ECS 030, Fall 2015
*
*   Susie Chac, Dec. 3, 2015
*    original program written
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*   Node structure of linked list;
*   Stores a word, its number of occurrences,
*   and the next word it is pointing to
*/
struct Node
{
    int occurences;     /* number of occurences of the word */
    char *word;         /* word from the file */
    struct Node *next;  /* next value in the linked list that word points to */
};

/*
*   Check if two strings are equal;
*   Compares strings character by character;
*   Strings of different lengths are not equal
*
*   parameters:     char *str1  string to compare against str2
*                   char *str2  string to compare against str1
*
*   returns: int    1           success!
*                   0           failure
*   exceptions:     none
*/
int isEqual(char *str1, char *str2)
{
    if(strlen(str1) == strlen(str2)) {
        int i = 0;  /* index of character to compare */
        while(i!=strlen(str1)) {
            /*
            *   check that the characters being compared are equal;
            *   increments character index if true,
            *   returns 0 and exits if false
            */
            if(str1[i] == str2[i]) {
                i++;
            } else {
                return(0);
            }
        }
        return(1);
    }
    /* returns 0 and exits if strings of different lengths */
    return(0);
}

/*
*   Check if str1 belongs before str2 in the linked list;
*   Compares strings character by character
*
*   parameters:     char *str1  string to compare against str2
*                   char *str2  string to compare against str1
*
*   returns:        1           success!
*                   0           failure
*   exceptions:     none
*/
int compareStrings(char *str1, char *str2)
{
    if(strlen(str1) != strlen(str2)) {
        int i = 0;  /* index of characters being compared */
        int len;    /* length of the longer string */
        /* Compares string lengths and sets len equal to longer length */
        if(strlen(str1) > strlen(str2)) {
            len = strlen(str1);
        } else {
            len = strlen(str2);
        }
        /*
        *   Check if str1 char has smaller ASCII value than str2 char;
        *   increments character index if ASCII values are equL
        *   returns 1 if true
        *           0 if false
        */
        while(i < len) {
            if(str1[i] < str2[i]) {
                return(1);
            } else if(str1[i] == str2[i]) {
                i++;
            } else {
                return(0);
            }
        }
    } else {
        int i = 0;  /* index of characters being compared */
        /* str1 and str2 have the same string length */
        while(i != strlen(str1)) {
            if(str1[i] < str2[i]) {
                return(1);
            } else if(str1[i] == str2[i]) {
                i++;
            } else {
                return(0);
            }
        }
    }
    return(1);
}

/*
*   Inserts a word into the linked list
*
*   parameters:     struct Node* head       pointer to head of linked list
*                   char *new_word          word to add to linked list
*                   char *fnane             name of file being processed
*                   int line_no             line number being processed
*   returns:        struct Node* head       head of the linked list
*                   struct Node* new_node   head of list if first Node
*   exceptions:     exit(1)                 malloc out of space to allocate
*                                           for struct that holds new_node, OR
*                                           malloc out of space to allocate
*                                           for struct that holds new_node->word
*/
struct Node* Insert(struct Node* head, char *new_word, char *fname, int line_no)
{
    /*
    *   Check if list is initially empty;
    *   Creates a Node and allocates space to hold new_node;
    *   Creates a Node and allocates space to hold new_word
    */
    if(head == NULL) {
        struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
        /* Check if space not allocated, and exit(1) if true */
        if(new_node == NULL) {
            exit(1);
        }
        new_node->word = (char*) malloc(sizeof(char)*(strlen(new_word)+1));
        /*
        *   Check if space not allocated;
        *   Print error message, word, file name, and line number,
        *   and exit(1) if true
        */
        if(new_node->word == NULL) {
            printf("%s, file %s, line %d: ran out of memory\n",
                    new_node->word, fname, line_no);
            exit(1);
        }
        /* new_node->word is set equal to new_word */
        strcpy(new_node->word, new_word);
        /* only 1 occurence so far */
        new_node->occurences = 1;
        /* only 1 Node in list, so first and last Node in list, next is NULL */
        new_node->next = NULL;
        return new_node;
    }
    /* Check if new_word belongs before head of linked list */
    if(compareStrings(head->word, new_word) == 0) {
        struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
        if (new_node == NULL) {
            exit(1);
        }
        new_node->word = (char*) malloc(sizeof(char)*(strlen(new_word)+1));
        if(new_node->word == NULL) {
            printf("%s, file %s, line %d: ran out of memory\n", new_node->word, fname, line_no);
            exit(1);
        }
        strcpy(new_node->word, new_word);
        new_node->occurences = 1;
        new_node->next = head;
        return new_node;
    }
    /* var to increment through linked list */
    struct Node* current = head;
    /*
    *   Check if current Node is not last in list;
    *   Inserts new_word in between two nodes or increments occurences
    */
    while(current->next != NULL) {
        /*
        *   Check if current->word is equivalent to new_word,
        *   increments occurences if true;
        *   el check if new_word belongs b/w current->word and current->next,
        *   returns head if true and no error in memory allocation;
        *   else increment current
        */
        if(isEqual(current->word, new_word)) {
            current->occurences++;
            return head;
        } else if(compareStrings(current->word, new_word)
                && compareStrings(current->next->word, new_word)==0) {
            struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
            if (new_node == NULL) {
                exit(1);
            }
            new_node->word = (char*) malloc(sizeof(char)*(strlen(new_word)+1));
            if(new_node->word == NULL) {
                printf("%s, file %s, line %d: ran out of memory\n", new_node->word, fname, line_no);
                exit(1);
            }
            strcpy(new_node->word, new_word);
            new_node->occurences = 1;
            new_node->next = current->next;
            current->next = new_node;
            return head;
        } else {
            current = current->next;
        }
    }
    /* Check if current Node is last in linked list */
    if(current->next == NULL) {
        if(isEqual(current->word, new_word)) {
            current->occurences++;
        } else if(compareStrings(current->word, new_word)) {
            struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
            if (new_node == NULL) {
                exit(1);
            }
            new_node->word = (char*) malloc(sizeof(char)*(strlen(new_word)+1));
            if(new_node->word == NULL) {
                printf("%s, file %s, line %d: ran out of memory\n", new_node->word, fname, line_no);
                exit(1);
            }
            strcpy(new_node->word, new_word);
            new_node->occurences = 1;
            new_node->next = NULL;
            current->next = new_node;
        }
    }
    /* successfully inserted Node! */
    return head;
}

/*
*   Prints out all the words in the linked list, preceded by their occurences
*
*   parameter:     struct Node* head   head of the linked list
*   return:        nothing (void)
*   exceptions:     none
*/
void readList(struct Node* head)
{
    /* var to increment through linked list */
    struct Node* current = head;
    /*
    *   loops until current reaches the last Node in the linked list,
    *   Prints word and occurences if true,
    *   Then increments current
    */
    while(current != NULL) {
        printf("%5d %s\n", current->occurences, current->word);
        current = current->next;
    }
}

/*
*   main routine:
*   separates words in files and inserts into linked list
*
*   parameters:     int argc        number of arguments inputted by user
*                   char** argv     pointer to the arguments
*   exceptions:     exit(1)         perror(arg) when file cannot be read
*/
int main(int argc, char** argv)
{
    /* linked list, initialized to NULL */
    struct Node* list = NULL;
    /* error flag: 1 if error, 0 if no error */
    int flag_error = 0;
    /*
    *   Check if user inputted more than 1 argument,
    *   Loops through arguments and opens files
    */
    if(argc > 0) {
        FILE *fp;   /* Points to current file being read */
        int i;      /* index of current argument */
        /* index starts at 1 because first arg is executable */
        for (i = 1; i < argc; ++i) {
            fp = fopen(argv[i], "r");
            /* Check if file cannot be read (=NULL) */
            if(fp == NULL) {
                /* prints error if file cannot be read */
                perror(argv[i]);
                /* changes error flag to 1 (true) */
                flag_error = 1;
            } else {
                char line[2048];    /* array to hold line w/ max length 2048 */
                int line_no = 1;    /* current line number being processed */
                /* fgets grabs each line and puts it in line until NULL */
                while(fgets(line, 2048, fp)) {
                    /* holds all the delimiters for chars and special chars */
                    char delimit[] = " \t\r\n\v\f~`!@#$^&*()-_=+[{]}|\\;:\"'<>?,./";
                    char *single_word;  /* pointer to hold one word from line */
                    /* single_word = first string of chars separated by delimiters */
                    single_word=strtok(line,delimit);
                    while(single_word != NULL) {
                        /* inserts word into the linked list */
                        list = Insert(list, single_word, argv[i], line_no);
                        /* sets single_word equal to NULL after insertion */
                        single_word = strtok(NULL, delimit);
                    }
                    /* moves onto the next line */
                    line_no++;
                }
            }
        }
        /* prints out the linked list */
        readList(list);
    }
    /*
    *   if flag_error = 1, exit(1);
    *   else exit(0)
    */
    flag_error ? exit(1):exit(0);
}
