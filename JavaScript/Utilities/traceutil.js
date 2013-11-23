
// simple object called 'DebugConsole'
function DebugConsole()
{   
	var consoleElem = document.createElement("div");
	consoleElem.id = "debug";
	consoleElem.style = "monospace";
	consoleElem.color = "#333333";

	document.body.appendChild(consoleElem);
	consoleElem.appendChild(document.createElement("hr"));

	this.shaded = false;
}

DebugConsole.prototype.displayMsg = function(funcname,varname,msg)
{
	var msgElement = document.createElement("div");
	msgElement.appendChild(document.createTextNode(funcname + "::" + varname
												   + "[" + msg + "]"));
	msgElement.style.backgroundColor = this.shaded ? "#DDDDDD" : "#FFFFFF";
	var consoleElem = document.getElementById("debug");
	consoleElem.appendChild(msgElement);
	this.shaded = ! this.shaded;
}
