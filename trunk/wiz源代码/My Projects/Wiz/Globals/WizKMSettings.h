#pragma once

#ifndef _WIZKMDATABASE_H_
#include "WizKMDatabase.h"
#endif

class CWizKMSettingsSection
{
public:
	CWizKMSettingsSection()
	{
	}
	CWizKMSettingsSection(IWizSettingsSection* pSection)
	{
		m_spSection = pSection;
	}
	CWizKMSettingsSection(IDispatch* pDisp)
	{
		m_spSection = CComQIPtr<IWizSettingsSection>(pDisp);
	}
protected:
	CComPtr<IWizSettingsSection> m_spSection;
public:
	BOOL Valid() const
	{
		return m_spSection ? TRUE : FALSE;
	}
	//
	CWizKMSettingsSection& operator = (const CWizKMSettingsSection& right)
	{
		m_spSection = right.m_spSection;
		//
		return *this;
	}
	//
	CString GetStr(LPCTSTR lpszKey, LPCTSTR lpszDefault = NULL)
	{
		CString str(lpszDefault);
		//
		if (!m_spSection)
			return str;
		//
		CComBSTR bstrValue;
		HRESULT hr = m_spSection->get_StringValue(CComBSTR(lpszKey), &bstrValue);
		if (FAILED(hr))
		{
			TOLOG1(_T("Failed to read string: %1!"), lpszKey);
			return str;
		}
		if (S_FALSE == hr)
			return str;
		//
		return CString(bstrValue);
	}
	int GetInt(LPCTSTR lpszKey, int nDefault = 0)
	{
		if (!m_spSection)
			return nDefault;
		//
		long n = nDefault;
		HRESULT hr = m_spSection->get_IntValue(CComBSTR(lpszKey), &n);
		if (FAILED(hr))
		{
			TOLOG1(_T("Failed to read string: %1!"), lpszKey);
			return nDefault;
		}
		if (S_FALSE == hr)
			return nDefault;
		//
		return n;
	}
	BOOL GetBool(LPCTSTR lpszKey, BOOL bDefault = FALSE)
	{
		if (!m_spSection)
			return bDefault;
		//
		VARIANT_BOOL vb = bDefault ? VARIANT_TRUE : VARIANT_FALSE;
		HRESULT hr = m_spSection->get_BoolValue(CComBSTR(lpszKey), &vb);
		if (FAILED(hr))
		{
			TOLOG1(_T("Failed to read string: %1!"), lpszKey);
			return bDefault;
		}
		if (S_FALSE == hr)
			return bDefault;
		//
		return vb ? TRUE : FALSE;
	}
};


class CWizKMSettings : public IWizSettingsBase
{
public:
	CWizKMSettings()
	{
		m_spSettings = WizKMCreateSettings();
		if (!m_spSettings)
		{
			TOLOG(_T("Failed to create IWizSettings"));
			return;
		}
		//
		CString strSettingsFileName = WizKMGetSettingsFileName();
		HRESULT hr = m_spSettings->Open(CComBSTR(strSettingsFileName));
		if (FAILED(hr))
		{
			TOLOG1(_T("Failed to open settings file; %1"), strSettingsFileName);
		}
	}
	virtual ~CWizKMSettings(void)
	{
		if (m_spSettings)
		{
			HRESULT hr = m_spSettings->Close();
			if (FAILED(hr))
			{
				TOLOG(_T("Failed to save settings!"));
			}
		}
	}
protected:
	CComPtr<IWizSettings> m_spSettings;
public:
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue)
	{
		if (!m_spSettings)
			return FALSE;
		//
		CComBSTR bstrValue;
		HRESULT hr = m_spSettings->get_StringValue(CComBSTR(lpszSection), CComBSTR(lpszKey), &bstrValue);
		if (FAILED(hr))
		{
			TOLOG2(_T("Failed to read string: %1.%2!"), lpszSection, lpszKey);
			return FALSE;
		}
		//
		strValue = CString(bstrValue);
		//
		return TRUE;
	}
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
	{
		if (!m_spSettings)
			return FALSE;
		//
		HRESULT hr = m_spSettings->put_StringValue(CComBSTR(lpszSection), CComBSTR(lpszKey), CComBSTR(lpszValue));
		if (FAILED(hr))
		{
			TOLOG3(_T("Failed to write string: %1.%2=%3!"), lpszSection, lpszKey, lpszValue);
			return FALSE;
		}
		//
		return TRUE;
	}
	BOOL GetSection(LPCTSTR lpszSection, CWizKMSettingsSection& section)
	{
		if (!m_spSettings)
			return FALSE;
		//
		CComPtr<IDispatch> spDisp;
		HRESULT hr = m_spSettings->get_Section(CComBSTR(lpszSection), &spDisp);
		if (S_FALSE == hr)
		{
			return FALSE;
		}
		//
		if (FAILED(hr))
		{
			//TOLOG1(_T("Failed to read section: %1!"), lpszSection);
			return FALSE;
		}
		//
		section = CWizKMSettingsSection(spDisp);
		//
		return section.Valid();
	}
	CWizKMSettingsSection GetSection(LPCTSTR lpszSection)
	{
		CWizKMSettingsSection section;
		GetSection(lpszSection, section);
		return section;
	}
	virtual BOOL ClearSection(LPCTSTR lpszSection)
	{
		if (!m_spSettings)
			return FALSE;
		//
		HRESULT hr = m_spSettings->ClearSection(CComBSTR(lpszSection));
		if (FAILED(hr))
		{
			TOLOG1(_T("Failed to clear section: %1"), lpszSection);
			return FALSE;
		}
		//
		return TRUE;
	}
};




inline CString WizKMGetDefaultDisplayTemplate()
{
	CString strTemplateBasePath = WizGetAppPath() + _T("templates\\display\\");
	CString strDefaultTemplateFileName = strTemplateBasePath + _T("default.ziw");
	//
	CWizKMSettings settings;
	return settings.GetStr(_T("DisplayTemplate"), _T("DefaultTemplate"), strDefaultTemplateFileName);
}

inline BOOL WizKMSetDefaultDisplayTemplate(LPCTSTR lpszFileName)
{
	if (!PathFileExists(lpszFileName))
		return FALSE;
	//
	CWizKMSettings settings;
	return settings.SetStr(_T("DisplayTemplate"), _T("DefaultTemplate"), lpszFileName);
}

inline BOOL WizKMGetUsingDisplayTemplate()
{
	CWizKMSettings settings;
	return settings.GetBool(_T("DisplayTemplate"), _T("UseTemplate"), TRUE);
}

inline BOOL WizKMSetUsingDisplayTemplate(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(_T("DisplayTemplate"), _T("UseTemplate"), b);
}





#define CALENDAR_SECTION _T("Calendar")

inline BOOL WizCalendarIsShowWeekNumbers()
{
	CWizKMSettings settings;
	return settings.GetBool(CALENDAR_SECTION, _T("ShowWeekNumbers"), TRUE);
}

inline BOOL WizCalendarSetShowWeekNumbers(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(CALENDAR_SECTION, _T("ShowWeekNumbers"), b);
}


inline COleDateTime WizCalendarGetFirstWeek()
{
	CWizKMSettings settings;
	CString strFirstWeek = settings.GetStr(CALENDAR_SECTION, _T("FirstWeek"), _T(""));
	if (strFirstWeek.IsEmpty())
		return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), 1, 1, 0, 0, 0);
	//
	COleDateTime t = WizStringToDateTime(strFirstWeek);
	if (t.GetMonth() == 2 && t.GetDay() == 29)
	{
		return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), 2, 28, 0, 0, 0);
	}
	//
	return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
}

inline BOOL WizCalendarSetFirstWeek(const COleDateTime& t)
{
	COleDateTime t1 = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
	//
	CWizKMSettings settings;
	return settings.SetStr(CALENDAR_SECTION, _T("FirstWeek"), ::WizDateTimeToString(t1));
}





#define WIZKM_ACTION_NAME_DOC_DBLCLICKNAME		_T("DocumentListCtrl_DblClickItem")
#define WIZKM_ACTION_NAME_DOC_DBLCLICKBLANK		_T("DocumentListCtrl_DblClickBlank")
#define WIZKM_ACTION_NAME_DOCVIEW_DBLCLICK		_T("DocView_DblClick")

#define WIZKM_ACTION_VALUE_NO_ACTION			_T("NoAction")
#define WIZKM_ACTION_VALUE_NEW_DOCUMENT			_T("NewDocument")
#define WIZKM_ACTION_VALUE_EDIT_DOCUMENT		_T("EditDocument")
#define WIZKM_ACTION_VALUE_FULLSCREEN			_T("FullScreen")

