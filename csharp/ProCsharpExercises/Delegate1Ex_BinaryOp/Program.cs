using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Delegate1Ex_BinaryOp
{
    class Program
    {
        delegate void BinaryOp(int x, int y);

        BinaryOp callBack = null;

        void Add(int first, int second)
        {
            Console.WriteLine(first + second);
        }

        void Sub(int first, int second)
        {
            Console.WriteLine(first - second);
        }

        void DoProggy()
        {
            callBack = Add;
            callBack += Sub;

            foreach (Delegate d in callBack.GetInvocationList())
            {
                Console.WriteLine("Method Name[" + d.Method + "]");
                Console.WriteLine("Type Name[" + d.Target + "]");
            }
            // do the responsible thing :)
            if(callBack != null)
            {
                callBack(4, 5);
            }
        }
        static void Main(string[] args)
        {
            Program p = new Program();
            p.DoProggy();
        }

    }
}
