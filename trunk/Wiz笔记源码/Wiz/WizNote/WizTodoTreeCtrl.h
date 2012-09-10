#pragma once

#include "../Globals/WizKMTodo.h"
#include "../Globals/WizKMCalendarEvents.h"

#include "TodoLinksDlg.h"

const UINT WM_UM_TODO_TREE_ADD_BLANK = ::RegisterWindowMessage(_T("CWizTodoTreeCtrl_AddBlank"));

class CWizTodoTreeCtrl 
	: public CWizTreeCtrlImpl<CWizTodoTreeCtrl>
	, public CWizTreeCtrlCoreCopyItemEvents<CWizTodoTreeCtrl>
{
public:
	CWizTodoTreeCtrl(CWizKMDatabase* pDatabase)
		: m_pDatabase(pDatabase)
	{
		WizCreateUIFont(m_fontStrikeOut, WIZUIFONT_STRIKEOUT);
		WizCreateUIFont(m_fontStrikeOutBold, WIZUIFONT_STRIKEOUT | WIZUIFONT_BOLD);
		//
		m_bBoldRootItem = FALSE;
		m_il.Create(16, 16, ILC_COLOR32 | ILC_MASK, 5, 2);
		CBitmap bmp;
		if (bmp.LoadBitmap(IDB_BITMAP_TODO_STATE))
		{
			m_il.Add(bmp, RGB(255, 0, 255));
		}
		//
		m_nDrawTextFlags = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX;
		//
		m_bModified = FALSE;
		//
		m_hCursorDefault = ::LoadCursor(NULL, IDC_ARROW);
		m_hCursorHand = ::LoadCursor(NULL, IDC_HAND);
	}
protected:
	CFont m_fontStrikeOut;
	CFont m_fontStrikeOutBold;
	//
	BOOL m_bModified;
	//
	CWizKMDatabase* m_pDatabase;
	//
	typedef std::map<HTREEITEM, CRect> CItemLinkRectMap;
	CItemLinkRectMap m_mapLinkRect;
	//
	HCURSOR m_hCursorDefault;
	HCURSOR m_hCursorHand;
public:
	BEGIN_MSG_MAP(CWizTodoTreeCtrl)
		COMMAND_ID_HANDLER(ID_PRIORITY_URGENTANDIMPORTANT, OnTodoItemUrgentAndImportant)
		COMMAND_ID_HANDLER(ID_PRIORITY_URGENTBUTNOTIMPORTANT, OnTodoItemUrgentButNotImportant)
		COMMAND_ID_HANDLER(ID_PRIORITY_NOTURGENTBUTIMPORTANT, OnTodoItemNotUrgentButImportant)
		COMMAND_ID_HANDLER(ID_PRIORITY_NOTURGENTANDNOTIMPORTANT, OnTodoItemNotUrgentAndNotImportant)
		COMMAND_ID_HANDLER(ID_PRIORITY_NORMAL, OnTodoItemPriorityNormal)
		COMMAND_ID_HANDLER(ID_TODOITEM_NEWTASK, OnAddTask)
		COMMAND_ID_HANDLER(ID_TODOITEM_ADDCHILD, OnAddChild)
		COMMAND_ID_HANDLER(ID_TODOITEM_MOVEUP, OnMoveUp)
		COMMAND_ID_HANDLER(ID_TODOITEM_MOVEDOWN, OnMoveDown)
		COMMAND_ID_HANDLER(ID_TODOITEM_MOVELEFT, OnMoveLeft)
		COMMAND_ID_HANDLER(ID_TODOITEM_MOVERIGHT, OnMoveRight)
		COMMAND_ID_HANDLER(ID_TODOITEM_DELETE, OnDelete)
		COMMAND_ID_HANDLER(ID_TODOITEM_EDIT, OnEdit)
		COMMAND_ID_HANDLER(ID_TODOITEM_CREATELINK, OnCreateLink)
		COMMAND_ID_HANDLER(ID_TODOITEM_DELAYTOTOMORROW, OnDelayToTomorrow)
		COMMAND_ID_HANDLER(ID_TODOITEM_DELAYTO, OnDelayTo)
		COMMAND_RANGE_HANDLER(ID_TODOITEM_0, ID_TODOITEM_100, OnTodoItemState)
		MESSAGE_HANDLER(WM_UM_TODO_TREE_ADD_BLANK, OnAddBlank)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		REFLECTED_NOTIFY_CODE_HANDLER(NM_DBLCLK, OnNMDblclick)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDING, OnItemExpanding)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_BEGINLABELEDIT, OnBeginLabelEdit)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_ENDLABELEDIT, OnEndLabelEdit)
		CHAIN_MSG_MAP(CWizTreeCtrlImpl<CWizTodoTreeCtrl>)
	END_MSG_MAP()
	//
	//
	void SetAllChildItemState(HTREEITEM hItemParent, WIZTODOSTATE eState)
	{
		HTREEITEM hItem = GetChildItem(hItemParent);
		while (hItem)
		{
			SetItemTodoState(hItem, eState, FALSE);
			//
			SetAllChildItemState(hItem, eState);
			//
			hItem = GetNextSiblingItem(hItem);
		}
	}
	//
	BOOL GetAllChildItemHaveSameState(HTREEITEM hItemParent, WIZTODOSTATE eState)
	{
		HTREEITEM hItem = GetChildItem(hItemParent);
		while (hItem)
		{
			if (GetItemTodoState(hItem) != eState)
				return FALSE;
			//
			if (!GetAllChildItemHaveSameState(hItem, eState))
				return FALSE;
			//
			hItem = GetNextSiblingItem(hItem);
		}
		//
		return TRUE;
	}
	//
	void AutoSetParentItemState(HTREEITEM hItemChild, WIZTODOSTATE eState)
	{
		HTREEITEM hItem = GetParentItem(hItemChild);
		while (hItem)
		{
			if (GetAllChildItemHaveSameState(hItem, eState))
			{
				SetItemTodoState(hItem, eState, FALSE);
			}
			else
			{
				SetItemTodoState(hItem, todoStateMixed, FALSE);
			}
			//
			hItem = GetParentItem(hItem);
		}
	}
	
	virtual void OnItemCheckStateChanged(HTREEITEM hItem, WIZTODOSTATE eOldState, WIZTODOSTATE eNewState)
	{
		if (!hItem)
			return;
		//
		WIZTODOSTATE eState = GetItemTodoState(hItem);
		//
		if (todoState100 == eState
			|| todoState0 == eState)
		{
			SetAllChildItemState(hItem, eState);
			AutoSetParentItemState(hItem, eState);
		}
		else
		{
			//SetAllChildItemState(hItem, eState);
			AutoSetParentItemState(hItem, todoState100);
		}
		//
		static LPCTSTR lpszOnItemCheckStateChanged = _T("OnItemCheckStateChanged");
		GetParent().SendMessage(WIZ_WM_UM_NOTIFY_PARENT_COMMAND, (WPARAM)lpszOnItemCheckStateChanged, (LPARAM)GetItemTodo(hItem));
	}
	virtual void OnItemCheckStyleChanged(HTREEITEM hItem, WIZTODOPRIOR eOldStyle, WIZTODOPRIOR eNewStyle)
	{
	}
	//
	BOOL OnLButtonDown()
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		//
		UINT uFlags = 0;
		HTREEITEM hItem = HitTest(pt, &uFlags);
		if (!hItem)
			return FALSE;
		//
		CItemLinkRectMap::const_iterator it = m_mapLinkRect.find(hItem);
		if (it != m_mapLinkRect.end())
		{
			if (it->second.PtInRect(pt))
			{
				OnTodoLinkClicked(hItem);
				return TRUE;
			}
		}
		//
		if (TVHT_ONITEMICON & uFlags)
		{
			WIZTODOSTATE eState = GetItemTodoState(hItem);
			//
			WIZTODOSTATE eNewState = todoState100;
			if (todoState100 == eState)
			{
				eNewState = todoState0;
			}
			//
			SetItemTodoState(hItem, eNewState, TRUE);
		}
		else if(TVHT_ONITEMLABEL & uFlags)
		{
			WIZTODODATA* pData = GetItemTodo(hItem);
			ATLASSERT(pData);
			if (!pData)
				return FALSE;
			//
			if (pData->bBlank)
			{
				EditLabel(hItem);
				return TRUE;
			}
		}
		//
		return FALSE;
	}
	//
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (OnLButtonDown())
			return 0;
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		return lRet;
	}
	LRESULT OnNMDblclick(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		//
		UINT uFlags = 0;
		HTREEITEM hItem = HitTest(pt, &uFlags);
		if (!hItem)
			return 0;
		//
		if (TVHT_ONITEMLABEL & uFlags)
		{
			EditLabel(hItem);
		}
		//
		return 0;
	}
	LRESULT OnBeginLabelEdit(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTVDISPINFO* pInfo = (NMTVDISPINFO *)(pNMHDR);
		//
		WIZTODODATA* pData = GetItemTodo(pInfo->item.hItem);
		ATLASSERT(pData);
		if (!pData)
			return TRUE;
		//
		if (pData->bBlank)
		{
			//*pInfo->item.pszText = '\0';
			SetItemText(pInfo->item.hItem, _T(""));
		}
		//
		return 0;
	}
	//
	LRESULT OnEndLabelEdit(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTVDISPINFO* pInfo = (NMTVDISPINFO *)(pNMHDR);
		//
		WIZTODODATA* pData = GetItemTodo(pInfo->item.hItem);
		ATLASSERT(pData);
		if (!pData)
			return FALSE;
		//
		if (!pInfo->item.pszText 
			|| !(*pInfo->item.pszText))
		{
			if (pData->bBlank)
			{
				SetItemText(pInfo->item.hItem, pData->strText);
			}
			return FALSE;
		}
		//
		CString strText = pInfo->item.pszText;
		//
		HTREEITEM hItem = pInfo->item.hItem;
		HTREEITEM hExistsItem = FindChildItem(GetParentItem(hItem), strText, FALSE, FALSE);
		if (hExistsItem)
		{
			SelectItem(hExistsItem);
			//
			if (pData->bBlank)
			{
				SetItemText(hItem, pData->strText);
			}
			return FALSE;
		}
		//
		pData->strText = strText;
		pData->tModified = COleDateTime::GetCurrentTime();
		//
		if (pData->bBlank)
		{
			//
			pData->bBlank = FALSE;
			//
			PostMessage(WM_UM_TODO_TREE_ADD_BLANK, 0, 0);
		}
		//
		SetModified(TRUE);
		//
		return TRUE;
	}
	//
	void NodifyParentClientScrollChanged()
	{
		CWindow parent = GetParent();
		if (parent.IsWindow())
		{
			parent.SendMessage(WIZ_WM_UM_CLIENT_SCROLL_CHANGED, 0, 0);
		}
	}
	//
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		NodifyParentClientScrollChanged();
		//
		return lRet;
	}
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UINT nKey = (UINT)wParam;
		//
		if (VK_INSERT == nKey)
		{
			PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_ADDCHILD, 0), 0);
			return 0;
		}
		else if (VK_DELETE == nKey)
		{
			PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_DELETE, 0), 0);
			return 0;
		}
		else if (VK_UP == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVEUP, 0), 0);
				return 0;
			}
		}
		else if (VK_DOWN == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVEDOWN, 0), 0);
				return 0;
			}
		}
		else if (VK_LEFT == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVELEFT, 0), 0);
			}
			return TRUE;
		}
		else if (VK_RIGHT == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVERIGHT, 0), 0);
			}
			return TRUE;
		}
		else if (VK_TAB == nKey)
		{
			if (GetKeyState(VK_SHIFT) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVELEFT, 0), 0);
			}
			else
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_MOVERIGHT, 0), 0);
			}
			return TRUE;
		}
		else if (VK_RETURN == nKey)
		{
			if (GetKeyState(VK_SHIFT) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_EDIT, 0), 0);
			}
			else
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_NEWTASK, 0), 0);
			}
			//
			return 0;
		}
		else if (VK_F2 == nKey)
		{
			PostMessage(WM_COMMAND, MAKEWPARAM(ID_TODOITEM_EDIT, 0), 0);
			//
			return 0;
		}
		else if ('1' == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_PRIORITY_URGENTANDIMPORTANT, 0), 0);
			}
			//
			return 0;
		}
		else if ('2' == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_PRIORITY_URGENTBUTNOTIMPORTANT, 0), 0);
			}
			//
			return 0;
		}
		else if ('3' == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_PRIORITY_NOTURGENTBUTIMPORTANT, 0), 0);
			}
			//
			return 0;
		}
		else if ('4' == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_PRIORITY_NOTURGENTANDNOTIMPORTANT, 0), 0);
			}
			//
			return 0;
		}
		else if ('0' == nKey)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(ID_PRIORITY_NORMAL, 0), 0);
			}
			//
			return 0;
		}
		//
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		if (VK_UP == nKey
			|| VK_DOWN == nKey
			|| VK_PRIOR == nKey
			|| VK_NEXT == nKey
			|| VK_HOME == nKey
			|| VK_END == nKey)
		{
			NodifyParentClientScrollChanged();
		}
		//
		return lRet;
	}
	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPoint ptCursor;
		GetCursorPos(&ptCursor);
		//
		ScreenToClient(&ptCursor);
		//
		UINT uFlags = 0;
		HTREEITEM hItem = HitTest(ptCursor, &uFlags);
		if (!hItem)
			return 0;
		//
		CItemLinkRectMap::const_iterator it = m_mapLinkRect.find(hItem);
		if (it != m_mapLinkRect.end())
		{
			if (it->second.PtInRect(ptCursor))
			{
				SetCursor(m_hCursorHand);
				return TRUE;
			}
		}
		SetCursor(m_hCursorDefault);
		return TRUE;
	}
	
	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		NodifyParentClientScrollChanged();
		//
		return lRet;
	}
	LRESULT OnAddBlank(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hParentItem = GetFirstCommandItem();
		if (hParentItem)
		{
			hParentItem = GetParentItem(hParentItem);
		}
		//
		HTREEITEM hItem = GetBlankTodoItem(hParentItem, TRUE);
		if (hItem)
		{
			SelectItem(hItem);
			EnsureVisible(hItem);
			EditLabel(hItem);
		}
		//
		SetModified(TRUE);
		//
		return 0;
	}

	void SetItemTodoState(HTREEITEM hItem, WIZTODOSTATE eState, BOOL bNotify = FALSE)
	{
		if (!hItem)
			return;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		ATLASSERT(pData);
		if (!pData)
			return;
		//
		WIZTODOSTATE oldState = pData->eState;
		pData->eState = eState;
		//
		if (eState == todoState100)
		{
			pData->tCompleted = COleDateTime::GetCurrentTime();
		}
		//
		InvalidateItem(hItem);
		//
		SetModified(TRUE);
		//
		if (bNotify && oldState != eState)
		{
			OnItemCheckStateChanged(hItem, oldState, eState);
		}
	}
	//
	WIZTODOSTATE GetItemTodoState(HTREEITEM hItem)
	{
		if (!hItem)
			return todoState0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		ATLASSERT(pData);
		if (!pData)
			return todoState0;
		//
		return pData->eState;
	}
	void SetItemTodoPrior(HTREEITEM hItem, WIZTODOPRIOR ePrior, BOOL bNotify = FALSE)
	{
		if (!hItem)
			return;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		ATLASSERT(pData);
		if (!pData)
			return;
		//
		WIZTODOPRIOR oldStyle = pData->ePrior;
		pData->ePrior = ePrior;
		if (bNotify && oldStyle != ePrior)
		{
			OnItemCheckStyleChanged(hItem, oldStyle, ePrior);
		}
		//
		InvalidateItem(hItem);
		//
		SortChildItems(GetParentItem(hItem), FALSE);
		//
		SetModified(TRUE);
	}
	WIZTODOPRIOR GetItemTodoPrior(HTREEITEM hItem)
	{
		if (!hItem)
			return todoPriorNormal;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		ATLASSERT(pData);
		if (!pData)
			return todoPriorNormal;
		//
		return pData->ePrior;
	}
	LRESULT OnTodoItemUrgentAndImportant(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		SetItemTodoPrior(hItem, todoPriorUrgentAndImportant, TRUE);
		return 0;
	}
	LRESULT OnTodoItemUrgentButNotImportant(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		SetItemTodoPrior(hItem, todoPriorUrgent, TRUE);
		return 0;
	}
	LRESULT OnTodoItemNotUrgentButImportant(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		SetItemTodoPrior(hItem, todoPriorImportant, TRUE);
		return 0;
	}
	LRESULT OnTodoItemNotUrgentAndNotImportant(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		SetItemTodoPrior(hItem, todoPriorNotUrgentAndNotImportant, TRUE);
		return 0;
	}
	LRESULT OnTodoItemPriorityNormal(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		SetItemTodoPrior(hItem, todoPriorNormal, TRUE);
		return 0;
	}

	LRESULT OnAddTask(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hParentItem = GetFirstCommandItem();
		if (hParentItem)
		{
			hParentItem = GetParentItem(hParentItem);
		}
		
		HTREEITEM hNewItem = GetBlankTodoItem(hParentItem, TRUE);
		if (!hNewItem)
			return 0;
		//
		SelectItem(hNewItem);
		EnsureVisible(hNewItem);
		EditLabel(hNewItem);
		//
		return 0;
	}
	LRESULT OnAddChild(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		WIZTODODATA data(WizFormatString0(IDS_ADD_TASK), todoState0, todoPriorNormal);
		//
		HTREEITEM hChildItem = AddTodo(hItem, data);
		if (!hChildItem)
			return 0;
		//
		SelectItem(hChildItem);
		EnsureVisible(hChildItem);
		EditLabel(hChildItem);
		//
		SetModified(TRUE);
		//
		return 0;
	}
	LRESULT OnTodoItemState(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		WIZTODOSTATE eNewState = todoState0;
		switch (wID)
		{
		case ID_TODOITEM_0:
			eNewState = todoState0;
			break;
		case ID_TODOITEM_25:
			eNewState = todoState25;
			break;
		case ID_TODOITEM_50:
			eNewState = todoState50;
			break;
		case ID_TODOITEM_75:
			eNewState = todoState75;
			break;
		case ID_TODOITEM_100:
			eNewState = todoState100;
			break;
		}
		//
		SetItemTodoState(hItem, eNewState, TRUE);
		//
		return 0;
	}

	LRESULT OnItemExpanding(int nCtrlID, LPNMHDR pNMHDR, BOOL& bHandled)
	{
		NMTREEVIEW* pNMTreeView = (NMTREEVIEW *)pNMHDR;
		//
		if (pNMTreeView->action == TVE_COLLAPSE)
			return TRUE;
		//
		return FALSE;
	}
