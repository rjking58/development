using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VersioningExample
{
    public class TargetImplementation_V1
    {
        public void DoSomething(int paramA,
                                int paramB)
        {
            Console.WriteLine("paramA[{0}] paramB[{1}]",
                                paramA,
                                paramB);
        }
    }
    public class TargetImplementation_V2
    {
        public void DoSomething(int paramA,
                                int paramB,
                                bool paramCisValid,
                                int  paramC)
        {
            Console.WriteLine("paramA[{0}] paramB[{1}] paramCisValid[{2}] paramC[{3}]",
                                paramA,
                                paramB,
                                paramCisValid,
                                paramC);
        }
    }

    public class TargetImplementation_V3
    {
        public void DoSomething(int paramA,
                                int paramB,
                                bool paramCisValid,
                                int paramC)
        {
            Console.WriteLine("paramA[{0}] paramB[{1}] paramCisValid[{2}] paramC[{3}]",
                                paramA,
                                paramB,
                                paramCisValid,
                                paramC);
        }

        public void DoSomethingElse(int paramA)
        {
            Console.WriteLine("paramA[{0}]",paramA);
        }
    }

    public class XX
    {
        public void x()
        {
            throw new NotImplementedException();
        }
    }
}
