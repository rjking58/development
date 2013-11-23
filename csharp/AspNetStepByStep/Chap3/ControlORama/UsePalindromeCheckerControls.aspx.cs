using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class UsePalindromeCheckerControls : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        this.PalindromeCheckerCustomControl1.Text = this.TextBox1.Text;
    }
    protected void PalindromeCheckerCustomControl1_PalindromeFound(object sender, EventArgs e)
    {
        Response.Write("The page detected a PalindromeFound event");
    }
}
