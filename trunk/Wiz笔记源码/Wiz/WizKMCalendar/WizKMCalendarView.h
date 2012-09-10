// WizKMCalendarView.h : interface of the CWizKMCalendarView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../WizGlobals/WizCalendarView.h"
#include "../Globals/WizKMCalendarEvents.h"

enum WizKMMonthViewCellBackgroundTextType
{
	textNone,
	textNote,
	textTodoList,
	textJournal,
};

class CWizKMMonthViewCellBackgroundTextMap : public std::map<CString, CString>
{
public:
	virtual CString GetBackgroundText(WizKMMonthViewCellBackgroundTextType eType, const COleDateTime& t);
private:
	CString GetKey(const COleDateTime& t);

};


class CWizKMCalendarView 
	: public CWizCalendarView
	, public CWizCalendayEventProvider

{
public:
	CWizKMCalendarView();
	//
protected:
	CWizKMMonthViewCellBackgroundTextMap m_mapBackgroundText;
	//
	WizKMMonthViewCellBackgroundTextType m_eBackgroundTextType;
	//
	CWizStdStringArray m_arrayTags;
	//
	BOOL m_bShowWeekNumbers;
public:
	virtual void GetEvents(const COleDateTime& tStart, COleDateTime& tEnd, CWizCalendarEventArray& arrayEvent);
	virtual void CreateEvent(const COleDateTime& tSelected);
	virtual void DeleteEvent(const WIZCALENDAREVENT& e);
	virtual void EditEvent(const WIZCALENDAREVENT& e);
	virtual CString GetMonthViewBackgroundText(const COleDateTime& t);
	virtual CString GetSecondCalendarDateText(const COleDateTime& t, BOOL bLong);
	//
	virtual CString GetNavigatorText(int index);
	virtual COleDateTime GetFirstWeek(const COleDateTime& t);
	//
	void LoadSettings();
public:
	void SetBackgroundTextType(WizKMMonthViewCellBackgroundTextType eType);
	WizKMMonthViewCellBackgroundTextType GetBackgroundTextType() const { return m_eBackgroundTextType; }
	//
	void SetTags(const CWizStdStringArray& arrayTags);
public:
	BEGIN_MSG_MAP(CWizKMCalendarView)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		CHAIN_MSG_MAP(CWizCalendarView)
	END_MSG_MAP()
	//
	LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

