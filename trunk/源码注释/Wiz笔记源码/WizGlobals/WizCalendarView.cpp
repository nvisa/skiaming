#include "stdafx.h"
#include "WizCalendarView.h"

#include "WizCalendarEventColumnRow.h"


COLORREF g_crLineColor = RGB(214, 221, 230);
COLORREF g_crLineLightColor = WizColorLighter(g_crLineColor, 1.1f);
COLORREF g_crLineDarkColor = WizColorDarker(g_crLineColor, 0.5f);

COLORREF g_crSelectedBorderColor = WizColorDarker(g_crLineColor, 0.8f);
COLORREF g_crSelectedFillColor = RGB(182, 214, 251);
COLORREF g_crSelectedFillLighterColor = RGB(242, 247, 254);//WizColorLighter(g_crSelectedFillColor, 1.03f);
COLORREF g_crCurrentMonthFillColor = g_crSelectedFillLighterColor;

COLORREF g_crCurrentMonthTextColor = WizColorDarker(g_crLineColor, 0.5f);
COLORREF g_crNotCurrentMonthTextColor = WizColorDarker(g_crLineColor, 0.7f);


#define HEADER_HEIGHT			50
#define TIME_WIDTH				50
#define HALF_HOUR_HEIGHT		24
#define HOUR_HEIGHT				(HALF_HOUR_HEIGHT * 2)
#define HALF_WIZ_CALENDAR_HOUR_COUNT			48

#define MONTH_VIEW_ROW_COUNT	6

CWizCalendarView::CWizCalendarView()
{
	m_pProvider = NULL;
	m_pEvents = NULL;
	//
	m_tSelected = COleDateTime(2000, 1, 1, 0, 0, 0);
	m_tMonthViewCurrentMonth = m_tSelected;
	//
	WizCreateUIFont(m_fontMonthViewDay);
	WizCreateUIFont(m_fontText);
	WizCreateUIFont(m_fontTextBold, WIZUIFONT_BOLD);
	//
	m_eViewType = viewtypeMonth;
	//
	m_penLine.CreatePen(PS_SOLID, 1, g_crLineColor);
	m_penLineLighter.CreatePen(PS_SOLID, 1, g_crLineLightColor);
	m_penSelectedBorder.CreatePen(PS_SOLID, 1, g_crSelectedBorderColor);
	m_penLineDarker.CreatePen(PS_SOLID, 2, g_crLineDarkColor);
	//
	m_brushSelected.CreateSolidBrush(g_crSelectedFillColor);
	m_brushCurrentMonth.CreateSolidBrush(g_crCurrentMonthFillColor);
	m_brushSelectedLighter.CreateSolidBrush(g_crSelectedFillLighterColor);
	//
	ZeroMemory(m_arrayDayOfWeek, sizeof(int) * WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	int nDay = WizGetFirstDayOfWeek();
	//
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		m_arrayDayOfWeek[i] = (i + nDay) % WIZ_CALENDAR_WEEK_DAY_COUNT;
		m_arrayDayOfWeekLongName[i] = WizGetDayOfWeekLongName(m_arrayDayOfWeek[i]);
		m_arrayDayOfWeekShortName[i] = WizGetDayOfWeekShortName(m_arrayDayOfWeek[i]);
	}
	//
	TCHAR szFormat[MAX_PATH] = {0};
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, szFormat, MAX_PATH);
	CString strFormat(szFormat);
	strFormat.Replace(_T("m"), _T(""));
	strFormat.Replace(_T("s"), _T(""));
	strFormat.Replace(_T(":"), _T(""));
	//
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		COleDateTime t(2009, 1, 1, i, 0, 0);
		SYSTEMTIME st;
		t.GetAsSystemTime(st);
		//
		TCHAR szTime[MAX_PATH] = {0};
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, strFormat, szTime, MAX_PATH);
		//
		m_arrayHour[i] = szTime;
	}
	//
	SetSelectedTime(COleDateTime::GetCurrentTime(), FALSE);
}

void CWizCalendarView::SetEventProvider(CWizCalendayEventProvider* pProvider)
{
	ATLASSERT(pProvider);
	m_pProvider = pProvider;
	//
	if (!IsWindow())
		return;
	//
	ResetEvents();
}
CWizCalendayEventProvider* CWizCalendarView::GetEventProvider()
{
	return m_pProvider;
}

BOOL CWizCalendarView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CWizCalendarView::OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;   // no background painting needed
}

void CWizCalendarView::DoPaint(CDCHandle dc)
{
	//TODO: Add your drawing code here
	//
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(dc);
	//
	CRect rcClient;
	GetClientRect(&rcClient);
	//
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rcClient.Width(), rcClient.Height());
	HBITMAP hBmpOld = dcMemory.SelectBitmap(bmp);
	//
	dcMemory.FillSolidRect(&rcClient, ::GetSysColor(COLOR_WINDOW));
	//
	dcMemory.SetViewportOrg(-m_ptOffset.x, -m_ptOffset.y);
	//
	int nDC = dcMemory.SaveDC();
	//
	PaintView(dcMemory.m_hDC);
	//
	dcMemory.RestoreDC(nDC);
	//
	::BitBlt(dc, 0, 0, rcClient.Width() + m_ptOffset.x, rcClient.Height() + m_ptOffset.y, dcMemory.m_hDC, 0, 0, SRCCOPY);
	dcMemory.SelectBitmap(hBmpOld);
}


void CWizCalendarView::PaintView(CDCHandle dc)
{
	dc.SetBkMode(TRANSPARENT);
	if (viewtypeMonth == m_eViewType)
	{
		DrawMonthView(dc);
	}
	else if (viewtypeWeek == m_eViewType)
	{
		DrawWeekView(dc);
	}
	else if (viewtypeDay== m_eViewType)
	{
		DrawDayView(dc);
	}
	else
	{
		ATLASSERT(FALSE);
	}
	//
	DrawAllEvents(dc);
}

void CWizCalendarView::SetView(WizCalendarViewType eView)
{
	if (m_eViewType == eView)
		return;
	//
	m_eViewType = eView;
	if (!IsWindow())
		return;
	//
	if (viewtypeMonth == m_eViewType)
	{
		MonthViewResetCurrentMonth();
	}
	//
	Resize();
	//
	ResetEvents();
	//
	Invalidate();
	//
	OnViewChanged(m_eViewType);
}

BOOL CWizCalendarView::SetSelectedTime(const COleDateTime& t, BOOL bNotifyChanged /*= FALSE*/)
{
	if (m_tSelected == t)
		return TRUE;
	//
	COleDateTime tOldStart;
	COleDateTime tOldEnd;
	GetTimeRange(tOldStart, tOldEnd);
	//
	m_tSelected = t;
	//
	if (viewtypeMonth == m_eViewType)
	{
		MonthViewResetCurrentMonth();
	}
	//
	COleDateTime tNewStart;
	COleDateTime tNewEnd;
	GetTimeRange(tNewStart, tNewEnd);
	//
	if (tNewStart != tOldStart
		|| tNewEnd != tOldEnd)
	{
		ResetEvents();
	}
	//
	if (!IsWindow())
		return TRUE;
	//
	EnsureSelectedTimeVisible();
	//
	Invalidate();
	//
	if (bNotifyChanged)
	{
		OnTimeChanged(m_tSelected);
	}
	//
	return TRUE;
}

