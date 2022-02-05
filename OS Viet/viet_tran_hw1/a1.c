/** Viet Tran  **/
/** ID: 01607460  **/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/resource.h>

int counter = 0, counter_2G = 0;

typedef union {
	int exit_status;
	
	struct {
		unsigned sig_num : 7;
		unsigned core_dmp : 1;
		unsigned exit_num : 8;
	} parts;
	
} LE_wait_status;

void sig_handler(int signal){
	printf("\n\nPARENT PROG: Awake in handler - You Got Me With Signal\n \
Number %d after spinning for more\n than %d %s loop iterations, goodbye\n\n", 
                signal, ((counter_2G)?counter_2G*2:counter),
                ((counter_2G)?"Billion":"\0"));
    printf("CHILD PROG: Now beginning to exec target program. goodbye\n");
    fflush(stdout);
    execl("./A1", "A1", NULL);
	perror("\nexecl cannot execute the A1");
	exit(5);
}

int main(void)
{
	pid_t	pid, ppid;
	int	ruid, rgid, euid, egid;
	int	priority;
	sigset_t	mask, proc_mask;
	struct sigaction new_acct;
    char read_buf[10];
    int synch_pipe[2];
    LE_wait_status exit_union;
	
    if(pipe(synch_pipe) == -1) {
        perror("failed in parent pipe creation:");
    }

    // Report a collection of process and thread info for parent
    printf("\n This is Parent Process Report: \n");
	pid = getpid();
	ppid = getppid();
	ruid = getuid();
	euid = geteuid();
	rgid = getgid();
	egid = getegid();
	
    if((priority = getpriority(PRIO_PROCESS, 0)) == -1) {
        perror(" getpriority failed");
        exit(2);
    }
	
    // printing out report
	printf("\tPARENT PROG:  Process ID is:\t\t%d\n\
            PARENT PROG:  Process parent ID is:\t%d\n\
            PARENT PROG:  Real UID is:\t\t%d\n\
            PARENT PROG:  Real GID is:\t\t%d\n\
            PARENT PROG:  Effective UID is:\t%d\n\
            PARENT PROG:  Effective GID is:\t%d\n\
            PARENT PROG:  Process priority is:\t%d\n\
            ", pid, ppid, ruid, rgid, euid, egid, priority);

    printf(" PARENT PROG: will now create child, read pipe, \n\
     signal child  and wait for obituary from child ");
    
    switch (pid = fork()) {
        // check of Fork failed to call
        case -1 :
            perror("Parent cannot create child, good bye");
            exit(4);

        case 0 :
            printf("\n This is the Chold Process info: \n");
            sigemptyset(&mask);
            new_acct.sa_mask = mask;
            new_acct.sa_handler = sig_handler;
            new_acct.sa_flags = 0;
            if (sigaction(SIGTERM, &new_acct, NULL) == -1) {
                perror(" failed in signaction: ");
                exit(2);
            }
            pid = getpid();
            ppid = getppid();
            ruid = getuid();
            euid = geteuid();
            rgid = getgid();
            egid = getegid();

            if((priority = getpriority(PRIO_PROCESS, 0)) == -1) {
                perror("getpriority failed");
                exit(2);
            }
            
            printf("\n This is Child report: \n");
            printf("\t\tPARENT PROG:  Process ID is:\t\t%d\n\
                    PARENT PROG:  Process parent ID is:\t%d\n\
                    PARENT PROG:  Real UID is:\t\t%d\n\
                    PARENT PROG:  Real GID is:\t\t%d\n\
                    PARENT PROG:  Effective UID is:\t%d\n\
                    PARENT PROG:  Effective GID is:\t%d\n\
                    PARENT PROG:  Process priority is:\t%d\n\
                ", pid, ppid, ruid, rgid, euid, egid, priority);
            printf("\nCHILD PROG: write pipe and go to endless loop\n");
            fflush(stdout);
            if(write(synch_pipe[1], "x", 1) == -1) {
                perror("write pipe failed");
                exit(2);
            }

            while (1) {
                counter++;
                if(counter < 0) {
                    counter = 0;
                    counter_2G++;
                }
            }
        break;
        default:
            printf("\nPARENT PROG: created child with %d PID\n", pid);
        break;   
    }

    if(read(synch_pipe[0], read_buf, 1) == -1) {
        perror(" read pipe failed");
        exit(2);
    }
    if(kill(pid, SIGTERM) == -1) {
        perror("kill failed");
        exit(2);
    }
    printf("\n PARENT PROG: read pipe and sent SIGTERM, now wait exit\n");
    if((pid = wait(&exit_union.exit_status)) == -1) {
        perror(" wait failed in PARENT, goodbye : ");
        exit(6);
    } 
    printf("\n PARENT PROG: Child %d exited with %s code %d%s, good bye \n", pid,
    (exit_union.parts.sig_num == 0)? "exit":"signal",
    (exit_union.parts.sig_num == 0) ? exit_union.parts.exit_num:exit_union.parts.sig_num,
    (exit_union.parts.core_dmp)?" and a core dump" : "\0");
                       
}
