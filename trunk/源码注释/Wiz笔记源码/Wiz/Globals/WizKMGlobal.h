#pragma once

#include "WizKMDef.h"

#include "../../WizGlobals/WizToolsDll.h"

const LPCTSTR WIZKM_SETTINGS_ROOT_NODE_NAME = _T("WizKMSettings");

CString WizKMGetTempPath();
CString WizKMGetEditorTempPath();
CString WizKMGetDataStorePath();
CString WizKMGetSettingsPath();
CString WizKMGetSettingsFileName();
CString WizKMGetLogFileName();
CString WizKMGetSkinsPath();
HICON WizKMLoadSkinsIcon(LPCTSTR lpszIconFileName, int nWidth = 16, int nHeight = 16);
BOOL WizKMIsPortable();
BOOL WizKMIsDev();

BOOL WizKMSetDataStorePath(LPCTSTR lpszPath);
//
CString WizKMGetBackupPath();
BOOL WizKMSetBackupPath(LPCTSTR lpszPath);
//
BOOL WizKMNewDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, LPCTSTR lpszHtmlFileName, BOOL bInitEmptyTitle, LPCTSTR lpszDocumentType);
BOOL WizKMEditDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszHtmlFileName, LPCTSTR lpszDocumentGUID);
//
CString WizKMGetAccountsBasePath();


inline BOOL WizKMIsOEM()
{
	static BOOL b = PathFileExists(WizGetAppPath() + _T("oem.ini"));
	return b;
}

inline BOOL WizKMIsSysFolderName(LPCTSTR lpszName)
{
	if (!lpszName)
		return FALSE;
	//
	if (!*lpszName)
		return FALSE;
	//
	return 0 == _tcsicmp(lpszName, FOLDER_MY_NOTES)
		|| 0 == _tcsicmp(lpszName, FOLDER_MY_JOURNALS)
		|| 0 == _tcsicmp(lpszName, FOLDER_MY_EVENTS)
		|| 0 == _tcsicmp(lpszName, FOLDER_MY_CONTACTS)
		|| 0 == _tcsicmp(lpszName, FOLDER_DELETED_ITEMS)
		;
}

inline CString WizKMGetVersion()
{
	return WizGetFileVersion(WizGetAppPath() + _T("WizKMControls.dll"));
}
inline CString WizKMWebSiteGetURL(LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	LCID lcid = WizTranslationsGetCurrentMappedLCID();
	CString strVersion = WizKMGetVersion();
	//
	CString strProductName = WizGetProductName();
	if (WizKMIsOEM())
	{
		strProductName = _T("Wiz");
	}
	//
	return WizWebSiteVisitGetURL(strProductName, WizIntToStr((int)lcid), strVersion, lpszCommand, lpszExtInfo);
}
inline CString WizKMWebSiteGetURL(LPCTSTR lpszCommand)
{
	return WizKMWebSiteGetURL(lpszCommand, _T(""));
}

inline void WizKMWebSiteVisit(LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	CString strURL = WizKMWebSiteGetURL(lpszCommand, lpszExtInfo);
	//
	ShellExecute(NULL, _T("open"), strURL, NULL, NULL, SW_SHOW);
}

inline void WizKMWebSiteVisit(LPCTSTR lpszCommand)
{
	WizKMWebSiteVisit(lpszCommand, _T(""));
}

inline void WizKMWebSiteVisitHome()
{
	WizKMWebSiteVisit(_T("home"));
}
inline void WizKMWebSiteVisitHelp(LPCTSTR lpszFile)
{
	WizKMWebSiteVisit(_T("help"), lpszFile);
}
inline void WizKMWebSiteVisitFeedback()
{
	WizKMWebSiteVisit(_T("feedback"));
}

inline CString WizKMWebSiteGetReturn(LPCTSTR lpszCommand)
{
	LCID lcid = WizTranslationsGetCurrentMappedLCID();
	CString strVersion = WizKMGetVersion();
	//
	CString strProductName = WizGetProductName();
	if (WizKMIsOEM())
	{
		strProductName = _T("Wiz");
	}
	//
	return WizWebSiteGetReturn(strProductName, lcid, strVersion, lpszCommand, _T(""));
}


inline CString WizKMGetDateTimeForTitle(const COleDateTime& t)
{
	return WizDateToLocalStringLongDate(t);
}

inline CString WizKMGetDateTitle(const COleDateTime& t, LPCTSTR lpszSubTitle)
{
	return WizFormatString2(_T("%1 %2"), WizKMGetDateTimeForTitle(t), lpszSubTitle);
}


inline BOOL WizKMIsAmazingNote()
{
	static BOOL b = (0 == WizGetProductName().CompareNoCase(_T("AmazingNote")));
	return b;
}

inline CString WizKMGetExplorerFileNameNoPath()
{
	return WizKMIsAmazingNote() ? _T("AnmazingNote.exe") : _T("WizExplorer.exe");
}
inline CString WizKMGetExplorerFileName()
{
	return WizGetAppPath() + WizKMGetExplorerFileNameNoPath();
}

inline BOOL WizKMNoteExists()
{
	static BOOL b = PathFileExists(WizGetAppPath() + _T("WizNote.exe"));
	return b;
}

inline BOOL WizKMCalendarExists()
{
	static BOOL b = PathFileExists(WizGetAppPath() + _T("WizKMCalendar.exe"));
	return b;
}

inline BOOL WizKMExplorerExists()
{
	static BOOL b = PathFileExists(WizKMGetExplorerFileName());
	return b;
}
inline BOOL WizKMEditorExists()
{
	static BOOL b = PathFileExists(WizGetAppPath() + _T("WizHtmlEditor.exe"));
	return b;
}

