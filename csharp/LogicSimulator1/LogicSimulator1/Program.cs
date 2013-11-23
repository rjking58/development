using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;



namespace LogicSimulator1
{
    //class Program
    //{
    //    static void Main(string[] args)
    //    {

    //        List<SimulatedComponent> components = new List<SimulatedComponent>();

    //        NotGate ng = new NotGate();

    //        Connector inputConnector = new Connector();
    //        ng.ConnectInputA(inputConnector);

    //        Connector outputConnector = new Connector();
    //        ng.ConnectOutput(outputConnector);


    //        components.Add(ng);

    //        bool currSignal = false;
    //        for (int x = 1; x < 30; x++ )
    //        {
    //            inputConnector.SendSignal(currSignal);

    //            foreach (SimulatedComponent sc in components)
    //            {
    //                sc.Tick();
    //            }

    //            Console.WriteLine("Input[" + currSignal.ToString() + "] Output[" + outputConnector.HasSignal().ToString() + "]");

    //            currSignal = !currSignal;


    //        }

    //    }
    //}
}
