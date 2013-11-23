using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DetectingNumericOverflows
{
    class Program
    {
        static void Main(string[] args)
        {

            byte b1 = 100;
            byte b2 = 250;

            // note here that the default for Managed compilers is to NOT
            // check for overflow conditions.
            try
            {
                byte sum = checked((byte) Add(b1,b2));
                Console.WriteLine(sum);
            }
            catch(OverflowException ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
        }

        static int Add(int x, int y)
        {
            return (x+y);
        }

        // again, generated IL
        //.method private hidebysig static void  Main(string[] args) cil managed
        //{
        //  .entrypoint
        //  // Code size       61 (0x3d)
        //  .maxstack  2
        //  .locals init ([0] uint8 b1,
        //           [1] uint8 b2,
        //           [2] uint8 sum,
        //           [3] class [mscorlib]System.OverflowException ex)
        //  IL_0000:  nop
        //  IL_0001:  ldc.i4.s   100
        //  IL_0003:  stloc.0
        //  IL_0004:  ldc.i4     0xfa
        //  IL_0009:  stloc.1
        //  .try
        //  {
        //    IL_000a:  nop
        //    IL_000b:  ldloc.0
        //    IL_000c:  ldloc.1
        //    IL_000d:  call       int32 DetectingNumericOverflows.Program::Add(int32,
        //                                                                      int32)
        //    IL_0012:  conv.ovf.u1
        //    IL_0013:  stloc.2
        //    IL_0014:  ldloc.2
        //    IL_0015:  call       void [mscorlib]System.Console::WriteLine(int32)
        //    IL_001a:  nop
        //    IL_001b:  nop
        //    IL_001c:  leave.s    IL_003b
        //  }  // end .try
        //  catch [mscorlib]System.OverflowException 
        //  {
        //    IL_001e:  stloc.3
        //    IL_001f:  nop
        //    IL_0020:  ldloc.3
        //    IL_0021:  callvirt   instance string [mscorlib]System.Exception::get_Message()
        //    IL_0026:  call       void [mscorlib]System.Console::WriteLine(string)
        //    IL_002b:  nop
        //    IL_002c:  ldloc.3
        //    IL_002d:  callvirt   instance string [mscorlib]System.Exception::get_StackTrace()
        //    IL_0032:  call       void [mscorlib]System.Console::WriteLine(string)
        //    IL_0037:  nop
        //    IL_0038:  nop
        //    IL_0039:  leave.s    IL_003b
        //  }  // end handler
        //  IL_003b:  nop
        //  IL_003c:  ret
        //} // end of method Program::Main


    }
}
