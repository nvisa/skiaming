// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

#include "NoteDlg.h"
#include "TodoDlg.h"

#include "RemindEventDlg.h"

#include "ConfigHotkeyDlg.h"
#include "ConfigGeneralDlg.h"
#include "ConfigToolbarDlg.h"

#include "NoteSettings.h"

#include "../Globals/WizKMCommonUI.h"

#include "../WizWebCapture/WizWebCapture_i.h"
#include "../WizKMControls/WizKMControls_i.h"

#include "../../WizGlobals/WizPropertySheetEx.h"


#include <algorithm>


#define ID_TIMER_EVENT_REMINDER		101
#define	ID_TIMER_REMEMBER_FOREGROUND_WINDOW		102
#define ID_TIMER_CHECK_WINDOW_POS	103

#define WIDTH_LEFT_BAR		16

CMainDlg* CMainDlg::m_spMainDlg = NULL;

CMainDlg::CMainDlg(LPCTSTR lpszCommandLine)
	: m_strCommandLine(lpszCommandLine)
	, m_hwndForegroundWindow(NULL)
	, m_hwndLastIEWindow(NULL)
	, m_pTodoDlg(NULL)
	, m_cursorDefault(NULL)
	, m_cursorMove(NULL)
	, m_bRButtonDown(FALSE)
	, m_bTextLabel(FALSE)
	, m_bCompact(FALSE)
	, m_dwLastSyncTickCount(0)
	, m_bSyncEnabled(TRUE)
	, m_nSyncMinutes(15)
{
	m_bSuspend = FALSE;
	//
	m_spMainDlg = this;
	m_crNoteText = ::GetSysColor(COLOR_WINDOWTEXT);
	//
	LoadSettings();
}
//
CMainDlg::~CMainDlg()
{
	m_db.Close();
}

BOOL CMainDlg::OpenDatabase()
{
	if (!m_db.DefaultOpen(WizGetCommandLineValue(m_strCommandLine, _T("DatabasePath"))))
	{
		return FALSE;
	}
	//
	return TRUE;
}

void CMainDlg::LoadSettings()
{
	m_bSyncEnabled = GetSyncEnabled();
	m_nSyncMinutes = GetSyncMinutes();
}
CMainDlg* CMainDlg::GetMainDlg()
{
	ATLASSERT(m_spMainDlg);
	return m_spMainDlg;
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	AutoSync();
	//
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	WizTranslationsTranslateWindow(m_hWnd);
	//
	m_databaseWindow.Register(m_db.GetDatabasePath(), m_hWnd, WIZKM_DATABASE_WINDOW_NOTE);
	//
	SetWindowText(_T("WizNote"));
	//
	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);
	//
	LoadStatus();
	//
	ResetToolBar();
	//
	InstallIcon(WizFormatString0(IDS_WIZNOTE), hIconSmall, IDR_MENU_TRAY);
	//
	LoadNotesStatus();
	//
	InitTask();
	//
	ResetEvents();
	//
	SetTimer(ID_TIMER_EVENT_REMINDER, 1000 * 10);	///*每隔10秒检查一次*/
	SetTimer(ID_TIMER_REMEMBER_FOREGROUND_WINDOW, 300);
	SetTimer(ID_TIMER_CHECK_WINDOW_POS, 1000 * 3);	///*每隔3秒检查一次窗口*/
	//
	m_dwLastSyncTickCount = GetTickCount() - int((m_nSyncMinutes - 0.5) * 1000 * 60);
	//
	RegisterAllHotkeys();
	//
	std::set<UINT> setFormats;
	setFormats.insert(CF_HTML_FORMAT());
	setFormats.insert(CF_RTF_FORMAT());
	setFormats.insert(CF_TEXT);
	setFormats.insert(CF_UNICODETEXT);
	setFormats.insert(CF_HDROP);
	setFormats.insert(CF_BITMAP);
	CWizAtlDropTargetEx::RegisterDragDrop(this, setFormats, m_hWnd);
	//
	ProcessCommandLine(m_strCommandLine);
	//
	WizKMSetNoteWindowHandle(m_hWnd);
	//
	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	WizKMSetNoteWindowHandle(NULL);
	//
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	//
	RemoveIcon();
	//
	SaveNotesStatus();
	//
	DestroyAllNotes();
	//
	return 0;
}

LRESULT CMainDlg::OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	WizKMSetNoteWindowHandle(NULL);
	//
	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(1));
	SaveNotesStatus();
	//
	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(2));
	//DestroyAllNotes();

	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(3));
	//DestroyAllRemindEvent();
	//
	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(4));
	SaveStatus();
	//
	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(5));
	RemoveIcon();
	//
	//DEBUG_TOLOG1(_T("CMainDlg::OnQueryEndSession: %1"), WizIntToStr(6));
	return TRUE;
}

void CMainDlg::DestroyAllNotes()
{
	try
	{
		for (CNodeDlgArray::const_iterator it = m_arrayNote.begin();
			it != m_arrayNote.end();
			it++)
		{
			CNoteDlg* pDlg = *it;
			if (pDlg && pDlg->IsWindow())
			{
				pDlg->DestroyWindow();
				delete pDlg;
			}
		}
		//
		m_arrayNote.clear();
		//
		if (m_pTodoDlg && m_pTodoDlg->IsWindow())
		{
			m_pTodoDlg->DestroyWindow();
			delete m_pTodoDlg;
			m_pTodoDlg = NULL;
		}
	}
	catch (...)
	{
	}
}
void CMainDlg::DestroyAllRemindEvent()
{
	for (CRemindEventDlgArray::const_iterator it = m_arrayRemindEvent.begin();
		it != m_arrayRemindEvent.end();
		it++)
	{
		CRemindEventDlg* pDlg = *it;
		if (pDlg->IsWindow())
		{
			pDlg->DestroyWindow();
		}
		//
		delete pDlg;
	}
	//
	m_arrayRemindEvent.clear();
}


intptr_t CMainDlg::IndexOfNote(LPCTSTR lpszDocumentGUID)
{
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		CComPtr<IWizDocument> spDocument = pDlg->GetDocument();
		if (spDocument)
		{
			if (0 == CWizKMDatabase::GetObjectGUID(spDocument.p).CompareNoCase(lpszDocumentGUID))
				return i;
		}
	}
	//
	return -1;
}

