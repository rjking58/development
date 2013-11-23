using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IntrinsicDataTypes
{
    class Program
    {
        static void Main(string[] args)
        {
            int x = 0;
            int y = new Int32();
            
            short shrt1 = 0;
            short shrt2 = new Int16();

            byte byt1 = 0;
            byte byt2 = new Byte();

            bool first = false;
            bool second = new Boolean();

            double d1 = 0.0;
            double d2 = new Double();

            DateTime dt = new DateTime();

            // IL for this..!
            //.method private hidebysig static void  Main(string[] args) cil managed
            //{
            //  .entrypoint
            //   Code size       52 (0x34)
            //  .maxstack  1
            //  .locals init ([0] int32 x,
            //           [1] int32 y,
            //           [2] int16 shrt1,
            //           [3] int16 shrt2,
            //           [4] uint8 byt1,
            //           [5] uint8 byt2,
            //           [6] bool first,
            //           [7] bool second,
            //           [8] float64 d1,
            //           [9] float64 d2,
            //           [10] valuetype [mscorlib]System.DateTime dt)
            //  IL_0000:  nop
            //  IL_0001:  ldc.i4.0
            //  IL_0002:  stloc.0
            //  IL_0003:  ldc.i4.0
            //  IL_0004:  stloc.1
            //  IL_0005:  ldc.i4.0
            //  IL_0006:  stloc.2
            //  IL_0007:  ldc.i4.0
            //  IL_0008:  stloc.3
            //  IL_0009:  ldc.i4.0
            //  IL_000a:  stloc.s    byt1
            //  IL_000c:  ldc.i4.0
            //  IL_000d:  stloc.s    byt2
            //  IL_000f:  ldc.i4.0
            //  IL_0010:  stloc.s    first
            //  IL_0012:  ldc.i4.0
            //  IL_0013:  stloc.s    second
            //  IL_0015:  ldc.r8     0.0
            //  IL_001e:  stloc.s    d1
            //  IL_0020:  ldc.r8     0.0
            //  IL_0029:  stloc.s    d2
            //  IL_002b:  ldloca.s   dt
            //  IL_002d:  initobj    [mscorlib]System.DateTime
            //  IL_0033:  ret
            //} // end of method Program::Main


        }
    }
}
