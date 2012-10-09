#ifndef _WIZKMTODO_H_
#define _WIZKMTODO_H_

#pragma once


class CWizKMTodoDocument : public CWizXMLDocument
{
public:
	CWizKMTodoDocument()
	{
	}
protected:
	//
	BOOL DataArrayToNodeChild(const WIZTODODATAEX::CWizTodoDataExArray& arrayData, CWizXMLNode& nodeParent)
	{
		for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = arrayData.begin();
			it != arrayData.end();
			it++)
		{
			CWizXMLNode nodeChild;
			if (!nodeParent.AppendChild(_T("WizTodo"), nodeChild))
			{
				TOLOG(_T("Failed to append child node: WizTodo!"));
				return FALSE;
			}
			//
			if (!DataToNode(*it, nodeChild))
			{
				TOLOG(_T("Failed to save todo data to node!"));
				return FALSE;
			}
		}
		//
		return TRUE;
	}
	//

	BOOL DataToNode(const WIZTODODATAEX& data, CWizXMLNode& node)
	{
		node.SetAttributeText(_T("Text"), data.strText);
		node.SetAttributeInt(_T("Complete"), data.eState);
		node.SetAttributeInt(_T("Prior"), data.ePrior);
		node.SetAttributeText(_T("LinkedDocumentGUID"), data.GetLinkedDocumentGUIDString());
		//
		node.SetAttributeText(_T("DateCreated"), WizDateTimeToString(data.tCreated));
		node.SetAttributeText(_T("DateModified"), WizDateTimeToString(data.tModified));
		node.SetAttributeText(_T("DateCompleted"), WizDateTimeToString(data.tCompleted));
		node.SetAttributeInt64(_T("Order"), data.nOrder);
		//
		node.SetAttributeBool(_T("Blank"), data.bBlank);
		//
		return DataArrayToNodeChild(data.arrayChild, node);
	}
	//
	//
	BOOL NodeArrayToDataArray(std::vector<CWizXMLNode>& arrayNode, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		for (std::vector<CWizXMLNode>::iterator it = arrayNode.begin();
			it != arrayNode.end();
			it++)
		{
			WIZTODODATAEX data;
			if (NodeToData(*it, data))
			{
				arrayData.push_back(data);
			}
			else
			{
				TOLOG(_T("Warning: Failed to load todo data from node!"));
			}
		}
		//
		return TRUE;
	}
	//
	BOOL NodeChildToDataArray(CWizXMLNode& nodeParent, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		std::vector<CWizXMLNode> arrayNode;
		if (!nodeParent.GetAllChildNodes(arrayNode))
		{
			TOLOG(_T("Failed to find all WizTodo nodes"));
			return FALSE;
		}
		//
		return NodeArrayToDataArray(arrayNode, arrayData);
	}
	//
	BOOL NodeToData(CWizXMLNode& node, WIZTODODATAEX& data)
	{
		node.GetAttributeText(_T("Text"), data.strText);
		data.eState = (WIZTODOSTATE)node.GetAttributeIntDef(_T("Complete"), todoState0);
		data.ePrior = (WIZTODOPRIOR)node.GetAttributeIntDef(_T("Prior"), todoPriorNormal);
		data.SetLinkedDocumentGUIDString(node.GetAttributeTextDef(_T("LinkedDocumentGUID"), _T("")));
		//
		data.tCreated =  WizStringToDateTime(node.GetAttributeTextDef(_T("DateCreated"), _T("")));
		data.tModified = WizStringToDateTime(node.GetAttributeTextDef(_T("DateModified"), _T("")));
		data.tCompleted = WizStringToDateTime(node.GetAttributeTextDef(_T("DateCompleted"), _T("")));
		node.GetAttributeInt64(_T("Order"), data.nOrder);
		//
		data.bBlank = node.GetAttributeBoolDef(_T("Blank"), FALSE);
		//
		return NodeChildToDataArray(node, data.arrayChild);
	}
