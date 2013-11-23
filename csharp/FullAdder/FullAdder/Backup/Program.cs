using System;
using System.Collections.Generic;
using System.Text;

namespace FullAdder
{
    class Program
    {
        static void Main(string[] args)
        {
            for(int carry = 0; carry < 2; carry++)
            {
                int a = 0;
                int b = 0;
                for(int ab = 0; ab < 4; ab++)
                {
                    switch(ab)
                    {
                        case 0:
                            a = 0;
                            b = 0;
                            break;
                        case 1:
                            a = 0;
                            b = 1;
                            break;
                        case 2:
                            a = 1;
                            b = 0;
                            break;
                        case 3:
                            a = 1;
                            b = 1;
                            break;
                            
                    }
                    // half adder 1
                    int ha1_s = a ^ b;
                    int ha1_c = a & b;
                    int ha2_s = carry ^ ha1_s;
                    int ha2_c = carry & ha1_s;
                    int fulladder_c = ha2_c | ha1_c;
                    System.Console.WriteLine(carry + " " + a + " " + b + "  " + fulladder_c + " " + ha2_s);
                }
            }
        }
    }
}
