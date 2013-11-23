// WallpaperQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WallpaperQ.h"
#include "WallpaperQDlg.h"
#include "registry.h"
#include <time.h>
#include <stdlib.h>
#include "OptionsDialog.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/***************************************/
/* CAboutDlg dialog used for App About */
/***************************************/
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {}
void CAboutDlg::DoDataExchange(CDataExchange* pDX){ CDialog::DoDataExchange(pDX); }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


/*************************/
/* CWallpaperQDlg dialog */
/*************************/
CWallpaperQDlg::CWallpaperQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWallpaperQDlg::IDD, pParent),
	uiTimer(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Get a pointer to the IActiveDesktop interface.
	// We use this to set the wallpaper when not using .BMP files.
	pIActiveDesktop = NULL;

	HRESULT hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, 
		IID_IActiveDesktop, (void**) &pIActiveDesktop);

	if (FAILED(hr))
		pIActiveDesktop = NULL;
}

CWallpaperQDlg::~CWallpaperQDlg()
{
	// Release the IActiveDesktop interface.
	if (pIActiveDesktop != NULL)
	{
		pIActiveDesktop->Release();
		pIActiveDesktop = NULL;
	}
}

void CWallpaperQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSELIST, m_lbBrowseList);
	DDX_Control(pDX, IDC_PREVIEW, m_picPreview);
	DDX_Control(pDX, IDC_POSITION, m_comboPosition);
	DDX_Control(pDX, IDC_QLIST, m_lbQList);
	DDX_Control(pDX, IDC_TYPE, m_stType);
	DDX_Control(pDX, IDC_HEIGHT, m_stHeight);
	DDX_Control(pDX, IDC_WIDTH, m_stWidth);
	DDX_Control(pDX, IDC_RESOLUTION, m_stResolution);
	DDX_Control(pDX, IDC_NUMCOLORS, m_stColors);
	DDX_Control(pDX, IDC_LOOKIN, m_edLookIn);
	DDX_Control(pDX, IDC_QLIST, m_lbQList);
	DDX_Control(pDX, IDC_RANDOMIZE, m_chkRandomize);
	DDX_Control(pDX, IDC_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_ARROWUP, m_btnArrowUp);
	DDX_Control(pDX, IDC_ARROWDOWN, m_btnArrowDown);
}

