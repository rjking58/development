
#ifndef _Composite_Iterator_
#define _Composite_Iterator_

class Component;
class ComponentIterator
{
	Component	*m_component ;	// we are NOT the owner of this pointer
	long		m_current_pos;
	ComponentIterator() { }

public:
	ComponentIterator(Component * component_o) 
							:   m_component(component_o),
								m_current_pos(0) { }
	void		First();
	void		Last();
	int			IsDone();
	void		Next();
	void		operator++();
	void		operator++(int);
	Component * CurrentItem();

};

#endif