//
//  grep1.c
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
    int fileDataset, readedBytes;
    int childIn[2], childOut[2];
    char buffer[100];
    
    if(pipe(childIn) == -1 || pipe(childOut) == -1){
        perror("Failed to create parent pipe\n");
        exit(7);
    }
    
    switch(fork()){
        case -1:
            perror("Fork failed: ");
            exit(1);
            
        case 0:{
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
                perror("Fail to close the pipe");
                exit(5);
            }
            
            execlp("grep", "grep", "123", NULL);
            perror("Grep execlp: ");
            exit(4);
        };
        default:
            break;
    }
    
    if(close(childOut[0]) == -1 || close(childIn[1]) == -1){
        printf("Parent is closed: ");
        exit(3);
    }
    
    if((fileDataset = open("cs308a2_grep_data_2", O_RDONLY, 0)) == -1){
        perror("Parent cannot open file: ");
        exit(-1);
    }
    
    while((readedBytes = read(fileDataset, buffer, 80)) != 0){
        if(readedBytes == -1){
            printf("Failed to write: ");
            exit(3);
        }
        
        if(write(childOut[1], buffer, readedBytes) == -1){
            printf("Parent cannot write:  ");
            exit(2);
        }
    }
    
    if(close(fileDataset) == -1 || close(childOut[1]) == -1){
        printf("Parent cannot terminate pipes: ");
        exit(1);
    }
    
    FILE* file = fopen("temp.txt", "w+");
    
    fileDataset = open("temp.txt", O_RDWR);
    
    while((readedBytes = read(childIn[0], buffer, sizeof(buffer))) != 0){
        write(fileDataset, buffer, readedBytes);
    }
    
    int i = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        i++;
    }
    
    printf("This Grep had %d lines matching with given string.\n", i);
    close(childIn[0]);
    return 0;
    
}
