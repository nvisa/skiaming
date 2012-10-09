#ifndef _WIZUIBASE_H_
#define _WIZUIBASE_H_

#pragma once

#ifndef __ATLCOLL_H__
#include <atlcoll.h>
#endif

#ifndef __ATLTYPES_H__
#include <atltypes.h>
#endif

enum WizDrawItemBackgroundState 
{
	wizStateNone = 0, 
	wizStateSelected = 0x01, 
	wizStateHot = 0x02, 
	wizStateFocused = 0x04,
	wizStateControlDropTarget = 0x08,
};

void WizGradientFill(HDC hDC, const RECT& rcItem, COLORREF cr1, COLORREF cr2, BOOL bHor);
void WizDrawItemBackgroundBox(HDC hDC, const RECT& rcItem, COLORREF rgbBackground, COLORREF rgbOuter, COLORREF rgbInner, COLORREF rgbTop, COLORREF rgbBottom);
void WizDrawItemBackground(HWND hWnd, HDC hDC, const RECT& rc, UINT nState, COLORREF crDefaultBackgroundColor);
void WizDrawItemBackground_Button(HDC hDC, const RECT& rcItem, BOOL bHover);
void WizDrawCrystalBackground(HDC hDC, const RECT& rcItem, int nCenterLine, BOOL bHot);
void WizDrawCrystalBackground_Hot(HDC hDC, const RECT& rcItem, int nCenterLine);
void WizDrawCrystalBackground_Pressed(HDC hDC, const RECT& rcItem, int nCenterLine);
void WizDrawLighterGradientLine(HDC hDC, const POINT& ptFrom, const POINT& ptTo);
void WizDrawDarkerGradientLine(HDC hDC, const POINT& ptFrom, const POINT& ptTo);


#define WIZUIFONT_BOLD			0x01
#define WIZUIFONT_ITALIC		0x02
#define WIZUIFONT_UNDERLINE		0x04
#define WIZUIFONT_STRIKEOUT		0x08
#define WIZUIFONT_SMALL			0x10
#define WIZUIFONT_LARGE			0x20

BOOL WizCreateUIFont(CFont& font, UINT nFlags = 0, LPCTSTR lpszFontName = NULL, int nFontHeight = 0);
int WizGetFontHeight(HWND hWnd, HFONT hFont);
int WizGetFontHeight(HWND hWnd);
int WizGetTextWidth(HWND hWnd, LPCTSTR lpszText, HFONT hFont = NULL);

class CWizDCSaver
{
public:
	CWizDCSaver(HDC hDC);
	~CWizDCSaver();
private:
	int m_nSavedDC;
	HDC m_hDC;
};



#ifdef __ATLSPLIT_H__


template <bool t_bVertical = true, class TSettings = CWizEmptySettings>
class CWizVistaSplitterWindowT : 
	public CSplitterWindowImpl<CWizVistaSplitterWindowT<t_bVertical>, t_bVertical>
{
public:
	CWizVistaSplitterWindowT()
		: m_nSmallWindowHeight(100)
	{
	}
	DECLARE_WND_CLASS_EX(_T("Wiz_SplitterWindow"), CS_DBLCLKS, COLOR_BTNFACE)

	typedef CSplitterWindowImpl<CWizVistaSplitterWindowT<t_bVertical>, t_bVertical>   _baseClass;

	// Overrideables
	void DrawSplitterBar(CDCHandle dc)
	{
		RECT rect;

		if ( GetSplitterBarRect ( &rect ) )
		{

			COLORREF rgbTop = RGB(255, 255, 255);
			//
			if (t_bVertical)
			{
				int nWidth = rect.right - rect.left;
				for (int i = 0; i < nWidth; i++)
				{
					double f = 160 + (255.0 - 160) * (i + 1.0) / nWidth;
					int n = int(f);
					COLORREF rgbBottom = RGB(n, n, n);
					//
					//
					GRADIENT_RECT grdRect = { 0, 1 };
					TRIVERTEX triVertextTop[ 2 ] = {
												rect.left + i,
												rect.top,
												GetRValue( rgbTop) << 8,
												GetGValue( rgbTop) << 8,
												GetBValue( rgbTop) << 8,
												0x0000,			
												rect.left + i + 1,
												rect.bottom / 2,
												GetRValue( rgbBottom) << 8,
												GetGValue( rgbBottom) << 8,
												GetBValue( rgbBottom) << 8,
												0x0000
											};
				
					dc.GradientFill( triVertextTop, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
					//
					TRIVERTEX triVertextBottom[ 2 ] = {
												rect.left + i,
												rect.bottom / 2,
												GetRValue( rgbBottom) << 8,
												GetGValue( rgbBottom) << 8,
												GetBValue( rgbBottom) << 8,
												0x0000,			
												rect.left + i + 1,
												rect.bottom,
												GetRValue( rgbTop) << 8,
												GetGValue( rgbTop) << 8,
												GetBValue( rgbTop) << 8,
												0x0000
											};
				
					dc.GradientFill( triVertextBottom, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
				}
			}
			else
			{
				int nHeight = rect.bottom - rect.top;
				for (int i = 0; i < nHeight; i++)
				{
					double f = 160 + (255.0 - 160) * (i + 1.0) / nHeight;
					int n = int(f);
					COLORREF rgbBottom = RGB(n, n, n);
					//
					//
					GRADIENT_RECT grdRect = { 0, 1 };
					TRIVERTEX triVertextLeft[ 2 ] = {
												rect.left,
												rect.top + i,
												GetRValue( rgbTop) << 8,
												GetGValue( rgbTop) << 8,
												GetBValue( rgbTop) << 8,
												0x0000,			
												rect.right / 2,
												rect.top + i + 1,
												GetRValue( rgbBottom) << 8,
												GetGValue( rgbBottom) << 8,
												GetBValue( rgbBottom) << 8,
												0x0000
											};
				
					dc.GradientFill( triVertextLeft, 2, &grdRect, 1, GRADIENT_FILL_RECT_H );
					//
					TRIVERTEX triVertextRight[ 2 ] = {
												rect.right / 2,
												rect.top + i,
												GetRValue( rgbBottom) << 8,
												GetGValue( rgbBottom) << 8,
												GetBValue( rgbBottom) << 8,
												0x0000,			
												rect.right,
												rect.top + i + 1,
												GetRValue( rgbTop) << 8,
												GetGValue( rgbTop) << 8,
												GetBValue( rgbTop) << 8,
												0x0000
											};
				
					dc.GradientFill( triVertextRight, 2, &grdRect, 1, GRADIENT_FILL_RECT_H );
				}
			}
		}
	}

protected:
	CString m_strSection;
	//
	CWindow m_wndSmall;
	int m_nSmallWindowHeight;
public:
	void SetStateSection(LPCTSTR lpszSection)
	{
		m_strSection = lpszSection;
		if (IsWindow())
		{
			TSettings settings;
			int nSpliterPos = settings.GetInt(lpszSection, _T("SplitterPos"), GetSplitterPos());
			SetSplitterPos(nSpliterPos);
		}
	}
	void SetSmallWindow(HWND hwnd, int nHeight)
	{
		m_nSmallWindowHeight = nHeight;
		m_wndSmall.Detach();
		m_wndSmall.Attach(hwnd);
		if (m_wndSmall.IsWindow())
		{
			m_wndSmall.SetParent(m_hWnd);
		}
		//
		UpdateSplitterLayout();
	}
public:
	//
	BEGIN_MSG_MAP(CWizVistaSplitterWindowT)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP(_baseClass)
	END_MSG_MAP()
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		SaveState();
		//
		bHandled = FALSE;
		return 0;
	}
	//
	void SaveState()
	{
		if (!m_strSection.IsEmpty())
		{
			if (SPLIT_PANE_NONE == GetSinglePaneMode())
			{
				TSettings settings;
				settings.SetInt(m_strSection, _T("SplitterPos"), GetSplitterPos());
			}
		}
	}
	BOOL IsShowAD() const
	{
		if (!m_wndSmall.IsWindow())
			return FALSE;
		if (m_wndSmall.GetParent() != m_hWnd)
			return FALSE;
		//
		if (0 == (m_wndSmall.GetStyle() & WS_VISIBLE))
			return FALSE;
		//
		return TRUE;
	}
	
	virtual void GetADRect(LPRECT lpRect) const
	{
		if (IsShowAD())
		{
			_baseClass::GetSplitterPaneRect(SPLIT_PANE_LEFT, lpRect);
			lpRect->top = lpRect->bottom - m_nSmallWindowHeight;
		}
	}
	virtual bool GetSplitterPaneRect(int nPane, LPRECT lpRect) const
	{
		bool bRet = _baseClass::GetSplitterPaneRect(nPane, lpRect);
		//
		if (IsShowAD() && SPLIT_PANE_LEFT == nPane)
		{
			lpRect->bottom -=  m_nSmallWindowHeight;
		}
		//
		return bRet;
	}
	virtual void UpdateSplitterLayout()
	{
		_baseClass::UpdateSplitterLayout();
		//
		if (IsShowAD())
		{
			CRect rcAD;
			GetADRect(&rcAD);
			//
			m_wndSmall.MoveWindow(&rcAD);
		}
	}
};

typedef CWizVistaSplitterWindowT<true, CWizEmptySettings>    CWizVistaSplitterWindow;
typedef CWizVistaSplitterWindowT<false, CWizEmptySettings>   CWizVistaHorSplitterWindow;


#endif //__ATLSPLIT_H__



template <class T>
class CWizVistaListBoxImpl 
	: public ATL::CWindowImpl< T, CListBox, ATL::CControlWinTraits>
	, public COwnerDraw<CWizVistaListBoxImpl<T> >
	, public CDoubleBufferImpl<CWizVistaListBoxImpl<T> >
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CListBox::GetWndClassName())
public:
	CWizVistaListBoxImpl(void)
	{
		WizCreateUIFont(m_font);
		WizCreateUIFont(m_fontBold, WIZUIFONT_BOLD);
		//
		m_bMouseOver = FALSE;
		//
		m_nHoverItem = -1;
		m_nFocusedItem = -1;
	}
public:
	BEGIN_MSG_MAP(CWizVistaListBoxImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CWizVistaListBoxImpl>, 1)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CWizVistaListBoxImpl> )
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
protected:
	CFont m_font;
	CFont m_fontBold;
	//
	int m_nHoverItem;
	BOOL m_bMouseOver;
	int m_nFocusedItem;
	//
	CWizNamedImageList m_il;
	//
	typedef std::map<int, int> CImageIndexMap;
	CImageIndexMap m_mapImageIndex;
public:
	int GetFocusedItemDirect() { return m_nFocusedItem; }
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_MULTIPLESEL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_EXTENDEDSEL | LBS_NOTIFY;
	}
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		DRAWITEMSTRUCT ds = *lpDrawItemStruct;
		CMemoryDC dcMem(lpDrawItemStruct->hDC, lpDrawItemStruct->rcItem);
		ds.hDC = dcMem.m_hDC;
		//
		DrawBackground(&ds);
		DrawText(&ds);
	}
	void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
	{
		DeleteItemData(lpDeleteItemStruct);
	}
public:
	BOOL SubclassWindow(HWND hWnd)
	{
		return ATL::CWindowImpl< T, CListBox, ATL::CControlWinTraits>::SubclassWindow( hWnd ) ? OnInitControl() : FALSE;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		OnInitControl();
		//
		return lRet;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		OnDestroyControl();
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);
		//
		pT->Invalidate();
		//
		return lRet;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);
		//
		pT->Invalidate();
		//
		return lRet;
	}
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		if(!m_bMouseOver)
		{
			m_bMouseOver = TRUE;
			//Invalidate();
			//UpdateWindow();
			StartTrackMouseLeave();
		}
		//
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 

		BOOL bOutside = FALSE;
		int nItem = (UINT)ItemFromPoint(pt, bOutside);
		if (bOutside)
		{
			nItem = -1;
		}
		if (m_nHoverItem != nItem)
		{
			int nOldHoverItem = m_nHoverItem;
			m_nHoverItem = nItem;
			//
			InvalidateItem(nOldHoverItem);
			InvalidateItem(nItem);
		}
		
		//
		bHandled = FALSE;
		return 1;
	}
	void InvalidateItem(int nItem)
	{
		if (-1 == nItem)
			return;
		//
		CRect rcItem;
		GetItemRect(nItem, &rcItem);
		InvalidateRect(&rcItem, FALSE);
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_bMouseOver)
		{
			m_bMouseOver = FALSE;
			//Invalidate();
			//UpdateWindow();
		}
		//
		int nOldHoverItem = m_nHoverItem;
		m_nHoverItem = -1;
		//
		InvalidateItem(nOldHoverItem);
		//UpdateWindow();
		//
		return 0;
	}
	LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		UINT xPos = GET_X_LPARAM(lParam); 
		UINT yPos = GET_Y_LPARAM(lParam); 
		//
		CPoint pt(xPos, yPos);
		ClientToScreen(&pt);
		//
		m_nFocusedItem = GetFocusedItem();
		//
		ShowMenu(xPos, yPos);
		//
		//
		InvalidateItem(m_nFocusedItem);
		UpdateWindow();
		m_nFocusedItem = -1;
		//
		return 0;
	}
	void DoPaint( CDCHandle dcPaint )
	{
		DefWindowProc( WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC, 0 );
		DefWindowProc( WM_PAINT, (WPARAM)dcPaint.m_hDC, 0 );
	}
protected:
	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}
	//
	int GetFocusedItem()
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		//
		BOOL bOutside = TRUE;
		UINT nItem = ItemFromPoint(pt, bOutside);
		if (bOutside)
			return LB_ERR;
		//
		return nItem;
	}
	void ShowMenu(int x, int y)
	{
		CMenuHandle menu = GetContextMenu();
		if (!menu.m_hMenu)
			return;
		//
		OnUpdateContextMenu(m_nFocusedItem, menu);
		//
		UINT nCmd = menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD, x, y, m_hWnd);
		//
		if (nCmd)
		{
			SendMessage(WM_COMMAND, MAKEWPARAM(nCmd, 0), 0);
		}
	}
protected:
	virtual void DrawBackground(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		int nItem = lpDrawItemStruct->itemID;
		//
		BOOL bSelected = (lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED;
		BOOL bFocus = (lpDrawItemStruct->itemState & ODS_FOCUS) == ODS_FOCUS;
		//
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		//
		//BOOL bHot = CRect(lpDrawItemStruct->rcItem).PtInRect(pt);
		BOOL bHot = FALSE;
		//
		UINT nState = 0;
		if (bSelected)
		{
			nState |= wizStateSelected;
		}
		if (bHot)
		{
			nState |= wizStateHot;
		}
		//if (bFocus)
		//{
		//	nState |= wizStateFocused;
		//}

		WizDrawItemBackground(m_hWnd, lpDrawItemStruct->hDC, lpDrawItemStruct->rcItem, nState, GetBackgroundColor(nItem));
	}
	virtual void DrawText(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		CDCHandle dc(lpDrawItemStruct->hDC);
		//
		int nItem = lpDrawItemStruct->itemID;
		//
		int nDC = dc.SaveDC();
		//
		if (IsTextBold(nItem))
		{
			dc.SelectFont(m_fontBold);
		}
		else
		{
			dc.SelectFont(m_font);
		}
		//
		TCHAR szText[1024] = {0};
		if (lpDrawItemStruct->itemID == -1)
		{
			_tcscpy_s(szText, 1024, _T("No Data")); 
		}
		else
		{
			GetText(lpDrawItemStruct->itemID, szText);
		}
		//
		CRect rcText = lpDrawItemStruct->rcItem;
		rcText.DeflateRect(4, 2);
		//
		//
		if (lpDrawItemStruct->itemID == -1)
		{
			dc.SetTextColor(::GetSysColor(COLOR_BTNFACE));
		}
		else
		{
			dc.SetTextColor(GetTextColor(nItem));
		}
		//
		if (lpDrawItemStruct->itemID != -1 
			&& !m_il.IsNull())
		{
			int nImage = GetItemImage(lpDrawItemStruct->itemID);
			//
			CRect rcImage = rcText;
			rcImage.right = 16;
			rcImage.top = rcImage.top + (rcImage.Height() - 16) / 2;
			//
			if (-1 != nImage)
			{
				m_il.Draw(dc, nImage, rcImage.TopLeft(), ILD_TRANSPARENT);
			}
			//
			rcText.left += rcImage.right + 4;
		}
		//
		//
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(szText, -1, &rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS); 
		//
		dc.RestoreDC(nDC);
	}
	virtual void DeleteItemData(LPDELETEITEMSTRUCT lpDeleteItemStruct)
	{
	}
	virtual BOOL OnInitControl()
	{
		ResetItemHeight();
		//
		return TRUE;
	}
	//
	virtual BOOL OnDestroyControl()
	{
		return TRUE;
	}
public:
	virtual int CalItemHeight()
	{
		return ::GetSystemMetrics(SM_CYMENU) + 4;
	}
	virtual void ResetItemHeight()
	{
		CWizVistaListBoxImpl::SetItemHeight(0, CalItemHeight());
	}
	virtual HMENU GetContextMenu()
	{
		return NULL;
	}
	virtual void OnUpdateContextMenu(int nFocusedItem, HMENU hMenu)
	{
	}
	//
	virtual COLORREF GetTextColor(int nItem)
	{
		static COLORREF crText = GetSysColor(COLOR_WINDOWTEXT);
		return crText;
	}
	virtual COLORREF GetBackgroundColor(int nItem)
	{
		static COLORREF crBackground = GetSysColor(COLOR_WINDOW);
		return crBackground;
	}
	virtual BOOL IsTextBold(int nItem)
	{
		return GetCurSel() == nItem;
	}
public:
	void DeleteAllItems()
	{
		ResetContent();
	}
	//
	int SetItemImage(int nItem, LPCTSTR lpszIconFileName)
	{
		if (m_il.IsNull())
		{
			m_il.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
		}
		//
		int nImage = m_il.SafeAddIconFile(lpszIconFileName);
		m_mapImageIndex[nItem] = nImage;
		//
		return nImage;
	}
	//
	int GetItemImage(int nItem)
	{
		CImageIndexMap::const_iterator it = m_mapImageIndex.find(nItem);
		if (it == m_mapImageIndex.end())
			return -1;
		//
		return it->second;
	}
};


template <class T>
class CWizVistaListBoxMultiSelectBase
{
public:
	virtual int GetCommandItemCount()
	{
		T* pT = static_cast<T*>(this);
		//
		int nFocusedItem = pT->GetFocusedItemDirect();
		if (nFocusedItem != -1 && pT->GetSel(nFocusedItem) == 0)
		{
			return 1;
		}
		else
		{
			return pT->GetSelCount();
		}		
	}
	virtual void GetCommandItems(std::vector<int>& arrayItem)
	{
		T* pT = static_cast<T*>(this);
		//
		arrayItem.clear();
		//
		int nFocusedItem = pT->GetFocusedItemDirect();
		if (nFocusedItem != -1 && pT->GetSel(nFocusedItem) == 0)
		{
			//not a selected item
			arrayItem.push_back(nFocusedItem);
		}
		else
		{
			GetSelectedItems(arrayItem);
		}		
	}
	virtual void GetSelectedItems(std::vector<int>& arrayItem)
	{
		T* pT = static_cast<T*>(this);
		//
		arrayItem.clear();
		//
		//on selected items
		int nCount = pT->GetSelCount();
		//
		int* pData = new int[nCount];
		//
		pT->GetSelItems(nCount, pData); 
		//
		arrayItem.insert(arrayItem.begin(), pData, pData + nCount);
		//
		delete [] pData;
	}
	virtual int GetFirstCommandItem()
	{
		T* pT = static_cast<T*>(this);
		//
		std::vector<int> arrayItem;
		GetCommandItems(arrayItem);
		if (arrayItem.empty())
			return -1;
		//
		return arrayItem[0];
	}
	void SelectSingleItem(int nItem)
	{
		T* pT = static_cast<T*>(this);
		//
		std::vector<int> arrayItem;
		GetSelectedItems(arrayItem);
		for (std::vector<int>::const_iterator it = arrayItem.begin(); it != arrayItem.end(); it++)
		{
			pT->SetSel(*it, FALSE);
		}
		pT->SetSel(nItem, TRUE);
	}
	
};


class CWizVistaListBox : public CWizVistaListBoxImpl<CWizVistaListBox>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_ListBox"), GetWndClassName())
	//
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOTIFY;
	}
	//
	virtual int GetCommandItem()
	{
		if (-1 != m_nFocusedItem)
			return m_nFocusedItem;
		else
			return GetCurSel();
	}
};

class CWizVistaListBoxMultipleSelect : 
	public CWizVistaListBoxImpl<CWizVistaListBoxMultipleSelect>,
	public CWizVistaListBoxMultiSelectBase<CWizVistaListBoxMultipleSelect>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_ListBoxMultipleSelect"), GetWndClassName())
	//
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		if (0 != dwStyle)
			return dwStyle;
		//
		return WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_MULTIPLESEL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOTIFY;
	}
	virtual BOOL IsTextBold(int nItem)
	{
		return FALSE;
	}
};

class CWizVistaListBoxExtendedSelect : 
	public CWizVistaListBoxImpl<CWizVistaListBoxExtendedSelect>,
	public CWizVistaListBoxMultiSelectBase<CWizVistaListBoxMultipleSelect>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_ListBoxExtendedSelect"), GetWndClassName())
	//
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		if (0 != dwStyle)
			return dwStyle;
		//
		return WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_MULTIPLESEL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_EXTENDEDSEL | LBS_NOTIFY;
	}
	virtual BOOL IsTextBold(int nItem)
	{
		return FALSE;
	}
};




template <class T>
class CWizToolBarControlContainer
	: public ATL::CWindowImpl< T, ATL::CWindow, ATL::CControlWinTraits>
	, public CDoubleBufferImpl<T>
{
public:
	DECLARE_WND_CLASS_EX(NULL, 0, COLOR_WINDOW)
	//
	CWizToolBarControlContainer()
	{
	}

public:
	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLORLISTBOX, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLORMSGBOX, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLORSCROLLBAR, OnCtlColor)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColor)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDoubleBufferImpl<T >)
	END_MSG_MAP()
	//
	LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HWND hWndChild = (HWND)lParam;
		LRESULT ret = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
		if (ret)
			return ret;
		//
		return  ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		InvalidateRect(NULL);
		return 0;
	}
	
	void DrawBackground(CDCHandle dcPaint)
	{
		CWindow wndParent = GetParent();
		ATLASSERT(wndParent.m_hWnd);
		//
		CPoint pt(0, 0);
		MapWindowPoints(wndParent, &pt, 1);
		dcPaint.OffsetWindowOrg(pt.x, pt.y, &pt);
		LRESULT lRet = wndParent.SendMessage(WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC);
		dcPaint.SetWindowOrg(pt.x, pt.y);
	}
	//
	virtual void DoPaint(CDCHandle dcPaint)
	{
		DrawBackground(dcPaint);
	}
};

template <class TComboBoxClass>
class CWizToolBarComboBoxContainer 
	: public CWizToolBarControlContainer<CWizToolBarComboBoxContainer<TComboBoxClass>  >
{
public:
	CWizToolBarComboBoxContainer(DWORD dwComboStyle = 0)
		: m_dwComboStyle(dwComboStyle)
	{
	}
private:
	DWORD m_dwComboStyle;
public:
	TComboBoxClass m_combo;
public:
	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		COMMAND_CODE_HANDLER(CBN_SELCHANGE, OnComboSelChange)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CWizToolBarControlContainer)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_combo.Create(m_hWnd, rcDefault, NULL, m_dwComboStyle);
		//
		UpdateLayout();
		//
		return lRet;
	}
	//
	int CalComboBoxHeight()
	{
		static int height = -1;
		if (-1 == height)
		{
			CClientDC dc(m_hWnd);
			HFONT hFont = ((HFONT)GetStockObject( DEFAULT_GUI_FONT ));
			dc.SelectFont( hFont ); //GetFont()
			TEXTMETRIC tm;
			dc.GetTextMetrics(&tm); 

			height = tm.tmHeight + tm.tmInternalLeading + 4;
		}
		
		return height;
	}
	//
	LRESULT OnComboSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		return GetParent().SendMessage(WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), wNotifyCode), (LPARAM)hWndCtl);
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizToolBarControlContainer::OnSize(uMsg, wParam, lParam, bHandled);
		//
		UpdateLayout();
		//
		return 0;
	}
	//
	void UpdateLayout()
	{
		if (!m_combo.IsWindow())
			return;
		//
		CRect rcClient;
		GetClientRect(rcClient);
		//
		int nComboBoxHeight = CalComboBoxHeight();
		//
		CRect rcCombo = rcClient;
		//
		rcCombo.top = rcCombo.top + (rcClient.Height() - nComboBoxHeight) / 2;
		if (rcCombo.top < 0)
		{
			rcCombo.top = 0;
		}
		//
		rcCombo.bottom = rcCombo.top + 400;
		//
		m_combo.MoveWindow(rcCombo);
	}
	CString GetComboBoxText()
	{
		CString str;
		int nSel = m_combo.GetCurSel();
		if (-1 == nSel)
			return str;
		//
		m_combo.GetLBText(nSel, str);
		return str;
	}
};

class CWizToolBarEdit 
	: public ATL::CWindowImpl< CWizToolBarEdit, CEdit, ATL::CControlWinTraits>
{
public:
	CWizToolBarEdit();

	unsigned m_fMouseOver:1;

	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
	END_MSG_MAP()

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL StartTrackMouseLeave();
	BOOL IsMouseHover() const;
};


