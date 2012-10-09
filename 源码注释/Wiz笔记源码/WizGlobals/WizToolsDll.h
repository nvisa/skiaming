#ifndef _WIZTOOLSDLL_H_
#define _WIZTOOLSDLL_H_

#pragma once

#include "WizHtmlSaverDef.h"
#include "WizToolsDef.h"

#include "WizHtmlBase.h"

#ifndef __MAP_
#include <map>
#endif

interface IHTMLDocument2;

class CWizToolsTableCells : public std::map<CString, CString>
{
public:
	CWizToolsTableCells()
	{
		m_nRowCount = 0;
		m_nColumnCount = 0;
	}
private:
	int m_nRowCount;
	int m_nColumnCount;
public:
	CString GetKey(int column, int row)
	{
		CString strKey;
		strKey.Format(_T("%d*%d"), column, row);
		return strKey;
	}
	void SetCell(int column, int row, LPCTSTR lpszHtml)
	{
		m_nRowCount = std::max<int>(row + 1, m_nRowCount);
		m_nColumnCount = std::max<int>(column + 1, m_nColumnCount);
		//
		insert(std::make_pair<CString, CString>(GetKey(column, row), lpszHtml));
	}
	//
	CString GetCell(int column, int row)
	{
		return operator[](GetKey(column, row));
	}
	//
	int GetRowCount()
	{
		return m_nRowCount;
	}
	int GetColumnCount()
	{
		return m_nColumnCount;
	}
};



struct WIZRSAKEYPAIR
{
	CString str_N;
	CString str_e;
	CString str_d;
};

