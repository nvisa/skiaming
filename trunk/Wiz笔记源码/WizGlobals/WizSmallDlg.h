#pragma once


const UINT WIZ_WM_UM_CLIENT_SCROLL_CHANGED = ::RegisterWindowMessage(_T("WizClientScrollChanged"));
const UINT WIZ_WM_UM_NOTIFY_PARENT_COMMAND = ::RegisterWindowMessage(_T("WizNotifyParentCommand"));

enum WIZSMALLDLGSTATE
{
	stateNormal = 0,
	stateTopMost = 1,
	//statePinDesk = 2
};
#define WIZSMALLDLGSTATEMAX  stateTopMost



template <class T, class TBase = ATL::CWindow, class TWinTraits = ATL::CControlWinTraits>
class ATL_NO_VTABLE CWizHideScrollBarContainerImpl 
	: public ATL::CWindowImpl< T, TBase, TWinTraits >
{
protected:
	CWindow m_wndClient;
public:
	DECLARE_WND_CLASS_EX(NULL, 0, -1)

	//
	void UpdateLayout()
	{
		if (!IsWindow())
			return;
		//
		if (!m_wndClient.IsWindow())
			return;
		//
		int nScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL);
		//
		CRect rcClient;
		GetClientRect(rcClient);
		//
		rcClient.right += nScrollBarWidth;
		//
		m_wndClient.SetWindowPos(NULL, rcClient, SWP_NOACTIVATE | SWP_NOZORDER);
		m_wndClient.Invalidate();
	}
	//
	void SetClient(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		//
		m_wndClient = hWnd;
		//
		if (m_wndClient.IsWindow())
		{
			m_wndClient.SetParent(m_hWnd);
			m_wndClient.BringWindowToTop();
			m_wndClient.Invalidate();
		}
		//
		pT->UpdateLayout();
	}
	//
	HWND GetClient() const
	{
		return m_wndClient;
	}
public:

// Message map and handlers
	BEGIN_MSG_MAP(CWizHideScrollBarContainerImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WIZ_WM_UM_CLIENT_SCROLL_CHANGED, OnClientScrollChanged)
		MESSAGE_HANDLER(WIZ_WM_UM_NOTIFY_PARENT_COMMAND, OnNotifyParentCommand)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		//
		pT->UpdateLayout();

		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		pT->UpdateLayout();
		//
		return 0;
	}

	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_wndClient.m_hWnd != NULL)
			m_wndClient.SetFocus();
		return 0;
	}

	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 1;   // no background needed
	}
	//
	LRESULT OnNotifyParentCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (!m_wndClient.IsWindow())
			return 0;
		//
		CWindow parent = GetParent();
		if (parent.IsWindow())
		{
			parent.SendMessage(uMsg, wParam, lParam);
		}
		//
		return 0;
	}
	LRESULT OnClientScrollChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (!m_wndClient.IsWindow())
			return 0;
		//
		CWindow parent = GetParent();
		if (parent.IsWindow())
		{
			parent.SendMessage(uMsg, wParam, lParam);
		}
		//
		return 0;
	}
};


class CWizHideScrollBarContainer 
	: public CWizHideScrollBarContainerImpl<CWizHideScrollBarContainer>
{
public:
	DECLARE_WND_CLASS_EX(_T("CWizHideScrollBarContainer"), 0, -1)
};



#define WIZ_SMALL_DLG_TITLE_HEIGHT		28

#define WIZ_ID_SMALL_DLG_UP_BUTTON		10000
#define WIZ_ID_SMALL_DLG_DOWN_BUTTON	10001
#define WIZ_ID_SMALL_DLG_CLOSE_BUTTON	10002
#define WIZ_ID_SMALL_DLG_MENU_BUTTON	10003
#define WIZ_ID_SMALL_DLG_LOCK_BUTTON	10004

#define WIZ_ID_SMALL_DLG_BUTTON_BASE	10020

