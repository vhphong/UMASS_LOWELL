/**********************************************
Class: 		CS308 - Operating Systems
Name: 		DangNhi Ngoc Ngo
Student ID: 	01553277
Email: 		DangNhi_Ngo@student.uml.edu
Homework 4
***********************************************/

/*****************************************************************/
/* INCLUDE FILES, DEFINES AND DECLARATIONS AS SEEN IN CLASS      */
/*        THESE BELONG IN A    .h     FILE                       */
/*****************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define	SEMKEY (key_t)549351763
#define	MEMKEY	(key_t)549351763

#define NUMCONSUMERS    5
#define	NUMPRODUCERS	5
#define DOZENS 		 12
#define LOOPS		 10
#define NUMFLAVORS   4
#define NUMSLOTS     50
#define NUMSEMIDS    3
#define PROD         0
#define CONSUMER     1
#define OUTPTR       2


/**
 * @param
 */
void initFlavors(int flavors[NUMFLAVORS][DOZENS]);
void printAllFlavors(int flavors[NUMFLAVORS][DOZENS]);
void updateDonutRings(int num);
ushort* generateXSub(struct timeval randtime);

struct  donut_ring {
	int     flavor [NUMFLAVORS] [NUMSLOTS];
	int     outptr [NUMFLAVORS];
	int		in_ptr [NUMFLAVORS];
	int		serial [NUMFLAVORS];
	int		spaces [NUMFLAVORS];
	int		donuts [NUMFLAVORS];
};

/**********************************************************************/
/* SIGNAL WAITER, PRODUCER AND CONSUMER THREAD FUNCTIONS              */
/**********************************************************************/

void	*sig_waiter ( void *arg );
void	*producer   ( void *arg );
void	*consumer ( void *arg) ;
void    sig_handler ( int );

/**********************    END HEADER FILE         *******************/
