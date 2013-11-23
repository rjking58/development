using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace int64mechanisms
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Int32 x = System.Int32.MinValue;
            System.Int64 i64 = Convert.ToInt64(x);
            System.Int64 i64_minus10 = i64 - 10;
            System.Int64 i64_plus10 = i64 + 10;


            byte [] b = BitConverter.GetBytes(i64);

          

            System.Console.WriteLine(i64);
            System.Console.WriteLine("{0}",b[0]);


            x = System.Int32.MaxValue;
            i64 = System.Int32.MaxValue;
            x = Convert.ToInt32(i64);

            //i64 = Convert.ToInt64(x);
            i64_minus10 = i64 - 10;
            i64_plus10 = i64 + 10;
            
        }
    }
}
