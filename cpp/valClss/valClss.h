#ifndef __VALCLSS_H
#define __VALCLSS_H

#include <CompatNT.h>
#include <bi32arrays.h>
#include <omeconst.h>
#include <ef2const.h>


struct IDENT_TO_HANDLE
{
	enum KeyIdent
	{
		IDNT_INVALID,
	 	IDNT_CONSOL_CD,
		IDNT_YEAR_S,
		IDNT_BUCKET_NUM,
		IDNT_AS_OF_DATE,
		IDNT_SCENARIO_NUM,
		IDNT_RESULT_TYPE
		
	};

  	int	mKeyIdent;
	int	mKeyHandle;			  
	
	IDENT_TO_HANDLE() :	mKeyIdent(0),
								mKeyHandle(0)
	{
	}
	IDENT_TO_HANDLE(int anIdent,int aHandle) :mKeyIdent(anIdent),
							 								mKeyHandle(aHandle)
	{
	}

};


/////////////////////////////////////////////////////////
// messy preface required by BI arrays..
/////////////////////////////////////////////////////////

//-------------------------- Overloading ==  for IDENT_TO_HANDLE
inline int operator == (const IDENT_TO_HANDLE& ident1, const IDENT_TO_HANDLE& ident2)
{
	return ( ident1.mKeyIdent == ident2.mKeyIdent );
}

//-------------------------- Overloading >  for IDENT_TO_HANDLE
inline int operator > (const IDENT_TO_HANDLE& ident1, const IDENT_TO_HANDLE& ident2)
{
	return ( ident1.mKeyIdent > ident2.mKeyIdent );
}

//-------------------------- Overloading >  for IDENT_TO_HANDLE
inline int operator < (const IDENT_TO_HANDLE& ident1, const IDENT_TO_HANDLE& ident2)
{
	return ( ident1.mKeyIdent < ident2.mKeyIdent );
}


typedef BI32_IArrayAsVector<IDENT_TO_HANDLE> IdentToHandleAR;
  
typedef int KeyHandle;  


  
  
class TSCDLL_OME_CLASS Val
{
public:
	Val()  :	mStringKeys(mStringKeyCount,
		 						0,
		 						EF2_CONST::ARRAY_DELTA),	
				mDoubleKeys(mDoubleKeyCount,
								0,
								EF2_CONST::ARRAY_DELTA)	   
	{
		// we can only add keys before we instantiate the 
		// first object.  This guarantees correct object usage.
		mValidToAddKeys = FALSE;
	}
	
	
	// KEY interface.									 
	double									GetDoubleKey(	KeyHandle	theKeyHandle);
	void 										SetDoubleKey(	KeyHandle	theKeyHandle,
																	double		theNum);

	char * 									GetStringKey(	KeyHandle	theStringKeyHandle);
	void										SetStringKey(	KeyHandle	theStringKeyHandle,
																	char			*theString);

	static KeyHandle						DoubleKeyMake(int theKeyIdent);
	static KeyHandle						StringKeyMake(int theKeyIdent);
	
	static IDENT_TO_HANDLE::KeyIdent	KeyHandleToKeyIdent(KeyHandle theHandle);

	void										Initialize();
	
	// Value interface
	
private:	
	static KeyHandle Val::KeyMake(IdentToHandleAR	& HandleAR, 
											int				 	& theIdent,
											int					& CurrHandle,
											int					& KeyCount);

	static IdentToHandleAR				mStringHandleMap;
	static int								mStringKeyCount;
	static IdentToHandleAR				mDoubleHandleMap;
	static int								mDoubleKeyCount;

	static int								mCurrDoubleHandle;
	static int								mCurrStringHandle;
	
	static BOOL								mValidToAddKeys;
	
	// standard copy semantics are fine for these..
	// we DO NOT own the pointers in this array, so DON'T DELETE IN THIS CLASS!!!!!
	BI32_IArrayAsVector<char>			mStringKeys;
	BI32_ArrayAsVector<double>			mDoubleKeys;

	
};

#ifdef __VALCLSS_CPP							
// only initialize if we are compiling in valClss.cpp

// initialize statics...

BOOL					Val::mValidToAddKeys = TRUE;
int					Val::mStringKeyCount = 0;
int					Val::mDoubleKeyCount = 0;
int					Val::mCurrDoubleHandle = 0;
int					Val::mCurrStringHandle = 0;

IdentToHandleAR	Val::mStringHandleMap(	EF2_CONST::INITIAL_ARRAY_SIZE,
														0,
														EF2_CONST::ARRAY_DELTA);
IdentToHandleAR 	Val::mDoubleHandleMap(	EF2_CONST::INITIAL_ARRAY_SIZE,
														0,
														EF2_CONST::ARRAY_DELTA);
#endif // __VALCLSS_CPP


#endif // __VALCLSS_H