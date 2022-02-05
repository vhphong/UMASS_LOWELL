/**
 * Example of openmp parallel for
 * 
 * To compile, enter:
 *
 *	g++ -fopenmp -o openmp2 openmp2.cpp
 *
 */

#include <omp.h>
#include <iostream>
#include <vector>

using namespace std;


int main(void)
{
	/* sequential code */
	int nthreads = omp_get_max_threads();
	cout << "openmp example: max threads == " << nthreads << endl;
	
	cout << "main thread BEFORE parallel for: Number of threads == " <<	omp_get_num_threads()
	     << ", my thread num == " << omp_get_thread_num()
		 << endl << endl;
			
	vector<int> a(nthreads);
	vector<int> b(nthreads);
	
	for (int i = 0; i < nthreads; i++) {
		a[i] = i+1;
		b[i] = (i+1)*10;
	}
	
	vector<int> c(nthreads);	

	#pragma omp parallel for
	for (int i = 0; i < nthreads; i++) {
		#pragma omp critical
		{
			cout << "In parallel for: i == " << i
				 << ", number of threads == " << omp_get_num_threads()
				 << ", my thread num == " << omp_get_thread_num()
				 << endl;
		}
		
		c[i] = a[i] + b[i];
	}

	/* sequential code */
	cout << "\nmain thread AFTER parallel for: Number of threads == " << omp_get_num_threads()
		 << ", my thread num == " << omp_get_thread_num()
		 << endl << endl;
			
	for (int i = 0; i < nthreads; i++) {
		cout << "c[" << i << "] == " << c[i] << endl;
	}
	
	return 0;
}
