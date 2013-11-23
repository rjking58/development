// Copyright (C) 1995 Treasury Services Corporation ALL RIGHTS RESERVED

#ifndef INC_SIMPSTR_H
#define INC_SIMPSTR_H 1

#ifndef INC_IOSTREAM_H
#define INC_IOSTREAM_H 1
#include <iostream.h>
#endif // INC_IOSTREAM_H


//@DESC: Simple byte/ascii string null terminated with comparison and
//			hash operators.
//@PGMR: LDC
//@CRDT: 19950525
class  SimpleString
{
public:
	SimpleString(const char* = 0);
	~SimpleString();

	SimpleString(const SimpleString&);
	SimpleString& operator=(const SimpleString&);

	// operator= on a const char* (it's so much simpler).
	SimpleString& operator=(const char*);

	// Comparison
	friend int operator<(const SimpleString&, const SimpleString&);
	friend int operator<(const char *, const SimpleString&);
	friend int operator<(const SimpleString&, const char*);
	friend int operator>(const SimpleString&, const SimpleString&);
	friend int operator>(const char*, const SimpleString&);
	friend int operator>(const SimpleString&, const char *);
	friend int operator==(const SimpleString&, const SimpleString&);
	friend int operator==(const char*, const SimpleString&);
	friend int operator==(const SimpleString&, const char*);

	void Concat(const char*);
	int StrLen() const;

	//@DESC: operator <=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator<=(const SimpleString& S1, const SimpleString& S2)
	{
		return !(S1 > S2);
	}

	//@DESC: operator <=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator<=(const char* S1, const SimpleString& S2)
	{
		return !(S1 > S2);
	}

	//@DESC: operator <=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator<=(const SimpleString& S1, const char* S2)
	{
		return !(S1 > S2);
	}

	//@DESC: operator >=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator>=(const SimpleString& S1, const SimpleString& S2)
	{
		return !(S1 < S2);
	}

	//@DESC: operator >=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator>=(const char* S1, const SimpleString& S2)
	{
		return !(S1 < S2);
	}

	//@DESC: operator >=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator>=(const SimpleString& S1, const char* S2)
	{
		return !(S1 < S2);
	}

	//@DESC: operator !=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator!=(const SimpleString& S1, const SimpleString& S2)
	{
		return !(S1 == S2);
	}

	//@DESC: operator !=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator!=(const char* S1, const SimpleString& S2)
	{
		return !(S1 == S2);
	}

	//@DESC: operator !=
	//@PGMR: LDC
	//@CRDT: 19950525
	friend int operator!=(const SimpleString& S1, const char* S2)
	{
		return !(S1 == S2);
	}

	//@DESC: cast to char*
	//@PGMR: LDC
	//@CRDT: 19950525
	operator const char*() const { return mInternalString ? mInternalString : ""; }

	unsigned HashVal() const;

	// Stream inserters.
	friend ostream& operator<<(ostream&, const SimpleString&);
	friend istream& operator>>(istream&, SimpleString&);
	
private:
	char* mInternalString;			//@DESC: The internal string
};

#endif // INC_SIMPSTR_H
