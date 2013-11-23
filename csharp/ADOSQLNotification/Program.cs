using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;
using System.Threading;

namespace ADOSQLNotification
{
    class Program
    {
        static SqlDependency m_dependency = null;
        static SqlCommand    m_dependency_cmd = null;
        static bool          m_restartWatch = false;
        static SqlConnection m_conn = null;
        
        static void Main(string[] args)
        {
            //Console.WriteLine(EnoughPermission());
            SqlConnectionStringBuilder scsb = new SqlConnectionStringBuilder();
            scsb.DataSource = @"79-RKING2\RKING";
            scsb.InitialCatalog = "EzWeb";
            scsb.UserID = "notifylistener";
            scsb.Password = "notifylistener";
            // this is used if we are using Windows Authentication (which we are not)
            //scsb.IntegratedSecurity = true;
            Console.WriteLine(scsb.ConnectionString);
            m_conn = new SqlConnection(scsb.ConnectionString);
            
            m_conn.Open();            
            SqlDependency.Start(scsb.ConnectionString);

//            KeyMapOrderDS kmoDS = new KeyMapOrderDS();
            
//            KeyMapOrderDSTableAdapters.KeyMapOrderTableAdapter kmoTA = new ADOSQLNotification.KeyMapOrderDSTableAdapters.KeyMapOrderTableAdapter();
            
//            kmoTA.Fill(kmoDS.KeyMapOrder,1);

//            Console.WriteLine("row count:" + kmoDS.KeyMapOrder.Rows.Count);
//            foreach(KeyMapOrderDS.KeyMapOrderRow row in kmoDS.KeyMapOrder.Rows)
//            {
//                Console.WriteLine(String.Format("{0,4} {1,2}",row.OutRon, row.KeyOrder));
//            }
            
            startDependencyWatch();
                        
            for(int x = 0; x < 240; x++)
            {
                Console.Write(".");
                Thread.Sleep(1000);    
                if(m_restartWatch)
                {            
                    startDependencyWatch();
                    m_restartWatch = false;
                }
            }
            m_conn.Close();
            SqlDependency.Stop(scsb.ConnectionString);
        }

        static void  kmoDependency_OnChange(object sender, SqlNotificationEventArgs e)
        {
            Console.WriteLine("change happened");
            Console.WriteLine(e.Info.ToString());
            Console.WriteLine(e.Source.ToString());
            Console.WriteLine(e.Type.ToString());
            Console.WriteLine("restarting dependency watch...");
            m_restartWatch = true;
        }
        
        static private bool EnoughPermission()
        {
            SqlClientPermission perm = new SqlClientPermission(System.Security.Permissions.PermissionState.Unrestricted);
            try
            {
                perm.Demand();
                return true;
            } 
            catch (System.Exception)
            {
                return false;
            }
        }

        // create a command object for SQL to be watched...
        // then our dependency object...
        // then activity the relationship with a read using the
        // command object.
        static void startDependencyWatch()
        {
            // select to be compared against..
            m_dependency_cmd = new SqlCommand("SELECT OUTRON FROM dbo.KeyMapOrder",m_conn);
            // our dependency object..
            
            m_dependency = new SqlDependency(m_dependency_cmd);
            // link up the event to our change handling mechanism.
            m_dependency.OnChange += new OnChangeEventHandler(kmoDependency_OnChange);
            
            // required for dependency to work correctly..
            SqlDataReader rdr = m_dependency_cmd.ExecuteReader();
            while (rdr.Read())
            {
                for(int currColumn = 0;
                    currColumn < rdr.FieldCount;
                    currColumn++)
                {
                    Console.Write(rdr.GetValue(currColumn) + " ");
                }
                Console.WriteLine();
            }
            rdr.Close();
        }
    }
}
