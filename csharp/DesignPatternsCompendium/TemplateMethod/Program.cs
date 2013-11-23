using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TemplateMethod
{
    /// <summary>
    /// our 'template method class'
    /// </summary>
    abstract class AbstractStepwiseProcess
    {
        /// <summary>
        /// a bunch of steps which will have overridden 
        /// behavior in subclasses.. Note that not all steps 
        /// must look like this.. we may have steps that never
        /// change and therefore would have a simple method declared
        /// in this class
        /// </summary>
        public abstract void Step1();
        public abstract void Step2();
        public abstract void Step3();
        public void Step4()
        {
            Console.WriteLine("Process:Step4");
        }

        /// <summary>
        /// our template method. 
        /// </summary>
        public void DoProcess()
        {
            Step1();
            Step2();
            Step3();
            Step4();
        }
    }
    /// <summary>
    /// a class which provides specific behaviors for the 
    /// abstract steps in the base class
    /// </summary>
    class Process1 : AbstractStepwiseProcess
    {
        public override void Step1()
        {
            Console.WriteLine("Process1:Step1");
        }
        public override void Step2()
        {
            Console.WriteLine("Process1:Step2");
        }
        public override void Step3()
        {
            Console.WriteLine("Process1:Step3");
        }
    }
    /// <summary>
    /// a class which provides specific behaviors for the 
    /// abstract steps in the base class
    /// </summary>
    class Process2 : AbstractStepwiseProcess
    {
        public override void Step1()
        {
            Console.WriteLine("Process2:Step1");
        }
        public override void Step2()
        {
            Console.WriteLine("Process2:Step2");
        }
        public override void Step3()
        {
            Console.WriteLine("Process2:Step3");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            AbstractStepwiseProcess asp = new Process1();
            asp.DoProcess();

            asp = new Process2();
            asp.DoProcess();
        }
    }
}
