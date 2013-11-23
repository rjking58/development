#include <iostream.h>
#include <string.h>
#include <strstrea.h>

// example showing how a class that is contained in another 
// class always has its copy constructor called during normal 
// object copy

class ContainedClass
{

public:
	// normal constructor... set our name up using passed in variable..
	
	ContainedClass(char * name) : mName(new char [(strlen(name) + 1)])
	{
		cout << "ContainedClass::Normal Constructor Call" << endl;
		strcpy(mName,name);
	}

	// copy constructor.. required since we are manipulating char *'s  
	ContainedClass(ContainedClass& CCref)
	{
		ostrstream tmp;

		cout << "ContainedClass::**COPY** Constructor Call" << endl;

		mName = new char [strlen(CCref.mName) + 9];

		tmp << "copy of " << CCref.mName << ends;

		strcpy(mName,tmp.str());
	}

	// assignment op.. again... required since we are manipulating char *'s  
	ContainedClass& operator=(ContainedClass& CCref)
	{
		ostrstream tmp;

		cout << "ContainedClass::**assignment** Called" << endl;

		mName = new char [strlen(CCref.mName) + 9];

		tmp << "copy of " << CCref.mName << ends;

		strcpy(mName,tmp.str());

		return *this;
	}


	~ContainedClass()
	{
		cout << "ContainedClass::Normal Destructor Call" << endl;
	}

	void PrintName()
	{
		cout << mName << endl;
	}

private:
	ContainedClass();
	char * mName;
	
};

// this class acts as a container for the ContainedClass.  
class BaseClass
{
public:
	BaseClass(char * CCName) : CCobj(CCName)
	{
		cout << "BaseClass::Normal Constructor Call" << endl;
	}
	virtual ~BaseClass()
	{
		cout << "BaseClass::Normal Destructor Call" << endl;
	}
	virtual BaseClass* Clone() = 0;
protected:
	ContainedClass CCobj;
};

class SubClass : public BaseClass
{
public:
	SubClass(char * CCName) : BaseClass(CCName)
	{
		cout << "SubClass::Normal Constructor Call" << endl;
	}
	~SubClass()
	{
		cout << "SubClass::Normal Destructor Call" << endl;
	}
	virtual BaseClass* Clone()
	{

		cout << "SubClass::Clone Call" << endl;
		
		// intentionally invoke copy construction.  
		// Order of Events.. Copy Contained class, automatically calling the defined CC.
		//							Copy BaseClass, automatically calling the default CC.
		//							Copy SubClass, automatically calling the default CC.
		return new SubClass(*this);
	}
	void PrintName()
	{
		CCobj.PrintName();
	}
private:
	int i;
};

void main(void)
{
	// create our SubClass.. setting the CCobj to "WoofWoof"
	SubClass sc1("WoofWoof");
	// intentionally invoke copy construction.  
	// Order of Events.. Copy Contained class, automatically calling the defined CC.
	//							Copy BaseClass, automatically calling the default CC.
	//							Copy SubClass, automatically calling the default CC.
	SubClass sc2 = sc1;
	SubClass *p_sc3;
		
	p_sc3 = (SubClass *)sc2.Clone();

	// make sure it worked...
	sc1.PrintName();
	sc2.PrintName();
	p_sc3->PrintName();

}