struct WIZKBINFO
{
	__int64 nStorageLimit;
	__int64 nStorageUsage;
	CString strStorageLimit;
	CString strStorageUsage;
	//
	__int64 nTrafficLimit;
	__int64 nTrafficUsage;
	CString strTrafficLimit;
	CString strTrafficUsage;

	//
	WIZKBINFO()
	{
		nStorageLimit = 0;
		nStorageUsage = 0;
		nTrafficLimit = 0;
		nTrafficUsage = 0;
	}
};



struct WIZOBJECTVERSION
{
	__int64 nDocumentVersion;
	__int64 nTagVersion;
	__int64 nStyleVersion;
	__int64 nAttachmentVersion;
	__int64 nDeletedGUIDVersion;
	//
	WIZOBJECTVERSION()
	{
		nDocumentVersion = -1;
		nTagVersion = -1;
		nStyleVersion = -1;
		nAttachmentVersion = -1;
		nDeletedGUIDVersion = -1;
	}
};




inline CString WizKMGetPrivateSettingsFileName()
{
	CString strName = ::WizGetProductName() + _T(".ini");
	//
	CString strUserFileName = WizKMGetDataStorePath() + strName;
	if (PathFileExists(strUserFileName))
		return strUserFileName;
	//
	return WizGetAppSettingsFileName();
}

inline int WizKMGetPrivateInt(LPCTSTR lpszSection, LPCTSTR lpszKeyName, int nDef)
{
	return GetPrivateProfileInt(lpszSection, lpszKeyName, nDef, WizKMGetPrivateSettingsFileName());
}

inline CString WizKMGetPrivateString(LPCTSTR lpszSection, LPCTSTR lpszKeyName, LPCTSTR lpszDef)
{
	TCHAR szBuffer[1024] = {0};
	GetPrivateProfileString(lpszSection, lpszKeyName, lpszDef, szBuffer, 1024, WizKMGetPrivateSettingsFileName());
	//
	return CString(szBuffer);
}

inline BOOL WizKMGetPrivateBool(LPCTSTR lpszSection, LPCTSTR lpszKeyName, BOOL bDef)
{
	return WizKMGetPrivateInt(lpszSection, lpszKeyName, bDef ? 1 : 0) ? TRUE : FALSE;
}


#ifndef _WIZTOOLSDLL_H_
#include "../../WizGlobals/WizToolsDll.h"
#endif

class CWizKMToolsDll : public CWizToolsDll
{
public:
	CWizKMToolsDll()
		: CWizToolsDll(WizKMGetLogFileName(), WizKMGetSettingsFileName())
	{
	}
	HRESULT HtmlGetContentEx(LPCWSTR lpszURL, LPCWSTR lpszHtmlText, CString& strContentHtml)
	{
		CComBSTR bstrContentHtml;
		HRESULT hr = HtmlGetContent(lpszURL, lpszHtmlText, &bstrContentHtml);
		if (FAILED(hr))
			return hr;
		//
		strContentHtml = CString(bstrContentHtml);
		//
		return hr;
	}
	//
	using CWizToolsDll::ShowBubbleWindow;
	using CWizToolsDll::ShowBubbleWindowEx;
	using CWizToolsDll::ShowBubbleWindow2;
	using CWizToolsDll::ShowBubbleWindow2Ex;

	int ShowBubbleWindow(LPCWSTR lpszSubTitle, LPCWSTR lpszIconFileName, LPCWSTR lpszText, LPCWSTR lpszButtonText, int nDelaySeconds, LPCWSTR lpszExtOptions)
	{
		return CWizToolsDll::ShowBubbleWindow(_T("Wiz"), lpszSubTitle, lpszIconFileName, lpszText, lpszButtonText, nDelaySeconds, lpszExtOptions);
	}
	int ShowBubbleWindowDefaultIcon(LPCWSTR lpszSubTitle, LPCWSTR lpszText, LPCWSTR lpszButtonText, int nDelaySeconds, LPCWSTR lpszExtOptions)
	{
		return ShowBubbleWindow(lpszSubTitle, WizKMGetSkinsPath() + _T("Wiz.ico"), lpszText, lpszButtonText, nDelaySeconds, lpszExtOptions);
	}
	//
	BOOL RunScriptInWizShell(HWND hwndParent, LPCTSTR lpszScriptFileName)
	{
		CString strParams = WizFormatString3(_T("\"%1\", WizToolsRunScript2 /HWND=%2 /ScriptFileName=%3"),
			WizGetAppPath() + _T("WizTools.dll"),
			WizInt64ToStr(__int64(hwndParent)),
			lpszScriptFileName
			);
		//
		CString strWizShell2FileName = WizGetAppPath() + _T("WizShell.exe");
		//
		return int(ShellExecute(NULL, _T("open"), strWizShell2FileName, strParams, NULL, SW_SHOW)) > 32;
	}
};



inline CString WizKMGetDatabaseMutexName(LPCTSTR lpszDatabasePath, LPCTSTR lpszAppType)
{
	CString strPath(lpszDatabasePath);
	if (strPath.IsEmpty())
		return CString();
	if (!PathFileExists(strPath))
		return CString();
	//
	strPath = WizGetLongFileName(strPath);
	WizPathAddBackslash(strPath);
	//
	CString strName = CString(lpszAppType) + _T("_") + strPath;
	strName.MakeLower();
	//
	CString strMutexName = _T("WizKM_") + WizMd5StringNoSpace(strName);
	//
	return strMutexName;
}

