#include <iostream.h>
#include <windows.h>

class Concrete1;
class Concrete2;
class Concrete3;

class Abstract
{
public:
	virtual int Compare(Abstract * a_obj) = 0;
	virtual int Compare(Concrete1 * a_obj) = 0;
	virtual int Compare(Concrete2 * a_obj) = 0;
	virtual int Compare(Concrete3 * a_obj) = 0;
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
	virtual int Compare(Abstract * a_obj)
	{
		return a_obj->Compare(this);
	}

	virtual int Compare(Concrete1 * a_obj)
	{
		cout << "1 to 1" << endl;
		return FALSE;
	}
	virtual int Compare(Concrete2 * a_obj)
	{
		cout << "1 to 2" << endl;
		return TRUE;
	}
	virtual int Compare(Concrete3 * a_obj)
	{
		cout << "1 to 3" << endl;
		return FALSE;
	}

};

class Concrete2 : public Abstract
{
public:
	virtual int Compare(Abstract * a_obj)
	{
		return a_obj->Compare(this);
	}

	virtual int Compare(Concrete1 * a_obj)
	{
		cout << "2 to 1" << endl;
		return TRUE;
	}
	virtual int Compare(Concrete2 * a_obj)
	{
		cout << "2 to 2" << endl;
		return FALSE;
	}
	virtual int Compare(Concrete3 * a_obj)
	{
		cout << "2 to 3" << endl;
		return TRUE;
	}
};

class Concrete3 : public Abstract
{
public:
	virtual int Compare(Abstract * a_obj)
	{
		return a_obj->Compare(this);
	}

	virtual int Compare(Concrete1 * a_obj)
	{
		cout << "3 to 1" << endl;
		return FALSE;
	}
	virtual int Compare(Concrete2 * a_obj)
	{
		cout << "3 to 2" << endl;
		return TRUE;
	}
	virtual int Compare(Concrete3 * a_obj)
	{
		cout << "3 to 3" << endl;
		return FALSE;
	}
};

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
