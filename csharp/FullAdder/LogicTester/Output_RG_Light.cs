using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LogicTester
{
    class Output_RG_Light : SignalPropogation
    {
        System.Windows.Forms.TextBox    m_output_light = null;
        Connector                       m_connector = null;
        
        public Output_RG_Light(System.Windows.Forms.TextBox txt_box)
        {
            m_output_light = txt_box;
        }
        public void AddConnector_A(Connector cntr)
        {
            m_connector = cntr;
            cntr.AddPropogation_A(this);
        }

        public void Propogate_A(bool signal)
        {
            if (signal)
            {
                m_output_light.BackColor = System.Drawing.Color.LawnGreen;
            }
            else
            {
                m_output_light.BackColor = System.Drawing.Color.Red;
            }
        }
        public void Propogate_B(bool signal)
        {
        }
    }
}
