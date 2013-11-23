using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InnerClasses
{
    public class OuterClass 
    {
        private int m_oc_i1 = 0;
        
        public class InnerClass
        {
            OuterClass m_parent = null;

            public InnerClass(OuterClass p_parent)
            {
                m_parent = p_parent;
            }
            public void change_OC_I1(int val)
            {
                m_parent.m_oc_i1 = val;
            }
        }

        public void show_oc_i1()
        {
            Console.WriteLine(m_oc_i1);
        }
        static public void Main()
        {
            OuterClass oc = new OuterClass();
            InnerClass ic = new InnerClass(oc);

            oc.show_oc_i1();
            ic.change_OC_I1(10);

            oc.show_oc_i1();
            ic.change_OC_I1(20);

            oc.show_oc_i1();
            ic.change_OC_I1(30);

            oc.show_oc_i1();
            ic.change_OC_I1(40);
            oc.show_oc_i1();
        }
    }

}
