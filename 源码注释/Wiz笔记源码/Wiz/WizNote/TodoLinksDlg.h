#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "../Globals/WizKMCommonUI.h"

// CTodoLinksDlg

class CTodoLinksDlg
	: public CAxDialogImpl<CTodoLinksDlg>
	, public CWinDataExchange<CTodoLinksDlg>
{
public:
	CTodoLinksDlg(CWizKMDatabase* pDatabase, const CWizStdStringArray& arrayDocumentGUID)
		: m_pDatabase(pDatabase)
		, m_arrayDocumentGUID(arrayDocumentGUID)
	{
		ATLASSERT(m_pDatabase);
	}
	~CTodoLinksDlg()
	{
	}

	enum { IDD = IDD_DIALOG_TODO_LINKS};

public:
	CWizKMDatabase* m_pDatabase;
	CWizStdStringArray m_arrayDocumentGUID;
	//
	CListBoxImpl m_wndList;
public:
	BEGIN_DDX_MAP(CTodoLinksDlg)
		DDX_CONTROL(IDC_LIST_DOCUMENTS, m_wndList)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CTodoLinksDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_ADD, BN_CLICKED, OnBnClickedButtonAdd)
		COMMAND_HANDLER(IDC_BUTTON_REMOVE, BN_CLICKED, OnBnClickedButtonRemove)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnBnClickedOk)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnBnClickedCancel)
		CHAIN_MSG_MAP(CAxDialogImpl<CTodoLinksDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DoDataExchange(FALSE);
		WizTranslationsTranslateWindow(m_hWnd);
		//
		ATLASSERT(m_pDatabase);
		for (CWizStdStringArray::const_iterator it = m_arrayDocumentGUID.begin();
			it != m_arrayDocumentGUID.end();
			it++)
		{
			CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(*it);
			if (spDocument)
			{
				AddItem(spDocument, *it);
			}
		}
		//
		return 0;
	}
	//
	int AddItem(IWizDocument* pDocument, LPCTSTR lpszDocumentGUID)
	{
		int nItem = m_wndList.AddString(CWizKMDatabase::GetDocumentTitle(pDocument));
		m_wndList.SetItemData(nItem, (DWORD_PTR)(new CString(lpszDocumentGUID)));
		//
		return nItem;
	}
	//
	void DeleteItem(int nIndex)
	{
		if (nIndex < 0)
			return;
		if (nIndex >= m_wndList.GetCount())
			return;
		//
		CString* pString = (CString *)m_wndList.GetItemData(nIndex);
		if (pString)
		{
			delete pString;
		}
		//
		m_wndList.DeleteString(nIndex);
	}
	//
	LRESULT OnBnClickedButtonAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
		if (!spCommonUI)
			return 0;
		//
		CComPtr<IDispatch> spDisp;
		//
		spCommonUI->SelectWizDocument(CComBSTR(m_pDatabase->GetDatabasePath()),
			CComBSTR(WizFormatString0(IDS_SELECT_DOCUMENT)), 
			&spDisp);
		//
		if (!spDisp)
			return 0;
		//
		CWizDocumentArray arrayDocument;
		WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
		//
		for (CWizDocumentArray::iterator it = arrayDocument.begin();
			it != arrayDocument.end();
			it++)
		{
			CComPtr<IWizDocument> spDocument = *it;
			AddItem(spDocument, CWizKMDatabase::GetObjectGUID(spDocument.p));
		}

		return 0;
	}

	LRESULT OnBnClickedButtonRemove(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		//
		for (int i = m_wndList.GetCount() - 1; i >= 0; i--)
		{
			if (m_wndList.GetSel(i))
			{
				DeleteItem(i);
			}
		}

		return 0;
	}

	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		//
		m_arrayDocumentGUID.clear();
		//
		for (int i = 0; i < m_wndList.GetCount(); i++)
		{
			CString* pString = (CString *)m_wndList.GetItemData(i);
			if (pString)
			{
				m_arrayDocumentGUID.push_back(*pString);
			}
		}
		//
		for (int i = m_wndList.GetCount() - 1; i >= 0; i--)
		{
			DeleteItem(i);
		}
		//
		EndDialog(IDOK);

		return 0;
	}

	LRESULT OnBnClickedCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		EndDialog(IDCANCEL);

		return 0;
	}
};


