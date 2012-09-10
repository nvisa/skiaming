// WizKMCalendarView.h : interface of the CWizKMCalendarView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "WizCalendarEventEx.h"

#define WIZ_CALENDAR_WEEK_DAY_COUNT		7
#define WIZ_CALENDAR_HOUR_COUNT			24

enum WizCalendarViewType 
{
	viewtypeMonth,
	viewtypeWeek,
	viewtypeDay
};

class CWizCalendarColumnArray;
class CWizCalendarRowArray;


interface IWizCalendarViewEvents
{
	virtual void WCV_OnTimeChanged(const COleDateTime& t) = 0;
	virtual void WCV_OnEventChanged(const WIZCALENDAREVENTDATA& e) = 0;
	virtual void WCV_OnViewChanged(WizCalendarViewType eView) = 0;
};

class CWizCalendarView 
	: public CScrollWindowImpl<CWizCalendarView>
{
public:
	CWizCalendarView();
private:
	WizCalendarViewType m_eViewType;
	//
	IWizCalendarViewEvents* m_pEvents;
	//
	CPen m_penLine;
	CPen m_penLineLighter;
	CPen m_penSelectedBorder;
	CPen m_penLineDarker;
	//
	CBrush m_brushCurrentMonth;
	CBrush m_brushSelected;
	CBrush m_brushSelectedLighter;
	//
	CFont m_fontMonthViewDay;
	CFont m_fontText;
	CFont m_fontTextBold;
	//
	int m_arrayDayOfWeek[WIZ_CALENDAR_WEEK_DAY_COUNT];
	CString m_arrayDayOfWeekShortName[WIZ_CALENDAR_WEEK_DAY_COUNT];
	CString m_arrayDayOfWeekLongName[WIZ_CALENDAR_WEEK_DAY_COUNT];
	CString m_arrayHour[WIZ_CALENDAR_HOUR_COUNT];
	//
	COleDateTime m_tSelected;
	COleDateTime m_tMonthViewCurrentMonth;
	//
	WIZCALENDAREVENTDATA m_eventSelected;
	CWizRectArray m_arrayMonthViewMoreEventLinkRectArray;
	//
	CWizCalendayEventProvider* m_pProvider;
	CWizCalendarEventDataArray m_arrayEvent;
public:
	void SetEventProvider(CWizCalendayEventProvider* pProvider);
	CWizCalendayEventProvider* GetEventProvider();
	//
	void SetEventsListener(IWizCalendarViewEvents* pEvents) { m_pEvents = pEvents; }
private:
	BOOL MonthViewResetCurrentMonth();
	int IndexOfDayOfWeek(int nDayOfWeek);
	int WeekViewGetDayIndexOfWeekView(const COleDateTime& t);
	//
	void AutoSelect(POINT pt);
	//
	void Resize();
	//
	int GetMonthViewEventHeight();
public:
	COleDateTime GetSelectedTime();
	BOOL SetSelectedTime(const COleDateTime& t, BOOL bNotifyChanged);
	BOOL SetSelectedEvent(const WIZCALENDAREVENTDATA& e);
	//
	void SetView(WizCalendarViewType eView);
	WizCalendarViewType GetView() const { return m_eViewType; }
	WIZCALENDAREVENTDATA GetSelectedEvent() const { return m_eventSelected; }
	//
	void ResetEvents();
	void ScrollSelectedTimeToView();
	void EnsureSelectedTimeVisible();
public:
	BOOL WeekDayViewGetHalfHourTimeRect(const COleDateTime& t, RECT& rc);
	//
	BOOL GetHeaderTextRect(int nIndex, RECT& rc);
	BOOL GetHourTextRect(int nHour, RECT& rc);
	//
	COleDateTime MonthViewGetCellTime(int x, int y);
	BOOL MonthViewGetCellRect(int x, int y, RECT& rc);
	BOOL MonthViewGetRowRect(int nRow, RECT& rc);
	BOOL MonthViewGetNavigatorTextRect(int y, RECT& rc);
	//
	BOOL GetDayRect(const COleDateTime& t, RECT& rc);
	//
	BOOL HitTest(POINT pt, COleDateTime& t);
	BOOL HitTestEvent(POINT pt, WIZCALENDAREVENTDATA& e);
	//
	COleDateTime GetStartTime();
	int GetDayCount();
	void GetTimeRange(COleDateTime& tStart, COleDateTime& tEnd);
	//
	COleDateTime MonthViewGetStartTime();
	COleDateTime WeekViewGetStartTime();
	COleDateTime DayViewGetStartTime();
	//
	int MonthViewGetDayCount();
	int WeekViewGetDayCount();
	int DayViewGetDayCount();
public:
	BOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo);
	int ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll = NULL, LPCRECT lpRectClip = NULL, HRGN hRgnUpdate = NULL, LPRECT lpRectUpdate = NULL) throw();
protected:
	virtual void DrawMonthView(CDCHandle dc);
	virtual void DrawWeekView(CDCHandle dc);
	virtual void DrawDayView(CDCHandle dc);
	//
	virtual void DrawAllEvents(CDCHandle dc);
	virtual void DrawMonthViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent);
	virtual void DrawWeekViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent);
	virtual void DrawDayViewEvents(CDCHandle dc, const CWizCalendarEventDataArray& arrayEvent);
	virtual void DrawEvent(CDCHandle dc, const CRect& rcEvent, const WIZCALENDAREVENTDATA& e);
	//
	virtual CString GetMonthViewBackgroundText(const COleDateTime& t);
	virtual CString GetSecondCalendarDateText(const COleDateTime& t, BOOL bLong);
	virtual void OnTimeChanged(const COleDateTime& t);
	virtual void OnViewChanged(WizCalendarViewType eView);
	//
	virtual int GetMonthViewNavigatorWidth();

	virtual CString GetNavigatorText(int index);
	virtual int GetWeekNumber(const COleDateTime& t);
	virtual COleDateTime GetFirstWeek(const COleDateTime& t);
private:
	void PaintView(CDCHandle dc);
	void DrawMonthCell(CDCHandle dc, const COleDateTime& t, const CRect& rcCell);
	void DrawDayViewEvents(CDCHandle dc, const COleDateTime& tDay, CRect& rcDay, const CWizCalendarEventDataArray& arrayEvent);
	void DrawMonthViewMoreEvent(CDCHandle dc, CRect& rcDay);
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);
	void DoPaint(CDCHandle dc);

	BEGIN_MSG_MAP(CWizCalendarView)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		CHAIN_MSG_MAP(CScrollWindowImpl<CWizCalendarView>)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
	END_MSG_MAP()


	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
