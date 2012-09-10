#include "stdafx.h"
#include "WizHtmlBase.h"


#include <tchar.h>
#include <shlwapi.h>


#include <algorithm>

#include <set>

intptr_t GetTagLen(LPCTSTR lpszTag)
{
	LPCTSTR p = lpszTag;
	//
	BOOL bInQuot = FALSE;
	TCHAR chQuot = 0;
	//
	while (*p)
	{
		TCHAR ch = *p;
		if (bInQuot)
		{
			if (ch == chQuot)
			{
				bInQuot = FALSE;
				chQuot = 0;
			}
		}
		else
		{
			if (ch == '>')
			{
				return p - lpszTag + 1;
				break;
			}
			else if (ch == '\'' || ch == '"')
			{
				bInQuot = TRUE;
				chQuot = ch;
			}
		}
		p++;
	}
	//
	return _tcslen(lpszTag);
}

intptr_t GetValuePos(LPCTSTR lpszTag, LPCTSTR lpszValueName)
{
	size_t nTagLen = GetTagLen(lpszTag);
	size_t nNameLen = _tcslen(lpszValueName);
	if (nTagLen < nNameLen)
		return -1;
	//
	LPCTSTR p = lpszTag;
	LPCTSTR pEnd = p + (nTagLen - nNameLen);

	BOOL bInQuot = FALSE;
	TCHAR chQuot = 0;

	while (p < pEnd)
	{
		TCHAR ch = *p;
		//
		if (bInQuot)
		{
			if (ch == chQuot)
			{
				bInQuot = FALSE;
				chQuot = 0;
			}
		}
		else
		{
			if (ch == '>')
			{
				return -1;
			}
			else if (ch == '\'' || ch == '"')
			{
				bInQuot = TRUE;
				chQuot = ch;
			}
			else
			{
				if (_tcsnicmp(p, lpszValueName, nNameLen) == 0)
				{
					TCHAR chAfterName = *(p + nNameLen);
					TCHAR chBeforeName = *(p - 1);
					//
					if (WizIsSpaceChar(chBeforeName) 
						&& (chAfterName == _T('=') || WizIsSpaceChar(chAfterName)))
					{
						return p - lpszTag;
					}
				}
			}
		}
		//
		p++;
	}
	return -1;
}

LPCTSTR FindEndOfQuotInLineScriptSource(LPCTSTR p, TCHAR chQuot)
{
	LPCTSTR pOld = p;
	TCHAR chOld = 0;
	while (*p)
	{
		TCHAR ch = *p;
		if (WizHTMLIsQuot(ch))
		{
			if (ch == chQuot)
			{
				if (chOld != _T('\\'))
					return p;
			}
			else
			{
				TCHAR chSubQuot = *p;
				p++;
				p = WizHTMLFindEndOfQuotInBlockScriptSource(p, chSubQuot);
			}
		}
		chOld = *p;
		p++;
	}
	return pOld;
}

LPCTSTR FindEndOfValueNotQuot(LPCTSTR p)
{
	LPCTSTR pEnd = NULL;
	LPCTSTR p1 = _tcschr(p, _T(' '));
	LPCTSTR p2 = _tcschr(p, _T('>'));
	if (p1 && !p2)
	{
		pEnd = p1;
	}
	else if (!p1 && p2)
	{
		pEnd = p2;
	}
	else if (p1 && p2)
	{
		pEnd = min(p1, p2);
	}
	return pEnd;
}
void WizHTMLMoveStr(LPTSTR psz, ptrdiff_t nStep)
{
	if (nStep == 0)
	{
		return;
	}
	else if (nStep > 0)
	{
		size_t nLen = _tcslen(psz);
		LPTSTR pEnd = psz + nLen - 1;
		while (pEnd >= psz)
		{
			*(pEnd + nStep) = *pEnd;
			pEnd--;
		}
		psz[nLen + nStep] = 0;
	}
	else
	{
		LPTSTR pBegin = psz;
		while (*pBegin)
		{
			*(pBegin + nStep) = *pBegin;
			pBegin++;
		}
		*(pBegin + nStep) = 0;
	}
}


BOOL WizHTMLDeleteTagValue(LPTSTR pszTag, LPCTSTR lpszValueName)
{
	//begin
	intptr_t nPos = GetValuePos(pszTag, lpszValueName);
	if (nPos == -1)
		return FALSE;
	LPTSTR pBegin = pszTag + nPos;
	//end
	LPTSTR pEnd = _tcschr(pBegin, _T('='));
	if (!pEnd)
		return FALSE;
	pEnd++;
	TCHAR chEnd = *pEnd;
	pEnd++;
	if (WizHTMLIsQuot(chEnd))
	{
		pEnd = (LPTSTR)FindEndOfQuotInLineScriptSource(pEnd, chEnd);
	}
	else
	{
		pEnd = (LPTSTR)FindEndOfValueNotQuot(pEnd);
	}
	if (!*pEnd)
		return FALSE;
	if (WizHTMLIsQuot(chEnd))
	{
		pEnd++;
	}
	ptrdiff_t nOldLen = pEnd - pBegin;

	WizHTMLMoveStr(pEnd, - nOldLen);

	return TRUE;
}


void WizHTMLDeleteStr(LPTSTR p, int nPos, int nCount)
{
	p += (nPos + nCount);
	WizHTMLMoveStr(p, - nCount);
}
void WizHTMLInsertStr(LPTSTR p, int nPos, LPCTSTR lpszText)
{
	size_t nLen = _tcslen(lpszText);
	if (0 == nLen)
		return;
	p += nPos;
	WizHTMLMoveStr(p, nLen);
	memcpy(p, lpszText, nLen * sizeof(TCHAR));
}

void WizHTMLReplaceString(LPTSTR pszText, LPCTSTR lpszFrom, LPCTSTR lpszTo)
{
	if (!WizStrStrI_Ptr(pszText, lpszFrom))
		return;
	//
	size_t nFromLen = _tcslen(lpszFrom);
	if (nFromLen == 0)
		return;
	size_t nToLen = _tcslen(lpszTo);
	//
	static CWizStrBufferAlloc ba(1024 * 4);
	//
	size_t nLen = _tcslen(pszText);
	if (nFromLen < nToLen)
	{
		ba.SetNewSize(size_t(nLen * (double(nToLen) / nFromLen)) + 1);
	}
	else
	{
		ba.SetNewSize(nLen + 1);
	}
	//
	LPTSTR pNewBuffer = ba.GetBuffer();
	LPCTSTR pBegin = pszText;
	LPTSTR p = pNewBuffer;
	while (*pBegin)
	{
		if (_tcsnicmp(pBegin, lpszFrom, nFromLen) == 0)
		{
			StrCpy(p, lpszTo);
			p += nToLen;
			pBegin += nFromLen;
		}
		else
		{
			*p = *pBegin;
			p++;
			pBegin++;
		}
	}
	//
	*p = '\0';
	//
	StrCpy(pszText, pNewBuffer);
}
void WizHTMLReplaceString(LPTSTR pszText, TCHAR chFrom, TCHAR chTo)
{
	while (*pszText)
	{
		if (*pszText == chFrom)
		{
			*pszText = chTo;
		}
		pszText++;
	}
}