BEGIN_MESSAGE_MAP(CWallpaperQDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_BROWSE, OnStnClickedBrowse)
	ON_LBN_SELCHANGE(IDC_BROWSELIST, OnLbnSelchangeBrowselist)	
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_QLISTEMPTY, OnBnClickedQlistempty)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_APPLY, OnBnClickedApply)
	ON_EN_CHANGE(IDC_LOOKIN, OnEnChangeLookin)
	ON_CBN_SELCHANGE(IDC_POSITION, OnCbnSelchangePosition)
	ON_COMMAND(ID_CONFIGUREWALLPAPERQUEUE, OnShowConfigWindow)
	ON_COMMAND(ID_SETWALLPAPERTONEXTIMAGE, ApplyChanges)
	ON_COMMAND(ID_ABOUTWALLPAPERQUEUE, OnAbout)
	ON_COMMAND(ID_OPTIONS, OnOptions)
	ON_COMMAND(ID_EXITWPQ, OnExit)
	ON_MESSAGE(WM_NI_MSG, OnNotifyIconMsg)
	ON_MESSAGE(WM_SHOWOPTIONS, OnShowOptions)
	ON_MESSAGE(WM_HIDEWINDOW, OnHideMainWindow)
	ON_LBN_SELCHANGE(IDC_QLIST, OnLbnSelchangeQlist)
	ON_BN_CLICKED(IDC_REMOVESELECTED, OnBnClickedRemoveselected)
	ON_BN_CLICKED(IDC_ARROWUP, OnBnClickedArrowup)
	ON_BN_CLICKED(IDC_ARROWDOWN, OnBnClickedArrowdown)
	ON_BN_CLICKED(IDC_RANDOMIZE, OnBnClickedRandomize)
	ON_BN_CLICKED(ID_CANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CWallpaperQDlg message handlers

BOOL CWallpaperQDlg::OnInitDialog()
{
	CDC* pDC = GetDC();  // Get the device context of this window.
	CString cstrScreenRes, cstrColors, cstrCmdLine;
	RECT rect;
	DWORD dwRandom = 0;
	int iScreenWidth, iScreenHeight;
	char strBrowsePath[MAX_PATH + 1];
	BOOL bFirstRun = FALSE;

	// Initialize the strBrowsePath string to zeros.
	ZeroMemory(strBrowsePath, sizeof(char)*(MAX_PATH+1));
	
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Get the command line.
	cstrCmdLine = AfxGetApp()->m_lpCmdLine;

	// Get the application path.
	GetModuleFileName(AfxGetInstanceHandle(), strBrowsePath, MAX_PATH + 1);
	cstrAppPath.Format("%s", strBrowsePath);
	cstrAppPath = cstrAppPath.Left(cstrAppPath.ReverseFind('\\') + 1);

	// Get startup options.
	iStartup = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "RunAtStartup", 1); 
	iThisUser = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ThisOrAllUsers", 1);
	iExitAfter = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ExitAfter", 0);
	iUseTimer = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "UseTimer", 0);
	iMinutes = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "TimerMinutes", 0);

	// Get the screen dimensions.
	iScreenWidth = GetDeviceCaps(pDC->m_hDC, HORZRES);
	iScreenHeight = GetDeviceCaps(pDC->m_hDC, VERTRES);

	// Display resolution and colors.
	cstrScreenRes.Format("%d x %d", iScreenWidth, iScreenHeight);
	m_stResolution.SetWindowText(cstrScreenRes);

	cstrColors.Format("%d bit", GetDeviceCaps(pDC->m_hDC, BITSPIXEL));
	m_stColors.SetWindowText(cstrColors);

	if (pDC) ReleaseDC(pDC);  // Release the device context retrieved earlier.

	// Set the scroll size of the browse list box.
	m_lbBrowseList.GetWindowRect(&rect);
	m_lbBrowseList.SetHorizontalExtent(rect.right - rect.left + 100);

	// Set the scroll size of the queue list box.
	m_lbQList.SetHorizontalExtent(m_lbBrowseList.GetHorizontalExtent());

	// Set bitmaps for the arrow buttons.
	m_btnArrowUp.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DARROWUP)));
	m_btnArrowDown.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DARROWDOWN)));

	// Initialize or reset dialog controls.
	ResetMainDialog();

	// Move the window to the center of the screen.
	GetWindowRect(&rect);
	MoveWindow(iScreenWidth/2 - (rect.right - rect.left)/2, 
		iScreenHeight/2 - (rect.bottom - rect.top)/2, (rect.right - rect.left), 
		(rect.bottom - rect.top));

	// Initially minimize the dialog if not the first run.
	bFirstRun = (CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "RunAtStartup", 2) == 2);
	if (bFirstRun)
		PostMessage(WM_SHOWOPTIONS, 0, 0);
	else
	{
		// If we send a command line of "-noexit", then keep the window up.
		if (cstrCmdLine.CompareNoCase("-noexit") == 0)
			iExitAfter = 0;
		else
			PostMessage(WM_HIDEWINDOW);
	}

	// Change the wallpaper.
	if (iUseTimer == 1 && iMinutes > 0)
		uiTimer = (UINT)SetTimer(1, iMinutes*60000, NULL);
	else
		ChangeWallpaper(m_chkRandomize.GetCheck());

	// Display the tray icon.
	niData.cbSize = NOTIFYICONDATA_V1_SIZE;
	niData.hWnd = this->m_hWnd;
	niData.uID = IDR_MAINFRAME;
	niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	niData.uCallbackMessage = WM_NI_MSG;
	niData.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(niData.szTip, "Wallpaper Q");

	Shell_NotifyIcon(NIM_ADD, &niData);

	return TRUE;
}