class CWizLinkToolBarEdit 
	: public CWizToolBarEdit 
{
public:
	CWizLinkToolBarEdit();
	~CWizLinkToolBarEdit();

	BEGIN_MSG_MAP(CWizLinkToolBarEdit)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(OCM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		//
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		//
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnMouseEvent)
		MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMouseEvent)
		MESSAGE_HANDLER(WM_MBUTTONUP, OnMouseEvent)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseEvent)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnMouseEvent)
		//
		CHAIN_MSG_MAP(CWizToolBarEdit)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

private:
	CBrush m_brush;
	CFont m_font;
	HCURSOR m_hCursor;
	//
	CToolTipCtrl m_tip;
public:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void ToolTipRelayEvent();
};

template <class TEditClass, bool t_bLargeFont = false>
class CWizToolBarEditContainer 
	: public CWizToolBarControlContainer<CWizToolBarEditContainer<TEditClass>  >
{
public:
	CWizToolBarEditContainer(DWORD dwEditStyle)
		: m_dwEditStyle(dwEditStyle)
		, m_fMouseOver(0)
	{
		WizCreateUIFont(m_font, t_bLargeFont ? WIZUIFONT_LARGE : 0);
		//
		m_penBorderLight.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNFACE));
		m_penBorderDark.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
	}
public:
	DWORD m_dwEditStyle;
	CFont m_font;
	TEditClass m_edit;
	CPen m_penBorderLight;
	CPen m_penBorderDark;
	unsigned m_fMouseOver:1;
public:
	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		COMMAND_CODE_HANDLER(EN_CHANGE, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_SETFOCUS, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_KILLFOCUS, OnEditNotify)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		CHAIN_MSG_MAP(CWizToolBarControlContainer)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.Create(m_hWnd, rcDefault, 0, m_dwEditStyle | ES_AUTOHSCROLL);
		m_edit.SetFont(m_font);
		//
		UpdateLayout();
		//
		return lRet;
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		if(m_fMouseOver == 0)
		{
			m_fMouseOver = 1;
			Invalidate();
			UpdateWindow();
			StartTrackMouseLeave();
		}
		//
		return lRet;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_fMouseOver == 1)
		{
			m_fMouseOver = 0;
			Invalidate();
			UpdateWindow();
		}
		return 0;
	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.SetFocus();
		//
		return lRet;
	}
	//
	LRESULT OnEditNotify(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (EN_SETFOCUS == wNotifyCode)
		{
			OnEnSetFocus();
		}
		else if (EN_KILLFOCUS == wNotifyCode)
		{
			OnEnKillFocus();
		}
		else if (EN_CHANGE == wNotifyCode)
		{
			OnEnChanged();
		}
		//
		return GetParent().SendMessage(WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), wNotifyCode), (LPARAM)hWndCtl);
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizToolBarControlContainer::OnSize(uMsg, wParam, lParam, bHandled);
		//
		UpdateLayout();
		//
		return 0;
	}
	//
	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}
	BOOL IsMouseHover()
	{
		if (m_fMouseOver)
			return TRUE;
		//
		if (GetFocus() == m_edit.m_hWnd)
			return TRUE;
		//
		__if_exists(TEditClass::IsMouseHover)
		{
			if (m_edit.IsMouseHover())
				return TRUE;
		}
		return FALSE;
	}
	virtual void DoPaint(CDCHandle dcPaint)
	{
		DrawBackground(dcPaint);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		CWizDCSaver saver(dcPaint);
		//
		if (IsMouseHover())
		{
			dcPaint.SelectStockBrush(NULL_BRUSH);
			dcPaint.SelectPen(IsMouseHover() ? m_penBorderDark : m_penBorderLight);
			//
			CRect rcBorder = rcClient;
			//rcBorder.DeflateRect(1, 1);
			//
			dcPaint.Rectangle(rcBorder);
		}
	}
	//
	virtual void OnEnSetFocus()
	{
		Invalidate();
	}
	virtual void OnEnKillFocus()
	{
		Invalidate();
	}
	virtual void OnEnChanged()
	{
	}
	//
	virtual CRect GetEditRect()
	{
		CRect rcClient;
		GetClientRect(rcClient);
		//
		int nEditHeight = CalEditHeight();
		//
		CRect rcEdit = rcClient;
		rcEdit.left += 4;
		rcEdit.right -= 2;
		//
		rcEdit.top = rcEdit.top + (rcClient.Height() - nEditHeight) / 2 + 1;
		if (rcEdit.top < 0)
		{
			rcEdit.top = 0;
		}
		//
		rcEdit.bottom = rcEdit.top + nEditHeight;
		//
		return rcEdit;
	}
	//
	virtual void UpdateLayout()
	{
		if (!m_edit.IsWindow())
			return;
		//
		CRect rcEdit = GetEditRect();
		m_edit.MoveWindow(rcEdit);
	}
	CString GetEditText()
	{
		CString str;
		m_edit.GetWindowText(str);
		return str;
	}
	//
	int CalEditHeight()
	{
		static int height = -1;
		if (-1 == height)
		{
			height = WizGetFontHeight(m_hWnd, m_font) + 2;
		}
		
		return height;
	}
	//
	int GetMinHeight()
	{
		if (!IsWindow())
			return 28;
		return CalEditHeight() + 8;
	}
};


template <class TEditClass, bool t_bLargeFont = false>
class CWizToolBarIconEditContainer 
	: public CWizToolBarControlContainer<CWizToolBarIconEditContainer<TEditClass>  >
{
public:
	CWizToolBarIconEditContainer(DWORD dwEditStyle)
		: m_dwEditStyle(dwEditStyle)
		, m_pImageList(NULL)
		, m_nImageIndex(-1)
		, m_fMouseOver(0)
	{
		WizCreateUIFontEx(m_font, t_bLargeFont ? WIZUIFONT_LARGE : 0);
		//
		m_penBorderLight.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNFACE));
		m_penBorderDark.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
	}
public:
	DWORD m_dwEditStyle;
	CFont m_font;
	TEditClass m_edit;
	CPen m_penBorderLight;
	CPen m_penBorderDark;
	//
	CImageList* m_pImageList;
	int m_nImageIndex;
	//
	unsigned m_fMouseOver:1;
public:
	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		COMMAND_CODE_HANDLER(EN_CHANGE, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_SETFOCUS, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_KILLFOCUS, OnEditNotify)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP(CWizToolBarControlContainer)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.Create(m_hWnd, rcDefault, 0, m_dwEditStyle | ES_AUTOHSCROLL);
		m_edit.SetFont(m_font);
		//
		UpdateLayout();
		//
		return lRet;
	}
	
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		if(m_fMouseOver == 0)
		{
			m_fMouseOver = 1;
			Invalidate();
			UpdateWindow();
			StartTrackMouseLeave();
		}
		//
		return lRet;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_fMouseOver == 1)
		{
			m_fMouseOver = 0;
			Invalidate();
			UpdateWindow();
		}
		return 0;
	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.SetFocus();
		//
		return lRet;
	}
	//
	LRESULT OnEditNotify(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (EN_SETFOCUS == wNotifyCode)
		{
			OnEnSetFocus();
		}
		else if (EN_KILLFOCUS == wNotifyCode)
		{
			OnEnKillFocus();
		}
		//
		return GetParent().SendMessage(WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), wNotifyCode), (LPARAM)hWndCtl);
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizToolBarControlContainer::OnSize(uMsg, wParam, lParam, bHandled);
		//
		UpdateLayout();
		//
		return 0;
	}
	//
	
	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}
	BOOL IsMouseHover()
	{
		if (m_fMouseOver)
			return TRUE;
		//
		if (GetFocus() == m_edit.m_hWnd)
			return TRUE;
		//
		__if_exists(TEditClass::IsMouseHover)
		{
			if (m_edit.IsMouseHover())
				return TRUE;
		}
		return FALSE;
	}
	//
	virtual void DoPaint(CDCHandle dcPaint)
	{
		DrawBackground(dcPaint);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		CWizDCSaver saver(dcPaint);
		//
		if (IsMouseHover())
		{
			dcPaint.SelectStockBrush(NULL_BRUSH);
			dcPaint.SelectPen(IsMouseHover() ? m_penBorderDark : m_penBorderLight);
			//
			CRect rcBorder = rcClient;
			rcBorder.DeflateRect(1, 1);
			//
			rcBorder.left += 40;
			//
			dcPaint.Rectangle(rcBorder);
		}
		//
		if (m_pImageList && m_nImageIndex >= 0)
		{
			CRect rcIcon = GetIconRect();
			m_pImageList->Draw(dcPaint, m_nImageIndex, rcIcon.TopLeft(), ILD_TRANSPARENT); 
		}
	}
	//
	void OnEnSetFocus()
	{
		Invalidate();
	}
	void OnEnKillFocus()
	{
		Invalidate();
	}
	//
	CRect GetIconRect()
	{
		CRect rcClient;
		GetClientRect(rcClient);
		//
		CRect rcIcon = rcClient;
		rcIcon.left = 22;
		rcIcon.right = rcIcon.left + 16;
		//
		rcIcon.top = rcIcon.top + (rcClient.Height() - 16) / 2;
		if (rcIcon.top < 0)
		{
			rcIcon.top = 0;
		}
		//
		rcIcon.bottom = rcIcon.top + 16;
		//
		return rcIcon;
	}
	CRect GetEditRect()
	{
		CRect rcClient;
		GetClientRect(rcClient);
		//
		int nEditHeight = CalEditHeight();
		//
		CRect rcEdit = rcClient;
		rcEdit.left += 46;
		rcEdit.right -= 2;
		//
		rcEdit.top = rcEdit.top + (rcClient.Height() - nEditHeight) / 2 + 1;
		if (rcEdit.top < 0)
		{
			rcEdit.top = 0;
		}
		//
		rcEdit.bottom = rcEdit.top + nEditHeight;
		//
		return rcEdit;
	}
	//
	void UpdateLayout()
	{
		if (!m_edit.IsWindow())
			return;
		//
		CRect rcEdit = GetEditRect();
		m_edit.MoveWindow(rcEdit);
	}
	CString GetEditText()
	{
		CString str;
		m_edit.GetWindowText(str);
		return str;
	}
	//
	int CalEditHeight()
	{
		static int height = -1;
		if (-1 == height)
		{
			height = WizGetFontHeight(m_hWnd, m_font) + 2;
		}
		
		return height;
	}
	//
	void SetImage(CImageList* pImageList, int nImageIndex)
	{
		m_pImageList = pImageList;
		m_nImageIndex = nImageIndex;
	}
};



template <class TEditClass, bool t_bLargeFont = false>
class CWizToolBarTextEditContainer 
	: public CWizToolBarControlContainer<CWizToolBarTextEditContainer<TEditClass>  >
{
public:
	CWizToolBarTextEditContainer(DWORD dwEditStyle)
		: m_dwEditStyle(dwEditStyle)
		, m_fMouseOver(0)
	{
		WizCreateUIFontEx(m_font, t_bLargeFont ? WIZUIFONT_LARGE : 0);
		//
		m_penBorderLight.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNFACE));
		m_penBorderDark.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
	}
public:
	DWORD m_dwEditStyle;
	CFont m_font;
	TEditClass m_edit;
	CPen m_penBorderLight;
	CPen m_penBorderDark;
	//
	unsigned m_fMouseOver:1;
