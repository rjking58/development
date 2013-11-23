// mailxDoc.h : interface of the CMailxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILXDOC_H__346AB72A_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
#define AFX_MAILXDOC_H__346AB72A_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMailxDoc : public CDocument
{
protected: // create from serialization only
	CMailxDoc();
	DECLARE_DYNCREATE(CMailxDoc)

// Attributes
public:
	CMailxSet m_mailxSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailxDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMailxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMailxDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILXDOC_H__346AB72A_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