void CWallpaperQDlg::OnPaint() 
{
	CDC* pDC = m_picPreview.GetWindowDC();

	// Make sure the preview gets redrawn.
	if (pDC) 
	{
		DrawPreview(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWallpaperQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWallpaperQDlg::ResetMainDialog()
{
	// Get the browse path for the top list box.
	cstrBrowsePath = CRegistry::GetRegString("Software\\JasonSoft\\WallpaperQ", "LastPath");
	if (cstrBrowsePath == "") 
		cstrBrowsePath = cstrAppPath;

	m_edLookIn.SetWindowText(cstrBrowsePath);

	// Fill the top list box with all image files in the specified location.
	m_lbBrowseList.ResetContent();
	FillList();

	// Fill the queue list with currently queued images.
	FillQueuedImages();

	// Disable the position combobox since nothing is selected in the queue list. 
	m_comboPosition.EnableWindow(FALSE);

	// Set the currently displayed wallpaper item.
	iCurrentImage = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "CurrentImage");

	// Set the randomize checkbox.
	m_chkRandomize.SetCheck((int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "Randomize"));

	m_btnApply.EnableWindow(FALSE);	
}

void CWallpaperQDlg::FillQueuedImages()
{
	DWORD dwNumImagesInQueue = 0;
	CString cstrImageInfoPath = "";
	CString cstrImageInfo = "";
	int iQueuedWallpaperPosition = 0;
	
	// Get the total number of already queued images from the registry.
	dwNumImagesInQueue = CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "NumImages");
	
	// Clear the queued image list.
	m_lbQList.ResetContent();

	// Fill the queued images list with already queued images from the registry.
	for (DWORD dwLoop = 0; dwLoop < dwNumImagesInQueue; dwLoop++)
	{
		cstrImageInfoPath.Format("%d", dwLoop);

		cstrImageInfo = CRegistry::GetRegString("Software\\JasonSoft\\WallpaperQ", cstrImageInfoPath);

		// We save the image path and also the "position" of the wallpaper in the same string (comma delimited).
		int iIndex = m_lbQList.InsertString((int)dwLoop, cstrImageInfo.Left(cstrImageInfo.Find(",")));
		int iWPPos = atoi(cstrImageInfo.Right(cstrImageInfo.GetLength() - cstrImageInfo.Find(",") - 1));
		m_lbQList.SetItemData(iIndex, iWPPos);
	}

	// Select the first item.
	if (dwNumImagesInQueue > 0) 
		m_lbQList.SetSel(0);
}

void CWallpaperQDlg::OnStnClickedBrowse()
{
	BROWSEINFO* lpbi = NULL;
	ITEMIDLIST* lpiidl;
	char chrDiplayName[MAX_PATH];
	char chrPath[MAX_PATH];
	
	// Open a browse for folder dialog.
	lpbi = new BROWSEINFO;

	ZeroMemory(lpbi, sizeof(BROWSEINFO));
	ZeroMemory(chrPath, sizeof(MAX_PATH));

    lpbi->hwndOwner = this->m_hWnd; 
    lpbi->pidlRoot = NULL; 
    lpbi->pszDisplayName = chrDiplayName;
    lpbi->lpszTitle = "Browse for Images (.bmp)"; ; 
    lpbi->ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS | BIF_BROWSEINCLUDEFILES; 
    lpbi->lpfn = NULL; 

	lpiidl = SHBrowseForFolder(lpbi);

	SHGetPathFromIDList(lpiidl, chrPath);

	// Set the browse path to the path you just browsed to.
	strcat(chrPath, "\\");
	SetBrowsePath(chrPath);

	m_edLookIn.SetWindowText(GetBrowsePath());

	if (chrPath[0] != '\0')
	{
		// Reset the top list box.
		m_lbBrowseList.ResetContent();
		OnLbnSelchangeBrowselist();

		FillList();
	}

	delete lpbi;
}

void CWallpaperQDlg::OnEnChangeLookin()
{
	// Change browse list contents based on what they typed in the edit box.
	m_edLookIn.GetWindowText(cstrBrowsePath);
	m_lbBrowseList.ResetContent();
	OnLbnSelchangeBrowselist();
	FillList();
}

void CWallpaperQDlg::FillList()
{
	CFileFind finder;
	int iOnlyBMPs = 1;

	// Clear the list box.
	m_lbBrowseList.ResetContent();

	// Build the search string.
	if (cstrBrowsePath.GetAt(cstrBrowsePath.GetLength()-1) != '\\') cstrBrowsePath += "\\";

	CString cstrSearch[6] = {cstrBrowsePath + "*.bmp", cstrBrowsePath + "*.jpg", cstrBrowsePath + "*.jpeg", 
		cstrBrowsePath + "*.gif", cstrBrowsePath + "*.dib", cstrBrowsePath + "*.png"};
	
	// If Active Desktop is available, we can use other images besides BMPs.
	if (pIActiveDesktop != NULL) 
		iOnlyBMPs = 6;

	// Get all image files into the list.
	for (int i=0; i<iOnlyBMPs; i++)
	{
		BOOL bWorking = finder.FindFile(cstrSearch[i]);
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			m_lbBrowseList.AddString(finder.GetFilePath());
		}

		finder.Close();
	}

	// Select the first image.
	if (m_lbBrowseList.GetCount() > 0)
	{
		m_lbBrowseList.SetSel(0);
		OnLbnSelchangeBrowselist();
	}
}

