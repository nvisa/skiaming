// WizKMCalendarView.cpp : implementation of the CWizKMCalendarView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "WizKMCalendarView.h"

#include "MainFrm.h"

#include "../../WizGlobals/WizChineseCalendar.h"

#include "../Globals/WizKMCommonUI.h"


CWizKMCalendarView::CWizKMCalendarView()
{
	SetEventProvider(this);
	m_eBackgroundTextType = textNone;
	//
	m_bShowWeekNumbers = TRUE;
	//
	LoadSettings();
}

void CWizKMCalendarView::GetEvents(const COleDateTime& tStart, COleDateTime& tEnd, CWizCalendarEventArray& arrayEvent)
{
	WizKMGetCalendarEvents(WizGetDatabase(), tStart, tEnd, arrayEvent);
	//
	if (!m_arrayTags.empty())
	{
		CWizKMDatabase* pDatabase = WizGetDatabase();
		if (pDatabase)
		{
			size_t nEventCount = arrayEvent.size();
			for (intptr_t iEvent = nEventCount - 1; iEvent >= 0; iEvent--)
			{
				CComPtr<IWizDocument> spDocument = pDatabase->GetDocumentByGUID(arrayEvent[iEvent].strGUID);
				if (spDocument)
				{
					CString strTagsText;
					CWizKMDatabase::GetDocumentTagsText(spDocument, strTagsText);
					strTagsText.Replace(_T("; "), _T(";"));
					strTagsText.MakeLower();
					strTagsText = CString(_T(";")) + strTagsText + _T(";");
					//
					BOOL bRemove = TRUE;
					//
					for (CWizStdStringArray::const_iterator it = m_arrayTags.begin();
						it != m_arrayTags.end();
						it++)
					{
						CString strTag = CString(_T(";")) + *it + _T(";");
						strTag.MakeLower();
						if (-1 != strTagsText.Find(strTag))
						{
							bRemove = FALSE;
							break;
						}
					}
					//
					if (!bRemove)
						continue;
					//
					arrayEvent.erase(arrayEvent.begin() + iEvent);
				}
			}
		}
	}
}
void CWizKMCalendarView::CreateEvent(const COleDateTime& tSelected)
{
	if (!WizKMCreateEvent(WizGetDatabase()->GetDatabase(), tSelected))
		return;
	//
	ResetEvents();
}

void CWizKMCalendarView::DeleteEvent(const WIZCALENDAREVENT& e)
{
	if (e.IsNull())
		return;
	//
	CWizKMDatabase* pDatabase = WizGetDatabase();
	if (!pDatabase)
	{
		ATLASSERT(FALSE);
		return;
	}
	//
	CComPtr<IWizDocument> spDocument = pDatabase->GetDocumentByGUID(e.strGUID);
	if (!spDocument)
	{
		return;
	}
	//
	spDocument->RemoveFromCalendar();
	//
	ResetEvents();
}
void CWizKMCalendarView::EditEvent(const WIZCALENDAREVENT& e)
{
	if (e.IsNull())
		return;
	//
	CWizKMDatabase* pDatabase = WizGetDatabase();
	if (!pDatabase)
	{
		ATLASSERT(FALSE);
		return;
	}
	//
	CComPtr<IWizDocument> spDocument = pDatabase->GetDocumentByGUID(e.strGUID);
	if (!spDocument)
	{
		return;
	}
	//
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	CComPtr<IDispatch> spDocumentDisp;
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	HRESULT hr = spCommonUI->EditCalendarEvent(spDocument, &vb);
	if (FAILED(hr))
		return;
	//
	ResetEvents();
}

