#pragma once

#include "WizKMCalendarEventsDef.h"

#ifndef _WIZKMTODO_H_
#include "WizKMTodo.h"
#endif


inline BOOL WizKMEventToCalendarEvent(IWizEvent* pEvent, WIZDOCUMENTEVENTDATA& e)
{
	CComBSTR bstrGUID;
	CComBSTR bstrTitle;
	DATE dtStart = 0;
	DATE dtEnd = 0;
	long nColor = 0;
	long nReminder = 0;
	CComBSTR bstrRecurrence;
	CComBSTR bstrEndRecurrence;
	VARIANT_BOOL vbCompleted;
	CComBSTR bstrRecurrenceIndex;
	//
	pEvent->get_GUID(&bstrGUID);
	pEvent->get_Title(&bstrTitle);
	pEvent->get_Start(&dtStart);
	pEvent->get_End(&dtEnd);
	pEvent->get_Color(&nColor);
	pEvent->get_Reminder(&nReminder);
    pEvent->get_Recurrence(&bstrRecurrence);
    pEvent->get_EndRecurrence(&bstrEndRecurrence);
	pEvent->get_Completed(&vbCompleted);
	pEvent->get_RecurrenceIndex(&bstrRecurrenceIndex);
	//
	e.strGUID = CString(bstrGUID);
	e.strTitle = CString(bstrTitle);
	e.tStart = dtStart;
	e.tEnd = dtEnd;
	e.crBackground = nColor;
	e.nReminder = nReminder;
	e.strRecurrence = CString(bstrRecurrence);
	e.strEndRecurrence = CString(bstrEndRecurrence);
	e.bCompleted = vbCompleted ? TRUE : FALSE;
	e.strRecurrenceIndex = CString(bstrRecurrenceIndex);
	if (e.tStart >= e.tEnd)
		return FALSE;
	//
	return TRUE;
}


inline BOOL WizKMDocumentToCalendarEvent(IWizDocument* pDocument, WIZDOCUMENTEVENTDATA& e)
{
	CComPtr<IDispatch> spEventDisp;
	pDocument->get_Event(&spEventDisp);
	if (!spEventDisp)
		return FALSE;
	//
	CComQIPtr<IWizEvent> spEvent(spEventDisp);
	if (!spEvent)
		return FALSE;
	//
	return WizKMEventToCalendarEvent(spEvent, e);
}





inline BOOL WizKMGetCalendarEvents(CWizKMDatabase* pDatabase, const COleDateTime& tStart, const COleDateTime& tEnd, CWizDocumentEventDataArray& events)
{
	CWizEventArray arrayEvent;
	if (!pDatabase->GetCalendarEvents(tStart, tEnd, arrayEvent))
	{
		TOLOG(_T("Failed to get calendar events!"));
		return FALSE;
	}
	//
	for (CWizEventArray::const_iterator it = arrayEvent.begin();
		it != arrayEvent.end();
		it++)
	{
		WIZDOCUMENTEVENTDATA e;
		if (WizKMEventToCalendarEvent(*it, e))
		{
			events.push_back(e);
		}
	}
	//
	return TRUE;
}



inline BOOL WizKMGetCalendarEvents(CWizKMDatabase* pDatabase, const COleDateTime& tStart, const COleDateTime& tEnd, CWizCalendarEventArray& events)
{
	CWizDocumentEventDataArray arrayEvent;
	if (!WizKMGetCalendarEvents(pDatabase, tStart, tEnd,  arrayEvent))
		return FALSE;
	//
	events.assign(arrayEvent.begin(), arrayEvent.end());
	//
	return TRUE;
}

