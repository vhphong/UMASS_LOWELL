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
  int current_data;

  int data_signal = open(data_filename, O_RDONLY);
  dup2(data_signal, 0);

  if (data_signal == -1 ) {
    perror("PARENT PROGRESS: Parent failed to open file\n");
    exit(6);
  }

  while ((current_data = read(data_signal, message_buffer, 50))) {
    if (write(old_child[1], message_buffer, current_data) == -1) {
      perror("PARENT PROGRESS: Parent failed to write to old child\n");
      exit(6);
    }
  }

  /* close data file and old child after reading the data file*/
  if (close(data_signal) == -1 || close(old_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed close data file\n");
    exit(1);
  }
}

void parentCollectInput(int new_child[]) {
  // define variables for input type
  char* first_name = malloc(sizeof(char) * 100);
  char* last_name = malloc(sizeof(char) * 100);
  int area_code, prefix_code, calling_code;

  int area_list[1000];
  memset(area_list, 0, sizeof(area_list));

  FILE* fp = fdopen(new_child[0], "r");

  while(fscanf(fp, "%s %s %d %d %d\n", last_name, first_name, &area_code, &prefix_code, &calling_code) != EOF) {
    area_list[area_code]++;
  }

  // print out the value
  int i;
  for(i = 0; i < 1000; i++) { 
    if (area_list[i] != 0) {
        printf("Area Code %d: %d\n", i, area_list[i]);
    }
  }
}

int main() {
  // Since this sort only sort from one single data file
  // so no need to read data file name from the command
  char* data_filename = "sort_data";
  char* msg_buffer;
  int new_child[2], old_child[2];

  /* initializing variables */
  msg_buffer = malloc(sizeof(char) * 512);

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
        Load the sort program at the end
        This line will move to another process so no need to break here
      */
      execlp("sort", "sort", "-k", "3.3n", "-k", "1.1", "-k", "2.2", NULL);
    default:
      break;
  }

  // When child has done forking, parent need to shut off their pipes
  if (close(old_child[0]) == -1 || close(new_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed to close pipe\n");
    exit(6);
  }

  /* Read and Write file to child process */
  parentWriteToChild(data_filename, msg_buffer, old_child);
  parentCollectInput(new_child);

  return 0;
}
