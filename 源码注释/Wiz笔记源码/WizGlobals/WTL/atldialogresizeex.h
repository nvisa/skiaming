#ifndef __NF_RESIZE_H__
#define __NF_RESIZE_H__

#pragma once

#ifndef __ATLFRAME_H__
#include <altframe.h>
#endif	

#ifndef __ATLMISC_H__
#include <atlmisc.h>
#endif

#ifndef __ATLGDI_H__	
#include <atlgdi.h>
#endif


/////////////////////////////////////////////////////////////////////////////
// Classes in this file
//
// CNoFlickerDialogResize<T>

namespace WTL
{

template <class T>
class CNoFlickerDialogResize : public CDialogResize<T>
{
public:
	typedef CDialogResize<T> baseclass;

	CNoFlickerDialogResize()
	{
	}

	// Message map and handlers
	BEGIN_MSG_MAP(CNoFlickerDialogResize)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		CHAIN_MSG_MAP(baseclass)
	END_MSG_MAP()

	// Operations

	void DlgResize_Init(bool bAddGripper = true, bool bUseMinTrackSize = true, DWORD dwForceStyle = WS_THICKFRAME | WS_CLIPCHILDREN)
	{
		T* pT = static_cast<T*>(this);
		//
		baseclass::DlgResize_Init(bAddGripper,bUseMinTrackSize,dwForceStyle);
		//
		EnumChildWindows(pT->m_hWnd, EnumAllGroupboxSetStyles, 0);
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		baseclass::OnSize(uMsg, wParam, lParam, bHandled);
		//
		EnumChildWindows(pT->m_hWnd, EnumAllGroupboxRepaint, 0);
		//
		return 0;
	}
	static BOOL __stdcall EnumAllGroupboxSetStyles(HWND hwnd, LPARAM lParam)
	{
		CWindow groupboxcontrol(hwnd);
		if(IsGroupBox(groupboxcontrol))
		{
			// Get the extended style for the group box.
			DWORD dwStyleEx = ::GetWindowLong(hwnd, GWL_EXSTYLE);

			// add the WS_EX_TRANSPARENT flag to the group box.
			::SetWindowLong(hwnd, GWL_EXSTYLE, dwStyleEx | WS_EX_TRANSPARENT);

			// apply the style for the window.
			::SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
		return TRUE;
	}
	static BOOL __stdcall EnumAllGroupboxRepaint(HWND hwnd, LPARAM lParam)
	{
		CWindow groupboxcontrol(hwnd);
		if(IsGroupBox(groupboxcontrol))
		{
			groupboxcontrol.Invalidate();
		}
		return TRUE;
	}
	static bool IsGroupBox(CWindow &win)
	{
		long Style = win.GetStyle();

		if((Style & 0xF) == BS_GROUPBOX)
		{
			TCHAR sclass[MAX_PATH];
			GetClassName(win,sclass,MAX_PATH);
			if(_tcscmp(sclass,_T("Button"))==0)
			{
				return true;
			}
		}
		return false;
	}
};

}; //namespace WTL

#endif // __NF_RESIZE_H__