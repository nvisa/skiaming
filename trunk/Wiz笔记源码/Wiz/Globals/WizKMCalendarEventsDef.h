#pragma once

#include "../../WizGlobals/WizCalendarEvent.h"
#include "../../WizGlobals/WizChineseCalendar.h"


#define WIZKM_CALENDAR_EVENT_MODIFIED_MESSAGE_NAME		_T("WizKM_CalendarEventModified")



inline COLORREF WizKMCalendarEventGetDefaultBackground()
{
	return RGB(213, 248, 221);
}

struct WIZDOCUMENTEVENTDATA : public WIZCALENDAREVENT
{
	int nReminder;
	BOOL bCompleted;
	CString strRecurrence;
	CString strEndRecurrence;
	//
	WIZDOCUMENTEVENTDATA()
	{
		nReminder = -1;
		bCompleted = FALSE;
	}
	//
	//
	static int GetDayOfWeekInner(const COleDateTime& t)
	{
		//Returns the day of the week based on local time; 1 = Sunday, 2 = Monday, to 7 = Saturday.
		int nDayOfWeek = t.GetDayOfWeek();
		//
		switch (nDayOfWeek)
		{
		case 1:	//sun
			return 7;
		case 2:	//mon
			return 1;
		case 3:	//mon
			return 2;
		case 4:	//mon
			return 3;
		case 5:	//mon
			return 4;
		case 6:	//mon
			return 5;
		case 7:	//mon
			return 6;
		}
		ATLASSERT(FALSE);
		return 1;
	}
	//
	BOOL Accept(const COleDateTime& t) const
	{
		if (strRecurrence.IsEmpty())
			return FALSE;
		if (0 == strRecurrence.CompareNoCase(_T("None")))
			return FALSE;
		//
		if (t == tStart)
			return TRUE;
		//
		if (t.GetYear() == tStart.GetYear()
			&& t.GetMonth() == tStart.GetMonth()
			&& t.GetDay() == tStart.GetDay())
			return TRUE;
		//
		if (t < tStart)
			return FALSE;
		//
		if (t > GetEndRecurrence())
			return FALSE;
		//
		if (0 == strRecurrence.CompareNoCase(_T("Daily")))
		{
			return TRUE;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeekday")))
		{
			switch (GetDayOfWeekInner(t))
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				return TRUE;
			}
			return FALSE;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek1")))
		{
			return 1 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek2")))
		{
			return 2 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek3")))
		{
			return 3 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek4")))
		{
			return 4 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek5")))
		{
			return 5 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek6")))
		{
			return 6 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeek7")))
		{
			return 7 == GetDayOfWeekInner(t);
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeekday135")))
		{
			switch (GetDayOfWeekInner(t))
			{
			case 1:
			case 3:
			case 5:
				return TRUE;
			}
			return FALSE;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeekday24")))
		{
			switch (GetDayOfWeekInner(t))
			{
			case 2:
			case 4:
				return TRUE;
			}
			return FALSE;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("EveryWeekday67")))
		{
			switch (GetDayOfWeekInner(t))
			{
			case 6:
			case 7:
				return TRUE;
			}
			return FALSE;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("Weekly")))
		{
			return t.GetDayOfWeek() == tStart.GetDayOfWeek();
		}
		else if (0 == strRecurrence.CompareNoCase(_T("Every2Weeks")))
		{
			COleDateTimeSpan ts = t - tStart;
			return t.GetDayOfWeek() == tStart.GetDayOfWeek()
				&& (ts.GetDays() % 14) > 7;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("Monthly")))
		{
			return t.GetDay() == tStart.GetDay();
		}
		else if (0 == strRecurrence.CompareNoCase(_T("Yearly")))
		{
			return t.GetMonth() == tStart.GetMonth()
				&& t.GetDay() == tStart.GetDay();
		}
		else if (0 == strRecurrence.CompareNoCase(_T("ChineseMonthly")))
		{
			WIZCHINESECALENDARDATEDATA c = WizChineseCalendarGetLunar(t);
			WIZCHINESECALENDARDATEDATA cStart = WizChineseCalendarGetLunar(tStart);
			return c.day == cStart.day;
		}
		else if (0 == strRecurrence.CompareNoCase(_T("ChineseYearly")))
		{
			WIZCHINESECALENDARDATEDATA c = WizChineseCalendarGetLunar(t);
			WIZCHINESECALENDARDATEDATA cStart = WizChineseCalendarGetLunar(tStart);
			return c.day == cStart.day
				&& c.month == cStart.month;
		}
		//
		return FALSE;
	}
	//
	COleDateTime GetEndRecurrence() const
	{
		if (strEndRecurrence.IsEmpty())
			return COleDateTime(2030, 1, 1, 0, 0, 0);
		//
		return WizStringToDateTime(strEndRecurrence);
	}
};

typedef std::vector<WIZDOCUMENTEVENTDATA> CWizDocumentEventDataArray;
typedef CWizDocumentEventDataArray  CWizEventDataArray;

const UINT WIZDOCUMENTEVENT_RECURRENCES_COUNT = 19;

__declspec( selectany ) LPCTSTR WIZDOCUMENTEVENT_RECURRENCES[WIZDOCUMENTEVENT_RECURRENCES_COUNT] =
{
	_T("None"),
	_T("Daily"),
	_T("EveryWeekday"),
	_T("EveryWeek1"),
	_T("EveryWeek2"),
	_T("EveryWeek3"),
	_T("EveryWeek4"),
	_T("EveryWeek5"),
	_T("EveryWeek6"),
	_T("EveryWeek7"),
	_T("EveryWeekday135"),
	_T("EveryWeekday24"),
	_T("EveryWeekday67"),
	_T("Weekly"),
	_T("Every2Weeks"),
	_T("Monthly"),
	_T("Yearly"),
	_T("ChineseMonthly"),
	_T("ChineseYearly"),
};

__declspec( selectany ) LPCTSTR WIZDOCUMENTEVENT_RECURRENCES_DESC[WIZDOCUMENTEVENT_RECURRENCES_COUNT] =
{
	_T("None"),
	_T("Daily"),
	_T("Every weekday"),
	_T("Every Mon"),
	_T("Every Tue"),
	_T("Every Wed"),
	_T("Every Thu"),
	_T("Every Fri"),
	_T("Every Sat"),
	_T("Every Sun"),
	_T("Every Mon, Wed, Fri"),
	_T("Every Tue, Thu"),
	_T("Every Sat, Sun"),
	_T("Weekly"),
	_T("Every 2 weeks"),
	_T("Monthly"),
	_T("Yearly"),
	_T("Chinese Calendar monthly"),
	_T("Chinese Calendar yearly"),
};

inline int WizKMDocumentEventRecurrenceGetIndex(LPCTSTR lpszName)
{
	if (!lpszName | !*lpszName)
		return 0;
	//
	for (int i = 0; i < WIZDOCUMENTEVENT_RECURRENCES_COUNT; i++)
	{
		if (0 == _tcsicmp(lpszName, WIZDOCUMENTEVENT_RECURRENCES[i]))
			return i;
	}
	//
	return 0;
}
inline CString WizKMDocumentEventRecurrenceGetDescription(LPCTSTR lpszName)
{
	int nIndex = WizKMDocumentEventRecurrenceGetIndex(lpszName);
	if (-1 == nIndex)
		return CString();
	//
	WizTranslationsTranslateString(WIZDOCUMENTEVENT_RECURRENCES_DESC[nIndex]);
}

inline CString WizKMDocumentEventRecurrenceGetDescription(int nIndex)
{
	ATLASSERT(nIndex >= 0 && nIndex < WIZDOCUMENTEVENT_RECURRENCES_COUNT);
	if (nIndex < 0 || nIndex >= WIZDOCUMENTEVENT_RECURRENCES_COUNT)
		return CString();
	//
	return WizTranslationsTranslateString(WIZDOCUMENTEVENT_RECURRENCES_DESC[nIndex]);
}