inline BOOL WizKMUpdateEvent(IWizDocument* pDocument, const WIZDOCUMENTEVENTDATA& e)
{
	CComPtr<IWizEvent> spEvent = WizKMCreateEvent();
	if (!spEvent)
	{
		TOLOG(_T("Failed to create event object!"));
		return FALSE;
	}
	//
	spEvent->put_Start(e.tStart);
	spEvent->put_End(e.tEnd);
	spEvent->put_Recurrence(CComBSTR(e.strRecurrence));
	spEvent->put_EndRecurrence(CComBSTR(e.strEndRecurrence));
	spEvent->put_Reminder(e.nReminder);
	spEvent->put_Color(e.crBackground);
	//
	return SUCCEEDED(pDocument->put_Event(spEvent));
}



inline BOOL WizKMDocumentAddToCalendar(IWizDocument* pDocument, const COleDateTime& tStart, const COleDateTime& tEnd, LPCTSTR lpszRecurrence, LPCTSTR lpszEndRecurrence, COLORREF crBackground, int nReminder)
{
	if (tStart >= tEnd)
		return FALSE;
	//
	WIZDOCUMENTEVENTDATA e;
	e.strGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	e.strTitle = CWizKMDatabase::GetDocumentTitle(pDocument);
	//
	e.tStart = tStart;
	e.tEnd = tEnd;
	//
	e.strRecurrence = lpszRecurrence;
	e.strEndRecurrence = lpszEndRecurrence;
	//
	e.crBackground = crBackground;
	e.nReminder = nReminder;
	e.bCompleted = FALSE;
	//
	return WizKMUpdateEvent(pDocument, e);
}

inline BOOL WizKMEventSetCompleted(IWizEvent* pEvent)
{
	return SUCCEEDED(pEvent->put_Completed(VARIANT_TRUE))
		&& SUCCEEDED(pEvent->Save());
}

inline BOOL WizKMEventSetDonotRemind(IWizEvent* pEvent)
{
	return SUCCEEDED(pEvent->put_Reminder(-1))
		&& SUCCEEDED(pEvent->Save());
}



inline BOOL WizKMCalendarEventsAddToTodoData(CWizKMDatabase* pDatabase, const COleDateTime& t, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	if (!pDatabase)
		return FALSE;
	//
	COleDateTime tStart = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
	COleDateTime tEnd = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 23, 59, 59);
	//
	CWizEventArray arrayEvent;
	pDatabase->GetCalendarEvents(tStart, tEnd, arrayEvent);
	//
	for (CWizEventArray::const_iterator it = arrayEvent.begin();
		it != arrayEvent.end();
		it++)
	{
		CComPtr<IWizEvent> spEvent = *it;
		//
		CString strEventGUID = CWizKMDatabase::GetObjectGUID(spEvent.p);
		//
		if (WIZTODODATAEX::WizTodoDataArrayFindLinkedDocument(arrayData, strEventGUID))
			continue;
		//
		CComBSTR bstrTitle;
		spEvent->get_Title(&bstrTitle);
		CString strTitle(bstrTitle);
		//
		WIZTODODATA data(strTitle, todoState0, todoPriorImportant);
		//
		data.arrayLinkedDocumentGUID.push_back(strEventGUID);
		//
		arrayData.push_back(data);
	}
	//
	return TRUE;
}


inline BOOL WizKMDocumentGetCollectedUncompletedTasks(IWizDocument* pDocument)
{
	if (!pDocument)
		return FALSE;
	//
	return CWizKMDatabase::GetDocumentParamBool(pDocument, WIZTODODATE_DOCUMENT_PARAM_NAME_COLLECTED_UNCOMPLETED_TASKS, FALSE);
}

inline BOOL WizKMDocumentSetCollectedUncompletedTasks(IWizDocument* pDocument, BOOL b)
{
	if (!pDocument)
		return FALSE;
	//
	return CWizKMDatabase::SetDocumentParamBool(pDocument, WIZTODODATE_DOCUMENT_PARAM_NAME_COLLECTED_UNCOMPLETED_TASKS, b);
}