public:
	BEGIN_MSG_MAP(CWizToolBarControlContainer)
		COMMAND_CODE_HANDLER(EN_CHANGE, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_SETFOCUS, OnEditNotify)
		COMMAND_CODE_HANDLER(EN_KILLFOCUS, OnEditNotify)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP(CWizToolBarControlContainer)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.Create(m_hWnd, rcDefault, 0, m_dwEditStyle | ES_AUTOHSCROLL);
		m_edit.SetFont(m_font);
		//
		UpdateLayout();
		//
		return lRet;
	}
	
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		if(m_fMouseOver == 0)
		{
			m_fMouseOver = 1;
			Invalidate();
			UpdateWindow();
			StartTrackMouseLeave();
		}
		//
		return lRet;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_fMouseOver == 1)
		{
			m_fMouseOver = 0;
			Invalidate();
			UpdateWindow();
		}
		return 0;
	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_edit.SetFocus();
		//
		return lRet;
	}
	//
	LRESULT OnEditNotify(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (EN_SETFOCUS == wNotifyCode)
		{
			OnEnSetFocus();
		}
		else if (EN_KILLFOCUS == wNotifyCode)
		{
			OnEnKillFocus();
		}
		//
		return GetParent().SendMessage(WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), wNotifyCode), (LPARAM)hWndCtl);
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizToolBarControlContainer::OnSize(uMsg, wParam, lParam, bHandled);
		//
		UpdateLayout();
		//
		return 0;
	}
	//
	
	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}
	BOOL IsMouseHover()
	{
		if (m_fMouseOver)
			return TRUE;
		//
		if (GetFocus() == m_edit.m_hWnd)
			return TRUE;
		//
		__if_exists(TEditClass::IsMouseHover)
		{
			if (m_edit.IsMouseHover())
				return TRUE;
		}
		return FALSE;
	}
	//
	virtual void DoPaint(CDCHandle dcPaint)
	{
		DrawBackground(dcPaint);
		//
		CRect rcClient;
		GetClientRect(&rcClient);
		//
		CWizDCSaver saver(dcPaint);
		//
		if (IsMouseHover())
		{
			dcPaint.SelectStockBrush(NULL_BRUSH);
			dcPaint.SelectPen(IsMouseHover() ? m_penBorderDark : m_penBorderLight);
			//
			CRect rcEdit = GetEditRect();
			CRect rcBorder = rcClient;
			rcBorder.DeflateRect(1, 1);
			//
			rcBorder.left = rcEdit.left - 2;
			//
			dcPaint.Rectangle(rcBorder);
		}
		//
		UINT nID = GetWindowLong(GWL_ID);
		CString strText = WizFormatString0(nID);
		//
		dcPaint.SelectFont(m_font);
		CRect rcText = GetTextRect();
		dcPaint.DrawText(strText, strText.GetLength(), &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//
	void OnEnSetFocus()
	{
		Invalidate();
	}
	void OnEnKillFocus()
	{
		Invalidate();
	}
	//
	CRect GetTextRect()
	{
		UINT nID = GetWindowLong(GWL_ID);
		CString strText = WizFormatString0(nID);
		//
		CRect rcClient;
		GetClientRect(rcClient);
		//
		CRect rcText = rcClient;
		rcText.right = rcText.left + ::WizGetTextWidth(m_hWnd, strText, m_font) + 16;
		//
		int nFontHeight = ::WizGetFontHeight(m_hWnd, m_font);
		//
		rcText.top = rcText.top + (rcClient.Height() - nFontHeight) / 2;
		if (rcText.top < 0)
		{
			rcText.top = 0;
		}
		//
		rcText.bottom = rcText.top + nFontHeight + 1;
		//
		return rcText;
	}
	CRect GetEditRect()
	{
		CRect rcClient;
		GetClientRect(rcClient);
		//
		int nEditHeight = CalEditHeight();
		//
		CRect rcText = GetTextRect();
		//
		CRect rcEdit = rcClient;
		rcEdit.left = rcText.right;
		rcEdit.right -= 2;
		//
		rcEdit.top = rcEdit.top + (rcClient.Height() - nEditHeight) / 2 + 1;
		if (rcEdit.top < 0)
		{
			rcEdit.top = 0;
		}
		//
		rcEdit.bottom = rcEdit.top + nEditHeight;
		//
		return rcEdit;
	}
	//
	void UpdateLayout()
	{
		if (!m_edit.IsWindow())
			return;
		//
		CRect rcEdit = GetEditRect();
		m_edit.MoveWindow(rcEdit);
	}
	CString GetEditText()
	{
		CString str;
		m_edit.GetWindowText(str);
		return str;
	}
	//
	int CalEditHeight()
	{
		static int height = -1;
		if (-1 == height)
		{
			height = WizGetFontHeight(m_hWnd, m_font) + 2;
		}
		
		return height;
	}
};




template <class T>
class CWizToolBarCtrlBase : public ATL::CWindowImpl< T, CToolBarCtrl, ATL::CControlWinTraits>
{
public:
	CWizToolBarCtrlBase()
	{
		m_bAutoSize = TRUE;
		m_nStreatchButtonCommand = 0;
		m_nStreatchButtonMinWidth = 24;
	}
protected:
	BOOL m_bAutoSize;
	int m_nStreatchButtonCommand;
	int m_nStreatchButtonMinWidth;
public:
	BEGIN_MSG_MAP(CWizToolBarCtrlBase)
		MESSAGE_HANDLER(TB_SETBUTTONSIZE, OnSetButtonSize)
		MESSAGE_HANDLER(TB_SETBITMAPSIZE, OnSetBitmapSize)
		MESSAGE_HANDLER(WM_SETTINGCHANGE, OnPreserveZeroBorderHelper)
		MESSAGE_HANDLER(WM_SETFONT, OnPreserveZeroBorderHelper)
	END_MSG_MAP()
	LRESULT OnSetButtonSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CSize size;
		return OnSetSizeHelper(size, uMsg, wParam, lParam);
	}
	LRESULT OnSetBitmapSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CSize size;
		return OnSetSizeHelper(size, uMsg, wParam, lParam);
	}
	LRESULT OnPreserveZeroBorderHelper(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DWORD dwStyle = GetStyle();
		BOOL bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT|TBSTYLE_FLAT);
		DWORD dwStyleEx = 0;
		if (IsWindow())
		{
			dwStyleEx = SetExtendedStyle(GetExtendedStyle() &~ TBSTYLE_EX_DRAWDDARROWS);
		}

		LRESULT lResult = DefWindowProc(uMsg, wParam, lParam);;

		if (bModify)
		{
			SetWindowLong(GWL_STYLE, dwStyle);
		}
		if (dwStyleEx & TBSTYLE_EX_DRAWDDARROWS)
		{
			SetExtendedStyle(dwStyleEx);
		}
		//
		AlignControls();

		return lResult;
	}
	LRESULT OnSetSizeHelper(CSize& size, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		DWORD dwStyle = GetStyle();
		BOOL bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT);
		//
		DWORD dwStyleEx = 0;
		if (IsWindow())
		{
			dwStyleEx = SetExtendedStyle(GetExtendedStyle() &~ TBSTYLE_EX_DRAWDDARROWS);
		}
		//
		LRESULT lResult = DefWindowProc(nMessage, wParam, lParam);
		//
		if (lResult)
		{
			size = DWORD(lParam); // IA64: Assume size is packed in low-order DWORD
		}

		if (bModify)
		{
			SetWindowLong(GWL_STYLE, dwStyle);
		}
		if (dwStyleEx)
		{
			SetExtendedStyle(dwStyleEx);
		}
		//
		AlignControls();

		return lResult;
	}
	void AddToolButtonNoTextWithToolTip(UINT nID, LPCTSTR lpszButtonText, UINT nImageIndex)
	{
		int nButtonStyle = BTNS_BUTTON;
		//
		CString str(lpszButtonText);
		//
		TCHAR szText[1024];
		ZeroMemory(szText, sizeof(TCHAR) * 1024);
		memcpy_s(szText, sizeof(TCHAR) * (1024), (LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		//
		int nStringIndex = AddStrings(szText);
		//
		TBBUTTON tbbtn = { 0 };
		ZeroMemory(&tbbtn, sizeof(tbbtn));
		tbbtn.idCommand = nID;
		tbbtn.fsState = TBSTATE_ENABLED;
		tbbtn.fsStyle = nButtonStyle;
		tbbtn.iBitmap = nImageIndex;
		tbbtn.iString = nStringIndex;
		AddButtons(1, &tbbtn);
	}
	void AddToolButton2(UINT nID, LPCTSTR lpszButtonText, UINT nButtonStyle = 0, BOOL bShowText = TRUE, UINT nImageIndex = I_IMAGENONE, int nInsertPos = -1)
	{
		if (0 == nButtonStyle)
		{
			nButtonStyle = BTNS_BUTTON;
		}
		//
		if (m_bAutoSize)
		{
			nButtonStyle |= BTNS_AUTOSIZE;
		}
		//
		int nStringIndex = -1;
		if (bShowText)
		{
			CString str(lpszButtonText);
			//
			TCHAR szText[1024];
			ZeroMemory(szText, sizeof(TCHAR) * 1024);
			memcpy_s(szText, sizeof(TCHAR) * (1024), (LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
			//
			nStringIndex = AddStrings(szText);
			//
			if (-1 != nStringIndex)
			{
				nButtonStyle |= BTNS_SHOWTEXT;
			}
		}
		//
		//
		TBBUTTON tbbtn = { 0 };
		ZeroMemory(&tbbtn, sizeof(tbbtn));
		tbbtn.idCommand = nID;
		tbbtn.fsState = TBSTATE_ENABLED;
		tbbtn.fsStyle = nButtonStyle;
		tbbtn.iBitmap = nImageIndex;
		tbbtn.iString = nStringIndex;
		//
		if (-1 == nInsertPos)
		{
			AddButtons(1, &tbbtn);
		}
		else
		{
			InsertButton(nInsertPos, &tbbtn);
		}
	}

	void AddToolButton(UINT nID, UINT nButtonStyle = 0, BOOL bShowText = TRUE, UINT nImageIndex = I_IMAGENONE)
	{
		CString str = WizFormatString0(nID);
		int nPos = str.Find(_T("\n"));
		if (-1 != nPos)
		{
			str.Delete(0, nPos + 1);
		}
		//
		return AddToolButton2(nID, str, nButtonStyle, bShowText, nImageIndex);
	}
	void AddToolButtonSep()
	{
		TBBUTTON tbbtn = { 0 };
		ZeroMemory(&tbbtn, sizeof(tbbtn));
		tbbtn.fsStyle = BTNS_SEP;
		AddButtons(1, &tbbtn);
	}
	//
	virtual BOOL AddControl(UINT nID, int cx, HWND hwndControl)
	{
		CSize sizeButton;
		GetButtonSize(sizeButton);
		//
		/*
		添加按钮，可能导致按钮高度变化，因此在添加按钮之前，先获得按钮大小
		*/
		CString str = WizFormatString0(nID);
		int nPos = str.Find(_T("\n"));
		if (-1 != nPos)
		{
			str.Delete(0, nPos + 1);
		}
		TCHAR szText[1024];
		ZeroMemory(szText, sizeof(TCHAR) * 1024);
		memcpy_s(szText, sizeof(TCHAR) * (1024), (LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		//
		int nStringIndex = AddStrings(szText);
		//
		TBBUTTON tbbtn = { 0 };
		ZeroMemory(&tbbtn, sizeof(tbbtn));
		tbbtn.idCommand = nID;
		tbbtn.fsState = TBSTATE_ENABLED;
		tbbtn.fsStyle = BTNS_BUTTON;
		tbbtn.iBitmap = -2;
		tbbtn.iString = nStringIndex;
		AddButtons(1, &tbbtn);
		//
		/*
		重新设置按钮大小
		*/
		SetButtonSize(sizeButton.cx, sizeButton.cy);
		//
		int nItemIndex = CommandToIndex(nID); 
		if (-1 == nItemIndex)
			return FALSE;
		//
		SetButtonInfo(nID, TBIF_SIZE, 0, 0, NULL, 0, cx, 0, NULL); 
		//
		CRect rcItem;
		GetItemRect(nItemIndex, &rcItem);
		rcItem.bottom = rcItem.top + sizeButton.cy;
		//
		::SetWindowPos(hwndControl, NULL, rcItem.left, rcItem.top, rcItem.Width(), rcItem.Height(), SWP_NOZORDER);
		//
		return TRUE;
	}
	//
	void SetStreatchButton(int nCommandID, int nMinWidth)
	{
		m_nStreatchButtonCommand = nCommandID;
		m_nStreatchButtonMinWidth = nMinWidth;
	}
	virtual void StreatchButton()
	{
		if (0 == m_nStreatchButtonCommand)
			return;
		//
		CRect rc;
		GetClientRect(&rc);
		//
		int nTotalWidth = 0;
		//
		int  nIndex = CommandToIndex(m_nStreatchButtonCommand);
		if (-1 == nIndex)
			return;
		//
		int nButtonCount = GetButtonCount();
		for (int i = nButtonCount - 1; i >= 0; i--)
		{
			if (i != nIndex)
			{
				CRect rcBtn;
				GetItemRect(i, rcBtn);
				//
				nTotalWidth += rcBtn.Width();
			}
		}
		//
		nTotalWidth += 3;
		//
		int nStreatchWidth = rc.Width() - nTotalWidth;
		//
		if (nStreatchWidth < m_nStreatchButtonMinWidth)
		{
			nStreatchWidth = m_nStreatchButtonMinWidth;
		}
		//
		SetButtonInfo(m_nStreatchButtonCommand, TBIF_SIZE, 0, 0, NULL, 0, nStreatchWidth, 0, NULL); 
	}

	virtual void AlignControls()
	{
		StreatchButton();
		//
		int nCount = GetButtonCount();
		for (int i = 0; i < nCount; i++)
		{
			TBBUTTON button;
			GetButton(i, &button);
			//
			CWindow wnd = ::GetDlgItem(m_hWnd, button.idCommand);
			if (wnd.IsWindow())
			{
				CRect rc;
				GetButtonDrawRect(i, rc);
				wnd.MoveWindow(&rc);
			}
		}
	}
	virtual void GetButtonDrawRect(int nIndex, CRect& rc)
	{
		GetItemRect(nIndex, rc);
	}
	//
	void SetButtonText(UINT nID, LPCTSTR lpszText)
	{
		SetButtonInfo(nID, TBIF_TEXT , 0, 0, lpszText, 0, 0, 0, NULL);
	}
	void SetButtonImage(UINT nID, int nImage)
	{
		SetButtonInfo(nID, TBIF_IMAGE, 0, 0, NULL, nImage, 0, 0, NULL);
	}
};


#define WIZ_BTNS_EX_BOLD_BUTTON			0x0001
#define WIZ_BTNS_EX_DEFAULT_BUTTON		0x0002
#define WIZ_BTNS_EX_TITLE_BUTTON		0x0004
#define WIZ_BTNS_EX_SPACE_BUTTON		0x0008

const UINT WIZ_UM_TOOLBAR_DROPDOWN_MENU		= ::RegisterWindowMessage(_T("WIZ_UM_TOOLBAR_DROPDOWN_MENU"));

template <class T>
class CWizToolBarCtrlBaseExImpl 
	: public CWizToolBarCtrlBase< T>
	, public CDoubleBufferImpl<CWizToolBarCtrlBaseExImpl<T> >
{
public:
	typedef ATL::CWindowImpl< T, CToolBarCtrl, ATL::CControlWinTraits> CBaseClass;
	//
	//DECLARE_WND_SUPERCLASS(NULL, CBaseClass::GetWndClassName())
public:
	CWizToolBarCtrlBaseExImpl(void)
	{
		WizCreateUIFont(m_font);
		WizCreateUIFont(m_fontBold, WIZUIFONT_BOLD);
		m_nCenterLine = 0;
		m_nDropDown = -1;
		m_nHighlightPos = -1;
	}
public:
	BEGIN_MSG_MAP(CWizToolBarCtrlBaseExImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WIZ_UM_TOOLBAR_DROPDOWN_MENU, OnToolbarDropdownMenu)
		REFLECTED_NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnTbnDropDown)
		REFLECTED_NOTIFY_CODE_HANDLER(TTN_NEEDTEXTA, OnToolTipNotify)
		REFLECTED_NOTIFY_CODE_HANDLER(TTN_NEEDTEXTW, OnToolTipNotify)
		REFLECTED_NOTIFY_CODE_HANDLER(TBN_GETINFOTIP, OnGetInfoTipNotify)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CWizToolBarCtrlBaseExImpl<T> > )
		CHAIN_MSG_MAP(CWizToolBarCtrlBase<T>)
	END_MSG_MAP()
public:
	CFont m_font;
	CFont m_fontBold;
	//
protected:
	int m_nCenterLine;
	int m_nDropDown;
	//
	std::map<UINT, UINT> m_mapButtonExStyle;
	//
	int m_nHighlightPos;
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		if (0 == dwStyle)
		{
			return ATL_SIMPLE_TOOLBAR_STYLE | CCS_NODIVIDER | TBSTYLE_LIST | TBSTYLE_FLAT;
		}
		else
		{
			return dwStyle;
		}
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		return CBaseClass::SubclassWindow( hWnd ) ? OnInitControl() : FALSE;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		OnInitControl();
		//
		return lRet;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		OnDestroyControl();
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		//
		//为了让控件透明
		//
		CRect rc;
		GetClientRect(&rc);
		//
		HDC hDC = (HDC)wParam;
		HWND hwnd = WindowFromDC(hDC);
		//
		if (hwnd == m_hWnd)
			return 1;
		//
		CDCHandle dcPaint(hDC);
		//
		DrawBackground(dcPaint, rc);
		//
		return 1;   // no background painting needed
	}
	void DoPaint( CDCHandle dcPaint )
	{
		T* pT = static_cast<T*>(this);
		//
		CRect rc;
		GetClientRect(&rc);
		//
		int nDC = dcPaint.SaveDC();
		DrawBackground(dcPaint, rc);
		// prepare dc
		dcPaint.SelectFont(m_font);
		// paint the tabs first and then the borders
		int nButtonCount = GetButtonCount();
		int nHot = GetHotItem();
		//
		CImageList il = GetImageList();
		CImageList ilDisabled = GetDisabledImageList();
		//
		for (int i = 0; i < nButtonCount; i++)
		{
			DrawButton(dcPaint, i, i == nHot, il, ilDisabled);
		}
		//
		dcPaint.RestoreDC(nDC);
	}
	virtual BOOL OnInitControl()
	{
		SetButtonStructSize();
		return TRUE;
	}
	virtual BOOL OnDestroyControl()
	{
		return TRUE;
	}
	//
	virtual void GetButtonDrawRect(int nIndex, CRect& rc)
	{
		GetItemRect(nIndex, &rc);
		//
		rc.DeflateRect(1, 0);
		rc.top += 1;
		//
		if (0 == nIndex)
		{
			rc.left += 2;
		}
	}
	//
	virtual void DrawButtonBackground(CDCHandle dc, int nIndex, BOOL bHot) = 0;
	virtual void DrawBackground(CDCHandle dc, const CRect& rc) = 0;
	//

	/*
	//为了兼容linux的wine。wine在这里有一个bug：////
	//TB_GETSTRING （unicode版本TB_GETSTRINGW）的时候，对字体长度计算有错误，导致无法正确返回unicode字符串。增加缓冲区可以解决这个问题。////
	*/
	/*
	int _GetString(int nString, _CSTRING_NS::CString& str) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		int nLength = (int)(short)LOWORD(::SendMessage(m_hWnd, TB_GETSTRING, MAKEWPARAM(0, nString), NULL));
		if(nLength != -1)
		{
			int nBufferLength = nLength * 4 + 1;
			LPTSTR lpstr = str.GetBufferSetLength(nBufferLength);
			if(lpstr != NULL)
				nLength = (int)::SendMessage(m_hWnd, TB_GETSTRING, MAKEWPARAM(nBufferLength, nString), (LPARAM)lpstr);
			else
				nLength = -1;
			str.ReleaseBuffer();
		}
		return nLength;
	}
	*/
	CString GetButtonTextByCommand(UINT nCommand)
	{
		TCHAR szButtonText[MAX_PATH] = {0};
		TBBUTTONINFO tbi;
		ZeroMemory(&tbi, sizeof(TBBUTTONINFO));
		tbi.cbSize = sizeof(TBBUTTONINFO);
		tbi.dwMask = TBIF_TEXT;
		tbi.pszText = szButtonText;
		tbi.cchText = MAX_PATH;
		GetButtonInfo(nCommand, &tbi);
		return CString(szButtonText);
	}
	virtual void DrawButton(CDCHandle dc, int nIndex, BOOL bHot, CImageList& il, CImageList& ilDisabled)
	{
		TBBUTTON button;
		GetButton(nIndex, &button);
		//
		UINT nExStyle = GetButtonExStyle(button.idCommand);
		//
		if (0 == (nExStyle & WIZ_BTNS_EX_TITLE_BUTTON)
			&& 0 == (nExStyle & WIZ_BTNS_EX_SPACE_BUTTON))
		{
			DrawButtonBackground(dc, nIndex, bHot);
		}
		//
		if (button.fsStyle & BTNS_SEP)
			return;
		//
		CRect rc;
		GetButtonDrawRect(nIndex, rc);
		//
		BOOL bDrawText = (0 != (button.fsStyle & BTNS_SHOWTEXT));
		BOOL bDrawImage = !il.IsNull() && button.iBitmap >= 0;
		//
		CRect rcText;
		CRect rcImage;
		//
		CString strText = GetButtonTextByCommand(button.idCommand);
		//
		if (bDrawText)
		{
			BOOL bBold = (GetButtonExStyle(button.idCommand) & WIZ_BTNS_EX_BOLD_BUTTON) ? TRUE : FALSE;
			dc.SelectFont(bBold ? m_fontBold : m_font);
		}
		//
		if (bDrawText && bDrawImage)
		{
			CSize size;
			dc.GetTextExtent(strText, -1, &size);
			size.cx += 2;
			//
			int x = rc.left + (rc.Width() - size.cx - 18) / 2;
			rcImage = CRect(x, rc.top, x + 18, rc.bottom);
			rcText = CRect(x + 18, rc.top, x + 18 + size.cx, rc.bottom);
		}
		else if (bDrawText)
		{
			CSize size;
			dc.GetTextExtent(strText, -1, &size);
			//
			int x = rc.left + (rc.Width() - size.cx) / 2;
			rcText = CRect(x, rc.top, x + size.cx, rc.bottom);
		}
		else if (bDrawImage)
		{
			int x = rc.left + (rc.Width() - 18) / 2;
			rcImage = CRect(x, rc.top, x + 18, rc.bottom);
		}
		else
		{
			//ATLASSERT(FALSE);
		}
		//
		if (button.fsStyle & BTNS_DROPDOWN)
		{
			rcText.MoveToX(rcText.left - 8);
			rcImage.MoveToX(rcImage.left - 8);
			//
			CRect rcDropDown = rc;
			rcDropDown.left = rcDropDown.right - 16;
			rcDropDown.right -= 2;
			DrawDropDownArrow(dc, rcDropDown);
		}
		else if (button.fsStyle & BTNS_WHOLEDROPDOWN)
		{
			rcText.MoveToX(rcText.left - 4);
			rcImage.MoveToX(rcImage.left - 4);
			//
			CRect rcDropDown = bDrawText ? rcText : rcImage;
			//
			rcDropDown.MoveToX(rcDropDown.right);
			rcDropDown.right = rcDropDown.left + 8;
			if (rcDropDown.right > rc.right)
			{
				rcDropDown.right = rc.right;
			}
			//
			DrawDropDownArrow(dc, rcDropDown);
		}
		//
		if (bDrawImage)
		{
			rcImage.DeflateRect((rcImage.Width() - 16) / 2, (rcImage.Height() - 16) / 2);
			//
			CPoint pt = rcImage.TopLeft();
			if (button.fsState & TBSTATE_ENABLED)
			{
				il.Draw(dc, button.iBitmap, pt.x, pt.y, ILD_TRANSPARENT); 
			}
			else
			{
				if (ilDisabled.IsNull())
				{
					HICON hIcon = il.ExtractIcon(button.iBitmap);
					if (hIcon)
					{
						dc.DrawState(pt, CSize(16, 16), hIcon, DSS_DISABLED | DST_ICON);
						DestroyIcon(hIcon);
					}
				}
				else
				{
					ilDisabled.Draw(dc, button.iBitmap, pt.x, pt.y, ILD_TRANSPARENT); 
				}
			}
		}
		//
		if (bDrawText
			&& 0 == (nExStyle & WIZ_BTNS_EX_SPACE_BUTTON))
		{
			BOOL bBold = (nExStyle & WIZ_BTNS_EX_BOLD_BUTTON) ? TRUE : FALSE;
			dc.SelectFont(bBold ? m_fontBold : m_font);
			//
			if (nExStyle & WIZ_BTNS_EX_TITLE_BUTTON)
			{
				dc.SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
			}
			else
			{
				dc.SetTextColor(button.fsState & TBSTATE_ENABLED ? ::GetSysColor(COLOR_WINDOWTEXT) : ::GetSysColor(COLOR_GRAYTEXT));
			}
			//
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(strText, -1, &rcText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}

	virtual void DrawDropDownArrow(CDCHandle dc, const CRect& rc)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_WINDOWTEXT));
		dc.SelectPen(pen);
		//
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
		dc.SelectBrush(brush);
		//
		CPoint ptCenter = rc.CenterPoint();
		//
		POINT arrayPt[3] = 
		{
			{ptCenter.x - 2, ptCenter.y -1},
			{ptCenter.x + 2, ptCenter.y - 1},
			{ptCenter.x, ptCenter.y + 1}
		};
		//
		dc.Polygon(arrayPt, 3);
	}
	virtual void DrawSplitterLine(CDCHandle dc, const CRect& rc, UINT nLine)
	{
		static COLORREF rgbOuter = RGB( 217, 217, 217);
		static COLORREF rgbInner = RGB( 250, 250, 251);
		//
		int nSplitter = rc.right - 16;
		//
		if (nLine & 0x01)
		{
			dc.FillSolidRect(CRect(nSplitter, rc.top + 1, nSplitter + 1, rc.bottom - 1), rgbInner);
		}
		//
		if (nLine & 0x02)
		{
			dc.FillSolidRect(CRect(nSplitter + 1, rc.top + 1, nSplitter + 2, rc.bottom - 1), rgbOuter);
		}
		//
		if (nLine & 0x04)
		{
			dc.FillSolidRect(CRect(nSplitter + 2, rc.top + 1, nSplitter + 3, rc.bottom - 1), rgbInner);
		}
	}
	//
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nDropDown = -1;
		//
		int xPos = GET_X_LPARAM(lParam); 
		int yPos = GET_Y_LPARAM(lParam); 
		//
		CPoint pt(xPos, yPos);
		//
		int nButton = HitTest(&pt);
		//
		if (-1 != nButton)
		{
			TBBUTTON button;
			GetButton(nButton, &button);
			//
			if (button.fsStyle & BTNS_DROPDOWN)
			{
				CRect rcItem;
				GetItemRect(nButton, &rcItem);
				rcItem.left = rcItem.right - 15;
				//
				if (rcItem.PtInRect(pt))
				{
					m_nDropDown = nButton;
				}
			}
		}
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		if (-1 != m_nDropDown)
		{
			CRect rcItem;
			GetItemRect(nButton, &rcItem);
			//
			InvalidateRect(&rcItem);
			//
			m_nDropDown = -1;
		}
		//
		return lRet;
	}
	LRESULT OnToolbarDropdownMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWindow parent = GetParent();
		if (parent.IsWindow())
		{
			parent.SendMessage(uMsg, wParam, lParam);
		}
		bHandled = TRUE;
		//
		return 0;
	}
	//
	void ShowDropDownMenu(UINT nID)
	{
		CMenu menu;
		if (!menu.LoadMenu(nID))
			return;
		//
		WizTranslationsTranslateMenu(menu);
		//
		CMenuHandle subMenu = menu.GetSubMenu(0);
		//
		if (!subMenu)
			return;
		//
		int nIndex = CommandToIndex(nID);
		if (-1 == nIndex)
			return;
		//
		CRect rc;
		GetItemRect(nIndex, rc);
		ClientToScreen(&rc);
		//
		CWindow parent = GetParent();
		if (parent.IsWindow())
		{
			parent.SendMessage(WIZ_UM_TOOLBAR_DROPDOWN_MENU, nID, (LPARAM)subMenu.m_hMenu);
		}
		//
		subMenu.TrackPopupMenu(0, rc.left, rc.bottom, m_hWnd);
	}
	//
	LRESULT OnTbnDropDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		NMTOOLBAR* pToolBar = (NMTOOLBAR *)pnmh;
		//
		int nID = pToolBar->iItem;
		//
		ShowDropDownMenu(nID);
		//
		return 0;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		//if (GetStyle() & TBSTYLE_WRAPABLE)
		{
			AlignControls();
		}
		//
		return lRet;
	}
	virtual int GetRowHeight()
	{
		CSize sz;
		GetButtonSize(sz);
		return sz.cy;
	}

	virtual int GetMinWidth()
	{
		int nCount = GetButtonCount();
		int nWidth = 0;
		for (int i = 0; i < nCount; i++)
		{
			CRect rc;
			GetItemRect(i, rc);
			nWidth += rc.Width();
		}
		return nWidth + 4;
	}
	virtual int GetMinHeight()
	{
		int nCount = GetButtonCount();
		if (0 == nCount)
			return 22;
		//
		CSize sz;
		GetButtonSize(sz);
		return sz.cy * GetRows() + 3;
	}
	virtual int GetHeight()
	{
		CRect rc;
		GetWindowRect(&rc);
		return rc.Height();
	}
	virtual int GetMinHeight(int nMinToolBarHeight)
	{
		int n = GetMinHeight();
		return std::max<int>(n, nMinToolBarHeight);
	}
	virtual int GetMinButtonHeight(int nMinToolBarHeight)
	{
		return ::std::max<int>(WizGetFontHeight(m_hWnd, m_font) + 10, nMinToolBarHeight - 2);
	}
	//
	void AutoArrange()
	{
		int nCount = GetButtonCount();
		if (0 == nCount)
			return;
		//
		int nWidth = GetMinWidth();
		CRect rc;
		GetClientRect(&rc);
		//
		int nMax = rc.Width();
		//
		int nPadding = int(double(nMax - nWidth) / nCount / 2);
		//
		if (nPadding < 0)
			return;
		//
		SetPadding(nPadding, 0);
	}
	//
	void SetButtonExStyle(UINT nID, UINT nExStyle)
	{
		m_mapButtonExStyle[nID] = nExStyle;
		if (IsWindow())
		{
			int nButton = CommandToIndex(nID);
			if (-1 != nButton)
			{
				CRect rcItem;
				GetItemRect(nButton, &rcItem);
				//
				InvalidateRect(&rcItem);
			}
		}
	}
	UINT GetButtonExStyle(UINT nID)
	{
		std::map<UINT, UINT>::const_iterator it = m_mapButtonExStyle.find(nID);
		if (it == m_mapButtonExStyle.end())
			return 0;
		//
		return it->second;
	}
	//
	LRESULT OnToolTipNotify(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*) pNMHDR;
		TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*) pNMHDR;
		
		if (pNMHDR->idFrom)
		{
			CString str = WizFormatString0(UINT(pNMHDR->idFrom));
			if (!str.IsEmpty())
			{
				int nPos = str.Find(_T('\n'));
				if (nPos != -1)
				{
					str.Delete(0, nPos + 1);
				}
				//
	#ifndef _UNICODE
				if (pNMHDR->code == TTN_NEEDTEXTA)
					lstrcpyn(pTTTA->szText, str, _countof(pTTTA->szText));
				else
					_mbstowcsz(pTTTW->szText, str, _countof(pTTTW->szText));
	#else
				if (pNMHDR->code == TTN_NEEDTEXTA)
					_wcstombsz(pTTTA->szText, str, _countof(pTTTA->szText));
				else
					lstrcpyn(pTTTW->szText, str, _countof(pTTTW->szText));
	#endif		
				return 0;
			}
		}
		
		return 0;
	}
	LRESULT OnGetInfoTipNotify(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTBGETINFOTIP * pTB = (NMTBGETINFOTIP *) pNMHDR;
		
		if (pNMHDR->idFrom)
		{
			CString str = WizFormatString0(UINT(pTB->iItem));
			if (!str.IsEmpty() && pTB->pszText && pTB->cchTextMax >= MAX_PATH)
			{
				int nPos = str.Find(_T('\n'));
				if (nPos != -1)
				{
					str.Delete(0, nPos + 1);
				}
				//
				lstrcpyn(pTB->pszText, str, pTB->cchTextMax);
				//
				return 0;
			}
		}
		
		return 0;
	}
	//
	void SetHighlightPos(int nPos)
	{
		m_nHighlightPos = nPos;
		//
		if (IsWindow())
		{
			InvalidateRect(NULL);
		}
	}
	//
	virtual void AutoSetButtonSize(HFONT hFont)
	{
		int nFontHeight = ::WizGetFontHeight(m_hWnd, hFont);
		int nButtonHeight = 30 - 16 + nFontHeight;
		//
		SetButtonSize(30, nButtonHeight);
	}
	virtual void AutoSetButtonSize()
	{
		return AutoSetButtonSize(m_font);
	}
};


class CWizToolBarCtrl 
	: public CWizToolBarCtrlBase<CWizToolBarCtrl>
{
};


class CWizVistaToolBarCtrl 
	: public CWizToolBarCtrlBaseExImpl<CWizVistaToolBarCtrl>
{
public:
	virtual void DrawButtonBackground(CDCHandle dc, int nIndex, BOOL bHot);
	virtual void DrawBackground(CDCHandle dc, const CRect& rc);
};



template<class T, class TSettings>
class CWizWindowState
{
public:
	CWizWindowState(LPCTSTR lpszSection)
		: m_strWindowStateSection(lpszSection)
	{
	}
protected:
	CString m_strWindowStateSection;
public:
	virtual void LoadStatus(BOOL bShowWindow = TRUE)
	{
		if (m_strWindowStateSection.IsEmpty())
			return;
		//
		T* pT = static_cast<T*>(this);
		//
		TSettings settings;
		//
		if (settings.GetBool(m_strWindowStateSection, _T("Maximized"), FALSE))
		{
			if (bShowWindow)
			{
				pT->ShowWindow(SW_SHOWMAXIMIZED);
			}
		}
		else
		{
			CRect rc;
			rc.left = settings.GetInt(m_strWindowStateSection, _T("Left"), 0);
			rc.top = settings.GetInt(m_strWindowStateSection, _T("Top"), 0);
			rc.right = settings.GetInt(m_strWindowStateSection, _T("Right"), 0);
			rc.bottom = settings.GetInt(m_strWindowStateSection, _T("Bottom"), 0);
			if (rc.Width() < 10
				|| rc.Height() < 10)
			{
				if (bShowWindow)
				{
					pT->ShowWindow(SW_SHOWDEFAULT);
				}
			}
			else
			{
				pT->MoveWindow(rc);
				if (bShowWindow)
				{
					pT->ShowWindow(SW_SHOW);
				}
			}
		}
	}
	//
	virtual void SaveStatus()
	{
		if (m_strWindowStateSection.IsEmpty())
			return;
		//
		T* pT = static_cast<T*>(this);
		//
		TSettings settings;
		//
		if (pT->GetStyle() & WS_MAXIMIZE)
		{
			settings.SetBool(m_strWindowStateSection, _T("Maximized"), TRUE);
		}
		else if (pT->GetStyle() & WS_MINIMIZE)
		{
		}
		else
		{
			settings.SetBool(m_strWindowStateSection, _T("Maximized"), FALSE);
			//
			CRect rc;
			pT->GetWindowRect(&rc);
			//
			settings.SetInt(m_strWindowStateSection, _T("Left"), rc.left);
			settings.SetInt(m_strWindowStateSection, _T("Top"), rc.top);
			settings.SetInt(m_strWindowStateSection, _T("Right"), rc.right);
			settings.SetInt(m_strWindowStateSection, _T("Bottom"), rc.bottom);
		}
	}
	//
public:
	//
	BEGIN_MSG_MAP(CWizWindowState)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
	END_MSG_MAP()
	//
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (!m_strWindowStateSection.IsEmpty())
		{
			SaveStatus();
		}
		//
		bHandled = FALSE;
		return 0;
	}
};


class CWizSimpleToolBar : public CWizToolBarCtrlBase<CWizSimpleToolBar>
{
protected:
	CImageList m_il;
public:
	HWND CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON* parrayIcon, UINT nIconCount, UINT nToolBarID);
	HWND CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON hIcon, UINT nToolBarID);
	HWND CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszIconFileName, UINT nToolBarID);
};

class CWizSimpleToggleButton : public CWizSimpleToolBar
{
public:
	BEGIN_MSG_MAP(CWizToolBarCtrlBase)
		REFLECTED_NOTIFY_CODE_HANDLER(NM_CLICK, OnNMClick)
		CHAIN_MSG_MAP(CWizSimpleToolBar)
	END_MSG_MAP()
public:
	//
	HWND CreateToggleButton(HWND hwndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszNormalIconFileName, LPCTSTR lpszDownIconFileName, UINT nToolBarID);
	LRESULT OnNMClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	UINT GetButtonID();
	BOOL IsToggleButton();
	BOOL GetCheck();
	void SetCheck(BOOL b);
	void UpdateStatus();
};

class CWizFlatToolBarCtrl 
	: public CWizToolBarCtrlBaseExImpl<CWizFlatToolBarCtrl >
{
public:
	CWizFlatToolBarCtrl(COLORREF crBackground);
protected:
	COLORREF m_crBackground;
	BOOL m_bDrawShadow;
public:
	virtual void DrawButtonBackground(CDCHandle dc, int nIndex, BOOL bHot);
	virtual void DrawBackground(CDCHandle dc, const CRect& rc);
	void SetDrawShadow(BOOL b);
};


