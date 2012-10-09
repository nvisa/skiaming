#ifndef _WIZKMDATABASE_H_
#define _WIZKMDATABASE_H_

#pragma once


#include "WizKMCoreDef.h"

typedef std::vector<CComPtr<IWizTag> > CWizTagArray;
typedef std::vector<CComPtr<IWizStyle> > CWizStyleArray;

typedef std::vector<CComPtr<IWizFolder> > CWizFolderArray;
typedef std::vector<CComPtr<IWizDocument> > CWizDocumentArray;
typedef std::vector<CComPtr<IWizDocumentAttachment> > CWizDocumentAttachmentArray;
typedef std::vector<CComPtr<IWizDocumentParam> > CWizDocumentParamArray;
typedef std::vector<CComPtr<IWizEvent> > CWizEventArray;


typedef std::set<CString> CWizStringSet;


struct WIZKMFOLDERDOCUMENTCOUNTDATA
{
	int nSelf;
	int nIncludeChildren;
	//
	WIZKMFOLDERDOCUMENTCOUNTDATA()
		: nSelf(0)
		, nIncludeChildren(0)
	{
	}
};

typedef std::map<CString, WIZKMFOLDERDOCUMENTCOUNTDATA> CWizFolderDocumentCountMap;
typedef std::map<CString, int> CWizTagDocumentCountMap;




class CWizKMDatabase
{
public:
	CWizKMDatabase();
	virtual ~CWizKMDatabase(void);
protected:
	CComPtr<IWizDatabase> m_spDatabase;
public:
	virtual void SetDatabase(IWizDatabase* pDatabase);
	virtual CComPtr<IWizDatabase> GetDatabase() { return m_spDatabase; }
	//
	BOOL IsModified();
	//
	BOOL GetAttachments(CWizDocumentAttachmentArray& arrayAttachment);
	BOOL GetAttachments(CWizStdStringArray& arrayAttachment);
	//
	BOOL GetRootTags(CWizTagArray& arrayTag);
	BOOL GetTags(CWizTagArray& arrayTag);
	static BOOL GetTags(IWizTag* pParentTag, CWizTagArray& arrayTag);
	BOOL GetRootTagsName(CWizStdStringArray& arrayName);
	BOOL GetTagsName(CWizStdStringArray& arrayName);
	static BOOL GetTagsName(IWizTag* pParentTag, CWizStdStringArray& arrayName);
	//
	BOOL GetStyles(CWizStyleArray& arrayStyle);
	BOOL GetStylesName(CWizStdStringArray& arrayName);
	//
	BOOL CreateRootTag(LPCTSTR lpszName, LPCTSTR lpszDescription, IWizTag** ppTag);
	static BOOL CreateTag(IWizTag* pParentTag, LPCTSTR lpszName, LPCTSTR lpszDescription, IWizTag** ppTag);
	BOOL CreateStyle(LPCTSTR lpszName, LPCTSTR lpszDescription, COLORREF crText, COLORREF crBackground, BOOL bTextBold, int nFlagIndex, IWizStyle** ppStyle);
	//
	BOOL GetFolders(CWizFolderArray& arrayFolder);
	static BOOL GetFolders(IWizFolder* pFolder, CWizFolderArray& arrayFolder);
	CComPtr<IWizFolder> GetRootFolder(UINT nNameStringID, BOOL bCreate);
	CComPtr<IWizFolder> GetRootFolder(LPCTSTR lpszName, BOOL bCreate);
	//
	static CComPtr<IWizFolder> GetChildFolder(IWizFolder* pParentFolder, LPCTSTR lpszName, BOOL bCreate);
	static CComPtr<IWizFolder> GetChildFolderByPath(IWizFolder* pParentFolder, LPCTSTR lpszPath, BOOL bCreate);

	//
	BOOL GetAllDocuments(CWizDocumentArray& arrayDocument);
	BOOL GetAllDocumentsTitle(CWizStdStringArray& arrayDocument);
	BOOL GetDocumentsByTags(IWizTagCollection* pTagCollection, IDispatch** ppDocumentCollectionDisp);
	BOOL GetDocumentsByTagWithChildren(IWizTag* pTag, IDispatch** ppDocumentCollectionDisp);
	//
	BOOL GetDocumentsBySQL(LPCTSTR lpszSQL, IDispatch** ppDocumentCollectionDisp);
	BOOL GetDocumentsBySQL(LPCTSTR lpszSQL, CWizDocumentArray& arrayDocument);
	BOOL GetDocumentsByURL(LPCTSTR lpszURL, CWizDocumentArray& arrayDocument);
	//
	static BOOL GetDocumentsByFolder(IWizFolder* pFolder, IDispatch** ppDocumentCollectionDisp);
	static BOOL GetDocumentsByFolder(IWizFolder* pFolder, CWizDocumentArray& arrayDocument);
	//
	//
	static BOOL GetDocumentsTitleSet(IWizFolder* pFolder, CWizStringSet& setDocument);
	static CComPtr<IWizFolder> GetDocumentFolder(IWizDocument* pDocument);
	//
	static CString DocumentToTemp(IWizDocument* pDocument, long nFlags = 0);
	//
	CString GetDatabasePath();
	//
	template <class T>
	static CString GetDatabasePath(T* p)
	{
		if (!p)
			return CString();
		//
		CComPtr<IDispatch> spDatabaseDisp;
		HRESULT hr = p->get_Database(&spDatabaseDisp);
		if (FAILED(hr))
			return CString();
		//
		CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
		if (!spDatabase)
			return CString();
		//
		CComBSTR bstrPath;
		spDatabase->get_DatabasePath(&bstrPath);
		return CString(bstrPath);
	}
	template <class T>
	static CComPtr<IWizDatabase> GetDatabase(T* p)
	{
		if (!p)
			return NULL;
		//
		CComPtr<IDispatch> spDatabaseDisp;
		HRESULT hr = p->get_Database(&spDatabaseDisp);
		if (FAILED(hr))
			return NULL;
		//
		CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
		if (!spDatabase)
			return NULL;
		//
		return spDatabase;
	}
	static CString GetFolderPath(IWizFolder* pFolder);
	static CString GetFolderLocation(IWizFolder* pFolder);
	static CString GetFolderDisplayName(IWizFolder* pFolder, long nFlags = 0);
	static CString GetFolderDisplayTemplate(IWizFolder* pFolder);
	static BOOL GetFolderIsRoot(IWizFolder* pFolder);
	static BOOL GetFolderIsSync(IWizFolder* pFolder);
	static BOOL GetFolderIsDeletedItems(IWizFolder* pFolder);
	static BOOL CanRenameFolder(IWizFolder* pFolder);
	static CString GetFolderIconFileName(IWizFolder* pFolder);
	static HICON GetFolderIcon(IWizFolder* pFolder);
	static CString GetFolderSortOrder(IWizFolder* pFolder);
	static CString GetFolderSortBy(IWizFolder* pFolder);
	static BOOL SetFolderSortOrder(IWizFolder* pFolder, LPCTSTR lpszSortOrder);
	static BOOL SetFolderSortBy(IWizFolder* pFolder, LPCTSTR lpszSortBy);
	static BOOL GetFolderEncrypt(IWizFolder* pFolder);
	//
	BOOL CreateRootFolder(LPCTSTR lpszName, BOOL bSync, IWizFolder** ppFolder);
	BOOL CreateRootFolder2(LPCTSTR lpszName, BOOL bSync, LPCTSTR lpszIconFileName, IWizFolder** ppFolder);
	static BOOL CreateFolder(IWizFolder* pParentFolder, LPCTSTR lpszName, IWizFolder** ppFolder);
	//
	CComPtr<IWizFolder> GetDeletedItemsFolder();
	//
	static BOOL GetDocumentIsSync(IWizDocument* pDocument);
	static BOOL GetAttachmentIsSync(IWizDocumentAttachment* pAttachment);
	//
	static CString GetDocumentTitle(IWizDocument* pDocument);
	static CString GetDocumentLocation(IWizDocument* pDocument);
	static CString GetDocumentSEO(IWizDocument* pDocument);
	static CString GetDocumentAuthor(IWizDocument* pDocument);
	static int GetDocumentReadCount(IWizDocument* pDocument);
	static CString GetDocumentKeywords(IWizDocument* pDocument);
	static CString GetDocumentType(IWizDocument* pDocument);
	static CString GetDocumentOwner(IWizDocument* pDocument);
	static CString GetDocumentFileType(IWizDocument* pDocument);
	static COleDateTime GetDocumentDateCreated(IWizDocument* pDocument);
	static COleDateTime GetDocumentDateModified(IWizDocument* pDocument);
	static COleDateTime GetDocumentDataDateModified(IWizDocument* pDocument);
	static COleDateTime GetDocumentDateAccessed(IWizDocument* pDocument);
	static CString GetDocumentStyleGUID(IWizDocument* pDocument);
	static CString GetDocumentFileName(IWizDocument* pDocument);
	static BOOL GetDocumentTagGUIDs(IWizDocument* pDocument, CWizStdStringArray& arrayTagGUID);
	static CComPtr<IStream> GetDocumentDataStream(IWizDocument* pDocument);
	static CComPtr<IStream> GetAttachmentDataStream(IWizDocumentAttachment* pAttachment);
	static int GetDocumentAttachmentCount(IWizDocument* pDocument);
	static BOOL GetDocumentParams(IWizDocument* pDocument, std::vector<WIZDOCUMENTPARAMDATA>& arrayParam);
	static BOOL GetDocumentAttachments(IWizDocument* pDocument, CWizDocumentAttachmentArray& arrayAttachment);
	static BOOL GetDocumentAttachments(IWizDocument* pDocument, CWizStdStringArray& arrayAttachmentFileName);
	static BOOL GetDocumentParams(IWizDocument* pDocument, CWizDocumentParamArray& arrayParam);
	static CString GetDocumentIconFileName(IWizDocument* pDocument);
	static long GetDocumentProtected(IWizDocument* pDocument);

