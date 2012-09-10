// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MonthCalendarView.h"


class CMainFrame 
	: public CFrameWindowImpl<CMainFrame>
	, public CUpdateUI<CMainFrame>
	, public CMessageFilter
	, public CIdleHandler
	, public IMonthCalendarViewEvents
	, public IWizCalendarViewEvents
	, public CWizWindowState<CMainFrame, CWizKMSettings>
{
public:
	CMainFrame(LPCTSTR lpszCommandLine);
	//
	typedef CWizWindowState<CMainFrame, CWizKMSettings> CMainFrameWindowState;
	//
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
public:
private:
	static CMainFrame* m_spMainFrame;
public:
	static CMainFrame* GetMainFrame();
private:
	UINT m_nMessageCalendarEventModified;

public:
	CWizKMToolBar m_toolbar;
	CWizKMSplitterWindow m_splitter;
	//
	CMonthCalendarView m_leftview;
	CWizKMCalendarView m_view;
	CWizKMDatabaseEx m_db;

	//
	CString m_strCommandLine;
	BOOL OpenDatabase();

public:
	virtual void MCV_OnDateChanged(const COleDateTime& t);
	virtual void MCV_OnTagsChanged(const CWizStdStringArray& arrayTags);
	//
	virtual void WCV_OnTimeChanged(const COleDateTime& t);
	virtual void WCV_OnEventChanged(const WIZCALENDAREVENTDATA& e);
	virtual void WCV_OnViewChanged(WizCalendarViewType eView);

	virtual void LoadStatus();
public:
	CWizKMDatabase* GetDatabase() { return &m_db; }
	void UpdateLayout(BOOL bResizeBars = TRUE);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_CALENDAR_MONTH, UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_CALENDAR_WEEK, UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_CALENDAR_DAY, UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_CALENDAR_DELETEEVENT, UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_CALENDAR_EDITEVENT, UPDUI_TOOLBAR)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(m_nMessageCalendarEventModified, OnCalendarEventModified)
		MESSAGE_HANDLER(WIZ_UM_TOOLBAR_DROPDOWN_MENU, OnToolbarDropDownMenu)
		MESSAGE_HANDLER(WIZ_UM_CLOSE_WINDOW_FOR_AUTO_UPDATE, OnCloseWindowForAutoUpdate)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_CALENDAR_DAY, OnCalendarDay)
		COMMAND_ID_HANDLER(ID_CALENDAR_MONTH, OnCalendarMonth)
		COMMAND_ID_HANDLER(ID_CALENDAR_WEEK, OnCalendarWeek)
		COMMAND_ID_HANDLER(ID_CALENDAR_NEWEVENT, OnCalendarNewevent)
		COMMAND_ID_HANDLER(ID_CALENDAR_DELETEEVENT, OnCalendarDeleteevent)
		COMMAND_ID_HANDLER(ID_CALENDAR_EDITEVENT, OnCalendarEditevent)
		COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnHelpAbout)
		COMMAND_ID_HANDLER(ID_HELP_MANUAL, OnHelpManual)
		COMMAND_ID_HANDLER(ID_BACKGROUND_NONE, OnBackgroundNone)
		COMMAND_ID_HANDLER(ID_BACKGROUND_NOTE, OnBackgroundNote)
		COMMAND_ID_HANDLER(ID_BACKGROUND_TODOLIST, OnBackgroundTodolist)
		COMMAND_ID_HANDLER(ID_BACKGROUND_JOURNAL, OnBackgroundJournal)
		COMMAND_ID_HANDLER(ID_CALENDAR_OPTIONS, OnOptions)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CMainFrameWindowState)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnToolbarDropDownMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarDay(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarMonth(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarWeek(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarNewevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarDeleteevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarEditevent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBackgroundNone(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBackgroundNote(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBackgroundTodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBackgroundJournal(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
