#pragma once

#include "../Globals/WizKMDatabase.h"

class CWizKMDatabaseEx : public CWizKMDatabase
{
public:
	CWizKMDatabaseEx(void)
	{
		m_spDatabase = WizKMCreateDatabase(); 
	}

	~CWizKMDatabaseEx(void)
	{
	}
public:
	BOOL Open(LPCTSTR lpszPath, LPCTSTR lpszPassword, long nFlags, CString& strError)
	{
		if (!m_spDatabase)
		{
			TOLOG1(_T("NULL Pointer, Failed to open database: %1"), lpszPath);
			return FALSE;
		}
		//
		CComBSTR bstrErr;
		HRESULT hr = m_spDatabase->Open2(CComBSTR(lpszPath), CComBSTR(lpszPassword), nFlags, &bstrErr);
		if (FAILED(hr))
		{
			CString strErr(bstrErr);
			TOLOG(strErr);
			TOLOG1(_T("Failed to open database: %1"), lpszPath);
			return FALSE;
		}
		//
		return TRUE;
	}
	BOOL DefaultOpen(LPCTSTR lpszPath)
	{
		CString strErr;
		if (!Open(lpszPath, _T(""), 0, strErr))
		{
			WizMessageBox(strErr);
			TOLOG(strErr);
			return FALSE;
		}
		//
		return TRUE;
	}
	BOOL CoreOpen(LPCTSTR lpszPath)
	{
		CString strErr;
		if (!Open(lpszPath, _T("{5A05DAD5-444A-4381-8D4E-5FE1AFD2271F}"), 0, strErr))
		{
			WizMessageBox(strErr);
			TOLOG(strErr);
			return FALSE;
		}
		//
		return TRUE;
	}
	void Close()
	{
		if (!m_spDatabase)
		{
			TOLOG(_T("NULL Pointer, Failed to close database"));
			return;
		}
		//
		m_spDatabase->Close();
	}
	//
	virtual void SetDatabase(IWizDatabase* pDatabase)
	{
		ATLASSERT(FALSE);
	}
};

