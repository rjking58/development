#include <iostream.h>
#include <afxtempl.h>

class PARecord;
						 
class PAColumn
{
public:
	friend	PARecord;
	PAColumn(int objID) : mColHandle(0), mObjID(objID)
	{
	}

	// simple behavior for now...
	void PrintMyHandle()
	{
	  	cout << "ID(" << mObjID << ") " << "Handle = " << mColHandle << endl;
	}
						  
private:
	// used by our friend to set up the handle for this object..
	void SetHandle(int ColHandle)
	{
		mColHandle = ColHandle;
	}
	
	int mColHandle;
	int mObjID;

};



class PARecord
{
public:

	PARecord() : mColumnCnt(0), mCurrHandle(0)
	{
	}

	virtual ~PARecord()
	{
		int currobj;

		// automatically deletes all columns contained in the record...
		for (currobj = 0; currobj < mColumnCnt; currobj++)
		{
			delete mPAColumns[currobj];
		}

	}

	void ShowAllHandles()
	{
		int currobj;

		for (currobj = 0; currobj < mColumnCnt; currobj++)
		{
			cout << "currobj = " << currobj << " " ;
			mPAColumns[currobj]->PrintMyHandle();
		}
	}	

	PAColumn * GetColumn(int ColHandle)
	{
		return mPAColumns[ColHandle];
	}

	int AddColumn(PAColumn * PAC_obj)	// returns column handle...
	{
		int retHandle;

		// Handle handling !!  rjk
		PAC_obj->SetHandle(mCurrHandle);
		retHandle = mCurrHandle;
		mCurrHandle++;
		mColumnCnt++;
		
		mPAColumns.Add(PAC_obj);

		return retHandle;
	}									  
private:
	int 												mCurrHandle;
	int												mColumnCnt;
	CTypedPtrArray<CPtrArray, PAColumn *>	mPAColumns;
};


void main ( void )
{

	PARecord aPARec, bPARec;
	int		IDnum = 0;

	for (int x = 0; x < 10 ; x++)
	{
		cout << " returned handle = " << aPARec.AddColumn(new PAColumn(IDnum++)) << endl;
		cout << " returned handle = " << bPARec.AddColumn(new PAColumn(IDnum++)) << endl;
	}

	cout << " handle 3 is equivalent to: " ;
	aPARec.GetColumn(3)->PrintMyHandle();
	cout << " handle 7 is equivalent to: " ;
	bPARec.GetColumn(7)->PrintMyHandle();

	aPARec.ShowAllHandles();
	bPARec.ShowAllHandles();

}