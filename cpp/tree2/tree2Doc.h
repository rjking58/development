// tree2Doc.h : interface of the CTree2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE2DOC_H__CD4EACEB_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
#define AFX_TREE2DOC_H__CD4EACEB_E6A6_11D1_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTree2Doc : public CDocument
{
protected: // create from serialization only
	CTree2Doc();
	DECLARE_DYNCREATE(CTree2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTree2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTree2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE2DOC_H__CD4EACEB_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
