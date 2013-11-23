using System;
using System.Collections.Generic;
using System.Text;

namespace ternaryOperatorTest
{
    class x
    {
        private bool state = false;
        public bool IsState
        {
            get
            {
                return state;
            }
            set
            {
                state = value;
            }
        }
    }
    class Program
    {
    
        static void Main(string[] args)
        {
            x my_x = null;
            for(int x = 0; x < 2; x++)
            {
                if( (my_x != null ? my_x.IsState : false))
                {
                    Console.WriteLine("is true");
                }
                else
                {
                    Console.WriteLine("is false");
                }
                my_x = new x();
                my_x.IsState = true;
            }
        }
    }
}
