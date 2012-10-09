// WizKMCalendar.cpp : main source file for WizKMCalendar.exe
//

#include "stdafx.h"

#include "resource.h"

#include "WizKMCalendarView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

CAppModule _Module;

int Run(LPTSTR lpstrCmdLine, int nCmdShow = SW_SHOWDEFAULT)
{
	if (WizKMIsSingleApp())
	{
		if (!CWizSingletonApp::InitApp(_T("WizCalendarApp")))
		{
			if (HWND hwnd = WizKMGetCalendarWindowHandle())
			{
				BringWindowToTop(hwnd);
				SetForegroundWindow(hwnd);
				ShowWindow(hwnd, SW_SHOW);
				return 0;
			}
		}
	}
	//
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain(lpstrCmdLine);
	if (!wndMain.OpenDatabase())
		return -1;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
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

	//
	AtlAxWinInit();
	//
	WizTranslationsInit();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
