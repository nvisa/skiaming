#pragma once

#include "../WizKMCore/WizKMCore_i.h"
#include "../WizKMControls/WizKMControls_i.h"
#include <shellapi.h>

inline void WizKMAbout(LPCTSTR lpszModuleName)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->AboutBox(CComBSTR(lpszModuleName));
}

inline void WizKMAbout(UINT nModuleNameID)
{
	WizKMAbout(WizFormatString0(nModuleNameID));
}

#ifdef IDS_MODULE_NAME
inline void WizKMAbout()
{
	WizKMAbout(IDS_MODULE_NAME);
}
#endif


inline void WizKMOptionsDlg(long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->OptionsDlg(nFlags);
}

inline void WizKMOptionsDlg2(IDispatch* pDatabase, long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->OptionsDlg2(pDatabase, nFlags);
}

inline void WizKMBackupDlg(long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->BackupDlg(nFlags);
}


inline void WizKMAccountsManagerDlg(long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->AccountsManagerDlg(nFlags);
}

inline void WizKMAccountSecurityDlg(IWizDatabase* pDatabase, long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->AccountSecurityDlg(pDatabase, nFlags);
}


inline void WizKMInitEncryptionDlg(IWizDatabase* pDatabase, long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->InitEncryptionDlg(pDatabase, nFlags);
}

inline void WizKMImporrtCertDlg(IWizDatabase* pDatabase, long nFlags)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->ImportCertDlg(pDatabase, nFlags);
}

inline BOOL WizKMCanEncrypt(IWizDatabase* pDatabase)
{
	CComBSTR bstrN;
	pDatabase->GetCertN(&bstrN);
	CComBSTR bstre;
	pDatabase->GetCerte(&bstre);
	//
	if (bstrN && bstrN.Length() > 0
		&& bstre && bstre.Length() > 0)
		return TRUE;
	//
	return FALSE;
}

inline BOOL WizKMCanDecrypt(IWizDatabase* pDatabase)
{
	CComBSTR bstrN;
	pDatabase->GetCertN(&bstrN);
	CComBSTR bstre;
	pDatabase->GetCerte(&bstre);
	CComBSTR bstrEncrypted_d;
	pDatabase->GetEncryptedCertd(&bstrEncrypted_d);
	//
	if (bstrN && bstrN.Length() > 0
		&& bstre && bstre.Length() > 0
		&& bstrEncrypted_d && bstrEncrypted_d.Length() > 0)
		return TRUE;
	//
	return FALSE;
}
inline BOOL WizKMInitEncryptionSystemForEncrypt(IWizDatabase* pDatabase, long nFlags, HWND hwnd)
{
	if (WizKMCanEncrypt(pDatabase))
		return TRUE;
	//
	HRESULT hr = pDatabase->InitCertFromServer((__int64)hwnd);
	if (FAILED(hr))
	{
		WizMessageBox(WizTranslationsTranslateString(_T("Can not get cert info from server!")));
		return FALSE;
	}
	//
	//如果获得了公钥////
	if (WizKMCanEncrypt(pDatabase))
		return TRUE;
	//
	WizKMInitEncryptionDlg(pDatabase, nFlags);
	//
	return WizKMCanEncrypt(pDatabase);
}

inline BOOL WizKMInitEncryptionSystemForDecrypt(IWizDatabase* pDatabase, long nFlags, HWND hwnd)
{
	CComBSTR bstrUserName;
	pDatabase->get_UserName(&bstrUserName);
	if (!bstrUserName || bstrUserName.Length() == 0)
	{
		WizKMInitEncryptionSystemForEncrypt(pDatabase, 0, hwnd);
		return 0;
	}
	//
	//是否可以解密////
	if (WizKMCanDecrypt(pDatabase))
		return TRUE;
	//从服务器初始化////
	HRESULT hr = pDatabase->InitCertFromServer((__int64)hwnd);
	if (FAILED(hr))
	{
		WizMessageBox(WizTranslationsTranslateString(_T("Can not get cert info from server!")));
		return FALSE;
	}
	//
	//如果获得了私钥////
	if (WizKMCanDecrypt(pDatabase))
		return TRUE;
	//
	WizKMImporrtCertDlg(pDatabase, nFlags);
	//
	return WizKMCanDecrypt(pDatabase);
}
inline BOOL WizKMGetIntValue(LPCTSTR lpszTitle, LPCTSTR lpszDescription, long nMin, long nMax, long& nValue)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return FALSE;
	//
	VARIANT_BOOL vbOK = VARIANT_FALSE;
	//
	spCommonUI->GetIntValue2(CComBSTR(lpszTitle), CComBSTR(lpszDescription),
		nValue, nMin, nMax, &vbOK, &nValue);
	//
	return vbOK ? TRUE : FALSE;
}
inline BOOL WizKMGetIntValue(UINT nIDTitle, UINT nIDDescription, long nMin, long nMax, long& nValue)
{
	return WizKMGetIntValue(WizFormatString0(nIDTitle), WizFormatString0(nIDDescription),
		nMin, nMax, nValue);
}