void WizHTMLDecodeInplace(LPTSTR lpszHTML)
{
	WizHTMLReplaceString(lpszHTML, _T("&lt;"), _T("<"));
	WizHTMLReplaceString(lpszHTML, _T("&gt;"), _T(">"));
	WizHTMLReplaceString(lpszHTML, _T("&nbsp;"), _T(" "));
	WizHTMLReplaceString(lpszHTML, _T("&apos;"), _T("'"));
	WizHTMLReplaceString(lpszHTML, _T("&quot;"), _T("\""));
	WizHTMLReplaceString(lpszHTML, _T("&mdash;"), _T("¡ª"));
	WizHTMLReplaceString(lpszHTML, _T("&middot;"), _T("¡¤"));
	WizHTMLReplaceString(lpszHTML, _T("&amp;"), _T("&"));
	
}

void WizHTMLEncodeInplace(LPTSTR lpszHTML)
{
	WizHTMLReplaceString(lpszHTML, _T("&"), _T("&amp;"));
    WizHTMLReplaceString(lpszHTML, _T("<"), _T("&lt;"));
    WizHTMLReplaceString(lpszHTML, _T(">"), _T("&gt;"));
    WizHTMLReplaceString(lpszHTML, _T("\""), _T("&quot;"));
	WizHTMLReplaceString(lpszHTML, _T(" "), _T("&nbsp;"));
	WizHTMLReplaceString(lpszHTML, _T("'"), _T("&apos;"));
}
void WizHTMLEncodeInplaceForTagValue(LPTSTR lpszHTML, TCHAR ch)
{
	ATLASSERT('"' == ch || '\'' == ch);
	//
	if ('"' == ch)
	{
		WizHTMLReplaceString(lpszHTML, _T("\""), _T("&quot;"));
	}
	else if ('\'' == ch)
	{
		WizHTMLReplaceString(lpszHTML, _T("'"), _T("&apos;"));
	}
	else
	{
		ATLASSERT(FALSE);
	}
}

void WizHTMLDecodeInplace(CString& strText)
{
	strText.Replace(_T("&lt;"), _T("<"));
	strText.Replace(_T("&gt;"), _T(">"));
	strText.Replace(_T("&nbsp;"), _T(" "));
	strText.Replace(_T("&apos;"), _T("'"));
	strText.Replace(_T("&quot;"), _T("\""));
	strText.Replace(_T("&amp;"), _T("&"));
	strText.Replace(_T("&mdash;"), _T("¡ª"));
	strText.Replace(_T("&middot;"), _T("¡¤"));
}



BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, LPTSTR pszValue, size_t nSize)
{
	intptr_t nPos = GetValuePos(lpszTag, lpszValueName);
	if (nPos == -1)
		return FALSE;
	*pszValue = 0;

	nPos += _tcslen(lpszValueName);
    lpszTag += nPos;
    lpszTag = WizTrimLeft(lpszTag);
    if ((!*lpszTag) || *lpszTag != _T('='))
        return FALSE;
	//
    lpszTag++;
    if (!*lpszTag)
        return FALSE;
	//
	if(WizIsSpaceChar(*lpszTag))
	{
	    lpszTag = WizTrimLeft(lpszTag);
		TCHAR ch = *lpszTag;
		if (!ch || (ch != _T('"') && ch != _T('\'')))
		{
			*pszValue = 0;
			return TRUE;
		}
	}
	TCHAR cEnd = _T(' ');
    if (*lpszTag == _T('"') || *lpszTag == _T('\''))
    {
        cEnd = *lpszTag;
        lpszTag++;
    }
    if (!*lpszTag)
        return FALSE;
	lpszTag = WizTrimLeft(lpszTag);
    LPCTSTR pEnd = lpszTag;
    if (cEnd == _T(' '))
    {
        while (*pEnd)
        {
            if (WizIsSpaceChar(*pEnd) || *pEnd == _T('>'))
                break;
            pEnd++;
        }
    }
    else
    {
        while (*pEnd)
        {
            if (*pEnd == cEnd)
                break;
            pEnd++;
        }
    }
    if (!*pEnd)
        return FALSE;
    if (pEnd == lpszTag)
    {
        *pszValue = 0;
        return TRUE;
    }
    pEnd--;

    while (pEnd > lpszTag && WizIsSpaceChar(*pEnd))
        pEnd--;
	//
	size_t nValueLen = pEnd - lpszTag + 1;
	if (nSize <= nValueLen)
		return FALSE;
	//
    _tcsncpy_s(pszValue, nSize, lpszTag, nValueLen);
	pszValue[nValueLen] = 0;
	//
	WizHTMLDecodeInplace(pszValue);
	//
	return TRUE;
}

#ifdef __CSTRINGT_H__
BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, CString& strValue)
{
	TCHAR szValue[4096] = {0};
	if (!WizHTMLGetTagValue(lpszTag, lpszValueName, szValue, 4096))
		return FALSE;
	strValue = CString(szValue);
	return TRUE;
}
#endif

//
BOOL WizHTMLGetTagName(LPCTSTR lpszTag, LPTSTR lpszName, size_t nSize)
{
	if (!lpszTag)
		return FALSE;
	if (!*lpszTag)
		return FALSE;
	if (*lpszTag != _T('<'))
		return FALSE;
	//
	LPCTSTR lpszBegin = lpszTag;
	lpszBegin++;
	//
	lpszBegin = WizTrimLeft(lpszBegin);
	//
	if (!*lpszBegin)
		return FALSE;
	//
	if(*lpszBegin == _T('/'))
		lpszBegin++;
	lpszBegin = WizTrimLeft(lpszBegin);
	if (!*lpszBegin)
		return FALSE;
	//
	LPCTSTR lpszEnd = lpszBegin;
	while (*lpszEnd)
	{
		TCHAR ch = *lpszEnd;
		if (ch == _T('>'))
			break;
		if (ch == _T('/') && *(lpszEnd + 1) == _T('>'))
			break;
		if (WizIsSpaceChar(ch))
			break;
		lpszEnd++;
	}
	//
	size_t nLen = lpszEnd - lpszBegin;
	if (nLen >= nSize)
	{
		//´íÎóµÄTag±ê¼Ç
		//ºöÂÔ´íÎó¼ÌÐø
		nLen = nSize - 1;
	}
	//
	_tcsncat_s(lpszName, nSize, lpszBegin, nLen);
	lpszName[nLen] = _T('\0');
	//
	if (!(*lpszName))
		return FALSE;
	//
	return TRUE;
}