intptr_t CMainDlg::IndexOfNote(IWizDocument* pDocument)
{
	return IndexOfNote(CWizKMDatabase::GetObjectGUID(pDocument));
}

CNoteDlg* CMainDlg::FindNote(LPCTSTR lpszDocumentGUID, BOOL bCreate, BOOL bUpdate)
{
	CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(lpszDocumentGUID);
	if (!spDocument)
		return NULL;
	//
	return FindNote(spDocument, bCreate, bUpdate);
}

CNoteDlg* CMainDlg::FindNote(IWizDocument* pDocument, BOOL bCreate, BOOL bUpdate)
{
	CString strGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	//
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		CComPtr<IWizDocument> spDocument = pDlg->GetDocument();
		if (spDocument)
		{
			if (0 == CWizKMDatabase::GetObjectGUID(spDocument.p).CompareNoCase(strGUID))
			{
				if (bUpdate
					&& !pDlg->IsModified()
					&& CWizKMDatabase::GetDocumentDataDateModified(pDocument) > CWizKMDatabase::GetDocumentDataDateModified(spDocument))
				{
					pDlg->Load();
				}
				//
				return pDlg;
			}
		}
	}
	//
	if (!bCreate)
		return NULL;
	//
	CNoteDlg* pDlg = new CNoteDlg(&m_db, NULL);
	pDlg->Create(NULL);
	//
	if (pDlg->SetDocument(pDocument))
	{
		m_arrayNote.push_back(pDlg);
		return pDlg;
	}
	else
	{
		pDlg->DestroyWindow();
		delete pDlg;
		//
		return NULL;
	}
}



LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	//CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	SaveStatus();
	//
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CloseDialog(IDOK);

	return 0;
}

CNoteDlg* CMainDlg::NewNote(LPCTSTR lpszInitTitle /*= NULL*/)
{
	CNoteDlg* pDlg = new CNoteDlg(&m_db, lpszInitTitle);
	//
	//HWND hwndProgMan = ::FindWindow(_T("ProgMan"), NULL);
	//
	//pDlg->Create(hwndProgMan);

	pDlg->Create(NULL);
	//pDlg->SetParent(hwndProgMan);
	//
	pDlg->BringWindowToTopEx();
	//
	m_arrayNote.push_back(pDlg);
	//
	return pDlg;
}

LRESULT CMainDlg::OnTrayNewnote(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	SetForegroundWindow(m_hWnd);
	NewNote();
	//
	return 0;
}


void CMainDlg::SaveNotesStatus()
{
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		if ((pDlg->GetWindowLong(GWL_STYLE) & WS_VISIBLE) == WS_VISIBLE)
		{
			pDlg->AutoSave();
			pDlg->SavePos();
		}
	}
	//
	if (m_pTodoDlg)
	{
		m_pTodoDlg->SaveStatus();
	}
}


void CMainDlg::LoadNotesStatus()
{
	SendMessage(WM_COMMAND, MAKEWPARAM(ID_NOTES_LOADRECENTNOTES, 0), 0);
}



void CMainDlg::OnTrayPrepareMenu(HMENU hMenu)
{
	CMenuHandle menu(hMenu);
	//
	CMenuHandle menuNotes = menu.GetSubMenu(2);
	if (menuNotes.IsMenu())
	{
		InitNotesMenu(menuNotes);
	}
	//
	BOOL bVisible = (GetStyle() & WS_VISIBLE) ? TRUE : FALSE;
	CString strMenuText = WizFormatString0(bVisible ? IDS_MINIMIZE : IDS_RESTORE);
	TCHAR szMenuText[MAX_PATH] = { 0 };
	_tcscpy_s(szMenuText, MAX_PATH, strMenuText);
	//
	MENUITEMINFO info;
	ZeroMemory(&info, sizeof(MENUITEMINFO));
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STRING;
	info.dwTypeData = szMenuText;
	menu.SetMenuItemInfo(ID_TRAY_MINIMIZE, FALSE, &info);
	//
	menu.ModifyMenu(ID_TRAY_COMPACTMODE, MF_BYCOMMAND, (UINT_PTR)ID_TRAY_COMPACTMODE, (LPCTSTR)WizFormatString0(IsCompact() ? IDS_NORMAL_MODE : IDS_COMPACT_MODE));
	//
	BOOL bWizExplorerExists = WizKMExplorerExists();
	//
	if (!bWizExplorerExists)
	{
		for (int i = 18; i >= 12; i--)
		{
			menu.DeleteMenu(i, MF_BYPOSITION);
		}
	}
	//
	m_hotkeys.UpdateHotKeyToMenu(menu);
}


void CMainDlg::OnTrayLButtonDblclk()
{
	CString strActionName = GetDoubleClickAction();
	//
	if (0 == strActionName.CompareNoCase(_T("ShowOpenedNotes")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_BRINGALLNOTESTOFRONT, 0), 0);
	}
	else if (0 == strActionName.CompareNoCase(_T("ShowRecentNotes")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_NOTES_SHOWALLNOTES, 0), 0);
	}
	else if (0 == strActionName.CompareNoCase(_T("ShowTasks")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_TODOLIST, 0), 0);
	}
	else if (0 == strActionName.CompareNoCase(_T("Explorer")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_WIZEXPLORER, 0), 0);
	}
	else if (0 == strActionName.CompareNoCase(_T("Calendar")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_WIZCALENDAR, 0), 0);
	}
	else
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_NEWNOTE, 0), 0);
	}
}


