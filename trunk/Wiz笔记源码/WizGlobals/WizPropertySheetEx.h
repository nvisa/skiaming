#pragma once


const UINT UM_WM_INITWIZPROPERTYSHEET = ::RegisterWindowMessage(_T("UM_WM_INITWIZPROPERTYSHEET"));
const UINT UM_WM_PROPERTYSHEET_UPDATE_STATUS = ::RegisterWindowMessage(_T("UM_WM_PROPERTYSHEET_UPDATE_STATUS"));


#ifdef __AFX_H__

class CWizPropertySheetEx : public CPropertySheet
{
public:
	CWizPropertySheetEx()
	{
	}
	CWizPropertySheetEx(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0)
		:CPropertySheet(nIDCaption, pParentWnd ,iSelectPage)
	{
	}
	CWizPropertySheetEx(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0)
		:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
	{
	}
	CWizPropertySheetEx(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL)
		: CPropertySheet(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
	{
	}
	CWizPropertySheetEx(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL)
		: CPropertySheet(pszCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
	{
	}

	virtual BOOL OnInitDialog()
	{
		BOOL b = CPropertySheet::OnInitDialog();
		WizTranslationsTranslatePropertySheet(m_hWnd);
		return b;
	}
};


#else


class CWizPropertySheetEx : public CPropertySheetImpl<CWizPropertySheetEx>
{
public:
	CWizPropertySheetEx(ATL::_U_STRINGorID title = (LPCTSTR)NULL, UINT uStartPage = 0, HWND hWndParent = NULL)
		: CPropertySheetImpl<CWizPropertySheetEx>(title, uStartPage, hWndParent)
	{
	}
	void OnSheetInitialized()
	{
		PostMessage(UM_WM_INITWIZPROPERTYSHEET, 0, 0);
	}
BEGIN_MSG_MAP(CWizPropertySheetEx)
		MESSAGE_HANDLER(UM_WM_INITWIZPROPERTYSHEET, OnInitWizPropertySheet)
END_MSG_MAP()
	//
	LRESULT OnInitWizPropertySheet(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(NULL);
		WizTranslationsTranslatePropertySheet(m_hWnd);
		//
		return 0;
	}
};



inline BOOL WizPropertySheetPageIsActive(HWND hwndPropertyPage)
{
	CWindow wndSheet = GetParent(hwndPropertyPage);
	if (!wndSheet.IsWindow())
		return FALSE;
	//
	CWindow wndPage = PropSheet_GetCurrentPageHwnd(wndSheet);
	if (!wndPage.IsWindow())
		return FALSE;
	//
	return wndPage == hwndPropertyPage;
}

inline void WizPropertySheetEnableOKButton(HWND hwndPropertyPage, BOOL bEnabled)
{
	CWindow wndSheet = GetParent(hwndPropertyPage);
	if (!wndSheet.IsWindow())
		return;
	//
	CWindow btnOK = wndSheet.GetDlgItem(IDOK);
	if (btnOK.IsWindow())
	{
		btnOK.EnableWindow(bEnabled);
	}
}

#endif
