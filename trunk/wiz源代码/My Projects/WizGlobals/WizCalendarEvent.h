#pragma once

struct WIZCALENDAREVENT
{
	CString strGUID;
	CString strTitle;
	COleDateTime tStart;
	COleDateTime tEnd;
	COLORREF crBackground;
	//
	CString strRecurrenceIndex;
	//
	WIZCALENDAREVENT(LPCTSTR lpszGUID, LPCTSTR lpszTitle, const COleDateTime& start, const COleDateTime& end, COLORREF crBack)
		: strGUID(lpszGUID)
		, strTitle(lpszTitle)
		, tStart(start)
		, tEnd(end)
		, crBackground(crBack)
	{
		ATLASSERT(tStart <= tEnd);
	}
	WIZCALENDAREVENT()
	{
		tStart = COleDateTime::GetCurrentTime();
		tEnd - tStart;
	}
	//
	BOOL IsNull() const
	{
		return strGUID.IsEmpty();
	}
};

typedef std::vector<WIZCALENDAREVENT> CWizCalendarEventArray;

class CWizCalendayEventProvider
{
public:
	virtual void GetEvents(const COleDateTime& tStart, COleDateTime& tEnd, CWizCalendarEventArray& arrayEvent) = 0;
	virtual void CreateEvent(const COleDateTime& tSelected) = 0;
	virtual void DeleteEvent(const WIZCALENDAREVENT& e) = 0;
	virtual void EditEvent(const WIZCALENDAREVENT& e) = 0;
};

