/*******************************************************                        
  Name: Hung Q Nguyen                                                           
  Student ID: 01583193                                                          
  Email: Hung_Nguyen3@student.uml.edu                                           
  Date: 4/27/2017                                                                
  Assignment 6                         
*******************************************************/
#include "main.h"

int main(int argc, char *argv[]) {
	struct stat st;
  struct dirent* dirent;
  DIR* dir;

  if (argc <= 1) {
  	// no specific files wanted, just need to get the current files in the current directory
  	if((dir = opendir(".")) == NULL){
      printf("Failed to open current directory.\n");
      exit(3);
    } else {
    	while((dirent = readdir(dir)) != NULL) {
      	if(lstat(dirent->d_name, &st) == -1){
        	printf("Failed to list stat structs\n");
        	exit(1);
      	} else {
      		printf("FILENAME: %s\n", dirent->d_name);
	      	printCompleteFileDetail(st);
      	}
    	}
    }
  } else if (argc > 1) {
  	int i;
    for(i = 1; i < argc; i++){
      if(lstat(argv[i], &st) == -1){
				printf("Faile fetching stats at %s", argv[i]);
				exit(2);
      }
      printf("FILENAME: %s\n", argv[i]);      
      printCompleteFileDetail(st);
    }
  }

	return 0;
}

void printCompleteFileDetail(struct stat st) {
	getFileType(st);
	getFilePermission(st);
	getFileOwnerInfo(st);
	getGroupOwnInfo(st);
	getFileDateInfo(st);
	getAllowDevices(st);
}