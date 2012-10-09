#ifndef _WIZHTMLBASE_H_
#define _WIZHTMLBASE_H_

#pragma once

#define wizHTMLTagStyleEnd		0x01

#define WizHTMLIsQuot(x)   ((x) == _T('\'') || (x) == _T('"'))


UINT WizHTMLGetTagStyle(LPCTSTR lpszTag);
BOOL WizHTMLGetTagName(LPCTSTR lpszTag, LPTSTR lpszName, size_t nSize);
BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, LPTSTR pszValue, size_t nSize);
BOOL WizHTMLSetTagValue(LPTSTR pszTag, size_t nSize, LPCTSTR lpszValueName, LPCTSTR lpszValue);
BOOL WizHTMLDeleteTagValue(LPTSTR pszTag, LPCTSTR lpszValueName);
BOOL WizHTMLGetTagEvent(LPCTSTR lpszTag, LPTSTR lpszEvent, size_t nBufferSize);
LPCTSTR WizHTMLFindEndOfQuotInBlockScriptSource(LPCTSTR p, TCHAR chQuot);


#ifdef __CSTRINGT_H__
BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, CString& strValue);
void WizHTMLDecodeInplace(CString& strText);

//
#define wizHTMLTagStyleExEnd		0x01
#define wizHTMLTagStyleExBegin		0x02

UINT WizHTMLGetTagStyleEx(LPCTSTR lpszTag);
//
#endif



BOOL WizHTMLGetBodyTextWithoutBodyTag(LPCTSTR lpszText, CString& strRet);
LPCTSTR WizGetHtmlContentHiddenTagBegin();
LPCTSTR WizGetHtmlContentHiddenTagEnd();
BOOL WizHtmlGetContentByHiddenTag(const CString& strHtmlText, CString& strContent);
BOOL WizHtmlContentAppendHiddenTag(CString& strContent);
BOOL WizHtmlGetContentByHiddenTagWithHiddenTag(const CString& strHtmlText, CString& strContent);
BOOL WizHtmlContentInsertIntoContent(CString& strContent, LPCTSTR lpszHtml);
BOOL WizHTMLGetHeadText(LPCTSTR lpszText, CString& strRet);
CString WizHTMLGetTitleFromText(LPCTSTR lpszText);
BOOL WizHTMLSetTitleToText(CString& strText, LPCTSTR lpszTitle);
CString WizHTMLGetTitleFromFile(LPCTSTR lpszFileName);
BOOL WizHTMLSetTitleToFile(LPCTSTR lpszFileName, LPCTSTR lpszTitle);
void WizHTMLInsertTextInHead(LPCTSTR lpszText, CString& strHTML);
void WizHTMLInsertTextInHead2(LPCTSTR lpszText, CString& strHTML);

struct WIZHTMLIMAGEDATA
{
	CString strURL;
	CString strText;
	CString strFileName;
};

typedef std::vector<WIZHTMLIMAGEDATA> CWizHTMLImageDataArray;

BOOL WizHTMLImageInArray(const WIZHTMLIMAGEDATA& data, const CWizHTMLImageDataArray& arrayImages);

void WizHTMLInsertTextAfterBodyA(LPCSTR lpszText, CStringA& strHTML);
void WizHTMLInsertTextAfterBodyW(LPCWSTR lpszText, CStringW& strHTML);

#ifdef _UNICODE
#define WizHTMLInsertTextAfterBody WizHTMLInsertTextAfterBodyW
#else
#define WizHTMLInsertTextAfterBody WizHTMLInsertTextAfterBodyA
#endif



BOOL WizHTMLLinkInArray(const WIZHTMLLINKDATA& data, const CWizHTMLLinkDataArray& arrayLinks);
void WizHTMLLinkRemoveMultiLinks(CWizHTMLLinkDataArray& arrayLinks);



struct WIZHTMLURLANDFILEDATA
{
	CString strURL;
	CString strFileName;
	//
	WIZHTMLURLANDFILEDATA()
	{
	}
	//
	WIZHTMLURLANDFILEDATA(LPCTSTR lpszURL, LPCTSTR lpszFileName)
	{
		strURL = lpszURL;
		strFileName = lpszFileName;
	}
};

typedef std::vector<WIZHTMLURLANDFILEDATA> CWizHTMLURLAndFileDataArray;

intptr_t WizHTMLURLAndFileIndexOfURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL);
CString WizURLAndFileGetFileNameByURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL);

#define WIZHTMLFLASHDATA			WIZHTMLURLANDFILEDATA
#define CWizHTMLFlashDataArray		CWizHTMLURLAndFileDataArray

BOOL WizHTMLFlashInArray(const WIZHTMLFLASHDATA& data, const CWizHTMLFlashDataArray& arrayLinks);



struct WIZHTMLFRAMEDATA
{
	CString strURL;
	CString strName;
	CString strID;
	CString strExtName;
	CString strFileName;
	CString strIncludeScriptFileName;
	CString strNoScriptFileName;
	//
	CString strResultText;
	//
	int nDepth;
	//
	WIZHTMLFRAMEDATA()
	{
		nDepth = 0;
	}
};


typedef std::vector<WIZHTMLFRAMEDATA> CWizHTMLFrameDataArray;


#define WIZ_URL_SERIAL_WILDCARD  _T("(*)")


BOOL WizHTMLRemoveDocType(CStringW& strHtml);
BOOL WizHTMLRemoveBodyInnerText(CString& strHtml);


void WizHTMLInsertTextBeforeBody(LPCTSTR lpszText, CString& strHTML);
CString WizHTMLGetFilesTextToInsert(LPCTSTR lpszHtmlFilePath, LPCTSTR lpszFilesTitle, const CWizStdStringArray& arrayFiles);




BOOL WizHtmlUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset = NULL, BOOL bForceNotUseUnicode = FALSE);
BOOL WizTextUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset = NULL, BOOL bForceNotUseUnicode = FALSE);


BOOL WizHtmlUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText);
BOOL WizTextUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText);

BOOL WizHtmlReplaceCharset(CStringA& strText, LPCTSTR lpszCharset);


BOOL WizConvertFlashToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL WizConvertFlashToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertFlashToHTMLFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
CString CyberArticleGetConvertFlashToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL CyberArticleConvertFlashToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL CyberArticleConvertFlashToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName);
BOOL WizConvertImageToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
CString CyberArticleGetConvertImageToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL CyberArticleConvertImageToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL CyberArticleConvertImageToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName);
BOOL WizConvertImageToHtmlFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertImageToHtmlFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertImageToHTML_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(int nBegin, CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_ProcessBeginSpace(CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_ProcessEndSpace(CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_Line(CStringW& strLine, const CStringW& strTab, const CStringW& strMidTab);
BOOL WizConvertTextToHTML_ForPaste(CStringW& strText, int nTabSize);
CString CyberArticleGetConvertTextToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL WizConvertTextToHTML_Template(LPCWSTR lpszTemplateText, LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextToHTML(LPCTSTR lpszTemplateFileName, LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextToHTML_DefaultTemplate(LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextFileToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertTextFileToHTMLFile_DefaultTemplate(LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName);




#endif