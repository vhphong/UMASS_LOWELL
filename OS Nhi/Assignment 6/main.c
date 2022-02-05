/**********************************************
Class: 		CS308 - Operating Systems
Name: 		DangNhi Ngoc Ngo
Student ID: 	01553277
Email: 		DangNhi_Ngo@student.uml.edu
Homework 6
***********************************************/

#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

// Print function, displays all the stats about the files
void print_details(struct stat statBuffer);

int main(int argc, char *argv[]) {
  struct stat statBuffer;
  struct dirent* entry;
  DIR* directory;
  int x;

  if (argc > 1) {

    // Run through all the arguments
    for(x = 1; x < argc; x++) {
      if (lstat(argv[x], &statBuffer ) == -1) {
        printf("Error: failed to access file %s!\n", argv[x]);
        exit(1);
      }
      printf("FILE NAME: %s\n", argv[x]);
      print_details(statBuffer);
    }

    return 0;
  }

  if ( (directory = opendir(".")) == NULL) {
    printf("Error: failed to open the current directory!\n");
    exit(1);
  }

  while( (entry = readdir(directory)) != NULL) {
    if (lstat(entry -> d_name, &statBuffer) == -1) {
      printf("Error: lstat failed on the current directory!\n");
      exit(2);
    }
    printf("FILE NAME: %s\n", entry -> d_name);
    print_details(statBuffer);
  }

  return 0;
}

void print_details(struct stat statBuffer) {
  struct passwd  *owner;
  struct group   *group;
  printf("FILE_TYPE: ");

  // Get the mode of the file
  switch (statBuffer.st_mode & S_IFMT) {
    case S_IFREG:
      printf("ordinary\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFLNK:
      printf("symbolic link\n");
      break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    default:
        printf("Error: unknown file type\n");
        break;
  }

  printf("PERMISSIONS: ");
  printf( (S_ISDIR(statBuffer.st_mode))  ? "d" : "-");
  printf( (statBuffer.st_mode & S_IRUSR) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWUSR) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXUSR) ? "x" : "-");
  printf( (statBuffer.st_mode & S_IRGRP) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWGRP) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXGRP) ? "x" : "-");
  printf( (statBuffer.st_mode & S_IROTH) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWOTH) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");

  // Print the owner name if found using getpwuid()
  if ( (owner = getpwuid(statBuffer.st_uid) ) != NULL) {
    printf("OWNER_NAME: %-8.8s\n", owner -> pw_name);
  }
  else {
    // Otherwise just print the UID
    printf("OWNER_NAME: %-8d\n", statBuffer.st_uid);
  }

  // Print the group name if found using getgrgid()
  if ( (group = getgrgid(statBuffer.st_gid) ) != NULL) {
    printf("GROUP_NAME: %-8.8s\n", group -> gr_name);
  }
  else {
    // Otherwise just print the GID
    printf("GROUP_NAME: %-8d\n", statBuffer.st_gid);
  }
  printf("DATE_OF_LAST_MODIFICATION: %s", ctime(&(statBuffer.st_mtime)));

  // Print the link count, size in bytes and inode number
  printf("LINK_COUNT: %jd\n", (long) statBuffer.st_nlink);
  printf("SIZE_IN_BYTES: %jd\n", (long) statBuffer.st_size);
  printf("INODE_NUMBER: %jd\n", (long) statBuffer.st_ino);

  // Print a blank link between each entry.
  printf("\n");
}
