#ifndef __WIZDATABASEDEF_H__
#define __WIZDATABASEDEF_H__

#pragma once


enum WIZTODOSTATE
{
	todoState0,
	todoState25,
	todoState50,
	todoState75,
	todoState100,
	todoStateMixed
};

enum WIZTODOPRIOR
{
	todoPriorNotUrgentAndNotImportant = -1,
	todoPriorNormal = 0,
	todoPriorImportant = 1,
	todoPriorUrgent = 2,
	todoPriorUrgentAndImportant = 3
};

struct WIZTODODATA
{
	CString strText;
	WIZTODOSTATE eState;
	WIZTODOPRIOR ePrior;
	CWizStdStringArray arrayLinkedDocumentGUID;
	BOOL bBlank;
	//
	COleDateTime tCreated;
	COleDateTime tModified;
	COleDateTime tCompleted;
	//
	__int64 nOrder;
	//
	WIZTODODATA()
	{
		nOrder = 0;
		bBlank = FALSE;
		eState = todoState0;
		ePrior = todoPriorNormal;
		//
		InitTime();
	}
	WIZTODODATA(LPCTSTR lpszText, WIZTODOSTATE state, WIZTODOPRIOR prior)
		: strText(lpszText)
		, eState(state)
		, ePrior(prior)
	{
		nOrder = 0;
		bBlank = FALSE;
		//
		InitTime();
	}
	//
	void InitTime()
	{
		static int index = 0;
		index++;
		//
		tCreated = WizGetCurrentTime();
		tModified = WizGetCurrentTime();
		tCompleted = WizGetCurrentTime();
		//
		nOrder = WizTimeGetTimeT(tCreated);
		nOrder = nOrder * 1000;
		nOrder = nOrder + index;
	}
	//
	void AddLink(LPCTSTR lpszDocumentGUID)
	{
		arrayLinkedDocumentGUID.push_back(lpszDocumentGUID);
	}
	//
	CString GetLinkedDocumentGUIDString() const
	{
		CString strText;
		WizStringArrayToText(arrayLinkedDocumentGUID, strText, _T(";"));
		return strText;
	}
	//
	void SetLinkedDocumentGUIDString(LPCTSTR lpsz)
	{
		WizSplitTextToArray(lpsz, ';', arrayLinkedDocumentGUID);
	}
};


#pragma pack(1)


#define WIZVIRTUALFOLDER_OVERVIEW		_T("Quick Views")
#define WIZVIRTUALFOLDER_CREATED		_T("Recent Created Documents")
#define WIZVIRTUALFOLDER_MODIFIED		_T("Recent Modified Documents")

#define WIZKM_XMKRPC_DOCUMENT_PART_INFO		0x01
#define WIZKM_XMKRPC_DOCUMENT_PART_DATA		0x02
#define WIZKM_XMKRPC_DOCUMENT_PART_PARAM		0x04


#define WIZKM_XMKRPC_ATTACHMENT_PART_INFO		0x01
#define WIZKM_XMKRPC_ATTACHMENT_PART_DATA		0x02

struct WIZTAGDATA
{
	CString strGUID;
	CString strParentGUID;
	CString strName;
	CString strDescription;
	COleDateTime tModified;
	__int64 nVersion;
	//
	WIZTAGDATA()
	{
		nVersion = -1;
	}
	//
	friend bool operator< ( _In_ const WIZTAGDATA& data1, _In_ const WIZTAGDATA& data2 ) throw()
	{
		return( data1.strName.CompareNoCase( data2.strName) < 0 );
	}
	BOOL EqualForSync(const WIZTAGDATA& data) const
	{
		ATLASSERT(strGUID == data.strGUID);
		return strName == data.strName
			&& strDescription == data.strDescription
			&& strParentGUID == data.strParentGUID;
	}
	//
	CString GetObjectsFileName(LPCTSTR lpszDatabasePath) const
	{
		CString strDatabasePath(lpszDatabasePath);
		WizPathAddBackslash(strDatabasePath);
		//
		return strDatabasePath + _T(".tags");
	}
};

