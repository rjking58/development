#include <iostream.h>

class MsgClss
{
public:
	virtual void PrintMsg() = 0;
	virtual ~MsgClss()
	{
	}
};

class MsgConcreteClss : public MsgClss
{
public:
	MsgConcreteClss()
	{
		cout << "constructing Concrete" << endl;
	}
	~MsgConcreteClss()
	{
		cout << "destructing Concrete" << endl;
	}
	virtual void PrintMsg()
	{
		cout << "Enter Concrete::PrintMsg()" << endl;
		cout << "here is our message..." << endl;
		cout << "Exit Concrete::PrintMsg()" << endl;
	}
private:
};

class MsgProxyClss : public MsgClss

{
public:
	MsgProxyClss() : OurMsgClss (0)
	{
		cout << "constructing Proxy" << endl;
	}
	~MsgProxyClss()
	{
		cout << "Enter: destructing Proxy" << endl;
		if (OurMsgClss)
		{
			delete OurMsgClss;
		}
		cout << "Exit: destructing Proxy" << endl;
		
	}
	virtual void PrintMsg()
	{
		cout << "Enter Proxy::PrintMsg()" << endl;
		if(!OurMsgClss)
		{
			MakeMsgClss();
		}
		
		OurMsgClss->PrintMsg();
		cout << "Exit Proxy::PrintMsg()" << endl;
	}
protected:
	void MakeMsgClss()
	{
		OurMsgClss = new MsgConcreteClss;
	}
private:
		MsgClss *OurMsgClss;
};


void main()
{
	MsgProxyClss MPC;
	
	MPC.PrintMsg();

}