#include <iostream.h>


class Concrete1;
class Concrete2;
// Abstract visitor class															
class Visitor
{
public:
	~Visitor()
	{
	
	}
	// One visit operation for each type of concrete element we can manipulate...
	// i.e. Real numbers
	virtual void VisitConcrete1(Concrete1 * pC1) = 0;
	// i.e. Integers
	virtual void VisitConcrete2(Concrete2 * pC2) = 0;
};


class Element
{
public:
	virtual void Accept(Visitor *v) = 0;
	virtual void DoStuff() = 0;
};


class Concrete1 : public Element
{
public:
	virtual void Accept(Visitor *v)
	{
		v->VisitConcrete1(this);
	}
	virtual void DoStuff()
	{
		cout << "Concrete1:: doing stuff" << endl;
	}
};

class Concrete2 : public Element
{
public:
	virtual void Accept(Visitor *v)
	{
		v->VisitConcrete2(this);
	}
	virtual void DoStuff()
	{
		cout << "Concrete2:: doing stuff" << endl;
	}
};


// Operation #1 to be performed on the element... i.e.  multiplying...
class VisitorOperationA : public Visitor
{
public:
	virtual void VisitConcrete1(Concrete1 * pC1)
	{
		cout << "VisitorA::VisitConcrete1";
		// note that any portions of Concrete1's public interface may be called...
		pC1->DoStuff();
	}
	virtual void VisitConcrete2(Concrete2 * pC2)
	{
		cout << "VisitorA::VisitConcrete2";
		// note that any portions of Concrete2's public interface may be called...
		pC2->DoStuff();
	}
};

// Operation #2 to be performed on element... i.e. adding...
class VisitorOperationB : public Visitor
{
public:
	virtual void VisitConcrete1(Concrete1 * pC1)
	{
		cout << "VisitorB::VisitConcrete1";
		// note that any portions of Concrete1's public interface may be called...
		pC1->DoStuff();
	}
	virtual void VisitConcrete2(Concrete2 * pC2)
	{
		cout << "VisitorB::VisitConcrete2";
		// note that any portions of Concrete2's public interface may be called...
		pC2->DoStuff();
	}
};

void main()
{
	VisitorOperationA	VOA;
	VisitorOperationB	VOB;
	
	Concrete1	C1;
	Concrete2	C2;
	
	// do both operations on C1
	
	C1.Accept(&VOA);
	C1.Accept(&VOB);
	
	// do both operations on C2
	C2.Accept(&VOA);
	C2.Accept(&VOB);
	
	
	
}