struct WIZSTYLEDATA
{
	CString strGUID;
	CString strName;
	CString strDescription;
	COLORREF crTextColor;
	COLORREF crBackColor;
	BOOL bTextBold;
	int nFlagIndex;
	COleDateTime tModified;
	__int64 nVersion;
	//
	WIZSTYLEDATA()
	{
		bTextBold = FALSE;
		nFlagIndex = 0;
		nVersion = -1;
	}
	//
	friend bool operator< ( _In_ const WIZSTYLEDATA& data1, _In_ const WIZSTYLEDATA& data2 ) throw()
	{
		return( data1.strName.CompareNoCase( data2.strName) < 0 );
	}
	BOOL EqualForSync(const WIZSTYLEDATA& data) const
	{
		ATLASSERT(strGUID == data.strGUID);
		return strName == data.strName
			&& strDescription == data.strDescription
			&& crTextColor == data.crTextColor
			&& crBackColor == data.crBackColor
			&& bool(bTextBold ? true : false) == bool(data.bTextBold ? true : false)
			&& nFlagIndex == data.nFlagIndex;
	}
	//
	CString GetObjectsFileName(LPCTSTR lpszDatabasePath) const
	{
		CString strDatabasePath(lpszDatabasePath);
		WizPathAddBackslash(strDatabasePath);
		//
		return strDatabasePath + _T(".styles");
	}
};


struct WIZDOCUMENTDATA
{
	CString strGUID;
	CString strTitle;
	CString strName;
	CString strSEO;
	CString strLocation;
	CString strURL;
	CString strAuthor;
	CString strKeywords;
	CString strType;
	CString strOwner;
	CString strFileType;
	CString strStyleGUID;
	COleDateTime tCreated;
	COleDateTime tModified;
	COleDateTime tAccessed;
	long nIconIndex;
	long nSync;
	long nProtected;
	long nReadCount;
	long nAttachmentCount;
	long nIndexed;
	COleDateTime tInfoModified;
	CString strInfoMD5;
	COleDateTime tDataModified;
	CString strDataMD5;
	COleDateTime tParamModified;
	CString strParamMD5;
	__int64 nVersion;
	//
	WIZDOCUMENTDATA()
	{
		nIconIndex = 0;
		nSync = 0;
		nProtected = 0;
		nReadCount = 0;
		nAttachmentCount = 0;
		nIndexed = 0;
		nVersion = -1;
	}
	BOOL EqualForSync(const WIZDOCUMENTDATA& data) const
	{
		ATLASSERT(strGUID == data.strGUID);
		return strInfoMD5 == data.strInfoMD5
			&& strDataMD5 == data.strDataMD5
			&& strParamMD5 == data.strParamMD5;
	}
	//
	CString GetObjectsFileName(LPCTSTR lpszDatabasePath) const
	{
		CString strDatabasePath(lpszDatabasePath);
		WizPathRemoveBackslash(strDatabasePath);
		//
		CString strObjectsFileName = strDatabasePath + strLocation + _T(".documents");
		strObjectsFileName.Replace('/', '\\');
		return strObjectsFileName;
	}
};

struct WIZDOCUMENTPARAMDATA
{
	CString strDocumentGUID;
	CString strName;
	CString strValue;
};


enum WizGUIDType
{
	wizguidtypeError = -1,
	wizguidtypeTag = 1,
	wizguidtypeStyle,
	wizguidtypeDocumentAttachment,
	wizguidtypeDocument,
};

struct WIZDELETEDGUIDDATA
{
	CString strGUID;
	WizGUIDType eType;
	COleDateTime tDeleted;
	__int64 nVersion;
	//
	WIZDELETEDGUIDDATA()
	{
		eType = wizguidtypeError;
		nVersion = 0;
	}
	//
	static WizGUIDType IntToGUIDType(int n)
	{
		if (n <= wizguidtypeError || n > wizguidtypeDocument)
		{
			ATLASSERT(FALSE);
			return wizguidtypeError;
		}
		//
		return WizGUIDType(n);
	}
	static WizGUIDType TypeStringToGUIDType(LPCTSTR lpszType)
	{
		if (!lpszType || !*lpszType)
		{
			TOLOG1(_T("Unknown guid type: %1"), lpszType);
			ATLASSERT(FALSE);
			return wizguidtypeError;
		}
		//
		if (0 == _tcsicmp(lpszType, _T("tag")))
			return wizguidtypeTag;
		if (0 == _tcsicmp(lpszType, _T("tag_group")))
			return wizguidtypeTag;
		else if (0 == _tcsicmp(lpszType, _T("style")))
			return wizguidtypeStyle;
		else if (0 == _tcsicmp(lpszType, _T("attachment")))
			return wizguidtypeDocumentAttachment;
		else if (0 == _tcsicmp(lpszType, _T("document")))
			return wizguidtypeDocument;
		//
		TOLOG1(_T("Unknown guid type: %1"), lpszType);
		ATLASSERT(FALSE);
		return wizguidtypeError;
	}
	static CString GUIDTypeToTypeString(WizGUIDType eType)
	{
		switch (eType)
		{
		case wizguidtypeTag:
			return CString(_T("tag"));
		case wizguidtypeStyle:
			return CString(_T("style"));
		case wizguidtypeDocumentAttachment:
			return CString(_T("attachment"));
		case wizguidtypeDocument:
			return CString(_T("document"));
		default:
			TOLOG1(_T("Unknown guid type value: %1"), WizIntToStr(eType));
			ATLASSERT(FALSE);
			return CString();
		}
	}
	BOOL EqualForSync(const WIZDELETEDGUIDDATA& data) const
	{
		ATLASSERT(strGUID == data.strGUID);
		return TRUE;
	}
};

