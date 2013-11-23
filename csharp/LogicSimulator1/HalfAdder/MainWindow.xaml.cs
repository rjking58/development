using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Windows.Threading;

using LogicSimulator1;

namespace HalfAdder
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer timer;

        // latch infrastructure..
        List<SimulatedComponent> components = new List<SimulatedComponent>();

        NAndGate exclusive = new NAndGate();
        OrGate og = new OrGate();
        AndGate result = new AndGate();
        AndGate carry = new AndGate();

        Connector bit_a1 = new Connector();
        Connector bit_b1 = new Connector();
        Connector bit_result = new Connector();
        Connector bit_carry = new Connector();
        Connector exclusive_out = new Connector();
        Connector og_out = new Connector();

        bool bitb1_state = false;
        bool bita1_state = false;

        int currTimerBox = 1;


        public MainWindow()
        {
            InitializeComponent();
            Loaded += new RoutedEventHandler(Page1_Loaded);
            Unloaded += new RoutedEventHandler(Page1_Unloaded);

            InitializeAdder();
        }
        public void Page1_Loaded(object sender, RoutedEventArgs e)
        {
            timer = new DispatcherTimer();
            timer.Interval = System.TimeSpan.FromMilliseconds(10);
            timer.Tick += timer1_Tick;

            timer.Start();
        }

        public void Page1_Unloaded(object sender, RoutedEventArgs e)
        {
            timer.Stop();
        }
        public void timer1_Tick(object sender, EventArgs e)
        {
            foreach (SimulatedComponent sc in components)
            {
                sc.Tick();
            }

            if (bit_result.HasSignal())
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                TextBox_R.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                TextBox_R.Background = scb;
            }

            if (bit_carry.HasSignal())
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                TextBox_C.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                TextBox_C.Background = scb;
            }

            UpdateTimerBoxes();
        }


        private void UpdateTimerBoxes()
        {
            SolidColorBrush scb = null;
            switch (currTimerBox)
            {
                case 1:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox1.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox9.Background = scb;

                    break;
                case 2:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox2.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox1.Background = scb;
                    break;
                case 3:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox3.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox2.Background = scb;
                    break;
                case 4:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox4.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox3.Background = scb;
                    break;
                case 5:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox5.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox4.Background = scb;
                    break;
                case 6:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox6.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox5.Background = scb;
                    break;
                case 7:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox7.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox6.Background = scb;
                    break;
                case 8:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox8.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox7.Background = scb;
                    break;
                case 9:
                    scb = new SolidColorBrush();
                    scb.Color = Colors.Gray;
                    textBox9.Background = scb;
                    scb = new SolidColorBrush();
                    scb.Color = Colors.White;
                    textBox8.Background = scb;
                    break;

            }
            currTimerBox += 1;
            if (currTimerBox > 9)
            {
                currTimerBox = 1;
            }

        }

        private void InitializeAdder()
        {

            //bit_a1
            //bit_b1
            //bit_result
            //bit_carry
            //exclusive_out
            //og_out

            exclusive.ConnectInputA(bit_a1);
            exclusive.ConnectInputB(bit_b1);

            exclusive.ConnectOutput(exclusive_out);

            og.ConnectInputA(bit_a1);
            og.ConnectInputB(bit_b1);

            og.ConnectOutput(og_out);

            carry.ConnectInputA(bit_a1);
            carry.ConnectInputB(bit_b1);

            carry.ConnectOutput(bit_carry);

            result.ConnectInputA(og_out);
            result.ConnectInputB(exclusive_out);
            result.ConnectOutput(bit_result);

            components.Add(exclusive);
            components.Add(og);
            components.Add(result);
            components.Add(carry);

        }

        private void button_bitb1_Click(object sender, RoutedEventArgs e)
        {
            bitb1_state = ! bitb1_state;

            if (bitb1_state)
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                frame_bitb1.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                frame_bitb1.Background = scb;
            }

            bit_b1.SendSignal(bitb1_state);
        }

        private void button_bita1_Click(object sender, RoutedEventArgs e)
        {
            bita1_state = ! bita1_state;
            if (bita1_state)
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                frame_bita1.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                frame_bita1.Background = scb;
            }
            bit_a1.SendSignal(bita1_state);
        }

        private void frame1_Navigated(object sender, NavigationEventArgs e)
        {

        }

    }
}
