using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicSimulator1
{
    public abstract class BinaryGateIO : BinaryLogicComponent
    {
        List<Connector> InputA = new List<Connector>();
        List<Connector> InputB = new List<Connector>();

        List<Connector> Output = new List<Connector>();

        public bool GetASignal()
        {
            bool currInputA = false;
            foreach(Connector cnctr in InputA)
            {
                // if any are on.. turn this signal ON.
                if (cnctr.HasSignal())
                {
                    currInputA = true;
                }
            }
            return currInputA;
        }
        public bool GetBSignal()
        {
            bool currInputB = false;
            foreach (Connector cnctr in InputB)
            {
                if (cnctr.HasSignal())
                {
                    currInputB = true;
                }
            }
            return currInputB;
        }

        public void SendSignal(bool Signal)
        {
            foreach (Connector cnctr in Output)
            {
                cnctr.SendSignal(Signal);
            }
        }
        public void ConnectInputA(Connector Alpha)
        {
            InputA.Add(Alpha);
        }

        public void ConnectInputB(Connector Bravo)
        {
            InputB.Add(Bravo);
        }

        public void ConnectOutput(Connector TheOutput)
        {
            Output.Add(TheOutput);
        }
        public abstract void Tick();
    }
    public class AndGate : BinaryGateIO
    {
        public override void Tick()
        {
            SendSignal(GetASignal() && GetBSignal());
        }
    }

    public class NAndGate : BinaryGateIO
    {
        public override void Tick()
        {
            SendSignal( ! (GetASignal() && GetBSignal()));
        }
    }

    public class OrGate : BinaryGateIO
    {

        public override void Tick()
        {
            SendSignal(GetASignal() || GetBSignal());
        }
    }

    public class NOrGate : BinaryGateIO
    {
        public override void Tick()
        {
            SendSignal( ! (GetASignal() || GetBSignal()));
        }
    }

    public class XOrGate : BinaryGateIO
    {
        public override void Tick()
        {
            SendSignal((GetASignal() ^ GetBSignal()));
        }
    }

    public class XNOrGate : BinaryGateIO
    {
        public override void Tick()
        {
            SendSignal( ! (GetASignal() ^ GetBSignal()));
        }
    }

}