template <class T, class TBase = CButton, class TWinTraits = ATL::CControlWinTraits>
class ATL_NO_VTABLE CWizVistaIconButtonImpl : public ATL::CWindowImpl< T, TBase, TWinTraits>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

	// Bitmap button specific extended styles
	// Internal states
	unsigned m_fMouseOver:1;
	unsigned m_fFocus:1;
	unsigned m_fPressed:1;
	//
	COLORREF m_crBackground;
	//
	BOOL m_b3D;
	//
	BOOL m_bDestroyIcon;
	BOOL m_bDestroyDisabledIcon;
	//
	HICON m_hIcon;
	HICON m_hDisabledIcon;
	//
	int m_nIconWidth;
	int m_nIconHeight;

	// Constructor/Destructor
	CWizVistaIconButtonImpl() 
		: m_fMouseOver(0), m_fFocus(0), m_fPressed(0)
	{
		m_bDestroyIcon = FALSE;
		m_hIcon = NULL;
		//
		m_bDestroyDisabledIcon = FALSE;
		m_hDisabledIcon = NULL;
		//
		m_crBackground = ::GetSysColor(COLOR_BTNFACE);
		//
		m_nIconWidth = 16;
		m_nIconHeight = 16;
		//
		m_b3D = TRUE;
	}

	~CWizVistaIconButtonImpl()
	{
		DestroyButtonIcon();
		DestroyButtonDisabledIcon();
	}
	//
	void DestroyButtonIcon()
	{
		if (m_bDestroyIcon && m_hIcon)
		{
			DestroyIcon(m_hIcon);
			m_hIcon = NULL;
		}
	}
	void DestroyButtonDisabledIcon()
	{
		if (m_bDestroyDisabledIcon && m_hDisabledIcon)
		{
			DestroyIcon(m_hDisabledIcon);
			m_hDisabledIcon = NULL;
		}
	}
	//
	void Set3D(BOOL b)
	{
		m_b3D = b;
	}

	// overridden to provide proper initialization
	BOOL SubclassWindow(HWND hWnd)
	{
#if (_MSC_VER >= 1300)
		BOOL bRet = ATL::CWindowImpl< T, TBase, TWinTraits>::SubclassWindow(hWnd);
#else // !(_MSC_VER >= 1300)
		typedef ATL::CWindowImpl< T, TBase, TWinTraits>   _baseClass;
		BOOL bRet = _baseClass::SubclassWindow(hWnd);
#endif // !(_MSC_VER >= 1300)
		if(bRet)
			OnInitControl();
		return bRet;
	}
	//
	enum WizVistaIconButtonState { stateNormal, stateDisabled, stateHover, stateDown };
	WizVistaIconButtonState GetButtonState()
	{
		if(!IsWindowEnabled())
			return stateDisabled;
		else if(m_fPressed == 1)
			return stateDown;
		else if(m_fMouseOver == 1)
			return stateHover;
		//
		return stateNormal;
	}
	//
	void SetIcon(HICON hIcon, int nWidth = 16, int nHeight = 16)
	{
		m_nIconWidth = nWidth;
		m_nIconHeight = nHeight;
		//
		DestroyButtonIcon();
		//
		m_bDestroyIcon = FALSE;
		m_hIcon = hIcon;
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	void SetIcon(UINT nID, int nWidth = 16, int nHeight = 16)
	{
		m_nIconWidth = nWidth;
		m_nIconHeight = nHeight;
		//
		DestroyButtonIcon();
		//
		m_bDestroyIcon = TRUE;
		m_hIcon = (HICON)::LoadImage(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(nID), 
			IMAGE_ICON, m_nIconWidth, m_nIconHeight, LR_DEFAULTCOLOR);
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	//
	void SetDisabledIcon(HICON hDisabledIcon)
	{
		DestroyButtonDisabledIcon();
		//
		m_bDestroyDisabledIcon = FALSE;
		m_hDisabledIcon = hDisabledIcon;
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	void SetDisabledIcon(UINT nID)
	{
		DestroyButtonDisabledIcon();
		//
		m_bDestroyDisabledIcon = TRUE;
		m_hDisabledIcon = (HICON)::LoadImage(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(nID), 
			IMAGE_ICON, m_nIconWidth, m_nIconHeight, LR_DEFAULTCOLOR);
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	//
	void SetBackgroundColor(COLORREF cr)
	{
		m_crBackground = cr;
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}


	// Attributes
	// Operations
	// Overrideables
	void DoPaint(CDCHandle dc)
	{
		WizVistaIconButtonState state = GetButtonState();
		//
		CRect rect;
		GetClientRect(&rect);
		//
		BOOL bEnabled = IsWindowEnabled();
		//
		if (m_b3D && bEnabled && (stateHover == state || stateDown == state))
		{
			if (stateHover == state)
			{
				DrawBackground(dc, TRUE, rect);
			}
			else
			{
				DrawBackground(dc, FALSE, rect);
			}
		}
		else
		{
			dc.FillSolidRect(&rect, m_crBackground);
		}
		//
		int x = rect.left + (rect.Width() - m_nIconWidth) / 2;
		int y = rect.top + (rect.Height() - m_nIconHeight) / 2;
		
		//
		HICON hIcon = m_hIcon;
		if (!bEnabled && m_hDisabledIcon)
		{
			hIcon = m_hDisabledIcon;
		}
		//
		if (hIcon)
		{
			dc.DrawIconEx(x, y, hIcon, m_nIconWidth, m_nIconHeight, 0, 0, DI_NORMAL);
		}
	}

// Message map and handlers
	BEGIN_MSG_MAP(CWizVistaIconButtonImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnFocus)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
		MESSAGE_HANDLER(WM_ENABLE, OnEnable)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_UPDATEUISTATE, OnUpdateUiState)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		OnInitControl();
		//
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 1;   // no background needed
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		if(wParam != NULL)
		{
			pT->DoPaint((HDC)wParam);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			pT->DoPaint(dc.m_hDC);
		}
		return 0;
	}

	LRESULT OnFocus(UINT uMsg, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_fFocus = (uMsg == WM_SETFOCUS) ? 1 : 0;
		Invalidate();
		UpdateWindow();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		if(IsHoverMode())
			SetCapture();
		else
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() == m_hWnd)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		return lRet;
	}

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		if(!IsHoverMode())
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() != m_hWnd)
			SetCapture();
		if(m_fPressed == 0)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		return lRet;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		bool bHover = IsHoverMode();
		if(!bHover)
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() == m_hWnd)
		{
			if(bHover && m_fPressed == 1)
				::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
			::ReleaseCapture();
		}
		return lRet;
	}

	LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(m_fPressed == 1)
		{
			m_fPressed = 0;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnEnable(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		Invalidate();
		UpdateWindow();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		if(::GetCapture() == m_hWnd)
		{
			POINT ptCursor = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			ClientToScreen(&ptCursor);
			RECT rect = { 0 };
			GetWindowRect(&rect);
			unsigned int uPressed = ::PtInRect(&rect, ptCursor) ? 1 : 0;
			if(m_fPressed != uPressed)
			{
				m_fPressed = uPressed;
				Invalidate();
				UpdateWindow();
			}
		}
		else if(IsHoverMode() && m_fMouseOver == 0)
		{
			m_fMouseOver = 1;
			Invalidate();
			UpdateWindow();
			StartTrackMouseLeave();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(m_fMouseOver == 1)
		{
			m_fMouseOver = 0;
			Invalidate();
			UpdateWindow();
		}
		return 0;
	}

	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(wParam == VK_SPACE && IsHoverMode())
			return 0;   // ignore if in hover mode
		if(wParam == VK_SPACE && m_fPressed == 0)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(wParam == VK_SPACE && IsHoverMode())
			return 0;   // ignore if in hover mode
		if(wParam == VK_SPACE && m_fPressed == 1)
		{
			m_fPressed = 0;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnUpdateUiState(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// If the control is subclassed or superclassed, this message can cause
		// repainting without WM_PAINT. We don't use this state, so just do nothing.
		return 0;
	}

	// Implementation
	virtual void OnInitControl()
	{
		// We need this style to prevent Windows from painting the button
		ModifyStyle(0, BS_OWNERDRAW);

		// create a tool tip
	}

	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}

	bool IsHoverMode() const
	{
		return true;
	}
	//
	void DrawBackground(CDCHandle dc, BOOL bHot, const RECT& rcBorder)
	{
		if (bHot)
		{
			COLORREF crOuter = WizColorDarker(m_crBackground, 0.7f);
			COLORREF crInner = WizColorDarker(m_crBackground, 0.9f);
			//
			dc.FillSolidRect(&rcBorder, WizColorLighter(m_crBackground, 1.03f));
			//
			dc.SelectStockBrush(NULL_BRUSH);
			//
			CPen penInner;
			penInner.CreatePen(PS_SOLID, 1, crInner);
			CRect rcInner = rcBorder;
			rcInner.right--;
			rcInner.bottom--;
			dc.SelectPen(penInner);
			dc.RoundRect(rcInner, CPoint(2, 2));
			//			
			CPen penOuter;
			penOuter.CreatePen(PS_SOLID, 1, crOuter);
			CRect rcOuter = rcBorder;
			dc.RoundRect(rcOuter, CPoint(2, 2));
		}
		else
		{
			COLORREF crOuter = WizColorDarker(m_crBackground, 0.7f);
			COLORREF crInner = WizColorDarker(m_crBackground, 0.9f);
			//
			dc.FillSolidRect(&rcBorder, WizColorDarker(m_crBackground, 0.95f));
			//
			dc.SelectStockBrush(NULL_BRUSH);
			//
			CPen penInner;
			penInner.CreatePen(PS_SOLID, 1, crInner);
			CRect rcInner = rcBorder;
			rcInner.left++;
			rcInner.top++;
			dc.SelectPen(penInner);
			dc.RoundRect(rcInner, CPoint(2, 2));
			//			
			CPen penOuter;
			penOuter.CreatePen(PS_SOLID, 1, crOuter);
			CRect rcOuter = rcBorder;
			dc.RoundRect(rcOuter, CPoint(2, 2));
		}

	}
};


class CWizVistaIconButton : public CWizVistaIconButtonImpl<CWizVistaIconButton>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WizVistaIconButton"), GetWndClassName())

	CWizVistaIconButton() 
	{
	}
};



class CWizFontComboBox 
	: public CWindowImpl<CWizFontComboBox, CComboBox>
{	
public:	
	CWizFontComboBox() 
	{
		m_cyItem = -1;
	}


	BEGIN_MSG_MAP(CWizFontComboBox)
		MESSAGE_HANDLER(WM_CREATE, OnCreate);
		MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem);
		MESSAGE_HANDLER(OCM_MEASUREITEM, OnMeasureItem);
	END_MSG_MAP()

	static DWORD GetWndStyle(DWORD dwStyle)
	{
		if (0 == dwStyle)
		{
			return WS_CHILD|WS_VSCROLL|WS_TABSTOP|WS_VISIBLE|CBS_DROPDOWN|CBS_OWNERDRAWFIXED|CBS_HASSTRINGS | CBS_SORT;
		}
		else
		{
			return dwStyle;
		}
	}
	const TCHAR* GetSelFontName()
	{
		static TCHAR szFaceName[LF_FACESIZE];		
		GetLBText(GetCurSel(), szFaceName);
		return szFaceName;
	}

	int SetSelFont (CHARFORMAT& cf)
	{
		return SelectString(-1, cf.szFaceName);
	}

	int SetSelFont (CHARFORMAT2& cf)
	{
		return SelectString(-1, cf.szFaceName);
	}

protected:
	//CImageList m_img;	
	int m_cyItem;
	
	enum 
	{
		ITEM_DEFAULT_HEIGHT = 15,
			GLYPH_WIDTH = 0
	};

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		Init();
		//
		return lRet;
	}

	LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		DRAWITEMSTRUCT *lpDIS = reinterpret_cast<DRAWITEMSTRUCT *>(lParam);

		ATLASSERT(lpDIS->CtlType == ODT_COMBOBOX); 
	
		CDCHandle dc = lpDIS->hDC;		
		RECT rc = lpDIS->rcItem;
	
		if (lpDIS->itemState & ODS_FOCUS)
			dc.DrawFocusRect(&rc);
			
		int nIndexDC = dc.SaveDC();

		CBrush br;
		
		if (lpDIS->itemState & ODS_SELECTED)
		{
			br.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			br.CreateSolidBrush(dc.GetBkColor());
		}

		dc.SetBkMode(TRANSPARENT);
		dc.FillRect(&rc, br);
		
		//DWORD dwData = GetItemData(lpDIS->itemID);

		int nLen = GetLBTextLen(lpDIS->itemID);
		TCHAR* psFont = (TCHAR *)_alloca(sizeof TCHAR * (nLen + 1));
		GetLBText(lpDIS->itemID, psFont);
		
		//if (dwData & TRUETYPE_FONTTYPE)
		//	m_img.Draw(dc, 0, rc.left, rc.top,ILD_TRANSPARENT);
	
		rc.left += GLYPH_WIDTH + 2;
		dc.TextOut(rc.left, rc.top, psFont);

		dc.RestoreDC(nIndexDC);
		return 0;
	}

	LRESULT OnMeasureItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		MEASUREITEMSTRUCT* pmis = reinterpret_cast<MEASUREITEMSTRUCT*>(lParam);
		ATLASSERT(pmis->CtlType == ODT_COMBOBOX);

		if (m_cyItem == -1)
		{
			// calculate height
			CClientDC dc(m_hWnd);
			HFONT hFont = ((HFONT)GetStockObject( DEFAULT_GUI_FONT ));
			dc.SelectFont( hFont ); //GetFont()
			TEXTMETRIC tm;
			dc.GetTextMetrics(&tm); 

			m_cyItem = tm.tmHeight + tm.tmInternalLeading;
		}

		pmis->itemHeight = m_cyItem;
		return TRUE;			
	}


	void Init ()
	{		
		HFONT hFont = ((HFONT)GetStockObject( DEFAULT_GUI_FONT ));
		SetFont(hFont);

		//m_img.CreateFromImage(IDB_TRUETYPE_FONTTYPE, GLYPH_WIDTH, 1, RGB(255,255,255), IMAGE_BITMAP);
		CClientDC dc(m_hWnd);		

		EnumFonts (dc, 0,(FONTENUMPROC) EnumFontProc,(LPARAM)this); //Enumerate font
	}


	static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC /*lptm*/, DWORD dwType, LPARAM lpData)	
	{	
		CWizFontComboBox *pThis = reinterpret_cast<CWizFontComboBox*>(lpData);		
		int index = pThis->AddString(lplf->lfFaceName);
		pThis->SetItemData (index, dwType); 
		return TRUE;
	}

};


class CWizFontPreviewComboBox 
	: public CWizFontComboBox
{	

public:	
	CWizFontPreviewComboBox() { }

	BEGIN_MSG_MAP(CWizFontPreviewComboBox)
		MESSAGE_HANDLER(WM_CREATE, OnCreate);
		MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem);
		MESSAGE_HANDLER(OCM_MEASUREITEM, OnMeasureItem);
		CHAIN_MSG_MAP(CWizFontComboBox)	
	END_MSG_MAP()


protected:

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = CWizFontComboBox::OnCreate(uMsg, wParam, lParam, bHandled);
		
		SetDroppedWidth(300);
		
		return lRet;
	}

	LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		DRAWITEMSTRUCT *lpDIS = reinterpret_cast<DRAWITEMSTRUCT *>(lParam);

		ATLASSERT(lpDIS->CtlType == ODT_COMBOBOX); 
	
		CDCHandle dc = lpDIS->hDC;		
		RECT rc = lpDIS->rcItem;
	

		if (lpDIS->itemState & ODS_FOCUS)
			dc.DrawFocusRect(&rc);
			
		int nIndexDC = dc.SaveDC();

		CBrush br;
		
		if (lpDIS->itemState & ODS_SELECTED)
		{
			br.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			br.CreateSolidBrush(dc.GetBkColor());
		}

		dc.SetBkMode(TRANSPARENT);
		dc.FillRect(&rc, br);
		

		int nLen = GetLBTextLen(lpDIS->itemID);
		TCHAR* psFont = (TCHAR *)_alloca(sizeof TCHAR * (nLen + 1));
		GetLBText(lpDIS->itemID, psFont);
		
		//DWORD dwData = GetItemData(lpDIS->itemID);

		//if (dwData & TRUETYPE_FONTTYPE)
		//	m_img.Draw(dc, 0, rc.left+5, rc.top+4,ILD_TRANSPARENT);
	
		rc.left += GLYPH_WIDTH + 2;

		CFont cf;

		cf.CreateFont(20,0,0,0,FW_NORMAL,FALSE, FALSE, FALSE,DEFAULT_CHARSET ,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,psFont);
		HFONT hf = dc.SelectFont(cf);
		dc.TextOut(rc.left+8, rc.top, psFont);
		dc.SelectFont(hf);

		dc.RestoreDC(nIndexDC);
		return 0;
	}

	LRESULT OnMeasureItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		MEASUREITEMSTRUCT* pmis = reinterpret_cast<MEASUREITEMSTRUCT*>(lParam);
		ATLASSERT(pmis->CtlType == ODT_COMBOBOX);

		if (m_cyItem == -1)
		{
			// calculate height
			m_cyItem = WizGetFontHeight(m_hWnd) + 1;
		}
		else
		{
			m_cyItem = 20;
		}
		//
		pmis->itemHeight = m_cyItem;
		return TRUE;			
	}
};


#define WIZ_ALIGN_BOTTOM	0
#define WIZ_ALIGN_TOP		1
#define WIZ_ALIGN_LEFT		2
#define WIZ_ALIGN_RIGHT		3

int WizGetTaskBarHeight(int& nAlign);
void WizSetInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex, HWND hWnd);
BOOL WizIsInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex);
RECT WizGetInfoWindowRect(HWND hwnd, LPCTSTR lpszRegKey, int& nInfoWndIndex);



const UINT WIZ_WM_UM_LISTCTRL_CHECK_SELCHANGED = ::RegisterWindowMessage(_T("WizListCtrlCheckSelChanged"));

#ifdef __ATLCTRLX_H__

template <class T>
class CWizAtlListCtrlBase 
	: public CSortListViewCtrlImpl<T> 
	, public CDoubleBufferImpl<T >

{
public:
	CWizAtlListCtrlBase()
	{
#ifdef WINCE
		m_penBottomLine.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNFACE));
#endif
		m_nCommandItem = -1;
		m_bLeftButtonClicking = FALSE;
		m_bRightButtonClicking = FALSE;
		m_bSorting = FALSE;
		//
		WizCreateUIFont(m_font, FALSE);
		WizCreateUIFont(m_fontBold, TRUE);
	}
	//
	typedef CSortListViewCtrlImpl<T>  _baseClass1;
	typedef CDoubleBufferImpl<T> _baseClass2;
protected:
#ifdef WINCE
	CPen m_penBottomLine;
#endif
	//
	BOOL m_bSorting;
	int m_nCommandItem;
	//
	BOOL m_bLeftButtonClicking;
	BOOL m_bRightButtonClicking;
	//
	CImageList m_ilAdjustItemHeight;
	CFont m_font;
	CFont m_fontBold;
public:
	BEGIN_MSG_MAP(CWizAtlListCtrlBase)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		REFLECTED_NOTIFY_CODE_HANDLER(LVN_DELETEITEM, OnDeleteItem)
		REFLECTED_NOTIFY_CODE_HANDLER(LVN_ITEMCHANGING, OnItemChanging)
		CHAIN_MSG_MAP(_baseClass1)
		CHAIN_MSG_MAP(_baseClass2)
	END_MSG_MAP()
public:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		OnInitControl();
		//
		return lRet;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		OnDestroyControl();
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bRightButtonClicking = TRUE;
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		m_bRightButtonClicking = FALSE;
		Invalidate();
		//
		return lRet;
	}
	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bRightButtonClicking = FALSE;
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLeftButtonClicking = TRUE;
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLeftButtonClicking = FALSE;
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		GetParent().PostMessage(WIZ_WM_UM_LISTCTRL_CHECK_SELCHANGED, 0, 0);
		//
		return lRet;
	}
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		GetParent().PostMessage(WIZ_WM_UM_LISTCTRL_CHECK_SELCHANGED, 0, 0);
		//
		return lRet;
	}
	
	LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		UINT xPos = GET_X_LPARAM(lParam); 
		UINT yPos = GET_Y_LPARAM(lParam); 
		//
		CPoint pt(xPos, yPos);
		ScreenToClient(&pt);
		//
		UINT nFlags = 0;
		m_nCommandItem = HitTest(pt, &nFlags);
		//
		ShowMenu(m_nCommandItem, xPos, yPos);
		//
		InvalidateItem(m_nCommandItem);
		UpdateWindow();
		m_nCommandItem = -1;
		//
		return 0;
	}
	LRESULT OnDeleteItem(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMLISTVIEW* pNMListView = (NMLISTVIEW *)pNMHDR;
		//
		OnDeleteItemData(pNMListView->lParam);
		pNMListView->lParam = 0;
		//
		return TRUE;
	}
	LRESULT OnItemChanging(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMLISTVIEW* pNMListView = (NMLISTVIEW *)pNMHDR;
		//
		if (0 == pNMListView->iItem)
		{
			InvalidateItem(0);
		}
		//
		return FALSE;
	}
	void InvalidateItem(int nItem)
	{
		CRect rcItem;
		GetItemRect(nItem, &rcItem, LVIR_BOUNDS);
		//
		InvalidateRect(&rcItem);
	}
	int GetColumnCount()
	{
		CHeaderCtrl header = GetHeader();
		return header.GetItemCount();
	}
public:
	virtual void OnDeleteItemData(LPARAM lParam)
	{
	}
	virtual BOOL OnInitControl()
	{
		SetExtendedListViewStyle(LVS_EX_FULLROWSELECT );
		//
		ResetItemHeight();
		//
		return TRUE;
	}
	//
	virtual BOOL OnDestroyControl()
	{
		return TRUE;
	}
	virtual int CalItemHeight()
	{
		return 16;
	}
	virtual void ResetItemHeight()
	{
		SetItemHeight(CalItemHeight());
	}
	virtual HMENU GetContextMenu()
	{
		return NULL;
	}
	virtual void OnUpdateContextMenu(int nFocusedItem, HMENU hMenu)
	{
	}
	//
	void DoPaint( CDCHandle dcPaint )
	{
		int nColumnCount = GetColumnCount();
		//
		DefWindowProc( WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC, 0 );
		if (0 == nColumnCount)
		{
			DefWindowProc( WM_PAINT, (WPARAM)dcPaint.m_hDC, 0 );
			return;
		}
		//
		if (IsSorting())
			return;
		//
		int nDC = dcPaint.SaveDC();
		//
		dcPaint.SelectFont(m_font);
		//
		int nItemCount = GetItemCount();
		//
		int xPos = GetScrollPos(SB_HORZ);
		int nFirstColumnWidth = GetColumnWidth(0);
		//
		CHeaderCtrl header = GetHeader();
		std::vector<UINT> arrayColumnFlags(nColumnCount, 0);
		for (int i = 0; i < nColumnCount; i++)
		{
			HDITEM item;
			item.mask = HDI_FORMAT;
			header.GetItem(i, &item);
			arrayColumnFlags[i] = item.fmt;
		}
		//
		HIMAGELIST hImageListLarge = GetImageList(LVSIL_NORMAL);
		HIMAGELIST hImageListSmall = GetImageList(LVSIL_SMALL);
		//
		DWORD dwView = GetView();
		//
		int nFirst = GetTopIndex();
		if (nFirst < 0)
			nFirst = 0;
		int nLast = nFirst + GetCountPerPage() + 1;
		//
		CRect rcUpdate;
		dcPaint.GetClipBox(&rcUpdate);
		//
		ATLTRACE(_T("Update Rect: left=%d, top=%d, width=%d, height=%d\n"), rcUpdate.left, rcUpdate.top, rcUpdate.Width(), rcUpdate.Height());
		//
		if (!rcUpdate.IsRectEmpty())
		{
			int nItem = HitTest(rcUpdate.TopLeft(), NULL);
			if (nItem >= 0)
				nFirst = nItem;
			//
			nLast = nFirst + rcUpdate.Height() / CalItemHeight() + 2;
		}
		//
		for (int iItem = nFirst; iItem <= nLast && iItem < nItemCount; iItem++)
		{
			DWORD_PTR dwData = GetItemData(iItem);
			//
			CRect rcItem;
			GetItemRect(iItem, &rcItem, LVIR_BOUNDS);
			CRect rcIcon;
			GetItemRect(iItem, &rcIcon, LVIR_ICON);
			//
			UINT nItemState = GetItemState(iItem, LVIS_SELECTED | LVIS_FOCUSED);
			DrawBackground(dcPaint, iItem, nItemState, rcItem, dwData);
			//
			if (LVS_REPORT == dwView)
			{
				for (int iSubItem = 0; iSubItem < nColumnCount; iSubItem++)
				{
					CRect rcSubItem;
					GetSubItemRect(iItem, iSubItem, LVIR_BOUNDS, &rcSubItem);
					//
					if (0 == iSubItem)
					{
						rcSubItem.right = nFirstColumnWidth - xPos;
						//
						if (hImageListSmall && hImageListSmall != m_ilAdjustItemHeight)
						{
							DrawItemIcon(dcPaint, hImageListSmall, iItem, rcIcon);
							rcSubItem.left = rcIcon.right + 2;
						}
					}
					//
					DrawSubItemText(dcPaint, iItem, iSubItem, nItemState, rcSubItem, arrayColumnFlags[iSubItem], dwData);
				}
			}
			else
			{
				if (hImageListLarge && LVS_ICON == dwView)
				{
					DrawItemIcon(dcPaint, hImageListLarge, iItem, rcIcon);
				}
				else if (hImageListSmall && (LVS_SMALLICON == dwView || LVS_LIST == dwView))
				{
					DrawItemIcon(dcPaint, hImageListSmall, iItem, rcIcon);
				}
				//
				CRect rcSubItem;
				GetItemRect(iItem, &rcSubItem, LVIR_LABEL);
				//
				DrawSubItemText(dcPaint, iItem, 0, nItemState, rcSubItem, LVCFMT_LEFT, dwData);
			}
		}
		//
		dcPaint.RestoreDC(nDC);
	}
	virtual void DrawBackground(CDCHandle dc, int nItem, UINT nItemState, CRect& rcItem, DWORD_PTR dwData)
	{
		BOOL bSelected = (nItemState & LVIS_SELECTED) == LVIS_SELECTED;
		BOOL bFocus = (nItemState & LVIS_FOCUSED) == LVIS_FOCUSED;
		//
		if (bSelected)
		{
			static COLORREF crSelected = GetItemBackgroundColor(nItem, nItemState, dwData);
			dc.FillSolidRect(&rcItem, crSelected);
		}
		//
		if (bFocus)
		{
			CRect rcFocusedItem = rcItem;
			rcFocusedItem.DeflateRect(1, 1);
			dc.DrawFocusRect(&rcFocusedItem);
		}
#ifdef WINCE
		dc.SelectPen(m_penBottomLine);
		dc.MoveTo(rcItem.left, rcItem.bottom - 1);
		dc.LineTo(rcItem.right, rcItem.bottom - 1);
#endif
	}
	virtual void DrawItemIcon(CDCHandle dc, HIMAGELIST hImageList, int nItem, CRect& rcIcon)
	{
		int cx = 0;
		int cy = 0;
		ImageList_GetIconSize(hImageList, &cx, &cy);
		//
		CPoint pt = rcIcon.CenterPoint();
		//
		ImageList_Draw(hImageList, GetItemImage(nItem), dc, pt.x - cx / 2, pt.y - cy / 2, ILD_TRANSPARENT );
	}
	//
	virtual void DrawSubItemText(CDCHandle dc, int nItem, int nSubItem, UINT nItemState, CRect& rcSubItem, UINT nColumnFormat, DWORD_PTR dwData)
	{
		if (IsTextBold(nItem, nSubItem, dwData))
		{
			dc.SelectFont(m_fontBold);
		}
		else
		{
			dc.SelectFont(m_font);
		}
		//
		CString strText;
		GetItemText(nItem, nSubItem, strText);
		//
		CRect rcText = rcSubItem;
		rcText.DeflateRect(4, 2);
		//
		dc.SetTextColor(GetItemTextColor(nItem, nSubItem, nItemState, dwData));
		//
		UINT nTextAlign = DT_LEFT;
		if (nColumnFormat & HDF_RIGHT)
			nTextAlign = DT_RIGHT;
		else if (nColumnFormat & HDF_CENTER)
			nTextAlign = DT_CENTER;
		//
		DWORD dwFlags = DT_END_ELLIPSIS | nTextAlign;
		if (LVS_ICON != GetView())
		{
			dwFlags |= DT_VCENTER | DT_SINGLELINE;
		}
		else
		{
			dwFlags |= DT_WORDBREAK | DT_EDITCONTROL;
		}
		//
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(strText, -1, &rcText, dwFlags); 
	}
	virtual COLORREF GetItemTextColor(int nItem, int nSubItem, UINT nItemState, DWORD_PTR dwData)
	{
		BOOL bSelected = (nItemState & LVIS_SELECTED) == LVIS_SELECTED;
		if (bSelected)
		{
			static COLORREF crBackground = GetSysColor(COLOR_HIGHLIGHTTEXT);
			return crBackground;
		}
		else
		{
			static COLORREF crBackground = GetSysColor(COLOR_WINDOWTEXT);
			return crBackground;
		}
	}
	virtual COLORREF GetItemBackgroundColor(int nItem, UINT nItemState, DWORD_PTR dwData)
	{
		BOOL bSelected = (nItemState & LVIS_SELECTED) == LVIS_SELECTED;
		if (bSelected)
		{
			static COLORREF crBackground = GetSysColor(COLOR_HIGHLIGHT);
			return crBackground;
		}
		else
		{
			static COLORREF crBackground = GetSysColor(COLOR_WINDOW);
			return crBackground;
		}
	}
	virtual BOOL IsTextBold(int nItem, int nSubItem, DWORD_PTR dwData)
	{
		return FALSE;
	}
