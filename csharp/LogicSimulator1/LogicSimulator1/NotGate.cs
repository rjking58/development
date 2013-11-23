using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicSimulator1
{
    public class NotGate : UnaryLogicComponent
    {
        Connector InputA = null;
        Connector Output = null;

        public void Tick()
        {
            bool currInput = false;
            if (InputA != null)
            {
                currInput = InputA.HasSignal();
            }

            if (Output != null)
            {
                Output.SendSignal( ! currInput);
            }
        }


        public void ConnectInputA(Connector InputAlpha)
        {
            InputA = InputAlpha;
        }


        public void ConnectOutput(Connector TheOutput)
        {
            Output = TheOutput;
        }
    }
}
