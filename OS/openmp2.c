/**
 * Example of openmp parallel for
 * 
 * To compile, enter:
 *
 *	gcc -fopenmp openmp.c
 *
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/* sequential code */
	int nthreads = omp_get_max_threads();
	printf("openmp example: max threads == %d\n", nthreads);
	
	printf("main thread BEFORE parallel for: Number of threads == %d, my thread num == %d\n\n",
			omp_get_num_threads(), omp_get_thread_num());
			
	int* a = malloc( nthreads*sizeof(int) );
	int* b = malloc( nthreads*sizeof(int) );
	int* c = malloc( nthreads*sizeof(int) );

	for (int i = 0; i < nthreads; i++) {
		a[i] = i+1;
		b[i] = (i+1)*10;
	}
	
	#pragma omp parallel for
	for (int i = 0; i < nthreads; i++) {
		printf("In parallel for: i == %d, number of threads == %d, my thread num == %d\n",
				i, omp_get_num_threads(), omp_get_thread_num());
		c[i] = a[i] + b[i];
	}

	/* sequential code */
	printf("\nmain thread AFTER parallel for: Number of threads == %d, my thread num == %d\n\n",
			omp_get_num_threads(), omp_get_thread_num());
			
	for (int i = 0; i < nthreads; i++) {
		printf("c[%d] == %d\n", i, c[i]);
	}
	
	return 0;
}
