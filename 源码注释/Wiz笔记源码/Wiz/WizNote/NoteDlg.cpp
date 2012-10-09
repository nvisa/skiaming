#include "StdAfx.h"
#include "NoteDlg.h"
#include "MainDlg.h"



#define TIMER_ID_SAVE		101

CNoteDlg::CNoteDlg(CWizKMDatabase* pDatabase, LPCTSTR lpszInitTitle)
	: m_pDatabase(pDatabase)
	, m_strInitTitle(lpszInitTitle)
{
	ATLASSERT(m_pDatabase);
	//
	m_crBackground = WizHTMLStringColorToColor(WizKMGetPrivateString(_T("Note"), _T("DefaultBackgroundColor"), WizHTMLColorToStringColor(m_crBackground)));
	//
	m_nMenuID = IDR_MENU_NOTE;
}

CNoteDlg::~CNoteDlg()
{
}

LRESULT CNoteDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	//
	m_btnNew.Create(m_hWnd, NULL, NULL, 0, 0, IDC_BUTTON_NEW);
	m_editText.Create(m_hWnd, NULL, NULL, ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_CHILD | WS_VISIBLE, 0, IDC_EDIT_TEXT);
	//
	WizTranslationsTranslateWindow(m_hWnd);
	//
	InitClient();
	//
	UpdateLayout();
	SetColor(m_crBackground);
	//
	m_btnNew.SetIcon(IDI_ICON_NEW_BUTTON);
	m_btnMenu.SetIcon(IDI_ICON_MENU_BUTTON);
	m_btnClose.SetIcon(IDI_ICON_CLOSE_BUTTON);
	//
	UpdateLockButtonIcon();
	//
	RandomPosition();
	//
	ModifyStyle(0, WS_MAXIMIZEBOX, 0);
	ModifyStyleEx(0, WS_EX_LAYERED, 0);
	SetTransparentPercent(m_nTransparentPercent);
	//
	RegisterDragDrop(m_hWnd, this);
	//
	SetTimer(TIMER_ID_SAVE, 1000 * 30, NULL);
	//
	UpdateFont();
	//
	//
	return 1;  // Let the system set the focus
}


CRect CNoteDlg::GetTitleRect()
{
	CRect rcNew;
	if (m_btnNew.IsWindow())
	{
		m_btnNew.GetWindowRect(&rcNew);
		ScreenToClient(&rcNew);
	}
	CRect rcMenu;
	if (m_btnMenu.IsWindow())
	{
		m_btnMenu.GetWindowRect(&rcMenu);
		ScreenToClient(&rcMenu);
	}
	//
	CRect rcTitle(rcNew.right + 8, rcNew.top, rcMenu.left - 8, rcMenu.bottom);
	return rcTitle;
}

CString CNoteDlg::GetTitle()
{
	if (m_spDocument)
	{
		return CWizKMDatabase::GetDocumentTitle(m_spDocument);
	}
	else
	{
		if (m_strInitTitle.IsEmpty())
		{
			return WizFormatString0(IDS_UNTITLED);
		}
		else
		{
			return m_strInitTitle;
		}
	}
}


void CNoteDlg::SetColor(COLORREF cr)
{
	CWizNoteSmallDlgBase::SetColor(cr);
	//
	m_editText.SetBackgroundColor(cr);
	//
	COLORREF crTitle = GetTitleBackgroundColor();
	//
	m_btnNew.SetBackgroundColor(crTitle);
}


LRESULT CNoteDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch ((UINT)wParam)
	{
	case TIMER_ID_SAVE:
		AutoSave();
		break;
	}
	//
	return 0;
}

void CNoteDlg::InitClient()
{
	CWizNoteSmallDlgBase::InitClient();
	//
	m_wndContainer.SetClient(m_editText);
	//
	UpdateLayout();
}


