// QuickSort code for 91.404
// UMass Lowell 91.404 Analysis of Algorithms
// Prof. Karen Daniels (Fall 2000)
// Java implementation of p. 154's QuickSort pseudo-code
// of Cormen, Leiserson, Rivest


public class QuickSort
{
 static int n = 8;

   public static void main(String[] args)
     {
      int A[] = {0,5,3,2,6,4,1,3,7};

      QuickSort(A,1,n);
      Print(A,1,n);
     }

   public static void QuickSort(int[] A, int p, int r)
     {
      if (p < r)
       {
        int q = Partition(A, p, r);
        QuickSort(A, p, q);
        QuickSort(A, q+1, r);
       }
     }

   public static int Partition(int[] A, int p, int r)
     {
      Print(A,p,r);

      int x = A[p];
      int i = p-1;
      int j = r+1;
      while (true)
       {
        do { j--;} while (A[j] > x);
        do { i++;} while (A[i] < x);
        if (i<j) Exchange(A, i, j);
        else return j;
       }
     }

   public static void Exchange(int[] A, int i, int j)
     {
 	int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
     }


   public static void Print(int[] A, int p, int r)
     {
      System.out.print("\nA= ");
      for (int i=p; i<=r; i++)
        System.out.print(A[i] + "  "); 
      System.out.println("");   
     }
}
