#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>

/*
	struct stat {
	dev_t st_dev; /* device inode resides on 
	ino_t st_ino; /* this inode's number 
	mode_t st_mode; /* protection 
	nlink_t st_nlink; /* number or hard links to the file 
	uid_t st_uid; /* user-id of owner 
	gid_t st_gid; /* group-id of owner 
	dev_t st_rdev; /* dev type, for inode that is dev 
	off_t st_size; /* total size of file 
	time_t st_atime; /* file last access time 
	time_t st_mtime; /* file last modify time 
	time_t st_ctime; /* file last status change time 
	uint_t st_blksize; /* opt blocksize for file sys i/o ops 
	int st_blocks; /* actual number of blocks allocated 
	 };
 */

void printCompleteFileDetail(struct stat st);

void getFileType(struct stat st) {
  if(S_ISDIR(st.st_mode)){
    printf("FILE_TYPE: Directory\n"); 
  }

  if(S_ISCHR(st.st_mode)){
    printf("FILE_TYPE: Character\n");
  }

  if(S_ISBLK(st.st_mode)){
    printf("FILE_TYPE: Block\n");
  }

  if(S_ISREG(st.st_mode)){
    printf("FILE_TYPE: Regular file\n");
  }

  if(S_ISFIFO(st.st_mode)){
    printf("FILE_TYPE: Pipe\n");
  }

  if(S_ISLNK(st.st_mode)){
    printf("FILE_TYPE: Link\n");
  }

  if(S_ISSOCK(st.st_mode)){
    printf("FILE_TYPE: Socket\n");
  }
}

void getFilePermission(struct stat st) {
	char permissions[10];

  // init permission
  int i;
  for (i = 0; i < 10; i++) {
  	if (i == 9) {
  		permissions[i] == '\0';
  	} else {
  		permissions[i] == '-';
  	}
  }

  if(st.st_mode & S_IRUSR){
    permissions[0] = 'r'; 
  }

  if(st.st_mode & S_IWUSR){
    permissions[1] = 'w';
  }

  if(st.st_mode & S_IXUSR){
    permissions[2] = 'x';
  }

  if(st.st_mode & S_IRGRP){
    permissions[3] = 'r';
  }

  if(st.st_mode & S_IWGRP){
    permissions[4] = 'w';
  }

  if(st.st_mode & S_IXGRP){
    permissions[5] = 'w';
  }

  if(st.st_mode & S_IWOTH){
    permissions[6] = 'r';
  }

  if(st.st_mode & S_IROTH){
    permissions[7] = 'w';
  }

  if(st.st_mode & S_IXOTH){
    permissions[8] = 'x';
  }

  printf("PERMISSIONS: %s\n", permissions);
}

void getFileOwnerInfo(struct stat st) {
  struct passwd* pass;

  if((pass = getpwuid(st.st_uid)) == NULL){
    printf("OWNER_NAME: %d\n", st.st_uid);
  } else {
    printf("OWNER_NAME: %s\n", pass -> pw_name);
  }
}

void getGroupOwnInfo(struct stat st) {
  struct group* group;
  if((group = getgrgid(st.st_gid)) == NULL){
    printf("GROUP_NAME: %d\n", st.st_gid);
  } else {
    printf("GROUP_NAME: %s\n", group -> gr_name);
  }
}

void getFileDateInfo(struct stat st) {
	printf("DATE_OF_LAST_MODIFICATION: %s", ctime(&(st.st_mtime)));
  printf("LINK_COUNT: %d\n", st.st_nlink);
}

void getAllowDevices(struct stat st) {
	if((S_ISCHR(st.st_mode))|| S_ISBLK(st.st_mode)) {
    printf("FILE-MAJOR: %d, MINOR: %d\n", major(st.st_rdev), minor(st.st_rdev));
  } else {
    printf("SIZE_IN_BYTES: %d\n", st.st_size);
    printf("INODE_NUMBER: %d \n\n", st.st_ino);
  }
}

#endif