/* 
Name: 		DangNhi Ngoc Ngo 
Student ID:	01553277
Email: 		DangNhi_Ngo@student.uml.edu
Class:		Operating Systems
Assignment 1
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/wait.h>

int counter = 0, counter_2G = 0;

void sig_handler(int signal) {
	printf("CHILD PROG: Signal %d is called after %d time loops: \n", signal, counter);
	fflush(stdout);

	/* use the execl() call to load in the executable built from the source code */
	execl("./assign1", "assign1", NULL);
	perror("Excel did not start!");
	exit(10);
}

/* declare a typedef for exit status information returned from the waitpid() call */
typedef union {
	int exit_status;
	struct {
		unsigned sig_num:7;
		unsigned core_dmp: 1;
		unsigned exit_num:8;
	}parts;
} status;

int main(void) {
	pid_t pid, ppid;
	int	ruid, rgid, euid, egid;
	int	priority;
	sigset_t mask, proc_mask;
	struct sigaction new;
	int msg_pipe[2];
	char msg_buf[100];
	status wait_status;

	if (pipe(msg_pipe) == -1) {
		perror("Failed in Parent pip creation");
		exit(3);
	}

	pid = getpid();
	ppid = getppid();
	ruid = getuid();
	euid = geteuid();
	rgid = getgid();
	egid = getegid();
	priority = getpriority(PRIO_PROCESS, 0);

	printf("\nThis is the Parent process report:\n");

	printf("\nPARENT PROG:  Process ID is:\t\t%d\n\
PARENT PROG:  Process parent ID is:\t%d\n\
PARENT PROG:  Real UID is:\t\t%d\n\
PARENT PROG:  Real GID is:\t\t%d\n\
PARENT PROG:  Effective UID is:\t\t%d\n\
PARENT PROG:  Effective GID is:\t\t%d\n\
PARENT PROG:  Process priority is:\t%d\n\
", pid, ppid, ruid, rgid, euid, egid, priority);

	printf("\nPARENT PROG: will now create child, read pipe,\n\
signal child, and wait for obituary from child\n");

	switch (pid = fork()) { /* create a child using the fork() call */
		case -1: /* no child was created */
			perror("fork call failed");
			exit(4);
		case 0: /* only child can get here */
			/* clear signal mask */
			sigemptyset(&proc_mask);
    			sigprocmask(SIG_SETMASK, &proc_mask, NULL);

			sigemptyset(&mask);
			new.sa_mask = mask;
			new.sa_handler = &sig_handler;
			new.sa_flags = 0;

			if (sigaction(SIGTERM, &new, NULL) == -1) {
				perror("failed in sigaction:");
				exit(2);
			}

			pid = getpid();
			ppid = getppid();
			ruid = getuid();
			euid = geteuid();
			rgid = getgid();
			egid = getegid();
			priority = getpriority(PRIO_PROCESS, 0);

			printf("\nThis is the Child process report:\n");

			printf("\nCHILD PROG:  Process ID is:\t\t%d\n\
CHILD PROG:  Process parent ID is:\t%d\n\
CHILD PROG:  Real UID is:\t\t%d\n\
CHILD PROG:  Real GID is:\t\t%d\n\
CHILD PROG:  Effective UID is:\t\t%d\n\
CHILD PROG:  Effective GID is:\t\t%d\n\
CHILD PROG:  Process priority is:\t%d\n\
", pid, ppid, ruid, rgid, euid, egid, priority);

			printf("\nCHILD PROG: about to write pipe and go to endless loop\n");
			fflush(stdout);
			write(msg_pipe[1],"v", 1);

			while (counter_2G < 10){
				counter ++;
				if (counter < 0){
					counter = 0;
					counter_2G++;
				}
			}

			write(1,"CHILD PROG: timed out after 20 billion iterations\n", 51);
			exit(2);
		default: /* only parent can get here */
			printf("\nPARENT PROG: created child with %d PID\n", pid);
			break;
	}

	/* parent wakes from pipe read */
	if (read(msg_pipe[0], msg_buf, 1) == -1) {
		printf("\nPARENT PROG: Failed to read the read-channel of the pipe!");
		exit(8);
	}

	/* parent sends SIGTERM to child pid */
	if (kill(pid, SIGTERM) == -1) {	
		printf("\nPARENT PROG: Failed to kill child process!");
		exit(8);
	}

	printf("\nPARENT PROG: read pipe and send SIGTERM, now wait for exiting\n");

	/* clean up and wait for my child process to finish */
	pid = waitpid(-1, &wait_status.exit_status, 0);
	if (pid == -1) {
		printf("PARENT PROG: Failed to wait for killing child process!");
		exit(10);
	}


	if (wait_status.parts.sig_num != 0) {		
		printf("PARENT PROG: Child PID: %d exited with SIGNAL code: %d\n",
			pid, wait_status.parts.sig_num);

	} else {
		printf("PARENT PROG: Child PID: %d exited with EXIT code: %d\n",
			pid, wait_status.parts.exit_num);
	}
	return 0;
}