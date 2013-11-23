using System;

namespace Arrays
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class ArrayDemo
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
			int[] my_i_ary = new int[15];
			
			for(int my_i_ary_ofst = 0;
			    my_i_ary_ofst < my_i_ary.Length;
			    my_i_ary_ofst++)
	        {
	            my_i_ary[my_i_ary_ofst] = my_i_ary_ofst*my_i_ary_ofst;
            }
			for(int my_i_ary_ofst = 0;
			    my_i_ary_ofst < my_i_ary.Length;
			    my_i_ary_ofst++)
            {
                // yah.. the sizes for the numeric fields
                // assume the ofst < 100.. yup.. they do
                Console.WriteLine("my_i_ary[{0,2}]({1,4})",
                                  my_i_ary_ofst,
                                  my_i_ary[my_i_ary_ofst]);
            }
            
            // multiDim (rectangular)
            int[,] my_multi_i_ary1 = new int[4,10];
            for(int firstDim = 0; firstDim < 4; firstDim++)
            {
                for(int secondDim = 0; secondDim < 10; secondDim++)
                {
                    my_multi_i_ary1[firstDim,secondDim] = (firstDim*100) + secondDim;
                }
            }
            for(int firstDim = 0; firstDim < 4; firstDim++)
            {
                for(int secondDim = 0; secondDim < 10; secondDim++)
                {
                    Console.WriteLine("my_multi_i_ary1[{0,2},{1,2}]({2,3})",
                        firstDim,
                        secondDim,
                        my_multi_i_ary1[firstDim,secondDim]);
                   
                }
            }
            // multiDim (jagged)
            int [][] jaggy = new int [4][];
            jaggy[0] = new int[5];
            jaggy[1] = new int[6];
            jaggy[2] = new int[3];
            jaggy[3] = new int[4];                                    
            for(int firstDim = 0; firstDim < jaggy.Length; firstDim++)
            {
                for(int secondDim = 0; secondDim < jaggy[firstDim].Length; secondDim++)
                {
                    jaggy[firstDim][secondDim] =  (firstDim*100) + secondDim;
                }
            }
            for(int firstDim = 0; firstDim < jaggy.Length; firstDim++)
            {
                for(int secondDim = 0; secondDim < jaggy[firstDim].Length; secondDim++)
                {
                    Console.WriteLine("jaggy[{0,2},{1,2}]({2,3:000})",
                        firstDim,
                        secondDim,
                        jaggy[firstDim][secondDim]);

                }
            }
            
		}
	}
}