inline CString WizKMGetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszDefActionValue = NULL)
{
	CWizKMSettings settings;
	return settings.GetStr(_T("UserActions"), lpszActionsName, lpszDefActionValue ? lpszDefActionValue : WIZKM_ACTION_VALUE_NO_ACTION);
}

inline BOOL WizKMSetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszActionValue)
{
	CWizKMSettings settings;
	return settings.SetStr(_T("UserActions"), lpszActionsName, lpszActionValue);
}


inline BOOL WizKMIsAutoShowAttach()
{
	CWizKMSettings settings;
	//
	return settings.GetBool(_T("AttachmentsView"), _T("AutoShow"), TRUE);
}
//
inline void WizKMSetAutoShowAttach(BOOL b)
{
	CWizKMSettings settings;
	//
	settings.SetBool(_T("AttachmentsView"), _T("AutoShow"), b);
}



enum WizSearchFullText { fulltextNone, fulltextWindows, fulltextGoogle, fulltextInner};


inline WizSearchFullText WizKMFullTextSearchTypeFromString(const CString& str)
{
	if (0 == str.CompareNoCase(_T("None")))
		return fulltextNone;
	else if (0 == str.CompareNoCase(_T("WindowsSearch")))
		return fulltextWindows;
	else if (0 == str.CompareNoCase(_T("GoogleDesktop")))
		return fulltextGoogle;
	return fulltextInner;
}
inline CString WizKMFullTextSearchTypeToString(WizSearchFullText eType)
{
	switch (eType)
	{
	case fulltextNone:
		return CString(_T("None"));
	case fulltextWindows:
		return CString(_T("WindowsSearch"));
	case fulltextGoogle:
		return CString(_T("GoogleDesktop"));
	default:
		return CString(_T("Wiz"));
	}
}

inline WizSearchFullText WizKMGetFullTextSearchType(CWizKMDatabase* pDatabase)
{
	if (!pDatabase)
		return fulltextNone;
	//
	ATLASSERT(pDatabase);
	//
	CString strType = pDatabase->GetMeta(_T("FullTextSearch"), _T("Type"));
	//
	return WizKMFullTextSearchTypeFromString(strType);
}

inline BOOL WizKMSetFullTextSearchType(CWizKMDatabase* pDatabase, WizSearchFullText eType)
{
	ATLASSERT(pDatabase);
	//
	return pDatabase->SetMeta(_T("FullTextSearch"), _T("Type"), WizKMFullTextSearchTypeToString(eType));
}



const LPCTSTR SECTION_SYNC = _T("Sync");


inline int GetSyncMinutes()
{
	CWizKMSettings settings;
	return settings.GetInt(SECTION_SYNC, _T("SyncMinutes"), 15);
}

inline BOOL SetSyncMinutes(int nMinutes)
{
	CWizKMSettings settings;
	return settings.SetInt(SECTION_SYNC, _T("SyncMinutes"), nMinutes);
}

inline BOOL GetSyncEnabled()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_SYNC, _T("SyncEnabled"), TRUE);
}

inline BOOL SetSyncEnabled(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_SYNC, _T("SyncEnabled"), b);
}

inline BOOL IsSyncShowResult()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_SYNC, _T("ShowResult"), FALSE);
}

inline BOOL SetSyncShowResult(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_SYNC, _T("ShowResult"), b);
}


inline BOOL GetSyncHttpsEnabled()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_SYNC, _T("Https"), FALSE);
}

inline BOOL SetSyncHttpsEnabled(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_SYNC, _T("Https"), b);
}

inline CString GetCachedSyncURL(LPCTSTR lpszCommand)
{
	CWizKMSettings settings;
	return settings.GetStr(SECTION_SYNC, lpszCommand, _T(""));
}

inline BOOL SetCachedSyncURL(LPCTSTR lpszCommand, LPCTSTR lpszURL)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_SYNC, lpszCommand, lpszURL);
}




inline CString WizKMGetLastTagsText(LPCTSTR lpszAttributeName)
{
	CString strAttributeName(lpszAttributeName);
	if (strAttributeName.IsEmpty())
	{
		strAttributeName = _T("Last");
	}

	CWizKMSettings settings;
	//
	return settings.GetStr(_T("UserTagsText"), strAttributeName);
}

inline void WizKMSetLastTagsText(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText)
{
	CString strAttributeName(lpszAttributeName);
	if (strAttributeName.IsEmpty())
	{
		strAttributeName = _T("Last");
	}

	CWizKMSettings settings;
	//
	settings.SetStr(_T("UserTagsText"), strAttributeName, lpszTagsText);
}

inline BOOL WizKMGetTagsHistory(CWizStdStringArray& arrayTagsHistory)
{
	CWizKMSettings settings;
	settings.GetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	return TRUE;
}

inline BOOL WizKMAddToTagsHistory(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText)
{
	CString strTagsText(lpszTagsText);
	//
	WizKMRegularTagsText(strTagsText);
	WizKMSetLastTagsText(lpszAttributeName, strTagsText);
	//
	if (-1 == strTagsText.Find(';'))
		return TRUE;
	//
	CWizStdStringArray arrayTag;
	WizSplitTextToArray(strTagsText, ';', arrayTag);
	for (CWizStdStringArray::iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		it->Trim();
	}
	//
	WizStringArrayToText(arrayTag, strTagsText, _T("; "));
	//
	CWizStdStringArray arrayTagsHistory;
	//
	CWizKMSettings settings;
	settings.GetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	if (-1 != WizFindInArrayNoCase(arrayTagsHistory, strTagsText))
		return TRUE;
	//
	arrayTagsHistory.push_back(strTagsText);
	//
	settings.SetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	return TRUE;
}

inline BOOL WizKMGetTagsHistoryWithTagsName(CWizKMDatabase* pDatabase, CWizStdStringArray& arrayTagsHistory)
{
	pDatabase->GetTagsName(arrayTagsHistory);
	//
	return WizKMGetTagsHistory(arrayTagsHistory);
}



inline BOOL WizKMGetRecentPicks(CWizStdStringArray& arrayLocation)
{
	CWizKMSettings settings;
	//
	CWizKMSettingsSection section;
	if (!settings.GetSection(_T("RecentPicks"), section))	//empty?
		return TRUE;
	//
	int nCount = section.GetInt(_T("Count"));
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = section.GetStr(strKey);
		if (strValue.IsEmpty())
			continue;
		//
		arrayLocation.push_back(strValue);
	}
	//
	return TRUE;
}

inline BOOL WizKMGetRecentPicks(CWizKMDatabase* pDatabase, CWizFolderArray& arrayFolder)
{
	CWizStdStringArray arrayLocation;
	if (!WizKMGetRecentPicks(arrayLocation))
		return FALSE;
	//
	int nCount = int(arrayLocation.size());
	for (int i = 0; i < nCount; i++)
	{
		CString strLocation = arrayLocation[i];
		CComPtr<IWizFolder> spFolder = pDatabase->GetFolderByLocation(strLocation, FALSE);
		if (spFolder)
		{
			arrayFolder.push_back(spFolder);
		}
	}
	//
	return TRUE;
}

inline BOOL WizKMSetRecentPicks(const CWizStdStringArray& arrayLocation)
{
	CWizKMSettings settings;
	//
	CString strSection(_T("RecentPicks"));
	//
	int nCount = int(arrayLocation.size());
	settings.ClearSection(strSection);
	settings.SetInt(strSection, _T("Count"), nCount);
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = arrayLocation[i];
		//
		settings.SetStr(strSection, strKey, strValue);
	}
	//
	return TRUE;
}
//
inline BOOL WizKMAppendRecentPicks(LPCTSTR lpszLocation)
{
	if (!lpszLocation)
		return FALSE;
	//
	if (!*lpszLocation)
		return FALSE;
	//
	if (0 == CString(lpszLocation).CompareNoCase(CString(_T("/")) + FOLDER_DELETED_ITEMS + _T("/")))
		return TRUE;
	//
	CWizStdStringArray arrayLocation;
	if (!WizKMGetRecentPicks(arrayLocation))
		return FALSE;
	//
	if (-1 != ::WizFindInArrayNoCase(arrayLocation, lpszLocation))
		return TRUE;
	//
	arrayLocation.insert(arrayLocation.begin(), lpszLocation);
	//
	if (arrayLocation.size() > 10)
	{
		arrayLocation.resize(10);
	}
	//
	return WizKMSetRecentPicks(arrayLocation);
}

inline BOOL WizKMAppendRecentPicks(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	return WizKMAppendRecentPicks(CWizKMDatabase::GetFolderLocation(pFolder));
}




