#pragma once

class CNoteEdit : public CWizAtlBackgroundEdit
{
public:
	CNoteEdit()
	{
	}
public:

public:
	BEGIN_MSG_MAP(CNoteEdit)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		CHAIN_MSG_MAP(CWizAtlBackgroundEdit)
	END_MSG_MAP()
public:
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
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		NodifyParentClientScrollChanged();
		//
		return lRet;
	}
	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		//
		NodifyParentClientScrollChanged();
		//
		return lRet;
	}
};
