// Implementation of the CWizNotifyIconData class and the CWizTrayIconImpl template.
#pragma once


// Wrapper class for the Win32 NOTIFYICONDATA structure
class CWizNotifyIconData : public NOTIFYICONDATA
{
public:	
	CWizNotifyIconData()
	{
		memset(this, 0, sizeof(NOTIFYICONDATA));
		cbSize = sizeof(NOTIFYICONDATA);
	}
};

// Template used to support adding an icon to the taskbar.
// This class will maintain a taskbar icon and associated context menu.
template <class T>
class CWizTrayIconImpl
{
protected:
	UINT WM_TRAYICON;
	UINT WM_TASKBARCREATED;
	CWizNotifyIconData m_nid;
	bool m_bInstalled;
	UINT m_nDefault;
	HWND m_hMainWnd;
public:	
	CWizTrayIconImpl() 
		: m_bInstalled(false)
		, m_nDefault(0)
		, m_hMainWnd(NULL)
	{
		WM_TRAYICON = ::RegisterWindowMessage(_T("WM_TRAYICON"));
		WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
	}
	
	~CWizTrayIconImpl()
	{
		// Remove the icon
		RemoveIcon();
	}

	// Install a taskbar icon
	// 	lpszToolTip 	- The tooltip to display
	//	hIcon 		- The icon to display
	// 	nID		- The resource ID of the context menu
	/// returns true on success
	bool InstallIcon(LPCTSTR lpszToolTip, HICON hIcon, UINT nID)
	{
		T* pT = static_cast<T*>(this);
		// Fill in the data		
		m_nid.hWnd = pT->m_hWnd;
		m_nid.uID = nID;
		m_nid.hIcon = hIcon;
		m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_nid.uCallbackMessage = WM_TRAYICON;
		_tcscpy_s(m_nid.szTip, 128, lpszToolTip);
		// Install
		m_bInstalled = Shell_NotifyIcon(NIM_ADD, &m_nid) ? true : false;
		// Done
		return m_bInstalled;
	}
	//
	bool ShowBalloon(LPCTSTR lpszTitle, LPCTSTR lpszInfo, UINT nTimeOut)
	{
		if (!m_bInstalled)
			return FALSE;
		//
		UINT nOldFlags = m_nid.uFlags;
		//
		m_nid.uFlags &= ~NIF_MESSAGE;
		m_nid.uFlags |= NIF_INFO;
		//
		_tcscpy_s(m_nid.szInfoTitle, 64, lpszTitle);
		_tcscpy_s(m_nid.szInfo, 256, lpszInfo);
		m_nid.dwInfoFlags = NIIF_INFO;
		m_nid.uTimeout = nTimeOut;
		//
		bool bRet = Shell_NotifyIcon(NIM_MODIFY, &m_nid) ? true : false;
		//
		m_nid.uFlags &= ~NIF_INFO;
		//
		return bRet;
	}

	// Remove taskbar icon
	// returns true on success
	bool RemoveIcon()
	{
		if (!m_bInstalled)
			return false;
		// Remove
		m_nid.uFlags = 0;
		m_bInstalled = false;
		return Shell_NotifyIcon(NIM_DELETE, &m_nid) ? true : false;
	}

	// Set the icon tooltip text
	// returns true on success
	bool SetTooltipText(LPCTSTR pszTooltipText)
	{
		if (pszTooltipText == NULL)
			return FALSE;
		// Fill the structure
		m_nid.uFlags = NIF_TIP;
		_tcscpy(m_nid.szTip, pszTooltipText);
		// Set
		return Shell_NotifyIcon(NIM_MODIFY, &m_nid) ? true : false;
	}

	// Set the default menu item ID
	inline void SetDefaultItem(UINT nID) { m_nDefault = nID; }

	BEGIN_MSG_MAP(CWizTrayIcon)
		MESSAGE_HANDLER(WM_TRAYICON, OnTrayIcon)
		MESSAGE_HANDLER(WM_TASKBARCREATED, OnTaskbarCreated)
	END_MSG_MAP()

