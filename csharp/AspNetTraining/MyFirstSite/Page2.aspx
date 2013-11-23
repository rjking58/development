<%@ Page Language="C#" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<script runat="server">
    private void OnSubmit(Object sender, EventArgs args)
    {
        LabelResponse.Text = "You Suxx0rz " + TextBoxName.Text + "!";
    }
    private void Page_Load()
    {
        if (IsPostBack)
        {
            // Validate initially to force asterisks
            // to appear before the first roundtrip.
            PostbackDetected.Text = "postback!!!!!";
        }
    }

    
</script>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>SamplePage</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        Enter Name: <asp:TextBox ID="TextBoxName" runat="server"></asp:TextBox>
        <asp:Button ID="ButtonSubmit" runat="server" Text="Submit" OnClick="OnSubmit" />
        <br />
        <asp:Label ID="LabelResponse" runat="server" Text=""></asp:Label>
        <br />
        <asp:Label ID="PostbackDetected" runat="server" Text="no postback"></asp:Label>
    </div>
    </form>
</body>
</html>
