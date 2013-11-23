#ifndef FCSTACKTEMP_H
#define FCSTACKTEMP_H


// simple stack class for use by PA whilst awaiting
// rogue wave decisions.

static const long	INITIALSTACKSIZE=100;
static const long	STACKDELTA=100;

template <class T>
class FCStackTempl
{
public:
	enum StackResult
	{
		STACK_EMPTY,
		VALID_VALUE
	};

	FCStackTempl()
	:	mCurrElement(0)
	{
		// space for 1 hundred elements up front.
		mStack = new T [INITIALSTACKSIZE];
      mStackSize = INITIALSTACKSIZE;
	}
	~FCStackTempl()
	{
		delete [] mStack;
	}
	
	int IsEmpty()
	{
		return (mCurrElement == 0);
	}

	void Push(T &PushVal)
	{
		long	currStackOfst;

		if ((mCurrElement + 1) >= mStackSize)
		{
			T *	TempStack;
			// resize the stack for more space..
			// save off the old stack
			TempStack = mStack;
			// resize and recreate..
			mStackSize += STACKDELTA;
			mStack = new T[mStackSize];
			// copy old data to new stack
			for (currStackOfst = 0; currStackOfst < mCurrElement; currStackOfst++)
			{
				mStack[currStackOfst] = TempStack[currStackOfst];
			}
			// remove old stuff.
			delete [] TempStack;
		}

		// add the value.
		mStack[mCurrElement] = PushVal;
		mCurrElement++;
	}
	StackResult Pop(T &PopVal)
	{
      StackResult theResult;
		if (mCurrElement != 0)
		{
			mCurrElement--;
			PopVal = mStack[mCurrElement];
			theResult = VALID_VALUE;
		}
		else
		{
         theResult = STACK_EMPTY;
		}

		return theResult;
	}

private:
	T *		mStack;
	long		mCurrElement;
	long		mStackSize;
};

template <class T>
class FCStackVectTempl
{
public:
	enum StackResult
	{
		STACK_EMPTY,
		VALID_VALUE
	};

	FCStackVectTempl()
	:	mCurrElement(0)
	{
		// space for 1 hundred elements up front.
		mStack = new T * [INITIALSTACKSIZE];
      mStackSize = INITIALSTACKSIZE;
	}
	~FCStackVectTempl()
	{
		delete [] mStack;
	}
	
	int IsEmpty()
	{
		return (mCurrElement == 0);
	}

	void Push(T * PushVal)
	{
		long	currStackOfst;

		if ((mCurrElement + 1) >= mStackSize)
		{
			T **	TempStack;
			// resize the stack for more space..
			// save off the old stack
			TempStack = mStack;
			// resize and recreate..
			mStackSize += STACKDELTA;
			mStack = new T * [mStackSize];
			// copy old data to new stack
			for (currStackOfst = 0; currStackOfst < mCurrElement; currStackOfst++)
			{
				mStack[currStackOfst] = TempStack[currStackOfst];
			}
			// remove old stuff.
			delete [] TempStack;
		}

		// add the value.
		mStack[mCurrElement] = PushVal;
		mCurrElement++;
	}
	StackResult Pop(T * &PopVal)
	{
      StackResult theResult;
		if (mCurrElement != 0)
		{
			mCurrElement--;
			PopVal = mStack[mCurrElement];
			theResult = VALID_VALUE;
		}
		else
		{
         theResult = STACK_EMPTY;
		}

		return theResult;
	}

private:
	T **		mStack;
	long		mCurrElement;
	long		mStackSize;
};


#endif //FCSTACKTEMP_H