	static CString GetDocumentParam(IWizDocument* pDocument, LPCTSTR lpszParamName);
	static int GetDocumentParamInt(IWizDocument* pDocument, LPCTSTR lpszParamName, int nDef);
	static BOOL GetDocumentParamBool(IWizDocument* pDocument, LPCTSTR lpszParamName, BOOL bDef);
	static COLORREF GetDocumentParamColor(IWizDocument* pDocument, LPCTSTR lpszParamName, COLORREF crDef);
	static COleDateTime GetDocumentParamTime(IWizDocument* pDocument, LPCTSTR lpszParamName, const COleDateTime& tDef);
	static BOOL GetDocumentParamLine(IWizDocument* pDocument, LPCTSTR lpszParamName, CWizKMDocumentParamLine& line);
	//
	static BOOL SetDocumentParam(IWizDocument* pDocument, LPCTSTR lpszParamName, LPCTSTR lpszParamValue);
	static BOOL SetDocumentParamInt(IWizDocument* pDocument, LPCTSTR lpszParamName, int n);
	static BOOL SetDocumentParamBool(IWizDocument* pDocument, LPCTSTR lpszParamName, BOOL b);
	static BOOL SetDocumentParamColor(IWizDocument* pDocument, LPCTSTR lpszParamName, COLORREF cr);
	static BOOL SetDocumentParamTime(IWizDocument* pDocument, LPCTSTR lpszParamName, const COleDateTime& t);