public:
	BOOL SetTodoData(const WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		CWizXMLNode nodeRoot;
		if (!GetChildNode(_T("WizTodoList"), nodeRoot))
		{
			TOLOG(_T("Failed to create root node: WizTodoList"));
			return FALSE;
		}
		//
		return DataArrayToNodeChild(arrayData, nodeRoot);
	}
	BOOL GetTodoData(WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		CWizXMLNode nodeRoot;
		if (!FindChildNode(_T("WizTodoList"), nodeRoot))
		{
			TOLOG(_T("Failed to find root node: WizTodoList"));
			return FALSE;
		}
		//
		return NodeChildToDataArray(nodeRoot, arrayData);
	}
};




inline BOOL WizDataArrayToTodoItemCollection(const WIZTODODATAEX::CWizTodoDataExArray& arrayData, IWizTodoItemCollection* pColl);
inline CComPtr<IWizTodoItemCollection> WizDataArrayToTodoItemCollection(const WIZTODODATAEX::CWizTodoDataExArray& arrayData);

inline BOOL WizTodoItemCollectionToDataArray(IWizTodoItemCollection* pColl, WIZTODODATAEX::CWizTodoDataExArray& arrayData);


inline BOOL WizDataToTodoItem(const WIZTODODATAEX& data, IWizTodoItem* pTodo)
{
	pTodo->put_Text(CComBSTR(data.strText));
	pTodo->put_Prior(data.ePrior);
	pTodo->put_Complete(data.eState);
	pTodo->put_LinkedDocumentGUIDs(CComBSTR(data.GetLinkedDocumentGUIDString()));
	pTodo->put_Blank(data.bBlank ? VARIANT_TRUE : VARIANT_FALSE);
	pTodo->put_DateCreated(data.tCreated);
	pTodo->put_DateModified(data.tModified);
	pTodo->put_DateComplete(data.tCompleted);
	pTodo->put_Order(data.nOrder);
	//
	CComPtr<IDispatch> spChildrenDisp;
	pTodo->get_Children(&spChildrenDisp);
	//
	if (!spChildrenDisp)
		return TRUE;
	//
	CComQIPtr<IWizTodoItemCollection> spColl(spChildrenDisp);
	if (!spColl)
		return TRUE;
	//
	return WizDataArrayToTodoItemCollection(data.arrayChild, spColl);
}


inline BOOL WizDataArrayToTodoItemCollection(const WIZTODODATAEX::CWizTodoDataExArray& arrayData, IWizTodoItemCollection* pColl)
{
	if (!pColl)
		return FALSE;
	//
	for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = arrayData.begin();
		it != arrayData.end();
		it++)
	{
		CComPtr<IWizTodoItem> spTodo = WizKMCreateTodoItem();
		if (!spTodo)
			return FALSE;
		//
		if (!WizDataToTodoItem(*it, spTodo))
		{
			TOLOG(_T("Failed to save todo data to IWizTodoItem"));
			return FALSE;
		}
		
		pColl->Add(spTodo);
	}
	return TRUE;
}
inline CComPtr<IWizTodoItemCollection> WizDataArrayToTodoItemCollection(const WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	CComPtr<IWizTodoItemCollection> spColl = WizKMCreateTodoItemCollection();
	if (!spColl)
		return NULL;
	//
	if (!WizDataArrayToTodoItemCollection(arrayData, spColl))
		return NULL;
	//
	return spColl;
}

