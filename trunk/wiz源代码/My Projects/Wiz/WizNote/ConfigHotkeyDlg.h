// OptionsDatabaseDlg.h : Declaration of the CConfigHotkeyDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

// CConfigHotkeyDlg

#include "NoteSettings.h"

class CConfigHotkeyDlg 
	: public CAxPropertyPageImpl<CConfigHotkeyDlg>
	, public CWinDataExchange<CConfigHotkeyDlg>
{
public:
	CConfigHotkeyDlg()
	{
		m_nSaveLocation = ExplorerGetSaveDestination();
	}

	~CConfigHotkeyDlg()
	{
	}
private:
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyNewNote;
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyDisplayNotes;
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyClipScreen;
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyCopySelection;
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyPasteClipboard;
	int m_nSaveLocation;
public:

	enum { IDD = IDD_DIALOG_CONFIG_HOTKEY };

	BEGIN_DDX_MAP(CBackgroundOptsPage)
		DDX_CONTROL(IDC_HOTKEY_CREATE_NEW_NOTE, m_hotkeyNewNote)
		DDX_CONTROL(IDC_HOTKEY_DISPLAY_NOTES, m_hotkeyDisplayNotes)
		DDX_CONTROL(IDC_EDIT_CLIP_SCREEN, m_hotkeyClipScreen)
		DDX_CONTROL(IDC_EDIT_COPY_SELECTION, m_hotkeyCopySelection)
		DDX_CONTROL(IDC_EDIT_PASTE_CLIPBOARD, m_hotkeyPasteClipboard)
		DDX_RADIO(IDC_RADIO_SAVE_TO_MYDRAFTS, m_nSaveLocation)
    END_DDX_MAP()

	BEGIN_MSG_MAP(CConfigHotkeyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_RESTORE_DEFAULTS, BN_CLICKED, OnBnClickedButtonRestoreDefaults)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CConfigHotkeyDlg>)
	END_MSG_MAP()



	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxPropertyPageImpl<CConfigHotkeyDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		WizTranslationsTranslateWindow(m_hWnd);
		//
		DoDataExchange(FALSE);
		//
		m_hotkeyNewNote.SetStateSection(SECTION_HOTKEY_NOTE, HOTKEY_NAME_NEWNOTE, HOTKEY_DEFAULT_NEWNOTE);
		m_hotkeyDisplayNotes.SetStateSection(SECTION_HOTKEY_NOTE, HOTKEY_NAME_DISPLAY_NOTES, HOTKEY_DEFAULT_DISPLAY_NOTE);
		m_hotkeyClipScreen.SetStateSection(SECTION_HOTKEY, HOTKEY_NAME_CLIPSCREEN, HOTKEY_DEFAULT_CLIPSCREEN);
		m_hotkeyCopySelection.SetStateSection(SECTION_HOTKEY, HOTKEY_NAME_COPYCLIPBOARD, HOTKEY_DEFAULT_COPYSELECTION);
		m_hotkeyPasteClipboard.SetStateSection(SECTION_HOTKEY, HOTKEY_NAME_PASTECLIPBOARD, HOTKEY_DEFAULT_PASTECLIPBOARD);
		//
		return 1;  // Let the system set the focus
	}

	int OnApply()
	{
		if (!DoDataExchange(TRUE))
			return PSNRET_INVALID;
		//
		m_hotkeyNewNote.Save();
		m_hotkeyDisplayNotes.Save();
		m_hotkeyClipScreen.Save();
		m_hotkeyCopySelection.Save();
		m_hotkeyPasteClipboard.Save();
		//
		ExplorerSetSaveDestination((WizSaveDestination)m_nSaveLocation);
		//
		return PSNRET_NOERROR;
	}

	LRESULT OnBnClickedButtonRestoreDefaults(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_hotkeyNewNote.SetWindowText(HOTKEY_DEFAULT_NEWNOTE);
		m_hotkeyDisplayNotes.SetWindowText(HOTKEY_DEFAULT_DISPLAY_NOTE);
		m_hotkeyClipScreen.SetWindowText(HOTKEY_DEFAULT_CLIPSCREEN);
		m_hotkeyCopySelection.SetWindowText(HOTKEY_DEFAULT_COPYSELECTION);
		m_hotkeyPasteClipboard.SetWindowText(HOTKEY_DEFAULT_PASTECLIPBOARD);
		//
		return 0;
	}
};


