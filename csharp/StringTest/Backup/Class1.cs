using System;

namespace StringTest
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
            const int OFFSETS_SZ = 4;
            String someStr = "123 abc 987 joe_mama abc woof bark woof abc ninety woof abc";
            int found_ofst;
            int found_cnt = 0;
            int [] offsets = new int[OFFSETS_SZ];
            for(int curr_offset = 0; 
                curr_offset < OFFSETS_SZ;
                curr_offset++)
            {
                offsets[curr_offset] = -1;
            }

            //someStr2 = (String) someStr.Clone();

            //System.Console.WriteLine("someStr=" + someStr);
            //System.Console.WriteLine("someStr2=" + someStr2);


            System.Console.WriteLine("someStr.IndexOf(\"abc\")=" + someStr.IndexOf("abc"));

            found_ofst = someStr.IndexOf("uvw");
            System.Console.WriteLine("found_ofst = " + found_ofst);

            found_ofst = someStr.IndexOf("abc");
            
            while(found_ofst >= 0)
            {
                found_cnt++;
                offsets[found_cnt-1] = found_ofst;
                found_ofst = someStr.IndexOf("abc",found_ofst+1);
            }

            for(int curr_offset = 0; 
                curr_offset < OFFSETS_SZ;
                curr_offset++)
            {
                System.Console.WriteLine(offsets[curr_offset]);
            }


    		//
			// TODO: Add code to start application here
			//
		}
	}
}