inline BOOL WizKMIsDatabaseAppRunning(LPCTSTR lpszDatabasePath, LPCTSTR lpszAppType)
{
	CString strMutexName = WizKMGetDatabaseMutexName(lpszDatabasePath, lpszAppType);
	//
	if (HANDLE hMutex =	OpenMutex(SYNCHRONIZE, FALSE, strMutexName))
	{
		DEBUG_TOLOG(WizFormatString3(_T("%1 is running, MutexName=%2, Mutex=%3"), lpszAppType, strMutexName, WizIntToHex(int(hMutex), TRUE)));
		CloseHandle(hMutex);
		return TRUE;
	}
	return FALSE;
}


#define WIZKM_APP_TYPE_SYNC			_T("Sync")
#define WIZKM_APP_TYPE_INDEX		_T("Index")

inline BOOL WizKMIsSyncing(LPCTSTR lpszDatabasePath)
{
	return WizKMIsDatabaseAppRunning(lpszDatabasePath, WIZKM_APP_TYPE_SYNC);
}
inline BOOL WizKMIsIndexing(LPCTSTR lpszDatabasePath)
{
	return WizKMIsDatabaseAppRunning(lpszDatabasePath, WIZKM_APP_TYPE_INDEX);
}

class CWizKMRunningApp
{
public:
	CWizKMRunningApp(LPCTSTR lpszDatabasePath, LPCTSTR lpszAppType)
		: m_hMutex(NULL)
	{
		CString strMutexName = WizKMGetDatabaseMutexName(lpszDatabasePath, lpszAppType);
		//
		m_hMutex = CreateMutex(NULL, TRUE, strMutexName);
		//
		if (m_hMutex != NULL 
			&& GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(m_hMutex);
			m_hMutex = NULL;
		}
		else
		{
			DEBUG_TOLOG(WizFormatString3(_T("%1 running: MutexName=%2, Mutex=%3"), lpszAppType, strMutexName, WizIntToHex(int(m_hMutex), TRUE)));
		}
	}
	virtual ~CWizKMRunningApp()
	{
		if (m_hMutex)
		{
			DEBUG_TOLOG(WizFormatString1(_T("Mutex Closed: Mutex=%1"), WizIntToHex(int(m_hMutex), TRUE)));
			//
			CloseHandle(m_hMutex);
			m_hMutex = NULL;
		}
	}
protected:
	HANDLE m_hMutex;
public:
	BOOL CanContinue()
	{
		return m_hMutex ? TRUE : FALSE;
	}
};

class CWizKMAppRunningSync : public CWizKMRunningApp
{
public:
	CWizKMAppRunningSync(LPCTSTR lpszDatabasePath)
		: CWizKMRunningApp(lpszDatabasePath, WIZKM_APP_TYPE_SYNC)
	{
	}
};
class CWizKMAppRunningIndex : public CWizKMRunningApp
{
public:
	CWizKMAppRunningIndex(LPCTSTR lpszDatabasePath)
		: CWizKMRunningApp(lpszDatabasePath, WIZKM_APP_TYPE_INDEX)
	{
	}
};




inline BOOL WizKMShellRunDll(LPCTSTR lpszDllFileName, LPCTSTR lpszFunctionName, LPCTSTR lpszParams, UINT nShowCommand = SW_SHOW)
{
	CString strExeFileName = WizGetAppPath() + _T("WizShell.exe");
	CString strCommandLine = WizFormatString3(_T("\"%1\", %2 %3"), lpszDllFileName, lpszFunctionName, lpszParams);
	//
	DEBUG_TOLOG(strCommandLine);
	//
	return (int)ShellExecute(NULL, _T("open"), strExeFileName, strCommandLine, NULL, nShowCommand) > 32;
}

inline BOOL WizKMShellSync(LPCTSTR lpszDatabasePath, BOOL bBackground)
{
	if (WizKMIsSyncing(lpszDatabasePath))
		return FALSE;
	//
	CString strParams = WizFormatString2(_T("/DatabasePath=%1 /Background=%2"), lpszDatabasePath, bBackground ? _T("1") : _T("0"));
	//
	return WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMSync"), strParams, SW_SHOW);
}



inline int WizKMShowBubbleWindow(LPCTSTR lpszSubTitle, LPCTSTR lpszText, LPCTSTR lpszCustomButtonText, int nDelay, LPCTSTR lpszExtOptions)
{
	CWizKMToolsDll dll;
	return dll.ShowBubbleWindowDefaultIcon(lpszSubTitle, lpszText, lpszCustomButtonText, nDelay, lpszExtOptions);
}

inline int WizKMShowBubbleWindowTextIsLink(LPCTSTR lpszSubTitle, LPCTSTR lpszText, LPCTSTR lpszCustomButtonText, int nDelay)
{
	return WizKMShowBubbleWindow(lpszSubTitle, lpszText, lpszCustomButtonText, nDelay, _T("/TextIsLink=1"));
}

inline int WizKMShowBubbleWindowTextIsLink(LPCTSTR lpszSubTitle, LPCTSTR lpszText, int nDelay)
{
	return WizKMShowBubbleWindowTextIsLink(lpszSubTitle, lpszText, WizTranslationsTranslateString(_T("View Details")), nDelay);
}


inline int WizKMShowBubbleWindow2(LPCTSTR lpszTitle, LPCTSTR lpszLinkText, LPCTSTR lpszLinkURL, COLORREF crBackground, int nDelay)
{
	CWizKMToolsDll dll;
	return dll.ShowBubbleWindow2(lpszTitle, lpszLinkText, lpszLinkURL, crBackground, nDelay);
}


