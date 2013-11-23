<%@ Page Language="C#" trace="true" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <p style="font-family: 'Times New Roman'; font-size: 14pt; font-weight: bold">
        Page in Visual Studio</p>
    <form id="form1" runat="server">
    <div>
    
        <asp:Label ForeColor="Crimson" ID="Label1" runat="server" Font-Names="Times New Roman" 
            Font-Size="Small" Text="Type In Me"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
    
    </div>
    <div>
        <asp:DropDownList ID="DropDownList1" runat="server">
            <asp:ListItem>selection 1</asp:ListItem>
            <asp:ListItem>selection 2</asp:ListItem>
            <asp:ListItem>selection 3</asp:ListItem>
            <asp:ListItem>selection 4</asp:ListItem>
        </asp:DropDownList>
    </div>
    <div>
        <asp:Button ID="Button1" runat="server" Text="Press Me!" 
            onclick="Button1_Click1" /> <br />
        <asp:Label ID="textboxoutput" runat="server" Font-Names="Times New Roman" 
            Font-Size="Small" Text=""></asp:Label>
        
    </div>
    <asp:Calendar ID="Calendar1" runat="server" BackColor="White" 
        BorderColor="#999999" CellPadding="4" DayNameFormat="Shortest" 
        Font-Names="Verdana" Font-Size="8pt" ForeColor="Black" Height="180px" 
        onselectionchanged="Calendar1_SelectionChanged" Width="200px">
        <SelectedDayStyle BackColor="#666666" Font-Bold="True" ForeColor="White" />
        <SelectorStyle BackColor="#CCCCCC" />
        <WeekendDayStyle BackColor="#FFFFCC" />
        <TodayDayStyle BackColor="#CCCCCC" ForeColor="Black" />
        <OtherMonthDayStyle ForeColor="#808080" />
        <NextPrevStyle VerticalAlign="Bottom" />
        <DayHeaderStyle BackColor="#CCCCCC" Font-Bold="True" Font-Size="7pt" />
        <TitleStyle BackColor="#999999" BorderColor="Black" Font-Bold="True" />
    </asp:Calendar><br />
    <asp:Label ID="calendaroutput" runat="server" Font-Names="Times New Roman" Font-Size="Small" Text=""></asp:Label>
    
    </form>
</body>
</html>