	static BOOL GetDocumentTags(IWizDocument* pDocument, CWizTagArray& arrayTag);
	static BOOL GetDocumentTagsText(IWizDocument* pDocument, CString& strTagText);
	static BOOL GetDocumentTagsNameStringArray(IWizDocument* pDocument, CWizStdStringArray& arrayTagName);
	static CString GetDocumentText(IWizDocument* pDocument, UINT nFlags);
	static BOOL GetDocumentText(IWizDocument* pDocument, UINT nFlags, CString& strText);
	static CString GetDocumentHtml(IWizDocument* pDocument);
	BOOL GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, IWizDocumentCollection** ppDocumentCollection);
	BOOL GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, IDispatch** ppDocumentCollectionDisp);
	BOOL GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, CWizDocumentArray& arrayDocument);
	//
	BOOL GetVirtualFolders(CWizStdStringArray& arrayVirtualFolderName);
	BOOL GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, IWizDocumentCollection** ppDocumentCollection);
	BOOL GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, IDispatch** ppDocumentCollectionDisp);
	BOOL GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, CWizDocumentArray& arrayDocument);
	CString GetVirtualFolderIcon(LPCTSTR lpszVirtualFolderName);
	//
	BOOL GetAllFoldersDocumentCount(long nFlags, CWizFolderDocumentCountMap& mapDocumentCount);
	BOOL GetAllTagsDocumentCount(long nFlags, CWizTagDocumentCountMap& mapDocumentCount);
	//
	static CString GetParamValue(IWizDocumentParam* pParam);
	//
	static int GetAttachmentSize(IWizDocumentAttachment* pAttachment);
	static CString GetAttachmentFileName(IWizDocumentAttachment* pAttachment);
	static CComPtr<IWizDocument> GetAttachmentDocument(IWizDocumentAttachment* pAttachment);
	static CString GetAttachmentDocumentTitle(IWizDocumentAttachment* pAttachment);
	static CString GetAttachmentDocumentGUID(IWizDocumentAttachment* pAttachment);
	static BOOL GetDocumentAttachmentNameSet(IWizDocument* pDocument, CWizStringSet& setAttachment);
	//
	template <class T>
	static CString GetObjectGUID(T* pT)
	{
		CComBSTR bstr;
		pT->get_GUID(&bstr);
		return CString(bstr);
	}

	template <class T>
	static CString GetObjectName(T* pT)
	{
		CComBSTR bstr;
		pT->get_Name(&bstr);
		return CString(bstr);
	}
	template <class T>
	static CString GetObjectURL(T* pT)
	{
		CComBSTR bstr;
		pT->get_URL(&bstr);
		return CString(bstr);
	}
	template <class T>
	static CString GetObjectDescription(T* pT)
	{
		CComBSTR bstr;
		pT->get_Description(&bstr);
		return CString(bstr);
	}
	template <class T>
	static COleDateTime GetObjectModified(T* pT)
	{
		DATE dt = 0;
		pT->get_DateModified(&dt);
		return dt;
	}
	template <class T>
	static COleDateTime GetObjectInfoModified(T* pT)
	{
		DATE dt = 0;
		pT->get_InfoDateModified(&dt);
		return dt;
	}
	template <class T>
	static COleDateTime GetObjectDataModified(T* pT)
	{
		DATE dt = 0;
		pT->get_DataDateModified(&dt);
		return dt;
	}
	template <class T>
	static COleDateTime GetObjectParamModified(T* pT)
	{
		DATE dt = 0;
		pT->get_ParamDateModified(&dt);
		return dt;
	}
	template <class T>
	static CString GetObjectInfoMD5(T* pT)
	{
		CComBSTR bstr;
		pT->get_InfoMD5(&bstr);
		return CString(bstr);
	}
	template <class T>
	static CString GetObjectDataMD5(T* pT)
	{
		CComBSTR bstr;
		pT->get_DataMD5(&bstr);
		return CString(bstr);
	}
	template <class T>
	static CString GetObjectParamMD5(T* pT)
	{
		CComBSTR bstr;
		pT->get_ParamMD5(&bstr);
		return CString(bstr);
	}
	//
	static COLORREF GetStyleTextColor(IWizStyle* pStyle);
	static COLORREF GetStyleBackgroundColor(IWizStyle* pStyle);
	static BOOL GetStyleTextBold(IWizStyle* pStyle);
	static int GetStyleFlagIndex(IWizStyle* pStyle);
	//
	CComPtr<IWizTag> GetTagByGUID(LPCTSTR lpszGUID);
	CComPtr<IWizStyle> GetStyleByGUID(LPCTSTR lpszGUID);
	CComPtr<IWizDocument> GetDocumentByGUID(LPCTSTR lpszGUID);
	CComPtr<IWizDocumentAttachment> GetAttachmentByGUID(LPCTSTR lpszGUID);
	//
	static CString GetParentTagGUID(IWizTag* pTag);
	static CComPtr<IWizTag> GetParentTag(IWizTag* pTag);
	//
	static int GetDeletedGUIDType(IWizDeletedGUID* pGUID);
	static COleDateTime GetDeletedGUIDTime(IWizDeletedGUID* pGUID);
	//
	CComPtr<IDispatch> GetObjectsByTime(LPCTSTR lpszObjectType, const COleDateTime& t);
	CComPtr<IDispatch> GetModifiedObjects(LPCTSTR lpszObjectType);
	//
	CString GetMeta(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey);
	BOOL SetMeta(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, LPCTSTR lpszValue);
	__int64 GetMetaInt64(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, __int64 nDef);
	BOOL SetMetaInt64(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, __int64 nVal);
	//
	BOOL Search(LPCTSTR lpszKeywords, long nFlags, IWizFolder* pFolder, long nMaxResults, IDispatch** ppDocumentCollectionDisp);
	BOOL Search(LPCTSTR lpszKeywords, long nFlags, IWizFolder* pFolder, long nMaxResults, IWizDocumentCollection** ppDocumentCollection);
	
	BOOL GetCalendarEvents(const COleDateTime& tStart, const COleDateTime& tEnd, CWizDocumentArray& arrayDocument);
	BOOL GetCalendarEvents(const COleDateTime& tStart, const COleDateTime& tEnd, CWizEventArray& arrayEvent);
	//
	static CString DocumentToWizKMURL(IWizDocument* pDocument);
	static CString AttachmentToWizKMURL(IWizDocumentAttachment* pAttachment);
	static BOOL IsWizKMURL(LPCTSTR lpszURL);
	static BOOL IsWizKMDocumentURL(LPCTSTR lpszURL);
	static BOOL IsWizKMAttachmentURL(LPCTSTR lpszURL);
	static CString WizKMURLGetCommand(LPCTSTR lpszURL);
	static CString WizKMURLGetParamValue(LPCTSTR lpszURL, LPCTSTR lpszParamName);
	static CString WizKMURLGetGUID(LPCTSTR lpszURL);
	static CString GetDocumentGUIDFromWizKMURL(LPCTSTR lpszURL);
	static CString GetAttachmentGUIDFromWizKMURL(LPCTSTR lpszURL);
	CComPtr<IWizDocument> GetDocumentFromWizKMURL(LPCTSTR lpszURL);
	CComPtr<IWizDocumentAttachment> GetAttachmentFromWizKMURL(LPCTSTR lpszURL);
	//
	static CComPtr<IWizDocument> CreateDocument2(IWizFolder* pFolder, LPCTSTR lpszTitle, LPCTSTR lpszURL);
	//
	CComPtr<IWizFolder> GetFolderByLocation(LPCTSTR lpszLocation, BOOL bCreate);
	CComPtr<IWizTag> GetTagByName(LPCTSTR lpszTagName, BOOL bCreate, LPCTSTR lpszRootTagNameForCreate);
	CComPtr<IWizTag> GetRootTagByName(LPCTSTR lpszTagName, BOOL bCreate);
	
	CComPtr<IWizStyle> GetStyleByName(LPCTSTR lpszStyleName);
	//
	BOOL BackupAll(LPCTSTR lpszPath);
	BOOL BackupIndex();
	//
	CString GetUserName();
	BOOL SetUserName(LPCTSTR lpszUserName);
	CString GetEncryptedPassword();
	CString GetUserPassword();
	BOOL ChangePassword(LPCTSTR lpszOldPassword, LPCTSTR lpszNewPassword);
	UINT GetPasswordFlags();
	BOOL SetPasswordFlags(UINT nFlags);
	CString GetUserType();
	//
	static CComPtr<IWizDocument> GetEventDocument(IWizEvent* pEvent);
	//
	CString GetKnownRootTagName(LPCTSTR lpszName);
	//
	BOOL GetCert(CString& strN, CString& stre, CString& strEncrypted_d, CString& strHint);
	BOOL SetCert(LPCTSTR lpszN, LPCTSTR lpsze, LPCTSTR lpszEncrypted_d, LPCTSTR lpszHint, long nFlags, __int64 nWindowHandle);
	//
	BOOL IsUseWizServer();
	BOOL SetUseWizServer(BOOL b);
};

class CWizKMDatabaseLocker
{
public:
	CWizKMDatabaseLocker(IWizDatabase* pDatabase)
		: m_spDatabase(pDatabase)
	{
		m_spDatabase->BeginUpdate();
	}
	CWizKMDatabaseLocker(CWizKMDatabase* pDatabase)
		: m_spDatabase(pDatabase->GetDatabase())
	{
		m_spDatabase->BeginUpdate();
	}
	~CWizKMDatabaseLocker()
	{
		m_spDatabase->EndUpdate();
	}
private:
	CComPtr<IWizDatabase> m_spDatabase;
};


class CWizKMDocumentParamLocker
{
public:
	CWizKMDocumentParamLocker(IWizDocument* pDocument)
		: m_spDocument(pDocument)
	{
		m_spDocument->BeginUpdateParams();
	}
	~CWizKMDocumentParamLocker()
	{
		m_spDocument->EndUpdateParams();
	}
private:
	CComPtr<IWizDocument> m_spDocument;
};



inline CString WizKMGetDateYearMonthFolderPath()
{
	COleDateTime t = WizGetCurrentTime();
	//
	SYSTEMTIME st;
	t.GetAsSystemTime(st);
	//
	TCHAR szMonth[MAX_PATH] = {0};
	GetDateFormat(GetUserDefaultLCID(), 0, &st, _T("MMMM"), szMonth, MAX_PATH);
	//
	CString strIntMonth;
	strIntMonth.Format(_T("%02d"), st.wMonth);
	//
	//CString strPath = WizFormatString3(_T("%1\\%2 %3"), WizIntToStr(t.GetYear()), strIntMonth, szMonth);
	CString strPath = WizFormatString2(_T("%1-%2"), WizIntToStr(t.GetYear()), strIntMonth);
	//
	return strPath;
}