struct WIZKMDOCUMENTGUIDANDTITLE
{
	CString strGUID;
	CString strTitle;
};

typedef std::vector<WIZKMDOCUMENTGUIDANDTITLE>	CWizKMDocumentGUIDAndTitleArray;


inline CString WizKMGetRecentDocumentsSettingsSectionName(CWizKMDatabase* pDatabase)
{
	ATLASSERT(pDatabase);
	//
	CString strPath = pDatabase->GetDatabasePath();
	strPath = WizGetLongFileName(strPath);
	strPath.MakeLower();
	//
	return CString(_T("RecentDocuments_")) + WizMd5StringNoSpace(strPath);
}

inline void WizKMGetRecentDocuments(CWizKMDatabase* pDatabase, CWizKMDocumentGUIDAndTitleArray& arrayDocument)
{
	arrayDocument.clear();
	//
	CWizStdStringArray arrayText;
	//
	CWizKMSettings settings;
	settings.GetStringArray(WizKMGetRecentDocumentsSettingsSectionName(pDatabase), arrayText);
	//
	for (CWizStdStringArray::const_iterator it =  arrayText.begin();
		it != arrayText.end();
		it++)
	{
		CString strText = *it;
		//
		WIZKMDOCUMENTGUIDANDTITLE data;
		if (!WizStringSimpleSplit(strText, '|', data.strGUID, data.strTitle))
			continue;
		//
		if (data.strGUID.IsEmpty())
			continue;
		if (data.strTitle.IsEmpty())
			continue;
		//
		CComPtr<IWizDocument> spDocument = pDatabase->GetDocumentByGUID(data.strGUID);
		if (!spDocument)
			continue;
		//
		data.strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
		//
		arrayDocument.push_back(data);
	}
}

inline void WizKMSetRecentDocuments(CWizKMDatabase* pDatabase, const CWizKMDocumentGUIDAndTitleArray& arrayDocument)
{
	CWizStdStringArray arrayText;
	//
	int nIndex = 0;
	for (CWizKMDocumentGUIDAndTitleArray::const_iterator it = arrayDocument.begin();
		it != arrayDocument.end();
		it++)
	{
		arrayText.push_back(it->strGUID + _T("|") + it->strTitle);
		nIndex++;
		//
		if (nIndex >= 10)
			break;
	}
	//
	CWizKMSettings settings;
	settings.SetStringArray(WizKMGetRecentDocumentsSettingsSectionName(pDatabase), arrayText);
}
inline void WizKMAddRecentDocuments(CWizKMDatabase* pDatabase, LPCTSTR lszDocumentGUID, LPCTSTR lpszDocumentTitle)
{
	CWizKMDocumentGUIDAndTitleArray arrayDocument;
	WizKMGetRecentDocuments(pDatabase, arrayDocument);
	//
	WIZKMDOCUMENTGUIDANDTITLE data;
	data.strGUID = lszDocumentGUID;
	data.strTitle = lpszDocumentTitle;
	//
	arrayDocument.insert(arrayDocument.begin(), data);
	//
	WizKMSetRecentDocuments(pDatabase, arrayDocument);
}



inline CString WizKMGetDefaultCSSFileName()
{
	CString strFileName(_T("files\\default.css"));
	//
	CString strUserFileName = ::WizKMGetSettingsPath() + strFileName;
	if (PathFileExists(strUserFileName))
		return strUserFileName;
	//
	CString strSystemFileName = WizGetAppPath() + strFileName;
	return strSystemFileName;
}
inline BOOL WizKMInsertDefaultCSSToHtml(CString& strHtml)
{
	CWizKMSettings settings;
	CWizKMSettingsSection section;
	settings.GetSection(_T("DocumentDefaults"), section);
	//
	BOOL bEnableDefaultCSS = section.GetBool(_T("EnableCSS"), FALSE);
	if (!bEnableDefaultCSS)
		return TRUE;
	//
	BOOL bEnableColor = section.GetBool(_T("EnableColor"), FALSE);
	//
	CString strFontName = section.GetStr(_T("FontName"), _T("Arial"));
	CString strFontSize = section.GetStr(_T("FontSize"), _T("10.5pt"));
	CString strLineHeight = section.GetStr(_T("LineHeight"), _T("1cm"));
	CString strFontColor = section.GetStr(_T("Color"), _T("black"));
	CString strBackgroundColor = section.GetStr(_T("BackgroundColor"), _T("white"));
	//
	if (!bEnableColor)
	{
		strFontColor = _T("inherit");
		strBackgroundColor = strFontColor;
	}
	//
	CString strCSSText;
	CString strDefaultCSSFileName = WizKMGetDefaultCSSFileName();
	if (!WizLoadUnicodeTextFromFile(strDefaultCSSFileName, strCSSText))
	{
		TOLOG1(_T("Failed to load default CSS file: %1"), strDefaultCSSFileName);
		return FALSE;
	}
	//
	strCSSText.Replace(_T("/*cssFontName*/"), strFontName);
	strCSSText.Replace(_T("/*cssFontSize*/"), strFontSize);
	strCSSText.Replace(_T("/*cssLineHeight*/"), strLineHeight);
	strCSSText.Replace(_T("/*cssColor*/"), strFontColor);
	strCSSText.Replace(_T("/*cssBackgroundColor*/"), strBackgroundColor);
	//
	strCSSText = CString(_T("\r\n<style type=\"text/css\" id=\"wiz_custom_css\">\r\n")) + strCSSText + _T("\r\n</style>\r\n");
	//
	::WizHTMLInsertTextInHead2(strCSSText, strHtml);
	//
	return TRUE;
}
inline BOOL WizKMInsertDefaultCSS(LPCTSTR lpszHtmlFileName)
{
	CString strHtml;
	if (!WizLoadUnicodeTextFromFile(lpszHtmlFileName, strHtml))
	{
		TOLOG1(_T("Failed to load template html file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	if (!::WizKMInsertDefaultCSSToHtml(strHtml))
	{
		TOLOG1(_T("Failed to insert default css to file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	if (!WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHtml))
	{
		TOLOG1(_T("Failed to save template html file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	return TRUE;
}



const LPCTSTR SECTION_EXPLORER = _T("WizExplorer");


inline CString ExplorerGetDoubleClickAction()
{
	CWizKMSettings settings;
	return settings.GetStr(SECTION_EXPLORER, _T("DoubleClickAction"), _T("NewNote"));
}

inline BOOL ExplorerSetDoubleClickAction(LPCTSTR lpszButtonName)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_EXPLORER, _T("DoubleClickAction"), lpszButtonName);
}


//
inline BOOL ExplorerIsEditDocumentAsDefault()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_EXPLORER, _T("EditDocumentAsDefault"), FALSE);
}
inline BOOL ExplorerSetEditDocumentAsDefault(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_EXPLORER, _T("EditDocumentAsDefault"), b);
}



//
inline BOOL ExplorerIsCloseToTray()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_EXPLORER, _T("CloseToTray"), TRUE);
}
inline BOOL ExplorerSetCloseToTray(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_EXPLORER, _T("CloseToTray"), b);
}

enum WizSaveDestination
{
	wizDestinationMyDrafts,
	wizSelectedFolder,
	wizPromptSelect
};

inline WizSaveDestination ExplorerGetSaveDestination()
{
	CWizKMSettings settings;
	return (WizSaveDestination)settings.GetInt(SECTION_EXPLORER, _T("SaveDestination"), wizPromptSelect);
}


inline BOOL ExplorerSetSaveDestination(WizSaveDestination dest)
{
	CWizKMSettings settings;
	return settings.SetInt(SECTION_EXPLORER, _T("SaveDestination"), dest);
}


inline BOOL ExplorerIsEnableGlobalPlugins()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_EXPLORER, _T("EnableGlobalPlugins"), TRUE);
}

inline BOOL ExplorerSetEnableGlobalPlugins(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_EXPLORER, _T("EnableGlobalPlugins"), b);
}

inline CString ExplorerGetEditorSettings()
{
	CWizKMSettings settings;
	//
	BOOL bTabAsSpace = settings.GetBool(_T("Editor"), _T("TabAsSpace"), TRUE);
	int nTabSize = settings.GetInt(_T("Editor"), _T("TabSize"), 4);
	CString strTabText = settings.GetStr(_T("Editor"), _T("TabText"), _T(""));
	//
	BOOL bEnterInsertDiv = settings.GetBool(_T("Editor"), _T("EnterInsertDiv"), TRUE);
	//
	return WizFormatString4(_T("/TabAsSpace=%1 /TabSize=%2 /TabText=%3 /EnterInsertDiv=%4"),
		bTabAsSpace ? _T("1") : _T("0"),
		WizIntToStr(nTabSize),
		strTabText,
		bEnterInsertDiv ? _T("1") : _T("0"));
}

