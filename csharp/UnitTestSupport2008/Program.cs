using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UnitTestSupport2008
{

    public class MyClassToTest
    {
        private string m_first = "";
        private string m_second = "";
        public MyClassToTest(string first, string second)
        {
            m_first = first;
            m_second = second;
        }
        
        public string OneTwo()
        {
            return m_first + " " + m_second;
        }

        public string TwoOne()
        {
            return m_second + " " + m_first;
        }
        
    }
    class Program
    {
        static void Main(string[] args)
        {
            
        }
    }
}