LRESULT CWizKMCalendarView::OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	if (!menu.LoadMenu(IDR_MENU_CALENDAR))
		return 0;
	WizTranslationsTranslateMenu(menu);
	//
	CMenuHandle submenu = menu.GetSubMenu(0);
	if (!submenu)
		return 0;
	//
	BOOL bSelectEvent = !GetSelectedEvent().IsNull();
	//
	UINT nEnabled = MF_BYCOMMAND | MF_ENABLED;
	UINT nDisabled = MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
	//
	submenu.EnableMenuItem(ID_CALENDAR_DELETEEVENT, bSelectEvent ? nEnabled : nDisabled);
	submenu.EnableMenuItem(ID_CALENDAR_EDITEVENT, bSelectEvent ? nEnabled : nDisabled);
	//
	UINT nChecked = MF_BYCOMMAND | MF_CHECKED;
	UINT nUnchecked = MF_BYCOMMAND | MF_UNCHECKED;
	//
	submenu.CheckMenuItem(ID_CALENDAR_MONTH, GetView() == viewtypeMonth ? nChecked : nUnchecked);
	submenu.CheckMenuItem(ID_CALENDAR_WEEK, GetView() == viewtypeWeek ? nChecked : nUnchecked);
	submenu.CheckMenuItem(ID_CALENDAR_DAY, GetView() == viewtypeDay ? nChecked : nUnchecked);
	//
	CPoint pt;
	GetCursorPos(&pt);
	submenu.TrackPopupMenu(0, pt.x, pt.y, WizGetMainFrame()->m_hWnd);
	//
	return 0;
}

CString CWizKMCalendarView::GetMonthViewBackgroundText(const COleDateTime& t)
{
	return m_mapBackgroundText.GetBackgroundText(m_eBackgroundTextType, t);
}
void CWizKMCalendarView::SetBackgroundTextType(WizKMMonthViewCellBackgroundTextType eType)
{
	m_mapBackgroundText.clear();
	m_eBackgroundTextType = eType;
	//
	if (IsWindow())
	{
		Invalidate();
	}
}

CString CWizKMCalendarView::GetSecondCalendarDateText(const COleDateTime& t, BOOL bLong)
{
	static UINT nACP = GetACP();
	switch (nACP)
	{
	case 936:
	case 950:
		{
			CString strDay = WizChineseCalendarGetChineseDay(t);
			//
			CString str;
			if (bLong)
			{
				str = WizChineseCalendarGetMonthDayString(COleDateTime(t));
			}
			else
			{
				str = WizChineseCalendarAutoGetDayString(COleDateTime(t));
			}
			//
			if (!strDay.IsEmpty())
			{
				str = str + _T(" ") + strDay;
			}
			return str;
		}
	}
	return CString();
}

void CWizKMCalendarView::SetTags(const CWizStdStringArray& arrayTags)
{
	m_arrayTags.assign(arrayTags.begin(), arrayTags.end());
	//
	ResetEvents();
}

CString CWizKMCalendarView::GetNavigatorText(int index)
{
	if (m_bShowWeekNumbers)
	{
		return CWizCalendarView::GetNavigatorText(index);
	}
	else
	{
		return CString();
	}
}

COleDateTime CWizKMCalendarView::GetFirstWeek(const COleDateTime& t)
{
	COleDateTime tWeek = WizCalendarGetFirstWeek();
	COleDateTime tRet = COleDateTime(t.GetYear(), tWeek.GetMonth(), tWeek.GetDay(), 0, 0, 0);
	if (tRet > t)
	{
		return COleDateTime(t.GetYear() - 1, tWeek.GetMonth(), tWeek.GetDay(), 0, 0, 0);
	}
	//
	return tRet;
}

void CWizKMCalendarView::LoadSettings()
{
	m_bShowWeekNumbers = WizCalendarIsShowWeekNumbers();
}


CString CWizKMMonthViewCellBackgroundTextMap::GetKey(const COleDateTime& t)
{
	CString strDate;
	strDate.Format(_T("%04d%02d%02d"), t.GetYear(), t.GetMonth(), t.GetDay());
	return strDate;
}

