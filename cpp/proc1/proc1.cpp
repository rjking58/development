#include <windows.h>
#include <iostream.h>
#include <strstrea.h>

const int MAX_PROCS = 5;


void main()
{
	int						processCount = 0;
	int						currProcess;
	int						done = FALSE;
	int						waitRetVal;
	int						curr_alive = 0;


	STARTUPINFO				myStartInfo[MAX_PROCS];
	PROCESS_INFORMATION 	myProcInfo[MAX_PROCS];
	HANDLE					ProcessHandle[MAX_PROCS];
	char						aString[100];
	
	for(currProcess = 0; currProcess < MAX_PROCS; currProcess++)
	{
		ostrstream	titleString;

		titleString << "Process(" << currProcess << ")" << ends;

		myStartInfo[currProcess].cb = sizeof(STARTUPINFO);
		myStartInfo[currProcess].lpReserved = NULL;
		myStartInfo[currProcess].lpDesktop = NULL;
		myStartInfo[currProcess].lpTitle = titleString.str();
		myStartInfo[currProcess].dwFlags = 0;
		myStartInfo[currProcess].cbReserved2 = 0;
		myStartInfo[currProcess].lpReserved2 = NULL;

	}	
	
	
	
	
	for(currProcess = 0; currProcess < MAX_PROCS; currProcess++)
	{
		BOOL Success;

		Success = CreateProcess (	"simple1.exe",	//app name
											NULL,				//command line
											NULL,				//process security attrib.
											NULL,				//thread security attrib.
											FALSE,			//inherit handles
											CREATE_NEW_CONSOLE,	//creation flags
											NULL,						//environment
											NULL,						//current dir.
											&(myStartInfo[currProcess]),
											&(myProcInfo[currProcess]) );
		if(Success)
		{
			ProcessHandle[currProcess] = myProcInfo[currProcess].hProcess;
	
			CloseHandle(myProcInfo[currProcess].hThread);
			curr_alive++;
		}
	}
	
	cout << "Processes Created" << endl;
		
	while (curr_alive > 0)
	{
		DWORD	exitCode;
				
		if((waitRetVal = WaitForMultipleObjects(	curr_alive,
																ProcessHandle,
																FALSE,
																INFINITE			)) != WAIT_FAILED)
		{
			int y;

			waitRetVal -= WAIT_OBJECT_0;


			if(GetExitCodeProcess(ProcessHandle[waitRetVal],&exitCode))
			{
				switch(exitCode)
				{
				   case STILL_ACTIVE: cout << "Process is still active" << endl;
				                      break;
				   default:           cout << "Exit code = " <<  exitCode << endl;
				                      break;
				}
			}
		   else 
			{
				cout << "GetExitCodeProcess() failed" << endl;
			}

			cout << "Process complete, returnval(" << exitCode << ")" << endl;

			CloseHandle(ProcessHandle[waitRetVal]);

			curr_alive--;
				
			// We have to pass an array of ONLY VALID HANDLES to 
			// WaitForMultipleObjects!!
			if (waitRetVal < curr_alive)
			{
				for(y = waitRetVal; y < curr_alive; y++)
				{
					ProcessHandle[y] = ProcessHandle[y+1];		
				}
			}

		}

	}
	
	cout << "input anything:" ;	
	cin >> aString;
}

