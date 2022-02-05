/* Name: Hoang Do
   Student ID: 01521888 */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/wait.h>
int counter = 0, counter_2G = 0;

typedef union {
	int exit_status;
	struct {
		unsigned sig_num:7;
		unsigned core_dmp: 1;
		unsigned exit_num:8;
	}parts;
}LE_Wait_Status;

void sig_handler(int signal){
	printf("\n\nPROF PROG: Awake in handler - You Got Me With Signal\n \
Number %d after spinning for more\n than %d %s loop iterations, goodbye\n\n", 
                signal, ((counter_2G)?counter_2G*2:counter),
                ((counter_2G)?"Billion":"\0"));
                
    printf("CHILD PROG: Now beginning to exec target program\n");
    fflush(stdout);
    execl("./Assign1", "Assign1", NULL);
	perror("\nExec couldn't execute");
	exit(10);
}

int main(void)
{
	pid_t	pid, ppid;
	int	ruid, rgid, euid, egid;
	int	priority;
	sigset_t	mask, proc_mask;
	struct sigaction new;
	int msg_pipe[2];
	char msg_buf[100];
	LE_Wait_Status Wstatus;

	if(pipe(msg_pipe) == -1){
		perror("failed in Parent pipe creation:");
        exit(7);
	}

	pid = getpid();
	ppid = getppid();
	ruid = getuid();
	euid = geteuid();
	rgid = getgid();
	egid = getegid();

	priority = getpriority(PRIO_PROCESS, 0);
	printf("\nThis is the Parent process report:\n");

	printf("\nPROF PROG:  Process ID is:\t\t%d\n\
PROF PROG:  Process parent ID is:\t%d\n\
PROF PROG:  Real UID is:\t\t%d\n\
PROF PROG:  Real GID is:\t\t%d\n\
PROF PROG:  Effective UID is:\t\t%d\n\
PROF PROG:  Effective GID is:\t\t%d\n\
PROF PROG:  Process priority is:\t%d\n\
", pid, ppid, ruid, rgid, euid, egid, priority);

   printf("\nPARENT PROC: will now create child, write pipe,\n \
signal child, and wait for obituary from child\n");

 	switch (pid = fork()){
        case -1: // if the call failes
            printf("\nFail to create child!!!\n");
            break;
            
		case 0:  // this is the child's case
		   // child must create and print report
			printf("\nThis is the Child process report: \n");
			
			/* clear signal mask */
			sigemptyset(&proc_mask);
			sigprocmask(SIG_SETMASK, &proc_mask, NULL);
    			
			sigemptyset(&mask);
	        new.sa_mask = mask;
            new.sa_handler = sig_handler;
	        new.sa_flags = 0;

        	if(sigaction(SIGTERM, &new, NULL) == -1){
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
			
			printf("\nCHILD PROG:  Process ID is:\t\t%d\n\
CHILD PROC:  Process parent ID is:\t%d\n\
CHILD PROC:  Real UID is:\t\t%d\n\
CHILD PROC:  Real GID is:\t\t%d\n\
CHILD PROC:  Effective UID is:\t\t%d\n\
CHILD PROC:  Effective GID is:\t\t%d\n\
CHILD PROC:  Process priority is:\t%d\n",
	pid, ppid, ruid, rgid, euid, egid, priority);
	
			printf("\nCHILD PROG: about to write pipe and go to endless loop\n");
            fflush(stdout);
            write(msg_pipe[1], "x", 1);
			
             while (1) {
                counter++;
                if(counter < 0) {
                    counter = 0;
                    counter_2G++;
                }
            }   
        	break;       
        default: // this is the parent's case  
                 // parent must write message to pipe 
            printf("\nPARENT PROG: created Child with %d PID", pid);
            break;
        } // switch and child end

    if (read(msg_pipe[0], msg_buf, 1) == -1) {
		perror("\nPARENT PROG: Failed to read the pipe!");
		exit(2);
	}

	/* parent sends SIGTERM to child pid */
	if (kill(pid, SIGTERM) == -1) {	
		perror("\nPARENT PROG: Failed to kill child!");
		exit(2);
	}
	
    printf("\n PARENT PROG: read pipe and sent SIGTERM, now wait to exit\n");
     if((pid = wait(&Wstatus.exit_status)) == -1) {
        perror("PARENT PROG: Failed to wait for killing child process!");
        exit(10);
    } 
    
    if (Wstatus.parts.sig_num != 0) {		
		printf("PARENT PROG: Child PID: %d exited with SIGNAL code: %d\n",
			pid, Wstatus.parts.sig_num);

	} else {
		printf("PARENT PROG: Child PID: %d exited with EXIT code: %d\n",
			pid, Wstatus.parts.exit_num);
	}
	exit(0);
}

