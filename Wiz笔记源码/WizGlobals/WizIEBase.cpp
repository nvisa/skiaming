#include "stdafx.h"
#include "WizIEBase.h"

#pragma comment( lib, "Oleacc.lib" )


BOOL WizHTMLDocumentHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszText, BOOL bWholdWordsOnly, BOOL bMatchCase, LPCTSTR lpszMatchStyle, LPCTSTR lpszSearchID)
{
	CComPtr<IHTMLElement> spBodyElem;
	HRESULT hr = pDoc->get_body(&spBodyElem);
	if (FAILED(hr))
		return FALSE;
	//
	CComQIPtr<IHTMLBodyElement> spBody(spBodyElem);
	if (!spBody)
		return FALSE;
	//
	CComPtr<IHTMLTxtRange> spTxtRange;
	hr = spBody->createTextRange(&spTxtRange);
	if (FAILED(hr))
		return FALSE;

	CComBSTR bstrHTML;
	CComBSTR bstrSearchText(lpszText);
	//
	long nFlags = 0;
	if (bWholdWordsOnly)
		nFlags |= 2;
	if (bMatchCase)
		nFlags |= 4;
	//
	BOOL bRet = FALSE;
	//
	while (1)
	{
		VARIANT_BOOL vbFound = VARIANT_FALSE;
		hr = spTxtRange->findText(bstrSearchText, 0, nFlags, &vbFound);
		if (FAILED(hr))
			return FALSE;
		if (VARIANT_FALSE == vbFound)
			break;
		//
		CComBSTR bstrHTML;
		hr = spTxtRange->get_htmlText(&bstrHTML);
		if (FAILED(hr))
			return FALSE;
		//
		if (bstrHTML.Length() == 0)
			bstrHTML.Append(L"&nbsp;");
		//
		CStringW strNewHTML;
		strNewHTML.Format(L"<span id='%s' style='%s'>%s</span>", CStringW(lpszSearchID), CStringW(lpszMatchStyle), CStringW(bstrHTML));
		spTxtRange->pasteHTML(CComBSTR(strNewHTML));
		//
		bRet = TRUE;
		//
		long nActualCountStart = 0;
		spTxtRange->moveStart(CComBSTR(L"Character"), 1, &nActualCountStart);
		//
		long nActualCountEnd = 0;
		spTxtRange->moveEnd(CComBSTR(L"Textedit"), 1, &nActualCountEnd);
	}
	//
	return bRet;
}


BOOL WizHTMLDocumentHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszText, BOOL bWholdWordsOnly, BOOL bMatchCase, COLORREF crBackColor, LPCTSTR lpszSearchID)
{	
	CString strStyle;
	strStyle.Format(_T("color: black; background-color: %s; font-weight: bold"), WizHTMLColorToStringColor(crBackColor));
	//
	return WizHTMLDocumentHighlightText(pDoc, lpszText, bWholdWordsOnly, bMatchCase, strStyle, lpszSearchID);
}

void WizHTMLDocumentClearHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszSearchID)
{
	CComBSTR testid(lpszSearchID);
	CComBSTR testtag(5,"SPAN");
	//

	CComPtr<IHTMLElementCollection> spElemCollection;
	HRESULT hr = pDoc->get_all(&spElemCollection);
	if (FAILED(hr))
		return;
	//
	ATLASSERT(spElemCollection);
	//
	CComPtr<IUnknown> spUnk;
	hr = spElemCollection->get__newEnum(&spUnk);
	if (FAILED(hr))
		return;
	//
	CComQIPtr<IEnumVARIANT> spEnum(spUnk);
	if (!spEnum)
		return;
	//
	CComVariant varElement;
	CComPtr<IHTMLElement> spElem;
	while (spEnum->Next(1, &varElement, NULL) == S_OK)
	{
		if (varElement.vt != VT_DISPATCH)
			continue;
		//
		CComQIPtr<IHTMLElement> spElem(varElement.pdispVal);
		if (!spElem)
			continue;
		//
		CComBSTR id;
		CComBSTR tag;
		//
		spElem->get_id(&id);
		spElem->get_tagName(&tag);
		//
		if((id == testid) && (tag == testtag))
		{
			CComBSTR innerText;
			spElem->get_innerHTML(&innerText);
			spElem->put_outerHTML(innerText);
		}
	}
}


BOOL WizIsIEWindow(HWND hWnd)
{
	TCHAR sz[MAX_PATH] = {0};
	GetClassName(hWnd, sz, MAX_PATH);
	return (0 == _tcscmp(sz, _T("Internet Explorer_Server")));
}




