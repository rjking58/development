using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MultiDimArrayExample
{
    class Program
    {
        static void Main(string[] args)
        {
            // multi dimensional
            int [,] myMatrix;

            myMatrix = new int[6,6];

            for(int i = 0 ; i < 6; i++)
                for(int j = 0; j < 6; j++)
                {
                    myMatrix[i,j] = i*j;
                }
            for(int i = 0 ; i < 6; i++)
                for(int j = 0; j < 6; j++)
                {
                    Console.WriteLine("myMatrix[{0},{1}] = {2}",i,j,myMatrix[i,j]);
                }

            // jagged.
            int [][] myJagArray = new int [5][];

            for (int i = 0; i < myJagArray.Length; i++)
            {
                myJagArray[i] = new int [i+7];
            }

            for( int i = 0; i < myJagArray.Length; i++)
            {
                Console.Write("myJagArray[{0}][array of length {1}] = ", i,myJagArray[i].Length);
                for (int j = 0; j < myJagArray[i].Length; j++)
                {
                    Console.Write("{0} ",myJagArray[i][j]);
                }
                Console.WriteLine();
            }
        }
    }
}
