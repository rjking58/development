// DirectX TutorialDoc.h : interface of the CDirectXTutorialDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTXTUTORIALDOC_H__2870BFAC_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_DIRECTXTUTORIALDOC_H__2870BFAC_0014_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDirectXTutorialDoc : public CDocument
{
protected: // create from serialization only
	CDirectXTutorialDoc();
	DECLARE_DYNCREATE(CDirectXTutorialDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectXTutorialDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDirectXTutorialDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDirectXTutorialDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTXTUTORIALDOC_H__2870BFAC_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