BOOL CWizCalendarView::SetSelectedEvent(const WIZCALENDAREVENTDATA& e)
{
	if (m_eventSelected.strGUID == e.strGUID)
		return TRUE;
	//
	m_eventSelected = e;
	//
	Invalidate();
	//
	if (m_pEvents)
	{
		m_pEvents->WCV_OnEventChanged(m_eventSelected);
	}
	//
	return TRUE;
}

void CWizCalendarView::EnsureSelectedTimeVisible()
{
	if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType)
	{
		ScrollSelectedTimeToView();
	}
}

void CWizCalendarView::ScrollSelectedTimeToView()
{
	ATLASSERT(viewtypeWeek == m_eViewType|| viewtypeDay == m_eViewType);
	//
	CRect rCOleDateTime;
	WeekDayViewGetHalfHourTimeRect(m_tSelected, rCOleDateTime);
	//
	CRect rc;
	GetClientRect(&rc);
	//
	if (rCOleDateTime.top - m_ptOffset.y < HEADER_HEIGHT)
	{
		int nTop = (rCOleDateTime.top - HOUR_HEIGHT) / HOUR_HEIGHT * HOUR_HEIGHT;

		SetScrollOffset(0, nTop);
	}
	else if (rCOleDateTime.bottom - m_ptOffset.y > rc.Height())
	{
		int nTop = (rCOleDateTime.bottom - rc.Height()) / HOUR_HEIGHT * HOUR_HEIGHT + HOUR_HEIGHT;

		SetScrollOffset(0, nTop);
	}
}

COleDateTime CWizCalendarView::GetSelectedTime()
{
	return m_tSelected;
}