struct WIZDOCUMENTATTACHMENTDATA
{
	CString strGUID;
	CString strDocumentGUID;
	CString strName;
	CString strURL;
	CString strDescription;
	COleDateTime tInfoModified;
	CString strInfoMD5;
	COleDateTime tDataModified;
	CString strDataMD5;
	__int64 nVersion;
	//
	WIZDOCUMENTATTACHMENTDATA()
	{
		nVersion = -1;
	}
	//
	friend bool operator< ( _In_ const WIZDOCUMENTATTACHMENTDATA& data1, _In_ const WIZDOCUMENTATTACHMENTDATA& data2 ) throw()
	{
		return( data1.strName.CompareNoCase( data2.strName) < 0 );
	}
	BOOL EqualForSync(const WIZDOCUMENTATTACHMENTDATA& data) const
	{
		ATLASSERT(strGUID == data.strGUID);
		return strInfoMD5 == data.strInfoMD5
			&& strDataMD5 == data.strDataMD5;
	}
};


struct WIZMETADATA
{
	CString strName;
	CString strKey;
	CString strValue;
	COleDateTime tModified;
	//
	CString GetObjectsFileName(LPCTSTR lpszDatabasePath) const
	{
		CString strDatabasePath(lpszDatabasePath);
		WizPathAddBackslash(strDatabasePath);
		//
		return strDatabasePath + _T(".metas");
	}
};


struct WIZDOCUMENTDATAEX : public WIZDOCUMENTDATA
{
	WIZDOCUMENTDATAEX()
	{
		bSkipped = FALSE;
	}
	WIZDOCUMENTDATAEX(const WIZDOCUMENTDATA& data)
		: WIZDOCUMENTDATA(data)
	{
		bSkipped = FALSE;
	}
	CWizStdStringArray arrayTagGUID;
	std::vector<WIZDOCUMENTPARAMDATA> arrayParam;
	CComPtr<IStream> spDataStream;
	//
	BOOL bSkipped;
	//
	WIZDOCUMENTDATAEX& operator = (const WIZDOCUMENTDATAEX& right)
	{
		WIZDOCUMENTDATA::operator = (right);
		//
		arrayTagGUID.assign(right.arrayTagGUID.begin(), right.arrayTagGUID.end());
		arrayParam.assign(right.arrayParam.begin(), right.arrayParam.end());
		spDataStream = right.spDataStream;
		//
		bSkipped = right.bSkipped;
		//
		return *this;
	}
	//
	BOOL ParamArrayToStringArray(CWizStdStringArray& params) const
	{
		for (std::vector<WIZDOCUMENTPARAMDATA>::const_iterator it = arrayParam.begin(); 
			it != arrayParam.end();
			it++)
		{
			params.push_back(it->strName + _T("=") + it->strValue);
		}
		//
		return TRUE;
	}
	//
	CComVariant ParamArrayToVariant() const
	{
		CWizStdStringArray params;
		ParamArrayToStringArray(params);
		CComVariant v;
		WizStringArrayToVariant(params, v);
		return v;
	}
	CComVariant TagGUIDArrayToVariant() const
	{
		CComVariant v;
		WizStringArrayToVariant(arrayTagGUID, v);
		return v;
	}
};

struct WIZDOCUMENTATTACHMENTDATAEX : public WIZDOCUMENTATTACHMENTDATA
{
	WIZDOCUMENTATTACHMENTDATAEX()
	{
		bSkipped = FALSE;
	}
	WIZDOCUMENTATTACHMENTDATAEX(const WIZDOCUMENTATTACHMENTDATA& data)
		:WIZDOCUMENTATTACHMENTDATA(data)
	{
		bSkipped = FALSE;
	}
	WIZDOCUMENTATTACHMENTDATAEX& operator = (const WIZDOCUMENTATTACHMENTDATAEX& right)
	{
		WIZDOCUMENTATTACHMENTDATA::operator = (right);
		//
		spDataStream = right.spDataStream;
		//
		bSkipped = right.bSkipped;
		//
		return *this;
	}
	//
	CComPtr<IStream> spDataStream;
	//
	BOOL bSkipped;
};