void CNoteDlg::UpdateLayout()
{
	CWizNoteSmallDlgBase::UpdateLayout();
	//
	CRect rc;
	GetClientRect(&rc);
	//
	CRect rcNew = CRect(8, 5, 26, 23);
	//
	if (m_btnNew.IsWindow())
	{
		m_btnNew.SetWindowPos(NULL, rcNew, SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CNoteDlg::Close()
{
	CWizNoteSmallDlgBase<CNoteDlg>::Close();
}

CString CNoteDlg::AutoGetTagsText(CString& strText)
{
	CString strTagBeginEnglish = _T("/Tags ");
	CString strTagBeginLocal = WizFormatString0(IDS_TAGS_NAME) + _T(" ");
	//
	CWizStdStringArray arrayText;
	WizSplitTextToArray(strText, '\n', arrayText);
	//
	CString strTagsText;
	//
	//
	for (CWizStdStringArray::iterator it = arrayText.begin();
		it != arrayText.end();
		it++)
	{
		if (0 == _tcsnicmp(strTagBeginEnglish, *it, strTagBeginEnglish.GetLength()))
		{
			strTagsText = it->Right(it->GetLength() - strTagBeginEnglish.GetLength());
			strTagsText.Trim();
		}
		else if (0 == _tcsnicmp(strTagBeginLocal, *it, strTagBeginLocal.GetLength()))
		{
			strTagsText = it->Right(it->GetLength() - strTagBeginLocal.GetLength());
			strTagsText.Trim();
		}
		//
		if (!strTagsText.IsEmpty())
		{
			BOOL bRemoveTagsLine = WizKMGetPrivateBool(_T("Note"), _T("RemoveTagsLine"), FALSE);
			if (bRemoveTagsLine)
			{
				arrayText.erase(it);
				WizStringArrayToText(arrayText, strText, _T("\r\n"));
			}
			//
			return strTagsText;
		}
	}
	return CString();
}


BOOL CNoteDlg::CreateDocument()
{
	if (m_spDocument)
		return TRUE;
	//
	CString strTitle = m_strInitTitle;
	if (strTitle.IsEmpty())
	{
		CString strText;
		m_editText.GetWindowText(strText);
		strTitle = AutoGetTitle(strText);
	}
	//
	CComPtr<IWizFolder> spMonthFolder = WizKMGetMonthFolder(m_pDatabase, FOLDER_MY_NOTES);
	if (!spMonthFolder)
	{
		TOLOG(_T("Failed to create month folder!"));
		return FALSE;
	}
	//
	//
	CComPtr<IDispatch> spNewDocumentDisp;
	HRESULT hr = spMonthFolder->CreateDocument2(CComBSTR(strTitle), CComBSTR(L""), &spNewDocumentDisp);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to create document object"));
		return FALSE;
	}
	//
	m_spDocument = CComQIPtr<IWizDocument>(spNewDocumentDisp);
	ATLASSERT(m_spDocument);
	if (!m_spDocument)
	{
		TOLOG(_T("System error: Failed convert dispatch to IWizDocument"));
		return FALSE;
	}
	//
	m_spDocument->put_Type(CComBSTR(L"note"));
	SetWindowText(CWizKMDatabase::GetDocumentTitle(m_spDocument));
	//
	return TRUE;
}
BOOL CNoteDlg::SaveData()
{
	CWaitCursor wait;
	//
	CString strText;
	m_editText.GetWindowText(strText);
	//
	CString strTagsText = AutoGetTagsText(strText);
	//
	if (!m_spDocument)
	{
		if (!CreateDocument())
		{
			TOLOG(_T("Failed to create document!"));
			return FALSE;
		}
		//
		if (!m_spDocument)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
	}
	else
	{
		m_spDocument->Reload();
	}
	//
	if (!WizConvertTextToHTML_DefaultTemplate(CWizKMDatabase::GetDocumentTitle(m_spDocument), strText))
	{
		TOLOG(_T("Failed to convert text to html!"));
		return FALSE;
	}
	//
	HRESULT hr = m_spDocument->UpdateDocument3(CComBSTR(strText), 0);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to update document!"));
		return FALSE;
	}
	//
	if (!strTagsText.IsEmpty())
	{
		m_spDocument->put_TagsText(CComBSTR(strTagsText));
	}
	//
	//
	m_editText.SetModify(FALSE);
	//
	return TRUE;
}

BOOL CNoteDlg::SavePos()
{
	if (!m_spDocument)
		return FALSE;
	if (!IsWindow())
		return FALSE;
	if (!m_pDatabase)
		return FALSE;
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	CWizKMDocumentParamLine line;
	line.AddInt(_T("l"), rc.left);
	line.AddInt(_T("t"), rc.top);
	line.AddInt(_T("r"), rc.right);
	line.AddInt(_T("b"), rc.bottom);
	//
	return m_pDatabase->SetMeta(_T("NotePos"), CWizKMDatabase::GetObjectGUID(m_spDocument.p), line.GetLine());
}

BOOL CNoteDlg::SaveParam()
{
	if (!m_spDocument)
		return FALSE;
	//
	CWaitCursor wait;
	//
	CWizKMDocumentParamLine line;
	line.AddColor(_T("c"), m_crBackground);
	line.AddInt(_T("ts"), m_nTransparentPercent);
	line.AddBool(_T("v"), IsWindowVisible());
	line.AddInt(_T("lk"), GetDlgState());
	line.AddInt(_T("mh"), m_nNormalHeight);
	//
	CWizKMDatabase::SetDocumentParam(m_spDocument, _T("Note"), line.GetLine());
	//
	m_bInfoModified = FALSE;
	//
	return TRUE;
}
//

BOOL CNoteDlg::AutoSave()
{
	if (!m_spDocument
		&& m_editText.GetWindowTextLength() == 0)
	{
		return TRUE;
	}
	//
	if (m_editText.GetModify())
	{
		if (!SaveData())
		{
			WizErrorMessageBox(IDS_FAILED_TO_SAVE_NOTES);
			return FALSE;
		}
	}
	//
	if (m_bInfoModified)
	{
		if (!SaveParam())
			return FALSE;
	}
	//
	Invalidate();
	//
	return TRUE;
}

//
BOOL CNoteDlg::LoadData()
{
	if (!IsWindow())
		return FALSE;
	//
	if (!m_spDocument)
		return FALSE;
	//
	CString strText;
	if (!CWizKMDatabase::GetDocumentText(m_spDocument, 0, strText))
		return FALSE;
	//
	WizStrToWindows(strText);
	//
	m_editText.SetWindowText(strText);
	//
	SetWindowText(CWizKMDatabase::GetDocumentTitle(m_spDocument));
	//
	m_editText.SetModify(FALSE);
	//
	UpdateUpDownButtons();
	//
	return TRUE;
}
//
BOOL CNoteDlg::LoadPos()
{
	if (!IsWindow())
		return FALSE;
	//
	if (!m_spDocument)
		return FALSE;
	//
	if (!m_pDatabase)
		return FALSE;
	//
	CWizKMDocumentParamLine line(m_pDatabase->GetMeta(_T("NotePos"), CWizKMDatabase::GetObjectGUID(m_spDocument.p)));
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	rc.left = line.GetInt(_T("l"), rc.left);
	rc.top = line.GetInt(_T("t"), rc.top);
	rc.right = line.GetInt(_T("r"), rc.right);
	rc.bottom = line.GetInt(_T("b"), rc.bottom);
	//
	if (rc.right < 0
		|| rc.bottom < 0
		|| rc.left >= ::GetSystemMetrics(SM_CXSCREEN)
		|| rc.top >= ::GetSystemMetrics(SM_CYSCREEN)
		|| rc.Width() < 5
		|| rc.Height() < 5)
	{
		RandomPosition();
		return TRUE;
	}
	//
	SetWindowPos(NULL, rc, SWP_NOZORDER | SWP_NOACTIVATE);
	//
	return TRUE;
}
//
BOOL CNoteDlg::LoadParam()
{
	if (!IsWindow())
		return FALSE;
	//
	if (!m_spDocument)
		return FALSE;
	//
	//
	LoadPos();
	//
	CWizKMDocumentParamLine line;
	CWizKMDatabase::GetDocumentParamLine(m_spDocument, _T("Note"), line);
	//
	COLORREF cr = line.GetColor(_T("c"), m_crBackground);
	int nTransparent = line.GetInt(_T("ts"), m_nTransparentPercent);
	m_nNormalHeight = line.GetInt(_T("mh"), m_nNormalHeight);
	BOOL bVisible = line.GetBool(_T("v"), FALSE);
	int nState = line.GetInt(_T("lk"), FALSE);
	//
	ShowWindow(bVisible ? SW_SHOW : SW_HIDE);
	SetDlgState((WIZSMALLDLGSTATE)nState);
	SetColor(cr);
	SetTransparentPercent(nTransparent);
	//
	m_bInfoModified = FALSE;
	//
	UpdateUpDownButtons();
	//
	Invalidate();
	//
	return TRUE;
}

void CNoteDlg::UpdateLockButtonIcon()
{
	UINT nIcon = IDI_ICON_UNLOCK_BUTTON;
	switch (GetDlgState())
	{
	case stateTopMost:
		nIcon = IDI_ICON_LOCK_BUTTON;
		break;
		/*
	case statePinDesk:
		nIcon = IDI_ICON_PIN_DESK_BUTTON;
		break;
		*/
	};
	//
	m_btnLock.SetIcon(nIcon);
}

CString CNoteDlg::AutoGetTitle(LPCTSTR lpszText)
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
	strTitle.Trim();
	//
	strTitle = WizKMGetDateTitle(COleDateTime::GetCurrentTime(), strTitle);
	//
	return strTitle;
}