UINT WizHTMLGetTagStyle(LPCTSTR lpszTag)
{
	UINT nStyle = 0;
	//
	if (!lpszTag)
		return nStyle;
	if (!*lpszTag)
		return nStyle;
	if (*lpszTag != _T('<'))
		return nStyle;
	//
	LPCTSTR lpszBegin = lpszTag;
	lpszBegin++;
	//
	lpszBegin = WizTrimLeft(lpszBegin);
	//
	if (!*lpszBegin)
		return nStyle;
	//
	if(*lpszBegin == _T('/'))
		nStyle |= wizHTMLTagStyleEnd;
	//
	return nStyle;
}


BOOL WizHTMLSetTagValue(LPTSTR pszTag, size_t nSize, LPCTSTR lpszValueName, LPCTSTR lpszValue)
{
	static CWizStrBufferAlloc ba1(1024 * 4);
	static CWizStrBufferAlloc ba2(1024 * 4);

	size_t nTagLen = _tcslen(pszTag) + _tcslen(lpszValue) + _tcslen(lpszValueName);
	//
	size_t nBufferLen = nTagLen * 2;
	ba1.SetNewSize(nBufferLen);
	ba2.SetNewSize(nBufferLen);

	LPTSTR pszBuffer1 = ba1.GetBuffer();
	LPTSTR pszBuffer2 = ba2.GetBuffer();

	size_t nValueNameLen = _tcslen(lpszValueName);

	LPTSTR pNewValue = pszBuffer1;
	_tcscpy_s(pNewValue, nBufferLen, lpszValue);
	//
	LPTSTR pOldValue = pszBuffer2;
	if (!WizHTMLGetTagValue(pszTag, lpszValueName, pOldValue, nBufferLen))
	{
		LPTSTR pszEnd = _tcschr(pszTag, _T('>'));
		if (!pszEnd)
			return FALSE;
		//
		if (*(pszEnd - 1) == '/')
			pszEnd--;
		//
		WizHTMLEncodeInplaceForTagValue(pNewValue, '"');
		
		LPTSTR pInsertStr = pszBuffer2;
		_stprintf_s(pInsertStr, nBufferLen, _T(" %s=\"%s\" "), lpszValueName, pNewValue);
		//
		WizHTMLInsertStr(pszEnd, 0, pInsertStr);
		//
		return TRUE;
	}
	else
	{
		//begin
		intptr_t nPos = GetValuePos(pszTag, lpszValueName);
		//
		LPTSTR pBegin = pszTag + nPos + nValueNameLen;
		//
		pBegin = _tcschr(pBegin, _T('='));
		if (!pBegin)
			return FALSE;
		pBegin++;
		//end
		TCHAR chEnd = *pBegin;
		if (chEnd != _T('"') && chEnd != _T('\''))
			chEnd = _T(' ');
		else
			pBegin++;
		//
		LPTSTR pEnd = pBegin;
		if (chEnd == _T(' '))
		{
			while (*pEnd && !WizIsSpaceChar(*pEnd) && *pEnd != _T('>'))
			{
				pEnd++;
			}
		}
		else
		{
			while (*pEnd && *pEnd != chEnd)
			{
				pEnd++;
			}
		}
		if (!*pEnd)
			return FALSE;
		pEnd--;
		//
		if (chEnd == _T(' '))
		{
			WizHTMLEncodeInplaceForTagValue(pNewValue, '"');
			//
			WizHTMLMoveStr(pNewValue, 1);
			pNewValue[0] =_T( '"');
			_tcscat_s(pNewValue, nBufferLen, _T("\""));
		}
		else
		{
			WizHTMLEncodeInplaceForTagValue(pNewValue, chEnd);
		}
		//
		size_t nOldLen = pEnd - pBegin + 1;
		size_t nNewLen = _tcslen(pNewValue);
		WizHTMLMoveStr(pEnd + 1, nNewLen - nOldLen);
		memcpy(pBegin, pNewValue, nNewLen * sizeof(TCHAR));
	}
	return TRUE;
}

LPCTSTR WizHTMLFindEndOfQuotInBlockScriptSource(LPCTSTR p, TCHAR chQuot)
{
	LPCTSTR pOld = p;
	while (*p)
	{
		TCHAR ch = *p;
		//
		if (ch == '\\')
		{
			TCHAR chNext = *(p + 1);
			switch (chNext)
			{
			case '\\':
			case '\'':
			case 'b':
			case 'f':
			case 'n':
			case 'r':
			case 't':
			case '/':
			case '"':
				p++;
				break;
			}
		}
		else if (ch == chQuot)
		{
			//TOLOG(WizSubString(pOld, 0, p - pOld));
			return p;
		}
		//
		p++;
	}
	//
	//
	return pOld;
}



