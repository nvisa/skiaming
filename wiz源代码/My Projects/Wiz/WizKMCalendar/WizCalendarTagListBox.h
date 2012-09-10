#pragma once


class CWizCalendarTagListBox 
	: public CWizVistaListBoxExtendedSelect
{
public:
	//DECLARE_WND_SUPERCLASS(NULL, CListBox::GetWndClassName())
	// Constructor/Destructor
	CWizCalendarTagListBox()
		: m_pDatabase(NULL)
	{
	}

	~CWizCalendarTagListBox()
	{
	}
protected:
	CWizKMDatabase* m_pDatabase;
public:
	void SetDatabase(CWizKMDatabase* pDatabase)
	{
		m_pDatabase = pDatabase;
		ATLASSERT(m_pDatabase);
	}

// Message map and handlers
	//BEGIN_MSG_MAP(CWizCalendarTagListBox)
	//END_MSG_MAP()

	void ResetTags()
	{
		if (!m_pDatabase)
			return;
		//
		while (GetCount() > 0)
		{
			DeleteString(0);
		}
		//
		AddString(WizFormatString0(IDS_ALL_CALENDAR_TAGS));
		//
		CWizStdStringArray arrayTagName;
		WizKMCalendarTagsGetAllTagsName(m_pDatabase, arrayTagName);
		//
		WizStringArraySort(arrayTagName);
		//
		for (CWizStdStringArray::const_iterator it = arrayTagName.begin();
			it != arrayTagName.end();
			it++)
		{
			int nItem = AddString(*it);
		}
	}
	void GetSelectedTags(CWizStdStringArray& arrayTag)
	{
		arrayTag.clear();
		//
		if (GetSel(0) > 0)
		{
			return;
		}
		//
		int nCount = GetCount();
		for (int i = 1; i < nCount; i++)
		{
			if (GetSel(i) > 0)
			{
				CString strText;
				GetText(i, strText);
				arrayTag.push_back(strText);
			}
		}
	}
};
