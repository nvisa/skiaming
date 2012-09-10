#include "StdAfx.h"
#include "TodoDlg.h"
#include "MainDlg.h"

#include "NoteSettings.h"

#include "../Globals/WizKMCalendarEvents.h"

#define TIMER_ID_SAVE		101

CTodoDlg::CTodoDlg(CWizKMDatabase* pDatabase)
	: m_pDatabase(pDatabase)
	, m_wndList(pDatabase)
{
	ATLASSERT(m_pDatabase);
	//
	m_crBackground = RGB(0xCB, 0xFE, 0xC5);
	m_crBackground = WizHTMLStringColorToColor(WizKMGetPrivateString(_T("Todo"), _T("DefaultBackgroundColor"), WizHTMLColorToStringColor(m_crBackground)));
	//
	m_nMenuID = IDR_MENU_TODO;
	//
	m_tTodoListDate = WizKMTimeToTodoListTime(COleDateTime::GetCurrentTime());
}

CTodoDlg::~CTodoDlg()
{
}

LRESULT CTodoDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	//
	m_btnPrev.Create(m_hWnd, NULL, NULL, 0, 0, IDC_BUTTON_PREV);
	m_btnNext.Create(m_hWnd, NULL, NULL, 0, 0, IDC_BUTTON_NEXT);
	m_wndList.Create(m_hWnd, NULL, NULL, 0, 0, IDC_TREE_TODO);

	WizTranslationsTranslateWindow(m_hWnd);
	//
	InitClient();
	//
	m_btnPrev.SetIcon(IDI_ICON_PREV_BUTTON, 8, 16);
	m_btnNext.SetIcon(IDI_ICON_NEXT_BUTTON, 8, 16);
	m_btnMenu.SetIcon(IDI_ICON_MENU_BUTTON);
	m_btnClose.SetIcon(IDI_ICON_CLOSE_BUTTON);
	//
	ModifyStyleEx(0, WS_EX_LAYERED, 0);
	//
	SetTimer(TIMER_ID_SAVE, 1000 * 10, NULL);
	//
	RandomPosition();
	//
	LoadStatus();
	//
	LoadCurrentTodoList();
	//
	WizKMObjectMessageRegisterReceiver(objecttypeDocument, m_hWnd);
	//
	return 1;  // Let the system set the focus
}

CRect CTodoDlg::GetTitleRect()
{
	CRect rcNext;
	if (m_btnNext.IsWindow())
	{
		m_btnNext.GetWindowRect(&rcNext);
		ScreenToClient(&rcNext);
	}
	CRect rcMenu;
	if (m_btnMenu.IsWindow())
	{
		m_btnMenu.GetWindowRect(&rcMenu);
		ScreenToClient(&rcMenu);
	}
	//
	CRect rcTitle(rcNext.right + 8, rcNext.top, rcMenu.left - 8, rcMenu.bottom);
	return rcTitle;
}

CString CTodoDlg::GetTitle()
{
	return WizKMGetDateTitle(m_tTodoListDate, WizFormatString0(IDS_TODO_LIST));
}

void CTodoDlg::SetColor(COLORREF cr)
{
	CWizNoteSmallDlgBase::SetColor(cr);
	//
	COLORREF crTitle = GetTitleBackgroundColor();
	//
	m_btnPrev.SetBackgroundColor(crTitle);
	m_btnNext.SetBackgroundColor(crTitle);
	//
	m_wndList.SetBackgroundColor(m_crBackground);
}


LRESULT CTodoDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch ((UINT)wParam)
	{
	case TIMER_ID_SAVE:
		AutoSave();
		break;
	}
	//
	return 0;
}

