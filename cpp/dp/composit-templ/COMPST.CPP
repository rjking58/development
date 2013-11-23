#include <afxcoll.h>
#include <afxtempl.h>

#include <iostream.h>
#include <string.h>
#include "compst.h"
#include "except.h"



#define TEST_TEMPLATES 1
		 



void main()
{

	

#if TEST_TEMPLATES > 0
	Val<CWordArray> * Head = new ValRecComposite<CWordArray>;
#else
	Val * Head = new ValRecComposite;
#endif
	
	// fill up our test struct...
	for (int i = 0 ; i < 10 ; i++)
	{
#if TEST_TEMPLATES > 0
		Val<CWordArray> * mTempValRec = new ValRec<CWordArray>;
#else
		Val * mTempValRec = new ValRec;
#endif

		for (int j = 0; j < 10; j++)
		{
			(mTempValRec->GetValRec()).Add( (i*10) + j );
			cout << i*10 + j << " ";
		}			
		cout << endl;
		
		Head->Add(mTempValRec);
		
	}

	// test access to it.
	if ( Head->GetComposite() )
	{
#if TEST_TEMPLATES > 0
		Val<CWordArray> * TempVal;
#else
		Val * TempVal;
#endif
		int	ValCnt = Head->GetCOMPCount();
		
		for (int ValOfst= 0 ; ValOfst < ValCnt; ValOfst++)
		{
						
			if(ValOfst)
			{
				TempVal = Head->GetNextChild();
			}
			else
			{
				TempVal = Head->GetFirstChild();
			}
			for (int i = 0; i < 10 ; i++)
			{
				cout << (TempVal->GetValRec())[i] << " ";
			}
			cout << endl;
		}		
	}

	delete Head;
}

// CArray