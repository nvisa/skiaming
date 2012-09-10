#include "stdafx.h"
#include "WizMisc.h"

#include <time.h>
#include <algorithm>
#include <stdlib.h>
#include <fcntl.h>
#include <share.h>
#include <io.h>
#include <sys/stat.h>
#include <direct.h>

#include <mlang.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <Shellapi.h>
#include <wininet.h>

#include <atlcomtime.h>
#include <atltime.h>
#include <atlenc.h>

#include <atlutil.h>

#include <atlsafe.h>
#include <atlimage.h>

#ifndef _INC_COMMDLG
#include <Commdlg.h>
#endif

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Msxml2.lib")

CString IWizGlobal::GetSettingsFileName()
{
	return CString();
}

void IWizGlobal::WriteDebugLog(LPCTSTR lpszMsg)
{
#ifndef _DEBUG
	static BOOL bFirst = TRUE;
	static BOOL bDebug = FALSE;
	if (bFirst)
	{
		bFirst = FALSE;
		//
		LPCTSTR lpszCommandLine = GetCommandLine();
		if (!lpszCommandLine)
			return;
		//
		bDebug = (NULL != StrStrI(lpszCommandLine, _T("/Debug")));
	}
	//
	if (!bDebug)
		return;
#endif
	//
	WriteLog(lpszMsg);
}



template<class T>
void WizProcessText(char* pBuffer, size_t nBufferLen, BOOL bNoRemoveCr)
{
	BOOL bRemoveCr = !bNoRemoveCr;
	//
	T* pEnd = (T*)(pBuffer + nBufferLen);
	//
	T* p1 = (T*)pBuffer;
	T* p2 = p1;
	//
	while (p2 < pEnd)
	{
		if (*p2 == '\0')
		{
			p2++;
		}
		else if (*p2 == '\r')
		{
			T chNext = *(p2 + 1);
			if (chNext != '\n')
			{
				*p1 = '\n';
				p1++;
				p2++;
			}
			else
			{
				if (bRemoveCr)
				{
					p2++;
				}
				else
				{
					*p1 = *p2;
					p1++;
					p2++;
				}
			}
		}
		else
		{
			*p1 = *p2;
			p1++;
			p2++;
		}
	}
	*p1 = 0;
}

BOOL WizBufferContainsZero(const char* pBuffer, size_t nLen)
{
	for (size_t i = 0; i < nLen; i++)
	{
		if (0 == *pBuffer)
			return TRUE;
		//
		pBuffer++;
	}
	//
	return FALSE;
}


BOOL WizLoadUnicodeTextFromBuffer2(char* pBuffer, size_t nLen, CStringW& strText, UINT nFlags /* = 0 */, UINT nDefaultCodePage /*= 0*/, LPCTSTR lpszFileName /*= NULL*/)
{
	ATLASSERT(pBuffer);
	//
	BOOL bForceHTML		=	(nFlags & WIZ_LTFF_FORCE_HTML)	?	TRUE : FALSE;
	BOOL bForceUTF8		=	(nFlags & WIZ_LTFF_FORCE_UTF8)	?	TRUE : FALSE;
	BOOL bForceUTF16	=	(nFlags & WIZ_LTFF_FORCE_UTF16) ?	TRUE : FALSE;
	BOOL bNoRemoveCr	=	(nFlags & WIZ_LTFF_NO_REMOVE_CR)	?	TRUE : FALSE;
	BOOL bForceXML		=	(nFlags & WIZ_LTFF_FORCE_XML)	?	TRUE : FALSE;
	//
	ATLASSERT(!(bForceUTF8 && bForceUTF16));
	//
	BOOL bRet = FALSE;
	try
	{
		//鉴别文件类型
		BYTE* pMark = (BYTE*)pBuffer;
		BOOL bUTF16AutoDetected = (pMark[0] == 0xFF && pMark[1] == 0xFE);
		BOOL bUTF8AutoDetected = (pMark[0] == 0xEF && pMark[1] == 0xBB && pMark[2] == 0xBF);
		//
		BOOL bUTF16 = (nLen >= 2) && (bForceUTF16 || bUTF16AutoDetected);
		BOOL bUTF8 =  (nLen >= 3) && (bForceUTF8  || bUTF8AutoDetected);
		//
#ifndef WINCE
		if (!bUTF16 && nLen > 10 && nLen % 2 == 0)
		{
			if (WizBufferContainsZero(pBuffer, nLen))
			{
				if (IsTextUnicode(pBuffer, int(nLen), NULL))
				{
					bUTF16 = TRUE;
				}

			}
		}
#endif
		//
		//过滤掉\r,只留\n
		//另外，有些文件中间会有\0，导致字符串不正常结束，取消这种情况
		if (bUTF16)
		{
			WizProcessText<wchar_t>(pBuffer, nLen, bNoRemoveCr);
		}
		else
		{
			WizProcessText<char>(pBuffer, nLen, bNoRemoveCr);
		}
		//
		//convert to unicode
		if (bUTF16)
		{
			const char* p = pBuffer;
			if (bUTF16AutoDetected)
			{
				p += 2;
			}
			//
			strText = (wchar_t *)p;
			//
			bRet = TRUE;
		}
		else if (bUTF8)
		{
			const char* p = pBuffer;
			if (bUTF8AutoDetected)
			{
				p += 3;
			}
			strText = WizSTR2BSTR(CP_UTF8, p);
			//
			bRet = TRUE;
		}
		else
		{
			CString strExt = WizExtractFileExt(CString(lpszFileName));
			if (bForceHTML || WizStrStrI_Ptr(strExt, _T(".htm")))
			{
				bRet = WizHtmlAnsiToUnicode(pBuffer, strText);
			}
			else if (bForceXML || WizStrStrI_Ptr(strExt, _T(".xml")))
			{
				bRet = WizXmlAnsiToUnicode(pBuffer, strText);
			}
			else if (WizStrStrI_Ptr(strExt, _T(".php")))
			{
				strText = WizSTR2BSTR(CP_UTF8, pBuffer);
			}
			else
			{
				strText = WizSTR2BSTR(nDefaultCodePage, pBuffer);
				//
				bRet = TRUE;
			}
		}
	}
	catch(...)
	{
	}
	return bRet;
}

BOOL WizLoadUnicodeTextFromBuffer(const char* pBuffer, size_t nLen, CStringW& strText, UINT nFlags /* = 0 */, UINT nDefaultCodePage /*= 0*/, LPCTSTR lpszFileName /*= NULL*/)
{
	size_t nNewBufferLen = nLen + 4;
	char * pBufferNew = new char [nNewBufferLen];
	if (!pBufferNew)
		return FALSE;
	//
	ZeroMemory(pBufferNew, nNewBufferLen);
	//
	memcpy(pBufferNew, pBuffer, nLen);
	//
	BOOL bRet = WizLoadUnicodeTextFromBuffer2(pBufferNew, nLen, strText, nFlags, nDefaultCodePage, lpszFileName);
	//
	delete [] pBufferNew;
	//
	return bRet;
}



#ifdef WINCE
BOOL WizLoadUnicodeTextFromFileEx(LPCTSTR lpszFileName, CStringW& strText, UINT nFlags /* = 0 */, UINT nDefaultCodePage /*= 0*/)
{
	BOOL bRet = FALSE;
	//
	char* pBuffer = NULL;
	try
	{
		size_t nLen = WizGetFileSize(lpszFileName);
		//
		if (FILE* fp = _tfopen(lpszFileName, _T("rb")))
		{
			pBuffer = new char[nLen + 4];
			if (pBuffer)
			{
				ZeroMemory(pBuffer, nLen + 4);
				fread(pBuffer, nLen, 1, fp);
				//
				bRet = WizLoadUnicodeTextFromBuffer2(pBuffer, nLen, strText, nFlags, nDefaultCodePage, lpszFileName);
			}
			fclose(fp);
		}
	}
	catch(...)
	{
	}
	delete [] pBuffer;
	//
	return bRet;
}

#else

BOOL WizLoadUnicodeTextFromFileEx(LPCTSTR lpszFileName, CStringW& strText, UINT nFlags /* = 0 */, UINT nDefaultCodePage /*= 0*/)
{
	BOOL bRet = FALSE;
	//
	char* pBuffer = NULL;
	try
	{
		size_t nLen = WizGetFileSize(lpszFileName);
		//
		int  fd = 0;
		if(0 == _tsopen_s(&fd, lpszFileName, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0))
		{
			if (FILE* fp = _tfdopen(fd, _T("rb")))
			{
				pBuffer = new char[nLen + 4];
				if (pBuffer)
				{
					ZeroMemory(pBuffer, nLen + 4);
					fread(pBuffer, nLen, 1, fp);
					//
					bRet = WizLoadUnicodeTextFromBuffer2(pBuffer, nLen, strText, nFlags, nDefaultCodePage, lpszFileName);
				}
				fclose(fp);
			}
			else
			{
				_close(fd);
			}
		}
	}
	catch(...)
	{
	}
	delete [] pBuffer;
	//
	return bRet;
}

#endif

BOOL WizLoadAnsiTextFromAnsiFileEx(LPCTSTR lpszFileName, CStringA& strText, UINT nFlags /* = 0 */)
{
	BOOL bLoadUTF8		=	(!(nFlags & WIZ_LATFAF_NO_LOAD_UTF8))	?	TRUE : FALSE;
	BOOL bNoRemoveCr	=	(nFlags & WIZ_LATFAF_NO_REMOVE_CR)	?	TRUE : FALSE;
	//
	BOOL bRet = FALSE;
	char* pBuffer = NULL;
	try
	{
		size_t nLen = WizGetFileSize(lpszFileName);
		//
		FILE* fp = NULL;
#ifdef WINCE
		if (fp == _tfopen(lpszFileName, _T("rb")))
#else
		if (0 == _tfopen_s(&fp, lpszFileName, _T("rb")) && fp)
#endif
		{
			pBuffer = new char[nLen + 4];
			if (pBuffer)
			{
				ZeroMemory(pBuffer, nLen + 4);
				fread(pBuffer, nLen, 1, fp);
			}
			fclose(fp);
		}
		//
		//
		if (pBuffer)
		{
			//鉴别文件类型
			BYTE* pMark = (BYTE*)pBuffer;
			BOOL bUTF16AutoDetected = (pMark[0] == 0xFF && pMark[1] == 0xFE);
			BOOL bUTF8AutoDetected = (pMark[0] == 0xEF && pMark[1] == 0xBB && pMark[2] == 0xBF);
			//
			BOOL bUTF16 = (nLen >= 2) && (bUTF16AutoDetected);
			BOOL bUTF8 =  (nLen >= 3) && (bUTF8AutoDetected);
			//
			//过滤掉\r,只留\n
			//另外，有些文件中间会有\0，导致字符串不正常结束，取消这种情况
			if (!bUTF16 && (!bUTF8 || bLoadUTF8))
			{
				WizProcessText<char>(pBuffer, nLen, bNoRemoveCr);
				//
				strText = pBuffer;
				//
				bRet = TRUE;
			}
		}
	}
	catch(...)
	{
	}
	delete [] pBuffer;
	return bRet;
}


BOOL WizEnsurePathExistsBase(LPCTSTR lpszPath)
{
    if (PathFileExists(lpszPath))
		return TRUE;
	//
	return CreateDirectory(lpszPath, NULL);
}
BOOL WizEnsurePathExists(LPCTSTR lpszPath)
{
	return WizEnsurePathExistsEx(lpszPath);
}
BOOL WizEnsurePathExistsEx(LPCTSTR lpszPath)
{
	CWizStdStringArray arrayText;
	WizSplitTextToArray(CStringW(lpszPath), '\\', arrayText);
	//
	CString strPath;
	//
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		strPath = strPath + CString(arrayText[i]) + _T("\\");
		if (0 == i)
			continue;
		//
		if (!WizEnsurePathExistsBase(strPath))
			return FALSE;
	}
	//
	return TRUE;
}

BOOL WizCmdLineToFileName(LPTSTR lpszCmdLine)
{
	if (!lpszCmdLine)
		return FALSE;
	if (!*lpszCmdLine)
		return FALSE;
	//
#ifdef WINCE
	CString str(lpszCmdLine);
	str.Trim(_T(" \""));
	_tcscpy(lpszCmdLine, str);
#else
	TCHAR szTrim[ ] = TEXT(" \"");
	StrTrim(lpszCmdLine, szTrim);
#endif
	return _tcslen(lpszCmdLine) > 0;
}

BOOL WizIsFileName(LPCTSTR lpszFileName)
{
	if (!PathFileExists(lpszFileName))
		return FALSE;
	//
	if (FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(lpszFileName))
		return FALSE;
	//
	return TRUE;
}

#define WIZ_INVALID_CHAR_OF_FILE_NAME		_T("/\"?:*|<>\r\n\t,%\'")

BOOL WizIsValidFileNameNoPath(LPCTSTR lpszFileName)
{
	CString strFileName(lpszFileName);
	//
	if (strFileName.GetLength() >= MAX_PATH)
		return FALSE;
	//
	return -1 == strFileName.FindOneOf(WIZ_INVALID_CHAR_OF_FILE_NAME);
}


void WizMakeValidFileNameNoPath(CString& strFileName)
{
	if (WizIsValidFileNameNoPath(strFileName))
		return;
	//
	if (strFileName.GetLength() >= MAX_PATH)
		strFileName = strFileName.Left(MAX_PATH - 1);
	//
	while (1)
	{
		int nPos = strFileName.FindOneOf(WIZ_INVALID_CHAR_OF_FILE_NAME);
		if (-1 == nPos)
			break;
		//
		strFileName.SetAt(nPos,  _T('-'));
	}
	//
	while (strFileName.Find(_T("--")) != -1)
	{
		strFileName.Replace(_T("--"), _T("-"));
	}
	//
	strFileName.Trim();
	strFileName.Trim(_T("-"));
}

void WizMakeValidFileNameNoPathLimitLength(CString& strFileName, int nMaxTitleLength)
{
	WizMakeValidFileNameNoPath(strFileName);
	//
	CString strTitle = WizExtractFileTitle(strFileName);
	CString strExt = WizExtractFileExt(strFileName);
	//
	if (strTitle.GetLength() > nMaxTitleLength)
	{
		strFileName = strTitle.Left(nMaxTitleLength) + strExt;
	}
}

void WizMakeValidFileNameNoPathLimitFullNameLength(CString& strFileName, int nMaxFullNameLength)
{
	WizMakeValidFileNameNoPath(strFileName);
	//
	if (strFileName.GetLength() <= nMaxFullNameLength)
		return;
	//
	CString strExt = WizExtractFileExt(strFileName);
	//
	int nMaxTitleLength = nMaxFullNameLength - strExt.GetLength();
	//
	WizMakeValidFileNameNoPathLimitLength(strFileName, nMaxTitleLength);
}

CString WizMakeValidFileNameNoPathReturn(LPCTSTR lpszFileName)
{
	CString strFileName(lpszFileName);
	WizMakeValidFileNameNoPath(strFileName);
	//
	return strFileName;
}

BOOL WizGetFileData(LPCTSTR lpszFileName, WIN32_FIND_DATA& data)
{
	ZeroMemory(&data, sizeof(WIN32_FIND_DATA));
	//
	HANDLE hFind = FindFirstFile(lpszFileName, &data);   
	if (INVALID_HANDLE_VALUE == hFind) 
	{
		return FALSE;
	}
	//
	FindClose(hFind);
	//
	return TRUE;
}

size_t WizGetFileSize(LPCTSTR lpszFileName)
{
	if (!PathFileExists(lpszFileName))
		return 0;
	if (!WizIsFileName(lpszFileName))
		return 0;
	//
	WIN32_FIND_DATA data;
	if (!WizGetFileData(lpszFileName, data))
		return 0;
	//
	return data.nFileSizeLow;
}

COleDateTime WizGetFileModifiedTime(LPCTSTR lpszFileName)
{
	WIN32_FIND_DATA data;
	if (!WizGetFileData(lpszFileName, data))
		return COleDateTime(2000, 1, 1, 0, 0, 0);
	//
	return COleDateTime(data.ftLastWriteTime);
}
COleDateTime WizGetFileCreatedTime(LPCTSTR lpszFileName)
{
	WIN32_FIND_DATA data;
	if (!WizGetFileData(lpszFileName, data))
		return COleDateTime(2000, 1, 1, 0, 0, 0);
	//
	return COleDateTime(data.ftCreationTime);
}


CString WizIntToStr(int n)
{
	TCHAR szBuffer[100] = {0};
	_itot_s(n, szBuffer, 100, 10);
	//
	return CString(szBuffer);
}
CString WizInt64ToStr(__int64 n)
{
	TCHAR szBuffer[100] = {0};
#ifdef WINCE
	WizX64toX_s(n, szBuffer, 100, 10, n < 0);
#else
	_i64tot_s(n, szBuffer, 100, 10);
#endif
	return CString(szBuffer);
}

CString WizDateToLocalString(const COleDateTime& t)
{
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	//
	TCHAR szBuffer[MAX_PATH] = {0};
#ifdef WINCE
	GetDateFormat(GetThreadLocale(), DATE_SHORTDATE, &st, NULL, szBuffer, MAX_PATH);
#else
	GetDateFormat(GetThreadLocale(), DATE_USE_ALT_CALENDAR, &st, NULL, szBuffer, MAX_PATH);
#endif
	//
	return CString(szBuffer);
}

CString WizDateToLocalStringLongDate(const COleDateTime& t)
{
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	//
	TCHAR szBuffer[MAX_PATH] = {0};
	GetDateFormat(GetThreadLocale(), DATE_LONGDATE, &st, NULL, szBuffer, MAX_PATH);
	//
	return CString(szBuffer);
}

CString WizTimeToLocalString(const COleDateTime& t, BOOL bNoSec /*= FALSE*/)
{
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	//
	TCHAR szBuffer[MAX_PATH] = {0};
	GetTimeFormat(GetThreadLocale(), bNoSec ? TIME_NOSECONDS : 0, &st, NULL, szBuffer, MAX_PATH);
	//
	return CString(szBuffer);
}
CString WizDateTimeToLocalString(const COleDateTime& t, BOOL bNoSec /*= FALSE*/)
{
	return WizDateToLocalString(t) + _T(" ") + WizTimeToLocalString(t, bNoSec);
}

CString WizDateTimeToLocalStringLongDate(const COleDateTime& t, BOOL bNoSec /*= FALSE*/)
{
	return WizDateToLocalStringLongDate(t) + _T(" ") + WizTimeToLocalString(t, bNoSec);
}

#ifndef WINCE

CString WizAsciiTime(const time_t t)
{
	char buffer[MAX_PATH] = {0};
	struct tm newtime;
	localtime_s(&newtime, &t);   // Convert time to struct tm form.
	asctime_s(buffer, MAX_PATH, &newtime);
	//
	//
	CString strTime = CString(buffer);
	strTime.Trim();
	//
	return strTime;
}

#endif

CString WizExtractFilePath(LPCTSTR lpszFileName)
{
	TCHAR szDrv[MAX_PATH] = {0};
	TCHAR szPath[MAX_PATH] = {0};
	//
	_tsplitpath_s(lpszFileName, szDrv, MAX_PATH, szPath, MAX_PATH, NULL, 0, NULL, 0);
	//
	return CString(szDrv) + szPath;
}
CString WizExtractFileName(LPCTSTR lpszFileName)
{
	TCHAR szName[MAX_PATH] = {0};
	TCHAR szExt[MAX_PATH] = {0};
	//
	_tsplitpath_s(lpszFileName, NULL, 0, NULL, 0, szName, MAX_PATH, szExt, MAX_PATH);
	//
	return CString(szName) + szExt;
}
CString WizExtractFileExt(LPCTSTR lpszFileName)
{
	TCHAR szExt[MAX_PATH] = {0};
	//
	_tsplitpath_s(lpszFileName, NULL, 0, NULL, 0, NULL, 0, szExt, MAX_PATH);
	//
	return CString(szExt);
}
CString WizReplaceFileExt(LPCTSTR lpszFileName, LPCTSTR lpszNewExt)
{
	return WizExtractFilePath(lpszFileName) + WizExtractFileTitle(lpszFileName) + lpszNewExt;
}
CString WizExtractFileTitle(LPCTSTR lpszFileName)
{
	TCHAR szName[MAX_PATH] = {0};
	//
	_tsplitpath_s(lpszFileName, NULL, 0, NULL, 0, szName, MAX_PATH, NULL, 0);
	//
	return CString(szName);
}
CString WizGetModulePath(HMODULE hModule)
{
	TCHAR szFileName[MAX_PATH] = {0};
	GetModuleFileName(hModule, szFileName, MAX_PATH);

	return WizExtractFilePath(szFileName);
}

CString WizIntToHex(int n, BOOL bWithPrefix /*= FALSE*/)
{
	TCHAR szBuffer[100] = {0};
	_itot_s(n, szBuffer, 100, 16);
	//
	if (bWithPrefix)
	{
		return CString(_T("0x")) + CString(szBuffer);
	}
	else
	{
		return CString(szBuffer);
	}
}
CString WizIntToHexEx(int n, int nWidth, BOOL bWithPrefix /*= FALSE*/)
{
	CString strFormat = CString(_T("%0")) + WizIntToStr(nWidth) + _T("X");
	//
	CString strValue;
	strValue.Format(strFormat, n);
	//
	if (bWithPrefix)
	{
		return CString(_T("0x")) + strValue;
	}
	else
	{
		return strValue;
	}
}

int WizHexToInt(LPCTSTR lpszText)
{
	CString strText(lpszText);
	if (0 == _tcsnicmp(strText, _T("0x"), 2))
		strText.Delete(0, 2);
	//
	strText.Trim();
	strText.MakeLower();
	//
	int nValue = 0;
	for (int i = 0; i < strText.GetLength(); i++)
	{
		TCHAR ch = strText[i];
		if (ch >= '0' && ch <= '9')
		{
			nValue = (nValue * 16) + ch - '0';
		}
		else if (ch >= 'a' &&ch <= 'f')
		{
			nValue = (nValue * 16) + ch - 'a' + 10;
		}
		else
		{
			return nValue;
		}
	}
	//
	return nValue;
}

CString WizIntToByteSizeStr(int n)
{
	TCHAR szBuffer[100] = {0};
	StrFormatByteSize(n, szBuffer, 100);
	//
	return CString(szBuffer);
}

// nFracDigits = -1 : use no. of frac. digits from string
CString WizFormatNumber(LPCTSTR lpszNumber, int nFracDigits)
{
	ATLASSERT(lpszNumber);
	ATLASSERT(lpszNumber[0] != 0);
	
	CString str = lpszNumber;

	NUMBERFMT nf;
	memset(&nf, 0, sizeof(nf));

	TCHAR szBuffer[100] = {0};
	TCHAR szDecSep[100] = {0};
	TCHAR szThousandsSep[100] = {0};

	// set decimal separator string from locale default
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL,
		szDecSep, sizeof(szDecSep)-1);
	nf.lpDecimalSep = szDecSep;

	// set thousand separator string from locale default
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND,
		szThousandsSep, sizeof(szThousandsSep)-1);
	nf.lpThousandSep = szThousandsSep;

	// set leading zeroes from locale default
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILZERO,
		szBuffer, sizeof(szBuffer)-1);
	nf.LeadingZero = _ttoi(szBuffer);

	// set grouping of digits from locale default
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SGROUPING,
		szBuffer, sizeof(szBuffer)-1);
	nf.Grouping = _ttoi(szBuffer);

	// set negative number mode from locale default
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_INEGNUMBER,
		szBuffer, sizeof(szBuffer)-1);
	nf.NegativeOrder = _ttoi(szBuffer);

	int dp = nFracDigits;

	if (dp == -1)
	{
		// set number of fractional digits from input string
		CString strDecSep = szDecSep;
		dp = str.Find(szDecSep);
		dp = (dp == -1) ? 0 : str.GetLength() - dp - strDecSep.GetLength();
	}
	nf.NumDigits = dp;
	//
	TCHAR szNumber[MAX_PATH] = {0};
	//
	if (GetNumberFormat(LOCALE_USER_DEFAULT, 
						0, 
						lpszNumber, 
						&nf, 
						szNumber, 
						MAX_PATH))
	{
		str = szNumber;
	}

	return str;
}

CString WizFormatInt(int nVal)
{
	return WizFormatNumber(WizIntToStr(nVal), 0);
}


BOOL WizLoadUnicodeTextFromFile(LPCTSTR lpszFileName, CStringW& strText)
{
	return WizLoadUnicodeTextFromFileEx(lpszFileName, strText, 0);
}
BOOL WizLoadUnicodeTextFromFileForceHTML(LPCTSTR lpszFileName, CStringW& strText)
{
	return WizLoadUnicodeTextFromFileEx(lpszFileName, strText, WIZ_LTFF_FORCE_HTML);
}
BOOL WizLoadUnicodeTextFromFileNoRemoveCR(LPCTSTR lpszFileName, CStringW& strText)
{
	return WizLoadUnicodeTextFromFileEx(lpszFileName, strText, WIZ_LTFF_NO_REMOVE_CR);
}

BOOL WizLoadAnsiTextFromAnsiFileNoRemoveCR(LPCTSTR lpszFileName, CStringA& strText)
{
	return WizLoadAnsiTextFromAnsiFileEx(lpszFileName, strText, WIZ_LATFAF_NO_REMOVE_CR);
}


UINT WizGetFileType(LPCTSTR lpszFileName)
{
	size_t nLen = WizGetFileSize(lpszFileName);
	if (3 >= nLen)
		return WIZ_FT_ANSI;
	//
	UINT nRet = WIZ_FT_ANSI;
	//
	FILE* fp = NULL;
	if(0 == _tfopen_s(&fp, lpszFileName, _T("rb")) && fp)
	{
		BYTE byMark[3] = {0, 0, 0};
		fread(byMark, 3, 1,fp);
		//
		BYTE* p = byMark;
		//
        bool bUTF_16 = (nLen >= 2 && (unsigned char)(*p) == 0xFF && (unsigned char)(*(p + 1)) == 0xFE);
        bool bUTF_8 = ((unsigned char)(*p) == 0xEF && (unsigned char)(*(p + 1)) == 0xBB && (unsigned char)(*(p + 2)) == 0xBF);
		//
		if (bUTF_8)
		{
			nRet = WIZ_FT_UTF_8;
		}
		else if (bUTF_16)
		{
			nRet = WIZ_FT_UTF_16;
		}
		//
		fclose(fp);
	}
	return nRet;
}

BOOL WizLfToCrLf(LPCWSTR lpszText, CStringW& wstrText)
{
	size_t nLen = wcslen(lpszText);
	//
	int nBufferLen = int(nLen + 1) * 2;
	LPWSTR pBuffer = wstrText.GetBuffer(nBufferLen);
	if (!pBuffer)
		return FALSE;
	//
	ZeroMemory(pBuffer, nBufferLen * sizeof(WCHAR));
	//
	LPCWSTR pCr = NULL;
	LPCWSTR p = lpszText;
	while (*p)
	{
		switch (*p)
		{
		case L'\r':
			pCr = p;
			break;
		case L'\n':
			if (!pCr || p - pCr != 1)
			{
				*pBuffer = L'\r';
				pBuffer++;
			}
			break;
		}
		*pBuffer = *p;
		//
		p++;
		pBuffer++;
	}
	//
	wstrText.ReleaseBuffer();
	//
	return TRUE;
}

BOOL WizSaveUnicodeTextToUnicodeFile(LPCTSTR lpszFileName, LPCWSTR lpszText)
{
	BOOL bRet = FALSE;
    try
    {
		CStringW wstrText;
		if (WizLfToCrLf(lpszText, wstrText))
		{
			lpszText = wstrText;
			//
			FILE* fp = NULL;
			if (0 == _tfopen_s(&fp, lpszFileName, _T("wb")))
			{
				BYTE szMark[2] = {BYTE(0xFF), BYTE(0xFE)};
				fwrite(szMark, 2, 1, fp);
	            fwrite(lpszText, wcslen(lpszText) * sizeof(WCHAR), 1, fp);
				//
				fclose(fp);
				bRet = TRUE;
			}
		}
    }
    catch(...)
    {
    }
	return bRet;
}
BOOL WizSaveUnicodeTextToUnicodeFileStream(IStream* pStream, LPCWSTR lpszText)
{
	ATLASSERT(pStream);
	//
	BOOL bRet = FALSE;
	try
	{
		CStringW wstrText;
		if (WizLfToCrLf(lpszText, wstrText))
		{
			lpszText = wstrText;
			//
			BYTE szMark[2] = {BYTE(0xFF), BYTE(0xFE)};
			//
			pStream->Write(szMark, 2, NULL);
			pStream->Write((const void *)lpszText, ULONG(wcslen(lpszText) * sizeof(WCHAR)), NULL);
			bRet = TRUE;
		}
	}
	catch(...)
	{
	}
	return bRet;
}
BOOL WizSaveAnsiTextToAnsiFile(LPCTSTR lpszFileName, LPCSTR lpszText, BOOL bBinary /*= FALSE*/, BOOL bAddUTF8Sing /*= FALSE*/)
{
	BOOL bRet = FALSE;
    try
    {
		FILE* fp = NULL;
		//
		LPCTSTR lpszMode = bBinary ? _T("wb") : _T("w");
		//
		if (0 == _tfopen_s(&fp, lpszFileName, lpszMode))
		{
			if (bAddUTF8Sing)
			{
				BYTE szSing[3] = {0xEF, 0xBB, 0xBF};
				fwrite(szSing, 3, 1, fp);
			}
			//
			if (bBinary)
			{
				fwrite(lpszText, strlen(lpszText), 1, fp);
			}
			else
			{
				fputs(lpszText, fp);
			}
			//
			fclose(fp);
			bRet = TRUE;
		}
    }
    catch(...)
    {
    }
	return bRet;
}
BOOL WizSaveUnicodeTextToUnicodeFile(HANDLE hFile, LPCWSTR lpszText)
{
	BOOL bRet = FALSE;
    try
    {
		CStringW wstrText;
		if (WizLfToCrLf(lpszText, wstrText))
		{
			lpszText = wstrText;
			//
			BYTE szMark[2] = {BYTE(0xFF), BYTE(0xFE)};
			DWORD dwWritted = 0;
			//
			WriteFile(hFile, szMark, 2, &dwWritted, NULL);
			//
			WriteFile(hFile, lpszText, DWORD(wcslen(lpszText) * sizeof(WCHAR)), &dwWritted, NULL);
			//
			bRet = TRUE;
		}
    }
    catch(...)
    {
    }
	return bRet;
}

CString WizPasswordToMd5String(LPCTSTR lpszPassword)
{
	CStringW wstrPassword(lpszPassword);
	//
	size_t nLen = wstrPassword.GetLength();
	if (nLen == 0)
		return CString();
	//
	LPCWSTR lpwstrPassword = wstrPassword;
	//
	return WizMd5String((BYTE *)lpwstrPassword, DWORD(sizeof(WCHAR) * nLen));
}

CString WizPasswordToMd5StringNoSpace(LPCTSTR lpszPassword)
{
	CStringW wstrPassword(lpszPassword);
	//
	size_t nLen = wstrPassword.GetLength();
	if (nLen == 0)
		return CString();
	//
	LPCWSTR lpwstrPassword = wstrPassword;
	//
	return WizMd5StringNoSpace((BYTE *)lpwstrPassword, DWORD(sizeof(WCHAR) * nLen));
}

BOOL WizSaveBufferToFile(const BYTE* pBuffer, size_t nSize, LPCTSTR lpszFileName)
{
	CString strPath(WizExtractFilePath(lpszFileName));
	if (!PathFileExists(strPath))
	{
		CreateDirectory(strPath, NULL);
	}
	//
	BOOL bRet = FALSE;
	//
	FILE* fp = NULL;
	if (0 == _tfopen_s(&fp, lpszFileName, _T("wb")))
	{
		fwrite(pBuffer, nSize, 1, fp);
		//
		fclose(fp);
		//
		bRet = TRUE;
	}
	return bRet;
}

CString WizGenGUID()
{
	GUID guid;
	if (S_OK == CoCreateGuid(&guid))
	{
		return CString(CComBSTR(guid));
	}
	return CString();
}

CString WizGenGUIDLowerCaseLetterOnly()
{
	CString strGUID = WizGenGUID();
	strGUID.MakeLower();
	strGUID.Trim(_T("{}"));
	return strGUID;
}


BOOL WizHGlobalToUnicodeText(HGLOBAL hGlobal, CStringW& strText)
{
	if (!hGlobal)
		return FALSE;
	//
	LPCWSTR pBuffer = (LPCWSTR)GlobalLock(hGlobal);
	if (!pBuffer)
		return FALSE;
	//
	strText = pBuffer;
	//
	GlobalUnlock(hGlobal);
	//
	return TRUE;
}

void WizPathAddBackslash(CString& strPath)
{
	if (strPath.IsEmpty())
		return;
	TCHAR ch = strPath[strPath.GetLength() - 1];
	if (ch == _T('/') || ch == _T('\\'))
		return;
	strPath += _T('\\');
}

CString WizGetLongFileName(LPCTSTR lpszFileName)
{
	TCHAR szLongFileName[1024] = {0};
	if (0 == GetLongPathName(lpszFileName, szLongFileName, 1024))
	{
		return CString(lpszFileName);
	}
	else
	{
		return CString(szLongFileName);
	}
}

CString WizGetShortFileName(LPCTSTR lpszFileName)
{
	TCHAR szShortFileName[1024] = {0};
	if (0 == GetShortPathName(lpszFileName, szShortFileName, 1024))
	{
		return CString(lpszFileName);
	}
	else
	{
		return CString(szShortFileName);
	}
}


CString WizGetAppFileName()
{
#ifdef __ATLBASE_H__
	HMODULE hModule = _AtlBaseModule.GetModuleInstance();
#else
	HMODULE hModule = AfxGetApp()->m_hInstance;
#endif
	//
	TCHAR szFileName[1024] = {0};
	GetModuleFileName(hModule, szFileName, 1024);
	//
	TCHAR szLongFileName[1024] = {0};
	GetLongPathName(szFileName, szLongFileName, 1024);
	//
	*szLongFileName = _totupper(*szLongFileName);

	return CString(szLongFileName);
}
CString WizGetAppPath()
{
	return WizExtractFilePath(WizGetAppFileName());
}

void WizProcessMessages()
{
	MSG Msg;
	while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
	{
		if (Msg.message != WM_QUIT)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}

CString WizGetMyDocumentsPath()
{
	static CString strPath;
	if (strPath.IsEmpty())
	{
		TCHAR szPath[MAX_PATH] = {0};
		if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, szPath)))
		{
			*szPath = _totupper(*szPath);
			//
			PathAddBackslash(szPath);
			strPath = szPath;
		}
		else
		{
			strPath = WizGetAppPath();
		}
	}
	return strPath;
}
CString WizGetAppDataPath()
{
	static CString strPath;
	if (strPath.IsEmpty())
	{
		TCHAR szPath[MAX_PATH] = {0};
		if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath)))
		{
			*szPath = _totupper(*szPath);
			//
			PathAddBackslash(szPath);
			strPath = szPath;
		}
		else
		{
			strPath = WizGetAppPath();
		}
	}
	return strPath;
}


CString WizGetAppDataLowPath()
{
	static CString strPath;
	if (strPath.IsEmpty())
	{
		const GUID WIZ_FOLDERID_LocalAppDataLow = {0xA520A1A4, 0x1780, 0x4FF6, {0xBD, 0x18, 0x16, 0x73, 0x43, 0xC5, 0xAF, 0x16}};
		#define WIZ_REFKNOWNFOLDERID const GUID
		//
		HMODULE hModule = GetModuleHandle(_T("shell32.dll"));
		if (hModule)
		{
			typedef HRESULT WINAPI Type_SHGetKnownFolderPath(WIZ_REFKNOWNFOLDERID* rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);
			//
			Type_SHGetKnownFolderPath* funSHGetKnownFolderPath = (Type_SHGetKnownFolderPath*)GetProcAddress(hModule, "SHGetKnownFolderPath");
			if (funSHGetKnownFolderPath)
			{
				PWSTR pwstrPath = NULL;
				HRESULT hr = funSHGetKnownFolderPath(&WIZ_FOLDERID_LocalAppDataLow, 0,  NULL, &pwstrPath);
				if (SUCCEEDED(hr))
				{
					strPath = CString(pwstrPath);
					CoTaskMemFree(pwstrPath);
					//
					WizPathAddBackslash(strPath);
					//
					WizEnsurePathExists(strPath);
				}
			}
		}
	}
	//
	return strPath;
}


CString WizGetUserPrfofilePath()
{
	static CString strPath;
	if (strPath.IsEmpty())
	{
		TCHAR szPath[MAX_PATH] = {0};
		if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, szPath)))
		{
			*szPath = _totupper(*szPath);
			//
			PathAddBackslash(szPath);
			strPath = szPath;
		}
	}
	return strPath;
}


HGLOBAL WizUnicodeTextToHGlobal(LPCWSTR lpszText)
{
	size_t nLen = wcslen(lpszText);
	//
	size_t nBufferLen = (nLen + 1) * sizeof(WCHAR);
	//
	HGLOBAL hGlobal = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, nBufferLen);
	//
	if (!hGlobal)
		return NULL;
	//
	LPWSTR pBuffer = (LPWSTR)GlobalLock(hGlobal);
	if (!pBuffer)
		return NULL;
	//
	wcscpy_s(pBuffer, nLen + 1, lpszText);
	//
	GlobalUnlock(hGlobal);
	//
	return hGlobal;
}

void WizPathRemoveBackslash(CString& strPath)
{
	if (strPath.IsEmpty())
		return;
	//
	TCHAR ch = strPath[strPath.GetLength() - 1];
	if (ch == '\\' || ch == '/')
		strPath.Delete(strPath.GetLength() - 1, 1);
}

CString WizExtractPathLastSubDir(LPCTSTR lpszPath)
{
	CString strPath(lpszPath);
	WizPathRemoveBackslash(strPath);
	//
	return WizExtractFileName(strPath);
}
void WizPathRemoveLastSubFolder(CString& strPath)
{
	WizPathRemoveBackslash(strPath);
	//
	strPath = WizExtractFilePath(strPath);
}

BOOL WizClipboardHGlobalToText(HGLOBAL hGlobal, CString& strText, BOOL bUnicode)
{
	BOOL bRet = FALSE;
	//
	if (bUnicode)
	{
		LPWSTR lptstr = (LPWSTR)GlobalLock(hGlobal); 
		if (lptstr)
		{
			strText = lptstr;
			bRet = TRUE;
		}
		GlobalUnlock(hGlobal);
	}
	else
	{
		LPCSTR lptstr = (LPCSTR)GlobalLock(hGlobal); 
		if (lptstr)
		{
			strText = CString(lptstr);
			bRet = TRUE;
		}
		GlobalUnlock(hGlobal);
	}
	//
	return bRet;
}

BOOL WizGetClipboardUnicodeText(CString& strText) 
{
	if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
		return FALSE;
	//
	if (!OpenClipboard(::GetForegroundWindow())) 
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	HGLOBAL hGlobal = GetClipboardData(CF_UNICODETEXT);
	if (hGlobal)
	{
		bRet = WizClipboardHGlobalToText(hGlobal, strText, TRUE);
	}
	CloseClipboard(); 
	//
	return bRet;
}
BOOL WizGetClipboardAnsiText(CString& strText) 
{
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return FALSE;
	//
	if (!OpenClipboard(::GetForegroundWindow())) 
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	HGLOBAL hGlobal = GetClipboardData(CF_TEXT);
	if (hGlobal)
	{
		bRet = WizClipboardHGlobalToText(hGlobal, strText, FALSE);
	}
	CloseClipboard(); 
	//
	return bRet;
}
BOOL WizGetClipboardText(CString& strText) 
{
	if (WizGetClipboardUnicodeText(strText))
		return TRUE;
	return WizGetClipboardAnsiText(strText);
}

void WizGetNextFileName(CString& strFileName) 
{
	CString strPath = WizExtractFilePath(strFileName);
	CString strTitle = WizExtractFileTitle(strFileName);
	CString strExt = WizExtractFileExt(strFileName);
	//
	//
	const UINT nMaxLength = MAX_PATH - 10;
	if (strFileName.GetLength() >= nMaxLength)
	{
		int nTitleLength = nMaxLength - (strPath.GetLength() + strExt.GetLength());
		if (nTitleLength <= 0)
		{
			TOLOG1(_T("File name is too long: %1"), strFileName);
			strTitle = WizIntToStr(GetTickCount());
		}
		else
		{
			ATLASSERT(strTitle.GetLength() >= nTitleLength);
			if (strTitle.GetLength() >= nTitleLength)
			{
				strTitle = strTitle.Left(nTitleLength);
			}
		}
		//
		strFileName = strPath + strTitle + strExt;
	}
	//
	if (!PathFileExists(strFileName))
		return;
	//
	int nPos = strTitle.ReverseFind('_');
	if (nPos != -1)
	{
		CString strTemp = strTitle.Right(strTitle.GetLength() - nPos - 1);
		if (strTemp == WizIntToStr(_ttoi(strTemp)))
		{
			strTitle.Delete(nPos, strTitle.GetLength() - nPos);
		}
	}
	//
	int nIndex = 2;
	while (PathFileExists(strFileName))
	{
		strFileName.Format(_T("%s%s_%d%s"), strPath, strTitle, nIndex, strExt);
		nIndex++;
	}
}
void WizGetNextPathName(CString& strPath) 
{
	if (!PathFileExists(strPath))
		return;
	//
	WizPathRemoveBackslash(strPath);
	WizGetNextFileName(strPath);
	WizPathAddBackslash(strPath);
}


CString WizComGetErrorInfo()
{
	CString str;
	CComQIPtr < IErrorInfo > spErrInfo;		// 声明 IErrorInfo 接口
	HRESULT hr = ::GetErrorInfo( 0, &spErrInfo );	// 取得接口
	if (S_OK != hr)
		return str;
	if (!spErrInfo)
		return str;
	//
	CComBSTR bstrDes;
	spErrInfo->GetDescription( &bstrDes );	// 取得错误描述
	//
	return CString(bstrDes);
}

CString WizGetErrorMessage(UINT nError) 
{
	LPVOID lpMsgBuf = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |  FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, nError, 0,  (LPTSTR) &lpMsgBuf, 0, NULL);
	//
	CString str = (LPTSTR)lpMsgBuf;
	LocalFree( lpMsgBuf );
	//
	if (str.IsEmpty())
	{
		//str = WizComGetErrorInfo();
		if (str.IsEmpty())
		{
			str = WizFormatString1(_T("GetLastError()=%1"), WizIntToStr(nError));
		}
	}
	//
	return str;
}
CString WizGetLastErrorMessage() 
{
	int nError = GetLastError();
	if (0 == nError)
		return CString();
	//
	return WizGetErrorMessage(nError);
}


CString WizFormatStringEx0(UINT nID)
{
	CString str = WizFormatString0(nID);
	int nPos = str.Find(_T("\n"));
	if (-1 != nPos)
	{
		str.Delete(0, nPos + 1);
	}
	//
	return str;
}


CString WizFormatString0(UINT nID)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return str;
}
CString WizFormatString1(LPCTSTR lpszFormat, LPCTSTR lpszParam1)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	//
	return str;
}
CString WizFormatString1(UINT nID, LPCTSTR lpszParam1)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString1(str, lpszParam1);
}
CString WizFormatString2(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	//
	return str;
}
CString WizFormatString2(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString2(str, lpszParam1, lpszParam2);
}
CString WizFormatString3(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	//
	return str;
}
CString WizFormatString3(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString3(str, lpszParam1, lpszParam2, lpszParam3);
}
CString WizFormatString4(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	//
	return str;
}
CString WizFormatString4(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString4(str, lpszParam1, lpszParam2, lpszParam3, lpszParam4);
}
CString WizFormatString5(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	str.Replace(_T("%5"), lpszParam5);
	//
	return str;
}
CString WizFormatString6(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	str.Replace(_T("%5"), lpszParam5);
	str.Replace(_T("%6"), lpszParam6);
	//
	return str;
}
CString WizFormatString7(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	str.Replace(_T("%5"), lpszParam5);
	str.Replace(_T("%6"), lpszParam6);
	str.Replace(_T("%7"), lpszParam7);
	//
	return str;
}
CString WizFormatString8(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	str.Replace(_T("%5"), lpszParam5);
	str.Replace(_T("%6"), lpszParam6);
	str.Replace(_T("%7"), lpszParam7);
	str.Replace(_T("%8"), lpszParam8);
	//
	return str;
}
CString WizFormatString9(LPCTSTR lpszFormat, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8, LPCTSTR lpszParam9)
{
	CString str(lpszFormat);
	//
	str.Replace(_T("%1"), lpszParam1);
	str.Replace(_T("%2"), lpszParam2);
	str.Replace(_T("%3"), lpszParam3);
	str.Replace(_T("%4"), lpszParam4);
	str.Replace(_T("%5"), lpszParam5);
	str.Replace(_T("%6"), lpszParam6);
	str.Replace(_T("%7"), lpszParam7);
	str.Replace(_T("%8"), lpszParam8);
	str.Replace(_T("%9"), lpszParam9);
	//
	return str;
}

CString WizFormatString5(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString5(str, lpszParam1, lpszParam2, lpszParam3, lpszParam4, lpszParam5);
}
CString WizFormatString6(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString6(str, lpszParam1, lpszParam2, lpszParam3, lpszParam4, lpszParam5, lpszParam6);
}
CString WizFormatString7(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString7(str, lpszParam1, lpszParam2, lpszParam3, lpszParam4, lpszParam5, lpszParam6, lpszParam7);
}
CString WizFormatString8(UINT nID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, LPCTSTR lpszParam4, LPCTSTR lpszParam5, LPCTSTR lpszParam6, LPCTSTR lpszParam7, LPCTSTR lpszParam8)
{
	CString str = WizTranslationsLoadString(nID);
	//
	return WizFormatString8(str, lpszParam1, lpszParam2, lpszParam3, lpszParam4, lpszParam5, lpszParam6, lpszParam7, lpszParam8);
}
void WizAppendErrorCode(CString& strMsg, UINT nCode)
{
	if (nCode == 0)
		return;
	//
	CString strErrorCodeFormat = WizTranslationsTranslateString(_T("\n\nError Code: %1"));
	CString strErrorCode = WizFormatString1(strErrorCodeFormat, WizIntToHex(nCode, TRUE));
	//
	strMsg += strErrorCode;
}

int WizMessageBox(LPCTSTR lpszText, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str(lpszText);
	if (str.IsEmpty())
	{
		if (nType & MB_OK)
			return IDOK;
		else if (nType & MB_YESNO)
			return IDYES;
		else
			return IDCANCEL;
	}
	//
#ifdef __AFX_H__
	return AfxMessageBox(str, nType);
#else
	if (!hwnd)
	{
		hwnd = ::GetForegroundWindow();
	}
	return MessageBox(hwnd, str, WizGlobal()->GetProductName(), nType);
#endif
}
int WizMessageBox(UINT nFormatID, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString0(nFormatID);
	//
	return WizMessageBox(str, nType, hwnd);
}
int WizMessageBox1(LPCTSTR lpszText, LPCTSTR lpszParam1, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString1(lpszText, lpszParam1);
	//
	return WizMessageBox(str, nType);
}
int WizMessageBox1(UINT nFormatID, LPCTSTR lpszParam1, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString1(nFormatID, lpszParam1);
	//
	return WizMessageBox(str, nType, hwnd);
}

int WizMessageBox2(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString2(nFormatID, lpszParam1, lpszParam2);
	//
	return WizMessageBox(str, nType, hwnd);
}

int WizMessageBox3(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, UINT nType /*= MB_OK | MB_ICONINFORMATION*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString3(nFormatID, lpszParam1, lpszParam2, lpszParam3);
	//
	return WizMessageBox(str, nType, hwnd);
}

int WizErrorMessageBox(LPCTSTR lpszText, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str(lpszText);
	WizAppendErrorCode(str, nErrorCode);
	//
	return WizMessageBox(str, MB_OK | MB_ICONERROR, hwnd);
}

int WizErrorMessageBox(UINT nFormatID, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString0(nFormatID);
	//
	return WizErrorMessageBox(str, nErrorCode, hwnd);
}

int WizErrorMessageBox1(LPCTSTR lpszText, LPCTSTR lpszParam1, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString1(lpszText, lpszParam1);
	//
	return WizErrorMessageBox(str, nErrorCode, hwnd);
}
int WizErrorMessageBox1(UINT nFormatID, LPCTSTR lpszParam1, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString1(nFormatID, lpszParam1);
	//
	return WizErrorMessageBox(str, nErrorCode, hwnd);
}

int WizErrorMessageBox2(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString2(nFormatID, lpszParam1, lpszParam2);
	//
	return WizErrorMessageBox(str, nErrorCode, hwnd);
}

int WizErrorMessageBox3(UINT nFormatID, LPCTSTR lpszParam1, LPCTSTR lpszParam2, LPCTSTR lpszParam3, UINT nErrorCode /*= 0*/, HWND hwnd /*= NULL*/)
{
	CString str = WizFormatString3(nFormatID, lpszParam1, lpszParam2, lpszParam3);
	//
	return WizErrorMessageBox(str, nErrorCode, hwnd);
}


static int CALLBACK WizBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
		case BFFM_INITIALIZED:		// sent when the browse dialog box has finished initializing. 
		{
			// set initial directory
			if (lpData)
			{
				LPCTSTR lpszPath = (LPCTSTR)lpData;
				if (lpszPath && *lpszPath)
				{
					::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
				}
			}
		}
		break;
	}
	return 0;
}

#ifndef WINCE
														
BOOL WizSelectFolder(HWND hWnd, LPCTSTR lpszTitle, CString& strRet)
{
	const UINT nBufferLength = MAX_PATH * 2;
	//
	TCHAR szInitialPath[nBufferLength];
	ZeroMemory(szInitialPath, sizeof(szInitialPath));
	//
	static CString strLast;
	//
	if (!strRet.IsEmpty())
	{
		_tcscpy_s(szInitialPath, nBufferLength, strRet);
	}
	else
	{
		_tcscpy_s(szInitialPath, nBufferLength, strLast);
	}
	//
	//
	TCHAR szDisplayName[MAX_PATH] = {0};
	//
	BROWSEINFO bi;
	bi.hwndOwner = hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szDisplayName;
    bi.lpszTitle = lpszTitle;
    bi.ulFlags = BIF_NEWDIALOGSTYLE;
    bi.lpfn = WizBrowseCallbackProc;
    bi.lParam = (LPARAM)szInitialPath;
    bi.iImage = 0;
	//
	LPITEMIDLIST pIDL = SHBrowseForFolder(&bi);
	//
	if (!pIDL)
		return FALSE;
	//
	TCHAR szPath[MAX_PATH] = {0};
	if (!SHGetPathFromIDList(pIDL, szPath))
		return FALSE;
	//
	strRet = szPath;
	WizPathAddBackslash(strRet);
	//
	strLast = strRet;
	//
	CComPtr<IMalloc> spMalloc;
	if (SUCCEEDED(SHGetMalloc(&spMalloc)))
	{
		spMalloc->Free(pIDL);
	}
	//
	return TRUE;
}

BOOL WizSelectFolder(HWND hWnd, UINT nID, CString& strRet)
{
	CString str = WizTranslationsLoadString(nID);
	return WizSelectFolder(hWnd, str, strRet);
}
#endif

BOOL WizConvertStringFromUTF8(const char* lpszUTF8Text, CString& strText)
{
	BOOL bRet = FALSE;
	//
	size_t nBufferLen = strlen(lpszUTF8Text) + 1;
    wchar_t * pwcharBuffer = new wchar_t[nBufferLen];
    if (pwcharBuffer)
    {
        memset(pwcharBuffer, 0, sizeof(wchar_t) * (nBufferLen));
        MultiByteToWideChar(CP_UTF8, 0, lpszUTF8Text, -1, pwcharBuffer, int(nBufferLen));
		strText = pwcharBuffer;
        delete [] pwcharBuffer;
		//
		bRet = TRUE;
    }
	return bRet;
}
BOOL WizConvertStringToUTF8(const LPCWSTR lpszUnicodeText, CStringA& strText)
{
	BOOL bRet = FALSE;
	//
	size_t nBufferLen = (wcslen(lpszUnicodeText) + 1) * 4;
    char * pcharBuffer = new char[nBufferLen];
    if (pcharBuffer)
    {
        memset(pcharBuffer, 0, sizeof(char) * (nBufferLen));
        WideCharToMultiByte(CP_UTF8, 0, lpszUnicodeText, -1, pcharBuffer, int(nBufferLen), NULL, NULL);
		strText = pcharBuffer;
        delete [] pcharBuffer;
		//
		bRet = TRUE;
    }
	return bRet;
}

BOOL WizHTMLTextIsLink(LPCTSTR lpszText)
{
    CString strTemp(lpszText);
	//
	strTemp.Trim();
	//
	strTemp.MakeLower();
	//
    return (!strTemp.IsEmpty()
        && strTemp.Find(_T("\r")) == -1
        && strTemp.Find(_T("\n")) == -1
        && (strTemp.Find(_T("http://")) == 0 || strTemp.Find(_T("https://")) == 0 || strTemp.Find(_T("file://")) == 0));
}

void WizShellOpenFileWith(LPCTSTR lpszFileName)
{
	CString strCommand;
	strCommand.Format(_T("shell32.dll OpenAs_RunDLL %s"), lpszFileName);
	ShellExecute(NULL, _T("open"), _T("rundll32.exe"), strCommand, NULL, SW_SHOW);
}

#ifndef WINCE
WIZSYSTEMVERSION WizGetSystemVersion()
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	{
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			return svUnknown;
	}
	//
	switch (osvi.dwPlatformId)
	{
		// Test for the Windows NT product family.
	case VER_PLATFORM_WIN32_NT:
		// Test for the specific product.
		if ( osvi.dwMajorVersion >= 6)
		{
			if (osvi.dwMinorVersion == 1)
				return svWin7;
			//
			return svWinVista;
		}
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
			return svWin2003;
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
			return svWinXP;
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
			return svWin2000;
		if ( osvi.dwMajorVersion <= 4 )
			return svWinNT;
		break;
		// Test for the Windows Me/98/95.
	case VER_PLATFORM_WIN32_WINDOWS:
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
			return svWin95;
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
			return svWin98;
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
			return svWinME;
		break;
	case VER_PLATFORM_WIN32s:
		return svWin32s;
	}
	return svUnknown; 
}

BOOL WizIsVista()
{
	return WizGetSystemVersion() >= svWinVista;
}

#endif


#ifdef WINCE
BOOL WizMd5File(LPCTSTR lpszFileName, DWORD arrayMd5[4])
{
	ULONG nSize = ULONG(WizGetFileSize(lpszFileName));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	if (FILE* fp = _tfopen(lpszFileName, _T("rb")))
	{
		fread(pBuffer, nSize, 1, fp);
		//
		WizMd5(pBuffer, DWORD(nSize), (BYTE*)arrayMd5);
		//
		bRet = TRUE;
		//
		// After _fdopen, close with fclose, not _close.
		fclose(fp);
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}
#else
BOOL WizMd5File(LPCTSTR lpszFileName, DWORD arrayMd5[4])
{
	CComPtr<IStream> spStream = ::WizCreateReadOnlyStreamOnFile(lpszFileName);
	if (!spStream)
		return FALSE;
	//
	if (!WizMd5(spStream, (BYTE*)arrayMd5))
		return FALSE;
	//
	return TRUE;
}
#endif
CString WizMd5FileString(LPCTSTR lpszFileName)
{
	DWORD arrayMd5[4] = {0, 0, 0, 0};
	if (!WizMd5File(lpszFileName, arrayMd5))
		return CString();
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%08x%08x%08x%08x"), arrayMd5[0], arrayMd5[1], arrayMd5[2], arrayMd5[3]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%08x%08x%08x%08x"), arrayMd5[0], arrayMd5[1], arrayMd5[2], arrayMd5[3]);
#endif
	//
	return CString(sz);
}

CString WizGetSystemPath()
{
	TCHAR szPath[1024] = {0};
	GetSystemDirectory(szPath, 1024);
	CString strPath(szPath);
	WizPathAddBackslash(strPath);
	return strPath;
}
CString WizGetWindowsPath()
{
	TCHAR szPath[1024] = {0};
	GetWindowsDirectory(szPath, 1024);
	CString strPath(szPath);
	WizPathAddBackslash(strPath);
	return strPath;
}
CString WizGetSystemTempPath()
{
	TCHAR szPath[1024] = {0};
	GetTempPath(1024, szPath);
	CString strPath(szPath);
	WizPathAddBackslash(strPath);
	return strPath;
}
CString WizGetProgramFilesPath()
{
	CString strPath;
    TCHAR szPath[MAX_PATH] = {0};
    if(SUCCEEDED(SHGetSpecialFolderPath(NULL, szPath, CSIDL_PROGRAM_FILES, TRUE)))
    {
        strPath = szPath;
		WizPathAddBackslash(strPath);
    }
	return strPath;
}
BYTE WizGetAccelVirt(LPCTSTR lpsz)
{
	CString str(lpsz);
	str.MakeLower();
	BYTE b = 0;
	if (str.Find(_T("ctrl")) != -1)
		b |= FCONTROL;
	if (str.Find(_T("shift")) != -1)
		b |= FSHIFT;
	if (str.Find(_T("alt")) != -1)
		b |= FALT;
	return b;
}

int WizComparePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2)
{
	CString strPath1 = WizGetLongFileName(lpszPath1);
	CString strPath2 = WizGetLongFileName(lpszPath2);
	//
	WizPathRemoveBackslash(strPath1);
	WizPathRemoveBackslash(strPath2);
	//
	return strPath1.CompareNoCase(strPath2);
}
#ifndef WINCE

WORD WizGetAccelKey(LPCTSTR lpsz)
{
	CString str;
	LPCTSTR p = _tcschr(lpsz, _T('+'));
	if (p)
		str = p + 1;
	else
		str = lpsz;
	//
	str.Trim();
	str.MakeUpper();
	//
	if (str.GetLength() == 1)
	{
		return str[0];
	}
	else if (str.GetLength() == 2 && str[0] == _T('F'))
	{
		if (str[1] >=  _T('1') && str[1] <= _T('9'))
		{
			return VK_F1 + (str[1] -  _T('0'));
		}
	}
	else if (str.GetLength() == 3 && str[0] ==  _T('F'))
	{
		if (str[1] ==  _T('1') && str[2] >=  _T('0') && str[2] <=  _T('9'))
		{
			return VK_F10 + (str[2] -  _T('0'));
		}
	}
	else if (str ==  _T("UP"))
	{
		return VK_UP;
	}
	else if (str ==  _T("DOWN"))
	{
		return VK_DOWN;
	}
	else if (str ==  _T("LEFT"))
	{
		return VK_LEFT;
	}
	else if (str ==  _T("RIGHT"))
	{
		return VK_RIGHT;
	}
	return 0;
}
WORD WizGetHotKeyModifiers(LPCTSTR lpsz)
{
	BYTE bVirt = WizGetAccelVirt(lpsz);
	//
	WORD wMod = 0;
	if (bVirt & FCONTROL)
		wMod |= HOTKEYF_CONTROL;
	if (bVirt & FALT)
		wMod |= HOTKEYF_ALT;
	if (bVirt & FSHIFT)
		wMod |= HOTKEYF_SHIFT;
	//
	return wMod;
}
WORD WizGetHotKeyKey(LPCTSTR lpsz)
{
	return WizGetAccelKey(lpsz);
}
#endif
////////////////////////////////////////////////////////////////////////

// WizGetErrorInfo
// Summary of Routines
//
// This function displays basic error information for an error object
// that doesn't support the IErrorRecords interface.
//
////////////////////////////////////////////////////////////////////////
HRESULT WizGetErrorInfo(HRESULT hrReturned, IErrorInfo* pIErrorInfo, CString& strError)
{
	// Get the description of the error.
	CComBSTR bstrDescription;
	HRESULT hr = pIErrorInfo->GetDescription(&bstrDescription);
	// Get the source of the error -- this will be the window title.
	CComBSTR bstrSource;
	hr = pIErrorInfo->GetSource(&bstrSource);
	// Display this error information.
	strError.Format(_T("ErrorInfo:  HResult: 0x%08x,\nDescription: %s\nSource:%s\n"),
		hrReturned, 
		CString(bstrDescription),
		CString(bstrSource));
	//
	return hr;
}

#if (_WIN32_WINNT >= 0x0500)

CString WizGetComputerName()
{
	TCHAR szComputerName[MAX_PATH] = {0};
	DWORD dwLen = MAX_PATH;
	GetComputerNameEx(ComputerNameNetBIOS, szComputerName, &dwLen);
	//
	return CString(szComputerName);
}

#endif

void WizDeleteAllFilesInFolder(LPCTSTR lpszPath)
{
	CString strPath = CString(lpszPath);
	WizPathAddBackslash(strPath);
	//
	strPath += _T("*.*");
	//
	TCHAR szBuffer[1024];
	ZeroMemory(szBuffer, 1024);
	//
	_tcscpy_s(szBuffer, 1024, strPath);
	//append a null char
	szBuffer[strPath.GetLength() + 1] = _T('\0');
	//
	SHFILEOPSTRUCT shi =
	{
		NULL, 
		FO_DELETE, 
		szBuffer, 
		NULL, 
		FOF_NOCONFIRMATION  | FOF_SILENT, 
		FALSE, 
		NULL, 
		NULL
	};
	SHFileOperation(&shi);
}

void WizDeleteFolder(LPCTSTR lpszPath)
{
	CString strPath = CString(lpszPath);
	WizPathAddBackslash(strPath);
	//
	TCHAR szBuffer[1024];
	ZeroMemory(szBuffer, 1024);
	//
	CString strFiles = strPath + _T("*.*");
	_tcscpy_s(szBuffer, 1024, strPath);
	//append a null char
	szBuffer[strPath.GetLength() + 1] = _T('\0');
	//
	SHFILEOPSTRUCT shi =
	{
		NULL, 
		FO_DELETE, 
		szBuffer, 
		NULL, 
		FOF_NOCONFIRMATION  | FOF_SILENT, 
		FALSE, 
		NULL, 
		NULL
	};
	SHFileOperation(&shi);
	//
	RemoveDirectory(lpszPath);
}

CString WizGetAppSettingsFileName()
{
	CString strFileName = ::WizGetAppPath() + WizGetProductName() + _T(".ini");
	return strFileName;
}

CString WizGetSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDef)
{
	CString strFileName = WizGetAppSettingsFileName();
	//
	return WizIniReadStringDef(strFileName, lpszSection, lpszValueName, lpszDef);
}


CString WizGetSecuteSettingsFileName()
{
	CString strAppPath = WizGetAppPath();
	CString strOEMFileName = strAppPath + _T("oem.ini");
	if (PathFileExists(strOEMFileName))
		return strOEMFileName;
	//
	CString strConfigFileName = strAppPath + _T("config.dat");
	return strConfigFileName;
}

CString WizGetSecuteSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bAllowEmpty)
{
	static CWizIniFileEx ini;
	static bool b = true;
	if (b)
	{
		b = false;
		//
		CString strText;
#ifdef _WIZ_SECUTE_TEXT
		strText = _WIZ_SECUTE_TEXT;
#else
		CString strFileName = WizGetSecuteSettingsFileName();
		if (0 == WizExtractFileName(strFileName).CompareNoCase(_T("oem.ini")))
		{
			WizLoadUnicodeTextFromFile(strFileName, strText);
		}
		else
		{
			WizSimpleDecryptStringFromFile("{F09B7828-4121-4392-9B80-78BD4C5526B3}", strFileName, strText);
		}
#endif
		//
		ini.LoadFromText(strText);
	}
	//
	CString str = ini.GetStringDef(lpszSection, lpszValueName, _T(""));
	if (str.IsEmpty())
	{
		if (!bAllowEmpty)
		{
			ATLASSERT(FALSE);
			exit(-1);
		}
	}
	//
	return str;
}

CString WizInnerGetSecuteSettings(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bAllowEmpty)
{
	static CWizIniFileEx ini;
	static bool b = true;
	if (b)
	{
		b = false;
		//
		CString strText;
#ifdef _WIZ_SECUTE_TEXT
		strText = _WIZ_SECUTE_TEXT;
#else
		CString strConfigFileName = WizGetAppPath() + _T("config.dat");
		WizSimpleDecryptStringFromFile("{F09B7828-4121-4392-9B80-78BD4C5526B3}", strConfigFileName, strText);
#endif
		//
		ini.LoadFromText(strText);
	}
	//
	CString str = ini.GetStringDef(lpszSection, lpszValueName, _T(""));
	if (str.IsEmpty())
	{
		if (!bAllowEmpty)
		{
			ATLASSERT(FALSE);
			exit(-1);
		}
	}
	//
	return str;

}


CString WizGetProductName()
{
	static CString strProductName;
	if (!strProductName.IsEmpty())
		return strProductName;
	//
	strProductName = WizGetSecuteSettings(_T("Common"), _T("ProductName"), FALSE);
	ATLASSERT(!strProductName.IsEmpty());
	//
	return strProductName;
}

CString WizGetCompanyName()
{
	static CString strCompanyName;
	if (!strCompanyName.IsEmpty())
		return strCompanyName;
	//
	strCompanyName = WizGetSecuteSettings(_T("Common"), _T("CompanyName"), TRUE);
	ATLASSERT(!strCompanyName.IsEmpty());
	//
	return strCompanyName;
}


CWizGlobalDefault::CWizGlobalDefault(BOOL bClearTempFiles /*= FALSE*/)
	: m_strProductName(WizGetProductName())
	, m_bClearTempFiles(bClearTempFiles)
{
}

CWizGlobalDefault::~CWizGlobalDefault()
{
	if (!m_strProductName.IsEmpty() && m_bClearTempFiles)
	{
		if (!m_strTempPath.IsEmpty())
		{
			WizDeleteAllFilesInFolder(m_strTempPath);
		}
	}
}
void CWizGlobalDefault::WriteLog(LPCTSTR lpszMsg)
{
}
CString CWizGlobalDefault::GetTempPath()
{
	if (m_strTempPath.IsEmpty())
	{
		m_strTempPath = WizGetSystemTempPath();
		if (!m_strProductName.IsEmpty())
		{
			m_strTempPath += m_strProductName;
			WizPathAddBackslash(m_strTempPath);
			WizEnsurePathExists(m_strTempPath);
		}
	}
	//
	return m_strTempPath;
}
BOOL CWizGlobalDefault::IsWizResourceURL(LPCTSTR lpszURL)
{
	LPCTSTR lpszDefault = WIZ_HTML_RESOURCEFILE_PATH;
	return 0 == _tcsncmp(lpszURL, lpszDefault, _tcslen(lpszDefault));
}
void CWizGlobalDefault::OnURLDownloadToFileProgress(ULONG ulProgress, ULONG ulProgressMax, LPCWSTR wszStatusText)
{
}
CString CWizGlobalDefault::GetProductName()
{
	return m_strProductName;
}


namespace wizmd5
{

typedef unsigned char *POINTER;
typedef unsigned short int UINT2;
typedef unsigned long int UINT4;

/* MD5 context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;


#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

const unsigned char PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions.
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}

/* Note: Replace "for loop" with standard memset if possible.
*/
void MD5_memset (POINTER output, int value, unsigned int len)
{
	unsigned int i;
	
	for (i = 0; i < len; i++)
		((char *)output)[i] = (char)value;
}


/* Decodes input (unsigned char) into output (UINT4). Assumes len is
a multiple of 4.
*/
void Decode (UINT4 *output, const unsigned char *input, unsigned int len)
{
	unsigned int i, j;
	
	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
		(((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* MD5 basic transformation. Transforms state based on block.
*/
void MD5Transform (UINT4 state[4], const unsigned char block[64])
{
	UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	
	Decode (x, block, 64);
	
	/* Round 1 */
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
	
	/* Round 2 */
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
	
	/* Round 3 */
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
	
	/* Round 4 */
	II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
	
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	
	/* Zeroize sensitive information.
	*/
	MD5_memset ((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
a multiple of 4.
*/
void Encode (unsigned char *output, UINT4 *input, unsigned int len)
{
	unsigned int i, j;
	
	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
	}
}


/* Note: Replace "for loop" with standard memcpy if possible.
*/

void MD5_memcpy (POINTER output, POINTER input, unsigned int len)
{
	unsigned int i;
	
	for (i = 0; i < len; i++)
		output[i] = input[i];
}


/* MD5 initialization. Begins an MD5 operation, writing a new context.
*/
void MD5Init (MD5_CTX *context)
{
	context->count[0] = context->count[1] = 0;
	/* Load magic initialization constants.
	*/
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
void MD5Update (MD5_CTX *context, const unsigned char *input, unsigned int inputLen)
{
	unsigned int i, index, partLen;
	
	/* Compute number of bytes mod 64 */
	index = (unsigned int)((context->count[0] >> 3) & 0x3F);
	
	/* Update number of bits */
	if ((context->count[0] += ((UINT4)inputLen << 3))
		< ((UINT4)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((UINT4)inputLen >> 29);
	
	partLen = 64 - index;
	
	/* Transform as many times as possible.
	*/
	if (inputLen >= partLen) {
		MD5_memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
		MD5Transform (context->state, context->buffer);
		
		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);
		
		index = 0;
	}
	else
		i = 0;
	
	/* Buffer remaining input */
	MD5_memcpy
		((POINTER)&context->buffer[index], (POINTER)&input[i],
		inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
the message digest and zeroizing the context.
*/
void MD5Final (unsigned char digest[16], MD5_CTX *context)
{
	unsigned char bits[8];
	unsigned int index, padLen;
	
	/* Save number of bits */
	Encode (bits, context->count, 8);
	
	/* Pad out to 56 mod 64.
	*/
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (context, PADDING, padLen);
	
	/* Append length (before padding) */
	MD5Update (context, bits, 8);
	
	/* Store state in digest */
	Encode (digest, context->state, 16);
	
	/* Zeroize sensitive information.
	*/
	MD5_memset ((POINTER)context, 0, sizeof (*context));
}


}




void WizMd5(const BYTE* pBuffer, DWORD dwLen, BYTE* pResult)
{
	wizmd5::MD_CTX context;
	wizmd5::MDInit (&context);
	wizmd5::MDUpdate (&context, pBuffer, dwLen);
	wizmd5::MDFinal (pResult, &context);
}

CString WizMd5String(const BYTE* pBuffer, DWORD dwLen)
{
	if (0 == dwLen)
		return CString();
	//
	DWORD dwBuffer[4] = {0, 0, 0, 0};
	//
	WizMd5(pBuffer, dwLen, (BYTE *)&dwBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%8x%8x%8x%8x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%8x%8x%8x%8x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#endif
	//
	return CString(sz);
}


BOOL WizMd5(IStream* pStream, BYTE* pResult)
{
	wizmd5::MD_CTX context;
	//
	wizmd5::MDInit (&context);
	//
	const UINT BUFFER_SIZE = 1024;
	//
	BOOL bRet = FALSE;
	//
	BYTE* pBuffer = NULL;
	try
	{
		WizStreamSeekToBegin(pStream);
		//
		pBuffer = new BYTE[BUFFER_SIZE];
		//
		int nSize = (int)WizStreamGetSize(pStream);
		int nCount = nSize / BUFFER_SIZE;
		//
		for (int i = 0; i < nCount; i++)
		{
			if (!WizStreamRead(pStream, pBuffer, BUFFER_SIZE))
				throw std::exception("Failed to read data from stream!");
			wizmd5::MDUpdate (&context, pBuffer, BUFFER_SIZE);
		}
		//
		int nLast = nSize % BUFFER_SIZE;
		if (nLast)
		{
			if (!WizStreamRead(pStream, pBuffer, nLast))
				throw std::exception("Failed to read data from stream!");
			wizmd5::MDUpdate (&context, pBuffer, nLast);
		}
		//
		bRet = TRUE;
	}
	catch (const std::exception& err)
	{
		TOLOG(CString(err.what()));
	}
	//
	delete [] pBuffer;
	//
	wizmd5::MDFinal (pResult, &context);
	//
	WizStreamSeekToBegin(pStream);
	//
	return bRet;
}


CString WizMd5String(IStream* pStream)
{
	if (0 == WizStreamGetSize(pStream))
		return CString();
	//
	DWORD dwBuffer[4] = {0, 0, 0, 0};
	//
	WizMd5(pStream, (BYTE *)&dwBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%8x%8x%8x%8x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%8x%8x%8x%8x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#endif
	//
	return CString(sz);
}

CString WizMd5StringNoSpace(const BYTE* pBuffer, DWORD dwLen)
{
	if (0 == dwLen)
		return CString();
	//
	DWORD dwBuffer[4] = {0, 0, 0, 0};
	//
	WizMd5(pBuffer, dwLen, (BYTE *)&dwBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%08x%08x%08x%08x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%08x%08x%08x%08x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#endif
	//
	return CString(sz);
}
CString WizMd5StringNoSpace(IStream* pStream)
{
	if (0 == WizStreamGetSize(pStream))
		return CString();
	//
	DWORD dwBuffer[4] = {0, 0, 0, 0};
	//
	WizMd5(pStream, (BYTE *)&dwBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%08x%08x%08x%08x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%08x%08x%08x%08x"), dwBuffer[0], dwBuffer[1], dwBuffer[2], dwBuffer[3]);
#endif
	//
	return CString(sz);
}

CString WizMd5StringNoSpaceJava(const BYTE* pBuffer, DWORD dwLen)
{
	if (0 == dwLen)
		return CString();
	//
	BYTE szBuffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//
	WizMd5(pBuffer, dwLen, szBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"), 
		szBuffer[0], szBuffer[1], szBuffer[2], szBuffer[3],
		szBuffer[4], szBuffer[5], szBuffer[6], szBuffer[7],
		szBuffer[8], szBuffer[9], szBuffer[10], szBuffer[11],
		szBuffer[12], szBuffer[13], szBuffer[14], szBuffer[15]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"), 
		szBuffer[0], szBuffer[1], szBuffer[2], szBuffer[3],
		szBuffer[4], szBuffer[5], szBuffer[6], szBuffer[7],
		szBuffer[8], szBuffer[9], szBuffer[10], szBuffer[11],
		szBuffer[12], szBuffer[13], szBuffer[14], szBuffer[15]);
#endif
	//
	return CString(sz);
}

CString WizMd5StringNoSpaceJava(IStream* pStream)
{
	if (0 == WizStreamGetSize(pStream))
		return CString();
	//
	BYTE szBuffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//
	WizMd5(pStream, szBuffer);
	//
	TCHAR sz[MAX_PATH] = {0};
#ifdef WINCE
	_stprintf(sz, _T("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"), 
		szBuffer[0], szBuffer[1], szBuffer[2], szBuffer[3],
		szBuffer[4], szBuffer[5], szBuffer[6], szBuffer[7],
		szBuffer[8], szBuffer[9], szBuffer[10], szBuffer[11],
		szBuffer[12], szBuffer[13], szBuffer[14], szBuffer[15]);
#else
	_stprintf_s(sz, MAX_PATH, _T("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"), 
		szBuffer[0], szBuffer[1], szBuffer[2], szBuffer[3],
		szBuffer[4], szBuffer[5], szBuffer[6], szBuffer[7],
		szBuffer[8], szBuffer[9], szBuffer[10], szBuffer[11],
		szBuffer[12], szBuffer[13], szBuffer[14], szBuffer[15]);
#endif
	//
	return CString(sz);
}
CString WizMd5StringNoSpace(LPCTSTR lpszText)
{
	return WizPasswordToMd5StringNoSpace(lpszText);
}

void WizEnumFiles(LPCTSTR lpszPath, LPCTSTR lpszExts, CWizStdStringArray& arrayFiles, UINT uFlags)
{
	BOOL bIncludeHiddenFile = uFlags & EF_INCLUDEHIDDEN;
	BOOL bIncludeSubDir = uFlags & EF_INCLUDESUBDIR;
	//
	CString strPath(lpszPath);
	WizPathAddBackslash(strPath);
	//
	CString strFindPath = strPath + _T("*.*");
	//
	CString strExts(lpszExts);
	strExts.Append(_T(";"));
	//
	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));
	//
	HANDLE hFind = FindFirstFile(strFindPath, &fd);
	while(hFind != INVALID_HANDLE_VALUE)
	{
		CString strName = fd.cFileName;
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (bIncludeSubDir)
			{
				if (strName != _T(".") && strName != _T(".."))
				{
					WizEnumFiles(strPath + strName + _T("\\"), lpszExts, arrayFiles, uFlags);
				}
			}
		}
		else if (bIncludeHiddenFile || !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			CString strExt = WizExtractFileExt(strName);
			CString strTest = CString(_T("*")) + strExt +  _T(";");
			if (0 == _tcsicmp(lpszExts, _T("*.*")) 
				|| (!strExt.IsEmpty() && NULL != WizStrStrI_Ptr(strExts, strTest)))
			{
				arrayFiles.push_back(CStringW(strPath + strName));
			}
		}
		if (!FindNextFile(hFind, &fd))
			break;
	}
	FindClose(hFind);
}

void WizEnumFolders(LPCTSTR lpszPath, CWizStdStringArray& arrayFolders, UINT uFlags)
{
	BOOL bIncludeHiddenFile = uFlags & EF_INCLUDEHIDDEN;
	BOOL bIncludeSubDir = uFlags & EF_INCLUDESUBDIR;
	//
	CString strPath(lpszPath);
	WizPathAddBackslash(strPath);
	//
	CString strFindPath = strPath + _T("*.*");
	//
	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));
	//
	HANDLE hFind = FindFirstFile(strFindPath, &fd);
	while(hFind != INVALID_HANDLE_VALUE)
	{
		CString strName = fd.cFileName;
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (bIncludeHiddenFile || !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				if (strName != _T(".") && strName != _T(".."))
				{
					CString strSubPath = WizGetLongFileName(strPath + strName);
					//
					arrayFolders.push_back(CStringW(strSubPath));
					//
					if (bIncludeSubDir)
					{
						WizEnumFolders(strSubPath, arrayFolders, uFlags);
					}
				}
			}
		}
		if (!FindNextFile(hFind, &fd))
			break;
	}
	FindClose(hFind);
}
BOOL WizRegReadString(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  LPTSTR pszValue, DWORD dwLen)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwType = REG_SZ;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, lpszValueName, 0, &dwType, (BYTE *)(pszValue), &dwLen))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegReadInt32(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  int& nValue)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		//
		DWORD dwValue = 0;
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof(DWORD);
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, lpszValueName, 0, &dwType, (BYTE *)(&dwValue), &dwSize))
		{
			nValue = int(dwValue);
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegReadInt64(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  __int64& nValue)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwType = REG_QWORD;
		DWORD dwSize = sizeof(__int64);
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, lpszValueName, 0, &dwType, (BYTE *)(&nValue), &dwSize))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegReadBool(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL& bValue)
{
	int nRet = 0;
	if (!WizRegReadInt32(hRootKey, lpszKey, lpszValueName, nRet))
		return FALSE;
	bValue = nRet ? TRUE : FALSE;
	return TRUE;
} 
BOOL WizRegReadBin(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BYTE* pBuffer, DWORD dwLen)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwType = REG_BINARY;
		DWORD dwSize = dwLen;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, lpszValueName, 0, &dwType, (BYTE *)pBuffer, &dwSize))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegReadPtr(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t& ptr)
{
	return WizRegReadBin(hRootKey, lpszKey, lpszValueName, (BYTE *)&ptr, sizeof(intptr_t));
}

BOOL WizRegWriteString(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, LPCTSTR lpszValue)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		RegCreateKeyEx(hRootKey, lpszKey, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, 0);
	}
	//
	if (hKey)
	{
		if (ERROR_SUCCESS == RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE *)lpszValue, (DWORD)((_tcslen(lpszValue) + 1) * sizeof(TCHAR))))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}

BOOL WizRegWriteInt32(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, int nValue)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		RegCreateKeyEx(hRootKey, lpszKey, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, 0);
	}
	if (hKey)
	{
		DWORD dwValue = nValue;
		//
		if (ERROR_SUCCESS == RegSetValueEx(hKey, lpszValueName, 0, REG_DWORD, (BYTE *)(&dwValue), sizeof(DWORD)))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegWriteInt64(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, __int64 nValue)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		RegCreateKeyEx(hRootKey, lpszKey, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, 0);
	}
	if (hKey)
	{
		if (ERROR_SUCCESS == RegSetValueEx(hKey, lpszValueName, 0, REG_QWORD, (BYTE *)(&nValue), sizeof(__int64)))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}

BOOL WizRegWriteBool(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL bVal)
{
	return WizRegWriteInt32(hRootKey, lpszKey, lpszValueName, bVal ? 1 : 0);
}

BOOL WizRegWriteBin(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BYTE* pBuffer, DWORD dwLen)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		RegCreateKeyEx(hRootKey, lpszKey, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, 0);
	}
	if (hKey)
	{
		if (ERROR_SUCCESS == RegSetValueEx(hKey, lpszValueName, 0, REG_BINARY, pBuffer, dwLen))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}
BOOL WizRegWritePtr(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t ptr)
{
	return WizRegWriteBin(hRootKey, lpszKey, lpszValueName, (BYTE *)&ptr, sizeof(intptr_t));
}

BOOL WizRegDeleteValue(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey) && hKey)
	{
		if (ERROR_SUCCESS == RegDeleteValue(hKey, lpszValueName))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}

CString WizRegReadStringDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, LPCTSTR lpszDefault)
{
	const int nBufferLen = 1024;
	TCHAR szBuffer[nBufferLen] = {0};
	ZeroMemory(szBuffer, nBufferLen * sizeof(TCHAR));
	//
	if (!WizRegReadString(hRootKey, lpszKey, lpszValueName, szBuffer, nBufferLen))
	{
		if (lpszDefault)
		{
			_tcscpy_s(szBuffer, 1024, lpszDefault);
		}
	}
	//
	return CString(szBuffer);
}

int WizRegReadInt32Def(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, int nDefault)
{
	int nRet = 0;
	if (!WizRegReadInt32(hRootKey, lpszKey, lpszValueName, nRet))
	{
		nRet = nDefault;
	}
	return nRet;
}

__int64 WizRegReadInt64Def(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, __int64 nDefault)
{
	__int64 nRet = 0;
	if (!WizRegReadInt64(hRootKey, lpszKey, lpszValueName, nRet))
	{
		nRet = nDefault;
	}
	return nRet;
}

BOOL WizRegReadBoolDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName,  BOOL bDefault)
{
	BOOL bRet = FALSE;
	if (!WizRegReadBool(hRootKey, lpszKey, lpszValueName, bRet))
	{
		return bRet = bDefault;
	}
	return bRet;
} 

intptr_t WizRegReadPtrDef(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName, intptr_t nDef)
{
	intptr_t nRet = 0;
	if (!WizRegReadBin(hRootKey, lpszKey, lpszValueName, (BYTE *)&nRet, sizeof(intptr_t)))
	{
		nRet = nDef;
	}
	return nRet;
}
BOOL WizRegKeyExists(HKEY hRootKey, LPCTSTR lpszKey)
{
	HKEY hKey = NULL;
	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		RegCloseKey(hKey);
	}
	return hKey ? TRUE : FALSE;
}
BOOL WizRegCreateKey(HKEY hRootKey, LPCTSTR lpszKey)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		RegCreateKeyEx(hRootKey, lpszKey, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, 0);
	}
	//
	if (hKey)
	{
		bRet = TRUE;
		RegCloseKey(hKey);
	}
	//
	return bRet;
}

BOOL WizRegValueExists(HKEY hRootKey, LPCTSTR lpszKey, LPCTSTR lpszValueName)
{
	BOOL bRet = FALSE;
	//
	HKEY hKey = NULL;
	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwType = REG_DWORD;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, lpszValueName, 0, &dwType, NULL, 0))
		{
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	//
	return bRet;
}
#ifndef WINCE
BOOL WizRegDeleteKey(HKEY hRootKey, LPCTSTR lpszKey)
{
	return ERROR_SUCCESS == SHDeleteKey(hRootKey, lpszKey);
}
#endif

BOOL WizRegEnumKey(HKEY hRootKey, LPCTSTR lpszKey, CWizStdStringArray& arrayKeyNames)
{
	BOOL bRet = FALSE;
	//
	HKEY hKey = NULL;
	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwSubKeys = 0;
		if (ERROR_SUCCESS == RegQueryInfoKey(hKey, NULL, NULL, NULL, &dwSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
		{
			for (DWORD i = 0; i < dwSubKeys; i++)
			{ 
				TCHAR szName[MAX_PATH] = {0};
				DWORD dwName = MAX_PATH;
				if (ERROR_SUCCESS == RegEnumKeyEx(hKey, i,szName, &dwName, NULL, NULL, NULL, NULL))
				{
					arrayKeyNames.push_back(CStringW(szName));
				}
			}
			bRet = TRUE;
		} 
		RegCloseKey(hKey);
	}
	return bRet;
}

BOOL WizRegEnumValueName(HKEY hRootKey, LPCTSTR lpszKey, CWizStdStringArray& arrayValueNames)
{
	BOOL bRet = FALSE;
	//
	HKEY hKey = NULL;
	if (ERROR_SUCCESS == RegOpenKeyEx(hRootKey, lpszKey, 0, KEY_READ, &hKey))
	{
		DWORD dwValues = 0;
		if (ERROR_SUCCESS == RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &dwValues, NULL, NULL, NULL, NULL))
		{
			for (DWORD i = 0; i < dwValues; i++)
			{ 
				TCHAR szName[MAX_PATH] = {0};
				DWORD dwName = MAX_PATH;
				if (ERROR_SUCCESS == RegEnumValue(hKey, i,szName, &dwName, NULL, NULL, NULL, NULL))
				{
					arrayValueNames.push_back(CStringW(szName));
				}
			}
			bRet = TRUE;
		} 
		RegCloseKey(hKey);
	}
	return bRet;
}


LPTSTR WizStrStrI_Ptr(LPCTSTR lpsz1, LPCTSTR lpsz2)
{
	return StrStrI(lpsz1, lpsz2);
}
LPTSTR WizStrRStrI_Ptr(LPCTSTR lpsz1, LPCTSTR lpsz2)
{
	return StrRStrI(lpsz1, NULL, lpsz2);
}
LPCSTR WizStrRStrI_PtrA(LPCSTR lpsz1, LPCSTR lpsz2)
{
	return StrRStrIA(lpsz1, NULL, lpsz2);
}


LPSTR WizStrStrI_PtrA(LPCSTR lpsz1, LPCSTR lpsz2)
{
	return StrStrIA(lpsz1, lpsz2);
}
LPTSTR WizStrStrI_Ptr2(LPCTSTR lpsz1, size_t nLen, LPCTSTR lpsz2)
{
	size_t nLen2 = _tcslen(lpsz2);
	LPCTSTR lpszEnd = lpsz1 + nLen - nLen2;
	//
	while (lpsz1 < lpszEnd)
	{
		if (_tcsnicmp(lpsz1, lpsz2, nLen2) == 0)
			return (LPTSTR)lpsz1;
		lpsz1++;
	}
	return NULL;
}

BOOL WizIsSameChar(TCHAR ch1, TCHAR ch2)
{
#ifdef WINCE
	return toupper(ch1) == toupper(ch2);
#else
	return ChrCmpI(ch1, ch2) == 0;
#endif
}
BOOL WizIsSpaceChar(TCHAR ch)
{
	return _istspace(ch);
}
LPCTSTR WizTrimLeft(LPCTSTR lpsz)
{
	LPCTSTR p = lpsz;
    while (*p)
    {
		if (_istspace(*p))
			p++;
		else
            break;
    }
    return p;
}
size_t WizReplaceChar(LPTSTR lpsz, TCHAR chFind, TCHAR chReplace)
{
	size_t nCount = 0;
	//
    while (*lpsz)
    {
		if (*lpsz == chFind)
		{
			*lpsz = chReplace;
			nCount++;
		}
		//
		lpsz++;
    }
    return nCount;
}

ptrdiff_t WizStrStrI_Pos(const CString& strText, const CString& strFind, ptrdiff_t nBegin /*= 0*/)
{
	LPCTSTR lpszText = strText;
	LPCTSTR lpszFind = strFind;
	//
	LPCTSTR lpszRet = WizStrStrI_Ptr(lpszText + nBegin, lpszFind);
	if (!lpszRet)
		return -1;
	return lpszRet - lpszText;
}
ptrdiff_t WizStrRStrI_Pos(const CString& strText, const CString& strFind, ptrdiff_t nBegin /*= 0*/)
{
	LPCTSTR lpszText = strText;
	LPCTSTR lpszFind = strFind;
	//
	LPCTSTR lpszRet = WizStrRStrI_Ptr(lpszText + nBegin, lpszFind);
	if (!lpszRet)
		return -1;
	return lpszRet - lpszText;
}

ptrdiff_t WizStrStrI_PosA(const CStringA& strText, const CStringA& strFind, ptrdiff_t nBegin /*= 0*/)
{
	LPCSTR lpszText = strText;
	LPCSTR lpszFind = strFind;
	//
	LPCSTR lpszRet = WizStrStrI_PtrA(lpszText + nBegin, lpszFind);
	if (!lpszRet)
		return -1;
	return lpszRet - lpszText;
}

ptrdiff_t WizStrRStrI_PosA(const CStringA& strText, const CStringA& strFind, ptrdiff_t nBegin /*= 0*/)
{
	LPCSTR lpszText = strText;
	LPCSTR lpszFind = strFind;
	//
	LPCSTR lpszRet = WizStrRStrI_PtrA(lpszText + nBegin, lpszFind);
	if (!lpszRet)
		return -1;
	return lpszRet - lpszText;
}

void WizStringRemoveAllSpace(CString& strText)
{
	int nLen = strText.GetLength();
	LPTSTR lpszRet = new TCHAR[nLen + 1];
	ZeroMemory(lpszRet, sizeof(TCHAR) * (nLen + 1));
	LPTSTR p = lpszRet;
	LPCTSTR pSrc = strText.LockBuffer();
	while (*pSrc)
	{
		if (_istspace(*pSrc))
		{
			pSrc++;
		}
		else
		{
			*p = *pSrc;
			p++;
			pSrc++;
		}
	}
	//
	strText.UnlockBuffer();
	//
	strText = lpszRet;
	//
	delete [] lpszRet;
}

CString WizStringReplace(LPCTSTR lpszText, LPCTSTR lpszFind, LPCTSTR lpszReplace)
{
	CString strText(lpszText);
	strText.Replace(lpszFind, lpszReplace);
	return strText;
}

CString WizStringReplace(LPCTSTR lpszText, TCHAR chFind, TCHAR chReplace)
{
	CString strText(lpszText);
	strText.Replace(chFind, chReplace);
	return strText;
}

int WizStringReplaceNoCase(CString& str, LPCTSTR lpszFind, LPCTSTR lpszReplaceWith, BOOL bReplaceAll /*= TRUE*/)
{
	int nReplaced = 0;
	//
	CString strFind(lpszFind);
	int nFindLen = strFind.GetLength();
	//
	int nReplaceLen = int(_tcslen(lpszReplaceWith));
	//
	int nBegin = 0;
	while (1)
	{
		int nPos = int(WizStrStrI_Pos(str, strFind, nBegin));
		if (nPos == -1)
			break;
		//
		str.Delete(nPos, nFindLen);
		str.Insert(nPos, lpszReplaceWith);
		//
		nReplaced++;
		//
		if (!bReplaceAll)
			break;
		//
		nBegin = nPos + nReplaceLen;
	}
	return nReplaced;
}

void WizLimitText(CString& strText, int nMaxLength)
{
	if (strText.GetLength() > nMaxLength)
		strText.Delete(nMaxLength, strText.GetLength() - nMaxLength);
}

CString WizSubString(LPCTSTR lpszText, ptrdiff_t nBegin, size_t nCount)
{
	CString strRet;
	LPTSTR pBuffer = strRet.GetBuffer(int(nCount) + 1);
	//
	ZeroMemory(pBuffer, (nCount + 1) * sizeof(TCHAR));
	_tcsncpy_s(pBuffer, nCount + 1, lpszText + nBegin, nCount);
	//
	strRet.ReleaseBuffer();
	//
	return strRet;
}

CStringA WizSubStringA(LPCSTR lpszText, ptrdiff_t nBegin, size_t nCount)
{
	CStringA strRet;
	LPSTR pBuffer = strRet.GetBuffer(int(nCount) + 1);
	//
	ZeroMemory(pBuffer, (nCount + 1) * sizeof(CHAR));
	strncpy_s(pBuffer, nCount + 1, lpszText + nBegin, nCount);
	//
	strRet.ReleaseBuffer();
	//
	return strRet;
}

BOOL WizSplitTextToArray(const CStringW& strText, WCHAR ch, CWizStdStringArray& arrayResult)
{
	if (strText.IsEmpty())
		return TRUE;

	int nBegin = 0;
	if (strText[0] == ch)	//skip first
		nBegin = 1;
	//
	//TRACE(_T("split %s\n"), strText);
	//
	while (1)
	{
		CStringW strLine;
		//
		int nPos = strText.Find(ch, nBegin);
		//
		if (-1 == nPos)
		{
			strLine = strText.Mid(nBegin, strText.GetLength() - nBegin);
			nBegin = strText.GetLength();
		}
		else
		{
			strLine = strText.Mid(nBegin, nPos - nBegin);
			nBegin = nPos + 1;
		}
		//
		if (ch == _T('\n'))
		{
			if (!strLine.IsEmpty())
			{
				if (strLine[strLine.GetLength() - 1] == _T('\r'))
				{
					strLine.Delete(strLine.GetLength() - 1, 1);
				}
			}
		}
		//
		//ATLTRACE(_T("%s\n"), strLine);
		arrayResult.push_back(strLine);
		//
		if (nBegin == strText.GetLength())
			break;
	}
	//
	return TRUE;
}

int WizSplitTextCompareString(LPCWSTR lpszText1, LPCWSTR lpszText2, BOOL bMatchCase)
{
	if (bMatchCase)
		return wcscmp(lpszText1, lpszText2);
	else
		return _wcsicmp(lpszText1, lpszText2);
}

int WizSplitTextFindString(LPCWSTR lpszText, LPCWSTR lpszFind, BOOL bMatchCase)
{
	if (bMatchCase)
	{
		LPCWSTR p = wcsstr(lpszText, lpszFind);
		if (!p)
			return -1;
		return int(p - lpszText);
	}
	else
	{
		LPCWSTR p = StrStrIW(lpszText, lpszFind);
		if (!p)
			return -1;
		return int(p - lpszText);
	}
}

BOOL WizSplitTextToArray(CStringW strText, LPCWSTR lpszSplitterText, BOOL bMatchCase, CWizStdStringArray& arrayResult)
{
	if (strText.IsEmpty())
		return TRUE;
	//
	int nSplitterTextLen = (int)wcslen(lpszSplitterText);
	//
	if (strText.GetLength() > nSplitterTextLen)
	{
		if (0 == WizSplitTextCompareString(strText.Left(nSplitterTextLen), lpszSplitterText, bMatchCase))
		{
			strText.Delete(0, nSplitterTextLen);
		}
	}
	//
	while (1)
	{
		CStringW strLine;
		//
		int nPos = WizSplitTextFindString(strText, lpszSplitterText, bMatchCase);
		//
		if (-1 == nPos)
		{
			strLine = strText;
			strText.Empty();
		}
		else
		{
			strLine = strText.Left(nPos);
			strText.Delete(0, nPos + nSplitterTextLen);
		}
		//
		//ATLTRACE(_T("%s\n"), strLine);
		arrayResult.push_back(strLine);
		//
		if (strText.IsEmpty())
			break;
	}
	//
	return TRUE;
}
BOOL WizSplitTextToArray(LPCWSTR lpszText, WCHAR ch, CWizStdStringArray& arrayResult)
{
	return WizSplitTextToArray(CStringW(lpszText), ch, arrayResult);
}

int WizFindInArray(const CWizStdStringArray& arrayText, LPCWSTR lpszFind)
{
	CWizStdStringArray::const_iterator i = std::find(arrayText.begin(), arrayText.end(), CStringW(lpszFind));
	if (i == arrayText.end())
		return -1;
	return int(i - arrayText.begin());
}
int WizFindInArrayNoCase(const CWizStdStringArray& arrayText, LPCWSTR lpszFind)
{
	int nCount = (int)arrayText.size();
	for (int i = 0; i < nCount; i++)
	{
		if (0 == arrayText[i].CompareNoCase(lpszFind))
			return i;
	}
	return -1;
}
void WizStringArrayToText(const CWizStdStringArray& arrayText, CStringW& strText, LPCWSTR lpszSplitter /*= L"\r\n"*/)
{
	size_t nSplitterLen = 0;
	if (lpszSplitter)
	{
		nSplitterLen = wcslen(lpszSplitter);
	}
	//
	int nTextLen = 0;
	//
	int nLineCount = (int)arrayText.size();
	//
	for (int i = 0; i < nLineCount; i++)
	{
		nTextLen += arrayText[i].GetLength();
	}
	//
	size_t nCharCount = nSplitterLen * nLineCount + nTextLen + 1024;
	//
	int nBufferSize = int(nCharCount * sizeof(WCHAR));
	//
	CWizBufferAlloc ba(nBufferSize);
	LPWSTR pBuffer = (LPWSTR)ba.GetBuffer();
	if (!pBuffer)
		return;
	//
	LPWSTR pBufferEnd = pBuffer + nCharCount;
	//
	LPWSTR p = pBuffer;
	//
	for (int i = 0; i < nLineCount; i++)
	{
		const CStringW& strLine = arrayText[i];
		//
		ATLASSERT(p < pBufferEnd);
		memcpy_s(p, (pBufferEnd - p) * sizeof(WCHAR), (LPCWSTR)strLine, strLine.GetLength() * sizeof(WCHAR));
		//
		p += strLine.GetLength();
		//
		if (i < nLineCount - 1)
		{
			ATLASSERT(p < pBufferEnd);
			memcpy_s(p, (pBufferEnd - p) * sizeof(WCHAR), lpszSplitter, nSplitterLen * sizeof(WCHAR));
			//
			p += nSplitterLen;
		}
	}
	//
	strText = pBuffer;

}
void WizStringArrayEraseEmptyLine(CWizStdStringArray& arrayText)
{
	int nCount = (int)arrayText.size();
	for (int i = nCount - 1; i >= 0; i--)
	{
		CStringW strLine = arrayText[i];
		strLine.Trim();
		if (strLine.IsEmpty())
		{
			arrayText.erase(arrayText.begin() + i);
		}
	}
}

bool WizStringArrayCompareElementAsc(const CStringW& elem1, const CStringW& elem2)
{
	return StrCmpIW (elem2, elem1) > 0;
}

bool WizStringArrayCompareElementDes(const CStringW& elem1, const CStringW& elem2)
{
	return StrCmpIW(elem1, elem2) > 0;
}

void WizStringArraySort(CWizStdStringArray& arrayText, BOOL bAscending /*= TRUE*/)
{
	if (bAscending)
	{
		std::sort(arrayText.begin(), arrayText.end(), WizStringArrayCompareElementAsc);
	}
	else
	{
		std::sort(arrayText.begin(), arrayText.end(), WizStringArrayCompareElementDes);
	}
}

void WizStringArrayRemoveMultiElement(CWizStdStringArray& arrayText)
{
	WizStringArraySort(arrayText);
	//
	size_t nCount = arrayText.size();
	for (intptr_t i = nCount - 1; i > 0; i--)
	{
		if (arrayText[i] == arrayText[i - 1])
			arrayText.erase(arrayText.begin() + i);
	}
}

void WizStringArrayRemoveMultiElementNoCase(CWizStdStringArray& arrayText)
{
	WizStringArraySort(arrayText);
	//
	size_t nCount = arrayText.size();
	for (intptr_t i = nCount - 1; i > 0; i--)
	{
		if (0 == arrayText[i].CompareNoCase(arrayText[i - 1]))
			arrayText.erase(arrayText.begin() + i);
	}
}
#ifdef _UNICODE
BOOL WizStringArrayMatchAllText(LPCTSTR lpszText, const CWizStdStringArray& arrayText, BOOL bMatchCase)
{
	if (arrayText.empty())
		return TRUE;
	//
	if (bMatchCase)
	{
		for (CWizStdStringArray::const_iterator it = arrayText.begin();
			it != arrayText.end();
			it++)
		{
			if (NULL == _tcsstr(lpszText, *it))
				return FALSE;
		}
	}
	else
	{
		for (CWizStdStringArray::const_iterator it = arrayText.begin();
			it != arrayText.end();
			it++)
		{
			if (NULL == WizStrStrI_Ptr(lpszText, *it))
				return FALSE;
		}
	}
	//
	return TRUE;
}
#endif

CStringW WizStringArrayGetValue(const CWizStdStringArray& arrayText, LPCWSTR lpszValueName)
{
	CStringW strValueName = CStringW(lpszValueName) + L"=";
	int nValueNameLen = strValueName.GetLength();
	//
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CStringW strLine = arrayText[i];
		if (0 == _wcsnicmp(strLine, strValueName, nValueNameLen))
			return strLine.Right(strLine.GetLength() - nValueNameLen);
	}
	//
	return CStringW();
}
BOOL WizStringArraySetValue(CWizStdStringArray& arrayText, LPCWSTR lpszValueName, LPCWSTR lpszValue)
{
	CStringW strValueName = CStringW(lpszValueName) + L"=";
	int nValueNameLen = strValueName.GetLength();
	//
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CStringW strLine = arrayText[i];
		if (0 == _wcsnicmp(strLine, strValueName, nValueNameLen))
		{
			arrayText[i] = strValueName + lpszValue;
			return TRUE;
		}
	}
	//
	arrayText.push_back(strValueName + lpszValue);
	//
	return TRUE;
	
}
void WizStringArrayGetAllValueName(const CWizStdStringArray& arrayText, CWizStdStringArray& arrayValueName)
{
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CStringW strLine = arrayText[i];
		int nPos = strLine.Find('=');
		if (-1 == nPos)
		{
			arrayValueName.push_back(strLine);
		}
		else
		{
			arrayValueName.push_back(strLine.Left(nPos));
		}
	}
}

BOOL WizStringArrayLoadFromFile(LPCTSTR lpszFileName, CWizStdStringArray& arrayText)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszFileName, strText))
		return FALSE;
	//
	return WizSplitTextToArray(strText, _T('\n'), arrayText);
}
BOOL WizStringArraySaveToUnicodeFile(LPCTSTR lpszFileName, const CWizStdStringArray& arrayText, LPCWSTR lpszSplitter /*= L"\r\n"*/)
{
	CStringW strText;
	WizStringArrayToText(arrayText, strText, lpszSplitter);
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszFileName, CStringW(strText));
}
BOOL WizStringArrayCombineFile(LPCTSTR lpszFileName1, LPCTSTR lpszFileName2, LPCTSTR lpszFileNameResult)
{
	CWizStdStringArray arrayText1;
	WizStringArrayLoadFromFile(lpszFileName1, arrayText1);
	//
	CWizStdStringArray arrayText2;
	WizStringArrayLoadFromFile(lpszFileName1, arrayText2);
	//
	arrayText2.insert(arrayText2.begin(), arrayText1.begin(), arrayText1.end());
	//
	return WizStringArraySaveToUnicodeFile(lpszFileNameResult, arrayText2);
}

BOOL WizStrToUnix(CString& str)
{
	if (-1 == str.Find('\r'))
		return TRUE;
	//
	int nCount = str.GetLength();
	int nNewBufferSize = nCount + 1;
	TCHAR* pBuffer = new TCHAR[nNewBufferSize];
	if (!pBuffer)
		return FALSE;
	//
	ZeroMemory(pBuffer, sizeof(TCHAR) * nNewBufferSize);
	//
	LPCTSTR pSrc = (LPCTSTR)str;
	LPTSTR pDest = pBuffer;
	//
	while (*pSrc)
	{
		TCHAR ch = *pSrc;
		if (ch != '\r')
		{
			*pDest = ch;
			pDest++;
		}
		pSrc++;
	}
	//
	str = pBuffer;
	//
	delete [] pBuffer;
	//
	return TRUE;

}
BOOL WizStrToWindows(CString& str)
{
	if (-1 == str.Find('\r')
		&& -1 == str.Find('\n'))
		return TRUE;
	//
	WizStrToUnix(str);
	//
	int nCount = str.GetLength();
	int nNewBufferSize = nCount * 2 + 1;
	TCHAR* pBuffer = new TCHAR[nNewBufferSize];
	if (!pBuffer)
		return FALSE;
	//
	ZeroMemory(pBuffer, sizeof(TCHAR) * nNewBufferSize);
	//
	LPCTSTR pSrc = (LPCTSTR)str;
	LPTSTR pDest = pBuffer;
	//
	while (*pSrc)
	{
		TCHAR ch = *pSrc;
		if (ch == '\n')
		{
			*pDest = '\r';
			pDest++;
			*pDest = '\n';
		}
		else
		{
			*pDest = ch;
		}
		pDest++;
		pSrc++;
	}
	//
	str = pBuffer;
	//
	delete [] pBuffer;
	//
	return TRUE;
}




CWizIniFileEx::CWizIniFileEx(void)
{
}

CWizIniFileEx::~CWizIniFileEx(void)
{
}
BOOL CWizIniFileEx::LoadFromUTF8File(LPCTSTR lpszFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFileEx(lpszFileName, strText, WIZ_LTFF_FORCE_UTF8))
		return FALSE;
	//
	WizSplitTextToArray(strText, _T('\n'), m_arrayText);
	//
	return TRUE;
}

BOOL CWizIniFileEx::LoadFromFile(LPCTSTR lpszFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszFileName, strText))
		return FALSE;
	//
	WizSplitTextToArray(strText, _T('\n'), m_arrayText);
	//
	return TRUE;
}
BOOL CWizIniFileEx::LoadFromText(LPCTSTR lpszText)
{
	WizSplitTextToArray(lpszText, _T('\n'), m_arrayText);
	//
	return TRUE;
}

BOOL CWizIniFileEx::SaveToUnicodeFile(LPCTSTR lpszFileName)
{
	return WizStringArraySaveToUnicodeFile(lpszFileName, m_arrayText);
}

void CWizIniFileEx::ToText(CString& strText)
{
	::WizStringArrayToText(m_arrayText, strText);
}

BOOL CWizIniFileEx::GetBoolDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bDefValue) const
{
	CString strValue = GetStringDef(lpszSection, lpszValueName);
	//
	if (strValue.IsEmpty())
		return bDefValue;
	//
	if (strValue == _T("0"))
		return FALSE;
	if (strValue == _T("1"))
		return TRUE;
	//
	if (0 == strValue.CompareNoCase(_T("false")))
		return FALSE;
	if (0 == strValue.CompareNoCase(_T("true")))
		return TRUE;
	//
	return bDefValue;
}
int CWizIniFileEx::GetIntDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, int nDefValue) const
{
	CString strValue = GetStringDef(lpszSection, lpszValueName);
	//
	int nVal = _ttoi(strValue);
	//
	if (WizIntToStr(nVal) != strValue)
		return nDefValue;
	//
	return nVal;
}

double CWizIniFileEx::GetDoubleDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, double nDefValue) const
{
	CString strValue = GetStringDef(lpszSection, lpszValueName);
	//
	return atof(CStringA(strValue));
}

BOOL CWizIniFileEx::ValueExists(LPCTSTR lpszSection, LPCTSTR lpszValueName)
{
	CString strDefault(_T("{4B3AFC45-7472-4545-BDA7-F83F788C2DFE}"));
	CString strValue = GetStringDef(lpszSection, lpszValueName, strDefault);
	//
	return strDefault != strValue;
}

CString CWizIniFileEx::GetStringDef(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDefValue /*= NULL*/) const
{
	ATLASSERT(lpszSection);
	ATLASSERT(lpszValueName);
	//
	BOOL bInSection = FALSE;
	//
	CString strSectionLine;
	strSectionLine.Format(_T("[%s]"), lpszSection);
	//
	CString strValueLine;
	strValueLine.Format(_T("%s="), lpszValueName);

	//
	size_t nCount = m_arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = m_arrayText[i];
		strLine.Trim();
		if (strLine.IsEmpty())
			continue;
		if (strLine[0] == _T(';'))
			continue;
		//
		if (bInSection)
		{
			if (strLine[0] == _T('['))
				break;
			//
			if (0 == _tcsnicmp(strLine, strValueLine, strValueLine.GetLength()))
			{
				return strLine.Right(strLine.GetLength() - strValueLine.GetLength());
			}
		}
		else
		{
			if (strLine[0] == _T('['))
			{
				if (0 == strLine.CompareNoCase(strSectionLine))
				{
					bInSection = TRUE;
				}
			}
		}
	}
	//
	if (lpszDefValue)
		return CString(lpszDefValue);
	//
	return CString();
}

void CWizIniFileEx::SetString(LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszValue)
{
	ATLASSERT(lpszSection);
	ATLASSERT(lpszValueName);
	//
	BOOL bInSection = FALSE;
	//
	CString strSectionLine;
	strSectionLine.Format(_T("[%s]"), lpszSection);
	//
	CString strValueLine;
	strValueLine.Format(_T("%s="), lpszValueName);
	//
	int nSectionIndex = -1;
	int nValueIndex = -1;
	//
	size_t nCount = m_arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = m_arrayText[i];
		strLine.Trim();
		if (strLine.IsEmpty())
			continue;
		if (strLine[0] == _T(';'))
			continue;
		//
		if (bInSection)
		{
			if (strLine[0] == _T('['))
				break;
			//
			if (0 == _tcsnicmp(strLine, strValueLine, strValueLine.GetLength()))
			{
				nValueIndex = (int)i;
				break;
			}
		}
		else
		{
			if (strLine[0] == _T('['))
			{
				if (0 == strLine.CompareNoCase(strSectionLine))
				{
					nSectionIndex = (int)i;
					bInSection = TRUE;
				}
			}
		}
	}
	//
	CString strText = CString(lpszValueName) + _T("=") + lpszValue;
	//
	if (-1 != nValueIndex)
	{
		m_arrayText[nValueIndex] = strText;
		return;
	}
	//
	if (-1 != nSectionIndex)
	{
		m_arrayText.insert(m_arrayText.begin() + nSectionIndex + 1, strText);
		return;
	}
	//
	m_arrayText.push_back(strSectionLine);
	m_arrayText.push_back(strText);
}

void CWizIniFileEx::GetSectionNames(CWizStdStringArray& arraySectionName)
{
	size_t nCount = m_arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = m_arrayText[i];
		strLine.Trim();
		if (strLine.IsEmpty())
			continue;
		if (strLine[0] == _T(';'))
			continue;
		//
		if (strLine[0] == _T('[')
			&& strLine[strLine.GetLength() - 1] == _T(']'))
		{
			strLine.Trim(_T("[]"));
			arraySectionName.push_back(strLine);
		}
	}
}

void CWizIniFileEx::GetSection(LPCTSTR lpszSection, CWizStdStringArray& arrayData)
{
	ATLASSERT(lpszSection);
	//
	BOOL bInSection = FALSE;
	//
	CString strSectionLine;
	strSectionLine.Format(_T("[%s]"), lpszSection);
	//
	//
	size_t nCount = m_arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = m_arrayText[i];
		strLine.Trim();
		if (strLine.IsEmpty())
			continue;
		if (strLine[0] == _T(';'))
			continue;
		//
		if (bInSection)
		{
			if (strLine[0] == _T('['))
				break;
			//
			arrayData.push_back(strLine);
		}
		else
		{
			if (strLine[0] == _T('['))
			{
				if (0 == strLine.CompareNoCase(strSectionLine))
				{
					bInSection = TRUE;
				}
			}
		}
	}
}

void CWizIniFileEx::GetArray(LPCTSTR lpszSection, CWizStdStringArray& arrayData)
{
	CWizStdStringArray arraySection;
	GetSection(lpszSection, arraySection);
	//
	std::map<int, CString> mapData;
	//
	for (CWizStdStringArray::const_iterator it = arraySection.begin();
		it != arraySection.end();
		it++)
	{
		CString strLine = *it;
		//
		CString strLeft;
		CString strRight;
		::WizStringSimpleSplit(strLine, '=', strLeft, strRight);
		//
		int nIndex = _ttoi(strLeft);
		//
		if (WizIntToStr(nIndex) == strLeft)
		{
			mapData[nIndex] = strRight;
		}
	}
	for (int i = 0; ; i++)
	{
		CString str = mapData[i];
		if (str.IsEmpty())
			break;
		arrayData.push_back(str);
	}
}
void CWizIniFileEx::AppendArray(LPCTSTR lpszSection, const CWizStdStringArray& arrayData)
{
	m_arrayText.push_back(WizFormatString1(_T("[%1]"), lpszSection));
	//
	for (size_t i = 0; i < arrayData.size(); i++)
	{
		m_arrayText.push_back(WizIntToStr(int(i)) + _T("=") + arrayData[i]);
	}
}



CStringA WizBase64Encode(const BYTE* pBuffer, int nLen)
{
	CStringA strRet;
	//
	int nRequiredLen = Base64EncodeGetRequiredLength(nLen, ATL_BASE64_FLAG_NONE);
	//
	char* pResult = strRet.GetBuffer(nRequiredLen);
	ZeroMemory(pResult, (nRequiredLen + 1) * sizeof(char));
	Base64Encode(pBuffer, nLen, pResult, &nRequiredLen, ATL_BASE64_FLAG_NONE);
	strRet.ReleaseBuffer();
	//
	return strRet;
}
BOOL WizBase64Decode(const char* lpszText, BYTE* pResult, int& nResultLen)
{
	return Base64Decode(lpszText, int(strlen(lpszText)), pResult, &nResultLen);
}
BOOL WizBase64Encode(IStream* pStream, CStringA& strText)
{
	WizStreamSeekToBegin(pStream);
	//
	int nLen = int(WizStreamGetSize(pStream));
	//
	BOOL bRet = FALSE;
	//
	BYTE* pBuffer = new BYTE[nLen];
	if (pBuffer)
	{
		if (WizStreamRead(pStream, pBuffer, nLen))
		{
			strText = WizBase64Encode(pBuffer, nLen);
			bRet = TRUE;
		}
		delete [] pBuffer;
	}
	return bRet;
}

BOOL WizBase64Encode(const char* lpszText, CStringA& strText)
{
	strText = WizBase64Encode((const BYTE*)lpszText, int(strlen(lpszText)));
	return TRUE;
}
CStringA WizBase64Encode(const char* lpszText)
{
	return WizBase64Encode((const BYTE*)lpszText, int(strlen(lpszText)));
}


BOOL WizBase64Decode(const char* lpszText, IStream* pStream)
{
	WizStreamSeekToBegin(pStream);
	WizStreamSetSize(pStream, 0);
	//
	int nLen = 0;
	WizBase64Decode(lpszText, NULL, nLen);
	//
	BOOL bRet = FALSE;
	int nBufferSize = nLen + 10;
	//
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (pBuffer)
	{
		if (WizBase64Decode(lpszText, pBuffer, nBufferSize))
		{
			bRet = WizStreamWrite(pStream, pBuffer, nBufferSize);
		}
		delete [] pBuffer;
	}
	return bRet;
}

CStringA WizBase64EncodeInline(LPCTSTR lpszCharset, LPCWSTR lpszText)
{
	CStringA strText = WizBSTR2STR(lpszCharset, lpszText);
	//
	CStringA strBase64Text = WizBase64Encode((const BYTE *)(LPCSTR)strText, strText.GetLength());
	//
	strBase64Text.Replace("\r", "");
	strBase64Text.Replace("\n", "");
	//
	CStringA strRet;
	strRet.Format("=?%s?B?%s?=", CStringA(lpszCharset), strBase64Text);
	//
	return strRet;
}

BOOL WizBase64DecodeToText(const char* lpszText, CStringA& strResultText)
{
	int nLen = 0;
	WizBase64Decode(lpszText, NULL, nLen);
	//
	BOOL bRet = FALSE;
	int nBufferSize = nLen + 10;
	//
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (pBuffer)
	{
		ZeroMemory(pBuffer, sizeof(BYTE) * (nBufferSize));
		//
		if (WizBase64Decode(lpszText, pBuffer, nBufferSize))
		{
			strResultText = (char*)pBuffer;
			bRet = TRUE;
		}
		delete [] pBuffer;
	}
	return bRet;
}
BOOL WizBase64DecodeToUnicodeText(const char* lpszText, LPCTSTR lpszCharset, CStringW& strResult)
{
	CStringA strTextA;
	if (!WizBase64DecodeToText(lpszText, strTextA))
		return FALSE;
	//
	strResult = WizSTR2BSTR(lpszCharset, strTextA);
	//
	return TRUE;
}
CStringW WizBase64DecodeToUnicodeText(const char* lpszText, LPCTSTR lpszCharset)
{
	CStringW strText;
	WizBase64DecodeToUnicodeText(lpszText, lpszCharset, strText);
	return strText;
}


CStringA WizBase64EncodeUnicodeText(const wchar_t* lpszText)
{
	CStringA strRet;
	if (!lpszText)
		return strRet;
	if (!*lpszText)
		return strRet;
	//
	size_t nLen = wcslen(lpszText);
	size_t nBufferLen = (nLen + 1) * sizeof(wchar_t);
	//
	strRet = ::WizBase64Encode((const BYTE*)lpszText, (int)nBufferLen);
	return strRet;
}
CStringW WizBase64DecodeUnicodeText(const char* lpszText)
{
	CStringW strRet;
	//
	int nLen = 0;
	WizBase64Decode(lpszText, NULL, nLen);
	//
	BOOL bRet = FALSE;
	int nBufferSize = nLen + 10;
	//
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (pBuffer)
	{
		ZeroMemory(pBuffer, sizeof(BYTE) * (nBufferSize));
		//
		if (WizBase64Decode(lpszText, pBuffer, nBufferSize))
		{
			strRet = (const wchar_t*)pBuffer;
		}
		delete [] pBuffer;
	}
	return strRet;
}

CStringA WizQPEncode(const BYTE* pBuffer, int nLen)
{
	CStringA strRet;
	//
	int nRequiredLen = QPEncodeGetRequiredLength(nLen);
	//
	char* pResult = strRet.GetBuffer(nRequiredLen);
	ZeroMemory(pResult, (nRequiredLen + 1) * sizeof(char));
	QPEncode((BYTE*)pBuffer, nLen, pResult, &nRequiredLen);
	strRet.ReleaseBuffer();
	//
	return strRet;
}
BOOL _WizAtlQPDecode(_In_count_(nSrcLen) const char* pbSrcData, _In_ int nSrcLen, _Out_z_cap_post_count_(*pnDestLen, *pnDestLen) LPSTR szDest, _Inout_ int* pnDestLen, _In_ DWORD dwFlags = 0)
{
	if (!pbSrcData || !szDest || !pnDestLen)
	{
		return FALSE;
	}
	
	LPSTR szDestEnd=szDest + *pnDestLen;
	int nRead = 0, nWritten = 0;
	char ch;
	while (nRead <= nSrcLen)
	{
		ch = *pbSrcData++;
		nRead++;
		if (ch == '=')
		{
			/*
			吃掉=\r\n
			其它的回车不吃
			*/
			if (*pbSrcData == '\r' && *(pbSrcData + 1) == '\n')	
			{
				pbSrcData += 2;
				nRead += 2;
				continue;
			}
			//
			//if the next character is a digit or a character, convert
			if ( ( nRead < ( nSrcLen - 1 ) ) && (isdigit(static_cast<unsigned char>(*pbSrcData)) || isalpha(static_cast<unsigned char>(*pbSrcData))))
			{
				char szBuf[5];
				szBuf[0] = *pbSrcData++;
				szBuf[1] = *pbSrcData++;
				szBuf[2] = '\0';
				char* tmp = '\0';
				ATLENSURE(szDest < szDestEnd);
				*szDest++ = (BYTE)strtoul(szBuf, &tmp, 16);
				nWritten++;
				nRead += 2;
				continue;
			}
			//
			//return FALSE;
		}
		ATLENSURE(szDest < szDestEnd);
		*szDest++ = ch;
		nWritten++;
	}

	*pnDestLen = nWritten-1;
	return TRUE;
}


BOOL WizQPDecode(const char* lpszText, BYTE* pResult, int& nResultLen)
{
	if (NULL == strchr(lpszText, '='))
	{
		strcpy_s((char*)pResult, nResultLen, lpszText);
		return TRUE;
	}
	//
	return _WizAtlQPDecode(lpszText, (int)strlen(lpszText), (LPSTR)pResult, &nResultLen);
}
BOOL WizQPEncode(IStream* pStream, CStringA& strText)
{
	WizStreamSeekToBegin(pStream);
	//
	int nLen = int(WizStreamGetSize(pStream));
	//
	BOOL bRet = FALSE;
	//
	BYTE* pBuffer = new BYTE[nLen];
	if (pBuffer)
	{
		if (WizStreamRead(pStream, pBuffer, nLen))
		{
			strText = WizQPEncode(pBuffer, nLen);
			bRet = TRUE;
		}
		delete [] pBuffer;
	}
	return bRet;
}
BOOL WizQPDecode(const char* lpszText, IStream* pStream)
{
	WizStreamSeekToBegin(pStream);
	WizStreamSetSize(pStream, 0);
	//
	int nLen = (int)strlen(lpszText);
	//
	int nBufferSize = nLen + 10;
	//
	BOOL bRet = FALSE;
	//
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (pBuffer)
	{
		if (WizQPDecode(lpszText, pBuffer, nBufferSize))
		{
			bRet = WizStreamWrite(pStream, pBuffer, nBufferSize);
		}
		delete [] pBuffer;
	}
	return bRet;
}
BOOL WizQPDecodeToText(const char* lpszText, CStringA& strResult)
{
	int nLen = (int)strlen(lpszText);
	//
	BOOL bRet = FALSE;
	//
	int nBufferSize = nLen + 10;
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (pBuffer)
	{
		ZeroMemory(pBuffer, sizeof(BYTE) * (nBufferSize));
		//
		if (WizQPDecode(lpszText, pBuffer, nBufferSize))
		{
			strResult = (char*)pBuffer;
			bRet = TRUE;
		}
		delete [] pBuffer;
	}
	return bRet;
}

BOOL WizBase64EncodeFile(LPCTSTR lpszFileName, CStringA& strText)
{
	CComPtr<IStream> spStream;
	if (FAILED(::CreateStreamOnHGlobal(NULL, TRUE, &spStream)))
		return FALSE;
	//
	if (!WizStreamLoadFromFile(lpszFileName, spStream))
		return FALSE;
	//
	return WizBase64Encode(spStream, strText);
}


COleDateTime WizGetCurrentTime()
{
	return COleDateTime::GetCurrentTime();
}

BOOL WizStringToDateTime(LPCTSTR lpsz, COleDateTime& t, CString& strError)
{
	t = WizGetCurrentTime();
	//
	if (!lpsz)
	{
		strError = _T("NULL pointer");
		return TRUE;
	}
	//
	if (_tcslen(lpsz) != 19)
	{
		strError = _T("Invalid date time format");
		return TRUE;
	}
	//xxxx-xx-xx xx:xx:xx
	int nYear = _ttoi(lpsz);
	int nMonth = _ttoi(lpsz + 5);
	int nDay = _ttoi(lpsz + 8);
	int nHour = _ttoi(lpsz + 11);
	int nMin = _ttoi(lpsz + 14);
	int nSec = _ttoi(lpsz + 17);
	//
	if (nYear < 1990 || nYear > 2050)
	{
		strError = _T("Invalid date time format (year)");
		return TRUE;
	}
	if (nMonth < 1 || nMonth > 12)
	{
		strError = _T("Invalid date time format (month)");
		return TRUE;
	}
	if (nDay < 1 || nDay > 31)
	{
		strError = _T("Invalid date time format (day)");
		return TRUE;
	}
	if (nHour < 0 || nHour > 23)
	{
		strError = _T("Invalid date time format (hour)");
		return TRUE;
	}
	if (nMin < 0 || nMin > 59)
	{
		strError = _T("Invalid date time format (minute)");
		return TRUE;
	}
	if (nSec < 0 || nSec > 59)
	{
		strError = _T("Invalid date time format (second)");
		return TRUE;
	}
	//
	t = COleDateTime(nYear, nMonth, nDay, nHour, nMin, nSec);
	//
	return TRUE;
}


BOOL WizStringToDateTime(LPCTSTR lpsz, COleDateTime& t)
{
	CString strErr;
	if (!WizStringToDateTime(lpsz, t, strErr))
	{
		TOLOG(strErr);
		return FALSE;
	}
	return TRUE;
}

COleDateTime WizStringToDateTime(LPCTSTR lpsz)
{
	COleDateTime t;
	if (WizStringToDateTime(lpsz, t))
		return t;
	//
	return COleDateTime::GetCurrentTime();
}

CString WizDateTimeToString(COleDateTime t)
{
	if (COleDateTime::valid != t.GetStatus()
		|| t.GetYear() < 1990
		|| t.GetYear() > 2050)
	{
		t = ::WizGetCurrentTime();
	}
	//
	//
	CString str;
	str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	//
	return str;
}
#ifndef _WIN32_WCE
CString WizDateTimeToString(time_t t)
{
	return WizDateTimeToString(COleDateTime(t));
}
#endif


CString WizColorToString(COLORREF cr)
{
	return WizIntToHexEx(GetRValue(cr), 2, FALSE)
		+ WizIntToHexEx(GetGValue(cr), 2, FALSE)
		+ WizIntToHexEx(GetBValue(cr), 2, FALSE);
}

COLORREF WizStringToColor(LPCTSTR sz)
{
	UINT n = WizHexToInt(sz);
	//
	int r = (LOBYTE((n)>>16));
	int g = (LOBYTE(((WORD)(n)) >> 8));
	int b = LOBYTE(n);

	return RGB(r, g, b);
}


CString WizStringToSQL(const CString& str, LPCTSTR lpszPrefix)
{
	if (str.GetLength() == 0)
	{
		return CString(_T("NULL"));
	}
	else
	{
		CString strPrefix(lpszPrefix);
		//
		if (str.Find(_T('\'')) == -1)
		{
			return strPrefix + CString(_T("'")) + str + CString(_T("'"));
		}
		else
		{
			CString strRet;
			//
			LPTSTR pBuffer = strRet.GetBuffer(str.GetLength() * 2);
			for (int i = 0; i < str.GetLength(); i++)
			{
				TCHAR ch = str[i];
				*pBuffer = ch;
				if (ch == _T('\''))
				{
					pBuffer++;
					*pBuffer = ch;
				}
				pBuffer++;
			}
			*pBuffer = _T('\0');
			strRet.ReleaseBuffer();
			//
			//
			return strPrefix + CString(_T("'")) + strRet + CString(_T("'"));
		}
	}
}

CString WizStringToSQL(LPCTSTR lpszStr, LPCTSTR lpszPrefix)
{
	return WizStringToSQL(CString(lpszStr), lpszPrefix);
}


CString WizTimeToSQL(const COleDateTime& t)
{
	CString str = WizDateTimeToString(t);
	return CString(_T("'")) + str + _T("'");
}


CString WizColorToSQL(COLORREF cr)
{
	TCHAR sz[10] = {'\'', 0};
	_tcscat_s(sz, 10, WizColorToString(cr));
	_tcscat_s(sz, 10, _T("'"));
	return CString(sz);
}


#ifndef _WIN32_WCE
CString WizTimeToSQL(time_t t)
{
	COleDateTime ct(t);
	return WizTimeToSQL(ct);
}
#endif



BOOL WizIso8601StringToDateTime(LPCTSTR lpsz, COleDateTime& t, CString& strError)
{
	if (!lpsz)
	{
		strError = _T("NULL pointer");
		return FALSE;
	}
	//
	if (_tcslen(lpsz) != 17)
	{
		strError = _T("Invalid date time format");
		return FALSE;
	}
	//xxxxxxxxTxx:xx:xx
	//01234567890123456
	CString str(lpsz);
	str.SetAt(8, ' ');
	str.Insert(6, '-');
	str.Insert(4, '-');
	return WizStringToDateTime(str, t, strError);
}


CString WizDateTimeToIso8601String(const COleDateTime& t)
{
	CString str;
	str.Format(_T("%04d%02d%02dT%02d:%02d:%02d"), t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	//
	return str;
}




int WizGetFirstDayOfWeek()
{
	TCHAR szData[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IFIRSTDAYOFWEEK, szData, MAX_PATH);
	return _ttoi(szData);
}

int WizGetLastDayOfWeek()
{
	int nFirst = WizGetFirstDayOfWeek();
	//
	nFirst += 6;
	nFirst %= 7;
	//
	return nFirst;
}

CString WizGetDayOfWeekLongName(int nLocaleDayOfWeek)
{
	ATLASSERT(nLocaleDayOfWeek >= 0 && nLocaleDayOfWeek < 7);
	//
	int arrayLocalInfo[7] =
	{
		LOCALE_SDAYNAME1,
		LOCALE_SDAYNAME2,
		LOCALE_SDAYNAME3,
		LOCALE_SDAYNAME4,
		LOCALE_SDAYNAME5,
		LOCALE_SDAYNAME6,
		LOCALE_SDAYNAME7
	};
	//
	TCHAR szData[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, arrayLocalInfo[nLocaleDayOfWeek] , szData, MAX_PATH);
	return CString(szData);
}

CString WizGetDayOfWeekShortName(int nLocaleDayOfWeek)
{
	ATLASSERT(nLocaleDayOfWeek >= 0 && nLocaleDayOfWeek < 7);
	//
	int arrayLocalInfo[7] =
	{
		LOCALE_SABBREVDAYNAME1,
		LOCALE_SABBREVDAYNAME2,
		LOCALE_SABBREVDAYNAME3,
		LOCALE_SABBREVDAYNAME4,
		LOCALE_SABBREVDAYNAME5,
		LOCALE_SABBREVDAYNAME6,
		LOCALE_SABBREVDAYNAME7
	};
	//
	TCHAR szData[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, arrayLocalInfo[nLocaleDayOfWeek] , szData, MAX_PATH);
	return CString(szData);
}


CString WizGetMonthShortName(int nMonth)
{
	ATLASSERT(nMonth >= 1 && nMonth <= 12);
	//
	int arrayLocalInfo[12] = 
	{
		LOCALE_SABBREVMONTHNAME1,
		LOCALE_SABBREVMONTHNAME2,
		LOCALE_SABBREVMONTHNAME3,
		LOCALE_SABBREVMONTHNAME4,
		LOCALE_SABBREVMONTHNAME5,
		LOCALE_SABBREVMONTHNAME6,
		LOCALE_SABBREVMONTHNAME7,
		LOCALE_SABBREVMONTHNAME8,
		LOCALE_SABBREVMONTHNAME9,
		LOCALE_SABBREVMONTHNAME10,
		LOCALE_SABBREVMONTHNAME11,
		LOCALE_SABBREVMONTHNAME12,
	};
	TCHAR szMonth[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, arrayLocalInfo[nMonth - 1] , szMonth, MAX_PATH);
	return CString(szMonth);
}


CString WizGetMonthLongName(int nMonth)
{
	ATLASSERT(nMonth >= 1 && nMonth <= 12);
	//
	int arrayLocalInfo[12] = 
	{
		LOCALE_SMONTHNAME1,
		LOCALE_SMONTHNAME2,
		LOCALE_SMONTHNAME3,
		LOCALE_SMONTHNAME4,
		LOCALE_SMONTHNAME5,
		LOCALE_SMONTHNAME6,
		LOCALE_SMONTHNAME7,
		LOCALE_SMONTHNAME8,
		LOCALE_SMONTHNAME9,
		LOCALE_SMONTHNAME10,
		LOCALE_SMONTHNAME11,
		LOCALE_SMONTHNAME12,
	};
	TCHAR szMonth[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, arrayLocalInfo[nMonth - 1] , szMonth, MAX_PATH);
	return CString(szMonth);
}


int WizCOleDateTimeDayOfWeekToLocalDayOfTime(int nCOleDateTimeDayOfWeek)
{
	if (nCOleDateTimeDayOfWeek < 1 || nCOleDateTimeDayOfWeek > 7)
	{
		ATLASSERT(FALSE);
		return -1;
	}
	//
	int arrayLocaleDayOfWeek[] = {
	   6,   // Sunday
	   0,   
	   1,
	   2,
	   3, 
	   4, 
	   5// Saturday
	};
	//
	return arrayLocaleDayOfWeek[nCOleDateTimeDayOfWeek - 1];
}


int WizCOleDateTimeDayOfWeekFromLocalDayOfTime(int nLocalDayOfWeek)
{
	if (nLocalDayOfWeek < 0 || nLocalDayOfWeek > 6)
	{
		ATLASSERT(FALSE);
		return -1;
	}
	//
	int arrayCOleDateTimeDayOfWeek[] = {
	   2,   // Monday
	   3,   
	   4,
	   5,
	   6, 
	   7, 
	   1// Sunday
	};
	//
	return arrayCOleDateTimeDayOfWeek[nLocalDayOfWeek];
}


#ifndef _WIN32_WCE
time_t WizTimeGetTimeT(const COleDateTime& t)
{
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	CTime ct(st);
	return ct.GetTime();
}
#endif


CWizTockCounter::CWizTockCounter(LPCTSTR lpszName)
	: m_strName(lpszName)
{
	m_dwBegin = GetTickCount();
}
CWizTockCounter::~CWizTockCounter()
{
	DWORD dwEnd = GetTickCount();
	CString str = WizFormatString2(_T("TickCount=%1, %2\n"), WizIntToStr((int)(dwEnd - m_dwBegin)), m_strName);
	ATLTRACE(str);
}


CWizCallTrace::CWizCallTrace(LPCTSTR lpszFunctionName)
	: m_strFunctionName(lpszFunctionName)
{
	DEBUG_TOLOG(WizFormatString1(_T("%1 begin"), m_strFunctionName));
}
CWizCallTrace::~CWizCallTrace()
{
	DEBUG_TOLOG(WizFormatString1(_T("%1 end"), m_strFunctionName));
}

CString WizIniReadStringDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszDefaultValue)
{
	TCHAR szValue[4096] = {0};
	GetPrivateProfileString(lpszSection, lpszValueName, lpszDefaultValue, szValue, 4096, lpszFileName);
	return CString(szValue);
}
#ifndef WINCE
BOOL WizIniWriteString(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, LPCTSTR lpszValue)
{
	return WritePrivateProfileString(lpszSection, lpszValueName, lpszValue, lpszFileName);
}
BOOL WizIniWriteInt(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, int nValue)
{
	return WizIniWriteString(lpszFileName, lpszSection, lpszValueName, WizIntToStr(nValue));
}
#endif

int WizIniReadIntDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, int nDefaultValue)
{
	return GetPrivateProfileInt(lpszSection, lpszValueName, nDefaultValue, lpszFileName);
}

BOOL WizIniReadBoolDef(LPCTSTR lpszFileName, LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bDefaultValue)
{
	return 0 != GetPrivateProfileInt(lpszSection, lpszValueName, bDefaultValue ? 1 : 0, lpszFileName);
}

BOOL WizIniReadArray(LPCTSTR lpszFileName, LPCTSTR lpszSection, CWizStdStringArray& arrayData)
{
	int nCount = WizIniReadIntDef(lpszFileName, lpszSection, _T("Count"), 0);
	for (int i = 0; i < nCount; i++)
	{
		arrayData.push_back(WizIniReadStringDef(lpszFileName, lpszSection, WizIntToStr(i)));
	}
	//
	return TRUE;
}

#ifndef WINCE
BOOL WizIniReadSection(LPCTSTR lpszFileName, LPCTSTR lpszSection, DWORD dwSize, CWizStdStringArray& arrayData)
{
	if (0 == dwSize)
		return TRUE;
	//
	DWORD dwBufferSize = dwSize + MAX_PATH;
	CString strBuffer;
	LPTSTR pBuffer = strBuffer.GetBuffer(dwBufferSize);
	ZeroMemory(pBuffer, sizeof(TCHAR) * dwBufferSize);
	//
	GetPrivateProfileSection(lpszSection, pBuffer, dwBufferSize, lpszFileName);
	//
	LPCTSTR p = pBuffer;
	while (*p)
	{
		CString strLine(p);
		arrayData.push_back(strLine);
		//
		p += (strLine.GetLength() + 1);
	}
	//
	strBuffer.ReleaseBuffer();
	//
	return TRUE;
}
#endif



CString WizGetHomeURL()
{
	static CString strHomeURL;
	if (!strHomeURL.IsEmpty())
		return strHomeURL;
	//
	strHomeURL = WizGetSecuteSettings(_T("Common"), _T("Home"), TRUE);
	ATLASSERT(!strHomeURL.IsEmpty());
	//
	if (strHomeURL[strHomeURL.GetLength() - 1] != '/')
	{
		strHomeURL += _T("/");
	}
	//
	return strHomeURL;
}

CString WizGetHomeURLBase()
{
	CString strURL = WizGetHomeURL();
	//
	strURL.MakeLower();
	//
	strURL.Replace(_T("http://"), _T(""));
	strURL.Replace(_T("www."), _T(""));
	strURL.Trim(_T("/"));
	//
	return strURL;
}


CString WizGetSupportEmail()
{
	static CString strEmail;
	if (!strEmail.IsEmpty())
		return strEmail;
	//
	strEmail = CString(_T("support@")) + WizGetHomeURLBase();
	return strEmail;
}

CString WizGetAPIURL()
{
	static CString strAPIURL;
	if (!strAPIURL.IsEmpty())
		return strAPIURL;
	//
	strAPIURL = WizGetSecuteSettings(_T("Common"), _T("API"), TRUE);
	ATLASSERT(!strAPIURL.IsEmpty());
	//
	if (strAPIURL[strAPIURL.GetLength() - 1] != '/')
	{
		strAPIURL += _T("/");
	}
	//
	return strAPIURL;
}

CString WizWebSiteVisitGetURL(LPCTSTR lpszProduct, LPCTSTR lpszLanguage, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	CString strAPIURL = WizGetAPIURL();
	if (strAPIURL.IsEmpty())
		return CString();
	//
	CString strProduct(lpszProduct);
	strProduct.MakeLower();
	//
	CString strURL = strAPIURL + _T("?p=%1&l=%2&v=%3&c=%4&a=%5&random=%6&cn=%7&plat=%8");
	//
	strURL.Replace(_T("%1"), strProduct);
	strURL.Replace(_T("%2"), lpszLanguage);
	strURL.Replace(_T("%3"), lpszVersion);
	strURL.Replace(_T("%4"), lpszCommand);
	strURL.Replace(_T("%5"), lpszExtInfo);
	strURL.Replace(_T("%6"), WizIntToStr((int)GetTickCount()));
	strURL.Replace(_T("%7"), WizGetComputerName());

#ifdef _M_X64
	strURL.Replace(_T("%8"), _T("x64"));
#else
	strURL.Replace(_T("%8"), _T("x86"));
#endif
	//
	return strURL;
}


void WizWebSiteVisit(LPCTSTR lpszProduct, LPCTSTR lpszLanguage, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	CString strURL = WizWebSiteVisitGetURL(lpszProduct, lpszLanguage, lpszVersion, lpszCommand, lpszExtInfo);
	//
	ShellExecute(NULL, _T("open"), strURL, NULL, NULL, SW_SHOW);
}

void WizWebSiteVisit(LPCTSTR lpszProduct, LCID lcid, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	TCHAR sz[MAX_PATH] = {0};
	_itot_s(lcid, sz, MAX_PATH, 10);
	return WizWebSiteVisit(lpszProduct, sz, lpszVersion, lpszCommand, lpszExtInfo);
}

CString WizWebSiteGetReturn(LPCTSTR lpszProduct, LCID lcid, LPCTSTR lpszVersion, LPCTSTR lpszCommand, LPCTSTR lpszExtInfo)
{
	TCHAR szLanguage[MAX_PATH] = {0};
	_itot_s(lcid, szLanguage, MAX_PATH, 10);
	//
	CString strURL = WizWebSiteVisitGetURL(lpszProduct, szLanguage, lpszVersion, lpszCommand, lpszExtInfo);
	//
	CString strRet;
	//
	TCHAR szTempFileName[1024] = {0};
	HRESULT hr = URLDownloadToCacheFile(NULL, strURL, szTempFileName, 1024, 0, NULL);
	if (FAILED(hr))
		return strRet;
	//
	if (!PathFileExists(szTempFileName))
		return strRet;
	//
	CString strText;
	if (!WizLoadUnicodeTextFromFile(szTempFileName, strText))
		return strRet;
	//
	return strText;
}

CString WizWebSiteGetProductHomeURL()
{
	CString strProductName = WizGetProductName();
	//
	strProductName.MakeLower();
	//
	return WizWebSiteVisitGetURL(strProductName, _T(""), _T(""), _T(""), _T(""));
}

CString WizWebSiteGetHome()
{
	return WizGetHomeURL();
}

CString WizWebSiteEscapeAtt(LPCTSTR lpszAtt)
{
	TCHAR szAtt[1024] = {0};
	DWORD dwAtt = 1024;
	UrlEscape(lpszAtt, szAtt, &dwAtt, 0);
	//
	CString strAtt(szAtt);
	strAtt.Replace(_T("="), _T("%3D"));
	//
	return strAtt;
}

CString WizGetRegKeyRoot()
{
	CString strProductName = ::WizGetProductName();
	CString strCompanyName = ::WizGetCompanyName();
	//
	if (strCompanyName.IsEmpty())
	{
		return WizFormatString1(_T("Software\\%1"), strProductName);
	}
	else
	{
		return WizFormatString2(_T("Software\\%1\\%2"), strCompanyName, strProductName);
	}
}



void CWizIniFileEx::SetInt(LPCTSTR lpszSection, LPCTSTR lpszValueName, int nVal)
{
	SetString(lpszSection, lpszValueName, WizIntToStr(nVal));
}
void CWizIniFileEx::SetBool(LPCTSTR lpszSection, LPCTSTR lpszValueName, BOOL bVal)
{
	SetString(lpszSection, lpszValueName, bVal ? _T("1") : _T("0"));
}
//
CString CWizIniFileEx::GetLocalString(LPCTSTR lpszSection, LPCTSTR lpszStringName)
{
	static LCID lcid = WizTranslationsGetCurrentMappedLCID();
	static CString strStringLastName = CString(_T("_")) + WizIntToStr(lcid);
	//
	CString strValue = GetStringDef(lpszSection, CString(lpszStringName) + strStringLastName);
	if (!strValue.IsEmpty())
		return strValue;
	//
	return GetStringDef(lpszSection, lpszStringName, lpszStringName);
}
CString CWizIniFileEx::GetLocalString(LPCTSTR lpszStringName)
{
	return GetLocalString(_T("Strings"), lpszStringName);
}

IWizSettingsBase::~IWizSettingsBase()
{
}

CString IWizSettingsBase::GetStr(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDef)
{
	CString str;
	if (!GetValue(lpszSection, lpszKey, str) || str.IsEmpty())
		return CString(lpszDef);
	//
	return str;
}
int IWizSettingsBase::GetInt(LPCTSTR lpszSection, LPCTSTR lpszKey, int nDef)
{
	CString str;
	if (!GetValue(lpszSection, lpszKey, str))
		return nDef;
	//
	if (str.IsEmpty())
		return nDef;
	//
	return _ttoi(str);
}
BOOL IWizSettingsBase::GetBool(LPCTSTR lpszSection, LPCTSTR lpszKey, BOOL bDef)
{
	CString str;
	if (!GetValue(lpszSection, lpszKey, str))
		return bDef;
	//
	if (str.IsEmpty())
		return bDef;
	//
	return _ttoi(str) ? TRUE : FALSE;
}
BOOL IWizSettingsBase::SetStr(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpsz)
{
	return SetValue(lpszSection, lpszKey, lpsz);
}
BOOL IWizSettingsBase::SetInt(LPCTSTR lpszSection, LPCTSTR lpszKey, int n)
{
	return SetValue(lpszSection, lpszKey, WizIntToStr(n));
}
BOOL IWizSettingsBase::SetBool(LPCTSTR lpszSection, LPCTSTR lpszKey, BOOL b)
{
	return SetValue(lpszSection, lpszKey, b ? _T("1") : _T("0"));
}
//
BOOL IWizSettingsBase::ClearSection(LPCTSTR lpszSection)
{
	return TRUE;
}
//
BOOL IWizSettingsBase::GetStringArray(LPCTSTR lpszSection, CWizStdStringArray& arrayText)
{
	int nIndex = 0;
	while(1)
	{
		CString strKey = CString(_T("Item") + WizIntToStr(nIndex));
		CString strValue;
		if (!GetValue(lpszSection, strKey, strValue))
			return TRUE;
		//
		if (strValue.IsEmpty())
			return TRUE;
		//
		arrayText.push_back(strValue);
		//
		nIndex++;
	}
	//
	return TRUE;
}

BOOL IWizSettingsBase::SetStringArray(LPCTSTR lpszSection, const CWizStdStringArray& arrayText)
{
	ClearSection(lpszSection);
	//
	//
	int nIndex = 0;
	for (CWizStdStringArray::const_iterator it = arrayText.begin();
		it != arrayText.end();
		it++)
	{
		CString strKey = CString(_T("Item") + WizIntToStr(nIndex));
		//
		if (!SetValue(lpszSection, strKey, *it))
		{
			TOLOG(_T("Failed to set value into WizKMSettings"));
			return FALSE;
		}
		//
		nIndex++;
	}
	//
	return TRUE;
}

BOOL CWizEmptySettings::GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue)
{
	return FALSE;
}
BOOL CWizEmptySettings::SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	return FALSE;
}

#ifdef __ATLCTRLS_H__

int CWizNamedImageList::AddNamedIcon(HICON hIcon, LPCTSTR lpszName)
{
	int nIndex = AddIcon(hIcon);
	if (-1 == nIndex)
		return -1;
	//
	m_mapNameIndex[CString(lpszName)] = nIndex;
	//
	return nIndex;
}
//
int CWizNamedImageList::GetIndex(LPCTSTR lpszName)
{
	CNameIndexMap::const_iterator it = m_mapNameIndex.find(lpszName);
	if (it == m_mapNameIndex.end())
		return -1;
	//
	return it->second;
}
//
int CWizNamedImageList::GetIndexByFileName(LPCTSTR lpszFileName)
{
	CString strName = WizGetLongFileName(lpszFileName);
	strName.MakeLower();
	//
	return GetIndex(strName);
}
//
int CWizNamedImageList::SafeAddIconFile(LPCTSTR lpszFileName)
{
	CString strName = WizGetLongFileName(lpszFileName);
	strName.MakeLower();
	//
	int nIndex = GetIndex(strName);
	if (-1 != nIndex)
		return nIndex;
	//
	int width = 16;
	int height = 16;
	ImageList_GetIconSize(m_hImageList, &width, &height);
	//
	HICON hIcon = (HICON)LoadImage(NULL, lpszFileName, IMAGE_ICON, width, height, LR_LOADFROMFILE);
	if (!hIcon)
		return -1;
	//
	nIndex = AddNamedIcon(hIcon, strName);
	//
	DestroyIcon(hIcon);
	//
	return nIndex;
}
//
BOOL CWizNamedImageList::AddIcons(WIZNAMEDIMAGELISTICONDATA* pData, int nCount)
{
	int width = 16;
	int height = 16;
	ImageList_GetIconSize(m_hImageList, &width, &height);
	//
	for (int i = 0; i < nCount; i++)
	{
		HICON hIcon = (HICON)::LoadImage(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(pData[i].nIconID), IMAGE_ICON, width, height, 0);
		if (hIcon)
		{
			AddNamedIcon(hIcon, pData[i].lpszName);
		}
	}
	//
	return TRUE;
}
BOOL CWizNamedImageList::AddIcons(WIZNAMEDIMAGELISTICONDATA* pData)
{
	int nCount = 0;
	WIZNAMEDIMAGELISTICONDATA* pTemp = pData;
	while (pTemp && pTemp->lpszName)
	{
		nCount++;
		pTemp++;
	}
	//
	return AddIcons(pData, nCount);
}
//
BOOL CWizNamedImageList::CreateEx(int width, int height)
{
	return Create(width, height, ILC_COLOR32 | ILC_MASK, 0, 0);
}

#endif //__ATLCTRLS_H__


CStringA WizW2A(const wchar_t* bstrText)
{
	return WizBSTR2STR(GetACP(), bstrText);
}
CStringW WizA2W(const char* lpszText)
{
	return WizSTR2BSTR(GetACP(), lpszText);
}
CStringW WizUTF82BSTR(const char* lpszText)
{
	return WizSTR2BSTR(CP_UTF8, lpszText);
}
CStringA WizBSTR2UTF8(const wchar_t* bstrText)
{
	return WizBSTR2STR(CP_UTF8, bstrText);
}



UINT WizGetCodePage(LPCTSTR lpszCharset)
{
	CComPtr<IMultiLanguage> spMultiLanguage;
	if (FAILED(spMultiLanguage.CoCreateInstance(CLSID_CMultiLanguage)))
		return 0;
	//
	MIMECSETINFO ci;
	ZeroMemory(&ci, sizeof(MIMECSETINFO));
	if (FAILED(spMultiLanguage->GetCharsetInfo(CComBSTR(lpszCharset), &ci)))
		return 0;
	//
	return ci.uiInternetEncoding;
}

UINT WizGetCharset(LPCTSTR lpszCharset)
{
	UINT nCodePage = WizGetCodePage(lpszCharset);
	//
	CComPtr<IMultiLanguage> spMultiLanguage;
	if (FAILED(spMultiLanguage.CoCreateInstance(CLSID_CMultiLanguage)))
		return 0;
	//
	MIMECPINFO cpi;
	if (FAILED(spMultiLanguage->GetCodePageInfo(nCodePage, &cpi)))
		return 0;
	//
	return cpi.bGDICharset;
}


typedef HRESULT WINAPI Type_ConvertINetUnicodeToMultiByte(LPDWORD lpdwMode, DWORD dwEncoding, LPCWSTR lpSrcStr, LPINT lpnWideCharCount, LPSTR lpDstStr, LPINT lpnMultiCharCount);

STDAPI My_ConvertINetUnicodeToMultiByte(LPDWORD lpdwMode, DWORD dwEncoding, LPCWSTR lpSrcStr, LPINT lpnWideCharCount, LPSTR lpDstStr, LPINT lpnMultiCharCount)
{
	//return ConvertINetUnicodeToMultiByte(lpdwMode, dwEncoding, lpSrcStr, lpnWideCharCount, lpDstStr, lpnMultiCharCount);
    HRESULT hr = E_FAIL;
    HMODULE hModule = LoadLibrary(_T("mlang.dll"));
    if (hModule)
    {
#ifdef WINCE
        Type_ConvertINetUnicodeToMultiByte* fun = (Type_ConvertINetUnicodeToMultiByte *)GetProcAddress(hModule, L"ConvertINetUnicodeToMultiByte");
#else
        Type_ConvertINetUnicodeToMultiByte* fun = (Type_ConvertINetUnicodeToMultiByte *)GetProcAddress(hModule, "ConvertINetUnicodeToMultiByte");
#endif
        if (fun)
        {
            hr = fun(lpdwMode, dwEncoding, lpSrcStr, lpnWideCharCount, lpDstStr, lpnMultiCharCount);
        }
        FreeLibrary(hModule);
    }
    return hr;
}

void ReplaceWideString(CStringW& wstr, const CStringW& wstrWord, const CStringW& wstrNew)
{
    if (wstrWord.GetLength() != 1 || wstrNew.IsEmpty())
        return;
    if (-1 != wstrNew.Find(wstrWord))
        return;
    if (wstrNew.GetLength() == 1)
    {
		wstr.Replace(wstrWord[0], wstrNew[0]);
    }
    else
    {
		wstr.Replace(wstrWord, wstrNew);
    }
}

void ChangeWideString(UINT nCodePage, CStringW& wstr)
{
    CString strFileName = WizGetAppPath() + _T("strconv\\") + WizIntToStr(nCodePage) + _T(".txt");
    if (!PathFileExists(strFileName))
        return;
    size_t nLen = WizGetFileSize(strFileName);
    size_t nCount = nLen / 2;
	//
	wchar_t* psz = new wchar_t[nCount + 1];
	if (psz)
	{
		ZeroMemory(psz, (nCount + 1) * sizeof(wchar_t));
		FILE* fp = NULL;
		if (0 == _tfopen_s(&fp, strFileName, _T("rb")) && fp)
		{
			fread(psz, (nCount) * sizeof(wchar_t), 1, fp);
			wchar_t* p = psz + 1;
			wchar_t szWord[2];
			wchar_t* pReplace;
			szWord[1] = 0;
			while (p && *p)
			{
				szWord[0] = *p;
				p += 2;
				pReplace = p;
				p = wcsstr(p, L"\r\n");
				if (p)
				{
					*p = 0;
					p += 2;
				}
				ReplaceWideString(wstr, szWord, pReplace);
			}
			fclose(fp);
		}
		delete [] psz;
	}
}



CStringA WizBSTR2STR(UINT nCodePage, const wchar_t* bstrText)
{
    if (nCodePage == 0)
	{
		nCodePage = GetACP();
	}
	//
	CStringW wstr(bstrText);
	//
    ChangeWideString(nCodePage, wstr);
	//
	CStringA str;
	//
    if (51932 == nCodePage)
    {
        INT nLen = 0;
        DWORD dwMode = 0;
        if (FAILED(My_ConvertINetUnicodeToMultiByte(&dwMode, nCodePage, wstr, NULL, NULL, &nLen)))
            return CStringA(wstr);

        char* psz = new char[nLen + 1];
		if (!psz)
            return CStringA(wstr);
        ZeroMemory(psz, nLen + 1);
        My_ConvertINetUnicodeToMultiByte(&dwMode, nCodePage, wstr, NULL, psz, &nLen);
		//
		str = psz;
		//
	    delete [] psz;
    }
    else
    {
        int nLen = WideCharToMultiByte(nCodePage, 0, wstr, -1, NULL, 0, NULL, NULL);
        if (nLen <= 0)
            return CStringA(wstr);

        char* psz = new char[nLen + 1];
		if (!psz)
            return CStringA(wstr);
        ZeroMemory(psz, nLen + 1);
        int nWritten = WideCharToMultiByte(nCodePage, 0, wstr, -1, psz, nLen + 1, NULL, NULL);
		//
#ifdef __ATLBASE_H__
		ATLASSERT(nWritten == nLen);
#elif defined __AFX_H__
		ASSERT(nWritten == nLen);
#else
		if (nWritten != nLen)
		{
			assert(false);
		}
#endif
		//
	    str = psz;
		//
		delete [] psz;
    }
    return str;
}
CStringA WizBSTR2STR(LPCTSTR lpszCharset, const wchar_t* bstrText)
{
    UINT nCodePage = WizGetCodePage(lpszCharset);
	return WizBSTR2STR(nCodePage, bstrText);
}

typedef HRESULT WINAPI Type_ConvertINetMultiByteToUnicode(LPDWORD lpdwMode, DWORD dwEncoding, LPCSTR lpSrcStr, LPINT lpnMultiCharCount, LPWSTR lpDstStr, LPINT lpnWideCharCount);

STDAPI My_ConvertINetMultiByteToUnicode(LPDWORD lpdwMode, DWORD dwEncoding, LPCSTR lpSrcStr, LPINT lpnMultiCharCount, LPWSTR lpDstStr, LPINT lpnWideCharCount)
{
	//return ConvertINetMultiByteToUnicode(lpdwMode, dwEncoding, lpSrcStr, lpnMultiCharCount, lpDstStr, lpnWideCharCount);
    HRESULT hr = E_FAIL;
    HMODULE hModule = LoadLibrary(_T("mlang.dll"));
    if (hModule)
    {
        Type_ConvertINetMultiByteToUnicode* fun = (Type_ConvertINetMultiByteToUnicode *)GetProcAddress(hModule, "ConvertINetMultiByteToUnicode");
        if (fun)
        {
            hr = fun(lpdwMode, dwEncoding, lpSrcStr, lpnMultiCharCount, lpDstStr, lpnWideCharCount);
        }
        FreeLibrary(hModule);
    }
    return hr;
}




CStringW WizSTR2BSTR(UINT nCodePage, const CStringA& strSrc)
{
	CStringA str(strSrc);
	if (str.GetLength() > 3)
	{
		if (str[0] == (char)0xEF && str[1] == (char)0xBB && str[2] == (char)0xBF)
		{
			str.Delete(0, 3);
			nCodePage = CP_UTF8;
		}
	}
	//
    if (nCodePage == 0)
	{
		nCodePage = WizAutoDetectTextCodePage(str);
	}
	//
    CStringW wstr;
	//
    if (nCodePage == 51932)
    {
        int nLen = str.GetLength() + 1;
        BSTR bstrText = SysAllocStringLen(NULL, nLen);
		if (!bstrText)
			return CStringW(str);
		//
		ZeroMemory(bstrText, sizeof(wchar_t) * nLen);
		//
		DWORD dwMode = 0;
		if (FAILED(My_ConvertINetMultiByteToUnicode(&dwMode, nCodePage, str, NULL, bstrText, &nLen)))
			return CStringW(str);
		//
		wstr = bstrText;
		//
		SysAllocString(bstrText);
    }
    else
    {
        int nLen = MultiByteToWideChar(nCodePage, 0, str, -1, NULL, 0);
        if (nLen <= 0)
            return CStringW(str);
        nLen += 1;

        BSTR bstrText = SysAllocStringLen(NULL, nLen);
		if (!bstrText)
            return CStringW(str);

        ZeroMemory(bstrText, sizeof(wchar_t) * nLen);
        MultiByteToWideChar(nCodePage, 0, str, -1, bstrText, nLen);
		//
        wstr = bstrText;
		//
        ::SysFreeString(bstrText);
    }
    return wstr;
}

CStringW WizSTR2BSTR(LPCTSTR lpszCharset, const CStringA& str)
{
    UINT nCodePage = WizGetCodePage(lpszCharset);
	//
	return WizSTR2BSTR(nCodePage, str);
}


CString WizHTMLGetCharsetFromHTMLText(const CStringA& strText)
{
    const char* pBegin = strText;
    const char* p = pBegin;
    //
    while (1)
    {
        const char* p1 = StrStrIA(p, "<meta");
        if (!p1)
            return CString();
		//
        const char* p2 = strchr(p1, '>');
        if (!p2)
            return CString();
		p2++;
        //
        CStringA strMeta = strText.Mid(int(p1 - pBegin), int(p2 - p1));
        //
        p = p2;
        //
        int nPos = (int)WizStrStrI_PosA(strMeta, "charset=");
        if (nPos == -1)
            continue;
        strMeta.Delete(0, nPos + 8);
        int nPos1 = strMeta.Find("\"");
        int nPos2 = strMeta.Find(">");
        if (nPos1 == -1)
            nPos = nPos2;
        else if (nPos2 == -1)
            nPos = nPos1;
        else
            nPos = min(nPos1, nPos2);
        if (nPos == -1)
            return CString();
		//
        CString strCharset(strMeta.Mid(0, nPos));
        nPos = strCharset.Find(_T(" "));
        if (nPos == -1)
            return strCharset;
        strCharset = strCharset.Mid(0, nPos);
        return strCharset;
    }
}
CString WizXMLGetCharsetFromXMLText(const CStringA& strText)
{
    const char* pBegin = strText;
    const char* p = pBegin;
	//
	CString strCharset;
    //
    const char* p1 = StrStrIA(p, "<?xml");
    if (!p1)
        return strCharset;
    const char* p2 = strchr(p1, '>');
    if (!p2)
        return strCharset;
    //
    CStringA strMark = strText.Mid(int(p1 - pBegin), int(p2 - p1));
    //
    p = p2;
    //
    int nPos = (int)WizStrStrI_PosA(strMark, "encoding=");
    if (nPos == -1)
        return strCharset;
	//
    strMark.Delete(0, nPos + 9);
	//
	strMark.Replace('"', ' ');
	strMark.Replace('\'', ' ');
	strMark.Replace('?', ' ');
	//
	strMark.Trim();
	//
	strCharset = CString(strMark);
	//
	int nPosEnd = strCharset.Find(' ');
	if (-1 == nPosEnd)
		return strCharset;
	//
	return strCharset.Left(nPosEnd);
}

BOOL WizHtmlAnsiToUnicode(const char* lpszText, CStringW& strText)
{
	CString strCharset = WizHTMLGetCharsetFromHTMLText(CStringA(lpszText));
	if (strCharset.IsEmpty())
	{
		strText = WizSTR2BSTR(WizAutoDetectTextCodePage(lpszText), lpszText);
	}
	else
	{
		strText = WizSTR2BSTR(strCharset, lpszText);
	}
	return TRUE;
}

BOOL WizXmlAnsiToUnicode(const char* lpszText, CStringW& strText)
{
	CString strCharset = WizXMLGetCharsetFromXMLText(CStringA(lpszText));
	if (strCharset.IsEmpty())
	{
		strText = WizSTR2BSTR(WizAutoDetectTextCodePage(lpszText), lpszText);
	}
	else
	{
		strText = WizSTR2BSTR(strCharset, lpszText);
	}
	return TRUE;
}



CString WizLcidToRfc1766String(LCID lcid)
{
	if (0 == lcid)
		return CString();
	//
	CComPtr<IMultiLanguage> spMultiLanguage;
	if (FAILED(spMultiLanguage.CoCreateInstance(CLSID_CMultiLanguage)))
		return CString();
	//
	CComBSTR bstr;
	spMultiLanguage->GetRfc1766FromLcid(lcid, &bstr);
	//
	return CString(bstr);
}


BOOL WizGetDefaultCharset(BSTR* pbstrCharset) throw()
{
	if (!pbstrCharset)
		return FALSE;

	BOOL bRet = FALSE;

#ifndef WINCE
	CoInitialize(NULL);
#endif
	try
	{

		IMultiLanguage* pMultiLanguage = NULL;
		if (S_OK == CoCreateInstance(CLSID_CMultiLanguage, NULL, CLSCTX_INPROC_SERVER, IID_IMultiLanguage, (void**)&pMultiLanguage))
		{
			UINT uiCodePage = GetACP();
			MIMECPINFO cpInfo;
			memset(&cpInfo, 0x00, sizeof(cpInfo));

			if (S_OK == pMultiLanguage->GetCodePageInfo(uiCodePage, &cpInfo))
			{
				*pbstrCharset = SysAllocString(cpInfo.wszWebCharset);

				bRet = TRUE;
			}
			pMultiLanguage->Release();
		}
	}
	catch (...)
	{
	}
#ifndef WINCE
	CoUninitialize();
#endif

	return bRet;
}
BOOL WizGetDefaultCharsetDescription(BSTR* pbstrCharsetDescription) throw()
{
	if (!pbstrCharsetDescription)
		return FALSE;

	BOOL bRet = FALSE;

#ifndef WINCE
	CoInitialize(NULL);
#endif
	try
	{

		IMultiLanguage* pMultiLanguage = NULL;
		if (S_OK == CoCreateInstance(CLSID_CMultiLanguage, NULL, CLSCTX_INPROC_SERVER, IID_IMultiLanguage, (void**)&pMultiLanguage))
		{
			UINT uiCodePage = GetACP();
			MIMECPINFO cpInfo;
			memset(&cpInfo, 0x00, sizeof(cpInfo));

			if (S_OK == pMultiLanguage->GetCodePageInfo(uiCodePage, &cpInfo))
			{
				*pbstrCharsetDescription = SysAllocString(cpInfo.wszDescription);

				bRet = TRUE;
			}
			pMultiLanguage->Release();
		}
	}
	catch (...)
	{
	}
#ifndef WINCE
	CoUninitialize();
#endif

	return bRet;
}
BOOL WizGetCharsetDescription(BSTR bstrCharset, BSTR* pbstrCharsetDescription) throw()
{
	if (!pbstrCharsetDescription)
		return FALSE;

	BOOL bRet = FALSE;

#ifndef WINCE
	CoInitialize(NULL);
#endif
	try
	{
		IMultiLanguage* pMultiLanguage = NULL;
		if (S_OK == CoCreateInstance(CLSID_CMultiLanguage, NULL, CLSCTX_INPROC_SERVER, IID_IMultiLanguage, (void**)&pMultiLanguage))
		{
            MIMECSETINFO info;
            memset(&info, 0, sizeof(MIMECSETINFO));
			if (S_OK == pMultiLanguage->GetCharsetInfo(bstrCharset, &info))
			{
                *pbstrCharsetDescription = SysAllocString(info.wszCharset);
                //
				bRet = TRUE;
			}
			pMultiLanguage->Release();
		}
	}
	catch (...)
	{
	}
#ifndef WINCE
	CoUninitialize();
#endif

	return bRet;
}

CString WizGetDefaultCharset()
{
	CString strRet("iso-8859-1");

	BSTR bstrCharset = NULL;
	if (WizGetDefaultCharset(&bstrCharset))
	{
		strRet = bstrCharset;
		SysFreeString(bstrCharset);
	}
	return strRet;
}


BOOL WizTestConvertToUnicode(const char* lpszText, UINT nCodePage, DWORD dwMultiByteToWideCharFlags)
{
	if (MultiByteToWideChar(nCodePage, dwMultiByteToWideCharFlags, lpszText, int(strlen(lpszText)), NULL, 0) > 0)
		return TRUE;
	//
	if (ERROR_NO_UNICODE_TRANSLATION == GetLastError())
		return FALSE;
	//
	return TRUE;
}

UINT WizAutoDetectTextCodePage(const char* lpszText)
{
	UINT nCodePageDefault = GetACP();
	BOOL bDefault = WizTestConvertToUnicode(lpszText, nCodePageDefault, MB_ERR_INVALID_CHARS);
	if (bDefault)
		return nCodePageDefault;
	//
	UINT nCodePageUTF8 = CP_UTF8;
	BOOL bUTF8 = WizTestConvertToUnicode(lpszText, nCodePageUTF8, 0);
	if (bUTF8)
		return nCodePageUTF8;
	//
	return nCodePageDefault;
}



int WizHTMLColorCharToNum(TCHAR c)
{
    if (c >= _T('0') && c <= _T('9'))
        return c - _T('0');
    else if (c >= _T('A') && c <= _T('F'))
        return c - _T('A') + 10;
    else if (c >= _T('a') && c <= _T('f'))
        return c - _T('a') + 10;
    else
        return 0;
}

COLORREF WizHTMLStringToColor(LPCTSTR lpszColor)
{
    COLORREF crDefault = -1;
	//
	CString strColor(lpszColor);
	//
    if (strColor.IsEmpty())
        return crDefault;
    if (strColor[0] == _T('#'))
        strColor.Delete(0, 1);
    strColor = strColor.Trim();
    if (strColor.GetLength() != 6)
        return crDefault;
	//
    strColor.MakeLower();
	//
    int nR = WizHTMLColorCharToNum(strColor[0]) * 16 + WizHTMLColorCharToNum(strColor[1]);
    int nG = WizHTMLColorCharToNum(strColor[2]) * 16 + WizHTMLColorCharToNum(strColor[3]);
    int nB = WizHTMLColorCharToNum(strColor[4]) * 16 + WizHTMLColorCharToNum(strColor[5]);
	//
    return RGB(nR, nG, nB);
}


#define HTML_COLOR_COUNT     140
static const char* g_arrayColors[HTML_COLOR_COUNT * 2] =
{
    "aliceblue",
    "#F0F8FF",
    "antiquewhite",
    "#FAEBD7",
    "aqua",
    "#00FFFF",
    "aquamarine",
    "#7FFFD4",
    "azure",
    "#F0FFFF",
    "beige",
    "#F5F5DC",
    "bisque",
    "#FFE4C4",
    "black",
    "#000000",
    "blanchedalmond",
    "#FFEBCD",
    "blue",
    "#0000FF",
    "blueviolet",
    "#8A2BE2",
    "brown",
    "#A52A2A",
    "burlywood",
    "#DEB887",
    "cadetblue",
    "#5F9EA0",
    "chartreuse",
    "#7FFF00",
    "chocolate",
    "#D2691E",
    "coral",
    "#FF7F50",
    "cornflowerblue",
    "#6495ED",
    "cornsilk",
    "#FFF8DC",
    "crimson",
    "#DC143C",
    "cyan",
    "#00FFFF",
    "darkblue",
    "#00008B",
    "darkcyan",
    "#008B8B",
    "darkgoldenrod",
    "#B8860B",
    "darkgray",
    "#A9A9A9",
    "darkgreen",
    "#006400",
    "darkkhaki",
    "#BDB76B",
    "darkmagenta",
    "#8B008B",
    "darkolivegreen",
    "#556B2F",
    "darkorange",
    "#FF8C00",
    "darkorchid",
    "#9932CC",
    "darkred",
    "#8B0000",
    "darksalmon",
    "#E9967A",
    "darkseagreen",
    "#8FBC8B",
    "darkslateblue",
    "#483D8B",
    "darkslategray",
    "#2F4F4F",
    "darkturquoise",
    "#00CED1",
    "darkviolet",
    "#9400D3",
    "deeppink",
    "#FF1493",
    "deepskyblue",
    "#00BFFF",
    "dimgray",
    "#696969",
    "dodgerblue",
    "#1E90FF",
    "firebrick",
    "#B22222",
    "floralwhite",
    "#FFFAF0",
    "forestgreen",
    "#228B22",
    "fuchsia",
    "#FF00FF",
    "gainsboro",
    "#DCDCDC",
    "ghostwhite",
    "#F8F8FF",
    "gold",
    "#FFD700",
    "goldenrod"
    "#DAA520",
    "gray",
    "#808080",
    "green",
    "#008000",
    "greenyellow",
    "#ADFF2F",
    "honeydew",
    "#F0FFF0",
    "hotpink",
    "#FF69B4",
    "indianred",
    "#CD5C5C",
    "indigo",
    "#4B0082",
    "ivory",
    "#FFFFF0",
    "khaki",
    "#F0E68C",
    "lavender",
    "#E6E6FA",
    "lavenderblush",
    "#FFF0F5",
    "lawngreen",
    "#7CFC00",
    "lemonchiffon",
    "#FFFACD",
    "lightblue",
    "#ADD8E6",
    "lightcoral",
    "#F08080",
    "lightcyan",
    "#E0FFFF",
    "lightgoldenrodyellow",
    "#FAFAD2",
    "lightgreen",
    "#90EE90",
    "lightgrey",
    "#D3D3D3",
    "lightpink",
    "#FFB6C1",
    "lightsalmon",
    "#FFA07A",
    "lightseagreen",
    "#20B2AA",
    "lightskyblue",
    "#87CEFA",
    "lightslategray",
    "#778899",
    "lightsteelblue",
    "#B0C4DE",
    "lightyellow",
    "#FFFFE0",
    "lime",
    "#00FF00",
    "limegreen",
    "#32CD32",
    "linen",
    "#FAF0E6",
    "magenta",
    "#FF00FF",
    "maroon",
    "#800000",
    "mediumaquamarine",
    "#66CDAA",
    "mediumblue",
    "#0000CD",
    "mediumorchid",
    "#BA55D3",
    "mediumpurple",
    "#9370DB",
    "mediumseagreen",
    "#3CB371",
    "mediumslateblue",
    "#7B68EE",
    "mediumspringgreen",
    "#00FA9A",
    "mediumturquoise",
    "#48D1CC",
    "mediumvioletred",
    "#C71585",
    "midnightblue",
    "#191970",
    "mintcream",
    "#F5FFFA",
    "mistyrose",
    "#FFE4E1",
    "moccasin",
    "#FFE4B5",
    "navajowhite",
    "#FFDEAD",
    "navy",
    "#000080",
    "oldlace",
    "#FDF5E6",
    "olive",
    "#808000",
    "olivedrab",
    "#6B8E23",
    "orange",
    "#FFA500",
    "orangered",
    "#FF4500",
    "orchid",
    "#DA70D6",
    "palegoldenrod",
    "#EEE8AA",
    "palegreen",
    "#98FB98",
    "paleturquoise",
    "#AFEEEE",
    "palevioletred",
    "#DB7093",
    "papayawhip",
    "#FFEFD5",
    "peachpuff",
    "#FFDAB9",
    "peru",
    "#CD853F",
    "pink",
    "#FFC0CB",
    "plum",
    "#DDA0DD",
    "powderblue",
    "#B0E0E6",
    "purple",
    "#800080",
    "red",
    "#FF0000",
    "rosybrown",
    "#BC8F8F",
    "royalblue",
    "#4169E1",
    "saddlebrown",
    "#8B4513",
    "salmon",
    "#FA8072",
    "sandybrown",
    "#F4A460",
    "seagreen",
    "#2E8B57",
    "seashell",
    "#FFF5EE",
    "sienna",
    "#A0522D",
    "silver",
    "#C0C0C0",
    "skyblue",
    "#87CEEB",
    "slateblue",
    "#6A5ACD",
    "slategray",
    "#708090",
    "snow",
    "#FFFAFA",
    "springgreen",
    "#00FF7F",
    "steelblue",
    "#4682B4",
    "tan",
    "#D2B48C",
    "teal",
    "#008080",
    "thistle",
    "#D8BFD8",
    "tomato",
    "#FF6347",
    "turquoise",
    "#40E0D0",
    "violet",
    "#EE82EE",
    "wheat",
    "#F5DEB3",
    "white",
    "#FFFFFF",
    "whitesmoke",
    "#F5F5F5",
    "yellow",
    "#FFFF00",
    "yellowgreen",
    "#9ACD32",
};

COLORREF WizHTMLColorNameToColor(LPCTSTR lpszName)
{
	CStringA str(lpszName);
	//
	str.MakeLower();
	for (int i = 0; i < HTML_COLOR_COUNT; i++)
	{
		if (0 == str.CompareNoCase(g_arrayColors[i * 2]))
		{
			return WizHTMLStringToColor(CString(g_arrayColors[i * 2 + 1]));
		}
	}
	return 0;
}

COLORREF WizHTMLStringColorToColor(LPCTSTR lpszHTMLColor)
{
	CString str(lpszHTMLColor);
	if (str.IsEmpty())
		return -1;
	//
    if (str[0] == '#')
    {
        return WizHTMLStringToColor(str);
    }
    else
    {
        return WizHTMLColorNameToColor(str);
    }
}
COLORREF WizHTMLVariantColorToColor(const VARIANT& v)
{
    if (v.vt == VT_I4)
    {
        return COLORREF(v.lVal);
    }
    else if (v.vt == VT_BSTR)
    {
		BSTR bstr = v.bstrVal;
        if (bstr && SysStringLen(bstr) > 0)
        {
			return WizHTMLStringColorToColor(CString(bstr));
        }
    }
    return -1;
}
CString WizHTMLColorToStringColor(COLORREF cr)
{
	if ((COLORREF)-1 == cr)
		return CString();
	//
	CString str;
	str.Format(_T("#%02X%02X%02X"), GetRValue(cr), GetGValue(cr), GetBValue(cr));
	return str;
}



struct LCIDMAPDATA
{
	LCID lcid;
	LCID lcidMapped;
};

static const LCIDMAPDATA g_arrayLCIDMaps[]=
{
	{3076, 1028},
	{1028, 1028},
	{5124, 1028},

	{2052, 2052},
	{4100, 2052},

	{0, 0}
};

LCID WizTranslationsMapLCID(LCID lcid)
{
	for (int i = 0; ; i++)
	{
		if (g_arrayLCIDMaps[i].lcid == 0)
			return lcid;
		//
		if (lcid == g_arrayLCIDMaps[i].lcid)
			return g_arrayLCIDMaps[i].lcidMapped;
	}
}
CString WizTranslationsGetLCIDName(LCID lcid)
{
	TCHAR szName[1024] = {0};
	GetLocaleInfo(lcid, LOCALE_SLANGUAGE, szName, 1024);
	//
	return CString(szName);
}

CString WizTranslationsGetDefaultProductName()
{
	static CString strProductName;
	if (!strProductName.IsEmpty())
		return strProductName;
	//
	CString strConfigFileName = WizGetAppPath() + _T("translations.ini");
	if (PathFileExists(strConfigFileName))
	{
		TCHAR szProductName[MAX_PATH] = {0};
		GetPrivateProfileString(_T("Common"), _T("ProductName"), NULL, szProductName, MAX_PATH, strConfigFileName);
		//
		if (*szProductName)
		{
			strProductName = szProductName;
		}
	}
	//
	if (strProductName.IsEmpty())
	{
		strProductName = WizGlobal()->GetProductName();
	}
	//
	return strProductName;
}
//
CString WizTranslationsGetKey()
{
	return ::WizGetRegKeyRoot();
}

LCID WizTranslationsGetCurrentMappedLCID()
{
	LCID lcid = WizRegReadInt32Def(HKEY_CURRENT_USER, WizTranslationsGetKey(), _T("LCID"), 0);
	//
	if (0 == lcid)
	{
		lcid = GetUserDefaultLCID();
	}
	//
	CString strUIExcludes = ::WizGetSecuteSettings(_T("Common"), _T("UIExcludes"), TRUE);
	CWizStdStringArray arrayUIExcludes;
	::WizSplitTextToArray(strUIExcludes, ',', arrayUIExcludes);
	if (-1 != ::WizFindInArray(arrayUIExcludes, WizIntToStr(lcid)))
	{
		lcid = 0;
	}
	//
	return WizTranslationsMapLCID(lcid);
}

BOOL WizTranslationsSetCurrentMappedLCID(LCID lcid)
{
	return WizRegWriteInt32(HKEY_CURRENT_USER, WizTranslationsGetKey(), _T("LCID"), int(lcid));
}


//
BOOL WizTranslationsIsUsingDefaultResource()
{
	return WizTranslationsGetResourcesPath().IsEmpty();
}

CString WizTranslationsGetResourcesBasePath()
{
	static CString strResourcePath;
	//
	if (!strResourcePath.IsEmpty())
		return strResourcePath;
	//
	CString strAppPath = WizGetAppPath();
	//
	CString strConfigFileName = strAppPath + _T("translations.ini");
	if (PathFileExists(strConfigFileName))
	{
		TCHAR szValue[MAX_PATH] = {0};
		GetPrivateProfileString(_T("Common"), _T("Path"), NULL, szValue, MAX_PATH, strConfigFileName);
		if (*szValue)
		{
			TCHAR szResultPath[MAX_PATH] = {0};
			PathCombine(szResultPath, strAppPath, szValue);
			strResourcePath = szResultPath;
		}
	}
	//
	if (strResourcePath.IsEmpty())
	{
		strResourcePath = strAppPath + _T("translations\\");
	}
	WizPathAddBackslash(strResourcePath);
	//
	return strResourcePath;
}

CString WizTranslationsGetResourcesPath()
{
	LCID lcid = WizTranslationsGetCurrentMappedLCID();
	//
	if (0 == lcid)
		return CString();
	//
	CString strResourceBasePath = WizTranslationsGetResourcesBasePath();
	//
	CString strResourcePath = strResourceBasePath + WizIntToStr(int(lcid)) + _T("\\");
	//
	if (!PathFileExists(strResourcePath))
		return CString();
	//
	return strResourcePath;
}
BOOL WizTranslationsEnumSupportedLanguages(std::vector<LCID>& arrayLCIDs)
{
	CString strResourcePath = WizTranslationsGetResourcesBasePath();
	//
	CWizStdStringArray arrayFolders;
	WizEnumFolders(strResourcePath, arrayFolders, 0);
	//
	size_t nCount = arrayFolders.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strPath = CString(arrayFolders[i]);
		//
		WizPathRemoveBackslash(strPath);
		//
		CString strLCID = WizExtractFileName(strPath);
		//
		LCID lcid = _ttoi(strLCID);
		//
		if (0 != lcid)
		{
			arrayLCIDs.push_back(lcid);
		}
	}
	//
	return TRUE;
}



class CWizTranslations
{
public:
	CWizTranslations()
	{
	}
	virtual ~CWizTranslations()
	{
	}
private:
	CWizTranslationsStringTable m_st;
public:
	BOOL LoadString(UINT nStringID, CString& strRet)
	{
		return m_st.LoadString(nStringID, strRet);
	}
	CString LoadString(UINT nStringID)
	{
		return m_st.LoadString(nStringID);
	}
	BOOL TranslateString(LPCTSTR lpszSrc, CString& strRet)
	{
		return m_st.TranslateString(lpszSrc, strRet);
	}
	CString TranslateString(LPCTSTR lpszSrc)
	{
		return m_st.TranslateString(lpszSrc);
	}
	//
	BOOL TranslateMenu(HMENU hMenu)
	{
		return m_st.TranslateMenu(hMenu);
	}
	BOOL TranslateWindow(HWND hWnd)
	{
		return m_st.TranslateWindow(hWnd);
	}
	BOOL TranslatePropertySheet(HWND hWnd)
	{
		return m_st.TranslatePropertySheet(hWnd);
	}
public:
	BOOL Init()
	{
		//m_st.Clear();
		//
		CString strResourcePath = WizTranslationsGetResourcesPath();
		if (strResourcePath.IsEmpty())
			return FALSE;

		CString strFileName = strResourcePath + WizExtractFileTitle(WizGetAppFileName()) + _T(".ini");
		CString strSharedFileName = strResourcePath + _T("share.ini");
		CString strGlobalsFileName = strResourcePath + _T("globals.ini");
		//
		if (!PathFileExists(strFileName))
			return FALSE;
		//
		m_st.AddStringsFromFile(strGlobalsFileName);
		m_st.AddStringsFromFile(strSharedFileName);
		//
		return m_st.AddStringsFromFile(strFileName); 
	}
	BOOL InitByText(LPCWSTR lpszText)
	{
		m_st.Clear();
		//
		return m_st.AddStrings(lpszText);
	}
	//
	BOOL AddResourceFile(LPCTSTR lpszFileName)
	{
		return m_st.AddStringsFromFile(lpszFileName);
	}
};

CWizTranslations theTranslations;


BOOL WizTranslationsInit()
{
	return theTranslations.Init();
}
BOOL WizTranslationsInitByText(LPCWSTR lpszText)
{
	return theTranslations.InitByText(lpszText);
}
BOOL WizTranslationsInitByResourceDirect(LPCTSTR lpszResourceType, LPCTSTR lpszResourceName)
{
	HINSTANCE hInstance = _AtlBaseModule.GetModuleInstance();
	//
	HRSRC hRes = FindResource(hInstance, lpszResourceName, lpszResourceType); 
	if (!hRes) 
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	int nSize = SizeofResource(hInstance, hRes);
	HRSRC hResLoad = (HRSRC)LoadResource(hInstance, hRes); 
	if (hResLoad)
	{
		BYTE * lpResLock = (BYTE *)LockResource(hResLoad); 
		if (lpResLock) 
		{
			CStringW strText;
			if (WizLoadUnicodeTextFromBuffer((const char *)lpResLock, nSize, strText))
			{
				bRet = WizTranslationsInitByText(strText);
			}
			//
			//UnlockResource(hResLoad);
		}
		//FreeResource(hResLoad);
	}
	//
	return bRet;
}
BOOL WizTranslationsInitByResource(LPCTSTR lpszResourceType)
{
	LCID lcid = WizTranslationsGetCurrentMappedLCID();
	//
	if (0 == lcid)
		return FALSE;
	//
	return WizTranslationsInitByResourceDirect(lpszResourceType, MAKEINTRESOURCE(lcid));
}

BOOL WizTranslationsAddResourceFile(LPCTSTR lpszFileName)
{
	return theTranslations.AddResourceFile(lpszFileName);
}
//
BOOL WizTranslationsLoadString(UINT nID, CString& strRet)
{
	return theTranslations.LoadString(nID, strRet);
}
//
CString WizTranslationsLoadString(UINT nID)
{
	return theTranslations.LoadString(nID);
}
//
BOOL WizTranslationsTranslateString(LPCTSTR lpszSrc, CString& strRet)
{
	return theTranslations.TranslateString(lpszSrc, strRet);
}
//
CString WizTranslationsTranslateString(LPCTSTR lpszSrc)
{
	return theTranslations.TranslateString(lpszSrc);
}
//
BOOL WizTranslationsTranslateWindow(HWND hWnd)
{
	return theTranslations.TranslateWindow(hWnd);
}
BOOL WizTranslationsTranslatePropertySheet(HWND hWnd)
{
	return theTranslations.TranslatePropertySheet(hWnd);
}
BOOL WizTranslationsTranslateMenu(HMENU hMenu)
{
	return theTranslations.TranslateMenu(hMenu);
}

int WizMenuCommandToIndex(HMENU hMenu, UINT nCommand)
{
	TCHAR szMenuItem[MAX_PATH] = {0};
	//
	int nMenuItemCount = GetMenuItemCount(hMenu);
	for (int i = 0; i < nMenuItemCount; i++)
	{
		*szMenuItem = 0;
		//
		MENUITEMINFO miOld;
		ZeroMemory(&miOld, sizeof(MENUITEMINFO));
		miOld.cbSize = sizeof(MENUITEMINFO);
		miOld.fMask = MIIM_ID;
		miOld.dwTypeData = NULL;
		miOld.cch = 0;
		//
		if (GetMenuItemInfo(hMenu, i, TRUE, &miOld))
		{
			if (miOld.wID == nCommand)
				return i;
		}
	}
	//
	return -1;
}

int WizMenuGetSubMenuIndex(HMENU hMenu, UINT nSubMenuNimber)
{
	UINT nIndex = 0;
	int nMenuItemCount = GetMenuItemCount(hMenu);
	for (int i = 0; i < nMenuItemCount; i++)
	{
		if (GetSubMenu(hMenu, i))
		{
			if (nIndex == nSubMenuNimber)
				return i;
			//
			nIndex++;
		}
	}
	//
	return -1;
}
BOOL WizMenuIsSeparator(HMENU hMenu, int nIndex)
{
	MENUITEMINFO miOld;
	ZeroMemory(&miOld, sizeof(MENUITEMINFO));
	miOld.cbSize = sizeof(MENUITEMINFO);
	miOld.fMask = MIIM_TYPE;
	miOld.dwTypeData = NULL;
	miOld.cch = 0;
	//
	if (GetMenuItemInfo(hMenu, nIndex, TRUE, &miOld))
	{
		if (miOld.fType == MF_SEPARATOR)
			return TRUE;
	}
	//
	return FALSE;
}
void WizMenuRemoveMultiSeparator(HMENU hMenu)
{
	int nMenuItemCount = GetMenuItemCount(hMenu);
	for (int i = nMenuItemCount - 1; i >= 1; i--)
	{
		if (WizMenuIsSeparator(hMenu, i)
			&& WizMenuIsSeparator(hMenu, i - 1))
		{
			DeleteMenu(hMenu, i, MF_BYPOSITION);
		}
	}
}


UINT WizGetCodePageFromLCID(LCID lcid)
{
	TCHAR szBuffer[MAX_PATH] = {0};
	if (0 == GetLocaleInfo(lcid, LOCALE_IDEFAULTANSICODEPAGE, szBuffer, MAX_PATH))
		return GetACP();
	//
	return _ttoi(szBuffer);
}



CWizTranslationsStringTable::CWizTranslationsStringTable()
{
}
CWizTranslationsStringTable::CWizTranslationsStringTable(LPCTSTR lpszFileName)
{
	AddStringsFromFile(lpszFileName);
}
CWizTranslationsStringTable::~CWizTranslationsStringTable()
{
}
void CWizTranslationsStringTable::EncodeString(CString& str)
{
	for (int i = 0; i < str.GetLength(); i++)
	{
		TCHAR ch = str[i];
		if (ch == '\\')
		{
			str.Insert(i + 1, '\\');
			i++;
		}
		else if (ch == '\r')
		{
			str.SetAt(i, '\\');
			str.Insert(i + 1, 'r');
			i++;
		}
		else if (ch == '\n')
		{
			str.SetAt(i, '\\');
			str.Insert(i + 1, 'n');
			i++;
		}
		else if (ch == '\t')
		{
			str.SetAt(i, '\\');
			str.Insert(i + 1, 't');
			i++;
		}
		else if (ch == '"')
		{
			str.SetAt(i, '"');
			str.Insert(i + 1, '"');
			i++;
		}
	}
}
void CWizTranslationsStringTable::DecodeString(CString& str)
{
	if (str.GetLength() <= 1)
		return;
	//
	for (int i = 0; i < str.GetLength() - 1; i++)
	{
		TCHAR ch = str[i];
		if (ch == '\\')
		{
			TCHAR chNext = str[i + 1];
			if (chNext == '\\')
			{
				str.Delete(i + 1);
			}
			else if (chNext == 'r')
			{
				str.SetAt(i, '\r');
				str.Delete(i + 1);
			}
			else if (chNext == 'n')
			{
				str.SetAt(i, '\n');
				str.Delete(i + 1);
			}
			else if (chNext == 't')
			{
				str.SetAt(i, '\t');
				str.Delete(i + 1);
			}
		}
		else if (ch == '"')
		{
			TCHAR chNext = str[i + 1];
			if (chNext == '"')
			{
				str.SetAt(i, '\"');
				str.Delete(i + 1);
			}
		}
	}
}

void CWizTranslationsStringTable::Clear()
{
	m_mapStrings.clear();
}
//
BOOL CWizTranslationsStringTable::AddStrings(const CWizStdStringArray& arrayText)
{
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = CString(arrayText[i]);
		strLine.Trim();
		if (strLine.IsEmpty())
			continue;
		//
		if (strLine[0] == ';')
			continue;
		//
		//if (strLine[0] == '[')
		//	continue;
		//
		int nPos = strLine.Find('=');
		if (-1 != nPos)
		{
			CString strLeft = strLine.Left(nPos);
			strLine.Delete(0, nPos + 1);
			//
			m_mapStrings[strLeft] = strLine;
		}
	}
	return TRUE;
}
BOOL CWizTranslationsStringTable::AddStrings(LPCWSTR lpszText)
{
	CWizStdStringArray arrayText;
	WizSplitTextToArray(lpszText, '\n', arrayText);
	return AddStrings(arrayText);
}
BOOL CWizTranslationsStringTable::AddStringsFromFile(LPCTSTR lpszFileName)
{
	CWizStdStringArray arrayText;
	if (!WizStringArrayLoadFromFile(lpszFileName, arrayText))
		return FALSE;
	//
	//
	return AddStrings(arrayText);
}
//
BOOL CWizTranslationsStringTable::TranslateString(LPCTSTR lpszSrc, CString& strRet)
{
	strRet = lpszSrc;
	//
	CString strSrc(lpszSrc);
	if (strSrc.IsEmpty())
		return FALSE;;
	//
	EncodeString(strSrc);
	//
	CWizTranslationsStringMap::const_iterator it = m_mapStrings.find(strSrc);
	if (it == m_mapStrings.end())
		return FALSE;
	//
	strRet = it->second;
	//
	DecodeString(strRet);
	//
	if (!strRet.IsEmpty())
		return TRUE;
	//
	strRet = lpszSrc;
	return FALSE;
}
CString CWizTranslationsStringTable::TranslateString(LPCTSTR lpszSrc)
{
	CString strRet;
	if (TranslateString(lpszSrc, strRet))
		return strRet;
	//
	return CString(lpszSrc);
}

BOOL CWizTranslationsStringTable::LoadString(UINT nStringID, CString& strRet)
{
	CString str;
	if (!str.LoadString(nStringID))
		return FALSE;
	//
	TranslateString(str, strRet);
	//
	return TRUE;
}
CString CWizTranslationsStringTable::LoadString(UINT nStringID)
{
	CString strRet;
	//
	LoadString(nStringID, strRet);
	//
	return strRet;
}
BOOL CWizTranslationsStringTable::TranslateMenu(HMENU hMenu)
{
	TCHAR szMenuItem[MAX_PATH] = {0};
	//
	int nMenuItemCount = GetMenuItemCount(hMenu);
	for (int i = 0; i < nMenuItemCount; i++)
	{
		*szMenuItem = 0;
		//
#ifdef WINCE
		MENUITEMINFO miOld;
		ZeroMemory(&miOld, sizeof(MENUITEMINFO));
		miOld.cbSize = sizeof(MENUITEMINFO);
		miOld.fMask = MIIM_TYPE;
		miOld.dwTypeData = szMenuItem;
		miOld.cch = MAX_PATH;
		//
		if (GetMenuItemInfo(hMenu, i, TRUE, &miOld) 
			&& miOld.fType == MFT_STRING 
			&& *szMenuItem)
#else
		//
		if (GetMenuString(hMenu, i, szMenuItem, MAX_PATH, MF_BYPOSITION) && *szMenuItem)
#endif
		{
			CString strNewMenuItemText;
			if (TranslateString(szMenuItem, strNewMenuItemText))
			{
				_tcscpy_s(szMenuItem, MAX_PATH, strNewMenuItemText);
				//
				MENUITEMINFO mi;
				ZeroMemory(&mi, sizeof(MENUITEMINFO));
				//
				mi.cbSize = sizeof(MENUITEMINFO);
#ifdef WINCE
				mi.fMask = MIIM_TYPE;
				mi.fType = MFT_STRING;
#else
#ifndef MIIM_STRING
#define MIIM_STRING      0x00000040
#endif
				mi.fMask = MIIM_STRING;
#endif
				mi.dwTypeData = szMenuItem;
				mi.cch = MAX_PATH;
				//
				SetMenuItemInfo(hMenu, i, TRUE, &mi);
			}
		}
		//
		if (HMENU hSubMenu = GetSubMenu(hMenu, i))
		{
			TranslateMenu(hSubMenu);
		}
	}
	//
	return TRUE;
}
BOOL CALLBACK CWizTranslationsStringTable::TranslateWindowEnumChildProc(HWND hwnd, LPARAM lParam)
{
	CWizTranslationsStringTable* pThis = (CWizTranslationsStringTable*)lParam;
	//
	if (!pThis)
		return FALSE;
	//
	pThis->TranslateWindow(hwnd);
	//
	return TRUE;
}

BOOL CWizTranslationsStringTable::TranslateWindowText(HWND hWnd)
{
	TCHAR szText[1024] = {0};
	if (GetWindowText(hWnd, szText, 1024) > 0)
	{
		CString strNewText;
		if (TranslateString(szText, strNewText))
		{
			SetWindowText(hWnd, strNewText);
			return TRUE;
		}
	}
	//
	return FALSE;
}

BOOL CWizTranslationsStringTable::TranslateWindow(HWND hWnd)
{
	TCHAR szClassName[MAX_PATH] = {0};
	::GetClassName(hWnd, szClassName, MAX_PATH);
	//
	if (0 != _tcsicmp(szClassName, _T("Edit"))
		&& 0 != _tcsicmp(szClassName, _T("ComboBox")))
	{
		TranslateWindowText(hWnd);
	}
	//
	EnumChildWindows(hWnd, TranslateWindowEnumChildProc, (LPARAM)this);
	//
	return TRUE;
}
BOOL CWizTranslationsStringTable::TranslatePropertySheet(HWND hWnd)
{
	TranslateWindow(hWnd);
	//
	HWND hwndPropertySheet = hWnd;
	if (!hwndPropertySheet)
		return FALSE;
	//
	HWND hwndTabCtrl = (HWND)SendMessage(hwndPropertySheet, PSM_GETTABCONTROL, 0, 0);
	if (!hwndTabCtrl)
		return FALSE;
	//
	if (!IsWindow(hwndTabCtrl))
		return FALSE;
	//
	TCHAR szText[MAX_PATH] = {0};
	//
	int nTabCount = (int)SendMessage(hwndTabCtrl, TCM_GETITEMCOUNT, 0, 0);
	for (int i = 0; i < nTabCount; i++)
	{
		TCITEM item;
		ZeroMemory(&item, sizeof(TCITEM));
		//
		szText[0] = '\0';
		//
		item.mask = TCIF_TEXT;
		item.pszText = szText;
		item.cchTextMax = MAX_PATH;
		//
		if (SendMessage(hwndTabCtrl, TCM_GETITEM, (WPARAM)i, (LPARAM)&item))
		{
			CString strNewText;
			if (TranslateString(szText, strNewText) && !strNewText.IsEmpty())
			{
				_tcscpy_s(item.pszText, MAX_PATH, strNewText);
				SendMessage(hwndTabCtrl, TCM_SETITEM, (WPARAM)i, (LPARAM)&item);
			}
		}
	}
	//
	TranslateWindowText(hwndPropertySheet);
	//
	return TRUE;
}



CWizURL::CWizURL()
{
}
CWizURL::CWizURL(LPCTSTR lpszURL, UINT nCodePage /*= 0*/, BOOL bUnescape /*= TRUE*/)
{
	CString strTempURL(lpszURL);
	if (strTempURL.IsEmpty())
		return;
	//
	if (bUnescape)
	{
		WizURLUnescapeAnsiChar(strTempURL);
	}
	//
	if (UrlIsFileUrl(strTempURL))
	{
		DWORD dwLen = 1024;
		TCHAR szPath[1024] = {0};
		PathCreateFromUrl(strTempURL, szPath, &dwLen, 0);
		//
		m_strURL = szPath;
		WizURLUnescapeAnsiChar(m_strURL);
		//
		return;
	}
	else if (strTempURL.GetLength() >= 2 && strTempURL[1] == ':')
	{
		TCHAR szURL[4096] = {0};
		DWORD dwLen = 4096;
		//
		UrlCanonicalize(strTempURL, szURL, &dwLen, 0);
		//
		UrlUnescape(szURL, NULL, &dwLen, URL_UNESCAPE_INPLACE);
		//
		dwLen = 1024;
		TCHAR szPath[1024] = {0};
		PathCreateFromUrl(szURL, szPath, &dwLen, 0);
		//
		m_strURL = szPath;
		//
		return;
	}
	else if (strTempURL.GetLength() >= 2 && strTempURL[0] == '/' && strTempURL[1] == '/')
	{
		strTempURL.Insert(0, _T("http:"));
	}
	//
	//
	/*
	线进行简单的解码
	*/
	//
	//
	//
	//
	if (NULL == _tcschr(strTempURL, '%'))
	{
		TCHAR szURL[4096] = {0};
		DWORD dwLen = 4096;
		//
		UrlCanonicalize(strTempURL, szURL, &dwLen, 0);
		//
		UrlUnescape(szURL, NULL, &dwLen, URL_UNESCAPE_INPLACE);
		//
		m_strURL = szURL;
	}
	else
	{
		//
		/*
		//仍然包含%，需要解码，可能是中文字符等等
		//
		//转换为Ansi，然后解码，然后重新转换成unicode
		*/
		//
		char szURL[4096] = {0};
		DWORD dwLen = 4096;
		//
		CStringA strURLA = WizBSTR2STR(GetACP(), strTempURL);
		//
		UrlCanonicalizeA(strURLA, szURL, &dwLen, 0);
		//
		if (bUnescape)
		{
			UrlUnescapeA(szURL, NULL, &dwLen, URL_UNESCAPE_INPLACE);
		}
		//
		if (1200 == nCodePage)
		{
			//utf16
			nCodePage = 0;
		}
		if (0 == nCodePage)
		{
			nCodePage = WizAutoDetectTextCodePage(szURL);
		}
		//
		WCHAR szURLW[4096] = {0};
		//
		MultiByteToWideChar(nCodePage, 0, szURL, -1, szURLW, 4096);
		//
		m_strURL = CString(szURLW);
	}
	//
	//
	if (IsFileURL())
	{
		m_strURL = GetFileNameInURL();
	}
}
CWizURL::CWizURL(const CWizURL& url)
{
	m_strURL = url.m_strURL;
}
void CWizURL::WizURLUnescapeAnsiChar(CString& strURL)
{
	if (-1 == strURL.Find('%'))
		return;
	//
	const UINT nCount = 14;
	LPCTSTR arrayText [nCount * 2] = {
		_T("^"),	_T("%5E"),
		_T("&"),	_T("%26"),
		_T("`"),	_T("%60"),
		_T("{"),	_T("%7B"),
		_T("}"),	_T("%7D"),
		_T("|"),	_T("%7C"),
		_T("]"),	_T("%5D"),
		_T("["),	_T("%5B"),
		_T("\""),	_T("%22"),
		_T("<"),	_T("%3C"),
		_T(">"),	_T("%3E"),
		_T("\\"),	_T("%5C"),
		_T("%"),	_T("%25"),
		_T(" "),	_T("%20"),
	};
	//
	for (int i = 0; i < nCount; i++)
	{
		strURL.Replace(arrayText[i * 2 + 1], arrayText[i * 2]);
	}
}
//
CString CWizURL::ToFileNameInternal(BOOL bDownload)
{
	if (IsFileURL() || IsFileName())
		return GetFileNameInURL();
	//
	CString strURL(m_strURL);
	if (_tcsnicmp(strURL, _T("http:"), 5) == 0 && _tcsncmp(strURL, _T("http:"), 5) != 0)
	{
		strURL.Delete(0, 4);
		strURL.Insert(0, _T("http"));
	}
	//
	CString strFileName;
	//
	strURL.Replace(_T('\\'), _T('/'));
	//
	DWORD dwEntrySize = 1024 * 8;
	TCHAR szBuffer[1024 * 8] = {0};
	ZeroMemory(szBuffer, 1024 * 8 * sizeof(TCHAR));
	//
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)szBuffer;
	//
	if (GetUrlCacheEntryInfo(CWizURL::DeleteBookmark(strURL), lpCacheEntry, &dwEntrySize))
	{
		if (lpCacheEntry->lpszLocalFileName)
		{
			strFileName = lpCacheEntry->lpszLocalFileName;
		}
	}
	//
	if (strFileName.IsEmpty() || !PathFileExists(strFileName))
	{
		if (bDownload)
		{
			int nIndex = 0;
			while (1)
			{
				if (DownloadToTemp(strFileName))
					break;
				nIndex++;
				//
				//if (nIndex > 3)
				//{
					//TOLOG(CString(_T("Failed to download: ")) + m_strURL);
					return CString();
				//}
			}
		}
	}
	//
	if (PathFileExists(strFileName) && strFileName.Find(_T('%')) != -1)
	{
		CString strOldFileName = strFileName;
		strFileName = WizGlobal()->GetTempPath() + Unescape(WizExtractFileName(strOldFileName));
		CopyFile(strOldFileName, strFileName, FALSE);
	}
	//
	return strFileName;
}

CWizURL& CWizURL::operator =(const CWizURL& urlSrc)
{
	m_strURL = urlSrc.m_strURL;
	m_strRedirectedURL.Empty();
	//
	return( *this );
}
CWizURL::operator LPCTSTR () const
{
	return m_strURL;
}
void CWizURL::SetURLIndirect(LPCTSTR lpszURL)
{
	m_strURL = lpszURL;
	m_strRedirectedURL.Empty();
}
BOOL CWizURL::URLHasPercent(LPCTSTR lpszURL)
{
	return NULL != _tcschr(lpszURL, '%');
}
//
CString CWizURL::GetRedirectedURL() const
{
	return m_strRedirectedURL;
}
//
BOOL CWizURL::Combine(const CWizURL& urlRelative)
{
	if (WizGlobal()->IsWizResourceURL(urlRelative.m_strURL))	//CYBERARTICLE_RESOURCEFILE_PATH: _T("%ResourceFilePath%/")
	{
		m_strURL = urlRelative.m_strURL;
		return TRUE;
	}
	//
	//如果是文件名，直接获得文件名
	//
	if (urlRelative.IsFileURL())
	{
		m_strURL = urlRelative;
		return TRUE;
	}
	//
	CString strRelativeURL = (LPCTSTR)urlRelative;
	while (strRelativeURL.GetLength() >= 2
		&& strRelativeURL[0] == '/'
		&& strRelativeURL[1] == '/')
	{
		strRelativeURL.Delete(0, 1);
	}
	//
	TCHAR szCombined[4096] = {0};
	DWORD dwLen = 4096;
	if (FAILED(UrlCombine(m_strURL, strRelativeURL, szCombined, &dwLen, 0)))
		return FALSE;
	m_strURL = CWizURL(szCombined);
	return TRUE;
}
CWizURL CWizURL::GetBase() const
{
	if (IsFileURL() || IsFileName())
	{
		return CWizURL(WizExtractFilePath(GetFileNameInURL()));
	}
	else
	{
		TCHAR szURL[4096] = {0};
		_tcscpy_s(szURL, 4096, m_strURL);
		//
		LPTSTR lpszParamBegin = StrChr(szURL, _T('?'));
		if (lpszParamBegin)
		{
			*lpszParamBegin = _T('\0');
		}
		LPTSTR lpszBookmarkBegin = StrChr(szURL, _T('#'));
		if (lpszBookmarkBegin)
		{
			*lpszBookmarkBegin = _T('\0');
		}
		//
		LPTSTR lpszEnd = StrRChr(szURL, NULL, _T('/'));
		if (lpszEnd)
		{
			*(lpszEnd + 1) = _T('\0');
			return CWizURL(szURL);
		}
		else
		{
			return CWizURL(szURL);
		}
	}
}
BOOL CWizURL::IsFileURL() const
{
	return UrlIsFileUrl(m_strURL) || IsFileName();
}
BOOL CWizURL::IsFileName() const
{
	if (m_strURL.GetLength() < 2)
		return FALSE;
	return m_strURL[1] == _T(':');
}
CString CWizURL::GetFileNameInURL() const
{
	CString strFileName;
	if (IsFileName())
	{
		strFileName = m_strURL;
	}
	else
	{
		LPCTSTR lpszURL = m_strURL;
		if (_tcsnicmp(lpszURL, _T("file:"), 5) != 0)
			return strFileName;
		//
		DWORD dwLen = 1024;
		TCHAR szPath[1024] = {0};
		PathCreateFromUrl(m_strURL, szPath, &dwLen, 0);
		//
		strFileName = szPath;
	}
	strFileName.Replace(_T('/'), _T('\\'));
	//
	int nPos = strFileName.FindOneOf(_T("#?"));
	if (nPos != -1)
	{
		strFileName = strFileName.Left(nPos);
	}
	//
	return strFileName;
}

//
BOOL WizIsAlpha(TCHAR ch)
{
	if (ch == '.')
		return TRUE;
	if (ch == '-')
		return TRUE;
	if (ch == '_')
		return TRUE;
	if (ch == '@')
		return TRUE;
	if (ch == '(')
		return TRUE;
	if (ch == ')')
		return TRUE;
	if (ch == '[')
		return TRUE;
	if (ch == ']')
		return TRUE;
	if (ch == '{')
		return TRUE;
	if (ch == '}')
		return TRUE;
	if (ch >= 'a' && ch <= 'z')
		return TRUE;
	if (ch >= 'A' && ch <= 'Z')
		return TRUE;
	if (ch >= '0' && ch <= '9')
		return TRUE;
	//
	return FALSE;
}
BOOL WizIsAlphaOnly(const CString& str)
{
	for (int i = 0; i < str.GetLength(); i++)
	{
		if (!WizIsAlpha(str[i]))
			return FALSE;
	}
	//
	return TRUE;
}

//
CString CWizURL::ToFileName(BOOL bDownload)
{
	CString strFileName = ToFileNameInternal(bDownload);
	if (strFileName.IsEmpty())
		return strFileName;
	//
	if (!PathFileExists(strFileName))
		return CString();
	//
	CString strOldTitle = WizExtractFileTitle(strFileName);
	CString strNewTitle = strOldTitle;
	//
	strNewTitle.Replace('%', '_');
	//
	if (strNewTitle.GetLength() > 50
		|| !WizIsAlphaOnly(strNewTitle))
	{
		strNewTitle = WizPasswordToMd5StringNoSpace(strNewTitle);
	}
	WizMakeValidFileNameNoPath(strNewTitle);
	//
	if (strNewTitle != strOldTitle)
	{
		CString strNewFileName = WizGlobal()->GetTempPath() + strNewTitle + WizExtractFileExt(strFileName);
		//
		strNewFileName = WizCompareCopyFile(strFileName, strNewFileName);
		//
		return strNewFileName;
	}
	//
	return strFileName;
}
//
BOOL CWizURL::ToFileName(CString& strFileName, BOOL bDownload)
{
	strFileName = ToFileName(bDownload);
	return !strFileName.IsEmpty() && PathFileExists(strFileName);
}
//
BOOL CWizURL::DownloadToFile(LPCTSTR lpszFileName)
{
	if (PathFileExists(lpszFileName))
	{
		if (!DeleteFile(lpszFileName))
			return FALSE;
	}
	//
	HRESULT hr = URLDownloadToFile(NULL, m_strURL, lpszFileName, 0, NULL);
	return SUCCEEDED(hr) && PathFileExists(lpszFileName);
}

BOOL CWizURL::DownloadToTemp(CString& strFileName)
{
	m_strRedirectedURL.Empty();
	//
	TCHAR szCacheFileName[MAX_PATH] = {0};
	if (FAILED(URLDownloadToCacheFile(NULL, m_strURL, szCacheFileName, MAX_PATH, 0, this)))
		return FALSE;
	//
	strFileName = WizGlobal()->GetTempPath() + WizExtractFileName(szCacheFileName);
	//
	if (PathFileExists(szCacheFileName))
	{
		strFileName = WizCompareCopyFile(szCacheFileName, strFileName);
		//
		return TRUE;
	}
	//
	WizGetNextFileName(strFileName);
	//
	return SUCCEEDED(URLDownloadToFile(NULL, m_strURL, strFileName, 0, this));
}
//
CString CWizURL::Unescape(LPCTSTR lpszText) 
{
	TCHAR szText[4096] = {0};
	_tcscpy_s(szText, 4096, lpszText);
	//
	DWORD dwLen = 4096;
	UrlUnescape(szText, NULL, &dwLen, URL_UNESCAPE_INPLACE);
	//
	return CString(szText);
}
//
BOOL CWizURL::GetNameOfURL(CString& strName) const
{
	if (IsFileName())
	{
		strName = WizExtractFileName(GetFileNameInURL());
		if (!strName.IsEmpty())
		{
			return TRUE;
		}
	}
	//
	TCHAR szURL[4096] = {0};
	_tcscpy_s(szURL, 4096, m_strURL);
	//
	LPTSTR lpszParamBegin = StrChr(szURL, _T('?'));
	if (lpszParamBegin)
	{
		*lpszParamBegin = _T('\0');
	}
	LPTSTR lpszBookmarkBegin = StrChr(szURL, _T('#'));
	if (lpszBookmarkBegin)
	{
		*lpszBookmarkBegin = _T('\0');
	}
	//
	if (0 == _tcsnicmp(szURL, _T("ca://"), 5))
	{
		if (0 == _tcsnicmp(szURL, _T("ca://article/?"), 14))
		{
			return FALSE;
		}
		//
		StrTrim(szURL, _T("/"));
	}
	//
	BOOL bRet = FALSE;
	//
	LPTSTR lpszEnd = StrRChr(szURL, NULL, _T('/'));
	if (lpszEnd)
	{
		lpszEnd++;
		//
		if (_tcslen(lpszEnd) > 0)
		{
			strName = lpszEnd;
			bRet = TRUE;
		}
	}
	else
	{
		strName = szURL;
		bRet = TRUE;
	}
	//
	WizMakeValidFileNameNoPath(strName);
	//
	if (WizExtractFileTitle(strName).GetLength() > 50)
	{
		strName = WizPasswordToMd5StringNoSpace(strName) + WizExtractFileExt(strName);
	}
	//
	return bRet;
}
CString CWizURL::GetHostName() const
{
	TCHAR szPart[MAX_PATH] = {0};
	DWORD dwLen = MAX_PATH;
	UrlGetPart(m_strURL, szPart, &dwLen, URL_PART_HOSTNAME, 0);
	//
	return CString(szPart);
}
CString CWizURL::GetQueryString() const
{
	TCHAR szPart[4096] = {0};
	DWORD dwLen = 4096;
	UrlGetPart(m_strURL, szPart, &dwLen, URL_PART_QUERY, 0);
	//
	return CString(szPart);
}
CString CWizURL::GetPathString() const
{
	int nHostBegin = m_strURL.Find(_T("://"));
	if (-1 == nHostBegin)
		nHostBegin = 0;
	else
		nHostBegin += 3;
	//
	int nBegin = m_strURL.Find(_T("/"), nHostBegin);
	if (-1 == nBegin)
		nBegin = 0;
	else
		nBegin++;
	//
	int nEnd = m_strURL.FindOneOf(_T("?#"));
	if (-1 == nEnd)
		nEnd = m_strURL.GetLength();
	if (nEnd < nBegin)
		return CString();
	//
	return m_strURL.Mid(nBegin, nEnd - nBegin);
}


CString CWizURL::GetFileExt() const
{
	CString strName;
	GetNameOfURL(strName);
	//
	return WizExtractFileExt(strName);
}
BOOL CWizURL::GetURLParamString(CString& strParamsPart) const
{
	int nPos = m_strURL.Find('?');
	if (-1 == nPos)
	{
		strParamsPart.Empty();
	}
	else
	{
		strParamsPart = m_strURL.Right(m_strURL.GetLength() - nPos - 1);
	}
	//
	strParamsPart = DeleteBookmark(strParamsPart);
	//
	return TRUE;
}

BOOL CWizURL::GetAllFileExt(CWizStdStringArray& arrayExts) const
{
	CString strParamsPart;
	//
	GetURLParamString(strParamsPart);
	//
	CWizStdStringArray arrayText;
	WizSplitTextToArray(strParamsPart, '&', arrayText);
	//
	CString strExt = GetFileExt();
	if (!strExt.IsEmpty())
	{
		arrayExts.push_back(strExt);
	}
	//
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strLine = arrayText[i];
		strLine.Replace(':', '_');
		strLine.Replace('/', '_');
		strLine.Replace('\\', '_');
		strLine.Replace('=', '_');
		strLine.Replace('&', '_');
		//
		strExt = WizExtractFileExt(strLine);
		//
		if (!strExt.IsEmpty())
		{
			if (-1 == WizFindInArrayNoCase(arrayExts, strExt))
			{
				arrayExts.push_back(strExt);
			}
		}
	}
	//
	return TRUE;
}
BOOL CWizURL::ContainExt(const CWizStdStringArray& arrayExts) const
{
	CWizStdStringArray arrayExtSelf;
	if (!GetAllFileExt(arrayExtSelf))
		return FALSE;
	//
	size_t nCount = arrayExtSelf.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (-1 != WizFindInArrayNoCase(arrayExts, arrayExtSelf[i]))
			return TRUE;
	}
	//
	return FALSE;
}
BOOL CWizURL::Equal(LPCTSTR lpszURL)
{
	return Equal(CWizURL(lpszURL));
}
BOOL CWizURL::Equal(const CWizURL& url)
{
	if (IsFileURL() && url.IsFileURL())
	{
		CString strFileName1 = WizGetLongFileName(GetFileNameInURL());
		CString strFileName2 = WizGetLongFileName(url.GetFileNameInURL());
		return 0 == strFileName1.CompareNoCase(strFileName2);
	}
	return 0 == url.m_strURL.CompareNoCase(m_strURL);
}
CString CWizURL::DeleteBookmark(LPCTSTR lpszURL)
{
	CString strURL(lpszURL);
	int nPos = strURL.Find(_T('#'));
	if (-1 != nPos)
	{
		strURL.Delete(nPos, strURL.GetLength() - nPos);
	}
	//
	return strURL;
}
CString CWizURL::GetBookmark(LPCTSTR lpszURL)
{
	LPCTSTR lpszBookmark = _tcschr(lpszURL, '#');
	if (!lpszBookmark)
		return CString();
	//
	return CString(lpszBookmark + 1);
}
STDMETHODIMP CWizURL::OnStartBinding(DWORD dwReserved, IBinding __RPC_FAR *pib)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizURL::GetPriority(LONG __RPC_FAR *pnPriority)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizURL::OnLowResource(DWORD reserved)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizURL::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText)
{
	if (BINDSTATUS_REDIRECTING == ulStatusCode)
	{
		m_strRedirectedURL = CString(wszStatusText);
	}
	//
	WizGlobal()->OnURLDownloadToFileProgress(ulProgress, ulProgressMax, wszStatusText);
	return S_OK;
}
STDMETHODIMP CWizURL::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
	return E_NOTIMPL; 
}

STDMETHODIMP CWizURL::GetBindInfo(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizURL::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizURL::OnObjectAvailable(REFIID riid, IUnknown __RPC_FAR *punk)
{
	return E_NOTIMPL;
}

ULONG STDMETHODCALLTYPE CWizURL::AddRef( void)
{
	return 1;
}

ULONG STDMETHODCALLTYPE CWizURL::Release( void)
{
	return 1;
}

STDMETHODIMP CWizURL::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)
{
	return E_NOTIMPL;
}


CWizFileSystemStream::CWizFileSystemStream()
{
	m_nRef			= 1;
	m_hFile			= NULL;
	m_szFileName[0] = 0;
}
CWizFileSystemStream::~CWizFileSystemStream()
{
	if (m_hFile)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}
}
void CWizFileSystemStream::Grf2Sam(DWORD grfMode, DWORD& dwDesiredAccess, DWORD& dwShareMode, BOOL& bCreate)
{
	dwDesiredAccess = GENERIC_READ;

	bCreate = FALSE;

	if ((grfMode & STGM_WRITE) == STGM_WRITE)
	   dwDesiredAccess = GENERIC_WRITE;
	else if	((grfMode & STGM_READWRITE) == STGM_READWRITE)
	   dwDesiredAccess = GENERIC_READ|GENERIC_WRITE;

	if (grfMode & STGM_CREATE)
		bCreate = TRUE;

	dwShareMode = 0;

	if ((grfMode & STGM_SHARE_DENY_NONE) == STGM_SHARE_DENY_NONE)
		dwShareMode = FILE_SHARE_READ|FILE_SHARE_WRITE;
	if ((grfMode & STGM_SHARE_DENY_READ) == STGM_SHARE_DENY_READ)
		dwShareMode = FILE_SHARE_WRITE;
	if ((grfMode & STGM_SHARE_DENY_WRITE)== STGM_SHARE_DENY_WRITE)
		dwShareMode = FILE_SHARE_READ;
	if ((grfMode & STGM_SHARE_EXCLUSIVE) == STGM_SHARE_EXCLUSIVE)
		dwShareMode = 0;

}
HRESULT CWizFileSystemStream::CreateFileSystemStream(LPCTSTR lpszFileName, DWORD grfMode, IStream** ppStream)
{
	BOOL		bCreate = FALSE;
	DWORD		dwDesiredAccess = 0;
	DWORD		dwShareMode = 0;

	Grf2Sam(grfMode, dwDesiredAccess, dwShareMode, bCreate);

    if (bCreate && PathFileExists(lpszFileName))
        bCreate = FALSE;

	HANDLE hFile = CreateFile(lpszFileName, dwDesiredAccess, dwShareMode, NULL,
										bCreate ? CREATE_ALWAYS : OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	CWizFileSystemStream* pStream = new CWizFileSystemStream();
	pStream->m_hFile = hFile;
	_tcscpy_s(pStream->m_szFileName, 1024, lpszFileName);

	//
	*ppStream = pStream;

	return S_OK;
}
// IStream interface implementation.
STDMETHODIMP_(ULONG)	CWizFileSystemStream::AddRef(void)
{
	return ++m_nRef;
}
STDMETHODIMP_(ULONG)	CWizFileSystemStream::Release(void)
{ 
	--m_nRef;

	if (m_nRef == 0)
	{
		delete this;
		return 0;
	}
	return m_nRef;
}
STDMETHODIMP CWizFileSystemStream::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown)			 
		*ppv = this;
	if (riid == IID_ISequentialStream) 
		*ppv = this;
	if (riid == IID_IStream)			 
		*ppv = this;

	if (*ppv)
	{
		AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP CWizFileSystemStream::Read(
		/* [out] */ void __RPC_FAR *pv,
		/* [in] */ ULONG cb,
		/* [out] */ ULONG __RPC_FAR *pcbRead)
{
	if (pcbRead) 
		*pcbRead = 0;
	if (!pv) 
		return STG_E_INVALIDPOINTER;
	if (0 == cb) 
		return S_OK; 

	DWORD	dwRead	= 0;

	if (!ReadFile(m_hFile, pv, cb, &dwRead, NULL))
		return E_FAIL;

	if (pcbRead)
	{
		*pcbRead = dwRead;
	}

	return S_OK;
}
STDMETHODIMP CWizFileSystemStream::Write(
		/* [in] */ const void __RPC_FAR *pv,
		/* [in] */ ULONG cb,
		/* [out] */ ULONG __RPC_FAR *pcbWritten)
{
	if (!pv) 
		return STG_E_INVALIDPOINTER;
	if (pcbWritten) 
		*pcbWritten = 0;
	if (0 == cb) 
		return S_OK;

	DWORD	dwWritten	= 0;

	if (!WriteFile(m_hFile, pv, cb, &dwWritten, NULL))
		return E_FAIL;

	if (pcbWritten) 
		*pcbWritten = dwWritten;

	return S_OK;
}

STDMETHODIMP CWizFileSystemStream::Seek(
		/* [in] */ LARGE_INTEGER dlibMove,
		/* [in] */ DWORD dwOrigin,
		/* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition) 
{
	LONG lMove = dlibMove.u.LowPart;
	LONG lNewPos = 0;

	switch (dwOrigin)
	{
	case STREAM_SEEK_SET:
		lNewPos = SetFilePointer(m_hFile, lMove, NULL, FILE_BEGIN);
		break;
	case STREAM_SEEK_CUR:
		lNewPos = SetFilePointer(m_hFile, lMove, NULL, FILE_CURRENT);
		break;
	case STREAM_SEEK_END:
		lNewPos = SetFilePointer(m_hFile, lMove, NULL, FILE_END);
		break;
	}

	if (plibNewPosition)
	{
		plibNewPosition->QuadPart = lNewPos;
	}

	return S_OK;
}

STDMETHODIMP CWizFileSystemStream::SetSize(
	/* [in] */ ULARGE_INTEGER libNewSize)
{ 
	if (!m_hFile)
		return E_FAIL;

	if (((DWORD)-1) == SetFilePointer(m_hFile, int(libNewSize.QuadPart), NULL, FILE_BEGIN))
		return E_FAIL;

	if (!SetEndOfFile((HANDLE)m_hFile))
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CWizFileSystemStream::CopyTo(
	/* [unique][in] */ IStream __RPC_FAR *pstm,
	/* [in] */ ULARGE_INTEGER cb,
	/* [out] */ ULARGE_INTEGER __RPC_FAR *pcbRead,
	/* [out] */ ULARGE_INTEGER __RPC_FAR *pcbWritten)
{
	if (!m_hFile)
		return E_FAIL;
	if (!pstm) 
		return STG_E_INVALIDPOINTER;

	int nSize = int(cb.QuadPart);
	char szBuffer[1024];
	int nCount = nSize / 1024;
	int nLeft = nSize - nCount * 1024;
	DWORD dwReadCount = 0;
	DWORD dwWrittenCount = 0;
	//
	for (int i = 0; i < nCount; i++)
	{
		DWORD dwRead = 0;
		DWORD dwWritten = 0;
		Read(szBuffer, 1024, &dwRead);
		dwReadCount += dwRead;
		pstm->Write(szBuffer, dwRead, &dwWritten);
		dwWrittenCount += dwWritten;
	}
	if (nLeft > 0)
	{
		DWORD dwRead = 0;
		DWORD dwWritten = 0;
		Read(szBuffer, nLeft, &dwRead);
		dwReadCount += dwRead;
		pstm->Write(szBuffer, dwRead, &dwWritten);
		dwWrittenCount += dwWritten;
	}
	if (pcbRead)
	{
		pcbRead->QuadPart = dwReadCount;
	}
	if (pcbWritten)
	{
		pcbWritten->QuadPart = dwWrittenCount;
	}
	return S_OK;
}

STDMETHODIMP CWizFileSystemStream::Commit(
	/* [in] */ DWORD grfCommitFlags)
{
	return FlushFileBuffers(m_hFile) ? S_OK : E_FAIL;
}

STDMETHODIMP CWizFileSystemStream::Revert(void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizFileSystemStream::LockRegion(
	/* [in] */ ULARGE_INTEGER libOffset,
	/* [in] */ ULARGE_INTEGER cb,
	/* [in] */ DWORD dwLockType)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizFileSystemStream::UnlockRegion(
	/* [in] */ ULARGE_INTEGER libOffset,
	/* [in] */ ULARGE_INTEGER cb,
	/* [in] */ DWORD dwLockType)
{
	return E_NOTIMPL;
}

STDMETHODIMP CWizFileSystemStream::Stat(
	/* [out] */ STATSTG __RPC_FAR *pstatstg,
	/* [in] */ DWORD grfStatFlag)
{
	if (!pstatstg)
		return STG_E_INVALIDPOINTER;

	memset(pstatstg, 0, sizeof(STATSTG));
	//
	GetFileTime(m_hFile, &pstatstg->ctime, &pstatstg->atime, &pstatstg->mtime);
	pstatstg->cbSize.QuadPart = GetFileSize(m_hFile, NULL);
	pstatstg->clsid = CLSID_NULL;
	pstatstg->grfLocksSupported = 0;
	pstatstg->grfMode = 0;
	pstatstg->grfStateBits = 0;
	pstatstg->reserved = 0;
	pstatstg->type = STGTY_STREAM;
	if (!(STATFLAG_NONAME & grfStatFlag))
	{
		TCHAR szName[MAX_PATH];
		TCHAR szExt[MAX_PATH];
		_tsplitpath_s(m_szFileName, NULL, 0, NULL, 0, szName, MAX_PATH, szExt, MAX_PATH);
		_tcscat_s(szName, MAX_PATH, szExt);

		wchar_t* p = (wchar_t *)CoTaskMemAlloc(MAX_PATH * sizeof(wchar_t));
		*p = 0;
#ifdef UNICODE
		wcscpy_s(p, MAX_PATH, szName);
#else
		MultiByteToWideChar(CP_ACP, 0, szName, -1, p, MAX_PATH);
#endif
		pstatstg->pwcsName = p;
	}

	return S_OK;
}

STDMETHODIMP CWizFileSystemStream::Clone(
	/* [out] */ IStream __RPC_FAR *__RPC_FAR *ppstm)
{
	return E_NOTIMPL;
}




__int64 WizStreamGetCurPos(IStream* pStream)
{
	__int64 nPos = 0;
	ULARGE_INTEGER	liRet;
	LARGE_INTEGER	li;
	memset(&li, 0, sizeof(LARGE_INTEGER));
	if (pStream->Seek(li, STREAM_SEEK_CUR, &liRet) == S_OK)
	{
		nPos = liRet.QuadPart;
	}
	return nPos;
}
__int64 WizStreamGetSize(IStream* pStream)
{
	__int64 nLen = 0;
	LARGE_INTEGER	cur;
	LARGE_INTEGER	zero;
	memset(&zero, 0, sizeof(LARGE_INTEGER));
	if (pStream->Seek(zero, STREAM_SEEK_CUR, (ULARGE_INTEGER*)&cur) == S_OK)
	{
		ULARGE_INTEGER	result;
		if (pStream->Seek(zero, STREAM_SEEK_END, &result) == S_OK)
		{
			nLen = result.QuadPart;
			pStream->Seek(cur, STREAM_SEEK_SET, NULL);
		}
	}
	return nLen;
}

void WizStreamSeekToBegin(IStream* pStream)
{
	LARGE_INTEGER size;
	memset(&size, 0, sizeof(LARGE_INTEGER));
	pStream->Seek(size, STREAM_SEEK_SET, NULL);
}


void WizStreamSetSize(IStream* pStream, __int64 nSize)
{
	ULARGE_INTEGER	size;
	memset(&size, 0, sizeof(ULARGE_INTEGER));
	size.QuadPart = nSize;
	pStream->SetSize(size);
}

BOOL WizStreamRead(IStream* pStream, void* pBuffer, ULONG nNeedRead)
{
	if (0 == nNeedRead)
		return TRUE;
	ULONG nRead = 0;
	HRESULT hr = pStream->Read(pBuffer, nNeedRead, &nRead);
	if (FAILED(hr))
		return FALSE;
	if (nRead != nNeedRead)
		return FALSE;
	return TRUE;
}
BOOL WizStreamWrite(IStream* pStream, const void* pBuffer, ULONG nNeedWrite)
{
	if (0 == nNeedWrite)
		return TRUE;
	ULONG nWritten = 0;
	HRESULT hr = pStream->Write(pBuffer, nNeedWrite, &nWritten);
	if (FAILED(hr))
		return FALSE;
	if (nWritten != nNeedWrite)
		return FALSE;
	return TRUE;
}

BOOL WizStreamAppendToStream(IStream* pFrom, IStream* pTo)
{
	WizStreamSeekToBegin(pFrom);

	ULONG nSize = ULONG(WizStreamGetSize(pFrom));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	if (WizStreamRead(pFrom, pBuffer, nSize))
	{
		bRet = WizStreamWrite(pTo, pBuffer, nSize);
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}

#ifdef WINCE
BOOL WizStreamLoadFromFile(LPCTSTR lpszFileName, IStream* pStream)
{
	WizStreamSeekToBegin(pStream);
	WizStreamSetSize(pStream, 0);
	//
	ULONG nSize = ULONG(WizGetFileSize(lpszFileName));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	if (FILE* fp = _tfopen(lpszFileName, _T("rb")))
	{
		fread(pBuffer, nSize, 1, fp);
		bRet = WizStreamWrite(pStream, pBuffer, nSize);
		//
		// After _fdopen, close with fclose, not _close.
		fclose(fp);
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}
#else
BOOL WizStreamLoadFromFile(LPCTSTR lpszFileName, IStream* pStream)
{
	WizStreamSeekToBegin(pStream);
	WizStreamSetSize(pStream, 0);
	//
	ULONG nSize = ULONG(WizGetFileSize(lpszFileName));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	int  fd = 0;
	if(0 == _tsopen_s(&fd, lpszFileName, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0))
	{
		if (FILE* fp = _tfdopen(fd, _T("rb")))
		{
			fread(pBuffer, nSize, 1, fp);
			bRet = WizStreamWrite(pStream, pBuffer, nSize);
			//
			// After _fdopen, close with fclose, not _close.
			fclose(fp);
		}
		else
		{
			_close(fd);
		}
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}
#endif
BOOL WizStreamSaveToFile(IStream* pStream, LPCTSTR lpszFileName)
{
	WizStreamSeekToBegin(pStream);
	//
	ULONG nSize = ULONG(WizStreamGetSize(pStream));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	if (WizStreamRead(pStream, pBuffer, nSize))
	{
		FILE* fp = NULL;
		if (0 == _tfopen_s(&fp, lpszFileName, _T("wb")))
		{
			fwrite(pBuffer, nSize, 1, fp);
			bRet = TRUE;
			//
			fclose(fp);
		}
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}

BOOL WizStreamWriteUnicode(IStream* pStream, LPCWSTR lpszText)
{
	size_t nLen = wcslen(lpszText);
	//
	return WizStreamWrite(pStream, (void*)lpszText, ULONG(nLen * sizeof(WCHAR)));
}
BOOL WizStreamWriteUnicodeAsFile(IStream* pStream, LPCWSTR lpszText)
{
	WizStreamSeekToBegin(pStream);
	WizStreamSetSize(pStream, 0);
	//
	BYTE szMark[2] = {0xFF, 0xFE};
	if (!WizStreamWrite(pStream, szMark, 2))
		return FALSE;
	//
	size_t nLen = wcslen(lpszText);
	//
	return WizStreamWrite(pStream, (void*)lpszText, ULONG(nLen * sizeof(WCHAR)));
}

BOOL WizStreamLoadAnsiText(IStream* pStream, CStringA& strText)
{
	WizStreamSeekToBegin(pStream);
	//
	int nDataLen = int(WizStreamGetSize(pStream));
	//
	int nStrLen = nDataLen;
	//
	LPSTR pBuffer = strText.GetBuffer(nStrLen + 1);
	ZeroMemory(pBuffer, (nStrLen + 1) * sizeof(CHAR));
	//
	WizStreamSeekToBegin(pStream);
	//
	WizStreamRead(pStream, pBuffer, nDataLen);
	//
	strText.ReleaseBuffer();
	//
	return TRUE;
}

BOOL WizStreamLoadUnicodeAsFile(IStream* pStream, CStringW& strText, BOOL bForceUTF16, LPCTSTR lpszFileName)
{
	WizStreamSeekToBegin(pStream);
	//
	UINT nDataLen = UINT(WizStreamGetSize(pStream));
	//
	if (nDataLen % 2 != 0)
	{
		bForceUTF16 = FALSE;
	}
	//
	UINT nFlags = 0;
	if (bForceUTF16)
	{
		nFlags |= WIZ_LTFF_FORCE_UTF16;
	}
	//
	BOOL bRet = FALSE;
	//
	HGLOBAL hGlobal = NULL;
	HRESULT hr = GetHGlobalFromStream(pStream, &hGlobal);
	if (SUCCEEDED(hr) && hGlobal)
	{
		SIZE_T nGlobalSize = GlobalSize(hGlobal);
		ATLASSERT(nGlobalSize >= nDataLen);
		//
		LPVOID pData = GlobalLock(hGlobal);
		if (pData)
		{
			bRet = WizLoadUnicodeTextFromBuffer((LPCSTR)pData, nDataLen, strText, nFlags, 0, lpszFileName);
		}
		//
		GlobalUnlock(hGlobal);
	}
	else
	{
		BYTE* pData = new BYTE[nDataLen];
		if (!pData)
			return FALSE;
		//
		if (WizStreamRead(pStream, pData, nDataLen))
		{
			bRet = WizLoadUnicodeTextFromBuffer((LPCSTR)pData, nDataLen, strText, nFlags, 0, lpszFileName);
		}
		//
		delete [] pData;
	}
	//
	return bRet;
}

BOOL WizStreamCopy(IStream* pStreamFrom, IStream* pStreamTo)
{
	__int64 nSize = WizStreamGetSize(pStreamFrom);
	//
	WizStreamSeekToBegin(pStreamFrom);
	//
	WizStreamSeekToBegin(pStreamTo);
	WizStreamSetSize(pStreamTo, 0);
	//
	ULARGE_INTEGER	size;
	memset(&size, 0, sizeof(ULARGE_INTEGER));
	size.QuadPart = nSize;
	//
	ULARGE_INTEGER	sizeRead = size;
	ULARGE_INTEGER	sizeWritten = size;
	HRESULT hr = pStreamFrom->CopyTo(pStreamTo, size, &sizeRead, &sizeWritten);
	if (FAILED(hr))
		return FALSE;
	//
	if (sizeRead.QuadPart != sizeWritten.QuadPart || size.QuadPart != sizeWritten.QuadPart)
		return FALSE;
	//
	WizStreamSeekToBegin(pStreamTo);
	//
	return TRUE;
}

size_t WizStreamAppendFile(IStream* pStream, LPCTSTR lpszFileName)
{
	size_t nSize = WizGetFileSize(lpszFileName);
	if (!nSize)
		return 0;
	//
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return size_t(-1);
	//
	BOOL bRet = FALSE;
	//
	FILE* fp = NULL;
	if (0 == _tfopen_s(&fp, lpszFileName, _T("rb")))
	{
		fread(pBuffer, nSize, 1, fp);
		bRet = WizStreamWrite(pStream, pBuffer, ULONG(nSize));
		//
		fclose(fp);
	}
	//
	delete [] pBuffer;
	//
	if (!bRet)
		return size_t(-1);
	//
	return nSize;
}
size_t WizStreamAppendStream(IStream* pStream, IStream* pStreamAppend)
{
	WizStreamSeekToBegin(pStreamAppend);

	ULONG nSize = ULONG(WizStreamGetSize(pStreamAppend));
	BYTE* pBuffer = new BYTE[nSize];
	if (!pBuffer)
		return 0;
	//
	BOOL bRet = FALSE;
	//
	if (WizStreamRead(pStreamAppend, pBuffer, nSize))
	{
		bRet = WizStreamWrite(pStream, pBuffer, nSize);
	}
	//
	delete [] pBuffer;
	//
	if (!bRet)
		return size_t(-1);
	//
	return nSize;
}

BOOL WizStreamCopyEx(IStream* pStreamFrom, IStream* pStreamTo, size_t nSize)
{
	WizStreamSeekToBegin(pStreamTo);
	WizStreamSetSize(pStreamTo, 0);
	//
	ULARGE_INTEGER	size;
	memset(&size, 0, sizeof(ULARGE_INTEGER));
	size.QuadPart = nSize;
	//
	ULARGE_INTEGER	sizeRead = size;
	ULARGE_INTEGER	sizeWritten = size;
	HRESULT hr = pStreamFrom->CopyTo(pStreamTo, size, &sizeRead, &sizeWritten);
	if (FAILED(hr))
		return FALSE;
	//
	if (sizeRead.QuadPart != sizeWritten.QuadPart || size.QuadPart != sizeWritten.QuadPart)
		return FALSE;
	//
	WizStreamSeekToBegin(pStreamTo);
	//
	return TRUE;
}


BOOL WizStreamSafeCopy(IStream* pStreamFrom, IStream* pStreamTo)
{
	const ULONG BUFFER_SIZE = 1024;
	BYTE szBuffer[BUFFER_SIZE];
	//
	while (1)
	{
		ULONG nRead = 0;
		//
		HRESULT hr = pStreamFrom->Read(szBuffer, BUFFER_SIZE, &nRead);
		if (FAILED(hr))
			return FALSE;
		//
		if (S_FALSE == hr)	//end of stream
			break;
		//
		if (0 == nRead)		//end of stream
			break;
		//
		ULONG nWritten = 0;
		if (S_OK != pStreamTo->Write(szBuffer, nRead, &nWritten))
			return FALSE;
		//
		if (nRead != nWritten)
			return FALSE;
		//
		if (nRead < BUFFER_SIZE)
			break;
	}
	//
	WizStreamSeekToBegin(pStreamTo);
	//
	return TRUE;
}

ULONG WizStreamCopyEx(IStream* pStream, IStream* pStreamDest, ULONG nNeedRead)
{
	const UINT nBufferSize = 1024;
	//
	BYTE buffer[nBufferSize];
	//
	ULONG nTotalRead = 0;
	while (1)
	{
		//
#ifdef _DEBUG
		ZeroMemory(buffer, nBufferSize);
#endif
		//
		if (nTotalRead >= nNeedRead)
			break;
		//
		ULONG n = 0;
		//
		ULONG nLast = nNeedRead - nTotalRead;
		if (nLast > nBufferSize)
		{
			n = nBufferSize;
		}
		else
		{
			n = nLast;
		}
		//
		ATLASSERT(n <= nBufferSize);
		//
		ULONG nRead = 0;
		pStream->Read(buffer, n, &nRead);
		//
		nTotalRead += nRead;
		//
		ULONG nWritten = 0;
		pStreamDest->Write(buffer, nRead, &nWritten);
		//
		if (nRead < n)	//read to last
			break;
		if (nWritten != nRead)
			return 0;
	}
	//
	return nTotalRead;
}

HRESULT WizCreateReadOnlyStreamOnFile(LPCTSTR lpszFileName, IStream** ppStream)
{
	if (!PathFileExists(lpszFileName))
	{
		TOLOG1(_T("File %1 does not exists"), lpszFileName);
		return E_INVALIDARG;
	}
	//
	return CWizFileSystemStream::CreateFileSystemStream(lpszFileName, STGM_SHARE_DENY_NONE, ppStream);
}

HRESULT WizCreateWriteOnlyStreamOnFile(LPCTSTR lpszFileName, IStream** ppStream)
{
	if (PathFileExists(lpszFileName))
	{
		if (!DeleteFile(lpszFileName))
		{
			TOLOG1(_T("Failed to delete file: %1"), lpszFileName);
			return E_FAIL;
		}
	}
	//
	return CWizFileSystemStream::CreateFileSystemStream(lpszFileName, STGM_CREATE | STGM_WRITE, ppStream);
}


CComPtr<IStream> WizCreateReadOnlyStreamOnFile(LPCTSTR lpszFileName)
{
	CComPtr<IStream> spStream;
	if (FAILED(WizCreateReadOnlyStreamOnFile(lpszFileName, &spStream)))
	{
		TOLOG1(_T("Failed to create read-only stream on file: %1"), lpszFileName);
		return NULL;
	}
	//
	return spStream;
}

CComPtr<IStream> WizCreateWriteOnlyStreamOnFile(LPCTSTR lpszFileName)
{
	CComPtr<IStream> spStream;
	if (FAILED(WizCreateWriteOnlyStreamOnFile(lpszFileName, &spStream)))
	{
		TOLOG1(_T("Failed to create write-only stream on file: %1"), lpszFileName);
		return NULL;
	}
	//
	return spStream;
}




BOOL WizCopyLargeFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists)
{
	if (bFailIfExists)
	{
		if (PathFileExists(lpNewFileName))
			return FALSE;
	}
	//
	const UINT nBufferSize = 10 * 1024 * 1024;
	BYTE* pBuffer = new BYTE[nBufferSize];
	if (NULL == pBuffer)
		return FALSE;
	//
	struct _stat64 st;
	ZeroMemory(&st, sizeof(st));
	_tstat64(lpExistingFileName, &st);
	__int64 nFileSize = st.st_size;
	//
	BOOL bRet = FALSE;
	//
	int  fd = 0;
	if(0 == _tsopen_s(&fd, lpExistingFileName, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0))
	{
		if (FILE* fp = _tfdopen(fd, _T("rb")))
		{
			FILE* fpDest = NULL;
			if (0 == _tfopen_s(&fpDest, lpNewFileName, _T("wbc")))
			{
				//
				__int64 nCount = nFileSize / nBufferSize;
				__int64 nLeft = nFileSize % nBufferSize;
				//
				__int64 nRead = 0;
				__int64 nWritten = 0;
				//
				for (__int64 i = 0; i < nCount; i++)
				{
					//Sleep(1);
					//WizProcessMessages();
					//
					nRead += nBufferSize * fread(pBuffer, nBufferSize, 1, fp);
					//
					nWritten += nBufferSize * fwrite(pBuffer, nBufferSize, 1, fpDest);
				}
				//
				if (nLeft)
				{
					nRead += nLeft * fread(pBuffer, size_t(nLeft), 1, fp);
					//
					nWritten += nLeft * fwrite(pBuffer, size_t(nLeft), 1, fpDest);
				}
				//
				bRet = (nRead == nWritten) && (nWritten == nFileSize);
				//
				fflush(fpDest);
				//
				fclose(fpDest);
			}
			//
			// After _fdopen, close with fclose, not _close.
			fclose(fp);
		}
		else
		{
			_close(fd);
		}
	}
	//
	delete [] pBuffer;
	//
	return bRet;
}


BOOL WizCopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists)
{
	if (WizGetFileSize(lpExistingFileName) > 10 * 1024 * 1024)
	{
		return WizCopyLargeFile(lpExistingFileName, lpNewFileName, bFailIfExists);
	}
	//
	if (bFailIfExists)
	{
		if (PathFileExists(lpNewFileName))
			return FALSE;
	}
	//
	CComPtr<IStream> spStream;
	if (FAILED(CreateStreamOnHGlobal(NULL, TRUE, &spStream)))
		return FALSE;
	//
	if (!WizStreamLoadFromFile(lpExistingFileName, spStream))
		return FALSE;
	//
	return WizStreamSaveToFile(spStream, lpNewFileName);
}


int WizFileCompare(LPCTSTR lpszFileName1, LPCTSTR lpszFileName2)
{
	if (0 == _tcsicmp(lpszFileName1, lpszFileName2))
		return 0;
	//
	if (!PathFileExists(lpszFileName1))
		return -1;
	else if (!PathFileExists(lpszFileName2))
		return 1;
	//
	DWORD arrayMd5_1[4];
	DWORD arrayMd5_2[4];
	if (!WizMd5File(lpszFileName1, arrayMd5_1))
		return -1;
	else if (!WizMd5File(lpszFileName2, arrayMd5_2))
		return 1;
	//
	return memcmp(arrayMd5_1, arrayMd5_2, sizeof(DWORD) * 4);
}

CString WizCompareCopyFile(LPCTSTR lpszExistingFileName, LPCTSTR lpszNewFileName)
{
	if (0 == WizFileCompare(lpszExistingFileName, lpszNewFileName))
		return CString(lpszNewFileName);							//don not copy file, return the new file
	//
	CString strNewFileName(lpszNewFileName);
	//
	if (PathFileExists(strNewFileName))
	{
		WizGetNextFileName(strNewFileName);
	}
	//
	WizCopyFile(lpszExistingFileName, strNewFileName, FALSE);
	//
	return strNewFileName;
}




void WizCommandLineToStringArray(LPCTSTR lpszCommandLine, CWizStdStringArray& arrayLine)
{
	CString strCommandLine(lpszCommandLine);
	//
	strCommandLine.Insert(0, ' ');
	//
	WizSplitTextToArray(strCommandLine, _T(" /"), FALSE, arrayLine);
}
CString WizGetCommandLineValue(LPCTSTR lpszCommandLine, LPCTSTR lpszKey)
{
	CWizStdStringArray arrayLine;
	WizCommandLineToStringArray(lpszCommandLine, arrayLine);
	//
	return WizStringArrayGetValue(arrayLine, lpszKey);
}

BOOL WizStringArrayGetBool(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey, BOOL bDef)
{
	CString str = WizStringArrayGetValue(arrayLine, lpszKey);
	if (0 == str.CompareNoCase(_T("1")))
		return TRUE;
	if (0 == str.CompareNoCase(_T("true")))
		return TRUE;
	if (0 == str.CompareNoCase(_T("0")))
		return FALSE;
	if (0 == str.CompareNoCase(_T("false")))
		return FALSE;
	//
	return bDef;
}
BOOL WizStringArrayGetInt(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey, int nDef)
{
	CString str = WizStringArrayGetValue(arrayLine, lpszKey);
	//
	int n = _ttoi(str);
	if (WizIntToStr(n) == str)
		return n;
	//
	return nDef;
}

BOOL WizCommandLineKeyExists(const CWizStdStringArray& arrayLine, LPCTSTR lpszKey)
{
	return -1 != WizFindInArrayNoCase(arrayLine, lpszKey);
}


BOOL WizCommandLineKeyExists(LPCTSTR lpszCommandLine, LPCTSTR lpszKey)
{
	CWizStdStringArray arrayLine;
	WizCommandLineToStringArray(lpszCommandLine, arrayLine);
	//
	return WizCommandLineKeyExists(arrayLine, lpszKey);
}

COleDateTime WizTimeBuildTime(const COleDateTime& tDate, const COleDateTime& tTime)
{
	return COleDateTime(tDate.GetYear(), tDate.GetMonth(), tDate.GetDay(), tTime.GetHour(), tTime.GetMinute(), tTime.GetSecond());
}


BOOL WizStringSimpleSplit(const CString& str, TCHAR ch, CString& strLeft, CString& strRight)
{
	int nPos = str.Find(ch);
	if (-1 == nPos)
		return FALSE;
	//
	strLeft = str.Left(nPos);
	strRight = str.Right(str.GetLength() - nPos - 1);
	return TRUE;
}



CWizBufferAlloc::CWizBufferAlloc(int nInitSize)
{
	m_nSize = 0;
    m_pBuffer = NULL;
    if (nInitSize > 0)
    {
        m_pBuffer = new BYTE[nInitSize];
        memset(m_pBuffer, 0, nInitSize);
	    m_nSize = nInitSize;
    }
}
CWizBufferAlloc::~CWizBufferAlloc()
{
    if (m_pBuffer)
    {
        delete [] m_pBuffer;
    }
    m_pBuffer = NULL;
}

BYTE* CWizBufferAlloc::GetBuffer()
{
    return m_pBuffer;
}

BOOL CWizBufferAlloc::SetNewSize(int nNewSize)
{
    if (!m_pBuffer)
    {
        m_pBuffer = new BYTE[nNewSize];
        memset(m_pBuffer, 0, nNewSize);
        m_nSize = nNewSize;
    }
    else
    {
        if (m_nSize < nNewSize)
        {
            delete [] m_pBuffer;
            m_pBuffer = NULL;
            m_pBuffer = new BYTE[nNewSize];
            memset(m_pBuffer, 0, nNewSize);
            m_nSize = nNewSize;
        }
    }
    return !m_pBuffer;
}




CWizStrBufferAlloc::CWizStrBufferAlloc(size_t nInitSize)
{
	m_nSize = 0;
	m_pBuffer = NULL;
	if (nInitSize > 0)
	{
		m_pBuffer = new TCHAR[nInitSize];
		memset(m_pBuffer, 0, nInitSize * sizeof(TCHAR));
		m_nSize = nInitSize;
	}
}
CWizStrBufferAlloc::~CWizStrBufferAlloc()
{
	if (m_pBuffer)
	{
		delete [] m_pBuffer;
	}
	m_pBuffer = NULL;
}

LPTSTR CWizStrBufferAlloc::GetBuffer()
{
	return m_pBuffer;
}

BOOL CWizStrBufferAlloc::SetNewSize(size_t nNewSize)
{
	if (!m_pBuffer)
	{
		m_pBuffer = new TCHAR[nNewSize];
		memset(m_pBuffer, 0, nNewSize * sizeof(TCHAR));
		m_nSize = nNewSize;
	}
	else
	{
		if (m_nSize < nNewSize)
		{
			LPTSTR lpszOldBuffer = m_pBuffer;
			//
			m_pBuffer = new TCHAR[nNewSize];
			memset(m_pBuffer, 0, nNewSize * sizeof(TCHAR));
			_tcscpy_s(m_pBuffer, nNewSize, lpszOldBuffer),
				m_nSize = nNewSize;
			//
			delete [] lpszOldBuffer;
		}
	}
	return !m_pBuffer;
}
void CWizStrBufferAlloc::Append(LPCTSTR lpszText)
{
	if (!m_pBuffer)
	{
		SetNewSize(_tcslen(lpszText) * 2);
	}
	if (!m_pBuffer)
		return;
	//
	size_t nOldLength = _tcslen(m_pBuffer);
	size_t nAddedLength = _tcslen(lpszText);
	if (nOldLength + nAddedLength < m_nSize)
	{
		_tcscpy_s(m_pBuffer + nOldLength, m_nSize - nOldLength, lpszText);
	}
	else
	{
		size_t nNewSize = size_t((m_nSize + nAddedLength) * 1.5);
		SetNewSize(nNewSize);
		_tcscpy_s(m_pBuffer + nOldLength, m_nSize - nOldLength, lpszText);
	}
}
void CWizStrBufferAlloc::Empty()
{
	if (!m_pBuffer)
		return;
	//
	*m_pBuffer = 0;

}

BOOL CWizStrBufferAlloc::IsEmpty() const
{
	if (!m_pBuffer)
		return TRUE;
	if (! (*m_pBuffer))
		return TRUE;
	//
	return FALSE;
}


BOOL WizSimpleEncryptStringToFile(const char* lpszPassword, LPCWSTR lpszText, LPCWSTR lpszFileName)
{
	typedef STDMETHODIMP Type_WizToolsSimpleEncryptStringToFile(const unsigned char* lpszKey, LPCWSTR lpszText, LPCWSTR lpszFileName);
	//
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizTools.dll"));
	if (!hModule)
		return FALSE;
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizToolsSimpleEncryptStringToFile* fun = (Type_WizToolsSimpleEncryptStringToFile *)GetProcAddress(hModule, "WizToolsSimpleEncryptStringToFile");
	if (fun)
	{
		hr = fun((const unsigned char* )lpszPassword, lpszText, lpszFileName);
	}
	//
	FreeLibrary(hModule);
	//
	return SUCCEEDED(hr);
}


BOOL WizSimpleDecryptStringFromFile(const char* lpszPassword, LPCWSTR lpszFileName, CString& strText)
{
	typedef STDMETHODIMP Type_WizToolsSimpleDecryptStringFromFile(const unsigned char* lpszKey, LPCWSTR lpszFileName, BSTR* pbstrRet);
	//
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizTools.dll"));
	if (!hModule)
		return FALSE;
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizToolsSimpleDecryptStringFromFile* fun = (Type_WizToolsSimpleDecryptStringFromFile *)GetProcAddress(hModule, "WizToolsSimpleDecryptStringFromFile");
	if (fun)
	{
		CComBSTR bstrText;
		hr = fun((const unsigned char* )lpszPassword, lpszFileName, &bstrText);
		if (SUCCEEDED(hr))
		{
			strText = CString(bstrText);
		}
	}
	//
	FreeLibrary(hModule);
	//
	return SUCCEEDED(hr);
}


BOOL WizSimpleEncryptTextFileToFile(const char* lpszPassword, LPCWSTR lpszTextFileName, LPCWSTR lpszFileName)
{
	CString strText;
	if (!WizLoadUnicodeTextFromFile(lpszTextFileName, strText))
		return FALSE;
	//
	return WizSimpleEncryptStringToFile(lpszPassword, strText, lpszFileName);
}


BOOL WizGetFileVersion(LPCTSTR lpszFileName, WIZFILEVERSIONDATA& version)
{
	BOOL bRet = FALSE;
	//
	DWORD dwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSize(lpszFileName, &dwHandle);
	//
	if (!dwSize)
		return bRet;
	//
	LPTSTR lpBuffer = new TCHAR[dwSize]; 
	if (!lpBuffer)
		return bRet;
	//
	if (GetFileVersionInfo (lpszFileName, 0, dwSize, (LPVOID)lpBuffer))
	{
		UINT cchVer = 0;
		VS_FIXEDFILEINFO *pInfo = NULL;

		if (VerQueryValue(lpBuffer, TEXT("\\"), (LPVOID*)&pInfo, &cchVer) && cchVer && pInfo)
		{
			int n1 = HIWORD(pInfo->dwFileVersionMS);
			int n2 = LOWORD(pInfo->dwFileVersionMS);
			int n3 = HIWORD(pInfo->dwFileVersionLS);
			int n4 = LOWORD(pInfo->dwFileVersionLS);
			//
			//1.2.3.4
			//
			//1.0.3.1		1.03 beta1
			//1.0.3.2		1.03 beta2
			//1.0.3.2		1.03 beta2
			//1.0.3.8		1.03 Release
			//
			if (n4 >= 8)
			{
				//Release
				version.bBeta = FALSE;
			}
			else
			{
				version.bBeta = TRUE;
			}
			//
			version.strMajor.Format(_T("%d.%d%d"), n1, n2, n3);
			//
			version.nIndex = n4;
			//
			bRet = TRUE;
		}
	}
	//
	delete [] lpBuffer;
	//
	return bRet;
}

CString WizGetFileVersion(LPCTSTR lpszFileName)
{
	CString strVersion;
	//
	DWORD dwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSize(lpszFileName, &dwHandle);
	//
	if (!dwSize)
		return strVersion;
	//
	LPTSTR lpBuffer = new TCHAR[dwSize]; 
	if (!lpBuffer)
		return strVersion;
	//
	if (GetFileVersionInfo (lpszFileName, 0, dwSize, (LPVOID)lpBuffer))
	{
		UINT cchVer = 0;
		VS_FIXEDFILEINFO *pInfo = NULL;

		if (VerQueryValue(lpBuffer, TEXT("\\"), (LPVOID*)&pInfo, &cchVer) && cchVer && pInfo)
		{
			strVersion.Format(_T("%d.%d.%d.%d"), 
				int(HIWORD(pInfo->dwFileVersionMS)),
				int(LOWORD(pInfo->dwFileVersionMS)),
				int(HIWORD(pInfo->dwFileVersionLS)),
				int(LOWORD(pInfo->dwFileVersionLS)));
		}
	}
	//
	delete [] lpBuffer;
	//
	return strVersion;
}

BOOL WizGetFileVersion(LPCTSTR lpszFileName, DWORD* pdwMajor, DWORD* pdwMinor)
{
	DWORD dwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSize(lpszFileName, &dwHandle);
	//
	if (!dwSize)
		return FALSE;
	//
	LPTSTR lpBuffer = new TCHAR[dwSize]; 
	if (!lpBuffer)
		return FALSE;
	//
	if (GetFileVersionInfo (lpszFileName, 0, dwSize, (LPVOID)lpBuffer))
	{
		UINT cchVer = 0;
		VS_FIXEDFILEINFO *pInfo = NULL;

		if (VerQueryValue(lpBuffer, TEXT("\\"), (LPVOID*)&pInfo, &cchVer) && cchVer && pInfo)
		{
			if (pdwMajor)
				*pdwMajor = HIWORD(pInfo->dwFileVersionMS);
			if (pdwMinor)
				*pdwMinor = LOWORD(pInfo->dwFileVersionMS);
		}
	}
	//
	delete [] lpBuffer;
	//
	return TRUE;
}

BOOL WizIsIE7()
{
	static DWORD dwMajor = 0;
	if (0 == dwMajor)
	{
		WizGetFileVersion(_T("mshtml.dll"), &dwMajor, NULL);
	}
	//
	return dwMajor >= 7;
}




HRESULT WizDispatchSetProperty(IDispatch* pDisp, LPCTSTR lpszName, VARIANT vValue)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.PutPropertyByName(lpszName, &vValue);
}

HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vValue)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.GetPropertyByName(lpszName, &vValue);
}
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, CComBSTR& bstrValue)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.GetPropertyByName(lpszName, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (!(vRet.vt & VT_BSTR))
		return E_FAIL;
	//
	if (!vRet.bstrVal)
		return E_FAIL;
	//
	bstrValue = vRet.bstrVal;
	//
	return S_OK;
}

HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, CComPtr<IDispatch>& spDispRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.GetPropertyByName(lpszName, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (vRet.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!vRet.pdispVal)
		return E_FAIL;
	//
	spDispRet = vRet.pdispVal;
	//
	return S_OK;
}

#ifdef __ATLCOMTIME_H__
HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, COleDateTime& dt)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.GetPropertyByName(lpszName, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (!(vRet.vt & VT_DATE))
		return E_FAIL;
	//
	if (!vRet.date)
		return E_FAIL;
	//
	dt = vRet.date;
	//
	return S_OK;
}
#endif

HRESULT WizDispatchGetProperty(IDispatch* pDisp, LPCTSTR lpszName, int& nRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.GetPropertyByName(lpszName, &vRet);
	if (FAILED(hr))
		return hr;
	//
	nRet = vRet.intVal;
	//
	return S_OK;
}

HRESULT WizDispatchInvoke0(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.Invoke0(lpszName, pvarRet);
}

HRESULT WizDispatchInvoke1(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT* pvarRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.Invoke1(lpszName, &vParam1, pvarRet);
}

HRESULT WizDispatchInvoke1(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, CComPtr<IDispatch>& spDispRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.Invoke1(lpszName, &vParam1, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (vRet.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!vRet.pdispVal)
		return E_FAIL;
	//
	spDispRet = vRet.pdispVal;
	//
	return S_OK;
}

HRESULT WizDispatchInvoke2(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT& vParam2, VARIANT* pvarRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.Invoke2(lpszName, &vParam1, &vParam2, pvarRet);
}
HRESULT WizDispatchInvoke2(IDispatch* pDisp, LPCTSTR lpszName, VARIANT& vParam1, VARIANT& vParam2, CComPtr<IDispatch>& spDispRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.Invoke2(lpszName, &vParam1, &vParam2, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (vRet.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!vRet.pdispVal)
		return E_FAIL;
	//
	spDispRet = vRet.pdispVal;
	//
	return S_OK;
}
HRESULT WizDispatchInvokeN(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarParams, int nParams, VARIANT* pvarRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	return spDisp.InvokeN(lpszName, pvarParams, nParams, pvarRet);
}
HRESULT WizDispatchInvokeN(IDispatch* pDisp, LPCTSTR lpszName, VARIANT* pvarParams, int nParams, CComPtr<IDispatch>& spDispRet)
{
	CComPtr<IDispatch> spDisp(pDisp);
	//
	CComVariant vRet;
	HRESULT hr = spDisp.InvokeN(lpszName, pvarParams, nParams, &vRet);
	if (FAILED(hr))
		return hr;
	//
	if (vRet.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!vRet.pdispVal)
		return E_FAIL;
	//
	spDispRet = vRet.pdispVal;
	//
	return S_OK;
}
BOOL WizCreateDispatchOnServer(LPCTSTR lpszProgID, CComPtr<IDispatch>& spDisp)
{
	CLSID clsid;
	if (FAILED(CLSIDFromProgID(CComBSTR(lpszProgID), &clsid)))
		return FALSE;
	//
	CComPtr<IUnknown> spUnk;
	HRESULT hr = spUnk.CoCreateInstance(clsid);
	if (FAILED(hr))
		return FALSE;
	//
	OleRun(spUnk);
	//
	spDisp = CComQIPtr<IDispatch>(spUnk);
	if (!spDisp)
		return FALSE;
	//
	return TRUE;
}




CWizWindowLocker::CWizWindowLocker()
{
	m_hWnd = NULL;
	m_bLocked = FALSE;
}
CWizWindowLocker::CWizWindowLocker(HWND hwnd)
{
	m_hWnd = hwnd;
	m_bLocked = FALSE;
	m_bLocked = Lock();
}
CWizWindowLocker::~CWizWindowLocker()
{
	Unlock();
}
BOOL CWizWindowLocker::Lock()
{
	if (!m_hWnd)
		return FALSE;
	if (m_bLocked)
		return FALSE;
	//
	ATLASSERT(m_hWnd);
	SendMessage(m_hWnd, WM_SETREDRAW, FALSE, 0);
	//
	m_bLocked = TRUE;
	//
	return TRUE;
}
void CWizWindowLocker::Unlock()
{
	if (!m_bLocked)
		return;
	if (!m_hWnd)
		return;
	//
	m_bLocked = FALSE;
	//
	SendMessage(m_hWnd, WM_SETREDRAW, TRUE, 0);
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	InvalidateRect(m_hWnd, &rc, FALSE);
}
void CWizWindowLocker::SetWindow(HWND hWnd)
{
	ATLASSERT(!m_hWnd);
	m_hWnd = hWnd;
}




BOOL WizVariantToStringArray(const VARIANT& v, CWizStdStringArray& arrayText)
{
	if (VT_ARRAY != (v.vt & VT_ARRAY))
		return FALSE;
	//
	CComSafeArray<VARIANT> sa(v.parray);
	//
	ULONG nCount = sa.GetCount();
	LONG nLower = sa.GetLowerBound();
	LONG nUpper = sa.GetUpperBound();
	for (LONG i = nLower; i <= nUpper; i++)
	{
		VARIANT vElem = sa.GetAt(i);
		if (vElem.vt != VT_BSTR)
			return FALSE;
		//
		arrayText.push_back(CString(vElem.bstrVal));
	}
	return TRUE;
}

BOOL WizStringArrayToVariant(const CWizStdStringArray& arrayText, VARIANT& v)
{
	ULONG nCount = ULONG(arrayText.size());
	CComSafeArray<VARIANT> varray(nCount);
	for (ULONG i = 0; i < nCount; i++)
	{
		varray.SetAt(i, CComVariant(CComBSTR(arrayText[i])));
	}
	CComVariant vTemp(varray.m_psa);
	//
	VariantCopy(&v, &vTemp);
	//
	return TRUE;
}

COLORREF WizColorSchemesGetDarkBackgroundColor(COLORREF crBackground)
{
	switch (crBackground)
	{
	case WIZCOLOR_PINK:
		return RGB(0xEF, 0xBD, 0xEF);
	case WIZCOLOR_YELLOW:
		return RGB(0xF7, 0xF6, 0xAE);
	case WIZCOLOR_GREEN:
		return RGB(0xBF, 0xF6, 0xBA);
	case WIZCOLOR_BLUE:
		return RGB(0xC3, 0xEA, 0xF7);
	case WIZCOLOR_PRUPLE:
		return RGB(0xCF, 0xC7, 0xF2);
	case WIZCOLOR_WHITE:
		return RGB(0xF4, 0xF4, 0xF4);
	default:
		return WizColorDarker(crBackground, 0.95f);
	}
}


CString WizGetProcessFileName()
{
	TCHAR szFileName[MAX_PATH] = {0};
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	//
	return CString(szFileName);
}

HICON WizGetProcessIcon()
{
	HMODULE hModule = GetModuleHandle(NULL);
	//
	return ExtractIcon(hModule, WizGetProcessFileName(), 0);
}


void WizDeleteAllFilesInFolderEx(LPCTSTR lpszPath)
{
	CWizStdStringArray arrayFiles;
	WizEnumFiles(lpszPath, _T("*.*"), arrayFiles, EF_INCLUDESUBDIR);
	//
	for (CWizStdStringArray::const_iterator it = arrayFiles.begin(); it != arrayFiles.end(); it++)
	{
		DeleteFile(*it);
	}
	//
	CWizStdStringArray arrayFolders;
	WizEnumFolders(lpszPath, arrayFolders, EF_INCLUDESUBDIR);
	//
	size_t nFolderCount = arrayFolders.size();
	for (intptr_t i = nFolderCount - 1; i >= 0; i--)
	{
		RemoveDirectory(arrayFolders[i]);
	}
	//
	return WizDeleteAllFilesInFolder(lpszPath);
}


BOOL WizDeleteAllFilesInFolder3(LPCTSTR lpszPath)
{
	CWizStdStringArray arrayFiles;
	WizEnumFiles(lpszPath, _T("*.*"), arrayFiles, EF_INCLUDESUBDIR);
	//
	for (CWizStdStringArray::const_iterator it = arrayFiles.begin(); it != arrayFiles.end(); it++)
	{
		DeleteFile(*it);
	}
	//
	CWizStdStringArray arrayFolders;
	WizEnumFolders(lpszPath, arrayFolders, EF_INCLUDESUBDIR);
	//
	std::sort(arrayFolders.begin(), arrayFolders.end());
	//
	size_t nFolderCount = arrayFolders.size();
	for (intptr_t i = nFolderCount - 1; i >= 0; i--)
	{
		RemoveDirectory(arrayFolders[i]);
	}
	//
	return TRUE;
}


BOOL WizDeleteAllEmptySubFolders(LPCTSTR lpszPath)
{
	CWizStdStringArray arrayFolders;
	WizEnumFolders(lpszPath, arrayFolders, 0);
	//
	for (CWizStdStringArray::const_iterator it = arrayFolders.begin();
		it != arrayFolders.end();
		it++)
	{
		CString strSubFolder = *it;
		//
		CWizStdStringArray arrayFile;
		WizEnumFiles(strSubFolder, _T("*.*"), arrayFile, EF_INCLUDESUBDIR);
		if (arrayFile.empty())
		{
			WizDeleteAllFilesInFolder3(strSubFolder);
			RemoveDirectory(strSubFolder);
		}
	}
	//
	return TRUE;
}


HRESULT WizSaveIconToFile(HICON hIcon, LPCTSTR lpszFileName)
{
	PICTDESC pictDesc;
	pictDesc.cbSizeofstruct = sizeof(PICTDESC);
	pictDesc.icon.hicon = hIcon;
	pictDesc.picType = PICTYPE_ICON;
	//
	CComPtr<IPicture> spPicture;
	//
	HRESULT hr = OleCreatePictureIndirect(&pictDesc, IID_IPicture, TRUE, (void**)&spPicture);
	if (FAILED(hr))
		return hr;
	//
	CComPtr<IStream> spStream;
	hr = ::CreateStreamOnHGlobal(NULL, TRUE ,&spStream);
	if (FAILED(hr))
		return hr;
	//
	LONG lSize = 0;
	hr = spPicture->SaveAsFile(spStream, TRUE, &lSize); 
	if (FAILED(hr))
		return hr;
	//
	WizStreamSeekToBegin(spStream);
	//
	return WizStreamSaveToFile(spStream, lpszFileName);
}


CWizComInit::CWizComInit()
{
	CoInitialize(NULL);
}
CWizComInit::~CWizComInit()
{
	CoUninitialize();
}




COLORREF WizColorDarker(COLORREF crBase, float fFactor)
{
	ATLASSERT(fFactor <= 1.0f && fFactor > 0.0f);

	fFactor = min(fFactor, 1.0f);
	fFactor = max(fFactor, 0.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedShadow, bBlueShadow, bGreenShadow;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedShadow = (BYTE)(bRed * fFactor);
	bBlueShadow = (BYTE)(bBlue * fFactor);
	bGreenShadow = (BYTE)(bGreen * fFactor);

	return RGB(bRedShadow, bGreenShadow, bBlueShadow);
}

COLORREF WizColorLighter(COLORREF crBase, float fFactor) 
{
	ATLASSERT(fFactor >= 1.0f);

	fFactor = max(fFactor, 1.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedHilite, bBlueHilite, bGreenHilite;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedHilite = (BYTE)min((int)(bRed * fFactor), 255);
	bBlueHilite = (BYTE)min((int)(bBlue * fFactor), 255);
	bGreenHilite = (BYTE)min((int)(bGreen * fFactor), 255);

	return RGB(bRedHilite, bGreenHilite, bBlueHilite);
}


void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMessage)
{
#ifdef __ATLBASE_H__
	ATLTRACE(_T("%s\n"), lpszMessage);
#else
	TRACE(_T("%s\n"), lpszMessage);
#endif
	//
	CString strFileName(lpszFileName);
	if (WizGetFileSize(strFileName) > 1024 * 1024 || WizGetFileType(strFileName) != WIZ_FT_UTF_16)
	{
		DeleteFile(strFileName);
	}
	//
	BOOL bExists = PathFileExists(strFileName);
	BOOL bWriteMark = !bExists;
	//
	FILE* fp = NULL;
	if (0 != _tfopen_s(&fp, strFileName, bExists ? _T("r+b") : _T("wb")))
		return;
	//
	try
	{
		//
		if (bWriteMark)
		{
			BYTE szMark[2] = {BYTE(0xFF), BYTE(0xFE)};
			fwrite(szMark, 2, 1, fp);
		}
		else
		{
			fseek(fp, 0, SEEK_END);
		}
		//
		CStringW strTime = CStringW(WizDateTimeToLocalStringLongDate(COleDateTime::GetCurrentTime()));
		//
		WCHAR szTimeBuffer[MAX_PATH] = {0};
		wcscpy_s(szTimeBuffer, MAX_PATH, strTime);
		//
		fwrite(szTimeBuffer, wcslen(szTimeBuffer) * sizeof(WCHAR), 1, fp);
		//
		int nTickCount = GetTickCount();
		WCHAR szTickCount[MAX_PATH] = {0};
#ifdef WINCE
		swprintf(szTickCount, L" (%d)", nTickCount);
#else
		swprintf_s(szTickCount, MAX_PATH, L" (%d)", nTickCount);
#endif
		fwrite(szTickCount, wcslen(szTickCount) * sizeof(WCHAR), 1, fp);
		//
		LPCWSTR lpszSplitter = L": ";
		fwrite(lpszSplitter, wcslen(lpszSplitter) * sizeof(WCHAR), 1, fp);
		//
		CStringW strMessage(lpszMessage);
		strMessage.Replace(L'\r', L' ');
		strMessage.Replace(L'\n', L' ');
		//
		LPCWSTR lpszMessageToWrite = strMessage;
		fwrite(lpszMessageToWrite, wcslen(lpszMessageToWrite) * sizeof(WCHAR), 1, fp);
		//
		LPCWSTR lpszEndLine = L"\r\n";
		fwrite(lpszEndLine, wcslen(lpszEndLine) * sizeof(WCHAR), 1, fp);
		//
		fflush(fp);
	}
	catch (...)
	{
	}
	fclose(fp);
}

void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID)
{
	CString strMsg;
	strMsg.LoadString(nMsgID);
	//
	WizWriteLog(lpszFileName, strMsg);
}
void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMsg, LPCTSTR lpszParam1)
{
	CString strMsg = WizFormatString1(lpszMsg, lpszParam1);
	//
	WizWriteLog(lpszFileName, strMsg);
}

void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID, LPCTSTR lpszParam1)
{
	CString strMsg = WizFormatString1(nMsgID, lpszParam1);
	//
	WizWriteLog(lpszFileName, strMsg);
}
void WizWriteLog(LPCTSTR lpszFileName, LPCTSTR lpszMsg, LPCTSTR lpszParam1, LPCTSTR lpszParam2)
{
	CString strMsg = WizFormatString2(lpszMsg, lpszParam1, lpszParam2);
	//
	WizWriteLog(lpszFileName, strMsg);
}

void WizWriteLog(LPCTSTR lpszFileName, UINT nMsgID, LPCTSTR lpszParam1, LPCTSTR lpszParam2)
{
	CString strMsg = WizFormatString2(nMsgID, lpszParam1, lpszParam2);
	//
	WizWriteLog(lpszFileName, strMsg);
}



HRESULT WizCallDispatchDefaultMethod(VARIANT& v)
{
	if (v.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!v.pdispVal)
		return S_FALSE;
	//
	CComPtr<IDispatch> spDisp(v.pdispVal);
	if (!spDisp)
		return S_FALSE;
	//
	CComVariant vResult;
	return spDisp.Invoke0((DISPID)DISPID_VALUE, &vResult);
}

HRESULT WizCallDispatchDefaultMethod1(VARIANT& v, VARIANT& vParam1)
{
	if (v.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!v.pdispVal)
		return S_FALSE;
	//
	CComPtr<IDispatch> spDisp(v.pdispVal);
	if (!spDisp)
		return S_FALSE;
	//
	CComVariant vResult;
	return spDisp.Invoke1((DISPID)DISPID_VALUE, &vParam1, &vResult);
}

HRESULT WizCallDispatchDefaultMethod2(VARIANT& v, VARIANT& vParam1, VARIANT& vParam2)
{
	if (v.vt != VT_DISPATCH)
		return E_FAIL;
	//
	if (!v.pdispVal)
		return S_FALSE;
	//
	CComPtr<IDispatch> spDisp(v.pdispVal);
	if (!spDisp)
		return S_FALSE;
	//
	CComVariant vResult;
	return spDisp.Invoke2((DISPID)DISPID_VALUE, &vParam1, &vParam2, &vResult);
}

#if _WIN32_WINNT >= 0x0501

BOOL WizOpenFolderAndSelectFile(LPCTSTR lpszFileName)
{
	CString strPath = WizExtractFilePath(lpszFileName);
	// Get a pointer to the Desktop's IShellFolder interface.
	// 
	CComPtr<IShellFolder> spDesktopFolder;
	if ( FAILED(SHGetDesktopFolder(&spDesktopFolder)))
		return FALSE;
	//
	WCHAR szPath[1024] = {0};
	wcscpy_s(szPath, 1024, CStringW(strPath));

	WCHAR szFileName[1024] = {0};
	wcscpy_s(szFileName, 1024, CStringW(lpszFileName));
	//
	LPITEMIDLIST pidlFolder = NULL;
	ULONG chEaten = 0;
	ULONG dwAttributes = 0;
	HRESULT hr = spDesktopFolder->ParseDisplayName(NULL, NULL, szPath, &chEaten, &pidlFolder, &dwAttributes);
	if (FAILED(hr))
		return FALSE;
	//
	LPITEMIDLIST pidlFile = NULL;
	chEaten = 0;
	dwAttributes = 0;
	//
	hr = spDesktopFolder->ParseDisplayName(NULL, NULL, szFileName, &chEaten, &pidlFile, &dwAttributes);
	if (FAILED(hr))
		return FALSE;
	//
	LPCITEMIDLIST pidlFileTemp = pidlFile;
	//
	hr = SHOpenFolderAndSelectItems(pidlFolder, 1, &pidlFileTemp, 0);
	//
	return SUCCEEDED(hr);
}

#endif


BOOL WizGetFileName(CString& strResultFileName, BOOL bOpen, LPCTSTR lpszFilter, LPCTSTR lpszInitFileName, LPCTSTR lpszDefExt)
{
	//
	TCHAR szFileName[1024] = {0};
	if (lpszInitFileName)
	{
		_tcscpy_s(szFileName, 1024, lpszInitFileName);
	}
	//
	CString strFilter(lpszFilter);
	TCHAR szFilter[1024] = {0};
	_tcscpy_s(szFilter, 1024, strFilter);
	LPTSTR p = szFilter;
	while (*p)
	{
		if (*p == '|')
		{
			*p = '\0';
		}
		p++;
	}
	//
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = ::GetActiveWindow();
	ofn.hInstance = NULL; 
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFileName; 
	ofn.nMaxFile = 1024;
	ofn.lpstrDefExt = lpszDefExt;
	ofn.lpstrTitle = NULL;
	//
	if (bOpen)
	{
		DWORD dwFlags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
		ofn.Flags = dwFlags;
		//
		if (!GetOpenFileName(&ofn))
			return FALSE;
	}
	else
	{
		DWORD dwFlags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
		ofn.Flags = dwFlags;
		//
		if (!GetSaveFileName(&ofn))
			return FALSE;
	}
	//
	strResultFileName = CString(szFileName);
	//
	return TRUE;
}

BOOL WizGetFileName(CString& strResultFileName, BOOL bOpen, UINT nIDFilter, LPCTSTR lpszInitFileName, LPCTSTR lpszDefExt)
{
	return WizGetFileName(strResultFileName, bOpen, WizFormatString0(nIDFilter), lpszInitFileName, strResultFileName);
}

BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, LPCTSTR lpszFilter, LPTSTR pFileBuffer, UINT nBufferSize)
{
	arrayFileName.clear();
	//
	CString strFilter(lpszFilter);
	TCHAR szFilter[1024] = {0};
	_tcscpy_s(szFilter, 1024, strFilter);
	LPTSTR p = szFilter;
	while (*p)
	{
		if (*p == '|')
		{
			*p = '\0';
		}
		p++;
	}
	//
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = ::GetActiveWindow();
	ofn.hInstance = NULL; 
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = pFileBuffer; 
	ofn.nMaxFile = nBufferSize;
	ofn.lpstrDefExt = NULL;
	ofn.lpstrTitle = NULL;
	//
	DWORD dwFlags = OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
	ofn.Flags = dwFlags;
	//
	if (!GetOpenFileName(&ofn))
		return FALSE;
	//
	p = pFileBuffer;
	while (*p)
	{
		arrayFileName.push_back(p);
		//
		p += _tcslen(p);
		p++;
	}
	//
	if (arrayFileName.empty())
		return FALSE;
	//
	if (1 == arrayFileName.size())
		return TRUE;
	//
	CString strPath = arrayFileName[0];
	WizPathAddBackslash(strPath);
	//
	arrayFileName.erase(arrayFileName.begin());
	//
	size_t nCount = arrayFileName.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strName = arrayFileName[i];
		CString strFileName = strPath + strName;
		arrayFileName[i] = strFileName;
	}
	//
	return TRUE;
}

BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, LPCTSTR lpszFilter, UINT nMaxFile)
{
	int nBufferSize = nMaxFile * (MAX_PATH * 2);
	TCHAR* pBuffer = new TCHAR[nBufferSize];
	if (!pBuffer)
	{
		TOLOG(_T("Out of memory!"));
		return FALSE;
	}
	//
	ZeroMemory(pBuffer, sizeof(TCHAR) * nBufferSize);
	//
	BOOL bRet = WizGetMultiFileName(arrayFileName, lpszFilter, pBuffer, nBufferSize);
	//
	delete [] pBuffer;
	//
	return bRet;
}
BOOL WizGetMultiFileName(CWizStdStringArray& arrayFileName, UINT nIDFilter, UINT nMaxFile)
{
	return WizGetMultiFileName(arrayFileName, WizFormatString0(nIDFilter), nMaxFile);
}



CString WizGetDisplayTime(const COleDateTime& t)
{
	COleDateTime tCurrent = WizGetCurrentTime();
	//
	int nYear = t.GetYear();
	int nMonth = t.GetMonth();
	int nDay = t.GetDay();
	int nCurrentYear = tCurrent.GetYear();
	int nCurrentMonth = tCurrent.GetMonth();
	int nCurrentDay = tCurrent.GetDay();
	//
	COleDateTimeSpan ts = tCurrent - t;
	//
	if (nYear == nCurrentYear
		&& nMonth == nCurrentMonth
		&& nDay == nCurrentDay)
	{
		int nHours = ts.GetHours();
		if (nHours > 0)
		{
			return WizFormatString1(WizTranslationsTranslateString(_T("%1 hours ago")), WizIntToStr(nHours));
		}
		else
		{
			int nMinutes = ts.GetMinutes();
			if (nMinutes > 0)
			{
				return WizFormatString1(WizTranslationsTranslateString(_T("%1 minutes ago")), WizIntToStr(nMinutes));
			}
			else
			{
				int nSeconds = ts.GetSeconds();
				return WizFormatString1(WizTranslationsTranslateString(_T("%1 seconds ago")), WizIntToStr(nSeconds));
			}
		}
	}
	else
	{
		COleDateTime tYesterday = tCurrent - COleDateTimeSpan(1, 0, 0, 0);
		if (nYear == tYesterday.GetYear()
			&& nMonth == tYesterday.GetMonth()
			&& nDay == tYesterday.GetDay())
		{
			return WizTranslationsTranslateString(_T("Yesterday"));
		}
		else
		{
			COleDateTime tDayBeforeYesterday = t - COleDateTimeSpan(2, 0, 0, 0);
			if (nYear == tDayBeforeYesterday.GetYear()
				&& nMonth == tDayBeforeYesterday.GetMonth()
				&& nDay == tDayBeforeYesterday.GetDay())
			{
				return WizTranslationsTranslateString(_T("The day before yesterday"));
			}
			else
			{
				return WizDateToLocalString(t);
			}
		}
	}
}

HRESULT WizCreateObjectGreen(LPCTSTR lpszDllFileName, CLSID clsid, REFIID iid, void** ppObj, HMODULE hModule)
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
	hr = spClassFactory->CreateInstance(NULL, iid, ppObj);
	if (FAILED(hr))
	{
		TOLOG2(_T("Failed to create object: IID=%1, DllFileName=%2"), CString(CComBSTR(iid)), lpszDllFileName);
		return hr;
	}
	//
	return hr;
}



BOOL CWizXmlSettingsSection::GetStr(LPCTSTR lpszKey, CString& strValue)
{
	const_iterator it = find(lpszKey);
	if (it == end())
		return FALSE;
	//
	strValue = it->second;
	//
	return TRUE;
}
//
CString CWizXmlSettingsSection::GetStr(LPCTSTR lpszKey, LPCTSTR lpszDef)
{
	CString str;
	if (!GetStr(lpszKey, str))
		return CString(lpszDef);
	//
	return str;
}
int CWizXmlSettingsSection::GetInt(LPCTSTR lpszKey, int nDef)
{
	CString str;
	if (!GetStr(lpszKey, str))
		return nDef;
	//
	return _ttoi(str);
}
BOOL CWizXmlSettingsSection::GetBool(LPCTSTR lpszKey, BOOL bDef)
{
	CString str;
	if (!GetStr(lpszKey, str))
		return bDef;
	//
	return _ttoi(str) ? TRUE : FALSE;
}
//
BOOL CWizXmlSettingsSection::Valid() const
{
	return !empty();
}




CWizXmlSettings::CWizXmlSettings(LPCTSTR lpszFileName, LPCTSTR lpszRootNodeName)
	: m_strFileName(lpszFileName)
	, m_strRootNodeName(lpszRootNodeName)
{
	m_bModified = FALSE;
	//
	if (PathFileExists(lpszFileName))
	{
		if (!m_doc.LoadFromFile(lpszFileName))
		{
			TOLOG1(_T("Failed to load xml file: %1"), lpszFileName);
		}
	}
}
CWizXmlSettings::~CWizXmlSettings(void)
{
	if (m_bModified)
	{
		if (!m_doc.ToUnicodeFile(m_strFileName))
		{
			TOLOG1(_T("Failed to save xml file: %1"), m_strFileName);
			return;
		}
	}
	//
	m_doc.Clear();
}
BOOL CWizXmlSettings::GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue)
{
	if (!m_doc.SettingsGetStringValue(m_strRootNodeName, lpszSection, lpszKey, _T(""), strValue))
	{
		TOLOG2(_T("Failed to get settings value: %1.%2"), lpszSection, lpszKey);
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizXmlSettings::SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	if (!m_doc.SettingsSetStringValue(m_strRootNodeName, lpszSection, lpszKey, lpszValue))
	{
		TOLOG3(_T("Failed to set settings value: %1.%2=%3"), lpszSection, lpszKey, lpszValue);
		return FALSE;
	}
	//
	m_bModified = TRUE;
	//
	return TRUE;
}
BOOL CWizXmlSettings::GetSection(LPCTSTR lpszSection, CWizXmlSettingsSection& section)
{
	// TODO: Add your implementation code here
	CWizXMLNode nodeSection;
	if (!m_doc.SettingsFindSectionNode(m_strRootNodeName, lpszSection, nodeSection))
	{
		//TOLOG1(_T("Failed to get section node: %1"), lpszSection);
		return S_FALSE;
	}
	//
	std::vector<CWizXMLNode> arrayNode;
	if (!nodeSection.GetAllChildNodes(arrayNode))
	{
		TOLOG1(_T("Failed to get section: %1"), lpszSection);
		return E_FAIL;
	}
	//
	for (std::vector<CWizXMLNode>::iterator it = arrayNode.begin();
		it != arrayNode.end();
		it++)
	{
		section[it->GetName()] = it->GetText();
	}
	//
	return TRUE;
}

BOOL CWizXmlSettings::ClearSection(LPCTSTR lpszSection)
{
	// TODO: Add your implementation code here
	CWizXMLNode nodeSection;
	if (!m_doc.SettingsFindSectionNode(m_strRootNodeName, lpszSection, nodeSection))
	{
		//TOLOG1(_T("Failed to get section node: %1"), lpszSection);
		return FALSE;
	}
	//
	nodeSection.DeleteAllChild();

	return TRUE;
}



CWizXMLNode::CWizXMLNode()
{
}


CWizXMLNode::CWizXMLNode(IXMLDOMDocument* pDoc, IXMLDOMNode* pNode)
{
	if (pDoc && pNode)
	{
		InitData(pDoc, pNode);
	}
}
CWizXMLNode::CWizXMLNode(const CWizXMLNode& nodeSrc)
{
	if (nodeSrc.Valid())
	{
		InitData(nodeSrc.m_spDoc, nodeSrc.m_spNode);
	}
	else
	{
		Clear();
	}
}

CWizXMLNode::~CWizXMLNode()
{
}
CWizXMLNode& CWizXMLNode::operator = (const CWizXMLNode& right)
{
	if (right.m_spDoc && right.m_spNode)
	{
		InitData(right.m_spDoc, right.m_spNode);
	}
	else
	{
		Clear();
	}
	return *this;
}

void CWizXMLNode::InitData(IXMLDOMDocument* pDoc, IXMLDOMNode* pNode)
{
#ifdef __ATLBASE_H__
	ATLASSERT(pDoc);
	ATLASSERT(pNode);
#else
	ASSERT(pDoc);
	ASSERT(pNode);
#endif
	m_spDoc = pDoc;
	m_spNode = pNode;
}

BOOL CWizXMLNode::GetName(CString& strName)
{
	BOOL bRet = FALSE;
	//
	CComBSTR bstrName = NULL;
	if (S_OK == m_spNode->get_nodeName(&bstrName) && bstrName)
	{
		bRet = TRUE;
		strName = bstrName;
	}
	//
	return bRet;
}
CString CWizXMLNode::GetName()
{
	CString strName;
	GetName(strName);
	return strName;
}
CString CWizXMLNode::GetType()
{
	if (!m_spNode)
		return CString();
	//
	CComBSTR bstrType = NULL;
	if (S_OK == m_spNode->get_nodeTypeString(&bstrType) && bstrType)
	{
		return CString(bstrType);
	}
	//
	return CString();
}


CString CWizXMLNode::GetText(LPCTSTR lpszDefault /* = NULL */)
{
	CString str;
	if (!GetText(str))
	{
		str = lpszDefault;
	}
	//
	return str;
}
BOOL CWizXMLNode::GetText(CString& strText)
{
	BOOL bRet = FALSE;
	//
	CComBSTR bstrText = NULL;
	if (S_OK == m_spNode->get_text(&bstrText) && bstrText)
	{
		bRet = TRUE;
		strText = bstrText;
	}
	//
	return bRet;
}
BOOL CWizXMLNode::SetText(LPCTSTR lpszText)
{
	ATLASSERT(m_spNode);
	//
	return SUCCEEDED(m_spNode->put_text(CComBSTR(lpszText)));
}
BOOL CWizXMLNode::GetAttributeText(LPCTSTR lpszName, CString& strVal)
{
	BOOL bRet = FALSE;
	CComPtr<IXMLDOMNamedNodeMap> spNodeMap = NULL;
	if (FAILED(m_spNode->get_attributes(&spNodeMap)))
		return FALSE;
	if (!spNodeMap)
		return FALSE;

	CComBSTR bstrName(lpszName);
	CComPtr<IXMLDOMNode> spNode = NULL;
	if (FAILED(spNodeMap->getNamedItem(bstrName, &spNode)))
		return FALSE;
	if (!spNode)
		return FALSE;
	//
	CComVariant vValue;
	if (FAILED(spNode->get_nodeValue(&vValue)))
		return FALSE;
	//
	if (vValue.vt != VT_BSTR)
		return FALSE;
	//
	strVal = vValue.bstrVal;
	return TRUE;
}
BOOL CWizXMLNode::GetAttributeInt(LPCTSTR lpszName, int& nVal)
{
	CString strRet;
	if (!GetAttributeText(lpszName, strRet))
		return FALSE;
	//
	nVal = _ttoi(strRet);
	//
	return TRUE;
}
BOOL CWizXMLNode::GetAttributeInt64(LPCTSTR lpszName, __int64& nVal)
{
	CString strRet;
	if (!GetAttributeText(lpszName, strRet))
		return FALSE;
	//
	nVal = _ttoi64(strRet);
	//
	return TRUE;
}
__int64 CWizXMLNode::GetAttributeInt64Def(LPCTSTR lpszName, __int64 nDefault)
{
	CString strRet;
	if (!GetAttributeText(lpszName, strRet))
		return nDefault;
	//
	return _ttoi64(strRet);
}
BOOL CWizXMLNode::GetAttributeUINT(LPCTSTR lpszName, UINT& nVal)
{
	int n;
	if (!GetAttributeInt(lpszName, n))
		return FALSE;
	//
	nVal = n;
	//
	return TRUE;
}
BOOL CWizXMLNode::GetAttributeTimeT(LPCTSTR lpszName, time_t& nVal)
{
	__int64 n64;
	if (!GetAttributeInt64(lpszName, n64))
		return FALSE;
	//
	nVal = time_t(n64);
	//
	return TRUE;
}
BOOL CWizXMLNode::GetAttributeTimeString(LPCTSTR lpszName, COleDateTime& t)
{
	CString str;
	if (!GetAttributeText(lpszName, str))
		return FALSE;
	//
	CString strError;
	if (!WizStringToDateTime(str, t, strError))
	{
		TOLOG(strError);
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizXMLNode::GetAttributeDWORD(LPCTSTR lpszName, DWORD& dwVal)
{
	int nVal = 0;
	if (!GetAttributeInt(lpszName, nVal))
		return FALSE;
	//
	dwVal = DWORD(nVal);
	//
	return TRUE;
}
BOOL CWizXMLNode::GetAttributeBool(LPCTSTR lpszName, BOOL& bVal)
{
	CString strRet;
	if (!GetAttributeText(lpszName, strRet))
		return FALSE;
	//
	strRet.Trim();
	//
	bVal = strRet.Compare(_T("1")) == 0;
	//
	return TRUE;
}
//
CString CWizXMLNode::GetAttributeTextDef(LPCTSTR lpszName, LPCTSTR lpszDefault)
{
	CString strVal;
	if (!GetAttributeText(lpszName, strVal))
	{
		strVal = lpszDefault;
	}
	return strVal;
}
int CWizXMLNode::GetAttributeIntDef(LPCTSTR lpszName, int nDefault)
{
	int nVal = 0;
	if (!GetAttributeInt(lpszName, nVal))
	{
		nVal = nDefault;
	}
	return nVal;
}
BOOL CWizXMLNode::GetAttributeBoolDef(LPCTSTR lpszName, BOOL bDefault)
{
	BOOL bVal = FALSE;
	if (!GetAttributeBool(lpszName, bVal))
	{
		bVal = bDefault;
	}
	return bVal;
}
BOOL CWizXMLNode::SetAttributeText(LPCTSTR lpszName, LPCTSTR lpszText)
{
	ATLASSERT(m_spNode);
	//
	HRESULT hr = E_FAIL;
	//
	CComBSTR bstrName(lpszName);
	//
	CComPtr<IXMLDOMAttribute> spAttr = NULL;
	if (FAILED(m_spDoc->createAttribute(bstrName, &spAttr)))
		return FALSE;
	if (FAILED(spAttr->put_nodeValue(CComVariant(CComBSTR(lpszText)))))
		return FALSE;
	CComPtr<IXMLDOMNamedNodeMap> spNodeMap = NULL;
	if (FAILED(m_spNode->get_attributes(&spNodeMap) ))
		return FALSE;
	CComPtr<IXMLDOMNode> spNewNode = NULL;
	return SUCCEEDED(spNodeMap->setNamedItem(spAttr, &spNewNode));
}
BOOL CWizXMLNode::SetAttributeInt(LPCTSTR lpszName, int nVal)
{
	return SetAttributeText(lpszName, WizIntToStr(nVal));
}
BOOL CWizXMLNode::SetAttributeInt64(LPCTSTR lpszName, __int64 nVal)
{
	return SetAttributeText(lpszName, WizInt64ToStr(nVal));
}
BOOL CWizXMLNode::SetAttributeTime(LPCTSTR lpszName, const COleDateTime& t)
{
	return SetAttributeText(lpszName, WizDateTimeToString(t));
}

BOOL CWizXMLNode::SetAttributeBool(LPCTSTR lpszName, BOOL bVal)
{
	return SetAttributeText(lpszName, bVal ? _T("1") : _T("0"));
}
BOOL CWizXMLNode::FindChildNode(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild)
{
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	CComPtr<IXMLDOMNode> spChildNode = NULL;
	if (!FindChildNode(spChildNodeList, lpszNodeName, &spChildNode))
		return FALSE;
	nodeChild.InitData(m_spDoc, spChildNode);
	return TRUE;
}
BOOL CWizXMLNode::GetAllChildNodes(CWizStdStringArray& arrayNodeName)
{
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		CComBSTR bstrNodeName;
		if (FAILED(spNode->get_nodeName(&bstrNodeName)))
			continue;
		//
		arrayNodeName.push_back(CString(bstrNodeName));
	}
	return TRUE;
}
BOOL CWizXMLNode::GetAllChildNodes(std::vector<CWizXMLNode>& arrayNodes)
{
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		//
		CWizXMLNode nodeChild(m_spDoc, spNode);
		arrayNodes.push_back(nodeChild);
	}
	return TRUE;
}
BOOL CWizXMLNode::GetFirstChildNode(CWizXMLNode& nodeChild)
{
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	if (nCount <= 0)
		return FALSE;
	//
	CComPtr<IXMLDOMNode> spNode = NULL;
	if (FAILED(spChildNodeList->get_item(0, &spNode)))
		return FALSE;
	//
	CComBSTR bstrType;
	spNode->get_nodeTypeString(&bstrType);
	if (CString(bstrType) != _T("element"))
		return FALSE;
	//
	nodeChild = CWizXMLNode(m_spDoc, spNode);
	//
	return TRUE;
}


BOOL CWizXMLNode::DeleteChild(LPCTSTR lpszChildName)
{
	CWizXMLNode node;
	if (!FindChildNode(lpszChildName, node))
		return TRUE;
	//
	m_spNode->removeChild(node.m_spNode, NULL);
	//
	return TRUE;
}
BOOL CWizXMLNode::DeleteChild(CWizXMLNode& nodeChild)
{
	return SUCCEEDED(m_spNode->removeChild(nodeChild.m_spNode, NULL));
}
BOOL CWizXMLNode::DeleteAllChild(LPCTSTR lpszExceptNodeName1, LPCTSTR lpszExceptNodeName2, LPCTSTR lpszExceptNodeName3)
{
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = nCount - 1; i >= 0; i--)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		//
		if ((lpszExceptNodeName1 && *lpszExceptNodeName1)
			|| (lpszExceptNodeName2 && *lpszExceptNodeName2)
			|| (lpszExceptNodeName3 && *lpszExceptNodeName3)
			)
		{
			CComBSTR bstrName;
			spNode->get_nodeName(&bstrName);
			//
			CString strName(bstrName);
			//
			if (lpszExceptNodeName1 
				&& *lpszExceptNodeName1
				&& strName == lpszExceptNodeName1)
				continue;
			//
			if (lpszExceptNodeName2
				&& *lpszExceptNodeName2
				&& strName == lpszExceptNodeName2)
				continue;
			//
			if (lpszExceptNodeName3
				&& *lpszExceptNodeName3
				&& strName == lpszExceptNodeName3)
				continue;
		}
		//
		m_spNode->removeChild(spNode, NULL);
	}
	return TRUE;
}
BOOL CWizXMLNode::HasChildNode()
{
	int nChildCount = 0;
	//
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	//
	return nCount > 0;
}

int CWizXMLNode::GetChildNodesCount()
{
	int nChildCount = 0;
	//
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spNode->get_childNodes(&spChildNodeList) && spChildNodeList))
		return nChildCount;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	//
	nChildCount = nCount;
	//
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		//
		CWizXMLNode node(m_spDoc, spNode);
		//
		nChildCount += node.GetChildNodesCount();
		//
	}
	return nChildCount;
}


BOOL CWizXMLNode::AppendChild(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild)
{
	CComBSTR bstrName(lpszNodeName);

	VARIANT vType;
	vType.vt = VT_I4;
	vType.lVal = NODE_ELEMENT;
	CComPtr<IXMLDOMNode> spNewNode = NULL;
	if (FAILED(m_spDoc->createNode(vType, bstrName, CComBSTR(L""), &spNewNode)))
		return FALSE;
	CComPtr<IXMLDOMNode> spRetNode;
	if (FAILED(m_spNode->appendChild(spNewNode, &spRetNode)))
		return FALSE;
	nodeChild.InitData(m_spDoc, spRetNode);
	//
	return TRUE;
}
BOOL CWizXMLNode::AppendChild(LPCTSTR lpszNodeName, LPCTSTR lpszChildNodeText)
{
	CWizXMLNode nodeChild;
	if (!AppendChild(lpszNodeName, nodeChild))
		return FALSE;
	//
	return nodeChild.SetText(lpszChildNodeText);
}

BOOL CWizXMLNode::SetChildNodeText(LPCTSTR lpszNodeName, LPCTSTR lpszText)
{
	CWizXMLNode nodeChild;
	if (!GetChildNode(lpszNodeName, nodeChild))
		return FALSE;
	//
	return nodeChild.SetText(lpszText);
}

BOOL CWizXMLNode::GetChildNodeText(LPCTSTR lpszNodeName, CString& strText)
{
	CWizXMLNode nodeChild;
	if (!GetChildNode(lpszNodeName, nodeChild))
		return FALSE;
	//
	return nodeChild.GetText(strText);
}
CString CWizXMLNode::GetChildNodeTextDef(LPCTSTR lpszNodeName, LPCTSTR lpszDef)
{
	CString str;
	if (GetChildNodeText(lpszNodeName, str))
		return str;
	//
	return CString(lpszDef);
}

BOOL CWizXMLNode::GetChildNode(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild)
{
	if (FindChildNode(lpszNodeName, nodeChild))
		return TRUE;
	return AppendChild(lpszNodeName, nodeChild);
}
BOOL CWizXMLNode::FindChildNode(IXMLDOMNodeList* pChildNodeList, LPCTSTR lpszName, IXMLDOMNode** ppChildNode)
{
	long nCount = 0;
	if (FAILED(pChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(pChildNodeList->get_item(i, &spNode)))
			continue;
		BSTR bstrNodeName;
		if (FAILED(spNode->get_nodeName(&bstrNodeName)))
			continue;
		//
		CString strNodeName(bstrNodeName);
		SysFreeString(bstrNodeName);
		//
		if (strNodeName.CompareNoCase(lpszName) == 0)
		{
			*ppChildNode = spNode;
			(*ppChildNode)->AddRef();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CWizXMLNode::FindNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet)
{
	CWizStdStringArray arrayText;
	if (!WizSplitTextToArray(lpszPath, '/', arrayText))
		return FALSE;
	//
	WizStringArrayEraseEmptyLine(arrayText);
	//
	if (arrayText.empty())
		return FALSE;
	//
	CWizXMLNode node = *this;
	//
	for (size_t i = 0; i < arrayText.size(); i++)
	{
		CString strNodeName = arrayText[i];
		//
		strNodeName.Trim();
		//
		if (strNodeName.IsEmpty())
			return FALSE;
		//
		CWizXMLNode nodeChild;
		if (!node.FindChildNode(strNodeName, nodeChild))
			return FALSE;
		//
		node = nodeChild;
	}
	//
	ATLASSERT(node.Valid());
	//
	nodeRet = node;
	//
	return TRUE;
}

BOOL CWizXMLNode::AppendNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet)
{
	CWizStdStringArray arrayText;
	if (!WizSplitTextToArray(lpszPath, '/', arrayText))
		return FALSE;
	//
	WizStringArrayEraseEmptyLine(arrayText);
	//
	if (arrayText.empty())
		return FALSE;
	//
	CWizXMLNode node = *this;
	//
	for (size_t i = 0; i < arrayText.size(); i++)
	{
		CString strNodeName = arrayText[i];
		//
		strNodeName.Trim();
		//
		if (strNodeName.IsEmpty())
			return FALSE;
		//
		CWizXMLNode nodeChild;
		if (!node.AppendChild(strNodeName, nodeChild))
		{
			TOLOG1(_T("Failed to append child node: %1"), strNodeName);
			return FALSE;
		}
		//
		node = nodeChild;
	}
	//
	ATLASSERT(node.Valid());
	//
	nodeRet = node;
	//
	return TRUE;
}

BOOL CWizXMLNode::AppendNodeSetTextByPath(LPCTSTR lpszPath, LPCTSTR lpszText)
{
	CWizXMLNode nodeRet;
	if (!AppendNodeByPath(lpszPath, nodeRet))
	{
		TOLOG1(_T("Failed to append node by path: %!"), lpszPath);
		return FALSE;
	}
	//
	BOOL bRet = nodeRet.SetText(lpszText);
	if (!bRet)
	{
		TOLOG(_T("Failed to set node text"));
		return FALSE;
	}
	//
	return TRUE;
}



BOOL CWizXMLNode::FindNodeTextByPath(LPCTSTR lpszPath, CString& strRet)
{
	CWizXMLNode node;
	if (!FindNodeByPath(lpszPath, node))
		return FALSE;
	//
	return node.GetText(strRet);
}
BOOL CWizXMLNode::GetElementNodeByValue(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, CWizXMLNode& nodeRet)
{
	std::vector<CWizXMLNode> arrayNodes;
	if (!GetAllChildNodes(arrayNodes))
		return FALSE;
	//
	size_t nCount = arrayNodes.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CWizXMLNode& node = arrayNodes[i];
		//
		if (node.GetName() != lpszElementName)
			continue;
		//
		CWizXMLNode nodeValue;
		if (!node.FindNodeByPath(lpszValueName, nodeValue))
			continue;
		//
		if (0 == nodeValue.GetText().CompareNoCase(lpszValue))
		{
			nodeRet = node;
			return TRUE;
		}
	}
	//
	return FALSE;
}
BOOL CWizXMLNode::GetElementOtherNodeByValue(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, CWizXMLNode& nodeRet)
{
	CWizXMLNode nodeElement;
	if (!GetElementNodeByValue(lpszElementName, lpszValueName, lpszValue, nodeElement))
		return FALSE;
	//
	return nodeElement.FindNodeByPath(lpszOtherNodePath, nodeRet);
}
BOOL CWizXMLNode::GetElementOtherNodeByValueReturnString(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, CString& strRet)
{
	CWizXMLNode nodeRet;
	if (!GetElementOtherNodeByValue(lpszElementName, lpszValueName, lpszValue, lpszOtherNodePath, nodeRet))
		return FALSE;
	//
	strRet = nodeRet.GetText();
	//
	return TRUE;
}
BOOL CWizXMLNode::GetElementOtherNodeByValueReturnInt(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, int& nRet)
{
	CString strRet;
	if (!GetElementOtherNodeByValueReturnString(lpszElementName, lpszValueName, lpszValue, lpszOtherNodePath, strRet))
		return FALSE;
	//
	strRet.Trim();
	//
	int nTemp = _ttoi(strRet);
	if (WizIntToStr(nTemp) == strRet)
	{
		nRet = nTemp;
		return TRUE;
	}
	//
	return FALSE;
}
BOOL CWizXMLNode::GetElementOtherNodeByValueReturnBool(LPCTSTR lpszElementName, LPCTSTR lpszValueName, LPCTSTR lpszValue, LPCTSTR lpszOtherNodePath, BOOL& bRet)
{
	CString strRet;
	if (!GetElementOtherNodeByValueReturnString(lpszElementName, lpszValueName, lpszValue, lpszOtherNodePath, strRet))
		return FALSE;
	//
	strRet.Trim();
	strRet.MakeLower();
	//
	if (strRet == _T("0")
		|| strRet == _T("false"))
	{
		bRet = FALSE;
		//
		return TRUE;
	}
	else if (strRet == _T("1")
		|| strRet == _T("true"))
	{
		bRet = TRUE;
		//
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	//
	return TRUE;
}


//////////////////////////////////////////////////////////////////////

CWizXMLDocument::CWizXMLDocument()
{
	m_spDoc = NULL;
	Create();
}
CWizXMLDocument::CWizXMLDocument(IXMLDOMDocument* pDoc)
{
	m_spDoc = pDoc;
}

CWizXMLDocument::~CWizXMLDocument()
{
}
BOOL CWizXMLDocument::Create()
{
	if (m_spDoc != NULL)
		return FALSE;
	//
	CLSID clsidXML;
	ZeroMemory(&clsidXML, sizeof(CLSID));
	//
	HRESULT hr = CLSIDFromProgID(L"Msxml2.DOMDocument", &clsidXML);
	if (FAILED(hr))
	{
		hr = CLSIDFromProgID(L"MSXML.DOMDocument", &clsidXML);
		if (FAILED(hr))
		{
			CString strMessage;
			strMessage.Format(_T("No MSXML Installed, HRESULT=0x%08X"), hr);
			MessageBox(GetForegroundWindow(), strMessage, 0, 0);
			return FALSE;
		}
	}
	//
	hr = m_spDoc.CoCreateInstance(clsidXML);
	if (FAILED(hr))
	{
		CString strMessage;
		strMessage.Format(_T("Failed to create XMLDocument, HRESULT=0x%08X"), hr);
		MessageBox(GetForegroundWindow(), strMessage, 0, 0);
		return FALSE;
	}
	return TRUE;
}
BOOL CWizXMLDocument::LoadXML(BSTR bstrXML)
{
#ifdef WINCE
	if (SysStringLen(bstrXML) > 1024 * 1024)
		return FALSE;
#endif
	if (!m_spDoc)
		return FALSE;
	VARIANT_BOOL b = VARIANT_FALSE;
	HRESULT hr = m_spDoc->loadXML(bstrXML, &b);
	if (FAILED(hr) || VARIANT_FALSE == b)
	{
#ifdef _DEBUG
		IsFail();
#endif
	}
	//
	return SUCCEEDED(hr) && (VARIANT_TRUE == b);
}
BOOL CWizXMLDocument::LoadFromFile(LPCTSTR lpszFileName, BOOL bPromptError /*= TRUE*/)
{
	if (!m_spDoc)
		return FALSE;
	//
	if (WizGetFileSize(lpszFileName) < 10)
	{
		DeleteFile(lpszFileName);
	}
	//
	if (!PathFileExists(lpszFileName))
		return FALSE;
	//
#ifdef WINCE
	if (WizGetFileSize(lpszFileName) > 1024 * 1024)
		return FALSE;
#endif
	CComBSTR bstrFileName(lpszFileName);
	//
	CComVariant vFileName(bstrFileName);
	VARIANT_BOOL b = VARIANT_FALSE;
	HRESULT hr = m_spDoc->load(vFileName, &b);
	//
	if (FAILED(hr) || VARIANT_FALSE == b)
	{
		if (bPromptError)
		{
			IsFail();
		}
	}
	//
	return SUCCEEDED(hr) && (VARIANT_TRUE == b);
}
void CWizXMLDocument::Clear()
{
	if (!m_spDoc)
		return;
	//
	m_spDoc.Release();
	Create();
}

//
BOOL CWizXMLDocument::FindChildNode(LPCTSTR lpszName, CWizXMLNode& nodeChild)
{
	if (!m_spDoc)
		return FALSE;
	//
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spDoc->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	CComPtr<IXMLDOMNode> spChildNode = NULL;
	if (!CWizXMLNode::FindChildNode(spChildNodeList, lpszName, &spChildNode))
		return FALSE;
	nodeChild.InitData(m_spDoc, spChildNode);
	return TRUE;
}
//
BOOL CWizXMLDocument::IsFail()
{
	if (!m_spDoc)
		return TRUE;
	//
	BOOL bRet = FALSE;
	//
	m_strErrorMessage.Empty();
	m_strErrorSrcText.Empty();
	//
	//
	CComPtr<IXMLDOMParseError> spParseError;
	if (FAILED(m_spDoc->get_parseError(&spParseError)))
		return FALSE;
	//
	if (!spParseError)
		return FALSE;
	//
	long nError = 0;
	spParseError->get_errorCode(&nError);
	//
	if (0 == nError)
		return FALSE;
	//
	CComBSTR bstrMessage;
	if (SUCCEEDED(spParseError->get_reason(&bstrMessage)))
	{
		m_strErrorMessage = CString(bstrMessage);
#ifdef _DEBUG
		WizErrorMessageBox(m_strErrorMessage);
#endif
		ATLTRACE(m_strErrorMessage);
		ATLTRACE(_T("\n"));
		TOLOG(m_strErrorMessage);
	}
	CComBSTR bstrSrcText;
	if (SUCCEEDED(spParseError->get_srcText(&bstrSrcText)))
	{
		m_strErrorSrcText = CString(bstrSrcText);
		ATLTRACE(m_strErrorSrcText);
		ATLTRACE(_T("\n"));
		TOLOG(m_strErrorSrcText);
	}
	//
	return TRUE;
}
BOOL CWizXMLDocument::AppendChild(LPCTSTR lpszNodeName, CWizXMLNode& nodeChild)
{
	if (!m_spDoc)
		return FALSE;
	//
	CComBSTR bstrName(lpszNodeName);

	VARIANT vType;
	vType.vt = VT_I4;
	vType.lVal = NODE_ELEMENT;
	CComPtr<IXMLDOMNode> spNewNode = NULL;
	if (FAILED(m_spDoc->createNode(vType, bstrName, CComBSTR(L""), &spNewNode)))
		return FALSE;
	CComPtr<IXMLDOMNode> spRetNode;
	if (FAILED(m_spDoc->appendChild(spNewNode, &spRetNode)))
		return FALSE;
	nodeChild.InitData(m_spDoc, spRetNode);
	//
	return TRUE;
}
BOOL CWizXMLDocument::GetChildNode(LPCTSTR lpszName, CWizXMLNode& nodeChild)
{
	if (!m_spDoc)
		return FALSE;
	//
	if (FindChildNode(lpszName, nodeChild))
		return TRUE;
	return AppendChild(lpszName, nodeChild);
}

BOOL CWizXMLDocument::ToXML(CString& strText, BOOL bFormatText)
{
	if (!m_spDoc)
		return FALSE;
	//
	BSTR bstrText = NULL;
	HRESULT hr = m_spDoc->get_xml(&bstrText);
	if (FAILED(hr) || !bstrText)
		return FALSE;
	//
	strText = CString(bstrText);
	if (strText.IsEmpty())
		return FALSE;
	//
	if (bFormatText)
	{
		WizFormatXML(strText);
	}
	//
	return TRUE;
}
BOOL CWizXMLDocument::ToUnicodeFile(LPCTSTR lpszFileName)
{
	if (!m_spDoc)
		return FALSE;
	//
	CString strText;
	if (!ToXML(strText, TRUE))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszFileName, CStringW(strText));
}

BOOL CWizXMLDocument::GetAllChildNodes(CWizStdStringArray& arrayNodeName)
{
	if (!m_spDoc)
		return FALSE;
	//
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spDoc->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		CComBSTR bstrNodeName;
		if (FAILED(spNode->get_nodeName(&bstrNodeName)))
			continue;
		//
		arrayNodeName.push_back(CString(bstrNodeName));
	}
	return TRUE;
}
BOOL CWizXMLDocument::GetAllChildNodes(std::vector<CWizXMLNode>& arrayNodes)
{
	if (!m_spDoc)
		return FALSE;
	//
	CComPtr<IXMLDOMNodeList> spChildNodeList = NULL;
	if (FAILED(m_spDoc->get_childNodes(&spChildNodeList) && spChildNodeList))
		return FALSE;
	//
	long nCount = 0;
	if (FAILED(spChildNodeList->get_length(&nCount)))
		return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> spNode = NULL;
		if (FAILED(spChildNodeList->get_item(i, &spNode)))
			continue;
		//
		CWizXMLNode nodeChild(m_spDoc, spNode);
		arrayNodes.push_back(nodeChild);
	}
	return TRUE;
}
BOOL CWizXMLDocument::FindNodeByPath(LPCTSTR lpszPath, CWizXMLNode& nodeRet)
{
	CWizStdStringArray arrayText;
	if (!WizSplitTextToArray(lpszPath, '/', arrayText))
		return FALSE;
	//
	WizStringArrayEraseEmptyLine(arrayText);
	//
	if (arrayText.empty())
		return FALSE;
	//
	CWizXMLNode nodeRoot;
	if (!FindChildNode(arrayText[0], nodeRoot))
		return FALSE;
	//
	CWizXMLNode node = nodeRoot;
	//
	for (size_t i = 1; i < arrayText.size(); i++)
	{
		CString strNodeName = arrayText[i];
		//
		strNodeName.Trim();
		//
		if (strNodeName.IsEmpty())
			return FALSE;
		//
		CWizXMLNode nodeChild;
		if (!node.FindChildNode(strNodeName, nodeChild))
			return FALSE;
		//
		node = nodeChild;
	}
	//
	ATLASSERT(node.Valid());
	//
	nodeRet = node;
	//
	return TRUE;
}

BOOL CWizXMLDocument::GetNodeTextByPath(LPCTSTR lpszPath, CString& strRet)
{
	CWizXMLNode node;
	if (!FindNodeByPath(lpszPath, node))
		return FALSE;
	//
	return node.GetText(strRet);
}

BOOL CWizXMLDocument::SettingsGetSectionNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, CWizXMLNode& node)
{
	CWizXMLNode nodeRoot;
	if (!GetChildNode(lpszRootName, nodeRoot))
	{
		//TOLOG1(_T("Failed to get root node by name: %1"), lpszRootName);
		return FALSE;
	}
	//
	if (!nodeRoot.GetChildNode(lpszNodeName, node))
	{
		//TOLOG1(_T("Failed to get section node by name: %1"), lpszNodeName);
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizXMLDocument::SettingsFindSectionNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, CWizXMLNode& node)
{
	CWizXMLNode nodeRoot;
	if (!FindChildNode(lpszRootName, nodeRoot))
	{
		//TOLOG1(_T("Failed to get root node by name: %1"), lpszRootName);
		return FALSE;
	}
	//
	if (!nodeRoot.FindChildNode(lpszNodeName, node))
	{
		//TOLOG1(_T("Failed to get section node by name: %1"), lpszNodeName);
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizXMLDocument::SettingsGetChildNode(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, CWizXMLNode& node)
{
	CWizXMLNode nodeRoot;
	if (!GetChildNode(lpszRootName, nodeRoot))
	{
		//TOLOG1(_T("Failed to get root node by name: %1"), lpszRootName);
		return FALSE;
	}
	//
	CWizXMLNode nodeParent;
	if (!nodeRoot.GetChildNode(lpszNodeName, nodeParent))
	{
		//TOLOG1(_T("Failed to get section node by name: %1"), lpszNodeName);
		return FALSE;
	}
	//
	if (!nodeParent.GetChildNode(lpszSubNodeName, node))
	{
		TOLOG1(_T("Failed to get key node by name: %1"), lpszSubNodeName);
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizXMLDocument::SettingsGetStringValue(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, LPCTSTR lpszDefault, CString& strValue)
{
	CWizXMLNode node;
	if (!SettingsGetChildNode(lpszRootName, lpszNodeName, lpszSubNodeName, node))
	{
		TOLOG(_T("Failed to get value node"));
		return FALSE;
	}
	//
	strValue = node.GetText(lpszDefault);
	//
	return TRUE;
}
BOOL CWizXMLDocument::SettingsSetStringValue(LPCTSTR lpszRootName, LPCTSTR lpszNodeName, LPCTSTR lpszSubNodeName, LPCTSTR lpszValue)
{
	CWizXMLNode node;
	if (!SettingsGetChildNode(lpszRootName, lpszNodeName, lpszSubNodeName, node))
	{
		TOLOG(_T("Failed to get value node"));
		return FALSE;
	}
	//
	return node.SetText(lpszValue);
}


BOOL WizFormatXML(CString& strXML)
{
	if (strXML.GetLength() > 10 * 1024)
		return TRUE;
	//
	int nBegin = -1;
	int nEnd = -1;
	for (int i = 1; i < strXML.GetLength(); i++)
	{
		if (strXML[i] == '>')
			nBegin = i + 1;
		else if (strXML[i] == '<')
			nEnd = i - 1;
		//
		if (nBegin != -1 && nEnd != -1 && nEnd >= nBegin)
		{
			CString strOld = strXML.Mid(nBegin, nEnd - nBegin + 1);
			if (!strOld.IsEmpty())
			{
				if (-1 != strOld.FindOneOf(_T("<>")))
				{
#ifdef __AFX_H__
					ASSERT(FALSE);
					TRACE0("Warning: Failed to format XML!");
#else
					ATLASSERT(FALSE);
					ATLTRACE(_T("Warning: Failed to format XML!"));
#endif
					return FALSE;
				}
				//
				CString strNew = strOld;
				strNew.Trim();
				if (strNew != strOld)
				{
					strXML.Delete(nBegin, strOld.GetLength());
					if (!strNew.IsEmpty())
					{
						strXML.Insert(nBegin, strNew);
					}
					//
					i = nBegin + strNew.GetLength();
				}
			}
			//
			nBegin = -1;
			nEnd = -1;
		}
	}
	//
	const LPCTSTR lpszEndLine = _T("\n");
	//
	#define WizFormatXML_ADDINDENT2(str, strOffset)\
		str.Append(lpszEndLine);\
		str.Append(strOffset);
	//
	if (strXML.IsEmpty())
		return TRUE;

	CString strOffset(_T('\t'));
	//
	CString strRet;
	strRet.AppendChar(strXML[0]);
	//
	int nXMLLength = strXML.GetLength();
	for (int i = 1; i < nXMLLength; i++)
	{
		TCHAR ch = strXML[i];
		TCHAR chPrev = strXML[i - 1];
		TCHAR chNext = 0;
		if (i < nXMLLength - 1)
			chNext = strXML[i + 1];
		//
		BOOL bSelfClose = (ch == '>' && chPrev == '/');				//	/>
		BOOL bCloseTag  = (ch == '<' && chNext == '/');				//	 </
		//
		if (bCloseTag || bSelfClose)
		{
			strOffset.Delete(strOffset.GetLength() - 1);
			//
			if (bCloseTag)
			{
				//
				TCHAR chPrev1 = chPrev;
				TCHAR chPrev2 = 0;
				if (i >= 2)
				{
					chPrev2 = strXML[i - 2];
				}
				//
				BOOL bPrevIsSelfClose = (chPrev2 == '/' && chPrev1 == '>');
				if (bPrevIsSelfClose)
				{
					//<b><a/>Here</b>
					WizFormatXML_ADDINDENT2(strRet, strOffset);
				}
				else
				{
					//<b><a></a>Here</b>
					int nPrevTagBegin = strRet.ReverseFind('<');
					//
					ATLASSERT(nPrevTagBegin != -1);
					//
					if (nPrevTagBegin != -1)
					{
						ATLASSERT(strRet.GetLength() > nPrevTagBegin + 1);
						//
						if (strRet[nPrevTagBegin + 1] == '/')
						{
							WizFormatXML_ADDINDENT2(strRet, strOffset);
						}
					}
				}
			}
		}
		else if (ch == '<')
		{
			WizFormatXML_ADDINDENT2(strRet, strOffset);
			//
			strOffset += '\t';
		}
		strRet.AppendChar(strXML[i]);
	}
	//
	strXML = strRet;
	//
	return TRUE;
}

CString WizGetUserName()
{
	TCHAR szUserName[MAX_PATH] = {0};
	DWORD dwLen = MAX_PATH;
	GetUserName(szUserName, &dwLen);
	//
	return CString(szUserName);
}
BOOL WizIsSystem()
{
	return 0 == WizGetUserName().CompareNoCase(_T("SYSTEM"));
}


#define ACCESS_READ         0x01
#define ACCESS_WRITE        0x02

BOOL WizIsAdmin()
{
	HANDLE hToken;
	DWORD dwStatus;
	DWORD dwAccessMask;
	DWORD dwAccessDesired;
	DWORD dwACLSize;
	DWORD dwStructureSize = sizeof(PRIVILEGE_SET);
	PACL pACL = NULL;
	PSID psidAdmin = NULL;
	BOOL bReturn = FALSE;
	PRIVILEGE_SET ps;
	GENERIC_MAPPING GenericMapping;
	PSECURITY_DESCRIPTOR psdAdmin = NULL;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;

	__try {
		// AccessCheck() requires an impersonation token.
		ImpersonateSelf(SecurityImpersonation);
		if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE,  &hToken)) 
		{
			if (GetLastError() != ERROR_NO_TOKEN)
				__leave;
			// If the thread does not have an access token, we'll 
			// examine the access token associated with the process.
			if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
				__leave;
		}
		if (!AllocateAndInitializeSid(&SystemSidAuthority, 2, 
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &psidAdmin))
			__leave;
		psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (psdAdmin == NULL)
			__leave;
		if (!InitializeSecurityDescriptor(psdAdmin,
			SECURITY_DESCRIPTOR_REVISION))
			__leave;

		// Compute size needed for the ACL.
		dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
			GetLengthSid(psidAdmin) - sizeof(DWORD);
		// Allocate memory for ACL.
		pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
		if (pACL == NULL)
			__leave;
		// Initialize the new ACL.
		if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))
			__leave;
		dwAccessMask= ACCESS_READ | ACCESS_WRITE;

		// Add the access-allowed ACE to the DACL.
		if (!AddAccessAllowedAce(pACL, ACL_REVISION2,
			dwAccessMask, psidAdmin))
			__leave;
		// Set our DACL to the SD.
		if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
			__leave;
		// AccessCheck is sensitive about what is in the SD; set
		// the group and owner.
		SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
		SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);
		if (!IsValidSecurityDescriptor(psdAdmin))
			__leave;
		dwAccessDesired = ACCESS_READ;
		// 
		// Initialize GenericMapping structure even though we
		// won't be using generic rights.
		// 
		GenericMapping.GenericRead = ACCESS_READ;
		GenericMapping.GenericWrite = ACCESS_WRITE;
		GenericMapping.GenericExecute = 0;
		GenericMapping.GenericAll = ACCESS_READ | ACCESS_WRITE;
		if (!AccessCheck(psdAdmin, hToken, dwAccessDesired, 
			&GenericMapping, &ps, &dwStructureSize, &dwStatus, 
			&bReturn)) 
		{
			//printf("AccessCheck() failed with error %lu\n", GetLastError());
			__leave;
		}
		RevertToSelf();

	} __finally 
	{
		// Cleanup 
		if (pACL) LocalFree(pACL);
		if (psdAdmin) LocalFree(psdAdmin); 
		if (psidAdmin) FreeSid(psidAdmin);
	}
	return bReturn;
}

BOOL WizStringSimpleMatch(LPCTSTR lpszSubString, LPCTSTR lpszText)
{
	CString strSub(lpszSubString);
	if (strSub.IsEmpty())
		return FALSE;
	//
	BOOL bLeft = (strSub[0] == '%');
	BOOL bRight = (strSub[strSub.GetLength() - 1] == '%');
	//
	strSub.Trim('%');
	//
	if (bLeft && bRight)
	{
		return NULL != WizStrStrI_Ptr(lpszText, strSub);
	}
	else if (bLeft)
	{
		int nSubLength = strSub.GetLength();
		int nTextLength = (int)_tcslen(lpszText);
		if (nTextLength < nSubLength)
			return FALSE;
		//
		return 0 == _tcsicmp(strSub, lpszText + (nTextLength - nSubLength));
	}
	else if (bRight)
	{
		return 0 == _tcsnicmp(lpszText, strSub, strSub.GetLength());
	}
	else
	{
		return 0 == strSub.CompareNoCase(lpszText);
	}
}

BOOL WizStringSimpleFind(LPCTSTR lpszSubString, LPCTSTR lpszText)
{
	CString strSub(lpszSubString);
	if (strSub.IsEmpty())
		return FALSE;
	//
	if (-1 == strSub.Find('*'))
	{
		return NULL != WizStrStrI_Ptr(lpszText, lpszSubString);
	}
	//
	CWizStdStringArray arrayPart;
	WizSplitTextToArray(strSub, '*', arrayPart);
	if (arrayPart.empty())
		return FALSE;
	//
	CWizStdStringArray::const_iterator it = arrayPart.begin();
	int nIndex = 0;
	//
	LPCTSTR p = lpszText;
	while (p && *p)
	{
		if (it >= arrayPart.end())
			break;
		//
		CString strPart = *it;
		//
		LPCTSTR pFind = WizStrStrI_Ptr(p, strPart);
		if (!pFind)
			return FALSE;
		//
		p += strPart.GetLength();
		//
		it++;
	}
	//
	return TRUE;
}



HANDLE WizCreateProcess(LPCTSTR lpszExeFileName, LPCTSTR lpszParam, BOOL bShowWindow)
{
	PROCESS_INFORMATION pInfo;
	STARTUPINFO         sInfo;
	memset(&pInfo, 0, sizeof(PROCESS_INFORMATION));
	memset(&sInfo, 0, sizeof(STARTUPINFO));
	//
	sInfo.cb              = sizeof(STARTUPINFO);
	sInfo.dwFlags         = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow     = bShowWindow ? SW_SHOW : SW_HIDE;
	//
	TCHAR szCommandLine[4096] = {0};
	_tcscpy_s(szCommandLine, 4096, WizFormatString2(_T("\"%1\" %2"), lpszExeFileName, lpszParam));
	//
	if (!CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo))
		return NULL;
	//
	return pInfo.hProcess;
}

DWORD WizCreateProcessAndWait(LPCTSTR lpszExeFileName, LPCTSTR lpszParam, BOOL bShowWindow)
{
	HANDLE handle = WizCreateProcess(lpszExeFileName, lpszParam, bShowWindow);
	if (!handle)
		return FALSE;
	//
	WaitForSingleObject(handle, INFINITE);
	//
	DWORD dwExitCode = 0;
	GetExitCodeProcess(handle, &dwExitCode);
	return dwExitCode;
}

HINSTANCE WizShellExecuteReturnInstance(HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd)
{
	SHELLEXECUTEINFO info;
	ZeroMemory(&info, sizeof(SHELLEXECUTEINFO));
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	info.hwnd = hwnd;
	info.lpVerb = lpOperation;
	info.lpFile = lpFile;
	info.lpParameters = lpParameters;
	info.lpDirectory = lpDirectory;
	info.nShow = nShowCmd;
	//
	if (!ShellExecuteEx(&info))
		return NULL;
	//
	return (HINSTANCE)info.hProcess;
}

DWORD WizShellExecuteAndWait(HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd)
{
	HINSTANCE hInstance = WizShellExecuteReturnInstance(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	if (!hInstance)
		return 0xFF;
	//
	WaitForSingleObject(hInstance, INFINITE);
	//
	DWORD dwExitCode = 0;
	if (!GetExitCodeProcess(hInstance, &dwExitCode))
		return 0xFF;
	//
	return dwExitCode;
}

BOOL InitGdiCharsetCodePageMap(CGdiCharsetCodePageMap& mapCharset)
{
	CComPtr<IMultiLanguage> spMultiLanguage;
	if (FAILED(spMultiLanguage.CoCreateInstance(CLSID_CMultiLanguage)))
		return FALSE;
	//
	if (!spMultiLanguage)
		return FALSE;
	//
	CComPtr<IEnumCodePage> spEnumCodePage;
	if (FAILED(spMultiLanguage->EnumCodePages(MIMECONTF_BROWSER, &spEnumCodePage)))
		return FALSE;
	//
	if (!spEnumCodePage)
		return FALSE;
	//
	while (TRUE)
	{
		MIMECPINFO cpinfo;
		ZeroMemory(&cpinfo, sizeof(MIMECPINFO));
		//
		ULONG nCount = 0;
		if (S_OK != spEnumCodePage->Next(1, &cpinfo, &nCount))
			break;
		//
		if (mapCharset.find(cpinfo.bGDICharset) == mapCharset.end())
		{
			mapCharset[cpinfo.bGDICharset] = cpinfo.uiCodePage;
		}
	}

	return TRUE;
}

UINT GetCodePageByGdiCharset(BYTE nCharset)
{
	if (0 == nCharset)
		return GetACP();
	//
	static CGdiCharsetCodePageMap mapCharset;
	if (mapCharset.empty())
	{
		if (!InitGdiCharsetCodePageMap(mapCharset))
			return 0;
	}
	//
	CGdiCharsetCodePageMap::const_iterator it = mapCharset.find(nCharset);
	if (it != mapCharset.end())
	{
		return it->second;
	}
	//
	return 0;
}



LPCTSTR _tcstrimleft(LPCTSTR lpsz)
{
	if (!lpsz)
		return NULL;
	LPCTSTR p = lpsz;
	while (isspace(*p))
	{
		p++;
	}
	return p;
}
int _tcstomon(LPCTSTR lpsz)
{
	int nMon = -1;
	const LPCTSTR arrayMon[12] = 
	{
		_T("Jan"), _T("Feb"), _T("Mar"), _T("Apr"), 
		_T("May"), _T("Jun"), _T("Jul"), _T("Aug"), 
		_T("Sep"), _T("Oct"), _T("Nov"), _T("Dec")
	};
	for (int i = 0; i < 12; i++)
	{
		if (_tcsnicmp(lpsz, arrayMon[i], 3) == 0)
			return i + 1;
	}
	return -1;
}

int _tcstotimezone(LPCTSTR lpsz)
{
	if (!lpsz)
		return -1;

	int zone = 0;
	TCHAR ch = *lpsz;
	switch (ch)
	{
    case _T('-'):
    case _T('+'):
		zone = _ttoi(lpsz);
		zone = zone % 10000 / 1000 * 600 
			+ zone % 1000 / 100 * 60 
			+ zone % 100 / 10 * 10 
			+ zone % 10;
		break;
    case _T('U'):
    case _T('u'):
        if (lpsz[1] == 'T' || lpsz[1] == 't') 
		{
            zone = 0;
        }
        else 
		{
            /* Military time zone */
            zone = 480;
        }
        break;
    case _T('G'):
    case _T('g'):
        if ((lpsz[1] == 'M' || lpsz[1] == 'm')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = 0;
        }
        else 
		{
            /* Military time zone */
            zone = -420;
        }
        break;
    case _T('E'):
    case _T('e'):
        if ((lpsz[1] == 'S' || lpsz[1] == 's')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -300;
        }
        else if ((lpsz[1] == 'D' || lpsz[1] == 'd')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -240;
        }
        else 
		{
            /* Military time zone */
            zone = -300;
        }
        break;
    case _T('C'):
    case _T('c'):
        if ((lpsz[1] == 'S' || lpsz[1] == 's')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -360;
        }
        else if ((lpsz[1] == 'D' || lpsz[1] == 'd')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -300;
        }
        else
		{
            /* Military time zone */
            zone = -180;
        }
        break;
    case _T('M'):
    case _T('m'):
        if ((lpsz[1] == 'S' || lpsz[1] == 's')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -420;
        }
        else if ((lpsz[1] == 'D' || lpsz[1] == 'd')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -360;
        }
        else 
		{
            /* Military time zone */
            zone = -720;
        }
        break;
    case _T('P'):
    case _T('p'):
        if ((lpsz[1] == 'S' || lpsz[1] == 's')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -480;
        }
        else if ((lpsz[1] == 'D' || lpsz[1] == 'd')
            && (lpsz[2] == 'T' || lpsz[2] == 't')) 
		{
            zone = -420;
        }
        else 
		{
            /* Military time zone */
            zone = 180;
        }
        break;
    case _T('Z'):
        /* Military time zone */
        zone = 0;
        break;
    default:
        /* Military time zone */
        if (_T('A') <= ch && ch <= _T('I')) 
		{
            zone = _T('A') - 1 - ch;
        }
        else if (_T('K') <= ch && ch <= _T('M')) 
		{
            zone = _T('A') - ch;
        }
        else if (_T('N') <= ch && ch <= _T('Y')) 
		{
            zone = ch - _T('N') + 1;
        }
		else
		{
			zone = 0;
		}
		break;
	}
	return zone;
}

COleDateTime WizTimeFromRfc822(LPCTSTR lpsz, BOOL* pbSucceeded /*= NULL*/)
{
	if (pbSucceeded)
	{
		*pbSucceeded = FALSE;
	}
	COleDateTime tDefailt = WizGetCurrentTime();
	if (!lpsz)
		return tDefailt;

	LPCTSTR p = lpsz;
	while (*p)
	{
		if (*p >= _T('0') && (*p) <= _T('9'))
			break;
		p++;
	}
	if (!(*p))
		return tDefailt;
	int nDay = _ttoi(p);
	if (nDay < 1 || nDay > 31)
		return tDefailt;

	p = _tcschr(p, _T(' '));
	if (!p)
		return tDefailt;
	p = _tcstrimleft(p);
	int nMon = _tcstomon(p);
	if (nMon < 1 || nMon > 12)
		return tDefailt;

	p = _tcschr(p, _T(' '));
	if (!p)
		return tDefailt;
	p = _tcstrimleft(p);
	int nYear = _ttoi(p);
	if (nYear < 1970 || nYear > 2050)
		return tDefailt;

	p = _tcschr(p, _T(' '));
	if (!p)
		return tDefailt;
	p = _tcstrimleft(p);
	int nHour = _ttoi(p);
	if (nHour < 0 || nHour > 23)
		return tDefailt;

	p = _tcschr(p, _T(':'));
	if (!p)
		return tDefailt;
	p++;
	p = _tcstrimleft(p);
	int nMin = _ttoi(p);
	if (nMin < 0 || nMin > 59)
		return tDefailt;
	
	p = _tcschr(p, _T(':'));
	if (!p)
		return tDefailt;
	p++;
	p = _tcstrimleft(p);
	int nSec = _ttoi(p);
	if (nSec < 0 || nSec > 59)
		return tDefailt;

	int nTimeZone = 0;
	p = _tcschr(p, _T(' '));
	if (p)
	{
		p = _tcstrimleft(p);
		nTimeZone = _tcstotimezone(p);
	}

	TIME_ZONE_INFORMATION tzi;
	memset(&tzi, 0, sizeof(tzi));
	GetTimeZoneInformation(&tzi);
	DWORD dwTimeZoneId = GetTimeZoneInformation(&tzi);
	int ltzBias = 0;
	switch (dwTimeZoneId)
	{
	case TIME_ZONE_ID_STANDARD:
		ltzBias = tzi.Bias + tzi.StandardBias;
		break;

	case TIME_ZONE_ID_DAYLIGHT:
		ltzBias = tzi.Bias + tzi.DaylightBias;
		break;

	case TIME_ZONE_ID_UNKNOWN:
	default:
		ltzBias = tzi.Bias;
		break;
	}
	nTimeZone = nTimeZone + ltzBias;

	COleDateTime t(nYear, nMon, nDay, nHour, nMin, nSec);
	COleDateTimeSpan ts(nTimeZone / 60 / 24, nTimeZone / 60, nTimeZone % 60, 0);
	COleDateTime t2 = t - ts;

	if (pbSucceeded)
	{
		*pbSucceeded = TRUE;
	}
	return t2;
}

inline bool IsSepChar(TCHAR ch)
{
	return ch == _T('-') || ch == _T('/') || ch == ('\\') || ch == _T(':') || ch == _T(' ');
}

inline bool IsZero(LPCTSTR lpsz)
{
	//ASSERT(lpsz);
	while (*lpsz)
	{
		if (*lpsz != _T('0'))
			return FALSE;
		lpsz++;
	}
	return TRUE;
}

int ScanTimeNumber(CString& str)
{
	str.TrimLeft();
	while (!str.IsEmpty() && IsSepChar(str[0]))
	{
		str.Delete(0, 1);
	}
	if (str.IsEmpty())
		return -1;
	str.TrimLeft();
	//
	CString strNumber;
	int nPos = str.FindOneOf(_T("-/\\: "));
	if (nPos == -1)
	{
		strNumber = str;
		str.Empty();
	}
	else
	{
		strNumber = str.Left(nPos);
		str.Delete(0, nPos);
	}
	//
	int nNumber = _tcstomon(strNumber);
	if (nNumber != -1)
	{
		str.Delete(0, 3);
		return nNumber;
	}
	//
	if (IsZero(strNumber))
		return 0;
	nNumber = _ttoi(strNumber);
	return nNumber == 0 ? -1 : nNumber;;
}

COleDateTime LocalStrToTime(LPCTSTR lpsz, BOOL* pbSucceeded /*= NULL*/)
{
	if (pbSucceeded)
	{
		*pbSucceeded = FALSE;
	}
	COleDateTime tDefault = WizGetCurrentTime();
	//
	CString str(lpsz);
	//
	int nNumber1 = ScanTimeNumber(str);
	if (nNumber1 == -1)
		return tDefault;
	int nNumber2 = ScanTimeNumber(str);
	if (nNumber2 == -1)
		return tDefault;
	int nNumber3 = ScanTimeNumber(str);
	if (nNumber3 == -1)
		return tDefault;
	int nNumber4 = ScanTimeNumber(str);
	if (nNumber4 == -1)
		return tDefault;
	int nNumber5 = ScanTimeNumber(str);
	if (nNumber5 == -1)
		return tDefault;
	int nNumber6 = ScanTimeNumber(str);
	//
	int nAddedHour = 0;
	if (StrStrI(str, _T("PM")))
		nAddedHour = 12;
	//
	DWORD dwType = 0;
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILDATE, (LPTSTR)&dwType, sizeof(DWORD));
	//
	int nYear = 0;
	int nMon = 0;
	int nDay = 0;
	int nHour = nNumber4;
	int nMin = nNumber5;
	int nSec = nNumber6;
	//
	if (dwType == 0)
	{
		nMon = nNumber1;
		nDay = nNumber2;
		nYear = nNumber3;
	}
	else if (dwType == 1)
	{
		nDay = nNumber1;
		nMon = nNumber2;
		nYear = nNumber3;
	}
	else if (dwType == 2)
	{
		nYear = nNumber1;
		nMon = nNumber2;
		nDay = nNumber3;
	}
	//
	if (nYear <= 0)
		return tDefault;
	//
	if (nYear < 50)
		nYear += 2000;
	if (nYear >= 50 && nYear <= 100)
		nYear += 1900;
	//
	if (nYear < 1950 || nYear > 2050)
		return tDefault;
	//
	if (nMon <= 0 || nMon > 12)
		return tDefault;
	//
	if (nDay <= 0 || nDay > 31)
		return tDefault;
	//
	if (nHour < 0 || nHour >= 24)
		return tDefault;
	if (nMin < 0 || nMin >= 60)
		return tDefault;
	if (nSec < 0 || nSec >= 60)
		return tDefault;
	//
	try
	{
		COleDateTime t(nYear, nMon, nDay, nHour, nMin, nSec);
		//
		if (pbSucceeded)
		{
			*pbSucceeded = TRUE;
		}
		//
		return t;
	}
	catch (...)
	{
		return tDefault;
	}
	return tDefault;
}

COleDateTime WizTimeFromStr(LPCTSTR lpsz, BOOL* pbSucceeded /*= NULL*/)
{
	BOOL bRet = FALSE;
	COleDateTime t = WizTimeFromRfc822(lpsz, &bRet);
	if (!bRet)
	{
		t = LocalStrToTime(lpsz, &bRet);
	}
	//
	if (pbSucceeded)
	{
		*pbSucceeded = bRet;
	}
	//
	if (!bRet)
	{
		return WizGetCurrentTime();
	}
	//
	return t;
}

inline size_t WizSetRfc822Time(__out_ecount_part_z_opt(dwLen, return) LPSTR szDate, __in size_t dwLen) throw()
{
	// Max buffer size required(including NULL) - 38
	const size_t s_dwMaxBufferLen = 38;
	if (szDate == NULL)
	{
		return s_dwMaxBufferLen;
	}
	
	if (dwLen < 38)
	{
		return 0;
	}
	static const LPCSTR s_months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
							   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	static const LPCSTR s_days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	SYSTEMTIME st;
	DWORD      dwTimeZoneId=TIME_ZONE_ID_UNKNOWN;
	CHAR       cDiff;
	LONG       ltzBias=0;
	LONG       ltzHour;
	LONG       ltzMinute;
	TIME_ZONE_INFORMATION tzi;

	GetLocalTime(&st);

	// Gets TIME_ZONE_INFORMATION
	memset(&tzi, 0, sizeof(tzi));
	dwTimeZoneId = GetTimeZoneInformation(&tzi);
	switch (dwTimeZoneId)
	{
	case TIME_ZONE_ID_STANDARD:
		ltzBias = tzi.Bias + tzi.StandardBias;
		break;

	case TIME_ZONE_ID_DAYLIGHT:
		ltzBias = tzi.Bias + tzi.DaylightBias;
		break;

	case TIME_ZONE_ID_UNKNOWN:
	default:
		ltzBias = tzi.Bias;
		break;
	}

	// Set Hour Minutes and time zone dif
	ltzHour = ltzBias / 60;
	ltzMinute = ltzBias % 60;
	cDiff = (ltzHour < 0) ? '+' : '-';

	int nDay = (st.wDayOfWeek > 6) ? 0 : st.wDayOfWeek;
	int nMonth = st.wMonth = (WORD)((st.wMonth < 1 || st.wMonth > 12) ? 0 : st.wMonth - 1);


	// Constructs RFC 822 format: "ddd, dd mmm yyyy hh:mm:ss +/- hhmm\0"
	sprintf_s(szDate, dwLen, "Date: %3s, %d %3s %4d %02d:%02d:%02d %c%02d%02d",
					  s_days[nDay],                            // "ddd"
					  st.wDay,                                 // "dd"
					  s_months[nMonth],                        // "mmm"
					  st.wYear,                                // "yyyy"
					  st.wHour,                                // "hh"
					  st.wMinute,                              // "mm"
					  st.wSecond,                              // "ss"
					  cDiff,                                   // "+" / "-"
					  abs (ltzHour),                           // "hh"
					  abs (ltzMinute));                        // "mm"
	return s_dwMaxBufferLen;
}


CString WizRfc822Time()
{
	CHAR szBuffer[MAX_PATH] = {0};
	WizSetRfc822Time(szBuffer, MAX_PATH);
	//
	return CString(szBuffer);
}




BOOL WizURLADDownload(LPCTSTR lpszProduct, LPCTSTR lpszRelatedURL, LPCTSTR lpszADXMLFileName, LPCTSTR lpszVersion)
{
	CStringA strURLA = WizBSTR2STR(CP_UTF8, lpszRelatedURL);
	char szEncodedURL[4096] = {0};
	DWORD dwEncodeURLSize = 4096;
	//
	AtlEscapeUrl(strURLA, szEncodedURL, &dwEncodeURLSize, dwEncodeURLSize, 0);
	//
	CString strLanguage = WizIntToStr(GetUserDefaultLCID());
	CString strVersion(lpszVersion);
	if (strVersion.IsEmpty())
	{
		strVersion = WizGetFileVersion(WizGetAppFileName());
	}
	CString strProduct(lpszProduct);
	strProduct.MakeLower();
	//
	CString strCheckURL = WizWebSiteVisitGetURL(strProduct, strLanguage, strVersion, _T("ad"), _T(""));
	strCheckURL += (_T("&url=") + CString(szEncodedURL) + _T("&t=") + WizIntToStr(GetTickCount()));
	//
	CWizURL url(strCheckURL);
	CString strTempFileName = url.ToFileName(TRUE);
	if (strTempFileName.IsEmpty())
	{
#ifdef _DEBUG
		TOLOG1(_T("Failed to download %1"), url);
#endif
		return FALSE;
	}
	//
	if (!PathFileExists(strTempFileName))
		return FALSE;
	//
	if (FAILED(WizCopyFile(strTempFileName, lpszADXMLFileName, FALSE)))
		return FALSE;
	//
	DeleteFile(strTempFileName);
	//
	return TRUE;
}

BOOL WizURLADLoad(CWizXMLNode& nodeAds, CWizHTMLLinkDataArray& arrayAD)
{
	std::vector<CWizXMLNode> arrayNodes;
	if (!nodeAds.GetAllChildNodes(arrayNodes))
		return FALSE;
	//
	for (std::vector<CWizXMLNode>::iterator it = arrayNodes.begin();
		it != arrayNodes.end();
		it++)
	{
		WIZHTMLLINKDATA data;
		data.strText = it->GetAttributeTextDef(_T("Title"), _T(""));
		data.strURL = it->GetAttributeTextDef(_T("URL"), _T(""));
		//
		if (data.strText.IsEmpty()
			|| data.strURL.IsEmpty())
			continue;
		//
		arrayAD.push_back(data);
	}
	//
	return TRUE;
}


BOOL WizURLADLoad(LPCTSTR lpszADXMLFileName, CWizHTMLLinkDataArray& arrayAD)
{
	CString strXmlText;
	if (!WizLoadUnicodeTextFromFile(lpszADXMLFileName, strXmlText))
		return FALSE;
	//
	CWizXMLDocument doc;
	if (!doc.LoadXML(CComBSTR(strXmlText)))
		return FALSE;
	//
	CWizXMLNode nodeAds;
	if (!doc.FindChildNode(_T("Ads"), nodeAds))
		return FALSE;
	//
	return WizURLADLoad(nodeAds, arrayAD);
}

BOOL WizURLADLoadOneAD(LPCTSTR lpszADXMLFileName, WIZHTMLLINKDATA& data)
{
	CWizHTMLLinkDataArray arrayAD;
	if (!WizURLADLoad(lpszADXMLFileName, arrayAD))
		return FALSE;
	//
	if (arrayAD.empty())
		return FALSE;
	//
	data = arrayAD[GetTickCount() % arrayAD.size()];
	//
	return TRUE;
}

BOOL WizURLADDownloadToXmlFile(LPCTSTR lpszProduct, LPCTSTR lpszRelatedURL, LPCTSTR lpszXmlFileName, LPCTSTR lpszRootNodeName, LPCTSTR lpszVersion)
{
	CString strTempFileName = WizGlobal()->GetTempPath() + WizIntToStr(GetTickCount()) + _T(".xml");
	if (!WizURLADDownload(lpszProduct, lpszRelatedURL, strTempFileName, lpszVersion))
		return FALSE;
	//
	CWizHTMLLinkDataArray arrayAD;
	if (!WizURLADLoad(strTempFileName, arrayAD))
		return FALSE;
	//
	CWizXMLDocument doc;
	if (PathFileExists(lpszXmlFileName))
	{
		doc.LoadFromFile(lpszXmlFileName);
	}
	//
	CWizXMLNode nodeRoot;
	if (!doc.GetChildNode(lpszRootNodeName, nodeRoot))
		return FALSE;
	//
	CWizXMLNode nodeAds;
	if (!nodeRoot.GetChildNode(_T("Ads"), nodeAds))
		return FALSE;
	//
	nodeAds.DeleteAllChild();
	//
	for (CWizHTMLLinkDataArray::const_iterator it = arrayAD.begin();
		it != arrayAD.end();
		it++)
	{
		CWizXMLNode nodeAd;
		if (!nodeAds.AppendChild(_T("Ad"), nodeAd))
			return FALSE;
		//
		nodeAd.SetAttributeText(_T("Title"), it->strText);
		nodeAd.SetAttributeText(_T("URL"), it->strURL);
	}
	//
	return doc.ToUnicodeFile(lpszXmlFileName);
}

BOOL WizURLADLoadFromXmlFile(LPCTSTR lpszADXMLFileName, CWizHTMLLinkDataArray& arrayAD)
{
	CString strXmlText;
	if (!WizLoadUnicodeTextFromFile(lpszADXMLFileName, strXmlText))
		return FALSE;
	//
	CWizXMLDocument doc;
	if (!doc.LoadXML(CComBSTR(strXmlText)))
		return FALSE;
	//
	CString strRootNodeName = WizXMLDocumentGetRootNodeName(doc);
	//
	CWizXMLNode nodeRoot;
	if (!doc.FindChildNode(strRootNodeName, nodeRoot))
		return FALSE;
	//
	CWizXMLNode nodeAds;
	if (!nodeRoot.FindChildNode(_T("Ads"), nodeAds))
		return FALSE;
	//
	return WizURLADLoad(nodeAds, arrayAD);
}

BOOL WizURLADLoadOneADFromXmlFile(LPCTSTR lpszADXMLFileName, WIZHTMLLINKDATA& data)
{
	CWizHTMLLinkDataArray arrayAD;
	if (!WizURLADLoadFromXmlFile(lpszADXMLFileName, arrayAD))
		return FALSE;
	//
	if (arrayAD.empty())
		return FALSE;
	//
	data = arrayAD[GetTickCount() % arrayAD.size()];
	//
	return TRUE;
}


BOOL WizURLGetClicked(LPCTSTR lpszADIniFileName, LPCTSTR lpszURL)
{
	return WizIniReadBoolDef(lpszADIniFileName, _T("Clicked"), WizMd5StringNoSpace(lpszURL), FALSE);
}
void WizURLSetClicked(LPCTSTR lpszADIniFileName, LPCTSTR lpszURL, BOOL bClicked)
{
	WizIniWriteInt(lpszADIniFileName, _T("Clicked"), WizMd5StringNoSpace(lpszURL), bClicked ? 1 : 0);
}
//
BOOL WizURLADLoadFromXmlFileEx(LPCTSTR lpszADXMLFileName, LPCTSTR lpszCategory, LPCTSTR lpszADIniFileName, CWizHTMLLinkDataArray& arrayAD)
{
	CWizHTMLLinkDataArray arrayADTemp;
	if (!WizURLADLoadFromXmlFile(lpszADXMLFileName, arrayADTemp))
		return FALSE;
	//
	CString strCategory(lpszCategory);
	if (strCategory.IsEmpty())
	{
		arrayAD.assign(arrayADTemp.begin(), arrayADTemp.end());
		return TRUE;
	}
	//
	strCategory = WizFormatString1(_T("[%1]"), strCategory);
	//
	for (CWizHTMLLinkDataArray::const_iterator it = arrayADTemp.begin();
		it != arrayADTemp.end();
		it++)
	{
		if (!WizURLGetClicked(lpszADIniFileName, it->strURL))
		{
			if (it->strText.GetLength() >= strCategory.GetLength()
				&& 0 == _tcsnicmp(it->strText, strCategory, strCategory.GetLength()))
			{
				arrayAD.push_back(*it);
			}
		}
	}
	//
	return TRUE;
}

BOOL WizURLADLoadOneADFromXmlFileEx(LPCTSTR lpszADXMLFileName, LPCTSTR lpszCategory, LPCTSTR lpszADIniFileName, WIZHTMLLINKDATA& data)
{
	CWizHTMLLinkDataArray arrayAD;
	if (!WizURLADLoadFromXmlFileEx(lpszADXMLFileName, lpszCategory, lpszADIniFileName, arrayAD))
		return FALSE;
	//
	if (arrayAD.empty())
		return FALSE;
	//
	data = arrayAD[GetTickCount() % arrayAD.size()];
	//
	return TRUE;
}

CWizClipboardFormats WizEnumClipboardFormat(HWND hWnd)
{
	CWizClipboardFormats formats;
	//
	if (OpenClipboard(hWnd))
	{
		UINT uFormat = EnumClipboardFormats(0);
		while (uFormat) 
		{
			formats.insert(uFormat);
#ifdef _DEBUG
			/*
			TCHAR szFormatName[MAX_PATH] = {0};
			GetClipboardFormatName(uFormat, szFormatName, MAX_PATH);
			ATLTRACE(szFormatName);
			ATLTRACE(_T("\n"));
			*/
#endif
			//
			uFormat = EnumClipboardFormats(uFormat);
		}
		//
		CloseClipboard();
	}
	//
	return formats;
}



CString WizXMLDocumentGetRootNodeName(CWizXMLDocument& doc)
{
	std::vector<CWizXMLNode> arrayNodes;
	doc.GetAllChildNodes(arrayNodes);
	//
	for (std::vector<CWizXMLNode>::iterator it = arrayNodes.begin();
		it != arrayNodes.end();
		it++)
	{
		CWizXMLNode& node = *it;
		if (0 == node.GetType().CompareNoCase(_T("element")))
		{
			return node.GetName();
		}
	}
	//
	return CString();

}

CString WizXMLDocumentGetRootNodeName(LPCTSTR lpszFileName)
{
	CWizXMLDocument doc;
	if (!doc.LoadFromFile(lpszFileName))
		return CString();
	//
	return WizXMLDocumentGetRootNodeName(doc);	
}


CString WizVariantToString(const VARIANT& v)
{
	if (v.vt == VT_BSTR)
		return CString(v.bstrVal);
	else
		return WizIntToStr(v.lVal);
}

int WizVariantToInt(const VARIANT& v, int nDef)
{
	CString str = WizVariantToString(v);
	if (str.IsEmpty())
		return nDef;
	//
	int nVal = _ttoi(str);
	if (WizIntToStr(nVal) == str)
		return nVal;
	//
	return nDef;
}



BOOL WizClipboardHGlobalToHTML(HGLOBAL hGlobal, CStringW& strHtml)
{
	ATLASSERT(hGlobal);
	//
	BOOL bRet = FALSE;
	//
	SIZE_T nSize = GlobalSize(hGlobal);
	LPCSTR pData = (LPCSTR)GlobalLock(hGlobal); 
	if (pData)
	{
		char* pBuffer = new char[nSize + 1];
		if (pBuffer)
		{
			ZeroMemory(pBuffer, nSize + 1);
			strncpy_s(pBuffer, nSize + 1, pData, nSize);
			//
			bRet = WizConvertStringFromUTF8(pBuffer, strHtml);
			//
			delete [] pBuffer;
		}
		GlobalUnlock(hGlobal);
	}
	//
	return bRet;
}

BOOL WizClipboardHGlobalToRTF(HGLOBAL hGlobal, CStringA& strRTF)
{
	ATLASSERT(hGlobal);
	//
	BOOL bRet = FALSE;
	//
	SIZE_T nSize = GlobalSize(hGlobal);
	LPCSTR pData = (LPCSTR)GlobalLock(hGlobal); 
	if (pData)
	{
		char* pBuffer = new char[nSize + 1];
		if (pBuffer)
		{
			ZeroMemory(pBuffer, nSize + 1);
			strncpy_s(pBuffer, nSize + 1, pData, nSize);
			//
			strRTF = pBuffer;
			//
			delete [] pBuffer;
			//
			bRet = TRUE;
		}
		GlobalUnlock(hGlobal);
	}
	//
	return bRet;
}


BOOL WizGetClipboardHTML(CString& strHTML)
{
	if (!IsClipboardFormatAvailable(CF_HTML_FORMAT()))
		return FALSE;
	//
	if (!OpenClipboard(::GetForegroundWindow())) 
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	HGLOBAL hGlobal = GetClipboardData(CF_HTML_FORMAT());
	if (hGlobal)
	{
		bRet = WizClipboardHGlobalToHTML(hGlobal, strHTML);
	}
	//
	CloseClipboard(); 
	//
	return bRet;
}
BOOL WizGetClipboardRTF(CStringA& strRTF)
{
	if (!IsClipboardFormatAvailable(CF_RTF_FORMAT()))
		return FALSE;
	//
	if (!OpenClipboard(::GetForegroundWindow())) 
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	HGLOBAL hGlobal = GetClipboardData(CF_RTF_FORMAT());
	if (hGlobal)
	{
		bRet = WizClipboardHGlobalToRTF(hGlobal, strRTF);
	}
	else
	{
		MessageBox(NULL, WizGetLastErrorMessage(), 0, 0);
	}
	//
	CloseClipboard(); 
	//
	return bRet;
}

BOOL WizHTMLToClipboardHTML(LPCTSTR lpszHTML, LPCTSTR lpszURL, CStringA& strClipboardHTML)
{
	CStringA strHTML;
	if (!WizConvertStringToUTF8(lpszHTML, strHTML))
		return FALSE;
	//
	if (-1 == WizStrStrI_PosA(strHTML, "<!--StartFrag"))
	{
		strHTML = "<!--StartFragment -->\r\n" 
			+ strHTML
			+ "\r\n"
			+ "<!--EndFragment-->\r\n";
	}
	if (-1 == WizStrStrI_PosA(strHTML, "<html>"))
	{
		strHTML = "<html><body>\r\n"
			+ strHTML
			+ "\r\n"
			+ "</body></html>";
	}
	//
	CStringA strURL;
	if (!WizConvertStringToUTF8(lpszURL, strURL))
		return FALSE;
	//
    // Create temporary buffer for HTML header...
	int nBufferLen = strURL.GetLength() + 1024 + strHTML.GetLength();
	char *buf = strClipboardHTML.GetBuffer(nBufferLen);
    if(!buf) 
		return FALSE;

    // Create a template string for the HTML header...
    sprintf_s(buf, nBufferLen, 
        "Version:1.0\r\n"
        "StartHTML:00000000\r\n"
        "EndHTML:00000000\r\n"
        "StartFragment:00000000\r\n"
        "EndFragment:00000000\r\n"
		"SourceURL:%s\r\n"
		"\r\n",
		strURL);
    // Append the HTML...
    strcat_s(buf, nBufferLen, strHTML);
    strcat_s(buf, nBufferLen, "\r\n");

    // Now go back, calculate all the lengths, and write out the
    // necessary header information. Note, wsprintf() truncates the
    // string when you overwrite it so you follow up with code to replace
    // the 0 appended at the end with a '\r'...
    char *ptr = strstr(buf, "StartHTML");
    sprintf_s(ptr + 10, 9, "%08u", strstr(buf, "<html>") - buf);
    *(ptr + 10 + 8) = '\r';

    ptr = strstr(buf, "EndHTML");
    sprintf_s(ptr + 8, 9, "%08u", strlen(buf));
    *(ptr + 8 + 8) = '\r';

    ptr = strstr(buf, "StartFragment");
    sprintf_s(ptr + 14, 9, "%08u", strstr(buf, "<!--StartFrag") - buf);
    *(ptr + 14 + 8) = '\r';

    ptr = strstr(buf, "EndFragment");
    sprintf_s(ptr + 12, 9, "%08u", strstr(buf, "<!--EndFrag") - buf);
    *(ptr + 12 + 8) = '\r';
	//
	strClipboardHTML = buf;
	//
	//
	return TRUE;
}


BOOL WizHTMLGetBodyFromClipboardText(const CString& strText, CString& strHTML, CString& strURL)
{
	LPCTSTR lpszMark = _T("SourceURL:");
	int nURLBegin = strText.Find(lpszMark);
	if (nURLBegin != -1)
	{
		nURLBegin += int(_tcslen(lpszMark));
		int nURLEnd = strText.Find(_T('\n'), nURLBegin);
		if (nURLEnd != -1)
		{
			strURL = strText.Mid(nURLBegin, nURLEnd - nURLBegin);
			strURL.Trim();
		}
	}
	//
	int nHTMLBegin = strText.Find(_T('<'));
	if (nHTMLBegin == -1)
		return FALSE;
	//
	strHTML = strText.Right(strText.GetLength() - nHTMLBegin);
	//
	return TRUE;
}

BOOL WizGetClipboardInfo(WIZCLIPBOARDINFO& info, HWND hwnd)
{
	if (IsClipboardFormatAvailable(CF_HTML_FORMAT()))
	{
		info.bHasHTML = TRUE;
	}
	//
	if (IsClipboardFormatAvailable(CF_RTF_FORMAT()))
	{
		info.bHasRTF = TRUE;
	}
	//
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		info.bHasText = TRUE;
	}
	//
	if (IsClipboardFormatAvailable(CF_BITMAP))
	{
		info.bHasImage = TRUE;
	}
	//
	if (IsClipboardFormatAvailable(CF_HDROP))
	{
		info.bHasFiles = TRUE;
	}
	//
	if (!hwnd)
	{
		hwnd = ::GetForegroundWindow();
	}

	CWizClipboardFormats formats = WizEnumClipboardFormat(hwnd);
	CString str;
	for (CWizClipboardFormats::const_iterator it = formats.begin();
		it != formats.end();
		it++)
	{
		str += WizIntToStr(*it) + _T(";");
	}
	//
	if (info.bHasText)
	{
		str += info.GetPlainText();
	}
	//
	if (info.bHasFiles)
	{
		CWizStdStringArray arrayFile;
		info.GetFiles(arrayFile);
		//
		for (CWizStdStringArray::const_iterator it = arrayFile.begin();
			it != arrayFile.end();
			it++)
		{
			str += *it + _T(";");
		}
	}
	//
	info.strClipboardInfoMD5 = WizMd5StringNoSpace(str);
	//
	return TRUE;
}
CString WizClipboardBitmapToFileName()
{
	if (!IsClipboardFormatAvailable(CF_BITMAP))
		return CString();
	//
	CString strFileName = WizGlobal()->GetTempPath() + WizIntToStr(GetTickCount()) + _T("_WizClipboardBitmapToFileName.bmp");
	if (!WizClipboardSaveToImageFile(strFileName))
		return CString();
	//
	return strFileName;
}



BOOL WizAutoCompressPngFile(LPCTSTR lpszFileName)
{
	if (0 != WizExtractFileExt(lpszFileName).CompareNoCase(_T(".png")))
		return FALSE;
	//
	CString strExeFileName = WizGetAppPath() + _T("pngout.exe");
	if (!PathFileExists(strExeFileName))
		return FALSE;
	//
	CString strParams = WizFormatString1(_T("\"%1\""), lpszFileName);
	return ::WizShellExecuteAndWait(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
}


BOOL WizClipboardSaveToImageFile(LPCTSTR lpszFileName)
{
	if (!IsClipboardFormatAvailable(CF_BITMAP))
	{
#ifdef _DEBUG
		WizMessageBox(_T("No bitmap in clipboard!"));
#endif
		TOLOG(_T("No bitmap in clipboard!"));
		return FALSE;
	}
	//
	HWND arrayHWND[3] = {::GetDesktopWindow(), ::GetFocus(), ::GetForegroundWindow()};
	for (int i = 0; i < 3; i++)
	{
		HWND hwnd = arrayHWND[i];
		if (!OpenClipboard(hwnd))
			continue;
		//
		BOOL bRet = FALSE;
		//
		HBITMAP hBmp = (HBITMAP)GetClipboardData(CF_BITMAP);
		if (hBmp)
		{
			bRet = WizClipboardHGlobalSaveToImageFile(hBmp, lpszFileName);
		}
		//
		CloseClipboard(); 
		//
		if (bRet)
		{
			WizAutoCompressPngFile(lpszFileName);
			//
			return TRUE;
		}
	}
	//
#ifdef _DEBUG
	WizMessageBox(WizGetLastErrorMessage());
#endif
	return FALSE;
}


HRESULT WizSaveJPG(HBITMAP hBmp, LPCTSTR lpszJpgFileName, int quality = 90)
{
	Gdiplus::GdiplusStartupInput startinput;
	ZeroMemory(&startinput, sizeof(Gdiplus::GdiplusStartupInput));
	startinput.GdiplusVersion = 1;
	//
	ULONG_PTR lToken = 0;
	if (Gdiplus::Ok != Gdiplus::GdiplusStartup(&lToken, &startinput, NULL))
		return E_FAIL;

	HRESULT hr = E_FAIL;
	//
	{
		//release bm first
		Gdiplus::Bitmap bm( hBmp, NULL);
		if (Gdiplus::Ok == bm.GetLastStatus())
		{
			GUID tJpgEncoder;
			CLSIDFromString( L"{557CF401-1A04-11D3-9A73-0000F81EF32E}", &tJpgEncoder);
			//
			Gdiplus::EncoderParameters tParams;
			tParams.Count = 1;
			tParams.Parameter[0].Guid = Gdiplus::EncoderQuality;
			tParams.Parameter[0].NumberOfValues = 1;
			tParams.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong ;
			tParams.Parameter[0].Value = (void*)(&quality);

			if (Gdiplus::Ok == bm.Save(lpszJpgFileName, &tJpgEncoder, &tParams))
			{
				hr = S_OK;
			}
		}
	}
	//
	Gdiplus::GdiplusShutdown(lToken);
	//
	return hr;
}


BOOL WizClipboardHGlobalSaveToImageFile(HANDLE hData, LPCTSTR lpszFileName)
{
	if (!hData)
		return FALSE;
	//
	BOOL bRet = FALSE;
	//
	CString strExt = WizExtractFileExt(lpszFileName);
	if (0 == strExt.CompareNoCase(_T(".jpg")))
	{
		bRet = SUCCEEDED(WizSaveJPG((HBITMAP)hData, lpszFileName, 90));
	}
	else
	{
		CImage img;
		img.Attach((HBITMAP)hData);
		//
		bRet = SUCCEEDED(img.Save(lpszFileName));
		//
		img .Detach();
		//
		if (bRet)
		{
			WizAutoCompressPngFile(lpszFileName);
		}
	}
	//
	return bRet;
}

BOOL WizClipboardAutoSaveToImage(LPCTSTR lpszPath, CString& strImageFileName, HWND hWnd /*= NULL*/)
{
	if (!IsWindow(hWnd))
		hWnd = ::GetFocus();
	//
	if (!OpenClipboard(hWnd)) 
	{
		if (!OpenClipboard(::GetForegroundWindow()))
		{
#ifdef _DEBUG
			WizMessageBox(_T("Failed to open clipboard!"));
#endif
			TOLOG(_T("Failed to open clipboard!"));
			return FALSE;
		}
	}
	//
	HBITMAP hBmp = (HBITMAP)GetClipboardData(CF_BITMAP);
	if (hBmp)
	{
		CString strImageFileTitle = WizIntToStr(GetTickCount());
		CString strPath(lpszPath);
		if (strPath.IsEmpty())
		{
			strPath = WizGlobal()->GetTempPath();
		}
		//
		WizPathAddBackslash(strPath);
		WizEnsurePathExists(strPath);
		//
		CString strJpgFileName = strPath + strImageFileTitle + _T(".jpg");
		CString strPngFileName = strPath + strImageFileTitle + _T(".png");
		//
		WizClipboardHGlobalSaveToImageFile(hBmp, strJpgFileName);
		WizClipboardHGlobalSaveToImageFile(hBmp, strPngFileName);
		//
		int nJpgSize = (int)WizGetFileSize(strJpgFileName);
		int nPngSize = (int)WizGetFileSize(strPngFileName);
		//
		CString strResultFileName;
		//
		if (nJpgSize > 0 && nPngSize > 0)
		{
			if (nJpgSize >= nPngSize)
			{
				strResultFileName = strPngFileName;
			}
			else
			{
				double fRate = double(nPngSize) / nJpgSize;
				if (fRate > 1.2)
				{
					strResultFileName = strJpgFileName;
				}
				else
				{
					strResultFileName = strPngFileName;
				}
			}
		}
		else if (nPngSize > 0)
		{
			strResultFileName = strPngFileName;
		}
		else if (nJpgSize > 0)
		{
			strResultFileName = strJpgFileName;
		}
		else
		{
			strResultFileName = strPath + strImageFileTitle + _T(".bmp");
			WizClipboardHGlobalSaveToImageFile(hBmp, strResultFileName);
		}
		//
		strImageFileName = strResultFileName;
	}
	CloseClipboard();
	//
	return PathFileExists(strImageFileName);
}


BOOL WizClipboardGetFilesByHDrop(HDROP hDrop, CWizStdStringArray& arrayFile)
{
	UINT nFiles = ::DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); 
	for(UINT i = 0; i < nFiles; i++)
	{
		TCHAR szFileName[MAX_PATH] = {0};
		::DragQueryFile(hDrop, i, szFileName, MAX_PATH);
		//
		ATLTRACE(_T("%s\n"), szFileName);
		arrayFile.push_back(szFileName);
	}
	//
	return TRUE;
}


WIZCLIPBOARDINFO::WIZCLIPBOARDINFO()
{
	bHasText = FALSE;
	bHasImage = FALSE;
	bHasHTML = FALSE;
	bHasRTF = FALSE;
	bHasFiles = FALSE;
}
//
CString WIZCLIPBOARDINFO::GetPlainText()
{
	CString strText;
	WizGetClipboardText(strText);
	return strText;
}
CString WIZCLIPBOARDINFO::GetHTMLText(CString& strURL)
{
	CString strHTML;
	if (WizGetClipboardHTML(strHTML))
	{
		CString strHTMLText;
		WizHTMLGetBodyFromClipboardText(strHTML, strHTMLText, strURL);
		//
		return strHTMLText;
	}
	//
	return CString();
}
CStringA WIZCLIPBOARDINFO::GetRTFText()
{
	CStringA strRTFText;
	//
	WizGetClipboardRTF(strRTFText);
	//
	return strRTFText;
}
CString WIZCLIPBOARDINFO::GetBitmapFileName()
{
	return WizClipboardBitmapToFileName();
}
//

//
BOOL WIZCLIPBOARDINFO::GetFiles(CWizStdStringArray& arrayFile)
{
	if (!OpenClipboard(::GetFocus())) 
	{
		if (!OpenClipboard(::GetForegroundWindow()))
		{
#ifdef _DEBUG
			WizMessageBox(_T("Failed to open clipboard!"));
#endif
			TOLOG(_T("Failed to open clipboard!"));
			return FALSE;
		}
	}
	//
	BOOL bRet = FALSE;
	//
	HDROP hDrop = (HDROP)GetClipboardData(CF_HDROP);
	if (hDrop)
	{
		bRet = WizClipboardGetFilesByHDrop(hDrop, arrayFile);
	}
	else
	{
#ifdef _DEBUG
		WizMessageBox(WizGetLastErrorMessage());
#endif
	}
	//
	CloseClipboard(); 
	//
	return bRet;
}



HWND WizGetPopupWindow(HWND hwnd)
{
	while (hwnd)
	{
		if (GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD)
		{
		}
		else
		{
			return hwnd;
		}
		hwnd = GetParent(hwnd);
	}
	return NULL;
}

void WizCheckWindowTopMost(HWND hwnd)
{
	if (!::IsWindow(hwnd))
		return;
	//
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if (0 == (dwStyle & WS_VISIBLE))
		return;
	//
	CRect rc;
	GetWindowRect(hwnd, &rc);
	//
	HWND hwndTop = WizGetPopupWindow(::WindowFromPoint(rc.CenterPoint()));
	if (!hwndTop)
		return;
	//
	if (hwndTop == hwnd)
		return;
	//
	DWORD dwTopID = 0;
	DWORD dwID = 0;
	GetWindowThreadProcessId (hwndTop, &dwTopID);
	GetWindowThreadProcessId(hwnd, &dwID);
	if (dwTopID == dwID)
		return;
	//
	DWORD dwExStyle = GetWindowLong(hwndTop, GWL_EXSTYLE);
	if (0 == (dwExStyle & WS_EX_TOPMOST))
	{
		DEBUG_TOLOG(_T("Reset window z-order: top most"));
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}


BOOL WizDayOnce(LPCTSTR lpszKey, LPCTSTR lpszName)
{
	CString strOldTime = WizRegReadStringDef(HKEY_CURRENT_USER, lpszKey, lpszName, NULL);
	//
	CTime tCurrentTime = CTime::GetCurrentTime();
	//
	__int64 nCurrentTime = tCurrentTime.GetTime();
	//
	WizRegWriteString(HKEY_CURRENT_USER, lpszKey, lpszName, WizInt64ToStr(nCurrentTime));
	//
	if (strOldTime.IsEmpty())
		return TRUE;
	//
	CTime tOldTime(_ttoi64(strOldTime));
	//
	if (tCurrentTime.GetYear() == tOldTime.GetYear()
		&& tCurrentTime.GetMonth() == tOldTime.GetMonth()
		&& tCurrentTime.GetDay() == tOldTime.GetDay())
		return FALSE;
	//
	return TRUE;
}


BOOL WizIsAutoRun(LPCTSTR lpszName)
{
	CString strKey = CString(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	//
	return WizRegValueExists(HKEY_CURRENT_USER, strKey, lpszName)
		|| WizRegValueExists(HKEY_LOCAL_MACHINE, strKey, lpszName);
}

BOOL WizEnableAutoRun(HKEY hRootKey, LPCTSTR lpszName, LPCTSTR lpszExeFileName)
{
	CString strKey = CString(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	//
	return WizRegWriteString(hRootKey, strKey, lpszName, lpszExeFileName);
}

BOOL WizEnableAutoRun(HKEY hRootKey, LPCTSTR lpszName, LPCTSTR lpszExeFileName, LPCTSTR lpszParams)
{
	CString strKey = CString(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	//
	CString strCommandLine = WizFormatString2(_T("\"%1\" %2"), lpszExeFileName, lpszParams);
	//
	return WizRegWriteString(hRootKey, strKey, lpszName, strCommandLine);
}

BOOL WizDisableAutoRun(LPCTSTR lpszName)
{
	CString strKey = CString(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	//
	WizRegDeleteValue(HKEY_CURRENT_USER, strKey, lpszName);
	WizRegDeleteValue(HKEY_LOCAL_MACHINE, strKey, lpszName);
	//
	return TRUE;
}

HWND WizGetOwnerPopupWindow(HWND hwnd)
{
	while (hwnd)
	{
		if (GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD)
		{
		}
		else
		{
			return hwnd;
		}
		hwnd = GetParent(hwnd);
	}
	return NULL;
}



BOOL WizCreateSingleton(HANDLE& hMutex, LPCTSTR lpszName)
{
	ATLASSERT(!hMutex);
	//
    hMutex = ::CreateMutex(NULL, TRUE, lpszName);
    if (hMutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
    {
		CloseHandle(hMutex);
        hMutex = NULL;
        return FALSE;
    }
    return TRUE;
}

void WizCloseSingleton(HANDLE hMutex)
{
	ATLASSERT(hMutex);
	//
	CloseHandle(hMutex);
}



CWizSingletonApp::CWizSingletonApp()
{
	m_hMutex = NULL;
}
CWizSingletonApp::~CWizSingletonApp()
{
	Close();
}
BOOL CWizSingletonApp::Create(LPCTSTR lpszName)
{
	ATLASSERT(!m_hMutex);
	//
	return WizCreateSingleton(m_hMutex, lpszName);
}
BOOL CWizSingletonApp::Close()
{
	if (m_hMutex)
	{
		WizCloseSingleton(m_hMutex);
		m_hMutex = NULL;
		//
		return TRUE;
	}
	//
	return FALSE;
}
CWizSingletonApp* CWizSingletonApp::GetSingletonApp()
{
	static CWizSingletonApp sa;
	return &sa;
}

BOOL CWizSingletonApp::InitApp(LPCTSTR lpszName)
{
	CWizSingletonApp* psa = GetSingletonApp();
	return psa->Create(lpszName);
}
BOOL CWizSingletonApp::CloseApp()
{
	CWizSingletonApp* psa = GetSingletonApp();
	return psa->Close();
}

CWizSingletonAppEx::CWizSingletonAppEx()
{
}
BOOL CWizSingletonAppEx::CreateEx(LPCTSTR lpszName)
{
	return Create(lpszName);
}





#if defined __ATLGDI_H__ || defined __AFX_H__

void WizFlashWindow(HWND hWnd)
{
    if (!hWnd)
        return;
    HDC hDC = GetDC(NULL);
    if (!hDC)
		return;
	//
	int nDC = SaveDC(hDC);
	//
	SetROP2(hDC, R2_NOTXORPEN);
	//
	CPen pen;
	pen.CreatePen(PS_SOLID, 6, RGB(255, 0, 0));
	SelectObject(hDC, (HPEN)pen);
	//
    RECT rcWindow;
    GetWindowRect(hWnd, &rcWindow);
	//
	for (int nFlashCount = 0; nFlashCount < 4; nFlashCount++)
	{
		Rectangle(hDC, rcWindow.left + 3, rcWindow.top + 3, rcWindow.right - 3, rcWindow.bottom - 3);
		Sleep(100);
	}
	//
	RestoreDC(hDC, nDC);
	ReleaseDC(NULL, hDC);
}

void WizFlashWindow(HWND hWnd, const RECT& rc, int nPenWidth)
{
    if (!hWnd)
        return;
	//
    HDC hDC = GetDC(NULL);
    if (!hDC)
		return;
	//
	ClientToScreen(hWnd, (LPPOINT)&rc);
	ClientToScreen(hWnd, ((LPPOINT)&rc) + 1);
	//
	CRect rcWindow;
	GetWindowRect(hWnd, &rcWindow);
	//
	int nDC = SaveDC(hDC);
	//
    SetROP2(hDC, R2_NOTXORPEN);
	//
	CPen pen;
	pen.CreatePen(PS_SOLID, nPenWidth, RGB(255, 0, 0));
	SelectObject(hDC, (HPEN)pen);
	//
	CRgn rgn;
	if (rgn.CreateRectRgn(rcWindow.left, rcWindow.top, rcWindow.right, rcWindow.bottom))
	{
		SelectClipRgn(hDC, rgn);
	}
	//
	for (int nFlashCount = 0; nFlashCount < 4; nFlashCount++)
	{
		Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		Sleep(100);
	}
	//
	RestoreDC(hDC, nDC);
    ReleaseDC(NULL, hDC);
}

#endif //__ATLGDI_H__


CWizAtlDataObject::CWizAtlDataObject(IDataObject* pData)
	: m_pData(pData)
{
	ATLASSERT(m_pData);
}
CWizAtlDataObject::~CWizAtlDataObject()
{
}
IDataObject* CWizAtlDataObject::GetData()
{
	return m_pData;
}
BOOL CWizAtlDataObject::FindFormat(IDataObject* pData, UINT nFormat)
{
	if (!pData)
		return FALSE;
	//
	CComPtr<IEnumFORMATETC> spEnum;
	HRESULT hr = pData->EnumFormatEtc(DATADIR_GET, &spEnum);
	if (FAILED(hr))
		return FALSE;
	//
	FORMATETC etc;
	while (S_OK == spEnum->Next(1, &etc, NULL))
	{
		if (etc.cfFormat == nFormat)
			return TRUE;
	}
	//
	return FALSE;
}
BOOL CWizAtlDataObject::IsFormatAvaliable(UINT nFormat)
{
	if (!m_pData)
		return FALSE;
	//
	CComPtr<IEnumFORMATETC> spEnum;
	HRESULT hr = m_pData->EnumFormatEtc(DATADIR_GET, &spEnum);
	if (FAILED(hr))
		return FALSE;
	//
	FORMATETC etc;
	while (S_OK == spEnum->Next(1, &etc, NULL))
	{
		if (etc.cfFormat == nFormat)
			return TRUE;
	}
	//
	return FALSE;
}
//
HANDLE CWizAtlDataObject::GetData(UINT nFormat)
{
	if (!m_pData)
		return NULL;
	//
	FORMATETC format;
	ZeroMemory(&format, sizeof(FORMATETC));
	//
	format.cfFormat = nFormat;
	format.ptd = NULL;
	format.dwAspect = DVASPECT_CONTENT;
	format.lindex = -1;
	format.tymed = TYMED_HGLOBAL;
	//
	STGMEDIUM stg;
	memset(&stg, 0, sizeof(STGMEDIUM));
	//
	HRESULT hr = m_pData->GetData(&format, &stg);
	if (FAILED(hr))
		return NULL;
	//
	return stg.hGlobal;
}
//
BOOL CWizAtlDataObject::GetHtml(CString& strHtml, CString& strURL)
{
	HANDLE hData = GetData(CF_HTML_FORMAT());
	if (!hData)
		return FALSE;
	//
	CString strClipboardHTML;
	if (!WizClipboardHGlobalToHTML(hData, strClipboardHTML))
		return FALSE;
	//
	return WizHTMLGetBodyFromClipboardText(strClipboardHTML, strHtml, strURL);
}
BOOL CWizAtlDataObject::GetRtf(CStringA& strRTF)
{
	HANDLE hData = GetData(CF_RTF_FORMAT());
	if (!hData)
		return FALSE;
	//
	return WizClipboardHGlobalToRTF(hData, strRTF);
}
BOOL CWizAtlDataObject::GetBitmapFileName(LPCTSTR lpszFileName)
{
	HANDLE hData = GetData(CF_BITMAP);
	if (!hData)
		return FALSE;
	//
	return WizClipboardHGlobalSaveToImageFile(hData, lpszFileName);
}
BOOL CWizAtlDataObject::GetUnicodeText(CString& strText)
{
	BOOL bRet = FALSE;
	//
	HANDLE hData = GetData(CF_UNICODETEXT);
	if (!hData)
		return FALSE;
	//
	return WizClipboardHGlobalToText(hData, strText, TRUE);
}
BOOL CWizAtlDataObject::GetAnsiText(CString& strText)
{
	HANDLE hData = GetData(CF_TEXT);
	if (!hData)
		return FALSE;
	//
	return WizClipboardHGlobalToText(hData, strText, FALSE);
}
BOOL CWizAtlDataObject::GetText(CString& strText)
{
	if (GetUnicodeText(strText))
		return TRUE;
	//
	return GetAnsiText(strText);
}
BOOL CWizAtlDataObject::GetFiles(CWizStdStringArray& arrayFile)
{
	HDROP hDrop = (HDROP)GetData(CF_HDROP);
	if (hDrop)
	{
		return WizClipboardGetFilesByHDrop(hDrop, arrayFile);
	}
	return FALSE;
}



CString WizTextGetFirstLine(LPCTSTR lpszText)
{
	CWizStdStringArray arrayLines;
	WizSplitTextToArray(lpszText, '\n', arrayLines);
	//
	WizStringArrayEraseEmptyLine(arrayLines);
	//
	if (arrayLines.empty())
		return CString();
	//
	CString strLine = arrayLines[0];
	strLine.Trim();
	//
	return strLine;
}
