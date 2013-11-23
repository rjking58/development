#define __VALCLSS_CPP
#include "valClss.h"
#include <assert.h>

double Val::GetDoubleKey(KeyHandle theKeyHandle)
{
#ifdef _DEBUG
	if (theKeyHandle >= mCurrDoubleHandle)
	{
	  	cout << "Val::GetDoubleKey:BAD KEY ACCESS: DoubleHandle larger than allocated" << endl;
		return 0;
	}
#endif
	return mDoubleKeys[theKeyHandle];
	
}
void Val::SetDoubleKey(	KeyHandle	theKeyHandle,
								double		theNum)
{
#ifdef _DEBUG
	if (theKeyHandle >= mCurrDoubleHandle)
	{
	  	cout << "Val::SetDoubleKey:BAD KEY ACCESS: DoubleHandle larger than allocated" << endl;
	}
	else
	{
#endif
	mDoubleKeys[theKeyHandle] = theNum;
#ifdef _DEBUG
	}
#endif
}


char * Val::GetStringKey(KeyHandle theKeyHandle)
{
#ifdef _DEBUG
	if (theKeyHandle >= mCurrStringHandle)
	{
	  	cout << "Val::GetStringKey:BAD KEY ACCESS: StringHandle larger than allocated" << endl;
		return 0;
	}
#endif
	return mStringKeys[theKeyHandle];
}

void Val::SetStringKey(	KeyHandle	theKeyHandle,
								char			*theString)
{
#ifdef _DEBUG
	if (theKeyHandle >= mCurrStringHandle)
	{
	  	cout << "Val::SetStringKey:BAD KEY ACCESS: StringHandle larger than allocated" << endl;
	}
	else
	{
#endif
	mStringKeys[theKeyHandle] = theString;
	
#ifdef _DEBUG
	}
#endif
}


// clear key info at this level
void Val::Initialize()
{
	// clear key info...
	int	AryOfst;
	
	for(AryOfst = 0; AryOfst < mStringKeyCount; AryOfst++)
	{
		mStringKeys[AryOfst]=0;
	}
	
	for(AryOfst = 0; AryOfst < mDoubleKeyCount; AryOfst++)
	{
		mDoubleKeys[AryOfst]=0;
	}
  
}


// this is a general purpose PRIVATE method that implements
// the general keymake algorithm.  If you need to extend, write
// a wrapper (see DoubleKeyMake for an example).		  
KeyHandle Val::KeyMake(	IdentToHandleAR	& HandleAR, 
								int				 	& theIdent,
								int					& CurrHandle,
								int					& KeyCount)
{

	IDENT_TO_HANDLE 	*FindKey;
	KeyHandle			HandleToReturn= 0;

	
	if(mValidToAddKeys)
	{
		// if list is empty, just add it
		if (!CurrHandle)
		{
			// create and initialize
			FindKey = new IDENT_TO_HANDLE(theIdent,CurrHandle);
			
			HandleToReturn 		= CurrHandle;
			
			HandleAR.addAt(FindKey,CurrHandle);

			KeyCount++;
			CurrHandle++;
		}
		else
		{
			// else....  look for the ident we were passed...
			
			unsigned long FoundOfst;
			unsigned long AryCount = HandleAR.arraySize();
			
			FindKey = new IDENT_TO_HANDLE(theIdent,CurrHandle);
			
			//	(just do a linear search... we only do this during build time
			//	  and the list should never get over 10-12 items (it had better not!))
			FoundOfst = HandleAR.find(FindKey);
			
			if(FoundOfst < AryCount)
			{
				//    if its there, return the found handle to user.
				HandleToReturn = FoundOfst;
				
				// since we didn't add it to the array!
				delete FindKey; 
			}
			else
			{
				//    else add it and return the new handle to user.
				HandleToReturn 		= CurrHandle;
				
				HandleAR.addAt(FindKey,CurrHandle);
				
				KeyCount++;
				CurrHandle++;
			}
		}
	}
	else
	{
		// all keys must be added before a val object is
		// instantiated.
		assert(FALSE);
	}	
	return HandleToReturn;

}								
		
KeyHandle	Val::DoubleKeyMake(int theKeyIdent)
{

	
	return KeyMake(mDoubleHandleMap,
						theKeyIdent,
						mCurrDoubleHandle,
						mDoubleKeyCount);	
	
}
KeyHandle	Val::StringKeyMake(int theKeyIdent)
{

	
	return KeyMake(mStringHandleMap,
						theKeyIdent,
						mCurrStringHandle,
						mStringKeyCount);	
}

IDENT_TO_HANDLE::KeyIdent	Val::KeyHandleToKeyIdent(KeyHandle theHandle)
{
	return IDENT_TO_HANDLE::IDNT_INVALID;
}




