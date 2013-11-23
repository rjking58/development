///////////////////////////////////////////////////////////
// CDIB.H: Header file for the DIB class.
///////////////////////////////////////////////////////////

#ifndef __CDIB_H
#define __CDIB_H

class CDib : public CObject
{
private:
	CString m_Name;
protected:
   LPBITMAPFILEHEADER m_pBmFileHeader;
   LPBITMAPINFO m_pBmInfo;
   LPBITMAPINFOHEADER m_pBmInfoHeader;
   RGBQUAD* m_pRGBTable;
   BYTE* m_pDibBits;
   UINT m_numColors;

public:
   CDib(CString fileName);
   ~CDib();

   DWORD GetDibSizeImage();
   UINT GetDibWidth();
   UINT GetDibHeight();
   UINT GetDibNumColors();
   LPBITMAPINFOHEADER GetDibInfoHeaderPtr();
   LPBITMAPINFO GetDibInfoPtr();
   LPRGBQUAD GetDibRGBTablePtr();
   BYTE* GetDibBitsPtr();
	CString GetDibName();

protected:
    void LoadBitmapFile(const char* fileName);

};

#endif

