#include "StdAfx.h"
#include "WizKMDatabase.h"

CWizKMDatabase::CWizKMDatabase(void)
{
}

CWizKMDatabase::~CWizKMDatabase(void)
{
}
void CWizKMDatabase::SetDatabase(IWizDatabase* pDatabase)
{
	ATLASSERT(pDatabase);
	m_spDatabase = pDatabase;
}

const LPCTSTR g_lpszDatabaseNotInitialized = _T("Database have not been initialilized!");

#define CHECK_DATABASE() \
	if (!m_spDatabase)\
	{\
		TOLOG(g_lpszDatabaseNotInitialized);\
		return FALSE;\
	}\
//

BOOL CWizKMDatabase::GetAttachments(CWizDocumentAttachmentArray& arrayAttachment)
{
	CHECK_DATABASE();
	//
	CComPtr<IDispatch> spCollDisp;
	m_spDatabase->get_Attachments(&spCollDisp);
	//
	return WizCollectionDispatchToArray<IWizDocumentAttachmentCollection, IWizDocumentAttachment>(spCollDisp, arrayAttachment);
}
BOOL CWizKMDatabase::GetAttachments(CWizStdStringArray& arrayAttachment)
{
	CHECK_DATABASE();
	//
	CWizDocumentAttachmentArray arrayAttach;
	if (!GetAttachments(arrayAttach))
	{
		return FALSE;
	}
	//
	for (CWizDocumentAttachmentArray::const_iterator it = arrayAttach.begin();
		it != arrayAttach.end();
		it++)
	{
		arrayAttachment.push_back(GetAttachmentFileName(it->p));
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetRootTags(CWizTagArray& arrayTag)
{
	CHECK_DATABASE();
	//
	CComPtr<IDispatch> spTagCollDisp;
	HRESULT hr = m_spDatabase->get_RootTags(&spTagCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get taggroups!"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizTagCollection, IWizTag>(spTagCollDisp, arrayTag);
}
BOOL CWizKMDatabase::IsModified()
{
	CHECK_DATABASE();
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	m_spDatabase->IsModified(&vb);
	//
	return vb ? TRUE : FALSE;
}

BOOL CWizKMDatabase::GetTags(CWizTagArray& arrayTag)
{
	CHECK_DATABASE();
	//
	CComPtr<IDispatch> spTagCollDisp;
	HRESULT hr = m_spDatabase->get_Tags(&spTagCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get tags!"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizTagCollection, IWizTag>(spTagCollDisp, arrayTag);
}

BOOL CWizKMDatabase::GetStyles(CWizStyleArray& arrayStyle)
{
	CHECK_DATABASE();
	//
	CComPtr<IDispatch> spStyleCollDisp;
	HRESULT hr = m_spDatabase->get_Styles(&spStyleCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get tags!"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizStyleCollection, IWizStyle>(spStyleCollDisp, arrayStyle);
}
BOOL CWizKMDatabase::GetStylesName(CWizStdStringArray& arrayName)
{
	CWizStyleArray arrayStyle;
	if (!GetStyles(arrayStyle))
		return FALSE;
	//
	for (CWizStyleArray::const_iterator it = arrayStyle.begin();
		it != arrayStyle.end();
		it++)
	{
		arrayName.push_back(CWizKMDatabase::GetObjectName(it->p));
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetRootTagsName(CWizStdStringArray& arrayName)
{
	CWizTagArray arrayTag;
	if (!GetRootTags(arrayTag))
		return FALSE;
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		arrayName.push_back(CWizKMDatabase::GetObjectName(it->p));
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::GetTagsName(CWizStdStringArray& arrayName)
{
	CWizTagArray arrayTag;
	if (!GetTags(arrayTag))
		return FALSE;
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		arrayName.push_back(CWizKMDatabase::GetObjectName(it->p));
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetTags(IWizTag* pParentTag, CWizTagArray& arrayTag)
{
	CComPtr<IDispatch> spTagCollDisp;
	HRESULT hr = pParentTag->get_Children(&spTagCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get taggroups!"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizTagCollection, IWizTag>(spTagCollDisp, arrayTag);
}

BOOL CWizKMDatabase::GetTagsName(IWizTag* pParentTag, CWizStdStringArray& arrayName)
{
	CWizTagArray arrayTag;
	if (!GetTags(pParentTag, arrayTag))
		return FALSE;
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		arrayName.push_back(GetObjectName(it->p));
	}
	//
	return TRUE;
}


BOOL CWizKMDatabase::CreateRootTag(LPCTSTR lpszName, LPCTSTR lpszDescription, IWizTag** ppTag)
{
	CComPtr<IDispatch> spTagDisp;
	HRESULT hr = m_spDatabase->CreateRootTag(CComBSTR(lpszName), CComBSTR(lpszDescription), &spTagDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create tag: %1"), lpszName);
		return FALSE;
	}
	//
	hr = spTagDisp->QueryInterface(ppTag);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to query IWizTag: %1"), lpszName);
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::CreateTag(IWizTag* pParentTag, LPCTSTR lpszName, LPCTSTR lpszDescription, IWizTag** ppTag)
{
	CComPtr<IDispatch> spTagDisp;
	HRESULT hr = pParentTag->CreateChildTag(CComBSTR(lpszName), CComBSTR(lpszDescription), &spTagDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create tag: %1"), lpszName);
		return FALSE;
	}
	//
	hr = spTagDisp->QueryInterface(ppTag);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to query IWizTag: %1"), lpszName);
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::CreateStyle(LPCTSTR lpszName, LPCTSTR lpszDescription, COLORREF crText, COLORREF crBackground, BOOL bTextBold, int nFlagIndex, IWizStyle** ppStyle)
{
	CComPtr<IDispatch> spStyleDisp;
	HRESULT hr = m_spDatabase->CreateStyle(CComBSTR(lpszName), CComBSTR(lpszDescription), 
		crText, crBackground, bTextBold ? VARIANT_TRUE : VARIANT_FALSE, nFlagIndex,
		&spStyleDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create Style: %1"), lpszName);
		return FALSE;
	}
	//
	hr = spStyleDisp->QueryInterface(ppStyle);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to query IWizStyle: %1"), lpszName);
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetFolders(CWizFolderArray& arrayFolder)
{
	CHECK_DATABASE();
	//
	CComPtr<IDispatch> spFolderCollDisp;
	HRESULT hr = m_spDatabase->get_Folders(&spFolderCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get root folders"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizFolderCollection, IWizFolder>(spFolderCollDisp, arrayFolder);
}
BOOL CWizKMDatabase::GetDocumentsByFolder(IWizFolder* pFolder, IDispatch** ppDocumentCollectionDisp)
{
	HRESULT hr = pFolder->get_Documents(ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get documents by folder!"));
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::GetDocumentsByFolder(IWizFolder* pFolder, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDocumentCollectionDisp = NULL;
	BOOL bRet = GetDocumentsByFolder(pFolder, &spDocumentCollectionDisp);
	if (!bRet)
		return FALSE;
	if (!spDocumentCollectionDisp)
		return FALSE;
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDocumentCollectionDisp, arrayDocument);
}

BOOL CWizKMDatabase::GetDocumentsTitleSet(IWizFolder* pFolder, CWizStringSet& setDocument)
{
	CComPtr<IDispatch> spCollDisp;
	if (!GetDocumentsByFolder(pFolder, &spCollDisp))
		return FALSE;
	//
	CComQIPtr<IWizDocumentCollection> spColl(spCollDisp);
	if (!spColl)
	{
		TOLOG(_T("Failed to cast IDispatch to IWizDocumentCollection!"));
		return FALSE;
	}
	//
	long nCount = 0;
	spColl->get_Count(&nCount);
	for (long i = 0; i < nCount; i++)
	{
		CComPtr<IDispatch> spDocumentDisp;
		HRESULT hr = spColl->get_Item(i, &spDocumentDisp);
		if (FAILED(hr))
		{
			TOLOG(_T("Failed to get item from collection!"));
			return FALSE;
		}
		//
		CComQIPtr<IWizDocument> spDocument(spDocumentDisp);
		if (!spDocument)
		{
			TOLOG(_T("Failed to query element interface!"));
			return FALSE;
		}
		//
		CString strTitle = GetDocumentTitle(spDocument);
		strTitle.MakeLower();
		//
		setDocument.insert(strTitle);
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetFolders(IWizFolder* pFolder, CWizFolderArray& arrayFolder)
{
	CComPtr<IDispatch> spFolderCollDisp;
	HRESULT hr = pFolder->get_Folders(&spFolderCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get sub folders"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizFolderCollection, IWizFolder>(spFolderCollDisp, arrayFolder);
}

CComPtr<IWizFolder> CWizKMDatabase::GetRootFolder(UINT nNameStringID, BOOL bCreate)
{
	return GetRootFolder(WizFormatString0(nNameStringID), bCreate);
}
CComPtr<IWizFolder> CWizKMDatabase::GetRootFolder(LPCTSTR lpszName, BOOL bCreate)
{
	CWizFolderArray arrayFolder;
	GetFolders(arrayFolder);
	//
	for (CWizFolderArray::const_iterator it = arrayFolder.begin();
		it != arrayFolder.end();
		it++)
	{
		CString strName = GetObjectName<IWizFolder>(*it);
		if (0 == strName.CompareNoCase(lpszName))
			return *it;
	}
	//
	if (!bCreate)
		return NULL;
	//
	CComPtr<IDispatch> spNewFolderDisp;
	HRESULT hr = m_spDatabase->CreateRootFolder(CComBSTR(lpszName), VARIANT_TRUE, &spNewFolderDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create folder: %1"), lpszName);
		return NULL;
	}
	//
	return CComQIPtr<IWizFolder>(spNewFolderDisp);
}

CComPtr<IWizFolder> CWizKMDatabase::GetFolderByLocation(LPCTSTR lpszLocation, BOOL bCreate)
{
	CComPtr<IDispatch> spNewFolderDisp;
	HRESULT hr = m_spDatabase->GetFolderByLocation(CComBSTR(lpszLocation), bCreate ? VARIANT_TRUE : VARIANT_FALSE, &spNewFolderDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get folder: %1"), lpszLocation);
		return NULL;
	}
	//
	return CComQIPtr<IWizFolder>(spNewFolderDisp);
}
CComPtr<IWizTag> CWizKMDatabase::GetRootTagByName(LPCTSTR lpszTagName, BOOL bCreate)
{
	CComPtr<IDispatch> spNewTagDisp;
	HRESULT hr = m_spDatabase->GetRootTagByName(CComBSTR(lpszTagName), bCreate ? VARIANT_TRUE : VARIANT_FALSE, &spNewTagDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get tag: %1"), lpszTagName);
		return NULL;
	}
	//
	return CComQIPtr<IWizTag>(spNewTagDisp);
}

CComPtr<IWizTag> CWizKMDatabase::GetTagByName(LPCTSTR lpszTagName, BOOL bCreate, LPCTSTR lpszRootTagNameForCreate)
{
	CComPtr<IDispatch> spNewTagDisp;
	HRESULT hr = m_spDatabase->GetTagByName(CComBSTR(lpszTagName), bCreate ? VARIANT_TRUE : VARIANT_FALSE, CComBSTR(lpszRootTagNameForCreate), &spNewTagDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get tag: %1"), lpszTagName);
		return NULL;
	}
	//
	return CComQIPtr<IWizTag>(spNewTagDisp);
}
CComPtr<IWizStyle> CWizKMDatabase::GetStyleByName(LPCTSTR lpszStyleName)
{
	CWizStyleArray arrayStyle;
	GetStyles(arrayStyle);
	//
	for (CWizStyleArray::const_iterator it = arrayStyle.begin();
		it != arrayStyle.end();
		it++)
	{
		if (GetObjectName(it->p) == lpszStyleName)
			return *it;
	}
	//
	return NULL;
}



CComPtr<IWizFolder> CWizKMDatabase::GetChildFolder(IWizFolder* pParentFolder, LPCTSTR lpszName, BOOL bCreate)
{
	ATLASSERT(pParentFolder);
	//
	CWizFolderArray arrayFolder;
	GetFolders(pParentFolder, arrayFolder);
	//
	for (CWizFolderArray::const_iterator it = arrayFolder.begin();
		it != arrayFolder.end();
		it++)
	{
		CString strName = GetObjectName<IWizFolder>(*it);
		if (0 == strName.CompareNoCase(lpszName))
			return *it;
	}
	//
	if (!bCreate)
		return NULL;
	//
	CComPtr<IDispatch> spNewFolderDisp;
	HRESULT hr = pParentFolder->CreateSubFolder(CComBSTR(lpszName), &spNewFolderDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create folder: %1"), lpszName);
		return NULL;
	}
	//
	return CComQIPtr<IWizFolder>(spNewFolderDisp);
}

CComPtr<IWizFolder> CWizKMDatabase::GetChildFolderByPath(IWizFolder* pParentFolder, LPCTSTR lpszPath, BOOL bCreate)
{
	ATLASSERT(pParentFolder);
	//
	CString strPath(lpszPath);
	strPath.Replace('/', '\\');
	//
	CWizStdStringArray arrayName;
	WizSplitTextToArray(strPath, '\\', arrayName);
	//
	WizStringArrayEraseEmptyLine(arrayName);
	//
	CComPtr<IWizFolder> spParent = pParentFolder;
	for (CWizStdStringArray::const_iterator it = arrayName.begin();
		it != arrayName.end();
		it++)
	{
		CComPtr<IWizFolder> spNewFolder = GetChildFolder(spParent, *it, bCreate);
		if (!spNewFolder)
			return NULL;
		//
		spParent = spNewFolder;
	}
	//
	return spParent;
}

BOOL CWizKMDatabase::GetAllDocuments(CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->GetAllDocuments(&spDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get all documents!"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
}
BOOL CWizKMDatabase::GetAllDocumentsTitle(CWizStdStringArray& arrayDocument)
{
	CComBSTR bstrText;
	HRESULT hr = m_spDatabase->get_AllDocumentsTitle(&bstrText);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get all documents title!"));
		return FALSE;
	}
	//
	::WizSplitTextToArray(CString(bstrText), '\n', arrayDocument);
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetDocumentsByTags(IWizTagCollection* pTagCollection, IDispatch** ppDocumentCollectionDisp)
{
	if (!pTagCollection)
	{
		TOLOG(_T("NULL Pointer: CWizKMDatabase::GetDocumentsByTags"));
		return FALSE;
	}
	//
	HRESULT hr = m_spDatabase->DocumentsFromTags(pTagCollection, ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get documents from tags!"));
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::GetDocumentsByTagWithChildren(IWizTag* pTag, IDispatch** ppDocumentCollectionDisp)
{
	if (!pTag)
	{
		TOLOG(_T("NULL Pointer: CWizKMDatabase::GetDocumentsByTagGroup"));
		return FALSE;
	}
	//
	HRESULT hr = m_spDatabase->DocumentsFromTagWithChildren(pTag, ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get documents from tags!"));
		return FALSE;
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetDocumentsBySQL(LPCTSTR lpszSQL, IDispatch** ppDocumentCollectionDisp)
{
	if (!m_spDatabase)
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
	//
	HRESULT hr = m_spDatabase->DocumentsFromSQL(CComBSTR(lpszSQL), ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get documents from tags!"));
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::GetDocumentsBySQL(LPCTSTR lpszSQL, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDisp;
	if (!GetDocumentsBySQL(CComBSTR(lpszSQL), &spDisp))
		return FALSE;
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
}
BOOL CWizKMDatabase::GetDocumentsByURL(LPCTSTR lpszURL, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->DocumentsFromURL(CComBSTR(lpszURL), &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get documents from url: %1"), lpszURL);
		return FALSE;
	}
	if (!spDisp)
		return FALSE;
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
}

CString CWizKMDatabase::DocumentToTemp(IWizDocument* pDocument, long nFlags /*= 0*/)
{
	ATLASSERT(pDocument);
	//
	CString strTempPath = WizKMGetTempPath();
	CString strTempFileName = strTempPath + CWizKMDatabase::GetObjectGUID(pDocument) + _T("_") + WizIntToStr(nFlags) + _T(".htm");
	//
	HRESULT hr = pDocument->SaveToHtml(CComBSTR(strTempFileName), nFlags);
	//
	if (FAILED(hr))
		return CString();
	//
	return strTempFileName;
}
CString CWizKMDatabase::GetDatabasePath()
{
	ATLASSERT(m_spDatabase);
	//
	CComBSTR bstrPath;
	m_spDatabase->get_DatabasePath(&bstrPath);
	//
	return CString(bstrPath);
}
CString CWizKMDatabase::GetFolderPath(IWizFolder* pFolder)
{
	ATLASSERT(pFolder);
	//
	CComBSTR bstrPath;
	pFolder->get_FullPath(&bstrPath);
	//
	return CString(bstrPath);
}
CString CWizKMDatabase::GetFolderLocation(IWizFolder* pFolder)
{
	ATLASSERT(pFolder);
	//
	CComBSTR bstrLocation;
	pFolder->get_Location(&bstrLocation);
	//
	return CString(bstrLocation);
}
CString CWizKMDatabase::GetFolderDisplayName(IWizFolder* pFolder, long nFlags /* = 0 */)
{
	ATLASSERT(pFolder);
	//
	CComBSTR bstrDisplayName;
	pFolder->GetDisplayName(nFlags, &bstrDisplayName);
	//
	return CString(bstrDisplayName);
}

CString CWizKMDatabase::GetFolderDisplayTemplate(IWizFolder* pFolder)
{
	ATLASSERT(pFolder);
	//
	CComBSTR bstrTemplate;
	pFolder->GetDisplayTemplate(&bstrTemplate);
	//
	return CString(bstrTemplate);
}

BOOL CWizKMDatabase::GetFolderIsRoot(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	ATLASSERT(pFolder);
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	pFolder->get_IsRoot(&vb);
	return vb ? TRUE : FALSE;
}
BOOL CWizKMDatabase::GetFolderIsSync(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	ATLASSERT(pFolder);
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	pFolder->get_Sync(&vb);
	return vb ? TRUE : FALSE;
}
BOOL CWizKMDatabase::GetDocumentIsSync(IWizDocument* pDocument)
{
	ATLASSERT(pDocument);
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	pDocument->get_Sync(&vb);
	return vb ? TRUE : FALSE;
}
BOOL CWizKMDatabase::GetAttachmentIsSync(IWizDocumentAttachment* pAttachment)
{
	ATLASSERT(pAttachment);
	//
	CComPtr<IWizDocument> spDocument = CWizKMDatabase::GetAttachmentDocument(pAttachment);
	if (!spDocument)
		return FALSE;
	//
	return GetDocumentIsSync(spDocument);
}

BOOL CWizKMDatabase::GetFolderIsDeletedItems(IWizFolder* pFolder)
{
	ATLASSERT(pFolder);
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	pFolder->get_IsDeletedItems(&vb);
	return vb ? TRUE : FALSE;
}

BOOL CWizKMDatabase::CanRenameFolder(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	if (!GetFolderIsRoot(pFolder))
		return TRUE;
	//
	CString strName = GetObjectName(pFolder);
	return !WizKMIsSysFolderName(strName);
}

CString CWizKMDatabase::GetFolderIconFileName(IWizFolder* pFolder)
{
	if (!pFolder)
		return CString();
	//
	CComBSTR bstrFileName;
	pFolder->GetIconFileName(&bstrFileName);
	//
	if (!bstrFileName)
		return CString();
	//
	return CString(bstrFileName);
}
CString CWizKMDatabase::GetDocumentIconFileName(IWizDocument* pDocument)
{
	if (!pDocument)
		return CString();
	//
	CComBSTR bstrFileName;
	pDocument->GetIconFileName(&bstrFileName);
	//
	if (!bstrFileName)
		return CString();
	//
	return CString(bstrFileName);
}
long CWizKMDatabase::GetDocumentProtected(IWizDocument* pDocument)
{
	long nProtected = 0;
	//
	pDocument->get_Protect(&nProtected);
	//
	return nProtected;
}

HICON CWizKMDatabase::GetFolderIcon(IWizFolder* pFolder)
{
	CString strFileName = GetFolderIconFileName(pFolder);
	if (strFileName.IsEmpty())
		return NULL;
	if (!PathFileExists(strFileName))
		return NULL;
	//
	return (HICON)LoadImage(NULL, strFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
}
CString CWizKMDatabase::GetFolderSortOrder(IWizFolder* pFolder)
{
	CComBSTR bstrSectionName(WIZKM_FOLDER_SETTINGS_SECTION_SORT);
	//
	CComBSTR bstrSortOrder;
	pFolder->get_Settings(bstrSectionName, CComBSTR(WIZKM_FOLDER_SETTINGS_KEY_SORT_ORDER), &bstrSortOrder);
	CString str(bstrSortOrder);
	if (str.IsEmpty())
	{
		str = _T("Desc");
	}
	return str;
}
CString CWizKMDatabase::GetFolderSortBy(IWizFolder* pFolder)
{
	CComBSTR bstrSectionName(WIZKM_FOLDER_SETTINGS_SECTION_SORT);
	//
	CComBSTR bstrSortBy;
	pFolder->get_Settings(bstrSectionName, CComBSTR(WIZKM_FOLDER_SETTINGS_KEY_SORT_BY), &bstrSortBy);
	CString str(bstrSortBy);
	if (str.IsEmpty())
	{
		str = _T("DateCreated");
	}
	return str;
}
BOOL CWizKMDatabase::SetFolderSortOrder(IWizFolder* pFolder, LPCTSTR lpszSortOrder)
{
	CComBSTR bstrSectionName(WIZKM_FOLDER_SETTINGS_SECTION_SORT);
	return SUCCEEDED(pFolder->put_Settings(bstrSectionName, CComBSTR(WIZKM_FOLDER_SETTINGS_KEY_SORT_ORDER), CComBSTR(lpszSortOrder)));
}
BOOL CWizKMDatabase::SetFolderSortBy(IWizFolder* pFolder, LPCTSTR lpszSortBy)
{
	CComBSTR bstrSectionName(WIZKM_FOLDER_SETTINGS_SECTION_SORT);
	return SUCCEEDED(pFolder->put_Settings(bstrSectionName, CComBSTR(WIZKM_FOLDER_SETTINGS_KEY_SORT_BY), CComBSTR(lpszSortBy)));
}
BOOL CWizKMDatabase::GetFolderEncrypt(IWizFolder* pFolder)
{
	VARIANT_BOOL vbEncrypt = VARIANT_FALSE;
	pFolder->get_Encrypt(&vbEncrypt);
	return vbEncrypt ? TRUE : FALSE;
}

BOOL CWizKMDatabase::CreateRootFolder(LPCTSTR lpszName, BOOL bSync, IWizFolder** ppFolder)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->CreateRootFolder(CComBSTR(lpszName), bSync ? VARIANT_TRUE : VARIANT_FALSE, &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create root folder: %1"), lpszName);
		return FALSE;
	}
	return SUCCEEDED(spDisp->QueryInterface(ppFolder));
}
BOOL CWizKMDatabase::CreateRootFolder2(LPCTSTR lpszName, BOOL bSync, LPCTSTR lpszIconFileName, IWizFolder** ppFolder)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->CreateRootFolder2(CComBSTR(lpszName), bSync ? VARIANT_TRUE : VARIANT_FALSE, CComBSTR(lpszIconFileName), &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create root folder: %1"), lpszName);
		return FALSE;
	}
	return SUCCEEDED(spDisp->QueryInterface(ppFolder));
}

BOOL CWizKMDatabase::CreateFolder(IWizFolder* pParentFolder, LPCTSTR lpszName, IWizFolder** ppFolder)
{
	if (!lpszName|| !*lpszName)
	{
		TOLOG(_T("Failed to create filder, sub folder name is empty"));
		return FALSE;
	}
	//
	ATLASSERT(pParentFolder);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = pParentFolder->CreateSubFolder(CComBSTR(lpszName), &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create folder: %1"), lpszName);
		return FALSE;
	}
	return SUCCEEDED(spDisp->QueryInterface(ppFolder));
}
CComPtr<IWizFolder> CWizKMDatabase::GetDeletedItemsFolder()
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->get_DeletedItemsFolder(&spDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get deleted items folder!"));
		return NULL;
	}
	//
	return CComQIPtr<IWizFolder>(spDisp);
}

CString CWizKMDatabase::GetDocumentTitle(IWizDocument* pDocument)
{
	CComBSTR bstrTitle;
	pDocument->get_Title(&bstrTitle);
	return CString(bstrTitle);
}
CString CWizKMDatabase::GetDocumentLocation(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_Location(&bstr);
	return CString(bstr);
}
CString CWizKMDatabase::GetDocumentSEO(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_SEO(&bstr);
	return CString(bstr);
}

CString CWizKMDatabase::GetDocumentAuthor(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_Author(&bstr);
	return CString(bstr);
}
int CWizKMDatabase::GetDocumentReadCount(IWizDocument* pDocument)
{
	long n;
	pDocument->get_ReadCount(&n);
	return n;
}

CString CWizKMDatabase::GetDocumentKeywords(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_Keywords(&bstr);
	return CString(bstr);
}
CString CWizKMDatabase::GetDocumentType(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_Type(&bstr);
	return CString(bstr);
}
CString CWizKMDatabase::GetDocumentOwner(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_Owner(&bstr);
	return CString(bstr);
}
CString CWizKMDatabase::GetDocumentFileType(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_FileType(&bstr);
	return CString(bstr);
}
CString CWizKMDatabase::GetDocumentText(IWizDocument* pDocument, UINT nFlags)
{
	CComBSTR bstrText;
	pDocument->GetText(nFlags, &bstrText);
	return CString(bstrText);
}
BOOL CWizKMDatabase::GetDocumentText(IWizDocument* pDocument, UINT nFlags, CString& strText)
{
	CComBSTR bstrText;
	HRESULT hr = pDocument->GetText(nFlags, &bstrText);
	strText = bstrText;
	return SUCCEEDED(hr);
}
CString CWizKMDatabase::GetDocumentHtml(IWizDocument* pDocument)
{
	CComBSTR bstrHtml;
	pDocument->GetHtml(&bstrHtml);
	return CString(bstrHtml);
}

COleDateTime CWizKMDatabase::GetDocumentDateCreated(IWizDocument* pDocument)
{
	DATE dt = 0;
	pDocument->get_DateCreated(&dt);
	return dt;
}
COleDateTime CWizKMDatabase::GetDocumentDateModified(IWizDocument* pDocument)
{
	DATE dt = 0;
	pDocument->get_DateModified(&dt);
	return dt;
}
COleDateTime CWizKMDatabase::GetDocumentDateAccessed(IWizDocument* pDocument)
{
	DATE dt = 0;
	pDocument->get_DateAccessed(&dt);
	return dt;
}
COleDateTime CWizKMDatabase::GetDocumentDataDateModified(IWizDocument* pDocument)
{
	DATE dt = 0;
	pDocument->get_DataDateModified(&dt);
	return dt;
}

BOOL CWizKMDatabase::GetDocumentTagGUIDs(IWizDocument* pDocument, CWizStdStringArray& arrayTagGUID)
{
	CWizTagArray arrayTag;
	if (!GetDocumentTags(pDocument, arrayTag))
		return FALSE;
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		arrayTagGUID.push_back(CWizKMDatabase::GetObjectGUID(it->p));
	}
	return TRUE;
}
CString CWizKMDatabase::GetDocumentFileName(IWizDocument* pDocument)
{
	CComBSTR bstr;
	pDocument->get_FileName(&bstr);
	return CString(bstr);
}

CComPtr<IStream> CWizKMDatabase::GetDocumentDataStream(IWizDocument* pDocument)
{
	CString strFileName = GetDocumentFileName(pDocument);
	if (!PathFileExists(strFileName))
	{
		TOLOG1(_T("%1 does not exists!"), strFileName);
		return NULL;
	}
	CComPtr<IStream> spStream;
	HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStream);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create stream: %1"), strFileName);
		return NULL;
	}
	//
	if (!WizStreamLoadFromFile(strFileName, spStream))
	{
		TOLOG1(_T("Failed to load document into stream: %1"), strFileName);
		return NULL;
	}
	//
	return spStream;
}
CComPtr<IStream> CWizKMDatabase::GetAttachmentDataStream(IWizDocumentAttachment* pAttachment)
{
	CString strFileName = GetAttachmentFileName(pAttachment);
	if (!PathFileExists(strFileName))
	{
		TOLOG1(_T("%1 does not exists!"), strFileName);
		return NULL;
	}
	CComPtr<IStream> spStream;
	HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStream);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to create stream: %1"), strFileName);
		return NULL;
	}
	//
	if (!WizStreamLoadFromFile(strFileName, spStream))
	{
		TOLOG1(_T("Failed to load attachment into stream: %1"), strFileName);
		return NULL;
	}
	//
	return spStream;
}
CString CWizKMDatabase::GetParamValue(IWizDocumentParam* pParam)
{
	CComBSTR bstr;
	pParam->get_Value(&bstr);
	return CString(bstr);
}

BOOL CWizKMDatabase::GetDocumentParams(IWizDocument* pDocument, std::vector<WIZDOCUMENTPARAMDATA>& arrayParam)
{
	CWizDocumentParamArray params;
	if (!GetDocumentParams(pDocument, params))
	{
		TOLOG(_T("Failed to get document params!"));
		return FALSE;
	}
	for (CWizDocumentParamArray::const_iterator it = params.begin();
		it != params.end();
		it++)
	{
		WIZDOCUMENTPARAMDATA data;
		data.strName = GetObjectName(it->p);
		data.strValue = GetParamValue(*it); 
		//
		arrayParam.push_back(data);
	}
	//
	return TRUE;
}



CString CWizKMDatabase::GetDocumentStyleGUID(IWizDocument* pDocument)
{
	CComBSTR bstrStyleGUID;
	pDocument->get_StyleGUID(&bstrStyleGUID);
	return CString(bstrStyleGUID);
}

int CWizKMDatabase::GetDocumentAttachmentCount(IWizDocument* pDocument)
{
	long nCount = 0;
	pDocument->get_AttachmentCount(&nCount);
	return nCount;
}
BOOL CWizKMDatabase::GetDocumentAttachments(IWizDocument* pDocument, CWizDocumentAttachmentArray& arrayAttachment)
{
	CComPtr<IDispatch> spCollDisp;
	HRESULT hr = pDocument->get_Attachments(&spCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get attachments"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizDocumentAttachmentCollection, IWizDocumentAttachment>(spCollDisp, arrayAttachment);
}
BOOL CWizKMDatabase::GetDocumentAttachments(IWizDocument* pDocument, CWizStdStringArray& arrayAttachmentFileName)
{
	CWizDocumentAttachmentArray arrayAttachment;
	if (!GetDocumentAttachments(pDocument, arrayAttachment))
		return FALSE;
	//
	for (CWizDocumentAttachmentArray::const_iterator it = arrayAttachment.begin();
		it != arrayAttachment.end();
		it++)
	{
		arrayAttachmentFileName.push_back(CWizKMDatabase::GetAttachmentFileName(it->p));
	}
	return TRUE;
}
BOOL CWizKMDatabase::GetDocumentParams(IWizDocument* pDocument, CWizDocumentParamArray& arrayParam)
{
	CComPtr<IDispatch> spCollDisp;
	HRESULT hr = pDocument->get_Params(&spCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get attachments"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizDocumentParamCollection, IWizDocumentParam>(spCollDisp, arrayParam);
}
CString CWizKMDatabase::GetDocumentParam(IWizDocument* pDocument, LPCTSTR lpszParamName)
{
	CComBSTR bstrValue;
	pDocument->get_ParamValue(CComBSTR(lpszParamName), &bstrValue);
	return CString(bstrValue);
}
int CWizKMDatabase::GetDocumentParamInt(IWizDocument* pDocument, LPCTSTR lpszParamName, int nDef)
{
	CString str = GetDocumentParam(pDocument, lpszParamName);
	if (str.IsEmpty())
		return nDef;
	//
	return _ttoi(str);
}

BOOL CWizKMDatabase::GetDocumentParamBool(IWizDocument* pDocument, LPCTSTR lpszParamName, BOOL bDef)
{
	CString str = GetDocumentParam(pDocument, lpszParamName);
	if (str.IsEmpty())
		return bDef;
	//
	return _ttoi(str) ? TRUE : FALSE;
}

COLORREF CWizKMDatabase::GetDocumentParamColor(IWizDocument* pDocument, LPCTSTR lpszParamName, COLORREF crDef)
{
	CString str = GetDocumentParam(pDocument, lpszParamName);
	if (str.IsEmpty())
		return crDef;
	//
	return WizStringToColor(str);
}

COleDateTime CWizKMDatabase::GetDocumentParamTime(IWizDocument* pDocument, LPCTSTR lpszParamName, const COleDateTime& tDef)
{
	CString str = GetDocumentParam(pDocument, lpszParamName);
	if (str.IsEmpty())
		return tDef;
	//
	return WizStringToDateTime(str);
}
BOOL CWizKMDatabase::GetDocumentParamLine(IWizDocument* pDocument, LPCTSTR lpszParamName, CWizKMDocumentParamLine& line)
{
	CString str = GetDocumentParam(pDocument, lpszParamName);
	if (str.IsEmpty())
		return FALSE;
	//
	line.SetLine(str);
	//
	return TRUE;
}

BOOL CWizKMDatabase::SetDocumentParam(IWizDocument* pDocument, LPCTSTR lpszParamName, LPCTSTR lpszParamValue)
{
	return SUCCEEDED(pDocument->put_ParamValue(CComBSTR(lpszParamName), CComBSTR(lpszParamValue)));
}
BOOL CWizKMDatabase::SetDocumentParamInt(IWizDocument* pDocument, LPCTSTR lpszParamName, int n)
{
	return SetDocumentParam(pDocument, lpszParamName, WizIntToStr(n));
}
BOOL CWizKMDatabase::SetDocumentParamBool(IWizDocument* pDocument, LPCTSTR lpszParamName, BOOL b)
{
	return SetDocumentParam(pDocument, lpszParamName, b ? _T("1") : _T("0"));
}
BOOL CWizKMDatabase::SetDocumentParamColor(IWizDocument* pDocument, LPCTSTR lpszParamName, COLORREF cr)
{
	return SetDocumentParam(pDocument, lpszParamName, WizColorToString(cr));
}
BOOL CWizKMDatabase::SetDocumentParamTime(IWizDocument* pDocument, LPCTSTR lpszParamName, const COleDateTime& t)
{
	return SetDocumentParam(pDocument, lpszParamName, WizDateTimeToString(t));
}


BOOL CWizKMDatabase::GetDocumentTags(IWizDocument* pDocument, CWizTagArray& arrayTag)
{
	CComPtr<IDispatch> spCollDisp;
	HRESULT hr = pDocument->get_Tags(&spCollDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get document tags"));
		return FALSE;
	}
	//
	return WizCollectionDispatchToArray<IWizTagCollection, IWizTag>(spCollDisp, arrayTag);
}
BOOL CWizKMDatabase::GetDocumentTagsNameStringArray(IWizDocument* pDocument, CWizStdStringArray& arrayTagName)
{
	CWizTagArray arrayTag;
	if (!GetDocumentTags(pDocument, arrayTag))
		return FALSE;
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		arrayTagName.push_back(GetObjectName(it->p));
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetDocumentTagsText(IWizDocument* pDocument, CString& strTagText)
{
	CWizTagArray arrayTag;
	if (!GetDocumentTags(pDocument, arrayTag))
		return FALSE;
	//
	strTagText.Empty();
	//
	for (CWizTagArray::const_iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		if (strTagText.IsEmpty())
		{
			strTagText = GetObjectName(it->p);
		}
		else
		{
			strTagText = strTagText + _T("; ") + GetObjectName(it->p);
		}
	}
	//
	return TRUE;
}


CString CWizKMDatabase::GetAttachmentFileName(IWizDocumentAttachment* pAttachment)
{
	CComBSTR bstrFileName;
	pAttachment->get_FileName(&bstrFileName);
	return CString(bstrFileName);
}

int CWizKMDatabase::GetAttachmentSize(IWizDocumentAttachment* pAttachment)
{
	long nSize = 0;
	pAttachment->get_Size(&nSize);
	return nSize;
}

CComPtr<IWizDocument> CWizKMDatabase::GetAttachmentDocument(IWizDocumentAttachment* pAttachment)
{
	CComPtr<IDispatch> spDisp;
	pAttachment->get_Document(&spDisp);
	//
	return CComQIPtr<IWizDocument>(spDisp);
}
CString CWizKMDatabase::GetAttachmentDocumentTitle(IWizDocumentAttachment* pAttachment)
{
	CComPtr<IWizDocument> spDocument = GetAttachmentDocument(pAttachment);
	if (!spDocument)
		return CString();
	//
	return GetDocumentTitle(spDocument);
}

CString CWizKMDatabase::GetAttachmentDocumentGUID(IWizDocumentAttachment* pAttachment)
{
	CComBSTR bstr;
	pAttachment->get_DocumentGUID(&bstr);
	return CString(bstr);
}

BOOL CWizKMDatabase::GetDocumentAttachmentNameSet(IWizDocument* pDocument, CWizStringSet& setAttachment)
{
	CWizDocumentAttachmentArray arrayAttachment;
	if (!GetDocumentAttachments(pDocument, arrayAttachment))
	{
		TOLOG(_T("Failed to cast get document attachments!"));
		return FALSE;
	}
	//
	for (CWizDocumentAttachmentArray::const_iterator it = arrayAttachment.begin();
		it != arrayAttachment.end();
		it++)
	{
		setAttachment.insert(GetObjectName(it->p));
	}
	//
	return TRUE;
}

COLORREF CWizKMDatabase::GetStyleTextColor(IWizStyle* pStyle)
{
	long nColor = 0;
	pStyle->get_TextColor(&nColor);
	return nColor;
}
COLORREF CWizKMDatabase::GetStyleBackgroundColor(IWizStyle* pStyle)
{
	long nColor = 0;
	pStyle->get_BackColor(&nColor);
	return nColor;
}
BOOL CWizKMDatabase::GetStyleTextBold(IWizStyle* pStyle)
{
	VARIANT_BOOL vb = VARIANT_FALSE;
	pStyle->get_TextBold(&vb);
	return vb ? TRUE : FALSE;
}
int CWizKMDatabase::GetStyleFlagIndex(IWizStyle* pStyle)
{
	long nFlagIndex = 0;
	pStyle->get_FlagIndex(&nFlagIndex);
	return nFlagIndex;
}

CComPtr<IWizFolder> CWizKMDatabase::GetDocumentFolder(IWizDocument* pDocument)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = pDocument->get_Parent(&spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get the folder of the document: %1"), GetDocumentTitle(pDocument));
		return NULL;
	}
	//
	return CComQIPtr<IWizFolder>(spDisp);
}

CComPtr<IWizTag> CWizKMDatabase::GetTagByGUID(LPCTSTR lpszGUID)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->TagFromGUID(CComBSTR(lpszGUID), &spDisp);
	if (FAILED(hr))
	{
		//TOLOG1(_T("Failed to get the style from guid: %1"), lpszGUID);
		return NULL;
	}
	//
	return CComQIPtr<IWizTag>(spDisp);
}
CComPtr<IWizStyle> CWizKMDatabase::GetStyleByGUID(LPCTSTR lpszGUID)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->StyleFromGUID(CComBSTR(lpszGUID), &spDisp);
	if (FAILED(hr))
	{
		//TOLOG1(_T("Failed to get the style from guid: %1"), lpszGUID);
		return NULL;
	}
	//
	return CComQIPtr<IWizStyle>(spDisp);
}

CComPtr<IWizDocument> CWizKMDatabase::GetDocumentByGUID(LPCTSTR lpszGUID)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->DocumentFromGUID(CComBSTR(lpszGUID), &spDisp);
	if (FAILED(hr))
	{
		//TOLOG1(_T("Failed to get the document from guid: %1"), lpszGUID);
		return NULL;
	}
	//
	return CComQIPtr<IWizDocument>(spDisp);
}
CComPtr<IWizDocumentAttachment> CWizKMDatabase::GetAttachmentByGUID(LPCTSTR lpszGUID)
{
	ATLASSERT(m_spDatabase);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->AttachmentFromGUID(CComBSTR(lpszGUID), &spDisp);
	if (FAILED(hr))
	{
		//TOLOG1(_T("Failed to get the attachment from guid: %1"), lpszGUID);
		return NULL;
	}
	//
	return CComQIPtr<IWizDocumentAttachment>(spDisp);
}


CString CWizKMDatabase::GetParentTagGUID(IWizTag* pTag)
{
	CComBSTR bstr;
	pTag->get_ParentTagGUID(&bstr);
	return CString(bstr);
}
CComPtr<IWizTag> CWizKMDatabase::GetParentTag(IWizTag* pTag)
{
	CComPtr<IDispatch> spDisp;
	pTag->get_ParentTag(&spDisp);
	//
	return CComQIPtr<IWizTag>(spDisp);
}

int CWizKMDatabase::GetDeletedGUIDType(IWizDeletedGUID* pGUID)
{
	long nType = 0;
	pGUID->get_TypeValue(&nType);
	return nType;
}
COleDateTime CWizKMDatabase::GetDeletedGUIDTime(IWizDeletedGUID* pGUID)
{
	DATE dt = 0;
	pGUID->get_DeletedTime(&dt);
	return dt;
}
CComPtr<IDispatch> CWizKMDatabase::GetObjectsByTime(LPCTSTR lpszObjectType, const COleDateTime& t)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->GetObjectsByTime(t, CComBSTR(lpszObjectType), &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get objects: %1"), lpszObjectType);
		return NULL;
	}
	//
	return spDisp;
}
CComPtr<IDispatch> CWizKMDatabase::GetModifiedObjects(LPCTSTR lpszObjectType)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->GetModifiedObjects(CComBSTR(lpszObjectType), &spDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to get objects: %1"), lpszObjectType);
		return NULL;
	}
	//
	return spDisp;
}

CString CWizKMDatabase::GetMeta(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey)
{
	CComBSTR bstrValue;
	m_spDatabase->get_Meta(CComBSTR(lpszMetaName), CComBSTR(lpszMetaKey), &bstrValue);
	return CString(bstrValue);
}
BOOL CWizKMDatabase::SetMeta(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, LPCTSTR lpszValue)
{
	return SUCCEEDED(m_spDatabase->put_Meta(CComBSTR(lpszMetaName), CComBSTR(lpszMetaKey), CComBSTR(lpszValue)));
}
__int64 CWizKMDatabase::GetMetaInt64(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, __int64 nDef)
{
	CString str = GetMeta(lpszMetaName, lpszMetaKey);
	if (str.IsEmpty())
		return nDef;
	//
	return _ttoi64(str);
}
BOOL CWizKMDatabase::SetMetaInt64(LPCTSTR lpszMetaName, LPCTSTR lpszMetaKey, __int64 nVal)
{
	return SetMeta(lpszMetaName, lpszMetaKey, WizInt64ToStr(nVal));
}

BOOL CWizKMDatabase::Search(LPCTSTR lpszKeywords, long nFlags, IWizFolder* pFolder, long nMaxResults, IDispatch** ppDocumentCollectionDisp)
{
	if (!m_spDatabase)
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
	//
	HRESULT hr = m_spDatabase->SearchDocuments(CComBSTR(lpszKeywords), nFlags, pFolder, nMaxResults, ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to search %1"), lpszKeywords);
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::Search(LPCTSTR lpszKeywords, long nFlags, IWizFolder* pFolder, long nMaxResults, IWizDocumentCollection** ppDocumentCollection)
{
	CComPtr<IDispatch> spDisp;
	if (!Search(lpszKeywords, nFlags, pFolder, nMaxResults, &spDisp))
		return FALSE;
	//
	return SUCCEEDED(spDisp->QueryInterface(ppDocumentCollection));
}
BOOL CWizKMDatabase::GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, IWizDocumentCollection** ppDocumentCollection)
{
	CComPtr<IDispatch> spDisp;
	if (!GetRecentDocuments(nFlags, lpszDocumentType, nCount, &spDisp))
		return FALSE;
	//
	return SUCCEEDED(spDisp->QueryInterface(ppDocumentCollection));
}
BOOL CWizKMDatabase::GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, IDispatch** ppDocumentCollectionDisp)
{
	if (!m_spDatabase)
	{
		ATLASSERT(FALSE);
		return FALSE;
	}
	//
	HRESULT hr = m_spDatabase->GetRecentDocuments2(nFlags, CComBSTR(lpszDocumentType), nCount, ppDocumentCollectionDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get recent documents"));
		return FALSE;
	}
	//
	return TRUE;
}
BOOL CWizKMDatabase::GetRecentDocuments(long nFlags, LPCTSTR lpszDocumentType, int nCount, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDisp;
	if (!GetRecentDocuments(nFlags, lpszDocumentType, nCount, &spDisp))
		return FALSE;
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
}

BOOL CWizKMDatabase::GetVirtualFolders(CWizStdStringArray& arrayVirtualFolderName)
{
	CComVariant v;
	if (FAILED(m_spDatabase->GetVirtualFolders(&v)))
	{
		TOLOG(_T("Failed to get virtual folders"));
		return FALSE;
	}
	//
	return WizVariantToStringArray(v, arrayVirtualFolderName);
}
BOOL CWizKMDatabase::GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, IWizDocumentCollection** ppDocumentCollection)
{
	CComPtr<IDispatch> spDisp;
	if (!GetVirtualFolderDocuments(lpszVirtualFolderName, &spDisp))
		return FALSE;
	//
	return SUCCEEDED(spDisp->QueryInterface(IID_IWizDocumentCollection, (void**)ppDocumentCollection));
}
BOOL CWizKMDatabase::GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, IDispatch** ppDocumentCollectionDisp)
{
	return SUCCEEDED(m_spDatabase->GetVirtualFolderDocuments(CComBSTR(lpszVirtualFolderName), ppDocumentCollectionDisp));
}
BOOL CWizKMDatabase::GetVirtualFolderDocuments(LPCTSTR lpszVirtualFolderName, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDocumentCollectionDisp;
	if (!GetVirtualFolderDocuments(lpszVirtualFolderName, &spDocumentCollectionDisp))
		return FALSE;
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDocumentCollectionDisp, arrayDocument);
}
CString CWizKMDatabase::GetVirtualFolderIcon(LPCTSTR lpszVirtualFolderName)
{
	CComBSTR bstrFileName;
	m_spDatabase->GetVirtualFolderIcon(CComBSTR(lpszVirtualFolderName), &bstrFileName);
	//
	return CString(bstrFileName);
}

BOOL CWizKMDatabase::GetAllFoldersDocumentCount(long nFlags, CWizFolderDocumentCountMap& mapDocumentCount)
{
	mapDocumentCount.clear();
	//
	CComVariant v;
	HRESULT hr = m_spDatabase->GetAllFoldersDocumentCount(nFlags, &v);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get all folders document count!"));
		return FALSE;
	}
	//
	CWizStdStringArray arrayText;
	if (!WizVariantToStringArray(v, arrayText))
		return FALSE;
	//
	for (CWizStdStringArray::const_iterator it = arrayText.begin();
		it != arrayText.end();
		it++)
	{
		CString strDocumentCount;
		CString strLocation;
		if (WizStringSimpleSplit(*it, '=', strDocumentCount, strLocation)
			&& !strLocation.IsEmpty()
			&& !strDocumentCount.IsEmpty())
		{
			WIZKMFOLDERDOCUMENTCOUNTDATA data;
			data.nSelf = _ttoi(strDocumentCount);
			int nPos = strDocumentCount.Find('/');
			if (-1 != nPos)
			{
				data.nIncludeChildren = _ttoi(strDocumentCount.Right(strDocumentCount.GetLength() - (nPos + 1)));
			}
			//
			mapDocumentCount[strLocation] = data;
		}
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetAllTagsDocumentCount(long nFlags, CWizTagDocumentCountMap& mapDocumentCount)
{
	mapDocumentCount.clear();
	//
	CComVariant v;
	HRESULT hr = m_spDatabase->GetAllTagsDocumentCount(nFlags, &v);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get all tags document count!"));
		return FALSE;
	}
	//
	CWizStdStringArray arrayText;
	if (!WizVariantToStringArray(v, arrayText))
		return FALSE;
	//
	for (CWizStdStringArray::const_iterator it = arrayText.begin();
		it != arrayText.end();
		it++)
	{
		CString strDocumentCount;
		CString strTagGUID;
		if (WizStringSimpleSplit(*it, '=', strDocumentCount, strTagGUID)
			&& !strTagGUID.IsEmpty()
			&& !strDocumentCount.IsEmpty())
		{
			mapDocumentCount[strTagGUID] = _ttoi(strDocumentCount);
		}
	}
	//
	return TRUE;
}

BOOL CWizKMDatabase::GetCalendarEvents(const COleDateTime& tStart, const COleDateTime& tEnd, CWizDocumentArray& arrayDocument)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->GetCalendarEvents(tStart, tEnd, &spDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get calendar events"));
		return NULL;
	}
	//
	return WizCollectionDispatchToArray<IWizDocumentCollection, IWizDocument>(spDisp, arrayDocument);
}
BOOL CWizKMDatabase::GetCalendarEvents(const COleDateTime& tStart, const COleDateTime& tEnd, CWizEventArray& arrayEvent)
{
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_spDatabase->GetCalendarEvents2(tStart, tEnd, &spDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get calendar events"));
		return NULL;
	}
	//
	return WizCollectionDispatchToArray<IWizEventCollection, IWizEvent>(spDisp, arrayEvent);
}

CString CWizKMDatabase::DocumentToWizKMURL(IWizDocument* pDocument)
{
	ATLASSERT(pDocument);
	return WizFormatString1(_T("wiz:open_document?guid=%1"), GetObjectGUID(pDocument));
}
CString CWizKMDatabase::AttachmentToWizKMURL(IWizDocumentAttachment* pAttachment)
{
	ATLASSERT(pAttachment);
	return WizFormatString1(_T("wiz:open_attachment?guid=%1"), GetObjectGUID(pAttachment));
}

BOOL WizKMURLIsOld(LPCTSTR lpszURL)
{
	ATLASSERT(lpszURL);
	return 0 == _tcsnicmp(lpszURL, _T("wizkm://"), 8);
}
CString WizKMURLGetParamValueOld(LPCTSTR lpszURL, LPCTSTR lpszParamName)
{
	ATLASSERT(CWizKMDatabase::IsWizKMURL(lpszURL));
	if (!CWizKMDatabase::IsWizKMURL(lpszURL))
		return CString();
	//
	CString strURL(lpszURL);
	int nParamBegin = strURL.Find('?');
	if (-1 == nParamBegin)
		return CString();
	//
	strURL.Delete(0, nParamBegin + 1);
	//
	CWizStdStringArray arrayParam;
	WizSplitTextToArray(strURL, '&', arrayParam);
	//
	return WizStringArrayGetValue(arrayParam, lpszParamName);
}

CString WizKMURLGetTypeOld(LPCTSTR lpszURL)
{
	return WizKMURLGetParamValueOld(lpszURL, _T("type"));
}

BOOL CWizKMDatabase::IsWizKMURL(LPCTSTR lpszURL)
{
	ATLASSERT(lpszURL);
	return WizKMURLIsOld(lpszURL)
		|| 0 == _tcsnicmp(lpszURL, _T("wiz:"), 4);
}

CString CWizKMDatabase::WizKMURLGetCommand(LPCTSTR lpszURL)
{
	ATLASSERT(lpszURL);
	//
	if (!IsWizKMURL(lpszURL))
		return CString();
	//
	if (WizKMURLIsOld(lpszURL))
	{
		CString strType = WizKMURLGetTypeOld(lpszURL);
		strType.MakeLower();
		if (strType == _T("document"))
		{
			return CString(_T("open_document"));
		}
		else if (strType == _T("attachment"))
		{
			return CString(_T("open_attachment"));
		}
		else
		{
			return _T("unknown_command");
		}
	}
	else
	{
		CString strURL(lpszURL);
		//
		if(strURL.GetLength() <= 5)
			return CString();
		//
		strURL.Delete(0, 4);	//wiz:
		//
		int nPos = strURL.Find('?');
		if (-1 == nPos)
			return strURL;
		//
		strURL = strURL.Left(nPos);
		//
		return strURL;
	}
}

BOOL CWizKMDatabase::IsWizKMDocumentURL(LPCTSTR lpszURL)
{
	if (!IsWizKMURL(lpszURL))
		return FALSE;
	//
	return 0 == WizKMURLGetCommand(lpszURL).CompareNoCase(_T("open_document"));
}
BOOL CWizKMDatabase::IsWizKMAttachmentURL(LPCTSTR lpszURL)
{
	if (!IsWizKMURL(lpszURL))
		return FALSE;
	//
	return 0 == WizKMURLGetCommand(lpszURL).CompareNoCase(_T("open_attachment"));
}
CString CWizKMDatabase::WizKMURLGetParamValue(LPCTSTR lpszURL, LPCTSTR lpszParamName)
{
	ATLASSERT(IsWizKMURL(lpszURL));
	if (!IsWizKMURL(lpszURL))
		return CString();
	//
	CString strURL(lpszURL);
	int nParamBegin = strURL.Find('?');
	if (-1 == nParamBegin)
		return CString();
	//
	strURL.Delete(0, nParamBegin + 1);
	//
	int nBookmark = strURL.Find('#');
	if (nBookmark != -1)
	{
		strURL = strURL.Left(nBookmark);
	}
	//
	//
	CWizStdStringArray arrayParam;
	WizSplitTextToArray(strURL, '&', arrayParam);
	//
	return WizStringArrayGetValue(arrayParam, lpszParamName);
}

CString CWizKMDatabase::WizKMURLGetGUID(LPCTSTR lpszURL)
{
	return WizKMURLGetParamValue(lpszURL, _T("guid"));
}
CString CWizKMDatabase::GetDocumentGUIDFromWizKMURL(LPCTSTR lpszURL)
{
	ATLASSERT(IsWizKMDocumentURL(lpszURL));
	if (!IsWizKMDocumentURL(lpszURL))
		return CString();
	//
	return WizKMURLGetGUID(lpszURL);
}
CString CWizKMDatabase::GetAttachmentGUIDFromWizKMURL(LPCTSTR lpszURL)
{
	ATLASSERT(IsWizKMAttachmentURL(lpszURL));
	if (!IsWizKMAttachmentURL(lpszURL))
		return CString();
	//
	return WizKMURLGetGUID(lpszURL);
}
CComPtr<IWizDocument> CWizKMDatabase::GetDocumentFromWizKMURL(LPCTSTR lpszURL)
{
	CString strGUID = GetDocumentGUIDFromWizKMURL(lpszURL);
	if (strGUID.IsEmpty())
		return NULL;
	//
	return GetDocumentByGUID(strGUID);
}
CComPtr<IWizDocumentAttachment> CWizKMDatabase::GetAttachmentFromWizKMURL(LPCTSTR lpszURL)
{
	CString strGUID = GetAttachmentGUIDFromWizKMURL(lpszURL);
	if (strGUID.IsEmpty())
		return NULL;
	//
	return GetAttachmentByGUID(strGUID);
}
CComPtr<IWizDocument> CWizKMDatabase::CreateDocument2(IWizFolder* pFolder, LPCTSTR lpszTitle, LPCTSTR lpszURL)
{
	ATLASSERT(pFolder);
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = pFolder->CreateDocument2(CComBSTR(lpszTitle), CComBSTR(lpszURL), &spDisp);
	if (FAILED(hr))
	{
		TOLOG(WizFormatString1(_T("Failed to create document: %1"), lpszTitle));
		return NULL;
	}
	//
	return CComQIPtr<IWizDocument>(spDisp);
}
BOOL CWizKMDatabase::BackupAll(LPCTSTR lpszPath)
{
	CHECK_DATABASE();
	//
	HRESULT hr = m_spDatabase->BackupAll(CComBSTR(lpszPath));
	return SUCCEEDED(hr);
}
BOOL CWizKMDatabase::BackupIndex()
{
	CHECK_DATABASE();
	//
	HRESULT hr = m_spDatabase->BackupIndex();
	return SUCCEEDED(hr);
}

CString CWizKMDatabase::GetUserName()
{
	if (!m_spDatabase)
		return CString();
	//
	CComBSTR bstrUserName;
	m_spDatabase->get_UserName(&bstrUserName);
	return CString(bstrUserName);
}
BOOL CWizKMDatabase::SetUserName(LPCTSTR lpszUserName)
{
	if (!m_spDatabase)
		return FALSE;
	//
	CComBSTR bstrUserName;
	HRESULT hr = m_spDatabase->put_UserName(CComBSTR(lpszUserName));
	if (FAILED(hr))
		return FALSE;
	//
	return TRUE;
}
CString CWizKMDatabase::GetEncryptedPassword()
{
	if (!m_spDatabase)
		return CString();
	//
	CComBSTR bstrPassword;
	m_spDatabase->GetEncryptedPassword(&bstrPassword);
	return CString(bstrPassword);
}
CString CWizKMDatabase::GetUserPassword()
{
	if (!m_spDatabase)
		return CString();
	//
	CComBSTR bstrPassword;
	m_spDatabase->GetUserPassword(&bstrPassword);
	return CString(bstrPassword);
}
BOOL CWizKMDatabase::ChangePassword(LPCTSTR lpszOldPassword, LPCTSTR lpszNewPassword)
{
	if (!m_spDatabase)
		return FALSE;
	//
	HRESULT hr = m_spDatabase->ChangePassword(CComBSTR(lpszOldPassword), CComBSTR(lpszNewPassword));
	return SUCCEEDED(hr);
}
UINT CWizKMDatabase::GetPasswordFlags()
{
	if (!m_spDatabase)
		return 0;
	//
	long nFlags = 0;
	m_spDatabase->get_PasswordFlags(&nFlags);
	return nFlags;
}
BOOL CWizKMDatabase::SetPasswordFlags(UINT nFlags)
{
	if (!m_spDatabase)
		return FALSE;
	//
	HRESULT hr = m_spDatabase->put_PasswordFlags(nFlags);	
	return SUCCEEDED(hr);
}

CString CWizKMDatabase::GetUserType()
{
	return GetMeta(_T("SERVER_INFO"), _T("user_type"));
}

CComPtr<IWizDocument> CWizKMDatabase::GetEventDocument(IWizEvent* pEvent)
{
	if (!pEvent)
		return NULL;
	//
	CComPtr<IDispatch> spDisp;
	pEvent->get_Document(&spDisp);
	//
	return CComQIPtr<IWizDocument>(spDisp);
}
CString CWizKMDatabase::GetKnownRootTagName(LPCTSTR lpszName)
{
	if (!m_spDatabase)
		return CString();
	//
	CComBSTR bstrName;
	m_spDatabase->GetKnownRootTagName(CComBSTR(lpszName), &bstrName);
	//
	return CString(bstrName);
}

BOOL CWizKMDatabase::GetCert(CString& strN, CString& stre, CString& strEncrypted_d, CString& strHint)
{
	if (!m_spDatabase)
		return FALSE;
	//
	CComBSTR bstrN;
	CComBSTR bstre;
	CComBSTR bstrEncrypted_d;
	CComBSTR bstrHint;
	//
	HRESULT hr1 = m_spDatabase->GetCertN(&bstrN);
	HRESULT hr2 = m_spDatabase->GetCerte(&bstre);
	HRESULT hr3 = m_spDatabase->GetEncryptedCertd(&bstrEncrypted_d);
	m_spDatabase->GetCertHint(&bstrHint);
	//
	strN = CString(bstrN);
	stre = CString(bstre);
	strEncrypted_d = CString(bstrEncrypted_d);
	strHint = CString(bstrHint);
	//
	return SUCCEEDED(hr1)
		&& SUCCEEDED(hr2)
		&& SUCCEEDED(hr3);
}
BOOL CWizKMDatabase::SetCert(LPCTSTR lpszN, LPCTSTR lpsze, LPCTSTR lpszEncrypted_d, LPCTSTR lpszHint, long nFlags, __int64 nWindowHandle)
{
	if (!m_spDatabase)
		return FALSE;
	//
	HRESULT hr = m_spDatabase->SetCert(CComBSTR(lpszN), CComBSTR(lpsze), CComBSTR(lpszEncrypted_d), CComBSTR(lpszHint), nFlags, nWindowHandle);
	return SUCCEEDED(hr);
}
//
BOOL CWizKMDatabase::IsUseWizServer()
{
	if (!::WizKMIsOEM())
		return TRUE;
	//
	CString str = GetMeta(_T("Sync"), _T("UseWizServer"));
	return str == _T("1");
}
//
BOOL CWizKMDatabase::SetUseWizServer(BOOL b)
{
	if (!::WizKMIsOEM())
		return TRUE;
	//
	return SetMeta(_T("Sync"), _T("UseWizServer"), b ? _T("1") : _T("0"));
}
