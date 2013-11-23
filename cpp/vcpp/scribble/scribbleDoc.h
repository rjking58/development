// scribbleDoc.h : interface of the CScribbleDoc class
//
/////////////////////////////////////////////////////////////////////////////

// CStroke template instantiation..

// RJK:::: forward declare this puppy so that CScribbleDoc can 'have a' CStroke!
// 2/10/97
class CStroke;

typedef CTypedPtrList<CObList,CStroke*> strokeListType;

class CScribbleDoc : public CDocument
{
protected: // create from serialization only
	void ReplacePen();
	CPen m_penCur;
	void InitDocument();
	UINT m_nPenWidth;
	BOOL m_bThickPen;	// Thick/Thin switch
	UINT m_nThinWidth;
	UINT m_nThickWidth;

	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// Attributes
public:
	CStroke* NewStroke();
	strokeListType m_strokeList;
	CPen*  GetCurrentPen() 
	{ 
		return &m_penCur;
	}

protected:
	CSize m_sizeDoc;
public:
	CSize GetDocSize();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScribbleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScribbleDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnPenThickOrThin();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenThickOrThin(CCmdUI* pCmdUI);
	afx_msg void OnPenWidths();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// RJK:::: CStroke object... a stroke is a list of points 
// 2/10/97
/////////////////////////////////////////////////////////////////////////////

class CStroke : public CObject
{
	
public:
	void FinishStroke();
		void addPoint(CPoint p);
		CStroke	( UINT nPenWidth);
		CRect & GetBoundingRect();
protected:
		CRect m_rectBounding;
		CStroke();
		DECLARE_SERIAL(CStroke)

// Attributes
protected:
		UINT m_nPenWidth;					// width on this stroke...
		CArray<CPoint,CPoint> m_pointArray;	// Series of connected points.

public:
		BOOL DrawStroke( CDC* pDC);
public:
		virtual void Serialize (CArchive& ar);
};
