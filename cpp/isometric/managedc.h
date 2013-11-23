
#ifndef MANAGEDC_H
#define MANAGEDC_H

class ManageDC
{
public:
	ManageDC(HWND hWindow)
	{
		m_DC = GetDC(hWindow);
	}
	
	~ManageDC()
	{
      ReleaseDC(m_hWindow,m_DC);
	}
	
	HDC borrowedDC()
	{
		return m_DC;
	}
private:
	
		HDC 	m_DC;			// DC we are managing
		HWND 	m_hWindow;	// handle to dc's owning window
	 
};

#endif //MANAGEDC_H
