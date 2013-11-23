#include <windows.h>
#include <stdio.h>

class WinVersion
{
	public:
	
	WinVersion(void)
	{
		DWORD dwVersion;
		
		dwVersion = GetVersion();
		
		mWin_major_rls = LOBYTE(LOWORD(dwVersion));
		mWin_minor_rls = HIBYTE(LOWORD(dwVersion));
	}
	
	int BetterThan31(void)
	{
		if (		mWin_major_rls > 3
				||(	(mWin_major_rls == 3)
					&&	(mWin_minor_rls >= 50)	)
			)		
		{
			return 1;			
		}
		else
		{
			return 0;
		}
	}
	int GetMajorNumber(void)
	{
		return mWin_major_rls;
	}
	int GetMinorNumber(void)
	{
		return mWin_minor_rls;
	}	
	
	private:
	
	int mWin_major_rls;
	int mWin_minor_rls;
};

	
main()
{
	WinVersion wv;
	
	printf("Win: %d.%d\n",wv.GetMajorNumber(),wv.GetMinorNumber());
	printf("BetterThan31 %d\n",wv.BetterThan31());
	
}
