#include <iostream>
// #include <stdlib.h>
#include <string.h>

class CMessage
{
public:
	virtual void PrintMessage() = 0;
};

// base class that is to be decorated...
class TestMessage : public CMessage 
{
public:
	TestMessage(char * theMsg)
	{
		mMsg = new char [strlen(theMsg) + 1];
		strcpy(mMsg,theMsg);
	}
	~TestMessage()
	{
		delete [] mMsg;
	}
	virtual void PrintMessage()
	{
		cout << mMsg;
	}
private:
	char * mMsg;
};

class CMessageDecorator : public CMessage
{
public:
	CMessageDecorator(CMessage * CMessageObj) : mCMessageObj(CMessageObj)
	{
	}

	virtual void PrintMessage()
	{
		//essential decorator behaviour... forward request to decorated
		//object.
		mCMessageObj->PrintMessage();
	}
private:
	CMessage * mCMessageObj;
};

class CMessageDecor1 : public CMessageDecorator
{
public:
	CMessageDecor1(CMessage * CMessageObj ): CMessageDecorator(CMessageObj)
	{
	}

	virtual void PrintMessage()
	{
		//essential decorator behaviour... forward request to decorated
		//object.
		CMessageDecorator::PrintMessage();

		cout << endl << "decor1.. ";
	}
};

class CMessageDecor2 : public CMessageDecorator
{
public:
	CMessageDecor2(CMessage * CMessageObj ): CMessageDecorator(CMessageObj)
	{
	}

	virtual void PrintMessage()
	{
		//essential decorator behaviour... forward request to decorated
		//object.
		CMessageDecorator::PrintMessage();
		cout << endl << "decor2.. ";
	}
};

class CMessageUser
{
public:
	CMessageUser(CMessage * CMessageObj) : mCMessageObj(CMessageObj)
	{
	}

	void PrintCMessage()
	{
		mCMessageObj->PrintMessage();
	}
private:
	CMessage * mCMessageObj;
};

void main()
{
	CMessage * CMObj = new TestMessage ("woof woof");
//	CMessageUser	CMUObj( new CMessageDecor2(new CMessageDecor1(CMObj)));
	CMessageUser	CMUObj( new CMessageDecor1(CMObj));

	CMUObj.PrintCMessage();
}
