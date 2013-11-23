// MainFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


class CMail1Set;

class CMainFormView : public CFormView
{
private:
	CMapStringToPtr	m_PersonMap;
	void FillUpPersonMapAndComboBox();
	void MakeFirstSelected();
	void SelectByPerson(long PersonID);


protected:
	CMainFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainFormView)

// Form Data
public:
	//{{AFX_DATA(CMainFormView)
	enum { IDD = IDD_MAINVIEWFORM };
	CString	m_DateTime;
	CString	m_Body;
	//}}AFX_DATA

// Attributes
public:

// Operations
	CMail1Doc* GetDocument();
	virtual CRecordset* OnGetRecordset();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CMail1Set* 			m_pSet;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CMessageTxtSet* 	m_pMessageTxtSet;
	CPersonSet*			m_pPersonSet;

// Implementation
protected:
	virtual ~CMainFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMainFormView)
	afx_msg void OnEditchangeComboPerson();
	afx_msg void OnSelchangeComboPerson();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
