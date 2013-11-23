using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LogicTester
{
    public partial class Form1 : Form
    {

        Output_RG_Light m_outputlight_sum = null;
        Output_RG_Light m_outputlight_carry = null;
        
        Connector inputA_connector = new Connector();
        Connector inputB_connector = new Connector();
        Connector inputCarry_connector = new Connector();
        Connector lowerSum_to_UpperB_connector = new Connector();
        Connector upperCarry_to_OrA_connector = new Connector();
        Connector lowerCarry_to_OrB_connector = new Connector();

        Connector sum_connector = new Connector();
        Connector carry_connector = new Connector();

        HalfAdder haLower = new HalfAdder();
        HalfAdder haUpper = new HalfAdder();
        TwoInputGate orGate = new OrGate();
        
        public Form1()
        {
            InitializeComponent();

            // all direct inputs.
            haLower.AddConnector_A(inputA_connector);
            haLower.AddConnector_B(inputB_connector);
            haUpper.AddConnector_A(inputCarry_connector);

            // lower sum to upper B
            haLower.AddConnector_Sum(lowerSum_to_UpperB_connector);
            haUpper.AddConnector_B(lowerSum_to_UpperB_connector);

            // lower Carry to orB
            haLower.AddConnector_Carry(lowerCarry_to_OrB_connector);
            orGate.AddConnector_B(lowerCarry_to_OrB_connector);
            // upper Carry to orA
            haUpper.AddConnector_Carry(upperCarry_to_OrA_connector);
            orGate.AddConnector_A(upperCarry_to_OrA_connector);

            m_outputlight_sum = new Output_RG_Light(this.output_light_sum_txtbox);
            m_outputlight_carry = new Output_RG_Light(this.output_light_carry_txtbox);

            haUpper.AddConnector_Sum(sum_connector);
            m_outputlight_sum.AddConnector_A(sum_connector);

            orGate.AddConnector_Out(carry_connector);
            m_outputlight_carry.AddConnector_A(carry_connector);
        }

        private void ClockSignal_btn_Click(object sender, EventArgs e)
        {
            inputA_connector.SetSignal(inputA_cb.Checked);
            inputB_connector.SetSignal(inputB_cb.Checked);
            inputCarry_connector.SetSignal(inputCarry_cb.Checked);
        }

        private void inputA_cb_CheckedChanged(object sender, EventArgs e)
        {
            inputA_connector.SetSignal(inputA_cb.Checked);

        }

        private void inputB_cb_CheckedChanged(object sender, EventArgs e)
        {
            inputB_connector.SetSignal(inputB_cb.Checked);

        }

        private void inputCarry_cb_CheckedChanged(object sender, EventArgs e)
        {
            inputCarry_connector.SetSignal(inputCarry_cb.Checked);
        }
    }
}
