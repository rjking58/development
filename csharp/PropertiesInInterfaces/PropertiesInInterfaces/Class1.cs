using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PropertiesInInterfaces
{
    interface IF_WithProperty
    {
        string myproperty { get; }
    }


    public class Class1 : IF_WithProperty
    {
        public string myproperty
        {
            get
            {
                return "x";
            }
        }
    }
}