const LPCTSTR SECTION_HOTKEY = _T("HotKey");

const LPCTSTR HOTKEY_NAME_NEWDOCUMENT = _T("NewDocument");
const LPCTSTR HOTKEY_NAME_CLIPSCREEN = _T("ClipScreen");
const LPCTSTR HOTKEY_NAME_COPYCLIPBOARD = _T("CopySelection");
const LPCTSTR HOTKEY_NAME_PASTECLIPBOARD = _T("PasteClipboard");


const LPCTSTR HOTKEY_DEFAULT_NEWDOCUMENT = _T("Ctrl+Alt+D");
const LPCTSTR HOTKEY_DEFAULT_CLIPSCREEN = _T("Win+PrintScreen");
const LPCTSTR HOTKEY_DEFAULT_COPYSELECTION = _T("Win+S");
const LPCTSTR HOTKEY_DEFAULT_PASTECLIPBOARD = _T("Ctrl+Alt+V");

inline BOOL IsFolderTreeCtrlIncludeSubFolders()
{
	CWizKMSettings settings;
	return settings.GetBool(_T("FolderTreeCtrl"), _T("IncludeSubFolders"), FALSE);
}
inline void SetFolderTreeCtrlIncludeSubFolders(BOOL b)
{
	CWizKMSettings settings;
	settings.SetBool(_T("FolderTreeCtrl"), _T("IncludeSubFolders"), b);
}



//
inline BOOL ExplorerIsShowVirtualFolder(CWizKMSettings& settings)
{
	return settings.GetBool(SECTION_EXPLORER, _T("ShowVirtualFolder"), TRUE);
}
inline BOOL ExplorerSetShowVirtualFolder(CWizKMSettings& settings, BOOL b)
{
	return settings.SetBool(SECTION_EXPLORER, _T("ShowVirtualFolder"), b);
}
inline BOOL ExplorerIsShowStatusBar(CWizKMSettings& settings)
{
	return settings.GetBool(SECTION_EXPLORER, _T("StatusBarVisible"), TRUE);
}
inline BOOL ExplorerSetShowStatusBar(CWizKMSettings& settings, BOOL b)
{
	return settings.SetBool(SECTION_EXPLORER, _T("StatusBarVisible"), b);
}

inline BOOL ExplorerIsShowVirtualFolder()
{
	CWizKMSettings settings;
	return ExplorerIsShowVirtualFolder(settings);
}
inline BOOL ExplorerSetShowVirtualFolder(BOOL b)
{
	CWizKMSettings settings;
	return ExplorerSetShowVirtualFolder(settings, b);
}

inline BOOL ExplorerIsShowStatusBar()
{
	CWizKMSettings settings;
	return ExplorerIsShowStatusBar(settings);
}
inline BOOL ExplorerSetShowStatusBar(BOOL b)
{
	CWizKMSettings settings;
	return ExplorerSetShowStatusBar(settings, b);
}

inline CString WizKMGetDestinationParam(LPCTSTR lpszSelectedLocation)
{
	CString strAppFileName = ::WizGetAppFileName();
	CString strAppName = WizExtractFileTitle(strAppFileName);

	CString strSelectedLocation(lpszSelectedLocation);
	//
	switch (ExplorerGetSaveDestination())
	{
	case wizSelectedFolder:
		if (strSelectedLocation.IsEmpty())
		{
			return WizFormatString1(_T("/Location=/%1/"), FOLDER_MY_DRAFTS);
		}
		else
		{
			return WizFormatString1(_T("/Location=%1"), strSelectedLocation);
		}
	case wizPromptSelect:
		return CString(_T("/PromptLocation=1"));
	default:
		return WizFormatString1(_T("/Location=/%1/"), FOLDER_MY_DRAFTS);
	}
}

