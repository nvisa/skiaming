#pragma once

#ifndef __ATLCOMTIME_H__
#include <atlcomtime.h>
#endif


#ifndef _MAP_
#include <map>
#endif	

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _SET_
#include <set>
#endif

#ifndef __msxml2_h__
#include <msxml2.h>
#endif

#ifndef _INC_SHELLAPI
#include <shellapi.h>
#endif

#ifndef _INC_SHLWAPI
#include <shlwapi.h>
#endif

#define WIZ_HTML_RESOURCEFILE_PATH		_T("%ResourceFilePath%/")

interface IWizGlobal
{
	virtual void WriteLog(LPCTSTR lpszMsg) = 0;
	virtual CString GetTempPath() = 0;
	virtual BOOL IsWizResourceURL(LPCTSTR lpszURL) = 0;
	virtual void OnURLDownloadToFileProgress(ULONG ulProgress, ULONG ulProgressMax, LPCWSTR wszStatusText) = 0;
	virtual CString GetProductName() = 0;
	//
	virtual CString GetSettingsFileName();
	virtual void WriteDebugLog(LPCTSTR lpszMsg);
};

interface IWizGlobal2
{
	virtual CString GetCommonString(LPCTSTR lpszStringName) = 0;
};

interface IWizGlobal3
{
	virtual CString GetHTMLGetSentenceFileName() = 0;				//HTMLGetSentence
	virtual CString GetEncryptSystemKeyFileName() = 0;				//CyberArticle.ini
	virtual CString GetEncryptSystemSourceKeyFileName() = 0;		//CyberArticle.exe
};


class CWizGlobalDefault : public IWizGlobal
{
public:
	CWizGlobalDefault(BOOL bClearTempFiles = FALSE);
	virtual ~CWizGlobalDefault();
protected:
	CString m_strProductName;
	CString m_strTempPath;
	BOOL m_bClearTempFiles;
public:
	virtual void WriteLog(LPCTSTR lpszMsg);
	virtual CString GetTempPath();
	virtual BOOL IsWizResourceURL(LPCTSTR lpszURL);
	virtual void OnURLDownloadToFileProgress(ULONG ulProgress, ULONG ulProgressMax, LPCWSTR wszStatusText);
	virtual CString GetProductName();
};


IWizGlobal* WizGlobal();
IWizGlobal2* WizGlobal2();
IWizGlobal3* WizGlobal3();

#ifdef _UNICODE
typedef std::vector<CString> CWizStdStringArray;
#else
typedef std::vector<CStringW> CWizStdStringArray;
#endif


UINT WizGetCodePageFromLCID(LCID lcid);
//
LCID WizTranslationsMapLCID(LCID lcid);
CString WizTranslationsGetLCIDName(LCID lcid);
//
LCID WizTranslationsGetCurrentMappedLCID();
//
BOOL WizTranslationsSetCurrentMappedLCID(LCID lcid);
//
BOOL WizTranslationsIsUsingDefaultResource();
//
BOOL WizTranslationsEnumSupportedLanguages(std::vector<LCID>& arrayLCIDs);
//
//
CString WizTranslationsGetResourcesBasePath();
CString WizTranslationsGetResourcesPath();
BOOL WizTranslationsInit();
BOOL WizTranslationsInitByText(LPCTSTR lpszText);
BOOL WizTranslationsInitByResourceDirect(LPCTSTR lpszResourceType, LPCTSTR lpszResourceName);
BOOL WizTranslationsInitByResource(LPCTSTR lpszProductName, LPCTSTR lpszResourceType);

BOOL WizTranslationsAddResourceFile(LPCTSTR lpszFileName);
//
BOOL WizTranslationsLoadString(UINT nID, CString& strRet);
CString WizTranslationsLoadString(UINT nID);
//
BOOL WizTranslationsTranslateString(LPCTSTR lpszSrc, CString& strRet);
CString WizTranslationsTranslateString(LPCTSTR lpszSrc);
//
BOOL WizTranslationsTranslateWindow(HWND hWnd);
BOOL WizTranslationsTranslatePropertySheet(HWND hWnd);
BOOL WizTranslationsTranslateMenu(HMENU hMenu);

int WizMenuCommandToIndex(HMENU hMenu, UINT nCommand);
int WizMenuGetSubMenuIndex(HMENU hMenu, UINT nSubMenuNimber);
void WizMenuRemoveMultiSeparator(HMENU hMenu);
BOOL WizMenuIsSeparator(HMENU hMenu, int nIndex);



BOOL WizEnsurePathExists(LPCTSTR lpszPath);
BOOL WizEnsurePathExistsEx(LPCTSTR lpszPath);
BOOL WizCmdLineToFileName(LPTSTR lpszCmdLine);
BOOL WizIsFileName(LPCTSTR lpszFileName);

BOOL WizIsValidFileNameNoPath(LPCTSTR lpszFileName);
void WizMakeValidFileNameNoPath(CString& strFileName);
void WizMakeValidFileNameNoPathLimitLength(CString& strFileName, int nMaxTitleLength);
void WizMakeValidFileNameNoPathLimitFullNameLength(CString& strFileName, int nMaxFullNameLength);
CString WizMakeValidFileNameNoPathReturn(LPCTSTR lpszFileName);
size_t WizGetFileSize(LPCTSTR lpszFileName);
COleDateTime WizGetFileModifiedTime(LPCTSTR lpszFileName);
COleDateTime WizGetFileCreatedTime(LPCTSTR lpszFileName);

CString WizIntToStr(int n);
CString WizInt64ToStr(__int64 n);
CString WizDateToLocalString(const COleDateTime& t);
CString WizDateToLocalStringLongDate(const COleDateTime& t);
CString WizTimeToLocalString(const COleDateTime& t, BOOL bNoSec = FALSE);
CString WizDateTimeToLocalString(const COleDateTime& t, BOOL bNoSec = FALSE);
CString WizDateTimeToLocalStringLongDate(const COleDateTime& t, BOOL bNoSec = FALSE);
#ifndef WINCE
CString WizAsciiTime(const time_t t);
#endif
CString WizExtractFilePath(LPCTSTR lpszFileName);
CString WizExtractFileName(LPCTSTR lpszFileName);
CString WizExtractFileExt(LPCTSTR lpszFileName);
CString WizReplaceFileExt(LPCTSTR lpszFileName, LPCTSTR lpszNewExt);
CString WizExtractFileTitle(LPCTSTR lpszFileName);
CString WizGetModulePath(HMODULE hModule);
CString WizIntToHex(int n, BOOL bWithPrefix = FALSE);
CString WizIntToHexEx(int n, int nWidth, BOOL bWithPrefix = FALSE);
int WizHexToInt(LPCTSTR lpszText);
CString WizIntToByteSizeStr(int n);
CString WizFormatNumber(LPCTSTR lpszNumber, int nFracDigits);
CString WizFormatInt(int nVal);

#define			WIZ_LTFF_FORCE_HTML				0x01
#define			WIZ_LTFF_FORCE_UTF8				0x02
#define			WIZ_LTFF_FORCE_UTF16			0x04
#define			WIZ_LTFF_NO_REMOVE_CR			0x08
#define			WIZ_LTFF_FORCE_XML				0x10

BOOL WizLoadUnicodeTextFromBuffer(const char* pBuffer, size_t nLen, CStringW& strText, UINT nFlags = 0 , UINT nDefaultCodePage = 0, LPCTSTR lpszFileName = NULL);
BOOL WizLoadUnicodeTextFromFileEx(LPCTSTR lpszFileName, CStringW& strText, UINT nFlags = 0, UINT nDefaultCodePage = 0);

BOOL WizLoadUnicodeTextFromFile(LPCTSTR lpszFileName, CStringW& strText);
BOOL WizLoadUnicodeTextFromFileForceHTML(LPCTSTR lpszFileName, CStringW& strText);
BOOL WizLoadUnicodeTextFromFileNoRemoveCR(LPCTSTR lpszFileName, CStringW& strText);

#define WIZ_LATFAF_NO_LOAD_UTF8		0x01		
#define WIZ_LATFAF_NO_REMOVE_CR		0x08

BOOL WizLoadAnsiTextFromAnsiFileEx(LPCTSTR lpszFileName, CStringA& strText, UINT nFlags = 0);

BOOL WizLoadAnsiTextFromAnsiFileNoRemoveCR(LPCTSTR lpszFileName, CStringA& strText);

#define WIZ_FT_ANSI			1
#define WIZ_FT_UTF_8		2
#define WIZ_FT_UTF_16		3