inline BOOL WizDocumentGetTodoData(IWizDocument* pDocument, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	if (!pDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spCollDisp;
	if (FAILED(pDocument->get_TodoItems(&spCollDisp)))
		return FALSE;
	//
	CComQIPtr<IWizTodoItemCollection> spColl(spCollDisp);
	if (!spColl)
		return TRUE;
	//
	return WizTodoItemCollectionToDataArray(spColl, arrayData);
}
inline BOOL WizDocumentSetTodoData(IWizDocument* pDocument, const WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	if (!pDocument)
		return FALSE;
	//
	CComPtr<IWizTodoItemCollection> spColl = WizDataArrayToTodoItemCollection(arrayData);
	if (!spColl)
		return FALSE;
	//
	return SUCCEEDED(pDocument->put_TodoItems(spColl));
}


inline BOOL WizTodoDataArrayToHtmlText(const WIZTODODATAEX::CWizTodoDataExArray& arrayData, CWizStrBufferAlloc& ba)
{
	ba.Append(_T("<ul>\r\n"));
	//
	for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = arrayData.begin();
		it != arrayData.end();
		it++)
	{
		CString strText = it->strText;
		if (todoState100 == it->eState)
		{
			switch (it->ePrior)
			{
			case todoPriorNotUrgentAndNotImportant:
				strText = CString(_T("<span class=\"pri-1done\">")) + strText + _T("</span>");
				break;
			case todoPriorImportant:
				strText = CString(_T("<span class=\"pri1done\">")) + strText + _T("</span>");
				break;
			case todoPriorUrgent:
				strText = CString(_T("<span class=\"pri2done\">")) + strText + _T("</span>");
				break;
			case todoPriorUrgentAndImportant:
				strText = CString(_T("<span class=\"pri3done\">")) + strText + _T("</span>");
				break;
			default:
				strText = CString(_T("<span class=\"pri0done\">")) + strText + _T("</span>");
				break;
			}
		}
		else
		{
			switch (it->ePrior)
			{
			case todoPriorNotUrgentAndNotImportant:
				strText = CString(_T("<span class=\"pri-1\">")) + strText + _T("</span>");
				break;
			case todoPriorImportant:
				strText = CString(_T("<span class=\"pri1\">")) + strText + _T("</span>");
				break;
			case todoPriorUrgent:
				strText = CString(_T("<span class=\"pri2\">")) + strText + _T("</span>");
				break;
			case todoPriorUrgentAndImportant:
				strText = CString(_T("<span class=\"pri3\">")) + strText + _T("</span>");
				break;
			default:
				strText = CString(_T("<span class=\"pri0\">")) + strText + _T("</span>");
				break;
			}
		}
		//
		CString strImageName = _T("todo_0.gif");
		switch (it->eState)
		{
		case todoState25:
			strImageName = _T("todo_25.gif");
			break;
		case todoState50:
			strImageName = _T("todo_50.gif");
			break;
		case todoState75:
			strImageName = _T("todo_75.gif");
			break;
		case todoState100:
			strImageName = _T("todo_100.gif");
			break;
		case todoStateMixed:
			strImageName = _T("todo_mixed.gif");
			break;
		}
		//
		CString strImageFileName = WizKMGetSkinsPath() + strImageName;
		//
		CString strLine = WizFormatString2(_T("<li><img border=\"0\" src=\"%1\" />%2</li>\r\n"),
			strImageFileName,
			strText);
		//
		ba.Append(strLine);
		//
		WizTodoDataArrayToHtmlText(it->arrayChild, ba);
	}
	//
	ba.Append(_T("</ul>\r\n"));
	//
	return TRUE;
}


inline BOOL WizTodoDataArrayToHtmlText(const WIZTODODATAEX::CWizTodoDataExArray& arrayData, LPCTSTR lpszTitle, LPCTSTR lpszXmlFileName, CString& strText)
{
	strText = WizFormatString2(
		_T("\
<html>\r\n\
<head>\r\n\
<meta http-equiv=content-type content=\"text/html; charset=unicode\">\r\n\
<title>%1</title>\r\n\
<link rel=\"File-List\" type=\"WizTodoList\" href=\"%2\" />\r\n\
</head>\r\n\
<body>\r\n"),
		lpszTitle,
		lpszXmlFileName);
	//
	CString strCSSFileName = WizGetAppPath() + _T("files\\todolist.css");
	CString strCSSText;
	WizLoadUnicodeTextFromFile(strCSSFileName, strCSSText);
	//
	strText += CString(_T("<style type=\"text/css\">\r\n")) + strCSSText + _T("\r\n</style>\r\n");
	//
	strText += CString(_T("<div class=\"todolist\">\r\n"));
	//
	CWizStrBufferAlloc ba;
	WizTodoDataArrayToHtmlText(arrayData, ba);
	//
	strText += ba.GetBuffer();
	//
	strText += _T("</div>\r\n");
	//
	strText += _T("</body>\r\n</html>");
	//
	return TRUE;
}


inline CString WizKMGetTodoTitle(const COleDateTime& t)
{
	return WizKMGetDateTitle(t, ::WizTranslationsTranslateString(_T("Todo List")));
}
inline BOOL WizKMSetDocumentTodoDate(IWizDocument* pDocument, const COleDateTime& t)
{
	CString strDate;
	strDate.Format(_T("%04d-%02d-%02d"), 
		t.GetYear(),
		t.GetMonth(),
		t.GetDay());
	//
	HRESULT hr = pDocument->put_ParamValue(CComBSTR(WIZTODODATE_DOCUMENT_PARAM_NAME), CComBSTR(strDate));
	return SUCCEEDED(hr);
}