typedef CWinTraits<WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_MAXIMIZEBOX, WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_WINDOWEDGE>		CWizSmallDlgWinTraits;


template <class T>
class CWizSmallDlgBase
	: public CWindowImpl<T, CWindow, CWizSmallDlgWinTraits>
	, public CDoubleBufferImpl<T>
{
protected:
	CString m_strTitle;
	//
	COLORREF m_crBackground;
	//
	int m_nSizeFrame;
	UINT m_nTransparentPercent;
	int m_nNormalHeight;
	//
	CFont m_fontTitle;
	//
	BOOL m_bInfoModified;
	//
	CWizHideScrollBarContainer m_wndContainer;
	//
	CWizVistaIconButton m_btnUp;
	CWizVistaIconButton m_btnDown;
	//
	CWizVistaIconButton m_btnLock;
	CWizVistaIconButton m_btnMenu;
	CWizVistaIconButton m_btnClose;
	//
	CMenu m_menu;
	UINT m_nMenuID;
public:
	CWizSmallDlgBase()
	{
		m_crBackground = RGB(0xFD, 0xFD, 0xC3);
		//
		WizCreateUIFont(m_fontTitle, WIZUIFONT_BOLD);
		//
		m_nTransparentPercent = 0;
		m_nNormalHeight = WIZ_SMALL_DLG_TITLE_HEIGHT * 4;
		m_nSizeFrame = GetSystemMetrics(SM_CXSIZEFRAME);
		//
		m_bInfoModified = FALSE;
		//
		m_nMenuID = 0;
	}
	//

	static ATL::CWndClassInfo& GetWndClassInfo()
	{
		static ATL::CWndClassInfo classInfo =
		{

			{ sizeof(WNDCLASSEX), CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, StartWindowProc,
			  0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, _T ("WizSmallDlg"), NULL },
			NULL, NULL, IDC_ARROW, TRUE, 0, _T("")
		};
		//
		classInfo.m_wc .style |= CS_DROPSHADOW;
		//
		return classInfo;
	}
public:
	virtual COLORREF GetTitleBackgroundColor()
	{
		return WizColorSchemesGetDarkBackgroundColor(m_crBackground);
	}
	virtual CString GetTitle()
	{
		return CString(_T("WizSmallDlg"));
	}
	virtual CRect GetTitleRect()
	{
		return CRect();
	}
	virtual void SetColor(COLORREF cr)
	{
		m_crBackground = cr;
		//
		m_btnUp.SetBackgroundColor(cr);
		m_btnDown.SetBackgroundColor(cr);
		//
		COLORREF crTitle = GetTitleBackgroundColor();
		//
		m_btnLock.SetBackgroundColor(crTitle);
		m_btnMenu.SetBackgroundColor(crTitle);
		m_btnClose.SetBackgroundColor(crTitle);
		//
		Invalidate();
		SendMessage(WM_NCPAINT, 0, 0);
		//
		OnInfoModified();
	}
	virtual void SetTransparentPercent(UINT nPercent)
	{
		m_nTransparentPercent = nPercent;
		//
		if (m_nTransparentPercent > 80)
		{
			m_nTransparentPercent = 0;
		}
		//
		if (IsWindow())
		{
			SetLayeredWindowAttributes(m_hWnd, 0, (BYTE)(255 - m_nTransparentPercent / 100.0 * 255), LWA_ALPHA);
		}
		//
		OnInfoModified();
	}
	virtual void InitClient()
	{
		ATLASSERT(IsWindow());
		//
		m_wndContainer.Create(m_hWnd);
		//
		m_btnUp.Create(m_hWnd, NULL, NULL, 0, 0, WIZ_ID_SMALL_DLG_UP_BUTTON);
		m_btnDown.Create(m_hWnd, NULL, NULL, 0, 0, WIZ_ID_SMALL_DLG_DOWN_BUTTON);
		m_btnLock.Create(m_hWnd, NULL, NULL, 0, 0, WIZ_ID_SMALL_DLG_LOCK_BUTTON);
		m_btnMenu.Create(m_hWnd, NULL, NULL, 0, 0, WIZ_ID_SMALL_DLG_MENU_BUTTON);
		m_btnClose.Create(m_hWnd, NULL, NULL, 0, 0, WIZ_ID_SMALL_DLG_CLOSE_BUTTON);
		//
		if (WizGetSystemVersion() >= svWin7
			&& GetShowTaskbarButton())
		{
			ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
		}

	}
	virtual BOOL GetShowTaskbarButton()
	{
		return FALSE;
	}
	virtual void UpdateLayout()
	{
		if (!m_wndContainer.IsWindow())
			return;
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		CRect rcClose = CRect(rcClient.right - 26, 5, rcClient.right - 8, 23);
		//
		CRect rcLock = rcClose;
		rcLock.MoveToX(rcLock.left - rcLock.Width() - 2);
		//
		CRect rcMenu = rcLock;
		rcMenu.MoveToX(rcMenu.left - rcMenu.Width() - 2);
		//
		if (m_btnLock.IsWindow())
		{
			m_btnLock.SetWindowPos(NULL, rcLock, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		if (m_btnMenu.IsWindow())
		{
			m_btnMenu.SetWindowPos(NULL, rcMenu, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		if (m_btnClose.IsWindow())
		{
			m_btnClose.SetWindowPos(NULL, rcClose, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		//
		CRect rcContainer = CRect(5, WIZ_SMALL_DLG_TITLE_HEIGHT + 3, rcClient.right - 5 - 18, rcClient.bottom - 14);
		//
		m_wndContainer.SetWindowPos(NULL, rcContainer, SWP_NOZORDER | SWP_NOACTIVATE);
		//
		CRect rcUp = rcContainer;
		rcUp.left = rcUp.right + 2;
		rcUp.top = rcUp.bottom - 18 * 2;
		rcUp.right = rcUp.left + 18;
		rcUp.bottom = rcUp.top + 18;
		m_btnUp.SetWindowPos(NULL, rcUp, SWP_NOZORDER | SWP_NOACTIVATE);
		//
		CRect rcDown = rcUp;
		rcDown.top = rcDown.bottom;
		rcDown.bottom = rcDown.bottom + 18;
		m_btnDown.SetWindowPos(NULL, rcDown, SWP_NOZORDER | SWP_NOACTIVATE);
		//
		UpdateUpDownButtons();

	}
	virtual void UpdateLockButtonIcon()
	{
	}
	//
	virtual void SetDlgState(WIZSMALLDLGSTATE state)
	{
		if (!IsWindow())
			return;
		//
		if (stateTopMost == state)
		{
			::SetParent(m_hWnd, NULL);
			SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		}
		/*
		else if (statePinDesk == state)
		{
			::SetWindowLong(m_hWnd, GWL_STYLE, (::GetWindowLong(m_hWnd, GWL_STYLE) &~ WS_POPUP) | WS_CHILD);

			HWND hwndProgMan = ::FindWindow(_T("ProgMan"), NULL);
			::ShowWindow(hwndProgMan, SW_SHOW);
			::BringWindowToTop(hwndProgMan);
			WizFlashWindow(hwndProgMan);

			::SetParent(m_hWnd, hwndProgMan);
			//
			HWND hwndNewParent = ::GetParent(m_hWnd);
			ATLASSERT(hwndNewParent == hwndProgMan);
			//
			SetWindowPos(HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			//
			BringWindowToTopEx();
			//
		}
		*/
		else
		{
			::SetParent(m_hWnd, NULL);
			SetWindowPos(HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		}
		//
		UpdateLockButtonIcon();
		//
		OnInfoModified();
	}
	virtual WIZSMALLDLGSTATE GetDlgState() const
	{
		HWND parent =GetAncestor(m_hWnd, GA_PARENT); //::GetParent(m_hWnd); 
		HWND progman = ::FindWindow(_T("Progman"), NULL);
		//if (::GetParent(m_hWnd) == ::FindWindow(_T("Progman"), NULL)) //ProgMan
		/*
		if (parent == progman)
		{
			return statePinDesk;
		}
		else 
		*/
		if (GetExStyle() & WS_EX_TOPMOST)
		{
			return stateTopMost;
		}
		else
		{
			return stateNormal;
		}
	}
	//
	virtual void OnInfoModified()
	{
		m_bInfoModified = TRUE;
	}
	//
	virtual void RandomPosition()
	{
		CRect rcDlg;
		GetWindowRect(&rcDlg);
		//
		if (rcDlg.Width() <= 10)
		{
			rcDlg.right = rcDlg.left + 300;
		}
		if (rcDlg.Height() <= 10)
		{
			rcDlg.bottom = rcDlg.top + 200;
		}
		//
		int width = ::GetSystemMetrics(SM_CXSCREEN);
		int height = ::GetSystemMetrics(SM_CYSCREEN);
		//
		int x = width - rcDlg.Width() - 40;
		int y = height - rcDlg.Height() - 40;
		//
		if (x <= 0 || y <= 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = GetTickCount() * 10 % x;
			y = GetTickCount() * 10 % y;
		}
		//
		rcDlg.MoveToXY(x, y);
		MoveWindow(rcDlg, FALSE);
	}
	//
	virtual void Close()
	{
		OnInfoModified();
		//
		ShowWindow(SW_HIDE);
		//
		SavePos();
		//
		AutoSave();
	}
	//
	virtual BOOL SavePos()
	{
		return FALSE;
	}
	virtual BOOL LoadPos()
	{
		return FALSE;
	}
	//

	virtual void BringWindowToTopEx()
	{
		CRect rcWindow;
		GetWindowRect(&rcWindow);
		//
		CRect rcOldWindow = rcWindow;
		//
		if (rcWindow.Width() < 20)
		{
			rcWindow.right = rcWindow.left + 300;
		}
		if (rcWindow.Height() < 20)
		{
			rcWindow.bottom = rcWindow.top + 200;
		}
		//
		if (rcWindow.right < 0)
		{
			rcWindow.MoveToX(0);
		}
		if (rcWindow.bottom < 0)
		{
			rcWindow.MoveToY(0);
		}
		if (rcWindow.left >= ::GetSystemMetrics(SM_CXSCREEN))
		{
			rcWindow.MoveToX(0);
		}
		if (rcWindow.top >= ::GetSystemMetrics(SM_CYSCREEN))
		{
			rcWindow.MoveToY(0);
		}
		//
		if (rcWindow != rcOldWindow)
		{
			SetWindowPos(NULL, rcWindow, SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW);
		}
		//
		if (!IsWindowVisible())
		{
			ShowWindow(SW_SHOW);
			//
			OnInfoModified();
		}
		//
		BringWindowToTop();
		//
		CWindow wnd = m_wndContainer.GetClient();
		if (wnd.IsWindow())
		{
			wnd.SetFocus();
		}
		//
		AutoSave();

	}
	virtual BOOL IsModified() const
	{
		return m_bInfoModified;
	}

	//
	BEGIN_MSG_MAP(CWizSmallDlgBase)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(WIZ_ID_SMALL_DLG_CLOSE_BUTTON, BN_CLICKED, OnBnClickedButtonClose)
		COMMAND_HANDLER(WIZ_ID_SMALL_DLG_LOCK_BUTTON, BN_CLICKED, OnBnClickedButtonLock)
		COMMAND_HANDLER(WIZ_ID_SMALL_DLG_MENU_BUTTON, BN_CLICKED, OnBnClickedButtonMenu)
		COMMAND_HANDLER(WIZ_ID_SMALL_DLG_UP_BUTTON, BN_CLICKED, OnBnClickedUpButton)
		COMMAND_HANDLER(WIZ_ID_SMALL_DLG_DOWN_BUTTON, BN_CLICKED, OnBnClickedDownButton)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		MESSAGE_HANDLER(WM_NCRBUTTONDOWN, OnNcRButtonDown)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, OnNcLButtonDblClk)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WIZ_WM_UM_CLIENT_SCROLL_CHANGED, OnClientScrollChanged)
		CHAIN_MSG_MAP(CDoubleBufferImpl<T>)
	END_MSG_MAP()
	//
	
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your message handler code here and/or call default
		Close();

		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your message handler code here and/or call default
		UpdateLayout();
		//
		Invalidate();
		//
		return 0;
	}

	//
	LRESULT OnNcLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// TODO: Add your message handler code here and/or call default
		CPoint pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		//
		ScreenToClient(&pt);
		//
		int nCode = NcHitTest(pt);
		if (HTCAPTION != nCode)
			return 0;
		//
		SetMinimize();

		return 0;
	}

	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// TODO: Add your message handler code here and/or call default
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		//
		UINT nCode = (UINT)wParam;
		//
		switch (nCode)
		{
		case HTTOPLEFT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, lParam);
			 return 0;
		case HTTOPRIGHT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, lParam);
			 return 0;
		case HTBOTTOMLEFT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, lParam);
			 return 0;
		case HTBOTTOMRIGHT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, lParam);
			 return 0;
		case HTLEFT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, lParam);
			 return 0;
		case HTTOP:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, lParam);
			 return 0;
		case HTRIGHT:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, lParam);
			 return 0;
		case HTBOTTOM:
			 SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, lParam);
			 return 0;
		case HTCAPTION:
			 SendMessage( WM_SYSCOMMAND, SC_MOVE| HTCAPTION, lParam);
			 return 0;
		}
		//
		return 0;
	}
	//
	
	LRESULT OnNcRButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// TODO: Add your message handler code here and/or call default
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		//
		UINT nCode = (UINT)wParam;
		//
		switch (nCode)
		{
		case HTCAPTION:
			 SendMessage( WM_COMMAND, MAKEWPARAM(WIZ_ID_SMALL_DLG_MENU_BUTTON, 0), 0);
			 return 0;
		}
		//
		return 0;
	}

	void SetMinimize()
	{
		CRect rc;
		GetWindowRect(&rc);
		//
		int nNewHeight = 0;
		if (rc.Height() <= WIZ_SMALL_DLG_TITLE_HEIGHT)
		{
			nNewHeight = m_nNormalHeight;
			if (nNewHeight <= WIZ_SMALL_DLG_TITLE_HEIGHT)
			{
				nNewHeight = WIZ_SMALL_DLG_TITLE_HEIGHT * 4;
			}
		}
		else
		{
			nNewHeight = WIZ_SMALL_DLG_TITLE_HEIGHT;
			m_nNormalHeight = rc.Height();
		}
		//
		rc.bottom = rc.top + nNewHeight;
		//
		SetWindowPos(NULL, rc, SWP_NOZORDER | SWP_NOMOVE);
	}
	//
	int NcHitTest(CPoint pt)
	{
		CRect rc;
		GetClientRect(&rc);
		//
		int x = pt.x;
		int y = pt.y;
		//
		if (x < m_nSizeFrame && y < m_nSizeFrame)
		{
			return HTTOPLEFT;
		}
		else if (x > rc.right - m_nSizeFrame && y < m_nSizeFrame)
		{
			return HTTOPRIGHT;
		}
		else if (x < m_nSizeFrame && y > rc.bottom - m_nSizeFrame)
		{
			return HTBOTTOMLEFT;
		}
		else if (x > rc.right - m_nSizeFrame && y > rc.bottom - m_nSizeFrame)
		{
			return HTBOTTOMRIGHT;
		}
		else if (x < 3)
		{
			return HTLEFT;
		}
		else if (y < 3)
		{
			return HTTOP;
		}
		else if (x > rc.right - 3)
		{
			return HTRIGHT;
		}
		else if (y > rc.bottom - 3)
		{
			return HTBOTTOM;
		}
		else if (GetTitleRect().PtInRect(pt))
		{
			return HTCAPTION;
		}
		//
		return HTCLIENT;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPoint pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		ScreenToClient(&pt);
		//
		return NcHitTest(pt);
	}

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

		// Limit the size of the dialog to some minimum to avoid being able to resize
		// the dialog to a line or a dot.
		lpMMI->ptMinTrackSize.x = 18 * 6;
		lpMMI->ptMinTrackSize.y = WIZ_SMALL_DLG_TITLE_HEIGHT;
		return 0;
	}

	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CDCHandle dc = GetWindowDC();
		if (!dc)
			return 0;
		//
		HBRUSH hOldBrush = dc.SelectStockBrush(NULL_BRUSH);
		//
		CPen pen;
		//pen.CreatePen(PS_SOLID, 1, ::WizColorDarker(m_crBackgroundTitle, 0.8f));
		pen.CreatePen(PS_SOLID, 1, GetTitleBackgroundColor());
		//
		HPEN hOldPen = dc.SelectPen(pen);
		//
		CRect rcWindow;
		GetWindowRect(&rcWindow);
		dc.Rectangle(CRect(0, 0, rcWindow.Width(), rcWindow.Height()));
		//
		dc.SelectPen(hOldPen);
		//
		dc.SelectBrush(hOldBrush);
		//
		ReleaseDC(dc);

		return 0;
	}
	//
	void DoPaint(CDCHandle dc)
	{
		dc.SelectFont(m_fontTitle);
		//
		CRect rc;
		GetClientRect(&rc);
		//
		CRect rcTitle = rc;
		rcTitle.bottom = WIZ_SMALL_DLG_TITLE_HEIGHT;
		CRect rcEdit = rc;
		rcEdit.top = WIZ_SMALL_DLG_TITLE_HEIGHT;
		//
		dc.FillSolidRect(&rcTitle, GetTitleBackgroundColor());
		dc.FillSolidRect(&rcEdit, m_crBackground);
		//
		CString strTitle = GetTitle();
		CRect rcTitleText = GetTitleRect();
		//
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(strTitle, -1, rcTitleText, DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS);
		//
		DrawGripper(dc);
	}
	//
	void DrawGripperDot(CDCHandle dc, POINT pt)
	{
		COLORREF cr1 = WizColorDarker(m_crBackground, 0.90f);
		COLORREF cr2 = WizColorDarker(m_crBackground, 0.80f);
		COLORREF cr3 = WizColorDarker(m_crBackground, 0.70f);
		//
		dc.SetPixelV(pt.x, pt.y + 1, cr1);
		dc.SetPixelV(pt.x + 1, pt.y, cr2);
		dc.SetPixelV(pt.x + 1, pt.y + 1, cr3);
	}

	void DrawGripper(CDCHandle dc)
	{
		CRect rc;
		GetClientRect(&rc);
		//
		if (rc.Height() <= WIZ_SMALL_DLG_TITLE_HEIGHT + 10)
			return;
		//
		int left = rc.right - 11;
		int top = rc.bottom - 11;
		//
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i + j >= 2)
				{
					int x = left + i * 3;
					int y = top + j * 3;
					DrawGripperDot(dc, CPoint(x, y));
				}
			}
		}
	}
	//
	void UpdateUpDownButtons()
	{
		if (!m_wndContainer.IsWindow())
			return;
		//
		CWindow wndClient = m_wndContainer.GetClient();
		if (!wndClient.IsWindow())
			return;
		//
		SCROLLINFO sbi;
		ZeroMemory(&sbi, sizeof(SCROLLINFO));
		sbi.cbSize = sizeof(SCROLLINFO);
		sbi.fMask = SIF_ALL;
		//
		wndClient.GetScrollInfo(SB_VERT, &sbi);
		//
		m_btnUp.EnableWindow(sbi.nMax > 0 && 0 != sbi.nPos);
		m_btnDown.EnableWindow(sbi.nMax > 0 && sbi.nMax >= sbi.nPos + int(sbi.nPage));
		//
		BOOL bVisible = m_btnUp.IsWindowEnabled() || m_btnDown.IsWindowEnabled();
		m_btnUp.ShowWindow(bVisible ? SW_SHOW : SW_HIDE);
		m_btnDown.ShowWindow(bVisible ? SW_SHOW : SW_HIDE);
		//
		CRect rcUp;
		m_btnUp.GetWindowRect(&rcUp);
		ScreenToClient(&rcUp);
		//
		if (bVisible && rcUp.top <= WIZ_SMALL_DLG_TITLE_HEIGHT)
		{
			m_btnUp.ShowWindow(SW_HIDE);
			m_btnDown.ShowWindow(SW_HIDE);
		}
	}
	//
	LRESULT OnClientScrollChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UpdateUpDownButtons();
		//
		return 0;
	}
	LRESULT OnBnClickedUpButton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (!m_wndContainer.IsWindow())
			return 0;
		//
		CWindow wndClient = m_wndContainer.GetClient();
		if (!wndClient.IsWindow())
			return 0;
		//
		wndClient.SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
		//
		return 0;
	}
	LRESULT OnBnClickedDownButton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (!m_wndContainer.IsWindow())
			return 0;
		//
		CWindow wndClient = m_wndContainer.GetClient();
		if (!wndClient.IsWindow())
			return 0;
		//
		wndClient.SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
		//
		return 0;
	}

	LRESULT OnBnClickedButtonClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		//
		Close();

		return 0;
	}

	WIZSMALLDLGSTATE GetNextDlgState(WIZSMALLDLGSTATE state)
	{
		int next = state + 1;
		int nMax = WIZSMALLDLGSTATEMAX + 1;
		int ret = next % nMax;
		return (WIZSMALLDLGSTATE)ret;
	}

	LRESULT OnBnClickedButtonLock(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		SetDlgState(GetNextDlgState(GetDlgState()));
		//
		return 0;
	}
	LRESULT OnBnClickedButtonMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		if (0 == m_nMenuID)
			return 0;
		//
		if (!m_menu.IsMenu())
		{
			if (!m_menu.LoadMenu(m_nMenuID))
				return 0;
			//
			WizTranslationsTranslateMenu(m_menu);
		}
		//
		CMenuHandle subMenu = m_menu.GetSubMenu(0);
		if (subMenu.IsNull())
			return 0;
		//
		CPoint pt;
		if (NULL == hWndCtl)
		{
			GetCursorPos(&pt);
		}
		else
		{
			CRect rc;
			m_btnMenu.GetWindowRect(&rc);
			pt.x = rc.left;
			pt.y = rc.bottom;
		}
		//
		subMenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
		//
		return 0;
	}
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Close();

		return 0;
	}
	LRESULT OnActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		int nActivate = LOWORD(wParam);
		if (nActivate == WA_INACTIVE)
		{
			AutoSave();
		}
		else
		{
			CWindow wnd = m_wndContainer.GetClient();
			if (wnd.IsWindow())
			{
				wnd.SetFocus();
			}
		}
		//
		return 0;
	}
	//
	virtual BOOL AutoSave()
	{
		return TRUE;
	}
	//
	virtual void SetInfoModified(BOOL b)
	{
		m_bInfoModified = b;
	}
};