void CWizCalendarView::ResetEvents()
{
	m_arrayEvent.clear();
	//
	if (m_pProvider)
	{
		COleDateTime tStart;
		COleDateTime tEnd;
		GetTimeRange(tStart, tEnd);
		//
		CWizCalendarEventArray events;
		m_pProvider->GetEvents(tStart, tEnd, events);
		//
		m_arrayEvent.assign(events.begin(), events.end());
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
}

BOOL CWizCalendarView::MonthViewGetNavigatorTextRect(int y, RECT& rc)
{
	ATLASSERT(viewtypeMonth == m_eViewType);
	//
	CRect rcClient;
	GetClientRect(&rcClient);
	//
	int nNavigatorWidth = GetMonthViewNavigatorWidth();
	//
	int nCellHeight = (rcClient.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
	//
	rc.left = 0;
	rc.right = nNavigatorWidth;
	rc.top = HEADER_HEIGHT + nCellHeight * y;
	rc.bottom = rc.top + nCellHeight;
	//
	return TRUE;
}

BOOL CWizCalendarView::GetHeaderTextRect(int nIndex, RECT& rc)
{
	if (viewtypeMonth == m_eViewType)
	{
		ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
		if (nIndex < 0 || nIndex >= WIZ_CALENDAR_WEEK_DAY_COUNT)
			return FALSE;
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nCellWidth = rcClient.Width() / WIZ_CALENDAR_WEEK_DAY_COUNT;
		//
		rc.left = nIndex * nCellWidth;
		rc.right = rc.left + nCellWidth;
		rc.top = 0;
		rc.bottom = HEADER_HEIGHT;
		//
		return TRUE;
	}
	else if (viewtypeWeek == m_eViewType)
	{
		ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
		if (nIndex < 0 || nIndex >= WIZ_CALENDAR_WEEK_DAY_COUNT)
			return FALSE;
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nCellWidth = (rcClient.Width() - TIME_WIDTH) / WIZ_CALENDAR_WEEK_DAY_COUNT;
		//
		rc.left = TIME_WIDTH + nIndex * nCellWidth;
		rc.right = rc.left + nCellWidth;
		rc.top = m_ptOffset.y;
		rc.bottom = HEADER_HEIGHT + rc.top;
		//
		return TRUE;
	}
	else if (viewtypeDay == m_eViewType)
	{
		ATLASSERT(nIndex == 0);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		rc.left = 0;
		rc.right = rcClient.Width();
		rc.top = 0;
		rc.bottom = HEADER_HEIGHT;
		//
		return TRUE;
	}
	else
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
}
BOOL CWizCalendarView::GetHourTextRect(int nHour, RECT& rc)
{
	if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType)
	{
		ATLASSERT(nHour >= 0 && nHour < WIZ_CALENDAR_HOUR_COUNT);
		//
		if (nHour < 0 || nHour >= WIZ_CALENDAR_HOUR_COUNT)
			return FALSE;
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		rc.left = 0;
		rc.top = HEADER_HEIGHT + nHour * HALF_HOUR_HEIGHT * 2;
		rc.right = rc.left + TIME_WIDTH;
		rc.bottom = rc.top + HALF_HOUR_HEIGHT * 2;
		//
		return TRUE;
	}
	else
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
}

BOOL CWizCalendarView::MonthViewGetCellRect(int x, int y, RECT& rc)
{
	ATLASSERT(viewtypeMonth == m_eViewType);

	ATLASSERT(x >= 0 && x < WIZ_CALENDAR_WEEK_DAY_COUNT);
	ATLASSERT(y >= 0 && y < MONTH_VIEW_ROW_COUNT);
	//
	CRect rcClient;
	GetClientRect(&rcClient);
	//
	int nNavigatorWidth = GetMonthViewNavigatorWidth();
	//
	int nCellWidth = (rcClient.Width() - nNavigatorWidth) / WIZ_CALENDAR_WEEK_DAY_COUNT;
	int nCellHeight = (rcClient.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
	//
	rc.left = nNavigatorWidth + x * nCellWidth;
	rc.right = rc.left + nCellWidth;
	rc.top = HEADER_HEIGHT + y * nCellHeight;
	rc.bottom = rc.top + nCellHeight;
	//
	return TRUE;
}

int CWizCalendarView::WeekViewGetDayIndexOfWeekView(const COleDateTime& t)
{
	ATLASSERT(viewtypeWeek == m_eViewType);
	//
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tSelected.GetDayOfWeek());
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	COleDateTime tTemp(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
	COleDateTime tSelected(m_tSelected.GetYear(), m_tSelected.GetMonth(), m_tSelected.GetDay(), 0, 0, 0); 
	//
	COleDateTimeSpan ts = tTemp - tSelected;
	int nDays = (int)ts.GetDays();
	//
	int nNewIndex = nIndex + nDays;
	if (nNewIndex < 0 || nNewIndex >= WIZ_CALENDAR_WEEK_DAY_COUNT)
	{
		return -1;
	}
	//
	return nNewIndex;
}

BOOL CWizCalendarView::MonthViewGetRowRect(int nRow, RECT& rc)
{
	ATLASSERT(viewtypeMonth == m_eViewType);
	ATLASSERT(nRow >= 0 && nRow < MONTH_VIEW_ROW_COUNT);
	//
	CRect rcClient;
	GetClientRect(&rcClient);
	//
	int nCellHeight = (rcClient.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
	//
	rc.left = rcClient.left + GetMonthViewNavigatorWidth();
	rc.right = rcClient.right;
	rc.top = HEADER_HEIGHT + nRow * nCellHeight;
	rc.bottom = rc.top + nCellHeight;
	//
	return TRUE;

}

BOOL CWizCalendarView::GetDayRect(const COleDateTime& t, RECT& rc)
{
	if (viewtypeMonth == m_eViewType)
	{
		COleDateTime tTemp(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
		COleDateTime tFirstDayOfMonth(m_tMonthViewCurrentMonth.GetYear(), m_tMonthViewCurrentMonth.GetMonth(), 1, 0, 0, 0); 
		int nIndex = IndexOfDayOfWeek(tFirstDayOfMonth.GetDayOfWeek());
		//
		ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
		//
		COleDateTimeSpan ts = tTemp - tFirstDayOfMonth;
		int nDays = (int)ts.GetDays();
		//
		int nAllIndex = nIndex + nDays;
		//
		if (nAllIndex < 0 || nAllIndex >= WIZ_CALENDAR_WEEK_DAY_COUNT * MONTH_VIEW_ROW_COUNT)
			return FALSE;
		//
		int x = nAllIndex / WIZ_CALENDAR_WEEK_DAY_COUNT;
		int y = nAllIndex % WIZ_CALENDAR_WEEK_DAY_COUNT;
		//
		ATLASSERT(x >= 0 && x < WIZ_CALENDAR_WEEK_DAY_COUNT);
		ATLASSERT(y >= 0 && y < MONTH_VIEW_ROW_COUNT);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nCellWidth = rcClient.Width() / WIZ_CALENDAR_WEEK_DAY_COUNT;
		int nCellHeight = (rcClient.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
		//
		rc.left = x * nCellWidth;
		rc.right = rc.left + nCellWidth;
		rc.top = HEADER_HEIGHT + y * nCellHeight;
		rc.bottom = rc.top + nCellHeight;
		//
		return TRUE;
	}
	else if (viewtypeWeek == m_eViewType)
	{
		int nIndex = WeekViewGetDayIndexOfWeekView(t);
		//
		ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nCellWidth = (rcClient.Width() - TIME_WIDTH) / WIZ_CALENDAR_WEEK_DAY_COUNT;
		//
		rc.left = TIME_WIDTH + nIndex * nCellWidth;
		rc.right = rc.left + nCellWidth;
		rc.top = 0;
		rc.bottom = HEADER_HEIGHT + HALF_WIZ_CALENDAR_HOUR_COUNT * HALF_HOUR_HEIGHT;
		//
		return TRUE;
	}
	else if (viewtypeDay == m_eViewType)
	{
		ATLASSERT(t.GetYear() == m_tSelected.GetYear()
			&& t.GetMonth() == m_tSelected.GetMonth()
			&& t.GetDay() == m_tSelected.GetDay());
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		rc.left = TIME_WIDTH;
		rc.right = rc.right;
		rc.top = 0;
		rc.bottom = HEADER_HEIGHT + HALF_WIZ_CALENDAR_HOUR_COUNT * HALF_HOUR_HEIGHT;
		//
		return TRUE;
	}
	else
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
}

BOOL CWizCalendarView::WeekDayViewGetHalfHourTimeRect(const COleDateTime& t, RECT& rc)
{
	if (viewtypeWeek == m_eViewType)
	{
		int nIndex = WeekViewGetDayIndexOfWeekView(t);
		//
		ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nCellWidth = (rcClient.Width() - TIME_WIDTH) / WIZ_CALENDAR_WEEK_DAY_COUNT;
		//
		int nHour = t.GetHour();
		int nMinute = t.GetMinute();
		//
		int nTimeIndex = nHour * 2 + (nMinute >= 30 ? 1 : 0);
		//
		rc.left = TIME_WIDTH + nIndex * nCellWidth;
		rc.right = rc.left + nCellWidth;
		rc.top = HEADER_HEIGHT + nTimeIndex * HALF_HOUR_HEIGHT;
		rc.bottom = rc.top + HALF_HOUR_HEIGHT;
		//
		return TRUE;
	}
	else if (viewtypeDay == m_eViewType)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		int nHour = t.GetHour();
		int nMinute = t.GetMinute();
		//
		int nTimeIndex = nHour * 2 + (nMinute >= 30 ? 1 : 0);
		//
		rc.left = TIME_WIDTH;
		rc.right = rcClient.right - 1;
		rc.top = HEADER_HEIGHT + nTimeIndex * HALF_HOUR_HEIGHT;
		rc.bottom = rc.top + HALF_HOUR_HEIGHT;
		//
		return TRUE;
	}
	else
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
}
int CWizCalendarView::IndexOfDayOfWeek(int nDayOfWeek)
{
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		if (m_arrayDayOfWeek[i] == nDayOfWeek)
		{
			return i;
		}
	}
	//
	ATLASSERT(FALSE);
	return 0;
}


COleDateTime CWizCalendarView::MonthViewGetCellTime(int x, int y)
{
	ATLASSERT(viewtypeMonth == m_eViewType);
	//
	ATLASSERT(x >= 0 && x < WIZ_CALENDAR_WEEK_DAY_COUNT);
	ATLASSERT(y >= 0 && y < MONTH_VIEW_ROW_COUNT);
	//
	COleDateTime tFirstDayOfMonth(m_tMonthViewCurrentMonth.GetYear(), m_tMonthViewCurrentMonth.GetMonth(), 1, 0, 0, 0); 
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(tFirstDayOfMonth.GetDayOfWeek());
	//
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	int nDays = y * WIZ_CALENDAR_WEEK_DAY_COUNT + x - nIndex;
	//
	COleDateTimeSpan ts(nDays, 0, 0, 0);
	COleDateTime t = tFirstDayOfMonth + ts;
	return WizTimeBuildTime(t, m_tSelected);
}

void CWizCalendarView::DrawMonthView(CDCHandle dc)
{
	ATLASSERT(viewtypeMonth == m_eViewType);
	//
	dc.SelectPen(m_penLine);
	//
	CRect rc;
	GetClientRect(&rc);
	//
	int nNavigatorWidth = GetMonthViewNavigatorWidth();
	//
	int nCellWidth = (rc.Width() - nNavigatorWidth) / WIZ_CALENDAR_WEEK_DAY_COUNT;
	int nCellHeight = (rc.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
	//
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		int x = nNavigatorWidth + i * nCellWidth;
		int y = 0;
		dc.MoveTo(x, y);
		dc.LineTo(x, rc.Height());
	}
	//
	for (int i = 0; i < MONTH_VIEW_ROW_COUNT; i++)
	{
		int x = 0;
		int y = HEADER_HEIGHT + i * nCellHeight;
		dc.MoveTo(x, y);
		dc.LineTo(rc.Width(), y);
	}
	//
	dc.SelectFont(m_fontText);
	BOOL bLongName = rc.Width() > 500;
	//
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		RECT rcHeader;
		GetHeaderTextRect(i, rcHeader);
		//
		if (bLongName)
		{
			dc.DrawText(m_arrayDayOfWeekLongName[i], -1, &rcHeader, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}
		else
		{
			dc.DrawText(m_arrayDayOfWeekShortName[i], -1, &rcHeader, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}
	}
	//
	for (int i = 0; i < MONTH_VIEW_ROW_COUNT; i++)
	{
		RECT rcNavigator;
		MonthViewGetNavigatorTextRect(i, rcNavigator);
		//
		dc.DrawText(GetNavigatorText(i), -1, &rcNavigator, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	}
	//
	for (int x = 0; x < WIZ_CALENDAR_WEEK_DAY_COUNT; x++)
	{
		for (int y = 0; y < MONTH_VIEW_ROW_COUNT; y++)
		{
			COleDateTime t = MonthViewGetCellTime(x, y);
			//
			CRect rcCell;
			MonthViewGetCellRect(x, y, rcCell);
			//
			DrawMonthCell(dc, t, rcCell);
		}
	}
}

void CWizCalendarView::DrawWeekView(CDCHandle dc)
{
	ATLASSERT(viewtypeWeek == m_eViewType);
	//
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tSelected.GetDayOfWeek());
	//
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	//
	COleDateTime tStart = m_tSelected - COleDateTimeSpan(nIndex, 0, 0, 0);
	//
	CRect rc;
	GetClientRect(&rc);
	//
	int nCellWidth = (rc.Width() - TIME_WIDTH) / WIZ_CALENDAR_WEEK_DAY_COUNT;
	int nCellHeight = HALF_HOUR_HEIGHT;
	int nCellCount = HALF_WIZ_CALENDAR_HOUR_COUNT;
	int nHeight = nCellHeight * HALF_WIZ_CALENDAR_HOUR_COUNT + HEADER_HEIGHT;
	//
	dc.SelectPen(m_penSelectedBorder);
	dc.SelectBrush(m_brushSelectedLighter);
	//
	CRect rcSelected(TIME_WIDTH + nIndex * nCellWidth, 0, TIME_WIDTH + nIndex * nCellWidth + nCellWidth + 1, nHeight + 1);
	dc.Rectangle(&rcSelected);
	//
	CRect rcFullHeader(0, m_ptOffset.y, rc.Width(), m_ptOffset.y + HEADER_HEIGHT);
	//
	dc.SelectPen(m_penLine);
	//
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		int x = TIME_WIDTH + i * nCellWidth;
		int y = 0;
		dc.MoveTo(x, y);
		dc.LineTo(x, nHeight);
	}
	//
	dc.MoveTo(rcFullHeader.left, rcFullHeader.bottom);
	dc.LineTo(rcFullHeader.right, rcFullHeader.bottom);
	//
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		int x = 0;
		int y = HEADER_HEIGHT + i * nCellHeight * 2;
		//
		if (y >= rcFullHeader.bottom)
		{
			dc.MoveTo(x, y);
			dc.LineTo(rc.Width(), y);
		}
	}
	//
	dc.SelectPen(m_penLineLighter);
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		int x = TIME_WIDTH;
		int y = HEADER_HEIGHT + i * nCellHeight * 2 + nCellHeight;
		//
		if (y >= rcFullHeader.bottom)
		{
			dc.MoveTo(x, y);
			dc.LineTo(rc.Width(), y);
		}
	}
	//
	dc.SelectFont(m_fontText);
	//
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		COleDateTime tCurr = tStart + COleDateTimeSpan(i, 0, 0, 0);
		//
		SYSTEMTIME st;
		tCurr.GetAsSystemTime(st);
		//
		TCHAR szDate[MAX_PATH] = {0};
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &st, NULL, szDate, MAX_PATH);
		//
		CString strText;
		CString strSecondCalendarText = GetSecondCalendarDateText(tCurr, TRUE);
		strText = WizFormatString3(_T("%1\n%2\n%3"), szDate, m_arrayDayOfWeekLongName[i], strSecondCalendarText);
		strText.Trim();
		//
		CRect rcHeader;
		GetHeaderTextRect(i, rcHeader);
		//
		CRect rcTemp = rcHeader;
		int nTextHeight = dc.DrawText(strText, -1, &rcTemp, DT_CENTER | DT_CALCRECT);
		rcHeader.top = rcHeader.top + (rcHeader.Height() - nTextHeight) / 2;
		//
		dc.DrawText(strText, -1, &rcHeader, DT_CENTER);
	}
	//
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		CRect rcHour;
		GetHourTextRect(i, rcHour);
		//
		if (rcHour.top >= rcFullHeader.bottom)
		{
			rcHour.DeflateRect(3, 3);
			dc.DrawText(m_arrayHour[i], -1, &rcHour, DT_RIGHT);
		}
	}
	//
	CRect rCOleDateTime;
	if (WeekDayViewGetHalfHourTimeRect(m_tSelected, rCOleDateTime))
	{
		if (rCOleDateTime.top - m_ptOffset.y >= HEADER_HEIGHT)
		{
			rCOleDateTime.right++;
			rCOleDateTime.bottom++;
			//
			dc.SelectPen(m_penSelectedBorder);
			dc.SelectBrush(m_brushSelected);
			//
			dc.Rectangle(&rCOleDateTime);
		}
	}
}