inline CString WizKMGetMonthFolderPath(LPCTSTR lpszDatabasePath, LPCTSTR lpszRootFolderName)
{
	CString strDatabasePath(lpszDatabasePath);
	WizPathAddBackslash(strDatabasePath);
	//
	return strDatabasePath + lpszRootFolderName + _T("\\") + WizKMGetDateYearMonthFolderPath();
}
inline CString WizKMGetMonthFolderLocation(LPCTSTR lpszRootFolderName)
{
	CString strLocation = CString(_T("/")) + lpszRootFolderName + _T("/") + WizKMGetDateYearMonthFolderPath() + _T("/");
	strLocation.Replace('\\', '/');
	return strLocation;
}


inline CComPtr<IWizFolder> WizKMGetMonthFolder(CWizKMDatabase* pDatabase, LPCTSTR lpszRootFolderName)
{
	CComPtr<IWizFolder> spRootFolder = pDatabase->GetRootFolder(lpszRootFolderName, TRUE);
	if (!spRootFolder)
	{
		TOLOG1(_T("Failed to create root folder: %1"), lpszRootFolderName);
		return 0;
	}
	//
	CComPtr<IWizFolder> spMonthFolder = CWizKMDatabase::GetChildFolderByPath(spRootFolder, WizKMGetDateYearMonthFolderPath(), TRUE);
	if (!spMonthFolder)
	{
		TOLOG(_T("Failed to create month folder!"));
		return FALSE;
	}
	//
	return spMonthFolder;
}


inline CString WizKMCalendarTagsGetRootTagName(CWizKMDatabase* pDatabase)
{
	return pDatabase->GetKnownRootTagName(_T("Calendar"));
}

inline BOOL WizKMCalendarTagsGetAllTagsName(CWizKMDatabase* pDatabase, CWizStdStringArray& arrayTagName)
{
	CString strTagName = WizKMCalendarTagsGetRootTagName(pDatabase);
	//
	CComPtr<IWizTag> spTag = pDatabase->GetRootTagByName(strTagName, TRUE);
	if (!spTag)
		return FALSE;
	//
	return CWizKMDatabase::GetTagsName(spTag, arrayTagName);
}



const LPCTSTR g_lpszDocumentCustomIDParamName = _T("DocumentCustomID");
const LPCTSTR g_lpszDocumentCustomModifiedParamName = _T("DocumentCustomModified");

inline CString WizKMStringToDocumentCustomID(LPCTSTR lpszIDString)
{
	CString str(lpszIDString);
	//
	return WizPasswordToMd5StringNoSpace(str);
}

inline BOOL WizKMSetDocumentCustomIDByString(IWizDocument* pDocument, LPCTSTR lpszIDString)
{
	return SUCCEEDED(pDocument->put_ParamValue(CComBSTR(g_lpszDocumentCustomIDParamName), CComBSTR(WizKMStringToDocumentCustomID(lpszIDString))));
}
inline BOOL WizKMSetDocumentCustomIDByID(IWizDocument* pDocument, LPCTSTR lpszCustomID)
{
	return SUCCEEDED(pDocument->put_ParamValue(CComBSTR(g_lpszDocumentCustomIDParamName), CComBSTR(lpszCustomID)));
}


struct WIZKMTAGDATA
{
	int nIndex;
	CComPtr<IWizTag> spTag;
	//
	WIZKMTAGDATA(IWizTag* pTag, int index)
		: spTag(pTag)
		, nIndex(index)
	{
	}
	//
	CString GetName() const
	{
		return CWizKMDatabase::GetObjectName(spTag.p);
	}
};



inline CString WizKMGetURLDownloadToDocumentDllFileName()
{
	return WizGetAppPath() + _T("WizKMControls.dll");
}

inline BOOL WizKMOverwriteDocument(CWizKMDatabase* pDatabase, IWizDocument* pDocument, long nUpdateDocumentFlags)
{
	CString strDatabasePath = pDatabase->GetDatabasePath();
	CString strDocumentGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	CString strURL = CWizKMDatabase::GetObjectURL(pDocument);
	if (strURL.IsEmpty())
		return FALSE;
	//
	CString strParams = WizFormatString5(_T("\"%1\", WizKMURLDownloadToDocument /DatabasePath=%2 /OverwriteDocumentGUID=%3 /UpdateDocumentFlags=%4 /URL=%5"),
		WizKMGetURLDownloadToDocumentDllFileName(),
		strDatabasePath,
		strDocumentGUID,
		WizIntToStr(nUpdateDocumentFlags),
		strURL);
	//
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	CString strExeFileName = WizGetAppPath() + _T("WizShell.exe");
	ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}

inline BOOL WizKMOverwriteDocumentWholePage(CWizKMDatabase* pDatabase, IWizDocument* pDocument)
{
	return WizKMOverwriteDocument(pDatabase, pDocument, 0);
}

inline BOOL WizKMOverwriteDocumentContentOnly(CWizKMDatabase* pDatabase, IWizDocument* pDocument)
{
	return WizKMOverwriteDocument(pDatabase, pDocument, wizUpdateDocumentSaveContentOnly | wizUpdateDocumentAllowAutoGetContent);
}



inline BOOL WizKMSaveURL(LPCTSTR lpszURL)
{
	CString strURL = (lpszURL);
	if (strURL.IsEmpty())
		return FALSE;
	//
	CString strParams = WizFormatString2(_T("\"%1\", WizKMURLDownloadToDocument /URL=%2"),
		WizKMGetURLDownloadToDocumentDllFileName(),
		strURL);
	//
	CString strExeFileName = WizGetAppPath() + _T("WizShell.exe");
	ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}
inline CString WizKMGetSaveURLCommandLineForOpera()
{
	CString strExeFileName = WizGetAppPath() + _T("WizShell.exe");
	CString strCommandLine = WizFormatString2(_T("Execute program, \"%1\", \"%2, WizKMURLDownloadToDocument /ShowProgress=1 /URL=%u /CacheFile=%s\""),
		strExeFileName,
		WizGetShortFileName(WizKMGetURLDownloadToDocumentDllFileName()));
	//
	return strCommandLine;
}



template <class TElementInterface>
inline BOOL WizKMObjectIsEqual(TElementInterface* p1, TElementInterface* p2)
{
	if (!p1 && !p2)
		return TRUE;
	//
	if (!p1 || !p2)
		return FALSE;
	//
	CComBSTR bstrGUID1;
	CComBSTR bstrGUID2;
	p1->get_GUID(&bstrGUID1);
	p2->get_GUID(&bstrGUID2);
	//
	if (!bstrGUID1 || !bstrGUID2)
		return FALSE;
	//
	return 0 == wcscmp(bstrGUID1, bstrGUID2);
}

template <>
inline BOOL WizKMObjectIsEqual(IWizFolder* p1, IWizFolder* p2)
{
	if (!p1 && !p2)
		return TRUE;
	//
	if (!p1 || !p2)
		return FALSE;
	//
	CComBSTR bstrFullPath1;
	CComBSTR bstrFullPath2;
	p1->get_FullPath(&bstrFullPath1);
	p2->get_FullPath(&bstrFullPath2);
	//
	if (!bstrFullPath1 || !bstrFullPath2)
		return FALSE;
	//
	return 0 == _wcsicmp(bstrFullPath1, bstrFullPath2);
}