void CWallpaperQDlg::OnLbnSelchangeBrowselist()
{
	CDC* pDC = m_picPreview.GetWindowDC();

	// Change the previewed image.
	if (pDC) 
	{
		DrawPreview(pDC);
		ReleaseDC(pDC);
	}
}

void CWallpaperQDlg::DrawPreview(CDC* pDC)
{
	USES_CONVERSION;

	CString cstrWidth, cstrHeight, cstrType;
	UINT uiWidth, uiHeight;
	UINT thumbWidth, thumbHeight;
	int iAdjTop, iAdjLeft;
	int iCount = 0;
	double dRatio;
	TCHAR szBuf[MAX_PATH];
	RECT rect;
	CWnd* pWndTemp = NULL;

	// Initialize the Graphics class in GDI+.
	Graphics graphics(pDC->m_hDC);

	// Fill the preview area with a WHITE background.
	m_picPreview.GetClientRect(&rect);
	rect.left += 1;
	rect.top += 1;
	rect.right -= 1;
	rect.bottom -= 1;
	pDC->FillSolidRect(&rect, RGB(255,255,255));

	// Determine which listbox (LeftList or QList has focus.
	pWndTemp = GetFocus();
	if (pWndTemp)
	{
		// Since one list is a ListBox and the other is a ListCtrl
		// we get the count in 2 different ways.
		if (GetFocus()->m_hWnd == m_lbQList.m_hWnd)
			iCount = m_lbQList.GetCount();  // QList has focus, so get its count.
		else
			iCount = m_lbBrowseList.GetCount();  // LeftList has focus, so get its count.

		if (iCount > 0)
		{
			// Get the path to the image from the list with focus.
			if (GetFocus()->m_hWnd == m_lbQList.m_hWnd)
				m_lbQList.GetText(m_lbQList.GetCurSel(), szBuf);
			else
				m_lbBrowseList.GetText(m_lbBrowseList.GetCurSel(), szBuf);

			// Make sure there is an image chosen.
			if (szBuf[0] != '/0')
			{
				// Use the Image class to display a thumbnail of the image.
				Image image(T2CW(szBuf));

				// Determine the appropriate size of the thumbnail preview
				// given the image size ratio and the preview window size ratio.
				uiWidth = image.GetWidth();
				uiHeight = image.GetHeight();
				dRatio = ((double)uiWidth)/((double)uiHeight);

				// If the width is larger than the height of the image, 
				// set the width of the thumbnail to the width of the preview area
				// and calculate the thumbnail height by using the ratios.
				// If the height is larger than the width of the image, 
				// set the height of the thumbnail to the height of the preview area
				// and calculate the thumbnail width by using the ratios.
				if (uiWidth > uiHeight)
				{
					thumbWidth = rect.right - rect.left;
					thumbHeight = (UINT)(thumbWidth/dRatio);

					if (thumbHeight == 0) thumbHeight = 1;
					if (thumbHeight > (UINT)(rect.bottom - rect.top)) thumbHeight = rect.bottom - rect.top;

					// Adjust things to make the preview not paint over the control border.
					iAdjTop = 1 + ((rect.bottom - rect.top)/2) - (thumbHeight/2);
					iAdjLeft = 1;
				}
				else
				{
					thumbHeight = rect.bottom - rect.top;
					thumbWidth = (UINT)(uiWidth*thumbHeight/uiHeight);

					if (thumbWidth == 0) thumbWidth = 1;
					if (thumbWidth > (UINT)(rect.right - rect.left)) thumbWidth = rect.right - rect.left;

					// Adjust things to make the preview not paint over the control border.
					iAdjTop = 1;
					iAdjLeft = 1 + ((rect.right - rect.left)/2) - (thumbWidth/2);
				}

				// Get the thumbnail and display it in the preview control.
				Image* pThumbnail = image.GetThumbnailImage(thumbWidth, thumbHeight, NULL, NULL);
				graphics.DrawImage(pThumbnail, iAdjLeft, iAdjTop, pThumbnail->GetWidth(), pThumbnail->GetHeight());

				delete pThumbnail;

				// Display the image width and height.
				cstrWidth.Format("Width: %d", uiWidth);
				m_stWidth.SetWindowText(cstrWidth);
				cstrHeight.Format("Height: %d", uiHeight);
				m_stHeight.SetWindowText(cstrHeight);

				// Display the image bits per pixel (color depth).
				switch (image.GetPixelFormat())
				{
				case PixelFormat1bppIndexed:
					cstrType = "Type: 1bpp";
					break;
				case PixelFormat4bppIndexed:
					cstrType = "Type: 4bpp";
					break;
				case PixelFormat8bppIndexed:
					cstrType = "Type: 8bpp";
					break;
				case PixelFormat16bppARGB1555: 
				case PixelFormat16bppGrayScale: 
				case PixelFormat16bppRGB555: 
				case PixelFormat16bppRGB565:
					cstrType = "Type: 16bpp";
					break;
				case PixelFormat24bppRGB:
					cstrType = "Type: 24bpp";
					break;
				case PixelFormat32bppARGB: 
				case PixelFormat32bppPARGB: 
				case PixelFormat32bppRGB: 
					cstrType = "Type: 32bpp";
					break;
				case PixelFormat48bppRGB:
					cstrType = "Type: 48bpp";
					break;
				case PixelFormat64bppARGB: 
				case PixelFormat64bppPARGB:
					cstrType = "Type: 64bpp";
					break;
				default:
					cstrType = "Type: Unknown";
					break;
				}

				m_stType.SetWindowText(cstrType);
			}
			else
			{
				// No image to preview.
				m_stWidth.SetWindowText("Width:");
				m_stHeight.SetWindowText("Height:");
				m_stType.SetWindowText("Type:");
			}
		}
	}
}

