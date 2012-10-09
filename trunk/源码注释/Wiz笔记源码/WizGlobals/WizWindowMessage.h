#pragma once

#include <vector>
#include <algorithm>
#include "WizMisc.h"

#ifdef __ATLBASE_H__
#include <atlstr.h>
#endif


#define WIZWINDOWMESSAGE_KEY_VALUE_NAME		_T("Data")

class CWizWindowMessageData
{
public:
	CWizWindowMessageData(LPCTSTR lpszMessageName)
	{
		m_strMessageName = lpszMessageName;
		m_bModified = FALSE;
		//
		Load(lpszMessageName);
	}
	virtual ~CWizWindowMessageData()
	{
		if (m_bModified)
		{
			Save(m_strMessageName);
			m_bModified = FALSE;
		}
	}
private:
	std::vector<HWND> m_array;
	BOOL m_bModified;
	CString m_strMessageName;
public:
	const std::vector<HWND>& GetArray() const { return m_array; }
private:
	static CString GetRegKeyBase()
	{
		return CString(_T("Software\\WizBrother\\WizWindowMessage\\"));
	}
	CString GetRegKey(LPCTSTR lpszMessageName)
	{
		return GetRegKeyBase() + lpszMessageName + _T("\\");
	}
	//
public:
	BOOL Load(LPCTSTR lpszMessageName)
	{
		CString strKey = GetRegKey(lpszMessageName);
		//
		BOOL bRet = FALSE;
		HKEY hKey = NULL;

		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, strKey, 0, KEY_READ, &hKey))
		{
			DWORD dwType = REG_BINARY;
			DWORD dwSize = 0;
			if (ERROR_SUCCESS == RegQueryValueEx(hKey, WIZWINDOWMESSAGE_KEY_VALUE_NAME, 0, &dwType, NULL, &dwSize))
			{
				size_t nCount = dwSize / sizeof(HWND);
				//
				HWND* pData = new HWND[nCount];
				if (pData)
				{
					dwSize = DWORD(nCount * sizeof(HWND));
					if (ERROR_SUCCESS == RegQueryValueEx(hKey, WIZWINDOWMESSAGE_KEY_VALUE_NAME, 0, &dwType, (BYTE *)pData, &dwSize))
					{
						for (size_t i = 0; i < nCount; i++)
						{
							if (IsWindow(pData[i]))
							{
								m_array.push_back(pData[i]);
							}
							else
							{
								m_bModified = TRUE;
							}
						}
						//
						bRet = TRUE;
					}
					delete [] pData;
				}
			}
			RegCloseKey(hKey);
		}
		return bRet;
	}
	BOOL Save(LPCTSTR lpszMessageName)
	{
		BOOL bRet = FALSE;
		//
		size_t nCount = m_array.size();
		HWND* pData = new HWND[nCount];
		if (pData)
		{
			for (size_t i = 0; i < nCount; i++)
			{
				pData[i] = m_array[i];
			}
			CString strKey = GetRegKey(lpszMessageName);
			bRet = WizRegWriteBin(HKEY_CURRENT_USER, strKey, WIZWINDOWMESSAGE_KEY_VALUE_NAME, (BYTE*)pData, DWORD(nCount * sizeof(HWND)));
			//
			delete [] pData;
		}
		//
		return bRet;
	}

	//
	void Add(HWND hWnd)
	{
		m_bModified = TRUE;
		//
		size_t nCount = m_array.size();
		for (size_t i = 0; i < nCount; i++)
		{
			if (!m_array[i])
			{
				m_array[i] = hWnd;
				return;
			}
		}
		//
		m_array.push_back(hWnd);
	}
	void Remove(HWND hWnd)
	{
		size_t nCount = m_array.size();
		for (size_t i = 0; i < nCount; i++)
		{
			if (m_array[i] == hWnd)
			{
				m_array[i] = NULL;
				m_bModified = TRUE;
				return;
			}
		}
	}
};

class CWizWindowMessage
{
public:
	CWizWindowMessage(LPCTSTR lpszMessageName)
	{
		m_strMessageName = lpszMessageName;
		m_nMessage = RegisterWindowMessage(lpszMessageName);
		//
		InitRandom();
	}
	CWizWindowMessage(LPCTSTR lpszMessageName, UINT nMessage)
	{
		m_strMessageName = lpszMessageName;
		m_nMessage = nMessage;
		//
		InitRandom();
	}
	virtual ~CWizWindowMessage(void)
	{
	}
protected:
	CString m_strMessageName;
	UINT m_nMessage;
private:
	void InitRandom()
	{
		static bool bFirst = true;
		if (bFirst)
		{
			srand((unsigned)time(NULL) * GetTickCount());
			bFirst = false;
		}
	}
public:
	UINT GetMessage() const
	{
		return m_nMessage;
	}
	BOOL RegisterReceiver(HWND hWnd)
	{
		CWizWindowMessageData data(m_strMessageName);
		data.Add(hWnd);
		//
		return TRUE;
	}
	BOOL UnregisterReceiver(HWND hWnd)
	{
		CWizWindowMessageData data(m_strMessageName);
		data.Remove(hWnd);
		//
		return TRUE;
	}
	//
protected:
	virtual BOOL Post(WPARAM wParam, LPARAM lParam)
	{
		CWizWindowMessageData data(m_strMessageName);
		//
		const std::vector<HWND>& arrayData = data.GetArray();
		//
		intptr_t nCount = arrayData.size();
		for (intptr_t i = 0; i < nCount; i++)
		{
			PostMessage(arrayData[i], m_nMessage, wParam, lParam);
		}
		return TRUE;
	}
	virtual BOOL Send(WPARAM wParam, LPARAM lParam)
	{
		CWizWindowMessageData data(m_strMessageName);
		//
		const std::vector<HWND>& arrayData = data.GetArray();
		//
		intptr_t nCount = arrayData.size();
		for (intptr_t i = 0; i < nCount; i++)
		{
			SendMessage(arrayData[i], m_nMessage, wParam, lParam);
		}
		return TRUE;
	}
};
