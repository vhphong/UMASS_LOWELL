/** This is the source file for the first assignment  **/
/** You may find it helpful to cut and paste from it  **/
/** The executable you need to exec has been compiled **/
/**   from this file and is located on mercury at:    **/
/**                 ~bill/cs308/A1                    **/

/*******************************************************
	Name: Hung Q Nguyen
	Student ID: 01583193
	Email: Hung_Nguyen3@student.uml.edu
	Date: 1/31/2017
	Assignment 1
*******************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int counter = 0, counter_2G = 0;

void sig_handler(int signal) {
	/* Print message then clear output screen */
	printf("CHILD PROG: Signal %d is called after %d time loops: \n", signal, counter);
	fflush(stdout);

	execl("./assign1", "assign1", NULL);
	// print out error message for execl
	perror("Excel did not start!");
	exit(10);
}

void collectPIDdata(pid_t *pid, pid_t *ppid, int *ruid, int* rgid,
	 int* euid, int *egid, int *priority) {
	/* Collect all the PID information */
	*pid = getpid();
	*ppid = getppid();
	*ruid = getuid();
	*euid = geteuid();
	*rgid = getgid();
	*egid = getegid();
	*priority = getpriority(PRIO_PROCESS, 0);
}

void printParentReport(pid_t *pid, pid_t *ppid, int *ruid, int* rgid,
	 int* euid, int *egid, int *priority) {

	printf("\nThis is the prof process report:");

	printf("\n\tPROF PROG:  Process ID is:\t\t%d\n\
	PROF PROG:  Process parent ID is:\t%d\n\
	PROF PROG:  Real UID is:\t\t%d\n\
	PROF PROG:  Real GID is:\t\t%d\n\
	PROF PROG:  Effective UID is:\t\t%d\n\
	PROF PROG:  Effective GID is:\t\t%d\n\
	PROF PROG:  Process priority is:\t%d\n\
	", *pid, *ppid, *ruid, *rgid, *euid, *egid, *priority);
}

void printChildReport(pid_t *pid, pid_t *ppid, int *ruid, int* rgid,
	 int* euid, int *egid, int *priority) {

	printf("\nThis is the child process report:\n");

	printf("\tCHILD PROG:  Process ID is:\t\t%d\n\
	CHILD PROG:  Process parent ID is:\t%d\n\
	CHILD PROG:  Real UID is:\t\t%d\n\
	CHILD PROG:  Real GID is:\t\t%d\n\
	CHILD PROG:  Effective UID is:\t\t%d\n\
	CHILD PROG:  Effective GID is:\t\t%d\n\
	CHILD PROG:  Process priority is:\t%d\n\
	", *pid, *ppid, *ruid, *rgid, *euid, *egid, *priority);
}

/* Making new union structer for the wait statuses */
typedef union {
	int exit_signal;
	struct {
		unsigned signal_states:7;
		unsigned core_states: 1;
		unsigned exit_states:8;
	} state;
} status;

void printExitInfo(status *stat, pid_t* pid) {
	if (stat->state.signal_states != 0) {
		printf("PARENT PROG: Child (PID: %d) exited with SIGNAL code: %d\n", *pid, stat->state.signal_states);
	} else {
		printf("PARENT PROG: Child (PID: %d) exited with EXIT code: %d\n", *pid, stat->state.exit_states);
	}
}

int main(void) {
	pid_t pid, ppid;
	int	ruid, rgid, euid, egid;
	int	priority;
	/* implementing the Sigtern */
	sigset_t mask, proc_mask;
	struct sigaction new;
	int sync_pipe[2];
	char message_buffer[10];
	status wait_stat;

	if (pipe(sync_pipe) == -1) {
		perror("failed to create parent pipe:");
		exit(7);
	}

	/*Collect PID data for parent process and then print it*/
	collectPIDdata(&pid, &ppid, &ruid, &rgid, &euid, &egid, &priority);
	printParentReport(&pid, &ppid, &ruid, &rgid, &euid, &egid, &priority);

	printf("\n\tPARENT PROG: Creating child process...!\n");
	printf("\t************************************************\n");

	// Now try to create child process
	switch (pid = fork()) {
		case -1:
			// get here if no child was created
			perror("Can't create child");
			exit(4);
		case 0:
			/** clear signal mask **/
			sigemptyset(&proc_mask);
    		sigprocmask(SIG_SETMASK, &proc_mask, NULL);
			// Get to this point means child created
			sigemptyset(&mask);
			
			new.sa_mask = mask;
			new.sa_handler = &sig_handler;
			new.sa_flags = 0;

			if (sigaction(SIGTERM, &new, NULL) == -1) {
				perror("failed in sigaction:");
				exit(2);
			}

			/*Collect PID data for child process and then print it*/
			collectPIDdata(&pid, &ppid, &ruid, &rgid, &euid, &egid, &priority);
			printChildReport(&pid, &ppid, &ruid, &rgid, &euid, &egid, &priority);

			printf("\n**CHILD PROG: Entering infinite loop\n");
			fflush(stdout);
			write(sync_pipe[1],"v", 1);

			// Get into child endless loops
			while (counter_2G < 10){
				counter ++;
				if (counter < 0){
					counter = 0;
					counter_2G++;
				}
			}

			write(1,"CHILD PROG: timed out after 20 billion iterations\n", 51);
			exit(2);
		default:
			// only parent can get here
			printf("\tPARENT PROG: Created child with PID: %d\n", pid);
			break;
	}

	// Now we need to kill the children's loops
	if (read(sync_pipe[0], message_buffer, 1) == -1) {
		printf("\nPARENT PROG: Failed to read message buffer!");
		exit(8);
	}

	if (kill(pid, SIGTERM) == -1) {
		printf("\nPARENT PROG: Failed to kill child process!");
		exit(8);
	}

	printf("\nPARENT PROG: killing child's process, waiting to exit!\n");
	// get pid from waitime;
	pid = waitpid(-1, &wait_stat.exit_signal, 0);
	if (pid == -1) { // If parent failed to wait
		printf("PARENT PROG: Failed to wait to kill child process!");
		exit(10);
	}

	// If parent's waitime was successfully
	printExitInfo(&wait_stat, &pid);

	return 0;
}
