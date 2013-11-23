using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ADOTest
{
    class Program
    {
        static void Main(string[] args)
        {
            rjkTestTableAdapters.rjk_test_tableTableAdapter rjk_test_tableTA = new rjkTestTableAdapters.rjk_test_tableTableAdapter();
            rjkTest.rjk_test_tableDataTable rjk_test_tableDT = new rjkTest.rjk_test_tableDataTable();
            rjk_test_tableTA.Fill(rjk_test_tableDT);
            
            for(int currRow = 0; currRow < rjk_test_tableDT.Count; currRow++)
            {
                System.Console.Write(rjk_test_tableDT[currRow].str1 + " ");
                System.Console.Write(rjk_test_tableDT[currRow].str2 + " ");
                System.Console.Write(rjk_test_tableDT[currRow].val1 + " ");
                System.Console.WriteLine(" ");
            }
        }
    }
}
