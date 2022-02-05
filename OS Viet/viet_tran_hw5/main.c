/* Assignment 5: Main
	- Name: Viet Tran
	- E-mail: viet_tran1@student.uml.edu
	- Reference: http://www.cs.uml.edu/~bill/cs308/Assignment_5_data_structs.txt */

#include "main.h"

int main(int argc, char *argv[]){

  /* Check to see if they have the correct number of args */
  if(!argc > 3){
    printf("\nYou must provide the following arguments"); 
    printf("\npolicy, total memory free pool size, name of file containg requests");
    printf("\nExample: ./a.out best 1024 proj5_data > output.txt");
    
    printf("\nYou only provided %d arguements.", argc);

    exit(2);
  }

  /* break up arg vectors */
  int mem = atoi(argv[2]);

  /* call best fit */
  if(strcmp(argv[1], "best") == 0){
    bestFit(mem, argv[3]);
  }
  
  /* call first fit */
  if(strcmp(argv[1], "first") == 0){
     firstFit(mem, argv[3]);
  }

  /* call buddy system */
  if(strcmp(argv[1], "buddy") == 0){
    buddySys(mem, argv[3]); 
  }

  return 0;
}
