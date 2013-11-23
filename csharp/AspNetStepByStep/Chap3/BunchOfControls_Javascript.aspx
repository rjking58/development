<%@ Language="javascript" %>

 <h2> Page in ASP </h2>
 <form>
	 <span>Type in me</span>
	 <input name="textinfo" type="text" id="textinfo" />
	 <BR>
	 <select name="selectitems" id="ddl">
		 <option value="Item 1">Item 1</option>
		 <option value="Item 2">Item 2</option>
		 <option value="Item 3">Item 3</option>
		 <option value="Item 4">Item 4</option>
	 </select>
	 <BR>
	 <input type="submit" name="pressme" value="Press Me!" id="pressme" />
<p>
<% if (Request("textinfo") != "") { %>
this was in the text box: <%=Request("textinfo") %> <br>
And this was in the selection control: <%=Request("selectitems") %>
<% } %>
</p>
</form>
