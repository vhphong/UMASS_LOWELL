/**********************************************
Class: 		CS308 - Operating Systems
Name: 		DangNhi Ngoc Ngo
Student ID: 	01553277
Email: 		DangNhi_Ngo@student.uml.edu
Homework 3
***********************************************/

#ifndef DONUTS_H
#define DONUTS_H


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <stdio.h>

#define	SEMKEY (key_t)549351763
#define	MEMKEY	(key_t)549351763

#define DOZENS 		 12
#define LOOPS		 10
#define NUMFLAVORS   4
#define NUMSLOTS     50
#define NUMSEMIDS    3
#define PROD         0
#define CONSUMER     1
#define OUTPTR       2

struct donut_ring{
  int flavor  [NUMFLAVORS]  [NUMSLOTS];
  int outptr  [NUMFLAVORS];
};

/* CUSTOM FUNCTIONS */

/**
 * @parameter: timeval randtime
 * @return: list of xsub values;
 */
ushort* generateXSub(struct timeval randtime);

/**
 * @param
 */
void initFlavors(int flavors[NUMFLAVORS][DOZENS]);
void printAllFlavors(int flavors[NUMFLAVORS][DOZENS]);

extern int p (int, int);
extern int v (int, int);
extern int semsetall (int, int, int);

#endif