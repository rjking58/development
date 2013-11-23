using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PopulatingStructsCSharp
{
    public struct S1
    {
        public int pX
        {
            get
            {
                return x;
            }
            set
            {
                x = value;
            }
        }
        public int pY
        {
            get
            {
                return y;
            }
            set
            {
                y = value;
            }
        }
        int x;
        int y;
    }
}