BOOL CNoteDlg::Load()
{
	return LoadData()&& LoadParam();
}

BOOL CNoteDlg::SetDocument(IWizDocument* pDocument)
{
	AutoSave();
	//
	CComPtr<IWizDocument> spDocument(pDocument);
	if (spDocument && m_spDocument)
	{
		if (0 == CWizKMDatabase::GetObjectGUID(spDocument.p).CompareNoCase(CWizKMDatabase::GetObjectGUID(m_spDocument.p)))
		{
			COleDateTime tDatabase = CWizKMDatabase::GetDocumentDateModified(spDocument);
			COleDateTime tCurrent = CWizKMDatabase::GetDocumentDateModified(m_spDocument);
			if (tDatabase <= tCurrent)
				return TRUE;
		}
	}
	//
	ATLASSERT(!m_spDocument);
	m_spDocument = pDocument;
	ATLASSERT(m_spDocument);
	//
	return Load();
}


LRESULT CNoteDlg::OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	if (CMainDlg* pMainDlg = WizGetMainDlg())
	{
		pMainDlg->NewNote();
	}
	//
	return 0;
}

LRESULT CNoteDlg::OnNoteDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	if (CMainDlg* pMainDlg = WizGetMainDlg())
	{
		if (m_spDocument)
		{
			if (IDYES != WizMessageBox1(IDS_PROMPT_DELETE_NOTE, GetTitle(), MB_YESNO | MB_ICONQUESTION))
				return 0;
			//
			m_spDocument->Delete();
		}
		//
		pMainDlg->PostMessage(UM_REMOVE_NOTE, 0, (LPARAM)this);
	}

	return 0;
}

