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

namespace XAML_Basics_ch2
{
    // note that on the xaml page the grid is named using a convention
    // that allows names on objects that don't have a name property!
    // its a decorator class that gets applied.

    // the button foreground is set using a xaml oriented reference to 
    // a static class property offered in .NET.

    // also note the attached 'Grid.Row' in the button/text boxes/etc.  
    // these are attached properties that come from the Grid container 
    // that the controls exist in.

    // xml:space="preserve"  is applied to text and shows an exact match of what appears
    // in the element without doing fancy whitespace stripping, etc.  Use with care.

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
    }
}
