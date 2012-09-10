#pragma once

#include <algorithm>

typedef CWizCalendarEventDataArray	CWizCalendarColumn;
typedef CWizCalendarEventDataArray	CWizCalendarRow;

class CWizCalendarColumnArray : public std::vector<CWizCalendarColumn>
{
public:
	void BuildColumnArray(const COleDateTime& tDay, const CWizCalendarEventDataArray& arrayEvent)
	{
		COleDateTime start(tDay.GetYear(), tDay.GetMonth(), tDay.GetDay(), 0, 0, 0);
		COleDateTime end(tDay.GetYear(), tDay.GetMonth(), tDay.GetDay(), 23, 59, 59);
		//
		CWizCalendarEventDataArray events;
		arrayEvent.CopyToRange(start, end, events);
		//
		std::sort(events.begin(), events.end());
		//
		while (!events.empty())
		{
			CWizCalendarColumn column;
			//
			WIZCALENDAREVENTDATA& e = events[0];
			//
			column.push_back(e);
			COleDateTime tEnd = e.tEnd;
			events.erase(events.begin());
			//
			for (size_t i = 0; i < events.size();)
			{
				WIZCALENDAREVENTDATA& eNext = events[i];
				if (eNext.tStart >= tEnd)
				{
					column.push_back(eNext);
					tEnd = eNext.tEnd;
					events.erase(events.begin() + i);
				}
				else
				{
					i++;
				}
			}
			//
			push_back(column);
		}
		//
		for (size_t iColumn = 0; iColumn < size(); iColumn++)
		{
			CWizCalendarColumn& column = at(iColumn);
			//
			for (size_t iEvent = 0; iEvent < column.size(); iEvent++)
			{
				WIZCALENDAREVENTDATA& e = column[iEvent];
				e.nColumnIndex = (int)iColumn;
				//
				for (size_t iColumnNext = iColumn + 1; iColumnNext < size(); iColumnNext++)
				{
					if (at(iColumnNext).Conflict(e))
						break;
					//
					e.nColumnSpan++;
				}
			}
		}
	}
};


class CWizCalendarRowArray : public std::vector<CWizCalendarRow>
{
public:
	void Check()
	{
		int nRowCount = (int)begin()->size();
		for (const_iterator it = begin(); it != end(); it++)
		{
			ATLASSERT(nRowCount == it->size());
		}
	}
	//
	int GetRowCount()
	{
		Check();
		//
		if (empty())
			return 0;
		//
		return (int)begin()->size();
	}
	//
	void AppendRow()
	{
		if (empty())
			return;
		//
		Check();
		//
		WIZCALENDAREVENTDATA dataEmpty;
		for (iterator it = begin(); it != end(); it++)
		{
			it->push_back(dataEmpty);
		}
	}
	//
	int FindRow(int nDayIndex, int nDaySpan)
	{
		ATLASSERT(nDayIndex >= 0 && nDayIndex < int(size()));
		ATLASSERT(nDaySpan >= 1 && nDayIndex + nDaySpan <= int(size()));
		//
		int nRowCount = GetRowCount();
		for (int iRow = 0; iRow < nRowCount; iRow++)
		{
			BOOL bEmpty = TRUE;
			for (int iDay = nDayIndex; iDay < nDayIndex + nDaySpan; iDay++)
			{
				if (!at(iDay).at(iRow).IsNull())
				{
					bEmpty = FALSE;
					break;
				}
			}
			//
			if (bEmpty)
				return iRow;
		}
		return -1;
	}
	int AddEvent(int nDayIndex, int nDaySpan, const WIZCALENDAREVENTDATA& e)
	{
		int nRow = FindRow(nDayIndex, nDaySpan);
		if (-1 == nRow)
		{
			AppendRow();
			nRow = GetRowCount() - 1;
		}
		//
		for (int iDay = nDayIndex; iDay < nDayIndex + nDaySpan; iDay++)
		{
			iterator it = begin() + iDay;
			//
			it->at(nRow) = e;
		}
		//
		return nRow;
	}
	void BuildRowArray(const COleDateTime& tStart, const COleDateTime& tEnd, const CWizCalendarEventDataArray& arrayEvent)
	{
		COleDateTime start = COleDateTime(tStart.GetYear(), tStart.GetMonth(), tStart.GetDay(), 0, 0, 0);
		COleDateTime end = COleDateTime(tEnd.GetYear(), tEnd.GetMonth(), tEnd.GetDay(), 23, 59, 59);
		//
		CWizCalendarEventDataArray events;
		arrayEvent.CopyToRange(start, end, events);

		COleDateTimeSpan ts = end- start;
		int nDays = (int)ts.GetDays() + 1;
		//
		resize(nDays);
		//
		for (int iDay = 0; iDay < nDays; iDay++)
		{
			COleDateTime day_start = start + COleDateTimeSpan(iDay, 0, 0, 0);
			COleDateTime day_end = day_start + COleDateTimeSpan(0, 23, 59, 59);
			//
			CWizCalendarEventDataArray day_events;
			for (CWizCalendarEventDataArray::const_iterator it = events.begin();
				it != events.end();
				it++)
			{
				if (it->tStart >= day_start && it->tStart <= day_end)
				{
					day_events.push_back(*it);
				}
			}
			//
			for (CWizCalendarEventDataArray::const_iterator it = day_events.begin();
				it != day_events.end();
				it++)
			{
				WIZCALENDAREVENTDATA e = *it;
				//
				if (e.tEnd > end)
					e.tEnd = end;
				//
				COleDateTimeSpan ts = e.tEnd - e.tStart;
				int nDaySpan = (int)ts.GetDays() + 1;
				//
				AddEvent(iDay, nDaySpan, e);
			}
		}
	}
};

