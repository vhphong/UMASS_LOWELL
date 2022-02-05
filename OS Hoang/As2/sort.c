/* Name: Hoang Do
   Student ID: 01521888 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int child_In[2], child_Out[2];
	int fileData = open("cs308a2_sort_data", O_RDONLY, 0);

	int readData;
	char buffer[100];
	int counter = -1;
	int code = 0;
	char fName[20], lName[20];
	int areaCode, midCode, lastCode;


	if(pipe(child_In) == -1 || pipe(child_Out) == -1){
		perror("Failed to create parent\n");;
		exit(7);
	}
	
	switch(fork()){
		case -1:
			perror("Failed to create Child: ");
			exit(1);

		case 0:
		      if(close(0) == -1) {
			perror("Child close error stdout: ");
			exit(3);
		      }
		      if(dup(child_Out[0]) != 0) {
			perror("Child dup error stdout: ");
			exit(3);
		      }
		      if(close(1) == -1){
			perror("Child close error stdin: ");
			exit(3);
		      }
		      if(dup(child_In[1]) != 1){
			perror("Child dup error stdin: ");
			exit(3);
		      }
		      if(close(child_In[0]) == -1 || close(child_In[1]) == -1
			 || close(child_Out[0]) == -1 || close(child_Out[1]) == -1){
			perror("Fail to close Child pipe");
			exit(3);
		      }
				
			execlp("sort", "sort", "-k", "3.3n", "-k", "1.1", "-k", "2.2", NULL);
			perror("Failed execlp: ");
			exit(4);
					
		default:
			break;
	}
	
  	if(close(child_Out[0]) == -1 || close(child_In[1]) == -1){
	  perror("Fail to close the parent\n");
	  exit(3);
  }
	
	if(fileData == -1){
   		perror("Parent failed to open file: ");
    		exit(-1);
  }
	while(readData = read(fileData, buffer, 80)){
		if (write(child_Out[1], buffer, readData) == -1){
			perror("Parent failed to write: ");
			exit(1);
		}
	}
	
	if (close(child_Out[1]) == -1){
		printf("Parent failed to close pipes: ");
		exit(1);
	}

	FILE* file = fdopen(child_In[0], "r");
	
	
	while(fscanf(file, "%s %s %d %d %d\n", lName, fName, &areaCode, &midCode, &lastCode) != EOF){
	  if (code == 0) {
	    code = areaCode;
	    counter++;
	  } 
		
	  if(code == areaCode){
	     counter++;
	     continue;
	  } 
          else {
	  printf("Area code: %d: Number of people : %d\n", code, counter); 
	  code = areaCode;
	  counter = 1;
	  }
	}
	printf("Area code: %d: Number of people : %d\n", code, counter);
	fclose(file);
	return 0; 
}
	
