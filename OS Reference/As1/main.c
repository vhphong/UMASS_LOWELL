/*****************************************************************/
/* Yoo Min Cha                                                   */
/* Computer Architecture                                         */
/* Professor Maloney                                             */
/* 17 September 2014                                             */
/*****************************************************************/

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

typedef union LE_Wait_Status{
	int exit_status;
	struct{
		unsigned sig_num:7;
		unsigned core_dmp:1;
		unsigned exit_num:8;
	}parts;
}LE_Wait_Status;

int counter = 0;
int counter_2G = 0;

void sig_handler(int signum){
  printf("\nCHILD PROG: Awake in Handler - You Got Me With Signal\n\
  Number %d after spinning for more than %d %s loop iterations\n\n", signum,
  ((counter_2G)?counter_2G*2:counter), ((counter_2G)?"Billion":"\0"));
  printf("CHILD PROG: Now beginning to exec target program, goodbye\n");
  fflush(stdout);
  execl("./Assign1", "Assign1", NULL);  
  perror("if you see this we failed exec, bad new_act, goodbye");
  exit(200);
};

int main(void)
{
  pid_t   pid, ppid;
  int     ruid, rgid, euid, egid;
  int     priority;
  char    msg_buf[100];
  int     msg_pipe[2];
  sigset_t mask;
  LE_Wait_Status exit_union;
/* Tells us what to block when we are in the signal handler */ 
  struct sigaction new_act;
/*
	http://man7.org/linux/man-pages/man2/sigaction.2.html
	struct sigaction
	void			(*sa_handler)(int) - pointer to a signal-catching function or one of the 
												macros SIG_IGN or SIG_DFL. (ignore or default)
	sigset_t 	sa_mask				- Additional set of signals to be blocked during 
												execution of signal-catching function.
	int 			sa_flags  			- Special flags to affect behavior of signal.
	void			(*sa_sigaction)(int, siginfo_t *, void *)  - Pointer to a signal-catching 
																				function.(May be
																				a union with sa_handler)
*/

/* use the pipe() system call to create the pipe */
  if(pipe(msg_pipe) == -1){
    perror("failed in Parent pipe creation: \n");
    exit(7);
  }

/* use various system calls to collect and print process details */
  printf("\nThis is the Parent process report:\n");

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

   printf("\nPARENT PROC: will now create child, read pipe,\n \
signal child, and wait for obituary from child\n\n");

  switch (pid = fork()){
     case -1: /* if the call fails */
	perror("\nChild process failed to create: \n");
	exit (48);

     default:
	printf("PARENT PROC: created Child with %d PID\n", pid);
        break;

     case 0:		
	sigemptyset(&mask);
	new_act.sa_mask = mask;
	new_act.sa_handler = sig_handler;
	new_act.sa_flags = 0;

	if(sigaction(SIGTERM, &new_act, NULL) == -1){
		perror("failed in sigaction: ");
                exit(20);
        }

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
, pid, ppid, ruid, rgi