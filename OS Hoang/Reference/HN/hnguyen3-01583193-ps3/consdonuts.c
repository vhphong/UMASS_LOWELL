/*******************************************************                        
  Name: Hung Q Nguyen                                                           
  Student ID: 01583193                                                          
  Email: Hung_Nguyen3@student.uml.edu                                           
  Date: 3/7/2017                                                                
  Assignment 3
  -- Taken code from prof. Moloney's template (assign3-call-help)
  -- Then added my functions to make a consumer                                          
*******************************************************/

#include "donuts.h"

int main (int argc, char *argv[]) {
	int flavors[NUMFLAVORS][DOZENS];
	int shmid, semid[3];
	unsigned short xsub1[3];
	struct donut_ring *shared_ring;
	struct timeval randtime;

	if((shmid = shmget (MEMKEY, sizeof(struct donut_ring), 0)) == -1){
		perror("shared get failed: ");
		exit(1);
	}

	/***  begin syscall shmat comment for shared memory
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/shm.h>

   void *shmat (int shmid, const void *attach_addr, 
				   int shmflg);
	************* end syscall shmat comment ******/
	if((shared_ring = (struct donut_ring *) 
	shmat (shmid, (const void *)0, 0)) == (void *)-1){
		perror("shared attach failed: ");
		exit(2);
	}

	/***  begin syscall semget comment for semaphores
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/sem.h>
   int semget (key_t key, int nsems, int semflg);
	************* end syscall semget comment ******/
	int i;
	for(i = 0; i < NUMSEMIDS; i++) {
		if ((semid[i] = semget (SEMKEY + i, NUMFLAVORS, 0)) == -1){
			perror("semaphore allocation failed: ");
			exit(3);
		}
	}


	/*** begin syscall gettimeofday comment for time seed
   #include <sys/time.h>
   int gettimeofday (struct timeval *tp, struct timezone *tzp);
   struct timeval {
	  long    tv_sec;         	/* seconds 
    long    tv_usec;        	/* and microseconds 
   }
	********* end syscall gettimeofday comment ******/
	gettimeofday (&randtime, (struct timezone *)0);

	/* use microsecond component for uniqueness */
  xsub1[0] = (ushort) randtime.tv_usec;
  xsub1[1] = (ushort)(randtime.tv_usec >> 16);
  xsub1[2] = (ushort)(getpid());

  int k, j;
  for (i = 0; i < LOOPS; i++) {

  	// initializing flavor array to the array of 0s
  	initFlavors(flavors);

  	// get donuts type for list of dozens donut
  	for (k = 0; k < DOZENS; k++) {
			/********* end syscall gettimeofday comment ******/
			gettimeofday (&randtime, (struct timezone *)0);

			/* use nrand48 with xsub1 to get 32 bit random number */
		  j = nrand48(xsub1) & 3;

		  // regenerate the value of xsub
	    ushort* temp = generateXSub(randtime);
	    xsub1[0] = *(temp);
	    xsub1[1] = *(temp + 1);
	    xsub1[2] = *(temp + 2);

			p(semid[OUTPTR], j);
		  p(semid[CONSUMER], j);

			flavors[j][k] = shared_ring->flavor[j][shared_ring->outptr[j]];

			/* Consuming donut */
      if (shared_ring -> outptr[j] >= NUMSLOTS){
				shared_ring -> outptr[j] = 0;
      } else {
				shared_ring -> outptr[j] = shared_ring -> outptr[j] + 1;
      }

			v(semid[PROD], j);
			v(semid[OUTPTR], j);
  	}

  	// get current process time
  	gettimeofday(&randtime, (struct timezone *)0);

		// Print process ...
		// EXP: process PID: 34567 time: 10:22:36.344 dozen #: 4
		printf("\tCONS PROCESS PID: %d, TIME: %d , dozen #: %d\n\n", getpid(), (ushort)randtime.tv_usec, i + 1);

  	printAllFlavors(flavors);
  }
}

void initFlavors(int flavors[NUMFLAVORS][DOZENS]) {
	int i, j;
	for (i = 0; i < NUMFLAVORS; i++) {
		for (j = 0; j < DOZENS; j++) {
			flavors[i][j] = 0;
		}
	}
}

ushort* generateXSub(struct timeval randtime) {
  unsigned short xsub[3];
  xsub[0] = (ushort)randtime.tv_usec;
  xsub[1] = (ushort)(randtime.tv_usec >> 16);
  xsub[2] = (ushort)(getpid());

  return xsub;
}

void printAllFlavors(int flavors[NUMFLAVORS][DOZENS]) {
	int i, j;

	// Print: plain jelly coconut honey-dip
	printf("\n\tplain\tjelly\tcoconut\thoney-dip\n");

	for(i = 0; i < DOZENS; i++) {
			for(j = 0; j < NUMFLAVORS; j++){
				if(flavors[j][i] != 0)
					printf("\t\t%d", flavors[i][j]);
				else
					printf("\t\t");
			}
			printf("\n");
		}
}