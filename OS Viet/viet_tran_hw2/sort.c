//
//  sort.c
//  vtran_hw2
//
//  Created by CS Admin on 10/3/17.
//  Copyright © 2017 Viet Tran Quoc Hoang. All rights reserved.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int childIn[2], childOut[2];
	int fileDataset, readedBytes;
	char buffer[100];
	
	if(pipe(childIn) == -1 || pipe(childOut) == -1){
		perror("Failed to create parent pipe\n");;
		exit(7);
	}
	
	switch(fork()){
		case -1:
			perror("Fork failed: ");
			exit(1);

		case 0:
      if(close(0) == -1) {
        perror("Child close stdout: ");
        exit(6);
      }
      if(dup(childOut[0]) != 0) {
        perror("Child dup stdout: ");
        exit(6);
      }
      if(close(1) == -1){
        perror("Child close stdin: ");
        exit(6);
      }
      if(dup(childIn[1]) != 1){
        perror("Child dup stdin: ");
        exit(6);
      }
      if(close(childIn[0]) == -1 || close(childIn[1]) == -1
         || close(childOut[0]) == -1 || close(childOut[1]) == -1){
        perror("fail to close the pipe");
        exit(5);
      }
		
			execlp("sort", "sort", "-k", "3.3n", "-k", "1.1", "-k", "2.2", NULL);
			perror("Failed execlp: ");
			exit(4);
			
		default:
		break;
	}
	
  if(close(childOut[0]) == -1 || close(childIn[1]) == -1){
	  printf("The parent is closed: ");
	  exit(3);
  }
	
	if((fileDataset = open("cs308a2_sort_data", O_RDONLY, 0)) == -1){
   		perror("Parent cannot open file: ");
    		exit(-1);
  }
	while(readedBytes = read(fileDataset, buffer, 80)){
		if (write(childOut[1], buffer, readedBytes) == -1){
			printf("Parent failed to write: ");
			exit(1);
		}
	}
	
	if (close(childOut[1]) == -1){
		printf("Parent failed to close pipes: ");
		exit(1);
	}
	FILE* file = fdopen(childIn[0], "r");
	int code_count = -1;
	// Number of area code of same number
	int code = 0;
	// Old area code number
	char firstName[20], lastName[20];
    
	int area_code, prefix, telNum;
	
	while(fscanf(file, "%s %s %d %d %d\n", lastName, firstName, &area_code, &prefix, &telNum) != EOF){
	  if (code == 0) {
	    code = area_code;
	    code_count++;
          //first run
	  } 
		
		if(code == area_code){
			code_count++;
			continue;
		} 
		else {
		printf("Area code: %d | Number of people : %5d \n", code, code_count); 
	  code = area_code;
	  code_count = 1;
	  }
	}
	printf("Area code: %d | Number of people : %5d \n", code, code_count);
	fclose(file);
	return 0; 
}
	
