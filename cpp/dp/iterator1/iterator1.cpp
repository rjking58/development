
#include <iostream.h>
#include "except.h"

//////////////////////////////////////////////
////////Thing declaration/implementation
//////////////////////////////////////////////
								 
class Thing				 
{
public: 
	Thing(int i) : m_i(i) { }
	
	void PrintThing() 
	{
		cout << "Thing:" << m_i << endl;
	}
private:
	Thing();
	int m_i;

};

//////////////////////////////////////////////
////////ThingArray declaration
//////////////////////////////////////////////
class ThingIterator;

static const int THING_COUNT = 10;

class ThingArray
{
public:
	friend ThingIterator;
	
	ThingArray();
	
	~ThingArray();
	
	ThingIterator * GetThingIterator();
	
private:
	long						GetCount();
	Thing * 					Get(int offset);
	
	long						m_ThingCount;
	Thing*					mThingAr[10];
};

//////////////////////////////////////////////
////////ThingIterator declaration
//////////////////////////////////////////////

class ThingIterator
{
	ThingArray			*m_thingar ;	// we are NOT the owner of this pointer
	long					m_current_pos;
	ThingIterator()	{ }

public:
	ThingIterator(ThingArray * thingarray_o) 
							:	m_thingar(thingarray_o),
								m_current_pos(0) { }
	int						Done();
	ThingIterator&			operator++();
	const ThingIterator	operator++(int);
	Thing * 					operator*() ;

};


//////////////////////////////////////////////
////////ThingArray implementation
//////////////////////////////////////////////

ThingArray::ThingArray() : m_ThingCount(THING_COUNT)
{
	for (int i = 0 ; i < THING_COUNT ; i++)
	{
		mThingAr[i] = new Thing(i);
		if (! mThingAr[i])
		{
			throw(EXC_HEAP_ALLOC_FAILURE);
		}
	}
}
	
ThingArray::~ThingArray()
{
	for (int i = 0 ; i < THING_COUNT ; i++)
	{
		delete mThingAr[i];
	}
}
	
ThingIterator * ThingArray::GetThingIterator()
{
	ThingIterator * ti;
	
	ti = new ThingIterator(this);
	
	if (! ti)
	{
		throw(EXC_HEAP_ALLOC_FAILURE);
	}

	return ti;
}
	
Thing * ThingArray::Get(int offset) 
{
	if (offset > m_ThingCount)
	{
		throw(EXC_BAD_ARRAY_ACCESS );		
	}
	return mThingAr[offset];
}

long	ThingArray::GetCount()
{
	return m_ThingCount;
}

//////////////////////////////////////////////
////////ThingIterator implementation
//////////////////////////////////////////////


int ThingIterator::Done() 
{
	return m_current_pos >= m_thingar->GetCount();
}

ThingIterator & ThingIterator::operator++() // prefix
{
	m_current_pos++;
   return *this;
}
const ThingIterator  ThingIterator::operator++(int)	// postfix!
{
	ThingIterator  tempThing = *this;
	m_current_pos++;
	
	return tempThing;
}


Thing * ThingIterator::operator*()
{
	if(Done())
	{
		throw(EXC_ITERATOR_PASSED_END);
	}
	return  m_thingar->Get(m_current_pos);
}



void main()
{
	ThingArray		ta1;
	ThingIterator *ti1;

	try
	{
		ti1 = ta1.GetThingIterator();

		while(! ti1->Done() )
		{
			// postfix...
			// terse way...
			//(*(*ti1)++)->PrintThing();
			
			// less terse way...
			(**ti1)->PrintThing();
			(*ti1)++;

		}

		// should cause error!
		(**ti1)->PrintThing();
		
	}
	catch(EXCEPTION_CODE ec)
	{
		
		switch (ec)
		{
		case EXC_MEMORY_ALLOC_FAILURE_LISTCLASS :
			cout << "Exception:" << "mem alloc failure.. list class" << endl;
			break;

		case EXC_HEAP_ALLOC_FAILURE :
			cout << "Exception:" << "Heap allocation failure!" << endl;
			break;

		case EXC_BAD_ADD_COMPONENT :
			cout << "Exception:" << "Tried to add w/ component object" << endl;
			break;

		case EXC_BAD_REMOVE_COMPONENT :
			cout << "Exception:" << "Tried to remove w/ component object" << endl;
			break;

		case EXC_BAD_COUNT_CALL :
			cout << "Exception:" << "Tried to get count on a component object" << endl;
			break;

		case EXC_BAD_GET_CALL :
			cout << "Exception:" << "Tried to get a component object from a component object" << endl;
			break;

		case EXC_CANT_CREATE_ITERATOR :
			cout << "Exception:" << "Can't create component for object of this type!" << endl;
			break;

		case EXC_BAD_ARRAY_ACCESS :
			cout << "Exception:" << "Array access out of bounds!" << endl;
			break;
			
		case EXC_ITERATOR_PASSED_END :
			cout << "Exception:" << "Access of object passed end of iterator!" << endl;
			break;
		
		default:
			cout << "Exception: " << " no msg for this exception" << endl;

		}
	}

}