public:
	BOOL IsLeftButtonClicking() const
	{
		return m_bLeftButtonClicking;
	}
	BOOL IsRightButtonClicking() const
	{
		return m_bRightButtonClicking;
	}
	//
	int CompareItemsCustom(LVCompareParam* pItem1, LVCompareParam* pItem2, int iSortCol)
	{
		return CustomCompareItem(pItem1, pItem2, iSortCol);
	}
	virtual int CustomCompareItem(LVCompareParam* pItem1, LVCompareParam* pItem2, int iSortCol)
	{
		return 0;
	}
protected:
	void ShowMenu(int nCommandItem, int x, int y)
	{
		CMenuHandle menu = GetContextMenu();
		if (!menu.m_hMenu)
			return;
		//
		OnUpdateContextMenu(nCommandItem, menu);
		//
		UINT nCmd = menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD, x, y, m_hWnd);
		//
		if (nCmd)
		{
			SendMessage(WM_COMMAND, MAKEWPARAM(nCmd, 0), 0);
		}
	}
public:
	void SetSingleSelectedItem(int nItem)
	{
		m_bRightButtonClicking = TRUE;
		//
		std::vector<int> arrayItem;
		GetSelectedItems(arrayItem);
		for (std::vector<int>::const_iterator it = arrayItem.begin();
			it != arrayItem.end();
			it++)
		{
			SetItemState(*it, 0, LVIS_SELECTED);
		}
		//
		m_bRightButtonClicking = FALSE;
		//
		SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
	void GetSelectedItems(std::vector<int>& arrayItem)
	{
		arrayItem.clear();
		//
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			arrayItem.push_back(nItem);
		}
	}
	//
	void GetCommandItems(std::vector<int>& arrayItem)
	{
		arrayItem.clear();
		//
		if (m_nCommandItem != -1 && GetItemState(m_nCommandItem, LVIS_SELECTED) == 0)
		{
			//not a selected item
			arrayItem.push_back(m_nCommandItem);
		}
		else
		{
			GetSelectedItems(arrayItem);
		}		
	}
	int GetFirstSelectedItem()
	{
		POSITION pos = GetFirstSelectedItemPosition();
		if (!pos)
			return -1;
		//
		return GetNextSelectedItem(pos);
	}
	int GetFirstCommandItem()
	{
		if (m_nCommandItem != -1 && GetItemState(m_nCommandItem, LVIS_SELECTED) == 0)
		{
			//not a selected item
			return m_nCommandItem;
		}
		else
		{
			return GetFirstSelectedItem();
		}
	}
	int GetCommandItemCount()
	{
		if (m_nCommandItem != -1 && GetItemState(m_nCommandItem, LVIS_SELECTED) == 0)
		{
			//not a selected item
			return 1;
		}
		else
		{
			return GetSelectedCount();
		}		
	}

	POSITION GetFirstSelectedItemPosition()
	{
		ATLASSERT(::IsWindow(m_hWnd)); 
		return (POSITION)(DWORD_PTR)(1+GetNextItem(-1, LVIS_SELECTED));
	}
	int GetNextSelectedItem(POSITION& pos) const
	{
		ATLASSERT(::IsWindow(m_hWnd)); 
		DWORD_PTR nOldPos = (DWORD_PTR)pos-1; 
		pos = (POSITION)(DWORD_PTR)(1+GetNextItem((UINT)nOldPos, LVIS_SELECTED)); 
		return (UINT)nOldPos;
	}
	//
	void SetItemHeight(int nHeight)
	{
		SetImageList(NULL, LVSIL_SMALL);
		//
		if (m_ilAdjustItemHeight.m_hImageList)
		{
			m_ilAdjustItemHeight.Destroy();
		}
		//
		m_ilAdjustItemHeight.Create(16, nHeight, ILC_COLOR32 | ILC_MASK, 2, 2);

		CBitmap bmp;
		//
		CDC dcMem;
		CClientDC dc(::GetDesktopWindow());
		dcMem.CreateCompatibleDC(dc.m_hDC);
		bmp.CreateCompatibleBitmap(dc.m_hDC, 16, nHeight);
		dcMem.DeleteDC();
		//
		m_ilAdjustItemHeight.Add(bmp, RGB(0, 0, 0));
		//
		SetImageList(m_ilAdjustItemHeight, LVSIL_SMALL);
	}
	int InsertItemWithData(int nItem, LPCTSTR lpszItem, LPARAM dwData)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return InsertItem(LVIF_TEXT|LVIF_PARAM, nItem, lpszItem, 0, 0, 0, dwData);
	}
	int InsertItemWithData(int nItem, LPCTSTR lpszItem, LPARAM dwData, int nImage)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return InsertItem(LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, dwData);
	}
	//
	void DeleteCommandItems()
	{
		std::vector<int> arrayItem;
		GetCommandItems(arrayItem);
		size_t nCount = arrayItem.size();
		for (intptr_t i = nCount - 1; i >= 0; i--)
		{
			DeleteItem(arrayItem[i]);
		}
	}
	void DeleteSelectedItems()
	{
		std::vector<int> arrayItem;
		GetSelectedItems(arrayItem);
		size_t nCount = arrayItem.size();
		for (intptr_t i = nCount - 1; i >= 0; i--)
		{
			DeleteItem(arrayItem[i]);
		}
	}
	//
	void SetItemImage(int nItem, int nImage)
	{
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.iItem = nItem;
		item.mask = LVIF_IMAGE;
		item.iImage = nImage;
		SetItem(&item);
	}
	int GetItemImage(int nItem)
	{
		LVITEM item;
		ZeroMemory(&item, sizeof(LVITEM));
		item.iItem = nItem;
		item.mask = LVIF_IMAGE;
		GetItem(&item);
		//
		return item.iImage;
	}
	CString GetItemTextEx(int nItem, int nSubItem)
	{
		CString str;
		GetItemText(nItem, nSubItem, str);
		return str;
	}
	BOOL SwapItem(int nItem1, int nItem2)
	{
		m_bSorting = TRUE;
		//
		try
		{
			ATLASSERT(nItem1 >= 0);
			ATLASSERT(nItem2 >= 0);
			ATLASSERT(nItem1 < GetItemCount());
			ATLASSERT(nItem2 < GetItemCount());
			ATLASSERT(nItem1 != nItem2);
			//
			UINT nStateMask = LVIS_CUT | LVIS_DROPHILITED | LVIS_FOCUSED | LVIS_SELECTED;
			//
			int nCount = GetColumnCount();
			//
			DWORD_PTR dwData1 = GetItemData(nItem1);
			int nImage1 = GetItemImage(nItem1);
			UINT nState1 = GetItemState(nItem1, nStateMask);
			CWizStdStringArray arrayText1;
			for (int i = 0; i < nCount; i++)
			{
				arrayText1.push_back(GetItemTextEx(nItem1, i));
			}
			//
			DWORD_PTR dwData2 = GetItemData(nItem2);
			int nImage2 = GetItemImage(nItem2);
			UINT nState2 = GetItemState(nItem2, nStateMask);
			CWizStdStringArray arrayText2;
			for (int i = 0; i < nCount; i++)
			{
				arrayText2.push_back(GetItemTextEx(nItem2, i));
			}
			//
			SetItemData(nItem1, dwData2);
			SetItemImage(nItem1, nImage2);
			SetItemState(nItem1, nState2, nStateMask);
			for (int i = 0; i < nCount; i++)
			{
				SetItemText(nItem1, i, arrayText2[i]);
			}
			//
			SetItemData(nItem2, dwData1);
			SetItemImage(nItem2, nImage1);
			SetItemState(nItem2, nState1, nStateMask);
			for (int i = 0; i < nCount; i++)
			{
				SetItemText(nItem2, i, arrayText1[i]);
			}
		}
		catch (...)
		{
		}
		//
		m_bSorting = FALSE;
		//
		return TRUE;
	}
	void ClearAllSelected()
	{
		std::vector<int> arrayItem;
		GetSelectedItems(arrayItem);
		for (std::vector<int>::const_iterator it = arrayItem.begin();
			it != arrayItem.end();
			it++)
		{
			SetItemState(*it, 0, LVIS_SELECTED);
		}
	}
	//
	bool SortItems(int iCol, bool bDescending = false)
	{
		CWizWindowLocker locker(m_hWnd);
		//
		bool bRet = false;
		//
		m_bSorting = TRUE;
		try
		{
			bRet = DoSortItems(iCol, bDescending);
		}
		catch (...)
		{
		}
		m_bSorting = FALSE;
		//
		return bRet;
	}
	BOOL IsSorting() const
	{
		return m_bSorting;
	}
};




template <class T>
class CWizListCtrlImpl 
	: public CWizAtlListCtrlBase<T>
{
public:
	typedef CWizAtlListCtrlBase<T> _baseClass;
	//
	DECLARE_WND_SUPERCLASS(NULL, _baseClass::GetWndClassName())
public:
	CWizListCtrlImpl(void)
	{
	}
public:
	BEGIN_MSG_MAP(CWizListCtrlImpl)
		CHAIN_MSG_MAP(CWizAtlListCtrlBase<T>)
		CHAIN_MSG_MAP(_baseClass)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
public:
	BOOL SubclassWindow(HWND hWnd)
	{
		return _baseClass::SubclassWindow( hWnd ) ? OnInitControl() : FALSE;
	}
public:
};


class CWizListCtrl : public CWizListCtrlImpl<CWizListCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_ListCtrl"), GetWndClassName())
};



template <class T>
class CWizVistaListCtrlImpl 
	: public CWizAtlListCtrlBase<T>
{
public:
	typedef CWizAtlListCtrlBase<T> _baseClass;
	DECLARE_WND_SUPERCLASS(NULL, _baseClass::GetWndClassName())
public:
	CWizVistaListCtrlImpl(void)
	{
	}
public:
	BEGIN_MSG_MAP(CWizVistaListCtrlImpl)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		CHAIN_MSG_MAP(_baseClass)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
protected:
public:
	static DWORD GetWndExStyle(DWORD dwExStyle)
	{
		return dwExStyle;
	}
	BOOL SubclassWindow(HWND hWnd)
	{
		return _baseClass::SubclassWindow( hWnd ) ? OnInitControl() : FALSE;
	}
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		Invalidate();
		//
		return lRet;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		Invalidate();
		//
		return lRet;
	}
protected:
	virtual void DrawBackground(CDCHandle dc, int nItem, UINT nItemState, CRect& rcItem, DWORD_PTR dwData)
	{
		BOOL bSelected = (nItemState & LVIS_SELECTED) == LVIS_SELECTED;
		BOOL bFocus = (nItemState & LVIS_FOCUSED) == LVIS_FOCUSED;
		//
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		//
		//BOOL bHot = rcItem.PtInRect(pt);
		BOOL bHot = FALSE;
		//
		UINT nState = 0;
		if (bSelected)
		{
			nState |= wizStateSelected;
		}
		if (bHot)
		{
			nState |= wizStateHot;
		}
		if (bFocus)
		{
			nState |= wizStateFocused;
		}

		WizDrawItemBackground(m_hWnd, dc, rcItem, nState, GetItemBackgroundColor(nItem, nItemState, dwData));
	}
	virtual COLORREF GetItemTextColor(int nItem, int nSubItem, UINT nItemState, DWORD_PTR dwData)
	{
		static COLORREF cr = GetSysColor(COLOR_WINDOWTEXT);
		return cr;
	}
	virtual BOOL OnInitControl()
	{
		SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT | LVS_EX_UNDERLINECOLD );
		//
		ResetItemHeight();
		//
		return TRUE;
	}
};


class CWizVistaListCtrl : public CWizVistaListCtrlImpl<CWizVistaListCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_ListCtrl"), GetWndClassName())
	//
	enum
	{
		m_cchCmpTextMax = 1024, // overrideable
	};
};

#endif	//__ATLCTRLX_H__



const UINT WIZ_UM_TASKPANELITEMCALHEIGHT = ::RegisterWindowMessage(_T("WizTaskPanelItemCalHeight"));
const UINT WIZ_UM_TASKPANELUPDATELAYOUT = ::RegisterWindowMessage(_T("WizTaskPanelUpdateLayout"));
const UINT WIZ_UM_TASKPANELQUERYUPDATELAYOUT = ::RegisterWindowMessage(_T("WizTaskPanelQueryUpdateLayout"));
const UINT WIZ_UM_TASKPANELENSUREVISIBLE = ::RegisterWindowMessage(_T("WizTaskPanelEnsureVisible"));


template <class T>
class CWizTaskPanelItemActiveX
{
	BEGIN_MSG_MAP(CWizTaskPanelItemActiveX)
		MESSAGE_HANDLER(WIZ_UM_TASKPANELITEMCALHEIGHT, OnTaskPanelItemCalHeight)
		MESSAGE_HANDLER(WIZ_UM_TASKPANELQUERYUPDATELAYOUT, OnForwardMessageToParent)
		MESSAGE_HANDLER(WIZ_UM_TASKPANELENSUREVISIBLE, OnForwardMessageToParent)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnForwardMessageToParent)
	END_MSG_MAP()
	//
	LRESULT OnTaskPanelItemCalHeight(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		CComPtr<IOleWindow> spOleWindow;
		HRESULT hRet = pT->QueryControl(IID_IOleWindow, (void**)&spOleWindow);
		if (spOleWindow)
		{
			HWND hwnd = NULL;
			spOleWindow->GetWindow(&hwnd);
			//
			if (::IsWindow(hwnd))
			{
				return ::SendMessage(hwnd, WIZ_UM_TASKPANELITEMCALHEIGHT, wParam, lParam);
			}
		}
		return 400;
	}
	LRESULT OnForwardMessageToParent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		if (WIZ_UM_TASKPANELQUERYUPDATELAYOUT == uMsg)
		{
			wParam = (WPARAM)pT->m_hWnd;
		}
		return ::SendMessage(pT->GetParent(), uMsg, wParam, lParam);
	}
};


template <class T>
class CWizTreeCtrlStateBase;

template <class T>
class CWizTreeCtrlCore;

template<class T>
interface CWizTreeCtrlCoreCopyItemEvents
{
	virtual LPARAM TCCI_OnCopyData(CWizTreeCtrlCore<T>* pTreeCtrl, HTREEITEM hItemSrc) = 0;
};


template <class T>
class CWizTreeCtrlCore
{
public:
	HTREEITEM InsertItemWithData(HTREEITEM hParent, LPCTSTR lpszItem, LPARAM lParam)
	{
		T* pT = static_cast<T*>(this);
		//
		ATLASSERT(::IsWindow(pT->m_hWnd));
		return pT->InsertItem(TVIF_TEXT | TVIF_PARAM, lpszItem, 0, 0, 0, 0, lParam, hParent, NULL); 
	}
	//
	HTREEITEM InsertItemWithData(HTREEITEM hParent, LPCTSTR lpszItem, LPARAM lParam, int nImage)
	{
		T* pT = static_cast<T*>(this);
		//
		ATLASSERT(::IsWindow(pT->m_hWnd));
		return pT->InsertItem(TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE, lpszItem, nImage, nImage, 0, 0, lParam, hParent, NULL); 
	}
	//
	HTREEITEM GetLastChildItem(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hLastItem = pT->GetChildItem(hItem);
		while (hLastItem && pT->GetNextSiblingItem(hLastItem))
		{
			hLastItem = pT->GetNextSiblingItem(hLastItem);
		}
		return hLastItem;
	}

	HTREEITEM GetPrevItem(HTREEITEM hItem)
	{
		if (!hItem)
			return NULL;
		//
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hPrevItem = pT->GetPrevSiblingItem(hItem);
		if (hPrevItem)
		{
			while (pT->ItemHasChildren(hPrevItem))
			{
				hPrevItem = GetLastChildItem(treectrl, hPrevItem);
			}
		}
		else
		{
			hPrevItem = pT->GetParentItem(hItem);
		}
		return hPrevItem;
	}
	HTREEITEM GetNextItem(HTREEITEM hItem)
	{
		if (!hItem)
			return NULL;
		//
		T* pT = static_cast<T*>(this);
		//
		//子Item
		if (pT->ItemHasChildren(hItem))
		{
			return pT->GetChildItem(hItem);
		}
		//同级Item
		HTREEITEM hNextItem = pT->GetNextSiblingItem(hItem);
		if (hNextItem)
			return hNextItem;
		//上级
		HTREEITEM hParentItem = hItem;
		while (!hNextItem && hParentItem )
		{
			hParentItem = pT->GetParentItem(hParentItem);
			hNextItem = pT->GetNextSiblingItem(hParentItem);
		}
		return hNextItem;
	}
	//
	int GetChildItemCount(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		int nCount = 0;
		HTREEITEM hNextItem = pT->GetChildItem(hItem);
		while (hNextItem)
		{
			nCount++;
			nCount += GetChildItemCount(treectrl, hNextItem);
			hNextItem = pT->GetNextSiblingItem(hNextItem);
		}
		return nCount;
	}
	int GetItemCount()
	{
		T* pT = static_cast<T*>(this);
		//
		int nCount = 0;
		HTREEITEM hItem = pT->GetChildItem(TVI_ROOT);
		while (hItem)
		{
			nCount++;
			nCount += GetChildItemCount(treectrl, hItem);
			hItem = pT->GetNextSiblingItem(hItem);
		}
		return nCount;
	}
	HTREEITEM GetLastItem()
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hRootItem = pT->GetChildItem(TVI_ROOT);
		if (!hRootItem)
			return NULL;
		HTREEITEM hItem = GetLastChildItem(treectrl, hRootItem);
		while (hItem && NULL != pT->GetChildItem(hItem))
		{
			hItem = GetLastChildItem(treectrl, hItem);
		}
		return hItem;
	}
	void BeginUpdate()
	{
		T* pT = static_cast<T*>(this);
		//
		pT->SendMessage(WM_SETREDRAW, FALSE, 0);
	}
	void EndUpdate()
	{
		T* pT = static_cast<T*>(this);
		//
		pT->SendMessage(WM_SETREDRAW, TRUE, 0);
		pT->Invalidate();
	}
	//
	void ExpandAllItems(UINT nCode)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hItem = pT->GetChildItem(NULL);
		while (hItem)
		{
			if (pT->ItemHasChildren(hItem))
			{
				pT->Expand(hItem, nCode);
			}
			//
			hItem = GetNextItem(hItem);
		}
	}
	void ExpandAllItemsWithChildren(HTREEITEM hItemParent, UINT nCode)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hItem = pT->GetChildItem(hItemParent);
		while (hItem)
		{
			if (pT->ItemHasChildren(hItem))
			{
				pT->Expand(hItem, nCode);
				//
				ExpandAllItemsWithChildren(hItem, nCode);
			}
			//
			hItem = pT->GetNextSiblingItem(hItem);
		}
	}

	void DeleteAllChildItem(HTREEITEM hItem)
	{
		if (!hItem)
			return;
		//
		T* pT = static_cast<T*>(this);
		//
		hItem = pT->GetChildItem(hItem);
		while (hItem)
		{
			HTREEITEM hNextItem = pT->GetNextSiblingItem(hItem);
			//
			pT->DeleteItem(hItem);
			//
			hItem = hNextItem;
		}
	}

	virtual BOOL CanMoveLeft(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hParentItem = pT->GetParentItem(hItem);
		return hParentItem ? TRUE : FALSE;
	}
	virtual BOOL CanMoveRight(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hItemPrev = pT->GetPrevSiblingItem(hItem);
		//
		if (!hItemPrev)
			return FALSE;
		//
		return TRUE;
	}

	BOOL MoveLeft(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hParentItem = pT->GetParentItem(hItem);
		if (!hParentItem)
			return FALSE;
		//
		try
		{
			CWizWindowLocker locker(pT->m_hWnd);
			//
			HTREEITEM hInsertToParentItem = pT->GetParentItem(hParentItem);
			HTREEITEM hInsertAfterItem = hParentItem;
			//
			HTREEITEM hItemFrom = GetLastChildItem(hParentItem);
			while (hItemFrom)
			{
				HTREEITEM hMoveItem = hItemFrom;
				hItemFrom = pT->GetPrevSiblingItem(hItemFrom);
				//
				ATLTRACE(_T("Move Left=%s\n"), GetItemTextReturn(hMoveItem));
				//
				MoveBranch(hMoveItem, hInsertToParentItem, hInsertAfterItem, pT, FALSE, TRUE);
				//
				if (hMoveItem == hItem)
					break;
			}
		}
		catch (...)
		{
		}
		//
		return TRUE;
	}
	BOOL MoveRight(HTREEITEM hItem, BOOL bSingle = FALSE)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hPrevItem = pT->GetPrevSiblingItem(hItem);
		if (!hPrevItem)
			return FALSE;
		//
		try
		{
			CWizWindowLocker locker(pT->m_hWnd);
			//
			HTREEITEM hInsertToParentItem = hPrevItem;
			HTREEITEM hInsertAfterItem = GetLastChildItem(hInsertToParentItem);
			if (!hInsertAfterItem)
				hInsertAfterItem = TVI_FIRST;
			//
			HTREEITEM hItemFrom = bSingle ? hItem : GetLastChildItem(pT->GetParentItem(hItem));
			while (hItemFrom)
			{
				HTREEITEM hMoveItem = hItemFrom;
				hItemFrom = pT->GetPrevSiblingItem(hItemFrom);
				//
				ATLTRACE(_T("Move Right=%s\n"), GetItemTextReturn(hMoveItem));
				//
				MoveBranch(hMoveItem, hInsertToParentItem, hInsertAfterItem, pT, FALSE, TRUE);
				//
				if (hMoveItem == hItem)
					break;
			}
		}
		catch (...)
		{
		}
		//
		return TRUE;
	}



	inline BOOL CanMove(HTREEITEM hItemFrom, HTREEITEM hItemTo)
	{
		T* pT = static_cast<T*>(this);
		//
		if (!hItemFrom)
			return FALSE;
		//
		while (hItemFrom && hItemTo)
		{
			if (hItemFrom == hItemTo)
				return FALSE;
			hItemTo = pT->GetParentItem(hItemTo);
		}
		//
		return TRUE;
	}
	//
	CString GetItemTextReturn(HTREEITEM hItem)
	{
		T* pT = (T *)this;
		//
		CString str;
		pT->GetItemText(hItem, str);
		return str;
	}
	//
	inline HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM hItemNewParent, HTREEITEM hItemAfter, CWizTreeCtrlCoreCopyItemEvents<T>* pEvents)
	{
		T* pT = static_cast<T*>(this);
		//
		CString sText;
		//
		TV_INSERTSTRUCT tvstruct;
		//
		tvstruct.item.hItem = hItem;
		tvstruct.item.mask = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		pT->GetItem( &tvstruct.item );
		sText = GetItemTextReturn( hItem );
		tvstruct.item.cchTextMax = sText.GetLength ();
		tvstruct.item.pszText = sText.LockBuffer ();
		
		tvstruct.hParent = hItemNewParent;
		tvstruct.hInsertAfter = hItemAfter;
		tvstruct.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
		//
		HTREEITEM hNewItem = pT->InsertItem(&tvstruct);
		sText.ReleaseBuffer ();
		//
		if (pEvents)
		{
			LPARAM lParam = pEvents->TCCI_OnCopyData(pT, hItem);
			pT->SetItemData(hNewItem, lParam);
		}
		//
		pT->SetItemState(hNewItem, pT->GetItemState(hItem, TVIS_STATEIMAGEMASK), TVIS_STATEIMAGEMASK);
		//
		return hNewItem;
	}

	inline HTREEITEM CopyBranch(HTREEITEM hItemFrom, HTREEITEM hItemNewParent, HTREEITEM hItemAfter, CWizTreeCtrlCoreCopyItemEvents<T>* pEvents)
	{
		T* pT = static_cast<T*>(this);
		//
		if (!CanMove(hItemFrom, hItemNewParent))
			return FALSE;
		//
		HTREEITEM hNewItem = CopyItem(hItemFrom,hItemNewParent,hItemAfter, pEvents);
		HTREEITEM hChild = pT->GetChildItem( hItemFrom );
		
		while( hChild != NULL )
		{
			CopyBranch(hChild,hNewItem,hItemAfter, pEvents);
			hChild = pT->GetNextSiblingItem( hChild );
		}
		BOOL bExpanded = (pT->GetItemState(hItemFrom, TVIS_EXPANDED) & TVIS_EXPANDED) ? TRUE : FALSE;
		pT->Expand(hNewItem, bExpanded ? TVE_EXPAND : TVE_COLLAPSE);
		
		return hNewItem;
	}
	inline HTREEITEM MoveBranch(HTREEITEM hItemFrom, HTREEITEM hItemNewParent, HTREEITEM hItemAfter, CWizTreeCtrlCoreCopyItemEvents<T>* pEvents, BOOL bSelectNextItem = TRUE, BOOL bSelectNewItem = FALSE)
	{
		T* pT = static_cast<T*>(this);
		//
		if (!CanMove(hItemFrom, hItemNewParent))
			return FALSE;
		//
		HTREEITEM hItemNext = pT->GetNextSiblingItem(hItemFrom);
		if (!hItemNext)
			hItemNext = pT->GetPrevSiblingItem(hItemFrom);
		if (!hItemNext)
			hItemNext = pT->GetParentItem(hItemFrom);
		if (!hItemNext)
			hItemNext = pT->GetChildItem(NULL);
		//
		HTREEITEM hItemNew = CopyBranch(hItemFrom, hItemNewParent, hItemAfter, pEvents);
		//
		pT->DeleteItem(hItemFrom);
		//
		if (bSelectNextItem)
		{
			pT->SelectItem(hItemNext);
		}
		else if (bSelectNewItem)
		{
			pT->SelectItem(hItemNew);
		}
		//
		return hItemNew;
	}
};

