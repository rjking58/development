using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using LogicTester;

namespace LogicTesterTests
{
    /// <summary>
    /// Summary description for UnitTest1
    /// </summary>

    public class FanOutSignaler
    {
        List<Connector> m_outputs = new List<Connector>();
        
        public void AddConnector_Out(Connector cntr)
        {
            m_outputs.Add(cntr);
        }

        public void SendSignal(bool signal)
        {
            foreach (Connector cntr in m_outputs)
            {
                cntr.SetSignal(signal);
            }
        }
    }
        
    public class TestOutput : SignalPropogation
    {
        private bool m_result = false;
        private bool m_triggered = false;
        public bool Result
        {
            get
            {
                return m_result;
            }
        }
        public bool Triggered
        {
            get
            {
                return m_triggered;
            }
        }
        public void ResetResult()
        {
            m_result = false;
            m_triggered = false;
        }
        public void Propogate_B(bool signal)
        {
            throw new NotImplementedException();
        }

        public void Propogate_A(bool signal)
        {
            m_result = signal;
            m_triggered = true;
        }
        
        public void AddConnector_A(Connector cntr)
        {
            cntr.AddPropogation_A(this);
        }
    }
    
    [TestClass]
    public class UnitTest1
    {
        public UnitTest1()
        {
            //
            // TODO: Add constructor logic here
            //
        }

        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        //
        // You can use the following additional attributes as you write your tests:
        //
        // Use ClassInitialize to run code before running the first test in the class
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // Use ClassCleanup to run code after all tests in a class have run
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // Use TestInitialize to run code before running each test 
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestMethod]
        public void AndGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new AndGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);
            
            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);
            
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);
            
            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);
            
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);
            
            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
            
            
            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }
        
        [TestMethod]
        public void OrGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new OrGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);

            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);


            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }
        [TestMethod]
        public void XorGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new XorGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);

            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);


            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }
        [TestMethod]
        public void NandGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new NandGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);

            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);


            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }
        [TestMethod]
        public void NorGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new NorGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);

            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);


            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }
        [TestMethod]
        public void XNorGateTest()
        {
            TestOutput tstOut = new TestOutput();
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector gate_out_to_class = new Connector();

            TwoInputGate gate = new XNorGate();

            //inputs
            gate.AddConnector_A(inputA_connector);
            gate.AddConnector_B(inputB_connector);

            //outputs
            tstOut.AddConnector_A(gate_out_to_class);
            gate.AddConnector_Out(gate_out_to_class);

            //false,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,false B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // false, true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            // true,false A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //false,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);


            // true,true A,B
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);

            //true,true B,A
            tstOut.ResetResult();
            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOut.Result);
            Assert.IsFalse(tstOut.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOut.Result);
            Assert.IsTrue(tstOut.Triggered);
        }

        [TestMethod]
        public void HalfAdderTest()
        {
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector sum_connector = new Connector();
            Connector carry_connector = new Connector();

            HalfAdder ha = new HalfAdder();
            

            TestOutput tstOutSum = new TestOutput();
            TestOutput tstOutCarry = new TestOutput();

            ha.AddConnector_A(inputA_connector);
            ha.AddConnector_B(inputB_connector);
            ha.AddConnector_Sum(sum_connector);
            ha.AddConnector_Carry(carry_connector);

            tstOutSum.AddConnector_A(sum_connector);
            tstOutCarry.AddConnector_A(carry_connector);


            //false,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //false,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);


            //false,false B,A
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //false,true B,A
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,false B,A
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,true B,A
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);
        }

        [TestMethod]
        public void FullAdderTest()
        {
            Connector inputA_connector = new Connector();
            Connector inputB_connector = new Connector();
            Connector inputCarry_connector = new Connector();
            Connector lowerSum_to_UpperB_connector = new Connector();
            Connector upperCarry_to_OrA_connector = new Connector();
            Connector lowerCarry_to_OrB_connector = new Connector();
            
            Connector sum_connector = new Connector();
            Connector carry_connector = new Connector();

            HalfAdder haLower = new HalfAdder();
            HalfAdder haUpper = new HalfAdder();
            TwoInputGate orGate = new OrGate();
            


            TestOutput tstOutSum = new TestOutput();
            TestOutput tstOutCarry = new TestOutput();

            // all direct inputs.
            haLower.AddConnector_A(inputA_connector);
            haLower.AddConnector_B(inputB_connector);
            haUpper.AddConnector_A(inputCarry_connector);

            // lower sum to upper B
            haLower.AddConnector_Sum(lowerSum_to_UpperB_connector);
            haUpper.AddConnector_B(lowerSum_to_UpperB_connector);
            
            // lower Carry to orB
            haLower.AddConnector_Carry(lowerCarry_to_OrB_connector);
            orGate.AddConnector_B(lowerCarry_to_OrB_connector);
            // upper Carry to orA
            haUpper.AddConnector_Carry(upperCarry_to_OrA_connector);
            orGate.AddConnector_A(upperCarry_to_OrA_connector);


            haUpper.AddConnector_Sum(sum_connector);
            tstOutSum.AddConnector_A(sum_connector);
            
            orGate.AddConnector_Out(carry_connector);
            tstOutCarry.AddConnector_A(carry_connector);


            //false,false,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //false,false,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(false);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);


            //false,true,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(false);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);


            //false,true,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,false,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(true);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,false,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);
            
            //true,true,false A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(false);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);

            //true,true,true A,B
            tstOutSum.ResetResult();
            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            tstOutCarry.ResetResult();
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputA_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputB_connector.SetSignal(true);

            Assert.IsFalse(tstOutSum.Result);
            Assert.IsFalse(tstOutSum.Triggered);
            Assert.IsFalse(tstOutCarry.Result);
            Assert.IsFalse(tstOutCarry.Triggered);

            inputCarry_connector.SetSignal(true);

            Assert.IsTrue(tstOutSum.Result);
            Assert.IsTrue(tstOutSum.Triggered);
            Assert.IsTrue(tstOutCarry.Result);
            Assert.IsTrue(tstOutCarry.Triggered);


        }
        
    }
}
