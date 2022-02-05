// UMass Lowell
// Organization of Programming Languages (OPL)
// by Phong Vo - Spring 2019
// Assignment 1

using System;
using System.Text;

class Permutations
{
	public void swap(ref int a, ref int b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	public void calPermut(int []list, int k, int m)
	{
		int i;
		if (k == m)
		{
			for (i = 0; i <= m; i++)
				Console.Write ("{0}",list [i]);
			Console.Write (" ");
		}
		else
			for (i = k; i <= m; i++)
			{
				swap(ref list [k], ref list [i]);
				calPermut(list, k+1, m);	// recursively call calPermut
				swap(ref list [k], ref list [i]);
			}
	}
}


class A1Permutation
{
	public static void Main()
	{
		int n,i;
		Permutations test = new Permutations();
		int[] arr1 = new int[5];
		
		Console.WriteLine("\n\n Recursion : Generate all possible permutations of an array :");
		Console.WriteLine("------------------------------------------------------------------");
		Console.Write(" Input the number of elements to store in the array [maximum 5 digits ] :");
		n = Convert.ToInt32(Console.ReadLine());
		Console.Write(" Input {0} number of elements in the array :\n",n);
		for(i=0;i<n;i++)
		{
			Console.Write(" element - {0} : ",i);
			arr1[i] = Convert.ToInt32(Console.ReadLine());
		}      

        Console.Write ("\n The Permutations with a combination of {0} digits are : \n",n);
		test.calPermut(arr1, 0, n-1);
		Console.Write ("\n\n");
	}
}