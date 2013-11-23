using System;
using System.Drawing;
using System.Windows.Forms;

class MessageButton : Button
{
    string strMessageBoxText;
    public MessageButton()
    {
        Enabled = false;

    }
    public string MessageBoxText
    {
        set
        {
            strMessageBoxText = value;
            Enabled =       (value != null      ) 
                        &&  (value.Length > 0   );
        }
        get
        {
            return strMessageBoxText;
        }
    }

    protected override void OnClick(EventArgs args)
    {
        MessageBox.Show(strMessageBoxText);
    }

}


class FormWithButton : Form
{
    private const string CLICKME = "Click Me DUDE!!";
    MessageButton mbtn;
    [STAThread]
    public static void Main()
    {
        Application.EnableVisualStyles();
        Application.Run(new FormWithButton());

    }

    public FormWithButton()
    {
        Text = "Form With Button";
        Button btn = new Button();
        btn.Parent = this;
        btn.Location = new Point(50,25);
        btn.AutoSize = true;
        btn.Text = CLICKME;
        btn.Click += ButtonOnClick;

        mbtn = new MessageButton();
        mbtn.Parent = this;
        mbtn.Location = new Point(50,50);
        mbtn.AutoSize = true;
        mbtn.Text = "My Message Button";

    }

    public void ButtonOnClick(Object objsrc, EventArgs args)
    {
        mbtn.MessageBoxText = "weeeee";
    }
}

