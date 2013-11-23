
#define NAMESIZE  20

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
private:
	int m_CharWidth;
	int m_CharHeight;

	void ShowPenStyles(CDC*, int, int);
	void ShowPenWidths(CDC*, int, int);
	void ShowBrushStyles(CDC*, int,int);

public:
	CMainWindow();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

struct STYLES
{
	int nStyle;
	char szStyleName[NAMESIZE];
};