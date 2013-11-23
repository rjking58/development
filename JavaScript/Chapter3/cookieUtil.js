// write a cookie to the cache.
function writeCookie(name,value,days)
{
	var expires = "";

	if(days)
	{
		var date= new Date();
		date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
		expires = "; expires=" + date.toGMTString();
	}

	document.cookie = name + "=" + value + expires + ";path=/";
}

// read the cookie from the cookie-cache
function readCookie(name)
{
	var searchName = name + "=";
	var cookies = document.cookie.split(';');
	for (var currcookie =0; currcookie < cookies.length; currcookie++)
	{
		var c = cookies[currcookie];
		while (c.charAt(0) == ' ')
		{
			c = c.substring(1,c.length);
		}
		if (c.indexOf(searchName) == 0)
		{
			return c.substring(searchName.length, c.length);
		}
	}
	return null;
}

// erase the cookie from the cookie-cache
function eraseCookie(name)
{
	writeCookie(name,"",-1);
}