UINT WizGetFileType(LPCTSTR lpszFileName);
BOOL WizLfToCrLf(LPCWSTR lpszText, CStringW& wstrText);
BOOL WizSaveUnicodeTextToUnicodeFile(LPCTSTR lpszFileName, LPCWSTR lpszText);
BOOL WizSaveUnicodeTextToUnicodeFileStream(IStream* pStream, LPCWSTR lpszText);
BOOL WizSaveAnsiTextToAnsiFile(LPCTSTR lpszFileName, LPCSTR lpszText, BOOL bBinary = FALSE, BOOL bAddUTF8Sing = FALSE);
BOOL WizSaveUnicodeTextToUnicodeFile(HANDLE hFile, LPCWSTR lpszText);
CString WizPasswordToMd5String(LPCTSTR lpszPassword);
CString WizPasswordToMd5StringNoSpace(LPCTSTR lpszPassword);
BOOL WizSaveBufferToFile(const BYTE* pBuffer, size_t nSize, LPCTSTR lpszFileName);
CString WizGenGUID();
CString WizGenGUIDLowerCaseLetterOnly();
BOOL WizHGlobalToUnicodeText(HGLOBAL hGlobal, CStringW& strText);
void WizPathAddBackslash(CString& strPath);
CString WizGetLongFileName(LPCTSTR lpszFileName);
CString WizGetShortFileName(LPCTSTR lpszFileName);
CString WizGetAppFileName();
CString WizGetAppPath();
void WizProcessMessages();
CString WizGetMyDocumentsPath();
CString WizGetAppDataPath();
CString WizGetAppDataLowPath();
CString WizGetUserPrfofilePath();


HGLOBAL WizUnicodeTextToHGlobal(LPCWSTR lpszText);
void WizPathRemoveBackslash(CString& strPath);
CString WizExtractPathLastSubDir(LPCTSTR lpszPath);
void WizPathRemoveLastSubFolder(CString& strPath);
BOOL WizClipboardHGlobalToText(HGLOBAL hGlobal, CString& strText, BOOL bUnicode);
BOOL WizGetClipboardUnicodeText(CString& strText);
BOOL WizGetClipboardAnsiText(CString& strText);
BOOL WizGetClipboardText(CString& strText);
void WizGetNextFileName(CString& strFileName);
void WizGetNextPathName(CString& strPath);
CString WizGetErrorMessage(UINT nError);
CString WizGetLastErrorMessage();
//
CString WizFormatStringEx0(UINT nID);
CString WizFormatString0(UINT nID);
CString WizFormatString1(LPCTSTR lpszFormat, LPCTSTR lpszParam1);
CString WizFormatString1(UINT nID, LPCTSTR lpszParam1);
CString WizFormatString2(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2);
CString WizFormatString2(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2);
CString WizFormatString3(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3);
CString WizFormatString3(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3);
CString WizFormatString4(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4);
CString WizFormatString4(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4);
CString WizFormatString5(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5);
CString WizFormatString5(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5);
CString WizFormatString6(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6);
CString WizFormatString6(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6);
CString WizFormatString7(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7);
CString WizFormatString7(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7);
CString WizFormatString8(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8);
CString WizFormatString8(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8);
CString WizFormatString9(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8, LPCTSTR lpszParam9);
void WizAppendErrorCode(CString& strMsg, UINT nCode);
int WizMessageBox(LPCTSTR lpszText, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizMessageBox(UINT nFormatID, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizMessageBox1(LPCTSTR lpszText, LPCTSTR lpszParam1, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizMessageBox1(UINT nFormatID, LPCTSTR lpszParam1, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizMessageBox2(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizMessageBox3(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, UINT nType = MB_OK | MB_ICONINFORMATION, HWND hwnd = NULL);
int WizErrorMessageBox(LPCTSTR lpszText, UINT nErrorCode = 0, HWND hwnd = NULL);
int WizErrorMessageBox(UINT nFormatID, UINT nErrorCode = 0, HWND hwnd = NULL);
int WizErrorMessageBox1(LPCTSTR lpszText, LPCTSTR lpszParam1, UINT nErrorCode = 0, HWND hwnd = NULL);
int WizErrorMessageBox1(UINT nFormatID, LPCTSTR lpszParam1, UINT nErrorCode = 0, HWND hwnd = NULL);
int WizErrorMessageBox2(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, UINT nErrorCode = 0, HWND hwnd = NULL);
int WizErrorMessageBox3(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, UINT nErrorCode = 0, HWND hwnd = NULL);
#ifndef WINCE
BOOL WizSelectFolder(HWND hWnd, LPCTSTR lpszTitle, CString& strRet);
BOOL WizSelectFolder(HWND hWnd, UINT nID, CString& strRet);
#endif
BOOL WizConvertStringFromUTF8(const char* lpszUTF8Text, CString& strText);
BOOL WizConvertStringToUTF8(const LPCWSTR lpszUnicodeText, CStringA& strText);
BOOL WizHTMLTextIsLink(LPCTSTR lpszText);
void WizShellOpenFileWith(LPCTSTR lpszFileName);

enum WIZSYSTEMVERSION
{
	svUnknown,
	svWin32s,
	svWin95,
	svWin98,
	svWinME,
	svWinNT,
	svWin2000,
	svWinXP,
	svWin2003,
	svWinVista,
	svWin7,
	svHigher
};

WIZSYSTEMVERSION WizGetSystemVersion();
BOOL WizIsVista();
BOOL WizMd5File(LPCTSTR lpszFileName, DWORD arrayMd5[4]);
CString WizMd5FileString(LPCTSTR lpszFileName);
CString WizGetSystemPath();
CString WizGetWindowsPath();
CString WizGetSystemTempPath();
CString WizGetProgramFilesPath();
BYTE WizGetAccelVirt(LPCTSTR lpsz);
int WizComparePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2);
#ifndef WINCE
WORD WizGetAccelKey(LPCTSTR lpsz);
WORD WizGetHotKeyModifiers(LPCTSTR lpsz);
WORD WizGetHotKeyKey(LPCTSTR lpsz);
#endif
HRESULT WizGetErrorInfo(HRESULT hrReturned, IErrorInfo* pIErrorInfo, CString& strError);

CString WizGetComputerName();

void WizDeleteAllFilesInFolder(LPCTSTR lpszPath);
void WizDeleteFolder(LPCTSTR lpszPath);

void WizMd5(const BYTE* pBuffer, DWORD dwLen, BYTE* pResult);
BOOL WizMd5(IStream* pStream, BYTE* pResult);
CString WizMd5String(const BYTE* pBuffer, DWORD dwLen);
CString WizMd5String(IStream* pStream);
CString WizMd5StringNoSpace(const BYTE* pBuffer, DWORD dwLen);
CString WizMd5StringNoSpace(IStream* pStream);
CString WizMd5StringNoSpaceJava(const BYTE* pBuffer, DWORD dwLen);
CString WizMd5StringNoSpaceJava(IStream* pStream);
CString WizMd5StringNoSpace(LPCTSTR lpszText);

#define TOLOG(x)		WizGlobal()->WriteLog(x)
#define TOLOG1(x, p1)		WizGlobal()->WriteLog(WizFormatString1((x), (p1)))
#define TOLOG2(x, p1, p2)		WizGlobal()->WriteLog(WizFormatString2((x), (p1), (p2)))
#define TOLOG3(x, p1, p2, p3)		WizGlobal()->WriteLog(WizFormatString3((x), (p1), (p2), (p3)))
#define TOLOG4(x, p1, p2, p3, p4)		WizGlobal()->WriteLog(WizFormatString4((x), (p1), (p2), (p3), (p4)))

#define DEBUG_TOLOG(x)		WizGlobal()->WriteDebugLog(x)
#define DEBUG_TOLOG1(x, p1)		WizGlobal()->WriteDebugLog(WizFormatString1((x), (p1)))
#define DEBUG_TOLOG2(x, p1, p2)		WizGlobal()->WriteDebugLog(WizFormatString2((x), (p1), (p2)))
#define DEBUG_TOLOG3(x, p1, p2, p3)		WizGlobal()->WriteDebugLog(WizFormatString3((x), (p1), (p2), (p3)))
#define DEBUG_TOLOG4(x, p1, p2, p3, p4)		WizGlobal()->WriteDebugLog(WizFormatString4((x), (p1), (p2), (p3), (p4)))

#define EF_INCLUDEHIDDEN			0x01
#define EF_INCLUDESUBDIR			0x02

void WizEnumFiles(LPCTSTR lpszPath, LPCTSTR lpszExts, CWizStdStringArray& arrayFiles, UINT uFlags);
void WizEnumFolders(LPCTSTR lpszPath, CWizStdStringArray& arrayFolders, UINT uFlags);

BOOL WizRegReadString(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  LPTSTR pszValue, DWORD dwLen);
BOOL WizRegReadInt32(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  int& nValue);
BOOL WizRegReadInt64(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  __int64& nValue);
BOOL WizRegReadBool(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL& bValue);
BOOL WizRegReadBin(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BYTE* pBuffer, DWORD dwLen);
BOOL WizRegReadPtr(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t& ptr);
BOOL WizRegWriteString(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, LPCTSTR lpszValue);
BOOL WizRegWriteInt32(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, int nValue);
BOOL WizRegWriteInt64(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, __int64 nValue);
BOOL WizRegWriteBool(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL bVal);
BOOL WizRegWriteBin(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BYTE* pBuffer, DWORD dwLen);
BOOL WizRegWritePtr(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t ptr);
BOOL WizRegDeleteValue(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName);
CString WizRegReadStringDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, LPCTSTR lpszDefault);
int WizRegReadInt32Def(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, int nDefault);
__int64 WizRegReadInt64Def(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, __int64 nDefault);
BOOL WizRegReadBoolDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL bDefault);
intptr_t WizRegReadPtrDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t nDef);
BOOL WizRegKeyExists(HKEY hRootKey, LPCTSTR lpszKey);
BOOL WizRegCreateKey(HKEY hRootKey, LPCTSTR lpszKey);
BOOL WizRegValueExists(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName);
#ifndef WINCE
BOOL WizRegDeleteKey(HKEY hRootKey, LPCTSTR lpszKey);
#endif
BOOL WizRegEnumKey(HKEY hRootKey, LPCTSTR lpszKey, CWizStdStringArray& arrayKeyNames);
BOOL WizRegEnumValueName(HKEY hRootKey, LPCTSTR lpszKey, CWizStdStringArray& arrayValueNames);

LPTSTR WizStrStrI_Ptr(LPCTSTR lpsz1, LPCTSTR lpsz2);
LPTSTR WizStrRStrI_Ptr(LPCTSTR lpsz1, LPCTSTR lpsz2);
LPCSTR WizStrRStrI_PtrA(LPCSTR lpsz1, LPCSTR lpsz2);
LPSTR WizStrStrI_PtrA(LPCSTR lpsz1, LPCSTR lpsz2);
LPTSTR WizStrStrI_Ptr2(LPCTSTR lpsz1, size_t nLen, LPCTSTR lpsz2);
BOOL WizIsSameChar(TCHAR ch1, TCHAR ch2);
BOOL WizIsSpaceChar(TCHAR ch);
LPCTSTR WizTrimLeft(LPCTSTR lpsz);
size_t WizReplaceChar(LPTSTR lpsz, TCHAR chFind, TCHAR chReplace);
ptrdiff_t WizStrStrI_Pos(const CString& strText, const CString& strFind, ptrdiff_t nBegin = 0);
ptrdiff_t WizStrRStrI_Pos(const CString& strText, const CString& strFind, ptrdiff_t nBegin = 0);
ptrdiff_t WizStrStrI_PosA(const CStringA& strText, const CStringA& strFind, ptrdiff_t nBegin = 0);
ptrdiff_t WizStrRStrI_PosA(const CStringA& strText, const CStringA& strFind, ptrdiff_t nBegin = 0);
void WizStringRemoveAllSpace(CString& strText);
CString WizStringReplace(LPCTSTR lpszText, LPCTSTR lpszFind, LPCTSTR lpszReplace);
CString WizStringReplace(LPCTSTR lpszText, TCHAR chFind, TCHAR chReplace);
int WizStringReplaceNoCase(CString& str, LPCTSTR lpszFind, LPCTSTR lpszReplaceWith, BOOL bReplaceAll = TRUE);
void WizLimitText(CString& strText, int nMaxLength);
CString WizSubString(LPCTSTR lpszText, ptrdiff_t nBegin, size_t nCount);
CStringA WizSubStringA(LPCSTR lpszText, ptrdiff_t nBegin, size_t nCount);

BOOL WizSplitTextToArray(const CStringW& strText, WCHAR ch, CWizStdStringArray& arrayResult);
int WizSplitTextCompareString(LPCWSTR lpszText1, LPCWSTR lpszText2, BOOL bMatchCase);
int WizSplitTextFindString(LPCWSTR lpszText, LPCWSTR lpszFind, BOOL bMatchCase);
BOOL WizSplitTextToArray(CStringW strText, LPCWSTR lpszSplitterText, BOOL bMatchCase, CWizStdStringArray& arrayResult);
BOOL WizSplitTextToArray(LPCWSTR lpszText, WCHAR ch, CWizStdStringArray& arrayResult);
int WizFindInArray(const CWizStdStringArray& arrayText, LPCWSTR lpszFind);
int WizFindInArrayNoCase(const CWizStdStringArray& arrayText, LPCWSTR lpszFind);
void WizStringArrayToText(const CWizStdStringArray& arrayText, CStringW& strText, LPCWSTR lpszSplitter = L"\r\n");
void WizStringArrayEraseEmptyLine(CWizStdStringArray& arrayText);
void WizStringArraySort(CWizStdStringArray& arrayText, BOOL bAscending = TRUE);
void WizStringArrayRemoveMultiElement(CWizStdStringArray& arrayText);
void WizStringArrayRemoveMultiElementNoCase(CWizStdStringArray& arrayText);
BOOL WizStringArrayMatchAllText(LPCTSTR lpszText, const CWizStdStringArray& arrayText, BOOL bMatchCase);
CStringW WizStringArrayGetValue(const CWizStdStringArray& arrayText, LPCWSTR lpszValueName);
BOOL WizStringArraySetValue(CWizStdStringArray& arrayText, LPCWSTR lpszValueName, LPCWSTR lpszValue);
void WizStringArrayGetAllValueName(const CWizStdStringArray& arrayText, CWizStdStringArray& arrayValueName);
BOOL WizStringArrayLoadFromFile(LPCTSTR lpszFileName, CWizStdStringArray& arrayText);
BOOL WizStringArraySaveToUnicodeFile(LPCTSTR lpszFileName, const CWizStdStringArray& arrayText, LPCWSTR lpszSplitter = L"\r\n");
BOOL WizStringArrayCombineFile(LPCTSTR lpszFileName1, LPCTSTR lpszFileName2, LPCTSTR lpszFileNameResult);


CString WizGetAppSettingsFileName();
CString WizGetSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDef);