BOOL CTodoDlg::OnModifyDocument(LPCTSTR lpszGUID)
{
	if (!m_spDocument)
		return FALSE;
	//
	if (0 != CWizKMDatabase::GetObjectGUID(m_spDocument.p).CompareNoCase(lpszGUID))
		return FALSE;
	//
	/*
	避免保存的时候，消息重入，导致死循环//
	*/
	//
	if (IsModified())
		return FALSE;
	//
	Refresh();
	//
	return TRUE;
}
CComPtr<IWizEvent> CTodoDlg::GetTodoEvent(WIZTODODATA* pData)
{
	if (!pData)
		return NULL;
	//
	if (pData->arrayLinkedDocumentGUID.size() != 1)
		return NULL;
	//
	CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(pData->arrayLinkedDocumentGUID[0]);
	if (!spDocument)
		return NULL;
	CString strType = CWizKMDatabase::GetDocumentType(spDocument);
	if (0 != strType.CompareNoCase(_T("event")))
		return NULL;
	CComPtr<IDispatch> spEventDisp;
	spDocument->get_Event(&spEventDisp);
	CComQIPtr<IWizEvent> spEvent(spEventDisp);
	if (!spEvent)
		return NULL;
	//
	CComBSTR bstrRecurrence;
	spEvent->get_Recurrence(&bstrRecurrence);
	CString strRecurrence(bstrRecurrence);
	if (!strRecurrence.IsEmpty())
	{
		CString strRecurrenceIndex;
		strRecurrenceIndex.Format(_T("%04d%02d%02d"),
			m_tTodoListDate.GetYear(),
			m_tTodoListDate.GetMonth(),
			m_tTodoListDate.GetDay());
	
		spEvent->put_RecurrenceIndex(CComBSTR(strRecurrenceIndex));
	}
	//
	return spEvent;
}
//

LRESULT CTodoDlg::OnNotifyParentCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LPCTSTR lpszCommand = (LPCTSTR)wParam;
	try
	{
		if (lpszCommand)
		{
			if (0 == _tcsicmp(lpszCommand, _T("OnItemCheckStateChanged")))
			{
				WIZTODODATA* pData = (WIZTODODATA *)lParam;
				if (pData
					&& pData->eState == todoState100)
				{
					CComPtr<IWizEvent> spEvent = GetTodoEvent(pData);
					if (spEvent)
					{
						if (WizKMGetPrivateBool(_T("Event"), _T("CompleteEventWhileTodoCompleted"), TRUE))
						{
							WizKMEventSetCompleted(spEvent);
							//
							WizGetMainDlg()->PostMessage(UM_REFRESH_TODO_LIST, 0, 0);
						}
					}
				}
			}
		}
	}
	catch (...)
	{
	}
	return 0;
}

void CTodoDlg::InitClient()
{
	CWizNoteSmallDlgBase::InitClient();
	//
	m_wndContainer.SetClient(m_wndList);
	//
	UpdateLayout();
}