inline int WizKMShowBubbleWindow2Background(LPCTSTR lpszTitle, LPCTSTR lpszLinkText, LPCTSTR lpszLinkURL, COLORREF crBackground, int nDelay, UINT nFlags = 0)
{
	CString strParams = WizFormatString6(_T("/Title=%1 /LinkText=%2 /LinkURL=%3 /Color=%4 /Delay=%5 /Flags=%6"),
		lpszTitle,
		lpszLinkText,
		lpszLinkURL,
		WizHTMLColorToStringColor(crBackground),
		WizIntToStr(nDelay),
		WizIntToStr(nFlags));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizTools.dll"),
		_T("WizToolsShowBubbleWindow2Ex"),
		strParams);
	//
	return 0;
}


inline BOOL WizKMDownloadAD(LPCTSTR lpszRelatedURL)
{
	CString strVersion = WizGetFileVersion(WizGetAppPath() + _T("WizKMControls.dll"));

	return WizURLADDownloadToXmlFile(WizGetProductName(), lpszRelatedURL, WizKMGetSettingsFileName(), WIZKM_SETTINGS_ROOT_NODE_NAME, strVersion);
}

inline void WizKMClearAD()
{
	CWizXMLDocument doc;
	if (doc.LoadFromFile(WizKMGetSettingsFileName()))
	{
		CWizXMLNode nodeADs;
		if (doc.FindNodeByPath(CString(WIZKM_SETTINGS_ROOT_NODE_NAME) + _T("/Ads/"), nodeADs))
		{
			nodeADs.DeleteAllChild();
			doc.ToUnicodeFile(WizKMGetSettingsFileName());
		}
	}
}

inline CString WizKMGetADSettingsFileName()
{
	CString strPath = WizKMGetSettingsPath() + _T("Files\\");
	WizEnsurePathExists(strPath);
	return strPath + _T("wizadc.ini");
}

inline BOOL WizKMLoadOneADEx(LPCTSTR lpszCategory, WIZHTMLLINKDATA& data)
{
	return WizURLADLoadOneADFromXmlFileEx(WizKMGetSettingsFileName(), lpszCategory, WizKMGetADSettingsFileName(), data);
}

inline BOOL WizKMDisplayOneAD(LPCTSTR lpszCategory)
{
	WIZHTMLLINKDATA data;
	if (!WizKMLoadOneADEx(lpszCategory, data))
		return FALSE;
	//
	CString strText = data.strText;
	int nPos = strText.Find(']');
	if (-1 != nPos)
	{
		strText.Delete(0, nPos + 1);
	}
	//
	CString strCategory = WizTranslationsTranslateString(lpszCategory);
	if (strCategory.IsEmpty())
	{
		strCategory = WizGetProductName();
	}
	//
	int nRet = WizKMShowBubbleWindow2(strCategory, strText, data.strURL, WIZCOLOR_YELLOW, 10);
	if (WIZ_BUBBLE_RESULT_TEXT == nRet)
	{
		WizURLSetClicked(WizKMGetADSettingsFileName(), data.strURL, TRUE);
		return TRUE;
	}
	//
	return TRUE;
}




inline CString WizKMGetMutexName(LPCTSTR lpszProductName, LPCTSTR lpszCommandLine)
{
	CString strDatabasePath = WizGetCommandLineValue(lpszCommandLine, _T("DatabasePath"));
	if (strDatabasePath.IsEmpty())
	{
		strDatabasePath = _T("Default");
	}
	else
	{
		strDatabasePath = WizGetLongFileName(strDatabasePath);
	}
	//
	strDatabasePath.MakeLower();
	//
	CString strMutexName = WizMd5StringNoSpace(CString(lpszProductName) + _T("_") + strDatabasePath);
	return strMutexName;
}



template <class TData>
BOOL WizKMDataArrayIsEqual(const std::vector<TData>& array1, const std::vector<TData>& array2)
{
	if (array1.size() != array2.size())
		return FALSE;
	//
	if (array1.empty())
		return TRUE;
	//
	std::set<CString> set1;
	for (std::vector<TData>::const_iterator it = array1.begin(); it != array1.end(); it++)
	{
		set1.insert(it->strGUID);
	}
	//
	for (std::vector<TData>::const_iterator it = array2.begin(); it != array2.end(); it++)
	{
		if (set1.find(it->strGUID) == set1.end())
			return FALSE;
	}
	//
	return TRUE;
}



inline int WizKMShowTrayIcon(LPCTSTR lpszToolTip, LPCTSTR lpszTitle, LPCTSTR lpszInfo, LPCTSTR lpszIconFileName, int nIconIndex, int nTimeOut)
{
	CString strFileName = WizGetAppPath() + _T("WizKMControls.dll");
	//
	HMODULE hModule = LoadLibrary(strFileName);
	if (!hModule)
		return -1;
	//
	CString strParams = WizFormatString6(_T("/ToolTip=%1 /Title=%2 /Info=%3 /IconFileName=%4 /IconIndex=%5 /TimeOut=%6"),
		lpszToolTip,
		lpszTitle,
		lpszInfo,
		lpszIconFileName,
		WizIntToStr(nIconIndex),
		WizIntToStr(nTimeOut));
	//
	typedef int WINAPI Type_WizKMShowTrayIcon(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow);
	//
	int nRet = 0;
	//
	Type_WizKMShowTrayIcon* fun = (Type_WizKMShowTrayIcon *)GetProcAddress(hModule, "WizKMShowTrayIcon");
	if (fun)
	{
		nRet = fun(NULL, NULL, strParams, 0);
	}
	//
	FreeLibrary(hModule);
	//
	return nRet;
}




