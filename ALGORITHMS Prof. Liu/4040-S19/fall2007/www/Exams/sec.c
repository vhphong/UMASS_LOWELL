#include <stdio.h>
int A[5] = { 2, 3, 7, 7, 4};

main()
{
  printf("%d\n", no2(A,5));
}

int no2(int A[], int n) // n is the size of A[0..n-1]; n>=2 
{  
  int i, largest, second;

       if (A[0] > A[1]) {
	largest = A[0];
	second = A[1];
       } else {
	largest = A[1];
	second = A[0];
       }
	

      for (i = 2; i < n; i++) {
      	if (A[i] > largest) {
                second = largest;
                largest = A[i];
            } else if (A[i] > second) 
	   second = A[i];	
      }

      return second;
}
