// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "WizKMCalendarView.h"
#include "MainFrm.h"

#include "../Globals/WizKMCommonUI.h"

CMainFrame* CMainFrame::m_spMainFrame = NULL;

CMainFrame* WizGetMainFrame()
{
	return CMainFrame::GetMainFrame();
}
CWizKMDatabase* WizGetDatabase()
{
	return WizGetMainFrame()->GetDatabase();
}


CMainFrame::CMainFrame(LPCTSTR lpszCommandLine)
	: CWizWindowState(_T("Calendar_MainWindow"))
	, m_strCommandLine(lpszCommandLine)
{
	m_spMainFrame = this;
	//
	m_leftview.SetEventsListener(this);
	m_view.SetEventsListener(this);
	//
	m_nMessageCalendarEventModified = ::RegisterWindowMessage(WIZKM_CALENDAR_EVENT_MODIFIED_MESSAGE_NAME);
	//
	CString strSection(_T("WizKMCalendar"));
	//
	CWizKMSettings settings;
	m_view.SetView((WizCalendarViewType)settings.GetInt(strSection, _T("View"), viewtypeMonth));
	m_view.SetBackgroundTextType((WizKMMonthViewCellBackgroundTextType)settings.GetInt(strSection, _T("Background"), textNone));
}


CMainFrame* CMainFrame::GetMainFrame()
{
	ATLASSERT(m_spMainFrame);
	return m_spMainFrame;
}

BOOL CMainFrame::OpenDatabase()
{
	CString strDatabasePath = ::WizGetCommandLineValue(m_strCommandLine, _T("DatabasePath"));
	//
	if (!m_db.DefaultOpen(strDatabasePath))
	{
		TOLOG(_T("Failed to open database!"));
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	WizKMSetCalendarWindowHandle(m_hWnd);
	//
	SetMenu(NULL);
	//
	m_toolbar.CreateEx(m_hWnd);
	ATLASSERT(m_toolbar.IsWindow());
	//
	//
	m_toolbar.AddToolButton(ID_CALENDAR_NEWEVENT);
	m_toolbar.AddToolButton(ID_CALENDAR_EDITEVENT);
	m_toolbar.AddToolButton(ID_CALENDAR_DELETEEVENT);
	m_toolbar.AddToolButton(ID_CALENDAR_MONTH);
	m_toolbar.AddToolButton(ID_CALENDAR_WEEK);
	m_toolbar.AddToolButton(ID_CALENDAR_DAY);
	m_toolbar.AddToolButton(ID_CALENDAR_BACKGROUND, BTNS_WHOLEDROPDOWN);
	m_toolbar.AddToolButton(ID_CALENDAR_HELP, BTNS_WHOLEDROPDOWN);
	m_toolbar.AddToolButton(ID_CALENDAR_OPTIONS);
	//
	m_toolbar.AutoSetButtonSize();
	//
	UIAddToolBar(m_toolbar);
	//
	m_hWndToolBar = m_toolbar;
	//
	CreateSimpleStatusBar();
	//
	m_hWndClient = m_splitter.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	m_splitter.m_cxyMin = 240; // minimum size
	m_splitter.SetSplitterPos(240); // from left
	m_splitter.m_bFullDrag = false; // ghost bar enabled
	m_splitter.m_cxySplitBar = 6;
	//
	m_leftview.Create(m_splitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_view.Create(m_splitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, 0);
	//
	m_splitter.SetSplitterPane(0, m_leftview);
	m_splitter.SetSplitterPane(1, m_view);
	//
	m_splitter.m_cxyMin = m_leftview.GetMinWidth();
	//
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);
	//
	WCV_OnViewChanged(m_view.GetView());
	WCV_OnEventChanged(m_view.GetSelectedEvent());
	//
	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	//
	WizKMSetCalendarWindowHandle(NULL);
	//
	CString strSection(_T("WizKMCalendar"));
	//
	CWizKMSettings settings;
	settings.SetInt(strSection, _T("View"), m_view.GetView());
	settings.SetInt(strSection, _T("Background"), m_view.GetBackgroundTextType());
	//
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}
LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainFrame::OnCalendarDay(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetView(viewtypeDay);

	return 0;
}

LRESULT CMainFrame::OnCalendarMonth(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetView(viewtypeMonth);

	return 0;
}

LRESULT CMainFrame::OnCalendarWeek(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetView(viewtypeWeek);

	return 0;
}

LRESULT CMainFrame::OnCalendarNewevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.CreateEvent(m_view.GetSelectedTime());
	//
	return 0;
}