template <class TCollectionInterface, class TElementInterface>
BOOL WizKMCollectionIsEqual(IDispatch* p1, IDispatch* p2)
{
	CComQIPtr<TCollectionInterface> sp1(p1);
	CComQIPtr<TCollectionInterface> sp2(p2);
	//
	if (!sp1 && !sp2)
		return TRUE;
	//
	if (!sp1 || !sp2)
		return FALSE;
	//
	long nCount1 = 0;
	sp1->get_Count(&nCount1);
	long nCount2 = 0;
	sp2->get_Count(&nCount2);
	//
	if (nCount1 != nCount2)
		return FALSE;
	//
	if (0 == nCount1)
		return TRUE;
	//
	std::vector<CComPtr<TElementInterface> > array1;
	if (!WizCollectionDispatchToArray<TCollectionInterface, TElementInterface>(p1, array1))
		return FALSE;
	//
	std::vector<CComPtr<TElementInterface> > array2;
	if (!WizCollectionDispatchToArray<TCollectionInterface, TElementInterface>(p2, array2))
		return FALSE;
	//
	std::set<CString> set1;
	for (std::vector<CComPtr<TElementInterface> >::const_iterator it = array1.begin(); it != array1.end(); it++)
	{
		CComPtr<TElementInterface> spElem = *it;
		//
		CComBSTR bstrGUID;
		spElem->get_GUID(&bstrGUID);
		//
		set1.insert(CString(bstrGUID));
	}
	//
	for (std::vector<CComPtr<TElementInterface> >::const_iterator it = array2.begin(); it != array2.end(); it++)
	{
		CComPtr<TElementInterface> spElem = *it;
		//
		CComBSTR bstrGUID;
		spElem->get_GUID(&bstrGUID);
		//
		if (set1.find(CString(bstrGUID)) == set1.end())
			return FALSE;
	}
	//
	return TRUE;
}


/*
inline BOOL WizKMCreateSimpleDocument(CWizKMIndexDatabase& index, LPCTSTR lpszRootFolderName, LPCTSTR lpszTitle, LPCTSTR lpszHtml, LPCTSTR lpszAbstractHtml, const CWizStdStringArray& arrayResourceFile)
{
	CWaitCursor wait;
	//
	CString strLocation = WizKMGetMonthFolderLocation(lpszRootFolderName);
	//
	CString strTitle(lpszTitle);
	index.GetNextTitle(strLocation, strTitle);
	//
	CString strName = WizMakeValidFileNameNoPathReturn(strTitle) + _T(".ziw");
	CString strFileName = index.LocationToPath(strLocation) + strName;
	WizGetNextFileName(strFileName);
	//
	CString strPath = WizExtractFilePath(strFileName);
	if (!WizEnsurePathExistsEx(strPath))
	{
		TOLOG1(_T("Failed to create path: %1"), strPath);
		return FALSE;
	}
	//
	CString strHtml(lpszHtml);
	CString strAbstractHtml(lpszAbstractHtml);
	//
	CWizZipFile zip;
	if (!zip.Create(strFileName))
	{
		TOLOG(_T("Failed to create zip file!"));
		return FALSE;
	}
	//
	if (!zip.AddUnicodeText(strHtml, _T("index.html")))
	{
		TOLOG(_T("Failed to add index unicode text to zip!"));
		return FALSE;
	}
	if (!zip.AddUnicodeText(strHtml, _T("wiz_full.html")))
	{
		TOLOG(_T("Failed to add full unicode text to zip!"));
		return FALSE;
	}
	if (!zip.AddUnicodeText(strHtml, _T("wiz_mobile.html")))
	{
		TOLOG(_T("Failed to add mobile unicode text to zip!"));
		return FALSE;
	}
	if (!zip.AddUnicodeText(strAbstractHtml, _T("wiz_abstract.html")))
	{
		TOLOG(_T("Failed to add abstract unicode text to zip!"));
		return FALSE;
	}
	if (!zip.AddData((const BYTE *)g_lpszZiwMeta, strlen(g_lpszZiwMeta), _T("meta.xml")))
	{
		TOLOG(_T("Failed to add meta.xml to zip!"));
		return FALSE;
	}
	//
	for (CWizStdStringArray::const_iterator it = arrayResourceFile.begin();
		it != arrayResourceFile.end();
		it++)
	{
		CString strResourceName = CString(_T("index_files/")) + WizExtractFileName(*it);
		if (!zip.AddFile(*it, strResourceName))
		{
			TOLOG1(_T("Failed to add resource file: %1"), *it);
		}
	}
	//
	if (!zip.Close())
	{
		TOLOG(_T("Failed to save zip file!"));
		return FALSE;
	}
	//
	WIZDOCUMENTDATA data;
	if (!index.CreateDocument(strTitle, WizExtractFileName(strFileName), strLocation, NULL, data))
	{
		TOLOG(_T("Failed to create document!"));
		return FALSE;
	}
	//
	index.UpdateDocumentDataMD5(data, strFileName);
	//
	return TRUE;
}

inline BOOL WizKMCreateSimpleDocument(CWizKMIndexDatabase& index, LPCTSTR lpszRootFolderName, LPCTSTR lpszTitle, LPCTSTR lpszHtml, LPCTSTR lpszAbstractHtml)
{
	CWizStdStringArray arrayResourceFile;
	return WizKMCreateSimpleDocument(index, lpszRootFolderName, lpszTitle, lpszHtml, lpszAbstractHtml, arrayResourceFile);
}


*/


#ifdef IDS_UNTITLED
inline CString WizKMAutoGetTitleFromText(LPCTSTR lpszText)
{
	CString strText(lpszText);
	strText.Trim();
	//
	if (strText.IsEmpty())
	{
		strText = WizFormatString0(IDS_UNTITLED);
	}
	//
	CString strTitle;
	//
	int nPos = strText.Find('\n');
	if (-1 == nPos)
	{
		strTitle = strText;
	}
	else
	{
		strTitle = strText.Left(nPos);
	}
	//
	if (strTitle.GetLength() > 100)
	{
		strTitle = strTitle.Left(100);
	}
	//
	strTitle = WizFormatString2(_T("%1 %2"), WizKMGetDateTimeForTitle(::WizGetCurrentTime()), strTitle);
	//
	return strTitle;
}

#endif

inline CString WizKMSplitText(LPCTSTR lpszText, int nPercent)
{
	if (!lpszText)
		return CString();
	//
	CString strText(lpszText);
	//
	int nLength = strText.GetLength();
	if (strText.GetLength() < 100)
		return strText;
	//
	if (nPercent < 10)
		nPercent = 10;
	if (nPercent >= 100)
		nPercent = 10;
	//
	//
	int nNewLength = int(nLength * nPercent / 100.0);
	if (0 == nNewLength)
		return strText;
	if (nNewLength >= nLength)
		return strText;
	//
	CString strNewText = strText.Left(nNewLength);
	return strNewText;
}

/*
inline BOOL WizKMCreateSimpleDocument(CWizKMIndexDatabase& index, LPCTSTR lpszRootFolderName, LPCTSTR lpszText)
{
	CString strAbstract = WizKMSplitText(lpszText, 30);
	CString strTitle = WizKMAutoGetTitleFromText(lpszText);
	//
	CString strHtml(lpszText);
	if (!WizConvertTextToHTML_DefaultTemplate(strTitle, strHtml))
	{
		TOLOG(_T("Failed to convert text to html!"));
		return FALSE;
	}
	//
	CString strAbstractHtml(strAbstract);
	if (!WizConvertTextToHTML_DefaultTemplate(strTitle, strAbstractHtml))
	{
		TOLOG(_T("Failed to convert summary text to html!"));
		return FALSE;
	}

	//
	CWizStdStringArray arrayResourceFile;
	return WizKMCreateSimpleDocument(index, lpszRootFolderName, strTitle, strHtml, strAbstractHtml, arrayResourceFile);
}

*/

