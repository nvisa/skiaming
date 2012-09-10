#ifndef __ATLCONTROLIMPL_H__
#define __ATLCONTROLIMPL_H__

#pragma once

namespace WTL
{

#ifndef BCM_SETSHIELD 
#define BCM_SETSHIELD 0x00160C
#endif


class CEditImpl : public CWindowImpl<CEditImpl, CEdit>
{
BEGIN_MSG_MAP(CEditImpl)
END_MSG_MAP()
};

class CComboBoxImpl : public CWindowImpl<CComboBoxImpl, CComboBox>
{
BEGIN_MSG_MAP(CComboBoxImpl)
END_MSG_MAP()
};
class CButtonImpl : public CWindowImpl<CButtonImpl, CButton>
{
BEGIN_MSG_MAP(CButtonImpl)
END_MSG_MAP()
//
public:
	void SetShield()
	{
		SendMessage(0x00160C/*BCM_SETSHIELD*/, 0, TRUE);
	}
};

class CListViewCtrlImpl : public CWindowImpl<CListViewCtrlImpl, CListViewCtrl>
{
BEGIN_MSG_MAP(CListViewCtrlImpl)
END_MSG_MAP()
};

class CTreeViewCtrlImpl : public CWindowImpl<CTreeViewCtrlImpl, CTreeViewCtrl>
{
BEGIN_MSG_MAP(CTreeViewCtrlImpl)
END_MSG_MAP()
};

class CProgressBarCtrlImpl : public CWindowImpl<CProgressBarCtrlImpl, CProgressBarCtrl>
{
BEGIN_MSG_MAP(CProgressBarCtrlImpl)
END_MSG_MAP()
};

#ifndef WINCE
class CRichEditCtrlImpl : public CWindowImpl<CRichEditCtrlImpl, CRichEditCtrl>
{
BEGIN_MSG_MAP(CRichEditCtrlImpl)
END_MSG_MAP()
};
class CHotKeyCtrlImpl : public CWindowImpl<CHotKeyCtrlImpl, CHotKeyCtrl>
{
BEGIN_MSG_MAP(CHotKeyCtrlImpl)
END_MSG_MAP()
};


#endif

class CStaticImpl : public CWindowImpl<CStaticImpl, CStatic>
{
BEGIN_MSG_MAP(CStaticImpl)
END_MSG_MAP()
};

class CDateTimePickerCtrlImpl : public CWindowImpl<CDateTimePickerCtrlImpl, CDateTimePickerCtrl>
{
BEGIN_MSG_MAP(CDateTimePickerCtrlImpl)
END_MSG_MAP()
};

class CUpDownCtrlImpl : public CWindowImpl<CUpDownCtrlImpl, CUpDownCtrl>
{
BEGIN_MSG_MAP(CUpDownCtrlImpl)
END_MSG_MAP()
};


class CTabCtrlImpl : public CWindowImpl<CTabCtrlImpl, CTabCtrl>
{
BEGIN_MSG_MAP(CTabCtrlImpl)
END_MSG_MAP()
};

class CListBoxImpl : public CWindowImpl<CListBoxImpl, CListBox>
{
BEGIN_MSG_MAP(CListBoxImpl)
END_MSG_MAP()
};

class CMonthCalendarCtrlImpl : public CWindowImpl<CMonthCalendarCtrlImpl, CMonthCalendarCtrl>
{
BEGIN_MSG_MAP(CMonthCalendarCtrlImpl)
END_MSG_MAP()
};


#ifdef __ATLCTRLX_H__
class CWizSortListViewCtrl : public CSortListViewCtrlImpl<CWizSortListViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_SortListViewCtrl"), GetWndClassName())
	enum
	{
		m_cchCmpTextMax = 1024, // overrideable
	};
};

#endif


}



#endif //__ATLCONTROLIMPL_H__

