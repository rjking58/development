using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
namespace Attribute1
{
    class SimpleClass
    {
        private string m_name;
        public string Name
        {
            get
            {
                return m_name;
            }
            set
            {
                m_name = value;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

            SimpleClass sc = new SimpleClass();
            PropertyInfo pi = sc.GetType().GetProperty("Name");

            Console.WriteLine(pi.Attributes);
            
        }
    }
}
