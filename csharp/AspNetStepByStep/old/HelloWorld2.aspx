<%@ Page language="C#" Debug = "true" %>
<html>
	<body>
		<h1>Hello World!</h1>
		<%
            // this block will execute in the Render_Control method
			Response.Write("Check out the family tree: <br> <br>");
			Response.Write(this.GetType().ToString());
			Response.Write(" which derives from <br> ");
            Response.Write(this.GetType().BaseType.ToString());
            Response.Write(" which derives from <br> ");
            Response.Write(this.GetType().BaseType.BaseType.ToString());
            Response.Write(" which derives from <br> ");
            Response.Write(this.GetType().BaseType.BaseType.BaseType.ToString());
            Response.Write(" which derives from <br> ");
            Response.Write(this.GetType().BaseType.BaseType.BaseType.BaseType.ToString());


        %>
	</body>

</html>