protected:
	CImageList m_il;
	CMenu m_menu;
public:
	//
	DECLARE_WND_SUPERCLASS(_T("Wiz_TodoTreeCtrl"), GetWndClassName())
	//
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | TVS_SHOWSELALWAYS | TVS_EDITLABELS | TVS_NOHSCROLL;
	}
	//
	BOOL IsBlankItem(HTREEITEM hItem)
	{
		if (!hItem)
			return FALSE;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		ATLASSERT(pData);
		if (!pData)
			return FALSE;
		//
		return pData->bBlank;
	}
	//
	HTREEITEM GetBlankTodoItem(HTREEITEM hParentItem, BOOL bCreate)
	{
		HTREEITEM hItem = GetChildItem(hParentItem);
		while (hItem)
		{
			WIZTODODATA* pData = GetItemTodo(hItem);
			ATLASSERT(pData);
			if (!pData)
				return NULL;
			//
			if (pData->bBlank)
				return hItem;
			//
			hItem = GetNextSiblingItem(hItem);
		}
		if (!bCreate)
			return NULL;
		//
		WIZTODODATA data(WizFormatString0(IDS_ADD_TASK), todoState0, todoPriorNormal);
		data.bBlank = TRUE;
		//
		SetModified(TRUE);
		//
		return AddTodo(hParentItem, data);
	}
	//
	virtual int CalItemHeight()
	{
		if (!IsWindow())
			return 16;
		//
		return std::max<int>(16, WizGetFontHeight(m_hWnd, m_fontTreeFont));
	}
	virtual BOOL OnInitControl()
	{
		CWizTreeCtrlImpl<CWizTodoTreeCtrl>::OnInitControl();
		SetImageList(m_il, TVSIL_NORMAL);
		//		
		return TRUE;
	}
	//
	virtual void GetClientRectEx(CRect& rc)
	{
		CRect rcWindow;
		GetWindowRect(rcWindow);
		//
		int nScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL);
		//
		rcWindow.right -= nScrollBarWidth;
		//
		rc = CRect(0, 0, rcWindow.Width(), rcWindow.Height());
	}
	//
	virtual void OnDeleteItemData(LPARAM lParam)
	{
		WIZTODODATA* pData = (WIZTODODATA*)lParam;
		if (pData)
		{
			delete pData;
		}
	}
	virtual void DrawItemImage(CDCHandle dcPaint, CImageList il, HTREEITEM hItem, POINT pt)
	{
		WIZTODOSTATE eState = GetItemTodoState(hItem);
		//
		il.Draw(dcPaint, eState, pt, ILD_TRANSPARENT);
	}
	//
	virtual void SetItemTextFont(CDCHandle dcPaint, HTREEITEM hItem)
	{
		WIZTODOSTATE eState = GetItemTodoState(hItem);
		WIZTODOPRIOR ePrior = GetItemTodoPrior(hItem);
		//
		if (todoState100 == eState)
		{
			switch (ePrior)
			{
			case todoPriorImportant:
			case todoPriorUrgentAndImportant:
				dcPaint.SelectFont(m_fontStrikeOutBold);
				break;
			default:
				dcPaint.SelectFont(m_fontStrikeOut);
				break;
			}
		}
		else
		{
			switch (ePrior)
			{
			case todoPriorImportant:
			case todoPriorUrgentAndImportant:
				dcPaint.SelectFont(m_fontTreeFontBold);
				break;
			default:
				dcPaint.SelectFont(m_fontTreeFont);
				break;
			}
		}
	}
	virtual COLORREF GetItemTextColor(HTREEITEM hItem)
	{
		if (GetItemState(hItem, TVIS_SELECTED) == TVIS_SELECTED)
		{
			return CWizTreeCtrlBase::GetItemTextColor(hItem);
		}
		else
		{
			WIZTODODATA* pData = GetItemTodo(hItem);
			if (!pData)
				return WIZ_TODO_TEXT_COLOR_DEFAULT;
			//
			if (pData->bBlank)
			{
				return RGB(0, 0, 255);
			}
			//
			return WizTodoGetTextColor(*pData);
		}
	}
	virtual HMENU GetContextMenu(HTREEITEM hFocusedItem)
	{
		if (!m_menu.IsMenu())
		{
			if (!m_menu.LoadMenu(IDR_MENU_TODO_ITEM))
				return NULL;
			//
			WizTranslationsTranslateMenu(m_menu);
		}
		//
		if (!m_menu.IsMenu())
			return NULL;
		//
		return m_menu.GetSubMenu(0);
	}
	virtual void OnUpdateContextMenu(HTREEITEM hFocusedItem, HMENU hMenu)
	{
		if (!hFocusedItem)
			return;
		//
		WIZTODOSTATE eState = GetItemTodoState(hFocusedItem);
		WIZTODOPRIOR ePrior = GetItemTodoPrior(hFocusedItem);
		//
		CMenuHandle menu(hMenu);
		//
		UINT nEnabled = MF_BYCOMMAND | MF_ENABLED;
		UINT nDisabled = MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
		//
		menu.EnableMenuItem(ID_TODOITEM_MOVEUP, CanMoveUp(hFocusedItem) ? nEnabled : nDisabled);
		menu.EnableMenuItem(ID_TODOITEM_MOVEDOWN, CanMoveDown(hFocusedItem) ? nEnabled : nDisabled);
		menu.EnableMenuItem(ID_TODOITEM_MOVELEFT, CanMoveLeft(hFocusedItem) ? nEnabled : nDisabled);
		menu.EnableMenuItem(ID_TODOITEM_MOVERIGHT, CanMoveRight(hFocusedItem) ? nEnabled : nDisabled);
		//
		CMenuHandle menuPrior = menu.GetSubMenu(0);
		if (menuPrior.IsMenu())
		{
			UINT nPriorMenuID = 0;
			switch (ePrior)
			{
			case todoPriorNotUrgentAndNotImportant:
				nPriorMenuID = ID_PRIORITY_NOTURGENTANDNOTIMPORTANT;
				break;
			case todoPriorNormal:
				nPriorMenuID = ID_PRIORITY_NORMAL;
				break;
			case todoPriorImportant:
				nPriorMenuID = ID_PRIORITY_NOTURGENTBUTIMPORTANT;
				break;
			case todoPriorUrgent:
				nPriorMenuID = ID_PRIORITY_URGENTBUTNOTIMPORTANT;
				break;
			case todoPriorUrgentAndImportant:
				nPriorMenuID = ID_PRIORITY_URGENTANDIMPORTANT;
				break;
			}
			//
			menuPrior.CheckMenuRadioItem(ID_PRIORITY_NOTURGENTANDNOTIMPORTANT, ID_PRIORITY_URGENTANDIMPORTANT, nPriorMenuID, MF_BYCOMMAND);
		}
		//
		CMenuHandle menuState = menu.GetSubMenu(1);
		if (menuState.IsMenu())
		{
			UINT nStateMenuItemID = 0;
			switch (eState)
			{
			case todoState0:
				nStateMenuItemID = ID_TODOITEM_0;
				break;
			case todoState25:
				nStateMenuItemID = ID_TODOITEM_25;
				break;
			case todoState50:
				nStateMenuItemID = ID_TODOITEM_50;
				break;
			case todoState75:
				nStateMenuItemID = ID_TODOITEM_75;
				break;
			case todoState100:
				nStateMenuItemID = ID_TODOITEM_100;
				break;
			}
			menuState.CheckMenuRadioItem(ID_TODOITEM_0, ID_TODOITEM_100, nStateMenuItemID, MF_BYCOMMAND);
		}
		//
	}
	//
	virtual void DrawItemText(CDCHandle dcPaint, HTREEITEM hItem, CRect& rcItemText, LPCTSTR lpszText)
	{
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return;
		//
		BOOL bLink = !pData->arrayLinkedDocumentGUID.empty();
		//
		CSize szText;
		dcPaint.GetTextExtent(lpszText, -1, &szText);
		if (bLink)
		{
			int nWidth = std::min<int>(szText.cx + 2 + 16, rcItemText.Width());
			//
			rcItemText.right = rcItemText.left + nWidth;
			//
			rcItemText.right -= 16;
		}
		//
		CWizTreeCtrlBase::DrawItemText(dcPaint, hItem, rcItemText, lpszText);
		//
		if (!bLink)
			return;
		//
		CRect rcLink = rcItemText;
		rcLink.left = rcLink.right;
		rcLink.right = rcLink.left + 16;
		rcLink.top = rcLink.CenterPoint().y - 16 / 2;
		rcLink.bottom = rcLink.top + 16;
		//
		m_il.Draw(dcPaint, 6, rcLink.TopLeft(), ILD_TRANSPARENT);
		//
		m_mapLinkRect[hItem] = rcLink;
	}
	virtual CString GetItemStateID(HTREEITEM hItem)
	{
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return CString();
		//
		return pData->strText + WizInt64ToStr(pData->nOrder);
	}