BOOL CNoteDlg::GetSelText(CString& strSelText)
{
	int nBegin = 0;
	int nEnd = 0;
	m_editText.GetSel(nBegin, nEnd);
	if (nEnd <= nBegin)
		return FALSE;
	//
	CString strText;
	m_editText.GetWindowText(strText);
	//
	if (strText.GetLength() < nEnd)
		return FALSE;
	//
	strSelText = strText.Mid(nBegin, nEnd - nBegin);
	strSelText.Trim();
	if (strSelText.IsEmpty())
		return FALSE;
	//
	return TRUE;
}


LRESULT CNoteDlg::OnNoteSetselectionastitle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strTitle;
	if (!GetSelText(strTitle))
		return 0;
	//
	if (!m_spDocument)
	{
		if (!AutoSave())
			return 0;
		if (!m_spDocument)
			return 0;
	}
	//
	m_spDocument->put_Title(CComBSTR(strTitle));
	SetWindowText(CWizKMDatabase::GetDocumentTitle(m_spDocument));
	//
	Invalidate();

	return 0;
}

LRESULT CNoteDlg::OnNoteSetselectionastags(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strText;
	if (!GetSelText(strText))
		return 0;
	//
	if (!m_spDocument)
	{
		if (!AutoSave())
			return 0;
		if (!m_spDocument)
			return 0;
	}
	//
	m_spDocument->put_TagsText(CComBSTR(strText));
	//
	return 0;
}

LRESULT CNoteDlg::OnNoteCloseallnotesbutthis(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	if (CMainDlg* pMainDlg = WizGetMainDlg())
	{
		pMainDlg->CloseAllNotes(this);
	}

	return 0;
}

