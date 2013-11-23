using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TestAssembly2;
namespace GridEngy1_weezl
{
    public class GridEngyClass
    {
        public static String retrieveFromAssembly()
        {
            return TestAssembly2Class.getName();
        }
    }
}
