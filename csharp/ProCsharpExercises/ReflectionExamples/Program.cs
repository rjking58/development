using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace ReflectionExamples
{
    class MyClass2
    {
        public string Name
        {
            get
            {
                return "george";
            }
        }
    }
    class MyClass
    {
        private int m_intMember;
        private MyClass2 m_myClass2Member;
        public void MyMethod1(int intParam,MyClass2 myClass2Param)
        {

        }
    }
    class Program
    {

        static void Main(string[] args)
        {
            Type myclassType = typeof(MyClass);

            MethodInfo[] mcMethods = myclassType.GetMethods();

            foreach (MethodInfo mi in mcMethods)
            {
                Console.Write(mi.ReturnType.Name + " " + mi.Name + "(");

                ParameterInfo [] paramsOfMi = mi.GetParameters();
                bool first = true;
                foreach (ParameterInfo pi in paramsOfMi)
                {
                    if (!first)
                    {
                        Console.Write(",");
                    }
                    else
                    {
                        first = false;
                    }
                    Console.Write(pi.ParameterType.Name + " " + pi.Name);
                }

                Console.WriteLine(")");
            }

        }
    }
}