inline BOOL WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(int nBegin, CStringW& strLine, const CStringW& strTab)
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

inline BOOL WizConvertTextToHTML_ForPaste_ProcessBeginSpace(CStringW& strLine, const CStringW& strTab)
{
	return WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(0, strLine, strTab);
}
inline BOOL WizConvertTextToHTML_ForPaste_ProcessEndSpace(CStringW& strLine, const CStringW& strTab)
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

inline BOOL WizConvertTextToHTML_ForPaste_Line(CStringW& strLine, const CStringW& strTab, const CStringW& strMidTab)
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

inline BOOL WizConvertTextToHTML_ForPaste(CStringW& strText, int nTabSize)
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

inline CString CyberArticleGetConvertTextToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath)
{
	CString strPath(lpszCyberArticleAppPath);
	WizPathAddBackslash(strPath);
	return strPath + _T("Plugins\\Import\\ImportText.htm");
}


inline BOOL WizConvertTextToHTML_Template(LPCWSTR lpszTemplateText, LPCWSTR lpszTitle, CStringW& strText)
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

inline BOOL WizConvertTextToHTML(LPCTSTR lpszTemplateFileName, LPCWSTR lpszTitle, CStringW& strText)
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

inline BOOL WizConvertTextToHTML_DefaultTemplate(LPCWSTR lpszTitle, CStringW& strText)
{
	CStringW strHTML(g_lpszText2HTMLDefaultTemplate);
	return WizConvertTextToHTML_Template(strHTML, lpszTitle, strText);
}

inline BOOL WizConvertTextFileToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszTextFileName, strText))
		return FALSE;

	if (!WizConvertTextToHTML(lpszTemplateFileName, lpszTitle, strText))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strText);
}

inline BOOL WizConvertTextFileToHTMLFile_DefaultTemplate(LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName)
{
	CStringW strText;
	if (!WizLoadUnicodeTextFromFile(lpszTextFileName, strText))
		return FALSE;

	if (!WizConvertTextToHTML_DefaultTemplate(lpszTitle, strText))
		return FALSE;
	//
	return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strText);
}




BOOL WizGetWndDocInterface(HWND hWnd, IHTMLDocument2** ppDoc)
{
    BOOL bRet = FALSE;
	//
    *ppDoc = NULL;
    // Explicitly load MSAA so we know if it's installed
    DWORD_PTR lRes = 0;
	
    static UINT nMsg = ::RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
    ::SendMessageTimeout( hWnd, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, &lRes );
	
	HRESULT hr = ObjectFromLresult(lRes, IID_IHTMLDocument2, 0, (void**)ppDoc);
    bRet = (S_OK == hr);
	
    return bRet;
}

