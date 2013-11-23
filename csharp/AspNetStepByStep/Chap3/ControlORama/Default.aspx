<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <div style="font-weight: bold; font-size: 14pt; font-family: 'Times New Roman'">
        Page In Visual Studio
    </div>
        <asp:Label ID="ResultOfTyping" runat="server" Font-Bold="True" Font-Names="Lucida Console" Font-Size="Medium"></asp:Label>
        <br />
        <asp:Label ID="Label1" runat="server" Text="Type in me"></asp:Label><asp:TextBox
            ID="TextBox1" runat="server"></asp:TextBox>
            <br />
            <asp:DropDownList ID="DropDownList1" runat="server">
                <asp:ListItem>Item1</asp:ListItem>
                <asp:ListItem>Item2</asp:ListItem>
                <asp:ListItem>Item3</asp:ListItem>
                <asp:ListItem>Item4</asp:ListItem>
            </asp:DropDownList>
            <br />
        <asp:Button ID="Button1" runat="server" Text="Press me now, dawg!" OnClick="Button1_Click" />
    <br />
    <br />
    <br />
    <a href="UseCustomControls.aspx">Custom Controls Demo</a>
    <br />
    <a href="UsePalindromeCheckerControls.aspx">Palindrome Checker Controls Demo</a></form>
</body>
</html>