void CWizCalendarView::DrawDayView(CDCHandle dc)
{
	ATLASSERT(viewtypeDay == m_eViewType);
	//
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tSelected.GetDayOfWeek());
	//
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	//
	CRect rc;
	GetClientRect(&rc);
	//
	int nCellWidth = rc.Width() - TIME_WIDTH;
	int nCellHeight = HALF_HOUR_HEIGHT;
	int nCellCount = HALF_WIZ_CALENDAR_HOUR_COUNT;
	int nHeight = nCellHeight * HALF_WIZ_CALENDAR_HOUR_COUNT + HEADER_HEIGHT;
	//
	dc.SelectPen(m_penSelectedBorder);
	dc.SelectBrush(m_brushSelectedLighter);
	//
	dc.SelectPen(m_penLine);
	//
	CRect rcHeader(0, m_ptOffset.y, rc.Width(), m_ptOffset.y + HEADER_HEIGHT);
	dc.MoveTo(rcHeader.left, rcHeader.bottom);
	dc.LineTo(rcHeader.right, rcHeader.bottom);
	//
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		int x = 0;
		int y = HEADER_HEIGHT + i * nCellHeight * 2;
		//
		if (y >= rcHeader.bottom)
		{
			dc.MoveTo(x, y);
			dc.LineTo(rc.Width(), y);
		}
	}
	//
	dc.SelectPen(m_penLineLighter);
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		int x = TIME_WIDTH;
		int y = HEADER_HEIGHT + i * nCellHeight * 2 + nCellHeight;
		//
		if (y >= rcHeader.bottom)
		{
			dc.MoveTo(x, y);
			dc.LineTo(rc.Width(), y);
		}
	}
	//
	dc.SelectFont(m_fontText);
	//
	SYSTEMTIME st;
	m_tSelected.GetAsSystemTime(st);
	//
	TCHAR szDate[MAX_PATH] = {0};
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &st, NULL, szDate, MAX_PATH);
	//
	CString strText;
	//
	CString strSecondCalendarText = GetSecondCalendarDateText(m_tSelected, TRUE);
	if(strSecondCalendarText.IsEmpty())
	{
		strText = WizFormatString2(_T("%1\n%2"),szDate, m_arrayDayOfWeekLongName[nIndex]);
	}
	else
	{
		strText = WizFormatString3(_T("%1 %2\n%3"),szDate, m_arrayDayOfWeekLongName[nIndex], strSecondCalendarText);
	}
	//
	CRect rcTemp = rcHeader;
	int nTextHeight = dc.DrawText(strText, -1, &rcTemp, DT_CENTER | DT_CALCRECT);
	rcHeader.top = rcHeader.top + (rcHeader.Height() - nTextHeight) / 2;
	//
	dc.DrawText(strText, -1, &rcHeader, DT_CENTER);
	//
	for (int i = 0; i < WIZ_CALENDAR_HOUR_COUNT; i++)
	{
		CRect rcHour;
		GetHourTextRect(i, rcHour);
		//
		if (rcHour.top >= rcHeader.bottom)
		{
			rcHour.DeflateRect(3, 3);
			dc.DrawText(m_arrayHour[i], -1, &rcHour, DT_RIGHT);
		}
	}
	//
	CRect rCOleDateTime;
	if (WeekDayViewGetHalfHourTimeRect(m_tSelected, rCOleDateTime))
	{
		if (rCOleDateTime.top - m_ptOffset.y >= HEADER_HEIGHT)
		{
			rCOleDateTime.right++;
			rCOleDateTime.bottom++;
			//
			dc.SelectPen(m_penSelectedBorder);
			dc.SelectBrush(m_brushSelected);
			//
			dc.Rectangle(&rCOleDateTime);
		}
	}
}

