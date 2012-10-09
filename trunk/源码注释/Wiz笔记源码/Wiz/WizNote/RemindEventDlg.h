#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>


// CRemindEventDlg

class CRemindEventDlg
	: public CAxDialogImpl<CRemindEventDlg>
	, public CWinDataExchange<CRemindEventDlg>
{
public:
	CRemindEventDlg(IWizEvent* pEvent)
		: m_spEvent(pEvent)
	{
		ATLASSERT(m_spEvent);
		//
		m_wndBrowser.m_bNo3DBorder = TRUE;
	}
	~CRemindEventDlg()
	{
	}

	enum { IDD = IDD_DIALOG_REMIND_EVENT };

public:
	CComPtr<IWizEvent> m_spEvent;
	//
	CAtlBrowser m_wndBrowser;
	CStaticImpl m_wndStaticBrowser;
	
public:
	CComPtr<IWizEvent> GetEvent() const { return m_spEvent; }
private:
	
	void RandomPosition()
	{
		CRect rcNote;
		GetWindowRect(&rcNote);
		//
		int width = ::GetSystemMetrics(SM_CXSCREEN);
		int height = ::GetSystemMetrics(SM_CYSCREEN);
		//
		int x = width - rcNote.Width() - 40;
		int y = height - rcNote.Height() - 40;
		//
		if (x <= 0 || y <= 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = GetTickCount() * 10 % x;
			y = GetTickCount() * 10 % y;
		}
		//
		rcNote.MoveToXY(x, y);
		MoveWindow(rcNote, FALSE);
	}
public:
	BEGIN_DDX_MAP(CRemindEventDlg)
		DDX_CONTROL(IDC_STATIC_BROWSER, m_wndStaticBrowser)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CRemindEventDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_COMPLETE, BN_CLICKED, OnBnClickedButtonComplete)
		COMMAND_HANDLER(IDC_BUTTON_DONOT_REMIND_ME_AGAIN, BN_CLICKED, OnBnClickedButtonDonotRemindMeAgain)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnBnClickedCancel)
		CHAIN_MSG_MAP(CAxDialogImpl<CRemindEventDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DoDataExchange(FALSE);
		WizTranslationsTranslateWindow(m_hWnd);
		//
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);
		//
		CRect rcBrowser;
		m_wndStaticBrowser.GetWindowRect(&rcBrowser);
		ScreenToClient(&rcBrowser);
		//
		m_wndBrowser.CreateEx(m_hWnd, NULL);
		m_wndBrowser.MoveWindow(&rcBrowser);
		m_wndBrowser.ShowWindow(SW_SHOW);
		//
		//CenterWindow();
		RandomPosition();
		//
		if (CComPtr<IWizDocument> spDocument = CWizKMDatabase::GetEventDocument(m_spEvent))
		{
			CString strTitle;
			GetWindowText(strTitle);
			SetWindowText(WizFormatString2(_T("%1 - %2"), strTitle, CWizKMDatabase::GetDocumentTitle(spDocument)));
			//
			CString strFileName = CWizKMDatabase::DocumentToTemp(spDocument, 0);
			if (!strFileName.IsEmpty())
			{
				m_wndBrowser.Navigate(strFileName);
			}
		}
		//
		return 0;
	}
	LRESULT OnBnClickedButtonComplete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DestroyWindow();
		//
		WizKMEventSetCompleted(m_spEvent);
		//
		if (WizKMGetPrivateBool(_T("Event"), _T("CompleteTodoWhileEventCompleted"), TRUE))
		{
			WizKMSetEventTodoCompleted(m_spEvent);
			//
			WizGetMainDlg()->PostMessage(UM_REFRESH_TODO_LIST, 0, 0);
		}
		//
		return 0;
	}
	LRESULT OnBnClickedButtonDonotRemindMeAgain(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DestroyWindow();
		//
		WizKMEventSetDonotRemind(m_spEvent);
		//
		return 0;
	}
	LRESULT OnBnClickedCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DestroyWindow();
		//
		return 0;
	}
};


