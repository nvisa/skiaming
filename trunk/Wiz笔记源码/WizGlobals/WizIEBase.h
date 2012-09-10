#pragma once


#ifndef __mshtml_h__
#include <mshtml.h>
#endif

BOOL WizHTMLDocumentHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszText, BOOL bWholdWordsOnly, BOOL bMatchCase, LPCTSTR lpszMatchStyle, LPCTSTR lpszSearchID);
BOOL WizHTMLDocumentHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszText, BOOL bWholdWordsOnly, BOOL bMatchCase, COLORREF crBackColor, LPCTSTR lpszSearchID);
void WizHTMLDocumentClearHighlightText(IHTMLDocument2* pDoc, LPCTSTR lpszSearchID);

BOOL WizIsIEWindow(HWND hWnd);




BOOL WizGetWndDocInterface(HWND hWnd, IHTMLDocument2** ppDoc);
HWND WizGetTopParentWindow(HWND hWnd);
HWND WizGetDocFromFocus(IHTMLDocument2** ppDoc, HWND hwndForegroundWindow);
BOOL WizGetDocFromMouse(IHTMLDocument2** ppDoc);
BOOL CALLBACK WizGetChildInternetExplorer_ServerWindowEnumChildProc(HWND hWnd, LPARAM lParam);
HWND WizGetChildInternetExplorer_ServerWindow(HWND hwndParent);

CString WizHTMLDocumentGetTitle(IHTMLDocument2* pDoc);
CString WizHTMLDocumentGetURL(IHTMLDocument2* pDoc);
BOOL WizHTMLDocumentGetPlainText(IHTMLDocument2* pDoc, CString& strText);
BOOL WizHTMLDocumentIsSelected(IHTMLDocument2* pDoc);
