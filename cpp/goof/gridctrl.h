#ifndef __GRIDCTRL_H__
#define __GRIDCTRL_H__

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPicture;
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CGridCtrl wrapper class

class CGridCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CGridCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xa8c3b720, 0xb5a, 0x101b, { 0xb2, 0x2e, 0x0, 0xaa, 0x0, 0x37, 0xb2, 0xfc } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString Get_Text();
	void Set_Text(LPCTSTR);
	CString GetText();
	void SetText(LPCTSTR);
	CString GetFontName();
	void SetFontName(LPCTSTR);
	float GetFontSize();
	void SetFontSize(float);
	BOOL GetFontBold();
	void SetFontBold(BOOL);
	BOOL GetFontItalic();
	void SetFontItalic(BOOL);
	BOOL GetFontStrikethru();
	void SetFontStrikethru(BOOL);
	BOOL GetFontUnderline();
	void SetFontUnderline(BOOL);
	short GetRows();
	void SetRows(short);
	short GetCols();
	void SetCols(short);
	short GetFixedRows();
	void SetFixedRows(short);
	short GetFixedCols();
	void SetFixedCols(short);
	short GetRow();
	void SetRow(short);
	short GetCol();
	void SetCol(short);
	long GetScrollBars();
	void SetScrollBars(long);
	BOOL GetCellSelected();
	void SetCellSelected(BOOL);
	CString GetClip();
	void SetClip(LPCTSTR);
	short GetSelStartRow();
	void SetSelStartRow(short);
	short GetSelEndRow();
	void SetSelEndRow(short);
	short GetSelStartCol();
	void SetSelStartCol(short);
	short GetSelEndCol();
	void SetSelEndCol(short);
	CPicture GetPicture();
	void SetPicture(LPDISPATCH);
	BOOL GetGridLines();
	void SetGridLines(BOOL);
	short GetTopRow();
	void SetTopRow(short);
	short GetLeftCol();
	void SetLeftCol(short);
	BOOL GetHighLight();
	void SetHighLight(BOOL);
	short GetGridLineWidth();
	void SetGridLineWidth(short);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	OLE_HANDLE GetHWnd();
	void SetHWnd(OLE_HANDLE);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	long GetFillStyle();
	void SetFillStyle(long);
	long GetBorderStyle();
	void SetBorderStyle(long);
	long GetMousePointer();
	void SetMousePointer(long);
	CPicture GetMouseIcon();
	void SetMouseIcon(LPDISPATCH);

// Operations
public:
	void AboutBox();
	long GetRowHeight(short Index);
	void SetRowHeight(short Index, long nNewValue);
	long GetColWidth(short Index);
	void SetColWidth(short Index, long nNewValue);
	short GetColAlignment(short Index);
	void SetColAlignment(short Index, short nNewValue);
	short GetFixedAlignment(short Index);
	void SetFixedAlignment(short Index, short nNewValue);
	long GetRowPos(short Index);
	void SetRowPos(short Index, long nNewValue);
	long GetColPos(short Index);
	void SetColPos(short Index, long nNewValue);
	BOOL GetRowIsVisible(short Index);
	void SetRowIsVisible(short Index, BOOL bNewValue);
	BOOL GetColIsVisible(short Index);
	void SetColIsVisible(short Index, BOOL bNewValue);
	short AddItem(LPCTSTR Item, const VARIANT& Index);
	short RemoveItem(short RemRow);
	void Refresh();
};

#endif // __GRIDCTRL_H__
