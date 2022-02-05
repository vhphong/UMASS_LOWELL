//Name:		Hoang Do
//ID:		01521888
//Email:	Hoang_Do@student.uml.edu
//Operating System -As3

#include "donuts.h"
#include <stdlib.h>

#define DOZENS 12

int main (int argc, char *argv[])
{
	int flavors[NUMFLAVORS][DOZENS];
	int shmid, semid[3];
	unsigned short xsub1[3];
	struct donut_ring *shared_ring;
	struct timeval randtime;
	int i, k, j, m, n, o;
	int c1, c2, c3, c4, c5;

	if((shmid = shmget (MEMKEY, sizeof(struct donut_ring), 0)) == -1){
		perror("shared get failed: ");
		exit(1);
	}

	if((shared_ring = (struct donut_ring *) 
	shmat (shmid, (const void *)0, 0)) == (void *)-1){
		perror("shared attach failed: ");
		exit(2);
	}

	for(i = 0; i < NUMSEMIDS; i++) {
		if ((semid[i] = semget (SEMKEY + i, NUMFLAVORS, 0)) == -1){
			perror("semaphore allocation failed: ");
			exit(3);
		}
	}

	gettimeofday (&randtime, (struct timezone *)0);

  xsub1[0] = (ushort) randtime.tv_usec;
  xsub1[1] = (ushort)(randtime.tv_usec >> 16);
  xsub1[2] = (ushort)(getpid());

  for (i = 0; i < 10; i++) {

  	c1 = 0;
	c2 = 0;
	c3 = 0;
	c4 = 0;
	c5 = 0;

  	for (k = 0; k < DOZENS; k++) {

	gettimeofday (&randtime, (struct timezone *)0);

	unsigned short *xsub;
  	xsub = (unsigned short *)malloc(sizeof(unsigned short)*3);
  	xsub[0] = (ushort)randtime.tv_usec;
  	xsub[1] = (ushort)(randtime.tv_usec >> 16);
  	xsub[2] = (ushort)(getpid());

	j = nrand48(xsub1) & 3;

	p(semid[OUTPTR], j);
  	p(semid[CONSUMER], j);

	int temp = shared_ring->flavor[j][shared_ring->outptr[j]];

	switch(j){
		case 0: {
			flavors[j][c1] = temp;
			c1++;
			break;
			}
		case 1: {
			flavors[j][c2] = temp;
			c2++;
			break;
			}
		case 2: {
			flavors[j][c3] = temp;
			c3++;
			break;
			}
		case 3: {
			flavors[j][c4] = temp;
			c1++;
			break;
			}
	}


      if (shared_ring -> outptr[j] >= NUMSLOTS){
		shared_ring -> outptr[j] = 0;
      } else {
		shared_ring -> outptr[j] = shared_ring -> outptr[j] + 1;
      }

		v(semid[PROD], j);
		v(semid[OUTPTR], j);
  	}

  	gettimeofday(&randtime, (struct timezone *)0);

	printf("\tCONS PROCESS PID: %d, TIME: %d , dozen #: %d\n", getpid(), (ushort)randtime.tv_usec, i + 1);

  	printf("\n\tplain\tjelly\tcoconut\thoney-dip\n");
	for(m = 0; m < DOZENS; m++) {
		printf("\t%d\t%d\t%d\t%d\n", flavors[0][m], flavors[1][m], flavors[2][m], flavors[3][m]);
	}
	printf("\n");
	for(m = 0; m < NUMFLAVORS; m++){
		for(n = 0; n < DOZENS; n++)
			flavors[m][n] = 0;

		}
  	}

return 0;

}