bool CompareNoteDlg(CNoteDlg* pDlg1, CNoteDlg* pDlg2)
{
	bool bVisible1 = (pDlg1->GetStyle() & WS_VISIBLE) ? true : false;
	bool bVisible2 = (pDlg2->GetStyle() & WS_VISIBLE) ? true : false;
	//
	if (bVisible1 == bVisible2)
	{
		return pDlg1->GetDateModified() > pDlg2->GetDateModified();
	}
	else
	{
		if (bVisible1 && !bVisible2)
			return true;
		else
			return false;
	}
}
void CMainDlg::InitNotesMenu(CMenuHandle menuNotes)
{
	while (menuNotes.GetMenuItemCount() > 3)
	{
		menuNotes.DeleteMenu(0, MF_BYPOSITION);
	}
	//
	std::sort(m_arrayNote.begin(), m_arrayNote.end(), CompareNoteDlg);
	//
	UINT nID = ID_NOTES_BEGIN;
	UINT nMax = ID_NOTES_END - ID_NOTES_BEGIN;
	//
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount && i < nMax; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		//
		CString strTitle = pDlg->GetTitle();
		//
		if (pDlg->GetStyle() & WS_VISIBLE)
		{
			strTitle = CString(_T("* ")) + strTitle;
		}
		//
		menuNotes.InsertMenu((UINT)i, MF_STRING | MF_BYPOSITION, (UINT)(nID + i), strTitle);
	}
}
LRESULT CMainDlg::OnShowNotes(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nIndex = wID - ID_NOTES_BEGIN;
	if (nIndex < 0 || nIndex >= int(m_arrayNote.size()))
		return 0;
	//
	CNoteDlg* pDlg = m_arrayNote[nIndex];
	pDlg->BringWindowToTopEx();
	//
	return 0;
}

LRESULT CMainDlg::OnNotesLoadrecentnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	//
	CWizDocumentArray arrayDocument;
	if (!m_db.GetRecentDocuments(0x01, _T("note"), 20, arrayDocument))
	{
		TOLOG(_T("Failed to get recent notes!"));
		return FALSE;
	}
	//
	//SetForegroundWindow(m_hWnd);
	//
	for (CWizDocumentArray::const_iterator it = arrayDocument.begin();
		it != arrayDocument.end();
		it++)
	{
		CComPtr<IWizDocument> spDocument = *it;
		//
		FindNote(spDocument, TRUE, TRUE);
	}
	//
	return 0;
}

LRESULT CMainDlg::OnTrayBringallnotestofront(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	SetForegroundWindow(m_hWnd);
	//
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		//
		if (pDlg->GetStyle() & WS_VISIBLE)
		{
			pDlg->BringWindowToTopEx();
		}
	}

	return 0;
}

LRESULT CMainDlg::OnTrayCloseallnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CloseAllNotes(NULL);

	return 0;
}
void CMainDlg::CloseAllNotes(CNoteDlg* pDlgExcept)
{
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		if (pDlg != pDlgExcept)
		{
			pDlg->Close();
		}
	}
}
LRESULT CMainDlg::OnRemoveNote(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CNoteDlg* pDlg = (CNoteDlg *)lParam;
	if (pDlg)
	{
		RemoveNote(pDlg);
	}
	//
	return 0;
}

void CMainDlg::RemoveNote(CNoteDlg* pDlg)
{
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* p = m_arrayNote[i];
		if (pDlg == p)
		{
			m_arrayNote.erase(m_arrayNote.begin() + i);
			//
			p->DestroyWindow();
			delete p;
			//
			return;
		}
	}
}
LRESULT CMainDlg::OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	ResetEvents();
	//
	return 0;
}
void CMainDlg::RefreshEvents()
{
	ResetEvents();
}

void CMainDlg::RefreshTodoList()
{
	if (m_pTodoDlg)
	{
		m_pTodoDlg->Refresh();
	}
}

LRESULT CMainDlg::OnRefreshEvents(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RefreshEvents();
	return 0;
}
LRESULT CMainDlg::OnRefreshTodoList(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RefreshTodoList();
	return 0;
}

void CMainDlg::RegisterAllHotkeys()
{
	if (m_hotkeys.IsRegistered())
	{
		m_hotkeys.UnregisterAll();
	}
	//
	CWizHotKeyDataArray arrayHotKey;
	//
	CWizKMSettings settings;
	//
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY_NOTE, HOTKEY_NAME_NEWNOTE, HOTKEY_DEFAULT_NEWNOTE), ID_TRAY_NEWNOTE));
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY_NOTE, HOTKEY_NAME_DISPLAY_NOTES, HOTKEY_DEFAULT_DISPLAY_NOTE), ID_TRAY_BRINGALLNOTESTOFRONT));
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY, HOTKEY_NAME_CLIPSCREEN, HOTKEY_DEFAULT_CLIPSCREEN), ID_TRAY_CLIPSCREENSHOT));
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY, HOTKEY_NAME_COPYCLIPBOARD, HOTKEY_DEFAULT_COPYSELECTION), ID_TRAY_COPYSELECTION));
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY, HOTKEY_NAME_PASTECLIPBOARD, HOTKEY_DEFAULT_PASTECLIPBOARD), ID_TRAY_PASTETOWIZ));
	//
	CString strError;
	if (!m_hotkeys.RegisterAll(m_hWnd, arrayHotKey, strError))
	{
		if (!WizKMIsExplorerHotKeyRegistered())
		{
			CString strMsg = WizFormatString1(IDS_REGISTER_HOTKEY_FAILED, strError);
			//
			WizKMShowBubbleWindow2Background(WizGetProductName(), strMsg, strMsg, WIZCOLOR_PINK, 10, WIZBUBBLE_SHOWLINKURLASMESSAGE);
		}
	}
}

void CMainDlg::ResetEvents()
{
	m_arrayEvent.clear();
	//
	COleDateTime t = COleDateTime::GetCurrentTime();
	COleDateTime tBegin = t - COleDateTimeSpan(1, 0, 0, 0);		//获得一天前的事件
	COleDateTime tEnd = t + COleDateTimeSpan(3 * 7, 0, 0, 0);		//提前获得三周事件
	//
	m_db.GetCalendarEvents(tBegin, tEnd, m_arrayEvent);
	//
	size_t nEventCount = m_arrayEvent.size();
	for (intptr_t i = nEventCount - 1; i >= 0; i--)
	{
		CComPtr<IWizEvent> spEvent = m_arrayEvent[i];
		//
		long nReminder = -1;
		spEvent->get_Reminder(&nReminder);
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (-1 == nReminder
			|| vbCompleted)
		{
			m_arrayEvent.erase(m_arrayEvent.begin() + i);
		}
	}
	//
	int nReminderCount = (int)m_arrayRemindEvent.size();
	for (intptr_t i = nReminderCount - 1; i>= 0; i--)
	{
		CRemindEventDlg* pDlg = m_arrayRemindEvent[i];
		if (!pDlg)
			continue;
		//
		if (!pDlg->IsWindow())
		{
			m_arrayRemindEvent.erase(m_arrayRemindEvent.begin() + i);
			continue;
		}
		//
		//
		CComPtr<IWizEvent> spEvent = pDlg->GetEvent();
		if (!spEvent)
			continue;
		//
		spEvent->Reload();
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (!vbCompleted)
			continue;
		//
		m_arrayRemindEvent.erase(m_arrayRemindEvent.begin() + i);
		//
		pDlg->ShowWindow(SW_HIDE);
		pDlg->DestroyWindow();
		delete pDlg;
	}
}