void CWizCalendarView::DrawMonthCell(CDCHandle dc, const COleDateTime& t, const CRect& rcCell)
{
	int nSelectedMonth = m_tSelected.GetMonth();
	int nSelectedDay = m_tSelected.GetDay();
	//
	int nCurrentMonth = m_tMonthViewCurrentMonth.GetMonth();
	//
	int nDay = t.GetDay();
	int nMonth = t.GetMonth();
	//
	dc.SetTextColor(nCurrentMonth == nMonth ? g_crCurrentMonthTextColor : g_crNotCurrentMonthTextColor);
	//
	CRect rcFill = rcCell;
	rcFill.left++;
	rcFill.top++;
	rcFill.InflateRect(1, 1);
	if (nSelectedMonth == nMonth 
		&& nSelectedDay == nDay)
	{
		dc.SelectPen(m_penSelectedBorder);
		dc.SelectBrush(m_brushSelected);
		dc.Rectangle(&rcFill);
	}
	else if (nCurrentMonth == nMonth)
	{
		dc.SelectPen(m_penSelectedBorder);
		dc.SelectBrush(m_brushCurrentMonth);
		dc.Rectangle(&rcFill);
	}
	//
	int nOldTextColor = dc.GetTextColor();
	//
	int nDayOfWeek = t.GetDayOfWeek();
	 if (7 == nDayOfWeek	//÷‹¡˘
		|| 1 == nDayOfWeek)		//÷‹»’
	{
		dc.SetTextColor(RGB(255, 0, 0));
	}
	else if (t.GetDay() == 1)
	{
		dc.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}
	//
	CString strDay = WizIntToStr(nDay);
	CString strDay2 = GetSecondCalendarDateText(t, FALSE);
	if (!strDay2.IsEmpty())
		strDay = strDay + _T(" (") + strDay2 + _T(")");
	//
	CRect rcCellText = rcCell;
	rcCellText.DeflateRect(3, 2);
	HFONT hOldFont = dc.SelectFont(m_fontMonthViewDay);
	dc.DrawText(strDay, -1, &rcCellText, DT_RIGHT | DT_SINGLELINE);
	dc.SelectFont(hOldFont);
	dc.SetTextColor(nOldTextColor);
	//
	CSize szDay;
	dc.GetTextExtent(strDay, -1, &szDay);
	//
	/*
	CRect rcSecondCalendarText = rcCellText;
	rcSecondCalendarText.right -= szDay.cx;
	rcSecondCalendarText.right -= 8;
	//
	dc.DrawText(GetSecondCalendarDateText(t, FALSE), -1, rcSecondCalendarText, DT_LEFT | DT_SINGLELINE);
	*/
	//
	CRect rcBackgroundText = rcCell;
	rcBackgroundText.DeflateRect(3, 3);
	rcBackgroundText.top += (szDay.cx + 8);
	//
	CString strBackgroundText = GetMonthViewBackgroundText(t);
	if (!strBackgroundText.IsEmpty())
	{
		dc.SetTextColor(GetSysColor(COLOR_BTNSHADOW));
		dc.DrawText(strBackgroundText, -1, &rcBackgroundText, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
	}
	//

}

void CWizCalendarView::Resize()
{
	CRect rc;
	GetClientRect(&rc);

	int cx = rc.Width();
	int cy = rc.Height();
	//
	if (viewtypeMonth == m_eViewType)
	{
		if (cx <= 0)
			cx = 1;
		if (cy <= 0)
			cy = 1;
		//
		SetScrollSize(cx, cy);
	}
	else if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType
		)
	{
		if (cx <= 0)
			cx = 1;
		if (cy <= 0)
			cy = 1;
		//
		if (cy <= HEADER_HEIGHT)
			return;
		//
		int nHeight = HEADER_HEIGHT + HOUR_HEIGHT * WIZ_CALENDAR_HOUR_COUNT;
		//
		int nExtra = (cy - HEADER_HEIGHT) % HOUR_HEIGHT;
		ATLASSERT(nExtra >= 0);
		//
		SetScrollSize(cy, nHeight + nExtra, TRUE, false);
		//
		m_sizePage.cy = (cy - HEADER_HEIGHT) / HOUR_HEIGHT * HOUR_HEIGHT;
		if (0 == m_sizePage.cy)
		{
			m_sizePage.cy = 1;
		}
		m_sizeLine.cy = HOUR_HEIGHT;
		//
		ScrollSelectedTimeToView();
	}
}


LRESULT CWizCalendarView::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	Resize();
	//
	return 0;
}

LRESULT CWizCalendarView::OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	if (viewtypeMonth == m_eViewType)
	{
		switch ((UINT)wParam)
		{
		case VK_LEFT:
			SetSelectedTime(m_tSelected - COleDateTimeSpan(1, 0, 0, 0), TRUE);
			return 0;
		case VK_RIGHT:
			SetSelectedTime(m_tSelected + COleDateTimeSpan(1, 0, 0, 0), TRUE);
			return 0;
		case VK_UP:
			SetSelectedTime(m_tSelected - COleDateTimeSpan(WIZ_CALENDAR_WEEK_DAY_COUNT, 0, 0, 0), TRUE);
			return 0;
		case VK_DOWN:
			SetSelectedTime(m_tSelected + COleDateTimeSpan(WIZ_CALENDAR_WEEK_DAY_COUNT, 0, 0, 0), TRUE);
			return 0;
		}
	}
	else if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType)
	{
		switch ((UINT)wParam)
		{
		case VK_LEFT:
			SetSelectedTime(m_tSelected - COleDateTimeSpan(1, 0, 0, 0), TRUE);
			return 0;
		case VK_RIGHT:
			SetSelectedTime(m_tSelected + COleDateTimeSpan(1, 0, 0, 0), TRUE);
			return 0;
		case VK_UP:
			if (m_tSelected.GetHour() > 0 || m_tSelected .GetMinute() >= 30)
			{
				SetSelectedTime(m_tSelected - COleDateTimeSpan(0, 0, 30, 0), TRUE);
			}
			return 0;
		case VK_DOWN:
			if (m_tSelected.GetHour() < 23 || m_tSelected .GetMinute() < 30)
			{
				SetSelectedTime(m_tSelected + COleDateTimeSpan(0, 0, 30, 0), TRUE);
			}
			return 0;
		}
	}
	//
	return 0;
}
BOOL CWizCalendarView::MonthViewResetCurrentMonth()
{
	if (m_tSelected.GetYear() == m_tMonthViewCurrentMonth.GetYear()
		&& m_tSelected.GetMonth() == m_tMonthViewCurrentMonth.GetMonth())
		return FALSE;
	//
	COleDateTime tFirstDayOfMonth(m_tMonthViewCurrentMonth.GetYear(), m_tMonthViewCurrentMonth.GetMonth(), 1, 0, 0, 0); 
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(tFirstDayOfMonth.GetDayOfWeek());
	//
	int nIndex = -1;
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		if (m_arrayDayOfWeek[i] == nDayOfWeek)
		{
			nIndex = i;
			break;
		}
	}
	ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	COleDateTime tSelected(m_tSelected.GetYear(), m_tSelected.GetMonth(), m_tSelected.GetDay(), 0, 0, 0);
	COleDateTimeSpan ts = tSelected - tFirstDayOfMonth;
	int nDays = (int)ts.GetDays();
	//
	if (nIndex + nDays < 0
		|| nIndex + nDays >= 42)
	{
		m_tMonthViewCurrentMonth = m_tSelected;
		return TRUE;
	}
	//
	return FALSE;
}

