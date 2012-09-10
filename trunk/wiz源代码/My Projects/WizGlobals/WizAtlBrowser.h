#ifndef _WIZATLBROWSER_H_
#define _WIZATLBROWSER_H_

#pragma once

#include <ExDispid.h>
#include <ComDef.h>
#include <mshtml.h>

#include "WizAtlHostEx.h"

#include "WizIEBase.h"

class CAtlWebBrowserEventsBase
{
protected:
	static _ATL_FUNC_INFO StatusTextChangeStruct;
	static _ATL_FUNC_INFO TitleChangeStruct;
	static _ATL_FUNC_INFO PropertyChangeStruct;
	static _ATL_FUNC_INFO OnQuitStruct;
	static _ATL_FUNC_INFO OnToolBarStruct;
	static _ATL_FUNC_INFO OnMenuBarStruct;
	static _ATL_FUNC_INFO OnStatusBarStruct;
	static _ATL_FUNC_INFO OnFullScreenStruct;
	static _ATL_FUNC_INFO OnTheaterModeStruct;
	static _ATL_FUNC_INFO DownloadBeginStruct;
	static _ATL_FUNC_INFO DownloadCompleteStruct;
	static _ATL_FUNC_INFO NewWindow2Struct; 
	static _ATL_FUNC_INFO NewWindow3Struct;
	static _ATL_FUNC_INFO CommandStateChangeStruct;
	static _ATL_FUNC_INFO BeforeNavigate2Struct;
	static _ATL_FUNC_INFO ProgressChangeStruct;
	static _ATL_FUNC_INFO NavigateComplete2Struct;
	static _ATL_FUNC_INFO DocumentComplete2Struct;
	static _ATL_FUNC_INFO OnVisibleStruct;
	static _ATL_FUNC_INFO SetSecureLockIconStruct;
	static _ATL_FUNC_INFO NavigateErrorStruct;
	static _ATL_FUNC_INFO PrivacyImpactedStateChangeStruct;
	//static _ATL_FUNC_INFO FileDownloadStruct;   // Unsafe to use
	//static _ATL_FUNC_INFO WindowClosingStruct;
};

template<class T, UINT nID = 0>
class CAtlWebBrowser 
	: public CAtlWebBrowserEventsBase 
	, public IDispEventSimpleImpl<nID, CAtlWebBrowser<T>, &DIID_DWebBrowserEvents2>
	, public IDocHostUIHandlerDispatch
	, public IZoomEvents
	, public IWizBrowserScriptError
{
	typedef CAtlWebBrowser<T, nID> thisClass;
public:
	enum RefreshConstants
	{
		REFRESH_NORMAL = 0,
		REFRESH_IFEXPIRED = 1,
		REFRESH_CONTINUE = 2,
		REFRESH_COMPLETELY = 3
	};
	//
	BOOL m_bNoMenu;
	BOOL m_bNo3DBorder;
	BOOL m_bNoScroll;
	BOOL m_bNoScript;
	BOOL m_bDialog;
	BOOL m_bNewWindow;
	BOOL m_bNoScriptError;
	BOOL m_bSilent;
	int m_nInitZoom;
	DWORD m_dwNavigateTickCount;
	
	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()
		
	BEGIN_SINK_MAP(thisClass)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_STATUSTEXTCHANGE, __StatusTextChange, &StatusTextChangeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_PROGRESSCHANGE, __ProgressChange, &ProgressChangeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_COMMANDSTATECHANGE, __CommandStateChange, &CommandStateChangeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_DOWNLOADBEGIN, __DownloadBegin, &DownloadBeginStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_DOWNLOADCOMPLETE, __DownloadComplete, &DownloadCompleteStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_TITLECHANGE, __TitleChange, &TitleChangeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, __NavigateComplete2, &NavigateComplete2Struct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, __BeforeNavigate2, &BeforeNavigate2Struct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_PROPERTYCHANGE, __PropertyChange, &PropertyChangeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW2, __NewWindow2, &NewWindow2Struct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW3, __NewWindow3, &NewWindow3Struct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, __DocumentComplete, &DocumentComplete2Struct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONQUIT, __OnQuit, &OnQuitStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONVISIBLE, __OnVisible, &OnVisibleStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONTOOLBAR, __OnToolBar, &OnToolBarStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONMENUBAR, __OnMenuBar, &OnMenuBarStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONSTATUSBAR, __OnStatusBar, &OnStatusBarStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONFULLSCREEN, __OnFullScreen, &OnFullScreenStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_ONTHEATERMODE, __OnTheaterMode, &OnTheaterModeStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_SETSECURELOCKICON, __SetSecureLockIcon, &SetSecureLockIconStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_NAVIGATEERROR, __NavigateError, &NavigateErrorStruct)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_PRIVACYIMPACTEDSTATECHANGE, __PrivacyImpactedStateChange, &PrivacyImpactedStateChangeStruct)
		//SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_WINDOWCLOSING, __WindowClosing, &WindowClosingStruct)
		//SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, DISPID_FILEDOWNLOAD, __FileDownload, &FileDownloadStruct)
	END_SINK_MAP()
		
	CAtlWebBrowser()
	{
		m_bState[back]=m_bState[forward]=FALSE;
		m_bNoMenu = FALSE;
		m_bNo3DBorder = FALSE;
		m_bNoScroll = FALSE;
		m_bNoScript = TRUE;
		m_bNewWindow = FALSE;
		m_bDialog = FALSE;
		m_bNoScriptError = TRUE;
		m_bSilent = FALSE;
		m_nInitZoom = -1;
		m_dwNavigateTickCount = 0;
	}
	//