template <class T>
class CWizTreeCtrlWithState : public CWizTreeCtrlCore<T>
{
public:
	virtual CString GetItemStateID(HTREEITEM hItem)
	{
		ATLASSERT(FALSE);
		return CString();
	}
	virtual void SaveState(CWizTreeCtrlStateBase<T>& state);
	virtual void RestoreState(CWizTreeCtrlStateBase<T>& state);
};



template <class T>
class CWizTreeCtrlStateBase
{
public:
	virtual void SaveScrollState(POINT pt) = 0;
	virtual void SaveItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL bExpanded, BOOL bSelected) = 0;
	virtual POINT GetScrollState() = 0;
	virtual void GetItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL& bExpanded, BOOL& bSelected) = 0;
	virtual BOOL StateExists() = 0;
	//
	virtual ~CWizTreeCtrlStateBase() {}
};


template <class T>
class CWizTreeCtrlState_Memory : 
	public std::map<CString, BOOL>,
	public CWizTreeCtrlStateBase<T>
{
public:
	CWizTreeCtrlState_Memory()
	{
		m_ptScroll.x = 0;
		m_ptScroll.y = 0;
	}
protected:
	POINT m_ptScroll;
	CString m_strSelectedID;
public:
	virtual void SaveScrollState(POINT pt)
	{
		m_ptScroll = pt;
	}
	virtual void SaveItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL bExpanded, BOOL bSelected)
	{
		CString strID = tree.GetItemStateID(hItem);
		//
		operator [] (strID) = bExpanded;
		//
		if (bSelected)
		{
			m_strSelectedID  = strID;
		}
	}
	virtual POINT GetScrollState()
	{
		return m_ptScroll;
	}
	virtual void GetItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL& bExpanded, BOOL& bSelected)
	{
		CString strID = tree.GetItemStateID(hItem);
		//
		bExpanded = FALSE;
		bSelected = (0 == m_strSelectedID.Compare(strID));
		//
		const_iterator it = find(strID);
		if (it != end())
		{
			bExpanded = it->second;
		}
	}
	virtual BOOL StateExists()
	{
		return !empty();
	}
};


template <class T>
inline void CWizTreeCtrlWithState<T>::SaveState(CWizTreeCtrlStateBase<T>& state)
{
	T* pT = static_cast<T*>(this);
	//
	HTREEITEM hSelectedItem = pT->GetSelectedItem();
	//
	HTREEITEM hItem = pT->GetChildItem(NULL);

	while (hItem)
	{
		if (pT->ItemHasChildren(hItem) || hSelectedItem == hItem)
		{
			state.SaveItemState(*this, hItem, pT->GetItemState(hItem, TVIS_EXPANDED) == TVIS_EXPANDED, hSelectedItem == hItem);
		}
		//
		hItem = GetNextItem(hItem);
	}
	//
	POINT pt;
	pt.x = pT->GetScrollPos(SB_HORZ);
	pt.y = pT->GetScrollPos(SB_VERT);
	//
	state.SaveScrollState(pt);
}
//
template <class T>
inline void CWizTreeCtrlWithState<T>::RestoreState(CWizTreeCtrlStateBase<T>& state)
{
	if (!state.StateExists())
		return;
	//
	T* pT = static_cast<T*>(this);
	//
	HTREEITEM hItem = pT->GetChildItem(NULL);
	while (hItem)
	{
		BOOL bExpanded = FALSE;
		BOOL bSelected = FALSE;
		//
		state.GetItemState(*this, hItem, bExpanded, bSelected);
		if (pT->ItemHasChildren(hItem))
		{
			pT->Expand(hItem, bExpanded ? TVE_EXPAND : TVE_COLLAPSE);
		}
		if (bSelected)
		{
			pT->SelectItem(hItem);
		}
		//
		hItem = GetNextItem(hItem);
	}
	//
	POINT pt = state.GetScrollState();
	pT->SetScrollPos(SB_HORZ, pt.x, FALSE);
	pT->SetScrollPos(SB_VERT, pt.y, FALSE);
}

template<class T>
class CWizTreeCtrlStateLocker
{
public:
	CWizTreeCtrlStateLocker(CWizTreeCtrlWithState<T>& tree)
		: m_tree(tree)
	{
		T* pT = static_cast<T*>(&m_tree);
		//
		m_locker.SetWindow(pT->m_hWnd);
		m_locker.Lock();
		//
		m_tree.SaveState(m_state);
	}
	~CWizTreeCtrlStateLocker()
	{
		m_tree.RestoreState(m_state);
	}
private:
	CWizTreeCtrlState_Memory<T> m_state;
	CWizWindowLocker m_locker;
	CWizTreeCtrlWithState<T>& m_tree;
};


#define WIZ_TVIS_EX_SPLIT_ITEM		0x01

#define ID_TIMER_EXPAND_ITEM_FOR_DRAG_AND_DROP		10000
#define ID_TIMER_SCROLL_FOR_DRAG_AND_DROP		10001

template <class T>
class CWizTreeCtrlBase
	: public CWizTreeCtrlWithState<T>
{
public:
	CWizTreeCtrlBase()
	{
		WizCreateUIFont(m_fontTreeFont);
		WizCreateUIFont(m_fontTreeFontBold, WIZUIFONT_BOLD);
		WizCreateUIFont(m_fontTreeFontSmall, WIZUIFONT_SMALL);
		//
		CreateButtons();
		m_hItemCommand = NULL;
		//
		m_penSplitterLine.CreatePen(PS_SOLID, 1, RGB(0xD6, 0xE5, 0xF5));
		//
		m_crBackgroundColor = GetSysColor(COLOR_WINDOW);
		//
		m_bBoldRootItem = TRUE;
		//
		m_nDrawTextFlags = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX;
		//
		m_hOldDropItem = NULL;
		//
		m_bScrolling = FALSE;
	}
	~CWizTreeCtrlBase()
	{
	}
protected:
	//
	BOOL m_bBoldRootItem;
	//
	CFont m_fontTreeFont;
	CFont m_fontTreeFontBold;
	CFont m_fontTreeFontSmall;
	CImageList m_ilButtons;
	HTREEITEM m_hItemCommand;;
	//
	CPen m_penSplitterLine;
	//
	std::map<HTREEITEM, UINT> m_mapItemExtStates;
	//
	COLORREF m_crBackgroundColor;
	UINT m_nDrawTextFlags;
	//
	HTREEITEM m_hOldDropItem;
	BOOL m_bScrolling;
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | TVS_SHOWSELALWAYS 
			| TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	}

	virtual int CalItemHeight()
	{
		return ::GetSystemMetrics(SM_CYMENU) + 4;
	}
	virtual void ResetItemHeight()
	{
		T* pT = static_cast<T*>(this);
		pT->SetItemHeight(CalItemHeight());
	}
	virtual BOOL OnInitControl()
	{
		ResetItemHeight();
		//		
		return TRUE;
	}
	virtual void OnDestroyControl()
	{
	}
	//
	virtual void GetClientRectEx(CRect& rc)
	{
		T* pT = static_cast<T*>(this);
		pT->GetClientRect(rc);
	}
	//
	virtual CString GetItemInfoTip(HTREEITEM hItem)
	{
		return CString();
	}
	//
	void SetItemStateEx(HTREEITEM hItem, UINT nState)
	{
		if (!hItem)
			return;
		//
		m_mapItemExtStates[hItem] = nState;
	}
	//
	UINT GetItemStateEx(HTREEITEM hItem)
	{
		if (!hItem)
			return 0;
		//
		std::map<HTREEITEM, UINT>::const_iterator it = m_mapItemExtStates.find(hItem);
		if (it == m_mapItemExtStates.end())
			return 0;
		//
		return it->second;
	}
	BOOL IsSplitItem(HTREEITEM hItem)
	{
		return (GetItemStateEx(hItem) & WIZ_TVIS_EX_SPLIT_ITEM) == WIZ_TVIS_EX_SPLIT_ITEM;
	}
	void SetSplitItem(HTREEITEM hItem, BOOL b)
	{
		UINT nState = GetItemStateEx(hItem);
		//
		if (b)
		{
			nState |= WIZ_TVIS_EX_SPLIT_ITEM;
		}
		else
		{
			nState &= ~WIZ_TVIS_EX_SPLIT_ITEM;
		}
		//
		SetItemStateEx(hItem, nState);
	}
	//
	void SetBackgroundColor(COLORREF cr)
	{
		m_crBackgroundColor = cr;
		//
		T* pT = static_cast<T*>(this);
		if (pT->IsWindow())
		{
			pT->Invalidate();
		}
	}

	BEGIN_MSG_MAP(CWizTreeCtrlBase)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_DELETEITEM, OnDeleteItem)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGING, OnSelChanging)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_GETINFOTIP, OnGetInfoTip)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);
		//
		OnInitControl();
		//
		return lRet;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		OnDestroyControl();
		//
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->SetFocus();
		return TRUE;
	}
	LRESULT OnDeleteItem(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTREEVIEW* pNMTreeView = (NMTREEVIEW *)pNMHDR;
		//
		OnDeleteItemData(pNMTreeView->itemOld.lParam);
		pNMTreeView->itemOld.lParam = 0;
		//
		std::map<HTREEITEM, UINT>::const_iterator it = m_mapItemExtStates.find(pNMTreeView->itemOld.hItem);
		if (it != m_mapItemExtStates.end())
		{
			m_mapItemExtStates.erase(it);
		}
		//
		return TRUE;
	}
	LRESULT OnSelChanging(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTREEVIEW* pNMTreeView = (NMTREEVIEW *)pNMHDR;
		//
		if (IsSplitItem(pNMTreeView->itemNew.hItem))
			return TRUE;
		//
		return FALSE;
	}
	//
	void StartScrollTimer()
	{
		if (m_bScrolling)
			return;
		//
		m_bScrolling = TRUE;
		
		T* pT = static_cast<T*>(this);
		//
		pT->SetTimer(ID_TIMER_SCROLL_FOR_DRAG_AND_DROP, 500, NULL);
		ATLTRACE(_T("StartTimer ID_TIMER_SCROLL_FOR_DRAG_AND_DROP\n"));
	}
	void StopScrollTimer()
	{
		m_bScrolling = FALSE;
		//
		T* pT = static_cast<T*>(this);
		//
		pT->KillTimer(ID_TIMER_SCROLL_FOR_DRAG_AND_DROP);
		ATLTRACE(_T("StopTimer ID_TIMER_SCROLL_FOR_DRAG_AND_DROP\n"));
	}
	//
	virtual void ScrollUp()
	{
		T* pT = static_cast<T*>(this);
		pT->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), 0);
	}
	virtual void ScrollDown()
	{
		T* pT = static_cast<T*>(this);
		pT->GetParent().SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), 0);
	}
	//
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		//
		UINT nID = (UINT)wParam;
		if (nID == ID_TIMER_EXPAND_ITEM_FOR_DRAG_AND_DROP)
		{
			CPoint pos;
			GetCursorPos(&pos);
			//
			T* pT = static_cast<T*>(this);
			pT->ScreenToClient(&pos);
			//
			UINT nFlags = 0;
			HTREEITEM hItem = pT->HitTest(pos, &nFlags);
			if (hItem && m_hOldDropItem == hItem)
			{
				pT->Expand(hItem, TVE_EXPAND);
			}
			//
			pT->KillTimer(ID_TIMER_EXPAND_ITEM_FOR_DRAG_AND_DROP);
		}
		else if (nID == ID_TIMER_SCROLL_FOR_DRAG_AND_DROP)
		{
			ATLTRACE(_T("OnTimer ID_TIMER_SCROLL_FOR_DRAG_AND_DROP\n"));
			//
			CPoint pos;
			GetCursorPos(&pos);
			//
			T* pT = static_cast<T*>(this);
			if (::WindowFromPoint(pos) != pT->m_hWnd)
			{
				StopScrollTimer();
				return 0;
			}
			//
			CPoint posTop(pos.x, pos.y - 10);
			CPoint posBottom(pos.x, pos.y + 10);
			if (::WindowFromPoint(posTop) != pT->m_hWnd)
			{
				ScrollUp();
			}
			else if (::WindowFromPoint(posBottom) != pT->m_hWnd)
			{
				ScrollDown();
			}
			else
			{
				StopScrollTimer();
			}
		}
		//
		return 0;
	}

	LRESULT OnDragOverItem(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		pT->SelectDropTarget(hItem);
		//
		CPoint pos;
		GetCursorPos(&pos);
		CPoint posTop(pos.x, pos.y - 10);
		CPoint posBottom(pos.x, pos.y + 10);
		if (hItem 
			&& (::WindowFromPoint(posTop) != pT->m_hWnd || ::WindowFromPoint(posBottom) != pT->m_hWnd)
			)
		{
			StartScrollTimer();
		}
		else
		{
			if (hItem != m_hOldDropItem)
			{
				if (hItem 
					&& 0 == pT->GetItemState(hItem, TVIS_EXPANDED)
					&& NULL != pT->GetChildItem(hItem))
				{
					m_hOldDropItem = hItem;
					//
					pT->KillTimer(ID_TIMER_EXPAND_ITEM_FOR_DRAG_AND_DROP);
					pT->SetTimer(ID_TIMER_EXPAND_ITEM_FOR_DRAG_AND_DROP, 1000, NULL);
				}
			}
		}
		//
		return 0;
	}
	//

	LRESULT OnGetInfoTip(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTVGETINFOTIP* pNMTreeView = (NMTVGETINFOTIP *)pNMHDR;
		//
		CString str = GetItemInfoTip(pNMTreeView->hItem);
		if (str.IsEmpty())
			return 0;
		//
		if (str.GetLength() > pNMTreeView->cchTextMax - 1)
		{
			str = str.Left(pNMTreeView->cchTextMax - 1);
		}
		//
		_tcscpy_s(pNMTreeView->pszText, pNMTreeView->cchTextMax, str);
		//
		return 0;
	}
	
	
	

	LRESULT OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);
		//
		HTREEITEM hSelectedItem = pT->GetSelectedItem();
		if (hSelectedItem)
		{
			CRect rcClient;
			GetClientRectEx(rcClient);
			//
			CRect rcItem;
			pT->GetItemRect(hSelectedItem, &rcItem, FALSE);
			//
			rcItem.left = rcClient.left;
			rcItem.right = rcClient.right;
			//
			pT->InvalidateRect(&rcItem);
		}
		//
		return lRet;
	}
	//
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);

		pT->Invalidate();
		//
		return lRet;
	}
	LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		UINT xPos = GET_X_LPARAM(lParam); 
		UINT yPos = GET_Y_LPARAM(lParam); 
		//
		T* pT = static_cast<T*>(this);
		//
		CPoint pt(xPos, yPos);
		pT->ScreenToClient(&pt);
		//
		std::vector<HTREEITEM> arraySelectedItems;
		GetCommandItems(arraySelectedItems);
		//
		UINT nFlags = 0;
		m_hItemCommand = pT->HitTest(pt, &nFlags);
		HTREEITEM hFocusedItem = m_hItemCommand;
		if (pT->GetItemState(m_hItemCommand, TVIS_SELECTED) == TVIS_SELECTED)
		{
			//item has been selected
			m_hItemCommand = NULL;
		}
		//
		if (m_hItemCommand)
		{
			InvalidateItem(m_hItemCommand);
			InvalidateItems(arraySelectedItems);
			pT->UpdateWindow();
		}
		//
		ShowMenu(hFocusedItem, xPos, yPos);
		//
		HTREEITEM hOldItem = m_hItemCommand;
		m_hItemCommand = NULL;
		if (hOldItem)
		{
			InvalidateItems(arraySelectedItems);
			InvalidateItem(hOldItem);
			pT->UpdateWindow();
		}
		//
		return 0;
	}
	//
	void InvalidateItems(const std::vector<HTREEITEM>& items)
	{
		for (std::vector<HTREEITEM>::const_iterator it = items.begin();
			it != items.end();
			it++)
		{
			InvalidateItem(*it);
		}
	}
	void InvalidateItem(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		CRect rcItem;
		pT->GetItemRect(hItem, &rcItem, FALSE);
		//
		pT->InvalidateRect(&rcItem);
	}
	void ShowMenu(HTREEITEM hFocusedItem, int x, int y)
	{
		CMenuHandle menu = GetContextMenu(hFocusedItem);
		if (!menu.m_hMenu)
			return;
		//
		OnUpdateContextMenu(hFocusedItem, menu);
		//
		T* pT = static_cast<T*>(this);
		//
		UINT nCmd = menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD, x, y, pT->m_hWnd);
		//
		if (nCmd)
		{
			pT->SendMessage(WM_COMMAND, MAKEWPARAM(nCmd, 0), 0);
		}
	}
	//
	void CreateButtons()
	{
		m_ilButtons.Create(8, 16, ILC_COLOR32 | ILC_MASK, 2, 2);
		COLORREF crBackground = RGB(255, 0, 255);
		for (int i = 0; i < 2; i++)
		{
			CBitmap bmp;
			//
			CDC dcMem;
			CClientDC dc(::GetDesktopWindow());
			dcMem.CreateCompatibleDC(dc.m_hDC);
			bmp.CreateCompatibleBitmap(dc.m_hDC, 8, 16);
			HBITMAP hbmOld = dcMem.SelectBitmap(bmp);
			RECT rc = {0, 0, 8, 16};
			//
			dcMem.FillSolidRect(&rc, crBackground);
			//
			if (0 == i)
			{
				DrawExpandedButton(&dcMem, rc);
			}
			else
			{
				DrawCollapsedButton(&dcMem, rc);
			}
			dcMem.SelectBitmap(hbmOld);
			dcMem.DeleteDC();
			//
			m_ilButtons.Add(bmp, crBackground);
		}
	}

	//
	void DrawExpandedButton(CDC* pDC, RECT& rc)
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(89, 89, 89));
		//
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(38, 38, 38));
		//
		HBRUSH hOldBrush = pDC->SelectBrush(brush);
		HPEN hOldPen = pDC->SelectPen(pen);
		//
		CRect rect(rc);
		//
		POINT ptCenter = rect.CenterPoint();
		CRect rcImage(ptCenter.x - 2, ptCenter.y - 2, ptCenter.x + 3, ptCenter.y + 3);
		//
		CPoint pts[3];
		pts[0].x = rcImage.right;
		pts[0].y = rcImage.top;

		pts[1].x = rcImage.left;
		pts[1].y = rcImage.bottom;

		pts[2].x = rcImage.right;
		pts[2].y = rcImage.bottom;
		//
		pDC->Polygon(pts, 3);
		//
		pDC->SelectBrush(hOldBrush);
		pDC->SelectPen(hOldPen);
	}
	void DrawCollapsedButton(CDC* pDC, RECT& rc)
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(252, 252, 252));
		//
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(135, 135, 135));
		//
		HBRUSH hOldBrush = pDC->SelectBrush(brush);
		HPEN hOldPen = pDC->SelectPen(pen);
		//
		CRect rect(rc);
		//
		POINT ptCenter = rect.CenterPoint();
		CRect rcImage(ptCenter.x - 4, ptCenter.y - 4, ptCenter.x + 4, ptCenter.y + 4);
		//
		CPoint pts[3];
		pts[0].x = ptCenter.x - 2;
		pts[0].y = ptCenter.y - 4;

		pts[1].x = ptCenter.x - 2;
		pts[1].y = ptCenter.y + 4;

		pts[2].x = ptCenter.x + 2;
		pts[2].y = ptCenter.y;
		//
		pDC->Polygon(pts, 3);
		//
		pDC->SelectBrush(hOldBrush);
		pDC->SelectPen(hOldPen);
	}

	void DoPaint( CDCHandle dcPaint )
	{
		T* pT = static_cast<T*>(this);
		//
		CRect rcUpdate;
		dcPaint.GetClipBox(&rcUpdate);
		//
		//pT->DefWindowProc( WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC, 0 );
		HTREEITEM hItem = pT->GetFirstVisibleItem();
		int iVisibleCount = pT->GetVisibleCount() + 1;
		//
		if (!rcUpdate.IsRectEmpty())
		{
			HTREEITEM hFirstItem = pT->HitTest(rcUpdate.TopLeft(), NULL);
			if (hFirstItem)
				hItem = hFirstItem;
			//
			iVisibleCount = rcUpdate.Height() / pT->CalItemHeight() + 2;
		}
		//
		CRect rcClient;
		GetClientRectEx(rcClient);
		//
		int nDC = dcPaint.SaveDC();
		//
		dcPaint.FillSolidRect(rcClient, m_crBackgroundColor);
		//
		dcPaint.SetBkMode(TRANSPARENT);
		//
		CImageList il = pT->GetImageList(TVSIL_NORMAL);
		CSize szImage;
		int nImageCount = 0;
		if (il.m_hImageList)
		{
			il.GetIconSize(szImage);
			nImageCount = il.GetImageCount();
		}
		//
		CPoint ptCursor;
		GetCursorPos(&ptCursor);
		pT->ScreenToClient(&ptCursor);
		//
		int nIndent = pT->GetIndent();
		//
		BOOL bDrawButtons = (pT->GetStyle() & TVS_HASBUTTONS) ? TRUE : FALSE;
		//
		while (hItem && iVisibleCount--)
		{
			CRect rcItemText;
			pT->GetItemRect(hItem, &rcItemText, TRUE);
			//
			if (IsSplitItem(hItem))
			{
				CRect rcItem = rcItemText;
				//
				rcItem.left = 0;
				rcItem.right = rcClient.right;
				//
				CPoint ptCenter = rcItem.CenterPoint();
				//
				HPEN hOldPen = dcPaint.SelectPen(m_penSplitterLine);
				dcPaint.MoveTo(rcItem.left + 8, ptCenter.y);
				dcPaint.LineTo(rcItem.right - 8, ptCenter.y);
				//
				if (hOldPen)
				{
					dcPaint.SelectPen(hOldPen);
				}
			}
			else
			{
				SetItemTextFont(dcPaint, hItem);
				//
				rcItemText.right = rcClient.right;
				//
				CRect rcItemBack = rcItemText;
				rcItemBack.left = 0;
				rcItemBack.right = rcClient.right;
				//
				BOOL bItemSelected = (pT->GetItemState(hItem, TVIS_SELECTED) == TVIS_SELECTED);
				BOOL bSelected = (bItemSelected && !m_hItemCommand) || (hItem == m_hItemCommand);
				BOOL bDragHighlight = (pT->GetItemState(hItem, TVIS_DROPHILITED) == TVIS_DROPHILITED);
				//BOOL bHot = rcItemBack.PtInRect(ptCursor);
				BOOL bHot = FALSE;
				//
				DrawItemBackground(dcPaint, hItem, rcItemBack, bSelected || bDragHighlight, bHot);
				//
				CString strText;
				pT->GetItemText(hItem, strText);
				//
				rcItemText.left += GetItemTextIndent(hItem);
				//
				DrawItemText(dcPaint, hItem, rcItemText, strText);
				//
				CString strExtText = GetItemExtText(hItem);
				if (!strExtText.IsEmpty())
				{
					CSize szText;
					dcPaint.GetTextExtent(strText, strText.GetLength(), &szText);
					//
					CRect rcItemExtText = rcItemText;
					rcItemExtText.left += szText.cx + 4;
					//
					DrawItemExtText(dcPaint, hItem, rcItemExtText, strExtText);
				}
				//
				CRect rcButton;
				//
				if (il.m_hImageList)
				{
					CRect rcImage = rcItemText;
					//
					rcImage.right = rcItemText.left - 3;
					rcImage.left = rcImage.right - szImage.cx;
					rcImage.top = rcImage.CenterPoint().y - szImage.cy / 2;
					//
					DrawItemImage(dcPaint, il, hItem, rcImage.TopLeft());
					//
					rcButton = rcImage;
					rcButton.left -= nIndent;
					rcButton.right -= nIndent;
				}
				else
				{
					rcButton = rcItemText;
					//
					rcButton.right = rcItemText.left - 3;
					rcButton.left = rcButton.right - (nIndent - 3);
					rcButton.top = rcButton.CenterPoint().y - 16 / 2;
				}
				//
				if (bDrawButtons && pT->GetChildItem(hItem) && m_ilButtons.m_hImageList)
				{
					if (TVIS_EXPANDED == pT->GetItemState(hItem, TVIS_EXPANDED))
					{
						m_ilButtons.Draw(dcPaint, 0, rcButton.TopLeft(), ILD_TRANSPARENT);
					}
					else
					{
						m_ilButtons.Draw(dcPaint, 1, rcButton.TopLeft(), ILD_TRANSPARENT);
					}
				}
			}
			//
			hItem = pT->GetNextVisibleItem( hItem );
		}
		//
		dcPaint.RestoreDC(nDC);
	}