LRESULT CNoteDlg::OnNoteAddtocalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	if (!AutoSave())
		return FALSE;
	//
	if (!m_spDocument)
		return 0;
	//
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return 0;
	//
	CComPtr<IDispatch> spDocumentDisp;
	VARIANT_BOOL vb = VARIANT_FALSE;
	HRESULT hr = spCommonUI->AddDocumentToCalendar(m_spDocument, &vb);
	if (FAILED(hr))
		return 0;
	//
	return 0;
}


STDMETHODIMP CNoteDlg::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	*pdwEffect = 0;
	//
	CWizAtlDataObject obj(pDataObj);
	//
	if (obj.IsFormatAvaliable(CF_TEXT)
		|| obj.IsFormatAvaliable(CF_UNICODETEXT)
		|| obj.IsFormatAvaliable(CF_HTML_FORMAT())
		|| obj.IsFormatAvaliable(CF_RTF_FORMAT())
		)
	{
		*pdwEffect = DROPEFFECT_COPY;
	}
	else
	{
		*pdwEffect = DROPEFFECT_NONE;
	}
	//
	return S_OK;
}

STDMETHODIMP CNoteDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	//
	return S_OK;
}

STDMETHODIMP CNoteDlg::DragLeave( void)
{
	return S_OK;
}

STDMETHODIMP CNoteDlg::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	CWaitCursor wait;
	//
	CWizAtlDataObject obj(pDataObj);
	//
	CString strText;
	//
	if (obj.IsFormatAvaliable(CF_UNICODETEXT)
		|| obj.IsFormatAvaliable(CF_TEXT))
	{
		obj.GetText(strText);
		//
		*pdwEffect = DROPEFFECT_COPY;
	}
	else if (obj.IsFormatAvaliable(CF_HTML_FORMAT()))
	{
		CString strHtml;
		CString strURL;
		if (obj.GetHtml(strHtml, strURL))
		{
			CWizKMToolsDll dll;
			CComBSTR bstrText;
			if (SUCCEEDED(dll.Html2Text(strHtml, 0, &bstrText)) && bstrText)
			{
				strText = bstrText;
			}
		}
		*pdwEffect = DROPEFFECT_COPY;
	}
	else if (obj.IsFormatAvaliable(CF_RTF_FORMAT()))
	{
		CStringA strRTF;
		if (obj.GetRtf(strRTF))
		{
			WizRtf2Text_WizTools(strRTF, strText);
		}
		*pdwEffect = DROPEFFECT_COPY;
	}
	else
	{
		*pdwEffect = DROPEFFECT_NONE;
	}
	//
	if (strText.IsEmpty())
		return S_OK;
	//
	CString strOldText;
	m_editText.GetWindowText(strOldText);
	//
	CString strNewText;
	//
	if (strOldText.IsEmpty())
	{
		strNewText = strText;
	}
	else
	{
		strNewText = strOldText + _T("\n\n") + strText;
	}
	//
	m_editText.SetWindowText(strNewText);
	m_editText.SetModify(TRUE);
	AutoSave();

	//
	return S_OK;
}

BOOL CNoteDlg::IsModified() const 
{
	if (!m_editText.IsWindow())
		return FALSE; 
	return m_editText.GetModify() || m_bInfoModified;
}
COleDateTime CNoteDlg::GetDateModified()
{
	if (m_spDocument)
	{
		DATE dt = 0;
		m_spDocument->get_DataDateModified(&dt);
		return dt;
	}
	//
	return WizGetCurrentTime();
}

LRESULT CNoteDlg::OnNoteFont(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	//
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	CFontHandle font = m_editText.GetFont();
	if (!font.IsNull())
	{
		font.GetLogFont(&lf);
	}
	//
	CFontDialog fd(&lf);
	fd.m_cf.rgbColors = m_editText.GetTextColor();
	if (IDOK != fd.DoModal())
		return 0;
	//
	WizGetMainDlg()->SetNoteFont(lf, fd.GetColor());

	return 0;
}
BOOL CNoteDlg::UpdateFont()
{
	if (!m_editText.IsWindow())
		return FALSE;
	//
	m_editText.SetFont(WizGetMainDlg()->GetNoteFont());
	m_editText.SetTextColor(WizGetMainDlg()->GetNoteTextColor());
	//
	return TRUE;
}
