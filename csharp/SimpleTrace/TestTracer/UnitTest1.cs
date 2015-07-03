#define DEBUG

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SimpleTrace;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace TestTracer
{
    [TestClass]
    public class UnitTest1
    {
        public UnitTest1()
        {
        }

        private int m_TaskID = 0;
        public int GetNextID()
        {
            return ++m_TaskID;
        }

        [TestMethod]
        public void SimpleTrace_BasicFunctionality()
        {
            RJKSimpleTrace st = new RJKSimpleTrace("c:\\temp\\trace1.txt");
            st.WriteLine("a");
            st.WriteLine("b");
            st.WriteLine("c");
            st.WriteLine("d");
            st.WriteLine("e");

            st.closeTrace();
        }



        [TestMethod]
        public void SimpleTrace_ParallelTaskTest()
        {

            RJKSimpleTrace st = new RJKSimpleTrace("c:\\temp\\parallel.txt");

            Action printVals = () =>
                {
                    int id = GetNextID();
                    RJKSimpleTrace stx = new RJKSimpleTrace();
                    for (int val = 0; val < 1000; val++)
                        stx.WriteLine(string.Format("[{0}]:{1}", id, val));
                };
            Task tA = new Task(printVals);
            Task tB = new Task(printVals);
            Task tC = new Task(printVals);

            tA.Start();
            tB.Start();
            tC.Start();

            tA.Wait();
            tB.Wait();
            tC.Wait();
            st.closeTrace();

        }
    }
}
