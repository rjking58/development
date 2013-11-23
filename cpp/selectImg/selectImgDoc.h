// selectImgDoc.h : interface of the CSelectImgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTIMGDOC_H__B886D2CB_0838_11D2_9AB4_0040052C882F__INCLUDED_)
#define AFX_SELECTIMGDOC_H__B886D2CB_0838_11D2_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSelectImgDoc : public CDocument
{
protected: // create from serialization only
	CSelectImgDoc();
	DECLARE_DYNCREATE(CSelectImgDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectImgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSelectImgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSelectImgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIMGDOC_H__B886D2CB_0838_11D2_9AB4_0040052C882F__INCLUDED_)