inline int WizKMCopySelection(HWND hwndOwnerWindow, HWND hwndForegroundWindow, HWND hwndLastIEWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	if (!hwndForegroundWindow)
		return 0;
	//
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strForegroundWindow = WizInt64ToStr(__int64(hwndForegroundWindow));
	CString strLastIEWindow = WizInt64ToStr(__int64(hwndLastIEWindow));
	//
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString5(_T("/OwnerWindow=%1 /ForegroundWindow=%2 /LastIEWindow=%3 /DatabasePath=%4 %5"),
		strOwnerWindow,
		strForegroundWindow,
		strLastIEWindow,
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMCopySelection"), strParams, SW_SHOW);
	//
	return 0;
}


inline int WizKMClipScreenshot(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	Sleep(500);
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString3(_T("/OwnerWindow=%1 /DatabasePath=%2 %3"),
		strOwnerWindow, 
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMClipScreenshot"), strParams, SW_SHOW);
	//
	return 0;
}


inline int WizKMPasteToWiz(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	// TODO: Add your command handler code here
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString3(_T("/OwnerWindow=%1 /DatabasePath=%2 %3"),
		strOwnerWindow,
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMPasteToWiz"), strParams, SW_SHOW);
	//
	return 0;
}




struct WIZKMIMPORTFILESDATA
{
	CString strDatabasePath;
	CString strLocation;
	CWizStdStringArray arrayFile;
	UINT nUpdateDocumentFlags;
	BOOL bDelete;
	//
	WIZKMIMPORTFILESDATA()
	{
		bDelete = FALSE;
		nUpdateDocumentFlags = 0;
	}
};


inline BOOL WizKMImportFilesDataLoadFromFile(LPCTSTR lpszFileName, WIZKMIMPORTFILESDATA& data)
{
	CWizIniFileEx file;
	if (!file.LoadFromFile(lpszFileName))
		return FALSE;
	//
	CString strCommonSection(_T("Common"));
	//
	data.strDatabasePath = file.GetStringDef(strCommonSection, _T("Database"));
	if (data.strDatabasePath.IsEmpty())
		return FALSE;
	//
	data.strLocation = file.GetStringDef(strCommonSection, _T("Location"));
	if (data.strLocation.IsEmpty())
	{
		data.strLocation = CString(_T("/")) + FOLDER_MY_DRAFTS + _T("/");
	}
	//
	data.nUpdateDocumentFlags = file.GetIntDef(strCommonSection, _T("UpdateDocumentFlags"), 0);
	data.bDelete = file.GetBoolDef(strCommonSection, _T("Delete"), FALSE);
	//
	int nCount = file.GetIntDef(strCommonSection, _T("FileCount"), 0);
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strFileName = file.GetStringDef(_T("Files"), WizIntToStr(i));
		if (PathFileExists(strFileName))
		{
			data.arrayFile.push_back(strFileName);
		}
	}
	//
	if (data.bDelete)
	{
		DeleteFile(lpszFileName);
	}
	//
	//data.nUpdateDocumentFlags |= wizUpdateDocumentSaveContentOnly;
	//
	return TRUE;
}



inline BOOL WizKMImportFilesDataSaveToFile(LPCTSTR lpszFileName, const WIZKMIMPORTFILESDATA& data)
{
	CWizIniFileEx file;
	CString strCommonSection(_T("Common"));
	//
	file.SetString(strCommonSection, _T("Database"), data.strDatabasePath);
	file.SetString(strCommonSection, _T("Location"), data.strLocation);
	file.SetString(strCommonSection, _T("UpdateDocumentFlags"), WizIntToStr(data.nUpdateDocumentFlags));
	file.SetString(strCommonSection, _T("FileCount"), WizIntToStr((int)data.arrayFile.size()));
	file.SetString(strCommonSection, _T("Delete"), data.bDelete ? _T("1") : _T("0"));
	//
	int nCount = int(data.arrayFile.size());
	for (int i = 0; i < nCount; i++)
	{
		file.SetString(_T("Files"), WizIntToStr(i), data.arrayFile[i]);
	}
	//
	return file.SaveToUnicodeFile(lpszFileName);
}

inline BOOL WizKMImportFiles(LPCTSTR lpszFileName)
{
	CString strWizShellFileName = WizGetAppPath()+ _T("WizShell.exe");
	CString strParams = WizFormatString2(_T("\"%1\", WizKMImportFiles /CommandFileName=%2"),
		WizGetAppPath() + _T("WizKMControls.dll"),
		lpszFileName);
	//
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	ShellExecute(NULL, _T("open"), strWizShellFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}

inline BOOL WizKMImportFiles(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, UINT nUpdateDocumentFlags, const CWizStdStringArray& arrayFile)
{
	if (arrayFile.empty())
		return FALSE;
	//
	CString strLocation(lpszLocation);
	if (strLocation.IsEmpty())
	{
		strLocation = WizFormatString1(_T("/%1/"), FOLDER_MY_DRAFTS);
	}
	//
	WIZKMIMPORTFILESDATA data;
	data.arrayFile.assign(arrayFile.begin(), arrayFile.end());
	data.strDatabasePath = lpszDatabasePath;
	data.strLocation = strLocation;
	data.nUpdateDocumentFlags = nUpdateDocumentFlags;
	data.bDelete = TRUE;
	//
	CString strFileName = WizKMGetTempPath() + WizIntToStr(GetTickCount()) + _T(".ini");
	//
	if (!WizKMImportFilesDataSaveToFile(strFileName, data))
		return FALSE;
	//
	return WizKMImportFiles(strFileName);
}




const LPCTSTR WIZKM_DATABASE_WINDOW_EXPLORER = _T("Explorer");
const LPCTSTR WIZKM_DATABASE_WINDOW_SYNC_DETAILS = _T("SyncDetails");
const LPCTSTR WIZKM_DATABASE_WINDOW_NOTE = _T("Note");

const LPCTSTR WIZKM_DATABASE_WINDOW_DATABASE_PARH = _T("DatabasePath");
const LPCTSTR WIZKM_DATABASE_WINDOW_STOP_SYNC = _T("StopSync");


class CWizKMDatabaseWindow
{
public:
	CWizKMDatabaseWindow()
	{
	}
	~ CWizKMDatabaseWindow()
	{
		Unregister();
	}
private:
	HWND m_hWnd;
	CString m_strDatabasePath;
	CString m_strType;
public:
	CString GetDatabasePath() const
	{
		return m_strDatabasePath;
	}
	static CString RegularDatabasePath(LPCTSTR lpszDatabasePath)
	{
		CString strDatabasePath = WizGetLongFileName(lpszDatabasePath);
		strDatabasePath.Trim('"');
		strDatabasePath.MakeLower();
		WizPathAddBackslash(strDatabasePath);
		return strDatabasePath;
	}
	static CString GetKeyPathOfDatabase(LPCTSTR lpszDatabasePath)
	{
		CString strDatabasePath = RegularDatabasePath(lpszDatabasePath);
		return CString(WIZKM_REG_KEY_ROOT) + CString(_T("\\WizKMDatabase_")) + WizMd5StringNoSpace(strDatabasePath);
	}
	//
	static HWND GetWindowOfDatabase(LPCTSTR lpszDatabasePath, LPCTSTR lpszType)
	{
		CString strKey(GetKeyPathOfDatabase(lpszDatabasePath));
		CString strVal = WizRegReadStringDef(HKEY_CURRENT_USER, strKey, lpszType, NULL);
		if (strVal.IsEmpty())
			return NULL;
		//
		__int64 nVal = _ttoi64(strVal);
		if (0 == nVal)
			return NULL;
		//
		HWND hWnd = (HWND)nVal;
		if (IsWindow(hWnd))
			return hWnd;
		//
		return NULL;
	}
	//
	static BOOL GetAllWindowsOfDatabase(LPCTSTR lpszDatabasePath, std::vector<HWND>& arrayHwnd)
	{
		CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
		CWizStdStringArray arrayName;
		WizRegEnumValueName(HKEY_CURRENT_USER, strKey, arrayName);
		//
		for (CWizStdStringArray::const_iterator it = arrayName.begin();
			it != arrayName.end();
			it++)
		{
			if (0 == it->CompareNoCase(WIZKM_DATABASE_WINDOW_DATABASE_PARH))
				continue;
			if (0 == it->CompareNoCase(WIZKM_DATABASE_WINDOW_STOP_SYNC))
				continue;

			HWND hWnd = GetWindowOfDatabase(lpszDatabasePath, *it);
			if (hWnd)
			{
				arrayHwnd.push_back(hWnd);
			}
		}
		return TRUE;
	}
	//
	static BOOL QueryStopStatus(LPCTSTR lpszDatabasePath)
	{
		CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
		return WizRegReadBoolDef(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_STOP_SYNC, FALSE);
	}
	static BOOL SetStopStatus(LPCTSTR lpszDatabasePath, BOOL b)
	{
		CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
		return WizRegWriteBool(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_STOP_SYNC, b);
	}
	//
public:
	BOOL Register(LPCTSTR lpszDatabasePath, HWND hWnd, LPCTSTR lpszType)
	{
		m_strDatabasePath = lpszDatabasePath;
		m_hWnd = hWnd;
		m_strType = lpszType;
		//
		CString strKey(GetKeyPathOfDatabase(m_strDatabasePath));
		//
		return WizRegWriteString(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_DATABASE_PARH, m_strDatabasePath)
			&& WizRegWriteString(HKEY_CURRENT_USER, strKey, lpszType, WizInt64ToStr(__int64(hWnd)));
	}
	//
	BOOL Unregister()
	{
		CString strKey(GetKeyPathOfDatabase(m_strDatabasePath));
		return WizRegKeyExists(HKEY_CURRENT_USER, strKey)
			&& WizRegDeleteValue(HKEY_CURRENT_USER, strKey, m_strType);
	}
	//
	void ShowSyncWindow()
	{
		HWND hWnd = GetWindowOfDatabase(m_strDatabasePath, WIZKM_DATABASE_WINDOW_SYNC_DETAILS);
		if (IsWindow(hWnd))
		{
			ShowWindow(hWnd, SW_SHOW);
			SetForegroundWindow(hWnd);
		}
	}
	//
	void StopSync()
	{
		SetStopStatus(m_strDatabasePath, TRUE);
	}
};




struct WIZKMEDITORDATA
{
	CString strName;
	CString strFileName;
	CString strParams;
	BOOL bTextEditor;
	BOOL bUTF8Encoding;
	//
	WIZKMEDITORDATA()
		: bTextEditor(FALSE)
		, bUTF8Encoding(FALSE)
	{
	}
};

typedef std::vector<WIZKMEDITORDATA> CWizKMEditorDataArray;

#define SECTION_EDITOR		_T("Editor")

inline CString WizKMGetWizHtmlEditorName()
{
	return CString(_T("Wiz Html Editor"));
}



inline BOOL WizKMIsWizHtmlEditor(const WIZKMEDITORDATA& data)
{
	CString strFileName = WizGetLongFileName(data.strFileName);
	CString strName = WizExtractFileName(strFileName);
	return 0 == strName.CompareNoCase(_T("WizHtmlEditor.exe"));
}

inline WIZKMEDITORDATA WizKMGetWizHtmlEditor()
{
	WIZKMEDITORDATA data;
	data.strName = WizKMGetWizHtmlEditorName();
	data.strFileName = WizGetAppPath() + _T("WizHtmlEditor.exe");
	return data;
}
inline BOOL WizKMIsWizHtmlEditorInstalled()
{
	return PathFileExists(WizKMGetWizHtmlEditor().strFileName);
}

inline intptr_t WizKMEditorArrayIndexOfFileName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszFileName)
{
	CString strFileName = WizGetLongFileName(lpszFileName);
	//
	size_t nCount = arrayEditor.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (0 == WizGetLongFileName(arrayEditor[i].strFileName).CompareNoCase(strFileName))
		{
			return i;
		}
	}
	//
	return -1;
}
inline intptr_t WizKMEditorArrayIndexOfName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszName)
{
	size_t nCount = arrayEditor.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (0 == arrayEditor[i].strName.CompareNoCase(lpszName))
		{
			return i;
		}
	}
	//
	return -1;
}

inline BOOL WizKMGetEditor(CWizKMEditorDataArray& arrayEditor)
{
	if (WizKMIsWizHtmlEditorInstalled())
	{
		arrayEditor.push_back(WizKMGetWizHtmlEditor());
	}
	//
	CWizKMSettings settings;
	int nCount = settings.GetInt(SECTION_EDITOR, _T("Count"));
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strSectionName = SECTION_EDITOR + CString(_T("_")) + WizIntToStr(i);
		//
		WIZKMEDITORDATA data;
		data.strName = settings.GetStr(strSectionName, _T("Name"));
		data.strFileName = settings.GetStr(strSectionName, _T("FileName"));
		data.strParams = settings.GetStr(strSectionName, _T("CommandLine"));
		data.bTextEditor = settings.GetBool(strSectionName, _T("TextEditor"));
		data.bUTF8Encoding = settings.GetBool(strSectionName, _T("UTF8Encoding"));
		//
		if (0 == WizExtractFileName(data.strFileName).CompareNoCase(_T("WizHtmlEditor.exe")))
			continue;
		//
		if (data.strName.IsEmpty())
			continue;
		if (data.strFileName.IsEmpty())
			continue;
		if (!PathFileExists(data.strFileName))
			continue;
		//
		arrayEditor.push_back(data);
	}
	//
	return TRUE;
}