void CWallpaperQDlg::OnBnClickedAdd()
{
	int iCount;
	CString cstrTemp;
	
	// Get all selected items from the browse list.
	iCount = m_lbBrowseList.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(iCount);
	m_lbBrowseList.GetSelItems(iCount, aryListBoxSel.GetData());

	// Loop through each slected item and add it to the Queue list.
	for (int i=0; i<aryListBoxSel.GetSize(); i++)
	{
		m_lbBrowseList.GetText(aryListBoxSel.GetAt(i), cstrTemp);

		// Select each newly added item.
		if (m_lbQList.FindStringExact(0, cstrTemp) > -1)
		{
			// If its already in the list, ask if they want to add it again.
			if (AfxMessageBox("This image already exists in the Queued Images list.  Do you wish to add it again?", MB_YESNO) == IDYES)
			{
                int index = m_lbQList.InsertString(m_lbQList.GetCount() + 1, cstrTemp);
				m_lbQList.SetItemData(index, 1);
			}
		}
		else
		{
            //int index = m_lbQList.InsertString(m_lbQList.GetCount() + 1, cstrTemp);
			int index = m_lbQList.AddString(cstrTemp);
			m_lbQList.SetItemData(index, 1);
		}
	}

	m_btnApply.EnableWindow();
}

void CWallpaperQDlg::OnLbnSelchangeQlist()
{
	CDC* pDC = m_picPreview.GetWindowDC();

	// Show the last selected item in the queued image list in the preview window.
	if (pDC)
	{
		DrawPreview(pDC);
		ReleaseDC(pDC);
	}

	if (m_lbQList.GetCount() > 0)
	{
		// If there are items in the queue list, enable the position combo box. 
		m_comboPosition.SetCurSel((int)m_lbQList.GetItemData(m_lbQList.GetCurSel()));
		m_comboPosition.EnableWindow();

		// Change the up and down arrow images.
		if (m_lbQList.GetSelCount() > 1)
		{
			m_btnArrowUp.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DARROWUP)));
			m_btnArrowDown.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DARROWDOWN)));
		}
		else if (m_lbQList.GetSelCount() == 1)
		{
			m_btnArrowUp.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ARROWUP)));
			m_btnArrowDown.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ARROWDOWN)));
		}
	}
}

void CWallpaperQDlg::OnBnClickedArrowup()
{
	int iIndex;
	DWORD dwData;
	CString cstrPath;

	// Move the selected item (single selection only) up one spot in the list.
	if (m_lbQList.GetCount() > 0 && m_lbQList.GetSelCount() == 1)
	{
		iIndex = m_lbQList.GetCurSel();

		if (iIndex > 0)
		{
			m_lbQList.GetText(iIndex, cstrPath);
			dwData = (DWORD)m_lbQList.GetItemData(iIndex);

			m_lbQList.DeleteString(iIndex);

			iIndex--;

			m_lbQList.InsertString(iIndex, cstrPath);
			m_lbQList.SetItemData(iIndex, dwData);

			m_lbQList.SetSel(iIndex);

			m_btnApply.EnableWindow();
		}
	}
}

