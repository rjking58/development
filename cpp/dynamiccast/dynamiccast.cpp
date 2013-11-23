#include <iostream.h>
#include <windows.h>

class Concrete1;
class Concrete2;
class Concrete3;

class Abstract
{
public:
	virtual int Compare(Abstract * a_obj) = 0;
};

//@DESC: Relationship to be modeled:
//@DESC: Concrete 1 - concrete 2 returns true
//@DESC: Concrete 2 - concrete 3 returns true
//@DESC: all others return false.
//@PGMR: RJK
//@CRDT: 19980615


class Concrete1 : public Abstract
{
public:
	virtual int Compare(Abstract * a_obj);
};

class Concrete2 : public Abstract
{
public:
	virtual int Compare(Abstract * a_obj);

};

class Concrete3 : public Abstract
{
public:
	virtual int Compare(Abstract * a_obj);

};

int Concrete1::Compare(Abstract * a_obj)
{
	Concrete2 	*c2_p;
	
	// we only are true against concrete2 objs.
	c2_p = dynamic_cast<Concrete2 *> (a_obj);
	
	// force into language rep. of boolean results.
	return (c2_p != NULL);
}

int Concrete2::Compare(Abstract * a_obj)
{
	Concrete1 	*c1_p;
	Concrete3	*c3_p;
	int			retval = FALSE;
	
	// we only are true against concrete2 objs.
	c1_p = dynamic_cast<Concrete1 *> (a_obj);
	c3_p = dynamic_cast<Concrete3 *> (a_obj);

	if (c1_p != NULL || c3_p != NULL)
	{
		retval = TRUE;
	}
	
	// force into language rep. of boolean results.
	return retval;
}

int Concrete3::Compare(Abstract * a_obj)
{
	Concrete2 	*c2_p;
	
	// we only are true against concrete2 objs.
	c2_p = dynamic_cast<Concrete2 *> (a_obj);

	
	// force into language rep. of boolean results.
	return (c2_p != NULL);
}


void main()
{
	Abstract 	*ab_ar[10];
	Abstract		*cmp_ab;

	ab_ar[0] = new Concrete1;
	ab_ar[1] = new Concrete2;
	ab_ar[2] = new Concrete3;

	cmp_ab = new Concrete1;

	for (int x = 0; x < 3; x++)
	{
		cout << "1 to " << (x+1) << endl;
		if(ab_ar[x]->Compare(cmp_ab))
		{
			cout << "returned TRUE" << endl;
		}
		else 
		{
			cout << "returned FALSE" << endl;
		}
	}

	delete cmp_ab;
	cmp_ab = new Concrete2;

	for (x = 0; x < 3; x++)
	{
		cout << "2 to " << (x+1) << endl;
		if(ab_ar[x]->Compare(cmp_ab))
		{
			cout << "returned TRUE" << endl;
		}
		else 
		{
			cout << "returned FALSE" << endl;
		}
	}
	delete cmp_ab;
	cmp_ab = new Concrete3;

	for (x = 0; x < 3; x++)
	{
		cout << "3 to " << (x+1) << endl;
		if(ab_ar[x]->Compare(cmp_ab))
		{
			cout << "returned TRUE" << endl;
		}
		else 
		{
			cout << "returned FALSE" << endl;
		}
	}

}


