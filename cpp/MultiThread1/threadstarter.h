
#ifndef THREADSTARTER_H
#define THREADSTARTER_H

class CTreadDiag;

class ThreadStarter
{
public:
	ThreadStarter(	CTreadDiag 		*TheDialog,
						unsigned int 	ThreadID,
						HWND				hwnd			)
	:	mTheDialog(TheDialog),
		mThreadID(ThreadID),
		mHwnd(hwnd)
	{}
	
	CTreadDiag * GetDialog()
	{
		return mTheDialog;
	}
	unsigned int GetThreadID()
	{
		return mThreadID;
	}
	HWND GetHWND()
	{
		return mHwnd;
	}
	
private:	
	CTreadDiag 		*mTheDialog;
	unsigned int 	mThreadID;
	HWND				mHwnd;

};


#endif THREADSTARTER_H
