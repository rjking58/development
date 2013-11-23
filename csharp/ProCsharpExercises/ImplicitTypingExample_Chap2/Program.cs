using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ImplicitTypingExample_Chap2
{
    class Program
    {
        static void Main(string[] args)
        {
            int [] numbers = {10,20,30,40,1,2,3,8};

            //LINQ query
            var subset = from i in numbers where i < 10 select i;

            Console.Write("Values in subset: ");

            foreach( var i in subset)
            {
                Console.Write("{0} ",i);
            }
            Console.WriteLine();

            Console.WriteLine("subset is a {0}", subset.GetType().Name);
            Console.WriteLine("subset is defined in: {0}", subset.GetType().Namespace);

            // IL for this..
            //.method private hidebysig static void  Main(string[] args) cil managed
            //{
            //  .entrypoint
            //  // Code size       188 (0xbc)
            //  .maxstack  4
            //  .locals init ([0] int32[] numbers,
            //           [1] class [mscorlib]System.Collections.Generic.IEnumerable`1<int32> subset,
            //           [2] int32 i,
            //           [3] class [mscorlib]System.Collections.Generic.IEnumerator`1<int32> CS$5$0000,
            //           [4] bool CS$4$0001)
            //  IL_0000:  nop
            //  IL_0001:  ldc.i4.8
            //  IL_0002:  newarr     [mscorlib]System.Int32
            //  IL_0007:  dup
            //  IL_0008:  ldtoken    field valuetype '<PrivateImplementationDetails>{FBBDE7AE-D2FE-4408-93EB-D01CDD2A697D}'/'__StaticArrayInitTypeSize=32' '<PrivateImplementationDetails>{FBBDE7AE-D2FE-4408-93EB-D01CDD2A697D}'::'$$method0x6000001-1'
            //  IL_000d:  call       void [mscorlib]System.Runtime.CompilerServices.RuntimeHelpers::InitializeArray(class [mscorlib]System.Array,
            //                                                                                                      valuetype [mscorlib]System.RuntimeFieldHandle)
            //  IL_0012:  stloc.0
            //  IL_0013:  ldloc.0
            //  IL_0014:  ldsfld     class [mscorlib]System.Func`2<int32,bool> ImplicitTypingExample_Chap2.Program::'CS$<>9__CachedAnonymousMethodDelegate1'
            //  IL_0019:  brtrue.s   IL_002e
            //  IL_001b:  ldnull
            //  IL_001c:  ldftn      bool ImplicitTypingExample_Chap2.Program::'<Main>b__0'(int32)
            //  IL_0022:  newobj     instance void class [mscorlib]System.Func`2<int32,bool>::.ctor(object,
            //                                                                                      native int)
            //  IL_0027:  stsfld     class [mscorlib]System.Func`2<int32,bool> ImplicitTypingExample_Chap2.Program::'CS$<>9__CachedAnonymousMethodDelegate1'
            //  IL_002c:  br.s       IL_002e
            //  IL_002e:  ldsfld     class [mscorlib]System.Func`2<int32,bool> ImplicitTypingExample_Chap2.Program::'CS$<>9__CachedAnonymousMethodDelegate1'
            //  IL_0033:  call       class [mscorlib]System.Collections.Generic.IEnumerable`1<!!0> [System.Core]System.Linq.Enumerable::Where<int32>(class [mscorlib]System.Collections.Generic.IEnumerable`1<!!0>,
            //                                                                                                                                       class [mscorlib]System.Func`2<!!0,bool>)
            //  IL_0038:  stloc.1
            //  IL_0039:  ldstr      "Values in subset: "
            //  IL_003e:  call       void [mscorlib]System.Console::Write(string)
            //  IL_0043:  nop
            //  IL_0044:  nop
            //  IL_0045:  ldloc.1
            //  IL_0046:  callvirt   instance class [mscorlib]System.Collections.Generic.IEnumerator`1<!0> class [mscorlib]System.Collections.Generic.IEnumerable`1<int32>::GetEnumerator()
            //  IL_004b:  stloc.3
            //  .try
            //  {
            //    IL_004c:  br.s       IL_0068
            //    IL_004e:  ldloc.3
            //    IL_004f:  callvirt   instance !0 class [mscorlib]System.Collections.Generic.IEnumerator`1<int32>::get_Current()
            //    IL_0054:  stloc.2
            //    IL_0055:  nop
            //    IL_0056:  ldstr      "{0} "
            //    IL_005b:  ldloc.2
            //    IL_005c:  box        [mscorlib]System.Int32
            //    IL_0061:  call       void [mscorlib]System.Console::Write(string,
            //                                                              object)
            //    IL_0066:  nop
            //    IL_0067:  nop
            //    IL_0068:  ldloc.3
            //    IL_0069:  callvirt   instance bool [mscorlib]System.Collections.IEnumerator::MoveNext()
            //    IL_006e:  stloc.s    CS$4$0001
            //    IL_0070:  ldloc.s    CS$4$0001
            //    IL_0072:  brtrue.s   IL_004e
            //    IL_0074:  leave.s    IL_0088
            //  }  // end .try
            //  finally
            //  {
            //    IL_0076:  ldloc.3
            //    IL_0077:  ldnull
            //    IL_0078:  ceq
            //    IL_007a:  stloc.s    CS$4$0001
            //    IL_007c:  ldloc.s    CS$4$0001
            //    IL_007e:  brtrue.s   IL_0087
            //    IL_0080:  ldloc.3
            //    IL_0081:  callvirt   instance void [mscorlib]System.IDisposable::Dispose()
            //    IL_0086:  nop
            //    IL_0087:  endfinally
            //  }  // end handler
            //  IL_0088:  nop
            //  IL_0089:  call       void [mscorlib]System.Console::WriteLine()
            //  IL_008e:  nop
            //  IL_008f:  ldstr      "subset is a {0}"
            //  IL_0094:  ldloc.1
            //  IL_0095:  callvirt   instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
            //  IL_009a:  callvirt   instance string [mscorlib]System.Reflection.MemberInfo::get_Name()
            //  IL_009f:  call       void [mscorlib]System.Console::WriteLine(string,
            //                                                                object)
            //  IL_00a4:  nop
            //  IL_00a5:  ldstr      "subset is defined in: {0}"
            //  IL_00aa:  ldloc.1
            //  IL_00ab:  callvirt   instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
            //  IL_00b0:  callvirt   instance string [mscorlib]System.Type::get_Namespace()
            //  IL_00b5:  call       void [mscorlib]System.Console::WriteLine(string,
            //                                                                object)
            //  IL_00ba:  nop
            //  IL_00bb:  ret
            //} // end of method Program::Main


        }
    }
}
