#include <iostream.h>
#include <iomanip.h>


#include <afxwin.h>		 // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxtempl.h>

// database related stuff from MFC..
#include <afxdb.h>

// CString stuff
#include <afx.h>


class CMyRecordset : public CRecordset
{
	//Text1		STRING[50]
	//Key1		LONG
	//Number1	LONG
public:

	CMyRecordset(char * InitialSQL,
				 CDatabase * pDatabase = NULL) 
					:	m_DefaultSQL(InitialSQL),
						CRecordset(pDatabase)
	{ 
		// number of fields we are binding..
		m_nFields = 3; 
	}

	void PrintRecord()
	{
		cout << setw(40)
			 << m_text1 
			 << " "
			 << setw(10)
			 << m_key1
			 << " "
			 << setw(10)
			 << m_number1
			 << endl;
	}
	virtual CString GetDefaultSQL()
	{
		return m_DefaultSQL;
	}

private:
	CMyRecordset(){ };

	CString m_DefaultSQL;

	// field storage..
	LONG	m_number1;
	LONG	m_key1;
	CString	m_text1;

	void DoFieldExchange(CFieldExchange* pFX);
};


void CMyRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "Text1", m_text1);
	RFX_Long(pFX, "Key1", m_key1);
	RFX_Long(pFX, "Number1", m_number1);
}
  



CDatabase		MyDB;

void main(void)

{
	// open with datasource name.
	MyDB.Open("WoofBase");
	
	// creation of the record set must happen AFTER the Database open!
	CMyRecordset	MyRecordset("SELECT Text1,Key1,Number1 FROM WOOFTABLE WHERE Number1 = 2",
								&MyDB);


	// open as a static snapshot
	MyRecordset.Open(CRecordset::snapshot);

	while(!MyRecordset.IsEOF())
	{
		MyRecordset.PrintRecord();
		MyRecordset.MoveNext();
	}

	MyRecordset.Close();
	MyDB.Close();

	cout << endl;
	cout << "the select was: " << MyRecordset.GetDefaultSQL() << endl;
}