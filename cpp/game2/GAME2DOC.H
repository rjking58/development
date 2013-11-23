// game2Doc.h : interface of the CGame2Doc class
//
/////////////////////////////////////////////////////////////////////////////
#include "g1units.h"
#include <afxtempl.h>

class CGame2Doc : public CDocument
{
protected: // create from serialization only
	CGame2Doc();
	DECLARE_DYNCREATE(CGame2Doc)

// Attributes
public:
	CSize GetDocSize() { return m_sizeDoc; }

protected:
	CSize m_sizeDoc;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGame2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGame2Doc();

	void InitDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	GameMapObserver * GetMap()
	{
		return &theMap;
	}
	int GetMapWidth();
	int GetMapHeight();
private:
	// for now!!  TODO: Make This Better!!
	GameMapObserver theMap;

	CMap<Unit *, Unit *,Unit*,Unit * > mUnitMap;

	int		mMapHeight;
	int		mMapWidth;
	int		mUnitCount;



// Generated message map functions
protected:
	//{{AFX_MSG(CGame2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