inline HRESULT WizKMDocumentUrlToFileName(LPCTSTR lpszSearchPath, size_t nSearchPathLength, LPCTSTR lpszURL, CString& strFileName)
{
	if (lpszURL
		&& *lpszURL
		&& *(lpszURL + 1)
		&& *(lpszURL + 1) == ':'
		&& PathFileExists(lpszURL))
	{
		strFileName = lpszURL;
		return S_OK;
	}
	//
	DWORD dwLen = 1024;
	TCHAR szPath[1024] = {0};
	HRESULT hr = PathCreateFromUrl(lpszURL, szPath, &dwLen, 0);
	if (FAILED(hr))
	{
		TOLOG2(_T("Failed to call PathCreateFromUrl: %1, %2"),  WizIntToHexEx(hr, 8, TRUE), lpszURL);
		return hr;
	}
	//
	CString strPathName = szPath;
	strPathName.Replace(_T('/'), _T('\\'));
	//
	int nPos = strPathName.FindOneOf(_T("#?"));
	if (nPos != -1)
	{
		strPathName = strPathName.Left(nPos);
	}
	//
	CString strLongFileName = WizGetLongFileName(strPathName);
	if (0 == _tcsnicmp(lpszSearchPath, strLongFileName, nSearchPathLength))
	{
		strFileName = strLongFileName;
		return S_OK;
	}
	else
	{
		TOLOG2(_T("File %1 does not in folder %2"), strLongFileName, lpszSearchPath);
		return E_FAIL;
	}
}




template <class T>
inline CComPtr<T> WizKMCreateObject(LPCTSTR lpszDllFileName, CLSID clsid)
{
	return WizCreateObjectAppPath<T>(lpszDllFileName, clsid); 
}

#ifdef __WizKMCore_i_h__

#define WIZKMCORE_DLL_NAME		_T("WizKMCore.dll")

inline CComPtr<IWizDatabase> WizKMCreateDatabase()
{
	return WizKMCreateObject<IWizDatabase>(WIZKMCORE_DLL_NAME, CLSID_WizDatabase);
}

inline CComPtr<IWizSettings> WizKMCreateSettings()
{
	return WizKMCreateObject<IWizSettings>(WIZKMCORE_DLL_NAME, CLSID_WizSettings);
}

inline CComPtr<IWizKMTools> WizKMCreateTools()
{
	return WizKMCreateObject<IWizKMTools>(WIZKMCORE_DLL_NAME, CLSID_WizKMTools);
}

inline CComPtr<IWizTodoItem> WizKMCreateTodoItem()
{
	return WizKMCreateObject<IWizTodoItem>(WIZKMCORE_DLL_NAME, CLSID_WizTodoItem);
}

inline CComPtr<IWizEvent> WizKMCreateEvent()
{
	return WizKMCreateObject<IWizEvent>(WIZKMCORE_DLL_NAME, CLSID_WizEvent);
}


inline CComPtr<IWizTodoItemCollection> WizKMCreateTodoItemCollection()
{
	return WizKMCreateObject<IWizTodoItemCollection>(WIZKMCORE_DLL_NAME, CLSID_WizTodoItemCollection);
}

#endif


#ifdef __WizKMControls_i_h__

#define WIZKMCONTROLS_DLL_NAME		_T("WizKMControls.dll")

inline CComPtr<IWizCommonUI> WizKMCreateCommonUI()
{
	return WizKMCreateObject<IWizCommonUI>(WIZKMCONTROLS_DLL_NAME, CLSID_WizCommonUI);
}

inline CComPtr<IWizProgressWindow> WizKMCreateProgressWindow()
{
	return WizKMCreateObject<IWizProgressWindow>(WIZKMCONTROLS_DLL_NAME, CLSID_WizProgressWindow);
}

inline CComPtr<IWizSyncProgressDlg> WizKMCreateSyncProgressWindow()
{
	return WizKMCreateObject<IWizSyncProgressDlg>(WIZKMCONTROLS_DLL_NAME, CLSID_WizSyncProgressDlg);
}

inline CComPtr<IWizBatchDownloader> WizKMCreateBatchDownloader()
{
	return WizKMCreateObject<IWizBatchDownloader>(WIZKMCONTROLS_DLL_NAME, CLSID_WizBatchDownloader);
}


#endif



#ifdef __WizWebCapture_i_h__

#define WIZWEBPACTURE_DLL_NAME		_T("NPWizWebCapture.dll")

inline CComPtr<IWizIECapture> WizKMCreateIECapture()
{
	return WizKMCreateObject<IWizIECapture>(WIZWEBPACTURE_DLL_NAME, CLSID_WizIECapture);
}

#endif



struct WIZCOMOBJECTDATA
{
	LPCTSTR lpszProgID;
	LPCTSTR lpszClsid;
	LPCTSTR lpszDllFileName;
};

