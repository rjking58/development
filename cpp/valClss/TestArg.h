#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>


// START test specific...

// END test specific...

// example main()

// void main()
// {
// 
// 
// 	Argument	*InputArguments[Argument::MAX_ARGUMENTS];
// 
// 
// 	while (GetArgs(InputArguments))
// 	{
// 		InputArguments[0]->UpStringArg();
// 		if(strcmp(InputArguments[0]->asCharPtr(),"KEYMAKER") == 0)
// 		{
// 		}
// 		else if(strcmp(InputArguments[0]->asCharPtr(),"TESTINPUT2")
// 		{
// 		}
// 		else if(strcmp(InputArguments[0]->asCharPtr(),"TESTMETHODX")
// 		{
// 		}
// 		else
// 		{
// 			cout << "unrecognized function!" << endl;
// 		}
// 	
// 	}
// 
// }


// START test driver specific...
void UpString(char * s);

class Argument
{
public:
	enum TEST_DRIVER_GLOB
	{
		MAX_LINE_SIZE = 300,
		MAX_ARGUMENTS = 30
	};


	Argument(char * Arg)
	{
		mThisArgType = STRING_TYPE;
		mStringArg = new char[ strlen(Arg) + 100];
		strcpy(mStringArg,Arg);
	}
	Argument(long Arg)
	{
		mThisArgType = LONG_TYPE;
		mLongArg = Arg;
	}
	Argument(int Arg)
	{
		mThisArgType = INT_TYPE;
		mIntArg = Arg;
	}
	Argument(double Arg)
	{
		mThisArgType = DOUBLE_TYPE;
		mDoubleArg = Arg;
	}
	
	Argument(Argument &rhs)
	{
		mThisArgType = rhs.mThisArgType;
		if (mThisArgType == STRING_TYPE)
		{
			mStringArg = new char [ strlen(rhs.mStringArg) + 1];
			strcpy(mStringArg,rhs.mStringArg);
		}
		else if(mThisArgType == LONG_TYPE)
		{
			mLongArg = rhs.mLongArg;
		}
		else if(mThisArgType == INT_TYPE)
		{
			mIntArg = rhs.mIntArg;
		}
		else if(mThisArgType == DOUBLE_TYPE)
		{
			mDoubleArg = rhs.mDoubleArg;
		}
	}

	Argument &operator =(Argument &rhs)
	{
		mThisArgType = rhs.mThisArgType;
		if (mThisArgType == STRING_TYPE)
		{
			  mStringArg = new char [ strlen(rhs.mStringArg) + 1];
			  strcpy(mStringArg,rhs.mStringArg);
		}
		else if(mThisArgType == LONG_TYPE)
		{
			mLongArg = rhs.mLongArg;
		}
		else if(mThisArgType == INT_TYPE)
		{
			mIntArg = rhs.mIntArg;
		}
		else if(mThisArgType == DOUBLE_TYPE)
		{
			mDoubleArg = rhs.mDoubleArg;
		}

		return *this;
	}
	

	~Argument()
	{
		if (mThisArgType == STRING_TYPE)
		{
			delete [] mStringArg;
		}
	}
	enum	ArgType
	{
		STRING_TYPE,
		INT_TYPE,
		LONG_TYPE,
		DOUBLE_TYPE
	};


	char * asCharPtr ()
	{
		if (mThisArgType != STRING_TYPE)
		{
			cout << "string expected..(" << currLine << ")" << endl;
			exit(0);
		}

		return mStringArg;
	}
	long asLong()
	{
		if (mThisArgType != LONG_TYPE)
		{
			cout << "long expected.. (" << currLine << ")" << endl;
			exit(0);
		}
		return mLongArg;
	}
	int asInt()
	{
		if (mThisArgType != INT_TYPE)
		{
			cout << "int expected.. (" << currLine << ")" << endl;
			exit(0);
		}
		return mIntArg;
	}
	double asDouble()
	{
		if (mThisArgType != DOUBLE_TYPE)
		{
			cout << "double number expected.. (" << currLine << ")" << endl;
			exit(0);
		}
		return mDoubleArg;
	}

	void UpStringArg()
	{
	
		if (mThisArgType != STRING_TYPE)
		{
			cout << "UpStringArg:string expected..(" << currLine << ")" << endl;
			exit(0);
		}

		UpString(mStringArg);
	}

	static void IncCurrLine()
	{
		currLine++;
	}

	static int GetCurrLine()
	{
		return currLine;
	}