void CTodoDlg::UpdateLayout()
{
	CWizNoteSmallDlgBase::UpdateLayout();
	//
	CRect rc;
	GetClientRect(&rc);
	//
	CRect rcPrev = CRect(8, 5, 20, 23);
	//
	CRect rcNext = rcPrev;
	rcNext.MoveToX(rcPrev.right);
	//
	if (m_btnPrev.IsWindow())
	{
		m_btnPrev.SetWindowPos(NULL, rcPrev, SWP_NOZORDER | SWP_NOACTIVATE);
	}
	if (m_btnNext.IsWindow())
	{
		m_btnNext.SetWindowPos(NULL, rcNext, SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


void CTodoDlg::Close()
{
	CWizNoteSmallDlgBase<CTodoDlg>::Close();
	//
	WizKMObjectMessageUnregisterReceiver(objecttypeDocument, m_hWnd);
	//
	SaveStatus();
}

void CTodoDlg::SaveStatus()
{
	if (!IsWindow())
		return;
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	CWizKMSettings settings;
	//
	LPCTSTR lpszSection = _T("TodoList");
	//
	settings.SetInt(lpszSection, _T("Left"), rc.left);
	settings.SetInt(lpszSection, _T("Top"), rc.top);
	settings.SetInt(lpszSection, _T("Right"), rc.right);
	settings.SetInt(lpszSection, _T("Bottom"), rc.bottom);
	settings.SetInt(lpszSection, _T("BackgroundColor"), m_crBackground);
	settings.SetInt(lpszSection, _T("Transparent"), m_nTransparentPercent);
	settings.SetBool(lpszSection, _T("Visible"), IsWindowVisible());
	settings.SetInt(lpszSection, _T("Locked"), GetDlgState());
	settings.SetInt(lpszSection, _T("NormalHeight"), m_nNormalHeight);
}
void CTodoDlg::LoadStatus()
{
	if (!IsWindow())
		return;
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	CWizKMSettings settings;
	//
	LPCTSTR lpszSection = _T("TodoList");
	//
	rc.left = settings.GetInt(lpszSection, _T("Left"), rc.left);
	rc.top = settings.GetInt(lpszSection, _T("Top"), rc.top);
	rc.right = settings.GetInt(lpszSection, _T("Right"), rc.right);
	rc.bottom = settings.GetInt(lpszSection, _T("Bottom"), rc.bottom);
	//
	MoveWindow(rc);
	//
	m_crBackground = settings.GetInt(lpszSection, _T("BackgroundColor"), m_crBackground);
	m_nTransparentPercent = settings.GetInt(lpszSection, _T("Transparent"), m_nTransparentPercent);
	//
	if (settings.GetBool(lpszSection, _T("Visible"), TRUE))
	{
		BringWindowToTopEx();
	}
	//
	int nState = settings.GetInt(_T("Locked"), FALSE);
	SetDlgState((WIZSMALLDLGSTATE)nState);
	//
	m_nNormalHeight = settings.GetInt(lpszSection, _T("NormalHeight"), m_nNormalHeight);
	//
	SetColor(m_crBackground);
	UpdateLockButtonIcon();
	SetTransparentPercent(m_nTransparentPercent);
	//
	UpdateLayout();
}


BOOL CTodoDlg::SaveData()
{
	CWaitCursor wait;
	//
	if (!m_spDocument)
	{
		m_spDocument = WizKMCreateTodoDocument(m_pDatabase, m_tTodoListDate, FALSE);
		if (!m_spDocument)
		{
			TOLOG(_T("Failed to create document!"));
			return FALSE;
		}
	}
	//
	CComPtr<IWizTodoItemCollection> spColl = m_wndList.GetAllData();
	if (!spColl)
	{
		TOLOG(_T("Failed to get todo item data!"));
		return FALSE;
	}
	//
	HRESULT hr = m_spDocument->put_TodoItems(spColl);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to update document!"));
		return FALSE;
	}
	//
	m_wndList.SetModified(FALSE);
	//
	return TRUE;
}

BOOL CTodoDlg::AutoSave()
{
	if (!m_wndList.GetModify())
		return TRUE;
	//
	if (!SaveData())
		return FALSE;
	//
	Invalidate();
	//
	return TRUE;
}

BOOL CTodoDlg::LoadData()
{
	if (!IsWindow())
		return FALSE;
	//
	{
		CWizTreeCtrlStateLocker<CWizTodoTreeCtrl> locker(m_wndList);
		//
		m_wndList.DeleteAllItems();
		//
		SetWindowText(GetTitle());
		//
		WIZTODODATAEX::CWizTodoDataExArray arrayData;
		//
		if (m_spDocument)
		{
			WizDocumentGetTodoData(m_spDocument, arrayData);
		}
		//
		WizKMCalendarEventsAddToTodoData(m_pDatabase, m_tTodoListDate, arrayData);
		//
		COleDateTime tNow = COleDateTime::GetCurrentTime();
		if (m_tTodoListDate.GetYear() == tNow.GetYear()
			&& m_tTodoListDate.GetMonth() == tNow.GetMonth()
			&& m_tTodoListDate.GetDay() == tNow.GetDay())
		{
			if (IsMoveUncompletedToTodayTasks())
			{
				if (WizKMAddUncompletedToTodoData(m_pDatabase, m_spDocument, m_tTodoListDate, arrayData))
				{
					ATLASSERT(m_spDocument);
				}
			}
		}
		//
		m_wndList.SetAllData(arrayData);
		//
		Invalidate();
		//
		m_wndList.GetBlankTodoItem(NULL, TRUE);
		m_wndList.SetModified(FALSE);
	}
	//
	m_wndList.ExpandAllItemsWithChildren(NULL, TVE_EXPAND);
	//
	UpdateUpDownButtons();
	//
	return TRUE;
}

void CTodoDlg::UpdateLockButtonIcon()
{
	UINT nIcon = IDI_ICON_UNLOCK_BUTTON;
	switch (GetDlgState())
	{
	case stateTopMost:
		nIcon = IDI_ICON_LOCK_BUTTON;
		break;
	/*
	case statePinDesk:
		nIcon = IDI_ICON_PIN_DESK_BUTTON;
		break;
		*/
	};
	//
	m_btnLock.SetIcon(nIcon);
}


BOOL CTodoDlg::CreateDocument()
{
	if (m_spDocument)
		return TRUE;
	//
	CString strTitle = GetTitle();
	if (strTitle.IsEmpty())
	{
		ATLASSERT(FALSE);
		strTitle = _T("Unknown Todo List");
	}
	//
	CComPtr<IWizFolder> spMonthFolder = WizKMGetMonthFolder(m_pDatabase, FOLDER_MY_NOTES);
	if (!spMonthFolder)
	{
		TOLOG(_T("Failed to create month folder!"));
		return FALSE;
	}
	//
	//
	CComPtr<IDispatch> spNewDocumentDisp;
	HRESULT hr = spMonthFolder->CreateDocument2(CComBSTR(strTitle), CComBSTR(L""), &spNewDocumentDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to create document object"));
		return FALSE;
	}
	//
	m_spDocument = CComQIPtr<IWizDocument>(spNewDocumentDisp);
	ATLASSERT(m_spDocument);
	if (!m_spDocument)
	{
		TOLOG(_T("System error: Failed convert dispatch to IWizDocument"));
		return FALSE;
	}
	//
	m_spDocument->put_Type(CComBSTR(L"todolist"));
	//
	CString strDate;
	strDate.Format(_T("%04d-%02d-%02d"), 
		m_tTodoListDate.GetYear(),
		m_tTodoListDate.GetMonth(),
		m_tTodoListDate.GetDay());
	//
	m_spDocument->put_ParamValue(CComBSTR(L"todolist_date"), CComBSTR(strDate));
	//
	return TRUE;
}

BOOL CTodoDlg::SetDocument(IWizDocument* pDocument, const COleDateTime& t)
{
	m_tTodoListDate = t;
	//
	m_spDocument = NULL;
	m_spDocument = pDocument;
	//
	return LoadData();
}

BOOL CTodoDlg::SetDocument(IWizDocument* pDocument)
{
	if (!pDocument)
		return FALSE;
	//
	COleDateTime t = WizKMGetDocumentTodoDate(pDocument);
	//
	return SetDocument(pDocument, t);
}
//
//LRESULT CTodoDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//{
//	Close();
//
//	return 0;
//}

LRESULT CTodoDlg::OnBnClickedButtonPrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	AutoSave();
	//
	COleDateTime t = m_tTodoListDate - COleDateTimeSpan(1, 0, 0, 0);
	LoadByTime(t);
	//
	return 0;
}
LRESULT CTodoDlg::OnBnClickedButtonNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	AutoSave();
	//
	COleDateTime t = m_tTodoListDate + COleDateTimeSpan(1, 0, 0, 0);
	LoadByTime(t);
	//
	return 0;
}
//
//LRESULT CTodoDlg::OnTodoClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//{
//	// TODO: Add your command handler code here
//	Close();
//
//	return 0;
//}

