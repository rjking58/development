//GLBL: This file modified by TSC GoGlobal
//PGMR: KMK
//DATE: 04/08/1996
/*DESC: Multi-byte enabling source base*/

// Copyright (C) 1995 Treasury Services Corporation ALL RIGHTS RESERVED
// PORT32
// #include "CompatNT.h"
// PORT32
#include <string.h>
#include "boolean.h"
#include "simpstr.h"
// #include "tsc_gall.h"

//@DESC: Cosntructor
//@PGMR: LDC
//@CRDT: 19950525
SimpleString::SimpleString(const char* Str)
	: mInternalString(Str != 0 ? new char[strlen(Str) + 1] : 0)
{
	if (mInternalString != 0)
	{
		strcpy(mInternalString, Str);
	}
}

//@DESC: Destructor
//@PGMR: LDC
//@CRDT: 19950525
SimpleString::~SimpleString()
{
	delete[] mInternalString;
}

//@DESC: Copy constructor
//@PGMR: LDC
//@CRDT: 19950525
SimpleString::SimpleString(const SimpleString& Str)
	: mInternalString(Str.mInternalString != 0
							? new char[strlen(Str.mInternalString) + 1]
							: 0)
{
	if (mInternalString)
	{
		strcpy(mInternalString, Str.mInternalString);
	}
}

//@DESC: Assignement operator
//@PGMR: LDC
//@CRDT: 19950525
SimpleString& SimpleString::operator=(const SimpleString& Str)
{
	if (this != &Str)
	{
		delete[] mInternalString;
		mInternalString = (Str.mInternalString != 0
								 ? new char[strlen(Str.mInternalString) + 1]
								 : 0);

		if (mInternalString)
		{
			strcpy(mInternalString, Str.mInternalString);
		}
	}
	return *this;
}

//@DESC: Assignment operator from a char* (not really needed)
//@PGMR: LDC
//@CRDT: 19950525
SimpleString& SimpleString::operator=(const char* Str)
{
	if (Str != mInternalString)
	{
		delete[] mInternalString;
		mInternalString = (Str == 0
								 ? 0
								 : new char[strlen(Str) + 1]);

		if (mInternalString)
		{
			strcpy(mInternalString, Str);
		}
	}
	
	return *this;
}

//@DESC: Less than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator<(const SimpleString& S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2.mInternalString)
	{
		ReturnVal = strcmp(S1.mInternalString, S2.mInternalString) < 0;
	}
	else
	{
		ReturnVal = S1.mInternalString == 0;
	}

	return ReturnVal;
}

//@DESC: Less than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator<(const char* S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1 && S2.mInternalString)
	{
		ReturnVal = strcmp(S1, S2.mInternalString) < 0;
	}
	else
	{
		ReturnVal = S1 == 0;
	}

	return ReturnVal;
}

//@DESC: Less than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator<(const SimpleString& S1, const char* S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2)
	{
		ReturnVal = strcmp(S1.mInternalString, S2) < 0;
	}
	else
	{
		ReturnVal = S1.mInternalString == 0;
	}

	return ReturnVal;
}

//@DESC: Greater than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator>(const SimpleString& S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2.mInternalString)
	{
		ReturnVal = strcmp(S1.mInternalString, S2.mInternalString) > 0;
	}
	else
	{
		ReturnVal = S1.mInternalString == S2.mInternalString;
	}

	return ReturnVal;
}

//@DESC: Greater than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator>(const char* S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1 && S2.mInternalString)
	{
		ReturnVal = strcmp(S1, S2.mInternalString) > 0;
	}
	else
	{
		ReturnVal = S1 == S2.mInternalString;
	}

	return ReturnVal;
}

//@DESC: Greater than operator
//@PGMR: LDC
//@CRDT: 19950525
int operator>(const SimpleString& S1, const char* S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2)
	{
		ReturnVal = strcmp(S1.mInternalString, S2) > 0;
	}
	else
	{
		ReturnVal = S1.mInternalString == S2;
	}

	return ReturnVal;
}

//@DESC: Equivalence operator
//@PGMR: LDC
//@CRDT: 19950525
int operator==(const SimpleString& S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2.mInternalString)
	{
		ReturnVal = strcmp(S1.mInternalString, S2.mInternalString) == 0;
	}
	else
	{
		ReturnVal = S2.mInternalString == S1.mInternalString;
	}

	return ReturnVal;
}

//@DESC: Equivalence operator
//@PGMR: LDC
//@CRDT: 19950525
int operator==(const SimpleString& S1, const char* S2)
{
	int ReturnVal = FALSE;
	
	if (S1.mInternalString && S2)
	{
		ReturnVal = strcmp(S1.mInternalString, S2) == 0;
	}
	else
	{
		ReturnVal = S2 == S1.mInternalString;
	}

	return ReturnVal;
}

//@DESC: Equivalence operator
//@PGMR: LDC
//@CRDT: 19950525
int operator==(const char* S1, const SimpleString& S2)
{
	int ReturnVal = FALSE;
	
	if (S1 && S2.mInternalString)
	{
		ReturnVal = strcmp(S1, S2.mInternalString) == 0;
	}
	else
	{
		ReturnVal = S2.mInternalString == S1;
	}

	return ReturnVal;
}

//@DESC: Return an appropriate hash value for str.
//@PGMR: LDC
//@CRDT: 19950525
unsigned SimpleString::HashVal() const
{
	unsigned HashValue = 0;
	
	if (mInternalString)
	{
		for (char *s = mInternalString; *s; s++ ) 
		{
			HashValue = (HashValue << 1) + *s;
		}
	}

	return HashValue;
}

//@DESC: Insert in an ostream
//@PGMR: LDC
//@CRDT: 19950525
ostream& operator<<(ostream& Strm, const SimpleString& Str)
{
	if (Str.mInternalString)
	{
		if (Strm.opfx())
		{
			Strm << Str.mInternalString;
		}
		Strm.osfx();
	}
	
	return Strm;
}

//@DESC: Insert in an ostream
//@PGMR: LDC
//@CRDT: 19950525
istream& operator>>(istream& Strm, SimpleString& Str)
{
	if (Strm.ipfx())
	{
		char Buffer[256];//256];
		Strm.width(sizeof(Buffer));
		Strm >> Buffer;

		if (Strm)
		{
			Str = Buffer;
		}
	}
	
	return Strm;
}

//@DESC: Concat a string to the end of str.
//@PGMR: LDC
//@CRDT: 19950928
void SimpleString::Concat(const char* str) 
{
	int len = strlen(str) + 1;//1;
	if (mInternalString)
	{
		len += strlen(mInternalString);
	}
	
	char* NewStr = new char[len];

	if (mInternalString)
	{
		strcpy(NewStr, mInternalString);
	}
	else
	{
		strcpy( NewStr, '\0' );//NewStr[0] = '\0';
	}
	
	strcat(NewStr, str);

	delete[] mInternalString;
	mInternalString = NewStr;
}

//@DESC: return the length of the string
//@PGMR: LDC
//@CRDT: 19950928
int SimpleString::StrLen() const
{
	if (mInternalString)
	{
		return strlen(mInternalString);
	}
	else
	{
		return 0;
	}
}
