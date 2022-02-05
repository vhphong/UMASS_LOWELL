/*******************************************************
  Name: Hung Q Nguyen
  Student ID: 01583193
  Email: Hung_Nguyen3@student.uml.edu
  Date: 2/9/2017
  Assignment 2
*******************************************************/

#import <stdio.h>
#import <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void parentWriteToChild(char* data_filename, char* message_buffer, int old_child[]) {
  int data_signal = open(data_filename, O_RDONLY, 0);
  if (data_signal == -1 ) {
    perror("PARENT PROGRESS: Parent failed to open file\n");
    exit(6);
  }

  long current_data = read(data_signal, message_buffer, 100);

  while (current_data != 0 && current_data != -1) {
    if (write(old_child[1], message_buffer, current_data) == -1) {
        perror("PARENT PROGRESS: Parent failed to write to old child\n");
        exit(6);
    }

    current_data = read(data_signal, message_buffer, sizeof(message_buffer));
  }

  /* close data file and old child after reading the data file*/
  if (close(data_signal) == -1 || close(old_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed close data file\n");
    exit(1);
  }
}

void parentCollectGrepOutput(char* message_buffer, int new_child[]) {
  FILE* fp = fopen("grep.bat", "w+");
  int count = 0;
  int data_signal = open("grep.bat", O_RDWR);

  int current_data = read(new_child[0], message_buffer, sizeof(message_buffer));
  while (current_data != 0 && current_data != -1) {
    write(data_signal, message_buffer, current_data);
    current_data = read(new_child[0], message_buffer, sizeof(message_buffer));
  }

  // after collecting grep data, count many lines contains "123" occurs in the file
  char* tempString = malloc(sizeof(char) * 100);
  while((tempString = fgets(message_buffer, sizeof(message_buffer), fp)) != NULL) {
    if (strstr(tempString, "123") != NULL) {
      count++;
    }
  }
  
  printf("PARENT PROGRESS: Collected %d lines (hits) of grep!\n", count);

  /* close data file and old child after reading the data file*/
  if (close(data_signal) == -1 || close(new_child[0]) == -1) {
    perror("PARENT PROGRESS: Parent failed close child\n");
    exit(1);
  }
}


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("\n***ATTENTION***\n");
    printf("-- To Execute: ./grep data-filename\n\n");
    exit(0);
  }

  /* declare needed variables */
  char* data_filename = *(argv + 1);
  char* msg_buffer;
  int new_child[2], old_child[2];

  /* initializing variables */
  msg_buffer = malloc(sizeof(char) * 100);

  /*creating pipes for each child*/
  if (pipe(new_child) == -1) {
    perror("Failed to create pipe on new child!\n");
    exit(7);
  }

  if (pipe(old_child) == -1) {
    perror("Failed to create pipe on old child!\n");
    exit(7);
  }

  /*
      Since we successfully created pipes
      now we fork and check for each case on the children
  */
  switch(fork()) {
    case -1:
      perror("CHILD PROGRESS: Failed to call fork\n");
      exit(7);
    case 0:
      if (close(0) == -1 || close(1) == -1) {
        perror("CHILD PROGRESS: Failed to close STDIO library!\n");
        exit(10);
      }

      if (dup(old_child[0]) != 0 || dup(new_child[1]) != 1) {
        perror("CHILD PROGRESS: Failed to start STDIO process!\n");
      }

      /* Now child try to close un-used pipes */
      if (close(old_child[0]) == -1 || close(old_child[1]) == -1) {
        perror("CHILD PROGRESS: Old child failed to close pipe\n");
        exit(6);
      }

      if (close(new_child[0]) == -1 || close(new_child[1]) == -1) {
        perror("CHILD PROGRESS: New child failed to close pipe\n");
        exit(6);
      }

      /* 
        Load the grep program at the end
        This line will move to another process so no need to break here
      */
      execlp("grep", "grep", "123", NULL);
    default:
      break;
  }

  // When child has done forking, parent need to shut off their useless pipes
  if (close(old_child[0]) == -1 || close(new_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed to close pipe\n");
    exit(6);
  }

  /*
      Since all process are completed, now we need to read data file
      and hook it up with the old child's process
  */
  parentWriteToChild(data_filename, msg_buffer, old_child);
  parentCollectGrepOutput(msg_buffer, new_child);

  return 0;
}