CString WizGetSecuteSettingsFileName();
CString WizGetSecuteSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bAllowEmpty);
CString WizGetProductName();
CString WizGetCompanyName();

CString WizInnerGetSecuteSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bAllowEmpty);

//
BOOL WizStrToWindows(CString& str);
BOOL WizStrToUnix(CString& str);


#ifdef WINCE
#include "WizCEHelper.h"
#endif

COleDateTime WizGetCurrentTime();
BOOL WizStringToDateTime(LPCTSTR lpsz, COleDateTime& t, CString& strError);

BOOL WizStringToDateTime(LPCTSTR lpsz, COleDateTime& t);
COleDateTime WizStringToDateTime(LPCTSTR lpsz);
CString WizDateTimeToString(COleDateTime t);
#ifndef _WIN32_WCE
CString WizDateTimeToString(time_t t);
#endif
CString WizColorToString(COLORREF cr);
COLORREF WizStringToColor(LPCTSTR sz);
CString WizStringToSQL(const CString& str, LPCTSTR lpszPrefix = NULL);
CString WizStringToSQL(LPCTSTR lpszStr, LPCTSTR lpszPrefix = NULL);
CString WizTimeToSQL(const COleDateTime& t);
CString WizColorToSQL(COLORREF cr);
#ifndef _WIN32_WCE
CString WizTimeToSQL(time_t t);
#endif

BOOL WizIso8601StringToDateTime(LPCTSTR lpsz, COleDateTime& t, CString& strError);
CString WizDateTimeToIso8601String(const COleDateTime& t);
int WizGetFirstDayOfWeek();
int WizGetLastDayOfWeek();
CString WizGetDayOfWeekLongName(int nLocaleDayOfWeek);
CString WizGetDayOfWeekShortName(int nLocaleDayOfWeek);
CString WizGetMonthShortName(int nMonth);
CString WizGetMonthLongName(int nMonth);
int WizCOleDateTimeDayOfWeekToLocalDayOfTime(int nCOleDateTimeDayOfWeek);
int WizCOleDateTimeDayOfWeekFromLocalDayOfTime(int nLocalDayOfWeek);
#ifndef _WIN32_WCE
time_t WizTimeGetTimeT(const COleDateTime& t);
#endif


class CWizTockCounter
{
	CString m_strName;
	DWORD m_dwBegin;
public:
	CWizTockCounter(LPCTSTR lpszName);
	~CWizTockCounter();
};

#ifdef _DEBUG
#define WIZCALTICK(x)   CWizTockCounter __tick(x)
#else
#define WIZCALTICK(x)   
#endif

class CWizCallTrace
{
	CString m_strFunctionName;
public:
	CWizCallTrace(LPCTSTR lpszFunctionName);
	~CWizCallTrace();
};

#ifdef _DEBUG
#define WIZCALLTRACE(x)		CWizCallTrace __wizcalltrace(x)
#else
#define WIZCALLTRACE(x)
#endif


const UINT WIZ_UM_PARENT_SIZED = ::RegisterWindowMessage(_T("WIZ_UM_PARENT_SIZED"));


CString WizIniReadStringDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDefaultValue = NULL);
#ifndef WINCE
BOOL WizIniWriteString(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszValue);
BOOL WizIniWriteInt(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, int nValue);
#endif

int WizIniReadIntDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, int nDefaultValue = 0);
BOOL WizIniReadBoolDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bDefaultValue = FALSE);
BOOL WizIniReadArray(LPCTSTR lpszFileName, LPCTSTR lpszSection, CWizStdStringArray& arrayData);
#ifndef WINCE
BOOL WizIniReadSection(LPCTSTR lpszFileName, LPCTSTR lpszSection, DWORD dwSize, CWizStdStringArray& arrayData);
#endif