inline BOOL WizKMSetEditor(const CWizKMEditorDataArray& arrayEditor)
{
	CWizKMSettings settings;
	//
	size_t nCount = arrayEditor.size();
	settings.SetInt(SECTION_EDITOR, _T("Count"), int(nCount));
	//
	for (size_t i = 0; i < nCount; i++)
	{
		const WIZKMEDITORDATA& data = arrayEditor[i];
		CString strSectionName = SECTION_EDITOR + CString(_T("_")) + WizIntToStr(int(i));
		//
		settings.SetStr(strSectionName, _T("Name"), data.strName);
		settings.SetStr(strSectionName, _T("FileName"), data.strFileName);
		settings.SetStr(strSectionName, _T("CommandLine"), data.strParams);
		settings.SetBool(strSectionName, _T("TextEditor"), data.bTextEditor);
		settings.SetBool(strSectionName, _T("UTF8Encoding"), data.bUTF8Encoding);
	}
	//
	return TRUE;
}

inline WIZKMEDITORDATA WizKMGetDefaultEditor()
{
	CWizKMEditorDataArray arrayEditor;
	WizKMGetEditor(arrayEditor);
	//
	CWizKMSettings settings;
	CString strName = settings.GetStr(SECTION_EDITOR, _T("DefaultEditor2"));
	intptr_t nIndex = WizKMEditorArrayIndexOfName(arrayEditor, strName);
	if (-1 != nIndex)
		return arrayEditor[nIndex];
	//
	WIZKMEDITORDATA data;
	//
	return data;
}
inline CString WizKMGetDefaultEditorName()
{
	WIZKMEDITORDATA data = WizKMGetDefaultEditor();
	return data.strName;
}

inline BOOL WizKMSetDefaultEditorName(LPCTSTR lpszName)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_EDITOR, _T("DefaultEditor2"), lpszName);
}


inline BOOL WizKMIsPromptSave()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_EDITOR, _T("PromptSave"), TRUE);
}

inline BOOL WizKMSetPromptSave(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_EDITOR, _T("PromptSave"), b);
}


inline int WizKMGetAutoSaveMinutes()
{
	CWizKMSettings settings;
	return settings.GetInt(SECTION_EDITOR, _T("AutoSaveMinutes"), 3);
}


inline BOOL WizKMSetAutoSaveMinutes(int nMinutes)
{
	CWizKMSettings settings;
	return settings.SetInt(SECTION_EDITOR, _T("AutoSaveMinutes"), nMinutes);
}



inline BOOL WizKMIsAutoSave()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_EDITOR, _T("AutoSaveDocument"), TRUE);
}

inline BOOL WizKMSetAutoSave(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_EDITOR, _T("AutoSaveDocument"), b);
}



#define WIZKM_FOLDER_SETTINGS_SECTION_SORT		_T("Sort")
#define WIZKM_FOLDER_SETTINGS_KEY_SORT_ORDER	_T("SortOrder")
#define WIZKM_FOLDER_SETTINGS_KEY_SORT_BY		_T("SortBy")




inline BOOL WizKMUsingOleDisplayDocument()
{
	LPCTSTR lpszSection = _T("Explorer");
	CWizKMSettings settings;
	return settings.GetBool(lpszSection, _T("UsingOle"), FALSE);
}

inline BOOL WizKMSetUsingOleDisplayDocument(BOOL b)
{
	LPCTSTR lpszSection = _T("Explorer");
	CWizKMSettings settings;
	return settings.SetBool(lpszSection, _T("UsingOle"), b);
}

inline CString WizKMGetDocumentFileType(IWizDocument* pDocument)
{
	if (!pDocument)
		return CString();
	//
	CString strFileType = CWizKMDatabase::GetDocumentFileType(pDocument);
	strFileType.MakeLower();
	return strFileType;
}
inline CString WizKMGetAttachmentFileType(IWizDocumentAttachment* pAttachment)
{
	if (!pAttachment)
		return CString();
	//
	CString strAttachmentFileName = CWizKMDatabase::GetAttachmentFileName(pAttachment);
	CString strExt = WizExtractFileExt(strAttachmentFileName);
	strExt.MakeLower();
	return strExt;
}
//
inline CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocument(IWizDocument* pDocument)
{
	if (!pDocument)
		return NULL;
	//
	CWizDocumentAttachmentArray arrayAttachment;
	CWizKMDatabase::GetDocumentAttachments(pDocument, arrayAttachment);
	//
	if (arrayAttachment.size() != 1)
		return NULL;
	//
	return arrayAttachment[0];
}

//
inline BOOL WizKMDocumentSupportOle(LPCTSTR lpszDocumentFileType)
{
	if (!lpszDocumentFileType)
		return FALSE;
	//
	if (0 == _tcsicmp(lpszDocumentFileType, _T(".pdf"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".doc"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".docx"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".xls"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".xlsx"))
		)
		return TRUE;
	//
	return FALSE;
}
//
inline CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocumentForOleViewing(IWizDocument* pDocument, BOOL bCheckOleConfig = TRUE)
{
	if (!pDocument)
		return NULL;
	//
	if (bCheckOleConfig)
	{
		if (!WizKMUsingOleDisplayDocument())
			return NULL;
	}
	//
	CString strDocumentFileType = WizKMGetDocumentFileType(pDocument);
	if (strDocumentFileType.IsEmpty())
		return NULL;
	//
	CWizDocumentAttachmentArray arrayAttachment;
	CWizKMDatabase::GetDocumentAttachments(pDocument, arrayAttachment);
	//
	CComPtr<IWizDocumentAttachment>  spAttachment = WizKMGetAttachmentOfDocument(pDocument);
	if (!spAttachment)
		return NULL;
	//
	CString strAttachmentFileType = WizKMGetAttachmentFileType(spAttachment);
	if (strDocumentFileType != strAttachmentFileType)
		return NULL;
	//
	if (!WizKMDocumentSupportOle(strDocumentFileType))
		return NULL;
	//
	return spAttachment;
}




inline BOOL WizKMIsEditNoteWithHtmlEditor()
{
	CWizKMSettings settings;
	return settings.GetBool(_T("EditDocument"), _T("EditNoteWithHtmlEditor"), FALSE);
}

inline BOOL WizKMSetEditNoteWithHtmlEditor(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(_T("EditDocument"), _T("EditNoteWithHtmlEditor"), b);
}

#ifdef __WizKMControls_i_h__

inline BOOL WizKMEditDocumentEx(CWizKMDatabase* pDatabase, IWizDocument* pDocument, BOOL bEditDocument)
{
	if (!pDocument)
		return FALSE;
	//
	CString strDatabasePath = pDatabase->GetDatabasePath();
	CString strDocumentGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	//
	CComBSTR bstrType;
	pDocument->get_Type(&bstrType);
	//
	CString strType(bstrType);
	strType.MakeLower();
	//
	if (WizKMIsEditNoteWithHtmlEditor())
	{
		strType.Empty();
	}
	//
	if (strType == _T("note"))
	{
		CString strNoteExeFileName = WizGetAppPath() + _T("WizNote.exe");
		//
		CString strParams = WizFormatString2(_T("/Command=edit_note /DocumentGUID=%1 /DatabasePath=%2"),
			strDocumentGUID,
			strDatabasePath);
		//
		ShellExecute(NULL, _T("open"), strNoteExeFileName, strParams, NULL, SW_SHOW);
		//
		return TRUE;
	}
	else if (strType == _T("todolist"))
	{
		CString strNoteExeFileName = WizGetAppPath() + _T("WizNote.exe");
		//
		CString strParams = WizFormatString2(_T("/Command=edit_todolist /DocumentGUID=%1 /DatabasePath=%2"),
			strDocumentGUID,
			strDatabasePath);
		//
		ShellExecute(NULL, _T("open"), strNoteExeFileName, strParams, NULL, SW_SHOW);
		//
		return TRUE;
	}
	else if (strType == _T("event"))
	{
		CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
		if (!spCommonUI)
			return FALSE;
		//
		VARIANT_BOOL vbRet = VARIANT_FALSE;
		HRESULT hr = spCommonUI->EditCalendarEvent(pDocument, &vbRet);
		return SUCCEEDED(hr);
	}
	else
	{
		if (bEditDocument)
		{
			CString strEditorTempPath = WizKMGetEditorTempPath();
			CString strTempFileName = strEditorTempPath + WizIntToStr(GetTickCount()) + _T(".htm");
			if (FAILED(pDocument->SaveToHtml(CComBSTR(strTempFileName), 0)))
			{
				TOLOG2(_T("Failed to save %1 to file: %2"), CWizKMDatabase::GetDocumentTitle(pDocument), strTempFileName);
			}
			//
			return WizKMEditDocument(strDatabasePath, strTempFileName, strDocumentGUID);
		}
		else
		{
			CString strExeFileName = WizGetAppPath() + _T("WizViewer.exe");
			//
			CString strFileName = CWizKMDatabase::GetDocumentFileName(pDocument);
			//
			CString strParams = WizFormatString1(_T("\"%1\""), strFileName);
			//
			ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
			//
			return TRUE;
		}
	}
}


