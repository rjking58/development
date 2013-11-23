#include <iostream.h>

//BUILDER::  
//		point:  allows multiple conversions for a single input format
//				the single input format is implemented by the director
//				the multiple output formats are implemented by the 
//				sub-classed builder




// these classes are elements of the widget class.
class MessageClass
{
public:
	virtual void do_msg(void)
	{
		cout << "MessageClass base class message.." << endl;
	}
};

class MessageClassD1 : public MessageClass
{
public:
	virtual void do_msg(void)
	{
		cout << "MessageClassD1 derived class message.." << endl;
	}
};


class NumberClass
{
protected:
	int m_num;
public:
	NumberClass(): m_num(20) 
	{
		cout << "NumberClass::NumberClass called" << endl;
		cout << "NumberClass::NumberClass exit" << endl;
	}
	int get_num(void)
	{
		cout << "NumberClass::get_num called" << endl;
		return m_num;
		cout << "NumberClass::get_num exit" << endl;
	}
};

class NumberClassD1 : public NumberClass
{
public:
	NumberClassD1() 
	{ 
		cout << "NumberClassD1::NumberClassD1 called" << endl;
		m_num = 45;
		cout << "NumberClassD1::NumberClassD1 exit" << endl;
	}
};


// this is the widget which is built by the builder/director
class WidgetClass
{
	MessageClass	*m_msg_c1;
	NumberClass		*m_num_c1;

public:
	WidgetClass()
	{
		cout << "WidgetClass::WidgetClass called" << endl;
		m_msg_c1 = NULL;
		m_num_c1 = NULL;
		cout << "WidgetClass::WidgetClass exit" << endl;
	}
	~WidgetClass()
	{
		cout << "WidgetClass::~WidgetClass called" << endl;
		if (!m_msg_c1)
		{
			delete m_msg_c1;
		}
		if (!m_num_c1)
		{
			delete m_num_c1;
		}
		cout << "WidgetClass::~WidgetClass exit" << endl;
	}
	void AddMessageClass(MessageClass	*msg_c1)
	{
		cout << "WidgetClass::AddMessageClass called" << endl;
		m_msg_c1 = msg_c1;
		cout << "WidgetClass::AddMessageClass exit" << endl;
	}
	void AddNumberClass(NumberClass	*num_c1)
	{
		cout << "WidgetClass::AddNumberClass called" << endl;
		m_num_c1 = num_c1;
		cout << "WidgetClass::AddNumberClass exit" << endl;
	}

	void DoMsg(void)
	{
		cout << "WidgetClass::DoMsg called" << endl;
		m_msg_c1->do_msg();
		cout << "WidgetClass::DoMsg exit" << endl;
	}

	void DoNum(void)
	{
		cout << "WidgetClass::DoNum called" << endl;
		cout << "number-->" << m_num_c1->get_num() << endl;
		cout << "WidgetClass::DoNum exit" << endl;
	}
};


// class responsible for building an object.  
// this contains the discrete actions used to build widgets 
// but DOES NOT abstract the ordering of the actions used to build 
// widgets

// this is where the widget creators are held
class WidgetBuilderBase
{
protected:
	WidgetClass		*msg_num;

public:

	WidgetBuilderBase() { }
	virtual void CreateWidgetClass(void) = 0;
	virtual void CreateNumClass(void) = 0;
    virtual void CreateMsgClass(void) = 0;
	virtual WidgetClass * GetMsgNum(void) = 0;

};

class WidgetBuilder : public WidgetBuilderBase
{

public:
	WidgetBuilder() 
	{
		cout << "WidgetBuilder::WidgetBuilder called" << endl;
		cout << "WidgetBuilder::WidgetBuilder exit" << endl;
    }
	void CreateWidgetClass(void)
	{
		cout << "WidgetBuilder::CreateWidgetClass called" << endl;
		msg_num = new WidgetClass;
		cout << "WidgetBuilder::CreateWidgetClass exit" << endl;
	}
	void CreateNumClass(void)
	{
		cout << "WidgetBuilder::CreateNumClass called" << endl;
		NumberClass	*nc = new NumberClass;

		msg_num->AddNumberClass(nc);
		cout << "WidgetBuilder::CreateNumClass exit" << endl;

	}
	void CreateMsgClass(void)
	{
		cout << "WidgetBuilder::CreateMsgClass called" << endl;
		MessageClass	*mc = new MessageClass;
		msg_num->AddMessageClass(mc);
		cout << "WidgetBuilder::CreateMsgClass exit" << endl;
	}