public:
	virtual void SetItemTextFont(CDCHandle dcPaint, HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		HTREEITEM hParentItem = pT->GetParentItem(hItem);
		if (hParentItem || !m_bBoldRootItem)
		{
			dcPaint.SelectFont(m_fontTreeFont);
		}
		else
		{
			dcPaint.SelectFont(m_fontTreeFontBold);
		}
	}
	virtual COLORREF GetItemTextColor(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		//
		if (pT->GetItemState(hItem, TVIS_SELECTED) == TVIS_SELECTED)
		{
			if (pT->m_hWnd == ::GetFocus())
			{
				static COLORREF color = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				return color;
			}
			else
			{
				static COLORREF color = ::GetSysColor(COLOR_WINDOWTEXT);
				return color;
			}
		}
		else
		{
			static COLORREF color = ::GetSysColor(COLOR_WINDOWTEXT);
			return color;
		}
	}
	virtual COLORREF GetItemTextBackgroundColor(HTREEITEM hItem)
	{
		T* pT = static_cast<T*>(this);
		if (pT->GetItemState(hItem, TVIS_SELECTED) == TVIS_SELECTED)
		{
			if (pT->m_hWnd == ::GetFocus())
			{
				static COLORREF color = ::GetSysColor(COLOR_HIGHLIGHT);
				return color;
			}
			else
			{
				static COLORREF color = ::GetSysColor(COLOR_BTNFACE);
				return color;
			}
		}
		else
		{
			return (COLORREF)-1;
		}
	}
	virtual void DrawItemBackground(CDCHandle dcPaint, HTREEITEM hItem, CRect& rcItemBack, BOOL bSelected, BOOL bHot)
	{
	}
	virtual void DrawItemText(CDCHandle dcPaint, HTREEITEM hItem, CRect& rcItemText, LPCTSTR lpszText)
	{
		dcPaint.SetTextColor(GetItemTextColor(hItem));
		//
		COLORREF crBackground = GetItemTextBackgroundColor(hItem);
		if ((COLORREF)-1 == crBackground)
		{
			dcPaint.SetBkMode(TRANSPARENT);
		}
		else
		{
			dcPaint.SetBkMode(OPAQUE);
			dcPaint.SetBkColor(crBackground);
		}
		//
		dcPaint.DrawText(lpszText, -1, &rcItemText, m_nDrawTextFlags);
	}
	virtual void DrawItemExtText(CDCHandle dcPaint, HTREEITEM hItem, CRect& rcItemExtText, LPCTSTR lpszExtText)
	{
		static COLORREF crExtTextColor = GetSysColor(COLOR_BTNSHADOW);
		dcPaint.SetTextColor(crExtTextColor);
		//
		dcPaint.SelectFont(m_fontTreeFontSmall);
		dcPaint.DrawText(lpszExtText, -1, &rcItemExtText,  DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	}
	virtual void DrawItemImage(CDCHandle dcPaint, CImageList il, HTREEITEM hItem, POINT pt)
	{
		T* pT = static_cast<T*>(this);
		int nImage = -1;
		int nSelectedImage = -1;
		pT->GetItemImage(hItem, nImage, nSelectedImage);
		//
		il.Draw(dcPaint, nImage, pt, ILD_TRANSPARENT);
	}
public:
	virtual void GetCommandItems(std::vector<HTREEITEM>& arrayItem)
	{
		T* pT = static_cast<T*>(this);
		//
		if (m_hItemCommand)
		{
			arrayItem.push_back(m_hItemCommand);
		}
		else
		{
			HTREEITEM hItem = pT->GetSelectedItem();
			if (hItem)
			{
				arrayItem.push_back(hItem);
			}
		}
	}
	virtual UINT GetCommandItemCount()
	{
		std::vector<HTREEITEM> arrayItem;
		GetCommandItems(arrayItem);
		return (UINT)arrayItem.size();
	}
	virtual HTREEITEM GetFirstCommandItem()
	{
		std::vector<HTREEITEM> arrayItem;
		GetCommandItems(arrayItem);
		if (arrayItem.empty())
			return NULL;
		return arrayItem[0];
	}
	virtual HTREEITEM GettCommandItem()
	{
		return GetFirstCommandItem();
	}
	virtual HMENU GetContextMenu(HTREEITEM hFocusedItem)
	{
		return NULL;
	}
	virtual void OnUpdateContextMenu(HTREEITEM hFocusedItem, HMENU hMenu)
	{
	}
	virtual CString GetItemExtText(HTREEITEM hItem)
	{
		return CString();
	}
	virtual int GetItemTextIndent(HTREEITEM hItem)
	{
		return 0;
	}
	virtual void OnDeleteItemData(LPARAM lParam)
	{
	}
	//
	static int CALLBACK WizAtlTreeCtrlBaseCompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		T* pT = (T *)lParamSort;
		//
		return pT->CompareItem(lParam1, lParam2);
	}
	//
	virtual int CompareItem(LPARAM lParam1, LPARAM lParam2)
	{
		ATLASSERT(FALSE);
		return 0;
	}

	void SortChildItems(HTREEITEM hItem, BOOL bRecurse = FALSE)
	{
		T* pT = (T *)this;
		//
		CWaitCursor wait;
		//
		TVSORTCB tvs;
		// Sort the tree control's items using my
		// callback procedure.
		tvs.hParent = hItem;
		tvs.lpfnCompare = WizAtlTreeCtrlBaseCompareItem;
		tvs.lParam = (LPARAM)pT;
		//
		pT->SortChildrenCB(&tvs, FALSE);
		//
		if (bRecurse)
		{
			HTREEITEM hChildItem = pT->GetChildItem(hItem);
			while (hChildItem)
			{
				SortChildItems(hChildItem, TRUE);
				//
				hChildItem = pT->GetNextSiblingItem(hChildItem);
			}
		}
	}
	HTREEITEM FindChildItem(HTREEITEM hParentItem, LPCTSTR lpszText, BOOL bMatchCase, BOOL bCreate)
	{
		T* pT = (T *)this;
		//
		HTREEITEM hItem = pT->GetChildItem(hParentItem);
		while (hItem)
		{
			CString str = GetItemTextReturn(hItem);
			if (bMatchCase)
			{
				if (str == lpszText)
					return hItem;
			}
			else
			{
				if (0 == str.CompareNoCase(lpszText))
					return hItem;
			}
			//
			hItem = pT->GetNextSiblingItem(hItem);
		}
		//
		if (bCreate)
		{
			return pT->InsertItem(lpszText, -1, -1, hParentItem, NULL);
		}
		return NULL;
	}
	//
	void AppendSplitItem(LPARAM lParam)
	{
		HTREEITEM hItem = InsertItemWithData(NULL, _T(""), lParam);
		if (hItem)
		{
			SetSplitItem(hItem, TRUE);
		}
	}
	//
	int GetAllVisibleItemCount()
	{
		T* pT = (T *)this;
		//
		int nVisible = 0;
		HTREEITEM hItem = pT->GetChildItem(NULL);
		while (hItem)
		{
			nVisible++;
			hItem = pT->GetNextVisibleItem(hItem);
		}
		//
		if (0 == nVisible)
		{
			nVisible++;
		}
		//
		return nVisible;
	}
		
	void MakeSelectedItemVisibleInTaskPanel()
	{
		T* pT = (T *)this;
		//
		HTREEITEM hItem = pT->GetSelectedItem();
		if (!hItem)
			return;
		//
		MakeItemVisibleInTaskPanel(hItem); 
	}
	void MakeItemVisibleInTaskPanel(HTREEITEM hItem)
	{
		if (!hItem)
			return;
		//
		T* pT = (T *)this;
		//
		CRect rc;
		pT->GetItemRect(hItem, &rc, FALSE);
		//
		::SendMessage(pT->GetParent(), WIZ_UM_TASKPANELENSUREVISIBLE, (WPARAM)pT->m_hWnd, (LPARAM)&rc);
	}
};


template <class T>
class CWizTreeCtrlImpl 
	: public ATL::CWindowImpl< T, CTreeViewCtrl, ATL::CControlWinTraits>
	, public CDoubleBufferImpl<CWizTreeCtrlImpl<T> >
	, public CWizTreeCtrlBase<T>
{
public:
	CWizTreeCtrlImpl()
	{
	}
	
	~CWizTreeCtrlImpl()
	{
	}
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	}
public:
	BEGIN_MSG_MAP(CWizTreeCtrlImpl)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CWizTreeCtrlImpl> )
		CHAIN_MSG_MAP(CWizTreeCtrlBase<T>)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

public:
	BOOL SubclassWindow( HWND hWnd )
	{
		return CWindowImpl< T, CTreeViewCtrl >::SubclassWindow( hWnd ) ? OnInitControl() : FALSE;
	}
	void DoPaint( CDCHandle dcPaint )
	{
		CWizTreeCtrlBase::DoPaint(dcPaint);
	}	
};

class CWizTreeCtrl : public CWizTreeCtrlImpl<CWizTreeCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("Wiz_TreeCtrl"), GetWndClassName())
};



inline WORD WizHotKeyMakeHotKeyValue(BYTE wVirtualKeyCode, BYTE wModifiers)
{
	return MAKEWORD(wVirtualKeyCode, wModifiers);
}

template<class T, class TSettings>
class CWizHotKeyCtrlImpl
	: public CWindowImpl<CWizHotKeyCtrlImpl<T, TSettings>, CHotKeyCtrl>
{
public:
	CWizHotKeyCtrlImpl()
	{
	}
	~CWizHotKeyCtrlImpl()
	{
	}
private:
	CString m_strSectionName;
	CString m_strKeyName;
public:
	BEGIN_MSG_MAP(CWizHotKeyCtrlImpl)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
public:
	void SetStateSection(LPCTSTR lpszSection, LPCTSTR lpszKey, DWORD nDefHotKey)
	{
		m_strSectionName = lpszSection;
		m_strKeyName = lpszKey;
		//
		if (m_strSectionName.IsEmpty()
			|| m_strKeyName.IsEmpty())
			return;
		if (!IsWindow())
			return;
		//
		int nKey = GetHotKeyFromSettings(m_strSectionName, m_strKeyName, nDefHotKey);
		if (0 == nKey)
			return;
		//
		SetHotKey(LOBYTE(nKey), HIBYTE(nKey));
	}
	//
	void Save()
	{
		if (m_strSectionName.IsEmpty()
			|| m_strKeyName.IsEmpty())
			return;
		if (!IsWindow())
			return;
		//
		DWORD dwKey = GetHotKey();
		//
		TSettings settings;
		settings.SetInt(m_strSectionName, m_strKeyName, dwKey);
	}
	//
	static DWORD GetHotKeyFromSettings(LPCTSTR lpszSection, LPCTSTR lpszKey, DWORD nDefHotKey)
	{
		TSettings settings;
		return settings.GetInt(lpszSection, lpszKey, nDefHotKey);
	}
};



template<class T>
class CWizAtlBackgroundEditImpl 
	: public CWindowImpl<CWizAtlBackgroundEditImpl<T>, CEdit>
{
public:
	CWizAtlBackgroundEditImpl()
	{
		m_crBackground = GetSysColor(COLOR_WINDOW);
		m_crText = GetSysColor(COLOR_WINDOWTEXT);
	}
	~CWizAtlBackgroundEditImpl()
	{
	}
	//
	typedef CWindowImpl<CWizAtlBackgroundEditImpl<T>, CEdit> CBaseClass;
private:
	CBrush m_brush;
	COLORREF m_crBackground;
	COLORREF m_crText;
public:
	BEGIN_MSG_MAP(CWizAtlBackgroundEditImpl)
		MESSAGE_HANDLER(OCM_CTLCOLOREDIT, OnCtlColorEdit)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

public:
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_brush.IsNull())
		{
			m_brush.CreateSolidBrush(m_crBackground);
		}
		//
		HDC hDC = (HDC)wParam;
		CDCHandle dc(hDC);
		dc.SetBkColor(m_crBackground);
		dc.SetTextColor(m_crText);
		//
		return (LRESULT)m_brush.m_hBrush;
	}
	//
	void SetBackgroundColor(COLORREF cr)
	{
		m_crBackground = cr;
		//
		if (!m_brush.IsNull())
		{
			m_brush.DeleteObject();
		}
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	void SetTextColor(COLORREF cr)
	{
		m_crText = cr;
		//
		if (IsWindow())
		{
			Invalidate();
		}
	}
	COLORREF GetTextColor() const
	{
		return m_crText;
	}
};

class CWizAtlBackgroundEdit : public CWizAtlBackgroundEditImpl<CWizAtlBackgroundEdit>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WizAtlBackgroundEdit"), GetWndClassName())
};



typedef CComEnumOnSTL<IEnumFORMATETC,           // name of enumerator interface
                      &IID_IEnumFORMATETC,      // IID of enumerator interface
                      FORMATETC,                // type of object to return
                      _Copy<FORMATETC>,         // copy policy class
                      std::vector<FORMATETC> >  // type of collection holding the data
	CWizEnumFORMATETCImpl;


inline LPFORMATETC WizFillFormatEtc(LPFORMATETC lpFormatEtc, CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtcFill)
{
	ATLASSERT(lpFormatEtcFill != NULL);
	//
	if (lpFormatEtc == NULL && cfFormat != 0)
	{
		lpFormatEtc = lpFormatEtcFill;
		lpFormatEtc->cfFormat = cfFormat;
		lpFormatEtc->ptd = NULL;
		lpFormatEtc->dwAspect = DVASPECT_CONTENT;
		lpFormatEtc->lindex = -1;
		lpFormatEtc->tymed = (DWORD) -1;
	}
	//
	return lpFormatEtc;
}


class CAtlWizDropSource
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CAtlWizDropSource>
	, public IDataObject
	, public IDropSource
{
public:
	CAtlWizDropSource()
	{
		m_bInitialized = FALSE;
		m_nFormat = 0;
		m_hData = NULL;
		m_dwLastEffect = 0;
	}
	virtual ~CAtlWizDropSource()
	{
	}
public:
	BEGIN_COM_MAP(CAtlWizDropSource)
		COM_INTERFACE_ENTRY(IDataObject)
		COM_INTERFACE_ENTRY(IDropSource)
	END_COM_MAP()

	// IDataObject
	STDMETHODIMP SetData ( FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease )
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP GetData ( FORMATETC* pformatetcIn, STGMEDIUM* pmedium )
	{
		if (!pformatetcIn || !pmedium)
			return E_INVALIDARG;
		//
		if (pformatetcIn->cfFormat != m_nFormat)
			return DV_E_FORMATETC;
		//
		if (pformatetcIn->dwAspect != DVASPECT_CONTENT)
			return DV_E_DVASPECT;
		//
		if (pformatetcIn->lindex != -1)
			return DV_E_LINDEX;
		//
		if (pformatetcIn->tymed != TYMED_HGLOBAL)
			return DV_E_TYMED;
		//
		memset(pmedium, 0, sizeof(STGMEDIUM));
		//
		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = m_hData;
		pmedium->pUnkForRelease = NULL;
		//
		return S_OK;
	}
	STDMETHODIMP EnumFormatEtc ( DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc )
	{
		CComObject<CWizEnumFORMATETCImpl>* pImpl = NULL;

		// Create an enumerator object.
		HRESULT hr = CComObject<CWizEnumFORMATETCImpl>::CreateInstance ( &pImpl );
		if ( FAILED(hr) )
			return hr;
		//
		CComPtr<IEnumFORMATETC> spImpl(pImpl);

		// Fill in m_vecSupportedFormats with the formats that the caller has
		// put in this object
		FORMATETC format;
		ZeroMemory(&format, sizeof(FORMATETC));
		//
		format.cfFormat = m_nFormat;
		format.dwAspect = DVASPECT_CONTENT;
		format.lindex = -1;
		format.tymed = TYMED_HGLOBAL;
		//
		m_arrayFormats.clear();
		m_arrayFormats.push_back(format);
		//
		// Init the enumerator, passing it our vector of supported FORMATETCs.
		hr = pImpl->Init ( GetUnknown(), m_arrayFormats);
		if ( FAILED(hr) )
		{
			return E_UNEXPECTED;
		}
		// Return the requested interface to the caller.
		hr = pImpl->QueryInterface ( ppenumFormatEtc );
		//
		return hr;
	}
	STDMETHODIMP QueryGetData ( FORMATETC* pformatetc )
	{
		if (!pformatetc)
			return E_INVALIDARG;
		//
		if (pformatetc->cfFormat != m_nFormat)
			return DV_E_FORMATETC;
		//
		if (pformatetc->dwAspect != DVASPECT_CONTENT)
			return DV_E_DVASPECT;
		//
		if (pformatetc->lindex != -1)
			return DV_E_LINDEX;
		//
		if (pformatetc->tymed != TYMED_HGLOBAL)
			return DV_E_TYMED;
		//
		return S_OK;
	}

	STDMETHODIMP GetDataHere(FORMATETC* pformatetc, STGMEDIUM *pmedium)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP GetCanonicalFormatEtc(FORMATETC* pformatectIn, FORMATETC* pformatetcOut)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP DAdvise(FORMATETC* pformatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP DUnadvise(DWORD dwConnection)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP EnumDAdvise(IEnumSTATDATA** ppenumAdvise)
	{
		return E_NOTIMPL;
	}

	// IDropSource
	STDMETHODIMP QueryContinueDrag ( BOOL fEscapePressed, DWORD grfKeyState )
	{
		// If ESC was pressed, cancel the drag. If the left button was released,
		// do the drop.
		if ( fEscapePressed )
			return DRAGDROP_S_CANCEL;
		else if ( !(grfKeyState & MK_LBUTTON) )
		{
			if ( DROPEFFECT_NONE == m_dwLastEffect )
				return DRAGDROP_S_CANCEL;

			// If the drop was accepted, do the extracting here, so that when we
			// return, the files are in the temp dir & ready for Explorer to copy.
			// If ExtractFilesFromCab() failed and m_bAbortingDueToMissingCab is true,
			// then return success anyway, because we don't want to fail the whole
			// shebang in the case of a missing CAB file (some files may still be
			// extractable).
			return DRAGDROP_S_DROP;
		}
		else
			return S_OK;
	}
	STDMETHODIMP GiveFeedback ( DWORD dwEffect )
	{
		m_dwLastEffect = dwEffect;
		return DRAGDROP_S_USEDEFAULTCURSORS;
	}
	//
public:
private:
	BOOL m_bInitialized;
	UINT m_nFormat;
	HANDLE m_hData;
	DWORD m_dwLastEffect;
	std::vector<FORMATETC> m_arrayFormats;
public:
	// Operations
	BOOL Init (UINT nFormat, HANDLE hData)
	{
		ATLASSERT(!m_bInitialized);
		ATLASSERT(!m_nFormat);
		ATLASSERT(!m_hData);
		if (m_bInitialized || m_nFormat || m_hData)
			return FALSE;
		//
		m_nFormat = nFormat;
		m_hData = hData;
		//
		ATLASSERT(m_nFormat);
		ATLASSERT(m_hData);
		if (!m_nFormat || !m_hData)
			return FALSE;
		//
		m_bInitialized = TRUE;
		//
		return TRUE;
	}

	HRESULT DoDragDrop ( DWORD dwOKEffects, DWORD* pdwEffect )
	{
		if ( !m_bInitialized )
			return E_FAIL;

		CComQIPtr<IDropSource> pDropSrc = this;
		CComQIPtr<IDataObject> pDataObj = this;

		ATLASSERT(pDropSrc && pDataObj);

		HRESULT hr =  ::DoDragDrop ( pDataObj, pDropSrc, dwOKEffects, pdwEffect );
		//
		return hr;
	}
};


class CWizAtlDropTarget
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CWizAtlDropTarget>
	, public IDropTarget
{
public:
	CWizAtlDropTarget()
	{
	}
	~CWizAtlDropTarget()
	{
	}
public:
	BEGIN_COM_MAP(CWizAtlDropTarget)
		COM_INTERFACE_ENTRY(IDropTarget)
	END_COM_MAP()
	//
    STDMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		return S_OK;
	}
    
    STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		return S_OK;
	}
    
	STDMETHODIMP DragLeave( void)
	{
		return S_OK;
	}
    
    STDMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		return S_OK;
	}
};



interface IWizAtlDropTargetEx
{
	virtual STDMETHODIMP OnDragLeave() = 0;
	virtual STDMETHODIMP OnDragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
	virtual STDMETHODIMP OnDrop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
};

class CWizAtlDropTargetEx
	: public CWizAtlDropTarget
{
public:
	CWizAtlDropTargetEx()
	{
		m_pTarget = NULL;
		m_dwEffect = 0;
	}
	virtual ~CWizAtlDropTargetEx()
	{
	}
protected:
	std::set<UINT> m_setFormats;
	IWizAtlDropTargetEx* m_pTarget;
	DWORD m_dwEffect;
public:
    STDMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		m_dwEffect = 0;
		//
		*pdwEffect = 0;
		//
		if (!m_pTarget)
			return S_OK;
		//
		CWizAtlDataObject data(pDataObj);
		//
		BOOL bAccept = FALSE;
		for (std::set<UINT>::const_iterator it = m_setFormats.begin();
			it != m_setFormats.end();
			it++)
		{
			if (data.IsFormatAvaliable(*it))
			{
				bAccept = TRUE;
				break;
			}
		}
		if (!bAccept)
			return S_OK;
		//
		if (MK_LBUTTON & grfKeyState)
		{
			*pdwEffect = DROPEFFECT_COPY;
			/*
			if (MK_CONTROL & grfKeyState)
			{
				*pdwEffect = DROPEFFECT_COPY;
			}
			else
			{
				*pdwEffect = DROPEFFECT_MOVE;
			}
			*/
		}
		//
		m_dwEffect = *pdwEffect;
		//
		return S_OK;
	}
    
    STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		*pdwEffect = m_dwEffect;
		//
		if (!m_pTarget)
			return S_OK;
		//
		return m_pTarget->OnDragOver(grfKeyState, pt, pdwEffect);
	}
    
	STDMETHODIMP DragLeave( void)
	{
		if (!m_pTarget)
			return S_OK;
		//
		m_pTarget->OnDragLeave();
		//
		return S_OK;
	}
    
    STDMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		if (!m_pTarget)
		{
			*pdwEffect = 0;
			return S_OK;
		}
		//
		return m_pTarget->OnDrop(pDataObj, grfKeyState, pt, pdwEffect);
	}
	//
public:
	void SetTarget(IWizAtlDropTargetEx* pTarget)
	{
		m_pTarget = pTarget;
	}
	//
	static HRESULT RegisterDragDrop(IWizAtlDropTargetEx* pTarget, const std::set<UINT>& setFormats, HWND hWnd)
	{
		CComObject<CWizAtlDropTargetEx>* pObj = NULL;
		HRESULT hr = CComObject<CWizAtlDropTargetEx>::CreateInstance(&pObj);
		if (!pObj)
			return E_OUTOFMEMORY;
		//
		std::set<UINT> formats(setFormats);
		pObj->m_setFormats.swap(formats);
		//
		CComPtr<IDropTarget> spObj(pObj);
		//
		pObj->SetTarget(pTarget);
		//
		return ::RegisterDragDrop(hWnd, pObj);
	}
	static HRESULT RegisterDragDrop(IWizAtlDropTargetEx* pTarget, UINT nFormat, HWND hWnd)
	{
		std::set<UINT> setFormats;
		setFormats.insert(nFormat);
		//
		return RegisterDragDrop(pTarget, setFormats, hWnd);
	}
};





inline void WizHotKeyCtrlValueToHotKey(DWORD dwValue, UINT& nModifiers, UINT& nKey)
{
	BYTE byMod = HIBYTE(dwValue);
	BYTE byKey = LOBYTE(dwValue);
	//
	nModifiers = 0;
	nKey = byKey;
	//
	if (byMod & HOTKEYF_ALT)
	{
		nModifiers |= MOD_ALT;
	}
	if (byMod & HOTKEYF_CONTROL)
	{
		nModifiers |= MOD_CONTROL;
	}
	if (byMod & HOTKEYF_SHIFT)
	{
		nModifiers |= MOD_SHIFT;
	}
}

