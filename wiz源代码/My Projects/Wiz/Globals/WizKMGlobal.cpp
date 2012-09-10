#include "stdafx.h"
#include "WizKMGlobal.h"


#include <shellapi.h>

CString WizKMGetTempPath()
{
	CString strPath = WizGetSystemTempPath() + _T("Wiz\\");
	WizEnsurePathExists(strPath);
	return strPath;
}

CString WizKMGetEditorTempPath()
{
	CString strPath = WizGetSystemTempPath() + _T("WizHtmlEditor\\") + WizIntToStr(GetTickCount()) + _T("\\");
	WizEnsurePathExists(strPath);
	return strPath;
}


CString WizKMSelectDataStore(LPCTSTR lpszReg, LPCTSTR lpszApp)
{
	CString strRet(lpszApp);
	//
	typedef BOOL WINAPI Type_WizKMSelectDataStore(LPCWSTR lpszReg, LPCWSTR lpszApp, BSTR* pbstrRet);
	//
	HMODULE hModule = ::LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return strRet;
	//
	Type_WizKMSelectDataStore* fun = (Type_WizKMSelectDataStore *)::GetProcAddress(hModule, "WizKMSelectDataStore");
	if (!fun)
		return strRet;
	//
	CComBSTR bstrRet;
	fun(CStringW(lpszReg), CStringW(lpszApp), &bstrRet);
	//
	strRet = CString(bstrRet);
	//
	FreeLibrary(hModule);
	//
	return strRet;
}


CString WizKMGetDataStoreSubPath()
{
	CString strProductName = ::WizGetProductName();
	if (::WizKMIsAmazingNote())
	{
		return CString(_T("AmazingNote Data\\"));
	}
	//
	return CString(_T("My Knowledge\\"));
}

CString WizKMGetDataStorePathFromReg()
{
	CString strPathFromReg = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DataStore"), NULL);
	if (!strPathFromReg.IsEmpty())
		return strPathFromReg;
	//
	//strPathFromReg = WizGetMyDocumentsPath() + g_lpszDataStoreSubPath;
	//if (PathFileExists(strPathFromReg))
	//	return strPathFromReg;
	//
	return CString();
}

BOOL WizKMIsDev()
{
	static BOOL bDev = (WizGetSettings(_T("Common"), _T("DEV"), _T(""))  == _T("1"));
	return bDev;
}

BOOL WizKMIsPortable()
{
	static BOOL bPortable = (WizGetSettings(_T("Common"), _T("Portable"), _T(""))  == _T("1"));
	return bPortable;
}
CString WizKMGetDataStorePathFromApp()
{
	CString strRet;
	//
	BOOL bPortable = WizKMIsPortable();
	if (!bPortable)
		return strRet;
	//
	strRet = WizGetAppPath() + WizKMGetDataStoreSubPath();
	//
	return strRet;
}

CString WizKMGetDataStorePath()
{
	if (WizIsSystem())
	{
		return WizGetAppPath();
	}
	//
	CString strPathFromReg = WizKMGetDataStorePathFromReg();
	CString strPathFromApp = WizKMGetDataStorePathFromApp();
	//
	CString strPath;
	//
	if (!strPathFromReg.IsEmpty()
		&& !strPathFromApp.IsEmpty())
	{
		strPath = WizKMSelectDataStore(strPathFromReg, strPathFromApp); 
	}
	else if (!strPathFromReg.IsEmpty())
	{
		strPath = strPathFromReg;
	}
	else if (!strPathFromApp.IsEmpty())
	{
		strPath = strPathFromApp;
	}
	else
	{
		strPath = WizGetMyDocumentsPath() + WizKMGetDataStoreSubPath();
	}
	//
	WizPathAddBackslash(strPath);
	WizEnsurePathExistsEx(strPath + _T("Data\\"));
	//
	return strPath;
}

BOOL WizKMSetDataStorePath(LPCTSTR lpszPath)
{
	CString strPath(lpszPath);
	//
	WizPathAddBackslash(strPath);
	//
	return WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DataStore"), strPath);
}

CString WizKMGetBackupPath()
{
	CString strPath = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("Backup"), NULL);
	if (strPath.IsEmpty())
		return strPath;
	//
	WizPathAddBackslash(strPath);
	//
	WizEnsurePathExists(strPath);
	return strPath;
}

