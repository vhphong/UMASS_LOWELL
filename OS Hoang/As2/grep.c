/* Name: Hoang Do
   Student ID: 01521888 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    char* fileName = *(argv + 1);;
    int fileData = open(fileName, O_RDONLY, 0);
    char buffer[100];
    int readData;
    int child_In[2], child_Out[2];
    int counter = 0;

    
    if (argc != 2){
	printf ("\nPlease enter the data filename\n");
    }

    if(pipe(child_In) == -1 || pipe(child_Out) == -1){
        perror("Failed to create parent pipe\n");
        exit(7);
    }
    
    switch(fork()){
        case -1:
            perror("Failed to create Child: ");
            exit(1);
            
        case 0:{
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
            
            execlp("grep", "grep", "123", NULL);
            exit(4);
        };
        default:
            break;
    }
    
    if(close(child_Out[0]) == -1 || close(child_In[1]) == -1){
        printf("Fail to close the parent\n");
        exit(3);
    }
    
    if(fileData  == -1){
        perror("Parent cannot open file: ");
        exit(-1);
    }
    
    while((readData = read(fileData, buffer, 80)) != 0 && readData != -1){      
        if(write(child_Out[1], buffer, readData) == -1){
            printf("Parent failed to write:  ");
            exit(2);
        }
    }
    
    if(close(fileData) == -1 || close(child_Out[1]) == -1){
        printf("Parent failed to close data: ");
        exit(1);
    }
    
    FILE* file = fopen("grepTemp.txt", "w+");
    
    fileData = open("grepTemp.txt", O_RDWR);
    
    while((readData = read(child_In[0], buffer, sizeof(buffer))) != 0){
        if (write(fileData, buffer, readData) == -1){
		printf ("Error while write to the grep temp file\n");
		exit (6);
	}
    }
    
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        counter++;
    }
    
    printf("The Grep returns %d lines.\n", counter);
    fclose(file);;
    close(child_In[0]);
    return 0;
    
}