#pragma pack()


typedef std::vector<WIZTAGDATA> CWizTagDataArray;
typedef std::vector<WIZSTYLEDATA> CWizStyleDataArray;
typedef std::vector<WIZDOCUMENTDATAEX> CWizDocumentDataArray;
typedef std::vector<WIZDOCUMENTPARAMDATA> CWizDocumentParamDataArray;
typedef std::vector<WIZDELETEDGUIDDATA> CWizDeletedGUIDDataArray;
typedef std::vector<WIZDOCUMENTATTACHMENTDATAEX> CWizDocumentAttachmentDataArray;
typedef std::vector<WIZMETADATA> CWizMetaDataArray;




struct WIZTODODATAEX : public WIZTODODATA
{
	typedef std::vector<WIZTODODATAEX> CWizTodoDataExArray;
	//
	CWizTodoDataExArray arrayChild;
	//
	WIZTODODATAEX()
	{
		
	}
	WIZTODODATAEX(const WIZTODODATA& data)
		: WIZTODODATA(data)
	{
		
	}
public:
	intptr_t AddChild(const WIZTODODATAEX& data)
	{
		arrayChild.push_back(data);
		return arrayChild.size() - 1;
	}

	static BOOL WizTodoDataArrayFindLinkedDocument(const CWizTodoDataExArray& arrayData, LPCTSTR lpszDocumentGUID)
	{
		for (CWizTodoDataExArray::const_iterator it = arrayData.begin();
			it != arrayData.end();
			it++)
		{
			if (-1 != WizFindInArrayNoCase(it->arrayLinkedDocumentGUID, lpszDocumentGUID))
				return TRUE;
			//
			if (WizTodoDataArrayFindLinkedDocument(it->arrayChild, lpszDocumentGUID))
				return TRUE;
		}
		//
		return FALSE;
	}
	static intptr_t WizTodoDataArrayFindText(const CWizTodoDataExArray& arrayData, LPCTSTR lpszText)
	{
		for (CWizTodoDataExArray::const_iterator it = arrayData.begin();
			it != arrayData.end();
			it++)
		{
			if (0 == it->strText.CompareNoCase(lpszText))
				return it - arrayData.begin();
		}
		//
		return -1;
	}
	static BOOL WizTodoDataItemCopyAndCombine(WIZTODODATAEX& itemDest, const WIZTODODATAEX& itemOther)
	{
		BOOL bCombined = FALSE;
		//
		if (itemDest.eState < itemOther.eState)
		{
			itemDest.eState = itemOther.eState;
			bCombined = TRUE;
		}
		if (itemDest.tCompleted < itemOther.tCompleted)
		{
			itemDest.tCompleted = itemOther.tCompleted;
			bCombined = TRUE;
		}
		if (itemDest.tModified < itemOther.tModified)
		{
			itemDest.tModified = itemOther.tModified;
			bCombined = TRUE;
		}
		if (itemDest.tCreated < itemOther.tCreated)
		{
			itemDest.tCreated = itemOther.tCreated;
			bCombined = TRUE;
		}
		if (itemDest.arrayLinkedDocumentGUID != itemOther.arrayLinkedDocumentGUID)
		{
			itemDest.arrayLinkedDocumentGUID.insert(itemDest.arrayLinkedDocumentGUID.begin(), itemOther.arrayLinkedDocumentGUID.begin(), itemOther.arrayLinkedDocumentGUID.end());
			::WizStringArrayRemoveMultiElement(itemDest.arrayLinkedDocumentGUID);
			bCombined = TRUE;
		}
		//
		if (WizTodoDataArrayCombine(itemDest.arrayChild, itemOther.arrayChild))
		{
			bCombined = TRUE;
		}
		//
		return bCombined;
	}
	static BOOL WizTodoDataArrayCombine(WIZTODODATAEX::CWizTodoDataExArray& arrayDest, const WIZTODODATAEX::CWizTodoDataExArray& arrayOther)
	{
		BOOL bCombined = FALSE;
		//
		for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = arrayOther.begin();
			it != arrayOther.end();
			it++)
		{
			intptr_t nIndex = WIZTODODATAEX::WizTodoDataArrayFindText(arrayDest, it->strText);
			//
			if (-1 == nIndex)
			{
				arrayDest.push_back(*it);
				bCombined = TRUE;
			}
			else
			{
				WIZTODODATAEX& itemDest = arrayDest[nIndex];
				const WIZTODODATAEX& itemOther = *it;
				//
				if (WizTodoDataItemCopyAndCombine(itemDest, itemOther))
				{
					bCombined = TRUE;
				}
			}
		}
		//
		return bCombined;
	}
	//
	static BOOL WizTodoDataArrayRemoveMultiItem(WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		BOOL bCombined = FALSE;
		//
		std::vector<int> arrayMultiIndex;
		//
		std::map<CString, int> mapTextAndIndex;
		for (WIZTODODATAEX::CWizTodoDataExArray::iterator it = arrayData.begin();
			it != arrayData.end();
			it++)
		{
			WIZTODODATAEX& dataCurr = *it;
			int nIndex = (int)(it - arrayData.begin());
			//
			CString strText = it->strText;
			strText.MakeLower();
			//
			std::map<CString, int>::const_iterator itMap = mapTextAndIndex.find(strText);
			if (itMap == mapTextAndIndex.end())
			{
				mapTextAndIndex[strText] = nIndex;
				//
				if (!dataCurr.arrayChild.empty())
				{
					bCombined = WizTodoDataArrayRemoveMultiItem(dataCurr.arrayChild);
				}
			}
			else
			{
				WIZTODODATAEX& dataDest = arrayData[itMap->second];
				WIZTODODATAEX::WizTodoDataItemCopyAndCombine(dataDest, dataCurr);
				//
				arrayMultiIndex.push_back(nIndex);
				//
				bCombined = TRUE;
			}
		}
		//
		if (arrayMultiIndex.empty())
			return bCombined;
		//
		size_t nMultiIndexCount = arrayMultiIndex.size();
		for (intptr_t i = nMultiIndexCount - 1; i >= 0; i--)
		{
			int nIndex = arrayMultiIndex[i];
			//
			arrayData.erase(arrayData.begin() + nIndex);
		}
		//
		return TRUE;
	}
};