inline BOOL WizKMEditDocumentEx(IWizDocument* pDocument, BOOL bEditDocument)
{
	if (!pDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spDisp;
	pDocument->get_Database(&spDisp);
	//
	CComQIPtr<IWizDatabase> spDatabase(spDisp);
	if (!spDatabase)
		return FALSE;
	//
	CWizKMDatabase db;
	db.SetDatabase(spDatabase);
	//
	return WizKMEditDocumentEx(&db, pDocument, bEditDocument);
}
inline BOOL WizKMEditDocumentEx(IWizDocument* pDocument)
{
	return WizKMEditDocumentEx(pDocument, TRUE);
}
inline BOOL WizKMViewDocumentEx(IWizDocument* pDocument)
{
	return WizKMEditDocumentEx(pDocument, FALSE);
}

#endif

inline BOOL WizKMTrackDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszDocumentGUID, LPCTSTR lpszDocumentHtmlFileName, HANDLE hProcess, BOOL bDeleteFiles, BOOL bTextFile, BOOL bUTF8)
{
	DWORD dwProcessID = GetProcessId(hProcess);
	//
	COleDateTime tFile = ::WizGetFileModifiedTime(lpszDocumentHtmlFileName);
	CString strFileTime = ::WizDateTimeToString(tFile);
	//
	CString strCommandLine = WizFormatString8(
		_T("/DatabasePath=%1 /DocumentGUID=%2 /DocumentHtmlFileName=%3 /ProcessID=%4 /FileModified=%5 /DeleteFiles=%6 /TextFile=%7 /UTF8=%8"),
		lpszDatabasePath,
		lpszDocumentGUID,
		lpszDocumentHtmlFileName,
		WizInt64ToStr(dwProcessID),
		strFileTime,
		bDeleteFiles ? _T("1") : _T("0"),
		bTextFile ? _T("1") : _T("0"),
		bUTF8 ? _T("1") : _T("0")
		);
	//
	CString strWizShellCommandLine = WizFormatString2(_T("\"%1\", WizKMTrackDocument %2"),
		WizGetAppPath() + _T("WizKMControls.dll"),
		strCommandLine);
	//
#ifdef _DEBUG
	TOLOG(strWizShellCommandLine);
#endif
	//
	return int(ShellExecute(NULL, _T("open"), WizGetAppPath() + _T("WizShell.exe"),
		strWizShellCommandLine, NULL, SW_SHOW)) > 32;
}

inline BOOL WizKMExternalEditorEditDocument(const WIZKMEDITORDATA& data, IWizDocument* pDocument)
{
	CString strTempPath = WizGetSystemTempPath() + WizIntToStr(GetTickCount()) + _T("\\");
	WizEnsurePathExists(strTempPath);
	//
	CString strTempFileName;
	if (data.bTextEditor)
	{
		strTempFileName = strTempPath + WizIntToStr(GetTickCount()) + _T(".txt");
		CString strText = CWizKMDatabase::GetDocumentText(pDocument, 0);
		if (data.bUTF8Encoding)
		{
			if (!WizSaveAnsiTextToAnsiFile(strTempFileName, WizBSTR2STR(CP_UTF8, strText), TRUE, FALSE))
				return FALSE;
		}
		else
		{
			if (!WizSaveUnicodeTextToUnicodeFile(strTempFileName, strText))
				return FALSE;
		}
	}
	else
	{
		strTempFileName = strTempPath + WizIntToStr(GetTickCount()) + _T(".htm");
		//
		long nFlags = 0;
		if (data.bUTF8Encoding)
		{
			nFlags |= wizDocumentToHtmlUTF8;
		}
		//
		HRESULT hr = pDocument->SaveToHtml(CComBSTR(strTempFileName), nFlags);
		if (FAILED(hr))
			return FALSE;
	}
	//
	CString strParams = data.strParams;
	if (strParams.IsEmpty())
	{
		strParams = _T("%FileName%");
	}
	//
	strParams.Replace(_T("%FileName%"), WizFormatString1(_T("\"%1\""), strTempFileName));
	//
	HANDLE hProcess = WizCreateProcess(data.strFileName, strParams, TRUE);
	if (!hProcess)
	{
		return FALSE;
	}
	//
	CComPtr<IDispatch> spDatabaseDisp;
	pDocument->get_Database(&spDatabaseDisp);
	CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
	if (!spDatabase)
		return FALSE;
	//
	CComBSTR bstrDatabasePath;
	spDatabase->get_DatabasePath(&bstrDatabasePath);
	//
	CString strDocumentGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	//
	return WizKMTrackDocument(CString(bstrDatabasePath), strDocumentGUID, strTempFileName, hProcess, TRUE, data.bTextEditor, data.bUTF8Encoding);
}




inline BOOL WizKMIsSingleApp()
{
	CWizKMSettings settings;
	return settings.GetBool(_T("Common"), _T("SingleApp"), TRUE);
}

inline BOOL WizKMSetSingleApp(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(_T("Common"), _T("SingleApp"), b);
}





const LPCTSTR SECTION_GLOBALS = _T("Globals");

inline BOOL IsUseGUIDAsDocumentFileName()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_GLOBALS, _T("GUIDAsDocumentFileName"), FALSE);
}

inline BOOL SetUseGUIDAsDocumentFileName(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_GLOBALS, _T("GUIDAsDocumentFileName"), b);
}




inline BOOL WizKMConvertFileIsConvertToHtml()
{
	CWizKMSettings settings;
	CString strSection(_T("Import"));
	return settings.GetBool(strSection, _T("ConvertToHTML"), TRUE);
}

inline BOOL WizKMConvertFileIsUsingOffice()
{
	CWizKMSettings settings;
	CString strSection(_T("Import"));
	return settings.GetBool(strSection, _T("UseOffice"), TRUE);
}
inline BOOL WizKMConvertFileSetConvertToHtml(BOOL b)
{
	CWizKMSettings settings;
	CString strSection(_T("Import"));
	return settings.SetBool(strSection, _T("ConvertToHTML"), b);
}

inline BOOL WizKMConvertFileSetUsingOffice(BOOL b)
{
	CWizKMSettings settings;
	CString strSection(_T("Import"));
	return settings.SetBool(strSection, _T("UseOffice"), b);
}

