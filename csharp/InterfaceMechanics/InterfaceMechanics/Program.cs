using System;
using System.Collections.Generic;
using System.Text;

namespace InterfaceMechanics
{
    public enum simpleEnum
    {
        VAL1,
        VAL2
    }
    interface simple
    {
        simpleEnum someMethod();
    }

    class simplec : simple
    {
        public simpleEnum someMethod()
        {
            return simpleEnum.VAL1;
        }
    }
    
    
    class Program
    {
        enum simpleEnum2
        {
            VAL1,
            VAL2
        }
        static void Main(string[] args)
        {
            simple smple = new simplec();

            Console.WriteLine(smple.someMethod());
        }
    }
}
