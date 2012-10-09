#pragma once

#include "../../WizGlobals/WizSmallDlg.h"
#include "NoteSettings.h"

template <class T>
class CWizNoteSmallDlgBase : public CWizSmallDlgBase<T>
{
public:
	typedef CWizSmallDlgBase<T> CWizNoteSmallDlgBase_BaseClass;
	//
	BEGIN_MSG_MAP(CWizNoteSmallDlgBase)
		COMMAND_ID_HANDLER(ID_COLOR_BLUE, OnColorBlue)
		COMMAND_ID_HANDLER(ID_COLOR_GREEN, OnColorGreen)
		COMMAND_ID_HANDLER(ID_COLOR_PINK, OnColorPink)
		COMMAND_ID_HANDLER(ID_COLOR_PURPLE, OnColorPurple)
		COMMAND_ID_HANDLER(ID_COLOR_WHITE, OnColorWhite)
		COMMAND_ID_HANDLER(ID_COLOR_YELLOW, OnColorYellow)
		COMMAND_ID_HANDLER(ID_OPACITY_100, OnOpacity100)
		COMMAND_ID_HANDLER(ID_OPACITY_80, OnOpacity80)
		COMMAND_ID_HANDLER(ID_OPACITY_60, OnOpacity60)
		COMMAND_ID_HANDLER(ID_OPACITY_40, OnOpacity40)
		COMMAND_ID_HANDLER(ID_OPACITY_20, OnOpacity20)
		COMMAND_ID_HANDLER(ID_SMALL_WINDOW_CLOSE, OnSmallWindowClose)
		CHAIN_MSG_MAP(CWizNoteSmallDlgBase_BaseClass)
	END_MSG_MAP()

	LRESULT OnColorBlue(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_BLUE);

		return 0;
	}

	LRESULT OnColorGreen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_GREEN);

		return 0;
	}

	LRESULT OnColorPink(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_PINK);

		return 0;
	}

	LRESULT OnColorPurple(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_PRUPLE);

		return 0;
	}

	LRESULT OnColorWhite(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_WHITE);

		return 0;
	}

	LRESULT OnColorYellow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetColor(WIZCOLOR_YELLOW);

		return 0;
	}

	LRESULT OnOpacity100(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetTransparentPercent(100 - 100);

		return 0;
	}

	LRESULT OnOpacity80(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetTransparentPercent(100 - 80);

		return 0;
	}

	LRESULT OnOpacity60(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetTransparentPercent(100 - 60);

		return 0;
	}
	LRESULT OnOpacity40(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetTransparentPercent(100 - 40);

		return 0;
	}

	LRESULT OnOpacity20(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your command handler code here
		SetTransparentPercent(100 - 20);

		return 0;
	}

	virtual void InitClient()
	{
		CWizSmallDlgBase::InitClient();
		//
		m_btnUp.SetIcon(IDI_ICON_UP_BUTTON);
		m_btnUp.SetDisabledIcon(IDI_ICON_UP_BUTTON_GRAY);
		m_btnDown.SetIcon(IDI_ICON_DOWN_BUTTON);
		m_btnDown.SetDisabledIcon(IDI_ICON_DOWN_BUTTON_GRAY);
		//
		SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);
		SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)), FALSE);
	}
	//
	virtual BOOL GetShowTaskbarButton()
	{
		return IsShowTaskbarButtons();
	}
	LRESULT OnSmallWindowClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Close();
		return 0;
	}
};
