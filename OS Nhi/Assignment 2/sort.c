/**********************************************
Class: 		CS308 - Operating Systems
Name: 		DangNhi Ngoc Ngo
Student ID: 	01553277
Email: 		DangNhi_Ngo@student.uml.edu
Homework 2
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
  char* nameOfFile = "cs308a2_sort_data";
  char* msg_buffer;
  char* lname = malloc(sizeof(char) * 100);
  char* fname = malloc(sizeof(char) * 100);
  int new_child[2], old_child[2];
  int read_data;
  int area_code, code1, code2;
  int data_list[2000];
  int data = open(nameOfFile, O_RDONLY);
  dup2(data, 0);

  memset(data_list, 0, sizeof(data_list));
  msg_buffer = malloc(sizeof(char) * 512);

  /* creating pipes for each child */
  if (pipe(new_child) == -1) {
      perror("Failed to create pipe on new child!\n");
      exit(7);
  }

  if (pipe(old_child) == -1) {
      perror("Failed to create pipe on old child!\n");
      exit(7);
  }

  switch(fork()) {
    case -1:
      perror("CHILD PROGRESS: Failed to call fork\n");
      exit(7);
    case 0:
      if (close(0) == -1 || close(1) == -1) {
        perror("CHILD PROGRESS: Failed to close stdio library!\n");
        exit(10);
      }

      if (dup(old_child[0]) != 0 || dup(new_child[1]) != 1) {
        perror("CHILD PROGRESS: Failed to start stdio process!\n");
      }

      if (close(old_child[0]) == -1 || close(old_child[1]) == -1) {
        perror("CHILD PROGRESS: Old child failed to close pipe\n");
        exit(6);
      }

      if (close(new_child[0]) == -1 || close(new_child[1]) == -1) {
        perror("CHILD PROGRESS: New child failed to close pipe\n");
        exit(6);
      }

      execlp("sort", "sort", "-k", "3.3n", "-k", "1.1", "-k", "2.2", NULL);
    default:
      break;
  }

  if (close(old_child[0]) == -1 || close(new_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed to close pipe\n");
    exit(6);
  }	     

  if (data == -1 ) {
    perror("PARENT PROGRESS: Parent failed to open file\n");
    exit(6);
  }

  /* read each line of the file */
  while ((read_data = read(data, msg_buffer, 50))) {
    if (write(old_child[1], msg_buffer, read_data) == -1) {
      perror("PARENT PROGRESS: Parent failed to write to old child\n");
      exit(6);
    }
  }

  /* close data file and old child */
  if (close(data) == -1 || close(old_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed close data file\n");
    exit(1);
  }

  FILE* fp = fdopen(new_child[0], "r");

  while(fscanf(fp, "%s %s %d %d %d\n", lname, fname, &area_code, &code1, &code2) != EOF) {
    data_list[area_code]++;
  }

  /* print out the sorted result */
  int i;
  for(i = 0; i < 2000; i++) { 
    if (data_list[i] != 0) {
        printf("Area Code %d:	Number of people: %d\n", i, data_list[i]);
    }
  }

  return 0;
}