public:
	WIZTODODATA* GetItemTodo(HTREEITEM hItem)
	{
		if (!hItem)
			return NULL;
		//
		WIZTODODATA* pData = (WIZTODODATA *)GetItemData(hItem);
		ATLASSERT(pData);
		//
		return pData;
	}
	HTREEITEM AddTodo(HTREEITEM hItemParent, const WIZTODODATA& data)
	{
		HTREEITEM hItem = InsertItemWithData(hItemParent, data.strText, (LPARAM)(new WIZTODODATA(data)));
		if (hItemParent)
		{
			Expand(hItemParent, TVE_EXPAND);
		}
		//
		NodifyParentClientScrollChanged();
		//
		SortChildItems(hItemParent);
		//
		return hItem;
	}
	HTREEITEM AddTodo(HTREEITEM hItemParent, LPCTSTR lpszText, WIZTODOSTATE eState, WIZTODOPRIOR ePrior)
	{
		HTREEITEM hNewItem = AddTodo(hItemParent, WIZTODODATA(lpszText, eState, ePrior));
		//
		return hNewItem;
	}
	//
public:
	LRESULT OnDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		if (IDYES != WizMessageBox1(IDS_DELETE_TODO_ITEM, GetItemTextReturn(hItem), MB_ICONQUESTION | MB_YESNO, m_hWnd))
			return 0;
		//
		DeleteItem(hItem);
		//
		SetModified(TRUE);
		//
		return 0;
	}
	LRESULT OnEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		EditLabel(hItem);
		//
		return 0;
	}
	
	LRESULT OnCreateLink(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return 0;
		//
		CTodoLinksDlg dlg(m_pDatabase, pData->arrayLinkedDocumentGUID);
		if (IDOK != dlg.DoModal())
			return 0;
		//
		pData->arrayLinkedDocumentGUID.assign(dlg.m_arrayDocumentGUID.begin(), dlg.m_arrayDocumentGUID.end());
		//
		SetModified(TRUE);
		//
		InvalidateItem(hItem);
		//
		return 0;
	}
	//
	BOOL CopyTodo(HTREEITEM hItem, const COleDateTime& t)
	{
		WIZTODODATAEX data;
		if (!ItemToData(hItem, data))
			return FALSE;
		//
		CComPtr<IWizDocument> spDocument;
		if (!WizKMGetTodoDocument(m_pDatabase, t, TRUE, TRUE, spDocument))
		{
			TOLOG(_T("Failed to get todo list document!"));
			return FALSE;
		}
		if (!spDocument)
		{
			TOLOG(_T("Failed to create document!"));
			return FALSE;
		}
		//
		WIZTODODATAEX::CWizTodoDataExArray arrayData;
		if (!WizDocumentGetTodoData(spDocument, arrayData))
		{
			TOLOG1(_T("Failed to get todo list data from %1"), CWizKMDatabase::GetDocumentTitle(spDocument));
			//return FALSE;
		}
		arrayData.insert(arrayData.begin(), data);
		//
		if (!WizDocumentSetTodoData(spDocument, arrayData))
		{
			TOLOG1(_T("Failed to set todo list data from %1"), CWizKMDatabase::GetDocumentTitle(spDocument));
			return FALSE;
		}
		//
		return TRUE;
	}
	
	LRESULT OnDelayToTomorrow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return 0;
		//
		COleDateTime t = COleDateTime::GetCurrentTime();
		COleDateTime tTomorrow = t + COleDateTimeSpan(1, 0, 0, 0);
		//
		if (!CopyTodo(hItem, tTomorrow))
		{
			WizMessageBox(IDS_FAILED_TO_COPY_TODO_ITEM);
		}
		//
		return 0;
	}
	LRESULT OnDelayTo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return 0;
		//
		CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
		if (!spCommonUI)
			return 0;
		//
		DATE dt = 0;
		if (S_OK != spCommonUI->SelectDay(COleDateTime::GetCurrentTime(), &dt))
			return 0;
		//
		if (!CopyTodo(hItem, dt))
		{
			WizMessageBox(IDS_FAILED_TO_COPY_TODO_ITEM);
		}
		//
		return 0;
	}
	//
	virtual int CompareItem(LPARAM lParam1, LPARAM lParam2)
	{
		WIZTODODATA* pData1 = (WIZTODODATA *)lParam1;
		WIZTODODATA* pData2 = (WIZTODODATA *)lParam2;
		//
		if (pData1->bBlank && pData2->bBlank)
			return 0;
		else if (pData1->bBlank)
			return 1;
		else if (pData2->bBlank)
			return -1;
		//
		if (pData1->ePrior == pData2->ePrior)
		{
			return int(__int64(pData1->nOrder) - __int64(pData2->nOrder));
		}
		else
		{
			return pData2->ePrior - pData1->ePrior;
		}
	}
	//
	
	LRESULT OnMoveUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		if (!CanMoveUp(hItem))
			return 0;
		//
		HTREEITEM hPrevItem = GetPrevSiblingItem(hItem);
		if (!hPrevItem)
			return 0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		WIZTODODATA* pPrevData = GetItemTodo(hPrevItem);
		if (!pData)
			return 0;
		if (!pPrevData)
			return 0;
		//
		__int64 nOrder = pData->nOrder;
		pData->nOrder = pPrevData->nOrder;
		pPrevData->nOrder = nOrder;
		//
		SortChildItems(GetParentItem(hItem), FALSE);
		//
		SetModified(TRUE);
		//
		return 0;
	}
	
	LRESULT OnMoveDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		if (!CanMoveDown(hItem))
			return 0;
		//
		HTREEITEM hNextItem = GetNextSiblingItem(hItem);
		if (!hNextItem)
			return 0;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		WIZTODODATA* pNextData = GetItemTodo(hNextItem);
		if (!pData)
			return 0;
		if (!pNextData)
			return 0;
		//
		__int64 nOrder = pData->nOrder;
		pData->nOrder = pNextData->nOrder;
		pNextData->nOrder = nOrder;
		//
		SortChildItems(GetParentItem(hItem), FALSE);
		//
		SetModified(TRUE);
		//
		return 0;
	}
	//
	virtual LPARAM TCCI_OnCopyData(CWizTreeCtrlCore<CWizTodoTreeCtrl>* pTreeCtrl, HTREEITEM hItemSrc)
	{
		WIZTODODATA* pData = GetItemTodo(hItemSrc);
		if (!pData)
		{
			ATLASSERT(FALSE);
			return NULL;
		}
		//
		WIZTODODATA* pNewData = new WIZTODODATA(*pData);
		//
		return (LPARAM)pNewData;
	}
	//
	LRESULT OnMoveLeft(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		if (!CanMoveLeft(hItem))
			return 0;
		//
		MoveLeft(hItem);
		SetModified(TRUE);
		//
		return 0;
	}
	LRESULT OnMoveRight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HTREEITEM hItem = GetFirstCommandItem();
		if (!hItem)
			return 0;
		//
		if (!CanMoveRight(hItem))
			return 0;
		//
		MoveRight(hItem, TRUE);
		SetModified(TRUE);
		//
		return 0;
	}
	//
	virtual BOOL CanMoveLeft(HTREEITEM hItem)
	{
		if (!hItem)
			return FALSE;
		//
		if (!CWizTreeCtrlImpl::CanMoveLeft(hItem))
			return FALSE;
		//
		if (IsBlankItem(hItem))
			return FALSE;
		//
		return TRUE;
	}
	virtual BOOL CanMoveRight(HTREEITEM hItem)
	{
		if (!hItem)
			return FALSE;
		//
		if (!CWizTreeCtrlImpl::CanMoveRight(hItem))
			return FALSE;
		//
		if (IsBlankItem(hItem))
			return FALSE;
		//
		return TRUE;
	}
	//
	virtual BOOL CanMoveUp(HTREEITEM hItem)
	{
		if (!hItem)
			return FALSE;
		//
		if (IsBlankItem(hItem))
			return FALSE;
		//
		HTREEITEM hPrevItem = GetPrevSiblingItem(hItem);
		if (!hPrevItem)
			return FALSE;
		//
		WIZTODOPRIOR ePrior = GetItemTodoPrior(hItem);
		WIZTODOPRIOR ePrevPrior = GetItemTodoPrior(hPrevItem);
		if (ePrior != ePrevPrior)
			return FALSE;
		//
		return TRUE;
	}
	//
	virtual BOOL CanMoveDown(HTREEITEM hItem)
	{
		if (!hItem)
			return FALSE;
		//
		if (IsBlankItem(hItem))
			return FALSE;
		//
		HTREEITEM hNextItem = GetNextSiblingItem(hItem);
		if (!hNextItem)
			return FALSE;
		//
		WIZTODOPRIOR ePrior = GetItemTodoPrior(hItem);
		WIZTODOPRIOR eNextPrior = GetItemTodoPrior(hNextItem);
		if (ePrior != eNextPrior)
			return FALSE;
		//
		return TRUE;
	}
	//
	BOOL ItemToData(HTREEITEM hItem, WIZTODODATAEX& data)
	{
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return FALSE;
		//
		data = WIZTODODATAEX(*pData);
		//
		HTREEITEM hChildItem = GetChildItem(hItem);
		while (hChildItem)
		{
			if (!IsBlankItem(hChildItem))
			{
				WIZTODODATAEX dataChild;
				if (!ItemToData(hChildItem, dataChild))
					return FALSE;
				//
				data.arrayChild.push_back(dataChild);
			}
			//
			hChildItem = GetNextSiblingItem(hChildItem);
		}
		//
		return TRUE;
	}
	//
	BOOL GetAllData(WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		HTREEITEM hChildItem = GetChildItem(NULL);
		while (hChildItem)
		{
			if (!IsBlankItem(hChildItem))
			{
				WIZTODODATAEX dataChild;
				if (!ItemToData(hChildItem, dataChild))
					return FALSE;
				//
				arrayData.push_back(dataChild);
			}
			//
			hChildItem = GetNextSiblingItem(hChildItem);
		}
		//
		return TRUE;
	}
	BOOL DataToItem(HTREEITEM hItemParent, const WIZTODODATAEX& data)
	{
		HTREEITEM hNewItem = AddTodo(hItemParent, data);
		if (!hNewItem)
		{
			TOLOG(_T("Failed to insert todo item!"));
			return FALSE;
		}
		//
		for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = data.arrayChild.begin();
			it != data.arrayChild.end();
			it++)
		{
			if (!DataToItem(hNewItem, *it))
			{
				TOLOG(_T("Failed to insert child todo item!"));
				return FALSE;
			}
		}
		//
		return TRUE;
	}
	//
	BOOL SetAllData(const WIZTODODATAEX::CWizTodoDataExArray& arrayData)
	{
		for (WIZTODODATAEX::CWizTodoDataExArray::const_iterator it = arrayData.begin();
			it != arrayData.end();
			it++)
		{
			if (!DataToItem(NULL, *it))
			{
				TOLOG(_T("Failed to insert todo item!"));
				return FALSE;
			}
		}
		return TRUE;
	}
	//
	CComPtr<IWizTodoItemCollection> GetAllData()
	{
		WIZTODODATAEX::CWizTodoDataExArray arrayData;
		if (!GetAllData(arrayData))
			return NULL;
		//
		return WizDataArrayToTodoItemCollection(arrayData);
	}
	BOOL SetAllData(IWizTodoItemCollection* pColl)
	{
		DeleteAllItems();
		m_mapLinkRect.clear();
		//
		WIZTODODATAEX::CWizTodoDataExArray arrayData;
		if (!WizTodoItemCollectionToDataArray(pColl, arrayData))
			return FALSE;
		//
		return SetAllData(arrayData);
	}
	//
	BOOL GetModify() const
	{
		return m_bModified;
	}
	//
	void SetModified(BOOL b)
	{
		m_bModified = b;
	}
	void OnTodoLinkClicked(HTREEITEM hItem)
	{
		if (!hItem)
			return;
		//
		if (!m_pDatabase)
			return;
		//
		WIZTODODATA* pData = GetItemTodo(hItem);
		if (!pData)
			return;
		//
		CString strDocumentGUID;
		//
		if (pData->arrayLinkedDocumentGUID.empty())
		{
			ATLASSERT(FALSE);
			return;
		}
		else if (pData->arrayLinkedDocumentGUID.size() == 1)
		{
			strDocumentGUID = pData->arrayLinkedDocumentGUID[0];
		}
		else
		{
			//
			CMenu menu;
			if (!menu.CreatePopupMenu())
				return;
			//
			const UINT ID_TODO_LINK_BEGIN = ID_NOTES_BEGIN;
			//
			for (CWizStdStringArray::const_iterator it = pData->arrayLinkedDocumentGUID.begin();
				it != pData->arrayLinkedDocumentGUID.end();
				it++)
			{
				CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(*it);
				if (!spDocument)
					continue;
				//
				CString strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
				if (strTitle.GetLength() > 50)
				{
					strTitle = strTitle.Left(50) + _T("...");
				}
				//
				menu.AppendMenu(MF_STRING, ID_TODO_LINK_BEGIN + int(it - pData->arrayLinkedDocumentGUID.begin()), strTitle);
			}
			//
			menu.AppendMenu(MF_SEPARATOR);
			menu.AppendMenu(MF_STRING, ID_TODOITEM_CREATELINK, WizFormatString0(IDS_EDIT_LINK));

			//
			CPoint pt;
			GetCursorPos(&pt);
			//
			UINT nID = menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD, pt.x, pt.y, m_hWnd, NULL);
			if (0 == nID)
				return;
			//
			int nIndex = nID - ID_TODO_LINK_BEGIN;
			//
			if (nIndex < 0 || nIndex >= int(pData->arrayLinkedDocumentGUID.size()))
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);
				return;
			}
			//
			strDocumentGUID = pData->arrayLinkedDocumentGUID[nIndex];
		}
		//
		CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(strDocumentGUID);
		if (!spDocument)
			return;
		//
		WizKMViewDocumentEx(spDocument);
	}
};