CString CWizKMMonthViewCellBackgroundTextMap::GetBackgroundText(WizKMMonthViewCellBackgroundTextType eType, const COleDateTime& t)
{
	if (textNone == eType)
		return CString();
	//
	CString strDate = GetKey(t);
	const_iterator it = find(strDate);
	if (it != end())
		return it->second;
	//
	//
	CWizKMDatabase* pDatabase = WizGetDatabase();
	if (!pDatabase)
		return CString();
	//
	COleDateTime tMonthBegin = COleDateTime(t.GetYear(), t.GetMonth(), 1, 0, 0, 0);
	COleDateTime tMonthEnd = tMonthBegin + COleDateTimeSpan(31, 0, 0, 0);
	//
	if (textTodoList == eType)
	{
		for (int i = 0; i < 31; i++)
		{
			COleDateTime tDay = tMonthBegin + COleDateTimeSpan(i, 0, 0, 0);
			//
			CComPtr<IDispatch> spDocumentDisp;
			pDatabase->GetDatabase()->GetTodoDocument(tDay, &spDocumentDisp);
			//
			CComQIPtr<IWizDocument> spDocument(spDocumentDisp);
			if (!spDocument)
				continue;
			//
			CString strKey = GetKey(tDay);
			//
			const_iterator itBackground = find(strKey);
			if (itBackground == end() || itBackground->second.IsEmpty())
			{
				CString strText = CWizKMDatabase::GetDocumentText(spDocument, 0);
				strText.Replace(_T("\r\n\r\n"), _T("\r\n"));
				strText.Replace(_T("\n\n"), _T("\n"));
				operator [] (strKey) = strText;
			}
		}
	}
	else if (textJournal == eType)
	{
		CString strSQL = WizFormatString2(_T("DOCUMENT_TYPE='journal' and DT_CREATED>=%1 and DT_CREATED<=%2"),
			WizTimeToSQL(tMonthBegin),
			WizTimeToSQL(tMonthEnd)
			);
		//
		CWizDocumentArray arrayDocument;
		pDatabase->GetDocumentsBySQL(strSQL, arrayDocument);
		//
		for (CWizDocumentArray::const_iterator it = arrayDocument.begin();
			it != arrayDocument.end();
			it++)
		{
			COleDateTime tNote = CWizKMDatabase::GetDocumentDateCreated(*it);
			CString strKey = GetKey(tNote);
			//
			const_iterator itBackground = find(strKey);
			if (itBackground == end() || itBackground->second.IsEmpty())
			{
				operator [] (strKey) = CWizKMDatabase::GetDocumentText(*it, 0);
			}
		}
	}
	else if (textNote == eType)
	{
		CString strSQL = WizFormatString2(_T("DOCUMENT_TYPE='note' and DT_CREATED>=%1 and DT_CREATED<=%2"),
			WizTimeToSQL(tMonthBegin),
			WizTimeToSQL(tMonthEnd)
			);
		//
		CWizDocumentArray arrayDocument;
		pDatabase->GetDocumentsBySQL(strSQL, arrayDocument);
		//
		for (CWizDocumentArray::const_iterator it = arrayDocument.begin();
			it != arrayDocument.end();
			it++)
		{
			COleDateTime tNote = CWizKMDatabase::GetDocumentDateCreated(*it);
			CString strKey = GetKey(tNote);
			//
			const_iterator itBackground = find(strKey);
			if (itBackground == end() || itBackground->second.IsEmpty())
			{
				operator [] (strKey) = CWizKMDatabase::GetDocumentText(*it, 0);
			}
		}
	}
	//
	for (int i = 0; i < 31; i++)
	{
		COleDateTime tDay = tMonthBegin + COleDateTimeSpan(i, 0, 0, 0);
		//
		CString strKey = GetKey(tDay);
		//
		const_iterator itBackground = find(strKey);
		if (itBackground == end())
		{
			operator [] (strKey) = _T("");
		}
	}
	//
	it = find(strDate);
	if (it != end())
		return it->second;
	//
	ATLASSERT(FALSE);
	//
	return CString();
}