class CWizToolsDll
{
public:
	CWizToolsDll(LPCWSTR lpszLogFileName, LPCTSTR lpszSettingsFileName, LPCTSTR lpszWizToolsPath = NULL)
	{
		m_hModule = NULL;
		m_pfunSetLogFileName = NULL;
		m_pfunSetTempPath = NULL;
		m_pfunSetSettingsFileName = NULL;
		m_pfunDocument2Html = NULL;
		m_pfunDocument2Mht = NULL;
		m_pfunDocument2Zip = NULL;
		m_pfunCompressHtml2Zip = NULL;
		m_pfunHtml2Html = NULL;
		m_pfunZip2Html = NULL;
		m_pfunHtmlGetContent = NULL;
		m_pfunHtml2Text = NULL;
		m_pfunHtml2TextAndImage = NULL;
		m_pfunRtfText2Html = NULL;
		m_pfunRtfFile2Html = NULL;
		m_pfunRtfText2Text = NULL;
		m_pfunRtfFile2Text = NULL;
		m_pfunConvertToHtmlFile = NULL;
		m_pfunConvertToHtmlFile2 = NULL;
		m_pfunHtmlContentRulesManagerDlg = NULL;
		m_pfunHtmlContentRulesDownloadAll = NULL;
		m_pfunHtmlContentRulesUploadAll = NULL;
		m_pfunExtractTags = NULL;
		m_pfunEnumTableCells = NULL;
		m_pfunURLDownloadToTempFile = NULL;
		m_pfunURLDownloadGetHtmlText = NULL;
		m_pfunEnumLinks= NULL;
		m_pfunLoadUnicodeTextFromFile = NULL;
		m_pfunTagGetAttribute = NULL;
		m_pfunTagSetAttribute = NULL;
		m_pfunFTSDeleteDocument = NULL;
		m_pfunFTSUpdateDocument = NULL;
		m_pfunFTSSearchDocument = NULL;
		m_pfunFTSOptimizeIndex = NULL;
		m_pfunDocumentGetSelection = NULL;
		m_pfunShowBubbleWindow = NULL;
		m_pfunShowBubbleWindowEx = NULL;
		m_pfunShowBubbleWindow2 = NULL;
		m_pfunShowBubbleWindow2Ex = NULL;
		m_pfunRunScript = NULL;
		m_pfunRunScript2 = NULL;
		m_pfunParseHtml = NULL;
		m_pfunEncrypt_AES256_CBC_PKCS5 = NULL;
		m_pfunDecrypt_AES256_CBC_PKCS5 = NULL;
		m_pfunEncrypt_RSA = NULL;
		m_pfunDecrypt_RSA = NULL;
		m_pfunGenerateKeyPair_RSA = NULL;
		m_pfunHtml2Mht = NULL;
		m_pfunMht2Html = NULL;
		m_pfunLoadMime = NULL;
		m_pfunCreateMimeMessageCreator = NULL;
		m_pfunPDF2Html = NULL;
		m_pfunPDF2Text = NULL;
		m_pfunCreateHtmlEditor = NULL;
		m_pfunScreenCapture = NULL;
		m_pfunScreenCaptureToFile = NULL;
		m_pfunCreateHtmlDocumentByHtmlText = NULL;
		m_pfunCreateHtmlDocumentByHtmlFileName = NULL;
		m_pfunHtmlDocumentToHtmlResourceFile = NULL;
		m_pfunHtmlResourceFileGetExtInfo = NULL;
		m_pfunHtmlResourceFileToHtmlDocument = NULL;
		m_pfunHtmlResourceFileClearFiles = NULL;
		//
		CString strPath(lpszWizToolsPath);
		if (strPath.IsEmpty())
		{
			strPath = WizGetAppPath();
		}
		WizPathAddBackslash(strPath);
		//
		CString strFileName = strPath + _T("WizTools.dll");
		//
		m_hModule = LoadLibrary(strFileName);
		if (m_hModule)
		{
			m_pfunSetLogFileName = (Type_WizToolsSetLogFileName *)GetProcAddress(m_hModule, "WizToolsSetLogFileName");
			m_pfunSetTempPath = (Type_WizToolsSetTempPath*)GetProcAddress(m_hModule, "WizToolsSetTempPath");
			m_pfunSetSettingsFileName = (Type_WizToolsSetSettingsFileName*)GetProcAddress(m_hModule, "WizToolsSetSettingsFileName");
			m_pfunDocument2Html = (Type_WizToolsDocument2Html *)GetProcAddress(m_hModule, "WizToolsDocument2Html");
			m_pfunDocument2Mht = (Type_WizToolsDocument2Mht *)GetProcAddress(m_hModule, "WizToolsDocument2Mht");
			m_pfunDocument2Zip = (Type_WizToolsDocument2Zip *)GetProcAddress(m_hModule, "WizToolsDocument2Zip");
			m_pfunCompressHtml2Zip = (Type_WizToolsCompressHtml2Zip *)GetProcAddress(m_hModule, "WizToolsCompressHtml2Zip");
			m_pfunHtml2Html = (Type_WizToolsHtml2Html *)GetProcAddress(m_hModule, "WizToolsHtml2Html");
			m_pfunZip2Html = (Type_WizToolsZip2Html *)GetProcAddress(m_hModule, "WizToolsZip2Html");
			m_pfunHtmlGetContent = (Type_WizToolsHtmlGetContent *)GetProcAddress(m_hModule, "WizToolsHtmlGetContent");
			m_pfunHtml2Text = (Type_WizToolsHtml2Text *)GetProcAddress(m_hModule, "WizToolsHtml2Text");
			m_pfunHtml2TextAndImage = (Type_WizToolsHtml2TextAndImage *)GetProcAddress(m_hModule, "WizToolsHtml2TextAndImage");
			m_pfunRtfText2Html = (Type_WizToolsRtfText2Html *)GetProcAddress(m_hModule, "WizToolsRtfText2Html");
			m_pfunRtfFile2Html = (Type_WizToolsRtfFile2Html *)GetProcAddress(m_hModule, "WizToolsRtfFile2Html");
			m_pfunRtfText2Text = (Type_WizToolsRtfText2Text *)GetProcAddress(m_hModule, "WizToolsRtfText2Text");
			m_pfunRtfFile2Text = (Type_WizToolsRtfFile2Text *)GetProcAddress(m_hModule, "WizToolsRtfFile2Text");
			m_pfunConvertToHtmlFile = (Type_WizToolsConvertToHtmlFile *)GetProcAddress(m_hModule, "WizToolsConvertToHtmlFile");
			m_pfunConvertToHtmlFile2 = (Type_WizToolsConvertToHtmlFile2 *)GetProcAddress(m_hModule, "WizToolsConvertToHtmlFile2");
			m_pfunHtmlContentRulesManagerDlg = (Type_WizToolsHtmlContentRulesManagerDlg *)GetProcAddress(m_hModule, "WizToolsHtmlContentRulesManagerDlg");
			m_pfunHtmlContentRulesDownloadAll = (Type_WizToolsHtmlContentRulesDownloadAll *)GetProcAddress(m_hModule, "WizToolsHtmlContentRulesDownloadAll");
			m_pfunHtmlContentRulesUploadAll = (Type_WizToolsHtmlContentRulesUploadAll *)GetProcAddress(m_hModule, "WizToolsHtmlContentRulesUploadAll");
			m_pfunExtractTags = (Type_WizToolsExtractTags *)GetProcAddress(m_hModule, "WizToolsExtractTags");
			m_pfunEnumTableCells = (Type_WizToolsEnumTableCells*)GetProcAddress(m_hModule, "WizToolsEnumTableCells");
			m_pfunURLDownloadToTempFile = (Type_WizToolsURLDownloadToTempFile *)GetProcAddress(m_hModule, "WizToolsURLDownloadToTempFile");
			m_pfunURLDownloadGetHtmlText = (Type_WizToolsURLDownloadGetHtmlText *)GetProcAddress(m_hModule, "WizToolsURLDownloadGetHtmlText");
			m_pfunEnumLinks= (Type_WizToolsEnumLinks*)GetProcAddress(m_hModule, "WizToolsEnumLinks");
			m_pfunLoadUnicodeTextFromFile = (Type_WizToolsLoadUnicodeTextFromFile *)GetProcAddress(m_hModule, "WizToolsLoadUnicodeTextFromFile");
			m_pfunTagGetAttribute = (Type_WizToolsTagGetAttribute *)GetProcAddress(m_hModule, "WizToolsTagGetAttribute");
			m_pfunTagSetAttribute = (Type_WizToolsTagSetAttribute *)GetProcAddress(m_hModule, "WizToolsTagSetAttribute");
			m_pfunFTSDeleteDocument = (Type_WizToolsFTSDeleteDocument *)GetProcAddress(m_hModule, "WizToolsFTSDeleteDocument");
			m_pfunFTSUpdateDocument = (Type_WizToolsFTSUpdateDocument *)GetProcAddress(m_hModule, "WizToolsFTSUpdateDocument");
			m_pfunFTSSearchDocument = (Type_WizToolsFTSSearchDocument *)GetProcAddress(m_hModule, "WizToolsFTSSearchDocument");
			m_pfunFTSOptimizeIndex = (Type_WizToolsFTSOptimizeIndex *)GetProcAddress(m_hModule, "WizToolsFTSOptimizeIndex");
			m_pfunDocumentGetSelection = (Type_WizToolsDocumentGetSelection *)GetProcAddress(m_hModule, "WizToolsDocumentGetSelection");
			m_pfunShowBubbleWindow = (Type_WizToolsShowBubbleWindow *)GetProcAddress(m_hModule, "WizToolsShowBubbleWindow");
			m_pfunShowBubbleWindowEx = (Type_WizToolsShowBubbleWindowEx *)GetProcAddress(m_hModule, "WizToolsShowBubbleWindowEx");
			m_pfunShowBubbleWindow2 = (Type_WizToolsShowBubbleWindow2 *)GetProcAddress(m_hModule, "WizToolsShowBubbleWindow2");
			m_pfunShowBubbleWindow2Ex = (Type_WizToolsShowBubbleWindow2Ex *)GetProcAddress(m_hModule, "WizToolsShowBubbleWindow2Ex");
			m_pfunRunScript = (Type_WizToolsRunScript *)GetProcAddress(m_hModule, "WizToolsRunScript");
			m_pfunRunScript2 = (Type_WizToolsRunScript2 *)GetProcAddress(m_hModule, "WizToolsRunScript2");
			m_pfunParseHtml = (Type_WizToolsParseHtml *)GetProcAddress(m_hModule, "WizToolsParseHtml");
			m_pfunEncrypt_AES256_CBC_PKCS5 = (Type_WizToolsEncrypt_AES256_CBC_PKCS5 *)GetProcAddress(m_hModule, "WizToolsEncrypt_AES256_CBC_PKCS5");
			m_pfunDecrypt_AES256_CBC_PKCS5 = (Type_WizToolsDecrypt_AES256_CBC_PKCS5 *)GetProcAddress(m_hModule, "WizToolsDecrypt_AES256_CBC_PKCS5");
			m_pfunEncrypt_RSA = (Type_WizToolsEncrypt_RSA *)GetProcAddress(m_hModule, "WizToolsEncrypt_RSA");
			m_pfunDecrypt_RSA = (Type_WizToolsDecrypt_RSA *)GetProcAddress(m_hModule, "WizToolsDecrypt_RSA");
			m_pfunGenerateKeyPair_RSA = (Type_WizToolsGenerateKeyPair_RSA *)GetProcAddress(m_hModule, "WizToolsGenerateKeyPair_RSA");
			m_pfunHtml2Mht = (Type_WizToolsHtml2Mht *)GetProcAddress(m_hModule, "WizToolsHtml2Mht");
			m_pfunMht2Html = (Type_WizToolsMht2Html *)GetProcAddress(m_hModule, "WizToolsMht2Html");
			m_pfunLoadMime = (Type_WizToolsLoadMime *)GetProcAddress(m_hModule, "WizToolsLoadMime");
			m_pfunCreateMimeMessageCreator = (Type_WizToolsCreateMimeMessageCreator*)GetProcAddress(m_hModule, "WizToolsCreateMimeMessageCreator");
			m_pfunPDF2Html = (Type_WizToolsPDF2Html *)GetProcAddress(m_hModule, "WizToolsPDF2Html");
			m_pfunPDF2Text = (Type_WizToolsPDF2Text *)GetProcAddress(m_hModule, "WizToolsPDF2Text");
			m_pfunCreateHtmlEditor = (Type_WizToolsCreateHtmlEditor *)GetProcAddress(m_hModule, "WizToolsCreateHtmlEditor");
			m_pfunScreenCapture = (Type_WizToolsScreenCapture *)GetProcAddress(m_hModule, "WizToolsScreenCapture");
			m_pfunScreenCaptureToFile = (Type_WizToolsScreenCaptureToFile *)GetProcAddress(m_hModule, "WizToolsScreenCaptureToFile");
			m_pfunCreateHtmlDocumentByHtmlText = (Type_WizToolsCreateHtmlDocumentByHtmlText *)GetProcAddress(m_hModule, "WizToolsCreateHtmlDocumentByHtmlText");
			m_pfunCreateHtmlDocumentByHtmlFileName = (Type_WizToolsCreateHtmlDocumentByHtmlFileName *)GetProcAddress(m_hModule, "WizToolsCreateHtmlDocumentByHtmlFileName");
			m_pfunHtmlDocumentToHtmlResourceFile = (Type_WizToolsHtmlDocumentToHtmlResourceFile *)GetProcAddress(m_hModule, "WizToolsHtmlDocumentToHtmlResourceFile");
			m_pfunHtmlResourceFileGetExtInfo = (Type_WizToolsHtmlResourceFileGetExtInfo *)GetProcAddress(m_hModule, "WizToolsHtmlResourceFileGetExtInfo");
			m_pfunHtmlResourceFileToHtmlDocument = (Type_WizToolsHtmlResourceFileToHtmlDocument *)GetProcAddress(m_hModule, "WizToolsHtmlResourceFileToHtmlDocument");
			m_pfunHtmlResourceFileClearFiles = (Type_WizToolsHtmlResourceFileClearFiles *)GetProcAddress(m_hModule, "WizToolsHtmlResourceFileClearFiles");

			//
			//
			if (lpszLogFileName)
			{
				SetLogFileName(lpszLogFileName);
			}
			if (lpszSettingsFileName)
			{
				SetSettingsFileName(lpszSettingsFileName);
			}
			//
			SetTempPath(WizGlobal()->GetTempPath());
		}
		else
		{
			TOLOG(WizFormatString1(_T("ErrorCode=%1"), WizIntToStr((int)GetLastError())));
			TOLOG1(_T("Failed to load WizTools.dll: %1"), strFileName);
		}
	}
	virtual ~CWizToolsDll()
	{
	}
public:
	typedef STDMETHODIMP Type_WizToolsSetLogFileName(LPCWSTR lpszLogFileName);
	typedef STDMETHODIMP Type_WizToolsSetTempPath(LPCWSTR lpszTempPath);
	typedef STDMETHODIMP Type_WizToolsSetSettingsFileName(LPCWSTR lpszFileName);
	typedef STDMETHODIMP Type_WizToolsDocument2Html(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszHtmlFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams);
	typedef STDMETHODIMP Type_WizToolsDocument2Mht(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszMhtFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams);
	typedef STDMETHODIMP Type_WizToolsDocument2Zip(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszZipFileName, LPCWSTR lpszHtmlFileNameInZip, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams);
	typedef STDMETHODIMP Type_WizToolsCompressHtml2Zip(LPCWSTR lpszSrcZipFileName, LPCWSTR lpszDestFileName);
	typedef STDMETHODIMP Type_WizToolsHtml2Html(LPCWSTR lpszSrcHtmlFileName, LPCWSTR lpszURL, LPCWSTR lpszDestFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams);
	typedef STDMETHODIMP Type_WizToolsZip2Html(LPCWSTR lpszSrcZipFileName, LPCWSTR lpszDestFileName, LPCWSTR lpszHtmlTitle);
	typedef STDMETHODIMP Type_WizToolsHtmlGetContent(LPCWSTR lpszURL, LPCWSTR lpszHtmlText, BSTR* pbstrContentHtml);
	typedef STDMETHODIMP Type_WizToolsHtml2Text(LPCWSTR lpszHtml, UINT nFlags, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsHtml2TextAndImage(LPCWSTR lpszHtml, UINT nFlags, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsRtfText2Html(const char* lpszRtfText, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsRtfFile2Html(LPCWSTR lpszRtfFileName, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsRtfText2Text(const char* lpszRtfText, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsRtfFile2Text(LPCWSTR lpszRtfFileName, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsConvertToHtmlFile(LPCWSTR lpszFileName, BSTR* pbstrHtmlFileName);
	typedef STDMETHODIMP Type_WizToolsConvertToHtmlFile2(LPCWSTR lpszFileName, long nFlags, BSTR* pbstrHtmlFileName);
	typedef int WINAPI Type_WizToolsHtmlContentRulesManagerDlg(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow);
	typedef STDMETHODIMP Type_WizToolsHtmlContentRulesDownloadAll(LPCWSTR lpszURL, long* pnCount);
	typedef STDMETHODIMP Type_WizToolsHtmlContentRulesUploadAll(LPCWSTR lpszURL, long* pnCount);
	typedef STDMETHODIMP Type_WizToolsExtractTags(LPCWSTR lpszHtmlText, LPCWSTR lpszTagName, LPCWSTR lpszTagAttributeName, LPCWSTR lpszTagAttributeValue, IWizToolsExtractTagsEvents* pEvents);
	typedef STDMETHODIMP Type_WizToolsEnumTableCells(LPCWSTR lpszTableHtmlText, IWizToolsEnumTableCellsEvents* pEvents);
	typedef STDMETHODIMP Type_WizToolsURLDownloadToTempFile(LPCWSTR lpszURL, BSTR* pbstrFileName);
	typedef STDMETHODIMP Type_WizToolsURLDownloadGetHtmlText(LPCWSTR lpszURL, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsEnumLinks(LPCWSTR lpszHtmlText, LPCWSTR lpszURL, IWizToolsEnumLinksEvents* pEvents);
	typedef STDMETHODIMP Type_WizToolsLoadUnicodeTextFromFile(LPCWSTR lpszFileName, BSTR* pbstrText);
	typedef STDMETHODIMP Type_WizToolsTagGetAttribute(LPCWSTR lpszTag, LPCWSTR lpszAttributeName, BSTR* pbstrValue);
	typedef STDMETHODIMP Type_WizToolsTagSetAttribute(LPWSTR lpszTag, long nTagBufferSize, LPCWSTR lpszAttributeName, LPCWSTR lpszValue);
	typedef STDMETHODIMP Type_WizToolsFTSDeleteDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszDocumentID);
	typedef STDMETHODIMP Type_WizToolsFTSUpdateDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszDocumentID, LPCWSTR lpszURL, LPCWSTR lpszText);
	typedef STDMETHODIMP Type_WizToolsFTSSearchDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszKeywords, IWizToolsSearchDocumentsEvents* pEvents);
	typedef STDMETHODIMP Type_WizToolsFTSOptimizeIndex(LPCWSTR lpszIndexPath);
	typedef STDMETHODIMP Type_WizToolsDocumentGetSelection(IHTMLDocument2* pDoc, BOOL bHtml, BSTR* pbstrText, BSTR* pbstrURL);
	typedef int WINAPI Type_WizToolsShowBubbleWindow(LPCWSTR lpszTitle, LPCWSTR lpszSubTitle, LPCWSTR lpszIconFileName, LPCWSTR lpszText, LPCWSTR lpszButtonText, int nDelaySeconds, LPCWSTR lpszExtOptions);
	typedef int WINAPI Type_WizToolsShowBubbleWindowEx(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow);
	typedef int WINAPI Type_WizToolsShowBubbleWindow2(LPCWSTR lpszTitle, LPCWSTR lpszLinkText, LPCWSTR lpszLinkURL, COLORREF crBackground, int nDelaySeconds);
	typedef int WINAPI Type_WizToolsShowBubbleWindow2Ex(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow);
	typedef STDMETHODIMP Type_WizToolsRunScript(HWND hwndParent, LPCWSTR lpszLanguage, LPCTSTR lpszCode);
	typedef int WINAPI Type_WizToolsRunScript2(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow);
	typedef STDMETHODIMP Type_WizToolsParseHtml(LPCWSTR lpszHtml, IWizToolsParseHtmlEvents* pEvents, BSTR* pbstrResult, BSTR* pbstrTextResult);
	typedef STDMETHODIMP Type_WizToolsEncrypt_AES256_CBC_PKCS5(const unsigned char* lpszKey, int nKeyLen, const unsigned char* pIV, int nIVLen, IStream* pStreamSrc, IStream* pStreamDest);
	typedef STDMETHODIMP Type_WizToolsDecrypt_AES256_CBC_PKCS5(const unsigned char* lpszKey, int nKeyLen, const unsigned char* pIV, int nIVLen, IStream* pStreamSrc, IStream* pStreamDest);
	typedef STDMETHODIMP Type_WizToolsEncrypt_RSA(const char* N, const char* e, IStream* pStreamSrc, IStream* pStreamDest);
	typedef STDMETHODIMP Type_WizToolsDecrypt_RSA(const char* N, const char* e, const char* d, IStream* pStreamSrc, IStream* pStreamDest);
	typedef STDMETHODIMP Type_WizToolsGenerateKeyPair_RSA(UINT nLength, BSTR* pbstrN, BSTR* pbstre, BSTR* pbstrd);
	typedef STDMETHODIMP Type_WizToolsHtml2Mht(LPCWSTR lpszHtmlFileName, LPCWSTR lpszMhtFileName);
	typedef STDMETHODIMP Type_WizToolsMht2Html(LPCWSTR lpszMhtFileName, LPCWSTR lpszHtmlFileName);
	typedef STDMETHODIMP Type_WizToolsLoadMime(LPCWSTR lpszMimeFileName, IUnknown** ppUnknown);
	typedef STDMETHODIMP Type_WizToolsCreateMimeMessageCreator(IUnknown** ppUnknown);
	typedef STDMETHODIMP Type_WizToolsPDF2Html(LPCWSTR lpszPDFFileName, LPCWSTR lpszHtmlFileName);
	typedef STDMETHODIMP Type_WizToolsPDF2Text(LPCWSTR lpszPDFFileName, LPCWSTR lpszTextFileName);
	typedef STDMETHODIMP Type_WizToolsCreateHtmlEditor(IWizHtmlEditorEvents* pEvents, IWizHtmlEditor** ppEditor);
	typedef STDMETHODIMP Type_WizToolsScreenCapture(HBITMAP* phbitmap);
	typedef STDMETHODIMP Type_WizToolsScreenCaptureToFile(LPCWSTR lpszFileName);
	typedef STDMETHODIMP Type_WizToolsCreateHtmlDocumentByHtmlText(LPCWSTR lpszHTML, LPCWSTR lpszURL, IHTMLDocument2** p);
	typedef STDMETHODIMP Type_WizToolsCreateHtmlDocumentByHtmlFileName(LPCTSTR lpszFileName, LPCTSTR lpszURL, IHTMLDocument2** p);
	typedef STDMETHODIMP Type_WizToolsHtmlDocumentToHtmlResourceFile(IHTMLDocument2* pDoc, LPCWSTR lpszTempPath, BOOL bSaveSel, LPCWSTR lpszContent, LPCWSTR lpszExtInfo, BSTR* pstrResourceFileName);
	typedef STDMETHODIMP Type_WizToolsHtmlResourceFileGetExtInfo(LPCWSTR lpszFileName, LPCWSTR lpszValueName, LPCWSTR lpszDef, BSTR* pbstrRet);
	typedef STDMETHODIMP Type_WizToolsHtmlResourceFileToHtmlDocument(LPCWSTR lpszFileName, IHTMLDocument2** ppDoc, BOOL* pbSaveSel);
	typedef STDMETHODIMP Type_WizToolsHtmlResourceFileClearFiles(LPCWSTR lpszFileName);

protected:
	HMODULE m_hModule;
	Type_WizToolsSetLogFileName* m_pfunSetLogFileName;
	Type_WizToolsSetTempPath* m_pfunSetTempPath;
	Type_WizToolsSetSettingsFileName* m_pfunSetSettingsFileName;
	Type_WizToolsDocument2Html* m_pfunDocument2Html;
	Type_WizToolsDocument2Mht* m_pfunDocument2Mht;
	Type_WizToolsDocument2Zip* m_pfunDocument2Zip;
	Type_WizToolsCompressHtml2Zip* m_pfunCompressHtml2Zip;
	Type_WizToolsHtml2Html* m_pfunHtml2Html;
	Type_WizToolsZip2Html* m_pfunZip2Html;
	Type_WizToolsHtmlGetContent* m_pfunHtmlGetContent;
	Type_WizToolsHtml2Text* m_pfunHtml2Text;
	Type_WizToolsHtml2TextAndImage* m_pfunHtml2TextAndImage;
	Type_WizToolsRtfText2Html* m_pfunRtfText2Html;
	Type_WizToolsRtfFile2Html* m_pfunRtfFile2Html;
	Type_WizToolsRtfText2Text* m_pfunRtfText2Text;
	Type_WizToolsRtfFile2Text* m_pfunRtfFile2Text;
	Type_WizToolsConvertToHtmlFile* m_pfunConvertToHtmlFile;
	Type_WizToolsConvertToHtmlFile2* m_pfunConvertToHtmlFile2;
	Type_WizToolsHtmlContentRulesManagerDlg* m_pfunHtmlContentRulesManagerDlg;
	Type_WizToolsHtmlContentRulesDownloadAll* m_pfunHtmlContentRulesDownloadAll;
	Type_WizToolsHtmlContentRulesUploadAll* m_pfunHtmlContentRulesUploadAll;
	Type_WizToolsExtractTags* m_pfunExtractTags;
	Type_WizToolsEnumTableCells* m_pfunEnumTableCells;
	Type_WizToolsURLDownloadToTempFile* m_pfunURLDownloadToTempFile;
	Type_WizToolsURLDownloadGetHtmlText* m_pfunURLDownloadGetHtmlText;
	Type_WizToolsEnumLinks* m_pfunEnumLinks;
	Type_WizToolsLoadUnicodeTextFromFile* m_pfunLoadUnicodeTextFromFile;
	Type_WizToolsTagGetAttribute* m_pfunTagGetAttribute;
	Type_WizToolsTagSetAttribute* m_pfunTagSetAttribute;
	Type_WizToolsFTSDeleteDocument* m_pfunFTSDeleteDocument;
	Type_WizToolsFTSUpdateDocument* m_pfunFTSUpdateDocument;
	Type_WizToolsFTSSearchDocument* m_pfunFTSSearchDocument;
	Type_WizToolsFTSOptimizeIndex* m_pfunFTSOptimizeIndex;
	Type_WizToolsDocumentGetSelection* m_pfunDocumentGetSelection;
	Type_WizToolsShowBubbleWindow* m_pfunShowBubbleWindow;
	Type_WizToolsShowBubbleWindowEx* m_pfunShowBubbleWindowEx;
	Type_WizToolsShowBubbleWindow2* m_pfunShowBubbleWindow2;
	Type_WizToolsShowBubbleWindow2Ex* m_pfunShowBubbleWindow2Ex;
	Type_WizToolsRunScript* m_pfunRunScript;
	Type_WizToolsRunScript2* m_pfunRunScript2;
	Type_WizToolsParseHtml* m_pfunParseHtml;
	Type_WizToolsEncrypt_AES256_CBC_PKCS5* m_pfunEncrypt_AES256_CBC_PKCS5;
	Type_WizToolsDecrypt_AES256_CBC_PKCS5* m_pfunDecrypt_AES256_CBC_PKCS5;
	Type_WizToolsEncrypt_RSA* m_pfunEncrypt_RSA;
	Type_WizToolsDecrypt_RSA* m_pfunDecrypt_RSA;
	Type_WizToolsGenerateKeyPair_RSA* m_pfunGenerateKeyPair_RSA;
	Type_WizToolsHtml2Mht* m_pfunHtml2Mht;
	Type_WizToolsMht2Html* m_pfunMht2Html;
	Type_WizToolsLoadMime* m_pfunLoadMime;
	Type_WizToolsCreateMimeMessageCreator* m_pfunCreateMimeMessageCreator;
	Type_WizToolsPDF2Html* m_pfunPDF2Html;
	Type_WizToolsPDF2Text* m_pfunPDF2Text;
	Type_WizToolsCreateHtmlEditor* m_pfunCreateHtmlEditor;
	Type_WizToolsScreenCapture* m_pfunScreenCapture;
	Type_WizToolsScreenCaptureToFile* m_pfunScreenCaptureToFile;
	Type_WizToolsCreateHtmlDocumentByHtmlText* m_pfunCreateHtmlDocumentByHtmlText;
	Type_WizToolsCreateHtmlDocumentByHtmlFileName* m_pfunCreateHtmlDocumentByHtmlFileName;
	Type_WizToolsHtmlDocumentToHtmlResourceFile* m_pfunHtmlDocumentToHtmlResourceFile;
	Type_WizToolsHtmlResourceFileGetExtInfo* m_pfunHtmlResourceFileGetExtInfo;
	Type_WizToolsHtmlResourceFileToHtmlDocument* m_pfunHtmlResourceFileToHtmlDocument;
	Type_WizToolsHtmlResourceFileClearFiles* m_pfunHtmlResourceFileClearFiles;

public:
	HRESULT SetLogFileName(LPCWSTR lpszLogFileName)
	{
		if (!m_pfunSetLogFileName)
			return E_FAIL;
		//
		return m_pfunSetLogFileName(lpszLogFileName);
	}
	HRESULT SetTempPath(LPCWSTR lpszTempPath)
	{
		if (!m_pfunSetTempPath)
			return E_FAIL;
		//
		return m_pfunSetTempPath(lpszTempPath);
	}
	HRESULT SetSettingsFileName(LPCWSTR lpszFileName)
	{
		if (!m_pfunSetSettingsFileName)
			return E_FAIL;
		//
		return m_pfunSetSettingsFileName(lpszFileName);
	}
	HRESULT Document2Html(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszHtmlFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams)
	{
		if (!m_pfunDocument2Html)
			return E_FAIL;
		//
		return m_pfunDocument2Html(pIHTMLDocument2Disp, lpszHtmlFileName, nHtmlSaverFlags, lpszExtParams);
	}
	HRESULT Document2Mht(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszMhtFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams)
	{
		if (!m_pfunDocument2Mht)
			return E_FAIL;
		//
		return m_pfunDocument2Mht(pIHTMLDocument2Disp, lpszMhtFileName, nHtmlSaverFlags, lpszExtParams);
	}
	HRESULT Document2Zip(IDispatch* pIHTMLDocument2Disp, LPCWSTR lpszZipFileName, LPCWSTR lpszHtmlFileNameInZip, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams)
	{
		if (!m_pfunDocument2Zip)
			return E_FAIL;
		//
		return m_pfunDocument2Zip(pIHTMLDocument2Disp, lpszZipFileName, lpszHtmlFileNameInZip, nHtmlSaverFlags, lpszExtParams);
	}
	HRESULT Html2Html(LPCWSTR lpszSrcHtmlFileName, LPCWSTR lpszURL, LPCWSTR lpszDestFileName, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams)
	{
		if (!m_pfunHtml2Html)
			return E_FAIL;
		//
		return m_pfunHtml2Html(lpszSrcHtmlFileName, lpszURL, lpszDestFileName, nHtmlSaverFlags, lpszExtParams);
	}
	//
	HRESULT CompressHtml2Zip(LPCWSTR lpszHtmlFileName, LPCWSTR lpszZipFileName)
	{
		if (!m_pfunCompressHtml2Zip)
			return E_FAIL;
		//
		return m_pfunCompressHtml2Zip(lpszHtmlFileName, lpszZipFileName);
	}

	HRESULT Html2Zip(LPCWSTR lpszSrcHtmlFileName, LPCWSTR lpszURL, LPCWSTR lpszDestFileName, LPCWSTR lpszHtmlFileNameInZip, LONG nHtmlSaverFlags, LPCWSTR lpszExtParams)
	{
		HRESULT hr = Html2Html(lpszSrcHtmlFileName, lpszURL, lpszHtmlFileNameInZip, nHtmlSaverFlags, lpszExtParams);
		if (FAILED(hr))
			return hr;
		//
		return CompressHtml2Zip(lpszHtmlFileNameInZip, lpszDestFileName);
	}
	HRESULT Zip2Html(LPCWSTR lpszSrcZipFileName, LPCWSTR lpszDestFileName, LPCWSTR lpszHtmlTitle)
	{
		if (!m_pfunHtml2Html)
			return E_FAIL;
		//
		return m_pfunZip2Html(lpszSrcZipFileName, lpszDestFileName, lpszHtmlTitle);
	}
	HRESULT HtmlGetContent(LPCWSTR lpszURL, LPCWSTR lpszHtmlText, BSTR* pbstrContentHtml)
	{
		if (!m_pfunHtmlGetContent)
			return E_FAIL;
		//
		return m_pfunHtmlGetContent(lpszURL, lpszHtmlText, pbstrContentHtml);
	}

	HRESULT Html2Text(LPCWSTR lpszHtml, UINT nFlags, BSTR* pbstrText)
	{
		if (!m_pfunHtml2Text)
		{
			TOLOG(_T("No function entry Html2Text"));
			return E_FAIL;
		}
		//
		return m_pfunHtml2Text(lpszHtml, nFlags, pbstrText);
	}
	HRESULT Html2TextAndImage(LPCWSTR lpszHtml, UINT nFlags, BSTR* pbstrText)
	{
		if (!m_pfunHtml2TextAndImage)
			return E_FAIL;
		//
		return m_pfunHtml2TextAndImage(lpszHtml, nFlags, pbstrText);
	}
	HRESULT RtfText2Html(const char* lpszRtfText, BSTR* pbstrHtml)
	{
		if (!m_pfunRtfText2Html)
			return E_FAIL;
		//
		return m_pfunRtfText2Html(lpszRtfText, pbstrHtml);
	}
	HRESULT RtfFile2Html(LPCWSTR lpszRtfFileName, BSTR* pbstrHtml)
	{
		if (!m_pfunRtfFile2Html)
			return E_FAIL;
		//
		return m_pfunRtfFile2Html(lpszRtfFileName, pbstrHtml);
	}
	HRESULT RtfFile2HtmlFile(LPCWSTR lpszRtfFileName, LPCWSTR lpszHtmlFileName)
	{
		CComBSTR bstrHtml;
		HRESULT hr = RtfFile2Html(lpszRtfFileName, &bstrHtml);
		if (FAILED(hr))
			return hr;
		//
		return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, bstrHtml) ? S_OK : E_FAIL;
	}
	HRESULT RtfText2Text(const char* lpszRtfText, BSTR* pbstrHtml)
	{
		if (!m_pfunRtfText2Text)
			return E_FAIL;
		//
		return m_pfunRtfText2Text(lpszRtfText, pbstrHtml);
	}
	HRESULT RtfFile2Text(LPCWSTR lpszRtfFileName, BSTR* pbstrHtml)
	{
		if (!m_pfunRtfFile2Text)
			return E_FAIL;
		//
		return m_pfunRtfFile2Text(lpszRtfFileName, pbstrHtml);
	}
	HRESULT ConvertToHtmlFile(LPCWSTR lpszFileName, BSTR* pbstrHtmlFileName)
	{
		if (!m_pfunConvertToHtmlFile)
			return E_FAIL;
		//
		return m_pfunConvertToHtmlFile(lpszFileName, pbstrHtmlFileName);
	}
	HRESULT ConvertToHtmlFile2(LPCWSTR lpszFileName, long nFlags, BSTR* pbstrHtmlFileName)
	{
		if (!m_pfunConvertToHtmlFile2)
			return E_FAIL;
		//
		return m_pfunConvertToHtmlFile2(lpszFileName, nFlags, pbstrHtmlFileName);
	}
	//
	BOOL ConvertToHtmlFile(LPCTSTR lpszFileName, CString& strHtmlFileName)
	{
		CComBSTR bstrFileName;
		if (FAILED(ConvertToHtmlFile(CStringW(lpszFileName), &bstrFileName)))
		{
			return FALSE;
		}
		//
		strHtmlFileName = CString(bstrFileName);
		return TRUE;
	}
	BOOL ConvertToHtmlFile2(LPCTSTR lpszFileName, long nFlags, CString& strHtmlFileName)
	{
		CComBSTR bstrFileName;
		if (FAILED(ConvertToHtmlFile2(CStringW(lpszFileName), nFlags, &bstrFileName)))
		{
			return FALSE;
		}
		//
		strHtmlFileName = CString(bstrFileName);
		return TRUE;
	}
	int HtmlContentRulesManagerDlg()
	{
		if (!m_pfunHtmlContentRulesManagerDlg)
			return 0;
		//
		m_pfunHtmlContentRulesManagerDlg(NULL, NULL, NULL, 0);
		//
		return 0;
	}
	STDMETHODIMP HtmlContentRulesDownloadAll(LPCWSTR lpszURL, long* pnCount = NULL)
	{
		if (!m_pfunHtmlContentRulesDownloadAll)
			return E_FAIL;
		//
		return m_pfunHtmlContentRulesDownloadAll(lpszURL, pnCount);
	}
	STDMETHODIMP HtmlContentRulesUploadAll(LPCWSTR lpszURL, long* pnCount = NULL)
	{
		if (!m_pfunHtmlContentRulesUploadAll)
			return E_FAIL;
		//
		return m_pfunHtmlContentRulesUploadAll(lpszURL, pnCount);
	}
	STDMETHODIMP URLDownloadToTempFile(LPCWSTR lpszURL, BSTR* pbstrFileName)
	{
		if (!m_pfunURLDownloadToTempFile)
			return E_FAIL;
		//
		return m_pfunURLDownloadToTempFile(lpszURL, pbstrFileName);
	}
	STDMETHODIMP URLDownloadGetHtmlText(LPCWSTR lpszURL, BSTR* pbstrText)
	{
		if (!m_pfunURLDownloadGetHtmlText)
			return E_FAIL;
		//
		return m_pfunURLDownloadGetHtmlText(lpszURL, pbstrText);
	}
	STDMETHODIMP URLDownloadGetHtmlText(LPCWSTR lpszURL, CString& strText)
	{
		CComBSTR bstrText;
		if (FAILED(URLDownloadGetHtmlText(lpszURL, &bstrText)))
			return E_FAIL;
		//
		strText = CString(bstrText);
		//
		return S_OK;
	}
	STDMETHODIMP EnumLinks(LPCWSTR lpszHtmlText, LPCWSTR lpszURL, IWizToolsEnumLinksEvents* pEvents)
	{
		if (!m_pfunEnumLinks)
			return E_FAIL;
		//
		return m_pfunEnumLinks(lpszHtmlText, lpszURL, pEvents);
	}
	STDMETHODIMP ExtractTags(LPCWSTR lpszHtmlText, LPCWSTR lpszTagName, LPCWSTR lpszTagAttributeName, LPCWSTR lpszTagAttributeValue, IWizToolsExtractTagsEvents* pEvents)
	{
		if (!m_pfunExtractTags)
			return E_FAIL;
		//
		return m_pfunExtractTags(lpszHtmlText, lpszTagName, lpszTagAttributeName, lpszTagAttributeValue, pEvents);
	}
	STDMETHODIMP EnumTableCells(LPCWSTR lpszTableHtmlText, IWizToolsEnumTableCellsEvents* pEvents)
	{
		if (!m_pfunEnumTableCells)
			return E_FAIL;
		//
		return m_pfunEnumTableCells(lpszTableHtmlText, pEvents);
	}
	STDMETHODIMP LoadUnicodeTextFromFile(LPCTSTR lpszFileName, CString& strText)
	{
		if (!m_pfunLoadUnicodeTextFromFile)
			return E_FAIL;
		//
		CComBSTR bstrText;
		HRESULT hr = m_pfunLoadUnicodeTextFromFile(lpszFileName, &bstrText);
		if (FAILED(hr))
			return hr;
		//
		strText = CString(bstrText);
		//
		return S_OK;
	}
	STDMETHODIMP TagGetAttribute(LPCWSTR lpszTag, LPCWSTR lpszAttributeName, BSTR* pbstrValue)
	{
		if (!m_pfunTagGetAttribute)
			return E_FAIL;
		//
		return m_pfunTagGetAttribute(lpszTag, lpszAttributeName, pbstrValue);
	}
	STDMETHODIMP TagSetAttribute(LPWSTR lpszTag, long nTagBufferSize, LPCWSTR lpszAttributeName, LPCWSTR lpszValue)
	{
		if (!m_pfunTagSetAttribute)
			return E_FAIL;
		//
		return m_pfunTagSetAttribute(lpszTag, nTagBufferSize, lpszAttributeName, lpszValue);
	}
	//
	STDMETHODIMP EnumLinks(LPCWSTR lpszHtmlText, LPCTSTR lpszURL, CWizHTMLLinkDataArray& arrayLink)
	{
		class CEnumLinksEvents : public IWizToolsEnumLinksEvents
		{
		public:
			CEnumLinksEvents(CWizHTMLLinkDataArray& arr)
				: m_array(arr)
			{
			}
			
			CWizHTMLLinkDataArray& m_array;
		public:
			virtual HRESULT __stdcall OnLink(LPCWSTR lpszURL, LPCWSTR lpszLinkText)
			{
				WIZHTMLLINKDATA data ;
				data.strURL = lpszURL;
				data.strText = lpszLinkText;
				m_array.push_back(data);
				return S_OK;
			}
		};
		CEnumLinksEvents events(arrayLink);
		return EnumLinks(lpszHtmlText, lpszURL, &events);
	}
	STDMETHODIMP ExtractTags(LPCWSTR lpszHtmlText, LPCWSTR lpszTagName, LPCWSTR lpszTagAttributeName, LPCWSTR lpszTagAttributeValue, CWizStdStringArray& arr)
	{
		class CExtractTagsEvents : public IWizToolsExtractTagsEvents
		{
		public:
			CExtractTagsEvents(CWizStdStringArray& arr)
				: m_array(arr)
			{
			}
			CWizStdStringArray& m_array;
		public:
			virtual HRESULT __stdcall OnTag(LPCWSTR lpszTagHtml)
			{
				m_array.push_back(lpszTagHtml);
				return S_OK;
			}
		};
		//
		CExtractTagsEvents events(arr);
		return ExtractTags(lpszHtmlText, lpszTagName, lpszTagAttributeName, lpszTagAttributeValue, &events);
	}
	STDMETHODIMP EnumTableCells(LPCWSTR lpszTableHtmlText, CWizToolsTableCells& cells)
	{
		class CEnumTableCellsEvents : public IWizToolsEnumTableCellsEvents
		{
		public:
			CEnumTableCellsEvents(CWizToolsTableCells& cells)
				: m_cells(cells)
			{
			}
			CWizToolsTableCells& m_cells;
		public:
			virtual HRESULT __stdcall OnCell(long columnIndex, long rowIndex, LPCWSTR lpszCellHtml)
			{
				m_cells.SetCell(columnIndex, rowIndex, lpszCellHtml);
				//
				return S_OK;
			}
		};

		CEnumTableCellsEvents events(cells);
		return EnumTableCells(lpszTableHtmlText, &events);
	}

	CString Html2Text(LPCWSTR lpszHtml, UINT nFlags = 0)
	{
		CComBSTR bstrText;
		Html2Text(lpszHtml, nFlags, &bstrText);
		//
		return CString(bstrText).Trim();
	}
	CString TagGetAttribute(LPCWSTR lpszTag, LPCWSTR lpszAttributeName)
	{
		CComBSTR bstrValue;
		TagGetAttribute(lpszTag, lpszAttributeName, &bstrValue);
		//
		return CString(bstrValue);
	}
	STDMETHODIMP FTSDeleteDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszDocumentID)
	{
		if (!m_pfunFTSDeleteDocument)
			return E_FAIL;
		//
		return m_pfunFTSDeleteDocument(lpszIndexPath, lpszDocumentID);
	}
	STDMETHODIMP FTSUpdateDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszDocumentID, LPCWSTR lpszURL, LPCWSTR lpszText)
	{
		if (!m_pfunFTSUpdateDocument)
			return E_FAIL;
		//
		return m_pfunFTSUpdateDocument(lpszIndexPath, lpszDocumentID, lpszURL, lpszText);
	}
	STDMETHODIMP FTSSearchDocument(LPCWSTR lpszIndexPath, LPCWSTR lpszKeywords, IWizToolsSearchDocumentsEvents* pEvents)
	{
		if (!m_pfunFTSSearchDocument)
			return E_FAIL;
		//
		return m_pfunFTSSearchDocument(lpszIndexPath, lpszKeywords, pEvents);
	}
	STDMETHODIMP FTSOptimizeIndex(LPCWSTR lpszIndexPath)
	{
		if (!m_pfunFTSOptimizeIndex)
			return E_FAIL;
		//
		return m_pfunFTSOptimizeIndex(lpszIndexPath);
	}
	STDMETHODIMP DocumentGetSelection(IHTMLDocument2* pDoc, BOOL bHtml, BSTR* pbstrText, BSTR* pbstrURL)
	{
		if (!m_pfunDocumentGetSelection)
			return E_FAIL;
		//
		if (!pDoc)
			return E_FAIL;
		//
		return m_pfunDocumentGetSelection(pDoc, bHtml, pbstrText, pbstrURL);
	}
	CString DocumentGetSelection(IHTMLDocument2* pDoc, BOOL bHtml, CString* pstrURL = NULL)
	{
		CComBSTR bstrText;
		CComBSTR bstrURL;
		//
		DocumentGetSelection(pDoc, bHtml, &bstrText, &bstrURL);
		//
		if (pstrURL)
		{
			*pstrURL = CString(bstrURL);
		}
		//
		return CString(bstrText);
	}
	int ShowBubbleWindow(LPCWSTR lpszTitle, LPCWSTR lpszSubTitle, LPCWSTR lpszIconFileName, LPCWSTR lpszText, LPCWSTR lpszButtonText, int nDelaySeconds, LPCWSTR lpszExtOptions)
	{
		if (!m_pfunShowBubbleWindow)
			return 0;
		//
		return m_pfunShowBubbleWindow(lpszTitle, lpszSubTitle, lpszIconFileName, lpszText, lpszButtonText, nDelaySeconds, lpszExtOptions);
	}
	int ShowBubbleWindowEx(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow)
	{
		if (!m_pfunShowBubbleWindowEx)
			return 0;
		//
		return m_pfunShowBubbleWindowEx(hwnd, hinst, lpszCmdLine, nCmdShow);
	}
	
	
	int ShowBubbleWindow2(LPCWSTR lpszTitle, LPCWSTR lpszLinkText, LPCWSTR lpszLinkURL, COLORREF crBackground, int nDelaySeconds)
	{
		if (!m_pfunShowBubbleWindow2)
			return 0;
		//
		return m_pfunShowBubbleWindow2(lpszTitle, lpszLinkText, lpszLinkURL, crBackground, nDelaySeconds);
	}
	int ShowBubbleWindow2Ex(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow)
	{
		if (!m_pfunShowBubbleWindow2Ex)
			return 0;
		//
		return m_pfunShowBubbleWindow2Ex(hwnd, hinst, lpszCmdLine, nCmdShow);
	}
	STDMETHODIMP RunScript(HWND hwndParent, LPCWSTR lpszLanguage, LPCTSTR lpszCode)
	{
		if (!m_pfunRunScript)
			return -1000;
		//
		return m_pfunRunScript(hwndParent, lpszLanguage, lpszCode);
	}
	int RunScript2(HWND hwnd, HINSTANCE hinst, LPCWSTR lpszCmdLine, int nCmdShow)
	{
		if (!m_pfunRunScript2)
			return -1000;
		//
		return m_pfunRunScript2(hwnd, hinst, lpszCmdLine, nCmdShow);
	}
	STDMETHODIMP ParseHtml(LPCWSTR lpszHtml, IWizToolsParseHtmlEvents* pEvents, BSTR* pbstrResult, BSTR* pbstrTextResult)
	{
		if (!m_pfunParseHtml)
			return E_FAIL;
		//
		return m_pfunParseHtml(lpszHtml, pEvents, pbstrResult, pbstrTextResult);
	}
	STDMETHODIMP ParseHtml(LPCWSTR lpszHtml, IWizToolsParseHtmlEvents* pEvents, CString& strResult, CString& strTextResult)
	{
		CComBSTR bstrResult;
		CComBSTR bstrTextResult;
		//
		HRESULT hr = ParseHtml(lpszHtml, pEvents, &bstrResult, &bstrTextResult);
		if (FAILED(hr))
			return hr;
		//
		strResult = CString(bstrResult);
		strTextResult = CString(bstrTextResult);
		//
		return hr;
	}
	STDMETHODIMP Encrypt_AES256_CBC_PKCS5(const unsigned char* lpszKey, int nKeyLen, const unsigned char* pIV, int nIVLen, IStream* pStreamSrc, IStream* pStreamDest)
	{
		if (!m_pfunEncrypt_AES256_CBC_PKCS5)
			return E_FAIL;
		//
		return m_pfunEncrypt_AES256_CBC_PKCS5(lpszKey, nKeyLen, pIV, nIVLen, pStreamSrc, pStreamDest);
	}
	//
#define s_lpszIV	(const unsigned char *)"0123456789abcdef"
#define s_nIVLen	16
	//
	STDMETHODIMP Encrypt_AES(const char* lpszKey, IStream* pStreamSrc, IStream* pStreamDest)
	{
		return Encrypt_AES256_CBC_PKCS5((const unsigned char *)lpszKey, int(strlen((const char*)lpszKey)), s_lpszIV, s_nIVLen, pStreamSrc, pStreamDest);
	}
	STDMETHODIMP Encrypt_AES(const char* lpszKey, IStream* pStreamSrc)
	{
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Out of memory!"));
			return hr;
		}
		//
		hr = Encrypt_AES(lpszKey, pStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to enrypt stream!"));
			return hr;
		}
		//
		if (!::WizStreamCopy(spStreamDest, pStreamSrc))
		{
			TOLOG(_T("Failed to copy stream!"));
			return E_FAIL;
		}
		//
		return S_OK;
	}
	STDMETHODIMP Decrypt_AES256_CBC_PKCS5(const unsigned char* lpszKey, int nKeyLen, const unsigned char* pIV, int nIVLen, IStream* pStreamSrc, IStream* pStreamDest)
	{
		if (!m_pfunDecrypt_AES256_CBC_PKCS5)
			return E_FAIL;
		//
		return m_pfunDecrypt_AES256_CBC_PKCS5(lpszKey, nKeyLen, pIV, nIVLen, pStreamSrc, pStreamDest);
	}
	STDMETHODIMP Decrypt_AES(const char* lpszKey, IStream* pStreamSrc, IStream* pStreamDest)
	{
		return Decrypt_AES256_CBC_PKCS5((const unsigned char *)lpszKey, int(strlen((const char*)lpszKey)), s_lpszIV, s_nIVLen, pStreamSrc, pStreamDest);
	}
	STDMETHODIMP Decrypt_AES(const char* lpszKey, IStream* pStreamSrc)
	{
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Out of memory!"));
			return hr;
		}
		//
		hr = Decrypt_AES(lpszKey, pStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to decrypt stream!"));
			return hr;
		}
		//
		if (!::WizStreamCopy(spStreamDest, pStreamSrc))
		{
			TOLOG(_T("Failed to copy stream!"));
			return E_FAIL;
		}
		//
		return S_OK;
	}
	CComPtr<IStream> UnicodeStringToUTF8Stream(LPCTSTR lpsz)
	{
		CStringA strStringA = ::WizBSTR2UTF8(lpsz);
		//
		CComPtr<IStream> spStream;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStream);
		if (FAILED(hr) || !spStream)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return NULL;
		}
		//
		if (!WizStreamWrite(spStream, strStringA, strStringA.GetLength()))
		{
			TOLOG(_T("Failed to call WizStreamWrite"));
			return NULL;
		}
		WizStreamSeekToBegin(spStream);
		//
		return spStream;
	}
	CString UTF8StreamToUnicodeString(IStream* pStream)
	{
		WizStreamSeekToBegin(pStream);
		//
		CStringA strTextA;
		if (!WizStreamLoadAnsiText(pStream, strTextA))
		{
			TOLOG(_T("Failed to call WizStreamLoadAnsiText"));
			return CString();
		}
		//
		CString strText = ::WizUTF82BSTR(strTextA);
		//
		return strText;
	}
	CString BinStreamToBase64String(IStream* pStream)
	{
		WizStreamSeekToBegin(pStream);
		//
		CStringA strRetA;
		WizBase64Encode(pStream, strRetA);
		strRetA.Replace("\r", "");
		strRetA.Replace("\n", "");
		//
		return CString(strRetA);
	}
	CComPtr<IStream> Base64StringToBinStream(LPCTSTR lpsz)
	{
		CComPtr<IStream> spStream;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStream);
		if (FAILED(hr) || !spStream)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return NULL;
		}
		if (!::WizBase64Decode(CStringA(lpsz), spStream))
		{
			TOLOG(_T("Failed to call WizBase64Decode"));
			return NULL;
		}
		WizStreamSeekToBegin(spStream);
		//
		return spStream;
	}
	BOOL EncryptString_AES(LPCTSTR lpszPassword, LPCTSTR lpszString, CString& strRet)
	{
		CString strDefault(lpszString);
		if (!lpszPassword || ! *lpszPassword)
			return FALSE;
		//
		if (!lpszString || ! *lpszString)
			return FALSE;
		//
		CStringA strKey(lpszPassword);
		//
		CComPtr<IStream> spStreamSrc = UnicodeStringToUTF8Stream(lpszString);
		if (!spStreamSrc)
		{
			TOLOG(_T("Failed to call UnicodeStringToUTF8Stream"));
			return FALSE;
		}
		//
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr) || !spStreamDest)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return FALSE;
		}
		//
		hr = Encrypt_AES(strKey, spStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to call Encrypt_AES"));
			return FALSE;
		}
		//
		strRet = BinStreamToBase64String(spStreamDest);
		return TRUE;
	}
	//
	BOOL DecryptString_AES(LPCTSTR lpszPassword, LPCTSTR lpszEncryptedString, CString& strRet)
	{
		CString strDefault(lpszEncryptedString);
		if (!lpszPassword || ! *lpszPassword)
			return FALSE;
		//
		if (!lpszEncryptedString || ! *lpszEncryptedString)
			return FALSE;
		//
		CStringA strKey(lpszPassword);
		//
		CComPtr<IStream> spStreamSrc = Base64StringToBinStream(lpszEncryptedString);
		if (!spStreamSrc)
		{
			TOLOG(_T("Failed to call Base64StringToBinStream"));
			return FALSE;
		}
		//
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr) || !spStreamDest)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return FALSE;
		}
		//
		hr = Decrypt_AES(strKey, spStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to call Decrypt_AES"));
			return FALSE;
		}
		//
		strRet = UTF8StreamToUnicodeString(spStreamDest);
		return TRUE;
	}
	//
	STDMETHODIMP Encrypt_RSA(const char* N, const char* e, IStream* pStreamSrc, IStream* pStreamDest)
	{
		if (!m_pfunEncrypt_RSA)
			return E_FAIL;
		//
		return m_pfunEncrypt_RSA(N, e, pStreamSrc, pStreamDest);
	}
	//
	STDMETHODIMP Decrypt_RSA(const char* N, const char* e, const char* d, IStream* pStreamSrc, IStream* pStreamDest)
	{
		if (!m_pfunDecrypt_RSA)
			return E_FAIL;
		//
		return m_pfunDecrypt_RSA(N, e, d, pStreamSrc, pStreamDest);
	}
	STDMETHODIMP Decrypt_RSA(const char* N, const char* e, const char* d, const BYTE* pBuffer, UINT nBufferSize, IStream* pStreamDest)
	{
		CComPtr<IStream> spStreamSrc;
		if (FAILED(::CreateStreamOnHGlobal(NULL, TRUE, &spStreamSrc)))
		{
			TOLOG(_T("Out of memory!"));
			return E_FAIL;
		}
		//
		if (!WizStreamWrite(spStreamSrc, pBuffer, nBufferSize))
		{
			TOLOG(_T("Failed to write data to stream!"));
			return E_FAIL;
		}
		//
		return Decrypt_RSA(N, e, d, spStreamSrc, pStreamDest);
	}
	CComPtr<IStream> Decrypt_RSA(const char* N, const char* e, const char* d, const BYTE* pBuffer, UINT nBufferSize)
	{
		CComPtr<IStream> spStreamDest;
		if (FAILED(::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest)))
		{
			TOLOG(_T("Out of memory!"));
			return NULL;
		}
		//
		HRESULT hr = Decrypt_RSA(N, e, d, pBuffer, nBufferSize, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to decrypt data!"));
			return NULL;
		}
		//
		return spStreamDest;
	}

	CComPtr<IStream> EncryptString_RSA_ReturnStream(const char* N, const char* e, LPCTSTR lpszString)
	{
		CString strDefault(lpszString);
		if (!N || ! *N)
			return NULL;
		if (!e || ! *e)
			return NULL;
		//
		if (!lpszString || ! *lpszString)
			return NULL;
		//
		CComPtr<IStream> spStreamSrc = UnicodeStringToUTF8Stream(lpszString);
		if (!spStreamSrc)
		{
			TOLOG(_T("Failed to call UnicodeStringToUTF8Stream"));
			return NULL;
		}
		//
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr) || !spStreamDest)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return NULL;
		}
		//
		hr = Encrypt_RSA(N, e, spStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to call Encrypt_AES"));
			return NULL;
		}
		WizStreamSeekToBegin(spStreamDest);
		return spStreamDest;
	}
	BOOL EncryptString_RSA(const char* N, const char* e, LPCTSTR lpszString, CString& strRet)
	{
		CString strDefault(lpszString);
		if (!N || ! *N)
			return FALSE;
		if (!e || ! *e)
			return FALSE;
		//
		if (!lpszString || ! *lpszString)
			return FALSE;
		//
		CComPtr<IStream> spStreamSrc = UnicodeStringToUTF8Stream(lpszString);
		if (!spStreamSrc)
		{
			TOLOG(_T("Failed to call UnicodeStringToUTF8Stream"));
			return FALSE;
		}
		//
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr) || !spStreamDest)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return FALSE;
		}
		//
		hr = Encrypt_RSA(N, e, spStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to call Encrypt_AES"));
			return FALSE;
		}
		//
		strRet = BinStreamToBase64String(spStreamDest);
		return TRUE;
	}
	BOOL EncryptString_RSA(const WIZRSAKEYPAIR& key, LPCTSTR lpszString, CString& strRet)
	{
		return EncryptString_RSA(CStringA(key.str_N), CStringA(key.str_e), lpszString, strRet);
	}
	//
	BOOL DecryptString_RSA(const char* N, const char* e, const char* d, LPCTSTR lpszEncryptedString, CString& strRet)
	{
		CString strDefault(lpszEncryptedString);
		if (!N || ! *N)
			return FALSE;
		if (!e || ! *e)
			return FALSE;
		if (!d || ! *d)
			return FALSE;
		//
		if (!lpszEncryptedString || ! *lpszEncryptedString)
			return FALSE;
		//
		CComPtr<IStream> spStreamSrc = Base64StringToBinStream(lpszEncryptedString);
		if (!spStreamSrc)
		{
			TOLOG(_T("Failed to call Base64StringToBinStream"));
			return FALSE;
		}
		//
		CComPtr<IStream> spStreamDest;
		HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStreamDest);
		if (FAILED(hr) || !spStreamDest)
		{
			TOLOG(_T("Failed to call CreateStreamOnHGlobal"));
			return FALSE;
		}
		//
		hr = Decrypt_RSA(N, e, d, spStreamSrc, spStreamDest);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to call Decrypt_AES"));
			return FALSE;
		}
		//
		strRet = UTF8StreamToUnicodeString(spStreamDest);
		return TRUE;
	}
	BOOL DecryptString_RSA(const WIZRSAKEYPAIR& key, LPCTSTR lpszEncryptedString, CString& strRet)
	{
		return DecryptString_RSA(CStringA(key.str_N), CStringA(key.str_e), CStringA(key.str_d), lpszEncryptedString, strRet);
	}

	//
	STDMETHODIMP GenerateKeyPair_RSA(UINT nLength, BSTR* pbstrN, BSTR* pbstre, BSTR* pbstrd)
	{
		if (!m_pfunGenerateKeyPair_RSA)
			return E_FAIL;
		//
		return m_pfunGenerateKeyPair_RSA(nLength, pbstrN, pbstre, pbstrd);
	}
	STDMETHODIMP GenerateKeyPair_RSA(UINT nLength, CString& strN, CString& stre, CString& strd)
	{
		CComBSTR bstrN;
		CComBSTR bstre;
		CComBSTR bstrd;
		HRESULT hr = GenerateKeyPair_RSA(nLength, &bstrN, &bstre, &bstrd);
		if (FAILED(hr))
			return hr;
		//
		strN = CString(bstrN);
		stre = CString(bstre);
		strd = CString(bstrd);
		//
		return hr;
	}
	STDMETHODIMP GenerateKeyPair_RSA(CString& strN, CString& stre, CString& strd)
	{
		return GenerateKeyPair_RSA(1024, strN, stre, strd);
	}
	STDMETHODIMP GenerateKeyPair_RSA(WIZRSAKEYPAIR& key)
	{
		return GenerateKeyPair_RSA(key.str_N, key.str_e, key.str_d);
	}
	
	STDMETHODIMP Html2Mht(LPCTSTR lpszHtmlFileName, LPCTSTR lpszMhtFileName)
	{
		if (!m_pfunHtml2Mht)
			return E_FAIL;
		//
		return m_pfunHtml2Mht(CStringW(lpszHtmlFileName), CStringW(lpszMhtFileName));
		//
	}
	STDMETHODIMP Mht2Html(LPCTSTR lpszMhtFileName, LPCTSTR lpszHtmlFileName)
	{
		if (!m_pfunMht2Html)
			return E_FAIL;
		//
		return m_pfunMht2Html(CStringW(lpszMhtFileName), CStringW(lpszHtmlFileName));
	}
	STDMETHODIMP LoadMime(LPCTSTR lpszMimeFileName, IUnknown** ppUnknown)
	{
		if (!m_pfunLoadMime)
			return E_FAIL;
		//
		return m_pfunLoadMime(CStringW(lpszMimeFileName), ppUnknown);
	}
	STDMETHODIMP CreateMimeMessageCreator(IUnknown** ppUnknown)
	{
		if (!m_pfunCreateMimeMessageCreator)
			return E_FAIL;
		//
		return m_pfunCreateMimeMessageCreator(ppUnknown);
	}
	HRESULT PDF2Html(LPCWSTR lpszPDFFileName, LPCWSTR lpszHtmlFileName)
	{
		if (!m_pfunPDF2Html)
			return E_FAIL;
		//
		return m_pfunPDF2Html(lpszPDFFileName, lpszHtmlFileName);
	}
	HRESULT PDF2Text(LPCWSTR lpszPDFFileName, LPCWSTR lpszTextFileName)
	{
		if (!m_pfunPDF2Text)
			return E_FAIL;
		//
		return m_pfunPDF2Text(lpszPDFFileName, lpszTextFileName);
	}
	STDMETHODIMP CreateHtmlEditor(IWizHtmlEditorEvents* pEvents, IWizHtmlEditor** ppEditor)
	{
		if (!m_pfunCreateHtmlEditor)
			return E_FAIL;
		//
		return m_pfunCreateHtmlEditor(pEvents, ppEditor);
	}
	STDMETHODIMP ScreenCapture(HBITMAP* phbitmap)
	{
		if (!m_pfunScreenCapture)
			return E_FAIL;
		//
		return m_pfunScreenCapture(phbitmap);
	}
	STDMETHODIMP ScreenCaptureToFile(LPCWSTR lpszFileName)
	{
		if (!m_pfunScreenCaptureToFile)
			return E_FAIL;
		//
		return m_pfunScreenCaptureToFile(lpszFileName);
	}
	//
	STDMETHODIMP CreateHtmlDocumentByHtmlText(LPCWSTR lpszHtmlText, LPCWSTR lpszURL, IHTMLDocument2** p)
	{
		if (!m_pfunCreateHtmlDocumentByHtmlText)
			return E_FAIL;
		//
		return m_pfunCreateHtmlDocumentByHtmlText(lpszHtmlText, lpszURL, p);
	}
	
	STDMETHODIMP CreateHtmlDocumentByHtmlFileName(LPCWSTR lpszHtmlFileName, LPCWSTR lpszURL, IHTMLDocument2** p)
	{
		if (!m_pfunCreateHtmlDocumentByHtmlFileName)
			return E_FAIL;
		//
		return m_pfunCreateHtmlDocumentByHtmlFileName(lpszHtmlFileName, lpszURL, p);
	}
	//
	CComPtr<IHTMLDocument2> CreateHtmlDocumentByHtmlText(LPCWSTR lpszHtmlText, LPCWSTR lpszURL)
	{
		CComPtr<IHTMLDocument2> spDoc;
		CreateHtmlDocumentByHtmlText(lpszHtmlText, lpszURL, &spDoc);
		//
		return spDoc;
	}
	CComPtr<IHTMLDocument2> CreateHtmlDocumentByHtmlFileName(LPCWSTR lpszHtmlFileName, LPCWSTR lpszURL)
	{
		CComPtr<IHTMLDocument2> spDoc;
		CreateHtmlDocumentByHtmlFileName(lpszHtmlFileName, lpszURL, &spDoc);
		//
		return spDoc;
	}
	//
	STDMETHODIMP HtmlDocumentToHtmlResourceFile(IHTMLDocument2* pDoc, LPCWSTR lpszTempPath, BOOL bSaveSel, LPCWSTR lpszContent, LPCWSTR lpszExtInfo, BSTR* pstrResourceFileName)
	{
		if (!m_pfunHtmlDocumentToHtmlResourceFile)
			return E_FAIL;
		//
		return m_pfunHtmlDocumentToHtmlResourceFile(pDoc, lpszTempPath, bSaveSel, lpszContent, lpszExtInfo, pstrResourceFileName);
	}
	STDMETHODIMP HtmlResourceFileGetExtInfo(LPCWSTR lpszFileName, LPCWSTR lpszValueName, LPCWSTR lpszDef, BSTR* pbstrRet)
	{
		if (!m_pfunHtmlResourceFileGetExtInfo)
			return E_FAIL;
		//
		return m_pfunHtmlResourceFileGetExtInfo(lpszFileName, lpszValueName, lpszDef, pbstrRet);
	}
	STDMETHODIMP HtmlResourceFileToHtmlDocument(LPCWSTR lpszFileName, IHTMLDocument2** ppDoc, BOOL* pbSaveSel)
	{
		if (!m_pfunHtmlResourceFileToHtmlDocument)
			return E_FAIL;
		//
		return m_pfunHtmlResourceFileToHtmlDocument(lpszFileName, ppDoc, pbSaveSel);
	}
	STDMETHODIMP HtmlResourceFileClearFiles(LPCWSTR lpszFileName)
	{
		if (!m_pfunHtmlResourceFileClearFiles)
			return E_FAIL;
		//
		return m_pfunHtmlResourceFileClearFiles(lpszFileName);
	}
	//

	CString HtmlDocumentToHtmlResourceFile(IHTMLDocument2* pDoc, LPCWSTR lpszTempPath, BOOL bSaveSel, LPCWSTR lpszContent, LPCWSTR lpszExtInfo)
	{
		CComBSTR bstrResourceFileName;
		if (FAILED(HtmlDocumentToHtmlResourceFile(pDoc, lpszTempPath, bSaveSel, lpszContent, lpszExtInfo, &bstrResourceFileName)))
			return CString();
		//
		CString strResourceFileName = CString(bstrResourceFileName);
		//
		return strResourceFileName;
	}
	CString HtmlResourceFileGetExtInfo(LPCWSTR lpszFileName, LPCWSTR lpszValueName, LPCWSTR lpszDef)
	{
		CComBSTR bstrRet;
		if (FAILED(HtmlResourceFileGetExtInfo(lpszFileName, lpszValueName, lpszDef, &bstrRet)))
			return CString(lpszDef);
		//
		return CString(bstrRet);
	}
	BOOL HtmlResourceFileToHtmlDocument(LPCWSTR lpszFileName, IHTMLDocument2** ppDoc, BOOL& bSaveSel)
	{
		return SUCCEEDED(HtmlResourceFileToHtmlDocument(lpszFileName, ppDoc, &bSaveSel));
	}
};



