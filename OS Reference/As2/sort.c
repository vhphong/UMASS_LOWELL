/*****************************************************************/
/* Yoo Min Cha                                                   */
/* Operating Systems                                             */
/* Professor Maloney                                             */
/* 24 September 2014                                             */
/*****************************************************************/

#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

void sig_handler(int signal){
    printf("\nSIGPIPE received: Someone shot the child.. \n");
    printf("nowhere to send data .. parent exiting.. goodbye\n\n");
    exit(1);
}

int main(){
  pid_t   pid, ppid;
  int     ruid, rgid, euid, egid;
  int     priority;
  int fd, nread, i, j, a;
  int pfdin[2], pfdout[2];
  int count =0, tcount = 0;
  char buf[81], print_buf[100];
  struct sigaction new_sig_state;
  sigset_t mask;
  FILE *in_pipe_read_end;
  char last_name[50], first_name[50];
  int area_code, old_code, prefix, telnum;
  int acode_count=0, total_count=0;
    
  sigemptyset(&mask);
  new_sig_state.sa_mask = mask;
  new_sig_state.sa_handler = sig_handler;
  new_sig_state.sa_flags =0;
   
  if(sigaction(SIGPIPE, &new_sig_state, NULL) == -1){
      perror("Sigpipe");
      exit(2);
  }
  
  pid  = getpid();
  ppid = getppid();
  ruid = getuid();
  euid = geteuid();
  rgid = getgid();
  egid = getegid();
  if (priority = getpriority(PRIO_PROCESS, 0) == -1){
    perror("getpriority failed ");
    exit(2);
  }
  printf("\nPARENT PROG:  Process ID is:\t\t%d\n\
  PARENT PROC:  Process parent ID is:\t%d\n\
  PARENT PROC:  Real UID is:\t\t%d\n\
  PARENT PROC:  Real GID is:\t\t%d\n\
  PARENT PROC:  Effective UID is:\t%d\n\
  PARENT PROC:  Effective GID is:\t%d\n\
  PARENT PROC:  Process priority is:\t%d\n", pid, ppid, ruid, rgid, euid, egid, priority);
  
  if(pipe(pfdin) == -1 || pipe(pfdout) == -1){
    perror("fork");
    exit(2);
  }
  
  switch( fork()){
    case -1: 
      perror("fork failed");
      exit(3);
    case 0:
        pid  = getpid();
        ppid = getppid();
        ruid = getuid();
        euid = geteuid();
        rgid = getgid();
        egid = getegid();
        if(priority = getpriority(PRIO_PROCESS, 0) == -1){
                perror("getpriority failed: ");                 
                exit(2);
        }
        printf("\nThis is the Child process report:\n");
        printf("\nCHILD PROG:  Process ID is:\t\t%d\n\
CHILD PROC:  Process parent ID is:\t%d\n\
CHILD PROC:  Real UID is:\t\t%d\n\
CHILD PROC:  Real GID is:\t\t%d\n\
CHILD PROC:  Effective UID is:\t\t%d\n\
CHILD PROC:  Effective GID is:\t\t%d\n\
CHILD PROC:  Process priority is:\t%d\n\n"
, pid, ppid, ruid, rgid, euid, egid, priority);
        
      if(close(0) == -1){
        perror("pipe");
        exit(1);
      }
      if(dup(pfdout[0]) != 0){
        perror("dup not opened on channel 0");
        exit(3);
      }
      /* inherited from parent and we need to close this */
      if(close(1) == -1){
        perror("failed on closing channel 1");
        exit(3);
      }
      /* duping on the right side where the parent will be reading from */
      if(dup(pfdin[1]) != 1){
        perror("failed to open onfchannel 1");
        exit(3);
      }
      if(close(pfdout[0]) == -1 || 
        close(pfdout[1]) == -1 ||
        close(pfdin[0]) == -1 ||
        close(pfdin[1]) == -1 ){
          perror("failed to close the appropriate channels");
          exit(1);
        }
        execlp("sort", "sort", "-k 3,3n", "-k 1.1", "-k 2.2", NULL);
        /* -k key, check 3rd item and only up the the third item */
        /* n is specifies numeric sort as opposed the the default alphanumeric setting */
        perror("execlp failed to execute");
        exit (1);
  }
  /*parent continues here */
  
  if(close(pfdout[0]) == -1 || close(pfdin[1]) == -1){
    perror("close");
    exit(1);
  }
  
  if((a=open("cs308a2_sort_data", O_RDONLY, 0)) == -1){
    perror("cannot open cs308a2_sort_data");
    exit(1)