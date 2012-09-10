#pragma once

#include "WizCalendarTagListBox.h"

interface IMonthCalendarViewEvents
{
	virtual void MCV_OnDateChanged(const COleDateTime& t) = 0;
	virtual void MCV_OnTagsChanged(const CWizStdStringArray& arrayTags) = 0;
};


#define IDC_TAGS_LIST_BOX		10000

class CMonthCalendarView
	: public ATL::CWindowImpl< CMonthCalendarView, ATL::CWindow, ATL::CControlWinTraits>
	, public CDoubleBufferImpl<CMonthCalendarView >
{
public:
	DECLARE_WND_CLASS_EX(NULL, 0, -1)
	//
	CMonthCalendarView()
	{
		m_tCurrent = COleDateTime::GetCurrentTime();
		//
		m_pEvents = NULL;
		WizCreateUIFont(m_font);
		//
		LOGFONT lf;
		m_font.GetLogFont(&lf);
		//
		//_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"));
		lf.lfHeight  = -16;
		lf.lfWeight = FW_BOLD;
		m_fontMonth.CreateFontIndirect(&lf);
		//
		//_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"));
		lf.lfHeight  = -16;
		lf.lfWeight = FW_BOLD;
		m_fontWeek.CreateFontIndirect(&lf);
		//
		lf.lfHeight  = -14;
		lf.lfWeight = FW_BOLD;
		m_fontSecond.CreateFontIndirect(&lf);
		//
		_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"));
		if (HasSecondCalendar())
		{
			lf.lfHeight  = -40;
		}
		else
		{
			lf.lfHeight  = -60;
		}
		lf.lfWeight = FW_BOLD;
		m_fontDay.CreateFontIndirect(&lf);

		m_bmpCalc.Attach((HBITMAP)::LoadImage(NULL, WizKMGetSkinsPath() + _T("calendar_back.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	}
private:
	BOOL HasSecondCalendar()
	{
		switch (GetACP())
		{
		case 936:
		case 950:
			return TRUE;
		}
		//
		return FALSE;
	}
	CString GetSecondCalendarString(const COleDateTime& t)
	{
		switch (GetACP())
		{
		case 936:
		case 950:
			return WizChineseCalendarGetMonthDayString(t);
		}
		//
		return CString();
	}

private:
	IMonthCalendarViewEvents* m_pEvents;
public:
	void SetEventsListener(IMonthCalendarViewEvents* pEvents)
	{
		m_pEvents = pEvents;
	}
	//
public:
	CMonthCalendarCtrl m_calendar;
	CFont m_font;
	//
	CFont m_fontMonth;
	CFont m_fontDay;
	CFont m_fontWeek;
	CFont m_fontSecond;
	//
	COleDateTime m_tCurrent;
	//
	CBitmap m_bmpCalc;
	//
	CWizCalendarTagListBox m_tags;

	BEGIN_MSG_MAP(CPaneContainerImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		NOTIFY_CODE_HANDLER(MCN_SELCHANGE, OnCalendarSelChanged)
		COMMAND_HANDLER(IDC_TAGS_LIST_BOX, LBN_SELCHANGE, OnTagsSelChanged)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMonthCalendarView >)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRect rc;
		GetClientRect(&rc);
		//
		CRect rcCalendar = rc;
		//
		m_calendar.Create(m_hWnd, rcCalendar, NULL, WS_CHILD | WS_VISIBLE);
		m_calendar.SetFont(m_font);
		//
		m_tags.SetDatabase(WizGetDatabase());
		m_tags.Create(m_hWnd, NULL, NULL, CWizVistaListBoxExtendedSelect::GetWndStyle(0) | WS_BORDER, 0, IDC_TAGS_LIST_BOX);
		m_tags.ResetTags();
		//m_tags.SetItemHeight(0, ::WizGetFontHeight(m_tags, m_font) + 2);
		//
		UpdateLayout();
		//
		return 0;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}
	//
	int GetMonthCalWidth()
	{
		if (m_calendar.IsWindow())
		{
			CRect rcReq;
			m_calendar.GetMinReqRect(&rcReq);
			return rcReq.Width() + 16;
		}
		//
		return 240;
	}
	int GetMonthCalHeight()
	{
		if (m_calendar.IsWindow())
		{
			CRect rcReq;
			m_calendar.GetMinReqRect(&rcReq);
			return rcReq.Height() + 16;
		}
		//
		return 180;
	}
	//
	int GetMinWidth()
	{
		return GetMonthCalWidth();
	}
	//
	void UpdateLayout()
	{
		CRect rc;
		GetClientRect(&rc);
		//
		CRect rcCalendar = rc;
		//
		if (m_calendar.IsWindow())
		{
			rcCalendar.top = 16;
			rcCalendar.bottom = rcCalendar.top + GetMonthCalHeight();
			//
			if (rcCalendar.Width() < GetMonthCalWidth())
			{
				rcCalendar.right = rcCalendar.left + GetMonthCalWidth();
			}
			//
			m_calendar.SetWindowPos(NULL, &rcCalendar, SWP_NOZORDER);
		}
		//
		CRect rcTags = rc;
		if (m_tags.IsWindow())
		{
			BITMAP bm;
			m_bmpCalc.GetBitmap(&bm);
			rcTags.top = rcCalendar.bottom + bm.bmHeight + 80;
			rcTags.bottom = rcTags.top + 200;
			rcTags.left += 8;
			rcTags.right -= 8;
			//
			if (rcTags.bottom > rc.bottom - 16)
				rcTags.bottom = rc.bottom - 16;
			//
			m_tags.SetWindowPos(NULL, &rcTags, SWP_NOZORDER);
		}
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UpdateLayout();
		Invalidate();
		//
		return 0;
	}

	LRESULT OnTagsSelChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (m_pEvents)
		{
			CWizStdStringArray arrayTag;
			m_tags.GetSelectedTags(arrayTag);
			m_pEvents->MCV_OnTagsChanged(arrayTag);
		}
		return 0;
	}

	void DoPaint( CDCHandle dcPaint )
	{
		CRect rc;
		GetClientRect(&rc);
		dcPaint.FillSolidRect(&rc, ::GetSysColor(COLOR_WINDOW));
		//
		//
		if (m_bmpCalc.IsNull())
			return;
		//
		BITMAP bm;
		m_bmpCalc.GetBitmap(&bm);
		//
		CRect rcCalendar = rc;
		rcCalendar.top = GetMonthCalHeight() + 40;
		rcCalendar.bottom = rcCalendar.top + bm.bmHeight;
		rcCalendar.left = rcCalendar.CenterPoint().x - bm.bmWidth / 2;
		rcCalendar.right = rcCalendar.left + bm.bmWidth;
		//
		CDC dcMem;
		dcMem.CreateCompatibleDC(dcPaint);
		HBITMAP hOldBmp = dcMem.SelectBitmap(m_bmpCalc);
		
		dcPaint.BitBlt(rcCalendar.left, rcCalendar.top, bm.bmWidth, bm.bmHeight, dcMem, 0, 0, SRCCOPY);
		dcMem.SelectBitmap(hOldBmp);
		//
		CString strWeek = WizGetDayOfWeekLongName(WizCOleDateTimeDayOfWeekToLocalDayOfTime(m_tCurrent.GetDayOfWeek()));
		CString strMonth = WizGetMonthShortName(m_tCurrent.GetMonth());
		CString strDay = WizIntToStr(m_tCurrent.GetDay());
		CString strSecond = GetSecondCalendarString(m_tCurrent);
		//
		CRect rcMonth = rcCalendar;
		rcMonth.left += 10;
		rcMonth.top += 2;
		rcMonth.right -= 10;
		rcMonth.bottom = rcMonth.top + 25;
		//
		CRect rcDay = rcMonth;
		rcDay.top = rcMonth.bottom + 10;
		rcDay.bottom = rcDay.top + ::WizGetFontHeight(m_hWnd, m_fontDay);
		//
		CRect rcWeek = rcDay;
		rcWeek.top = rcDay.bottom;
		rcWeek.bottom = rcWeek.top + ::WizGetFontHeight(m_hWnd, m_fontWeek);
		//
		CRect rcSecond = rcWeek;
		rcSecond.top = rcWeek.bottom + 6;
		rcSecond.bottom = rcSecond.top + ::WizGetFontHeight(m_hWnd, m_fontSecond);
		//
		dcPaint.SetBkMode(TRANSPARENT);
		//
		dcPaint.SetTextColor(RGB(255, 255, 255));
		dcPaint.SelectFont(m_fontMonth);
		dcPaint.DrawText(strMonth, -1, &rcMonth, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		//
		dcPaint.SetTextColor(RGB(0, 0, 0));
		dcPaint.SelectFont(m_fontDay);
		dcPaint.DrawText(strDay, -1, &rcDay, DT_SINGLELINE | DT_CENTER | DT_TOP);
		CSize sz;
		dcPaint.GetTextExtent(strDay, -1, &sz);
		//
		dcPaint.SelectFont(m_fontWeek);
		dcPaint.DrawText(strWeek, -1, &rcWeek, DT_SINGLELINE | DT_CENTER | DT_TOP);
		//
		dcPaint.SelectFont(m_fontSecond);
		dcPaint.DrawText(strSecond, -1, &rcSecond, DT_SINGLELINE | DT_CENTER | DT_TOP);
		/*
		//
		//static BOOL bDay = ::WizKMGetPrivateBool(_T("Calendar"), _T("DisplayLargeDay"), FALSE);
		if (bDay)
		{
			dcPaint.SelectFont(m_fontLarge);
			dcPaint.DrawText(strDay, -1, &rcDay, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
		}
		*/
	}
	//
	LRESULT OnCalendarSelChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		NMSELCHANGE* pSel = (NMSELCHANGE *)pnmh;
		if (pSel->stSelStart.wYear < 1980)
			return 0;
		if (pSel->stSelStart.wYear > 2030)
			return 0;
		//
		COleDateTime t(pSel->stSelStart);
		//
		if (m_pEvents)
		{
			m_pEvents->MCV_OnDateChanged(t);
		}
		//
		return 0;
	}
	//
	void SetTime(const COleDateTime& t)
	{
		m_tCurrent = t;
		Invalidate();
	}

};

