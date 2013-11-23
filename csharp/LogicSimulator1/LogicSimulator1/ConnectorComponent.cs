using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicSimulator1
{
    public interface ConnectorComponent
    {
        void SendSignal(bool signalValue);
        bool HasSignal();
    }
}
