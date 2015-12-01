// Susie Chac
// Created a function that will calculate the fibonacci numbers and print them out.

int fib(int n)
{
    if(n<0) { // when input is invalid
      return 0; // input is invalid
    } else if(n==0) { // when input is equal to 0
      printf("\n"); // print blank line
      return 1;
    } else { // when input is valid
        int i; // counter for for loop
        int j = 0; // val 1
        int k = 1; // val 2
        int sum; // sum of j and k
    
        for(i=0; i<n; i++) { 
          if(i==0) { // first element
            printf("%d", j); // prints j or 0
            if(n!=1) // when number of fib numbers greater than 1
              printf(" "); // print trailing space
          }else if(i==1) { // second element
            printf("%d", k); // prints k or 1
            if(n!=2) // when number of fib numbers greater than 2
              printf(" "); // print trailing space
          }else if(i!=n-1) { // when not last value
            sum = j + k; // sum of j and k
            printf("%d ", sum); // prints value with trailing space
            if(i%2==0) { // if counter is even
              j = sum; // sets j equal to the sum
            } else { // if counter is odd
              k = sum; // sets k equal to the sum
            }
          }else { // when last value
            sum = j + k; // sum of j and k
            printf("%d", sum); // print last value without trailing space
          }
        }
        printf("\n"); // prints blank line after everything, including n=0
        return 1; //input is valid
    }
}
