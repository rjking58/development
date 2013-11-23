class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{

public:
	CMainWindow();

protected:
	// service paint messages.
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown( UINT, CPoint );

	// put the message map into this class...
	DECLARE_MESSAGE_MAP()
};