	WidgetClass * GetMsgNum(void)
	{
		cout << "WidgetBuilder::GetMsgNum called" << endl;
		cout << "WidgetBuilder::GetMsgNum exit" << endl;
		return msg_num;
	}
};

class WidgetBuilder2 : public WidgetBuilderBase
{

public:
	WidgetBuilder2() 
	{
		cout << "WidgetBuilder2::WidgetBuilder2 called" << endl;
		cout << "WidgetBuilder2::WidgetBuilder2 exit" << endl;
    }
	void CreateWidgetClass(void)
	{
		cout << "WidgetBuilder2::CreateWidgetClass called" << endl;
		msg_num = new WidgetClass;
		cout << "WidgetBuilder2::CreateWidgetClass exit" << endl;
	}
	void CreateNumClass(void)
	{
		cout << "WidgetBuilder2::CreateNumClass called" << endl;
		NumberClass	*nc = new NumberClassD1;

		msg_num->AddNumberClass(nc);
		cout << "WidgetBuilder2::CreateNumClass exit" << endl;

	}
	void CreateMsgClass(void)
	{
		cout << "WidgetBuilder2::CreateMsgClass called" << endl;
		MessageClass	*mc = new MessageClassD1;
		msg_num->AddMessageClass(mc);
		cout << "WidgetBuilder2::CreateMsgClass exit" << endl;
	}

	WidgetClass * GetMsgNum(void)
	{
		cout << "WidgetBuilder2::GetMsgNum called" << endl;
		cout << "WidgetBuilder2::GetMsgNum exit" << endl;
		return msg_num;
	}
};



// this class knows about building the product and implements
// the ordering of widget actions in the builder.

// this is where the initialization abstraction is held
class WidgetDirector
{

	WidgetBuilderBase * m_WidgetBuilder;

	WidgetDirector() { }
public:
	WidgetDirector(WidgetBuilderBase * WidgetBuilder) :
		m_WidgetBuilder(WidgetBuilder)
	{
		
		// this is the director for the build...
		// the directors job is to provide a standard way of building
		// a more complex class...

		// possibly a more reasonable implemenation would
		// be to make this a normal member function rather
		// than part of the constructure.. but HEY...
		// its just a test program...
		cout << "START WidgetDirector constructor" << endl;
		cout << "WidgetDirector:: CreateWidgetClass()" << endl;

		// create the class
		WidgetBuilder->CreateWidgetClass();
		cout << "WidgetDirector:: CreateNumClass()" << endl;

		// create any contained classes, items
		WidgetBuilder->CreateNumClass();
		cout << "WidgetDirector:: CreateMsgClass()" << endl;
		WidgetBuilder->CreateMsgClass();

		cout << "END WidgetDirector constructor" << endl;
	}
	~WidgetDirector()
	{
		cout << "START WidgetDirector destructor" << endl;
		cout << "END WidgetDirector destructor" << endl;
	}

	WidgetClass *GetProduct(void)
	{
		// return the produced object to the client...
		return m_WidgetBuilder->GetMsgNum();
	}


};


void main(void )
{

	// change the new'd object to use different builder... 
	// pointer should remain the base pointer...
	// Nothing else has to change!!!
	WidgetBuilderBase *mnb_p = new WidgetBuilder2;


	WidgetDirector director(mnb_p);

	WidgetClass * mnc_product_p = director.GetProduct();

	mnc_product_p->DoMsg();
	mnc_product_p->DoNum();

}