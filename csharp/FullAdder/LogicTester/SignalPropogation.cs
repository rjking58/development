using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicTester
{
    public interface SignalPropogation
    {
        void Propogate_B(bool signal);

        void Propogate_A(bool signal);
    }
}