CString WizGetHomeURL();
CString WizGetHomeURLBase();
CString WizGetSupportEmail();
CString WizGetAPIURL();
CString WizWebSiteVisitGetURL(LPCTSTR lpszProduct, LPCTSTR lpszLanguage, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo);
void WizWebSiteVisit(LPCTSTR lpszProduct, LPCTSTR lpszLanguage, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo);
void WizWebSiteVisit(LPCTSTR lpszProduct, LCID lcid, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo);
CString WizWebSiteGetReturn(LPCTSTR lpszProduct, LCID lcid, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo);
CString WizWebSiteGetProductHomeURL();
CString WizWebSiteGetHome();
CString WizWebSiteEscapeAtt(LPCTSTR lpszAtt);
CString WizGetRegKeyRoot();

class CWizIniFileEx
{
public:
	CWizIniFileEx(void);
	virtual ~CWizIniFileEx(void);
public:
	BOOL LoadFromUTF8File(LPCTSTR lpszFileName);
	BOOL LoadFromFile(LPCTSTR lpszFileName);
	BOOL LoadFromText(LPCTSTR lpszText);
	BOOL SaveToUnicodeFile(LPCTSTR lpszFileName);
	void ToText(CString& strText);
private:
	CWizStdStringArray m_arrayText;
public:
	void Clear() { m_arrayText.clear(); }
	int GetIntDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, int nDefValue) const;
	double GetDoubleDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, double nDefValue) const;
	BOOL GetBoolDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bDefValue) const;
	CString GetStringDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDefValue = NULL) const;
	void SetString(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszValue);
	void SetInt(LPCTSTR lpszSection, LPCTSTR lpszValueName, int nVal);
	void SetBool(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bVal);
	CString GetLocalString(LPCTSTR lpszSection, LPCTSTR lpszStringName);
	CString GetLocalString(LPCTSTR lpszStringName);
	void GetSectionNames(CWizStdStringArray& arraySectionName);
	void GetSection(LPCTSTR lpszSection, CWizStdStringArray& arrayData);
	void GetArray(LPCTSTR lpszSection, CWizStdStringArray& arrayData);
	//
	void AppendArray(LPCTSTR lpszSection, const CWizStdStringArray& arrayData);
	//
	BOOL ValueExists(LPCTSTR lpszSection, LPCTSTR lpszValueName);
};


CStringA WizBase64Encode(const BYTE* pBuffer, int nLen);
BOOL WizBase64Decode(const char* lpszText, BYTE* pResult, int& nResultLen);
BOOL WizBase64Encode(IStream* pStream, CStringA& strText);
BOOL WizBase64Encode(const char* lpszText, CStringA& strText);
CStringA WizBase64Encode(const char* lpszText);
BOOL WizBase64Decode(const char* lpszText, IStream* pStream);
BOOL WizBase64DecodeToText(const char* lpszText, CStringA& strResult);
BOOL WizBase64DecodeToUnicodeText(const char* lpszText, LPCTSTR lpszCharset, CStringW& strResult);
CStringW WizBase64DecodeToUnicodeText(const char* lpszText, LPCTSTR lpszCharset);
CStringA WizBase64EncodeInline(LPCTSTR lpszCharset, LPCWSTR lpszText);
CStringA WizBase64EncodeUnicodeText(const wchar_t* lpszText);
CStringW WizBase64DecodeUnicodeText(const char* lpszText);
//
CStringA WizQPEncode(const BYTE* pBuffer, int nLen);
BOOL WizQPDecode(const char* lpszText, BYTE* pResult, int& nResultLen);
BOOL WizQPEncode(IStream* pStream, CStringA& strText);
BOOL WizQPDecode(const char* lpszText, IStream* pStream);
BOOL WizQPDecodeToText(const char* lpszText, CStringA& strResult);

BOOL WizBase64EncodeFile(LPCTSTR lpszFileName, CStringA& strText);


const UINT WIZ_UM_CLOSE_WINDOW_FOR_AUTO_UPDATE	= ::RegisterWindowMessage(_T("WIZ_UM_CLOSE_WINDOW_FOR_AUTO_UPDATE"));



interface IWizSettingsBase
{
public:
	virtual ~IWizSettingsBase();
public:
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue) = 0;
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue) = 0;
public:
	CString GetStr(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDef = NULL);
	int GetInt(LPCTSTR lpszSection, LPCTSTR lpszKey, int nDef = 0);
	BOOL GetBool(LPCTSTR lpszSection, LPCTSTR lpszKey, BOOL bDef = FALSE);
	BOOL SetStr(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpsz);
	BOOL SetInt(LPCTSTR lpszSection, LPCTSTR lpszKey, int n);
	BOOL SetBool(LPCTSTR lpszSection, LPCTSTR lpszKey, BOOL b);
	virtual BOOL ClearSection(LPCTSTR lpszSection);
	virtual BOOL GetStringArray(LPCTSTR lpszSection, CWizStdStringArray& arrayText);
	virtual BOOL SetStringArray(LPCTSTR lpszSection, const CWizStdStringArray& arrayText);
};

class CWizEmptySettings : public IWizSettingsBase
{
public:
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue);
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue);
};

#ifdef __ATLCTRLS_H__

struct WIZNAMEDIMAGELISTICONDATA
{
	LPCTSTR lpszName;
	UINT nIconID;
};

#define WIZNAMEDIMAGELIST_ICON_BEGIN(x)		static WIZNAMEDIMAGELISTICONDATA x[] = \
	{
#define WIZNAMEDIMAGELIST_ICON(name, id)	{name, id},
#define WIZNAMEDIMAGELIST_ICON_END()			{NULL, 0},\
	};


class CWizNamedImageList : public CImageList
{
public:
	typedef std::map<CString, int> CNameIndexMap;
protected:
	CNameIndexMap m_mapNameIndex;
public:
	int AddNamedIcon(HICON hIcon, LPCTSTR lpszName);
	int GetIndex(LPCTSTR lpszName);
	int GetIndexByFileName(LPCTSTR lpszFileName);
	int SafeAddIconFile(LPCTSTR lpszFileName);
	BOOL AddIcons(WIZNAMEDIMAGELISTICONDATA* pData, int nCount);
	BOOL AddIcons(WIZNAMEDIMAGELISTICONDATA* pData);
	BOOL CreateEx(int width = 16, int height = 16);
};


#endif


UINT WizGetCodePage(LPCTSTR lpszCharset);

CStringW WizSTR2BSTR(LPCTSTR lpszCharset, const CStringA& strText);
CStringA WizBSTR2STR(LPCTSTR lpszCharset, const wchar_t* bstrText);

CStringW WizSTR2BSTR(UINT nCodePage, const CStringA& strText);
CStringA WizBSTR2STR(UINT nCodePage, const wchar_t* bstrText);

BOOL WizHtmlAnsiToUnicode(const char* lpszText, CStringW& strText);
BOOL WizXmlAnsiToUnicode(const char* lpszText, CStringW& strText);

CString WizHTMLGetCharsetFromHTMLText(const CStringA& strText);

CStringA WizW2A(const wchar_t* bstrText);
CStringW WizA2W(const char* lpszText);
CStringW WizUTF82BSTR(const char* lpszText);
CStringA WizBSTR2UTF8(const wchar_t* bstrText);


CString WizLcidToRfc1766String(LCID lcid);



BOOL WizGetDefaultCharset(BSTR* pbstrCharset) throw();
BOOL WizGetDefaultCharsetDescription(BSTR* pbstrCharsetDescription) throw();
BOOL WizGetCharsetDescription(BSTR bstrCharset, BSTR* pbstrCharsetDescription) throw();
CString WizGetDefaultCharset();



BOOL WizTestConvertToUnicode(const char* lpszText, UINT nCodePage, DWORD dwMultiByteToWideCharFlags);
UINT WizAutoDetectTextCodePage(const char* lpszText);

COLORREF WizHTMLStringColorToColor(LPCTSTR lpszHTMLColor);
COLORREF WizHTMLVariantColorToColor(const VARIANT& v);
CString WizHTMLColorToStringColor(COLORREF cr);



typedef std::map<CString, CString> CWizTranslationsStringMap;

class CWizTranslationsStringTable
{
public:
	CWizTranslationsStringTable();
	CWizTranslationsStringTable(LPCTSTR lpszFileName);
	virtual ~CWizTranslationsStringTable();
private:
	CWizTranslationsStringMap m_mapStrings;
private:
	void EncodeString(CString& str);
	void DecodeString(CString& str);
public:
	void Clear();
	BOOL AddStrings(const CWizStdStringArray& arrayText);
	BOOL AddStrings(LPCWSTR lpszText);
	BOOL AddStringsFromFile(LPCTSTR lpszFileName);
	BOOL TranslateString(LPCTSTR lpszSrc, CString& strRet);
	CString TranslateString(LPCTSTR lpszSrc);
	BOOL LoadString(UINT nStringID, CString& strRet);
	CString LoadString(UINT nStringID);
	BOOL TranslateMenu(HMENU hMenu);
	static BOOL CALLBACK TranslateWindowEnumChildProc(HWND hwnd, LPARAM lParam);
	BOOL TranslateWindowText(HWND hWnd);
	BOOL TranslateWindow(HWND hWnd);