public:
	STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject)
	{
		ATLASSERT(ppvObject != NULL);
		if (ppvObject == NULL)
			return E_POINTER;
		*ppvObject = NULL;

		if (InlineIsEqualGUID(riid, IID_NULL))
			return E_NOINTERFACE;

		if (InlineIsEqualUnknown(riid))
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else if (InlineIsEqualGUID(riid, __uuidof(IDispatch)))
		{
			*ppvObject = (IDispatch *)this;
			AddRef();
			return S_OK;
		}
		else if (InlineIsEqualGUID(riid, __uuidof(IZoomEvents)))
		{
			*ppvObject = (IZoomEvents *)this;
			AddRef();
			return S_OK;
		}
		else if (InlineIsEqualGUID(riid, __uuidof(IWizBrowserScriptError)))
		{
			*ppvObject = (IWizBrowserScriptError *)this;
			AddRef();
			return S_OK;
		}
		else
			return E_NOINTERFACE;
	}

	// These are here only to support use in non-COM objects	
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1;
	}
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return 1;
	}
	//
    STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)
	{
		return E_NOTIMPL;
	}
    STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
	{
		return E_NOTIMPL;
	}
    STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
	{
		return E_NOTIMPL;
	}
	
    STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
	{
		return IDispEventSimpleImpl::Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	}

	STDMETHOD(ShowContextMenu)(DWORD dwID, DWORD x, DWORD y, IUnknown *pcmdtReserved, IDispatch *pdispReserved, HRESULT *dwRetVa)
	{
		if (m_bNoMenu)
		{
			*dwRetVa = S_OK;
			return S_OK;
		}
		//
		return S_FALSE;
	}
	STDMETHOD(GetHostInfo)(DWORD *pdwFlags, DWORD *pdwDoubleClick)
	{
		*pdwFlags = GetDocHostUIFlags();
		return S_OK;
	}
	STDMETHOD(ShowUI)(DWORD dwID, IUnknown *pActiveObject, IUnknown *pCommandTarget, IUnknown *pFrame, IUnknown *pDoc, HRESULT *dwRetVa)
	{
		return S_FALSE;
	}
	STDMETHOD(HideUI)(void)
	{
		return S_OK;
	}
	STDMETHOD(UpdateUI)(void)
	{
		return S_OK;
	}
	STDMETHOD(EnableModeless)(VARIANT_BOOL fEnable)
	{
		return S_OK;
	}
	STDMETHOD(OnDocWindowActivate)(VARIANT_BOOL fActivate)
	{
		return S_OK;
	}
	STDMETHOD(OnFrameWindowActivate)(VARIANT_BOOL fActivate)
	{
		return S_OK;
	}
	STDMETHOD(ResizeBorder)(long left, long top, long right, long bottom, IUnknown *pUIWindow, VARIANT_BOOL fFrameWindow)
	{
		return S_OK;
	}
	STDMETHOD(TranslateAccelerator)(DWORD_PTR hWnd, DWORD nMessage, DWORD_PTR wParam, DWORD_PTR lParam, BSTR bstrGuidCmdGroup, DWORD nCmdID, HRESULT *dwRetVal)
	{
		return S_FALSE;
	}
	STDMETHOD(GetOptionKeyPath)(OLECHAR **, DWORD)
	{
		return S_FALSE;
	}
	STDMETHOD(GetDropTarget)(IUnknown *pDropTarget, IUnknown **ppDropTarget)
	{
		return S_FALSE;
	}
	STDMETHOD(GetExternal)(LPDISPATCH*)
	{
		return S_FALSE;
	}
	STDMETHOD(TranslateUrl)(DWORD, OLECHAR*, OLECHAR **)
	{
		return S_FALSE;
	}
	STDMETHOD(FilterDataObject)(IUnknown *pDO, IUnknown **ppDORet)
	{
		return S_FALSE;
	}
	//
	STDMETHOD(OnZoomPercentChanged)(ULONG ulZoomPercent)
	{
		return S_OK;
	}
	//
	HRESULT GetScriptErrorInfo(VARIANT* pvaIn, int& line, int& column, int& code, CString& strMessage, CString& strSource)
	{
		// Get the document that is currently being viewed.
		CComQIPtr<IHTMLDocument2> spDoc(pvaIn->punkVal);
		if (!spDoc)
			return E_FAIL;
		// Get document.parentWindow.
		CComPtr<IHTMLWindow2> spWin;
		spDoc->get_parentWindow(&spWin);
		if (!spWin)
			return E_FAIL;
		//
		// Get the window.event object.
		CComPtr<IHTMLEventObj> spEventObj;
		spWin->get_event(&spEventObj);
		if (!spEventObj)
			return E_FAIL;
		//
		// Get the error info from the window.event object.
		CComVariant errorLine;
		WizDispatchGetProperty(spEventObj, _T("errorLine"), errorLine);
		//
		CComVariant errorCharacter;
		WizDispatchGetProperty(spEventObj, _T("errorCharacter"), errorCharacter);
		//
		CComVariant errorCode;
		WizDispatchGetProperty(spEventObj, _T("errorCode"), errorCode);
		//
		CComVariant errorMessage;
		WizDispatchGetProperty(spEventObj, _T("errorMessage"), errorMessage);
		//
		CComVariant errorUrl;
		WizDispatchGetProperty(spEventObj, _T("errorUrl"), errorUrl);
		//
		line = errorLine.lVal;
		column = errorCharacter.lVal;
		code = errorCode.lVal;
		if (errorMessage.vt == VT_BSTR)
		{
			strMessage = CString(errorMessage.bstrVal);
		}
		if (errorUrl.vt == VT_BSTR)
		{
			strSource = CString(errorUrl.bstrVal);
		}
		//
		return S_OK;
	}
	//
	//
    STDMETHOD(OnScriptError)(VARIANT* pvaIn)
	{
		return S_OK;
	}