BOOL CWizCalendarView::HitTestEvent(POINT pt, WIZCALENDAREVENTDATA& e)
{
	if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType)
	{
		pt.y += m_ptOffset.y;
	}
	//
	intptr_t nIndex = m_arrayEvent.HitTest(pt);
	if (-1 == nIndex)
		return FALSE;
	//
	e = m_arrayEvent[nIndex];
	return TRUE;
}

BOOL CWizCalendarView::HitTest(POINT pt, COleDateTime& t)
{
	CRect rc;
	GetClientRect(&rc);
	//
	if (viewtypeMonth == m_eViewType)
	{
		int nNavigatorWidth = GetMonthViewNavigatorWidth();
		//
		int nCellWidth = (rc.Width() - nNavigatorWidth) / WIZ_CALENDAR_WEEK_DAY_COUNT;
		int nCellHeight = (rc.Height() - HEADER_HEIGHT) / MONTH_VIEW_ROW_COUNT;
		//
		if (pt.x < nNavigatorWidth || pt.x > rc.Width())
			return FALSE;
		//
		if (pt.y < HEADER_HEIGHT || pt.y > rc.Height())
			return FALSE;
		//
		if (0 == nCellWidth)
			return FALSE;
		if (0 == nCellHeight)
			return FALSE;
		//
		int x = (pt.x - nNavigatorWidth) / nCellWidth;
		int y = (pt.y - HEADER_HEIGHT) / nCellHeight;
		if (x >= WIZ_CALENDAR_WEEK_DAY_COUNT)
			x = WIZ_CALENDAR_WEEK_DAY_COUNT - 1;
		if (y >= MONTH_VIEW_ROW_COUNT)
			y = MONTH_VIEW_ROW_COUNT - 1;
		//
		ATLASSERT(x >= 0 && x < WIZ_CALENDAR_WEEK_DAY_COUNT);
		ATLASSERT(y >= 0 && y < MONTH_VIEW_ROW_COUNT);
		//
		t = MonthViewGetCellTime(x, y);
		//
		return TRUE;
	}
	else if (viewtypeWeek == m_eViewType)
	{
		int nCellWidth = (rc.Width() - TIME_WIDTH) / WIZ_CALENDAR_WEEK_DAY_COUNT;
		int nCellHeight = HALF_HOUR_HEIGHT;
		//
		if (nCellWidth <= 0)
			return FALSE;
		if (nCellHeight <= 0)
			return FALSE;
		//
		if (pt.x <= TIME_WIDTH)
			pt.x = TIME_WIDTH + 1;
		//
		if (pt.y <= HEADER_HEIGHT)
			pt.y = HEADER_HEIGHT + 1;
		//
		int x = (pt.x - TIME_WIDTH) / nCellWidth;
		int y = (pt.y + m_ptOffset.y - HEADER_HEIGHT) / nCellHeight;
		//
		int nHour = y / 2;
		int nMinute = y % 2 ? 30 : 0;
		//
		int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tSelected.GetDayOfWeek());
		int nIndex = IndexOfDayOfWeek(nDayOfWeek);
		//
		COleDateTime tStart = m_tSelected - COleDateTimeSpan(nIndex, 0, 0, 0);
		//
		COleDateTime tTemp = tStart + COleDateTimeSpan(x, 0, 0, 0);
		t = COleDateTime(tTemp.GetYear(), tTemp.GetMonth(), tTemp.GetDay(), nHour, nMinute, 0);
		//
		return TRUE;
	}
	else if (viewtypeDay == m_eViewType)
	{
		CRect rc;
		GetClientRect(&rc);
		//
		int nCellHeight = HALF_HOUR_HEIGHT;
		//
		if (nCellHeight <= 0)
			return FALSE;
		//
		if (pt.x <= TIME_WIDTH)
			pt.x = TIME_WIDTH + 1;
		//
		if (pt.y <= HEADER_HEIGHT)
			pt.y = HEADER_HEIGHT + 1;
		//
		int y = (pt.y + m_ptOffset.y - HEADER_HEIGHT) / nCellHeight;
		//
		int nHour = y / 2;
		if (nHour >= 24)
			nHour = 23;
		//
		int nMinute = y % 2 ? 30 : 0;
		//
		t = COleDateTime(m_tSelected.GetYear(), m_tSelected.GetMonth(), m_tSelected.GetDay(), nHour, nMinute, 0);
		//
		return TRUE;
	}
	//
	return FALSE;
}

LRESULT CWizCalendarView::OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	//
	AutoSelect(pt);
	//
	SetFocus();
	//
	bHandled = FALSE;

	return 0;
}


LRESULT CWizCalendarView::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	//
	AutoSelect(pt);
	//
	SetFocus();

	return 0;
}
void CWizCalendarView::AutoSelect(POINT pt)
{
	COleDateTime t;
	if (!HitTest(pt, t))
		return;
	//
	WIZCALENDAREVENTDATA e;
	HitTestEvent(pt, e);
	//
	SetSelectedTime(t, TRUE);
	SetSelectedEvent(e);
	//
	if (viewtypeMonth == m_eViewType)
	{
		if (-1 != m_arrayMonthViewMoreEventLinkRectArray.HitTest(pt))
		{
			SetView(viewtypeDay);
		}
	}
}