	BOOL TranslatePropertySheet(HWND hWnd);
};




class CWizURL : public IBindStatusCallback  
{
public:
	CWizURL();
	CWizURL(LPCTSTR lpszURL, UINT nCodePage = 0, BOOL bUnescape = TRUE);
	CWizURL(const CWizURL& url);
private:
	CString m_strURL;
	CString m_strRedirectedURL;
private:
	//
	static void WizURLUnescapeAnsiChar(CString& strURL);
	CString ToFileNameInternal(BOOL bDownload);
public:
	CWizURL& operator=(const CWizURL& urlSrc);
	operator LPCTSTR () const;
	void SetURLIndirect(LPCTSTR lpszURL);
	static BOOL URLHasPercent(LPCTSTR lpszURL);
	CString GetRedirectedURL() const;
	BOOL Combine(const CWizURL& urlRelative);
	CWizURL GetBase() const;
	BOOL IsFileURL() const;
	BOOL IsFileName() const;
	CString GetFileNameInURL() const;
	CString ToFileName(BOOL bDownload);
	BOOL ToFileName(CString& strFileName, BOOL bDownload);
	BOOL DownloadToTemp(CString& strFileName);
	BOOL DownloadToFile(LPCTSTR lpszFileName);
	static CString Unescape(LPCTSTR lpszText);
	BOOL GetNameOfURL(CString& strName) const;
	CString GetHostName() const;
	CString GetFileExt() const;
	BOOL GetURLParamString(CString& strParamsPart) const;
	BOOL GetAllFileExt(CWizStdStringArray& arrayExts) const;
	BOOL ContainExt(const CWizStdStringArray& arrayExts) const;
	BOOL Equal(LPCTSTR lpszURL);
	BOOL Equal(const CWizURL& url);
	static CString DeleteBookmark(LPCTSTR lpszURL);
	static CString GetBookmark(LPCTSTR lpszURL);
	//
	CString GetQueryString() const;
	CString GetPathString() const;
public:
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);
	STDMETHOD_(ULONG,AddRef)();
	STDMETHOD_(ULONG,Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
};




class CWizFileSystemStream  : public IStream
{
private:
	DWORD		m_nRef;
	HANDLE		m_hFile;
	BOOL		m_bAutoClose;
	TCHAR		m_szFileName[1024];
protected:
	CWizFileSystemStream();
public:
	virtual ~CWizFileSystemStream();
public:
	static void Grf2Sam(DWORD grfMode, DWORD& dwDesiredAccess, DWORD& dwShareMode, BOOL& bCreate);
	static HRESULT CreateFileSystemStream(LPCTSTR lpszFileName, DWORD grfMode, IStream** ppStream);

	// IStream interface implementation.
	STDMETHODIMP_(ULONG)	AddRef(void);
	STDMETHODIMP_(ULONG)	Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
	STDMETHODIMP Read(void __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbRead);
	STDMETHODIMP Write(const void __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbWritten);
	STDMETHODIMP Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER __RPC_FAR *plibNewPosition);
	STDMETHODIMP SetSize(ULARGE_INTEGER libNewSize);
	STDMETHODIMP CopyTo(IStream __RPC_FAR *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER __RPC_FAR *pcbRead, ULARGE_INTEGER __RPC_FAR *pcbWritten);
	STDMETHODIMP Commit(DWORD grfCommitFlags);
	STDMETHODIMP Revert(void);
	STDMETHODIMP LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHODIMP UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHODIMP Stat(STATSTG __RPC_FAR *pstatstg, DWORD grfStatFlag);
	STDMETHODIMP Clone(IStream __RPC_FAR *__RPC_FAR *ppstm);
};



__int64 WizStreamGetCurPos(IStream* pStream);
__int64 WizStreamGetSize(IStream* pStream);
void WizStreamSeekToBegin(IStream* pStream);
void WizStreamSetSize(IStream* pStream, __int64 nSize);
BOOL WizStreamRead(IStream* pStream, void* pBuffer, ULONG nNeedRead);
BOOL WizStreamWrite(IStream* pStream, const void* pBuffer, ULONG nNeedWrite);
BOOL WizStreamAppendToStream(IStream* pFrom, IStream* pTo);
BOOL WizStreamLoadFromFile(LPCTSTR lpszFileName, IStream* pStream);
BOOL WizStreamSaveToFile(IStream* pStream, LPCTSTR lpszFileName);
BOOL WizStreamWriteUnicode(IStream* pStream, LPCWSTR lpszText);
BOOL WizStreamWriteUnicodeAsFile(IStream* pStream, LPCWSTR lpszText);
BOOL WizStreamLoadAnsiText(IStream* pStream, CStringA& strText);
BOOL WizStreamLoadUnicodeAsFile(IStream* pStream, CStringW& strText, BOOL bForceUTF16, LPCTSTR lpszFileName = NULL);

BOOL WizStreamCopy(IStream* pStreamFrom, IStream* pStreamTo);
size_t WizStreamAppendFile(IStream* pStream, LPCTSTR lpszFileName);
size_t WizStreamAppendStream(IStream* pStream, IStream* pStreamAppend);
BOOL WizStreamCopyEx(IStream* pStreamFrom, IStream* pStreamTo, size_t nSize);
BOOL WizStreamSafeCopy(IStream* pStreamFrom, IStream* pStreamTo);

ULONG WizStreamCopyEx(IStream* pStream, IStream* pStreamDest, ULONG nNeedRead);

HRESULT WizCreateReadOnlyStreamOnFile(LPCTSTR lpszFileName, IStream** ppStream);
HRESULT WizCreateWriteOnlyStreamOnFile(LPCTSTR lpszFileName, IStream** ppStream);
CComPtr<IStream> WizCreateReadOnlyStreamOnFile(LPCTSTR lpszFileName);
CComPtr<IStream> WizCreateWriteOnlyStreamOnFile(LPCTSTR lpszFileName);





BOOL WizCopyLargeFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists);
BOOL WizCopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists);




int WizFileCompare(LPCTSTR lpszFileName1, LPCTSTR lpszFileName2);
CString WizCompareCopyFile(LPCTSTR lpszExistingFileName, LPCTSTR lpszNewFileName);




void WizCommandLineToStringArray(LPCTSTR lpszCommandLine, CWizStdStringArray& arrayLine);
CString WizGetCommandLineValue(LPCTSTR lpszCommandLine, LPCTSTR lpszKey);
BOOL WizStringArrayGetBool(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey, BOOL bDef = FALSE);
BOOL WizStringArrayGetInt(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey, int nDef = 0);
BOOL WizCommandLineKeyExists(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey);
BOOL WizCommandLineKeyExists(LPCTSTR lpszCommandLine, LPCTSTR lpszKey);
COleDateTime WizTimeBuildTime(const COleDateTime& tDate, const COleDateTime& tTime);



BOOL WizStringSimpleSplit(const CString& str, TCHAR ch, CString& strLeft, CString& strRight);



class CWizBufferAlloc
{
public:
    CWizBufferAlloc(int nInitSize = 0);
    ~CWizBufferAlloc();
private:
    BYTE* m_pBuffer;
    int m_nSize;
public:
    BYTE* GetBuffer();
    BOOL SetNewSize(int nNewSize);
};


class CWizStrBufferAlloc
{
public:
	CWizStrBufferAlloc(size_t nInitSize = 0);
	~CWizStrBufferAlloc();
private:
	LPTSTR m_pBuffer;
	size_t m_nSize;
public:
	LPTSTR GetBuffer();
	BOOL SetNewSize(size_t nNewSize);
	size_t GetSize() const { return m_nSize; }
	void Append(LPCTSTR lpszText);
	void Empty();
	BOOL IsEmpty() const;
};



BOOL WizSimpleEncryptStringToFile(const char* lpszPassword, LPCWSTR lpszText, LPCWSTR lpszFileName);
BOOL WizSimpleDecryptStringFromFile(const char* lpszPassword, LPCWSTR lpszFileName, CString& strText);
BOOL WizSimpleEncryptTextFileToFile(const char* lpszPassword, LPCWSTR lpszTextFileName, LPCWSTR lpszFileName);




struct WIZFILEVERSIONDATA
{
	CString strMajor;
	BOOL bBeta;
	int nIndex;
	//
	WIZFILEVERSIONDATA()
	{
		bBeta = FALSE;
		nIndex = 0;
	}
};

BOOL WizGetFileVersion(LPCTSTR lpszFileName, WIZFILEVERSIONDATA& version);
CString WizGetFileVersion(LPCTSTR lpszFileName);
BOOL WizGetFileVersion(LPCTSTR lpszFileName, DWORD* pdwMajor, DWORD* pdwMinor);
BOOL WizIsIE7();



