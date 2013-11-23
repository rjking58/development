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
        myButton.Style.Add("color","White");
        myButton.Style.Add("background-color", "Black");
        myButton.Value = "weee!";
    }
    private void Page_Init(object sendiner, EventArgs e)
    {
    }
    private void Page_PreInit(object sendiner, EventArgs e)
    {
        // example of creating a control out of whole cloth during the page 
        // PreInit portion of the processing cycle.
        TextBox textBoxUserName = new TextBox();
        textBoxUserName.ID = "TextBoxUserName";
        form1.Controls.Add(textBoxUserName);
    }
}