BOOL CWizCalendarView::GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo)
{
	ATLASSERT(::IsWindow(m_hWnd));
	BOOL b = ATL::CWindowImpl<CWizCalendarView, CWindow, ATL::CControlWinTraits>::GetScrollInfo(nBar, lpScrollInfo);
	//
	if (nBar == SB_VERT)
	{
		if (lpScrollInfo->fMask & SIF_TRACKPOS)
		{
			if (viewtypeWeek == m_eViewType
				|| viewtypeDay == m_eViewType)
			{
				int nPos = lpScrollInfo->nTrackPos;
				int nMinPos = nPos / HOUR_HEIGHT * HOUR_HEIGHT;
				int nMaxPos = nPos / HOUR_HEIGHT * HOUR_HEIGHT + HOUR_HEIGHT;
				//
				if (nPos - nMinPos > nMaxPos - nPos)
				{
					lpScrollInfo->nTrackPos = nMaxPos;
				}
				else
				{
					lpScrollInfo->nTrackPos = nMinPos;
				}
			}
		}
	}
	return b;
}
int CWizCalendarView::ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll /*= NULL*/, LPCRECT lpRectClip /*= NULL*/, HRGN hRgnUpdate /*= NULL*/, LPRECT lpRectUpdate /*= NULL*/) throw()
{
	ATLASSERT(::IsWindow(m_hWnd));
	//
	if (viewtypeWeek == m_eViewType
		|| viewtypeDay == m_eViewType)
	{
		Invalidate();
		return TRUE;
	}
	else
	{
		return ATL::CWindowImpl<CWizCalendarView, CWindow, ATL::CControlWinTraits>::ScrollWindowEx(dx, dy, uFlags, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
	}
}
COleDateTime CWizCalendarView::GetStartTime()
{
	if (viewtypeMonth == m_eViewType)
	{
		return MonthViewGetStartTime();
	}
	else if (viewtypeWeek == m_eViewType)
	{
		return WeekViewGetStartTime();
	}
	else if (viewtypeDay== m_eViewType)
	{
		return DayViewGetStartTime();
	}
	else
	{
		ATLASSERT(FALSE);
		return COleDateTime::GetCurrentTime();
	}
}
int CWizCalendarView::GetDayCount()
{
	if (viewtypeMonth == m_eViewType)
	{
		return MonthViewGetDayCount();
	}
	else if (viewtypeWeek == m_eViewType)
	{
		return WeekViewGetDayCount();
	}
	else if (viewtypeDay== m_eViewType)
	{
		return DayViewGetDayCount();
	}
	else
	{
		ATLASSERT(FALSE);
		return 1;
	}
}


void CWizCalendarView::GetTimeRange(COleDateTime& tStart, COleDateTime& tEnd)
{
	tStart = GetStartTime();
	tEnd = tStart + COleDateTimeSpan(GetDayCount() - 1, 23, 59, 59);
}
COleDateTime CWizCalendarView::MonthViewGetStartTime()
{
	ATLASSERT(viewtypeMonth == m_eViewType);
	//
	COleDateTime tFirstDayOfMonth(m_tMonthViewCurrentMonth.GetYear(), m_tMonthViewCurrentMonth.GetMonth(), 1, 0, 0, 0); 
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(tFirstDayOfMonth.GetDayOfWeek());
	//
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	COleDateTimeSpan ts(nIndex, 0, 0, 0);
	COleDateTime t = tFirstDayOfMonth - ts;
	return t;
}
COleDateTime CWizCalendarView::WeekViewGetStartTime()
{
	ATLASSERT(viewtypeWeek == m_eViewType);
	//
	int nDayOfWeek = WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tSelected.GetDayOfWeek());
	//
	int nIndex = IndexOfDayOfWeek(nDayOfWeek);
	ATLASSERT(nIndex >= 0 && nIndex < WIZ_CALENDAR_WEEK_DAY_COUNT);
	//
	COleDateTimeSpan ts(nIndex, 0, 0, 0);
	COleDateTime t = COleDateTime(m_tSelected.GetYear(), m_tSelected.GetMonth(), m_tSelected.GetDay(), 0, 0, 0) - ts;
	return t;
}
COleDateTime CWizCalendarView::DayViewGetStartTime()
{
	ATLASSERT(viewtypeDay == m_eViewType);
	//
	return COleDateTime(m_tSelected.GetYear(), m_tSelected.GetMonth(), m_tSelected.GetDay(), 0, 0, 0);
}
int CWizCalendarView::MonthViewGetDayCount()
{
	return WIZ_CALENDAR_WEEK_DAY_COUNT * MONTH_VIEW_ROW_COUNT;
}
int CWizCalendarView::WeekViewGetDayCount()
{
	return WIZ_CALENDAR_WEEK_DAY_COUNT;
}
int CWizCalendarView::DayViewGetDayCount()
{
	return 1;
}

void CWizCalendarView::DrawAllEvents(CDCHandle dc)
{
	COleDateTime tStart;
	COleDateTime tEnd;
	GetTimeRange(tStart, tEnd);
	//
	ATLASSERT(tEnd >= tStart);
	//
	CWizCalendarEventDataArray events;
	m_arrayEvent.CopyToRange(tStart, tEnd, events);
	m_arrayEvent.ClearRect();
	m_arrayMonthViewMoreEventLinkRectArray.clear();
	//
	if (viewtypeMonth == m_eViewType)
	{
		DrawMonthViewEvents(dc, events);
	}
	else if (viewtypeWeek == m_eViewType)
	{
		DrawWeekViewEvents(dc, events);
	}
	else if (viewtypeDay== m_eViewType)
	{
		DrawDayViewEvents(dc, events);
	}
	else
	{
		ATLASSERT(FALSE);
	}
}
void CWizCalendarView::DrawMonthViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent)
{
	for (int y = 0; y < MONTH_VIEW_ROW_COUNT; y++)
	{
		COleDateTime t = MonthViewGetCellTime(0, y);
		//
		COleDateTime start = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
		COleDateTime end = start + COleDateTimeSpan(WIZ_CALENDAR_WEEK_DAY_COUNT - 1, 23, 59, 59);
		//
		CWizCalendarRowArray arrayRow;
		arrayRow.BuildRowArray(start, end, arrayEvent);
		//
		ATLASSERT(arrayRow.size() == WIZ_CALENDAR_WEEK_DAY_COUNT);
		//
		CRect rcRow;
		if (!MonthViewGetRowRect(y, rcRow))
			continue;
		//
		CSize szText;
		dc.GetTextExtent(_T("1"), 1, &szText);
		rcRow.top += szText.cy;
		//
		int nDayWidth = rcRow.Width() / WIZ_CALENDAR_WEEK_DAY_COUNT;
		for (int iDay = 0; iDay < WIZ_CALENDAR_WEEK_DAY_COUNT; iDay++)
		{
			COleDateTime day_start = start + COleDateTimeSpan(iDay, 0, 0, 0);
			COleDateTime day_end = day_start + COleDateTimeSpan(0, 23, 59, 59);
			//
			const CWizCalendarEventDataArray& events = arrayRow[iDay];
			//
			for (int iEvent = 0; iEvent < (int)events.size(); iEvent++)
			{
				const WIZCALENDAREVENTDATA& e = events[iEvent];
				//
				if (e.IsNull())
					continue;
				//
				int nDaySpan = (int)(e.tEnd - day_start).GetDays() + 1;
				//
				CRect rcEvent;
				rcEvent.left = int(rcRow.left + iDay * nDayWidth);
				rcEvent.right = int(rcEvent.left + nDaySpan * nDayWidth);
				rcEvent.top = int(rcRow.top + iEvent * GetMonthViewEventHeight());
				rcEvent.bottom = int(rcEvent.top + GetMonthViewEventHeight());
				//
				if (rcEvent.bottom > rcRow.bottom)
				{
					CRect rcDay(rcEvent.left, rcRow.top, int(rcEvent.left + nDayWidth), rcRow.bottom);
					DrawMonthViewMoreEvent(dc, rcDay);
					//Draw Link
					break;
				}
				//
				rcEvent.DeflateRect(2, 1);
				//
				if (e.tStart < day_start || e.tStart > day_end)
					continue;
				//
				DrawEvent(dc, rcEvent, e);
			}
		}
	}
}
void CWizCalendarView::DrawMonthViewMoreEvent(CDCHandle dc, CRect& rcDay)
{
	CRect rc = rcDay;
	//
	rc.top = rc.bottom - 9;
	if (rc.Width() > 60)
	{
		rc.left = rc.left + (rc.Width() - 60) / 2;
		rc.right = rc.left + 60;
	}
	//
	WizDrawItemBackgroundBox(dc, rc, GetSysColor(COLOR_WINDOW), 
		RGB(136, 152, 168), RGB(248, 248, 248),
		RGB(248, 248, 248), RGB(224, 232, 240));
	//
	dc.SelectPen(m_penLineDarker);
	CPoint pt = rc.CenterPoint();
	dc.MoveTo(pt.x - 4, pt.y - 2);
	dc.LineTo(pt.x, pt.y + 2);
	dc.LineTo(pt.x + 4, pt.y - 2);
	//
	m_arrayMonthViewMoreEventLinkRectArray.push_back(rc);
}

void CWizCalendarView::DrawWeekViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent)
{
	COleDateTime t = WeekViewGetStartTime();
	for (int i = 0; i < WIZ_CALENDAR_WEEK_DAY_COUNT; i++)
	{
		COleDateTime tDay = t + COleDateTimeSpan(i, 0, 0, 0);
		//
		CRect rcDay;
		if (GetDayRect(tDay, rcDay))
		{
			rcDay.left += 4;
			rcDay.right -= 4;
			DrawDayViewEvents(dc, tDay, rcDay, arrayEvent);
		}
	}
}