struct WIZKMSTYLEDATA
{
	COLORREF crText;
	COLORREF crBack;
	BOOL bBold;
	int nFlag;
	BOOL bDefault;
	//
	WIZKMSTYLEDATA()
		: bDefault(FALSE)
	{
		crText = RGB(0, 0, 0);
		crBack = RGB(255, 255, 255);
		bBold = FALSE;
		nFlag = -1;
	}
};

typedef std::map<CString, WIZKMSTYLEDATA> CWizKMStyleMap;

class CWizKMStyles : public CWizKMStyleMap
{
public:
	CWizKMStyles()
	{
		m_pDatabase = NULL;
		//
		m_dataDefault.crText = ::GetSysColor(COLOR_WINDOWTEXT);
		m_dataDefault.crBack = ::GetSysColor(COLOR_WINDOW);
		m_dataDefault.bDefault = TRUE;
	}
	~CWizKMStyles()
	{
	}
protected:
	CWizKMDatabase* m_pDatabase;
	//
	WIZKMSTYLEDATA m_dataDefault;
	//
	CWizStdStringArray m_arrayStyleName;
public:
	void SetDatabase(CWizKMDatabase* pDatabase)
	{
		ATLASSERT(pDatabase);
		m_pDatabase = pDatabase;
		//
		Reset();
	}
	//
	void Reset()
	{
		clear();
		m_arrayStyleName.clear();
		//
		InitStyles();
	}
	//
	const_iterator AddStyle(LPCTSTR lpszStyleGUID)
	{
		ATLASSERT(find(lpszStyleGUID) == end());
		//
		CComPtr<IWizStyle> spStyle = m_pDatabase->GetStyleByGUID(lpszStyleGUID);
		if (!spStyle)
		{
			AddEmptyStyle(lpszStyleGUID);
		}
		else
		{
			AddStyle(spStyle);
		}
		//
		return find(lpszStyleGUID);
	}
	//
	BOOL AddStyle(IWizStyle* pStyle)
	{
		CString strGUID = CWizKMDatabase::GetObjectGUID(pStyle);
		ATLASSERT(find(strGUID) == end());
		//
		WIZKMSTYLEDATA data;
		data.crText = CWizKMDatabase::GetStyleTextColor(pStyle);
		data.crBack = CWizKMDatabase::GetStyleBackgroundColor(pStyle);
		data.bBold = CWizKMDatabase::GetStyleTextBold(pStyle);
		data.nFlag = CWizKMDatabase::GetStyleFlagIndex(pStyle);
		//
		operator [] (strGUID) = data;
		//
		return TRUE;
	}
	BOOL AddEmptyStyle(LPCTSTR lpszStyleGUID)
	{
		CString strGUID = lpszStyleGUID;
		ATLASSERT(find(strGUID) == end());
		//
		WIZKMSTYLEDATA data;
		data.crText = ::GetSysColor(COLOR_WINDOWTEXT);
		data.crBack = ::GetSysColor(COLOR_WINDOW);
		data.bBold = FALSE;
		data.nFlag = -1;
		//
		operator [] (strGUID) = data;
		//
		return TRUE;
	}
	//
	const WIZKMSTYLEDATA& GetStyle(LPCTSTR lpszStyleGUID)
	{
		if (!lpszStyleGUID || !*lpszStyleGUID)
			return m_dataDefault;
		//
		const_iterator it = find(lpszStyleGUID);
		if (it != end())
			return it->second;
		//
		it = AddStyle(lpszStyleGUID);
		if (it != end())
			return it->second;
		//
		return m_dataDefault;
	}
	CComPtr<IWizStyle> GetStyleByName(LPCTSTR lpszStyleName)
	{
		CComPtr<IWizStyle> spStyle = m_pDatabase->GetStyleByName(lpszStyleName);
		return spStyle;
	}
	const WIZKMSTYLEDATA& GetDocumentStyle(IWizDocument* pDocument)
	{
		CString strStyleGUID = CWizKMDatabase::GetDocumentStyleGUID(pDocument);
		return GetStyle(strStyleGUID);
	}
	//
	BOOL InitStyles()
	{
		if (!m_pDatabase)
			return FALSE;
		//
		CWizStyleArray arrayStyle;
		m_pDatabase->GetStyles(arrayStyle);
		//
		for (CWizStyleArray::const_iterator it = arrayStyle.begin();
			it != arrayStyle.end();
			it++)
		{
			AddStyle(*it);
			m_arrayStyleName.push_back(CWizKMDatabase::GetObjectName(it->p));
		}
		//
		return TRUE;
	}
	//
	void GetAllStyleNames(CWizStdStringArray& arrayName)
	{
		arrayName.assign(m_arrayStyleName.begin(), m_arrayStyleName.end());
	}
};



inline BOOL WizKMWriteWindowHandleToReg(LPCTSTR lpszWindowName, HWND hwnd)
{
	if (hwnd)
	{
		return ::WizRegWriteInt64(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, lpszWindowName, (__int64)hwnd);
	}
	else
	{
		return ::WizRegDeleteValue(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, lpszWindowName);
	}
}

inline HWND WizKMReadWindowHandleFromReg(LPCTSTR lpszWindowName)
{
	HWND hwnd= (HWND)::WizRegReadInt64Def(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, lpszWindowName, 0);
	if (hwnd)
	{
		if (IsWindow(hwnd))
		{
			if ((GetWindowLong(hwnd,GWL_STYLE) & WS_CHILD) == WS_CHILD)
				return NULL;
			return hwnd;
		}
	}
	return NULL;
}


#define WIZKM_EXPLORER_WINDOW		_T("WizExplorerWindow")

inline BOOL WizKMSetExplorerWindowHandle(HWND hwnd)
{
	return WizKMWriteWindowHandleToReg(WIZKM_EXPLORER_WINDOW, hwnd);
}

inline HWND WizKMGetExplorerWindowHandle()
{
	return WizKMReadWindowHandleFromReg(WIZKM_EXPLORER_WINDOW);
}


#define WIZKM_CALENDAR_WINDOW		_T("WizCalendarWindow")

inline BOOL WizKMSetCalendarWindowHandle(HWND hwnd)
{
	return WizKMWriteWindowHandleToReg(WIZKM_CALENDAR_WINDOW, hwnd);
}

inline HWND WizKMGetCalendarWindowHandle()
{
	return WizKMReadWindowHandleFromReg(WIZKM_CALENDAR_WINDOW);
}



#define WIZKM_NOTE_WINDOW		_T("WizNoteWindow")

inline BOOL WizKMSetNoteWindowHandle(HWND hwnd)
{
	return WizKMWriteWindowHandleToReg(WIZKM_NOTE_WINDOW, hwnd);
}

inline HWND WizKMGetNoteWindowHandle()
{
	return WizKMReadWindowHandleFromReg(WIZKM_NOTE_WINDOW);
}


const UINT WIZKM_UM_IS_HOTKEY_REGISTERED = ::RegisterWindowMessage(_T("WIZKM_UM_IS_HOTKEY_REGISTERED"));

inline BOOL WizKMIsKeyRegistered(LPCTSTR lpszWindowName)
{
	HWND hwnd = WizKMReadWindowHandleFromReg(lpszWindowName);
	if (!hwnd)
		return FALSE;
	//
	return (BOOL)SendMessage(hwnd, WIZKM_UM_IS_HOTKEY_REGISTERED, 0, 0);
}
inline BOOL WizKMIsExplorerHotKeyRegistered()
{
	return WizKMIsKeyRegistered(WIZKM_EXPLORER_WINDOW);
}
inline BOOL WizKMIsNoteHotKeyRegistered()
{
	return WizKMIsKeyRegistered(WIZKM_NOTE_WINDOW);
}

