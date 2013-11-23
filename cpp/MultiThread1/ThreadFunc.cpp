
#include "stdafx.h"
#include "MultiThread1.h"
#include <strstream>
#include "ThreadFunc.h"
#include "TreadDiag.h"
#include "threadstarter.h"


UINT ThreadFunction( LPVOID pParam )
{
	ThreadStarter *Starter = (ThreadStarter *) pParam;

	for(int x = 1; x< 11; x++)
	{
		ostrstream outpt;

		outpt << "(" << Starter->GetThreadID() << ") message #" << x << ends;
		Starter->GetDialog()->AddString(outpt.str());

		PostMessage(Starter->GetHWND(),WM_USER_UPDATE_THREADDIAG,0,0);
		outpt.rdbuf()->freeze(0);
		::Sleep(500);
	}
	PostMessage(Starter->GetHWND(),WM_USER_THREADFINISH,Starter->GetThreadID(),0);
	
	delete Starter;
	return 1;
}