BOOL WizHTMLGetTagEvent(LPCTSTR lpszTag, LPTSTR lpszEvent, size_t nBufferSize)
{
	if (!lpszTag || !lpszEvent)
		return FALSE;
	//
	*lpszEvent = 0;

	LPCTSTR p = lpszTag;
	while (*p)
	{
		if (WizIsSpaceChar(*p) 
			&& WizIsSameChar(*(p + 1), 'o')
			&& WizIsSameChar(*(p + 2), 'n'))
		{
			p += 3;
			switch (_totupper(*p))
			{
			case _T('A'):
				if (0 == _tcsnicmp(p, _T("afterupdate="), 12))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onafterupdate"));
					return TRUE;
				}
				break;
			case 'B':
				if (0 == _tcsnicmp(p, _T("beforeupdate="), 13))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onbeforeupdate"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("blur="), 5))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onblur"));
					return TRUE;
				}
				break;
			case 'C':
				if (0 == _tcsnicmp(p, _T("click="), 6))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onclick"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("change="), 7))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onchange"));
					return TRUE;
				}
				break;
			case 'D':
				if (0 == _tcsnicmp(p, _T("dataavailable="), 14))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("ondataavailable"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("datasetchanged="), 15))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("ondatasetchanged"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("datasetcomplete="), 16))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("ondatasetcomplete"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("dblclick="), 9))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("ondblclick"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("dragstart="), 10))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("ondragstart"));
					return TRUE;
				}
				break;
			case 'E':
				if (0 == _tcsnicmp(p, _T("errorupdate="), 12))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onerrorupdate"));
					return TRUE;
				}
				break;
			case 'F':
				if (0 == _tcsnicmp(p, _T("filterchange="), 13))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onfilterchange"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("focus="), 6))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onfocus"));
					return TRUE;
				}
				break;
			case 'H':
				if (0 == _tcsnicmp(p, _T("help="), 5))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onhelp"));
					return TRUE;
				}
				break;
			case 'K':
				if (0 == _tcsnicmp(p, _T("keydown="), 8))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onkeydown"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("keypress="), 9))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onkeypress"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("keyup="), 6))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onkeyup"));
					return TRUE;
				}
				break;
			case 'L':
				if (0 == _tcsnicmp(p, _T("load="), 5))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onload"));
					return TRUE;
				}
				break;
			case 'M':
				if (0 == _tcsnicmp(p, _T("mousedown="), 10))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmousedown"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("mousemove="), 10))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmousemove"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("mouseout="), 9))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmouseout"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("mouseover="), 10))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmouseover"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("mouseup="), 8))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmouseup"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("mousewheel="), 11))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onmousewheel"));
					return TRUE;
				}
				
				break;
			case 'P':
				if (0 == _tcsnicmp(p, _T("paste="), 6))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onpaste"));
					return TRUE;
				}
			case 'R':
				if (0 == _tcsnicmp(p, _T("rowenter="), 9))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onrowenter"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("rowexit="), 8))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onrowexit"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("resize="), 7))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onresize"));
					return TRUE;
				}
				break;
			case 'S':
				if (0 == _tcsnicmp(p, _T("scroll="), 7))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onscroll"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("selectstart="), 12))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onselectstart"));
					return TRUE;
				}
				else if (0 == _tcsnicmp(p, _T("submit="), 7))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onsubmit"));
					return TRUE;
				}
				break;
			case 'U':
				if (0 == _tcsnicmp(p, _T("unload="), 7))
				{
					_tcscpy_s(lpszEvent, nBufferSize, _T("onunload"));
					return TRUE;
				}
				break;
			}
		}
		else
		{
			p++;
		}
	}
	return FALSE;
}



#ifdef __CSTRINGT_H__

UINT WizHTMLGetTagStyleEx(LPCTSTR lpszTag)
{
	CString str(lpszTag);
	str.Trim();
	//
	if (str.GetLength() < 4)
		return 0;
	//
	if (str[1] == '/')		//</a>
		return wizHTMLTagStyleExEnd;
	//
	if (str[str.GetLength() - 2] == '/')		//<a/>
		return wizHTMLTagStyleExBegin | wizHTMLTagStyleExEnd;
	//
	return wizHTMLTagStyleExBegin;
}

//
#endif




bool WizCompareImageDataURL(const WIZHTMLIMAGEDATA& image1, const WIZHTMLIMAGEDATA& image2)
{
	return image1.strURL.CompareNoCase(image2.strURL) == 0;
}

BOOL WizHTMLImageInArray(const WIZHTMLIMAGEDATA& data, const CWizHTMLImageDataArray& arrayImages)
{
	CWizHTMLImageDataArray arrayTemp;
	arrayTemp.push_back(data);
	//
	return std::find_first_of(arrayImages.begin(), arrayImages.end(), arrayTemp.begin(), arrayTemp.end(), WizCompareImageDataURL) != arrayImages.end();
}



bool WizCompareLinkDataURL(const WIZHTMLLINKDATA& link1, const WIZHTMLLINKDATA& link2)
{
	return link1.strURL.CompareNoCase(link2.strURL) == 0;
}

BOOL WizHTMLImageInArray(const WIZHTMLLINKDATA& data, const CWizHTMLLinkDataArray& arrayLinks)
{
	CWizHTMLLinkDataArray arrayTemp;
	arrayTemp.push_back(data);
	//
	return std::find_first_of(arrayLinks.begin(), arrayLinks.end(), arrayTemp.begin(), arrayTemp.end(), WizCompareLinkDataURL) != arrayLinks.end();
}