inline const WIZCOMOBJECTDATA* WizKMGetComObjectDataArray()
{
	static const WIZCOMOBJECTDATA data[] =
	{
		{_T("WizKMControls.WizBatchDownloader"),			_T("{8C43A23A-11CD-4BFA-A3FA-CBC4A586F666}"),	_T("WizKMControls.dll")},
		{_T("WizKMControls.WizCommonUI"),					_T("{5EABDAD8-A056-4445-AC98-E66885B0935F}"),	_T("WizKMControls.dll")},
		{_T("WizKMControls.WizProgressWindow"),				_T("{E132C3B7-DA0C-4946-9332-D3D1822FC52C}"),	_T("WizKMControls.dll")},
		{_T("WizKMControls.WizSyncProgressDlg"),			_T("{CDEF75C2-9494-4336-AF33-66980EB65E29}"),	_T("WizKMControls.dll")},

		{_T("WizKMCore.WizDatabase"),						_T("{AB45C39E-7793-4DCE-8C3E-3DA52B07AD68}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDeletedGUID"),					_T("{CDC8B878-61C3-4ECA-AC3B-7B7D8091A89B}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDeletedGUIDCollection"),			_T("{D69D50B6-9A9D-4BD9-AA38-2DDD05579C26}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocument"),						_T("{ED406C6B-C584-4029-B1A9-7FAE0A575C2B}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocumentAttachment"),				_T("{8D95BA68-C8E1-42C2-9287-CC8231C95E7F}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocumentAttachmentCollection"),	_T("{C06B06EA-6E58-4761-BCB0-725EA6A3804D}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocumentCollection"),				_T("{6A94B47D-FD36-452D-952D-E4D550F10628}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocumentParam"),					_T("{8F4F05F7-D3FC-4656-8D3B-B849DA3FB6A6}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizDocumentParamCollection"),		_T("{1B211802-4E90-440D-905E-BF6DD322B135}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizEvent"),							_T("{45BC1CC7-4BDD-4D17-A8F3-DC4CE48FE584}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizEventCollection"),				_T("{83287FD4-35C9-4E6D-83BC-BE341E339B0D}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizFolder"),							_T("{2DE89910-4C9B-4252-9D30-751915121E24}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizFolderCollection"),				_T("{150F936F-26A4-474D-8DD3-811A88F0CB96}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizKMTools"),						_T("{0862A44D-A591-4FAF-950C-EB81BE4AC372}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizMeta"),							_T("{0DC1C265-7695-45F4-8B97-4A4B06C4DE2E}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizMetaCollection"),					_T("{212C4E5C-88B0-477B-B399-A4F7FD3BC034}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizRowset"),							_T("{4D55D9D6-11EF-4816-9079-5C077D8EE864}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizSettings"),						_T("{8BC0154C-BE01-45A6-949D-A4D8E5A0D8AA}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizSettingsSection"),				_T("{A6FFBEDF-C292-4CD7-83DC-CB2779D77483}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizSQLiteDatabase"),					_T("{CD91B37A-6B51-46D1-BC7E-06C0F9F8539D}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizStyle"),							_T("{872DD0F4-D6B6-4730-9087-757B5F66054C}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizStyleCollection"),				_T("{B8B402D3-DE9E-42E5-838B-9BA0B923C16E}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTag"),							_T("{972019A8-D393-4EB3-B271-65E0BBBE2A2E}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTagCollection"),					_T("{95985FE1-9F9E-4F66-8A7D-4CBAEDCF5936}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTagGroup"),						_T("{BA585B1C-9291-49BB-9216-AFDDE648F278}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTagGroupCollection"),				_T("{A9352C86-E046-4868-92B5-D5C84162A69A}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTodoItem"),						_T("{AF6ADB0C-D5CB-4B83-88E8-2CA45BE7873F}"),	_T("WizKMCore.dll")},
		{_T("WizKMCore.WizTodoItemCollection"),				_T("{465102EA-EB28-4758-BA63-C8E177F4F3F2}"),	_T("WizKMCore.dll")},
		
		{_T("WizWebCapture.WizIECapture"),					_T("{ED20B72B-C691-4331-A8D0-FBBB231A5DD4}"),	_T("NPWizWebCapture.dll")},
		//
		{NULL, NULL, NULL},
	};

	return data;
}


inline CString WizKMGetProgIDNoVersion(LPCTSTR lpszProgID)
{
	CString str(lpszProgID);
	int nPos = str.ReverseFind('.');
	if (-1 == nPos)
		return str;
	//
	CString strRight = str.Right(str.GetLength() - nPos - 1);
	if (_ttoi(strRight) != 0)
		return str.Left(nPos);
	//
	return str;
}

inline BOOL WizKMGetComDataByProgID(LPCTSTR lpszProgID, CString& strClsid, CString& strDllName)
{
	CString strProgID = WizKMGetProgIDNoVersion(lpszProgID);
	//
	const WIZCOMOBJECTDATA* pData = WizKMGetComObjectDataArray();
	while (pData->lpszClsid
		&& pData->lpszDllFileName
		&& pData->lpszProgID)
	{
		if (0 == strProgID.CompareNoCase(pData->lpszProgID))
		{
			strClsid = pData->lpszClsid;
			strDllName = pData->lpszDllFileName;
			return TRUE;
		}
		//
		pData++;
	}
	//
	TOLOG1(_T("Failed to get wiz object data by ProgID: %1"), lpszProgID);
	//
	return FALSE;
}

template <class T>
inline CComPtr<T> WizKMCreateObjectByProgID(LPCTSTR lpszProgID)
{
	CString strClsid;
	CString strDllName;
	if (!WizKMGetComDataByProgID(lpszProgID, strClsid, strDllName))
		return NULL;
	//
	CLSID clsid;
	HRESULT hr = ::CLSIDFromString(CComBSTR(strClsid), &clsid);
	if (FAILED(hr))
	{
		TOLOG1(_T("%1 is not a valid guid"), strClsid);
		return NULL;
	}
	//
	return WizCreateObjectAppPath<T>(strDllName, clsid); 
}


