#include "compst.h"
#include "compit.h"


void ComponentIterator::First()
{
	m_current_pos = 0;
}

void ComponentIterator::Last()
{
	m_current_pos = (m_component->GetCount()) - 1;
}

int ComponentIterator::IsDone()
{
	return m_current_pos >= m_component->GetCount();
}
void ComponentIterator::Next()
{
	m_current_pos++;
}
void ComponentIterator::operator++()
{
	Next();
}
void ComponentIterator::operator++(int)	// postfix!
{
	Next();
}


Component *  ComponentIterator::CurrentItem()
{
	return m_component->Get(m_current_pos);
}