	void PopupTrayMenu(int x, int y)
	{

		T* pT = static_cast<T*>(this);
		//
		HMENU hMenu = LoadMenu(_AtlBaseModule.GetModuleInstance(), MAKEINTRESOURCE(m_nid.uID));
		if (!hMenu)
			return;
		//
		WizTranslationsTranslateMenu(hMenu);
		// Get the sub-menu
		HMENU hSubMenu = ::GetSubMenu(hMenu, 0);
		if (hSubMenu)
		{
			pT->OnTrayPrepareMenu(hSubMenu);
			// Get the menu position
			POINT pos;
			GetCursorPos(&pos);
			// Make app the foreground
			SetForegroundWindow(pT->m_hWnd);
			// Set the default menu item
			if (m_nDefault == 0)
				SetMenuDefaultItem(hSubMenu, 0, TRUE);
			else
				SetMenuDefaultItem(hSubMenu, m_nDefault, FALSE);
			// Track
			TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, x, y, 0, pT->m_hWnd, NULL);
			// BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
			pT->PostMessage(WM_NULL);
		}
		// Done
		DestroyMenu(hMenu);
	}
	LRESULT OnTrayIcon(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// Is this the ID we want?
		if (wParam != m_nid.uID)
			return 0;
		T* pT = static_cast<T*>(this);
		// Was the right-button clicked?
		if (LOWORD(lParam) == WM_RBUTTONUP)
		{
			// Get the menu position
			POINT pos;
			GetCursorPos(&pos);
			PopupTrayMenu(pos.x, pos.y);
		}
		else if (LOWORD(lParam) == WM_LBUTTONDOWN)
		{
			// Make app the foreground
			pT->OnTrayLButtonDown();
		}
		else if (LOWORD(lParam) == WM_MOUSEMOVE)
		{
			// Make app the foreground
			pT->OnTrayMouseMove();
		}
		else if (LOWORD(lParam) == WM_LBUTTONDBLCLK)
		{
			// Make app the foreground
			SetForegroundWindow(pT->m_hWnd);
			//
			pT->OnTrayLButtonDblclk();
			/*
			// Load the menu
			HMENU hMenu = LoadMenu(_AtlBaseModule.GetModuleInstance(), MAKEINTRESOURCE(m_nid.uID));
			if (hMenu)
			{
				WizTranslationsTranslateMenu(hMenu);
				// Get the sub-menu
				HMENU hSubMenu = ::GetSubMenu(hMenu, 0);
				if (hSubMenu)
				{
					pT->PrepareMenu(hSubMenu);
					// Get the menu position
					POINT pos;
					GetCursorPos(&pos);
					// Set the default menu item
					if (m_nDefault)
					{
						// Send
						pT->SendMessage(WM_COMMAND, m_nDefault, 0);
					}
					else
					{
						UINT nItem = GetMenuItemID(hSubMenu, 0);
						// Send
						pT->SendMessage(WM_COMMAND, nItem, 0);
					}
				}
				// Done
				DestroyMenu(hMenu);
			}
			*/
		}
		else if (UINT(lParam) == NIN_BALLOONTIMEOUT)
		{
			pT->OnBalloonTimeOut();
		}
		else if (UINT(lParam) == NIN_BALLOONUSERCLICK)
		{
			pT->OnBalloonTimeUserClick();
		}
		return 0;
	}
	LRESULT OnTaskbarCreated(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (m_bInstalled)
		{
			m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
			m_bInstalled = Shell_NotifyIcon(NIM_ADD, &m_nid) ? true : false;
		}
		//
		return 0;
	}
	//
	void SetMainWindow(HWND hwnd)
	{
		m_hMainWnd = hwnd;
	}
	void RestoreFromTray()
	{
		if (m_hMainWnd)
		{
			if (GetWindowLong(m_hMainWnd, GWL_STYLE) & WS_VISIBLE)
			{
			}
			else
			{
				::ShowWindow(m_hMainWnd, SW_RESTORE);
				::ShowWindow(m_hMainWnd, SW_SHOW);
			}
			//
			::SetForegroundWindow(m_hMainWnd);
			::BringWindowToTop(m_hMainWnd);
		}
		else
		{
			T* pT = static_cast<T*>(this);
			pT->ShowWindow(SW_SHOW);
			pT->ShowWindow(SW_RESTORE);
		}
	}
	void MinimizeToTray()
	{
		if (m_hMainWnd)
		{
			::ShowWindow(m_hMainWnd, SW_MINIMIZE);
			::ShowWindow(m_hMainWnd, SW_HIDE);
		}
		else
		{
			T* pT = static_cast<T*>(this);
			pT->ShowWindow(SW_MINIMIZE);
			pT->ShowWindow(SW_HIDE);
		}
	}

	// Allow the menu items to be enabled/checked/etc.
	virtual void OnTrayPrepareMenu(HMENU hMenu)
	{
	}
	//
	virtual void OnBalloonTimeOut()
	{
	}
	//
	virtual void OnBalloonTimeUserClick()
	{
	}
	//
	virtual void OnTrayLButtonDblclk()
	{
	}
	virtual void OnTrayLButtonDown()
	{
	}
	virtual void OnTrayMouseMove()
	{
	}
};
