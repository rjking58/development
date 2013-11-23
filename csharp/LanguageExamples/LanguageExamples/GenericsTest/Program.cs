using System;
using System.Collections.Generic;
using System.Text;

namespace GenericsTest
{

    class SimpleGeneric<T>
    {
        T m_val;
        public SimpleGeneric(T val)
        {
            m_val = val;
        }

        public T GetVal()
        {
            return m_val;
        }
    }

    class myClass
    {
        private int m_id;
        public myClass(int id)
        {
            m_id = id;
        }

        public override string ToString()
        {
            return "id(" + m_id + ")";
        }
        public override bool Equals(object obj)
        {
            bool areEqual = false;
            if(obj is myClass)
            {
                areEqual = (((myClass) obj).m_id == m_id);
            }
            return areEqual;
        }
        public override int GetHashCode()
        {
            return m_id;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            List<myClass> myclass_ar = new List<myClass>();
                
            myclass_ar.Add(new myClass(1));
            myclass_ar.Add(new myClass(2));
            myclass_ar.Add(new myClass(3));
            
            Console.WriteLine("myclass_ar.Count[" + myclass_ar.Count + "]");
            
            foreach (myClass instance in myclass_ar)
            {
                Console.WriteLine(instance);
            }
            
            myclass_ar.RemoveAt(1);
            Console.WriteLine("after remove..");
            Console.WriteLine("myclass_ar.Count[" + myclass_ar.Count + "]");            
            Console.WriteLine();
            foreach (myClass instance in myclass_ar)
            {
                Console.WriteLine(instance);
            }
            myclass_ar.Add(new myClass(4));            
            Console.WriteLine("after add..");
            Console.WriteLine("myclass_ar.Count[" + myclass_ar.Count + "]");            
            Console.WriteLine();
            foreach (myClass instance in myclass_ar)
            {
                Console.WriteLine(instance);
            }
        
            //lookup example inside a SortedList
            SortedList<int,int> m_IntLookup = new SortedList<int,int>();
            m_IntLookup.Add(1,1);
            m_IntLookup.Add(3,3);
            m_IntLookup.Add(5,5);
            for (int int_to_lookup = 0;
                 int_to_lookup < 10;
                 int_to_lookup++)
            {
                if(m_IntLookup.ContainsKey(int_to_lookup))
                {
                    Console.WriteLine(int_to_lookup + " found");
                }
                else
                {
                    Console.WriteLine(int_to_lookup + " NOT found");
                }
            }     
            
            //linked list tests..
            LinkedList<myClass> ll_tst = new LinkedList<myClass>();
            ll_tst.AddLast(new myClass(1));
            ll_tst.AddLast(new myClass(2));
            ll_tst.AddLast(new myClass(3));
            ll_tst.AddLast(new myClass(4));
            
            // now find #3
            LinkedListNode<myClass> ll_node = ll_tst.Find(new myClass(2));
            
            Console.WriteLine(((myClass)ll_node.Value).ToString());
            // delete it
            Console.WriteLine("deleting found node");
            ll_tst.Remove(ll_node);
            // print the rest..
            foreach(myClass mc in ll_tst)
            {
                Console.WriteLine(mc.ToString());
            }
            
            // Get a specific instance..
            for(int idx_to_find = 0;
                idx_to_find < 3;
                idx_to_find++)
            {
                int curr_idx = 0;
                myClass found_mc = null;
                foreach(myClass mc in ll_tst)
                {
                    if (curr_idx == idx_to_find)
                    {
                        found_mc = mc;
                        break;
                    }
                    curr_idx++;
                }
                Console.WriteLine("idx " + idx_to_find + "[" + found_mc.ToString() + "]");
            }
            
            // stack generic..
            Stack<int> m_stack = new Stack<int>();
            
            m_stack.Push(1);
            m_stack.Push(2);
            m_stack.Push(3);
            m_stack.Push(4);
            m_stack.Push(5);
            m_stack.Push(6);
            
            while(m_stack.Count != 0)
            {
                int popped = m_stack.Pop();
                Console.Write(popped + " ");
            }
            Console.WriteLine();

            //SimpleGeneric class test..
            SimpleGeneric<int> sg_i = new SimpleGeneric<int>(10);
            SimpleGeneric<string> sg_s = new SimpleGeneric<string>("woohoo");
            Console.WriteLine("SimpleGeneric<int> sg_i[" + sg_i.GetVal() + "]  SimpleGeneric<string> sg_s[" + sg_s.GetVal() + "]");

        }
    }
}
