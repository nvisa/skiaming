#pragma once

#include "WizCalendarEvent.h"


class CWizRectArray : public std::vector<CRect>
{
public:
	intptr_t HitTest(POINT pt) const
	{
		for (const_iterator it = begin(); it != end(); it++)
		{
			if (it->PtInRect(pt))
				return it - begin();
		}
		return -1;
	}
};

struct WIZCALENDAREVENTDATA : public WIZCALENDAREVENT
{
	int nColumnIndex;
	int nColumnSpan;
	//
	CWizRectArray arrayRect;
	//
	WIZCALENDAREVENTDATA()
		: nColumnIndex(0)
		, nColumnSpan (1)
	{
	}
	WIZCALENDAREVENTDATA(const WIZCALENDAREVENT& data)
		: WIZCALENDAREVENT(data)
		, nColumnIndex(0)
		, nColumnSpan (1)
	{
	}
	//
	friend bool operator< ( _In_ const WIZCALENDAREVENTDATA& data1, _In_ const WIZCALENDAREVENTDATA& data2 ) throw()
	{
		return data1.tStart < data2.tStart;
	}
	//
	BOOL InRange(const COleDateTime& start, const COleDateTime& end) const
	{
		ATLASSERT(tStart <= tEnd);
		//
		if (tEnd < start)
			return FALSE;
		if (tStart > end)
			return FALSE;
		//
		return TRUE;
	}
};

class CWizCalendarEventDataArray : public std::vector<WIZCALENDAREVENTDATA>
{
public:
	CWizCalendarEventDataArray()
	{
	}
	CWizCalendarEventDataArray(const CWizCalendarEventDataArray& data)
	{
		assign(data.begin(), data.end());
	}
	CWizCalendarEventDataArray& operator = (const CWizCalendarEventDataArray& right)
	{
		assign(right.begin(), right.end());
		//
		return *this;
	}
	//
	void CopyToRange(const COleDateTime& tStart, const COleDateTime& tEnd, CWizCalendarEventDataArray& dest) const
	{
		for (const_iterator it = begin(); it != end(); it++)
		{
			if (it->InRange(tStart, tEnd))
			{
				WIZCALENDAREVENTDATA data = *it;
				if (data.tStart < tStart)
					data.tStart = tStart;
				if (data.tEnd > tEnd)
					data.tEnd = tEnd;
				//
				dest.push_back(data);
			}
		}
	}
	BOOL Conflict(const WIZCALENDAREVENTDATA& e) const
	{
		for (const_iterator it = begin(); it != end(); it++)
		{
			if (it->InRange(e.tStart, e.tEnd))
				return TRUE;
			/*
			const WIZCALENDAREVENTDATA& curr = *it;
			if (curr.tStart >= e.tStart && curr.tStart < e.tEnd)
				return TRUE;
			if (curr.tEnd >= e.tStart && curr.tEnd < e.tEnd)
				return TRUE;
			*/
		}
		//
		return FALSE;
	}
	//
	void ClearRect()
	{
		for (iterator it = begin(); it != end(); it++)
		{
			it->arrayRect.clear();
		}
	}
	intptr_t IndexOf(LPCTSTR lpszGUID)
	{
		for (const_iterator it = begin(); it != end(); it++)
		{
			if (0 == it->strGUID.Compare(lpszGUID))
				return it - begin();
		}
		return -1;
	}
	intptr_t IndexOf(const WIZCALENDAREVENTDATA& data)
	{
		return IndexOf(data.strGUID);
	}
	BOOL AddRect(LPCTSTR lpszGUID, const RECT& rc)
	{
		intptr_t nIndex = IndexOf(lpszGUID);
		if (-1 == nIndex)
			return-1;
		//
		at(nIndex).arrayRect.push_back(rc);
		return TRUE;
	}
	BOOL AddRect(const WIZCALENDAREVENTDATA& data, const RECT& rc)
	{
		return AddRect(data.strGUID, rc);
	}
	intptr_t HitTest(POINT pt)
	{
		for (const_iterator itEvent = begin(); itEvent != end(); itEvent++)
		{
			if (-1 != itEvent->arrayRect.HitTest(pt))
				return itEvent - begin();
		}
		return -1;
	}
};


