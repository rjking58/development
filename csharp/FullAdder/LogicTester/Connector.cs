using System;
using System.Collections.Generic;
using System.Text;

namespace LogicTester
{
    public class Connector
    {
        private SignalPropogation m_signal_propogation_A = null;
        private SignalPropogation m_signal_propogation_B = null;
    
        public void SetSignal(bool signal)
        {
            if(m_signal_propogation_A != null)
            {
                m_signal_propogation_A.Propogate_A(signal);
            }
            if (m_signal_propogation_B != null)
            {
                m_signal_propogation_B.Propogate_B(signal);
            }
        }
        public void AddPropogation_A(SignalPropogation sp)
        {
            m_signal_propogation_A = sp;
        }

        public void AddPropogation_B(SignalPropogation sp)
        {
            m_signal_propogation_B = sp;
        }
    }
}
