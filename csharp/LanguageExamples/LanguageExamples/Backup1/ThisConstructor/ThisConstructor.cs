using System;
using System.Collections.Generic;
using System.Text;

namespace ThisConstructor
{
    class XYCoord
    {
        private int     m_x;
        private int     m_y;
        private string  m_name;

        public XYCoord(string name)
            : this(333, 999, name)
        {
        }
        public XYCoord(XYCoord ob1,string name)
            : this(ob1.m_x, ob1.m_y,name)
        {
        }
        public XYCoord(int x, int y, string name)
        {
            m_x = x;
            m_y = y;
            m_name = name;
        }

        public void Iam()
        {
            System.Console.WriteLine(     "name(" + m_name + ")"
                                        + "m_x(" + m_x + ")"
                                        + "m_y(" + m_y + ")");
        }
    }

    class ThisConstructor
    {
        static void Main(string[] args)
        {
            XYCoord ob1 = new XYCoord("ob1");
            XYCoord ob2 = new XYCoord(4,5,"ob2");
            XYCoord ob3 = new XYCoord(ob2,"ob3");
            ob1.Iam();
            ob2.Iam();
            ob3.Iam();

        }
    }
}