HRESULT WizDispatchSetProperty(IDispatch* pDisp, LPCTSTR lpszName, VARIANT vValue);
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vValue);
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, CComBSTR& bstrValue);
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, CComPtr<IDispatch>& spDispRet);
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, COleDateTime& dt);
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, int& nRet);
HRESULT WizDispatchInvoke0(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarRet = NULL);
HRESULT WizDispatchInvoke1(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT* pvarRet = NULL);
HRESULT WizDispatchInvoke1(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, CComPtr<IDispatch>& spDispRet);
HRESULT WizDispatchInvoke2(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT& vParam2, VARIANT* pvarRet = NULL);
HRESULT WizDispatchInvoke2(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT& vParam2, CComPtr<IDispatch>& spDispRet);
HRESULT WizDispatchInvokeN(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarParams, int nParams, VARIANT* pvarRet = NULL);
HRESULT WizDispatchInvokeN(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarParams, int nParams, CComPtr<IDispatch>& spDispRet);
BOOL WizCreateDispatchOnServer(LPCTSTR lpszProgID, CComPtr<IDispatch>& spDisp);



class CWizWindowLocker
{
public:
	CWizWindowLocker();
	CWizWindowLocker(HWND hwnd);
	~CWizWindowLocker();
public:
	BOOL Lock();
	void Unlock();
public:
	void SetWindow(HWND hWnd);
private:
	BOOL m_bLocked;
	HWND m_hWnd;
};



BOOL WizVariantToStringArray(const VARIANT& v, CWizStdStringArray& arrayText);
BOOL WizStringArrayToVariant(const CWizStdStringArray& arrayText, VARIANT& v);


COLORREF WizColorDarker(COLORREF crBase, float fFactor);
COLORREF WizColorLighter(COLORREF crBase, float fFactor); 




#define WIZCOLOR_BLUE		RGB(0xD2, 0xF0, 0xF9)
#define WIZCOLOR_GREEN		RGB(0xCB, 0xFE, 0xC5)
#define WIZCOLOR_PINK		RGB(0xF4, 0xCB, 0xF4)
#define WIZCOLOR_PRUPLE		RGB(0xD9, 0xD5, 0xFE)
#define WIZCOLOR_WHITE		RGB(0xFC, 0xFC, 0xFC)
#define WIZCOLOR_YELLOW		RGB(0xFD, 0xFD, 0xC3)



COLORREF WizColorSchemesGetDarkBackgroundColor(COLORREF crBackground);


CString WizGetProcessFileName();
HICON WizGetProcessIcon();



void WizDeleteAllFilesInFolderEx(LPCTSTR lpszPath);
BOOL WizDeleteAllFilesInFolder3(LPCTSTR lpszPath);
BOOL WizDeleteAllEmptySubFolders(LPCTSTR lpszPath);


HRESULT WizSaveIconToFile(HICON hIcon, LPCTSTR lpszFileName);


class CWizComInit
{
public:
	CWizComInit();
	~CWizComInit();
};

void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMessage);
void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID);
void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMsg, LPCTSTR lpszParam1);
void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID, LPCTSTR lpszParam1);
void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMsg, LPCTSTR lpszParam1, LPCTSTR lpszParam2);
void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID, LPCTSTR lpszParam1, LPCTSTR lpszParam2);


HRESULT WizCallDispatchDefaultMethod(VARIANT& v);
HRESULT WizCallDispatchDefaultMethod1(VARIANT& v, VARIANT& vParam1);
HRESULT WizCallDispatchDefaultMethod2(VARIANT& v, VARIANT& vParam1, VARIANT& vParam2);


#if _WIN32_WINNT >= 0x0501
BOOL WizOpenFolderAndSelectFile(LPCTSTR lpszFileName);
#endif




BOOL WizGetFileName(CString& strResultFileName, BOOL bOpen, LPCTSTR lpszFilter, LPCTSTR lpszInitFileName = NULL, LPCTSTR lpszDefExt = NULL);
BOOL WizGetFileName(CString& strResultFileName, BOOL bOpen, UINT nIDFilter, LPCTSTR lpszInitFileName = NULL, LPCTSTR lpszDefExt = NULL);
BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, LPCTSTR lpszFilter, LPTSTR pFileBuffer, UINT nBufferSize);
BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, LPCTSTR lpszFilter, UINT nMaxFile = 1024);
BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, UINT nIDFilter, UINT nMaxFile = 1024);


CString WizGetDisplayTime(const COleDateTime& t);



HRESULT WizCreateObjectGreen(LPCTSTR lpszDllFileName, CLSID clsid, REFIID iid, void** ppObj, HMODULE hModule);




class CWizXMLNode
{
public:
	CWizXMLNode();
	CWizXMLNode(IXMLDOMDocument* pDoc, IXMLDOMNode* pNode);
	CWizXMLNode(const CWizXMLNode& nodeSrc);
	virtual ~CWizXMLNode();
public:
	CWizXMLNode& operator = (const CWizXMLNode& right);
protected:
	CComPtr<IXMLDOMNode> m_spNode;
	CComPtr<IXMLDOMDocument> m_spDoc;
public:
	void InitData(IXMLDOMDocument* pDoc, IXMLDOMNode* pNode);
	CComPtr<IXMLDOMNode> GetNode() { return m_spNode; }
	CComPtr<IXMLDOMDocument> GetDoc() { return m_spDoc; }
	BOOL Valid() const { return m_spNode && m_spDoc; }
	void Clear() { m_spNode = NULL; m_spDoc = NULL; }
public:
	BOOL GetName(CString& strName);
	CString GetName();
	CString GetType();
	//
	CString GetText(LPCTSTR lpszDefault = NULL);
	BOOL GetText(CString& strText);
	BOOL SetText(LPCTSTR lpszText);
	//
	BOOL GetAttributeText(LPCTSTR lpszName, CString& strVal);
	BOOL GetAttributeInt(LPCTSTR lpszName, int& nVal);
	BOOL GetAttributeInt64(LPCTSTR lpszName, __int64& nVal);
	BOOL GetAttributeUINT(LPCTSTR lpszName, UINT& nVal);
	BOOL GetAttributeTimeT(LPCTSTR lpszName, time_t& nVal);
	BOOL GetAttributeTimeString(LPCTSTR lpszName, COleDateTime& t);
	BOOL GetAttributeBool(LPCTSTR lpszName, BOOL& bVal);
	BOOL GetAttributeDWORD(LPCTSTR lpszName, DWORD& dwVal);
	CString GetAttributeTextDef(LPCTSTR lpszName, LPCTSTR lpszDefault);
	int GetAttributeIntDef(LPCTSTR lpszName, int nDefault);
	__int64 GetAttributeInt64Def(LPCTSTR lpszName, __int64 Default);
	BOOL GetAttributeBoolDef(LPCTSTR lpszName, BOOL bDefault);
	//
	BOOL SetAttributeText(LPCTSTR lpszName, LPCTSTR lpszText);
	BOOL SetAttributeInt(LPCTSTR lpszName, int nVal);
	BOOL SetAttributeInt64(LPCTSTR lpszName, __int64 nVal);
	BOOL SetAttributeBool(LPCTSTR lpszName, BOOL bVal);
	BOOL SetAttributeTime(LPCTSTR lpszName, const COleDateTime& t);
	//
	BOOL FindChildNode(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild);
	BOOL AppendChild(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild);
	BOOL AppendChild(LPCTSTR lpszNodeName, LPCTSTR lpszChildNodeText);
	BOOL GetChildNode(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild);
	BOOL SetChildNodeText(LPCTSTR lpszNodeName, LPCTSTR lpszText);
	BOOL GetChildNodeText(LPCTSTR lpszNodeName, CString& strText);
	CString GetChildNodeTextDef(LPCTSTR lpszNodeName, LPCTSTR lpszDef);
	//
	BOOL GetAllChildNodes(CWizStdStringArray& arrayNodeName);
	BOOL GetAllChildNodes(std::vector<CWizXMLNode>& arrayNodes);
	BOOL GetFirstChildNode(CWizXMLNode& nodeChild);
	//
	BOOL DeleteChild(LPCTSTR lpszChildName);
	BOOL DeleteChild(CWizXMLNode& nodeChild);
	BOOL DeleteAllChild(LPCTSTR lpszExceptNodeName1 = NULL, LPCTSTR lpszExceptNodeName2 = NULL, LPCTSTR lpszExceptNodeName3 = NULL);
	//
	BOOL HasChildNode();
	int GetChildNodesCount();
	//
	BOOL AppendNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet);
	BOOL AppendNodeSetTextByPath(LPCTSTR lpszPath, LPCTSTR lpszText);
	//
	BOOL FindNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet);
	BOOL FindNodeTextByPath(LPCTSTR lpszPath, CString& strRet);
	//
	BOOL GetElementNodeByValue(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, CWizXMLNode& nodeRet);
	BOOL GetElementOtherNodeByValue(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, CWizXMLNode& nodeRet);
	BOOL GetElementOtherNodeByValueReturnString(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, CString& strRet);
	BOOL GetElementOtherNodeByValueReturnInt(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, int& nRet);
	BOOL GetElementOtherNodeByValueReturnBool(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, BOOL& bRet);