const COLORREF WIZ_TODO_TEXT_COLOR_DEFAULT = RGB(0, 0, 0);
const COLORREF WIZ_TODO_TEXT_COLOR_DEFAULT_COMPLETED = RGB(0x66, 0x66, 0x66);

const COLORREF WIZ_TODO_TEXT_COLOR_URGENT_COMPLATED = RGB(0xFF, 0x64, 0x64);
const COLORREF WIZ_TODO_TEXT_COLOR_URGENTANDIMPORTANT_COMPLETED = RGB(0xFF, 0x64, 0x64);

const COLORREF WIZ_TODO_TEXT_COLOR_URGENT = RGB(255, 0, 0);
const COLORREF WIZ_TODO_TEXT_COLOR_URGENTANDIMPORTANTR = RGB(255, 0, 0);

const COLORREF WIZ_TODO_TEXT_COLOR_NOTURGENTANDNOTIMPORTANT = RGB(128, 128, 128);



inline COLORREF WizTodoGetTextColor(const WIZTODODATA& data)
{
	COLORREF cr = WIZ_TODO_TEXT_COLOR_DEFAULT;
	//
	if (todoState100 == data.eState)
	{
		cr = WIZ_TODO_TEXT_COLOR_DEFAULT_COMPLETED;
		switch (data.ePrior)
		{
		case todoPriorUrgent:
			cr = WIZ_TODO_TEXT_COLOR_URGENT_COMPLATED;
			break;
		case todoPriorUrgentAndImportant:
			cr = WIZ_TODO_TEXT_COLOR_URGENTANDIMPORTANT_COMPLETED;
			break;
		}
	}
	else
	{
		switch (data.ePrior)
		{
		case todoPriorUrgent:
			cr = WIZ_TODO_TEXT_COLOR_URGENT;
			break;
		case todoPriorUrgentAndImportant:
			cr = WIZ_TODO_TEXT_COLOR_URGENTANDIMPORTANTR;
			break;
		case todoPriorNotUrgentAndNotImportant:
			cr = WIZ_TODO_TEXT_COLOR_NOTURGENTANDNOTIMPORTANT;
			break;
		}
	}
	//
	return cr;
}


#define WIZTODODATE_DOCUMENT_PARAM_NAME										_T("todolist_date")
#define WIZTODODATE_DOCUMENT_PARAM_NAME_COLLECTED_UNCOMPLETED_TASKS			_T("todolist_date_cut")
#define WIZTODODATE_DOCUMENT_PARAM_NAME_REMOVED_UNCOMPLETED_TASKS			_T("todolist_date_rut")





#endif