inline BOOL WizTextToHotKey(LPCTSTR lpsz, UINT& nModifiers, UINT& nKey)
{
	nModifiers = 0;
	nKey = 0;
	//
	CString str(lpsz);
	if (str.IsEmpty())
		return FALSE;
	//
	str.MakeUpper();
	//
	if (-1 != str.Find(_T("CTRL")))
		nModifiers |= MOD_CONTROL;
	if (-1 != str.Find(_T("ALT")))
		nModifiers |= MOD_ALT;
	if (-1 != str.Find(_T("SHIFT")))
		nModifiers |= MOD_SHIFT;
	if (-1 != str.Find(_T("WIN")))
		nModifiers |= MOD_WIN;
	//
	str.Replace(_T("CTRL"), _T(""));
	str.Replace(_T("ALT"), _T(""));
	str.Replace(_T("SHIFT"), _T(""));
	str.Replace(_T("WIN"), _T(""));
	//
	str.Replace(_T("+"), _T(""));
	str.Replace(_T(" "), _T(""));
	str.Trim();
	//
	if (str.IsEmpty())
		return FALSE;
	//
	if (str == _T("ENTER"))
	{
		nKey = VK_RETURN;
		return TRUE;
	}
	else if (str == _T("ESC"))
	{
		nKey = VK_ESCAPE;
		return TRUE;
	}
	else if (str == _T("PRINTSCREEN"))
	{
		nKey = VK_SNAPSHOT;
		return TRUE;
	}
	else if (str == _T("INSERT"))
	{
		nKey = VK_INSERT;
		return TRUE;
	}
	else if (str == _T("DEL"))
	{
		nKey = VK_DELETE;
		return TRUE;
	}
	else if (str == _T("HOME"))
	{
		nKey = VK_HOME;
		return TRUE;
	}
	else if (str == _T("END"))
	{
		nKey = VK_END;
		return TRUE;
	}
	else if (str == _T("BACKSPACE"))
	{
		nKey = VK_BACK;
		return TRUE;
	}
	else if (str == _T("PAGEUP"))
	{
		nKey = VK_PRIOR;
		return TRUE;
	}
	else if (str == _T("PAGEDOWN"))
	{
		nKey = VK_NEXT;
		return TRUE;
	}
	//
	if (str.GetLength() == 1)
		nKey = str[0];
	else
	{
		if (str[0] != 'F')
			return FALSE;
		//
		str.Delete(0);
		//
		int nNum = _ttoi(str);
		if (nNum == 0)
			return FALSE;
		//
		nKey = VK_F1 + (nNum - 1);
	}
	//
	return TRUE;
}


inline CString WizHotKeyCtrlValueToText(DWORD dwValue)
{
	UINT nKey = 0;
	UINT nMod = 0;
	WizHotKeyCtrlValueToHotKey(dwValue, nMod, nKey);

	CString str;
	if (nMod & MOD_CONTROL)
	{
		str += _T("Ctrl+");
	}
	if (nMod & MOD_SHIFT)
	{
		str += _T("Shift+");
	}
	if (nMod & MOD_ALT)
	{
		str += _T("Alt+");
	}
	//
	if (nKey >= 'A' && nKey <= 'Z')
	{
		str += (TCHAR)nKey;
	}
	else if (nKey >= '0' && nKey <= '9')
	{
		str += (TCHAR)nKey;
	}
	else if (nKey >= VK_F1 && nKey <= VK_F19)
	{
		CString strText;
		strText.Format(_T("F%d"), nKey - VK_F1 + 1);
		str += strText;
	}
	else if (nKey == VK_ESCAPE)
	{
		str += _T("ESC");
	}
	else if (nKey == VK_RETURN)
	{
		str += _T("Enter");
	}
	else if (nKey == VK_INSERT)
	{
		str += _T("Insert");
	}
	else if (nKey == VK_DELETE)
	{
		str += _T("Delete");
	}
	else if (nKey == VK_HOME)
	{
		str += _T("Home");
	}
	else if (nKey == VK_END)
	{
		str += _T("End");
	}
	else if (nKey == VK_UP)
	{
		str += _T("PageUp");
	}
	else if (nKey == VK_DOWN)
	{
		str += _T("PageDown");
	}
	return str;
}

inline BOOL WizTextToAccel(LPCTSTR lpsz, BYTE& fVirt, UINT& nKey)
{
	fVirt = FVIRTKEY;
	//
	UINT nModifiers = 0;
	nKey = 0;
	if (!WizTextToHotKey(lpsz, nModifiers, nKey))
		return FALSE;
	//
	if (MOD_CONTROL & nModifiers)
	{
		fVirt |= FCONTROL;
	}
	if (MOD_SHIFT & nModifiers)
	{
		fVirt |= FSHIFT;
	}
	if (MOD_ALT & nModifiers)
	{
		fVirt |= FALT;
	}
	//
	return TRUE;
}



inline CString WizAccelToText(BYTE fVirt, UINT nKey)
{
	UINT nMod = 0;
	if (fVirt & FCONTROL)
	{
		nMod |= HOTKEYF_CONTROL;
	}
	if (fVirt & FALT)
	{
		nMod |= HOTKEYF_ALT;
	}
	if (fVirt & FSHIFT)
	{
		nMod |= HOTKEYF_SHIFT;
	}
	//
	WORD hotkey = MAKEWORD(nKey, nMod);
	//
	return WizHotKeyCtrlValueToText(hotkey);
}

struct WIZHOTKEYDATA
{
	CString strHotKey;
	UINT nCommand;
	//
	BOOL bRegistered;
	//
	WIZHOTKEYDATA()
		: nCommand(0)
		, bRegistered(FALSE)
	{
	}
	WIZHOTKEYDATA(LPCTSTR lpszHotKey, UINT command)
		: strHotKey(lpszHotKey)
		, nCommand(command)
		, bRegistered(FALSE)
	{
		if (0 == strHotKey.CompareNoCase(_T("None")))
		{
			strHotKey.Empty();
		}
	}
};
typedef std::vector<WIZHOTKEYDATA> CWizHotKeyDataArray;

class CWizHotKeyHelper
{
public:
	CWizHotKeyHelper()
		: m_hWnd(NULL)
		, m_bRegistered(FALSE)
	{
	}
private:
	BOOL m_bRegistered;
	HWND m_hWnd;
	CWizHotKeyDataArray m_arrayHotKey;
private:
	static BOOL GetError(LPCTSTR lpszHotKey, UINT nCommandID, CString& strError)
	{
		CString strDescription = WizFormatString0(nCommandID);
		if (strDescription.IsEmpty())
			return FALSE;
		//
		int nPos = strDescription.Find('\n');
		if (-1 != nPos)
		{
			strDescription = strDescription.Left(nPos);
		}
		//
		strError += CString(_T("\n")) + WizFormatString2(_T("%1 %2"), strDescription, lpszHotKey);
		//
		return TRUE;
	}
	//
	static BOOL Register(HWND hwnd, UINT nCommandID, LPCTSTR lpszHotKey, CString& strError)
	{
		if (!lpszHotKey)
			return TRUE;
		if (!*lpszHotKey)
			return TRUE;
		//
		UINT nKey = 0;
		UINT nMod = 0;
		if (!WizTextToHotKey(lpszHotKey, nMod, nKey))
		{
			strError = WizFormatString1(_T("Unknown Hot Key: %1"), lpszHotKey);
			return FALSE;
		}
		//
		BOOL bRet = RegisterHotKey(hwnd, nCommandID, nMod, nKey);
		if (!bRet)
		{
			GetError(lpszHotKey, nCommandID, strError);
		}
		//
		return bRet;
	}
public:
	BOOL IsRegistered() const
	{
		return m_bRegistered;
	}
	BOOL RegisterAll(HWND hwnd, const CWizHotKeyDataArray& arrayHotKey, CString& strAllErrors)
	{
		strAllErrors.Empty();
		//
		if (m_bRegistered)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		if (m_hWnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		if (!hwnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		m_hWnd = hwnd;
		m_arrayHotKey.assign(arrayHotKey.begin(), arrayHotKey.end());
		//
		for (CWizHotKeyDataArray::iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			CString strError;
			if (!Register(m_hWnd, it->nCommand, it->strHotKey, strError))
			{
				it->bRegistered = FALSE;
				strAllErrors += (strError + _T("\n"));
			}
			else
			{
				it->bRegistered = TRUE;
				m_bRegistered = TRUE;
			}
		}
		//
		return strAllErrors.IsEmpty();
	}
	//
	BOOL UnregisterAll()
	{
		if (!m_bRegistered)
		{
			return FALSE;
		}
		if (!m_hWnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		for (CWizHotKeyDataArray::iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			UnregisterHotKey(m_hWnd, it->nCommand);
			it->bRegistered = FALSE;
		}
		//
		m_arrayHotKey.clear();
		m_hWnd = NULL;
		m_bRegistered = FALSE;
		//
		return TRUE;
	}
	//
	CString GetHotKeyByCommand(UINT nCommand)
	{
		for (CWizHotKeyDataArray::const_iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			if (it->nCommand == nCommand)
				return it->strHotKey;
		}
		return CString();
	}
	CString GetRegisteredHotKeyByCommand(UINT nCommand)
	{
		for (CWizHotKeyDataArray::const_iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			if (it->bRegistered
				&& it->nCommand == nCommand)
				return it->strHotKey;
		}
		return CString();
	}
#ifdef __ATLAPP_H__
	void UpdateHotKeyToMenu(HMENU hMenu)
	{
		CMenuHandle menu(hMenu);
		if (!menu.IsMenu())
			return;
		int nCount = menu.GetMenuItemCount();
		for (int i = 0; i < nCount; i++)
		{
			UINT nID = menu.GetMenuItemID(i);
			if (nID)
			{
				CString strHotKey = GetRegisteredHotKeyByCommand(nID);
				if (!strHotKey.IsEmpty())
				{
					CString strText;
					menu.GetMenuString(i, strText, MF_BYPOSITION);
					//
					CString strOld = strText;
					int nPos = strText.Find('\t');
					if (nPos != -1)
						strText = strText.Left(nPos);
					//
					strText += CString(_T("\t")) + strHotKey;
					if (strOld != strText)
					{
						TCHAR szMenuItem[MAX_PATH];
						_tcscpy_s(szMenuItem, MAX_PATH, strText);
						//
						MENUITEMINFO mi;
						ZeroMemory(&mi, sizeof(MENUITEMINFO));
						//
						mi.cbSize = sizeof(MENUITEMINFO);
						mi.fMask = MIIM_TYPE;
						mi.fType = MFT_STRING;
						mi.dwTypeData = szMenuItem;
						mi.cch = MAX_PATH;
						//
						menu.SetMenuItemInfo(i, TRUE, &mi);
					}
				}
			}
		}
	}
#endif
};

#ifdef __ATLAPP_H__
inline void WizUpdateAccelToMenu(HACCEL hAccel, CMenuHandle menu)
{
	if (!hAccel)
		return;
	//
	const UINT ACCEL_COUNT = 40;
	ACCEL accel[ACCEL_COUNT];
	ZeroMemory(accel, sizeof(ACCEL) * ACCEL_COUNT);
	int nAccelCount = CopyAcceleratorTable(hAccel, accel, ACCEL_COUNT);
	//
	int nMenuCount = menu.GetMenuItemCount();
	for (int iMenu = 0; iMenu < nMenuCount; iMenu++)
	{
		UINT nID = menu.GetMenuItemID(iMenu);
		if (nID)
		{
			CString strShortcut;
			for (int iAccel = 0; iAccel < nAccelCount; iAccel++)
			{
				if (nID == accel[iAccel].cmd)
				{
					strShortcut += (WizAccelToText(accel[iAccel].fVirt, accel[iAccel].key) + _T(" / "));
				}
			}
			if (strShortcut.IsEmpty())
				continue;
			strShortcut.Trim(_T("/ "));
			//
			CString strText;
			menu.GetMenuString(iMenu, strText, MF_BYPOSITION);
			//
			CString strOld = strText;
			int nPos = strText.Find('\t');
			if (nPos != -1)
				strText = strText.Left(nPos);
			//
			strText += CString(_T("\t")) + strShortcut;
			if (strOld != strText)
			{
				TCHAR szMenuItem[MAX_PATH];
				_tcscpy_s(szMenuItem, MAX_PATH, strText);
				//
				MENUITEMINFO mi;
				ZeroMemory(&mi, sizeof(MENUITEMINFO));
				//
				mi.cbSize = sizeof(MENUITEMINFO);
				mi.fMask = MIIM_TYPE;
				mi.fType = MFT_STRING;
				mi.dwTypeData = szMenuItem;
				mi.cch = MAX_PATH;
				//
				menu.SetMenuItemInfo(iMenu, TRUE, &mi);
			}
		}
	}
}
#endif


#ifdef __ATLCTRLX_H__

class CWizADCtrl : public CHyperLinkImpl<CWizADCtrl>
{
public:
	DECLARE_WND_CLASS(_T("Wiz_AD"))
public:
	CWizADCtrl(LPCTSTR lpszADFileName)
		: m_strADFileName(lpszADFileName)
		, m_bAdFile(TRUE)
	{
	}
	CWizADCtrl(LPCTSTR lpszADFileName, LPCTSTR lpszRootNodeName)
		: m_strADFileName(lpszADFileName)
		, m_strRootNodeName(lpszRootNodeName)
		, m_bAdFile(FALSE)
	{
	}
public:
	BEGIN_MSG_MAP(CWizADCtrl)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		CHAIN_MSG_MAP(CHyperLinkImpl)
	END_MSG_MAP()
public:
	BOOL m_bAdFile;
	CString m_strADFileName;
	CString m_strRootNodeName;
	//
	CWizHTMLLinkDataArray m_arrayLink;
	static const UINT ID_TIMER_AD = 100;
public:
	void Init()
	{
		CHyperLinkImpl::Init();
		//
#ifdef _DEBUG
		SetTimer(ID_TIMER_AD, 1000 * 5 + 111, NULL);
#else
		SetTimer(ID_TIMER_AD, 1000 * 30 + 111, NULL);
#endif
	}
	//
	void ShowAD()
	{
		if (m_arrayLink.empty())
		{
			if (m_bAdFile)
			{
				WizURLADLoad(m_strADFileName, m_arrayLink);
			}
			else
			{
				WizURLADLoadFromXmlFile(m_strADFileName, m_arrayLink);
			}
		}
		if (m_arrayLink.empty())
			return;
		//
		const WIZHTMLLINKDATA& data = m_arrayLink[GetTickCount() % m_arrayLink.size()];
		//
		SetLabel(data.strText);
		SetHyperLink(data.strURL);
		Invalidate();
	}
	//
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (ID_TIMER_AD == wParam)
		{
			ShowAD();
		}
		//
		return 0;
	}
};

#endif	//__ATLCTRLX_H__



class CWizHotKeyCtrlExImplHook
{
private:
	static HHOOK& GetHook()
	{
		static HHOOK s_hHook = NULL;
		return s_hHook;
	}
	static void SetHook(HHOOK hHook)
	{
		GetHook() = hHook;
	}
	//
	struct KEY
	{
		UINT nKey;
		bool bPressed;
	};
	//
	struct KEYDATA
	{
		std::vector<KEY> arrayKey;
	};
	//
	static KEYDATA& GetKeyData()
	{
		static KEYDATA data;
		return data;
	}
	//
	static intptr_t FindKey(UINT nKey)
	{
		KEYDATA& data = GetKeyData();
		for (std::vector<KEY>::const_iterator it = data.arrayKey.begin();
			it != data.arrayKey.end();
			it++)
		{
			if (it->nKey == nKey)
				return it - data.arrayKey.begin();
		}
		return -1;
	}

	static BOOL IsAllKeyUp()
	{
		KEYDATA& data = GetKeyData();
		for (std::vector<KEY>::const_iterator it = data.arrayKey.begin();
			it != data.arrayKey.end();
			it++)
		{
			if (it->bPressed)
				return FALSE;
		}
		//
		return TRUE;
	}
	static BOOL IsModKey(UINT nKey)
	{
		switch (nKey)
		{
		case VK_LCONTROL:
		case VK_RCONTROL:
		case VK_CONTROL:
		case VK_LSHIFT:
		case VK_RSHIFT:
		case VK_SHIFT:
		case VK_LMENU:
		case VK_RMENU:
		case VK_MENU:
		case VK_LWIN:
		case VK_RWIN:
			return TRUE;
		}
		//
		return FALSE;
	}
	static BOOL IsNormalKey(UINT nKey)
	{
		return !IsModKey(nKey);
	}
	//
	static intptr_t FindNormalKey()
	{
		KEYDATA& data = GetKeyData();
		for (std::vector<KEY>::const_iterator it = data.arrayKey.begin();
			it != data.arrayKey.end();
			it++)
		{
			if (IsNormalKey(it->nKey))
				return it - data.arrayKey.begin();
		}
		//
		return -1;
	}
	static intptr_t FindFirstModKey()
	{
		KEYDATA& data = GetKeyData();
		for (std::vector<KEY>::const_iterator it = data.arrayKey.begin();
			it != data.arrayKey.end();
			it++)
		{
			if (IsModKey(it->nKey))
				return it - data.arrayKey.begin();
		}
		//
		return -1;
	}
	static void RemoveNormalKey()
	{
		intptr_t nIndex = FindNormalKey();
		if (-1 == nIndex)
			return;
		//
		KEYDATA& data = GetKeyData();
		data.arrayKey.erase(data.arrayKey.begin() + nIndex);
	}
	static void OnKeyChanged()
	{
		HWND hwndEdit = GetEdit();
		if (!hwndEdit)
			return;
		if (!IsWindow(hwndEdit))
			return;
		//
		KEYDATA& data = GetKeyData();
		//
		if (data.arrayKey.empty())
		{
			SetWindowText(hwndEdit, GetEmptyText());
			return;
		}
		//
		CString strText;
		//
		for (std::vector<KEY>::const_iterator it = data.arrayKey.begin();
			it != data.arrayKey.end();
			it++)
		{
			CString strKey;
			UINT nKey = it->nKey;
			switch (nKey)
			{
			case VK_LCONTROL:
			case VK_RCONTROL:
			case VK_CONTROL:
				strKey = _T("Ctrl");
				break;
			case VK_LMENU:
			case VK_RMENU:
			case VK_MENU:
				strKey = _T("Alt");
				break;
			case VK_RSHIFT:
			case VK_LSHIFT:
			case VK_SHIFT:
				strKey = _T("Shift");
				break;
			case VK_LWIN:
			case VK_RWIN:
				strKey = _T("Win");
				break;
			case '0':
			case '1':
			case '2':
		case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
				strKey = (char)nKey;
				break;
			case VK_F1:
			case VK_F2:
			case VK_F3:
			case VK_F4:
			case VK_F5:
			case VK_F6:
			case VK_F7:
			case VK_F8:
			case VK_F9:
			case VK_F10:
			case VK_F11:
			case VK_F12:
			case VK_F13:
			case VK_F14:
			case VK_F15:
			case VK_F16:
			case VK_F17:
			case VK_F18:
			case VK_F19:
			case VK_F20:
			case VK_F21:
			case VK_F22:
			case VK_F23:
			case VK_F24:
				strKey = CString(_T("F")) + WizIntToStr(nKey - VK_F1 + 1);
				break;
			case VK_SNAPSHOT:
				strKey = _T("PrintScreen");
				break;
			case VK_INSERT:
				strKey = _T("Insert");
				break;
			case VK_DELETE:
				strKey = _T("Del");
				break;
			case VK_HOME:
				strKey = _T("Home");
				break;
			case VK_END:
				strKey = _T("End");
				break;
			case VK_PRIOR:
				strKey = _T("PageUp");
				break;
			case VK_NEXT:
				strKey = _T("PageDown");
				break;
			case VK_BACK:
				strKey = _T("Backspace");
				break;
			case VK_ESCAPE:
				strKey = _T("ESC");
				break;

			}
			if (!strKey.IsEmpty())
			{
				strText = strText + _T("+") + strKey;
			}
		}
		//
		strText.Trim(_T(" +"));
		SetWindowText(hwndEdit, strText);
		//
		if (IsAllKeyUp())
		{
			if (-1 == FindNormalKey()
				|| -1 == FindFirstModKey())
			{
				SetWindowText(hwndEdit, GetEmptyText());
			}
			data.arrayKey.clear();
		}
	}
private:
	static LRESULT CALLBACK CWizHotKeyCtrlExImplHookLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam )
	{
		if (HC_ACTION == nCode)
		{
			UINT message = (UINT)wParam;
			//
			KBDLLHOOKSTRUCT* pData = (KBDLLHOOKSTRUCT *)lParam;
			UINT nKey = pData->vkCode;
			//
			if (nKey != VK_TAB
				&& nKey != VK_RETURN)
			{
				HWND hwndEdit = GetEdit();
				if (hwndEdit && IsWindow(hwndEdit))
				{
					KEYDATA& data = GetKeyData();
					if (WM_KEYDOWN == message
						|| WM_SYSKEYDOWN == message)
					{
						TOLOG(_T("Key down"));
						//
						intptr_t nIndex = FindKey(nKey);
						if (-1 == nIndex)
						{
							if (IsNormalKey(nKey))
							{
								RemoveNormalKey();
							}
							//
							KEY k = {nKey, true};
							data.arrayKey.push_back(k);
						}
						else
						{
							data.arrayKey[nIndex].bPressed = false;
						}
						//
						OnKeyChanged();
					}
					else if (WM_KEYUP == message
						|| WM_SYSKEYUP == message)
					{
						TOLOG(_T("Key up"));
						//
						intptr_t nIndex = FindKey(nKey);
						if (-1 != nIndex)
						{
							data.arrayKey[nIndex].bPressed = false;
						}
						OnKeyChanged();
					}
					//
					return TRUE;
				}
			}
		}

		LRESULT RetVal = CallNextHookEx( GetHook(), nCode, wParam, lParam );
		return  RetVal;
	}

public:
	static HHOOK InstallHook()
	{
		if (GetHook())
			return GetHook();
		//
		SetHook(SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)CWizHotKeyCtrlExImplHookLowLevelKeyboardProc, _AtlBaseModule.m_hInst, 0));
		return GetHook();
	}
	static BOOL UninstallHook()
	{
		HHOOK hHook = GetHook();
		if (!hHook)
			return FALSE;
		//
		UnhookWindowsHookEx(hHook);
		//
		SetHook(NULL);
		//
		return TRUE;
	}
	//
	static void SetEdit(HWND hwnd)
	{
		GetEdit() = hwnd;
	}
	static HWND& GetEdit()
	{
		static HWND hwndEdit = NULL;
		return hwndEdit;
	}
	static CString GetEmptyText()
	{
		return ::WizTranslationsTranslateString(_T("None"));
	}
};

template<class T>
class CWizHotKeyCtrlExImpl 
	: public CWindowImpl<CWizHotKeyCtrlExImpl<T>, CEdit>
{
public:
	CWizHotKeyCtrlExImpl()
	{
		m_crBackground = GetSysColor(COLOR_WINDOW);
		m_crText = GetSysColor(COLOR_WINDOWTEXT);
	}
	~CWizHotKeyCtrlExImpl()
	{
	}
	//
	typedef CWindowImpl<CWizHotKeyCtrlExImpl<T>, CEdit> CBaseClass;
private:
	CBrush m_brush;
	COLORREF m_crBackground;
	COLORREF m_crText;
public:
	BEGIN_MSG_MAP(CWizHotKeyCtrlExImpl)
		MESSAGE_HANDLER(OCM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

public:
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizHotKeyCtrlExImplHook::SetEdit(m_hWnd);
		CWizHotKeyCtrlExImplHook::InstallHook();
		//
		bHandled = FALSE;
		//
		return 0;
	}
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWizHotKeyCtrlExImplHook::UninstallHook();
		CWizHotKeyCtrlExImplHook::SetEdit(NULL);
		//
		bHandled = FALSE;
		//
		return 0;
	}
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_brush.IsNull())
		{
			m_brush.CreateSolidBrush(m_crBackground);
		}
		//
		HDC hDC = (HDC)wParam;
		CDCHandle dc(hDC);
		dc.SetBkColor(m_crBackground);
		dc.SetTextColor(m_crText);
		//
		return (LRESULT)m_brush.m_hBrush;
	}
};

class CWizHotKeyCtrlEx : public CWizHotKeyCtrlExImpl<CWizHotKeyCtrlEx>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WizHotKeyCtrlEx"), GetWndClassName())
};



template<class TSettings>
class CWizHotKeyCtrlExWithSettings
	: public CWizHotKeyCtrlEx
{
public:
	CWizHotKeyCtrlExWithSettings()
	{
	}
private:
	CString m_strSectionName;
	CString m_strKeyName;
public:
	void SetStateSection(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDef)
	{
		m_strSectionName = lpszSection;
		m_strKeyName = lpszKey;
		//
		if (m_strSectionName.IsEmpty()
			|| m_strKeyName.IsEmpty())
			return;
		if (!IsWindow())
			return;
		//
		CString strKey = GetHotKeyFromSettings(m_strSectionName, m_strKeyName, lpszDef);
		if (strKey == _T("None"))
		{
			strKey = CWizHotKeyCtrlExImplHook::GetEmptyText();
		}
		SetWindowText(strKey);
	}
	//
	void Save()
	{
		if (m_strSectionName.IsEmpty()
			|| m_strKeyName.IsEmpty())
			return;
		if (!IsWindow())
			return;
		//
		CString strText;
		GetWindowText(strText);
		if (strText.IsEmpty()
			|| strText == CWizHotKeyCtrlExImplHook::GetEmptyText())
		{
			strText = _T("None");
		}
		//
		TSettings settings;
		settings.SetStr(m_strSectionName, m_strKeyName, strText);
	}
	//
	static CString GetHotKeyFromSettings(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDef)
	{
		TSettings settings;
		return settings.GetStr(lpszSection, lpszKey, lpszDef);
	}
};



#endif //_WIZUIBASE_H_

