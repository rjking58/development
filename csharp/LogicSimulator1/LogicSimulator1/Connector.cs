using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicSimulator1
{
    public class Connector : ConnectorComponent
    {
        bool Signal = false;

        public void SendSignal(bool signalValue)
        {
            Signal = signalValue;
        }


        public bool HasSignal()
        {
            return Signal;
        }
    }
}