inline COleDateTime WizKMGetDocumentTodoDate(IWizDocument* pDocument)
{
	CComBSTR bstrDate;
	pDocument->get_ParamValue(CComBSTR(WIZTODODATE_DOCUMENT_PARAM_NAME), &bstrDate);
	//
	CWizStdStringArray arrayText;
	WizSplitTextToArray(CString(bstrDate), '-', arrayText);
	//
	COleDateTime now = COleDateTime::GetCurrentTime();
	//
	if (arrayText.size() != 3)
		return now;
	//
	int nYear = _ttoi(arrayText[0]);
	int nMonth = _ttoi(arrayText[0]);
	int nDay = _ttoi(arrayText[0]);
	//
	if (nYear <= 1900 || nYear > 2100)
		return now;
	if (nMonth < 1 || nMonth > 12)
		return now;
	if (nDay < 1 || nDay > 31)
		return now;
	//
	try
	{
		COleDateTime t = COleDateTime(nYear, nMonth, nDay, 0, 0, 0);
		return t;
	}
	catch (...)
	{
		return now;
	}
}

inline CComPtr<IWizDocument> WizKMCreateTodoDocument(CWizKMDatabase* pDatabase, const COleDateTime& t, BOOL bInitEmptyData)
{
	CString strTitle = WizKMGetTodoTitle(t);
	//
	CComPtr<IWizFolder> spMonthFolder = WizKMGetMonthFolder(pDatabase, FOLDER_MY_NOTES);
	if (!spMonthFolder)
	{
		TOLOG(_T("Failed to create month folder!"));
		return NULL;
	}
	//
	//
	CComPtr<IDispatch> spNewDocumentDisp;
	HRESULT hr = spMonthFolder->CreateDocument2(CComBSTR(strTitle), CComBSTR(L""), &spNewDocumentDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to create document object"));
		return NULL;
	}
	//
	CComPtr<IWizDocument> spDocument = CComQIPtr<IWizDocument>(spNewDocumentDisp);
	ATLASSERT(spDocument);
	if (!spDocument)
	{
		TOLOG(_T("System error: Failed convert dispatch to IWizDocument"));
		return NULL;
	}
	//
	spDocument->put_Type(CComBSTR(L"todolist"));
	//
	WizKMSetDocumentTodoDate(spDocument, t);
	//
	if (bInitEmptyData)
	{
		spDocument->UpdateDocument3(CComBSTR("<p>&nbsp;</p>"), 0);
	}
	//
	return spDocument;
}

inline BOOL WizKMGetTodoDocument(CWizKMDatabase* pDatabase, const COleDateTime& t, BOOL bCreate, BOOL bInitEmptyData, CComPtr<IWizDocument>& spDocumentRet)
{
	if (!pDatabase)
		return FALSE;
	//
	CComPtr<IDispatch> spDocumentDisp;
	//
	HRESULT hr = pDatabase->GetDatabase()->GetTodoDocument(t, &spDocumentDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to get today todo items!"));
		return FALSE;
	}
	//
	spDocumentRet = CComQIPtr<IWizDocument>(spDocumentDisp);
	//
	if (spDocumentRet)
		return TRUE;
	//
	if (!bCreate)
		return TRUE;
	//
	spDocumentRet = WizKMCreateTodoDocument(pDatabase, t, bInitEmptyData);
	return spDocumentRet ? TRUE : FALSE;
}

