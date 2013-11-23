using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace ADOChapter3ConnectionBuilders
{
    class Program
    {
        static void Main(string[] args)
        {
            SqlConnectionStringBuilder bldr = new SqlConnectionStringBuilder();

            bldr.DataSource = @".\SQLExpress";
            //bldr["Data Source"] = @".\SQLExpress";
            bldr.InitialCatalog = "Northwind";
            //bldr["Initial Catalog"] = "Northwind";
            bldr.IntegratedSecurity = true;
            //bldr["Integrated Security"] = true;

            Console.WriteLine("resulting connection string [{0}]", bldr.ConnectionString);

            SqlConnection cn = new SqlConnection(bldr.ConnectionString);
            cn.Open();
            cn.Close();
        }
    }
}