void CWallpaperQDlg::OnBnClickedArrowdown()
{
	int iIndex;
	DWORD dwData;
	CString cstrPath;

	// Move the selected item (single selection only) down one spot in the list.
	if (m_lbQList.GetSelCount() > 0 && m_lbQList.GetSelCount() == 1)
	{
		iIndex = m_lbQList.GetCurSel();

		if (iIndex < m_lbQList.GetCount())
		{
			m_lbQList.GetText(iIndex, cstrPath);
			dwData = (DWORD)m_lbQList.GetItemData(iIndex);

			m_lbQList.DeleteString(iIndex);

			iIndex++;

			m_lbQList.InsertString(iIndex, cstrPath);
			m_lbQList.SetItemData(iIndex, dwData);

			m_lbQList.SetSel(iIndex);

			m_btnApply.EnableWindow();
		}
	}
}


void CWallpaperQDlg::OnBnClickedRemoveselected()
{
	int iCount = 0;

	// Get all selected items from the browse list.
	iCount = m_lbQList.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(iCount);
	m_lbQList.GetSelItems(iCount, aryListBoxSel.GetData());

	// Loop through each selected item and delete it from the Queue list.
	for (int i=0; i<aryListBoxSel.GetSize(); i++)
		m_lbQList.DeleteString(aryListBoxSel.GetAt(i));

	m_btnApply.EnableWindow();
}


void CWallpaperQDlg::OnBnClickedQlistempty()
{
	// Empty the Queued images list.
	m_lbQList.ResetContent();

	m_btnApply.EnableWindow();
}

void CWallpaperQDlg::OnCbnSelchangePosition()
{
	int iPosition = 1;
	int iCount = 0;

	iPosition = m_comboPosition.GetCurSel();
	
	// Get all selected items from the queued image list.
	iCount = m_lbQList.GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(iCount);
	m_lbQList.GetSelItems(iCount, aryListBoxSel.GetData());

	// Loop through each selected item and change its wallpaper position.
	for (int i=0; i<aryListBoxSel.GetSize(); i++)
		m_lbQList.SetItemData(aryListBoxSel.GetAt(i), (DWORD)iPosition);

	m_btnApply.EnableWindow();
}

void CWallpaperQDlg::OnBnClickedRandomize()
{
	m_btnApply.EnableWindow();
}

void CWallpaperQDlg::ApplyChanges()
{
	// Delete all keys under wallpaperq in the registry.
	CRegistry::RegDelete("Software\\JasonSoft", "", "WallpaperQ");

	// Set the last browse path in the registry.
	CRegistry::SetRegString("Software\\JasonSoft\\WallpaperQ", "LastPath", cstrBrowsePath);

	// Set the number of images saved in the registry from the queue list.
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "NumImages", m_lbQList.GetCount());

	// Loop through the queued image list and save each image in the registry.
	for (int iLoop = 0; iLoop < m_lbQList.GetCount(); iLoop++)
	{
		CString cstrPath;
		CString cstrRegValue = "";
		CString cstrRegPath = "";

		m_lbQList.GetText(iLoop, cstrPath);
		cstrRegPath.Format("%s,%d", cstrPath, (int)m_lbQList.GetItemData(iLoop));

		cstrRegValue.Format("%d", iLoop);

		CRegistry::SetRegString("Software\\JasonSoft\\WallpaperQ", cstrRegValue, cstrRegPath);
	}

	// Set whether to display a random image when run.
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "Randomize", (DWORD)m_chkRandomize.GetCheck());

	// Set them in the registry.
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "RunAtStartup", (DWORD)iStartup); 
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ThisOrAllUsers", (DWORD)iThisUser);
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ExitAfter", (DWORD)iExitAfter);
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "UseTimer", (DWORD)iUseTimer);
	CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "TimerMinutes", (DWORD)iMinutes);

	// Change the wallpaper.
	ChangeWallpaper(m_chkRandomize.GetCheck());
}

void CWallpaperQDlg::OnBnClickedApply()
{
	// Apply changes without closing/minimizing.
	ApplyChanges();

	m_btnApply.EnableWindow(FALSE);
}

