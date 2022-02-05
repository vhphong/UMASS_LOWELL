// permutations.cpp -- generate permutations using Heap's algorithm:
//		<https://en.wikipedia.org/wiki/Heap%27s_algorithm>
//
// Usage: permutations <number of elements>
//
// Author: Tom Wilkes - 2019

#include <iostream>
#include <vector>


int factorial(int n)
{
	if (n <= 1)
		return 1;
	else
		return n*factorial(n-1);
}


template <typename T>
void swap(T& a, T& b)
{
	T temp;
	
	temp = b;
	b = a;
	a = temp;
}


auto isEven = [] (int i) { return i%2 == 0; };


template <typename T>
void output(const std::vector<T>& v)
{
	for (T elem : v)
		std::cout << elem << ' ';
	std::cout << std::endl;
}


// Recursive implementation of Heap's algorithm
template <typename T>
void generate(int n, std::vector<T>& A)
{
	if (n == 1)
		output(A);
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			generate(n - 1, A);
			if (isEven(n))
				swap(A[i], A[n-1]);
			else
				swap(A[0], A[n-1]);
		}
		generate(n - 1, A);
	}
}


int main(int argc, char* argv[])
{
	int n = 0;
	
	if (argc == 2)
		n = atoi(argv[1]);
	else
	{
		std::cerr << "Usage: permutations <number of elements>\n";
		exit(-1);
	}
	
	int num = factorial(n);
	
	
	std::cout << "Generating " << num << " permutations of " << n << " integers:\n";
	
	std::vector<int> v_int;
	for (int i = 1; i <= n; i++)
		v_int.push_back(i);
	
	generate(n, v_int);
	
	std::cout << std::endl;
	
	
	std::cout << "Generating " << num << " permutations of " << n << " characters:\n";
	
	std::vector<char> v_char;
	for (int i = 1; i <= n; i++)
		v_char.push_back(i + 64); // convert i to upper-case character
	
	generate(n, v_char);
	
	return 0;
}
