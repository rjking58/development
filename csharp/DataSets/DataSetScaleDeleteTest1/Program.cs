using System;
using System.Collections.Generic;
using System.Text;

using System.Data;

namespace DataSetScaleDeleteTest1
{
    class MyObj
    {
        private int m_ID;
        private string m_ID_str;
        private bool m_deleted = false;
        public int ID
        {
            get
            {
                return m_ID;
            }
        }
        public MyObj(int ID)
        {
            m_ID = ID;
            m_ID_str = "myID[" + ID + "]";
        }
        public MyObj(int ID, string ID_str)
        {
            m_ID = ID;
            m_ID_str = ID_str;
        }
        public bool Deleted
        {
            get
            {
                return m_deleted;
            }
            set
            {
                m_deleted = value;
            }
        }
        public static void InitializeColumns(DataTable dt)
        {
            DataColumn IDCol = new DataColumn("ID",typeof(int));
            IDCol.Caption = "ID";
            IDCol.ReadOnly = false;
            IDCol.AllowDBNull = false;
            IDCol.Unique = true;
            
            DataColumn IDStrCol = new DataColumn("IDStr",typeof(string));
            
            dt.Columns.AddRange(new DataColumn[] {IDCol,IDStrCol});
        }
        
        public static void AddRowToArray(DataRow dr,
                                         List<MyObj> m_ary)
        {
            //Console.WriteLine(dr["ID"]);
            m_ary.Add(new MyObj((int) dr["ID"],dr["IDStr"].ToString()));
        }
        
        public void AddSelfToTable(DataTable dt)
        {
            DataRow dr = dt.NewRow();
            dr["ID"] = m_ID;
            dr["IDStr"] = m_ID_str;
            dt.Rows.Add(dr);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            const int DELETE_MODULO = 50;
            List<MyObj> ary = new List<MyObj>();
            LinkedList<MyObj> ll = new LinkedList<MyObj>();
            Dictionary<int,MyObj> dict = new Dictionary<int,MyObj>();
            
            DateTime startTime = DateTime.Now;
            LoadList(ary);
            DateTime endTime = DateTime.Now;
            TimeSpan duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("Create List: {0}:{1}:{2}.{3}",duration.Hours,duration.Minutes,duration.Seconds,duration.Milliseconds));
            Console.WriteLine("List count:" + ary.Count);
            PrintSeparator();
            
            startTime = DateTime.Now;
            LoadLinkedList(ll);
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            Console.WriteLine(String.Format("Create Linked List: {0}:{1}:{2}.{3}",duration.Hours,duration.Minutes,duration.Seconds,duration.Milliseconds));
            Console.WriteLine("Linked List count:" + ll.Count);
            PrintSeparator();
            
            startTime = DateTime.Now;
            LoadDictionary(dict);
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            Console.WriteLine(String.Format("Create Dictionary: {0}:{1}:{2}.{3}",duration.Hours,duration.Minutes,duration.Seconds,duration.Milliseconds));
            Console.WriteLine("Dictionary count:" + dict.Count);
            PrintSeparator();
            
            DataTable myObjTable = new DataTable("myObjs");
            MyObj.InitializeColumns(myObjTable);
            startTime = DateTime.Now;
            foreach(MyObj obj in ary)
            {
                obj.AddSelfToTable(myObjTable);
            }
            myObjTable.AcceptChanges();
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("Convert array of objects to DataTable: {0}:{1}:{2}.{3}",duration.Hours,duration.Minutes,duration.Seconds,duration.Milliseconds));
            Console.WriteLine("row count:" + myObjTable.Rows.Count);
            PrintSeparator();
            