BOOL WizHTMLRemoveDocType(CStringW& strHtml)
{
	int nBegin = (int)WizStrStrI_Pos(strHtml, _T("<!DOCTYPE "));
	if (-1 == nBegin)
		return FALSE;
	//
	int nEnd = strHtml.Find('>', nBegin);
	//
	if (nEnd - nBegin > 1024)
		return FALSE;
	//
	CString strDocType = strHtml.Mid(nBegin, nEnd - nBegin + 1);
	if (0 == strDocType.CompareNoCase(_T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">")))
		return FALSE;
	if (0 == strDocType.CompareNoCase(_T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">")))
		return FALSE;
	if (0 == strDocType.CompareNoCase(_T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.0 Transitional//EN\">")))
		return FALSE;
	if (0 == strDocType.CompareNoCase(_T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 2.0 Transitional//EN\">")))
		return FALSE;
	if (0 == strDocType.CompareNoCase(_T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 1.0 Transitional//EN\">")))
		return FALSE;
	//
	//if (-1 == WizStrStrI_Pos(strDocType, _T("-//W3C//DTD HTML 4.01 Transitional//EN")))
	//	return TRUE;
	//
	//
	strHtml.Delete(nBegin, nEnd - nBegin + 1);
	//strHtml.Insert(nBegin, strNewDocType);
	//
	return TRUE;
}


BOOL WizHTMLRemoveBodyInnerText(CString& strHtml)
{
	ptrdiff_t nBegin = WizStrStrI_Pos(strHtml, _T("<body"));
	if (-1 == nBegin)
		return FALSE;
	//
	nBegin = WizStrStrI_Pos(strHtml, _T(">"), nBegin);
	if (-1 == nBegin)
		return FALSE;
	//
	nBegin++;
	//
	ptrdiff_t nEnd = WizStrRStrI_Pos(strHtml, _T("</body"));
	if (-1 == nEnd)
		return FALSE;
	//
	if (nEnd < nBegin)
		return FALSE;
	//
	strHtml.Delete(int(nBegin), int(nEnd - nBegin));
	//
	return TRUE;
}



BOOL WizHTMLGetBodyTextWithoutBodyTag(LPCTSTR lpszText, CString& strRet)
{
	LPCTSTR pBegin = WizStrStrI_Ptr(lpszText, _T("<body"));
	if (pBegin)
	{
		pBegin = _tcschr(pBegin, _T('>'));
		if (pBegin)
			pBegin++;
	}
	else
	{
		pBegin = WizStrStrI_Ptr(lpszText, _T("<html"));
		//
		if (pBegin)
		{
			pBegin = _tcschr(pBegin, _T('>'));
			if (pBegin)
				pBegin++;
		}
		else
		{
			pBegin = lpszText;
		}
	}
	//could not find char '>', _tcschr failed
	if (!pBegin)
		pBegin = lpszText;
	//
	LPCTSTR pEnd = WizStrRStrI_Ptr(lpszText, _T("</body"));
	if (!pEnd)
		pEnd = WizStrRStrI_Ptr(lpszText, _T("</html"));
	if (!pEnd)
		pEnd = lpszText + _tcslen(lpszText);
	//
#ifdef __ATLBASE_H__
	ATLASSERT(pBegin);
	ATLASSERT(pEnd);
	ATLASSERT(pEnd >= pBegin);
#else
	ASSERT(pBegin);
	ASSERT(pEnd);
	ASSERT(pEnd >= pBegin);
#endif
	//
	//
	strRet = WizSubString(lpszText, pBegin - lpszText, pEnd - pBegin);
	//
	return TRUE;
}


LPCTSTR WizGetHtmlContentHiddenTagBegin()
{
	static const LPCTSTR lpszBegin = _T("<!--WizHtmlContentBegin-->");
	return lpszBegin;
}

LPCTSTR WizGetHtmlContentHiddenTagEnd()
{
	static const LPCTSTR lpszEnd = _T("<!--WizHtmlContentEnd-->");
	return lpszEnd;
}

BOOL WizHtmlGetContentByHiddenTag(const CString& strHtmlText, CString& strContent)
{
	static const LPCTSTR lpszBegin = WizGetHtmlContentHiddenTagBegin();
	static const LPCTSTR lpszEnd = WizGetHtmlContentHiddenTagEnd();
	static const int nBeginLen = (int)_tcslen(lpszBegin);
	static const int nEndLen = (int)_tcslen(lpszEnd);
	//
	int nBegin = strHtmlText.Find(lpszBegin);
	if (-1 == nBegin)
		return FALSE;
	//
	
	int nEnd = (int)WizStrRStrI_Pos(strHtmlText, lpszEnd);
	if (-1 == nEnd)
		return FALSE;
	//
	if (nBegin > nEnd)
		return FALSE;
	//
	strContent = strHtmlText.Mid(nBegin + nBeginLen, nEnd - nBegin - nBeginLen);
	//
	return TRUE;
}

BOOL WizHtmlContentAppendHiddenTag(CString& strContent)
{
	strContent = CString(WizGetHtmlContentHiddenTagBegin()) + strContent + WizGetHtmlContentHiddenTagEnd();
	//
	return TRUE;
}

BOOL WizHtmlGetContentByHiddenTagWithHiddenTag(const CString& strHtmlText, CString& strContent)
{
	if (!WizHtmlGetContentByHiddenTag(strHtmlText, strContent))
		return FALSE;
	//
	return WizHtmlContentAppendHiddenTag(strContent);
}



BOOL WizHtmlContentInsertIntoContent(CString& strContent, LPCTSTR lpszHtml)
{
	int nPos = (int)::WizStrStrI_Pos(strContent, WizGetHtmlContentHiddenTagBegin(), 0);
	if (-1 == nPos)
	{
		nPos = 0;
	}
	else
	{
		nPos += (int)_tcslen(WizGetHtmlContentHiddenTagBegin());
	}
	//
	strContent.Insert(nPos, lpszHtml);
	//
	return TRUE;
}

BOOL WizHTMLGetHeadText(LPCTSTR lpszText, CString& strRet)
{
	LPCTSTR pBegin = WizStrStrI_Ptr(lpszText, _T("<head"));
	if (!pBegin)
		return FALSE;
	//
	LPCTSTR pEnd = WizStrRStrI_Ptr(pBegin, _T("</head"));
	if (!pEnd)
		return FALSE;
	//
	strRet = WizSubString(pBegin, 0, pEnd - pBegin);
	strRet += _T("</head>");
	//
	return TRUE;
}



CString WizHTMLGetTitleFromText(LPCTSTR lpszText)
{
	LPCTSTR lpszBegin = WizStrStrI_Ptr(lpszText, _T("<title>"));
	if (!lpszBegin)
		return CString();
	//
	lpszBegin += 7;
	//
	LPCTSTR lpszEnd = WizStrStrI_Ptr(lpszBegin, _T("</title>"));
	if (!lpszEnd)
		return CString();
	//
	return WizSubString(lpszBegin, 0, lpszEnd - lpszBegin);
}

BOOL WizHTMLSetTitleToText(CString& strText, LPCTSTR lpszTitle)
{
	if (!lpszTitle)
		return FALSE;
	//
	intptr_t nBegin = WizStrStrI_Pos(strText, _T("<title>"), 0);
	if (-1 != nBegin)
	{
		nBegin += 7;
		//
		intptr_t nEnd = WizStrStrI_Pos(strText, _T("</title>"), nBegin);
		if (-1 != nEnd)
		{
			CString strOldTitle = strText.Mid(int(nBegin), int(nEnd - nBegin));
			if (strOldTitle == lpszTitle)
				return FALSE;
			//
			strText.Delete(int(nBegin), int(nEnd - nBegin));
			strText.Insert(int(nBegin), lpszTitle);
			return TRUE;
		}
	}
	//
	const CString strTitleText = CString(_T("<title>")) + lpszTitle + _T("</title>");
	//
	WizHTMLInsertTextInHead(strTitleText, strText);
	//
	return TRUE;
}

CString WizHTMLGetTitleFromFile(LPCTSTR lpszFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszFileName, strText))
		return CString();
	//
	return WizHTMLGetTitleFromText(strText);
}

BOOL WizHTMLSetTitleToFile(LPCTSTR lpszFileName, LPCTSTR lpszTitle)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszFileName, strText))
		return FALSE;
	//
	if (!WizHTMLSetTitleToText(strText, lpszTitle))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszFileName, strText);
}


void WizHTMLInsertTextInHead(LPCTSTR lpszText, CString& strHTML)
{
	BOOL nInserted = FALSE;
	//
	ptrdiff_t nPos = WizStrStrI_Pos(strHTML, _T("<head"));
	if (-1 != nPos)
	{
		nPos = WizStrStrI_Pos(strHTML, _T(">"), nPos);
		if (nPos != -1)
		{
			nPos++;
			//
			strHTML.Insert(int(nPos), lpszText);
			//
			nInserted = TRUE;
		}
	}
	//
	if (!nInserted)
	{
		strHTML = CString(lpszText) + strHTML;
	}
}


void WizHTMLInsertTextInHead2(LPCTSTR lpszText, CString& strHTML)
{
	ptrdiff_t nPos = WizStrStrI_Pos(strHTML, _T("</head"));
	if (-1 == nPos)
	{
		nPos = 0;
	}
	strHTML.Insert(int(nPos), lpszText);
}