inline void WizKMCheckNewVersion(BOOL bPrompt, BOOL bSilent)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	spCommonUI->CheckNewVersion(bPrompt ? VARIANT_TRUE : VARIANT_FALSE, bSilent ? VARIANT_TRUE : VARIANT_FALSE);
}

inline CString WizKMSelectTemplate(LPCTSTR lpszTemplateType)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return CString();
	//
	CComBSTR bstrTemplateFileName;
	if (S_OK != spCommonUI->SelectTemplate(CComBSTR(lpszTemplateType), &bstrTemplateFileName))
		return CString();
	//
	return CString(bstrTemplateFileName);
}

inline BOOL WizKMCreateEvent(IWizDatabase* pDatabase, const COleDateTime& t)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return FALSE;
	//
	CComPtr<IDispatch> spDocumentDisp;
	HRESULT hr = spCommonUI->CreateCalendarEvent(pDatabase, t, &spDocumentDisp);
	if (FAILED(hr))
		return FALSE;
	//
	return TRUE;
}

inline void WizKMReportSyncResult(HWND hwnd, 
								  const CWizStdStringArray& arrayDownloaded, 
								  const CWizStdStringArray& arrayUploaded,
								  const CWizStdStringArray& arraySkipped,
								  const CWizStdStringArray& arrayFailed)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return;
	//
	CComVariant vDownloaded;
	CComVariant vUploaded;
	CComVariant vSkipped;
	CComVariant vFailed;

	WizStringArrayToVariant(arrayDownloaded, vDownloaded);
	WizStringArrayToVariant(arrayUploaded, vUploaded);
	WizStringArrayToVariant(arraySkipped, vSkipped);
	WizStringArrayToVariant(arrayFailed, vFailed);
	//
	spCommonUI->ReportSyncResult(__int64(hwnd), vDownloaded, vUploaded, vSkipped, vFailed);
}

inline BOOL WizKMEnterPasswordDlg(LPCTSTR lpszTitle, LPCTSTR lpszInfo, BOOL bShowRememberPasswordButton, CString& strPassword, BOOL& bRememberPassword)
{
	CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
	if (!spCommonUI)
		return FALSE;
	//
	VARIANT_BOOL vbRememberPassword = bRememberPassword ? VARIANT_TRUE : VARIANT_FALSE;
	CComBSTR bstrPassword;
	//
	if (S_OK != spCommonUI->EnterPasswordDlg(CComBSTR(lpszTitle), CComBSTR(lpszInfo), bShowRememberPasswordButton ? VARIANT_TRUE : VARIANT_FALSE,
		&vbRememberPassword, &bstrPassword))
		return FALSE;
	//
	strPassword = CString(bstrPassword);
	if (strPassword.IsEmpty())
		return FALSE;
	//
	bRememberPassword = vbRememberPassword ? TRUE : FALSE;
	//
	return TRUE;
}

inline BOOL WizKMEnterPasswordDlg(LPCTSTR lpszTitle, LPCTSTR lpszInfo, CString& strPassword, BOOL& bRememberPassword)
{
	return WizKMEnterPasswordDlg(lpszTitle, lpszInfo, TRUE, strPassword, bRememberPassword);
}



inline BOOL WizKMBatchOverwriteDocuments(CWizKMDatabase* pDatabase, const CWizDocumentArray& arrayDocument, BOOL bSaveContentOnly)
{
	CString strDatabasePath = pDatabase->GetDatabasePath();
	//
	UINT nUpdateDocumentFlags = bSaveContentOnly ? wizUpdateDocumentSaveContentOnly : 0;
	UINT nJobFlags = wizWizBatchDownloaderJobExecuteScript;
	//
	CComPtr<IWizBatchDownloader> spDownloader = WizKMCreateBatchDownloader();
	if (!spDownloader)
	{
		TOLOG(_T("Failed to create IWizBatchDownloader!"));
		return FALSE;
	}
	//
	CComBSTR bstrDatabasePath(strDatabasePath);
	//
	for (CWizDocumentArray::const_iterator it = arrayDocument.begin();
		it != arrayDocument.end();
		it++)
	{
		CComPtr<IWizDocument> spDocument = *it;
		//
		CString strURL = CWizKMDatabase::GetObjectURL(spDocument.p);
		if (strURL.IsEmpty())
			continue;
		//
		CString strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
		//
		spDownloader->AddJob3(bstrDatabasePath, 
			CComBSTR(CWizKMDatabase::GetObjectGUID(spDocument.p)),
			CComBSTR(strURL),
			CComBSTR(strTitle),
			nUpdateDocumentFlags,
			nJobFlags);
	}
	//
	spDownloader->ShowWindow(VARIANT_TRUE);
	//
	return TRUE;
}

