// OptionsDatabaseDlg.h : Declaration of the CConfigGeneralDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "NoteSettings.h"

// CConfigGeneralDlg

class CConfigGeneralDlg 
	: public CAxPropertyPageImpl<CConfigGeneralDlg>
	, public CWinDataExchange<CConfigGeneralDlg>
{
public:
	CConfigGeneralDlg()
	{
		m_strNote = _T("WizNote");
		m_bExplorerExists = ::WizKMExplorerExists();
	}

	~CConfigGeneralDlg()
	{
	}
private:
	CString m_strNote;
	CButtonImpl m_btnAutoRun;
	CButtonImpl m_btnAutoCreateTodayTaskNote;
	CButtonImpl m_btnShowTaskbarButtons;
	CButtonImpl m_btnMoveUncompletedTasks;
	CComboBoxImpl m_wndStartOfDay;
	CComboBoxImpl m_wndCompactButton;
	CComboBoxImpl m_wndDoubleClickAction;
	BOOL m_bExplorerExists;
public:

	enum { IDD = IDD_DIALOG_CONFIG_GENERAL };

	BEGIN_MSG_MAP(CConfigGeneralDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_SYNC_OPTIONS, BN_CLICKED, OnBnClickedButtonSyncOptions)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CConfigGeneralDlg>)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CBackgroundOptsPage)
		DDX_CONTROL(IDC_CHECK_AUTO_RUN, m_btnAutoRun)
		DDX_CONTROL(IDC_CHECK_AUTO_CREATE_TODAY_TASK_NOTE, m_btnAutoCreateTodayTaskNote)
		DDX_CONTROL(IDC_CHECK_MOVE_UNCOMPLETED_TASKS, m_btnMoveUncompletedTasks)
		DDX_CONTROL(IDC_CHECK_SHOW_TASKBAR_BUTTONS, m_btnShowTaskbarButtons)
		DDX_CONTROL(IDC_COMBO_START_OF_DAY, m_wndStartOfDay)
		DDX_CONTROL(IDC_COMBO_COMPACT_BUTTON, m_wndCompactButton)
		DDX_CONTROL(IDC_COMBO_DOUBLE_CLICK_ACTION, m_wndDoubleClickAction)
    END_DDX_MAP()


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxPropertyPageImpl<CConfigGeneralDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		WizTranslationsTranslateWindow(m_hWnd);
		//
		DoDataExchange(FALSE);
		//
		m_btnAutoRun.SetCheck(WizIsAutoRun(m_strNote) ? BST_CHECKED : BST_UNCHECKED);
		m_btnAutoCreateTodayTaskNote.SetCheck(IsAutoCreateTodayTasks() ? BST_CHECKED : BST_UNCHECKED);
		m_btnMoveUncompletedTasks.SetCheck(IsMoveUncompletedToTodayTasks() ? BST_CHECKED : BST_UNCHECKED);
		m_btnShowTaskbarButtons.SetCheck(IsShowTaskbarButtons() ? BST_CHECKED : BST_UNCHECKED);
		m_btnShowTaskbarButtons.EnableWindow(WizGetSystemVersion() >= svWin7);
		//
		//
		m_wndStartOfDay.AddString(_T("00:00"));
		m_wndStartOfDay.AddString(_T("01:00"));
		m_wndStartOfDay.AddString(_T("02:00"));
		m_wndStartOfDay.AddString(_T("03:00"));
		m_wndStartOfDay.AddString(_T("04:00"));
		m_wndStartOfDay.AddString(_T("05:00"));
		m_wndStartOfDay.AddString(_T("06:00"));
		m_wndStartOfDay.AddString(_T("07:00"));
		//
		if (m_bExplorerExists)
		{
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_NEWNOTE));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_COPYSELECTION));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_PASTETOWIZ));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_CLIPSCREENSHOT));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_SYNC));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_TODOLIST));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_WIZCALENDAR));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_WIZEXPLORER));
			//
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_NEW_NOTE));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_OPENED_NOTES));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_RECENT_NOTES));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_TASKS));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_OPEN_WIZEXPLORER));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_OPEN_WIZCALENDAR));
			//
			m_wndStartOfDay.SetCurSel(GetStartOfDay());
			if (m_wndStartOfDay.GetCurSel() == CB_ERR)
			{
				m_wndStartOfDay.SetCurSel(0);
			}
			//
			CString strButtonName = GetCompactButton();
			if (0 == strButtonName.CompareNoCase(_T("CopySelection")))
			{
				m_wndCompactButton.SetCurSel(1);
			}
			else if (0 == strButtonName.CompareNoCase(_T("PasteToWiz")))
			{
				m_wndCompactButton.SetCurSel(2);
			}
			else if (0 == strButtonName.CompareNoCase(_T("ClipScreenshot")))
			{
				m_wndCompactButton.SetCurSel(3);
			}
			else if (0 == strButtonName.CompareNoCase(_T("Sync")))
			{
				m_wndCompactButton.SetCurSel(4);
			}
			else if (0 == strButtonName.CompareNoCase(_T("TodoList")))
			{
				m_wndCompactButton.SetCurSel(5);
			}
			else if (0 == strButtonName.CompareNoCase(_T("Calendar")))
			{
				m_wndCompactButton.SetCurSel(6);
			}
			else if (0 == strButtonName.CompareNoCase(_T("Explorer")))
			{
				m_wndCompactButton.SetCurSel(7);
			}
			else
			{
				m_wndCompactButton.SetCurSel(0);
			}
			//
			CString strActionName = GetDoubleClickAction();
			if (0 == strActionName.CompareNoCase(_T("ShowOpenedNotes")))
			{
				m_wndDoubleClickAction.SetCurSel(1);
			}
			else if (0 == strActionName.CompareNoCase(_T("ShowRecentNotes")))
			{
				m_wndDoubleClickAction.SetCurSel(2);
			}
			else if (0 == strActionName.CompareNoCase(_T("ShowTasks")))
			{
				m_wndDoubleClickAction.SetCurSel(3);
			}
			else if (0 == strActionName.CompareNoCase(_T("Explorer")))
			{
				m_wndDoubleClickAction.SetCurSel(4);
			}
			else if (0 == strActionName.CompareNoCase(_T("Calendar")))
			{
				m_wndDoubleClickAction.SetCurSel(5);
			}
			else
			{
				m_wndDoubleClickAction.SetCurSel(0);
			}
		}
		else
		{
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_NEWNOTE));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_SYNC));
			m_wndCompactButton.AddString(WizFormatStringEx0(ID_TRAY_TODOLIST));
			//
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_NEW_NOTE));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_OPENED_NOTES));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_RECENT_NOTES));
			m_wndDoubleClickAction.AddString(WizFormatString0(IDS_SHOW_TASKS));
			//
			m_wndStartOfDay.SetCurSel(GetStartOfDay());
			if (m_wndStartOfDay.GetCurSel() == CB_ERR)
			{
				m_wndStartOfDay.SetCurSel(0);
			}
			//
			CString strButtonName = GetCompactButton();
			if (0 == strButtonName.CompareNoCase(_T("Sync")))
			{
				m_wndCompactButton.SetCurSel(1);
			}
			else if (0 == strButtonName.CompareNoCase(_T("TodoList")))
			{
				m_wndCompactButton.SetCurSel(2);
			}
			else
			{
				m_wndCompactButton.SetCurSel(0);
			}
			//
			CString strActionName = GetDoubleClickAction();
			if (0 == strActionName.CompareNoCase(_T("ShowOpenedNotes")))
			{
				m_wndDoubleClickAction.SetCurSel(1);
			}
			else if (0 == strActionName.CompareNoCase(_T("ShowRecentNotes")))
			{
				m_wndDoubleClickAction.SetCurSel(2);
			}
			else if (0 == strActionName.CompareNoCase(_T("ShowTasks")))
			{
				m_wndDoubleClickAction.SetCurSel(3);
			}
			else
			{
				m_wndDoubleClickAction.SetCurSel(0);
			}
		}
		//
		return 1;  // Let the system set the focus
	}

	int OnApply()
	{
		if (!DoDataExchange(TRUE))
			return PSNRET_INVALID;
		//
		if (m_btnAutoRun.GetCheck() == BST_CHECKED)
		{
			WizEnableAutoRun(HKEY_CURRENT_USER, m_strNote, WizGetAppFileName());
		}
		else
		{
			WizDisableAutoRun(m_strNote);
		}
		//
		SetAutoCreateTodayTasks(m_btnAutoCreateTodayTaskNote.GetCheck() == BST_CHECKED);
		SetMoveUncompletedToTodayTasks(m_btnMoveUncompletedTasks.GetCheck() == BST_CHECKED);
		SetShowTaskbarButtons(m_btnShowTaskbarButtons.GetCheck() == BST_CHECKED);
		//
		SetStartOfDay(m_wndStartOfDay.GetCurSel());
		//
		if (m_bExplorerExists)
		{
			int nButtonIndex = m_wndCompactButton.GetCurSel();
			CString strButtonName = _T("NewNote");
			switch (nButtonIndex)
			{
			case 1:
				strButtonName = _T("CopySelection");
				break;
			case 2:
				strButtonName = _T("PasteToWiz");
				break;
			case 3:
				strButtonName = _T("ClipScreenshot");
				break;
			case 4:
				strButtonName = _T("Sync");
				break;
			case 5:
				strButtonName = _T("TodoList");
				break;
			case 6:
				strButtonName = _T("Calendar");
				break;
			case 7:
				strButtonName = _T("Explorer");
				break;
			}
			SetCompactButton(strButtonName);
			//
			int nActionIndex = m_wndDoubleClickAction.GetCurSel();
			CString strActionName = _T("NewNote");
			switch (nActionIndex)
			{
			case 1:
				strActionName = _T("ShowOpenedNotes");
				break;
			case 2:
				strActionName = _T("ShowRecentNotes");
				break;
			case 3:
				strActionName = _T("ShowTasks");
				break;
			case 4:
				strActionName = _T("Explorer");
				break;
			case 5:
				strActionName = _T("Calendar");
				break;
			}
			SetDoubleClickAction(strActionName);
		}
		else
		{
			int nButtonIndex = m_wndCompactButton.GetCurSel();
			CString strButtonName = _T("NewNote");
			switch (nButtonIndex)
			{
			case 1:
				strButtonName = _T("Sync");
				break;
			case 2:
				strButtonName = _T("TodoList");
				break;
			}
			SetCompactButton(strButtonName);
			//
			int nActionIndex = m_wndDoubleClickAction.GetCurSel();
			CString strActionName = _T("NewNote");
			switch (nActionIndex)
			{
			case 1:
				strActionName = _T("ShowOpenedNotes");
				break;
			case 2:
				strActionName = _T("ShowRecentNotes");
				break;
			case 3:
				strActionName = _T("ShowTasks");
				break;
			}
			SetDoubleClickAction(strActionName);
		}
		//
		return PSNRET_NOERROR;
	}
	//
	LRESULT OnBnClickedButtonSyncOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::WizKMOptionsDlg(0x00100000);
		//
		return 0;
	}
};