void WizHTMLInsertTextAfterBodyA(LPCSTR lpszText, CStringA& strHTML)
{
	BOOL nInserted = FALSE;
	//
	ptrdiff_t nPos = WizStrRStrI_PosA(strHTML, "</body");
	if (-1 != nPos)
	{
		strHTML.Insert(int(nPos), lpszText);
	}
	else
	{
		strHTML += lpszText;
	}
}

void WizHTMLInsertTextAfterBodyW(LPCWSTR lpszText, CStringW& strHTML)
{
	BOOL nInserted = FALSE;
	//
	ptrdiff_t nPos = WizStrRStrI_Pos(strHTML, _T("</body"));
	if (-1 != nPos)
	{
		strHTML.Insert(int(nPos), lpszText);
	}
	else
	{
		strHTML += lpszText;
	}
}



void WizHTMLInsertTextBeforeBody(LPCTSTR lpszText, CString& strHTML)
{
	BOOL nInserted = FALSE;
	//
	ptrdiff_t nPos = WizStrStrI_Pos(strHTML, _T("<body"));
	if (-1 != nPos)
	{
		nPos = WizStrStrI_Pos(strHTML, _T(">"), nPos);
		if (nPos != -1)
		{
			nPos++;
			//
			strHTML.Insert(int(nPos), lpszText);
			//
			nInserted = TRUE;
		}
	}
	//
	if (!nInserted)
	{
		strHTML = CString(lpszText) + strHTML;
	}
}



void WizHTMLLinkRemoveMultiLinks(CWizHTMLLinkDataArray& arrayLinks)
{
	std::set<CString> setURL;
	//
	size_t nCount = arrayLinks.size();
	for (intptr_t i = nCount - 1; i >= 0; i--)
	{
		const WIZHTMLLINKDATA& data = arrayLinks[i];
		//
		if (setURL.find(data.strURL) == setURL.end())
		{
			setURL.insert(data.strURL);
		}
		else
		{
			arrayLinks.erase(arrayLinks.begin() + i);
		}
	}
}




const LPCSTR g_strWizFileTable = 
"<table border=\"1\" width=\"100%\" id=\"table1\" cellspacing=\"0\" cellpadding=\"0\" style=\"border-collapse: collapse\">\n\
	<tr>\n\
		<td bgcolor=\"#FFCC99\">%FilesTitle%</td>\n\
	</tr>\n\
	<tr>\n\
		<td>%FilesText%</td>\n\
	</tr>\n\
</table>\n";

const LPCSTR g_strWizFileLine = 
"<div><a href=\"%FileURL%\">%FileName%</a></div>\n";


CString WizHTMLGetFilesTextToInsert(LPCTSTR lpszHtmlFilePath, LPCTSTR lpszFilesTitle, const CWizStdStringArray& arrayFiles)
{
	if (arrayFiles.empty())
		return CString();
	//
	CString strFilesText;
	//
	CString strHtmlFilePath(lpszHtmlFilePath);
	//
	size_t nCount = arrayFiles.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CString strFileName = arrayFiles[i];
		//
		if (!PathFileExists(strFileName))
			continue;
		//
		CString strURL = strFileName;
		//
		TCHAR szRelativePath[MAX_PATH] = {0};
		if (PathRelativePathTo(szRelativePath, strHtmlFilePath, FILE_ATTRIBUTE_DIRECTORY, WizExtractFilePath(strFileName), FILE_ATTRIBUTE_DIRECTORY))
		{
			PathAddBackslash(szRelativePath);
			if (0 == _tcscmp(szRelativePath, _T(".\\")))
			{
				strURL = WizExtractFileName(strFileName);
			}
			else
			{
				strURL = CString(szRelativePath) + WizExtractFileName(strFileName);
			}
			//
			strURL.Replace('\\', '/');
		}

		//
		CString strLine(g_strWizFileLine);
		strLine.Replace(_T("%FileURL%"), strURL);
		strLine.Replace(_T("%FileName%"), WizExtractFileName(strFileName));
		//
		strFilesText += strLine;
	}
	//
	CString strFilesTableText(g_strWizFileTable);
	strFilesTableText.Replace(_T("%FilesTitle%"), lpszFilesTitle);
	strFilesTableText.Replace(_T("%FilesText%"), strFilesText);
	//
	return strFilesTableText;
}



bool WizCompareFlashDataURL(const WIZHTMLFLASHDATA& flash1, const WIZHTMLFLASHDATA& flash2)
{
	return flash1.strURL.CompareNoCase(flash2.strURL) == 0;
}

BOOL WizHTMLFlashInArray(const WIZHTMLFLASHDATA& data, const CWizHTMLFlashDataArray& arrayFlash)
{
	CWizHTMLFlashDataArray arrayTemp;
	arrayTemp.push_back(data);
	//
	return std::find_first_of(arrayFlash.begin(), arrayFlash.end(), arrayTemp.begin(), arrayTemp.end(), WizCompareFlashDataURL) != arrayFlash.end();
}


BOOL WizCanConvertToDefaultCodePage(const wchar_t* lpszText)
{
	if (CP_UTF8 == GetACP())
		return TRUE;
	//
	BOOL bUseDefaultChar = FALSE;
	if (0 == WideCharToMultiByte(GetACP(), 0, lpszText, -1, NULL, 0, NULL, &bUseDefaultChar))
		return TRUE;
	//
	return !bUseDefaultChar;
}

BOOL WizHtmlReplaceCharset(CStringA& strText, LPCTSTR lpszCharset)
{
	CString strNewMeta = WizFormatString1(_T("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=%1\">"), lpszCharset);
	//
	int nFindBegin = 0;
	//
	while (1)
	{
		int nMetaBegin = (int)WizStrStrI_PosA(strText, "<meta", nFindBegin);
		if (-1 == nMetaBegin)
			break;
		//
		int nMetaEnd = strText.Find('>', nMetaBegin);
		if (-1 == nMetaEnd)
			break;
		//
		CString strMeta = CString(strText.Mid(nMetaBegin, nMetaEnd - nMetaBegin + 1));
		//
		CString strHttpEquiv;
		if (WizHTMLGetTagValue(strMeta, _T("http-equiv"), strHttpEquiv) && 0 == strHttpEquiv.CompareNoCase(_T("Content-Type")))
		{
			CString strContent;
			if (WizHTMLGetTagValue(strMeta, _T("content"), strContent) && -1 != WizStrStrI_Pos(strContent, _T("charset=")))
			{
				strText.Delete(nMetaBegin, nMetaEnd - nMetaBegin + 1);
				break;
			}
		}
		//
		nFindBegin += strMeta.GetLength();
	}
	//insert after head
	int nHeadBegin = (int)WizStrStrI_PosA(strText, "<head");
	if (-1 != nHeadBegin)
	{
		int nHeadEnd = strText.Find('>', nHeadBegin);
		if (-1 != nHeadEnd)
		{
			strText.Insert(nHeadEnd + 1, CStringA("\r\n") + CStringA(strNewMeta));
			return TRUE;
		}
	}
	//insert at file begin
	strText.Insert(0, CStringA(strNewMeta));
	//
	return TRUE;
}



