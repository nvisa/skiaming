// OptionsDatabaseDlg.h : Declaration of the CConfigToolbarDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "NoteSettings.h"

// CConfigToolbarDlg

class CConfigToolbarDlg 
	: public CAxPropertyPageImpl<CConfigToolbarDlg>
	, public CWinDataExchange<CConfigToolbarDlg>
{
public:
	CConfigToolbarDlg()
	{
		CWizKMSettings settings;
		m_bNewNote = GetToolbarButtonVisible(settings, _T("NewNote"));
		m_bNewTodoList = GetToolbarButtonVisible(settings, _T("NewTodoList"));
		m_bCopySelection = GetToolbarButtonVisible(settings, _T("CopySelection"));
		m_bClipScreen = GetToolbarButtonVisible(settings, _T("ClipScreen"));
		m_bPasteToWiz = GetToolbarButtonVisible(settings, _T("PasteToWiz"));
		m_bSync = GetToolbarButtonVisible(settings, _T("Sync"));
		m_bWizCalendar = GetToolbarButtonVisible(settings, _T("WizCalendar"));
		m_bWizExplorer = GetToolbarButtonVisible(settings, _T("WizExplorer"));
	}

	~CConfigToolbarDlg()
	{
	}
private:
	BOOL m_bNewNote;
	BOOL m_bNewTodoList;
	BOOL m_bCopySelection;
	BOOL m_bClipScreen;
	BOOL m_bPasteToWiz;
	BOOL m_bSync;
	BOOL m_bWizCalendar;
	BOOL m_bWizExplorer;
public:

	enum { IDD = IDD_DIALOG_CONFIG_TOOLBAR };

	BEGIN_DDX_MAP(CBackgroundOptsPage)
		DDX_CHECK(IDC_CHECK_NEW_NOTE, m_bNewNote)
		DDX_CHECK(IDC_CHECK_TODO_LIST, m_bNewTodoList)
		DDX_CHECK(IDC_CHECK_COPY_SELECTION, m_bCopySelection)
		DDX_CHECK(IDC_CHECK_CLIP_SCREENSHOT, m_bClipScreen)
		DDX_CHECK(IDC_CHECK_PASTE_TO_WIZ, m_bPasteToWiz)
		DDX_CHECK(IDC_CHECK_SYNC, m_bSync)
		DDX_CHECK(IDC_CHECK_WIZCLENDAR, m_bWizCalendar)
		DDX_CHECK(IDC_CHECK_WIZ, m_bWizExplorer)
    END_DDX_MAP()

	BEGIN_MSG_MAP(CConfigToolbarDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CConfigToolbarDlg>)
	END_MSG_MAP()



	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxPropertyPageImpl<CConfigToolbarDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		WizTranslationsTranslateWindow(m_hWnd);
		//
		DoDataExchange(FALSE);
		//
		return 1;  // Let the system set the focus
	}

	int OnApply()
	{
		if (!DoDataExchange(TRUE))
			return PSNRET_INVALID;
		//
		CWizKMSettings settings;
		SetToolbarButtonVisible(settings, _T("NewNote"), m_bNewNote);
		SetToolbarButtonVisible(settings, _T("NewTodoList"), m_bNewTodoList);
		SetToolbarButtonVisible(settings, _T("CopySelection"), m_bCopySelection);
		SetToolbarButtonVisible(settings, _T("ClipScreen"), m_bClipScreen);
		SetToolbarButtonVisible(settings, _T("PasteToWiz"), m_bPasteToWiz);
		SetToolbarButtonVisible(settings, _T("Sync"), m_bSync);
		SetToolbarButtonVisible(settings, _T("WizCalendar"), m_bWizCalendar);
		SetToolbarButtonVisible(settings, _T("WizExplorer"), m_bWizExplorer);

		//
		return PSNRET_NOERROR;
	}
};


