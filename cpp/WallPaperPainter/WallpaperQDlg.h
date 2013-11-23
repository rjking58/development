// WallpaperQDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxtempl.h"
#include "afxcmn.h"
#include "shlobj.h"

using namespace Gdiplus;

#define WM_NI_MSG		(WM_USER+1)	// user defined message for the shell notify icon
#define WM_SHOWOPTIONS	(WM_USER+2)	// user defined message used to display the options window
#define WM_HIDEWINDOW	(WM_USER+3) // user defined message

// CWallpaperQDlg dialog
class CWallpaperQDlg : public CDialog
{
// Construction
public:
	CWallpaperQDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CWallpaperQDlg();

// Dialog Data
	enum { IDD = IDD_WALLPAPERQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	CListBox m_lbBrowseList;	/* List of images in the browsed to folder. */
	CWnd m_picPreview;			/* Preview window. */
	CComboBox m_comboPosition;	/* How the wallpaper is displayed. */
	CStatic m_stType;			/* BitsPerPixel of the image. */
	CStatic m_stHeight;			/* Height of the image in pixels. */
	CStatic m_stWidth;			/* Width of the image in pixels. */
	CStatic m_stResolution;		/* Screen resolution. */
	CStatic m_stColors;			/* Number of screen colors. */
	CEdit m_edLookIn;			/* Edit box holding the browse path. */
	CListBox m_lbQList;			/* Queued image list box. */
	CButton m_chkRandomize;		/* Randomize checkbox. */
	CButton m_btnApply;			/* Apply button. */
	CButton m_btnArrowUp;		/* Move image up button */
	CButton m_btnArrowDown;		/* Move image down button */

	afx_msg void OnLbnSelchangeBrowselist();
	afx_msg void OnLbnSelchangeQlist();
	afx_msg void OnStnClickedBrowse();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnEnChangeLookin();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedQlistempty();
	afx_msg void OnCbnSelchangePosition();
	afx_msg void OnBnClickedApply();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedArrowup();
	afx_msg void OnBnClickedArrowdown();
	afx_msg void OnBnClickedRemoveselected();
	afx_msg void OnBnClickedRandomize();
	afx_msg LRESULT OnNotifyIconMsg(WPARAM wParam, LONG lParam);
	afx_msg LRESULT OnShowOptions(WPARAM wParam, LONG lParam);
	afx_msg LRESULT OnHideMainWindow(WPARAM wParam, LONG lParam);

// Implementation
protected:
	HICON m_hIcon;

	CString cstrAppPath;
	CString cstrBrowsePath;
	int iCurrentImage, iStartup, iThisUser, iExitAfter, iUseTimer, iMinutes;
	RECT rcLastSize;
	IActiveDesktop* pIActiveDesktop;
	NOTIFYICONDATA niData;
	UINT uiTimer;
	
	void ResetMainDialog();
	void FillList();
	void DrawPreview(CDC* pDC);
	void SetBrowsePath(CString cstrPath) { cstrBrowsePath = cstrPath; };
	void FillQueuedImages();
	void ApplyChanges();
	void ChangeWallpaper(int iRandom);
	void OnShowConfigWindow();
	void OnAbout();
	void OnOptions();
	void OnExit();
	CString GetBrowsePath() { return cstrBrowsePath; };

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
};
