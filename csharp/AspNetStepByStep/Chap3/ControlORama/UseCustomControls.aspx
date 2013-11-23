<%@ Page Language="C#" AutoEventWireup="true" CodeFile="UseCustomControls.aspx.cs" Inherits="UseCustomControls" Trace="true" %>

<%@ Register assembly="CustomControlLib" namespace="CustomControlLib" tagprefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <cc1:ServerControl1 ID="ServerControl11" runat="server" Text="weeeee" />
    <br />
        <asp:Label ID="Label1" runat="server" Text="Type something here:"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server" Width="280px"></asp:TextBox>
    <br />
        <asp:Button ID="Button1" runat="server" Text="Set Control Text" 
            onclick="Button1_Click" />
    </div>
    
    </form>
</body>
</html>
