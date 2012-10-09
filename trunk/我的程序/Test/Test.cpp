// Test.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "SkinPPWTL.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestApp construction

CTestApp::CTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestApp object

CTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestApp initialization

BOOL CTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	CString sSkin;
	GetTempPath(100, sSkin.GetBuffer(100));
	sSkin.ReleaseBuffer();
	CString sSkinPath = sSkin + "\spring.ssk";
	CFileFind find;
	if(!find.FindFile(sSkinPath))
	{
		HRSRC hMySource = FindResource(NULL, MAKEINTRESOURCE(IDR_SSK), "SSK");
		if(hMySource)
		{
			DWORD dwSourceSize = SizeofResource(NULL, hMySource);
			HGLOBAL hResData = LoadResource(NULL, hMySource);
			if(hResData)
			{
				HANDLE hFile = CreateFile(sSkinPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
				if(hFile)
				{
					DWORD dwWritten;
					WriteFile(hFile, (LPVOID)LockResource(hResData), dwSourceSize, &dwWritten, NULL);
					CloseHandle(hFile);
				}
			}
		}
	}	
	CTestDlg dlg;
	m_pMainWnd = &dlg;
	skinppLoadSkin(sSkinPath.GetBuffer(100));
	sSkinPath.ReleaseBuffer();
	int nResponse = dlg.DoModal();
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
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTestApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	skinppExitSkin();
	return CWinApp::ExitInstance();
}