public:
	static BOOL FindChildNode(IXMLDOMNodeList* pChildNodeList, LPCTSTR lpszName, IXMLDOMNode** ppChildNode);
};

class CWizXMLDocument
{
public:
	CWizXMLDocument();
	CWizXMLDocument(IXMLDOMDocument* pDoc);
	virtual ~CWizXMLDocument();
protected:
	CComPtr<IXMLDOMDocument> m_spDoc;
	CString m_strErrorMessage;
	CString m_strErrorSrcText;
protected:
	BOOL Create();
public:
	CComPtr<IXMLDOMDocument> GetDoc() { return m_spDoc; }
	//
	BOOL LoadXML(BSTR bstrXML);
	BOOL LoadFromFile(LPCTSTR lpszFileName, BOOL bPromptError = TRUE);
	void Clear();
	//
	BOOL ToXML(CString& strText, BOOL bFormatText);
	BOOL ToUnicodeFile(LPCTSTR lpszFileName);
	//
	BOOL IsFail();
	CString GetErrorMessage() const { return m_strErrorMessage; }
	CString GetErrorSrcText() const { return m_strErrorSrcText; }
	//
	BOOL FindChildNode(LPCTSTR lpszName, CWizXMLNode& nodeChild);
	BOOL AppendChild(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild);
	BOOL GetChildNode(LPCTSTR lpszName, CWizXMLNode& nodeChild);
	//
	BOOL GetAllChildNodes(CWizStdStringArray& arrayNodeName);
	BOOL GetAllChildNodes(std::vector<CWizXMLNode>& arrayNodes);
	//
	BOOL FindNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet);
	BOOL GetNodeTextByPath(LPCTSTR lpszPath, CString& strRet);
	//
	BOOL SettingsGetSectionNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, CWizXMLNode& node);
	BOOL SettingsFindSectionNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, CWizXMLNode& node);
	BOOL SettingsGetChildNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, CWizXMLNode& node);
	BOOL SettingsGetStringValue(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, LPCTSTR lpszDefault, CString& strValue);
	BOOL SettingsSetStringValue(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, LPCTSTR lpszValue);
};


class CWizXmlSettingsSection 
	: public std::map<CString, CString>
{
public:
	BOOL GetStr(LPCTSTR lpszKey, CString& strValue);
	CString GetStr(LPCTSTR lpszKey, LPCTSTR lpszDef = NULL);
	int GetInt(LPCTSTR lpszKey, int nDef = 0);
	BOOL GetBool(LPCTSTR lpszKey, BOOL bDef = FALSE);
	BOOL Valid() const;
};

class CWizXmlSettings : public IWizSettingsBase
{
public:
	CWizXmlSettings(LPCTSTR lpszFileName, LPCTSTR lpszRootNodeName);
	virtual ~CWizXmlSettings(void);
private:
	CWizXMLDocument m_doc;
	//
	CString m_strFileName;
	CString m_strRootNodeName;

	//
	BOOL m_bModified;
	//
public:
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue);
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue);
	BOOL GetSection(LPCTSTR lpszSection, CWizXmlSettingsSection& section);
	BOOL ClearSection(LPCTSTR lpszSection);
};


BOOL WizFormatXML(CString& strXML);

CString WizGetUserName();
BOOL WizIsSystem();
BOOL WizIsAdmin();


BOOL WizStringSimpleMatch(LPCTSTR lpszSubString, LPCTSTR lpszText);
BOOL WizStringSimpleFind(LPCTSTR lpszSubString, LPCTSTR lpszText);




HANDLE WizCreateProcess(LPCTSTR lpszExeFileName, LPCTSTR lpszParam, BOOL bShowWindow = FALSE);
DWORD WizCreateProcessAndWait(LPCTSTR lpszExeFileName, LPCTSTR lpszParam, BOOL bShowWindow = FALSE);
HINSTANCE WizShellExecuteReturnInstance(HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd);
DWORD WizShellExecuteAndWait(HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd);



typedef std::map<BYTE, UINT>  CGdiCharsetCodePageMap;
BOOL InitGdiCharsetCodePageMap(CGdiCharsetCodePageMap& mapCharset);
UINT GetCodePageByGdiCharset(BYTE nCharset);



COleDateTime WizTimeFromRfc822(LPCTSTR lpsz, BOOL* pbSucceeded = NULL);
COleDateTime WizTimeFromStr(LPCTSTR lpsz, BOOL* pbSucceeded = NULL);
CString WizRfc822Time();



struct WIZHTMLLINKDATA
{
	CString strURL;
	CString strText;
};

typedef std::vector<WIZHTMLLINKDATA> CWizHTMLLinkDataArray;

BOOL WizURLADDownload(LPCTSTR lpszProduct, LPCTSTR lpszRelatedURL, LPCTSTR lpszADXMLFileName, LPCTSTR lpszVersion = NULL);
BOOL WizURLADLoad(CWizXMLNode& nodeAds, CWizHTMLLinkDataArray& arrayAD);
BOOL WizURLADLoad(LPCTSTR lpszADXMLFileName, CWizHTMLLinkDataArray& arrayAD);
BOOL WizURLADLoadOneAD(LPCTSTR lpszADXMLFileName, WIZHTMLLINKDATA& data);
BOOL WizURLADDownloadToXmlFile(LPCTSTR lpszProduct, LPCTSTR lpszRelatedURL, LPCTSTR lpszXmlFileName, LPCTSTR lpszRootNodeName, LPCTSTR lpszVersion = NULL);
BOOL WizURLADLoadFromXmlFile(LPCTSTR lpszADXMLFileName, CWizHTMLLinkDataArray& arrayAD);
BOOL WizURLADLoadOneADFromXmlFile(LPCTSTR lpszADXMLFileName, WIZHTMLLINKDATA& data);
BOOL WizURLGetClicked(LPCTSTR lpszADIniFileName, LPCTSTR lpszURL);
void WizURLSetClicked(LPCTSTR lpszADIniFileName, LPCTSTR lpszURL, BOOL bClicked);
BOOL WizURLADLoadFromXmlFileEx(LPCTSTR lpszADXMLFileName, LPCTSTR lpszCategory, LPCTSTR lpszADIniFileName, CWizHTMLLinkDataArray& arrayAD);
BOOL WizURLADLoadOneADFromXmlFileEx(LPCTSTR lpszADXMLFileName, LPCTSTR lpszCategory, LPCTSTR lpszADIniFileName, WIZHTMLLINKDATA& data);


CString WizVariantToString(const VARIANT& v);
int WizVariantToInt(const VARIANT& v, int nDef);


typedef std::set<UINT> CWizClipboardFormats;
CWizClipboardFormats WizEnumClipboardFormat(HWND hWnd);




CString WizXMLDocumentGetRootNodeName(CWizXMLDocument& doc);
CString WizXMLDocumentGetRootNodeName(LPCTSTR lpszFileName);



struct WIZCLIPBOARDINFO;

BOOL WizClipboardHGlobalSaveToImageFile(HANDLE hData, LPCTSTR lpszFileName);
BOOL WizClipboardSaveToImageFile(LPCTSTR lpszFileName);
CString WizClipboardBitmapToFileName();

BOOL WizGetClipboardInfo(WIZCLIPBOARDINFO& info, HWND hwnd = NULL);
BOOL WizHTMLGetBodyFromClipboardText(const CString& strText, CString& strHTML, CString& strURL);

BOOL WizClipboardHGlobalToHTML(HGLOBAL hGlobal, CStringW& strHtml);
BOOL WizHTMLToClipboardHTML(LPCTSTR lpszHTML, LPCTSTR lpszURL, CStringA& strClipboardHTML);
BOOL WizGetClipboardHTML(CString& strHTML);

BOOL WizGetClipboardRTF(CStringA& strRTF);
BOOL WizClipboardHGlobalToRTF(HGLOBAL hGlobal, CStringA& strRTF);

BOOL WizClipboardAutoSaveToImage(LPCTSTR lpszPath, CString& strImageFileName, HWND hWnd = NULL);

BOOL WizAutoCompressPngFile(LPCTSTR lpszFileName);


BOOL WizClipboardGetFilesByHDrop(HDROP hDrop, CWizStdStringArray& arrayFile);

struct WIZCLIPBOARDINFO
{
	BOOL bHasHTML;
	BOOL bHasRTF;
	BOOL bHasImage;
	BOOL bHasText;
	BOOL bHasFiles;
	//
	CString strClipboardInfoMD5;
	//
	WIZCLIPBOARDINFO();
	CString GetPlainText();
	CString GetHTMLText(CString& strURL);
	CStringA GetRTFText();
	CString GetBitmapFileName();
	BOOL GetFiles(CWizStdStringArray& arrayFile);
};


inline UINT CF_HTML_FORMAT()
{
	static UINT nFormat = RegisterClipboardFormat(_T("HTML Format"));
	return nFormat;
}
inline UINT CF_RTF_FORMAT()
{
	static UINT nFormat = RegisterClipboardFormat(_T("Rich Text Format"));
	return nFormat;
}


void WizCheckWindowTopMost(HWND hwnd);
HWND WizGetPopupWindow(HWND hwnd);



