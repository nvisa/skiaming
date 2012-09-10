// NoteDlg.h : Declaration of the CNoteDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "WizNoteSmallDlgBase.h"
#include "NoteEdit.h"

// CNoteDlg
#define IDC_BUTTON_NEW				WIZ_ID_SMALL_DLG_BUTTON_BASE + 1
#define IDC_EDIT_TEXT				WIZ_ID_SMALL_DLG_BUTTON_BASE + 2

class CNoteDlg
	: public CWizNoteSmallDlgBase<CNoteDlg>
	, public CWinDataExchange<CNoteDlg>
	, public CComObject<CWizAtlDropTarget>
{
public:
	CNoteDlg(CWizKMDatabase* pDatabase, LPCTSTR lpszInitTitle);
	~CNoteDlg();

private:
	CWizKMDatabase* m_pDatabase;
	CString m_strInitTitle;
	//
	CWizVistaIconButton m_btnNew;
	CNoteEdit m_editText;
	//
	CFont m_fontText;
public:

BEGIN_MSG_MAP(CNoteDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	COMMAND_HANDLER(IDC_BUTTON_NEW, BN_CLICKED, OnBnClickedButtonNew)
	COMMAND_ID_HANDLER(ID_NOTE_DELETE, OnNoteDelete)
	COMMAND_ID_HANDLER(ID_NOTE_SETSELECTIONASTITLE, OnNoteSetselectionastitle)
	COMMAND_ID_HANDLER(ID_NOTE_CLOSEALLNOTESBUTTHIS, OnNoteCloseallnotesbutthis)
	COMMAND_ID_HANDLER(ID_NOTE_ADDTOCALENDAR, OnNoteAddtocalendar)
	COMMAND_ID_HANDLER(ID_NOTE_SETSELECTIONASTAGS, OnNoteSetselectionastags)
	COMMAND_ID_HANDLER(ID_NOTE_FONT, OnNoteFont)
	CHAIN_MSG_MAP(CWizNoteSmallDlgBase<CNoteDlg>)
	REFLECT_NOTIFICATIONS()
END_MSG_MAP()

public:
	STDMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHODIMP DragLeave( void);
	STDMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
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
	virtual BOOL IsModified() const;
	//
	virtual BOOL AutoSave();
	//
	COleDateTime GetDateModified();
private:
	CComPtr<IWizDocument> m_spDocument;
	//
	static CString AutoGetTitle(LPCTSTR lpszText);
	static CString AutoGetTagsText(CString& strText);
	//
	BOOL CreateDocument();
	//
	CMenu m_menu;
public:
	BOOL GetSelText(CString& strSelText);
	//
	virtual BOOL SavePos();
	virtual BOOL LoadPos();
	//
	BOOL SaveData();
	BOOL SaveParam();
	//
	BOOL LoadData();
	BOOL LoadParam();
	//
	BOOL Load();
	//
	CComPtr<IWizDocument> GetDocument() const { return m_spDocument; }
	BOOL SetDocument(IWizDocument* pDocument);
	//
	CNoteEdit& GetNoteEdit() { return m_editText; }
	//
	BOOL UpdateFont();
public:

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNoteDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNoteSetselectionastitle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNoteCloseallnotesbutthis(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNoteAddtocalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNcLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNoteSetselectionastags(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNoteFont(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