void CMainDlg::RememberForegroundWindow()
{
	POINT pt = {0, 0};
	GetCursorPos(&pt);
	HWND hwndCurrentPos = ::WindowFromPoint(pt);
	if (hwndCurrentPos != m_hwndLastIEWindow)
	{
		if (WizIsIEWindow(hwndCurrentPos))
		{
			m_hwndLastIEWindow = hwndCurrentPos;
		}
	}
	//
	HWND hwndForegroundWindow = ::GetForegroundWindow();
	if (!hwndForegroundWindow)
		return;
	if (hwndForegroundWindow == m_hwndForegroundWindow)
		return;
	if (hwndForegroundWindow == m_hWnd)
		return;
	if (hwndForegroundWindow == m_hMainWnd)
		return;
	//
	TCHAR szClassName[1024] = {0};
	GetClassName(hwndForegroundWindow, szClassName, 1024);
	//
	if (0 == _tcsicmp(_T("Shell_TrayWnd"), szClassName))
		return;
	if (0 == _tcsicmp(_T("NotifyIconOverflowWindow"), szClassName))
		return;

	m_hwndForegroundWindow = hwndForegroundWindow;
}


LRESULT CMainDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	UINT nID = (UINT)wParam;
	//
	bHandled = FALSE;
	//
	if (ID_TIMER_EVENT_REMINDER == nID)
	{
		bHandled = TRUE;
		//
		CheckReminder();
	}
	if (ID_TIMER_REMEMBER_FOREGROUND_WINDOW == nID)
	{
		bHandled = TRUE;
		//
		RememberForegroundWindow();
	}
	else if (ID_TIMER_CHECK_WINDOW_POS == nID)
	{
		bHandled = TRUE;
		//
		WizCheckWindowTopMost(m_hWnd);
	}
	//
	return 0;
}

void CMainDlg::CheckReminder()
{
	static COleDateTime tOld = ::WizGetCurrentTime();
	COleDateTime tNow = ::WizGetCurrentTime();
	if (tOld.GetDay() != tNow.GetDay())
	{
		ResetEvents();
		if (m_pTodoDlg)
		{
			m_pTodoDlg->LoadCurrentTodoList();
		}
		tOld = tNow;
	}
	//
	for (CWizEventArray::const_iterator it = m_arrayEvent.begin();
		it != m_arrayEvent.end();
		it++)
	{
		CComPtr<IWizEvent> spEvent = *it;
		//
		long nReminder = -1;
		spEvent->get_Reminder(&nReminder);
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (nReminder == -1
			|| vbCompleted)
			continue;
		//
		CComBSTR bstrGUID;
		spEvent->get_GUID(&bstrGUID);
		//
		if (m_setReminded.find(CString(bstrGUID)) != m_setReminded.end())
			continue;
		//
		DATE dtStart = 0;
		spEvent->get_Start(&dtStart);
		//
		COleDateTime tStart = dtStart;
		COleDateTime tBeginReminder = tStart - COleDateTimeSpan(0, 0, 0, nReminder);
		//
		if (COleDateTime::GetCurrentTime() > tBeginReminder)
		{
			RemindEvent(spEvent);
		}
	}
}

void CMainDlg::Sync()
{
	m_dwLastSyncTickCount = GetTickCount();
	WizKMShellSync(m_db.GetDatabasePath(), TRUE);
}
void CMainDlg::AutoSync()
{
	if (!m_bSyncEnabled)
		return;
	if (m_bSuspend)
		return;
	//
	//第一次不检查是否有改变。
	//
	DWORD dwTickCount = GetTickCount();
	if (dwTickCount - m_dwLastSyncTickCount > m_nSyncMinutes * 60 * 1000)
	{
		Sync();
	}
}

void CMainDlg::RemindEvent(IWizEvent* pEvent)
{
	if (!pEvent)
		return;
	//
	CComBSTR bstrGUID;
	pEvent->get_GUID(&bstrGUID);
	//
	CString strGUID(bstrGUID);
	m_setReminded.insert(strGUID);
	//
	CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strGUID);
	if (!spDocument)
		return;
	//
	//
	CRemindEventDlg* pDlg = new CRemindEventDlg(pEvent);
	//
	pDlg->Create(NULL);
	//
	m_arrayRemindEvent.push_back(pDlg);
	//
	pDlg->ShowWindow(SW_SHOW);
}


LRESULT CMainDlg::OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMWebSiteVisitHelp(_T("wiznote"));

	return 0;
}

LRESULT CMainDlg::OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMAbout();

	return 0;
}


BOOL CMainDlg::IsCompact()
{
	if (m_wndToolBar.IsWindow())
	{
		return m_wndToolBar.GetButtonCount() == 1;
	}
	//
	return m_bCompact;
}
void CMainDlg::SetCompact(BOOL b)
{
	m_bCompact = b;
	if (m_wndToolBar.IsWindow())
	{
		ResetToolBar();
	}
}

