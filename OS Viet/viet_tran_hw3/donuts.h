//Viet Tran
//Assignment 3
//Operating System
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <errno.h>

#define	    SEMKEY	    (key_t)5493517
#define	    MEMKEY	    (key_t)5493517
#define	    NUMFLAVORS	    4
#define	    NUMSLOTS        50
#define	    NUMSEMIDS	    3
#define	    PROD	    0
#define	    CONSUMER	    1
#define	    OUTPTR	    2

extern char *pcdonuts[];

struct	donut_ring{
  int flavor[NUMFLAVORS][NUMSLOTS];
  int outptr[NUMFLAVORS];
};

extern int  p (int, int);
extern int  v (int, int);
extern int  semsetall (int, int, int);