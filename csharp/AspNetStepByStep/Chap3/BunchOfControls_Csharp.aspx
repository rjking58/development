<%@ Language=C# trace=true %>
<script runat="server">
protected void Page_Load(object sender,EventArgs ea)
{
	// get the current selection..
	int curr_idx = ddl.SelectedIndex;
	// no matter what, always populate
	ddl.Items.Clear();
	ddl.Items.Add("Item 1");
	ddl.Items.Add("Item 2");
	ddl.Items.Add("Item 3");
	ddl.Items.Add("Item 4");
	// and reflect our selection
	ddl.SelectedIndex = curr_idx;
}
</script>

 <h2> Page in ASP.NET </h2>
 <form id="Form1" runat="server">
<asp:Label Text="Type in me" runat="server" />
<asp:TextBox id="textinfo" runat="server" />
<BR>
<asp:DropDownList id="ddl" runat="server" />
<BR>
<asp:Button id="pressme" Text="Press Me!" runat="server" />
</form>
