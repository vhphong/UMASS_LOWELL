using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        public static void getCombinations(string combination, int[] arr, int n)
        {
            //If there are no more available n spaces to fill, print the current combination
            if (n == 0)
            {
                Console.WriteLine(combination);
                return;
            }
            //Recursively call function with the current combination,
            //a new array with the first index removed to concatenate the
            //next character of the array into the combination, and finally the
            //number of available n spaces left 
            for (int i = 0; i < arr.Length; i++)
            {
                string currentCombination = combination == "" ? combination + arr[i].ToString() : combination + " " + arr[i].ToString();
                int[] newArray = arr.Skip(i+1).ToArray();
                getCombinations(currentCombination, newArray, n - 1);
            }
        }

        static void Main(string[] args)
        {
            // Get k and n inputs
            System.Console.Write("Enter a number for n: ");
            int nInput = int.Parse(Console.ReadLine());
            System.Console.Write("Enter a number for k: ");
            int kInput = int.Parse(Console.ReadLine());

            //Populate int array
            int[] arr = new int[kInput];
            for (int i = 0; i < kInput; i++)
            {
                arr[i] = i+1;
            }
            
            //Call recursive function to obtain combination
            getCombinations("", arr, nInput);
        }
    }
}
