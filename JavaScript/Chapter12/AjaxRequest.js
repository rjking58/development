AjaxRequest.prototype.send = function(type,url,handler,postDataType,postData)
{
	if(this.request != null)
	{
		// kill previous request..
		this.request.abort();
		url += "?dummy=" + new Date().getTime();

		try
		{
			this.request.onreadystatechange = handler;
			this.request.open(type,url,true);
			if(type.toLowerCase() == "get")
			{
				this.request.send(null);
			}
			else
			{
				this.request.setRequestHeader("Content-Type",postDataType);
				this.request.send(postData);
			}
		} catch (e)
		{
			alert("Ajax error communicating with the server.\n" + "Details: " + e);
		}
	}
}
