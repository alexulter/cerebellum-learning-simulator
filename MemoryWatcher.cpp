// MemoryWatcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MemoryWatcher.h"
#include "MemoryWatcherDlg.h"



//for console stdout
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
//for time counter
#include < ctime >

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void SetStdOutToNewConsole()
{
  int hConHandle;
  long lStdHandle;
  FILE *fp;

  // allocate a console for this app
  AllocConsole();

  // redirect unbuffered STDOUT to the console
  lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
  fp = _fdopen( hConHandle, "w" );
  *stdout = *fp;

  setvbuf( stdout, NULL, _IONBF, 0 );
}
void SetStdOutToNewConsole_advanced()
{
    // allocate a console for this app
    AllocConsole();

    // redirect unbuffered STDOUT to the console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int fileDescriptor = _open_osfhandle((intptr_t)consoleHandle, _O_TEXT);
    FILE *fp = _fdopen( fileDescriptor, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // give the console window a nicer title
    SetConsoleTitle(L"Debug Output");

    // give the console window a bigger buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if ( GetConsoleScreenBufferInfo(consoleHandle, &csbi) )
    {
        COORD bufferSize;
        bufferSize.X = csbi.dwSize.X;
        bufferSize.Y = 9999;
        SetConsoleScreenBufferSize(consoleHandle, bufferSize);
    }
}

// CMemoryWatcherApp

//BEGIN_MESSAGE_MAP(CMemoryWatcherApp, CWinApp)
//	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
//END_MESSAGE_MAP()


// CMemoryWatcherApp construction

CMemoryWatcherApp::CMemoryWatcherApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMemoryWatcherApp object

CMemoryWatcherApp theApp;


// CMemoryWatcherApp initialization

BOOL CMemoryWatcherApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	/*INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);*/

	CWinApp::InitInstance();
	
	SetStdOutToNewConsole();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

time_t tstart, tend;
tstart = time(0);

	Purkinje* purk = new Purkinje;
	purk->Run();
	if (purk!=NULL) delete purk;	// удалить динамический объект

tend = time(0);
cout << "It took " << difftime(tend, tstart) << " second(s)." << endl;
Sleep(5000);
//*/
/*	CMemoryWatcherDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.*/
	
	return FALSE;
}