class CWizKMLockTempPath
{
public:
	CWizKMLockTempPath()
	{
		SetCount(GetCount() + 1);
	}
	~CWizKMLockTempPath()
	{
		SetCount(GetCount() - 1);
	}
	//
	static LPCTSTR GetValueName()
	{
		static LPCTSTR lpsz = _T("TempCount");
		return lpsz;
	}
	static void SetCount(int nCount)
	{
		::WizRegWriteInt32(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, GetValueName(), nCount);
	}
	static int GetCount()
	{
		int nCount = ::WizRegReadInt32Def(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, GetValueName(), 0);
		if (nCount < 0)
		{
			nCount = 0;
			SetCount(0);
		}
		return nCount;
	}
	static BOOL CanDeleteTempFiles()
	{
		return TRUE;
		return GetCount() <= 0;
	}
};



inline void WizKMWebSiteVisitWithToken(LPCTSTR lpszCommand, LPCTSTR lpszToken)
{
	CString strAtt = WizFormatString1(_T("token=%1"), lpszToken);
	WizKMWebSiteVisit(lpszCommand, WizWebSiteEscapeAtt(strAtt));
}

inline BOOL WizKMHtmlContentRulesUploadAll(long* pnCount = NULL)
{
	CString strURL = WizKMWebSiteGetURL(_T("sharerule"), _T("%html-ruler-data%"));
	//
	CWizKMToolsDll dll;
	HRESULT hr = dll.HtmlContentRulesUploadAll(strURL, pnCount);
	if (FAILED(hr))
		return FALSE;
	//
	return TRUE;
}
inline BOOL WizKMHtmlContentRulesDownloadAll(long* pnCount = NULL)
{
	CString strURL = WizKMWebSiteGetURL(_T("cfrule"), _T("%html-rulers-version%"));
	//
	CWizKMToolsDll dll;
	HRESULT hr = dll.HtmlContentRulesDownloadAll(strURL, pnCount);
	if (FAILED(hr))
		return FALSE;
	//
	return TRUE;
}



inline CString WizKMGetSaveResourceFileExeFileName()
{
	return 	WizGetAppPath() + _T("WizWebCaptureResourceToDocument.exe");
}

inline CString WizKMGetSaveResourceFileCommandLine(LPCTSTR lpszResourceFileName)
{
	CStringA strCommandLine = CStringA("/FileName=") + WizBase64Encode(WizBSTR2STR(CP_UTF8, lpszResourceFileName));
	return CString(strCommandLine);
}
inline void WizKMSaveResourceFile(LPCTSTR lpszResourceFileName)
{
	CString strExeFileName = WizKMGetSaveResourceFileExeFileName();
	//
	CString strCommandLine = WizKMGetSaveResourceFileCommandLine(lpszResourceFileName);
	//
#ifdef _DEBUG
		MessageBox(NULL, CString(strCommandLine), 0, 0);
#endif
	//
	ShellExecute(NULL, _T("open"), strExeFileName, strCommandLine, NULL, SW_SHOW);
}



inline BOOL WizKMTrackAttachment(LPCTSTR lpszDatabasePath, LPCTSTR lpszAttachmentGUID, LPCTSTR lpszAttachmentFileName, HANDLE hProcess)
{
	//
	CString strCommandLine = WizFormatString4(_T("/DatabasePath=%1 /AttachmentGUID=%2 /AttachmentFileName=%3 /ProcessHandle=%4"),
		lpszDatabasePath,
		lpszAttachmentGUID,
		lpszAttachmentFileName,
		WizInt64ToStr(__int64(hProcess)));
	//
	CString strWizShellCommandLine = WizFormatString2(_T("\"%1\", WizKMTrackAttachment %2"),
		WizGetAppPath() + _T("WizKMControls.dll"),
		strCommandLine);
	//
#ifdef _DEBUG
	TOLOG(strWizShellCommandLine);
#endif
	
	//
	return int(ShellExecute(NULL, _T("open"), WizGetAppPath() + _T("WizShell.exe"),
		strWizShellCommandLine, NULL, SW_SHOW)) > 32;
}


#ifdef __ATLAPP_H__

template <class T>
class CWizKMSyncSimpleMessageBase
{
public:
	BEGIN_MSG_MAP(CWizKMSyncSimpleMessageBase)
		MESSAGE_HANDLER(WIZKM_SYNC_PROGRESS, _OnSyncProgress)
		MESSAGE_HANDLER(WIZKM_SYNC_BEGIN, _OnSyncBegin)
		MESSAGE_HANDLER(WIZKM_SYNC_END, _OnSyncEnd)
		MESSAGE_HANDLER(WIZKM_SYNC_STEP, _OnSyncStep)
	END_MSG_MAP()
public:
	LRESULT _OnSyncProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		pT->OnSyncProgress(int(wParam), int(lParam));
		//
		return TRUE;
	}
	LRESULT _OnSyncBegin(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		pT->OnSyncBegin();
		//
		return TRUE;
	}
	LRESULT _OnSyncEnd(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		pT->OnSyncEnd((int)wParam, (UINT)lParam);
		//
		return TRUE;
	}
	LRESULT _OnSyncStep(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		pT->OnSyncStep((int)wParam);
		//
		return TRUE;
	}
	
public:
	void OnSyncStep(int nStep)
	{
	}
	void OnSyncProgress(int nProgress, int nProgressMax)
	{
	}
	void OnSyncBegin()
	{
	}
	void OnSyncEnd(int nExitCode, UINT nFlags)
	{
	}
};

#endif //__ATLAPP_H__