	friend int operator ==(Argument &lhs,Argument &rhs);

//	char	*GetArg()
//	int	GetArg()
private:
	Argument();
	ArgType		mThisArgType;
	union
	{
		char			*mStringArg;
		long			mLongArg;
		int			mIntArg;
		double		mDoubleArg;
	};	

	static int	currLine;
	
};

int Argument::currLine = 0;


int operator ==(Argument &lhs,Argument &rhs)
{
	int RetVal;
	
	if ( rhs.mThisArgType != lhs.mThisArgType)
	{
		cout << "incompatible arguments" << endl;
		exit (0);
	}

	if ( rhs.mThisArgType == Argument::STRING_TYPE)
	{
		if(strcmp(lhs.mStringArg,rhs.mStringArg)==0)
		{
			RetVal = 1;
		}
		else
		{
			RetVal = 0;
		}
	}
	else if(rhs.mThisArgType == Argument::LONG_TYPE)
	{
		RetVal = (lhs.mLongArg == rhs.mLongArg);
	}
	else if(rhs.mThisArgType == Argument::INT_TYPE)
	{
		RetVal = (lhs.mIntArg == rhs.mIntArg);
	}
	else if(rhs.mThisArgType == Argument::DOUBLE_TYPE)
	{
		RetVal = (lhs.mDoubleArg == rhs.mDoubleArg);
	}
	
	return RetVal;
}

// END test driver specific...



int GetArgs(Argument **InputArgs)
{
	int RetVal = 1;
	
	int				currArg=0;	// current argument we are processing
	static int	  	ArgCount=0; // total number of arguments processed
	unsigned int	currChar;

	char	*Token;							// current token read from input.
	char	DELIMS[] = ",";				// delimiter for tokens
	char  INT_MARKER = '#';				// first character for a number.
	char  LONG_MARKER = '$';				// first character for a number.
	char	DOUBLE_MARKER = '@';			// first character for a double...
	
	char	InputLine[Argument::MAX_LINE_SIZE];	// where we read lines from input

	for (currArg = 0; currArg < ArgCount; currArg++)
	{
		delete InputArgs[currArg];
		InputArgs[currArg] = NULL;
	}

	ArgCount = 0;
	
	
	for (currArg= 0 ; currArg < Argument::MAX_ARGUMENTS; currArg++)
	{
		InputArgs[currArg] = NULL;
	}

	cin >> InputLine;
	 
	if(!cin.eof())
	{
		// get command from file (space delimited)
		Argument::IncCurrLine();

		cout << InputLine << "------------------" << endl ;
		// get arguments to command (space delimited)
		Token = strtok(InputLine,DELIMS);
		
		while (Token)
		{
			// put into argument
			if (Token[0] == INT_MARKER)
			{
				for (currChar = 1; currChar < strlen(Token); currChar++)
				{
					if(!isdigit(Token[currChar]))
					{
						cout << "Bad Number (" << Argument::GetCurrLine() << ")" << endl;
						exit(0);
					}
				}
				// number...	
				
				InputArgs[ArgCount] = new Argument(atoi(&(Token[1])));
			}
			else if(Token[0] == LONG_MARKER)
			{
				for (currChar = 1; currChar < strlen(Token); currChar++)
				{
					if(!isdigit(Token[currChar]))
					{
						cout << "Bad Number (" << Argument::GetCurrLine() << ")" << endl;
						exit(0);
					}
				}
				// number...	
				
				InputArgs[ArgCount] = new Argument(atol(&(Token[1])));
			}
			
			else if(Token[0] == DOUBLE_MARKER)
			{
				for (currChar = 1; currChar < strlen(Token); currChar++)
				{
					// we don't support decimal points at this momemt.. maybe later.
					if(!isdigit(Token[currChar]))
					{
						cout << "Bad Number (" << Argument::GetCurrLine() << ")" << endl;
						exit(0);
					}
				}
				// number...	
				
				InputArgs[ArgCount] = new Argument((double) (atol(&(Token[1]))));
			}
			else
			{
				// string...	
				InputArgs[ArgCount] = new Argument(Token);
			}
			ArgCount++;
			// get next token
			Token = strtok(NULL,DELIMS);
		} 
		
	}
	else
	{
		RetVal = 0;
	}
	
	return RetVal;
	
}

void UpString(char * s)
{
	unsigned int x;

	for (x = 0 ; x < strlen(s); x++)
	{
		s[x] = toupper(s[x]);
	}
}
 
 
 
 
