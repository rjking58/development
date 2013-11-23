using System;
using System.Collections.Generic;
using System.Text;

namespace LogicTester
{
    public class OrGate : TwoInputGate
    {
        protected override bool FigureResult(bool input1, bool input2)
        {
            return input1 || input2;
        }
    }
}