BOOL CTodoDlg::IsModified() const 
{
	if (!m_wndList.IsWindow())
		return FALSE; 
	//
	return m_wndList.GetModify();
}
//
BOOL CTodoDlg::LoadByTime(const COleDateTime& t)
{
	if (!m_pDatabase)
		return FALSE;
	//
	CComQIPtr<IWizDocument> spDocument;
	if (!WizKMGetTodoDocument(m_pDatabase, t, FALSE, FALSE, spDocument))
	{
		TOLOG(_T("Failed to get todo item document!"));
		return FALSE;
	}
	//
	if (spDocument && m_spDocument)
	{
		if (0 == CWizKMDatabase::GetObjectGUID(spDocument.p).CompareNoCase(CWizKMDatabase::GetObjectGUID(m_spDocument.p)))
		{
			COleDateTime tDatabase = CWizKMDatabase::GetDocumentDataDateModified(spDocument);
			COleDateTime tCurrent = CWizKMDatabase::GetDocumentDataDateModified(m_spDocument);
			if (tDatabase <= tCurrent)
				return TRUE;
		}
	}
	//
	SetDocument(spDocument, t);
	//
	return TRUE;
}
void CTodoDlg::LoadCurrentTodoList()
{
	COleDateTime t = COleDateTime::GetCurrentTime();
	LoadByTime(WizKMTimeToTodoListTime(t));
}
void CTodoDlg::Refresh()
{
	AutoSave();
	//
	LoadByTime(m_tTodoListDate);
}