const UINT WIZKM_UM_PROCESS_COMMAND_LINE = ::RegisterWindowMessage(_T("WIZKM_UM_PROCESS_COMMAND_LINE"));

inline void WizKMProcessCommandLine(HWND hwnd, LPCTSTR lpszCommandLine)
{
	::WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("CommandLine"), lpszCommandLine);
	SendMessage(hwnd, WIZKM_UM_PROCESS_COMMAND_LINE, 0, 0);
}
inline CString WizKMGetCommandLine()
{
	CString str = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("CommandLine"), _T(""));
	::WizRegDeleteValue(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("CommandLine"));
	//
	return str;
}

inline void WizKMExplorerRunPlugin(LPCTSTR lpszPluginGUID)
{
	HWND hwnd = WizKMGetExplorerWindowHandle();
	if (!hwnd)
		return;
	//
	CString strCommandLine = WizFormatString1(_T("/RunPlugin=%1"), lpszPluginGUID);
	//
	WizKMProcessCommandLine(hwnd, strCommandLine);
}

const UINT WIZKM_UM_GET_DATABASE_PATH = ::RegisterWindowMessage(_T("WIZKM_UM_GET_DATABASE_PATH"));

inline CString WizKMExplorerGetDatabasePath()
{
	HWND hwnd = WizKMGetExplorerWindowHandle();
	if (!hwnd)
		return CString();
	//
	SendMessage(hwnd, WIZKM_UM_GET_DATABASE_PATH, 0, 0);
	//
	CString str = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DatabasePath"), _T(""));
	WizRegDeleteValue(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DatabasePath"));
	//
	return str;
}



const UINT WIZKM_UM_GET_SELECTED_LOCATION = ::RegisterWindowMessage(_T("WIZKM_UM_GET_SELECTED_LOCATION"));

inline CString WizKMExplorerGetSelectedLocation()
{
	HWND hwnd = WizKMGetExplorerWindowHandle();
	if (!hwnd)
		return CString();
	//
	SendMessage(hwnd, WIZKM_UM_GET_DATABASE_PATH, 0, 0);
	//
	CString str = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("SelectedLocation"), _T(""));
	WizRegDeleteValue(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("SelectedLocation"));
	//
	return str;
}



template <class T, class TObject, class TCollection>
class CWizKMObjectDataObject : public CWizAtlDataObject
{
public:
	typedef std::vector<CComPtr<TObject> > CWizObjectArray;
public:
	CWizKMObjectDataObject(IDataObject* pData)
		: CWizAtlDataObject(pData)
	{
	}
	BOOL IsObjectsAvaliable()
	{
		return IsFormatAvaliable(GetDataFormat());
	}
	BOOL GetObjects(CWizKMDatabase* pDatabase, CWizObjectArray& arrayObject)
	{
		HANDLE hData = GetData(GetDataFormat());
		if (!hData)
			return FALSE;
		//
		return HGlobalToObjectArray(pDatabase, hData, arrayObject);
	}
public:
	static UINT GetDataFormat()
	{
		static UINT nFormat = RegisterClipboardFormat(T::GetFormatName());
		return nFormat;
	}
private:
	static BOOL ObjectArrayToString(const CWizObjectArray& arrayObject, BOOL bCopy, CString& strText)
	{
		CWizXMLDocument doc;
		//
		CWizXMLNode nodeObjects;
		if (!doc.AppendChild(_T("Objects"), nodeObjects))
			return FALSE;
		//
		if (!nodeObjects.SetAttributeBool(_T("Copy"), bCopy))
			return FALSE;
		//
		for (CWizObjectArray::const_iterator it = arrayObject.begin();
			it != arrayObject.end();
			it++)
		{
			CWizXMLNode nodeObject;
			if (!nodeObjects.AppendChild(_T("Object"), nodeObject))
				return FALSE;
			//
			CComPtr<TObject> spObject = *it;
			//
			CString strGUID = CWizKMDatabase::GetObjectGUID<TObject>(spObject);
			//
			if (!nodeObject.SetAttributeText(_T("GUID"), strGUID))
				return FALSE;
		}
		//
		return doc.ToXML(strText, FALSE);
	}
	static BOOL StringToObjectArray(CWizKMDatabase* pDatabase, LPCTSTR lpszText, CWizObjectArray& arrayObject, BOOL& bCopy)
	{
		CWizXMLDocument doc;
		if (!doc.LoadXML(CComBSTR(CString(lpszText))))
			return FALSE;
		//
		CWizXMLNode nodeObjects;
		if (!doc.FindChildNode(_T("Objects"), nodeObjects))
			return FALSE;
		//
		if (!nodeObjects.GetAttributeBool(_T("Copy"), bCopy))
			return FALSE;
		//
		std::vector<CWizXMLNode> arrayNode;
		nodeObjects.GetAllChildNodes(arrayNode);
		//
		for (std::vector<CWizXMLNode>::iterator it = arrayNode.begin();
			it != arrayNode.end();
			it++)
		{
			CWizXMLNode& nodeObject = *it;;
			//
			CString strGUID;
			if (!nodeObject.GetAttributeText(_T("GUID"), strGUID))
				return FALSE;
			//
			CComPtr<TObject> spObject = T::GUIDToObject(pDatabase, strGUID);
			if (!spObject)
				return FALSE;
			//
			arrayObject.push_back(spObject);
		}
		//
		return TRUE;
	}
public:
	static BOOL HGlobalToObjectArray(CWizKMDatabase* pDatabase, HGLOBAL hGlobal, CWizObjectArray& arrayObject, BOOL& bCopy)
	{
		CStringW strText;
		if (!WizHGlobalToUnicodeText(hGlobal, strText))
			return FALSE;
		//
		return StringToObjectArray(pDatabase, strText, arrayObject, bCopy);
	}
	static BOOL HGlobalToObjectArray(CWizKMDatabase* pDatabase, HGLOBAL hGlobal, CWizObjectArray& arrayObject)
	{
		BOOL bCopy = TRUE;
		//
		return HGlobalToObjectArray(pDatabase, hGlobal, arrayObject, bCopy);
	}
	static HGLOBAL ObjectArrayToHGlobal(const CWizObjectArray& arrayObject, BOOL bCopy)
	{
		CString strText;
		if (!ObjectArrayToString(arrayObject, bCopy, strText))
			return NULL;
		//
		return WizUnicodeTextToHGlobal(CStringW(strText));
	}
	static HGLOBAL ObjectArrayToHGlobal(IDispatch* pObjectCollectionDisp, BOOL bCopy)
	{
		if (!pObjectCollectionDisp)
			return NULL;
		//
		CWizObjectArray arrayObject;
		if (!WizCollectionDispatchToArray<TCollection, TObject>(pObjectCollectionDisp, arrayObject))
			return NULL;
		//
		return ObjectArrayToHGlobal(arrayObject, bCopy);
	}
	static BOOL ToClipboard(HWND hWnd, const CWizObjectArray& arrayObject, BOOL bCopy)
	{
		HGLOBAL hGlobal = ObjectArrayToHGlobal(arrayObject, bCopy);
		if (!hGlobal)
			return FALSE;
		//
		if (!OpenClipboard(hWnd)) 
	        return FALSE;
		//
		EmptyClipboard(); 
		//
		BOOL bRet = SetClipboardData(GetDataFormat(), hGlobal) ? TRUE : FALSE; 
		//
		CloseClipboard();
		//
		return bRet;
	}
	static BOOL FromClipboard(HWND hWnd, CWizKMDatabase* pDatabase, CWizObjectArray& arrayObject, BOOL& bCopy)
	{
		if (!IsClipboardFormatAvailable(GetDataFormat()))
			return FALSE;
		//
		if (!OpenClipboard(hWnd)) 
            return FALSE; 
		//
		BOOL bRet = FALSE;
		//
        HGLOBAL hGlobal = GetClipboardData(GetDataFormat());
        if (hGlobal)
        {
			bRet = HGlobalToObjectArray(pDatabase, hGlobal, arrayObject, bCopy);
        }
        CloseClipboard();
		//
		return bRet;
	}
};