void CMainDlg::ResetToolBar()
{
	if (m_ilToolBar.IsNull())
	{
		m_ilToolBar.Create(16, 16, ILC_COLOR32 | ILC_MASK, 2, 4);
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("newnote.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("todo.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("save.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("capture.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("paste.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("sync.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("calendar.ico")));
		m_ilToolBar.AddIcon(WizKMLoadSkinsIcon(_T("explorer.ico")));
	}
	if (m_ilToolBarDisabled.IsNull())
	{
		m_ilToolBarDisabled.Create(16, 16, ILC_COLOR32 | ILC_MASK, 2, 4);
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("newnote_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("todo_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("save_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("capture_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("paste_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("sync_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("calendar_g.ico")));
		m_ilToolBarDisabled.AddIcon(WizKMLoadSkinsIcon(_T("explorer_g.ico")));
	}
	//
	if (!m_wndToolBar.IsWindow())
	{
		m_wndToolBar.Create(m_hWnd, CRect(0, 0, 200, 24), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NORESIZE | CCS_NODIVIDER | CCS_TOP | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS, 0);
		ATLASSERT(m_wndToolBar.IsWindow());
		//
		m_wndToolBar.SetImageList(m_ilToolBar);
		m_wndToolBar.SetDisabledImageList(m_ilToolBarDisabled);
		m_wndToolBar.SetButtonStructSize();
		m_wndToolBar.SetExtendedStyle(m_wndToolBar.GetExtendedStyle() | TBSTYLE_EX_MIXEDBUTTONS | TBSTYLE_EX_DRAWDDARROWS);
	}
	//
	while (m_wndToolBar.GetButtonCount() > 0)
	{
		m_wndToolBar.DeleteButton(0);
	}
	//
	BOOL bWizExplorerExists = WizKMExplorerExists();
	//
	if (m_bCompact)
	{
		CString strButtonName = GetCompactButton();
		if (0 == strButtonName.CompareNoCase(_T("TodoList")))
		{
			m_wndToolBar.AddToolButton(ID_TRAY_TODOLIST, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 1);
		}
		else if (0 == strButtonName.CompareNoCase(_T("CopySelection")) && bWizExplorerExists)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_COPYSELECTION, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 2);
		}
		else if (0 == strButtonName.CompareNoCase(_T("ClipScreenshot")) && bWizExplorerExists)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_COPYSELECTION, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 3);
		}
		else if (0 == strButtonName.CompareNoCase(_T("PasteToWiz")) && bWizExplorerExists)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_COPYSELECTION, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 4);
		}
		else if (0 == strButtonName.CompareNoCase(_T("Sync")))
		{
			m_wndToolBar.AddToolButton(ID_TRAY_SYNC, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 5);
		}
		else if (0 == strButtonName.CompareNoCase(_T("Calendar")) && bWizExplorerExists)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_WIZCALENDAR, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 6);
		}
		else if (0 == strButtonName.CompareNoCase(_T("Explorer")) && bWizExplorerExists)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_WIZEXPLORER, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 7);
		}
		else
		{
			m_wndToolBar.AddToolButton(ID_TRAY_NEWNOTE, BTNS_BUTTON | BTNS_DROPDOWN, m_bTextLabel, 0);
		}
	}
	else
	{
		CWizKMSettings settings;
		
		BOOL bNewNote = GetToolbarButtonVisible(settings, _T("NewNote"));
		BOOL bNewTodoList = GetToolbarButtonVisible(settings, _T("NewTodoList"));
		BOOL bCopySelection = GetToolbarButtonVisible(settings, _T("CopySelection"));
		BOOL bClipScreen = GetToolbarButtonVisible(settings, _T("ClipScreen"));
		BOOL bPasteToWiz = GetToolbarButtonVisible(settings, _T("PasteToWiz"));
		BOOL bSync = GetToolbarButtonVisible(settings, _T("Sync"));
		BOOL bWizCalendar = GetToolbarButtonVisible(settings, _T("WizCalendar"));
		BOOL bWizExplorer = GetToolbarButtonVisible(settings, _T("WizExplorer"));

		if (bNewNote)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_NEWNOTE, 0, m_bTextLabel, 0);
		}
		if (bNewTodoList)
		{
			m_wndToolBar.AddToolButton(ID_TRAY_TODOLIST, 0, m_bTextLabel, 1);
		}
		//m_wndToolBar.AddToolButtonSep();
		if (bWizExplorerExists)
		{
			if (bCopySelection)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_COPYSELECTION, 0, m_bTextLabel, 2);
			}
			if (bClipScreen)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_CLIPSCREENSHOT, 0, m_bTextLabel, 3);
			}
			if (bPasteToWiz)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_PASTETOWIZ, 0, m_bTextLabel, 4);
			}
			//m_wndToolBar.AddToolButtonSep();
			if (bSync)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_SYNC, 0, m_bTextLabel, 5);
			}
			//m_wndToolBar.AddToolButtonSep();
			if (bWizCalendar)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_WIZCALENDAR, 0, m_bTextLabel, 6);
			}
			if (bWizExplorer)
			{
				m_wndToolBar.AddToolButton(ID_TRAY_WIZEXPLORER, BTNS_BUTTON, m_bTextLabel, 7);
			}
		}
		else
		{
			m_wndToolBar.AddToolButton(ID_TRAY_SYNC, BTNS_BUTTON, m_bTextLabel, 5);
		}
		//
		if (0 == m_wndToolBar.GetButtonCount())
		{
			m_wndToolBar.AddToolButton(ID_TRAY_NEWNOTE, 0, m_bTextLabel, 0);
		}
		//
		int nButtonCount = m_wndToolBar.GetButtonCount();
		TBBUTTON button;
		m_wndToolBar.GetButton(nButtonCount - 1, &button);
		m_wndToolBar.SetButtonInfo(button.idCommand, TBIF_STYLE, BTNS_BUTTON | BTNS_DROPDOWN, 0, NULL, 0, 0, 0, NULL);
	}
	//
	m_wndToolBar.SetButtonSize(22, 22);
	//
	SetWindowPos(NULL, 0, 0, m_wndToolBar.GetMinWidth() + WIDTH_LEFT_BAR, m_wndToolBar.GetMinHeight(),  SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	//
	UpdateLayout();
}

void CMainDlg::UpdateLayout()
{
	if (!m_wndToolBar.IsWindow())
		return;
	//
	m_wndToolBar.MoveWindow(WIDTH_LEFT_BAR, 0, m_wndToolBar.GetMinWidth(), m_wndToolBar.GetMinHeight() + 1);
}

LRESULT CMainDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	UpdateLayout();
	//
	return 0;
}
void CMainDlg::DoPaint(CDCHandle dc)
{
	CRect rc;
	GetClientRect(&rc);
	rc.bottom += 1;
	m_wndToolBar.DrawBackground(dc, rc);
	rc.bottom -= 1;
	//
	for (int x = 3; x < 2 * 3 + 3; x += 3)
	{
		for (int y = 3; y < rc.Height() - 3; y += 3)
		{
			dc.SetPixel(x, y, RGB(249, 249, 249));
			dc.SetPixel(x + 1, y, RGB(151, 151, 151));
			dc.SetPixel(x, y + 1, RGB(145, 145, 145));
			dc.SetPixel(x + 1, y + 1, RGB(98, 98, 98));
		}
	}
}


