#include <afxcoll.h>
#include <afxtempl.h>

#include <iostream.h>
#include <string.h>
#include "compst.h"
#include "except.h"



Component::Component(char *name)
{

	m_name_ar = new char[strlen(name) + 1];	// always remember the NULL Luke!

	if(m_name_ar == NULL)
	{
		throw(EXC_HEAP_ALLOC_FAILURE);
	}
	else
	{
		strcpy(m_name_ar,name);
	}
}

Component::~Component()
{
	cout << "Deleting component:" << m_name_ar << endl;
	delete [] m_name_ar;
}

void Component::Operation()
{
	cout << m_name_ar << endl;	
}
void Component::Add(Component * Component_o)
{
	// our base class object can't do these things.
	throw(EXC_BAD_ADD_COMPONENT);
}
void Component::Remove(Component * Component_o)
{
	// our base class object can't do these things.
	throw(EXC_BAD_REMOVE_COMPONENT);
}


int	Component::GetCount()
{
	throw(EXC_BAD_COUNT_CALL);
	return 0;
}

Component * Component::Get(int position)
{
	throw(EXC_BAD_GET_CALL);
	return 0;
}


Component * Component::GetChild()
{
	// our base class object can't do these things.
	return 0;
}

ComponentIterator *	Component::CreateIterator()
{
	throw(EXC_CANT_CREATE_ITERATOR);
	return 0;
}



Composite::~Composite()
{
	int ElementCount = _ComponentMap.GetSize();

	while(ElementCount > 0)
	{
		ElementCount--;
		delete _ComponentMap[ElementCount];
		_ComponentMap.RemoveAt(ElementCount);
	}
	cout << "Deleting COMPOSITE!!:(";
	PrintName();
	cout << ")" << endl;
}

void		Composite::Operation()
{

	int ElementCount = _ComponentMap.GetSize();
	int ElementOfst;

	for(ElementOfst = 0 ; ElementOfst < ElementCount; ElementOfst++)
	{
		_ComponentMap[ElementOfst]->Operation();
	}
}

void		Composite::Add(Component * Component_o)
{
	_ComponentMap.Add(Component_o);
	m_Count = _ComponentMap.GetSize();
}
void		Composite::Remove(Component * Component_o)
{
	int ElementCount = _ComponentMap.GetSize();
	BOOL Done = FALSE;

	while(		(ElementCount > 0	)
			&& 	(!Done				)		)
	{
		ElementCount--;
		if(_ComponentMap[ElementCount] == Component_o)
		{
			_ComponentMap.RemoveAt(ElementCount);
			Done = TRUE;
		}
	}

}

int Composite::GetCount()
{
	return _ComponentMap.GetSize();
}
Component * Composite::Get(int position)
{
	return _ComponentMap[position];
}

Component *	Composite::GetChild()
{
	return(this);
}

void Composite::PrintName()
{
	int ElementCount = _ComponentMap.GetSize();
	int ElementOfst;

	Component::PrintName();

	for(ElementOfst = 0 ; ElementOfst < ElementCount; ElementOfst++)
	{
		_ComponentMap[ElementOfst]->PrintName();
	}


}





void main()
{

	try
	{

		Component *			HeadComponent;
		Component *			CurrComponent;
		Component *			SubComponent;
		Component *			SubSubComponent;

		ComponentIterator * CompIter;
		int x;
		int y;
		int z;
		char name[100] = {"Object level"};
		char actual_name[100];
		char add_string[100];

		// build it up.....

		HeadComponent = new Composite("Head");
		CurrComponent = HeadComponent;

		for (x = 0; x<10 ;x++)
		{
			strcpy(actual_name,name);
			sprintf(add_string,"1-%d",x);
			strcat(actual_name,add_string);

			if(x == 2 || x == 4)
			{
				strcpy(actual_name,name);
				sprintf(add_string,"1-%d-%d",x,y);
				strcat(actual_name,add_string);

				SubComponent = new Composite(actual_name);
				CurrComponent->Add(SubComponent);
				for (y = 0; y < 10; y++)
				{
					if (y == 7 || y == 9)
					{
						SubSubComponent = new Composite(actual_name);
						SubComponent->Add(SubSubComponent);


					}
					else
					{
						SubComponent->Add(new Component(actual_name));
					}
				}

			}
			else
			{
				CurrComponent->Add(new Component(actual_name));
    		}
		}

		HeadComponent->Operation();

		// test iterator operation!
		if (HeadComponent->GetChild())
		{
			CompIter = HeadComponent->CreateIterator();

			while (! CompIter->IsDone())
			{
				CompIter->CurrentItem()->PrintName();
				(*CompIter)++;
			}
		}

		delete CompIter;

		delete HeadComponent;
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


		default:
			cout << "Exception: " << " no msg for this exception" << endl;

		}
	}
}