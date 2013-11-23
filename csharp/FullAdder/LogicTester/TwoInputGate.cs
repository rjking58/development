using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicTester
{
    public abstract class TwoInputGate : SignalPropogation
    {
        List<Connector> m_outputs = new List<Connector>();
        Connector m_connectorA = null;
        Connector m_connectorB = null;
        bool m_A_signal = false;
        bool m_B_signal = false;
//        bool m_A_set = false;
//        bool m_B_set = false;

        private void outputResult()
        {
            bool result = FigureResult(m_A_signal,m_B_signal);
            foreach (Connector cntr in m_outputs)
            {
                cntr.SetSignal(result);
            }
        }
        private void clearSets()
        {
//            m_A_set = false;
//            m_B_set = false;
        }
        public void Propogate_A(bool signal)
        {
            m_A_signal = signal;
//            m_A_set = true;
//            if (m_B_set)
//            {
//                clearSets();
                outputResult();
//            }
        }

        public void Propogate_B(bool signal)
        {
            m_B_signal = signal;
//            m_B_set = true;
//            if (m_A_set)
//            {
//                clearSets();
                outputResult();
//            }
        }

        public void AddConnector_A(Connector cntr)
        {
            m_connectorA = cntr;
            cntr.AddPropogation_A(this);
        }

        public void AddConnector_B(Connector cntr)
        {
            m_connectorB = cntr;
            cntr.AddPropogation_B(this);
        }
        public void AddConnector_Out(Connector cntr)
        {
            m_outputs.Add(cntr);
        }

        protected abstract bool FigureResult(bool input1, bool input2);
    }
}
