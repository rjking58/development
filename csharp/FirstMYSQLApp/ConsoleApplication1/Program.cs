using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Sql;

namespace FirstMYSQLApp
{
    class Program
    {
        static void Main(string[] args)
        {
            TestDataset1TableAdapters.rjk1TableAdapter rjk1TA = new FirstMYSQLApp.TestDataset1TableAdapters.rjk1TableAdapter();
            TestDataset1.rjk1DataTable rjk1DT = new TestDataset1.rjk1DataTable();
            

            rjk1TA.Fill(rjk1DT);
            System.Console.WriteLine("count:" + rjk1DT.Rows.Count);
            for (int currRow = 0; currRow < rjk1DT.Rows.Count; currRow++)
            {
                System.Console.Write(rjk1DT.Rows[currRow]["str1"] + " ");
                System.Console.Write(rjk1DT.Rows[currRow]["str2"] + " ");
                System.Console.Write(rjk1DT.Rows[currRow]["val1"] + " ");
                System.Console.WriteLine(" ");
            }
            //TestDataset1.rjk1[0]["str1"];
        }
    }
}