enum WizSortBy 
{
	sortbyDateCreated, 
	sortbyDateModified, 
	sortbyDateAccessed, 
	sortbyTitle, 
	sortbyLocation, 
	sortbyURL, 
	sortbyFileName, 
	sortbyAuthor, 
	sortbyKeywords,
	sortbySize,
	sortbyDataDateModified,
	sortbyReadCount
};


inline WizSortBy WizKMStringToSortBy(LPCTSTR lpszString)
{
	CString str(lpszString);
	if (0 == str.CompareNoCase(_T("DateCreated")))
	{
		return sortbyDateCreated;
	}
	else if (0 == str.CompareNoCase(_T("DateModified")))
	{
		return sortbyDateModified;
	}
	else if (0 == str.CompareNoCase(_T("DataDateModified")))
	{
		return sortbyDataDateModified;
	}
	else if (0 == str.CompareNoCase(_T("DateAccessed")))
	{
		return sortbyDateAccessed;
	}
	else if (0 == str.CompareNoCase(_T("Title")))
	{
		return sortbyTitle;
	}
	else if (0 == str.CompareNoCase(_T("Location")))
	{
		return sortbyLocation;
	}
	else if (0 == str.CompareNoCase(_T("URL")))
	{
		return sortbyURL;
	}
	else if (0 == str.CompareNoCase(_T("FileName")))
	{
		return sortbyFileName;
	}
	else if (0 == str.CompareNoCase(_T("Author")))
	{
		return sortbyAuthor;
	}
	else if (0 == str.CompareNoCase(_T("Keywords")))
	{
		return sortbyKeywords;
	}
	else if (0 == str.CompareNoCase(_T("Size")))
	{
		return sortbySize;
	}
	else if (0 == str.CompareNoCase(_T("ReadCount")))
	{
		return sortbyReadCount;
	}
	//
	//ATLASSERT(FALSE);
	//
	return sortbyDateCreated;
}

inline CString WizKMSortByToString(WizSortBy eSortBy)
{
	switch (eSortBy)
	{
	case sortbyDateModified: 
		return CString(_T("DateModified"));
	case sortbyDataDateModified: 
		return CString(_T("DataDateModified"));
	case sortbyDateAccessed: 
		return CString(_T("DateAccessed"));
	case sortbyTitle: 
		return CString(_T("Title"));
	case sortbyLocation: 
		return CString(_T("Location"));
	case sortbyURL: 
		return CString(_T("URL"));
	case sortbyFileName: 
		return CString(_T("FileName"));
	case sortbyAuthor: 
		return CString(_T("Author"));
	case sortbyKeywords: 
		return CString(_T("Keywords"));
	case sortbySize: 
		return CString(_T("Size"));
	case sortbyReadCount: 
		return CString(_T("ReadCount"));
	default: 
		return CString(_T("DateCreated"));
	}
}




class CWizKMDocumentParamLine
{
public:
	CWizKMDocumentParamLine()
	{
	}
	CWizKMDocumentParamLine(LPCTSTR lpszLine)
	{
		SetLine(lpszLine);
	}
private:
	CWizStdStringArray m_array;
public:
	void SetLine(LPCTSTR lpszLine)
	{
		WizSplitTextToArray(lpszLine, '/', m_array);
	}
	CString GetLine()
	{
		CString str;
		WizStringArrayToText(m_array, str, _T("/"));
		return str;
	}
public:
	CString GetStr(LPCTSTR lpszKey)
	{
		return WizStringArrayGetValue(m_array, lpszKey);
	}
	int GetInt(LPCTSTR lpszKey, int nDef)
	{
		CString str = WizStringArrayGetValue(m_array, lpszKey);
		if (str.IsEmpty())
			return nDef;
		//
		return _ttoi(str);
	}
	BOOL GetBool(LPCTSTR lpszKey, BOOL bDef)
	{
		CString str = WizStringArrayGetValue(m_array, lpszKey);
		if (str.IsEmpty())
			return bDef;
		//
		return _ttoi(str) ? TRUE : FALSE;
	}
	COLORREF GetColor(LPCTSTR lpszKey, COLORREF crDef)
	{
		CString str = WizStringArrayGetValue(m_array, lpszKey);
		if (str.IsEmpty())
			return crDef;
		//
		return WizStringToColor(str);
	}
	COleDateTime GetTime(LPCTSTR lpszKey, const COleDateTime& tDef)
	{
		CString str = WizStringArrayGetValue(m_array, lpszKey);
		if (str.IsEmpty())
			return tDef;
		//
		return WizStringToDateTime(str);
	}
	//
	void AddStr(LPCTSTR lpszKey, LPCTSTR lpszValue)
	{
		m_array.push_back(CString(lpszKey) + _T("=") + lpszValue);
	}
	void AddInt(LPCTSTR lpszKey, int n)
	{
		AddStr(lpszKey, WizIntToStr(n));
	}
	void AddBool(LPCTSTR lpszKey, BOOL b)
	{
		AddInt(lpszKey, b ? 1 : 0);
	}
	void AddColor(LPCTSTR lpszKey, COLORREF cr)
	{
		AddStr(lpszKey, WizColorToString(cr));
	}
	void AddTime(LPCTSTR lpszKey, const COleDateTime& t)
	{
		AddStr(lpszKey, WizTimeToSQL(t));
	}
};




inline BOOL WizKMRegularTagsText(CString& strText)
{
	strText.Replace(L',', L';');
	strText.Replace(L'£¬', L';');
	strText.Replace(L'£»', L';');
	strText.Trim(_T("; "));
	//
	return TRUE;
}