void CWizCalendarView::DrawDayViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent)
{
	CRect rc;
	GetClientRect(&rc);
	//
	rc.left += TIME_WIDTH;
	//
	rc.left += 8;
	rc.right -= 8;
	//
	DrawDayViewEvents(dc, m_tSelected, rc, arrayEvent);
}

void CWizCalendarView::DrawDayViewEvents(CDCHandle dc, const COleDateTime& tDay, CRect& rcDay, const CWizCalendarEventDataArray& arrayEvent)
{
	CWizCalendarColumnArray arrayColumn;
	arrayColumn.BuildColumnArray(tDay, arrayEvent);
	//
	size_t nColumnCount = arrayColumn.size();
	if (0 == nColumnCount)
		return;
	//
	int nColumnWidth = rcDay.Width() / (int)nColumnCount;
	//
	for (size_t iColumn = 0; iColumn < nColumnCount; iColumn++)
	{
		const CWizCalendarColumn& column = arrayColumn[iColumn];
		//
		int left = rcDay.left + (int)iColumn * nColumnWidth;
		//
		size_t nEventCount = column.size();
		for (size_t i = 0; i < nEventCount; i++)
		{
			const WIZCALENDAREVENTDATA& e = column[i];
			//
			COleDateTime tStart = e.tStart;
			COleDateTime tEnd = e.tEnd;
			//
			CRect rcEvent;
			rcEvent.left = left;
			rcEvent.top = HEADER_HEIGHT + (e.tStart.GetHour() * 2 + e.tStart.GetMinute() / 30) * HALF_HOUR_HEIGHT;
			rcEvent.right = rcEvent.left + e.nColumnSpan * nColumnWidth;
			rcEvent.bottom = HEADER_HEIGHT + (e.tEnd.GetHour() * 2 + e.tEnd.GetMinute() / 30) * HALF_HOUR_HEIGHT;
			if (e.tEnd.GetMinute() != 0)
				rcEvent.bottom += HALF_HOUR_HEIGHT;
			//
			if (rcEvent.top - m_ptOffset.y < HEADER_HEIGHT)
			{
				rcEvent.top = m_ptOffset.y + HEADER_HEIGHT;
			}
			//
			rcEvent.DeflateRect(2, 0);
			//
			if (rcEvent.top >= rcEvent.bottom)
				continue;
			//
			DrawEvent(dc, rcEvent, e);
		}
	}
}

void CWizCalendarView::DrawEvent(CDCHandle dc, const CRect& rcEvent, const WIZCALENDAREVENTDATA& e)
{
	m_arrayEvent.AddRect(e, rcEvent);
	//
	dc.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	//
	if (e.strGUID == m_eventSelected.strGUID)
	{
		WizDrawItemBackgroundBox(dc, rcEvent, GetSysColor(COLOR_WINDOW), 
			WizColorDarker(e.crBackground, 0.6f), WizColorLighter(e.crBackground, 1.1f),
			e.crBackground, e.crBackground);
		//
		dc.SelectFont(m_fontTextBold);
	}
	else
	{
		WizDrawItemBackgroundBox(dc, rcEvent, GetSysColor(COLOR_WINDOW), 
			WizColorDarker(e.crBackground, 0.6f), WizColorLighter(e.crBackground, 1.1f),
			WizColorLighter(e.crBackground, 1.05f), WizColorDarker(e.crBackground, 0.9f));
		//
		dc.SelectFont(m_fontText);
	}
	//
	CRect rcText = rcEvent;
	rcText.DeflateRect(4, 4);
	//
	dc.DrawText(e.strTitle, -1, &rcText, DT_WORDBREAK);
}


LRESULT CWizCalendarView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	ResetEvents();
	//
	EnsureSelectedTimeVisible();
	//

	return 0;
}

LRESULT CWizCalendarView::OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_pProvider)
		return 0;
	//
	if (m_eventSelected.IsNull())
	{
		m_pProvider->CreateEvent(m_tSelected);
	}
	else
	{
		m_pProvider->EditEvent(m_eventSelected);
	}

	return 0;
}

LRESULT CWizCalendarView::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	if (viewtypeMonth == m_eViewType)
	{
		int zDelta = (int)GET_WHEEL_DELTA_WPARAM(wParam);
		int nLines = zDelta / WHEEL_DELTA;
		//
		COleDateTime t = m_tSelected - COleDateTimeSpan(nLines * 7, 0, 0, 0);
		SetSelectedTime(t, TRUE);
		//
		return 0;
	}
	else
	{
		return CScrollWindowImpl<CWizCalendarView>::OnMouseWheel(uMsg, wParam, lParam, bHandled);
	}
}
CString CWizCalendarView::GetMonthViewBackgroundText(const COleDateTime& t)
{
	return CString();
}
CString CWizCalendarView::GetSecondCalendarDateText(const COleDateTime& t, BOOL bLong)
{
	return CString();
}

void CWizCalendarView::OnTimeChanged(const COleDateTime& t)
{
	if (m_pEvents)
	{
		m_pEvents->WCV_OnTimeChanged(t);
	}
}
void CWizCalendarView::OnViewChanged(WizCalendarViewType eView)
{
	if (m_pEvents)
	{
		m_pEvents->WCV_OnViewChanged(m_eViewType);
	}
}
int CWizCalendarView::GetMonthViewEventHeight()
{
	static int nHeight = 0;
	if (0 == nHeight)
	{
		if (!IsWindow())
			return 24;
		//
		nHeight = WizGetFontHeight(m_hWnd, m_fontText) + 8;
	}
	return nHeight;
}

int CWizCalendarView::GetMonthViewNavigatorWidth()
{
	if (!IsWindow())
		return 20;
	//
	static int nWidth = 0;
	if (0 == nWidth)
	{
		CClientDC dc(m_hWnd);
		//
		CSize sz;
		dc.GetTextExtent(_T("99"), 2, &sz);
		//
		nWidth = sz.cy + 8;
	}
	//
	return nWidth;
}

int GetDayIndexInWeek(const COleDateTime& t)
{
	int nCurrentDay = t.GetDayOfWeek();
	//
	int nFirstDay = WizCOleDateTimeDayOfWeekFromLocalDayOfTime(::WizGetFirstDayOfWeek());
	//
	int index = nCurrentDay - nFirstDay;
	if (index < 0)
		index += 7;
	//
	return index;
}

COleDateTime GetLastDayOfWeek(const COleDateTime& t)
{
	int index = GetDayIndexInWeek(t);
	//
	int nDays = 6 - index;
	//
	return t + COleDateTimeSpan(nDays, 0, 0, 0);
}

COleDateTime CWizCalendarView::GetFirstWeek(const COleDateTime& t)
{
	COleDateTime tWeek = COleDateTime(t.GetYear(), 1, 1, 0, 0, 0);
	return GetLastDayOfWeek(tWeek);
}

int CWizCalendarView::GetWeekNumber(const COleDateTime& t)
{
	COleDateTime tNow = GetLastDayOfWeek(t);
	//
	COleDateTime tStart = GetFirstWeek(tNow);
	//
	COleDateTimeSpan ts = tNow - tStart;
	//
	int nDays = ts.GetDays();
	int nWeeks = nDays / 7 + 1;
	//
	return nWeeks;
}
CString CWizCalendarView::GetNavigatorText(int index)
{
	COleDateTime t = MonthViewGetCellTime(0, index);
	//
	return WizIntToStr(GetWeekNumber(t));
}
