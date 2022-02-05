// mcs a1.cs
// mono a1.exe

using System; 
                      
  
public class OPL { 
//Prints the array 
    static void printArr(int []a, int n) 
    { 
        for (int i=0; i<n; i++) 
            Console.Write(a[i] + " "); 
        Console.WriteLine(); 
    } 
   
    //Generating permutation using Heap Algorithm 
    static void heapPermutation(int []a, int size, int n) 
    { 
        // if size becomes 1 then prints the obtained 
        // permutation 
        if (size == 1) 
            printArr(a,n); 
   
        for (int i=0; i<size; i++) 
        { 
            heapPermutation(a, size-1, n); 
   
            // if size is odd, swap first and last 
            // element 
            if (size % 2 == 1) 
            { 
                int temp = a[0]; 
                a[0] = a[size-1]; 
                a[size-1] = temp; 
            } 
   
            // If size is even, swap ith and last 
            // element 
            else
            { 
                int temp = a[i]; 
                a[i] = a[size-1]; 
                a[size-1] = temp; 
            } 
        } 
    } 
   
    // Driver code 
    public static void Main() 
    { 
        string user; 
        int n;
        //take the input as string
        Console.Write("Enter integer: ");
        user = Console.ReadLine();
        //convert string to integer
        n = Convert.ToInt32(user);
        int[] a = new int[n];
        for (int i=0; i < n; i++)
        {
          a[i] = i+1;
        }
        heapPermutation(a, a.Length, a.Length); 
    } 
} 
// https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/