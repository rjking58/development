using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button1_Click1(object sender, EventArgs e)
    {
        Response.Write("Hello, here's what you typed into the text box: ");
        Response.Write(this.TextBox1.Text);
        textboxoutput.Text = this.TextBox1.Text;
    }
    protected void Calendar1_SelectionChanged(object sender, EventArgs e)
    {
        calendaroutput.Text = Calendar1.SelectedDate.ToLongDateString();
    }
}