BOOL WizHtmlUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset /*= NULL*/, BOOL bForceNotUseUnicode /*= FALSE*/)
{
	CString strCharset = WizHTMLGetCharsetFromHTMLText(CStringA(lpszText));
	//
	if (strCharset.IsEmpty() 
		|| 0 == strCharset.CompareNoCase(_T("UNICODE")) 
		|| 0 == strCharset.CompareNoCase(_T("utf-8"))
		|| 0 == strCharset.CompareNoCase(_T("utf-7")))
	{
		if (bForceNotUseUnicode || WizCanConvertToDefaultCodePage(lpszText))
		{
			strCharset = WizGetDefaultCharset();
		}
		else
		{
			strCharset = _T("utf-8");
		}
		//
		strText = WizBSTR2STR(strCharset, lpszText);
	}
	else
	{
		strText = WizBSTR2STR(strCharset, lpszText);
	}
	//reset charset in html
	WizHtmlReplaceCharset(strText, strCharset);
	//
	if (pstrCharset)
	{
		*pstrCharset = strCharset;
	}
	//
	return TRUE;
}
BOOL WizTextUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset /*= NULL*/, BOOL bForceNotUseUnicode /*= FALSE*/)
{
	CString strCharset;
	//
	if (bForceNotUseUnicode || WizCanConvertToDefaultCodePage(lpszText))
	{
		strCharset = WizGetDefaultCharset();
	}
	else
	{
		strCharset = _T("utf-8");
	}
	strText = WizBSTR2STR(strCharset, lpszText);
	//
	if (pstrCharset)
	{
		*pstrCharset = strCharset;
	}
	//
	return TRUE;
}
BOOL WizHtmlUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText)
{
	CString strCharset = WizHTMLGetCharsetFromHTMLText(CStringA(lpszText));
	//
	if (strCharset.IsEmpty() 
		|| 0 != strCharset.CompareNoCase(_T("utf-8")))
	{
		strCharset = _T("utf-8");
		//
		strText = WizBSTR2STR(strCharset, lpszText);
	}
	else
	{
		strText = WizBSTR2STR(strCharset, lpszText);
	}
	//reset charset in html
	WizHtmlReplaceCharset(strText, strCharset);
	//
	return TRUE;
}

BOOL WizTextUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText)
{
	strText = WizBSTR2STR(_T("utf-8"), lpszText);
	//
	return TRUE;
}



intptr_t WizHTMLURLAndFileIndexOfURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL)
{
	size_t nCount = arrayFiles.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (0 == arrayFiles[i].strURL.CompareNoCase(lpszURL))
		{
			return i;
		}
	}
	//
	return -1;
}
//
CString WizURLAndFileGetFileNameByURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL)
{
	intptr_t nIndex = WizHTMLURLAndFileIndexOfURL(arrayFiles, lpszURL);
	if (-1 == nIndex)
		return CString();
	//
	return arrayFiles[nIndex].strFileName;
}



BOOL WizConvertFlashToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML)
{
	if (!WizLoadUnicodeTextFromFile(lpszTemplateFileName, strHTML))
		return FALSE;
	//
	strHTML.Replace(L"%title%", lpszTitle);
	strHTML.Replace(L"%filename%", lpszFileName);
	//
	return TRUE;
}

BOOL WizConvertFlashToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CString strHtml;
	if (!WizConvertFlashToHTML(lpszTemplateFileName, lpszFileName, lpszTitle, strHtml))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHtml);;
}

const LPCWSTR g_lpszFlash2HTMLDefaultTemplate = 
L"<html>\r\n\
<head>\r\n\
<title>%title%</title>\r\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">\r\n\
</head>\r\n\
<body>\r\n\
<!--WizHtmlContentBegin-->\r\n\
<EMBED src=\"%filename%\" width=\"100%\" height=\"100%\" quality=high  TYPE=\"application/x-shockwave-flash\"></EMBED>\r\n\
<!--WizHtmlContentEnd-->\r\n\
</body>\r\n\
</html>\r\n\
";

BOOL WizConvertFlashToHTMLFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CString strHtml(g_lpszFlash2HTMLDefaultTemplate);
	strHtml.Replace(L"%title%", lpszTitle);
	strHtml.Replace(L"%filename%", lpszFileName);
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHtml);;
}


CString CyberArticleGetConvertFlashToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath)
{
	CString strPath(lpszCyberArticleAppPath);
	WizPathAddBackslash(strPath);
	return strPath + _T("Plugins\\Import\\ImportFlash.htm");
}

BOOL CyberArticleConvertFlashToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML)
{
	return WizConvertFlashToHTML(CyberArticleGetConvertFlashToHTMLTemplateFileName(lpszCyberArticleAppPath), lpszFileName, lpszTitle, strHTML);
}
BOOL CyberArticleConvertFlashToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName)
{
	CStringW strHTML;
	if (!CyberArticleConvertFlashToHTML(lpszCyberArticleAppPath, lpszFileName, lpszTitle, strHTML))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHTMLFileName, strHTML);
}



BOOL WizConvertImageToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML)
{
	if (!WizLoadUnicodeTextFromFile(lpszTemplateFileName, strHTML))
		return FALSE;
	//
	strHTML.Replace(L"%title%", lpszTitle);
	strHTML.Replace(L"%filename%", lpszFileName);
	//
	return TRUE;
}


CString CyberArticleGetConvertImageToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath)
{
	CString strPath(lpszCyberArticleAppPath);
	WizPathAddBackslash(strPath);
	return strPath + _T("Plugins\\Import\\ImportImage.htm");
}

BOOL CyberArticleConvertImageToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML)
{
	return WizConvertImageToHTML(CyberArticleGetConvertImageToHTMLTemplateFileName(lpszCyberArticleAppPath), lpszFileName, lpszTitle, strHTML);
}

BOOL CyberArticleConvertImageToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName)
{
	CStringW strHTML;
	if (!CyberArticleConvertImageToHTML(lpszCyberArticleAppPath, lpszFileName, lpszTitle, strHTML))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHTMLFileName, strHTML);
}

BOOL WizConvertImageToHtmlFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CStringW strHTML;
	if (!WizConvertImageToHTML(lpszTemplateFileName, lpszFileName, lpszTitle, strHTML))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHTML);
}

