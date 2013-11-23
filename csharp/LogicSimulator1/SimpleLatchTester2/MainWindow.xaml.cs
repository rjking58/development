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

namespace SimpleLatchTester2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private DispatcherTimer timer;

        // latch infrastructure..
        List<SimulatedComponent> components = new List<SimulatedComponent>();

        NOrGate og1 = new NOrGate();
        NOrGate og2 = new NOrGate();

        Connector R = new Connector();
        Connector S = new Connector();
        Connector Q = new Connector();
        Connector NOT_Q = new Connector();

        int currTimerBox = 1;
        
        public MainWindow()
        {
            InitializeComponent();
            Loaded += new RoutedEventHandler(Page1_Loaded);
            Unloaded += new RoutedEventHandler(Page1_Unloaded);

            InitializeLatch();
        }
        public void Page1_Loaded(object sender, RoutedEventArgs e)
        {
            timer = new DispatcherTimer();
            timer.Interval = System.TimeSpan.FromMilliseconds(30);
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

            if (Q.HasSignal())
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                TextBox_Q.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                TextBox_Q.Background = scb;
            }

            if (NOT_Q.HasSignal())
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Green;
                TextBox_NOT_Q.Background = scb;
            }
            else
            {
                SolidColorBrush scb = new SolidColorBrush();
                scb.Color = Colors.Red;
                TextBox_NOT_Q.Background = scb;
            }

            R.SendSignal(false);
            S.SendSignal(false);

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
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            R.SendSignal(true);
        }

        private void button_S_Click(object sender, RoutedEventArgs e)
        {
            S.SendSignal(true);
        }

        private void InitializeLatch()
        {
            og1.ConnectInputA(R);
            og1.ConnectOutput(Q);

            og2.ConnectInputB(S);
            og2.ConnectOutput(NOT_Q);

            // cross connect for latch behavior
            og1.ConnectInputB(NOT_Q);
            og2.ConnectInputA(Q);

            components.Add(og1);
            components.Add(og2);

        }
    }
}