            startTime = DateTime.Now;
            List<MyObj> loadedAry = new List<MyObj>();
            loadedAry.Capacity = 1000000;
            foreach(DataRow dr in myObjTable.Rows)
            {
                MyObj.AddRowToArray(dr,loadedAry);
            }
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("convert DataTable to array of objects..: {0}:{1}:{2}.{3}",duration.Hours,duration.Minutes,duration.Seconds,duration.Milliseconds));
            Console.WriteLine("loadedAry count:" + loadedAry.Count);
            PrintSeparator();
            
            // delete every index that is mod 100...

            startTime = DateTime.Now;
            int currRow = 0;
            foreach(DataRow dr in myObjTable.Rows)
            {
                // touch it..
                if((currRow % DELETE_MODULO) == 0)
                {
                    dr.Delete();
                }
                currRow++;
            }
            myObjTable.AcceptChanges();
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("delete every {0}th item in DataTable: {1}:{2}:{3}.{4}",
                                            DELETE_MODULO,
                                            duration.Hours,
                                            duration.Minutes,
                                            duration.Seconds,
                                            duration.Milliseconds));
            Console.WriteLine("datatable count:" + myObjTable.Rows.Count);
            PrintSeparator();
            
            startTime = DateTime.Now;
            currRow = 0;
            foreach(MyObj obj in ary)
            {
                // touch it..
                if((currRow % DELETE_MODULO) == 0)
                {
                    obj.Deleted = true;
                }
                currRow++;
            }
            for(currRow = 0;
                currRow < ary.Count;
                currRow++)
            {
                if (ary[currRow].Deleted)
                {
                    ary.RemoveAt(currRow);
                }
            }
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("delete with RemoveAt in List every {0}th item: {1}:{2}:{3}.{4}",
                                            DELETE_MODULO,
                                            duration.Hours,
                                            duration.Minutes,
                                            duration.Seconds,
                                            duration.Milliseconds));
            Console.WriteLine("list count:" + ary.Count);
            PrintSeparator();
            
            
            ary.Clear();
            LoadList(ary);
            // now delete smarter..
            startTime = DateTime.Now;
            currRow = 0;
            foreach(MyObj obj in ary)
            {
                // touch it..
                if((currRow % DELETE_MODULO) == 0)
                {
                    obj.Deleted = true;
                }
                currRow++;
            }
            // now another pass to copy the ary to a new ary but leave behind the deleted items.
            List<MyObj> ary2 = new List<MyObj>();
            ary2.Capacity = 1000100;
            for(currRow = 0;
                currRow < ary.Count;
                currRow++               )
            {
                if(! ary[currRow].Deleted)
                {
                    ary2.Add(ary[currRow]);
                }
            }
            ary = ary2;
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("delete with ary move in List every {0}th item: {1}:{2}:{3}.{4}",
                                            DELETE_MODULO,
                                            duration.Hours,
                                            duration.Minutes,
                                            duration.Seconds,
                                            duration.Milliseconds));
            Console.WriteLine("list count:" + ary.Count);
            PrintSeparator();
            
              
            // now a delete in dictionary..
            startTime = DateTime.Now;
            LinkedList<int> deleteList = new LinkedList<int>();
            currRow = 0;
            foreach(KeyValuePair<int,MyObj> kvp in dict)
            {
                if((currRow % DELETE_MODULO) == 0)
                {
                    deleteList.AddLast(kvp.Value.ID);
                }
                currRow++;
            }
            foreach(int key in deleteList)
            {
                dict.Remove(key);
            }
            
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);

            Console.WriteLine(String.Format("delete in Dictionary every {0}th item: {1}:{2}:{3}.{4}",
                                            DELETE_MODULO,
                                            duration.Hours,
                                            duration.Minutes,
                                            duration.Seconds,
                                            duration.Milliseconds));
            Console.WriteLine("dict count:" + dict.Count);
            PrintSeparator();
            

            // now a delete in linked list..
            startTime = DateTime.Now;
            currRow = 0;
            foreach(MyObj obj in ll)
            {
                if((currRow % DELETE_MODULO) == 0)
                {
                    obj.Deleted = true;
                }
                currRow++;
            }
            // now delete by node..
            LinkedListNode<MyObj> ll_node = ll.First;
            LinkedListNode<MyObj> ll_nextnode = null;
            while(ll_node != null)
            {
                if(ll_node.Value.Deleted)
                {
                    ll_nextnode = ll_node.Next;
                    ll.Remove(ll_node);
                    ll_node = ll_nextnode;
                }
                else
                {
                    ll_node = ll_node.Next;
                }
            }
            endTime = DateTime.Now;
            duration = endTime.Subtract(startTime);
            
            Console.WriteLine(String.Format("delete in Linked List every {0}th item: {1}:{2}:{3}.{4}",
                                            DELETE_MODULO,
                                            duration.Hours,
                                            duration.Minutes,
                                            duration.Seconds,
                                            duration.Milliseconds));
            Console.WriteLine("linked list count:" + ll.Count);
            PrintSeparator();            
        }
        
        static void LoadDictionary(Dictionary<int,MyObj> dict)
        {
            for(int obj_count = 0;
                obj_count < 1000000;
                obj_count++)
            {
                dict.Add(obj_count,new MyObj(obj_count));
            }
        }
        static void LoadLinkedList(LinkedList<MyObj> ll)
        {
            for(int obj_count = 0;
                obj_count < 1000000;
                obj_count++)
            {
                ll.AddLast(new MyObj(obj_count));
            }
        }
        static void LoadList(List<MyObj> list)
        {
            list.Capacity = 1000100;
            for(int obj_count = 0;
                obj_count < 1000000;
                obj_count++)
            {
                list.Add(new MyObj(obj_count));
            }
        }
        static void PrintSeparator()
        {
            Console.WriteLine("================================================");
            Console.WriteLine("================================================");
        }
    }
}