LRESULT CMainDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	//
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(xPos, yPos));

	return 0;
}
LRESULT CMainDlg::OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	static RECT rc = {0, 0, 0, 0};
	if (rc.left == 0
		&& rc.right == 0
		&& rc.top == 0
		&& rc.bottom == 0)
	{
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	}
	//
	WINDOWPOS* lpwndpos = (WINDOWPOS *)lParam;
	//
	if (lpwndpos->x < rc.left)
	{
		lpwndpos->x = rc.left;
	}
	if (lpwndpos->y < rc.top)
	{
		lpwndpos->y = rc.top;
	}
	if (lpwndpos->x + lpwndpos->cx > rc.right)
	{
		lpwndpos->x = rc.right - lpwndpos->cx;
	}
	if (lpwndpos->y + lpwndpos->cy > rc.bottom)
	{
		lpwndpos->y = rc.bottom - lpwndpos->cy;
	}

	return 0;
}

void CMainDlg::InitCursor()
{
	if (!m_cursorDefault)
	{
		m_cursorDefault = ::LoadCursor(NULL, IDC_ARROW);
	}
	if (!m_cursorMove)
	{
		m_cursorMove = ::LoadCursor(NULL, IDC_SIZEALL);
	}
}

LRESULT CMainDlg::OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	//
	InitCursor();
	//
	if (pt.x < WIDTH_LEFT_BAR && !m_bRButtonDown)
	{
		SetCursor(m_cursorMove);
		return TRUE;
	}
	else
	{
		SetCursor(m_cursorDefault);
		return TRUE;
	}

	return 0;
}


void CMainDlg::LoadStatus()
{
	CWizKMSettings settings;
	int x = settings.GetInt(SECTION_NOTE, _T("Main_xPos"), -1);
	int y = settings.GetInt(SECTION_NOTE, _T("Main_yPos"), -1);
	m_bTextLabel = settings.GetBool(SECTION_NOTE, _T("Main_TextLabel"), m_bTextLabel);
	m_bCompact = settings.GetBool(SECTION_NOTE, _T("Main_Compact"), FALSE);
	//
	if (x > GetSystemMetrics(SM_CXSCREEN) - 20)
	{
		x = ::GetSystemMetrics(SM_CXSCREEN) - 400;
	}
	if (x < 0)
	{
		x = ::GetSystemMetrics(SM_CXSCREEN) - 400;
	}
	//
	if (y > GetSystemMetrics(SM_CYSCREEN) - 26)
	{
		y = 0;
	}
	if (y < 0)
	{
		y = 0;
	}
	//
	SetWindowPos(NULL, x, y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	//
	//
	BOOL bVisible = settings.GetBool(SECTION_NOTE, _T("Main_Visible"), TRUE);
	ShowWindow(bVisible  ? SW_SHOW : SW_HIDE);
}
void CMainDlg::SaveStatus()
{
	CRect rc;
	GetWindowRect(&rc);
	//
	CWizKMSettings settings;
	settings.SetInt(SECTION_NOTE, _T("Main_xPos"), rc.left);
	settings.SetInt(SECTION_NOTE, _T("Main_yPos"), rc.top);
	settings.SetBool(SECTION_NOTE, _T("Main_TextLabel"), m_bTextLabel);
	settings.SetBool(SECTION_NOTE, _T("Main_Compact"), IsCompact());

	BOOL bVisible = (GetStyle() & WS_VISIBLE) ? TRUE : FALSE;
	settings.SetBool(SECTION_NOTE, _T("Main_Visible"), bVisible);
}


LRESULT CMainDlg::OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	CPoint pos;
	GetCursorPos(&pos);
	//
	PopupTrayMenu(pos.x, pos.y);
	return 0;
}

LRESULT CMainDlg::OnTrayTextlabel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	m_bTextLabel = !m_bTextLabel;
	ResetToolBar();
	//
	return 0;
}

LRESULT CMainDlg::OnTrayMinimize(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	BOOL bVisible = (GetStyle() & WS_VISIBLE) ? TRUE : FALSE;
	if (bVisible)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		ShowWindow(SW_SHOW);
	}
	return 0;
}
LRESULT CMainDlg::OnTbnDropDownNote(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	NMTOOLBAR* pToolBar = (NMTOOLBAR *)pnmh;
	//
	CRect rc(pToolBar->rcButton);
	m_wndToolBar.ClientToScreen(&rc);
	//
	PopupTrayMenu(rc.left, rc.bottom);
	//
	return 0;
}

LRESULT CMainDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CWaitCursor wait;
	UINT nID = (UINT)wParam;
	if (ID_TRAY_COPYSELECTION == nID
		|| ID_TRAY_PASTETOWIZ == nID
		|| ID_TRAY_CLIPSCREENSHOT == nID
		|| ID_TRAY_NEWNOTE == nID
		|| ID_TRAY_BRINGALLNOTESTOFRONT == nID
		)
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);
	}
	//
	return 0;
}


LRESULT CMainDlg::OnTrayOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CWizPropertySheetEx ps(IDS_OPTIONS);
	ps.m_psh.dwFlags |= (PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP);
	//
	CConfigHotkeyDlg dlgHotkey;
	CConfigGeneralDlg dlgGeneral;
	CConfigToolbarDlg dlgToolbar;
	//
	ps.AddPage(dlgGeneral);
	ps.AddPage(dlgHotkey);
	//
	BOOL bWizExplorerExists = WizKMExplorerExists();
	if (bWizExplorerExists)
	{
		ps.AddPage(dlgToolbar);
	}
	//
	if (IDOK != ps.DoModal())
		return 0;
	//
	LoadSettings();
	RegisterAllHotkeys();
	//
	SetCompact(FALSE);
	ResetToolBar();

	return 0;
}

void CMainDlg::OnSyncEnd(int nExitCode, UINT nFlags)
{
	m_dwLastSyncTickCount = GetTickCount();
	//
	LoadNotesStatus();
	ResetEvents();
	//
	if (m_pTodoDlg && !m_pTodoDlg->IsModified())
	{
		m_pTodoDlg->Refresh();
	}
	//
	size_t nCount = m_arrayNote.size();
	for (intptr_t i = nCount - 1; i >= 0; i--)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		if (pDlg && pDlg->IsWindow())
		{
			CComPtr<IWizDocument> spDocument = pDlg->GetDocument();
			if (spDocument)
			{
				CComPtr<IWizDocument> spTemp = m_db.GetDocumentByGUID(CWizKMDatabase::GetObjectGUID(spDocument.p));
				if (!spTemp)
				{
					pDlg->DestroyWindow();
					m_arrayNote.erase(m_arrayNote.begin() + i);
				}
			}
		}
	}
}