void CWallpaperQDlg::ChangeWallpaper(int iRandom)
{
	USES_CONVERSION;

	int iImageNum = 0;
	int iPosition = 1;
	CString cstrTileWallpaper;
	CString cstrWallpaperStyle;
	TCHAR szBuf[MAX_PATH];

	// Choose then next image in the list, or choose a random image.
	if (iRandom == 1)
	{
		srand((unsigned)time(NULL));

		iImageNum = rand()%m_lbQList.GetCount();

		iCurrentImage = iImageNum;
	}
	else
	{
		iCurrentImage++;
		if (iCurrentImage + 1 > m_lbQList.GetCount()) iCurrentImage = 0;
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "CurrentImage", (DWORD)iCurrentImage);

		iImageNum = iCurrentImage;
	}

	// Get the image path from the registry by the image number.
	iPosition = (int)m_lbQList.GetItemData(iImageNum);
	m_lbQList.GetText(iImageNum, szBuf);

	if (szBuf[0] != '/0')
	{
		// If Active Desktop is not available, use the SystemParametersInfo function.
		if (pIActiveDesktop == NULL)
		{
			if (iPosition == 0)
			{
				// Tiled
				cstrTileWallpaper = "1";
				cstrWallpaperStyle = "1";
			}
			else if (iPosition == 1)
			{
				// Center
				cstrTileWallpaper = "0";
				cstrWallpaperStyle = "1";
			}
			else
			{
				// Stretch
				cstrTileWallpaper = "0";
				cstrWallpaperStyle = "2";
			}

			// Set registry values for the wallpaper position.
			CRegistry::SetRegString("Control Panel\\Desktop", "TileWallpaper", cstrTileWallpaper);
			CRegistry::SetRegString("Control Panel\\Desktop", "WallpaperStyle", cstrWallpaperStyle);

			// Change the wallpaper.
			SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)szBuf, 
				SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);	
		}
		else
		{
			WALLPAPEROPT wpOptions;
			COMPONENTSOPT compOptions;

			compOptions.dwSize = sizeof(COMPONENTSOPT);
			compOptions.fActiveDesktop = TRUE;
			compOptions.fEnableComponents = TRUE;

			pIActiveDesktop->SetDesktopItemOptions(&compOptions, 0);

			// Set the wallpaper position.
			wpOptions.dwSize = sizeof(WALLPAPEROPT);
			if (iPosition == 0)
				wpOptions.dwStyle = WPSTYLE_TILE;
			else if (iPosition == 1)
				wpOptions.dwStyle = WPSTYLE_CENTER;
			else
				wpOptions.dwStyle = WPSTYLE_STRETCH;

			pIActiveDesktop->SetWallpaperOptions(&wpOptions, 0);

			// Set the wallpaper image.
			pIActiveDesktop->SetWallpaper(T2CW(szBuf), 0);

			// Apply all changes.
			pIActiveDesktop->ApplyChanges(AD_APPLY_ALL);
		}

		if (iExitAfter == 1) OnExit();
	}
}

LRESULT CWallpaperQDlg::OnNotifyIconMsg(WPARAM wParam, LONG lParam)
{
	// Show a right-click menu from the system tray icon 
	// if they right-click or double click it.
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONUP:
		POINT point;
		CMenu menu;

		GetCursorPos(&point);
		
		menu.LoadMenu(IDR_NOTIFYICON_MENU);
		CMenu* pMenu = menu.GetSubMenu(0);
		pMenu->SetDefaultItem(ID_CONFIGUREWALLPAPERQUEUE);

		SetForegroundWindow();

		pMenu->TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,  point.x, point.y, this);

		PostMessage(WM_NULL, 0, 0);
		menu.DestroyMenu();
		break;
	}
 
	return 1;
}