BOOL WizDayOnce(LPCTSTR lpszKey, LPCTSTR lpszName);


BOOL WizIsAutoRun(LPCTSTR lpszName);
BOOL WizEnableAutoRun(HKEY hRootKey, LPCTSTR lpszName, LPCTSTR lpszExeFileName);
BOOL WizEnableAutoRun(HKEY hRootKey, LPCTSTR lpszName, LPCTSTR lpszExeFileName, LPCTSTR lpszParams);
BOOL WizDisableAutoRun(LPCTSTR lpszName);



HWND WizGetOwnerPopupWindow(HWND hwnd);


class CWizBoolLocker
{
public:
	CWizBoolLocker(BOOL& b)
		: m_b(b)
	{
		m_b = !m_b;
	}
	~CWizBoolLocker()
	{
		m_b = !m_b;
	}
public:
	BOOL& m_b;
};





template <class TCollectionInterface, class TElementInterface>
inline BOOL WizCollectionDispatchToArray(IDispatch* pDisp, std::vector<CComPtr<TElementInterface> >& arrayRet)
{
	CComQIPtr<TCollectionInterface> spColl(pDisp);
	if (!spColl)
	{
		TOLOG(_T("Failed to query collection interface!"));
		return FALSE;
	}
	//
	long nCount = 0;
	spColl->get_Count(&nCount);
	//
	for (long i = 0; i < nCount; i++)
	{
		CComPtr<IDispatch> spElemDisp;
		HRESULT hr = spColl->get_Item(i, &spElemDisp);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to get item from collection!"));
			return FALSE;
		}
		//
		CComQIPtr<TElementInterface> spElem(spElemDisp);
		if (!spElem)
		{
			TOLOG(_T("Failed to query element interface!"));
			return FALSE;
		}
		//
		arrayRet.push_back(spElem);
	}
	//
	return TRUE;
}

template <class TCollectionInterface, class TElementInterface>
inline BOOL WizArrayToCollectionDispatch(const std::vector<CComPtr<TElementInterface> >& arrayRet, CLSID clsid, IDispatch** ppDisp, LPCTSTR lpszDllName)
{
	CComPtr<TCollectionInterface> spColl = ::WizCreateObjectAppPath<TCollectionInterface>(lpszDllName, clsid);
	if (!spColl)
	{
		TOLOG(_T("Failed to create collection object!"));
		return FALSE;
	}
	//
	HRESULT hr = E_FAIL;
	//
	for (std::vector<CComPtr<TElementInterface> >::const_iterator it = arrayRet.begin(); it != arrayRet.end(); it++)
	{
		CComPtr<TElementInterface> spElem = *it;
		//
		hr = spColl->Add(spElem);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to add element to collection!"));
			return FALSE;
		}
	}
	//
	//
	hr = spColl.QueryInterface(ppDisp);
	return SUCCEEDED(hr);
}


template <class TObject>
inline TObject* WizDispatchToObject(IDispatch* pDisp)
{
	return dynamic_cast<TObject*>(pDisp);
}

template <class TObject, class TData>
inline TData* WizDispatchToData(IDispatch* pDisp)
{
	TObject* pObj = WizDispatchToObject<TObject>(pDisp);
	if (!pObj)
		return NULL;
	//
	return &pObj->m_data;
}


template <class TCollectionInterface, class TElementInterface, class TObject, class TData>
inline BOOL WizCollectionToDataArray(IDispatch* pCollectionDisp, std::vector<TData>& arrayData)
{
	std::vector<CComPtr<TElementInterface> > arrayElem;
	if (!WizCollectionDispatchToArray<TCollectionInterface, TElementInterface>(pCollectionDisp, arrayElem))
		return FALSE;
	//
	for (std::vector<CComPtr<TElementInterface> >::const_iterator it = arrayElem.begin(); it != arrayElem.end(); it++)
	{
		CComPtr<TElementInterface> spElem = *it;
		//
		TObject* pObj = dynamic_cast<TObject* >(spElem.p);
		if (!pObj)
			return FALSE;
		//
		arrayData.push_back(pObj->m_data);
	}
	//
	return TRUE;
}


template <class T>
inline HRESULT WizCreateObjectGreen(LPCTSTR lpszDllFileName, CLSID clsid, CComPtr<T>& spObj, HMODULE hModule)
{
	hModule = ::LoadLibrary(lpszDllFileName);
	if (!hModule)
	{
		TOLOG1(_T("Failed to load dll: %1"), lpszDllFileName);
		return E_FAIL;
	}
	//
	typedef HRESULT STDAPICALLTYPE Type_DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
	Type_DllGetClassObject* pfun = (Type_DllGetClassObject *)GetProcAddress(hModule, "DllGetClassObject");
	if (!pfun)
	{
		TOLOG1(_T("Couldnot find DllGetClassObject address: %1"), lpszDllFileName);
		return E_FAIL;
	}
	//
	CComPtr<IClassFactory> spClassFactory;
	HRESULT hr = pfun(clsid, IID_IClassFactory, (void **)&spClassFactory);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create IClassFactory: %1"), lpszDllFileName);
		return hr;
	}
	//
	IID iid = __uuidof(T);
	hr = spClassFactory->CreateInstance(NULL, iid, (void **)&spObj);
	if (FAILED(hr))
	{
		TOLOG2(_T("Failed to create object: IID=%1, DllFileName=%2"), CString(CComBSTR(iid)), lpszDllFileName);
		return hr;
	}
	//
	return hr;
}


template <class T>
inline HRESULT WizCreateObject(LPCTSTR lpszDllFileName, CLSID clsid, CComPtr<T>& spObj, HMODULE hModule)
{
#ifdef _WIZCOMHELPER
	return WizCreateObjectGreen<T>(lpszDllFileName, clsid, spObj, hModule);
#else
	return spObj.CoCreateInstance(clsid);
#endif
}


template <class T>
inline HRESULT WizCreateObject(LPCTSTR lpszDllFileName, CLSID clsid, CComPtr<T>& spObj)
{
	HMODULE hModule = NULL;
	return WizCreateObject<T>(lpszDllFileName, clsid, spObj, hModule);
}


template <class T>
inline CComPtr<T> WizCreateObject(LPCTSTR lpszDllFileName, CLSID clsid)
{
	CComPtr<T> spObj;
	HMODULE hModule = NULL;
	HRESULT hr = WizCreateObject<T>(lpszDllFileName, clsid, spObj, hModule);
	if (FAILED(hr))
	{
		TOLOG2(_T("Failed to create object: %1, %2"), CString(CComBSTR(clsid)), lpszDllFileName);
		return NULL;
	}
	//
	return spObj;
}

template <class T>
inline CComPtr<T> WizCreateObjectAppPath(LPCTSTR lpszDllFileNameNoPath, CLSID clsid)
{
	CString strDllFileName = WizGetAppPath() + lpszDllFileNameNoPath;
	//
	return WizCreateObject<T>(strDllFileName, clsid);
}


template <class T, class TClass>
inline CComPtr<T> WizCreateObjectCurrentInstance()
{
	CComObject<TClass>* pObj = NULL;
	HRESULT hr = CComObject<TClass>::CreateInstance(&pObj);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to create object by class"));
		return NULL;
	}
	//
	return CComQIPtr<T>(pObj);
}


BOOL WizCreateSingleton(HANDLE& hMutex, LPCTSTR lpszName);
void WizCloseSingleton(HANDLE hMutex);



class CWizSingletonApp
{
protected:
	CWizSingletonApp();
public:
	virtual ~CWizSingletonApp();
protected:
	HANDLE m_hMutex;
	BOOL Create(LPCTSTR lpszName);
	BOOL Close();
protected:
	static CWizSingletonApp* GetSingletonApp();
public:
	static BOOL InitApp(LPCTSTR lpszName);
	static BOOL CloseApp();
};

class CWizSingletonAppEx : public CWizSingletonApp
{
public:
	CWizSingletonAppEx();
	BOOL CreateEx(LPCTSTR lpszName);
};


#if defined __ATLGDI_H__ || defined __AFX_H__

void WizFlashWindow(HWND hWnd);
void WizFlashWindow(HWND hWnd, const RECT& rc, int nPenWidth);

#endif //__ATLGDI_H__


class CWizAtlDataObject
{
public:
	CWizAtlDataObject(IDataObject* pData);
	virtual ~CWizAtlDataObject();
protected:
	IDataObject* m_pData;
public:
	IDataObject* GetData();
public:
	static BOOL FindFormat(IDataObject* pData, UINT nFormat);
	BOOL IsFormatAvaliable(UINT nFormat);
	HANDLE GetData(UINT nFormat);
	BOOL GetHtml(CString& strHtml, CString& strURL);
	BOOL GetRtf(CStringA& strRTF);
	BOOL GetBitmapFileName(LPCTSTR lpszFileName);
	BOOL GetUnicodeText(CString& strText);
	BOOL GetAnsiText(CString& strText);
	BOOL GetText(CString& strText);
	BOOL GetFiles(CWizStdStringArray& arrayFile);
};


CString WizTextGetFirstLine(LPCTSTR lpszText);