BOOL CMainDlg::InitTask()
{
	if (!IsAutoCreateTodayTasks())
		return TRUE;
	//
	PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_TODOLIST, 0), 0);
	//
	return TRUE;
}

CString CMainDlg::GetTodayTaskTitle()
{
	CString strTitle = WizDateToLocalString(COleDateTime::GetCurrentTime()) + _T(" ") + WizFormatString0(IDS_TODAY_TASK);
	return strTitle;
}

CNoteDlg* CMainDlg::FindTaskNote()
{
	CString strTitle = GetTodayTaskTitle();
	for (CNodeDlgArray::const_iterator it = m_arrayNote.begin();
		it != m_arrayNote.end();
		it++)
	{
		CNoteDlg* pDlg = *it;
		CComPtr<IWizDocument> spDocument = pDlg->GetDocument();
		if (!spDocument)
			return NULL;
		//
		if (strTitle == CWizKMDatabase::GetDocumentTitle(spDocument))
			return pDlg;
		//
	}
	return NULL;
}
CComPtr<IWizDocument> CMainDlg::FindTaskDocument()
{
	CNoteDlg* pDlg = FindTaskNote();
	if (!pDlg)
		return NULL;
	//
	return pDlg->GetDocument();
}

LRESULT CMainDlg::OnTrayWizExplorer(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strParams = WizFormatString1(_T("/DatabasePath=%1"), m_db.GetDatabasePath());
	//
	ShellExecute(NULL, _T("open"), WizKMGetExplorerFileName(), strParams, NULL, SW_SHOW);

	return 0;
}
LRESULT CMainDlg::OnTrayWizCalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strParams = WizFormatString1(_T("/DatabasePath=%1"), m_db.GetDatabasePath());
	//
	ShellExecute(NULL, _T("open"), WizGetAppPath() + _T("WizKMCalendar.exe"), strParams, NULL, SW_SHOW);

	return 0;
}

#define WIZNOTE_COMMAND_LINE_REG_KEY			(WIZKM_REG_KEY_ROOT + _T("\\Note"))
#define WIZNOTE_COMMAND_LINE_REG_KEY_VALUE		_T("CommandLine")

BOOL CMainDlg::WriteCommandLineToReg(LPCTSTR lpszCommandLine)
{
	return WizRegWriteString(HKEY_CURRENT_USER, WIZNOTE_COMMAND_LINE_REG_KEY, WIZNOTE_COMMAND_LINE_REG_KEY_VALUE, lpszCommandLine);
}
BOOL CMainDlg::ReadCommandLineToReg(CString& strCommandLine, BOOL bClear)
{
	strCommandLine = WizRegReadStringDef(HKEY_CURRENT_USER, WIZNOTE_COMMAND_LINE_REG_KEY, WIZNOTE_COMMAND_LINE_REG_KEY_VALUE, _T(""));
	if (bClear)
	{
		WizRegDeleteValue(HKEY_CURRENT_USER, WIZNOTE_COMMAND_LINE_REG_KEY, WIZNOTE_COMMAND_LINE_REG_KEY_VALUE);
	}
	return TRUE;
}
LRESULT CMainDlg::OnProcessCommandLine(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CString strCommandLine;
	if (!ReadCommandLineToReg(strCommandLine, TRUE))
		return 0;
	//
	ProcessCommandLine(strCommandLine, wParam ? TRUE : FALSE);
	//
	return 0;
}
void CMainDlg::ProcessCommandLine(LPCTSTR lpszCommandLine, BOOL bPrompt /*= FALSE*/)
{
	CString strCommand = ::WizGetCommandLineValue(lpszCommandLine, _T("Command"));
	strCommand.MakeLower();
	//
	if (strCommand.IsEmpty() && bPrompt)
	{
		ShowBalloon(WizFormatString0(IDS_WIZNOTE), WizFormatString0(IDS_WIZNOTE_IS_RUNNING), 10);
	}
	else if (strCommand == _T("new_note"))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_NEWNOTE, 0), 0);
	}
	else if (strCommand == _T("edit_note"))
	{
		CString strDocumentGUID = ::WizGetCommandLineValue(lpszCommandLine, _T("DocumentGUID"));
		if (strDocumentGUID.IsEmpty())
			return;
		//
		CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strDocumentGUID);
		if (!spDocument)
			return;
		//
		if (CNoteDlg* pDlg = FindNote(spDocument, TRUE, FALSE))
		{
			pDlg->BringWindowToTopEx();
			pDlg->CenterWindow(GetDesktopWindow());
			pDlg->SetInfoModified(FALSE);
		}
	}
	else if (strCommand == _T("edit_todolist"))
	{
		CString strDocumentGUID = ::WizGetCommandLineValue(lpszCommandLine, _T("DocumentGUID"));
		if (strDocumentGUID.IsEmpty())
			return;
		//
		CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strDocumentGUID);
		if (!spDocument)
			return;
		//
		CreateTodoDlg();
		if (!m_pTodoDlg)
			return;
		//
		m_pTodoDlg->SetDocument(spDocument);
		m_pTodoDlg->BringWindowToTopEx();
		m_pTodoDlg->CenterWindow(GetDesktopWindow());
		m_pTodoDlg->SetInfoModified(FALSE);
	}
}

LRESULT CMainDlg::OnTrayTodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CreateTodoDlg();
	//
	m_pTodoDlg->BringWindowToTopEx();

	return 0;
}

void CMainDlg::CreateTodoDlg()
{
	if (!m_pTodoDlg)
	{
		m_pTodoDlg = new CTodoDlg(&m_db);
	}
	if (!m_pTodoDlg->IsWindow())
	{
		m_pTodoDlg->Create(NULL);
	}
}