const LPCWSTR g_lpszImage2HTMLDefaultTemplate = L"\
<html>\r\n\
<head>\r\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">\r\n\
<title>%title%</title>\r\n\
</head>\r\n\
<body>\r\n\
<!--WizHtmlContentBegin-->\r\n\
<p align=\"center\">\r\n\
<img align=\"middle\" border=\"0\" src=\"%filename%\" id=\"WizImageID\">\r\n\
</p>\r\n\
<!--WizHtmlContentEnd-->\r\n\
</body>\r\n\
</html>\r\n\
";

BOOL WizConvertImageToHtmlFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CString strHtml(g_lpszImage2HTMLDefaultTemplate);
	strHtml.Replace(L"%title%", lpszTitle);
	strHtml.Replace(L"%filename%", lpszFileName);
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHtml);;
}
BOOL WizConvertImageToHTML_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML)
{
	strHTML = g_lpszImage2HTMLDefaultTemplate;
	//
	strHTML.Replace(L"%title%", lpszTitle);
	strHTML.Replace(L"%filename%", lpszFileName);
	//
	return TRUE;
}


BOOL WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(int nBegin, CStringW& strLine, const CStringW& strTab)
{
	BOOL bRet = FALSE;
	//
	int i = nBegin;
	while (1)
	{
		if (i >= strLine.GetLength())
			return bRet;
		//
		TCHAR ch = strLine[i];
		//
		TCHAR chNext = 0;
		if (i < strLine.GetLength() - 1)
		{
			chNext = strLine[i + 1];
		}
		//
		if (ch == ' ')
		{
			if (chNext != ' ' && chNext != '\t' && bRet)
			{
				return bRet;
			}
			//
			strLine.Delete(i, 1);
			strLine.Insert(i, L"&nbsp;");
			i += 6;
			//
			bRet = TRUE;
		}
		else if (ch == '\t')
		{
			strLine.Delete(i, 1);
			strLine.Insert(i, strTab);
			i += strTab.GetLength();
			//
			bRet = TRUE;
		}
		else
		{
			return bRet;
		}
	}
}

BOOL WizConvertTextToHTML_ForPaste_ProcessBeginSpace(CStringW& strLine, const CStringW& strTab)
{
	return WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(0, strLine, strTab);
}
BOOL WizConvertTextToHTML_ForPaste_ProcessEndSpace(CStringW& strLine, const CStringW& strTab)
{
	int nPos = -1;
	//
	int nLen = strLine.GetLength();
	for (int i = nLen - 1; i >= 0; i--)
	{
		TCHAR ch = strLine[i];
		if (ch == '\t' || ch == ' ')
		{
			nPos = i;
		}
		else
		{
			break;
		}
	}
	//
	if (-1 == nPos)
		return FALSE;
	//
	return WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(nPos, strLine, strTab);
}

BOOL WizConvertTextToHTML_ForPaste_Line(CStringW& strLine, const CStringW& strTab, const CStringW& strMidTab)
{
	strLine.Replace(L"&", L"&amp;");
	strLine.Replace(L"<", L"&lt;");
	strLine.Replace(L">", L"&gt;");
	//
	WizConvertTextToHTML_ForPaste_ProcessBeginSpace(strLine, strTab);
	WizConvertTextToHTML_ForPaste_ProcessEndSpace(strLine, strTab);
	//
	strLine.Replace(L"\t", strMidTab);
	//
	return TRUE;
}

BOOL WizConvertTextToHTML_ForPaste(CStringW& strText, int nTabSize)
{
	CWizStdStringArray arrayText;
	WizSplitTextToArray(strText, '\n', arrayText);
	//
	CStringW strTab;
	for (int i = 0; i < nTabSize; i++)
	{
		strTab += L"&nbsp;";
	}
	//
	CStringW strMidTab;
	for (int i = 0; i < nTabSize - 1; i++)
	{
		strMidTab += L"&nbsp;";
	}
	strMidTab += _T(" ");
	//
	size_t nCount = arrayText.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CStringW strLine = arrayText[i];
		//
		CStringW strTestLine = strLine;
		strTestLine.Trim();
		//
		if (strLine.IsEmpty() || strTestLine.IsEmpty())
		{
			if (i != nCount - 1)
			{
				arrayText[i] = _T("<br />");//_T("<div>&nbsp;</div>");
			}
		}
		else
		{
			WizConvertTextToHTML_ForPaste_Line(strLine, strTab, strMidTab);
			//
			if (i != nCount - 1)
			{
				strLine += _T("<br />");
			}
			//
			arrayText[i] = strLine;
		}
	}
	//
	WizStringArrayToText(arrayText, strText, L"\r\n");
	//
	return TRUE;
}

CString CyberArticleGetConvertTextToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath)
{
	CString strPath(lpszCyberArticleAppPath);
	WizPathAddBackslash(strPath);
	return strPath + _T("Plugins\\Import\\ImportText.htm");
}


BOOL WizConvertTextToHTML_Template(LPCWSTR lpszTemplateText, LPCWSTR lpszTitle, CStringW& strText)
{
	WizConvertTextToHTML_ForPaste(strText, 4);
	//
	CStringW strHTML(lpszTemplateText);
	//
	strHTML.Replace(L"%title%", lpszTitle);
	strHTML.Replace(L"%text%", strText);
	//
	strText = strHTML;
	//
	return TRUE;
}

BOOL WizConvertTextToHTML(LPCTSTR lpszTemplateFileName, LPCWSTR lpszTitle, CStringW& strText)
{
	CStringW strHTML;
	if (!WizLoadUnicodeTextFromFile(lpszTemplateFileName, strHTML))
		return FALSE;

	return WizConvertTextToHTML_Template(strHTML, lpszTitle, strText);
}

const LPCWSTR g_lpszText2HTMLDefaultTemplate = 
L"<html>\r\n\
<head>\r\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">\r\n\
<title>%title%</title>\r\n\
</head>\r\n\
<body>\r\n\
<!--WizHtmlContentBegin-->\r\n\
%text%\r\n\
<!--WizHtmlContentEnd-->\r\n\
</body>\r\n\
</html>\r\n\
";

BOOL WizConvertTextToHTML_DefaultTemplate(LPCWSTR lpszTitle, CStringW& strText)
{
	CStringW strHTML(g_lpszText2HTMLDefaultTemplate);
	return WizConvertTextToHTML_Template(strHTML, lpszTitle, strText);
}

BOOL WizConvertTextFileToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszTextFileName, strText))
		return FALSE;

	if (!WizConvertTextToHTML(lpszTemplateFileName, lpszTitle, strText))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strText);
}

BOOL WizConvertTextFileToHTMLFile_DefaultTemplate(LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszTextFileName, strText))
		return FALSE;

	if (!WizConvertTextToHTML_DefaultTemplate(lpszTitle, strText))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strText);
}