public:
	virtual DWORD GetDocHostUIFlags()
	{
		DWORD dwFlags = 0;
		if (m_bNoScript)
		{
			dwFlags |= DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE;
		}
		if (m_bNo3DBorder)
		{
			dwFlags |= DOCHOSTUIFLAG_NO3DBORDER;
		}
		if (m_bNoScroll)
		{
			dwFlags |= DOCHOSTUIFLAG_SCROLL_NO;
		}
		if (m_bDialog)
		{
			dwFlags |= DOCHOSTUIFLAG_DIALOG;
		}
		if (m_bNewWindow)
		{
			dwFlags |= DOCHOSTUIFLAG_OPENNEWWIN;
		}
		//
		dwFlags |= DOCHOSTUIFLAG_THEME;
		//
		return dwFlags;
	}
	//
	void ChangeDocHostUIFlags()
	{
		T* pT = static_cast<T*>(this);
		//
		CComPtr<IAxWinHostWindow> spAxWindow;
		pT->QueryHost(&spAxWindow);
		if (spAxWindow)
		{
			CComQIPtr<IAxWinAmbientDispatchEx> spAxAmbient(spAxWindow);
			if (spAxAmbient)
			{
				spAxAmbient->put_DocHostFlags(GetDocHostUIFlags());
			}
		}
	}
	//
	void ChangeNoMenu()
	{
		T* pT = static_cast<T*>(this);
		//
		CComPtr<IAxWinHostWindow> spAxWindow;
		pT->QueryHost(&spAxWindow);
		if (spAxWindow)
		{
			CComQIPtr<IAxWinAmbientDispatch> spAxAmbient(spAxWindow);
			if (spAxAmbient)
			{
				spAxAmbient->put_AllowContextMenu(m_bNoMenu ? VARIANT_FALSE : VARIANT_TRUE);
			}
		}
	}
	//
	void SetNoMenu(BOOL bNoMenu)
	{
		m_bNoMenu = bNoMenu;
		ChangeNoMenu();
	}
	void SetDialog(BOOL bDialog)
	{
		m_bDialog = bDialog;
		ChangeNoMenu();
	}
	
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		LRESULT lResult = 0;
		lResult = WizAtlAxWindowOnCreate(pT->m_hWnd, uMsg, wParam, lParam);
		//
		HRESULT hResult = pT->QueryControl(IID_IWebBrowser2, (void**)&m_spBrowser);
		if (SUCCEEDED(hResult))
		{
			if (FAILED(DispEventAdvise(m_spBrowser,&DIID_DWebBrowserEvents2)))
			{
				ATLASSERT(FALSE);
				m_spBrowser.Release();
			}
		}
		//
		CComPtr<IAxWinHostWindow> spAxWindow;
		pT->QueryHost(&spAxWindow);
		if (spAxWindow)
		{
			spAxWindow->SetExternalUIHandler(this);
		}
		//
		if (m_bSilent)
		{
			PutSilent(TRUE);
		}
		//
		return lResult;
	}
	
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (m_spBrowser)
		{
			DispEventUnadvise(m_spBrowser, &DIID_DWebBrowserEvents2);
			m_spBrowser.Release();
		}
		bHandled=FALSE;
		return 0;
	}
	//
	virtual void OnSetSecureLockIcon(long nSecureLockIcon) { }
	virtual BOOL OnNavigateError(IDispatch* pDisp, const CString& szURL, const CString& szTargetFrameName, LONG nStatusCode)
	{   // Return TRUE to cancel
		return FALSE;
	}
	virtual void OnPrivacyImpactedStateChange(BOOL bImpacted) { }
	virtual void OnStatusTextChange(const CString& szText) { }
	virtual void OnProgressChange(long nProgress, long nProgressMax) { }
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable)
	{
		switch (nCommand)
		{
		case CSC_NAVIGATEBACK:
			m_bState[back]=bEnable;
			break;
		case CSC_NAVIGATEFORWARD:
			m_bState[forward]=bEnable;
			break;
		}
	}
	virtual void OnDownloadBegin() { }
	virtual void OnDownloadComplete() { }
	virtual void OnTitleChange(const CString& szTitle) { }
	virtual void OnNavigateComplete2(IDispatch* pDisp, const CString& szURL) { }
	virtual BOOL OnBeforeNavigate2(IDispatch* pDisp, const CString& szURL, DWORD dwFlags, const CString& szTargetFrameName, CSimpleArray<BYTE>& pPostedData, const CString& szHeaders)
	{   // Return TRUE to cancel
		return FALSE;
	}
	virtual void OnPropertyChange(const CString& szProperty) { }
	virtual BOOL OnNewWindow2(IDispatch** ppDisp)
	{   // Return TRUE to cancel
		return FALSE;
	}
	virtual BOOL OnNewWindow3(IDispatch** ppDisp, DWORD dwFlags, const CString& strUrlContext, const CString& strUrl)
	{   // Return TRUE to cancel
		return FALSE;
	}
	virtual void OnDocumentComplete(IDispatch* pDisp, const CString& szURL) { }
	virtual void OnQuit() { }
	virtual void OnVisible(BOOL bVisible) { }
	virtual void OnToolBar(BOOL bToolBar) { }
	virtual void OnMenuBar(BOOL bMenuBar) { }
	virtual void OnStatusBar(BOOL bStatusBar) { }
	virtual void OnFullScreen(BOOL bFullScreen) { }
	virtual void OnTheaterMode(BOOL bTheaterMode) { }
	/*
	BOOL OnWindowClosing(BOOL bChildWindow)
	{   // Return TRUE to cancel
		return FALSE;
	}
	*/
	/*
	BOOL OnFileDownload()
	{   // Return TRUE to cancel
		return FALSE;
	}
	*/
	
	// Properties
	__declspec(property(get=GetAddressBar,put=PutAddressBar)) BOOL AddressBar;
	__declspec(property(get=GetApplication)) IDispatchPtr Application;
	__declspec(property(get=GetBusy)) BOOL Busy;
	__declspec(property(get=GetFullName)) CString FullName;
	__declspec(property(get=GetLocationName)) CString LocationName;
	__declspec(property(get=GetLocationURL)) CString LocationURL;
	__declspec(property(get=GetRegisterAsBrowser,put=PutRegisterAsBrowser)) BOOL RegisterAsBrowser;
	__declspec(property(get=GetRegisterAsDropTarget,put=PutRegisterAsDropTarget)) BOOL RegisterAsDropTarget;
	__declspec(property(get=GetTheaterMode,put=PutTheaterMode)) BOOL TheaterMode;
	__declspec(property(get=GetVisible,put=PutVisible)) BOOL Visible;
	__declspec(property(get=GetMenuBar,put=PutMenuBar)) BOOL MenuBar;
	__declspec(property(get=GetToolBar,put=PutToolBar)) BOOL ToolBar;
	__declspec(property(get=GetOffline,put=PutOffline)) BOOL Offline;
	__declspec(property(get=GetSilent,put=PutSilent)) BOOL Silent;
	__declspec(property(get=GetFullScreen,put=PutFullScreen)) BOOL FullScreen;
	__declspec(property(get=GetStatusBar,put=PutStatusBar)) BOOL StatusBar;
	__declspec(property(get=GetLeft,put=PutLeft)) LONG Left;
	__declspec(property(get=GetTop,put=PutTop)) LONG Top;
	__declspec(property(get=GetWidth,put=PutWidth)) LONG Width;
	__declspec(property(get=GetHeight,put=PutHeight)) LONG Height;
	__declspec(property(get=GetDocument)) IDispatchPtr Document;

	BOOL CanBack() const
	{
		return m_bState[back];
	}

	BOOL CanForward() const
	{
		return m_bState[forward];
	}
	
	void Quit()
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->Quit();
	}
	
	void PutAddressBar(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_AddressBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetAddressBar()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_AddressBar(&bResult);
		return bResult ? TRUE : FALSE;
	}
	IDispatchPtr GetApplication()
	{
		if (!m_spBrowser)
			return NULL;
		ATLASSERT(m_spBrowser);
		IDispatchPtr pDispatch;
		m_spBrowser->get_Application(&pDispatch);
		return pDispatch;
	}
	BOOL GetBusy()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_Busy(&bResult);
		return bResult ? TRUE : FALSE;
	}
	CString GetFullName() const
	{
		if (!m_spBrowser)
			return CString();
		ATLASSERT(m_spBrowser);
		CComBSTR szResult;
		m_spBrowser->get_FullName(&szResult);
		return szResult;
	}
	CString GetLocationName() const
	{
		if (!m_spBrowser)
			return CString();
		ATLASSERT(m_spBrowser);
		CComBSTR szResult;
		m_spBrowser->get_LocationName(&szResult);
		return szResult;
	}
	CString GetLocationURL() const
	{
		if (!m_spBrowser)
			return CString();
		ATLASSERT(m_spBrowser);
		CComBSTR szResult;
		m_spBrowser->get_LocationURL(&szResult);
		return szResult;
	}
	void PutRegisterAsBrowser(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_RegisterAsBrowser(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetRegisterAsBrowser()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_RegisterAsBrowser(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutRegisterAsDropTarget(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_RegisterAsDropTarget(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetRegisterAsDropTarget()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_RegisterAsDropTarget(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutTheaterMode(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_TheaterMode(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetTheaterMode()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_TheaterMode(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutVisible(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Visible(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetVisible()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_Visible(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutMenuBar(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_MenuBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetMenuBar()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_MenuBar(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutToolBar(int nNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_ToolBar(nNewValue);
	}
	BOOL GetToolBar()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_ToolBar(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutOffline(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Offline(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetOffline()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_Offline(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutSilent(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Silent(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetSilent()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_Silent(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutFullScreen(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_FullScreen(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	BOOL GetFullScreen()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_FullScreen(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutStatusBar(BOOL bNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_StatusBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE); 
	}
	BOOL GetStatusBar()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		VARIANT_BOOL bResult;
		m_spBrowser->get_StatusBar(&bResult);
		return bResult ? TRUE : FALSE;
	}
	void PutLeft(LONG nNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Left(nNewValue);
	}
	LONG GetLeft()
	{
		if (!m_spBrowser)
			return FALSE;
		ATLASSERT(m_spBrowser);
		LONG nResult;
		m_spBrowser->get_Left(&bResult);
		return nResult;
	}
	void PutTop(LONG nNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Top(nNewValue);
	}
	LONG GetTop()
	{
		if (!m_spBrowser)
			return 0;
		ATLASSERT(m_spBrowser);
		LONG nResult;
		m_spBrowser->get_Top(&bResult);
		return nResult;
	}
	void PutWidth(LONG nNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Width(nNewValue);
	}
	LONG GetWidth()
	{
		if (!m_spBrowser)
			return 0;
		ATLASSERT(m_spBrowser);
		LONG nResult;
		m_spBrowser->get_Width(&bResult);
		return nResult;
	}
	void PutHeight(LONG nNewValue)
	{
		if (!m_spBrowser)
			return;
		ATLASSERT(m_spBrowser);
		m_spBrowser->put_Height(nNewValue);
	}
	LONG GetHeight()
	{
		if (!m_spBrowser)
			return 0;
		ATLASSERT(m_spBrowser);
		LONG nResult;
		m_spBrowser->get_Height(&bResult);
		return nResult;
	}
	IDispatchPtr GetDocument()
	{
		if (!m_spBrowser)
			return NULL;
		ATLASSERT(m_spBrowser);
		IDispatchPtr pDispatch;
		m_spBrowser->get_Document(&pDispatch);
		return pDispatch;
	}
	HRESULT PutProperty(LPCTSTR szProperty,const VARIANT& vtValue)
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		USES_CONVERSION;
		return m_spBrowser->PutProperty(CComBSTR(szProperty),vtValue);
	}
	CComVariant GetProperty(LPCTSTR szProperty)
	{
		if (!m_spBrowser)
			return CComVariant();
		ATLASSERT(m_spBrowser);
		CComDispatchDriver pDriver(m_spBrowser);
		ATLASSERT(pDriver);
		CComVariant vtResult;
		pDriver.GetPropertyByName(CComBSTR(szProperty),&vtResult);
		return vtResult;
	}
	
	// Methods
	HRESULT ClientToWindow(LPPOINT pPoint)
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		ATLASSERT(pPoint);
		return m_spBrowser->ClientToWindow(&(pPoint->x),&(pPoint->y));
	}
	HRESULT ExecWB(OLECMDID nCmd,OLECMDEXECOPT nCmdOptions,VARIANT* pvInput=NULL,VARIANT* pvOutput=NULL)
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->ExecWB(nCmd,nCmdOptions,pvInput,pvOutput);
	}
	HRESULT GoBack()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->GoBack();
	}
	HRESULT GoForward()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->GoForward();
	}
	HRESULT GoHome()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->GoHome();
	}
	HRESULT GoSearch()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->GoSearch();
	}
	HRESULT Navigate(LPCTSTR szURL,DWORD dwFlags=0,LPCTSTR szTargetFrameName=NULL,LPCVOID pPostData=NULL,DWORD dwPostDataLength=0,LPCTSTR szHeaders=NULL)
	{
		m_dwNavigateTickCount = GetTickCount();
		//
		if (!m_spBrowser)
			return E_FAIL;
		USES_CONVERSION;
		ATLASSERT(m_spBrowser);
		ATLASSERT(szURL);
		CComVariant vtTargetFrameName,vtPostData,vtHeaders;
		if (szTargetFrameName)
			vtTargetFrameName=szTargetFrameName;
		if (pPostData && dwPostDataLength>0)
		{
			vtPostData.ChangeType(VT_ARRAY|VT_UI1);
			SAFEARRAYBOUND Bound;
			Bound.cElements=dwPostDataLength;
			Bound.lLbound=0;
			vtPostData.parray=SafeArrayCreate(VT_UI1,1,&Bound);
			ATLASSERT(vtPostData.parray);
			if (vtPostData.parray==NULL)
				return E_OUTOFMEMORY;
			LPVOID pData;
			SafeArrayAccessData(vtPostData.parray,&pData);
			CopyMemory(pData,pPostData,dwPostDataLength);
			SafeArrayUnaccessData(vtPostData.parray);
		}
		if (szHeaders)
			vtHeaders=szHeaders;
		return m_spBrowser->Navigate(T2BSTR(szURL),&CComVariant((LONG)dwFlags),&vtTargetFrameName,&vtPostData,&vtHeaders);
	}
	HRESULT Navigate2(LPCTSTR szURL,DWORD dwFlags=0,LPCTSTR szTargetFrameName=NULL,LPCVOID pPostData=NULL,DWORD dwPostDataLength=0,LPCTSTR szHeaders=NULL)
	{
		m_dwNavigateTickCount = GetTickCount();
		//
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		ATLASSERT(szURL);
		CComVariant vtTargetFrameName,vtPostData,vtHeaders;
		if (szTargetFrameName)
			vtTargetFrameName=szTargetFrameName;
		if (pPostData && dwPostDataLength>0)
		{
			vtPostData.ChangeType(VT_ARRAY|VT_UI1);
			SAFEARRAYBOUND Bound;
			Bound.cElements=dwPostDataLength;
			Bound.lLbound=0;
			vtPostData.parray=SafeArrayCreate(VT_UI1,1,&Bound);
			ATLASSERT(vtPostData.parray);
			if (vtPostData.parray==NULL)
				return E_OUTOFMEMORY;
			LPVOID pData=NULL;
			SafeArrayAccessData(vtPostData.parray,&pData);
			ATLASSERT(pData);
			CopyMemory(pData,pPostData,dwPostDataLength);
			SafeArrayUnaccessData(vtPostData.parray);
		}
		if (szHeaders)
			vtHeaders=szHeaders;
		return m_spBrowser->Navigate2(&CComVariant(szURL),&CComVariant((LONG)dwFlags),&vtTargetFrameName,&vtPostData,&vtHeaders);
	}
	HRESULT Refresh()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->Refresh();
	}
	HRESULT Refresh2(LONG nLevel)
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->Refresh2(CComVariant(nLevel));
	}
	HRESULT Stop()
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		return m_spBrowser->Stop();
	}
	OLECMDF QueryStatusWB(OLECMDID nCmd)
	{
		if (!m_spBrowser)
			return E_FAIL;
		ATLASSERT(m_spBrowser);
		OLECMDF nResult;
		m_spBrowser->QueryStatusWB(nCmd,&nResult);
		return nResult;
	}
	
	HRESULT LoadFromResource(UINT nID) 
	{
		if (!m_spBrowser)
			return E_FAIL;
		TCHAR szFilename[MAX_PATH];
		GetModuleFileName(_Module.GetModuleInstance(),szFilename,sizeof(szFilename)/sizeof(TCHAR));
		TCHAR szURL[4096];
		_stprintf(szURL,_T("res://%s/%d"),szFilename,nID);
		return Navigate(szURL);
	}
	HRESULT LoadFromResource(LPCTSTR szID) 
	{
		if (!m_spBrowser)
			return E_FAIL;
		TCHAR szFilename[MAX_PATH];
		GetModuleFileName(_Module.GetModuleInstance(),szFilename,sizeof(szFilename)/sizeof(TCHAR));
		TCHAR szURL[4096];
		_stprintf(szURL,_T("res://%s/%s"),szFilename,szID);
		return Navigate(szURL);
	}
	CComPtr<IHTMLDocument2> GetDoc2()
	{
		if (!m_spBrowser)
			return NULL;
		CComPtr<IDispatch> spDisp = GetDocument();
		return CComQIPtr<IHTMLDocument2>(spDisp);
	}	
	CComPtr<IHTMLWindow2> GetWin2()
	{
		CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (!spDoc)
			return NULL;
		//
		CComQIPtr<IHTMLWindow2> spWindow;
		spDoc->get_parentWindow(&spWindow);
		return spWindow;
	}	
	CComPtr<IHTMLDocument3> GetDoc3()
	{
		if (!m_spBrowser)
			return NULL;
		return CComQIPtr<IHTMLDocument3>(GetDoc2());
	}	
	CComPtr<IHTMLDocument4> GetDoc4()
	{
		if (!m_spBrowser)
			return NULL;
		return CComQIPtr<IHTMLDocument4>(GetDoc2());
	}	
protected:
	enum
	{
		back = 0,
		forward
	};
	CComPtr<IWebBrowser2> m_spBrowser;
	BOOL m_bState[2];
public:
	CComPtr<IWebBrowser2> GetBrowser()
	{
		ATLASSERT(m_spBrowser);
		return m_spBrowser;
	}
	
private:
	void __stdcall __SetSecureLockIcon(long nSecureLockIcon)
	{
		OnSetSecureLockIcon(nSecureLockIcon);
	}
	
	void __stdcall __NavigateError(IDispatch* pDisp, VARIANT* pvURL, VARIANT* pvTargetFrameName, VARIANT* pvStatusCode, VARIANT_BOOL* pbCancel)
	{
		ATLASSERT(V_VT(pvURL) == VT_BSTR);
		ATLASSERT(V_VT(pvTargetFrameName) == VT_BSTR);
		ATLASSERT(V_VT(pvStatusCode) == (VT_I4));
		ATLASSERT(pbCancel != NULL);
		*pbCancel = OnNavigateError(pDisp,V_BSTR(pvURL),V_BSTR(pvTargetFrameName),V_I4(pvStatusCode));
	}
	
	void __stdcall __PrivacyImpactedStateChange(VARIANT_BOOL bImpacted)
	{
		OnPrivacyImpactedStateChange(bImpacted);
	}
	
	void __stdcall __StatusTextChange(BSTR szText)
	{
		OnStatusTextChange(szText);
	}
	
	void __stdcall __ProgressChange(long nProgress, long nProgressMax)
	{
		OnProgressChange(nProgress, nProgressMax);
	}
	
	void __stdcall __CommandStateChange(long nCommand, VARIANT_BOOL bEnable)
	{
		OnCommandStateChange(nCommand, (bEnable==VARIANT_TRUE) ? TRUE : FALSE);
	}
	
	void __stdcall __DownloadBegin()
	{
		OnDownloadBegin();
	}
	
	void __stdcall __DownloadComplete()
	{
		OnDownloadComplete();
	}
	
	void __stdcall __TitleChange(BSTR szText)
	{
		OnTitleChange(szText);
	}
	
	void __stdcall __NavigateComplete2(IDispatch* pDisp, VARIANT* pvURL)
	{
		ATLASSERT(V_VT(pvURL) == VT_BSTR);
		OnNavigateComplete2(pDisp, V_BSTR(pvURL));
	}
	
	void __stdcall __BeforeNavigate2(IDispatch* pDisp, VARIANT* pvURL, VARIANT* pvFlags, VARIANT* pvTargetFrameName, VARIANT* pvPostData, VARIANT* pvHeaders, VARIANT_BOOL* pbCancel)
	{
		ATLASSERT(V_VT(pvURL) == VT_BSTR);
		ATLASSERT(V_VT(pvTargetFrameName) == VT_BSTR);
		ATLASSERT(V_VT(pvPostData) == (VT_VARIANT | VT_BYREF));
		ATLASSERT(V_VT(pvHeaders) == VT_BSTR);
		ATLASSERT(pbCancel != NULL);
		
		VARIANT* vtPostedData = V_VARIANTREF(pvPostData);
		CSimpleArray<BYTE> pArray;
		if (V_VT(vtPostedData) & VT_ARRAY)
		{
			ATLASSERT(V_ARRAY(vtPostedData)->cDims == 1 && V_ARRAY(vtPostedData)->cbElements == 1);
			long nLowBound=0,nUpperBound=0;
			SafeArrayGetLBound(V_ARRAY(vtPostedData), 1, &nLowBound);
			SafeArrayGetUBound(V_ARRAY(vtPostedData), 1, &nUpperBound);
			DWORD dwSize=nUpperBound+1-nLowBound;
			LPVOID pData=NULL;
			SafeArrayAccessData(V_ARRAY(vtPostedData),&pData);
			ATLASSERT(pData);
			
			pArray.m_nSize=pArray.m_nAllocSize=dwSize;
			pArray.m_aT=(BYTE*)malloc(dwSize);
			ATLASSERT(pArray.m_aT);
			CopyMemory(pArray.GetData(), pData, dwSize);
			SafeArrayUnaccessData(V_ARRAY(vtPostedData));
		}
		//
		//
		if (pDisp && m_spBrowser && pvURL)
		{
			CComPtr<IUnknown> spUnkCurr(pDisp);
			CComPtr<IUnknown> spUnkOutter(m_spBrowser);
			if (spUnkCurr
				&& spUnkOutter
				&& spUnkCurr.p != spUnkOutter.p)
			{
				CString strURL(pvURL->bstrVal);
				CWizURL url(strURL);
				if (url.IsFileURL())
				{
					CString strFileName = url.GetFileNameInURL();
					if (!PathFileExists(strFileName)
						|| PathIsDirectory(strFileName))
					{
						*pbCancel = VARIANT_TRUE;
						return;
					}
					CString strExt = WizExtractFileExt(strFileName);
					strExt.MakeLower();
					if (strExt == _T(".htm")
						|| strExt == _T(".html")
						|| strExt == _T(".txt")
						|| strExt == _T(".png")
						|| strExt == _T(".bmp")
						|| strExt == _T(".jpg"))
					{
					}
					else
					{
						*pbCancel = VARIANT_TRUE;
						return;
					}
				}
			}
		}
		//
		//
		*pbCancel = OnBeforeNavigate2(pDisp, V_BSTR(pvURL), V_I4(pvFlags), V_BSTR(pvTargetFrameName), pArray, V_BSTR(pvHeaders)) ? VARIANT_TRUE : VARIANT_FALSE;
	}
	
	void __stdcall __PropertyChange(BSTR szProperty)
	{
		OnPropertyChange(szProperty);
	}
	
	void __stdcall __NewWindow2(IDispatch** ppDisp, VARIANT_BOOL* pbCancel)
	{
		*pbCancel = OnNewWindow2(ppDisp) ? VARIANT_TRUE : VARIANT_FALSE;
	}

	void __stdcall __NewWindow3(IDispatch** ppDisp, VARIANT_BOOL* pbCancel, DWORD dwFlags, BSTR bstrUrlContext, BSTR bstrUrl)
	{
		*pbCancel = OnNewWindow3(ppDisp, dwFlags, CString(bstrUrlContext),CString(bstrUrl)) ? VARIANT_TRUE : VARIANT_FALSE;
	}
	
	void __stdcall __DocumentComplete(IDispatch* pDisp, VARIANT* pvURL)
	{
		ATLASSERT(V_VT(pvURL) == VT_BSTR);
		OnDocumentComplete(pDisp, V_BSTR(pvURL));
		//
		if (m_nInitZoom > 10)
		{
			SetZoomPercent(m_nInitZoom, FALSE);
			m_nInitZoom = 0;
		}
	}
	
	void __stdcall __OnQuit()
	{
		OnQuit();
	}
	
	void __stdcall __OnVisible(VARIANT_BOOL bVisible)
	{
		OnVisible(bVisible == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	void __stdcall __OnToolBar(VARIANT_BOOL bToolBar)
	{
		OnToolBar(bToolBar == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	void __stdcall __OnMenuBar(VARIANT_BOOL bMenuBar)
	{
		OnMenuBar(bMenuBar == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	void __stdcall __OnStatusBar(VARIANT_BOOL bStatusBar)
	{
		OnStatusBar(bStatusBar == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	void __stdcall __OnFullScreen(VARIANT_BOOL bFullScreen)
	{
		OnFullScreen(bFullScreen == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	void __stdcall __OnTheaterMode(VARIANT_BOOL bTheaterMode)
	{
		OnTheaterMode(bTheaterMode == VARIANT_TRUE ? TRUE : FALSE);
	}
	
	/*
	void __stdcall __FileDownload(VARIANT_BOOL* pbCancel)
	{
		T* pT = static_cast<T*>(this);
		*pbCancel = pT->OnFileDownload() ? VARIANT_TRUE : VARIANT_FALSE;
	}
	*/
	/*
	void __stdcall __WindowClosing(VARIANT_BOOL bChildWindow,VARIANT_BOOL* pbCancel)
	{
		T* pT = static_cast<T*>(this);
		*pbCancel=pT->OnWindowClosing(bChildWindow ? TRUE : FALSE);
	}
	*/
	//
public:
	virtual HRESULT ExecCommand(const GUID *pGuid, long cmdID, long cmdExecOpt, VARIANT* pInVar=NULL, VARIANT* pOutVar=NULL)
	{
		const T* pT = static_cast<const T*>(this);
		::ATL::CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		HRESULT hr = E_FAIL;
		if (spDoc)
		{
			CComQIPtr<IOleCommandTarget> spCmdTarg = spDoc;
			if (spCmdTarg)
			{
				try
				{
					hr = spCmdTarg->Exec(pGuid, cmdID, cmdExecOpt, pInVar , pOutVar);
				}
				catch (...)
				{
				}
			}
			else
				hr = E_NOINTERFACE;
		}
		return hr;
	}
	HRESULT ExecCommandDefault(long cmdID, long cmdExecOpt, VARIANT* pInVar=NULL, VARIANT* pOutVar=NULL)
	{
		return ExecCommand(&CGID_MSHTML, cmdID, cmdExecOpt, 
					pInVar , pOutVar );
	}

	long QueryStatus(long cmdID)
	{
		const T* pT = static_cast<const T*>(this);
		::ATL::CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (spDoc)
		{
			CComQIPtr<IOleCommandTarget> spCmdTarg = spDoc;
			if (spCmdTarg)
			{
				OLECMD ocmd = {cmdID, 0};
				if (S_OK == spCmdTarg->QueryStatus(&CGID_MSHTML, 1, &ocmd, NULL))
					return ocmd.cmdf;
			}
		}
		// if an error occurred, returning 0 means the command is disabled
		return 0;
	}
	long IsCommandEnabled(long cmdID)
	{
		return (QueryStatus(cmdID) & OLECMDF_ENABLED) == OLECMDF_ENABLED;
	}
	long IsCommandChecked(long cmdID)
	{
		return (QueryStatus(cmdID) & OLECMDF_LATCHED) == OLECMDF_LATCHED;
	}
	//
	HRESULT ExecHelperNN(UINT nID,
						 long nMinSupportLevel = OLECMDF_SUPPORTED|OLECMDF_ENABLED,
						 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		long lStatus = QueryStatus(nID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
			hr = ExecCommandDefault(nID, nExecOpt);
		return hr;
	}

	HRESULT ExecHelperSetVal(UINT nCmdID, 
							 LPCTSTR szID=NULL,
							 long nMinSupportLevel = OLECMDF_SUPPORTED|OLECMDF_ENABLED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			if (szID)
			{
				CComVariant vName(szID);
				return ExecCommandDefault(nCmdID, nExecOpt, &vName);
			}
			else
				return ExecCommandDefault(nCmdID, nExecOpt);
		}
		return E_FAIL;
	}

	HRESULT ExecHelperSetVal(UINT nCmdID,
							 bool bValue,
							 long nMinSupportLevel = OLECMDF_SUPPORTED|OLECMDF_ENABLED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			CComVariant vIn(bValue);
			hr = ExecCommandDefault(nCmdID, nExecOpt, &vIn);
		}
		return hr;
	}

	HRESULT ExecHelperSetVal(UINT nCmdID,
							 short nNewVal,
							 long nMinSupportLevel = OLECMDF_SUPPORTED|OLECMDF_ENABLED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			CComVariant vIn((short)nNewVal);
			hr = ExecCommandDefault(nCmdID, nExecOpt, &vIn);
		}
		return hr;
	}

	HRESULT ExecHelperSetVal(UINT nCmdID,
							 int nNewVal,
							 long nMinSupportLevel = OLECMDF_SUPPORTED|OLECMDF_ENABLED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			CComVariant vIn((int)nNewVal);
			hr = ExecCommandDefault(nCmdID, nExecOpt, &vIn);
		}
		return hr;
	}

	HRESULT ExecHelperGetVal(UINT nCmdID,
							 bool &bValue,
							 long nMinSupportLevel = OLECMDF_SUPPORTED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		bValue = false;
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			CComVariant vOut;
			hr = ExecCommandDefault(nCmdID, nExecOpt, NULL, &vOut);
			if (hr == S_OK)
			{
				switch(vOut.vt)
				{
				case VT_BOOL:
					bValue = vOut.boolVal == VARIANT_TRUE ? true : false;
					break;
				case VT_NULL:
				case VT_EMPTY:
					break;
				case VT_ERROR:
					hr = V_ERROR(&vOut);
					break;
				default:
					hr = E_UNEXPECTED;
					break;
				}
			}
		}
		return hr;
	}

	HRESULT ExecHelperGetVal(UINT nCmdID,
							 short &nValue,
							 long nMinSupportLevel = OLECMDF_SUPPORTED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		int nTempVal;
		HRESULT hr = ExecHelperGetVal(nCmdID, nTempVal, nMinSupportLevel, nExecOpt);
		if (hr == S_OK)
			nValue = (short)nTempVal;
		return hr;
	}


	HRESULT ExecHelperGetVal(UINT nCmdID,
							 int &nValue,
							 long nMinSupportLevel = OLECMDF_SUPPORTED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		long lStatus = QueryStatus(nCmdID);
		nValue = 0;
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			CComVariant vOut;
			hr = ExecCommandDefault(nCmdID, nExecOpt, NULL, &vOut);
			if (hr == S_OK)
			{
				switch (vOut.vt)
				{
				case VT_I4:
					nValue = vOut.lVal;
					break;
				case VT_I2:
					nValue = vOut.iVal;
					break;
				case VT_EMPTY:
				case VT_NULL:
					break;
				case VT_ERROR:
					hr = V_ERROR(&vOut);
					break;
				default:
					hr = E_UNEXPECTED;
					break;
				}
			}
		}
		return hr;
	}

	HRESULT ExecHelperGetVal(UINT nCmdID,
							 CString& strValue,
							 long nMinSupportLevel = OLECMDF_SUPPORTED,
							 long nExecOpt = OLECMDEXECOPT_DODEFAULT)
	{
		HRESULT hr = E_FAIL;
		CComVariant vaRet;
		strValue.Empty();
		long lStatus = QueryStatus(nCmdID);
		if ((lStatus & nMinSupportLevel) == nMinSupportLevel)
		{
			hr = ExecCommandDefault(nCmdID, nExecOpt, NULL, &vaRet);
			if (hr == S_OK)
			{
				switch(vaRet.vt)
				{
				case VT_BSTR:
					{
					CW2T szVal(vaRet.bstrVal);
					strValue = szVal;
					}
					break;
				case VT_NULL:
				case VT_EMPTY:
					break;
				case VT_ERROR:
					hr = V_ERROR(&vaRet);
					break;
				default:
					hr = E_UNEXPECTED;
					break;
				}
			}
		}
		return hr;
	}
	//
	static const UINT WIZ_OLECMDID_OPTICAL_ZOOM = 63;
	void SetZoomPercent(UINT nPercent, BOOL bCheckTickCount = TRUE)
	{
		if (!::WizIsIE7())
			return;
		//
		if (-1 == m_nInitZoom)
		{
			m_nInitZoom = int(nPercent);
		}
		//
		if (bCheckTickCount)
		{
			DWORD dwNow = GetTickCount();
			if (dwNow - m_dwNavigateTickCount < 500)
				return;
		}
		//
		int nVal = int(nPercent);
		CComVariant v(nVal);
		//
		HRESULT hr = ExecCommand(NULL, WIZ_OLECMDID_OPTICAL_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER, &v, NULL);
		//
		OnZoomChanged();
	}
	UINT GetZoomPercent()
	{
		if (!::WizIsIE7())
			return 100;
		//
		CComVariant v(0);
		ExecCommand(NULL, WIZ_OLECMDID_OPTICAL_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER, NULL, &v);
		//
		UINT nPercent = (UINT)v.lVal;
		if (0 == nPercent)
			return 100;
		//
		return nPercent;
	}
	//
	virtual void OnZoomChanged()
	{
	}
	BOOL HasFocus()
	{
		T* pT = static_cast<T*>(this);
		//
		if (!pT->IsWindow())
			return FALSE;
		//
		HWND hwndFocus = ::GetFocus();
		while (hwndFocus)
		{
			if (hwndFocus == pT->m_hWnd)
				return TRUE;
			//
			hwndFocus = ::GetParent(hwndFocus);
		}
		//
		return FALSE;
	}
	//
	void FocusToDocument()
	{
		CComPtr<IHTMLDocument4> spDoc4 = GetDoc4();
		if (spDoc4)
		{
			spDoc4->focus();
		}
	}
	void FocusToDocument(LPCTSTR lpszFocusElementID, LPCTSTR lpszPromptText)
	{
		FocusToDocument();
		//
		if (lpszFocusElementID && *lpszFocusElementID)
		{
			CComPtr<IHTMLDocument3> spDoc3 = GetDoc3();
			if (spDoc3)
			{
				CComPtr<IHTMLElement> spElem;
				spDoc3->getElementById(CComBSTR(lpszFocusElementID), &spElem);
				if (spElem)
				{
					CComBSTR bstrHTML;
					spElem->get_innerHTML(&bstrHTML);
					if (!bstrHTML || bstrHTML.Length() == 0)
					{
						spElem->put_innerText(CComBSTR(lpszPromptText));
					}
					//
					SelectElement(spElem);
				}
			}
		}
	}
	//
	
	inline BOOL GetCommandValue(LPCTSTR lpszCommandID, CString& strValue)
	{
		CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (!spDoc)
			return FALSE;
		//
		CComVariant vRet;
		HRESULT hr = spDoc->queryCommandValue(CComBSTR(lpszCommandID), &vRet);
		if (SUCCEEDED(hr) && vRet.vt == VT_BSTR)
		{
			strValue = vRet.bstrVal;
			//
			return TRUE;
		}
		//
		return FALSE;
	}
};

__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::StatusTextChangeStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BSTR}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::TitleChangeStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BSTR}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::PropertyChangeStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BSTR}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::DownloadBeginStruct = {CC_STDCALL, VT_EMPTY, 0, {NULL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::DownloadCompleteStruct = {CC_STDCALL, VT_EMPTY, 0, {NULL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnQuitStruct = {CC_STDCALL, VT_EMPTY, 0, {NULL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::NewWindow2Struct = {CC_STDCALL, VT_EMPTY, 2, {VT_BYREF|VT_DISPATCH, VT_BYREF|VT_BOOL}}; 
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::NewWindow3Struct = {CC_STDCALL, VT_EMPTY, 5, {VT_BYREF|VT_DISPATCH, VT_BYREF|VT_BOOL, VT_I4, VT_BSTR, VT_BSTR}}; 
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::CommandStateChangeStruct = {CC_STDCALL, VT_EMPTY, 2, {VT_I4,VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::BeforeNavigate2Struct = {CC_STDCALL, VT_EMPTY, 7, {VT_DISPATCH,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::ProgressChangeStruct = {CC_STDCALL, VT_EMPTY, 2, {VT_I4,VT_I4}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::NavigateComplete2Struct = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::DocumentComplete2Struct = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnVisibleStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnToolBarStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnMenuBarStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnStatusBarStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnFullScreenStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::OnTheaterModeStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::SetSecureLockIconStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_I4}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::NavigateErrorStruct = {CC_STDCALL, VT_EMPTY, 5, {VT_BYREF|VT_BOOL,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_DISPATCH}};
__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::PrivacyImpactedStateChangeStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};
//__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::FileDownloadStruct = {CC_STDCALL, VT_EMPTY, 1, {VT_BYREF|VT_BOOL}};
//__declspec(selectany) _ATL_FUNC_INFO CAtlWebBrowserEventsBase::WindowClosingStruct = {CC_STDCALL, VT_EMPTY, 2, {VT_BYREF|VT_BOOL,VT_BOOL}};



class CAtlBrowser
	: public CWindowImpl<CAtlBrowser, CAxWindow>
	, public CAtlWebBrowser<CAtlBrowser>
{
public:
	CAtlBrowser()
	{
	}
public:
	DECLARE_WND_SUPERCLASS(NULL, CAxWindow::GetWndClassName())


	BEGIN_MSG_MAP(CWizExplorerView)
		CHAIN_MSG_MAP(CAtlWebBrowser<CAtlBrowser>)
	END_MSG_MAP()
	//
public:
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
	}

	HWND CreateEx(HWND hWndParent, LPCTSTR lpszURL)
	{
		static CString strProgID;
		if (strProgID.IsEmpty())
		{
			LPOLESTR pszProgID = NULL;
			HRESULT hr = ProgIDFromCLSID(CLSID_WebBrowser, &pszProgID);
			if (FAILED(hr))
				return NULL;
			//
			strProgID = CString(pszProgID);
			CoTaskMemFree(pszProgID);
		}//
		//
		//CreateControl(strProgID);
		if (!Create(hWndParent, rcDefault, strProgID, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0))
			return NULL;
		//
		if (lpszURL)
		{
			Navigate2(lpszURL);
		}
		//
		return m_hWnd;
	}
};



class CWizAtlBrowser 
	: public CAtlBrowser
{
public:
	CWizAtlBrowser()
	{
		m_pUnk = NULL;
	}
	//
	virtual BOOL OnNavigateError(IDispatch* pDisp, const CString& szURL, const CString& szTargetFrameName, LONG nStatusCode)
	{	
		if (pDisp)
		{
			IUnknown* pUnk = NULL;
			if (S_OK == pDisp->QueryInterface(IID_IUnknown, (void**)&pUnk) && pUnk)
			{
				pUnk->Release();

				if (pUnk == m_pUnk)
				{
					m_pUnk = NULL;
					//
					TOLOG1(_T("Failed to navigate url: %1"), szURL);
					OnDocumentCompleteEx(TRUE);
				}
			}
		}
		//
		return FALSE;
	}
	//
	virtual BOOL OnBeforeNavigate2(IDispatch* pDisp, const CString& szURL, DWORD dwFlags, const CString& szTargetFrameName, CSimpleArray<BYTE>& pPostedData, const CString& szHeaders)
	{
		if (pDisp && !m_pUnk)
		{
			if (S_OK == pDisp->QueryInterface(IID_IUnknown, (void**)&m_pUnk))
			{
				m_pUnk->Release();
			}
		}
		//
		return FALSE;
	}
	virtual void OnDocumentComplete(IDispatch* pDisp, const CString& szURL) 
	{
		if (pDisp)
		{
			IUnknown* pUnk = NULL;
			if (S_OK == pDisp->QueryInterface(IID_IUnknown, (void**)&pUnk) && pUnk)
			{
				pUnk->Release();

				if (pUnk == m_pUnk)
				{
					m_pUnk = NULL;
					//
					OnDocumentCompleteEx(FALSE);
					//
					CString strKeywords = GetSearchKeywords();
					if (!strKeywords.IsEmpty())
					{
						HighlightText(strKeywords);
					}
				}
			}
		}
		//
	}
	//
	virtual void OnDocumentCompleteEx(BOOL bError)
	{
	}
	//
#define WIZ_HIGHLIGHTTEXT_SPAN_ID		_T("wizkm_highlight")
	//
	void HighlightText(const CWizStdStringArray& arrayWord)
	{
		CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (!spDoc)
			return;
		//
		COLORREF cr = RGB(47, 222, 47); //::GetSysColor(COLOR_INFOBK);
		//
		for (CWizStdStringArray::const_iterator it = arrayWord.begin();
			it != arrayWord.end();
			it++)
		{
			WizHTMLDocumentHighlightText(spDoc, *it, FALSE, FALSE, cr, WIZ_HIGHLIGHTTEXT_SPAN_ID);
		}
	}
	void ClearHighlight()
	{
		CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (!spDoc)
			return;
		//
		WizHTMLDocumentClearHighlightText(spDoc,  WIZ_HIGHLIGHTTEXT_SPAN_ID);
	}
	void HighlightText(LPCTSTR lpszKetwords)
	{
		CComPtr<IHTMLDocument2> spDoc = GetDoc2();
		if (!spDoc)
			return;
		//
		CString strKeywords(lpszKetwords);
		//
		CWizStdStringArray arrayWord;
		WizSplitTextToArray(strKeywords, ' ', arrayWord);
		HighlightText(arrayWord);
	}
	virtual CString GetSearchKeywords()
	{
		return CString();
	}
	//
	virtual void SetOptions(LPCTSTR lpszOptions)
	{
		m_strOptions = lpszOptions;
	}
protected:
	IUnknown* m_pUnk;
	CString m_strOptions;
public:
	BEGIN_MSG_MAP(CWizAtlBrowser)
		CHAIN_MSG_MAP(CAtlBrowser)
	END_MSG_MAP()

};



class CWizSafeBrowser
	: public CWizAtlBrowser
{
public:
	CWizSafeBrowser()
	{
		m_bFirstNavigate = TRUE;
		m_pUnk = NULL;
	}
public:
	BEGIN_MSG_MAP(CWizSafeBrowser)
		CHAIN_MSG_MAP(CWizAtlBrowser)
	END_MSG_MAP()
protected:
	BOOL m_bFirstNavigate;
public:
	CString m_strHiddenagID;
	CString m_strLocalURL;
public:
	BOOL IsSucceeded()
	{
		if (m_strHiddenagID.IsEmpty()
			|| m_strLocalURL.IsEmpty())
			return TRUE;
		//
		CComPtr<IHTMLDocument3> spDoc = GetDoc3();
		if (!spDoc)
			return FALSE;
		//
		CComPtr<IHTMLElement> spElem;
		spDoc->getElementById(CComBSTR(m_strHiddenagID), &spElem);
		//
		return spElem ? TRUE : FALSE;
	}
	//

	virtual void OnDocumentCompleteEx(BOOL bError)
	{
		if (m_strHiddenagID.IsEmpty()
			|| m_strLocalURL.IsEmpty())
			return;
		//
		if (!m_bFirstNavigate)
			return;
		//
		m_bFirstNavigate = FALSE;
		//
		if (IsSucceeded())
			return;
		//
		OnError();
	}
	//
	void OnError()
	{
		if (m_strHiddenagID.IsEmpty()
			|| m_strLocalURL.IsEmpty())
			return;
		//
		Navigate(m_strLocalURL);
	}
};


#endif //_WIZATLBROWSER_H_
