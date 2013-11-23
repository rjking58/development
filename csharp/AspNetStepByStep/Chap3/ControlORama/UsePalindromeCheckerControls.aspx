<%@ Page Language="C#" AutoEventWireup="true" CodeFile="UsePalindromeCheckerControls.aspx.cs" Inherits="UsePalindromeCheckerControls" %>

<%@ Register Assembly="CustomControlLib" Namespace="CustomControlLib" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <cc1:PalindromeCheckerCustomControl ID="PalindromeCheckerCustomControl1" 
            runat="server" 
            onpalindromefound="PalindromeCheckerCustomControl1_PalindromeFound" />
        <br />
        <asp:Label ID="Label1" runat="server" Text="Type in a palindrome: "></asp:Label><asp:TextBox
            ID="TextBox1" runat="server"></asp:TextBox>
            <br />
        <asp:Button ID="Button1" runat="server" Text="Set Palindrome" 
            onclick="Button1_Click" />
    </div>
    </form>
</body>
</html>
