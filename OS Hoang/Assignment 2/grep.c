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

int main(int argc, char** argv) {
  char* name_of_file = *(argv + 1);
  char* msg_buffer;
  int new_child[2], old_child[2];

  msg_buffer = malloc(sizeof(char) * 100);
  int data = open(name_of_file, O_RDONLY, 0);
  long read_data = read(data, msg_buffer, 100);

  if (argc != 2) {
    printf("\nPlease enter the data filename\n");
    exit(0);
  }

  /*creating pipes for each child*/
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
      execlp("grep", "grep", "123", NULL);
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

  while (read_data != 0 && read_data != -1) {
    if (write(old_child[1], msg_buffer, read_data) == -1) {
        perror("PARENT PROGRESS: Parent failed to write to old child\n");
        exit(6);
    }

    read_data = read(data, msg_buffer, sizeof(msg_buffer));
  }

  /* close data file and old child */
  if (close(data) == -1 || close(old_child[1]) == -1) {
    perror("PARENT PROGRESS: Parent failed close data file\n");
    exit(1);
  }

  FILE* fp = fopen("grep.bat", "w+");
  int count = 0;
  int data2 = open("grep.bat", O_RDWR);
  int read_data2 = read(new_child[0], msg_buffer, sizeof(msg_buffer));

  while (read_data2 != 0 && read_data2 != -1) {
    write(data2, msg_buffer, read_data2);
    read_data2 = read(new_child[0], msg_buffer, sizeof(msg_buffer));
  }

  /* count many lines contains "123" */
  char* tempString = malloc(sizeof(char) * 100);
  while((tempString = fgets(msg_buffer, sizeof(msg_buffer), fp)) != NULL) {
    if (strstr(tempString, "123") != NULL) {
      count++;
    }
  } 
  printf("PARENT PROGRESS: Number of lines returned by grep: %d\n", count);

  if (close(data2) == -1 || close(new_child[0]) == -1) {
    perror("PARENT PROGRESS: Parent failed close child\n");
    exit(1);
  }

  return 0;
}