class CWizKMDocumentsDataObject : public CWizKMObjectDataObject<CWizKMDocumentsDataObject, IWizDocument, IWizDocumentCollection>
{
public:
	static CString GetFormatName()
	{
		return CString(_T("WizKMDocuments"));
	}
	//
	static CComPtr<IWizDocument> GUIDToObject(CWizKMDatabase* pDatabase, LPCTSTR lpszGUID)
	{
		if (!pDatabase)
			return NULL;
		//
		if (!lpszGUID)
			return NULL;
		//
		return pDatabase->GetDocumentByGUID(lpszGUID);
	}
	//
	CWizKMDocumentsDataObject(IDataObject* pData)
		: CWizKMObjectDataObject(pData)
	{
	}
};


class CWizKMTagsDataObject : public CWizKMObjectDataObject<CWizKMTagsDataObject, IWizTag, IWizTagCollection>
{
public:
	static CString GetFormatName()
	{
		return CString(_T("WizKMTags"));
	}
	//
	static CComPtr<IWizTag> GUIDToObject(CWizKMDatabase* pDatabase, LPCTSTR lpszGUID)
	{
		if (!pDatabase)
			return NULL;
		//
		if (!lpszGUID)
			return NULL;
		//
		return pDatabase->GetTagByGUID(lpszGUID);
	}
	//
	CWizKMTagsDataObject(IDataObject* pData)
		: CWizKMObjectDataObject(pData)
	{
	}
};


template <class TDataObject, class TObject>
class CWizKMObjectsDropSource : public CAtlWizDropSource
{
public:
	static DWORD DoDragDrop(IDispatch* pObjectCollectionDisp)
	{
		HANDLE hData = TDataObject::ObjectArrayToHGlobal(pObjectCollectionDisp, TRUE);
		if (!hData)
			return 0;
		//
		return DoDragDrop(hData);
	}
	static DWORD DoDragDrop(const std::vector<CComPtr<TObject> >& arrayObject)
	{
		HANDLE hData = TDataObject::ObjectArrayToHGlobal(arrayObject, TRUE);
		if (!hData)
			return 0;
		//
		return DoDragDrop(hData);
	}
	static DWORD DoDragDrop(HANDLE hData)
	{
		if (!hData)
			return 0;
		//
		CComObject<CAtlWizDropSource>* pDropSource = NULL;
		HRESULT hr = CComObject<CAtlWizDropSource>::CreateInstance(&pDropSource);
		if (!pDropSource)
			return 0;
		//
		CComPtr<IDataObject> spData(pDropSource);
		//
		pDropSource->Init(TDataObject::GetDataFormat(), hData);
		//
		DWORD dwEffect = 0;
		//
		pDropSource->DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);
		//
		return dwEffect;
	}
};

typedef CWizKMObjectsDropSource<CWizKMDocumentsDataObject, IWizDocument> CWizKMDocumentsDropSource;
typedef CWizKMObjectsDropSource<CWizKMTagsDataObject, IWizTag> CWizKMTagsDropSource;







inline CString WizKMServerGetToken(IWizDatabase* pDatabase)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return CString();
	//
	typedef HRESULT WINAPI Type_WizKMGetTokenFromServer(IWizDatabase* pDatabase, BSTR* pbstrToken, BSTR* pbstrErrorMessage);
	//
	HRESULT hr = E_FAIL;
	CString strToken;
	CString strError;
	//
	Type_WizKMGetTokenFromServer* fun = (Type_WizKMGetTokenFromServer *)GetProcAddress(hModule, "WizKMGetTokenFromServer");
	if (fun)
	{
		CComBSTR bstrToken;
		CComBSTR bstrError;
		hr = fun(pDatabase, &bstrToken, &bstrError);
		//
		strToken = CString(bstrToken);
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return CString();
	}
	//
	return strToken;
}



inline BOOL WizKMServerGetCert(IWizDatabase* pDatabase, CString& strN, CString& stre, CString& strd, CString& strHint, CString& strError)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return FALSE;
	//
	typedef HRESULT WINAPI Type_WizKMGetCertFromServer(IWizDatabase* pDatabase, BSTR* pbstrN, BSTR* pbstre, BSTR* pbstrd, BSTR* pbstrHint, BSTR* pbstrError);
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizKMGetCertFromServer* fun = (Type_WizKMGetCertFromServer *)GetProcAddress(hModule, "WizKMGetCertFromServer");
	if (fun)
	{
		CComBSTR bstrN;
		CComBSTR bstre;
		CComBSTR bstrd;
		CComBSTR bstrHint;
		CComBSTR bstrError;
		hr = fun(pDatabase, &bstrN, &bstre, &bstrd, &bstrHint, &bstrError);
		//
		strN = CString(bstrN);
		stre = CString(bstre);
		strd = CString(bstrd);
		strHint = CString(bstrHint);
		//
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return FALSE;
	}
	//
	return TRUE;
}


inline BOOL WizKMServerSetCert(IWizDatabase* pDatabase, LPCTSTR lpszN, LPCTSTR lpsze, LPCTSTR lpszd, LPCTSTR lpszHint, CString& strError)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return FALSE;
	//
	typedef HRESULT WINAPI Type_WizKMSetCertToServer(IWizDatabase* pDatabase, BSTR bstrN, BSTR bstre, BSTR bstrd, BSTR bstrHint, BSTR* pbstrError);
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizKMSetCertToServer* fun = (Type_WizKMSetCertToServer *)GetProcAddress(hModule, "WizKMSetCertToServer");
	if (fun)
	{
		CComBSTR bstrError;
		hr = fun(pDatabase, CComBSTR(lpszN), CComBSTR(lpsze), CComBSTR(lpszd), CComBSTR(lpszHint), &bstrError);
		//
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return FALSE;
	}
	//
	return TRUE;
}



inline void WizKMWebSiteVisitWithToken(LPCTSTR lpszCommand, IWizDatabase* pDatabase)
{
	return WizKMWebSiteVisitWithToken(lpszCommand, WizKMServerGetToken(pDatabase));
}
inline CString WizKMWebSiteGetURLWithToken(LPCTSTR lpszCommand, IWizDatabase* pDatabase)
{
	CString strAtt = WizFormatString1(_T("token=%1"), WizKMServerGetToken(pDatabase));
	return WizKMWebSiteGetURL(lpszCommand, WizWebSiteEscapeAtt(strAtt));
}

inline CString WizKMWebSiteGetURLWithToken(LPCTSTR lpszCommand, LPCTSTR lpszAtt, IWizDatabase* pDatabase)
{
	CString strAtt = WizFormatString2(_T("token=%1&%2"), WizKMServerGetToken(pDatabase), lpszAtt);
	return WizKMWebSiteGetURL(lpszCommand, WizWebSiteEscapeAtt(strAtt));
}


#endif //_WIZKMDATABASE_H_