BOOL WizKMSetBackupPath(LPCTSTR lpszPath)
{
	CString strPath(lpszPath);
	//
	WizPathAddBackslash(strPath);
	//
	return WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("Backup"), strPath);
}


CString WizKMGetSettingsPath()
{
	return WizKMGetDataStorePath();
}

CString WizKMGetSettingsFileTitle()
{
	return WizKMIsAmazingNote() ? _T("AmazingNote") : _T("WizKM");
}
CString WizKMGetSettingsFileName()
{
	static CString strPath = WizKMGetSettingsPath() + WizKMGetSettingsFileTitle() + _T(".xml");
	return strPath;
}

CString WizKMGetLogFileName()
{
	static CString strFileName = WizKMGetSettingsPath() + WizKMGetSettingsFileTitle() + _T(".log");
	return strFileName;
}
CString WizKMGetSkinsPath()
{
	static CString strPath = WizGetAppPath() + _T("skins\\default\\");
	return strPath;
}
HICON WizKMLoadSkinsIcon(LPCTSTR lpszIconFileName, int nWidth /*= 16*/, int nHeight /*= 16*/)
{
	CString strFileName = WizKMGetSkinsPath() + lpszIconFileName;
	if (!PathFileExists(strFileName))
		return NULL;
	//
	return (HICON)LoadImage(NULL, strFileName, IMAGE_ICON, nWidth, nHeight, LR_LOADFROMFILE);
}

CString WizKMGetDefaultHtmlEditorFileName()
{
	return WizGetAppPath() + _T("WizHtmlEditor.exe");
}

BOOL WizKMNewDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, LPCTSTR lpszHtmlFileName, BOOL bInitEmptyTitle, LPCTSTR lpszDocumentType)
{
	CString strExeFileName = WizKMGetDefaultHtmlEditorFileName();
	CString strTempPath = WizExtractFilePath(lpszHtmlFileName);
	//
	CString strParams = WizFormatString6(_T("/WizCommandLine=1 /WizKMNewDocument=1 /SaveAsNoChangeFile=1 /NoFileNameInTitle=1 /NoEmptyTitle=1 /NoFileNew=1 /NoFileOpen=1 /DonotAddToRecentList=1 /WizKMDatabasePath=%1 /WizKMDocumentLocation=%2 /WizKMDocumentType=%3 /TempPath=%4 /LogFileName=%5 /FileName=%6"), 
		lpszDatabasePath,
		lpszLocation,
		lpszDocumentType,
		strTempPath, 
		WizKMGetLogFileName(), 
		lpszHtmlFileName);
	//
	if (bInitEmptyTitle)
	{
		strParams = CString(_T("/InitEmptyTitle=1 ")) + strParams;
	}
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}
BOOL WizKMEditDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszHtmlFileName, LPCTSTR lpszDocumentGUID)
{
	CString strExeFileName = WizKMGetDefaultHtmlEditorFileName();
	CString strTempPath = WizExtractFilePath(lpszHtmlFileName);
	//
	CString strParams;
	strParams = WizFormatString5(_T("/WizCommandLine=1 /WizKMEditDocument=1 /SaveAsNoChangeFile=1 /NoFileNameInTitle=1 /NoEmptyTitle=1 /NoFileNew=1 /NoFileOpen=1 /DonotAddToRecentList=1 /WizKMDatabasePath=%1 /WizKMDocumentGUID=%2 /TempPath=%3 /LogFileName=%4 /FileName=%5"), 
		lpszDatabasePath, 
		lpszDocumentGUID, 
		strTempPath, 
		WizKMGetLogFileName(), 
		lpszHtmlFileName);
	//
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}


#ifndef WIZKM_NO_DEFAULT_WIZGLOBAL

class CWizKMGlobal: public CWizGlobalDefault
{
public:
	CWizKMGlobal()
		: CWizGlobalDefault(FALSE)
	{
	}
public:
	virtual void WriteLog(LPCTSTR lpszMsg)
	{
		WizWriteLog(WizKMGetLogFileName(), lpszMsg);
	}
};



IWizGlobal* WizGlobal()
{
	static CWizKMGlobal global;
	return &global;
}

#endif


CString WizKMGetAccountsBasePath()
{
	CString strAccountPath = WizKMGetDataStorePath() + _T("Data\\");
	WizEnsurePathExistsEx(strAccountPath);
	return strAccountPath;
}