void CWallpaperQDlg::OnAbout()
{
	// Show the about dialog.
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CWallpaperQDlg::OnShowConfigWindow()
{
	RECT trayrect;

	GetTrayWndRect(&trayrect);

	DrawAnimatedRects(IDANI_CAPTION, &trayrect, &rcLastSize);
	
	MoveWindow(&rcLastSize);
}

LRESULT CWallpaperQDlg::OnHideMainWindow(WPARAM wParam, LONG lParam)
{
	RECT rcTray, rcWindow;

	GetTrayWndRect(&rcTray);
	GetWindowRect(&rcWindow);

	rcLastSize = rcWindow;

	MoveWindow(rcTray.left, rcTray.top, 0, 0);

	DrawAnimatedRects(IDANI_CAPTION, &rcWindow, &rcTray);

	return 1;
}

LRESULT CWallpaperQDlg::OnShowOptions(WPARAM wParam, LONG lParam)
{
	// Display the options dialog.
	OnOptions();

	return 1;
}

void CWallpaperQDlg::OnOptions()
{
	CString cstrStartupApp = "";
	
	// Get initial options values from the registry.
	iStartup = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "RunAtStartup", 1); 
	iThisUser = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ThisOrAllUsers", 1);
	iExitAfter = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ExitAfter", 0);
	iUseTimer = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "UseTimer", 0);
	iMinutes = (int)CRegistry::GetRegDWORD("Software\\JasonSoft\\WallpaperQ", "TimerMinutes", 0);

	// Open the options dialog, sending the options values.
	COptionsDialog dlgOptions(iStartup, iThisUser, iExitAfter, iUseTimer, iMinutes);
	if (dlgOptions.DoModal() == IDOK)
	{
		// Get the chosen options.
		iStartup = dlgOptions.GetRunAtStartup(); 
		iThisUser = dlgOptions.GetRunForThisUserOrAll();
		iExitAfter = dlgOptions.GetExitAfterWallpaperChange();
		iUseTimer = dlgOptions.GetUseTimer();
		iMinutes = dlgOptions.GetMinutesForTimer();

		// Set them in the registry.
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "RunAtStartup", (DWORD)iStartup); 
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ThisOrAllUsers", (DWORD)iThisUser);
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "ExitAfter", (DWORD)iExitAfter);
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "UseTimer", (DWORD)iUseTimer);
		CRegistry::SetRegDWORD("Software\\JasonSoft\\WallpaperQ", "TimerMinutes", (DWORD)iMinutes);

		// Remove wallpaperq from the startup portion of the registry.
		CRegistry::RegDelete("Software\\Microsoft\\Windows\\CurrentVersion\\Run", "WallpaperQ", "", 
			HKEY_LOCAL_MACHINE); 
		CRegistry::RegDelete("Software\\Microsoft\\Windows\\CurrentVersion\\Run", "WallpaperQ", "", 
			HKEY_CURRENT_USER);

		// If the chose to start the app on system startup, add it back to the registry.
		if (iStartup == 1)
		{
			cstrStartupApp.Format("\"%sWallpaperQ.exe\"", cstrAppPath);
			if (iThisUser == 1)
			{
				// For this user only.
				CRegistry::SetRegString("Software\\Microsoft\\Windows\\CurrentVersion\\Run", 
					"WallpaperQ", cstrStartupApp);
			}
			else
			{
				// For all users.
				CRegistry::SetRegString("Software\\Microsoft\\Windows\\CurrentVersion\\Run", 
					"WallpaperQ", cstrStartupApp, HKEY_LOCAL_MACHINE);
			}
		}

		// If they chose to change the wallpaper every X minutes, kill any 
		// previous timers and start a new one based on the minutes entered.
		if (iUseTimer == 1)
		{
			if (uiTimer != 0)
				KillTimer(uiTimer);
				
			if (iMinutes > 0) 
				uiTimer = (UINT)SetTimer(1, iMinutes*60000, NULL);
		}
		else
		{
			// Or just kill it if they didn't choose to use a timer.
			if (uiTimer != 0)
				KillTimer(uiTimer);
		}

		// Ask them if they want to exit now if they chose to exit after changing wallpaper.
		if (iExitAfter == 1)
		{
			if (AfxMessageBox("You have chosen to exit after the wallpaper changes. " \
				"Would you like to exit now?", MB_YESNO) == IDYES)
				OnExit();
		}
	}
}

void CWallpaperQDlg::OnTimer(UINT nIDEvent)
{
	// When the timer is fired, change the wallpaper to the next image.
	ChangeWallpaper(m_chkRandomize.GetCheck());

	CDialog::OnTimer(nIDEvent);
}

void CWallpaperQDlg::OnBnClickedOk()
{
	// Apply changes, then minimize.
	ApplyChanges();

	m_btnApply.EnableWindow(FALSE);

	SendMessage(WM_HIDEWINDOW);
}

void CWallpaperQDlg::OnExit()
{
	// Remove the system tray icon.
	Shell_NotifyIcon(NIM_DELETE, &niData);

	PostQuitMessage(0);
}

void CWallpaperQDlg::OnBnClickedCancel()
{
	SendMessage(WM_HIDEWINDOW);

	// They hit cancel, so we reset things.
	// If they clicked OK, it comes to this function, but it should have 
	// saved everything prior toi this.
	ResetMainDialog();
}
