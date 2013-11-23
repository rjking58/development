using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicSimulator1
{
    public interface LogicComponent : SimulatedComponent
    {
        void ConnectOutput(Connector TheOutput);
    }

    public interface BinaryLogicComponent : LogicComponent
    {
        void ConnectInputA( Connector Alpha);
        void ConnectInputB( Connector Bravo);
    }

    public interface UnaryLogicComponent : LogicComponent
    {
        void ConnectInputA(Connector Alpha);
    }

}
