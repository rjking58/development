
#ifndef _Composite_
#define _Composite_

#include <afxcoll.h>
#include <afxtempl.h>
#include <iostream.h>
#include "compit.h"


class Component
{
	char *m_name_ar;
	Component();
public:
	Component(char *name);
	virtual ~Component();
	virtual void		Operation();
	virtual void		Add(Component * Component_o);
	virtual void		Remove(Component * Component_o);
	virtual	Component *	GetChild();
	virtual int			GetCount();
	virtual	Component *	Get(int pos);
	virtual void		PrintName()
	{
		cout << "PN:" << m_name_ar << endl;
	}
	virtual ComponentIterator *	CreateIterator();
};



class Composite : public Component
{

	CTypedPtrArray<CPtrArray, Component *> _ComponentMap;
	int	m_Count;
	
public:
								Composite(char *name)
									:	Component(name),
										m_Count(0)
								{ }
	virtual						~Composite();
	virtual void				Operation();
	virtual void				Add(Component * Component_o);
	virtual void				Remove(Component * Component_o);
	virtual	Component *			GetChild();
	virtual int					GetCount();
	virtual	Component *			Get(int pos);
								
	virtual void				PrintName();

	virtual ComponentIterator *	CreateIterator() 
	{
		return new ComponentIterator(this);
	}


};


#endif