inline BOOL WizKMSetEventTodoCompleted(CWizKMDatabase* pDatabase, IWizEvent* pEvent)
{
	if (!pEvent)
		return FALSE;
	//
	CComBSTR bstrGUID;
	pEvent->get_GUID(&bstrGUID);
	CString strGUID(bstrGUID);
	//
	DATE dtStart = 0;
	pEvent->get_Start(&dtStart);
	//
	COleDateTime tStart(dtStart);
	//
	CComPtr<IWizDocument> spDocument;
	if (!WizKMGetTodoDocument(pDatabase, tStart, FALSE, FALSE, spDocument))
	{
		TOLOG(_T("Failed to get todo items!"));
		return FALSE;
	}
	//
	if (!spDocument)
		return FALSE;
	//
	WIZTODODATAEX::CWizTodoDataExArray arrayData;
	if (!WizDocumentGetTodoData(spDocument, arrayData))
		return FALSE;
	//
	for (WIZTODODATAEX::CWizTodoDataExArray::iterator it = arrayData.begin();
		it != arrayData.end();
		it++)
	{
		if (it->eState == todoState100)
			continue;
		//
		if (it->arrayLinkedDocumentGUID.size() != 1)
			continue;
		//
		if (0 != it->arrayLinkedDocumentGUID[0].CompareNoCase(strGUID))
			continue;
		//
		it->eState = todoState100;
		break;
	}
	//
	WizDocumentSetTodoData(spDocument, arrayData);
	//
	return TRUE;
}
inline BOOL WizKMSetEventTodoCompleted(IWizEvent* pEvent)
{
	if (!pEvent)
		return FALSE;
	//
	CComPtr<IDispatch> spDocumentDisp;
	pEvent->get_Document(&spDocumentDisp);
	//
	CComQIPtr<IWizDocument> spDocument(spDocumentDisp);
	if (!spDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spDatabaseDisp;
	spDocument->get_Database(&spDatabaseDisp);
	CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
	if (!spDatabase)
		return FALSE;
	//
	CWizKMDatabase db;
	db.SetDatabase(spDatabase);
	//
	return WizKMSetEventTodoCompleted(&db, pEvent);
}



inline BOOL WizTodoItemToData(IWizTodoItem* pTodo, WIZTODODATAEX& data)
{
	CComBSTR bstrText;
	pTodo->get_Text(&bstrText);
	//
	long nPrior = 0;
	pTodo->get_Prior(&nPrior);

	long nComplete = 0;
	pTodo->get_Complete(&nComplete);
	//
	CComBSTR bstrLinkedDocumentGUID;
	pTodo->get_LinkedDocumentGUIDs(&bstrLinkedDocumentGUID);
	//
	VARIANT_BOOL vbBlank = VARIANT_FALSE;
	pTodo->get_Blank(&vbBlank);
	//
	DATE dtCreated = 0;
	DATE dtModified = 0;
	DATE dtCompleted = 0;
	//
	pTodo->get_DateCreated(&dtCreated);
	pTodo->get_DateModified(&dtModified);
	pTodo->get_DateComplete(&dtCompleted);
	//
	__int64 nOrder = 0;
	pTodo->get_Order(&nOrder);
	//
	data.strText = CString(bstrText);
	data.ePrior = (WIZTODOPRIOR)nPrior;
	data.eState = (WIZTODOSTATE)nComplete;
	data.SetLinkedDocumentGUIDString(CString(bstrLinkedDocumentGUID));
	data.bBlank = vbBlank ? TRUE : FALSE;
	data.tCreated = dtCreated;
	data.tModified = dtModified;
	data.tCompleted = dtCompleted;
	data.nOrder = nOrder;
	//
	//
	CComPtr<IDispatch> spChildrenDisp;
	pTodo->get_Children(&spChildrenDisp);
	//
	if (!spChildrenDisp)
		return TRUE;
	//
	CComQIPtr<IWizTodoItemCollection> spColl(spChildrenDisp);
	if (!spColl)
		return TRUE;
	//
	return WizTodoItemCollectionToDataArray(spColl, data.arrayChild);
}


inline BOOL WizTodoItemCollectionToDataArray(IWizTodoItemCollection* pColl, WIZTODODATAEX::CWizTodoDataExArray& arrayData)
{
	if (!pColl)
		return FALSE;
	//
	long nCount = 0;
	pColl->get_Count(&nCount);
	//
	for (long i = 0; i < nCount; i++)
	{
		CComPtr<IDispatch> spTodoDisp;
		pColl->get_Item(i, &spTodoDisp);
		if (!spTodoDisp)
			return FALSE;
		//
		CComQIPtr<IWizTodoItem> spTodo(spTodoDisp);
		if (!spTodo)
			return FALSE;
		//
		WIZTODODATAEX data;
		if (!WizTodoItemToData(spTodo, data))
			return FALSE;
		//
		arrayData.push_back(data);
	}
	//
	return TRUE;
}

#endif //_WIZKMTODO_H_

