// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Globals/WizKMCalendarEvents.h"

#include "../../WizGlobals/WizTrayIconImpl.h"

#include <set>

class CTodoDlg;
class CNoteDlg;
class CRemindEventDlg;

typedef std::vector<CNoteDlg*> CNodeDlgArray;
typedef std::vector<CRemindEventDlg*> CRemindEventDlgArray;
typedef std::set<CString> CReminderEventGUISSet;

#define UM_REMOVE_NOTE				(WM_USER + 3000)
#define UM_PROCESS_COMMANDLINE		(WM_USER + 3001)
#define UM_REFRESH_EVENTS			(WM_USER + 3002)
#define UM_REFRESH_TODO_LIST		(WM_USER + 3003)

const UINT UM_CALENDAREVENTMODIFIED = ::RegisterWindowMessage(WIZKM_CALENDAR_EVENT_MODIFIED_MESSAGE_NAME);

class CMainDlg 
	: public CAxDialogImpl<CMainDlg>
	, public CMessageFilter
	, public CIdleHandler
	, public CWizTrayIconImpl<CMainDlg>
	, public CDoubleBufferImpl<CMainDlg>
	, public IWizAtlDropTargetEx
	, public CWizKMSyncSimpleMessageBase<CMainDlg>
{
public:
	CMainDlg(LPCTSTR lpszCommandLine);
	~CMainDlg();
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();
	//
	virtual void OnTrayPrepareMenu(HMENU hMenu);
	virtual void OnTrayLButtonDblclk();
	//
	virtual STDMETHODIMP OnDragLeave() { return S_OK; }
	virtual STDMETHODIMP OnDragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	virtual STDMETHODIMP OnDrop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	//
	BOOL OpenDatabase();
private:
	CNodeDlgArray m_arrayNote;
	CRemindEventDlgArray m_arrayRemindEvent;
	//
	CWizEventArray m_arrayEvent;
	CReminderEventGUISSet m_setReminded;
	//
	CWizKMDatabaseEx m_db;
	//
	CString m_strCommandLine;
	//
	CWizKMDatabaseWindow m_databaseWindow;
	//
	CTodoDlg* m_pTodoDlg;
	//
	DWORD m_dwLastSyncTickCount;
	//
	CImageList m_ilToolBar;
	CImageList m_ilToolBarDisabled;
	CWizVistaToolBarCtrl m_wndToolBar;
	BOOL m_bTextLabel;
	BOOL m_bRButtonDown;
	HCURSOR m_cursorDefault;
	HCURSOR m_cursorMove;
	BOOL m_bCompact;
	COLORREF m_crNoteText;
	CFont m_fontNoteText;
	BOOL m_bSyncEnabled;
	UINT m_nSyncMinutes;
	//
	BOOL m_bSuspend;
	//
	HWND m_hwndForegroundWindow;
	HWND m_hwndLastIEWindow;
	//
	CWizHotKeyHelper m_hotkeys;
public:
	void RegisterAllHotkeys();
private:
	void ResetEvents();
	//
	void SaveNotesStatus();
	void LoadNotesStatus();
	//
	void DestroyAllNotes();
	void DestroyAllRemindEvent();
	//
	intptr_t IndexOfNote(LPCTSTR lpszDocumentGUID);
	intptr_t IndexOfNote(IWizDocument* pDocument);
	CNoteDlg* FindNote(LPCTSTR lpszDocumentGUID, BOOL bCreate, BOOL bUpdate);
	CNoteDlg* FindNote(IWizDocument* pDocument, BOOL bCreate, BOOL bUpdate);
	//
	void InitNotesMenu(CMenuHandle menuNotes);
	//
	void CheckReminder();
	void RemindEvent(IWizEvent* pEvent);
	//
	void AutoSync();
	void Sync();
	//
	void ResetToolBar();
	void UpdateLayout();
	//
	void LoadStatus();
	void SaveStatus();
	//
	CComPtr<IWizDocument> FindTaskDocument();
	CNoteDlg* FindTaskNote();
	BOOL InitTask();
	CString GetTodayTaskTitle();
	//
	BOOL IsCompact();
	void SetCompact(BOOL b);
	//
	void CreateTodoDlg();
	//
	void RememberForegroundWindow();
	//
	void ResetSyncTickCount();
	void OnPowerResume();
	void OnPowerSuspend();
private:
	static CMainDlg* m_spMainDlg;
public:
	static CMainDlg* GetMainDlg();
public:
	void DoPaint(CDCHandle dc);
	//
	void CloseDialog(int nVal);
	//
	CNoteDlg* NewNote(LPCTSTR lpszInitTitle = NULL);
	//
	void CloseAllNotes(CNoteDlg* pDlgExcept);
	void RemoveNote(CNoteDlg* pDlg);
	//
	void SaveHtml(LPCTSTR lpszHtml, LPCTSTR lpszURL, LPCTSTR lpszTitle);
	void SaveRtf(LPCSTR lpszRtf, LPCTSTR lpszTitle);
	void SaveText(LPCTSTR lpszText);
	void SaveBitmap(PCTSTR lpszBitmapFileName);
	//
	void OnSyncEnd(int nExitCode, UINT nFlags);
	//
	static BOOL WriteCommandLineToReg(LPCTSTR lpszCommandLine);
	static BOOL ReadCommandLineToReg(CString& strCommandLine, BOOL bClear);
	//
	void ProcessCommandLine(LPCTSTR lpszCommandLine, BOOL bPrompt = FALSE);
	//
	void UpdateAllNotesFont();
	//
	void SetNoteFont(const LOGFONT& lf, COLORREF crText);
	HFONT GetNoteFont();
	COLORREF GetNoteTextColor() const { return m_crNoteText; }
	//
protected:
	void RefreshEvents();
	void RefreshTodoList();
	//
	void LoadSettings();
	void InitCursor();
private:
	BOOL CreateNoteFont(CFont& font);
public:

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		MESSAGE_HANDLER(UM_REFRESH_EVENTS, OnRefreshEvents)
		MESSAGE_HANDLER(UM_REMOVE_NOTE, OnRemoveNote);
		MESSAGE_HANDLER(UM_PROCESS_COMMANDLINE, OnProcessCommandLine)
		MESSAGE_HANDLER(UM_CALENDAREVENTMODIFIED, OnCalendarEventModified)
		MESSAGE_HANDLER(UM_REFRESH_TODO_LIST, OnRefreshTodoList)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnWindowPosChanging)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WIZKM_UM_IS_HOTKEY_REGISTERED, OnIsHotKeyRegistered)
		MESSAGE_HANDLER(WIZ_UM_CLOSE_WINDOW_FOR_AUTO_UPDATE, OnCloseWindowForAutoUpdate)
		MESSAGE_HANDLER(WM_POWERBROADCAST, OnPowerBroadcast)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(ID_TRAY_EXIT, OnTrayExit)
		COMMAND_ID_HANDLER(ID_TRAY_NEWNOTE, OnTrayNewnote)
		COMMAND_ID_HANDLER(ID_NOTES_LOADRECENTNOTES, OnNotesLoadrecentnotes)
		COMMAND_ID_HANDLER(ID_TRAY_BRINGALLNOTESTOFRONT, OnTrayBringallnotestofront)
		COMMAND_ID_HANDLER(ID_TRAY_CLOSEALLNOTES, OnTrayCloseallnotes)
		COMMAND_ID_HANDLER(ID_HELP_MANUAL, OnHelpManual)
		COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnHelpAbout)
		COMMAND_ID_HANDLER(ID_TRAY_OPTIONS, OnTrayOptions)
		COMMAND_ID_HANDLER(ID_TRAY_TODOLIST, OnTrayTodolist)
		COMMAND_ID_HANDLER(ID_NOTES_SHOWALLNOTES, OnNotesShowallnotes)
		COMMAND_ID_HANDLER(ID_TRAY_WIZEXPLORER, OnTrayWizExplorer)
		COMMAND_ID_HANDLER(ID_TRAY_WIZCALENDAR, OnTrayWizCalendar)
		COMMAND_ID_HANDLER(ID_TRAY_SYNC, OnTraySync)
		COMMAND_ID_HANDLER(ID_TRAY_CLIPSCREENSHOT, OnTrayClipscreenshot)
		COMMAND_ID_HANDLER(ID_TRAY_COPYSELECTION, OnTrayCopyselection)
		COMMAND_ID_HANDLER(ID_TRAY_PASTETOWIZ, OnTrayPastetowiz)
		COMMAND_ID_HANDLER(ID_TRAY_COMPACTMODE, OnTrayCompactmode)
		COMMAND_ID_HANDLER(ID_TRAY_MINIMIZE, OnTrayMinimize)
		COMMAND_RANGE_HANDLER(ID_NOTES_BEGIN, ID_NOTES_END, OnShowNotes)
		NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnTbnDropDownNote)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CWizKMSyncSimpleMessageBase)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMainDlg>)
		CHAIN_MSG_MAP( CWizTrayIconImpl<CMainDlg>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTrayTextlabel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayMinimize(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTbnDropDownNote(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnRemoveNote(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPowerBroadcast(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnProcessCommandLine(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnHotKey(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnIsHotKeyRegistered(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayNewnote(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnShowNotes(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNotesLoadrecentnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayBringallnotestofront(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayCloseallnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayTodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNotesShowallnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayWizExplorer(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayWizCalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnRefreshEvents(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRefreshTodoList(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTraySync(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayClipscreenshot(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayCopyselection(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayPastetowiz(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayCompactmode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


inline CMainDlg* WizGetMainDlg()
{
	return CMainDlg::GetMainDlg();
}