LRESULT CMainFrame::OnCalendarDeleteevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.DeleteEvent(m_view.GetSelectedEvent());

	return 0;
}
void CMainFrame::MCV_OnDateChanged(const COleDateTime& t)
{
	m_view.SetSelectedTime(WizTimeBuildTime(t, m_view.GetSelectedTime()), FALSE);
	m_leftview.SetTime(t);
}
void CMainFrame::MCV_OnTagsChanged(const CWizStdStringArray& arrayTags)
{
	m_view.SetTags(arrayTags);
}

void CMainFrame::WCV_OnTimeChanged(const COleDateTime& t)
{
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	//
	m_leftview.m_calendar.SetCurSel(&st);
	m_leftview.SetTime(t);
}
void CMainFrame::WCV_OnEventChanged(const WIZCALENDAREVENTDATA& e)
{
	UIEnable(ID_CALENDAR_DELETEEVENT, !e.IsNull());
	UIEnable(ID_CALENDAR_EDITEVENT, !e.IsNull());
}
void CMainFrame::WCV_OnViewChanged(WizCalendarViewType eView)
{
	UISetCheck(ID_CALENDAR_MONTH, eView == viewtypeMonth);
	UISetCheck(ID_CALENDAR_WEEK, eView == viewtypeWeek);
	UISetCheck(ID_CALENDAR_DAY, eView == viewtypeDay);
}

LRESULT CMainFrame::OnToolbarDropDownMenu(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nID = (UINT)wParam;
	HMENU hMenu = (HMENU)lParam;
	if (!::IsMenu(hMenu))
		return 0;
	//
	if (ID_CALENDAR_BACKGROUND == nID)
	{
		CMenuHandle menu(hMenu);
		//
		UINT nChecked = MF_BYCOMMAND | MF_CHECKED;
		UINT nUnchecked = MF_BYCOMMAND | MF_UNCHECKED;
		//
		UINT nID = 0;
		//
		WizKMMonthViewCellBackgroundTextType eType = m_view.GetBackgroundTextType();
		switch (eType)
		{
		case textNone:
			nID = ID_BACKGROUND_NONE;
			break;
		case textNote:
			nID = ID_BACKGROUND_NOTE;
			break;
		case textTodoList:
			nID = ID_BACKGROUND_TODOLIST;
			break;
		case textJournal:
			nID = ID_BACKGROUND_JOURNAL;
			break;
		}
		menu.CheckMenuRadioItem(ID_BACKGROUND_NONE, ID_BACKGROUND_JOURNAL, nID, MF_BYCOMMAND);

		/*
		menu.CheckMenuItem(ID_BACKGROUND_NONE, m_view.GetBackgroundTextType() == textNone ? nChecked : nUnchecked);
		menu.CheckMenuItem(ID_BACKGROUND_NOTE, m_view.GetBackgroundTextType() == textNote ? nChecked : nUnchecked);
		menu.CheckMenuItem(ID_BACKGROUND_TODOLIST, m_view.GetBackgroundTextType() == textTodoList ? nChecked : nUnchecked);
		*/
	}
	//
	return 0;
}

LRESULT CMainFrame::OnCalendarEditevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.EditEvent(m_view.GetSelectedEvent());

	return 0;
}

LRESULT CMainFrame::OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_view.ResetEvents();
	//
	return 0;
}
LRESULT CMainFrame::OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMAbout();

	return 0;
}

LRESULT CMainFrame::OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMWebSiteVisitHelp(_T("wizcalendar"));

	return 0;
}

void CMainFrame::LoadStatus()
{
	CMainFrameWindowState::LoadStatus();
	//
	m_splitter.SetStateSection(_T("Calendar_CatalogChooserSplitter"));
}
void CMainFrame::UpdateLayout(BOOL bResizeBars /*= TRUE*/)
{
	CRect rc;
	GetClientRect(&rc);
	//
	int nToolBarHeight = m_toolbar.GetMinHeight();
	//
	CRect rcToolBar(0, 0, rc.right, nToolBarHeight);
	//
	m_toolbar.SetWindowPos(NULL, rcToolBar.left, rcToolBar.top, rcToolBar.Width(), rcToolBar.Height(), SWP_NOZORDER);
	//
	CFrameWindowImplBase::UpdateLayout(bResizeBars);
}

LRESULT CMainFrame::OnBackgroundNone(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetBackgroundTextType(textNone);

	return 0;
}

LRESULT CMainFrame::OnBackgroundNote(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetBackgroundTextType(textNote);

	return 0;
}

LRESULT CMainFrame::OnBackgroundTodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetBackgroundTextType(textTodoList);

	return 0;
}

LRESULT CMainFrame::OnBackgroundJournal(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_view.SetBackgroundTextType(textJournal);

	return 0;
}


LRESULT CMainFrame::OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE, 0, 0);
	return 0;
}
LRESULT CMainFrame::OnOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return 0;
	//
	spCommonUI->CalendarDlg(0);
	//
	m_view.LoadSettings();
	m_view.Invalidate();
	//
	//
	return 0;
}
