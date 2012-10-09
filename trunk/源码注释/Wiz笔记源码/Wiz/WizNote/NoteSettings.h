#pragma once


const LPCTSTR SECTION_NOTE = _T("WizNote");

inline BOOL IsAutoCreateTodayTasks()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_NOTE, _T("AutoCreateTodayTasks"), TRUE);
}

inline BOOL SetAutoCreateTodayTasks(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_NOTE, _T("AutoCreateTodayTasks"), b);
}


inline int GetStartOfDay()
{
	CWizKMSettings settings;
	return settings.GetInt(SECTION_NOTE, _T("StartOfDay"), 0);
}

inline BOOL SetStartOfDay(int n)
{
	CWizKMSettings settings;
	return settings.SetInt(SECTION_NOTE, _T("StartOfDay"), n);
}


inline BOOL IsShowTaskbarButtons()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_NOTE, _T("ShowTaskbarButtons"), FALSE);
}

inline BOOL SetShowTaskbarButtons(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_NOTE, _T("ShowTaskbarButtons"), b);
}

inline BOOL IsMoveUncompletedToTodayTasks()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_NOTE, _T("MoveUncompletedTasksToTodayTasks"), TRUE);
}
inline BOOL SetMoveUncompletedToTodayTasks(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_NOTE, _T("MoveUncompletedTasksToTodayTasks"), b);
}


const LPCTSTR SECTION_HOTKEY_NOTE = _T("WizNoteHotKey");

const LPCTSTR HOTKEY_NAME_NEWNOTE = _T("NewNote");
const LPCTSTR HOTKEY_NAME_DISPLAY_NOTES = _T("DisplayNotes");

const LPCTSTR HOTKEY_DEFAULT_NEWNOTE = _T("Ctrl+Alt+N");
const LPCTSTR HOTKEY_DEFAULT_DISPLAY_NOTE = _T("Ctrl+F2");

inline CString GetCompactButton()
{
	CWizKMSettings settings;
	return settings.GetStr(SECTION_NOTE, _T("ToolButtonOfCompact"), _T("NewNote"));
}

inline BOOL SetCompactButton(LPCTSTR lpszButtonName)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_NOTE, _T("ToolButtonOfCompact"), lpszButtonName);
}

inline CString GetDoubleClickAction()
{
	CWizKMSettings settings;
	return settings.GetStr(SECTION_NOTE, _T("DoubleClickAction"), _T("NewNote"));
}

inline BOOL SetDoubleClickAction(LPCTSTR lpszButtonName)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_NOTE, _T("DoubleClickAction"), lpszButtonName);
}

const LPCTSTR SECTION_TOOLBAR_NOTE = _T("WizNoteToolBar");
inline BOOL GetToolbarButtonVisible(CWizKMSettings& settings, LPCTSTR lpszButtonName)
{
	return settings.GetBool(SECTION_TOOLBAR_NOTE, lpszButtonName, TRUE);
}
inline BOOL SetToolbarButtonVisible(CWizKMSettings& settings, LPCTSTR lpszButtonName, BOOL b)
{
	return settings.SetBool(SECTION_TOOLBAR_NOTE, lpszButtonName, b);
}

inline COleDateTime WizKMTimeToTodoListTime(const COleDateTime& t)
{
	int nHours = GetStartOfDay();
	if (nHours <= 0)
	{
		return t;
	}
	//
	COleDateTime tStart = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), nHours, 0, 0);	//从凌晨6点开始
	COleDateTime tEnd = tStart + COleDateTimeSpan(1, 0, 0, 0);
	//
	if (t < tStart)
		return t - COleDateTimeSpan(1, 0, 0, 0);
	else if (t >= tStart && t < tEnd)
		return t;
	else
		return t + COleDateTimeSpan(1, 0, 0, 0);
}