HWND WizGetTopParentWindow(HWND hWnd)
{
	while (hWnd)
	{
		if (!(GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
			return hWnd;
		hWnd = GetParent(hWnd);
	}
	return NULL;
}

HWND WizGetDocFromFocus(IHTMLDocument2** ppDoc, HWND hwndForegroundWindow)
{
    if (!ppDoc)
        return NULL;
	//
    HWND hWnd = GetFocus();
	DEBUG_TOLOG1(_T("GetFocus() == %1"), WizIntToStr(int(hWnd)));
	//
    if (!hWnd)
    {                                              
        DWORD dwFromThreadID = GetWindowThreadProcessId(hwndForegroundWindow, NULL);
        DWORD dwToThreadID = GetCurrentThreadId();
        if (!AttachThreadInput(dwFromThreadID, dwToThreadID, TRUE))
		{
			TOLOG1(_T("Failed to call AttachThreadInput, GetLastError() = %1"), WizIntToStr(GetLastError()));
		}
        hWnd = GetFocus();
        AttachThreadInput(dwFromThreadID, dwToThreadID, FALSE);
		//
		DEBUG_TOLOG1(_T("GetFocus() == %1  (Retry)"), WizIntToStr(int(hWnd)));
    }
	//
	if (!hWnd)
	{
		RECT rc = {0, 0, 0 , 0};
		::GetWindowRect(hwndForegroundWindow, &rc);
		//
		POINT pt = { rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2};
		//
		hWnd = WindowFromPoint(pt);
		//
		DEBUG_TOLOG3(_T("WindowFromPoint(%1, %2) == %3"), WizIntToStr(pt.x), WizIntToStr(pt.y), WizIntToStr(int(hWnd)));
	}
	//
    HWND hDesktop = GetDesktopWindow();
    while (hWnd && hDesktop != hWnd)
    {
        if (WizGetWndDocInterface(hWnd, ppDoc))
        {
            return hWnd;
        }
        hWnd = GetParent(hWnd);
    }
    return NULL;
}


BOOL WizGetDocFromMouse(IHTMLDocument2** ppDoc)
{
	POINT pos;
	GetCursorPos(&pos);
    HWND hWnd = WindowFromPoint(pos);
    if (hWnd)
    {
        return WizGetWndDocInterface(hWnd, ppDoc);
    }
    return FALSE;
}

BOOL CALLBACK WizGetChildInternetExplorer_ServerWindowEnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND* phwnd = (HWND*)lParam;
	ATLASSERT(phwnd);
	//
	TCHAR szClassName[MAX_PATH] = {0};
	GetClassName(hWnd, szClassName, MAX_PATH);
	//
	if (0 != _tcsicmp(szClassName, _T("Internet Explorer_Server")))
		return TRUE;
	//
	*phwnd = hWnd;
	//
	return FALSE;
}

HWND WizGetChildInternetExplorer_ServerWindow(HWND hwndParent)
{
	if (WizIsIEWindow(hwndParent))
		return hwndParent;
	//
	HWND hwndResult = NULL;
	EnumChildWindows(hwndParent, WizGetChildInternetExplorer_ServerWindowEnumChildProc, (LPARAM)&hwndResult);
	//
	return hwndResult;
}



BOOL WizHTMLGetDocumentText_FromLocal(IHTMLDocument2* pDoc, CStringW& strText)
{
	if (!pDoc)
		return FALSE;
	//
	CComBSTR bstrURL;
	if (FAILED(pDoc->get_URL(&bstrURL)))
		return FALSE;
	//
	CWizURL url(bstrURL);
	//
	CString strFileName;
	if (!url.ToFileName(strFileName, FALSE))
		return FALSE;
	//
	if (!WizLoadUnicodeTextFromFileNoRemoveCR(strFileName, strText))
		return FALSE;
	if (WizStrStrI_Ptr(strText, L"xmlns:w=\"urn:schemas-microsoft-com:office:") != NULL)
		return FALSE;
	if (WizStrStrI_Ptr(strText, L"<?xml") != NULL)
		return FALSE;
	if (WizStrStrI_Ptr(strText, L"unescape(\"") != NULL)
		return FALSE;
	//
	return TRUE;
}



CString WizHTMLDocumentGetTitle(IHTMLDocument2* pDoc)
{
	ATLASSERT(pDoc);
	CComBSTR bstrTitle;
	if (FAILED(pDoc->get_title(&bstrTitle)))
		return CString();
	//
	return CString(bstrTitle);
}
CString WizHTMLDocumentGetURL(IHTMLDocument2* pDoc)
{
	ATLASSERT(pDoc);
	CComBSTR bstrURL;
	if (FAILED(pDoc->get_URL(&bstrURL)))
		return CString();
	//
	return CString(bstrURL);
}
BOOL WizHTMLDocumentGetPlainText(IHTMLDocument2* pDoc, CString& strText)
{
	ATLASSERT(pDoc);
	CComPtr<IHTMLElement> spBody;
	if (FAILED(pDoc->get_body(&spBody)))
		return FALSE;
	CComBSTR bstrText;
	if (FAILED(spBody->get_innerText(&bstrText)))
		return FALSE;
	//
	strText = bstrText;
	//
	return TRUE;
}

BOOL WizHTMLDocumentIsSelected(IHTMLDocument2* pDoc)
{
	CComPtr<IHTMLSelectionObject> spSelection;
	if (FAILED(pDoc->get_selection(&spSelection)))
		return FALSE;
	//
	CComPtr<IDispatch> spDisp;
	if (FAILED(spSelection->createRange(&spDisp)))
		return FALSE;
	CComQIPtr<IHTMLTxtRange, &IID_IHTMLTxtRange> spRange(spDisp);
	if (!spRange)
		return FALSE;
	//
	CComBSTR bstrHtml;
	if (FAILED(spRange->get_htmlText(&bstrHtml)))
		return FALSE;
	if (-1 != ::WizStrStrI_Pos(CString(bstrHtml), _T("<img")))
		return TRUE;
	//
	CComBSTR bstrText;
	if (FAILED(spRange->get_text(&bstrText)))
		return FALSE;
	return bstrText.Length() > 0;
}

