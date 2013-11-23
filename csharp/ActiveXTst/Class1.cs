using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace ActiveXTst
{
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class TestObj
    {   
        public TestObj()
        {
        }
        public string GetDescrip()
        {
            return "woohoo!";
        }
    }
}