LRESULT CMainDlg::OnNotesShowallnotes(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	size_t nCount = m_arrayNote.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CNoteDlg* pDlg = m_arrayNote[i];
		//
		pDlg->BringWindowToTopEx();
	}
	//
	return 0;
}
void CMainDlg::UpdateAllNotesFont()
{
}
void CMainDlg::SetNoteFont(const LOGFONT& lf, COLORREF crText)
{
	m_crNoteText = crText;
	//
	{
		CWizKMSettings settings;
		CString strSection(_T("Note"));
		settings.SetStr(strSection, _T("FontName"), lf.lfFaceName);
		settings.SetInt(strSection, _T("FontHeight"), lf.lfHeight);
		settings.SetInt(strSection, _T("FontWeight"), lf.lfWeight);
		settings.SetInt(strSection, _T("FontItalic"), lf.lfItalic);
		settings.SetInt(strSection, _T("FontUnderline"), lf.lfUnderline);
		settings.SetInt(strSection, _T("FontStrikeout"), lf.lfStrikeOut);
		//
		settings.SetInt(strSection, _T("FontColor"), m_crNoteText);
		//force save settings
	}
	//
	CFont oldFont;
	oldFont.Attach(m_fontNoteText.Detach());
	//
	ATLASSERT(m_fontNoteText.IsNull());
	//
	m_fontNoteText.CreateFontIndirect(&lf);
	if (m_fontNoteText.IsNull())
		return;
	//
	for (CNodeDlgArray::iterator it = m_arrayNote.begin();
		it != m_arrayNote.end();
		it++)
	{
		CNoteDlg* pDlg = *it;
		if (pDlg->IsWindow())
		{
			pDlg->UpdateFont();
		}
	}

}
HFONT CMainDlg::GetNoteFont()
{
	if (m_fontNoteText.IsNull())
	{
		CreateNoteFont(m_fontNoteText);
	}
	//
	return m_fontNoteText;
}

BOOL CMainDlg::CreateNoteFont(CFont& font)
{
	CFont fontDefault;
	WizCreateUIFont(fontDefault, WIZUIFONT_LARGE);
	//
	LOGFONT lf;
	fontDefault.GetLogFont(&lf);
	//
	CString strSection(_T("Note"));

	CWizKMSettings settings;
	CString strFontName = settings.GetStr(strSection, _T("FontName"), lf.lfFaceName);
	if (!strFontName.IsEmpty()
		&& strFontName.GetLength() < LF_FACESIZE)
	{
		_tcscpy_s(lf.lfFaceName, LF_FACESIZE, strFontName);
	}
	lf.lfHeight = settings.GetInt(strSection, _T("FontHeight"), lf.lfHeight);
	lf.lfWeight = settings.GetInt(strSection, _T("FontWeight"), lf.lfWeight);
	lf.lfItalic = settings.GetInt(strSection, _T("FontItalic"), lf.lfItalic);
	lf.lfUnderline = settings.GetInt(strSection, _T("FontUnderline"), lf.lfUnderline);
	lf.lfStrikeOut = settings.GetInt(strSection, _T("FontStrikeout"), lf.lfStrikeOut);
	//
	m_crNoteText = settings.GetInt(strSection, _T("FontColor"), GetSysColor(COLOR_WINDOWTEXT));
	//
	return font.CreateFontIndirect(&lf) ? TRUE : FALSE;
}

LRESULT CMainDlg::OnTraySync(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	Sync();
	//
	return 0;
}

LRESULT CMainDlg::OnTrayClipscreenshot(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMClipScreenshot(m_hWnd, m_db.GetDatabasePath(), WizKMExplorerGetSelectedLocation());

	return 0;
}

LRESULT CMainDlg::OnTrayCopyselection(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMCopySelection(m_hWnd, m_hwndForegroundWindow, m_hwndLastIEWindow, m_db.GetDatabasePath(), WizKMExplorerGetSelectedLocation());

	return 0;
}

LRESULT CMainDlg::OnTrayPastetowiz(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMPasteToWiz(m_hWnd, m_db.GetDatabasePath(), WizKMExplorerGetSelectedLocation());

	return 0;
}

LRESULT CMainDlg::OnTrayCompactmode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	SetCompact(!IsCompact());

	return 0;
}

LRESULT CMainDlg::OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	SetCompact(!IsCompact());

	return 0;
}

LRESULT CMainDlg::OnIsHotKeyRegistered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_hotkeys.IsRegistered();
}

STDMETHODIMP CMainDlg::OnDragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	return S_OK;
}
STDMETHODIMP CMainDlg::OnDrop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	CString strLocation;
	BOOL bPromptLocation = TRUE;
	//
	if (wizPromptSelect != ExplorerGetSaveDestination())
	{
		strLocation = WizFormatString1(_T("/%1/"), FOLDER_MY_DRAFTS);
		bPromptLocation = FALSE;
	}
	typedef HRESULT WINAPI Type_WizKMImportDataObject(IDataObject *pDataObj, LPCWSTR lpszDatabasePath, LPCWSTR lpszLocation, BOOL bPromptLocation);
	HMODULE hModule = ::LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
	{
		TOLOG(_T("Failed to load library: WizKMControls.dll"));
		return S_OK;
	}
	//
	Type_WizKMImportDataObject* fun = (Type_WizKMImportDataObject *)GetProcAddress(hModule, "WizKMImportDataObject");
	if (fun)
	{
		fun(pDataObj, m_db.GetDatabasePath(), strLocation, bPromptLocation);
	}
	//
	FreeLibrary(hModule);
	//
	return S_OK;
}

LRESULT CMainDlg::OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_EXIT, 0), 0);
	return 0;
}

LRESULT CMainDlg::OnPowerBroadcast(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch ((UINT)wParam)
	{
	case PBT_APMSUSPEND:
		OnPowerSuspend();
		break;
	case PBT_APMRESUMEAUTOMATIC:
	case PBT_APMRESUMESUSPEND:
	case PBT_APMRESUMECRITICAL:
		OnPowerResume();
		break;
	}
	//
	return 0;
}
void CMainDlg::ResetSyncTickCount()
{
	m_dwLastSyncTickCount = GetTickCount() - int((m_nSyncMinutes - 1) * 1000 * 60);
}
void CMainDlg::OnPowerResume()
{
	ResetSyncTickCount();
	//
	m_bSuspend = FALSE;
}
void CMainDlg::OnPowerSuspend()
{
	m_bSuspend = TRUE;
}