inline BOOL WizRtf2Html_WizTools(LPCSTR lpszRtfText, CStringW& strHtmlText)
{
	CWizToolsDll dll(NULL, NULL);
	CComBSTR bstrHtml;
	if (SUCCEEDED(dll.RtfText2Html(lpszRtfText, &bstrHtml)))
	{
		strHtmlText = bstrHtml;
		return TRUE;
	}
	//
	return FALSE;
}

inline BOOL WizRtfFile2HtmlFile_WizTools(LPCTSTR lpszRtfFileName, LPCTSTR lpszHtmlFileName)
{
	CWizToolsDll dll(NULL, NULL);
	CComBSTR bstrHtml;
	if (SUCCEEDED(dll.RtfFile2Html(lpszRtfFileName, &bstrHtml)))
	{
		return WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, bstrHtml);
	}
	//
	return FALSE;
}

inline BOOL WizClipboardRtf2Html_WizTools(CStringW& strHtmlText)
{
	WIZCLIPBOARDINFO info;
	if (!WizGetClipboardInfo(info))
		return FALSE;
	//
	if (!info.bHasRTF)
		return FALSE;
	//
	return WizRtf2Html_WizTools(info.GetRTFText(), strHtmlText);
}

///////////////////////////////////////////////////////////////////

inline BOOL WizRtf2Text_WizTools(LPCSTR lpszRtfText, CStringW& strText)
{
	CWizToolsDll dll(NULL, NULL);
	CComBSTR bstrText;
	if (SUCCEEDED(dll.RtfText2Text(lpszRtfText, &bstrText)))
	{
		strText = bstrText;
		return TRUE;
	}
	//
	return FALSE;
}

inline BOOL WizRtfFile2TextFile_WizTools(LPCTSTR lpszRtfFileName, LPCTSTR lpszTextFileName)
{
	CWizToolsDll dll(NULL, NULL);
	CComBSTR bstrText;
	if (SUCCEEDED(dll.RtfFile2Text(lpszRtfFileName, &bstrText)))
	{
		return WizSaveUnicodeTextToUnicodeFile(lpszTextFileName, bstrText);
	}
	//
	return FALSE;
}

inline BOOL WizClipboardRtf2Text_WizTools(CStringW& strText)
{
	WIZCLIPBOARDINFO info;
	if (!WizGetClipboardInfo(info))
		return FALSE;
	//
	if (!info.bHasRTF)
		return FALSE;
	//
	return WizRtf2Text_WizTools(info.GetRTFText(), strText);
}

#endif //_WIZTOOLSDLL_H_