inline BOOL WizKMConvertFileNeedToBeAddedToAttachment(LPCTSTR lpszExt)
{
	//CWizKMSettings settings;
	//CString strAllExt = settings.GetStr(_T("ImportFile"), _T("FileExt_AddToAttachment"), _T(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps"));
	CString strAllExt = _T(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps;.et;.pds;.tif;.tiff");
	//
	strAllExt.MakeLower();
	strAllExt = CString(_T(";")) + strAllExt + _T(";");
	//
	CString strExt(lpszExt);
	strExt.MakeLower();
	strExt = CString(_T(";")) + strExt + _T(";");
	//
	return -1 != strAllExt.Find(strExt);
}

inline BOOL WizKMConvertFileToHtml(CWizKMToolsDll& dll, LPCTSTR lpszSrcFileName, CString& strHtmlFileName)
{
	CWizKMSettings settings;
	CString strSection(_T("Import"));
	BOOL bConvertToHTML = settings.GetBool(strSection, _T("ConvertToHTML"), TRUE);
	BOOL bUseOffice = settings.GetBool(strSection, _T("UseOffice"), TRUE);
	//
	if (!bConvertToHTML)
	{
		CString strExt = WizExtractFileExt(lpszSrcFileName);
		strExt.MakeLower();
		//
		if (WizKMConvertFileNeedToBeAddedToAttachment(strExt))
		{
			CString strHtml = WizFormatString1(_T("%1"), lpszSrcFileName);
			strHtmlFileName = WizKMGetTempPath() + WizIntToStr(GetTickCount()) + _T(".htm");
			if (!WizSaveUnicodeTextToUnicodeFile(strHtmlFileName, strHtml))
			{
				bConvertToHTML = TRUE;
			}
		}
		else
		{
			bConvertToHTML = TRUE;
		}
	}
	//
	if (bConvertToHTML)
	{
		long nFlags = 0;
		if (!bUseOffice)
		{
			nFlags |= WIZ_CONVERT_FILE_TO_HTML_USE_INNEL_ONVERTER;
		}
		if (!dll.ConvertToHtmlFile2(lpszSrcFileName, nFlags, strHtmlFileName))
		{
			TOLOG1(_T("Failed to convert %1 to html file"), lpszSrcFileName);
			return FALSE;
		}
	}
	if (!PathFileExists(strHtmlFileName))
		return FALSE;
	//
	return TRUE;
}
inline BOOL WizKMConvertFileToHtml(LPCTSTR lpszSrcFileName, CString& strHtmlFileName)
{
	CWizKMToolsDll dll;
	return WizKMConvertFileToHtml(dll, lpszSrcFileName, strHtmlFileName);
}




inline BOOL WizKMTrackAttachment(IWizDocumentAttachment* pAttachment, HANDLE hProcess)
{
	CComPtr<IWizDocument> spDocument = CWizKMDatabase::GetAttachmentDocument(pAttachment);
	if (!spDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spDatabaseDisp;
	spDocument->get_Database(&spDatabaseDisp);
	CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
	if (!spDatabase)
		return FALSE;
	//
	CComBSTR bstrDatabasePath;
	spDatabase->get_DatabasePath(&bstrDatabasePath);
	//
	CString strAttachmentGUID = CWizKMDatabase::GetObjectGUID(pAttachment);
	CString strAttachmentFileName = CWizKMDatabase::GetAttachmentFileName(pAttachment);
	//
	return WizKMTrackAttachment(CString(bstrDatabasePath), strAttachmentGUID, strAttachmentFileName, hProcess);
}


#ifdef __ATLCTRLX_H__

inline BOOL WizCombineHtmlText(CString& strTextTo, LPCTSTR lpszTextFrom)
{
	/*
	强制获得正文
	*/
	int nInsertPos = (int)WizStrRStrI_Pos(strTextTo, WizGetHtmlContentHiddenTagEnd());
	if (-1 == nInsertPos)
		nInsertPos = (int)WizStrRStrI_Pos(strTextTo, _T("</body"));
	if (-1 == nInsertPos)
		nInsertPos = (int)WizStrRStrI_Pos(strTextTo, _T("</html"));
	if (-1 == nInsertPos)
		nInsertPos = (int)strTextTo.GetLength();
	//
	CString strFrom;
	if (!WizHtmlGetContentByHiddenTag(lpszTextFrom, strFrom))
	{
		if (!WizHTMLGetBodyTextWithoutBodyTag(lpszTextFrom, strFrom))
			return FALSE;
	}
	//
	strTextTo.Insert(nInsertPos, strFrom);
	//
	return TRUE;
}

inline BOOL WizKMCombineDocumentsToHtmlFile(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, CString& strHtmlFileName)
{
	CString strTempPath = WizKMGetTempPath();
	//
	CWizStdStringArray arrayFile;
	//
	size_t nCount = arrayDocument.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CComPtr<IWizDocument> spDocument = arrayDocument[i];
		//
		CString strFileName = CWizKMDatabase::DocumentToTemp(spDocument);
		arrayFile.push_back(strFileName);
	}
	//
	ATLASSERT(nCount == arrayFile.size());
	//
	CString strHTML;
	//
	for (size_t i = 0; i < nCount; i++)
	{
		CString strFileName = arrayFile[i];
		//
		CString strText;
		if (!WizLoadUnicodeTextFromFile(strFileName, strText))
			return FALSE;
		//
		if (-1 != WizStrStrI_Pos(strText, CString(_T("<frameset"))))
		{
			TOLOG(_T("Cannot combine html because html contains frame set"));
			return FALSE;
		}
		//
		if (!WizCombineHtmlText(strHTML, strText))
			return FALSE;
		//
		if (i < nCount - 1)
		{
			if (lpszHtmlSplitter && *lpszHtmlSplitter)
			{
				WizCombineHtmlText(strHTML, lpszHtmlSplitter);
			}
		}
	}
	//
	strHtmlFileName = strTempPath + WizIntToStr(GetTickCount()) + _T("_combine.htm");
	return WizSaveUnicodeTextToUnicodeFile(strHtmlFileName, strHTML);
}

inline BOOL WizKMCombineDocuments(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, LPCTSTR lpszTitle, BOOL bDelete)
{
	if (arrayDocument.size() <= 1)
		return FALSE;
	//
	CWaitCursor wait;
	//
	CString strHtmlFileName;
	if (!WizKMCombineDocumentsToHtmlFile(arrayDocument, lpszHtmlSplitter, strHtmlFileName))
	{
		TOLOG(_T("Failed to combine documents to html file!"));
		return FALSE;
	}
	//
	CComPtr<IWizDocument> spRetDocument = arrayDocument[0];
	HRESULT hr = spRetDocument->UpdateDocument(CComBSTR(strHtmlFileName), wizUpdateDocumentIncludeScript);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to update document!"));
		return FALSE;
	}
	//
	if (lpszTitle && *lpszTitle)
	{
		spRetDocument->ChangeTitleAndFileName(CComBSTR(lpszTitle));
	}
	//
	for (CWizDocumentArray::const_iterator it = arrayDocument.begin() + 1;
		it != arrayDocument.end();
		it++)
	{
		CWizStdStringArray arrayAttachment;
		::CWizKMDatabase::GetDocumentAttachments(*it, arrayAttachment);
		//
		for (CWizStdStringArray::const_iterator itAttachment = arrayAttachment.begin();
			itAttachment != arrayAttachment.end();
			itAttachment++)
		{
			if (PathFileExists(*itAttachment))
			{
				CComPtr<IDispatch> spAttachmentDisp;
				hr = spRetDocument->AddAttachment(CComBSTR(*itAttachment), &spAttachmentDisp);
				if (FAILED(hr))
				{
					TOLOG(_T("Failed to combine attachments!"));
					return FALSE;
				}
			}
		}
		if (bDelete)
		{
			hr = (*it)->Delete();
			if (FAILED(hr))
			{
				TOLOG1(_T("Failed to delete document: %1"), CWizKMDatabase::GetDocumentTitle(*it));
			}
		}
	}
	//
	return TRUE;
}

const LPCTSTR g_lpszCombineDocumentsSection = _T("CombineDocuments");

inline void WizKMGetCombineDocumentSettings(BOOL& bInsertSplitterHtml, CString& strSplitterHtml, BOOL& bDeleteDocuments)
{
	CWizKMSettings settings;
	bInsertSplitterHtml = settings.GetBool(g_lpszCombineDocumentsSection, _T("InsertSpliterHtml"), bInsertSplitterHtml);
	strSplitterHtml = settings.GetStr(g_lpszCombineDocumentsSection, _T("SpliterHtml"), strSplitterHtml);
	bDeleteDocuments = settings.GetBool(g_lpszCombineDocumentsSection, _T("DeleteDocuments"), bDeleteDocuments);
}
inline void WizKMSetCombineDocumentSettings(BOOL bInsertSplitterHtml, LPCTSTR lpszSplitterHtml, BOOL bDeleteDocuments)
{
	CWizKMSettings settings;
	settings.SetBool(g_lpszCombineDocumentsSection, _T("InsertSpliterHtml"), bInsertSplitterHtml);
	settings.SetStr(g_lpszCombineDocumentsSection, _T("SpliterHtml"), lpszSplitterHtml);
	settings.SetBool(g_lpszCombineDocumentsSection, _T("DeleteDocuments"), bDeleteDocuments);
}

inline BOOL WizKMCombineDocuments(IWizDocument* pDocOld, IWizDocument* pDocNew)
{
	BOOL bInsertSplitterHtml = TRUE;
	CString strSplitterHtml;
	BOOL bDeleteDocuments = TRUE;
	//
	WizKMGetCombineDocumentSettings(bInsertSplitterHtml, strSplitterHtml, bDeleteDocuments);
	//
	CString strTitle = CWizKMDatabase::GetDocumentTitle(pDocOld);
	//
	CWizDocumentArray arrayDocument;
	arrayDocument.push_back(pDocOld);
	arrayDocument.push_back(pDocNew);
	return WizKMCombineDocuments(arrayDocument, strSplitterHtml, strTitle, TRUE);
}

#endif