inline BOOL WizKMDocumentGetRemovedUncompletedTasks(IWizDocument* pDocument)
{
	if (!pDocument)
		return FALSE;
	//
	return CWizKMDatabase::GetDocumentParamBool(pDocument, WIZTODODATE_DOCUMENT_PARAM_NAME_REMOVED_UNCOMPLETED_TASKS, FALSE);
}

inline BOOL WizKMDocumentSetRemovedUncompletedTasks(IWizDocument* pDocument, BOOL b)
{
	if (!pDocument)
		return FALSE;
	//
	return CWizKMDatabase::SetDocumentParamBool(pDocument, WIZTODODATE_DOCUMENT_PARAM_NAME_REMOVED_UNCOMPLETED_TASKS, b);
}


inline BOOL WizKMTodoDataMoveUncompletedTasks(CWizKMDatabase* pDatabase, WIZTODODATAEX::CWizTodoDataExArray& arrayDataSrc, WIZTODODATAEX::CWizTodoDataExArray& arrayDataDest)
{
	BOOL bRet = FALSE;
	//
	size_t nCount = arrayDataSrc.size();
	for (intptr_t i = nCount - 1; i >= 0; i--)
	{
		WIZTODODATAEX& dataSrc = arrayDataSrc[i];
		if (dataSrc.eState == todoState100)
			continue;
		//
		if (dataSrc.arrayLinkedDocumentGUID.size() == 1)
		{
			CComPtr<IWizDocument> spDoc = pDatabase->GetDocumentByGUID(dataSrc.arrayLinkedDocumentGUID[0]);
			if (spDoc)
			{
				if (CWizKMDatabase::GetDocumentType(spDoc) == _T("event"))
					continue;
			}
		}
		//
		arrayDataDest.push_back(dataSrc);
		//
		arrayDataSrc.erase(arrayDataSrc.begin() + i);
		//
		bRet = TRUE;
	}
	//
	return bRet;
}

inline BOOL WizKMAddUncompletedToTodoData(CWizKMDatabase* pDatabase, CComPtr<IWizDocument>& spDocument, const COleDateTime& t, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	if (spDocument)
	{
		if (WizKMDocumentGetCollectedUncompletedTasks(spDocument))
			return FALSE;
	}
	//
	BOOL bRet = FALSE;
	int nCount = 0;
	for (int i = 1; i <= 60; i++)
	{
		COleDateTimeSpan ts(i, 0, 0, 0);
		COleDateTime tDoc = t - ts;
		//
		CComPtr<IWizDocument> spDocumentOld;
		if (!WizKMGetTodoDocument(pDatabase, tDoc, FALSE, FALSE, spDocumentOld))
		{
			TOLOG(_T("Failed to get todo items!"));
			return FALSE;
		}
		//
		if (spDocumentOld)
		{
			nCount++;
			//
			if (!WizKMDocumentGetRemovedUncompletedTasks(spDocumentOld))
			{
				WIZTODODATAEX::CWizTodoDataExArray arrayDataOld;
				//
				if (WizDocumentGetTodoData(spDocumentOld, arrayDataOld))
				{
					if (WizKMTodoDataMoveUncompletedTasks(pDatabase, arrayDataOld, arrayData))
					{
						bRet = TRUE;
						//
						WizDocumentSetTodoData(spDocumentOld, arrayDataOld);
					}
				}
				//
				WizKMDocumentSetRemovedUncompletedTasks(spDocumentOld, TRUE);
			}
		}
		//
		if (nCount >= 7)
			break;
	}
	//
	if (bRet)
	{
		if (!spDocument)
		{
			spDocument = WizKMCreateTodoDocument(pDatabase, t, FALSE);
			if (!spDocument)
			{
				TOLOG(_T("Failed to create document!"));
				return FALSE;
			}
		}
		//
		ATLASSERT(spDocument);
		//
		CComPtr<IWizTodoItemCollection> spColl = WizDataArrayToTodoItemCollection(arrayData);
		if (spColl)
		{
			spDocument->put_TodoItems(spColl);
		}
	}
	//
	return bRet;
}
