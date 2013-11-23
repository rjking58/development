using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using LogicSimulator1;

namespace TestProject1
{
    [TestClass]
    public class ComponentTests
    {
        [TestMethod]
        public void TestConnector()
        {
            Connector c = new Connector();

            c.SendSignal(false);
            Assert.IsFalse(c.HasSignal());
            c.SendSignal(true);
            Assert.IsTrue(c.HasSignal());
        }

        [TestMethod]
        public void TestNotGateBothConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NotGate ng = new NotGate();

            Connector inputConnector = new Connector();
            ng.ConnectInputA(inputConnector);

            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);


            components.Add(ng);

            bool currSignal = false;
            for (int x = 1; x < 30; x++)
            {
                inputConnector.SendSignal(currSignal);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Assert.IsTrue(outputConnector.HasSignal() == (! currSignal));

                currSignal = !currSignal;
            }
        }
        [TestMethod]
        public void TestNotGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NotGate ng = new NotGate();

            Connector inputConnector = new Connector();
            ng.ConnectInputA(inputConnector);

            components.Add(ng);

            bool currSignal = false;
            for (int x = 1; x < 30; x++)
            {
                inputConnector.SendSignal(currSignal);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                currSignal = !currSignal;
            }
        }
        [TestMethod]
        public void TestNotGateNoInput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NotGate ng = new NotGate();

            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);

            components.Add(ng);

            bool currSignal = false;
            for (int x = 1; x < 30; x++)
            {
                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                // floating input is 'false'
                Assert.IsTrue(outputConnector.HasSignal());
                currSignal = !currSignal;
            }
        }

        // ///////////////////////////////////////////////////////////////////////////////////////
        // AND gate..
        // ///////////////////////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void TestAndGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == (currSignal1 && currSignal2));

                currSignal1 = ! currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = ! currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestAndGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();

            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsFalse(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestAndGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsFalse(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestAndGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]" );

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }

        // ///////////////////////////////////////////////////////////////////////////////////////
        // NAND built up gate..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestBuiltUpNAndGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();
            NotGate ng = new NotGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            // put a not gate on the output of the and gate..
            Connector andToNot = new Connector();
            ag.ConnectOutput(andToNot);
            ng.ConnectInputA(andToNot);

            // out of the not gate..
            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);

            // ordering here is important for signal propogation.. if we reverse the order the propogation will be delayed.. 
            components.Add(ag);
            components.Add(ng);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() ==  (! (currSignal1 && currSignal2)) );

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestBuiltUpNAndGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();
            NotGate ng = new NotGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            // put a not gate on the output of the and gate..
            Connector andToNot = new Connector();
            ag.ConnectOutput(andToNot);
            ng.ConnectInputA(andToNot);

            // out of the not gate..
            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);

            // ordering here is important for signal propogation.. if we reverse the order the propogation will be delayed.. 
            components.Add(ag);
            components.Add(ng);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestBuiltUpNAndGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();
            NotGate ng = new NotGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            // put a not gate on the output of the and gate..
            Connector andToNot = new Connector();
            ag.ConnectOutput(andToNot);
            ng.ConnectInputA(andToNot);

            // out of the not gate..
            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);

            // ordering here is important for signal propogation.. if we reverse the order the propogation will be delayed.. 
            components.Add(ag);
            components.Add(ng);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestBuiltUpNAndGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            AndGate ag = new AndGate();
            NotGate ng = new NotGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            // put a not gate on the output of the and gate..
            Connector andToNot = new Connector();
            ag.ConnectOutput(andToNot);
            ng.ConnectInputA(andToNot);

            // out of the not gate..
            Connector outputConnector = new Connector();
            ng.ConnectOutput(outputConnector);

            // ordering here is important for signal propogation.. if we reverse the order the propogation will be delayed.. 
            components.Add(ag);
            components.Add(ng);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        // ///////////////////////////////////////////////////////////////////////////////////////
        // OR gate..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestOrGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            OrGate og = new OrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == (currSignal1 || currSignal2));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestOrGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            OrGate og = new OrGate();

            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == currSignal2);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestOrGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            OrGate og = new OrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == currSignal1);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestOrGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            OrGate og = new OrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        // ///////////////////////////////////////////////////////////////////////////////////////
        // NAND gate..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestNAndGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NAndGate ag = new NAndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == (! (currSignal1 && currSignal2)));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNAndGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NAndGate ag = new NAndGate();

            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNAndGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NAndGate ag = new NAndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            ag.ConnectOutput(outputConnector);


            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal());

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNAndGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NAndGate ag = new NAndGate();

            Connector inputConnectorA = new Connector();
            ag.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            ag.ConnectInputB(inputConnectorB);

            components.Add(ag);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }

        // ///////////////////////////////////////////////////////////////////////////////////////
        // NOR gate..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestNOrGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NOrGate og = new NOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == (! (currSignal1 || currSignal2)));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNOrGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NOrGate og = new NOrGate();

            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsFalse(outputConnector.HasSignal() == currSignal2);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNOrGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NOrGate og = new NOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsFalse(outputConnector.HasSignal() == currSignal1);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestNOrGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NOrGate og = new NOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }

        // ///////////////////////////////////////////////////////////////////////////////////////
        // XOR gate..
        // ///////////////////////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void TestXOrGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XOrGate og = new XOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == (currSignal1 ^ currSignal2));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXOrGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XOrGate og = new XOrGate();

            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == currSignal2);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXOrGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XOrGate og = new XOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue(outputConnector.HasSignal() == currSignal1);

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXOrGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XOrGate og = new XOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        // ///////////////////////////////////////////////////////////////////////////////////////
        // XNOR gate..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestXNOrGateAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XNOrGate og = new XNOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue( ! (outputConnector.HasSignal() == (currSignal1 ^ currSignal2)));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXNOrGateNoInputA()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XNOrGate og = new XNOrGate();

            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue( ! (outputConnector.HasSignal() == currSignal2));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXNOrGateNoInputB()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XNOrGate og = new XNOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);

            Connector outputConnector = new Connector();
            og.ConnectOutput(outputConnector);


            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "] = Result[" + outputConnector.HasSignal().ToString() + "]");
                Assert.IsTrue( ! (outputConnector.HasSignal() == currSignal1));

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        [TestMethod]
        public void TestXNOrGateNoOutput()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            XNOrGate og = new XNOrGate();

            Connector inputConnectorA = new Connector();
            og.ConnectInputA(inputConnectorA);
            Connector inputConnectorB = new Connector();
            og.ConnectInputB(inputConnectorB);

            components.Add(og);

            bool currSignal1 = false;
            bool currSignal2 = false;

            for (int x = 1; x < 30; x++)
            {
                inputConnectorA.SendSignal(currSignal1);
                inputConnectorB.SendSignal(currSignal2);

                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }

                Console.WriteLine("Signal1[" + currSignal1.ToString() + "] Signal2[" + currSignal2.ToString() + "]");

                currSignal1 = !currSignal1;
                if (currSignal1 == false)
                {
                    currSignal2 = !currSignal2;
                }
            }
        }
        
        // ///////////////////////////////////////////////////////////////////////////////////////
        // Latch test ..
        // ///////////////////////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void TestLatchAllConnectorsGood()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            NOrGate og1 = new NOrGate();
            NOrGate og2 = new NOrGate();

            Connector R = new Connector();
            Connector S = new Connector();
            Connector Q = new Connector();
            Connector NOT_Q = new Connector();


            og1.ConnectInputA(R);
            og1.ConnectOutput(Q);

            og2.ConnectInputB(S);
            og2.ConnectOutput(NOT_Q);

            // cross connect for latch behavior
            og1.ConnectInputB(NOT_Q);
            og2.ConnectInputA(Q);

            components.Add(og1);
            components.Add(og2);

            for (int x = 1; x < 30; x++)
            {
                if (x == 4 || x == 12 || x == 20 || x == 28)
                {
                    Console.WriteLine("Strobing Reset");
                    R.SendSignal(true);
                }
                else
                {
                    R.SendSignal(false);
                }
                if (x == 8 || x == 16 || x == 24)
                {
                    Console.WriteLine("Strobing Set");
                    S.SendSignal(true);
                }
                else
                {
                    S.SendSignal(false);
                }
                foreach (SimulatedComponent sc in components)
                {
                    sc.Tick();
                }
                Console.WriteLine("Q[" + Q.HasSignal().ToString() + "] NOT_Q[" + NOT_Q.HasSignal().ToString() + "]");
            }
        }
        // ///////////////////////////////////////////////////////////////////////////////////////
        // full adder test (discreets with XORs) ..
        // ///////////////////////////////////////////////////////////////////////////////////////
        [TestMethod]
        public void TestFullAdderDiscreets()
        {
            List<SimulatedComponent> components = new List<SimulatedComponent>();

            // bit 1 stage.
            XOrGate xogResultStage = new XOrGate();
            AndGate agResultStage1 = new AndGate();
            XOrGate xogInputStage1 = new XOrGate();
            AndGate agInputStage1 = new AndGate();

            OrGate carryOut1 = new OrGate();

            Connector inputA1 = new Connector();
            Connector inputB1 = new Connector();
            Connector outputCarryOut1 = new Connector();
            Connector outputSumOut1 = new Connector();
            Connector internalSumToB1 = new Connector();
            Connector internalCarry1a = new Connector();
            Connector internalCarry1b = new Connector();


            xogInputStage1.ConnectInputB(internalSumToB1);
            xogInputStage1.ConnectOutput(outputSumOut1);
            agInputStage1.ConnectInputB(internalSumToB1);
            agInputStage1.ConnectOutput(internalCarry1a);

            xogResultStage.ConnectInputA(inputA1);
            xogResultStage.ConnectInputB(inputB1);
            xogResultStage.ConnectOutput(internalSumToB1);
            agResultStage1.ConnectInputA(inputA1);
            agResultStage1.ConnectInputB(inputB1);
            agResultStage1.ConnectOutput(internalCarry1b);

            carryOut1.ConnectInputA(internalCarry1a);
            carryOut1.ConnectInputB(internalCarry1b);
            carryOut1.ConnectOutput(outputCarryOut1);

            components.Add(xogResultStage);
            components.Add(agResultStage1);
            components.Add(xogInputStage1);
            components.Add(agInputStage1);
            components.Add(carryOut1);

            // bit 2 stage.
            XOrGate xogResultStage2 = new XOrGate();
            AndGate agResultStage2 = new AndGate();
            XOrGate xogInputStage2 = new XOrGate();
            AndGate agInputStage2 = new AndGate();
            OrGate carryOut2 = new OrGate();

            Connector inputA2 = new Connector();
            Connector inputB2 = new Connector();
            Connector outputCarryOut2 = new Connector();
            Connector outputSumOut2 = new Connector();
            Connector internalSumToB2 = new Connector();
            Connector internalCarry2a = new Connector();
            Connector internalCarry2b = new Connector();

            xogInputStage2.ConnectInputA(outputCarryOut1);
            xogInputStage2.ConnectInputB(internalSumToB2);
            xogInputStage2.ConnectOutput(outputSumOut2);
            agInputStage2.ConnectInputA(outputCarryOut1);
            agInputStage2.ConnectInputB(internalSumToB2);
            agInputStage2.ConnectOutput(internalCarry2a);

            xogResultStage2.ConnectInputA(inputA2);
            xogResultStage2.ConnectInputB(inputB2);
            xogResultStage2.ConnectOutput(internalSumToB2);
            agResultStage2.ConnectInputA(inputA2);
            agResultStage2.ConnectInputB(inputB2);
            agResultStage2.ConnectOutput(internalCarry2b);

            carryOut2.ConnectInputA(internalCarry2a);
            carryOut2.ConnectInputB(internalCarry2b);
            carryOut2.ConnectOutput(outputCarryOut2);

            components.Add(xogResultStage2);
            components.Add(agResultStage2);
            components.Add(xogInputStage2);
            components.Add(agInputStage2);
            components.Add(carryOut2);

            // bit 3 stage.
            XOrGate xogResultStage3 = new XOrGate();
            AndGate agResultStage3 = new AndGate();
            XOrGate xogInputStage3 = new XOrGate();
            AndGate agInputStage3 = new AndGate();
            OrGate carryOut3 = new OrGate();

            Connector inputA3 = new Connector();
            Connector inputB3 = new Connector();
            Connector outputCarryOut3 = new Connector();
            Connector outputSumOut3 = new Connector();
            Connector internalSumToB3 = new Connector();
            Connector internalCarry3a = new Connector();
            Connector internalCarry3b = new Connector();

            xogInputStage3.ConnectInputA(outputCarryOut2);
            xogInputStage3.ConnectInputB(internalSumToB3);
            xogInputStage3.ConnectOutput(outputSumOut3);
            agInputStage3.ConnectInputA(outputCarryOut2);
            agInputStage3.ConnectInputB(internalSumToB3);
            agInputStage3.ConnectOutput(internalCarry3a);

            xogResultStage3.ConnectInputA(inputA3);
            xogResultStage3.ConnectInputB(inputB3);
            xogResultStage3.ConnectOutput(internalSumToB3);
            agResultStage3.ConnectInputA(inputA3);
            agResultStage3.ConnectInputB(inputB3);
            agResultStage3.ConnectOutput(internalCarry3b);

            carryOut3.ConnectInputA(internalCarry3a);
            carryOut3.ConnectInputB(internalCarry3b);
            carryOut3.ConnectOutput(outputCarryOut3);

            components.Add(xogResultStage3);
            components.Add(agResultStage3);
            components.Add(xogInputStage3);
            components.Add(agInputStage3);
            components.Add(carryOut3);


            for(int y = 0; y < 8; y++)
            for (int x = 0; x < 8; x ++)
            {
                if ((y & 1) != 0)
                {
                    inputB1.SendSignal(true);
                }
                else
                {
                    inputB1.SendSignal(false);
                }
                if ((y & 2) != 0)
                {
                    inputB2.SendSignal(true);
                }
                else
                {
                    inputB2.SendSignal(false);
                }
                if ((y & 4) != 0)
                {
                    inputB3.SendSignal(true);
                }
                else
                {
                    inputB3.SendSignal(false);
                }

                if ((x & 1) != 0)
                {
                    inputA1.SendSignal(true);
                }
                else
                {
                    inputA1.SendSignal(false);
                }
                if ((x & 2) != 0)
                {
                    inputA2.SendSignal(true);
                }
                else
                {
                    inputA2.SendSignal(false);
                }
                if ((x & 4) != 0)
                {
                    inputA3.SendSignal(true);
                }
                else
                {
                    inputA3.SendSignal(false);
                }


                for (int z = 0; z < 3; z++)
                {
                    foreach (SimulatedComponent sc in components)
                    {
                        sc.Tick();
                    }
                }
                int result = 0;

                if (outputCarryOut3.HasSignal())
                {
                    result |= 8;
                }

                if (outputSumOut3.HasSignal())
                {
                    result |= 4;
                }

                if (outputSumOut2.HasSignal())
                {
                    result |= 2;
                }

                if (outputSumOut1.HasSignal())
                {
                    result |= 1;
                }

                Assert.AreEqual(x + y, result);
                Console.WriteLine("x[" + x.ToString() + "] y[" + y.ToString() + "] = Result[" + result.ToString() + "]");

            }
        }

    }
}
