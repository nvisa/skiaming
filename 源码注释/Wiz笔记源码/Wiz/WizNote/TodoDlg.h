// TodoDlg.h : Declaration of the CTodoDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "WizNoteSmallDlgBase.h"

#include "WizTodoTreeCtrl.h"

#include "../Globals/WizKMObjectMessage.h"

#define IDC_BUTTON_PREV				WIZ_ID_SMALL_DLG_BUTTON_BASE + 1
#define IDC_BUTTON_NEXT				WIZ_ID_SMALL_DLG_BUTTON_BASE + 2
#define IDC_TREE_TODO				WIZ_ID_SMALL_DLG_BUTTON_BASE + 3


class CTodoDlg
	: public CWizNoteSmallDlgBase<CTodoDlg>
	, public CWinDataExchange<CTodoDlg>
	, public CWizKMObjectMessageHandler<CTodoDlg>
{
public:
	CTodoDlg(CWizKMDatabase* pDatabase);
	~CTodoDlg();

private:
	CWizKMDatabase* m_pDatabase;
	//
	CWizVistaIconButton m_btnPrev;
	CWizVistaIconButton m_btnNext;
	//
	CWizTodoTreeCtrl m_wndList;
public:

BEGIN_MSG_MAP(CTodoDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WIZ_WM_UM_NOTIFY_PARENT_COMMAND, OnNotifyParentCommand)
	COMMAND_HANDLER(IDC_BUTTON_PREV, BN_CLICKED, OnBnClickedButtonPrev)
	COMMAND_HANDLER(IDC_BUTTON_NEXT, BN_CLICKED, OnBnClickedButtonNext)
	CHAIN_MSG_MAP(CWizNoteSmallDlgBase<CTodoDlg>)
	CHAIN_MSG_MAP(CWizKMObjectMessageHandler<CTodoDlg>)
	REFLECT_NOTIFICATIONS()
END_MSG_MAP()
private:
	CComPtr<IWizDocument> m_spDocument;
	//
	BOOL CreateDocument();
	//
	CMenu m_menu;
	//
	COleDateTime m_tTodoListDate;
	BOOL SetDocument(IWizDocument* pDocument, const COleDateTime& t);
public:
	virtual CString GetTitle();
	virtual CRect GetTitleRect();
	//
	virtual void InitClient();
	virtual void UpdateLayout();
	virtual void UpdateLockButtonIcon();
	virtual void SetColor(COLORREF cr);
	//
	virtual void Close();
	//
	virtual BOOL AutoSave();
public:
	//
	BOOL SaveData();
	BOOL LoadData();
	//
	void SaveStatus();
	void LoadStatus();
	//
	CComPtr<IWizDocument> GetDocument() const { return m_spDocument; }
	//
	void SetMinimize();
	//
	BOOL IsModified() const;
	//
	BOOL LoadByTime(const COleDateTime& t);
	//
	void LoadCurrentTodoList();
	//
	void Refresh();
	//
	BOOL SetDocument(IWizDocument* pDocument);
	//
	CComPtr<IWizEvent> GetTodoEvent(WIZTODODATA* pData);
	//
	BOOL OnModifyDocument(LPCTSTR lpszGUID);
public:

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNotifyParentCommand(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonPrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


