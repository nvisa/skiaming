// WizNote.cpp : main source file for WizNote.exe
//

#include "stdafx.h"

#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

#include "../WizKMCore/WizKMCore_i.c"


CAppModule _Module;

int Run(LPTSTR lpstrCmdLine, int nCmdShow = SW_SHOWDEFAULT)
{
	if (!CWizSingletonApp::InitApp(_T("WizNoteApp")))
	{
		if (HWND hwnd = WizKMGetNoteWindowHandle())
		{
			SetForegroundWindow(hwnd);
			//
			CMainDlg::WriteCommandLineToReg(lpstrCmdLine);
			//
			PostMessage(hwnd, UM_PROCESS_COMMANDLINE, TRUE, 0);
			//
			return 0;
		}
	}
	//
	//
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain(lpstrCmdLine);
	if (!dlgMain.OpenDatabase())
		return 0;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	//
	OleInitialize(NULL);
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();
	//
	WizTranslationsInit();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
