using System.Threading;
using System.Runtime.Remoting.Messaging;
using System;
using System.Collections.Generic;
using System.Text;

namespace multiThread1
{
    // using delegates in asynchronous method invocation..
    
    public delegate int BinaryOp(int x, int y);
    
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("**** Asynch Callback Delegate Example****");
            
            // Print out the ID of the executing thread
            Console.WriteLine("Main() invoked on thread {0}.",
                                Thread.CurrentThread.GetHashCode());
            
            // invoke Add() in a synchronous manner
            BinaryOp b = new BinaryOp(Add);
            // start new thread..
            IAsyncResult iftAR = b.BeginInvoke( 10, 
                                                10, 
                                                new AsyncCallback(AddComplete),
                                                new SomeStateInfo(44,"woohoo!") );
            
            
            // other work...
            // while our thread is running.. do work..
            Console.WriteLine("Doing more work in Main()!");            


            //int answer = b.EndInvoke(iftAR);
            Console.ReadLine();
                                            
        }

        static void AddComplete(IAsyncResult iftAR)
        {
            Console.WriteLine("AddComplete() invoked on thread {0}.",
                                Thread.CurrentThread.GetHashCode());
            Console.WriteLine("Your addition is complete");                    
            
            // result retrieval..
            AsyncResult ar = (AsyncResult)iftAR;
            BinaryOp b = (BinaryOp)ar.AsyncDelegate;
            Console.WriteLine("10 + 10 is {0}.", b.EndInvoke(iftAR));

            // get our asynchronously passed state information...
            SomeStateInfo ssi = (SomeStateInfo)iftAR.AsyncState;
            ssi.printState();
        }
        static int Add(int x, int y)
        {
            // Print out the ID of the executing thread
            Console.WriteLine("Add() invoked on thread {0}.",
                                Thread.CurrentThread.GetHashCode());
                                
            // Pause to simulate long op.
            Thread.Sleep(5000);
            return x + y;
        }
    }
    
    public class SomeStateInfo
    {
        private string  m_s;
        private int     m_x;
        public SomeStateInfo(int x, string s)
        {
            m_x = x;
            m_s = s;
        }
        
        public void printState()
        {
            Console.WriteLine("m_s(" + m_s + ")");
            Console.WriteLine("m_x(" + m_x + ")");
        }
        
    }
}
